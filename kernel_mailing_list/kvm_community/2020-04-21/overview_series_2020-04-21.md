#### [PATCH v1 01/15] nitro_enclaves: Add ioctl interface definition
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11502067
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA8B181
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92F3F20738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="dcJohmdr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729360AbgDUSmQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 14:42:16 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:53386 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725870AbgDUSmQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 14:42:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1587494536; x=1619030536;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=p3KGxzu0ADrayANgam9z2ixDAMnSo4ulJX3kwnOktHY=;
  b=dcJohmdrbRTD833Md9aPsOCI9Cn3fSv0r1rELPiU1Wa1mMsBllLTYi8O
   I4jsmkAkZJLGYSRD56ArD376BSriALd8PKHLgjTm7OOOvOsOuOZrYn4ro
   VdZcTM7ocQwfmBxXdF/8OCnx/jPd8ySfMi8gxUMXTkvGfnQCvk06rhLC9
   Q=;
IronPort-SDR: 
 U2pF+64vnqDEzdek/BksJqqn8twIcJln9O+n26hSW7xkaukg9egpCd3UUBG9xeiMWoziJumiLL
 +FIvD9qptL+g==
X-IronPort-AV: E=Sophos;i="5.72,411,1580774400";
   d="scan'208";a="38565615"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 21 Apr 2020 18:42:14 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com (Postfix) with
 ESMTPS id 83459A1DBC;
        Tue, 21 Apr 2020 18:42:13 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:12 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:04 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@amazon.com>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1 01/15] nitro_enclaves: Add ioctl interface definition
Date: Tue, 21 Apr 2020 21:41:36 +0300
Message-ID: <20200421184150.68011-2-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200421184150.68011-1-andraprs@amazon.com>
References: <20200421184150.68011-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D25UWC004.ant.amazon.com (10.43.162.201) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver handles the enclave lifetime management. This
includes enclave creation, termination and setting up its resources such
as memory and CPU.

An enclave runs alongside the VM that spawned it. It is abstracted as a
process running in the VM that launched it. The process interacts with
the NE driver, that exposes an ioctl interface for creating an enclave
and setting up its resources.

Include the KVM API as part of the provided ioctl interface, with an
additional ENCLAVE_START ioctl command that triggers the enclave run.

Signed-off-by: Alexandru Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
 include/linux/nitro_enclaves.h      | 23 +++++++++++++
 include/uapi/linux/nitro_enclaves.h | 52 +++++++++++++++++++++++++++++
 2 files changed, 75 insertions(+)
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h

diff --git a/include/linux/nitro_enclaves.h b/include/linux/nitro_enclaves.h
new file mode 100644
index 000000000000..7e593a9fbf8c
--- /dev/null
+++ b/include/linux/nitro_enclaves.h
@@ -0,0 +1,23 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+/*
+ * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
+ *
+ * This program is free software; you can redistribute it and/or modify it
+ * under the terms and conditions of the GNU General Public License,
+ * version 2, as published by the Free Software Foundation.
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
+ * GNU General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, see <http://www.gnu.org/licenses/>.
+ */
+
+#ifndef _LINUX_NITRO_ENCLAVES_H_
+#define _LINUX_NITRO_ENCLAVES_H_
+
+#include <uapi/linux/nitro_enclaves.h>
+
+#endif /* _LINUX_NITRO_ENCLAVES_H_ */
diff --git a/include/uapi/linux/nitro_enclaves.h b/include/uapi/linux/nitro_enclaves.h
new file mode 100644
index 000000000000..b90dfcf6253a
--- /dev/null
+++ b/include/uapi/linux/nitro_enclaves.h
@@ -0,0 +1,52 @@
+/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
+/*
+ * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
+ *
+ * This program is free software; you can redistribute it and/or modify it
+ * under the terms and conditions of the GNU General Public License,
+ * version 2, as published by the Free Software Foundation.
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
+ * GNU General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, see <http://www.gnu.org/licenses/>.
+ */
+
+#ifndef _UAPI_LINUX_NITRO_ENCLAVES_H_
+#define _UAPI_LINUX_NITRO_ENCLAVES_H_
+
+#include <linux/kvm.h>
+#include <linux/types.h>
+
+/* Nitro Enclaves (NE) Kernel Driver Interface */
+
+/**
+ * The command is used to trigger enclave start after the enclave resources,
+ * such as memory and CPU, have been set.
+ *
+ * The enclave start metadata is an in / out data structure. It includes
+ * provided info by the caller - enclave cid and flags - and returns the
+ * slot uid and the cid (if input cid is 0).
+ */
+#define NE_ENCLAVE_START _IOWR('B', 0x1, struct enclave_start_metadata)
+
+/* Setup metadata necessary for enclave start. */
+struct enclave_start_metadata {
+	/* Flags for the enclave to start with (e.g. debug mode) (in). */
+	__u64 flags;
+
+	/**
+	 * Context ID (CID) for the enclave vsock device. If 0 as input, the
+	 * CID is autogenerated by the hypervisor and returned back as output
+	 * by the driver (in/out).
+	 */
+	__u64 enclave_cid;
+
+	/* Slot unique id mapped to the enclave to start (out). */
+	__u64 slot_uid;
+};
+
+#endif /* _UAPI_LINUX_NITRO_ENCLAVES_H_ */

From patchwork Tue Apr 21 18:41:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11502071
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6A4581
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 91C25206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="Y303xp9J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729462AbgDUSm0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 14:42:26 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:62215 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729380AbgDUSmY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 14:42:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1587494543; x=1619030543;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=Hcr8IWCBd9vxlMeEDzpaZbC8VQKGocQ+6X2HB/FejJk=;
  b=Y303xp9Jjbq4gXs0eJFlEwp7olLJ2Z9ny36/Nu8P0AWORfHjQsyC13fz
   Dw3/nlJmAOBYJ/RG+jNBGo2RqJg/E5xBbTiK/qsLi9Gzp5D2bFUuxSCXC
   oqdUbYe4S7I1AZYaE4UhCXbD+BupkyIy4sVqubZa4dj2ZogwCyGqbfm0o
   8=;
IronPort-SDR: 
 Z8UgWe5qohhMnkdOd8WQ/IQCIT9yo2+w8oOvkssHSCxGa79il6QccproX3tanx6htZ/TDJUbin
 GJHqpp01NmVQ==
X-IronPort-AV: E=Sophos;i="5.72,411,1580774400";
   d="scan'208";a="39978365"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 21 Apr 2020 18:42:22 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2a-538b0bfb.us-west-2.amazon.com (Postfix) with
 ESMTPS id 3044FA1DE0;
        Tue, 21 Apr 2020 18:42:21 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:20 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:12 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@amazon.com>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1 02/15] nitro_enclaves: Define the PCI device interface
Date: Tue, 21 Apr 2020 21:41:37 +0300
Message-ID: <20200421184150.68011-3-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200421184150.68011-1-andraprs@amazon.com>
References: <20200421184150.68011-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D25UWC004.ant.amazon.com (10.43.162.201) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves (NE) driver communicates with a new PCI device, that
is exposed to a virtual machine (VM) and handles commands meant for
handling enclaves lifetime e.g. creation, termination, setting memory
regions. The communication with the PCI device is handled using a MMIO
space and MSI-X interrupts.

