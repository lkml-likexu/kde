#### [RFC 1/2] vhost: IFC VF hardware operation layer
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11192197
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DCCA114DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:31:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B34092067D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:31:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389151AbfJPBbM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 21:31:12 -0400
Received: from mga17.intel.com ([192.55.52.151]:60917 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726786AbfJPBbL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 21:31:11 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 15 Oct 2019 18:31:10 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,302,1566889200";
   d="scan'208";a="279378817"
Received: from lingshan-mobl5.ccr.corp.intel.com (HELO localhost.localdomain)
 ([10.249.68.79])
  by orsmga001.jf.intel.com with ESMTP; 15 Oct 2019 18:31:01 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC 1/2] vhost: IFC VF hardware operation layer
Date: Wed, 16 Oct 2019 09:30:49 +0800
Message-Id: <20191016013050.3918-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20191016013050.3918-1-lingshan.zhu@intel.com>
References: <20191016013050.3918-1-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduced ifcvf_base layer, which handles IFC VF NIC
hardware operations and configurations.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_base.c | 390 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 137 ++++++++++++++
 2 files changed, 527 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h

diff --git a/drivers/vhost/ifcvf/ifcvf_base.c b/drivers/vhost/ifcvf/ifcvf_base.c
new file mode 100644
index 000000000000..b85e14c9bdcf
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.c
@@ -0,0 +1,390 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include "ifcvf_base.h"
+
+static void *get_cap_addr(struct ifcvf_hw *hw, struct virtio_pci_cap *cap)
+{
+	u8 bar = cap->bar;
+	u32 length = cap->length;
+	u32 offset = cap->offset;
+	struct ifcvf_adapter *ifcvf =
+		container_of(hw, struct ifcvf_adapter, vf);
+
+	if (bar >= IFCVF_PCI_MAX_RESOURCE) {
+		IFC_ERR(ifcvf->dev,
+			"Invalid bar number %u to get capabilities.\n", bar);
+		return NULL;
+	}
+
+	if (offset + length < offset) {
+		IFC_ERR(ifcvf->dev, "offset(%u) + length(%u) overflows\n",
+			offset, length);
+		return NULL;
+	}
+
+	if (offset + length > hw->mem_resource[cap->bar].len) {
+		IFC_ERR(ifcvf->dev,
+			"offset(%u) + len(%u) overflows bar%u to get capabilities.\n",
+			offset, length, bar);
+		return NULL;
+	}
+
+	return hw->mem_resource[bar].addr + offset;
+}
+
+int ifcvf_read_config_range(struct pci_dev *dev,
+			uint32_t *val, int size, int where)
+{
+	int i;
+
+	for (i = 0; i < size; i += 4) {
+		if (pci_read_config_dword(dev, where + i, val + i / 4) < 0)
+			return -1;
+	}
+	return 0;
+}
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev)
+{
+	int ret;
+	u8 pos;
+	struct virtio_pci_cap cap;
+	u32 i;
+	u16 notify_off;
+
+	ret = pci_read_config_byte(dev, PCI_CAPABILITY_LIST, &pos);
+
+	if (ret < 0) {
+		IFC_ERR(&dev->dev, "failed to read PCI capability list.\n");
+		return -EIO;
+	}
+
+	while (pos) {
+		ret = ifcvf_read_config_range(dev, (u32 *)&cap,
+				sizeof(cap), pos);
+
+		if (ret < 0) {
+			IFC_ERR(&dev->dev, "failed to get PCI capability at %x",
+					pos);
+			break;
+		}
+
+		if (cap.cap_vndr != PCI_CAP_ID_VNDR)
+			goto next;
+
+		IFC_INFO(&dev->dev, "read PCI config:\n"
+					"config type: %u.\n"
+					"PCI bar: %u.\n"
+					"PCI bar offset: %u.\n"
+					"PCI config len: %u.\n",
+					cap.cfg_type, cap.bar,
+					cap.offset, cap.length);
+
+		switch (cap.cfg_type) {
+		case VIRTIO_PCI_CAP_COMMON_CFG:
+			hw->common_cfg = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->common_cfg = %p.\n",
+					hw->common_cfg);
+			break;
+		case VIRTIO_PCI_CAP_NOTIFY_CFG:
+			pci_read_config_dword(dev, pos + sizeof(cap),
+				&hw->notify_off_multiplier);
+			hw->notify_bar = cap.bar;
+			hw->notify_base = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->notify_base = %p.\n",
+					hw->notify_base);
+			break;
+		case VIRTIO_PCI_CAP_ISR_CFG:
+			hw->isr = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->isr = %p.\n", hw->isr);
+			break;
+		case VIRTIO_PCI_CAP_DEVICE_CFG:
+			hw->dev_cfg = get_cap_addr(hw, &cap);
+			IFC_INFO(&dev->dev, "hw->dev_cfg = %p.\n", hw->dev_cfg);
+			break;
+		}
+next:
+		pos = cap.cap_next;
+	}
+
+	if (hw->common_cfg == NULL || hw->notify_base == NULL ||
+		hw->isr == NULL || hw->dev_cfg == NULL) {
+		IFC_ERR(&dev->dev, "Incomplete PCI capabilities.\n");
+		return -1;
+	}
+
+	for (i = 0; i < (IFCVF_MAX_QUEUE_PAIRS * 2); i++) {
+		iowrite16(i, &hw->common_cfg->queue_select);
+		notify_off = ioread16(&hw->common_cfg->queue_notify_off);
+		hw->notify_addr[i] = (void *)((u8 *)hw->notify_base +
+				notify_off * hw->notify_off_multiplier);
+	}
+
+	hw->lm_cfg = hw->mem_resource[4].addr;
+
+	IFC_INFO(&dev->dev, "PCI capability mapping:\n"
+				"common cfg: %p\n"
+				"notify base: %p\n"
+				"isr cfg: %p\n"
+				"device cfg: %p\n"
+				"multiplier: %u\n",
+				hw->common_cfg,
+				hw->notify_base,
+				hw->isr,
+				hw->dev_cfg,
+				hw->notify_off_multiplier);
+
+	return 0;
+}
+
+static u8 ifcvf_get_status(struct ifcvf_hw *hw)
+{
+	return ioread8(&hw->common_cfg->device_status);
+}
+
+static void ifcvf_set_status(struct ifcvf_hw *hw, u8 status)
+{
+	iowrite8(status, &hw->common_cfg->device_status);
+}
+
+static void ifcvf_reset(struct ifcvf_hw *hw)
+{
+	ifcvf_set_status(hw, 0);
+
+	/* flush status write */
+	ifcvf_get_status(hw);
+	hw->generation++;
+}
+
+static void ifcvf_add_status(struct ifcvf_hw *hw, u8 status)
+{
+	if (status != 0)
+		status |= ifcvf_get_status(hw);
+
+	ifcvf_set_status(hw, status);
+	ifcvf_get_status(hw);
+}
+
+u64 ifcvf_get_features(struct ifcvf_hw *hw)
+{
+	u32 features_lo, features_hi;
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+
+	iowrite32(0, &cfg->device_feature_select);
+	features_lo = ioread32(&cfg->device_feature);
+
+	iowrite32(1, &cfg->device_feature_select);
+	features_hi = ioread32(&cfg->device_feature);
+
+	return ((u64)features_hi << 32) | features_lo;
+}
+static int ifcvf_with_feature(struct ifcvf_hw *hw, u64 bit)
+{
+	return (hw->req_features & (1ULL << bit)) != 0;
+}
+
+static void ifcvf_read_dev_config(struct ifcvf_hw *hw, u64 offset,
+		       void *dst, int length)
+{
+	int i;
+	u8 *p;
+	u8 old_gen, new_gen;
+
+	do {
+		old_gen = ioread8(&hw->common_cfg->config_generation);
+
+		p = dst;
+		for (i = 0; i < length; i++)
+			*p++ = ioread8((u8 *)hw->dev_cfg + offset + i);
+
+		new_gen = ioread8(&hw->common_cfg->config_generation);
+	} while (old_gen != new_gen);
+}
+
+void ifcvf_get_linkstatus(struct ifcvf_hw *hw, u8 *is_linkup)
+{
+	u16 status;
+	u64 host_features;
+
+	host_features = ifcvf_get_features(hw);
+	if (ifcvf_with_feature(hw, VIRTIO_NET_F_STATUS)) {
+		ifcvf_read_dev_config(hw,
+				offsetof(struct ifcvf_net_config, status),
+				&status, sizeof(status));
+		if ((status & VIRTIO_NET_S_LINK_UP) == 0)
+			(*is_linkup) = 1;
+		else
+			(*is_linkup) = 0;
+	} else
+		(*is_linkup) = 0;
+}
+
+static void ifcvf_set_features(struct ifcvf_hw *hw, u64 features)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+
+	iowrite32(0, &cfg->guest_feature_select);
+	iowrite32(features & ((1ULL << 32) - 1), &cfg->guest_feature);
+
+	iowrite32(1, &cfg->guest_feature_select);
+	iowrite32(features >> 32, &cfg->guest_feature);
+}
+
+static int ifcvf_config_features(struct ifcvf_hw *hw)
+{
+	u64 host_features;
+	struct ifcvf_adapter *ifcvf =
+		container_of(hw, struct ifcvf_adapter, vf);
+
+	host_features = ifcvf_get_features(hw);
+	hw->req_features &= host_features;
+
+	ifcvf_set_features(hw, hw->req_features);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_FEATURES_OK);
+
+	if (!(ifcvf_get_status(hw) & VIRTIO_CONFIG_S_FEATURES_OK)) {
+		IFC_ERR(ifcvf->dev, "Failed to set FEATURES_OK status\n");
+		return -EIO;
+	}
+
+	return 0;
+}
+
+static void io_write64_twopart(u64 val, u32 *lo, u32 *hi)
+{
+	iowrite32(val & ((1ULL << 32) - 1), lo);
+	iowrite32(val >> 32, hi);
+}
+
+static int ifcvf_hw_enable(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg;
+	u8 *lm_cfg;
+	u32 i;
+	struct ifcvf_adapter *ifcvf =
+		container_of(hw, struct ifcvf_adapter, vf);
+
+	cfg = hw->common_cfg;
+	lm_cfg = hw->lm_cfg;
+
+	iowrite16(IFCVF_MSI_CONFIG_OFF, &cfg->msix_config);
+	if (ioread16(&cfg->msix_config) == VIRTIO_MSI_NO_VECTOR) {
+		IFC_ERR(ifcvf->dev, "No msix vector for device config.\n");
+		return -1;
+	}
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		iowrite16(i, &cfg->queue_select);
+		io_write64_twopart(hw->vring[i].desc, &cfg->queue_desc_lo,
+				&cfg->queue_desc_hi);
+		io_write64_twopart(hw->vring[i].avail, &cfg->queue_avail_lo,
+				&cfg->queue_avail_hi);
+		io_write64_twopart(hw->vring[i].used, &cfg->queue_used_lo,
+				&cfg->queue_used_hi);
+		iowrite16(hw->vring[i].size, &cfg->queue_size);
+
+		*(u32 *)(lm_cfg + IFCVF_LM_RING_STATE_OFFSET +
+				(i / 2) * IFCVF_LM_CFG_SIZE + (i % 2) * 4) =
+			(u32)hw->vring[i].last_avail_idx |
+			((u32)hw->vring[i].last_used_idx << 16);
+
+		iowrite16(i + IFCVF_MSI_QUEUE_OFF, &cfg->queue_msix_vector);
+		if (ioread16(&cfg->queue_msix_vector) ==
+				VIRTIO_MSI_NO_VECTOR) {
+			IFC_ERR(ifcvf->dev,
+				"No msix vector for queue %u.\n", i);
+			return -1;
+		}
+
+		iowrite16(1, &cfg->queue_enable);
+	}
+
+	return 0;
+}
+
+static void ifcvf_hw_disable(struct ifcvf_hw *hw)
+{
+	u32 i;
+	struct virtio_pci_common_cfg *cfg;
+
+	cfg = hw->common_cfg;
+
+	iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->msix_config);
+	for (i = 0; i < hw->nr_vring; i++) {
+		iowrite16(i, &cfg->queue_select);
+		iowrite16(0, &cfg->queue_enable);
+		iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->queue_msix_vector);
+	}
+}
+
+int ifcvf_start_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_reset(hw);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_ACKNOWLEDGE);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER);
+
+	if (ifcvf_config_features(hw) < 0)
+		return -1;
+
+	if (ifcvf_hw_enable(hw) < 0)
+		return -1;
+
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER_OK);
+
+	return 0;
+}
+
+void ifcvf_stop_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_hw_disable(hw);
+	ifcvf_reset(hw);
+}
+
+void ifcvf_enable_logging_vf(struct ifcvf_hw *hw, u64 log_base, u64 log_size)
+{
+	u8 *lm_cfg;
+
+	lm_cfg = hw->lm_cfg;
+
+	*(u32 *)(lm_cfg + IFCVF_LM_BASE_ADDR_LOW) =
+		log_base & IFCVF_32_BIT_MASK;
+
+	*(u32 *)(lm_cfg + IFCVF_LM_BASE_ADDR_HIGH) =
+		(log_base >> 32) & IFCVF_32_BIT_MASK;
+
+	*(u32 *)(lm_cfg + IFCVF_LM_END_ADDR_LOW) =
+		(log_base + log_size) & IFCVF_32_BIT_MASK;
+
+	*(u32 *)(lm_cfg + IFCVF_LM_END_ADDR_HIGH) =
+		((log_base + log_size) >> 32) & IFCVF_32_BIT_MASK;
+
+	*(u32 *)(lm_cfg + IFCVF_LM_LOGGING_CTRL) = IFCVF_LM_ENABLE_VF;
+}
+
+void ifcvf_disable_logging(struct ifcvf_hw *hw)
+{
+	u8 *lm_cfg;
+
+	lm_cfg = hw->lm_cfg;
+	*(u32 *)(lm_cfg + IFCVF_LM_LOGGING_CTRL) = IFCVF_LM_DISABLE;
+}
+
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid)
+{
+
+	iowrite16(qid, hw->notify_addr[qid]);
+}
+
+u8 ifcvf_get_notify_region(struct ifcvf_hw *hw)
+{
+	return hw->notify_bar;
+}
+
+u64 ifcvf_get_queue_notify_off(struct ifcvf_hw *hw, int qid)
+{
+	return (u8 *)hw->notify_addr[qid] -
+		(u8 *)hw->mem_resource[hw->notify_bar].addr;
+}
diff --git a/drivers/vhost/ifcvf/ifcvf_base.h b/drivers/vhost/ifcvf/ifcvf_base.h
new file mode 100644
index 000000000000..1ab1a1c40f24
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.h
@@ -0,0 +1,137 @@
+/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#ifndef _IFCVF_H_
+#define _IFCVF_H_
+
+#include <linux/virtio_mdev.h>
+#include <linux/pci.h>
+#include <linux/pci_regs.h>
+#include <uapi/linux/virtio_net.h>
+#include <uapi/linux/virtio_config.h>
+#include <uapi/linux/virtio_pci.h>
+
+#define IFCVF_VENDOR_ID         0x1AF4
+#define IFCVF_DEVICE_ID         0x1041
+#define IFCVF_SUBSYS_VENDOR_ID  0x8086
+#define IFCVF_SUBSYS_DEVICE_ID  0x001A
+
+/*
+ * Some ifcvf feature bits (currently bits 28 through 31) are
+ * reserved for the transport being used (eg. ifcvf_ring), the
+ * rest are per-device feature bits.
+ */
+#define IFCVF_TRANSPORT_F_START 28
+#define IFCVF_TRANSPORT_F_END   34
+
+#define IFC_SUPPORTED_FEATURES \
+		((1ULL << VIRTIO_NET_F_MAC)			| \
+		 (1ULL << VIRTIO_F_ANY_LAYOUT)			| \
+		 (1ULL << VIRTIO_F_VERSION_1)			| \
+		 (1ULL << VHOST_F_LOG_ALL)			| \
+		 (1ULL << VIRTIO_NET_F_GUEST_ANNOUNCE)		| \
+		 (1ULL << VIRTIO_NET_F_CTRL_VQ)			| \
+		 (1ULL << VIRTIO_NET_F_STATUS)			| \
+		 (1ULL << VIRTIO_NET_F_MRG_RXBUF)) /* not fully supported */
+
+#define IFCVF_MAX_QUEUE_PAIRS		1
+#define IFCVF_MAX_QUEUES		2
+
+#define IFCVF_QUEUE_ALIGNMENT		PAGE_SIZE
+
+#define IFCVF_MSI_CONFIG_OFF	0
+#define IFCVF_MSI_QUEUE_OFF	1
+#define IFCVF_PCI_MAX_RESOURCE	6
+
+/* 46 bit CPU physical address, avoid overlap */
+#define LM_IOVA 0x400000000000
+
+#define IFCVF_LM_CFG_SIZE		0x40
+#define IFCVF_LM_RING_STATE_OFFSET	0x20
+
+#define IFCVF_LM_LOGGING_CTRL		0x0
+
+#define IFCVF_LM_BASE_ADDR_LOW		0x10
+#define IFCVF_LM_BASE_ADDR_HIGH		0x14
+#define IFCVF_LM_END_ADDR_LOW		0x18
+#define IFCVF_LM_END_ADDR_HIGH		0x1c
+
+#define IFCVF_LM_DISABLE		0x0
+#define IFCVF_LM_ENABLE_VF		0x1
+#define IFCVF_LM_ENABLE_PF		0x3
+
+#define IFCVF_32_BIT_MASK		0xffffffff
+
+#define IFC_ERR(dev, fmt, ...)	dev_err(dev, fmt, ##__VA_ARGS__)
+#define IFC_INFO(dev, fmt, ...)	dev_info(dev, fmt, ##__VA_ARGS__)
+
+struct ifcvf_net_config {
+	u8    mac[6];
+	u16   status;
+	u16   max_virtqueue_pairs;
+} __packed;
+
+struct ifcvf_pci_mem_resource {
+	u64      phys_addr; /**< Physical address, 0 if not resource. */
+	u64      len;       /**< Length of the resource. */
+	u8       *addr;     /**< Virtual address, NULL when not mapped. */
+};
+
+struct vring_info {
+	u64 desc;
+	u64 avail;
+	u64 used;
+	u16 size;
+	u16 last_avail_idx;
+	u16 last_used_idx;
+	bool ready;
+	char msix_name[256];
+	struct virtio_mdev_callback cb;
+};
+
+struct ifcvf_hw {
+	u8	*isr;
+	u8	notify_bar;
+	u8	*lm_cfg;
+	u8	status;
+	u8	nr_vring;
+	u16	*notify_base;
+	u16	*notify_addr[IFCVF_MAX_QUEUE_PAIRS * 2];
+	u32	generation;
+	u32	notify_off_multiplier;
+	u64	req_features;
+	struct	virtio_pci_common_cfg *common_cfg;
+	struct	ifcvf_net_config *dev_cfg;
+	struct	vring_info vring[IFCVF_MAX_QUEUE_PAIRS * 2];
+	struct	ifcvf_pci_mem_resource mem_resource[IFCVF_PCI_MAX_RESOURCE];
+};
+
+#define IFC_PRIVATE_TO_VF(adapter) \
+	(&((struct ifcvf_adapter *)adapter)->vf)
+
+#define IFCVF_MAX_INTR (IFCVF_MAX_QUEUE_PAIRS * 2 + 1)
+
+struct ifcvf_adapter {
+	struct	device *dev;
+	struct	mutex mdev_lock;
+	int	mdev_count;
+	struct	list_head dma_maps;
+	int	vectors;
+	struct	ifcvf_hw vf;
+};
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev);
+u64 ifcvf_get_features(struct ifcvf_hw *hw);
+int ifcvf_start_hw(struct ifcvf_hw *hw);
+void ifcvf_stop_hw(struct ifcvf_hw *hw);
+void ifcvf_enable_logging(struct ifcvf_hw *hw, u64 log_base, u64 log_size);
+void ifcvf_enable_logging_vf(struct ifcvf_hw *hw, u64 log_base, u64 log_size);
+void ifcvf_disable_logging(struct ifcvf_hw *hw);
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid);
+void ifcvf_get_linkstatus(struct ifcvf_hw *hw, u8 *is_linkup);
+u8 ifcvf_get_notify_region(struct ifcvf_hw *hw);
+u64 ifcvf_get_queue_notify_off(struct ifcvf_hw *hw, int qid);
+
+#endif /* _IFCVF_H_ */

