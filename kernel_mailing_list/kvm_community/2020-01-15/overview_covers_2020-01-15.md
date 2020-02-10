

#### [PATCH 0/2 v2] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Jan 15 01:25:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11333115
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2141B109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 02:03:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F3679222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 02:03:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="VY+bzNe6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728882AbgAOCC7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jan 2020 21:02:59 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:40982 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728834AbgAOCC7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jan 2020 21:02:59 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00F22tjS111514;
        Wed, 15 Jan 2020 02:02:56 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=66y6/bzb6knDvZeFzJdqOTqNPnDuDsF1gXa4bDc+gQ0=;
 b=VY+bzNe6uK32JOPapTU4Tp6uZlrWdTnOSBov/K72cAEJMhvoi5ECdZhs/zZqD1pNxVax
 F5xJmN5AEadj9C+BqSdjCLhozQdxQLp+GvQZxR4vLNtC8HKIdFhC8zQ3DbdIhssGh3P3
 CW8m0OrQ4dCS4jKmAUhci4Tfo+BFOy2pIfpjNajCH47hCOodW7hLLdAZDuP/CAX3qEn8
 gfG/FqtqQ4mE//YPHvx7nEsozSRSt3SNQJcwrVhES+SJO8CPdOlZotBxl9jt9Kr2X7jN
 unHkFxntuhjkVi6TQCbNQmTeRpbK1bv3pYRjJBcKw9YXbslIx0ZfNRaz+A1gtW2zLm2b EA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 2xf73tshx1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Jan 2020 02:02:56 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00F1wxZI057781;
        Wed, 15 Jan 2020 02:02:55 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 2xh31524j7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Jan 2020 02:02:55 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 00F22tfJ031581;
        Wed, 15 Jan 2020 02:02:55 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 14 Jan 2020 18:02:55 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 0/2 v2] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
Date: Tue, 14 Jan 2020 20:25:39 -0500
Message-Id: <20200115012541.8904-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9500
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=532
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-2001150016
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9500
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1011
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=597 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-2001150017
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I sent out v1 a few months back. Here are the changes:

v1 -> v2:
	1. Patch# 1 has been dropped as we do not want to check GUEST_DEBUGCTL
	   software.
	2. Patch# 3 has been dropped.
	3. Patch# 4 has been modified to include only the tests for GUEST_DR7
	   and to be run directly on hardware as well.


[PATCH 1/2 v2] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
[PATCH 2/2 v2] kvm-unit-test: nVMX: Test GUEST_DR7 on vmentry of nested guests

 arch/x86/kvm/vmx/nested.c | 6 ++++++
 arch/x86/kvm/x86.c        | 2 +-
 arch/x86/kvm/x86.h        | 6 ++++++
 3 files changed, 13 insertions(+), 1 deletion(-)

Krish Sadhukhan (1):
      nVMX: Check GUEST_DR7 on vmentry of nested guests

 x86/vmx_tests.c | 44 ++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 44 insertions(+)

Krish Sadhukhan (1):
      nVMX: Test GUEST_DR7 on vmentry of nested guests
```
#### [PATCH v2 0/2] use vfio_dma_rw to read/write IOVAs from CPU side
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Wed Jan 15 03:41:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11333281
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 06B8A109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 03:51:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E33D7222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 03:51:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729008AbgAODvV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jan 2020 22:51:21 -0500
Received: from mga11.intel.com ([192.55.52.93]:3148 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728884AbgAODvV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jan 2020 22:51:21 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 14 Jan 2020 19:51:21 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,321,1574150400";
   d="scan'208";a="213570974"
Received: from unknown (HELO joy-OptiPlex-7040.sh.intel.com) ([10.239.13.9])
  by orsmga007.jf.intel.com with ESMTP; 14 Jan 2020 19:51:18 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com, zhenyuw@linux.intel.com
Cc: intel-gvt-dev@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        kevin.tian@intel.com, peterx@redhat.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v2 0/2] use vfio_dma_rw to read/write IOVAs from CPU side
Date: Tue, 14 Jan 2020 22:41:32 -0500
Message-Id: <20200115034132.2753-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is better for a device model to use IOVAs to read/write memory.
And because the rw operations come from CPUs, it is not necessary to call
vfio_pin_pages() to pin those pages.

patch 1 introduces interface vfio_dma_rw in vfio to read/write IOVAs
without pinning user space pages.

patch 2 let gvt switch from kvm side rw interface to vfio_dma_rw.

v2 changelog:
- rename vfio_iova_rw to vfio_dma_rw, vfio iommu driver ops .iova_rw
to .dma_rw. (Alex).
- change iova and len from unsigned long to dma_addr_t and size_t,
respectively. (Alex)
- fix possible overflow in dma->vaddr + iova - dma->iova + offset (Alex)
- split DMAs from on page boundary to on max available size to eliminate
  redundant searching of vfio_dma and switching mm. (Alex)
- add a check for IOMMU_WRITE permission.

Yan Zhao (2):
  vfio: introduce vfio_dma_rw to read/write a range of IOVAs
  drm/i915/gvt: subsitute kvm_read/write_guest with vfio_dma_rw

 drivers/gpu/drm/i915/gvt/kvmgt.c | 26 +++--------
 drivers/vfio/vfio.c              | 45 +++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c  | 76 ++++++++++++++++++++++++++++++++
 include/linux/vfio.h             |  5 +++
 4 files changed, 133 insertions(+), 19 deletions(-)
```
#### [PATCH RFC 0/3] x86/kvm/hyper-v: fix enlightened VMCS & QEMU4.2
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Jan 15 17:10:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11335449
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 756A213BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 17:10:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 532D22465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 17:10:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MV03FqL2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729154AbgAORKd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 12:10:33 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:43780 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729057AbgAORKY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 12:10:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579108223;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=oh8syvO3W6gUaj5dvdzY+X7LicIsoPtaC11FOH1zRXg=;
        b=MV03FqL2S9SPquadi0qA/KKu43ahwCdDHUURU24ujMtcXSoZ10ypeN/RSqAaQVrLxlJdIb
        XUMuvDkojhoYXa9n0R6Sju4COA7BuEu3QAXYN4oRyN93365hQko1jmQS9ObrjV8f3i1A6l
        9QWvHp4NvKkyAf8OpDfutd+5UNCAhNk=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-183-cQfE8RhiMVW02hXz8o0yyQ-1; Wed, 15 Jan 2020 12:10:18 -0500