This device communicates with the hypervisor on the host, where the VM
that spawned the enclave itself run, e.g. to launch a VM that is used
for the enclave.

Define the MMIO space of the PCI device, the commands that are
provided by this device. Add an internal data structure used as private
data for the PCI device driver and the functions for the PCI device init
/ uninit and command requests handling.

Signed-off-by: Alexandru-Catalin Vasile <lexnv@amazon.com>
Signed-off-by: Alexandru Ciobotaru <alcioa@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
 .../virt/amazon/nitro_enclaves/ne_pci_dev.h   | 266 ++++++++++++++++++
 1 file changed, 266 insertions(+)
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_pci_dev.h

diff --git a/drivers/virt/amazon/nitro_enclaves/ne_pci_dev.h b/drivers/virt/amazon/nitro_enclaves/ne_pci_dev.h
new file mode 100644
index 000000000000..e703419ed29d
--- /dev/null
+++ b/drivers/virt/amazon/nitro_enclaves/ne_pci_dev.h
@@ -0,0 +1,266 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+/*
+ * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
+ *
+ * This program is free software; you can redistribute it and/or modify it
+ * under the terms and conditions of the GNU General Public License,
+ * version 2, as published by the Free Software Foundation.
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
+ * GNU General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, see <http://www.gnu.org/licenses/>.
+ */
+
+#ifndef _NE_PCI_DEV_H_
+#define _NE_PCI_DEV_H_
+
+#include <linux/atomic.h>
+#include <linux/list.h>
+#include <linux/mutex.h>
+#include <linux/pci.h>
+#include <linux/pci_ids.h>
+#include <linux/wait.h>
+
+/* Nitro Enclaves (NE) PCI device identifier */
+
+#define PCI_DEVICE_ID_NE (0xe4c1)
+#define PCI_BAR_NE (0x03)
+
+/* Device registers */
+
+/**
+ * (1 byte) Register to notify the device that the driver is using it
+ * (Read/Write).
+ */
+#define NE_ENABLE (0x0000)
+#define NE_ENABLE_ON (0x00)
+#define NE_ENABLE_OFF (0x01)
+
+/* (2 bytes) Register to select the device run-time version (Read/Write). */
+#define NE_VERSION (0x0002)
+#define NE_VERSION_MAX (0x0001)
+
+/**
+ * (4 bytes) Register to notify the device what command was requested
+ * (Write-Only).
+ */
+#define NE_COMMAND (0x0004)
+
+/**
+ * (4 bytes) Register to notify the driver that a reply or a device event
+ * is available (Read-Only):
+ * - Lower half  - command reply counter
+ * - Higher half - out-of-band device event counter
+ */
+#define NE_EVTCNT (0x000c)
+#define NE_EVTCNT_REPLY_SHIFT (0)
+#define NE_EVTCNT_REPLY_MASK (0x0000ffff)
+#define NE_EVTCNT_REPLY(cnt) (((cnt) & NE_EVTCNT_REPLY_MASK) >> \
+			      NE_EVTCNT_REPLY_SHIFT)
+#define NE_EVTCNT_EVENT_SHIFT (16)
+#define NE_EVTCNT_EVENT_MASK (0xffff0000)
+#define NE_EVTCNT_EVENT(cnt) (((cnt) & NE_EVTCNT_EVENT_MASK) >> \
+			      NE_EVTCNT_EVENT_SHIFT)
+
+/* (240 bytes) Buffer for sending the command request payload (Read/Write). */
+#define NE_SEND_DATA (0x0010)
+
+/* (240 bytes) Buffer for receiving the command reply payload (Read-Only). */
+#define NE_RECV_DATA (0x0100)
+
+/* Device MMIO buffer sizes */
+
+/* 240 bytes for send / recv buffer. */
+#define NE_SEND_DATA_SIZE (240)
+#define NE_RECV_DATA_SIZE (240)
+
+/* MSI-X interrupt vectors */
+
+/* MSI-X vector used for command reply notification. */
+#define NE_VEC_REPLY (0)
+
+/* MSI-X vector used for out-of-band events e.g. enclave crash. */
+#define NE_VEC_EVENT (1)
+
+/* Device command types. */
+enum ne_pci_dev_cmd_type {
+	INVALID_CMD = 0,
+	ENCLAVE_START = 1,
+	ENCLAVE_GET_SLOT = 2,
+	ENCLAVE_STOP = 3,
+	SLOT_ALLOC = 4,
+	SLOT_FREE = 5,
+	SLOT_ADD_MEM = 6,
+	SLOT_ADD_VCPU = 7,
+	SLOT_COUNT = 8,
+	NEXT_SLOT = 9,
+	SLOT_INFO = 10,
+	SLOT_ADD_BULK_VCPUS = 11,
+	MAX_CMD,
+};
+
+/* Device commands - payload structure for requests and replies. */
+
+struct enclave_start_req {
+	/* Slot unique id mapped to the enclave to start. */
+	u64 slot_uid;
+
+	/**
+	 * Context ID (CID) for the enclave vsock device.
+	 * If 0, CID is autogenerated.
+	 */
+	u64 enclave_cid;
+
+	/* Flags for the enclave to start with (e.g. debug mode). */
+	u64 flags;
+} __attribute__ ((__packed__));
+
+struct enclave_get_slot_req {
+	/* Context ID (CID) for the enclave vsock device. */
+	u64 enclave_cid;
+} __attribute__ ((__packed__));
+
+struct enclave_stop_req {
+	/* Slot unique id mapped to the enclave to stop. */
+	u64 slot_uid;
+} __attribute__ ((__packed__));
+
+struct slot_alloc_req {
+	/* In order to avoid weird sizeof edge cases. */
+	u8 unused;
+} __attribute__ ((__packed__));
+
+struct slot_free_req {
+	/* Slot unique id mapped to the slot to free. */
+	u64 slot_uid;
+} __attribute__ ((__packed__));
+
+struct slot_add_mem_req {
+	/* Slot unique id mapped to the slot to add the memory region to. */
+	u64 slot_uid;
+
+	/* Physical address of the memory region to add to the slot. */
+	u64 paddr;
+
+	/* Memory size, in bytes, of the memory region to add to the slot. */
+	u64 size;
+} __attribute__ ((__packed__));
+
+struct slot_add_vcpu_req {
+	/* Slot unique id mapped to the slot to add the vCPU to. */
+	u64 slot_uid;
+
+	/* vCPU ID of the CPU to add to the enclave. */
+	u32 vcpu_id;
+} __attribute__ ((__packed__));
+
+struct slot_count_req {
+	/* In order to avoid weird sizeof edge cases. */
+	u8 unused;
+} __attribute__ ((__packed__));
+
+struct next_slot_req {
+	/* Slot unique id of the next slot in the iteration. */
+	u64 slot_uid;
+} __attribute__ ((__packed__));
+
+struct slot_info_req {
+	/* Slot unique id mapped to the slot to get information about. */
+	u64 slot_uid;
+} __attribute__ ((__packed__));
+
+struct slot_add_bulk_vcpus_req {
+	/* Slot unique id mapped to the slot to add vCPUs to. */
+	u64 slot_uid;
+
+	/* Number of vCPUs to add to the slot. */
+	u64 nr_vcpus;
+} __attribute__ ((__packed__));
+
+struct ne_pci_dev_cmd_reply {
+	s32 rc;
+
+	/* Valid for all commands except SLOT_COUNT. */
+	u64 slot_uid;
+
+	/* Valid for ENCLAVE_START command. */
+	u64 enclave_cid;
+
+	/* Valid for SLOT_COUNT command. */
+	u64 slot_count;
+
+	/* Valid for SLOT_ALLOC and SLOT_INFO commands. */
+	u64 mem_regions;
+
+	/* Valid for SLOT_INFO command. */
+	u64 mem_size;
+
+	/* Valid for SLOT_INFO command. */
+	u64 nr_vcpus;
+
+	/* Valid for SLOT_INFO command. */
+	u64 flags;
+
+	/* Valid for SLOT_INFO command. */
+	u16 state;
+} __attribute__ ((__packed__));
+
+/* Nitro Enclaves (NE) PCI device. */
+struct ne_pci_dev {
+	/* Variable set if a reply has been sent by the PCI device. */
+	atomic_t cmd_reply_avail;
+
+	/* Wait queue for handling command reply from the PCI device. */
+	wait_queue_head_t cmd_reply_wait_q;
+
+	/* List of the enclaves managed by the PCI device. */
+	struct list_head enclaves_list;
+
+	/* Mutex for accessing the list of enclaves. */
+	struct mutex enclaves_list_mutex;
+
+	/**
+	 * Work queue for handling out-of-band events triggered by the Nitro
+	 * Hypervisor which require enclave state scanning and propagation to
+	 * the enclave process.
+	 */
+	struct workqueue_struct *event_wq;
+
+	/* MMIO region of the PCI device. */
+	void __iomem *iomem_base;
+
+	/* Work item for every received out-of-band event. */
+	struct work_struct notify_work;
+
+	/* Mutex for accessing the PCI dev MMIO space. */
+	struct mutex pci_dev_mutex;
+};
+
+/**
+ * ne_do_request - Submit command request to the PCI device based on the command
+ * type and retrieve the associated reply.
+ *
+ * This function uses the ne_pci_dev mutex to handle one command at a time.
+ *
+ * @pdev: PCI device to send the command to and receive the reply from.
+ * @cmd_type: command type of the request sent to the PCI device.
+ * @cmd_request: command request payload.
+ * @cmd_request_size: size of the command request payload.
+ * @cmd_reply: command reply payload.
+ * @cmd_reply_size: size of the command reply payload.
+ *
+ * @returns: 0 on success, negative return value on failure.
+ */
+int ne_do_request(struct pci_dev *pdev, enum ne_pci_dev_cmd_type cmd_type,
+		  void *cmd_request, size_t cmd_request_size,
+		  struct ne_pci_dev_cmd_reply *cmd_reply,
+		  size_t cmd_reply_size);
+
+/* Nitro Enclaves (NE) PCI device driver */
+extern struct pci_driver ne_pci_driver;
+
+#endif /* _NE_PCI_DEV_H_ */