From patchwork Wed Oct 16 01:30:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11192199
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EFC8914DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:31:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C63E620873
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:31:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389248AbfJPBbW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 21:31:22 -0400
Received: from mga14.intel.com ([192.55.52.115]:44948 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726786AbfJPBbV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 21:31:21 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 15 Oct 2019 18:31:21 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,302,1566889200";
   d="scan'208";a="279378843"
Received: from lingshan-mobl5.ccr.corp.intel.com (HELO localhost.localdomain)
 ([10.249.68.79])
  by orsmga001.jf.intel.com with ESMTP; 15 Oct 2019 18:31:13 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC 2/2] vhost: IFC VF vdpa layer
Date: Wed, 16 Oct 2019 09:30:50 +0800
Message-Id: <20191016013050.3918-3-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20191016013050.3918-1-lingshan.zhu@intel.com>
References: <20191016013050.3918-1-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduced IFC VF operations for vdpa, which complys to
vhost_mdev interfaces, handles IFC VF initialization,
configuration and removal.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_main.c | 541 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 541 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c

diff --git a/drivers/vhost/ifcvf/ifcvf_main.c b/drivers/vhost/ifcvf/ifcvf_main.c
new file mode 100644
index 000000000000..c48a29969a85
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_main.c
@@ -0,0 +1,541 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include <linux/interrupt.h>
+#include <linux/module.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/sysfs.h>
+
+#include "ifcvf_base.h"
+
+#define VERSION_STRING	"0.1"
+#define DRIVER_AUTHOR	"Intel Corporation"
+#define IFCVF_DRIVER_NAME	"ifcvf"
+
+static irqreturn_t ifcvf_intr_handler(int irq, void *arg)
+{
+	struct vring_info *vring = arg;
+
+	if (vring->cb.callback)
+		return vring->cb.callback(vring->cb.private);
+
+	return IRQ_HANDLED;
+}
+
+static u64 ifcvf_mdev_get_features(struct mdev_device *mdev)
+{
+	return IFC_SUPPORTED_FEATURES;
+}
+
+static int ifcvf_mdev_set_features(struct mdev_device *mdev, u64 features)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->req_features = features;
+
+	return 0;
+}
+
+static u64 ifcvf_mdev_get_vq_state(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf->vring[qid].last_avail_idx;
+}
+
+static int ifcvf_mdev_set_vq_state(struct mdev_device *mdev, u16 qid, u64 num)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->vring[qid].last_used_idx = num;
+	vf->vring[qid].last_avail_idx = num;
+
+	return 0;
+}
+
+static int ifcvf_mdev_set_vq_address(struct mdev_device *mdev, u16 idx,
+				     u64 desc_area, u64 driver_area,
+				     u64 device_area)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->vring[idx].desc = desc_area;
+	vf->vring[idx].avail = driver_area;
+	vf->vring[idx].used = device_area;
+
+	return 0;
+}
+
+static void ifcvf_mdev_set_vq_num(struct mdev_device *mdev, u16 qid, u32 num)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->vring[qid].size = num;
+}
+
+static void ifcvf_mdev_set_vq_ready(struct mdev_device *mdev,
+				u16 qid, bool ready)
+{
+
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->vring[qid].ready = ready;
+}
+
+static bool ifcvf_mdev_get_vq_ready(struct mdev_device *mdev, u16 qid)
+{
+
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf->vring[qid].ready;
+}
+
+static void ifcvf_mdev_set_vq_cb(struct mdev_device *mdev, u16 idx,
+				 struct virtio_mdev_callback *cb)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->vring[idx].cb = *cb;
+}
+
+static void ifcvf_mdev_kick_vq(struct mdev_device *mdev, u16 idx)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	ifcvf_notify_queue(vf, idx);
+}
+
+static u8 ifcvf_mdev_get_status(struct mdev_device *mdev)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf->status;
+}
+
+static u32 ifcvf_mdev_get_generation(struct mdev_device *mdev)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf->generation;
+}
+
+static int ifcvf_mdev_get_version(struct mdev_device *mdev)
+{
+	return VIRTIO_MDEV_VERSION;
+}
+
+static u32 ifcvf_mdev_get_device_id(struct mdev_device *mdev)
+{
+	return IFCVF_DEVICE_ID;
+}
+
+static u32 ifcvf_mdev_get_vendor_id(struct mdev_device *mdev)
+{
+	return IFCVF_VENDOR_ID;
+}
+
+static u16 ifcvf_mdev_get_vq_align(struct mdev_device *mdev)
+{
+	return IFCVF_QUEUE_ALIGNMENT;
+}
+
+static int ifcvf_start_datapath(void *private)
+{
+	int i, ret;
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+
+	for (i = 0; i < (IFCVF_MAX_QUEUE_PAIRS * 2); i++) {
+		if (!vf->vring[i].ready)
+			break;
+
+		if (!vf->vring[i].size)
+			break;
+
+		if (!vf->vring[i].desc || !vf->vring[i].avail ||
+			!vf->vring[i].used)
+			break;
+	}
+	vf->nr_vring = i;
+
+	ret = ifcvf_start_hw(vf);
+	return ret;
+}
+
+static int ifcvf_stop_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	int i;
+
+	for (i = 0; i < IFCVF_MAX_QUEUES; i++)
+		vf->vring[i].cb.callback = NULL;
+
+	ifcvf_stop_hw(vf);
+
+	return 0;
+}
+
+static void ifcvf_reset_vring(struct ifcvf_adapter *adapter)
+{
+	int i;
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vf->vring[i].last_used_idx = 0;
+		vf->vring[i].last_avail_idx = 0;
+		vf->vring[i].desc = 0;
+		vf->vring[i].avail = 0;
+		vf->vring[i].used = 0;
+		vf->vring[i].ready = 0;
+		vf->vring->cb.callback = NULL;
+		vf->vring->cb.private = NULL;
+	}
+}
+
+static void ifcvf_mdev_set_status(struct mdev_device *mdev, u8 status)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	vf->status = status;
+
+	if (status == 0) {
+		ifcvf_stop_datapath(adapter);
+		ifcvf_reset_vring(adapter);
+		return;
+	}
+
+	if (status & VIRTIO_CONFIG_S_DRIVER_OK) {
+		ifcvf_start_datapath(adapter);
+		return;
+	}
+}
+
+static u16 ifcvf_mdev_get_queue_max(struct mdev_device *mdev)
+{
+	return IFCVF_MAX_QUEUES;
+}
+
+static struct virtio_mdev_device_ops ifc_mdev_ops = {
+	.get_features  = ifcvf_mdev_get_features,
+	.set_features  = ifcvf_mdev_set_features,
+	.get_status    = ifcvf_mdev_get_status,
+	.set_status    = ifcvf_mdev_set_status,
+	.get_queue_max = ifcvf_mdev_get_queue_max,
+	.get_vq_state   = ifcvf_mdev_get_vq_state,
+	.set_vq_state   = ifcvf_mdev_set_vq_state,
+	.set_vq_cb      = ifcvf_mdev_set_vq_cb,
+	.set_vq_ready   = ifcvf_mdev_set_vq_ready,
+	.get_vq_ready	= ifcvf_mdev_get_vq_ready,
+	.set_vq_num     = ifcvf_mdev_set_vq_num,
+	.set_vq_address = ifcvf_mdev_set_vq_address,
+	.kick_vq        = ifcvf_mdev_kick_vq,
+	.get_generation	= ifcvf_mdev_get_generation,
+	.get_version	= ifcvf_mdev_get_version,
+	.get_device_id	= ifcvf_mdev_get_device_id,
+	.get_vendor_id	= ifcvf_mdev_get_vendor_id,
+	.get_vq_align	= ifcvf_mdev_get_vq_align,
+};
+
+static int ifcvf_init_msix(struct ifcvf_adapter *adapter)
+{
+	int vector, i, ret, irq;
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	struct ifcvf_hw *vf = &adapter->vf;
+
+	ret = pci_alloc_irq_vectors(pdev, IFCVF_MAX_INTR,
+			IFCVF_MAX_INTR, PCI_IRQ_MSIX);
+	if (ret < 0) {
+		IFC_ERR(adapter->dev, "Failed to alloc irq vectors.\n");
+		return ret;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		ret = request_irq(irq, ifcvf_intr_handler, 0,
+				pci_name(pdev), &vf->vring[i]);
+		if (ret) {
+			IFC_ERR(adapter->dev,
+				"Failed to request irq for vq %d.\n", i);
+			return ret;
+		}
+	}
+
+	return 0;
+}
+
+static void ifcvf_destroy_adapter(struct ifcvf_adapter *adapter)
+{
+	int i, vector, irq;
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		free_irq(irq, &vf->vring[i]);
+	}
+}
+
+static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
+{
+	const char *name = "vhost accelerator (virtio ring compatible)";
+
+	return sprintf(buf, "%s\n", name);
+}
+MDEV_TYPE_ATTR_RO(name);
+
+static ssize_t device_api_show(struct kobject *kobj, struct device *dev,
+			       char *buf)
+{
+	return sprintf(buf, "%s\n", VIRTIO_MDEV_DEVICE_API_STRING);
+}
+MDEV_TYPE_ATTR_RO(device_api);
+
+static ssize_t available_instances_show(struct kobject *kobj,
+					struct device *dev, char *buf)
+{
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+
+	return sprintf(buf, "%d\n", adapter->mdev_count);
+}
+
+MDEV_TYPE_ATTR_RO(available_instances);
+
+static ssize_t type_show(struct kobject *kobj,
+			struct device *dev, char *buf)
+{
+	return sprintf(buf, "%s\n", "net");
+}
+
+MDEV_TYPE_ATTR_RO(type);
+
+
+static struct attribute *mdev_types_attrs[] = {
+	&mdev_type_attr_name.attr,
+	&mdev_type_attr_device_api.attr,
+	&mdev_type_attr_available_instances.attr,
+	&mdev_type_attr_type.attr,
+	NULL,
+};
+
+static struct attribute_group mdev_type_group = {
+	.name  = "vdpa_virtio",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group *mdev_type_groups[] = {
+	&mdev_type_group,
+	NULL,
+};
+
+const struct attribute_group *mdev_dev_groups[] = {
+	NULL,
+};
+
+static int ifcvf_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	int ret = 0;
+
+	mutex_lock(&adapter->mdev_lock);
+
+	if (adapter->mdev_count < 1) {
+		ret = -EINVAL;
+		goto out;
+	}
+
+	mdev_set_class_id(mdev, MDEV_ID_VHOST);
+	mdev_set_dev_ops(mdev, &ifc_mdev_ops);
+
+	mdev_set_drvdata(mdev, adapter);
+	mdev_set_iommu_device(mdev_dev(mdev), dev);
+
+	INIT_LIST_HEAD(&adapter->dma_maps);
+	adapter->mdev_count--;
+
+out:
+	mutex_unlock(&adapter->mdev_lock);
+	return ret;
+}
+
+static int ifcvf_mdev_remove(struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+
+	mutex_lock(&adapter->mdev_lock);
+	adapter->mdev_count++;
+	mutex_unlock(&adapter->mdev_lock);
+
+	return 0;
+}
+
+static struct mdev_parent_ops ifcvf_mdev_fops = {
+	.owner			= THIS_MODULE,
+	.supported_type_groups	= mdev_type_groups,
+	.mdev_attr_groups	= mdev_dev_groups,
+	.create			= ifcvf_mdev_create,
+	.remove			= ifcvf_mdev_remove,
+};
+
+static int ifcvf_probe(struct pci_dev *pdev, const struct pci_device_id *id)
+{
+	struct device *dev = &pdev->dev;
+	struct ifcvf_adapter *adapter;
+	struct ifcvf_hw *vf;
+	int ret, i;
+
+	adapter = kzalloc(sizeof(struct ifcvf_adapter), GFP_KERNEL);
+	if (adapter == NULL) {
+		ret = -ENOMEM;
+		goto fail;
+	}
+
+	mutex_init(&adapter->mdev_lock);
+	adapter->mdev_count = 1;
+	adapter->dev = dev;
+
+	pci_set_drvdata(pdev, adapter);
+
+	ret = pci_enable_device(pdev);
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to enable device.\n");
+		goto free_adapter;
+	}
+
+	ret = pci_request_regions(pdev, IFCVF_DRIVER_NAME);
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to request MMIO region.\n");
+		goto disable_device;
+	}
+
+	pci_set_master(pdev);
+
+	ret = ifcvf_init_msix(adapter);
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to initialize MSIX.\n");
+		goto free_msix;
+	}
+
+	vf = &adapter->vf;
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		vf->mem_resource[i].phys_addr = pci_resource_start(pdev, i);
+		vf->mem_resource[i].len = pci_resource_len(pdev, i);
+		if (!vf->mem_resource[i].len) {
+			vf->mem_resource[i].addr = NULL;
+			continue;
+		}
+
+		vf->mem_resource[i].addr = pci_iomap_range(pdev, i, 0,
+				vf->mem_resource[i].len);
+		if (!vf->mem_resource[i].addr) {
+			IFC_ERR(adapter->dev, "Failed to map IO resource %d\n",
+				i);
+			return -1;
+		}
+	}
+
+	if (ifcvf_init_hw(vf, pdev) < 0)
+		return -1;
+
+	ret = mdev_register_device(dev, &ifcvf_mdev_fops);
+	if (ret) {
+		IFC_ERR(adapter->dev,  "Failed to register mdev device\n");
+		goto destroy_adapter;
+	}
+
+	return 0;
+
+destroy_adapter:
+	ifcvf_destroy_adapter(adapter);
+free_msix:
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+disable_device:
+	pci_disable_device(pdev);
+free_adapter:
+	kfree(adapter);
+fail:
+	return ret;
+}
+
+static void ifcvf_remove(struct pci_dev *pdev)
+{
+	struct device *dev = &pdev->dev;
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	struct ifcvf_hw *vf;
+	int i;
+
+	mdev_unregister_device(dev);
+
+	vf = &adapter->vf;
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		if (vf->mem_resource[i].addr) {
+			pci_iounmap(pdev, vf->mem_resource[i].addr);
+			vf->mem_resource[i].addr = NULL;
+		}
+	}
+
+	ifcvf_destroy_adapter(adapter);
+	pci_free_irq_vectors(pdev);
+
+	pci_release_regions(pdev);
+	pci_disable_device(pdev);
+
+	kfree(adapter);
+}
+
+static struct pci_device_id ifcvf_pci_ids[] = {
+	{ PCI_DEVICE_SUB(IFCVF_VENDOR_ID,
+			IFCVF_DEVICE_ID,
+			IFCVF_SUBSYS_VENDOR_ID,
+			IFCVF_SUBSYS_DEVICE_ID) },
+	{ 0 },
+};
+MODULE_DEVICE_TABLE(pci, ifcvf_pci_ids);
+
+static struct pci_driver ifcvf_driver = {
+	.name     = IFCVF_DRIVER_NAME,
+	.id_table = ifcvf_pci_ids,
+	.probe    = ifcvf_probe,
+	.remove   = ifcvf_remove,
+};
+
+static int __init ifcvf_init_module(void)
+{
+	int ret;
+
+	ret = pci_register_driver(&ifcvf_driver);
+	return ret;
+}
+
+static void __exit ifcvf_exit_module(void)
+{
+	pci_unregister_driver(&ifcvf_driver);
+}
+
+module_init(ifcvf_init_module);
+module_exit(ifcvf_exit_module);
+
+MODULE_LICENSE("GPL v2");
+MODULE_VERSION(VERSION_STRING);
+MODULE_AUTHOR(DRIVER_AUTHOR);
```
#### [PATCH v9 01/22] RISC-V: Add bitmap reprensenting ISA features common across CPUs
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11193651
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67421112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 16:08:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 348E521D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 16:08:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="oLI/CT7F";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="dEp3w929"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391688AbfJPQI3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 12:08:29 -0400
Received: from esa6.hgst.iphmx.com ([216.71.154.45]:34733 "EHLO
        esa6.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391376AbfJPQI3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 12:08:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1571242109; x=1602778109;
  h=from:to:cc:subject:date:message-id:references:
   in-reply-to:content-transfer-encoding:mime-version;
  bh=pJGJIS/ysA8yI6JN1fWlYWTPzJxxG3lRxMek57vYPN0=;
  b=oLI/CT7FAkqXyDWXxM2w7rUtplwczvekzamMsjT4LFN8Plbm1VhT3M/c
   5JURoMlLf8ZH7wknx2B+tJoVvaqpjnvhpI7yYFkxczsPS4GgljvSiK3pW
   n7vkIdtuKrdOthkh5YErvCQZ2FnIFCQlOMB42Or/K+/MRwsD9/hEMZyTL
   cCADLejvZTiyXRxQXY2Y/l2a5sLEJIDlEY7sZBfY/CW53bSb7do01AtUN
   C+Tut0/FQ+SLQ61LsiApJ9hFOBgoI4BryxR2Jgd/9M9uYoMGelmIlHk0X
   ILKN/VY4OasN+44JHqP5Ub7K35bff2s5x1NFcDecHxgIIGP3dUCQJD/4p
   Q==;
IronPort-SDR: 
 1OsA3JhEI744edCbz4ki7P/oKySWU3zAX5vDHGJP8ImVekJBGLSz9g6LFCjUqQfDugCQonDOga
 xsvbJPUQq0zw6Wu0rZTNiBqvPN1mD2qdTAcRa4ba7qYEcmHeNo47pKsNUC7lerFW75djbTk1GQ
 9MLYM3Fh71SKRCQUIsc70UFjBGWJZZytdd2dYkTjenlul82qGlXhtYihOgQgAGchON1k5KaLhG
 lODnPn0SHGcTozQ4ZUwtpQsDhUF1WDj2BFmbGcV3zQoQ8vRxinw2ACzYOd6NXXzM+RNitplF6C
 FIU=
X-IronPort-AV: E=Sophos;i="5.67,304,1566835200";
   d="scan'208";a="122255431"
Received: from mail-dm3nam05lp2050.outbound.protection.outlook.com (HELO
 NAM05-DM3-obe.outbound.protection.outlook.com) ([104.47.49.50])
  by ob1.hgst.iphmx.com with ESMTP; 17 Oct 2019 00:08:26 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=hMWIF9VCsq3LUTTgszSX1dElVpLDHp0zH2AGYLIBx7crtKI1RoAA/EHfHpAjFOtOK7GYb9g+I8gCDpnWO3cdSsJWF7nFuYEcAtMyCtk8EMwYYDui/bHZz6jk86HEA7vtVbkf8nqHRT5rncHe199ZQQPltAMXFlyoyWKFzOEFN9N2YVlMWAZ8QnekCEe0cI1FNNPBsbg1b0j5AN09OxGF9QcJSzEkl/5vAaw2IgP0Kewn0W25aU5oL7ay+hg1kkh7E4+Vp/rqRhYzMDJ9Za0w9gDSMV84eUy4XLTrECjHGbxjYyNUlxFguYDCCK+1TpQIULgNrMuvHJWAcbevVpZ5KQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yw6LGxYTP7bkwQ7jGBixNL373jB02un0ExmgMRYNunI=;
 b=LGCQJD3d9ZPlgtu/V0Spk6mTqOkR1dAz4Gb5rtggnfRsfCDLhOH1lWxw4udFHvQegsuy2xdiFByYhw7bP6LgYr/I6MiMzPmdlhzOpKmRbHvLV3WqjzJeF9VOvfh8EhDn30SLzB3NTx3D2alLSw9FEWQDC7DAMhSZfZ2ZeK2ZSZqrQVhhs3D4wkAczNobjbtX0iKySfYXChVbuh0Snh7/QGU2MowYQjP4bM7/u4REnT7n5FIUc5+r5cyXcQw4l9rOKRLe9XmJdnq7qk1CNpb2uLK8weFE4eG32sYbufvVLxVeMtaJz5HSz9Ze09KQaNNDV0+p1xWEJ8Hq7u6N8PlEvQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yw6LGxYTP7bkwQ7jGBixNL373jB02un0ExmgMRYNunI=;
 b=dEp3w929F0ddofmcUrGkWr0gzgMea1JtjnovSCFSsoUj4q7uCWkC4vBN0Tziwf+jZYU2oFJ3vtIQ+2rGwy7ztu5M17/OWh3osxIsrJ646x5BAYcDaCnttkaWGgjn75kVQrYp2py7MVeshNZxFC05u1wSXkXay2p2r5ABJZXJcVU=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB7038.namprd04.prod.outlook.com (10.186.146.24) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2347.16; Wed, 16 Oct 2019 16:08:24 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a%7]) with mapi id 15.20.2347.023; Wed, 16 Oct 2019
 16:08:24 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v9 01/22] RISC-V: Add bitmap reprensenting ISA features common
 across CPUs
Thread-Topic: [PATCH v9 01/22] RISC-V: Add bitmap reprensenting ISA features
 common across CPUs
Thread-Index: AQHVhDvvIKmoDfkSiUyU/8i6Kcn5bA==
Date: Wed, 16 Oct 2019 16:08:23 +0000
Message-ID: <20191016160649.24622-2-anup.patel@wdc.com>
References: <20191016160649.24622-1-anup.patel@wdc.com>
In-Reply-To: <20191016160649.24622-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MAXPR01CA0098.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:5d::16) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [106.51.27.162]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 90b4e889-58fb-4af7-e4ae-08d7525311f0
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: MN2PR04MB7038:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB7038794E9DA9BB14F7423C018D920@MN2PR04MB7038.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:317;
x-forefront-prvs: 0192E812EC
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(366004)(376002)(396003)(136003)(346002)(39860400002)(199004)(189003)(102836004)(44832011)(486006)(2616005)(476003)(386003)(25786009)(446003)(52116002)(99286004)(186003)(76176011)(55236004)(66066001)(26005)(6506007)(5660300002)(36756003)(11346002)(64756008)(6436002)(66946007)(66446008)(66476007)(66556008)(86362001)(6486002)(4326008)(6512007)(1076003)(305945005)(14454004)(256004)(7736002)(7416002)(478600001)(6116002)(71190400001)(3846002)(54906003)(110136005)(2906002)(316002)(71200400001)(8936002)(9456002)(50226002)(81156014)(81166006)(8676002);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB7038;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 XtCSt5AppPyMsdkmH8FOkDLSJfWOjilSUUpqLc1iK+uyyz3guYLkPXH489qBAFCpQxGwd9X3gWNo+GLCfn/Hnnd077sA49LxeaoRd+e41Sx9vc4d43Pifrf7cbkO1UN+klqDhyRSlOK4rwpuUyNS7b3W0PBOIiXeYFB0ofd1/T0b94S2xdotEoe3IuhlGnBCvofY9MrP8XcbXlPg7BlA7Nc2ETnZ8chWdhc0cwaHl5Pag5RJZblo3VQgcKRIcuad0V1Z6fsGHJoHknMwErTxMggqQIcKx1765uryC7EeCwT5JzMv7N/ARMH5iWz1B4DiOINH8a3fpOg6QJZtjDYRgqFxxV3dWBjGzXGgZ9R/jxfap0Mjuth747nj8QFtffF3vS7FKrWR6SzYhB3oVYMNliMBPuCuiLRCB2TGi08VZq8=
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 90b4e889-58fb-4af7-e4ae-08d7525311f0
X-MS-Exchange-CrossTenant-originalarrivaltime: 16 Oct 2019 16:08:23.9273
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 VHY9gvQBg7Z53H1Ihmn67mr+swXZRP3l40Ze9LuvxqCgOT+TllZkBZEtlWYnxz4bl40ojqLW37E+a4U+XBkBZw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB7038
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds riscv_isa bitmap which represents Host ISA features
common across all Host CPUs. The riscv_isa is not same as elf_hwcap
because elf_hwcap will only have ISA features relevant for user-space
apps whereas riscv_isa will have ISA features relevant to both kernel
and user-space apps.

One of the use-case for riscv_isa bitmap is in KVM hypervisor where
we will use it to do following operations:

1. Check whether hypervisor extension is available
2. Find ISA features that need to be virtualized (e.g. floating
   point support, vector extension, etc.)

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Signed-off-by: Atish Patra <atish.patra@wdc.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/hwcap.h | 22 +++++++++
 arch/riscv/kernel/cpufeature.c | 83 ++++++++++++++++++++++++++++++++--
 2 files changed, 102 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: SVM: Fix potential wrong physical id in avic_handle_ldr_update
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11192741
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB4A81390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 09:24:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE15221D7C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 09:24:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391959AbfJPJYr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 05:24:47 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:47562 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2391925AbfJPJYr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 05:24:47 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 9493277D8DAEA9F0BA43;
        Wed, 16 Oct 2019 17:24:45 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Wed, 16 Oct 2019
 17:24:34 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>,
        <mingfangsen@huawei.com>
Subject: [PATCH] KVM: SVM: Fix potential wrong physical id in
 avic_handle_ldr_update
Date: Wed, 16 Oct 2019 17:25:08 +0800
Message-ID: <1571217908-7693-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest physical APIC ID may not equal to vcpu->vcpu_id in some case.
We may set the wrong physical id in avic_handle_ldr_update as we
always use vcpu->vcpu_id.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/svm.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH V3 1/2] linux headers: update against Linux 5.4-rc2
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11193341
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE6D076
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 13:07:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83844218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 13:07:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="BWbwZrVB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405318AbfJPNHl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 09:07:41 -0400
Received: from mail-pl1-f193.google.com ([209.85.214.193]:41022 "EHLO
        mail-pl1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2405314AbfJPNHl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 09:07:41 -0400
Received: by mail-pl1-f193.google.com with SMTP id t10so11251813plr.8
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 06:07:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=wZh677+pLYfT7Nth5oMeUYsjvXgYmTkpkEHZHSrS44o=;
        b=BWbwZrVBsSsukjhMAItwCHkL1v1Qz8t+u2h56Q23Uo+22G3BAg02AjTaLmW1UzLfz6
         YlW+a7vzXUzOUYgaDznRdn4ECZK/ru3erAteHzKI+roFLAnl9e1TsjgXCtLUUMDLI7FZ
         BhBAaGz09JQM4OCO2MlelMRn9rbshD2gg60A7xx+W45QWvTUKr2kOTA0VclziafaJLv6
         EeyFfyuOyXqeJOh1Nnr7jR+ulGlvxTfFepPexUT0AUBP4ElzwSggivmiYIUZa5dU44QG
         7z6bHkvZ9Hf8Le+pxl0LuGnnq6k6nmB2zngAs7H4/Xg7pNB6f9fAFUqbc2wpdd+7sSKF
         x6VA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=wZh677+pLYfT7Nth5oMeUYsjvXgYmTkpkEHZHSrS44o=;
        b=l953mNMJ6ysRjruX85uwSSA+yH++6Lr3F+ODii8MBnzSymvn69gNjRC44JmlHUJ/0w
         mc//ENzarZzn50ZMF62V/sxmh8vO2p+opZ6eiErtq5inbUKyrdJZ5I5i8rAQhB4BbcUG
         dkA+N7vcIAC5TS7NmM6pjBSud8Pc5c+F5oDl3sMNCq7uTRQRn6alkmsUm6Lt6R3L2rlZ
         7FsRETMhGZ9QzJ8kCP8jq9d9qNBo+PgkDouh0lb7ggXV6NRSjpeJpZgHF6fUpqgqkWBk
         NDH8lx3apWhSr1u5JsM5nGkoYGTb8Ovzdoi5gCwJQEIGwMPQH9Isn04xnRzhQcWD8jNe
         zw6A==
X-Gm-Message-State: APjAAAWMiTqO5dv6btfydkkWAGJj/bJQfyscYUPvc+zJh/g0JOGI4mLJ
        AxtW6DLaIAt/D7kp+uhbqO4=
X-Google-Smtp-Source: 
 APXvYqzoAJDe6Zk0KdLrhXUfsQHY0RnhOOCn8IgZLMDBrX0JwcLElHcLNUg6nhhvJ1qXlT2OEaH40g==
X-Received: by 2002:a17:902:7b87:: with SMTP id
 w7mr40967934pll.110.1571231257686;
        Wed, 16 Oct 2019 06:07:37 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.39])
        by smtp.googlemail.com with ESMTPSA id
 s97sm2792296pjc.4.2019.10.16.06.07.34
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Wed, 16 Oct 2019 06:07:37 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: mst@redhat.com, cohuck@redhat.com, pbonzini@redhat.com,
        rth@twiddle.net, ehabkost@redhat.com, mtosatti@redhat.com,
        rkagan@virtuozzo.com, vkuznets@redhat.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH V3 1/2] linux headers: update against Linux 5.4-rc2
Date: Wed, 16 Oct 2019 21:07:24 +0800
Message-Id: <20191016130725.5045-2-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
In-Reply-To: <20191016130725.5045-1-Tianyu.Lan@microsoft.com>
References: <20191016130725.5045-1-Tianyu.Lan@microsoft.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

commit da0c9ea146cbe92b832f1b0f694840ea8eb33cce

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
 include/standard-headers/asm-x86/bootparam.h |  2 +
 include/standard-headers/asm-x86/kvm_para.h  |  1 +
 include/standard-headers/linux/ethtool.h     | 24 ++++++++++
 include/standard-headers/linux/pci_regs.h    | 19 +++++++-
 include/standard-headers/linux/virtio_ids.h  |  2 +
 include/standard-headers/linux/virtio_pmem.h |  6 +--
 linux-headers/asm-arm/kvm.h                  | 16 ++++++-
 linux-headers/asm-arm/unistd-common.h        |  2 +
 linux-headers/asm-arm64/kvm.h                | 21 +++++++-
 linux-headers/asm-generic/mman-common.h      | 18 ++++---
 linux-headers/asm-generic/mman.h             | 10 ++--
 linux-headers/asm-generic/unistd.h           | 10 +++-
 linux-headers/asm-mips/mman.h                |  3 ++
 linux-headers/asm-mips/unistd_n32.h          |  2 +
 linux-headers/asm-mips/unistd_n64.h          |  2 +
 linux-headers/asm-mips/unistd_o32.h          |  2 +
 linux-headers/asm-powerpc/mman.h             |  6 +--
 linux-headers/asm-powerpc/unistd_32.h        |  2 +
 linux-headers/asm-powerpc/unistd_64.h        |  2 +
 linux-headers/asm-s390/kvm.h                 |  6 +++
 linux-headers/asm-s390/unistd_32.h           |  2 +
 linux-headers/asm-s390/unistd_64.h           |  2 +
 linux-headers/asm-x86/kvm.h                  | 28 ++++++++---
 linux-headers/asm-x86/unistd.h               |  2 +-
 linux-headers/asm-x86/unistd_32.h            |  2 +
 linux-headers/asm-x86/unistd_64.h            |  2 +
 linux-headers/asm-x86/unistd_x32.h           |  2 +
 linux-headers/linux/kvm.h                    | 12 ++++-
 linux-headers/linux/psp-sev.h                |  5 +-
 linux-headers/linux/vfio.h                   | 71 ++++++++++++++++++++--------
 30 files changed, 225 insertions(+), 59 deletions(-)

```
#### [PATCH v2 1/4] vfio-ccw: Refactor how the traces are built
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11192205
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 73031139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:58:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5D24C214AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 01:58:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388759AbfJPB6b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 21:58:31 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:49892 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728706AbfJPB6b (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 15 Oct 2019 21:58:31 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9G1q6fs081233
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 21:58:30 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vnkksjk6p-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 21:58:29 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Wed, 16 Oct 2019 02:58:27 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 16 Oct 2019 02:58:26 +0100
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9G1wOY754919190
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Oct 2019 01:58:24 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 88F0342041;
        Wed, 16 Oct 2019 01:58:24 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 727B742049;
        Wed, 16 Oct 2019 01:58:24 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 16 Oct 2019 01:58:24 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id CF3D8E01B5; Wed, 16 Oct 2019 03:58:23 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Steffen Maier <maier@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v2 1/4] vfio-ccw: Refactor how the traces are built