X-MC-Unique: cQfE8RhiMVW02hXz8o0yyQ-1
Received: by mail-wr1-f71.google.com with SMTP id z14so8309679wrs.4
        for <kvm@vger.kernel.org>; Wed, 15 Jan 2020 09:10:17 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oh8syvO3W6gUaj5dvdzY+X7LicIsoPtaC11FOH1zRXg=;
        b=tQ3eDes8++4eWL0Amp2BIGBut7KFq3oA+Nv+KiTmTn1BEEPlcuVT0sWZzp+sSBDVry
         K2QgLvZTIy2PcfBXp7jbxihdpz/AeIh0d0pGH+8cpA7/cn/rJWOhu8lkPLM/dFkGJtND
         b4pSAtH6+XnOPrdOBgaUvlfrpRsIYUg1DtF0iJesDpgzeDIrC97oA1s+rzqKZpPkxZ7H
         V87kTCycKA8xfjH6tQ2p26IvLt+ea25Ke5W0ei7HPcO5yY83In7vKfFxkzmdUEJLwe3w
         2rLWdjgUMHlH9Mzafj+zUCgi9UWIsRy5XNXWCg5SURB3pcIIagohJJRdsi0Y5hzIJXjr
         hubw==
X-Gm-Message-State: APjAAAWDQ3m2kRldGHtUazF6neRGqA97IgzYrPfpCzcmzWsF0pkNNXIP
        xC0sGP94BZkgFc0bUPySdi2iPZBYBxrDzYRt0VDGZ5T3REEn78XSbKKlYozltlPehSeKiu5Atz/
        gkn7wHF0Gr54j
X-Received: by 2002:a05:600c:54b:: with SMTP id
 k11mr868450wmc.63.1579108216783;
        Wed, 15 Jan 2020 09:10:16 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxxAUtkMeLimE0mSVgQTbE8fcqGapcKBRgSHFCBxThX2YfhrLDkFqEnKuSGULrLXasq18IvZA==
X-Received: by 2002:a05:600c:54b:: with SMTP id
 k11mr868433wmc.63.1579108216524;
        Wed, 15 Jan 2020 09:10:16 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 y20sm525071wmi.25.2020.01.15.09.10.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 15 Jan 2020 09:10:15 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH RFC 0/3] x86/kvm/hyper-v: fix enlightened VMCS & QEMU4.2
Date: Wed, 15 Jan 2020 18:10:11 +0100
Message-Id: <20200115171014.56405-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With fine grained VMX feature enablement QEMU>=4.2 tries to do KVM_SET_MSRS
with default (matching CPU model) values and in case eVMCS is also enabled,
fails. While the regression is in QEMU, it may still be preferable to
fix this in KVM.

It would be great if we could just omit the VMX feature filtering in KVM
and make this guest's responsibility: if it switches to using enlightened
vmcs it should be aware that not all hardware features are going to be
supported. Genuine Hyper-V, however, fails the test. In particular, it
enables SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES and without
'apic_access_addr' field in eVMCS there's not much we can do in KVM.

The suggested approach in this patch series is: move VMX feature
filtering to vmx_get_msr() so only guest doesn't see them when eVMCS
is enabled (PATCH2) and add a check that it doesn't enable them
(PATCH3).

I can't say that I'm a great fan of this workaround myself, thus RFC.

My initial RFC sent to qemu-devel@:
https://lists.nongnu.org/archive/html/qemu-devel/2020-01/msg00123.html

Vitaly Kuznetsov (3):
  x86/kvm/hyper-v: remove stale evmcs_already_enabled check from
    nested_enable_evmcs()
  x86/kvm/hyper-v: move VMX controls sanitization out of
    nested_enable_evmcs()
  x86/kvm/hyper-v: don't allow to turn on unsupported VMX controls for
    nested guests

 arch/x86/kvm/vmx/evmcs.c  | 99 ++++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/vmx/evmcs.h  |  2 +
 arch/x86/kvm/vmx/nested.c |  3 ++
 arch/x86/kvm/vmx/vmx.c    | 10 +++-
 4 files changed, 100 insertions(+), 14 deletions(-)
```