From patchwork Tue Apr 21 18:41:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11502073
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88F5281
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B50C2072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="FQ1xIRVP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729480AbgDUSme (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 14:42:34 -0400
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:64501 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729457AbgDUSmd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 14:42:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1587494552; x=1619030552;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=JvAkbGXE1TkqLW/VIeJ1UyQVKOVRurbP5B+dKLPBzQM=;
  b=FQ1xIRVPrambeWWZ8V9Px9igxHKBcFcQJxpnIjzDYYy1BG2G9XZGmYD5
   DOPsUDCAjLocLYrzhwdVWk1gz/8ttFOdZkp+d7mgov3id03hszbl9TJ4E
   grSZGe6QCQZAZRncJchBahvjx6Qis5UDPhGqgd6UW+NxjaygfxL5w14sc
   o=;
IronPort-SDR: 
 iTDTXD0VqbwQEv8BZHVf78cDcxHnyu4DA5JEEZvZhTMvucS95gF47zQxlGu8JiElk0mequShib
 N40L7bUh51kQ==
X-IronPort-AV: E=Sophos;i="5.72,411,1580774400";
   d="scan'208";a="30232759"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2a-e7be2041.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 21 Apr 2020 18:42:31 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2a-e7be2041.us-west-2.amazon.com (Postfix) with
 ESMTPS id DC015A22F5;
        Tue, 21 Apr 2020 18:42:29 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:29 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:20 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@amazon.com>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1 03/15] nitro_enclaves: Define enclave info for internal
 bookkeeping
Date: Tue, 21 Apr 2020 21:41:38 +0300
Message-ID: <20200421184150.68011-4-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200421184150.68011-1-andraprs@amazon.com>
References: <20200421184150.68011-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D25UWC004.ant.amazon.com (10.43.162.201) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves driver keeps an internal info per each enclave.

This is needed to be able to manage enclave resources state, enclave
notifications and have a reference of the PCI device that handles
command requests for enclave lifetime management.

Signed-off-by: Alexandru-Catalin Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
 .../virt/amazon/nitro_enclaves/ne_misc_dev.h  | 120 ++++++++++++++++++
 1 file changed, 120 insertions(+)
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_misc_dev.h

diff --git a/drivers/virt/amazon/nitro_enclaves/ne_misc_dev.h b/drivers/virt/amazon/nitro_enclaves/ne_misc_dev.h
new file mode 100644
index 000000000000..dece3ead86b9
--- /dev/null
+++ b/drivers/virt/amazon/nitro_enclaves/ne_misc_dev.h
@@ -0,0 +1,120 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+/*
+ * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
+ *
+ * This program is free software; you can redistribute it and/or modify it
+ * under the terms and conditions of the GNU General Public License,
+ * version 2, as published by the Free Software Foundation.
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
+ * GNU General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, see <http://www.gnu.org/licenses/>.
+ */
+
+#ifndef _NE_MISC_DEV_H_
+#define _NE_MISC_DEV_H_
+
+#include <linux/cpumask.h>
+#include <linux/list.h>
+#include <linux/miscdevice.h>
+#include <linux/mm.h>
+#include <linux/mutex.h>
+#include <linux/pci.h>
+#include <linux/wait.h>
+
+/* Entry in vCPU IDs list. */
+struct ne_vcpu_id {
+	/* CPU id associated with a given slot, apic id on x86. */
+	u32 vcpu_id;
+
+	struct list_head vcpu_id_list_entry;
+};
+
+/* Entry in memory regions list. */
+struct ne_mem_region {
+	struct list_head mem_region_list_entry;
+
+	/* Number of pages that make up the memory region. */
+	unsigned long nr_pages;
+
+	/* Pages that make up the user space memory region. */
+	struct page **pages;
+};
+
+/* Per-enclave data used for enclave lifetime management. */
+struct ne_enclave {
+	/**
+	 * CPU pool with siblings of already allocated CPUs to an enclave.
+	 * This is used when a CPU pool is set, to be able to know the CPU
+	 * siblings for the hyperthreading (HT) setup.
+	 */
+	cpumask_var_t cpu_siblings;
+
+	struct list_head enclave_list_entry;
+
+	/* Mutex for accessing this internal state. */
+	struct mutex enclave_info_mutex;
+
+	/**
+	 * Wait queue used for out-of-band event notifications
+	 * triggered from the PCI device event handler to the enclave
+	 * process via the poll function.
+	 */
+	wait_queue_head_t eventq;
+
+	/* Variable used to determine if the out-of-band event was triggered. */
+	bool has_event;
+
+	/**
+	 * The maximum number of memory regions that can be handled by the
+	 * lower levels.
+	 */
+	u64 max_mem_regions;
+
+	/* Enclave memory regions list. */
+	struct list_head mem_regions_list;
+
+	/* Enclave process abstraction mm data struct. */
+	struct mm_struct *mm;
+
+	/* PCI device used for enclave lifetime management. */
+	struct pci_dev *pdev;
+
+	/* Slot unique id mapped to the enclave. */
+	u64 slot_uid;
+
+	/* Enclave state, updated during enclave lifetime. */
+	u16 state;
+
+	/* Enclave vCPUs list. */
+	struct list_head vcpu_ids_list;
+};
+
+/**
+ * States available for an enclave.
+ *
+ * TODO: Determine if the following states are exposing enough information
+ * to the kernel driver.
+ */
+enum ne_state {
+	/* NE_ENCLAVE_START ioctl was never issued for the enclave. */
+	NE_STATE_INIT = 0,
+
+	/**
+	 * NE_ENCLAVE_START ioctl was issued and the enclave is running
+	 * as expected.
+	 */
+	NE_STATE_RUNNING = 2,
+
+	/* Enclave exited without userspace interaction. */
+	NE_STATE_STOPPED = U16_MAX,
+};
+
+/* Nitro Enclaves (NE) misc device */
+extern struct miscdevice ne_miscdevice;
+
+#endif /* _NE_MISC_DEV_H_ */