Date: Wed, 16 Oct 2019 03:58:19 +0200
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191016015822.72425-1-farman@linux.ibm.com>
References: <20191016015822.72425-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19101601-4275-0000-0000-000003726D73
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101601-4276-0000-0000-000038858107
Message-Id: <20191016015822.72425-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-15_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910160015
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 3cd90214b70f ("vfio: ccw: add tracepoints for interesting error
paths") added a quick trace point to determine where a channel program
failed while being processed.  It's a great addition, but adding more
traces to vfio-ccw is more cumbersome than it needs to be.

Let's refactor how this is done, so that additional traces are easier
to add and can exist outside of the FSM if we ever desire.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/Makefile         |  4 ++--
 drivers/s390/cio/vfio_ccw_cp.h    |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c   |  3 ---
 drivers/s390/cio/vfio_ccw_trace.c | 12 ++++++++++++
 drivers/s390/cio/vfio_ccw_trace.h |  2 ++
 5 files changed, 17 insertions(+), 5 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c

```
#### [PATCH v3 1/4] vfio-ccw: Refactor how the traces are built
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11193431
Return-Path: <SRS0=YWSl=YJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AC301668
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 14:20:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 84CCF218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 16 Oct 2019 14:20:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393991AbfJPOUv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 10:20:51 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39574 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2393982AbfJPOUu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Oct 2019 10:20:50 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9GE3Pdq005541
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 10:20:49 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vp3cfcff8-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 10:20:49 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Wed, 16 Oct 2019 15:20:47 +0100
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 16 Oct 2019 15:20:45 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9GEKhvT33685716
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Oct 2019 14:20:43 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D38F1A4053;
        Wed, 16 Oct 2019 14:20:42 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BAF1CA405D;
        Wed, 16 Oct 2019 14:20:42 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 16 Oct 2019 14:20:42 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 5B5E8E02BA; Wed, 16 Oct 2019 16:20:42 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Steffen Maier <maier@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v3 1/4] vfio-ccw: Refactor how the traces are built
Date: Wed, 16 Oct 2019 16:20:37 +0200
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191016142040.14132-1-farman@linux.ibm.com>
References: <20191016142040.14132-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19101614-0028-0000-0000-000003AA98B8
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101614-0029-0000-0000-0000246CB26C
Message-Id: <20191016142040.14132-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-16_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910160124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 3cd90214b70f ("vfio: ccw: add tracepoints for interesting error
paths") added a quick trace point to determine where a channel program
failed while being processed.  It's a great addition, but adding more
traces to vfio-ccw is more cumbersome than it needs to be.

Let's refactor how this is done, so that additional traces are easier
to add and can exist outside of the FSM if we ever desire.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/Makefile         |  4 ++--
 drivers/s390/cio/vfio_ccw_cp.h    |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c   |  3 ---
 drivers/s390/cio/vfio_ccw_trace.c | 12 ++++++++++++
 drivers/s390/cio/vfio_ccw_trace.h |  2 ++
 5 files changed, 17 insertions(+), 5 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c

```