From patchwork Tue Apr 21 18:41:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11502075
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C35E92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 680BE20724
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="kLd2F00O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729497AbgDUSmm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 14:42:42 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:53454 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729452AbgDUSmk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 14:42:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1587494559; x=1619030559;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=aMA7GuRQk9xRyNRDUSC1CF1PbdsE/6li9LlY6g7pMyo=;
  b=kLd2F00OkmG3kfJyj6m1+3dYrRJ1i7dbhver5u3+1hlPrBajKHq0+kfG
   pfyX4wN+yUdk1zksPU0+9c0/PioB8lKuetMwxVv4bMc3zirPEz3ufBrEl
   uveJuFYLTQ1vCe2xCMTvuCPqLk5X1m7kmLRbW62IOpbvE2qU1yoQOTAI1
   Q=;
IronPort-SDR: 
 QqqpYh2L/trLOag45i9lRLGDT6tMUArdG6WL8Lsrs/LDr5xJ0RWar4I6doUWfh3xjW+GiSwVd2
 phx0d9bE3bHw==
X-IronPort-AV: E=Sophos;i="5.72,411,1580774400";
   d="scan'208";a="38565694"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2c-1968f9fa.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 21 Apr 2020 18:42:39 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan3.pdx.amazon.com [10.170.41.166])
        by email-inbound-relay-2c-1968f9fa.us-west-2.amazon.com (Postfix) with
 ESMTPS id 0E67CA070F;
        Tue, 21 Apr 2020 18:42:37 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:37 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:28 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@amazon.com>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1 04/15] nitro_enclaves: Init PCI device driver
Date: Tue, 21 Apr 2020 21:41:39 +0300
Message-ID: <20200421184150.68011-5-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200421184150.68011-1-andraprs@amazon.com>
References: <20200421184150.68011-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D25UWC004.ant.amazon.com (10.43.162.201) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves PCI device is used by the kernel driver as a means of
communication with the hypervisor on the host where the primary VM and
the enclaves run. It handles requests with regard to enclave lifetime.

Setup the PCI device driver and add support for MSI-X interrupts.

Signed-off-by: Alexandru-Catalin Vasile <lexnv@amazon.com>
Signed-off-by: Alexandru Ciobotaru <alcioa@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
 .../virt/amazon/nitro_enclaves/ne_pci_dev.c   | 278 ++++++++++++++++++
 1 file changed, 278 insertions(+)
 create mode 100644 drivers/virt/amazon/nitro_enclaves/ne_pci_dev.c

diff --git a/drivers/virt/amazon/nitro_enclaves/ne_pci_dev.c b/drivers/virt/amazon/nitro_enclaves/ne_pci_dev.c
new file mode 100644
index 000000000000..8fbee95ea291
--- /dev/null
+++ b/drivers/virt/amazon/nitro_enclaves/ne_pci_dev.c
@@ -0,0 +1,278 @@
+// SPDX-License-Identifier: GPL-2.0
+/*
+ * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
+ *
+ * This program is free software; you can redistribute it and/or modify it
+ * under the terms and conditions of the GNU General Public License,
+ * version 2, as published by the Free Software Foundation.
+ *
+ * This program is distributed in the hope that it will be useful,
+ * but WITHOUT ANY WARRANTY; without even the implied warranty of
+ * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
+ * GNU General Public License for more details.
+ *
+ * You should have received a copy of the GNU General Public License
+ * along with this program; if not, see <http://www.gnu.org/licenses/>.
+ */
+
+/* Nitro Enclaves (NE) PCI device driver. */
+
+#include <linux/bug.h>
+#include <linux/delay.h>
+#include <linux/device.h>
+#include <linux/list.h>
+#include <linux/mutex.h>
+#include <linux/module.h>
+#include <linux/nitro_enclaves.h>
+#include <linux/pci.h>
+#include <linux/types.h>
+#include <linux/wait.h>
+
+#include "ne_misc_dev.h"
+#include "ne_pci_dev.h"
+
+#define DEFAULT_TIMEOUT_MSECS (120000) // 120 sec
+
+static const struct pci_device_id ne_pci_ids[] = {
+	{ PCI_DEVICE(PCI_VENDOR_ID_AMAZON, PCI_DEVICE_ID_NE) },
+	{ 0, }
+};
+
+MODULE_DEVICE_TABLE(pci, ne_pci_ids);
+
+/**
+ * ne_setup_msix - Setup MSI-X vectors for the PCI device.
+ *
+ * @pdev: PCI device to setup the MSI-X for.
+ * @ne_pci_dev: PCI device private data structure.
+ *
+ * @returns: 0 on success, negative return value on failure.
+ */
+static int ne_setup_msix(struct pci_dev *pdev, struct ne_pci_dev *ne_pci_dev)
+{
+	int nr_vecs = 0;
+	int rc = -EINVAL;
+
+	BUG_ON(!ne_pci_dev);
+
+	nr_vecs = pci_msix_vec_count(pdev);
+	if (nr_vecs < 0) {
+		rc = nr_vecs;
+
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in getting vec count [rc=%d]\n",
+				    rc);
+
+		return rc;
+	}
+
+	rc = pci_alloc_irq_vectors(pdev, nr_vecs, nr_vecs, PCI_IRQ_MSIX);
+	if (rc < 0) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in alloc MSI-X vecs [rc=%d]\n",
+				    rc);
+
+		goto err_alloc_irq_vecs;
+	}
+
+	return 0;
+
+err_alloc_irq_vecs:
+	return rc;
+}
+
+/**
+ * ne_pci_dev_enable - Select PCI device version and enable it.
+ *
+ * @pdev: PCI device to select version for and then enable.
+ * @ne_pci_dev: PCI device private data structure.
+ *
+ * @returns: 0 on success, negative return value on failure.
+ */
+static int ne_pci_dev_enable(struct pci_dev *pdev,
+			     struct ne_pci_dev *ne_pci_dev)
+{
+	u8 dev_enable_reply = 0;
+	u16 dev_version_reply = 0;
+
+	BUG_ON(!pdev);
+	BUG_ON(!ne_pci_dev);
+	BUG_ON(!ne_pci_dev->iomem_base);
+
+	iowrite16(NE_VERSION_MAX, ne_pci_dev->iomem_base + NE_VERSION);
+
+	dev_version_reply = ioread16(ne_pci_dev->iomem_base + NE_VERSION);
+	if (dev_version_reply != NE_VERSION_MAX) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci dev version cmd\n");
+
+		return -EIO;
+	}
+
+	iowrite8(NE_ENABLE_ON, ne_pci_dev->iomem_base + NE_ENABLE);
+
+	dev_enable_reply = ioread8(ne_pci_dev->iomem_base + NE_ENABLE);
+	if (dev_enable_reply != NE_ENABLE_ON) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci dev enable cmd\n");
+
+		return -EIO;
+	}
+
+	return 0;
+}
+
+/**
+ * ne_pci_dev_disable - Disable PCI device.
+ *
+ * @pdev: PCI device to disable.
+ * @ne_pci_dev: PCI device private data structure.
+ *
+ * @returns: 0 on success, negative return value on failure.
+ */
+static int ne_pci_dev_disable(struct pci_dev *pdev,
+			      struct ne_pci_dev *ne_pci_dev)
+{
+	u8 dev_disable_reply = 0;
+
+	BUG_ON(!pdev);
+	BUG_ON(!ne_pci_dev);
+	BUG_ON(!ne_pci_dev->iomem_base);
+
+	iowrite8(NE_ENABLE_OFF, ne_pci_dev->iomem_base + NE_ENABLE);
+
+	/*
+	 * TODO: Check for NE_ENABLE_OFF in a loop, to handle cases when the
+	 * device state is not immediately set to disabled and going through a
+	 * transitory state of disabling.
+	 */
+	dev_disable_reply = ioread8(ne_pci_dev->iomem_base + NE_ENABLE);
+	if (dev_disable_reply != NE_ENABLE_OFF) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci dev disable cmd\n");
+
+		return -EIO;
+	}
+
+	return 0;
+}
+
+static int ne_probe(struct pci_dev *pdev, const struct pci_device_id *id)
+{
+	struct ne_pci_dev *ne_pci_dev = NULL;
+	int rc = -EINVAL;
+
+	ne_pci_dev = kzalloc(sizeof(*ne_pci_dev), GFP_KERNEL);
+	if (!ne_pci_dev)
+		return -ENOMEM;
+
+	rc = pci_enable_device(pdev);
+	if (rc < 0) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci dev enable [rc=%d]\n", rc);
+
+		goto err_pci_enable_dev;
+	}
+
+	rc = pci_request_regions_exclusive(pdev, "ne_pci_dev");
+	if (rc < 0) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci request regions [rc=%d]\n",
+				    rc);
+
+		goto err_req_regions;
+	}
+
+	ne_pci_dev->iomem_base = pci_iomap(pdev, PCI_BAR_NE, 0);
+	if (!ne_pci_dev->iomem_base) {
+		rc = -ENOMEM;
+
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci bar mapping [rc=%d]\n", rc);
+
+		goto err_iomap;
+	}
+
+	rc = ne_setup_msix(pdev, ne_pci_dev);
+	if (rc < 0) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in pci dev msix setup [rc=%d]\n",
+				    rc);
+
+		goto err_setup_msix;
+	}
+
+	rc = ne_pci_dev_disable(pdev, ne_pci_dev);
+	if (rc < 0) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in ne_pci_dev disable [rc=%d]\n",
+				    rc);
+
+		goto err_ne_pci_dev_disable;
+	}
+
+	rc = ne_pci_dev_enable(pdev, ne_pci_dev);
+	if (rc < 0) {
+		dev_err_ratelimited(&pdev->dev,
+				    "Failure in ne_pci_dev enable [rc=%d]\n",
+				    rc);
+
+		goto err_ne_pci_dev_enable;
+	}
+
+	atomic_set(&ne_pci_dev->cmd_reply_avail, 0);
+	init_waitqueue_head(&ne_pci_dev->cmd_reply_wait_q);
+	INIT_LIST_HEAD(&ne_pci_dev->enclaves_list);
+	mutex_init(&ne_pci_dev->enclaves_list_mutex);
+	mutex_init(&ne_pci_dev->pci_dev_mutex);
+
+	pci_set_drvdata(pdev, ne_pci_dev);
+
+	return 0;
+
+err_ne_pci_dev_enable:
+err_ne_pci_dev_disable:
+	pci_free_irq_vectors(pdev);
+err_setup_msix:
+	pci_iounmap(pdev, ne_pci_dev->iomem_base);
+err_iomap:
+	pci_release_regions(pdev);
+err_req_regions:
+	pci_disable_device(pdev);
+err_pci_enable_dev:
+	kzfree(ne_pci_dev);
+	return rc;
+}
+
+static void ne_remove(struct pci_dev *pdev)
+{
+	struct ne_pci_dev *ne_pci_dev = pci_get_drvdata(pdev);
+
+	if (!ne_pci_dev || !ne_pci_dev->iomem_base)
+		return;
+
+	ne_pci_dev_disable(pdev, ne_pci_dev);
+
+	pci_set_drvdata(pdev, NULL);
+
+	pci_free_irq_vectors(pdev);
+
+	pci_iounmap(pdev, ne_pci_dev->iomem_base);
+
+	kzfree(ne_pci_dev);
+
+	pci_release_regions(pdev);
+
+	pci_disable_device(pdev);
+}
+
+/*
+ * TODO: Add suspend / resume functions for power management w/ CONFIG_PM, if
+ * needed.
+ */
+struct pci_driver ne_pci_driver = {
+	.name		= "ne_pci_dev",
+	.id_table	= ne_pci_ids,
+	.probe		= ne_probe,
+	.remove		= ne_remove,
+};

From patchwork Tue Apr 21 18:41:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11502077
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95D0081
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 794C9206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 18:42:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="LFal6lDD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729527AbgDUSmz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 14:42:55 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:62315 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729501AbgDUSmy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 14:42:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1587494573; x=1619030573;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=hCVuFtt9M+P1AunrCOwfanKEEX8ct24ptrnRC6w3jCI=;
  b=LFal6lDDDpQAQe4W5FE/CYdts/ePXeYeQIFCQRrqEyP9npZjdAV/Eqhn
   RNkq4Y83Hv2FLjoqPJB6kZVobmkXBz5U9Kg8+E+rPdWmf9TBHdXbfRwQB
   mt5EIsF+RNHkYQZVyY9C4bvb09D5mmvQmiKDiXM3QmSAm+Suc3K9jcLp9
   k=;
IronPort-SDR: 
 1eC9AHuypUgqQi5opmT0fPhKBsynrA/xsnzQcjJ3chmR2ilYNEKVDxbhhhg6KHfRej3AuCpfui
 3PJktKAyrvAw==
X-IronPort-AV: E=Sophos;i="5.72,411,1580774400";
   d="scan'208";a="39978453"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2b-c7131dcf.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 21 Apr 2020 18:42:53 +0000
Received: from EX13MTAUEA002.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2b-c7131dcf.us-west-2.amazon.com (Postfix) with
 ESMTPS id D58C6A1DC5;
        Tue, 21 Apr 2020 18:42:51 +0000 (UTC)
Received: from EX13D16EUB003.ant.amazon.com (10.43.166.99) by
 EX13MTAUEA002.ant.amazon.com (10.43.61.77) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:51 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.90) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 21 Apr 2020 18:42:42 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@amazon.com>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        David Woodhouse <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stewart Smith <trawets@amazon.com>,
        Uwe Dannowski <uwed@amazon.de>, <kvm@vger.kernel.org>,
        <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1 05/15] nitro_enclaves: Handle PCI device command requests
Date: Tue, 21 Apr 2020 21:41:40 +0300
Message-ID: <20200421184150.68011-6-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
In-Reply-To: <20200421184150.68011-1-andraprs@amazon.com>
References: <20200421184150.68011-1-andraprs@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.160.90]
X-ClientProxiedBy: EX13D37UWC004.ant.amazon.com (10.43.162.212) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Nitro Enclaves PCI device exposes a MMIO space that this driver
uses to submit command requests and to receive command replies e.g. for
enclave creation / termination or setting enclave resources.

Add logic for handling PCI device command requests based on the given
command type.

Register an MSI-X interrupt vector for command reply notifications to
handle this type of communication events.

Signed-off-by: Alexandru-Catalin Vasile <lexnv@amazon.com>
Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
---
 .../virt/amazon/nitro_enclaves/ne_pci_dev.c   | 264 ++++++++++++++++++
 1 file changed, 264 insertions(+)

```
#### [RFC PATCH v11 1/9] psci: export psci conduit get helper.
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11500359
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 82A5D159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 03:24:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 712B5214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 03:24:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728037AbgDUDXc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Apr 2020 23:23:32 -0400
Received: from foss.arm.com ([217.140.110.172]:57324 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725989AbgDUDXb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Apr 2020 23:23:31 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 03367C14;
        Mon, 20 Apr 2020 20:23:31 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 D44B43F6CF;
        Mon, 20 Apr 2020 20:23:23 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v11 1/9] psci: export psci conduit get helper.
Date: Tue, 21 Apr 2020 11:22:56 +0800
Message-Id: <20200421032304.26300-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200421032304.26300-1-jianyong.wu@arm.com>
References: <20200421032304.26300-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export arm_smccc_1_1_get_conduit then modules can use smccc helper which
adopts it.

Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
Acked-by: Mark Rutland <mark.rutland@arm.com>
---
 drivers/firmware/psci/psci.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [GIT PULL 1/2] KVM: s390: Fix PV check in deliverable_irqs()
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11500497
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A35BC6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 06:34:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 947E7218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 06:34:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726024AbgDUGe4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 02:34:56 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:12712 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725902AbgDUGe4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Apr 2020 02:34:56 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03L6Xbbg088887
        for <kvm@vger.kernel.org>; Tue, 21 Apr 2020 02:34:55 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30gmuy8pkv-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 21 Apr 2020 02:34:55 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Tue, 21 Apr 2020 07:34:19 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 21 Apr 2020 07:34:16 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03L6XgSS66519400
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 21 Apr 2020 06:33:42 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 67A19AE045;
        Tue, 21 Apr 2020 06:34:49 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4FFDDAE051;
        Tue, 21 Apr 2020 06:34:49 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 21 Apr 2020 06:34:49 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 1036EE05A7; Tue, 21 Apr 2020 08:34:49 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [GIT PULL 1/2] KVM: s390: Fix PV check in deliverable_irqs()
Date: Tue, 21 Apr 2020 08:34:46 +0200
X-Mailer: git-send-email 2.25.2
In-Reply-To: <20200421063447.6814-1-borntraeger@de.ibm.com>
References: <20200421063447.6814-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20042106-0008-0000-0000-000003748EA0
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20042106-0009-0000-0000-00004A96530A
Message-Id: <20200421063447.6814-2-borntraeger@de.ibm.com>
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-21_02:2020-04-20,2020-04-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 clxscore=1015
 priorityscore=1501 impostorscore=0 adultscore=0 malwarescore=0
 suspectscore=0 phishscore=0 spamscore=0 bulkscore=0 mlxlogscore=999
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004210055
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Farman <farman@linux.ibm.com>

The diag 0x44 handler, which handles a directed yield, goes into a
a codepath that does a kvm_for_each_vcpu() and ultimately
deliverable_irqs().  The new check for kvm_s390_pv_cpu_is_protected()
contains an assertion that the vcpu->mutex is held, which isn't going
to be the case in this scenario.

The result is a plethora of these messages if the lock debugging
is enabled, and thus an implication that we have a problem.

  WARNING: CPU: 9 PID: 16167 at arch/s390/kvm/kvm-s390.h:239 deliverable_irqs+0x1c6/0x1d0 [kvm]
  ...snip...
  Call Trace:
   [<000003ff80429bf2>] deliverable_irqs+0x1ca/0x1d0 [kvm]
  ([<000003ff80429b34>] deliverable_irqs+0x10c/0x1d0 [kvm])
   [<000003ff8042ba82>] kvm_s390_vcpu_has_irq+0x2a/0xa8 [kvm]
   [<000003ff804101e2>] kvm_arch_dy_runnable+0x22/0x38 [kvm]
   [<000003ff80410284>] kvm_vcpu_on_spin+0x8c/0x1d0 [kvm]
   [<000003ff80436888>] kvm_s390_handle_diag+0x3b0/0x768 [kvm]
   [<000003ff80425af4>] kvm_handle_sie_intercept+0x1cc/0xcd0 [kvm]
   [<000003ff80422bb0>] __vcpu_run+0x7b8/0xfd0 [kvm]
   [<000003ff80423de6>] kvm_arch_vcpu_ioctl_run+0xee/0x3e0 [kvm]
   [<000003ff8040ccd8>] kvm_vcpu_ioctl+0x2c8/0x8d0 [kvm]
   [<00000001504ced06>] ksys_ioctl+0xae/0xe8
   [<00000001504cedaa>] __s390x_sys_ioctl+0x2a/0x38
   [<0000000150cb9034>] system_call+0xd8/0x2d8
  2 locks held by CPU 2/KVM/16167:
   #0: 00000001951980c0 (&vcpu->mutex){+.+.}, at: kvm_vcpu_ioctl+0x90/0x8d0 [kvm]
   #1: 000000019599c0f0 (&kvm->srcu){....}, at: __vcpu_run+0x4bc/0xfd0 [kvm]
  Last Breaking-Event-Address:
   [<000003ff80429b34>] deliverable_irqs+0x10c/0x1d0 [kvm]
  irq event stamp: 11967
  hardirqs last  enabled at (11975): [<00000001502992f2>] console_unlock+0x4ca/0x650
  hardirqs last disabled at (11982): [<0000000150298ee8>] console_unlock+0xc0/0x650
  softirqs last  enabled at (7940): [<0000000150cba6ca>] __do_softirq+0x422/0x4d8
  softirqs last disabled at (7929): [<00000001501cd688>] do_softirq_own_stack+0x70/0x80

Considering what's being done here, let's fix this by removing the
mutex assertion rather than acquiring the mutex for every other vcpu.

Fixes: 201ae986ead7 ("KVM: s390: protvirt: Implement interrupt injection")
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Link: https://lore.kernel.org/r/20200415190353.63625-1-farman@linux.ibm.com
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/interrupt.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] KVM changes for Linux 5.7-rc3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11501785
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C7FB3112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 16:07:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5C7B2068F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 16:07:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DPEtup4T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726335AbgDUQHE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 12:07:04 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:58785 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725987AbgDUQHE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Apr 2020 12:07:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587485222;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=o5FOkANuc3nLYhQjPcsDscbLbZtxZk5DwaFRxRr4r+g=;
        b=DPEtup4T0UHRXsXgnRYBp9lqPZgySbAOIL+nSoo5gDGTcnYrfyufwnuWum42lh/53NlvS+
        PeW+yXFLLkBHwqRi5itxMSOxxX5GbDeXVW/wHN7YcGHR7plvO57Y07UmALnUEtSJT7Tdpr
        LqJUOL5k1WLtk8LLTSlNOkwaHXKtZAs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-501-qIM84Du8Oc-OIl56oNYQQQ-1; Tue, 21 Apr 2020 12:06:53 -0400
X-MC-Unique: qIM84Du8Oc-OIl56oNYQQQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E32361922021;
        Tue, 21 Apr 2020 16:06:52 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 71B9676E74;
        Tue, 21 Apr 2020 16:06:52 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.7-rc3
Date: Tue, 21 Apr 2020 12:06:51 -0400
Message-Id: <20200421160651.19274-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit ae83d0b416db002fe95601e7f97f64b59514d936:

  Linux 5.7-rc2 (2020-04-19 14:35:30 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 00a6a5ef39e7db3648b35c86361058854db84c83:

  Merge tag 'kvm-ppc-fixes-5.7-1' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into kvm-master (2020-04-21 09:39:55 -0400)

----------------------------------------------------------------
Bugfixes, and a few cleanups to the newly-introduced assembly language
vmentry code for AMD.

----------------------------------------------------------------
Borislav Petkov (1):
      KVM: SVM: Fix build error due to missing release_pages() include

Claudio Imbrenda (1):
      MAINTAINERS: add a reviewer for KVM/s390

Eric Farman (1):
      KVM: s390: Fix PV check in deliverable_irqs()

Josh Poimboeuf (1):
      kvm: Disable objtool frame pointer checking for vmenter.S

Oliver Upton (2):
      kvm: nVMX: reflect MTF VM-exits if injected by L1
      kvm: nVMX: match comment with return type for nested_vmx_exit_reflected

Paolo Bonzini (4):
      KVM: SVM: fix compilation with modular PSP and non-modular KVM
      KVM: SVM: move more vmentry code to assembly
      Merge tag 'kvm-s390-master-5.7-2' of git://git.kernel.org/.../kvms390/linux into kvm-master
      Merge tag 'kvm-ppc-fixes-5.7-1' of git://git.kernel.org/.../paulus/powerpc into kvm-master

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Handle non-present PTEs in page fault functions

Sean Christopherson (2):
      KVM: Check validity of resolved slot when searching memslots
      KVM: s390: Return last valid slot if approx index is out-of-bounds

Steve Rutherford (1):
      KVM: Remove CREATE_IRQCHIP/SET_PIT2 race

Uros Bizjak (4):
      KVM: VMX: Enable machine check support for 32bit targets
      KVM: SVM: Do not mark svm_vcpu_run with STACK_FRAME_NON_STANDARD
      KVM: SVM: Do not setup frame pointer in __svm_vcpu_run
      KVM: SVM: Fix __svm_vcpu_run declaration.

Venkatesh Srinivas (1):
      kvm: Handle reads of SandyBridge RAPL PMU MSRs rather than injecting #GP

 MAINTAINERS                            |  1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  9 +++++----
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  9 +++++----
 arch/s390/kvm/interrupt.c              |  2 +-
 arch/s390/kvm/kvm-s390.c               |  3 +++
 arch/x86/include/asm/nospec-branch.h   | 21 ---------------------
 arch/x86/kvm/Makefile                  |  4 ++++
 arch/x86/kvm/svm/sev.c                 |  6 +++++-
 arch/x86/kvm/svm/svm.c                 | 10 +---------
 arch/x86/kvm/svm/vmenter.S             | 10 +++++++++-
 arch/x86/kvm/vmx/nested.c              | 21 +++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.c                 |  2 +-
 arch/x86/kvm/x86.c                     | 21 +++++++++++++++++++--
 include/linux/kvm_host.h               |  2 +-
 14 files changed, 74 insertions(+), 47 deletions(-)
```
#### [PATCH 1/2] KVM: X86: TSCDEADLINE MSR emulation fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11501111
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B40E192C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 11:20:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90E882076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 11:20:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="dbvR1S1t"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728663AbgDULUm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 07:20:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47590 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728625AbgDULUj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 07:20:39 -0400
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CBB06C061A0F;
        Tue, 21 Apr 2020 04:20:39 -0700 (PDT)
Received: by mail-pf1-x443.google.com with SMTP id r14so6475813pfg.2;
        Tue, 21 Apr 2020 04:20:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=QbG6biHp7POKFANtSjyG5DgTEjhmjx/tR45VHaH/c6o=;
        b=dbvR1S1tnGDSR0EE8JeQjF1WfQcA3v9bN4+8IUeK0EFp1ih+yixTZu+w60i6g1AOcv
         XaM7n9loE28Tx9k6nfwirXh+HutG+Qr/VzyZcIvkg1sqg7+7iND1XKQOr7qVBEf4E9v+
         0mWm3movjv1Mvrgsxn+U1bnV9Cq6NVHxsFAQA8epmOlr32cut9wRQggoWYYM9pBsOlPV
         ckZ6XjC89O1lZ0du/uOHR2VhQm8zpheuAebT6OrDpRYflQDxDdXtlR4OmImHyG/XFsXf
         nvFNV5l9tv6jk41tdjGYGp/N4r7Y+SLzcgD+Nni/Ex2VC8mB6LG0uNgOb9ZsyJVFCnqk
         6HVA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=QbG6biHp7POKFANtSjyG5DgTEjhmjx/tR45VHaH/c6o=;
        b=BDNrvZEiWk2WNFPrycawlylrdyyWpCHyIddDMg5C9T0flref92yuqg9vfHPZOKpFb9
         0fFyF/JoiwguCN7+0ltDLfjn1LquQjwt52KBFIFNAEh7WJ94b3C2EXQUWXS76rAXEw8G
         Yj4W4BIjxO13KLQNbKnQjAI99C9HfYK2s62UP2ON0svssnbEj1DEkqJb7BW2WzKbxeDR
         HuuE6Pf4vnH7xy5huNwTEFI/bvMgWd/aZ3TwzHScEzUYjiYpte5jdWX5VL/VjwC4VdyK
         TWwja9RVLzdqHDs2V3JqfgyI8GzvTRw8daluiiax2Awa0hZR61aHAl1aoMyW+H2gleAi
         fKOw==
X-Gm-Message-State: AGi0PuYfXEDhxs+dNlBztgDGdgWm5l2B3x/gyiwWx2uSaUgGtiuPxwv/
        RxltP9+cWu13kh0GFlaztse91SgT
X-Google-Smtp-Source: 
 APiQypJmxhDbseGNrk49snh8EeA5KO89I4RjsXTpuzNfM1jl4yk99QASc7AI5sQmwCtXfMyRS21uHg==
X-Received: by 2002:a62:8746:: with SMTP id i67mr7003745pfe.9.1587468039044;
        Tue, 21 Apr 2020 04:20:39 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 f74sm8643176pje.3.2020.04.21.04.20.36
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Apr 2020 04:20:38 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH 1/2] KVM: X86: TSCDEADLINE MSR emulation fastpath
Date: Tue, 21 Apr 2020 19:20:25 +0800
Message-Id: <1587468026-15753-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1587468026-15753-1-git-send-email-wanpengli@tencent.com>
References: <1587468026-15753-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch implements tscdealine msr emulation fastpath, after wrmsr 
tscdeadline vmexit, handle it as soon as possible and vmentry immediately 
without checking various kvm stuff when possible.

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  3 +++
 arch/x86/kvm/lapic.c            | 20 +++-----------
 arch/x86/kvm/lapic.h            | 16 +++++++++++
 arch/x86/kvm/vmx/vmx.c          | 60 +++++++++++++++++++++++++++++++++++++----
 arch/x86/kvm/x86.c              | 55 ++++++++++++++++++++++++++++++++-----
 5 files changed, 126 insertions(+), 28 deletions(-)

```
#### [PATCH v3 1/2] KVM: nVMX: Drop a redundant call to vmx_get_intr_info()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11500657
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD717159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 07:53:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6B122084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 07:53:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727900AbgDUHxg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 03:53:36 -0400
Received: from mga06.intel.com ([134.134.136.31]:22871 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726018AbgDUHxb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 03:53:31 -0400
IronPort-SDR: 
 5NjhHUOTgKNrBIiT1EBnXQuYriaeSBQsfCYcePhDexH5EYbLgOso9wnyBv73E+EH4jT+2K2F3B
 ITjSV+xszyHw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Apr 2020 00:53:29 -0700
IronPort-SDR: 
 wG2o5a7z29Kq5M7cL4rwWui9yGD7c9HunpERaZVFwWrC9ACMkKpq4/VjibYGS2uAGL2Nz+fZFw
 GMUcMQ+TfcmA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,409,1580803200";
   d="scan'208";a="245611201"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga007.fm.intel.com with ESMTP; 21 Apr 2020 00:53:29 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v3 1/2] KVM: nVMX: Drop a redundant call to
 vmx_get_intr_info()
Date: Tue, 21 Apr 2020 00:53:27 -0700
Message-Id: <20200421075328.14458-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200421075328.14458-1-sean.j.christopherson@intel.com>
References: <20200421075328.14458-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop nested_vmx_l1_wants_exit()'s initialization of intr_info from
vmx_get_intr_info() that was inadvertantly introduced along with the
caching mechanism.  EXIT_REASON_EXCEPTION_NMI, the only consumer of
intr_info, populates the variable before using it.

Fixes: bb53120d67cdb ("KVM: VMX: Cache vmcs.EXIT_INTR_INFO using arch avail_reg flags")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/3] KVM: x86: check_nested_events is never NULL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11501999
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E2A86CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 16:57:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E17012071E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 16:57:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Kx7ktMZx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729620AbgDUQ45 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 12:56:57 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:43736 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729569AbgDUQ4l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 12:56:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587488200;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=QD8e0AJlb2zruiuH7vRdPAFxhSSX7kKN2RbOOPFIN+s=;
        b=Kx7ktMZx/mz/PxL4GIDRVIcK8/LH0R5225x4jUnF3+EEliiQozSiNWR9qubUSuzMA0NJl+
        Q60PKfCYVCJXJ0G03FQY/gx+u61hNcNrwzz3ZO8zJa98MQZsO4lVWnlyVZRRGNdt1hxwCq
        nt9ZUXc3ArPlwAxq6TqNmUu8HewV5aQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-245-nrWzbARkPjO5Xflv3dKk5Q-1; Tue, 21 Apr 2020 12:56:38 -0400
X-MC-Unique: nrWzbARkPjO5Xflv3dKk5Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6B95585EE6A;
        Tue, 21 Apr 2020 16:56:37 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C0D6648;
        Tue, 21 Apr 2020 16:56:36 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v2 1/3] KVM: x86: check_nested_events is never NULL
Date: Tue, 21 Apr 2020 12:56:30 -0400
Message-Id: <20200421165632.20157-2-pbonzini@redhat.com>
In-Reply-To: <20200421165632.20157-1-pbonzini@redhat.com>
References: <20200421165632.20157-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both Intel and AMD now implement it, so (as long as the check is under
is_guest_mode) there is no need to check if the callback is implemented.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH net] vsock/virtio: postpone packet delivery to monitoring devices
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11500919
Return-Path: <SRS0=bYh3=6F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B0A481
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 09:25:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 535712087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Apr 2020 09:25:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (1024-bit key)
 header.d=redhat.com header.i=@redhat.com header.b="PU/ARCnz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728453AbgDUJZj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 05:25:39 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41652 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727120AbgDUJZj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 05:25:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587461137;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=s6kZIJazKnfeWw9rqRwxCTiV7lo+E1jRmgFL7mG8v1w=;
        b=PU/ARCnzbHoIRw+5duN7yCVlaG+rYGBTgq6xo5xCGcjPJGdPAfoI5Y/KFqgvNJuEh2cLdE
        QEM63eIFH43krdmX1Pahv763B0cevLwlT1LGgCGnqZbdkvA4D/taptJdFz/qSszOibq9ep
        xbqwtS7ZLK2sQVfapxH9e5eTDlDlcC4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-pZMfjWLMOayjYnBl4uIC7Q-1; Tue, 21 Apr 2020 05:25:36 -0400
X-MC-Unique: pZMfjWLMOayjYnBl4uIC7Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CFCE48017F3;
        Tue, 21 Apr 2020 09:25:34 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-101.ams2.redhat.com
 [10.36.114.101])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A499A60C87;
        Tue, 21 Apr 2020 09:25:28 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: virtualization@lists.linux-foundation.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Jakub Kicinski <kuba@kernel.org>,
        Gerard Garcia <ggarcia@abra.uab.cat>
Subject: [PATCH net] vsock/virtio: postpone packet delivery to monitoring
 devices
Date: Tue, 21 Apr 2020 11:25:27 +0200
Message-Id: <20200421092527.41651-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We delivering packets to monitoring devices, before to check if
the virtqueue has enough space.

If the virtqueue is full, the transmitting packet is queued up
and it will be sent in the next iteration. This causes the same
packet to be delivered multiple times to monitoring devices.

This patch fixes this issue, postponing the packet delivery
to monitoring devices, only when it is properly queued in the
virqueue.

Fixes: 82dfb540aeb2 ("VSOCK: Add virtio vsock vsockmon hooks")
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
