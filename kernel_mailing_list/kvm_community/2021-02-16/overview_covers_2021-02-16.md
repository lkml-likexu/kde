

#### [PATCH v2 0/1] s390/vfio-ap: fix circular lockdep when staring SE
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Tue Feb 16 01:15:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12089329
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 575E3C433E9
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 01:17:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EC7F64DAF
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 01:17:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229881AbhBPBQp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Feb 2021 20:16:45 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14760 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229796AbhBPBQn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Feb 2021 20:16:43 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11G11bNm002079;
        Mon, 15 Feb 2021 20:15:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=gU4FNIphuUI1q38DRUTcXAriUiExmJdHEkApVL/gVdU=;
 b=ehKGnKc35FezKoeEpXjh2mz4jdRjCR/lYpo97aMuZJNPjxf4SvJ/mys2bgW5QDekbrDr
 ibbcMlkkH0YxwMVfJETBr1OeZu5AgOLlWy2mPZBUn8XDKjaiXdhsmO0Sx2qBwq1HyXeu
 AS686W4kAKr3Rf0NyHAXizVY60k+EcyuMr9EDDSkeOIXjFs7Ik35080rTAJXXNc3K9dA
 6/7va8qEQnggKJ1+9/TT52dopzO6GDO7h0+wt7S0uY+EfLGMWiU1vOM5W9cJO4af6W2K
 /pEnrdqKIu99ROitG/g3pPu91AVRVhTLZ8MbkhF6VzE1SRXt1KnaDsrEYMQVhVZSoIjS Ng==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36r2dwadac-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 20:15:56 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11G14di3015818;
        Mon, 15 Feb 2021 20:15:56 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36r2dwada2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 20:15:55 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11G1Biw2004463;
        Tue, 16 Feb 2021 01:15:55 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma04wdc.us.ibm.com with ESMTP id 36p6d8tx9m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Feb 2021 01:15:55 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 11G1FsBh30933426
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Feb 2021 01:15:54 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BA1822805E;
        Tue, 16 Feb 2021 01:15:54 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 17A8E28058;
        Tue, 16 Feb 2021 01:15:54 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.203.235])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 16 Feb 2021 01:15:53 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v2 0/1] s390/vfio-ap: fix circular lockdep when staring SE
 guest
Date: Mon, 15 Feb 2021 20:15:46 -0500
Message-Id: <20210216011547.22277-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-15_16:2021-02-12,2021-02-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 adultscore=0
 bulkscore=0 spamscore=0 priorityscore=1501 suspectscore=0 clxscore=1015
 malwarescore=0 impostorscore=0 lowpriorityscore=0 mlxlogscore=999
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102160003
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM
pointer invalidated") introduced a change that results in a circular
lockdep when a Secure Execution guest that is configured with
crypto devices is started. The problem resulted due to the fact that the
patch moved the setting of the guest's AP masks within the protection of
the matrix_dev->lock when the vfio_ap driver is notified that the KVM 
pointer has been set. Since it is not critical that setting/clearing of
the guest's AP masks be done under the matrix_dev->lock when the driver is
notified, the masks will not be updated under the matrix_dev->lock. The
lock is necessary for the setting/unsetting of the KVM pointer, however,
so that will remain in place. 

The dependency chain for the circular lockdep resolved by this patch 
is (in reverse order):

2:	vfio_ap_mdev_group_notifier:	kvm->lock
					matrix_dev->lock

1:	handle_pqap:			matrix_dev->lock
	kvm_vcpu_ioctl:			vcpu->mutex

0:	kvm_s390_cpus_to_pv:		vcpu->mutex
	kvm_vm_ioctl:  			kvm->lock

Please note that if checkpatch is run against this patch series, you may
get a "WARNING: Unknown commit id 'f21916ec4826', maybe rebased or not 
pulled?" message. The commit 'f21916ec4826', however, is definitely
in the master branch on top of which this patch series was built, so I'm
not sure why this message is being output by checkpatch. 

Change log v1=> v2:
------------------
* No longer holding the matrix_dev->lock prior to setting/clearing the
  masks supplying the AP configuration to a KVM guest.
* Make all updates to the data in the matrix mdev that is used to manage
  AP resources used by the KVM guest in the vfio_ap_mdev_set_kvm() function
  instead of the group notifier callback.
* Check for the matrix mdev's KVM pointer in the vfio_ap_mdev_unset_kvm()
  function instead of the vfio_ap_mdev_release() function.

Tony Krowiak (1):
  s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks

 drivers/s390/crypto/vfio_ap_ops.c | 119 +++++++++++++++++++++---------
 1 file changed, 84 insertions(+), 35 deletions(-)
```
#### [RFC PATCH 00/23] [RFC PATCH 00/24] TDX support
##### From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
From patchwork Tue Feb 16 02:12:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Isaku Yamahata <isaku.yamahata@intel.com>
X-Patchwork-Id: 12089419
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 969ACC433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 02:16:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 72B7A64DF0
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 02:16:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229894AbhBPCPv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Feb 2021 21:15:51 -0500
Received: from mga11.intel.com ([192.55.52.93]:40350 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229809AbhBPCPg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Feb 2021 21:15:36 -0500
IronPort-SDR: 
 7LVho8WCiGPzBmUWNyhY+tRCzqY5XNHlLtlmR7mcHHEEkifp6V5tDbpahJbl0qYwSOpaaa1zXV
 exCadvwdTbtQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9896"; a="179288239"
X-IronPort-AV: E=Sophos;i="5.81,182,1610438400";
   d="scan'208";a="179288239"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Feb 2021 18:14:50 -0800
IronPort-SDR: 
 opA2wsoGwXlexia1iVVZwIznZPh9F6pNgF1W/EYzonAX8H6+m8Nu1OZiufhfN1SNrqI6MjFz1L
 UivLAWaCPPSQ==
X-IronPort-AV: E=Sophos;i="5.81,182,1610438400";
   d="scan'208";a="399305134"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Feb 2021 18:14:49 -0800
From: Isaku Yamahata <isaku.yamahata@intel.com>
To: qemu-devel@nongnu.org, pbonzini@redhat.com, alistair@alistair23.me,
        ehabkost@redhat.com, marcel.apfelbaum@gmail.com, mst@redhat.com,
        cohuck@redhat.com, mtosatti@redhat.com, xiaoyao.li@intel.com,
        seanjc@google.com
Cc: kvm@vger.kernel.org, isaku.yamahata@gmail.com,
        isaku.yamahata@intel.com
Subject: [RFC PATCH 00/23] [RFC PATCH 00/24] TDX support
Date: Mon, 15 Feb 2021 18:12:56 -0800
Message-Id: <cover.1613188118.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is to enable TDX support.
This needs corresponding KVM patch for TDX[] and more patches are needed
that addresses generic corner cases, e.g. ACPI related stuff, are needed.
So This patch series is RFC.
More emulated devices and their behavior needs to be adjusted as some
operations are disallowed.

Patch series is organized as follows
 1- 5 code refactoring and simple hooks that will be used later
 6- 9 introduce kvm type and tdx type. disallow non-usable operations
10-15 wire up necessary TDX kvm ioctl to initialize TD guest
16-21 load TDVF and setup necessary info for TDVF
22-23 force x2apic and disable PIC

Isaku Yamahata (12):
  kvm: Switch KVM_CAP_READONLY_MEM to a per-VM ioctl()
  KVM: i386: use VM capability check for KVM_CAP_X86_SMM
  vl: Introduce machine_init_done_late notifier
  i386/kvm: Skip KVM_X86_SETUP_MCE for TDX guests
  target/i386: kvm: don't synchronize guest tsc for TD guest
  i386/tdx: Frame in the call for KVM_TDX_INIT_VCPU
  hw/i386: Add definitions from UEFI spec for volumes, resources, etc...
  i386/tdx: Add definitions for TDVF metadata
  i386/tdx: Parse tdvf metadata and store the result into TdxGuest
  i386/tdx: Create the TD HOB list upon machine init done
  i386/tdx: Add TDVF memory via INIT_MEM_REGION
  i386/tdx: Use KVM_TDX_INIT_VCPU to pass HOB to TDVF

Sean Christopherson (7):
  target/i386: Expose x86_cpu_get_supported_feature_word() for TDX
  i386/kvm: Move architectural CPUID leaf generation to separarte helper
  i386/kvm: Squash getting/putting guest state for TDX VMs
  i386/tdx: Frame in tdx_get_supported_cpuid with KVM_TDX_CAPABILITIES
  i386/tdx: Add hook to require generic device loader
  i386/tdx: Force x2apic mode and routing for TDs
  target/i386: Add machine option to disable PIC/8259

Xiaoyao Li (4):
  hw/i386: Introduce kvm-type for TDX guest
  linux-headers: Update headers to pull in TDX API changes
  hw/i386: Initialize TDX via KVM ioctl() when kvm_type is TDX
  target/i386/tdx: Finalize the TD's measurement when machine is done

 accel/kvm/kvm-all.c                      |   4 +-
 default-configs/devices/i386-softmmu.mak |   1 +
 hw/core/generic-loader.c                 |   5 +
 hw/core/machine.c                        |  26 ++
 hw/core/meson.build                      |   3 +
 hw/core/tdvf-stub.c                      |   6 +
 hw/i386/Kconfig                          |   5 +
 hw/i386/meson.build                      |   1 +
 hw/i386/pc.c                             |  18 +
 hw/i386/pc_piix.c                        |   4 +-
 hw/i386/pc_q35.c                         |   4 +-
 hw/i386/pc_sysfw.c                       |   6 +
 hw/i386/tdvf-hob.c                       | 226 +++++++++++
 hw/i386/tdvf-hob.h                       |  25 ++
 hw/i386/tdvf.c                           | 305 ++++++++++++++
 hw/i386/uefi.h                           | 496 +++++++++++++++++++++++
 hw/i386/x86.c                            |  46 +++
 hw/intc/apic_common.c                    |  12 +
 include/hw/i386/apic.h                   |   1 +
 include/hw/i386/apic_internal.h          |   1 +
 include/hw/i386/pc.h                     |   2 +
 include/hw/i386/tdvf.h                   |  55 +++
 include/hw/i386/x86.h                    |   1 +
 include/sysemu/sysemu.h                  |   2 +
 include/sysemu/tdvf.h                    |   6 +
 include/sysemu/tdx.h                     |  15 +
 linux-headers/asm-x86/kvm.h              |  55 +++
 linux-headers/linux/kvm.h                |   2 +
 target/i386/cpu.c                        |   4 +-
 target/i386/cpu.h                        |   3 +
 target/i386/kvm/kvm-stub.c               |   5 +
 target/i386/kvm/kvm.c                    | 227 +++++++----
 target/i386/kvm/kvm_i386.h               |   5 +
 target/i386/kvm/meson.build              |   1 +
 target/i386/kvm/tdx-stub.c               |  23 ++
 target/i386/kvm/tdx.c                    | 329 +++++++++++++++
 target/i386/kvm/tdx.h                    |  55 +++
 37 files changed, 1893 insertions(+), 92 deletions(-)
 create mode 100644 hw/core/tdvf-stub.c
 create mode 100644 hw/i386/tdvf-hob.c
 create mode 100644 hw/i386/tdvf-hob.h
 create mode 100644 hw/i386/tdvf.c
 create mode 100644 hw/i386/uefi.h
 create mode 100644 include/hw/i386/tdvf.h
 create mode 100644 include/sysemu/tdvf.h
 create mode 100644 include/sysemu/tdx.h
 create mode 100644 target/i386/kvm/tdx-stub.c
 create mode 100644 target/i386/kvm/tdx.c
 create mode 100644 target/i386/kvm/tdx.h
```
#### [RFC PATCH 00/10] vdpa: get/set_config() rework
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Tue Feb 16 09:44:44 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12089707
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A3985C433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 09:46:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55E9764DCF
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 09:46:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229919AbhBPJqg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Feb 2021 04:46:36 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:36817 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229626AbhBPJqd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Feb 2021 04:46:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613468707;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=wcnd7ClbZgShooWszPEgOAqPp+c33seC7pun/tamuzE=;
        b=hti9g678GWwU23gGIDts/48Kubo5NXXl/1cT/UQlemoHVxp53DCzgmQGQCCE87GwvSFwPS
        Cs8EulP2Q30rGhWDNW6kOAAt895hwf2nOUH7HC7eJE4iYn5gTIMkfrLDVqHO0/Yo+RSGXv
        Cg7a34t/6+mDLNMvOdrsvlV5u2K3RHc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-474-MA4WhP80O1ixGB_T6ZurCA-1; Tue, 16 Feb 2021 04:45:04 -0500
X-MC-Unique: MA4WhP80O1ixGB_T6ZurCA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0CD6A801998;
        Tue, 16 Feb 2021 09:45:03 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-212.ams2.redhat.com
 [10.36.113.212])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E7BD15D9C0;
        Tue, 16 Feb 2021 09:44:55 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC PATCH 00/10] vdpa: get/set_config() rework
Date: Tue, 16 Feb 2021 10:44:44 +0100
Message-Id: <20210216094454.82106-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Following the discussion with Michael and Jason [1], I reworked a bit
get/set_config() in vdpa.

I changed vdpa_get_config() to check the boundaries and added vdpa_set_config().
When 'offset' or 'len' parameters exceed boundaries, we limit the reading to
the available configuration space in the device, and we return the amount of
bytes read/written.

In this way the user space can pass buffers bigger than config space.
I also returned the amount of bytes read and written to user space.

Patches also available here:
https://github.com/stefano-garzarella/linux/tree/vdpa-get-set-config-refactoring

Thanks for your comments,
Stefano

[1] https://lkml.org/lkml/2021/2/10/350

Stefano Garzarella (10):
  vdpa: add get_config_size callback in vdpa_config_ops
  vdpa: check vdpa_get_config() parameters and return bytes read
  vdpa: add vdpa_set_config() helper
  vdpa: remove param checks in the get/set_config callbacks
  vdpa: remove WARN_ON() in the get/set_config callbacks
  virtio_vdpa: use vdpa_set_config()
  vhost/vdpa: use vdpa_set_config()
  vhost/vdpa: allow user space to pass buffers bigger than config space
  vhost/vdpa: use get_config_size callback in
    vhost_vdpa_config_validate()
  vhost/vdpa: return configuration bytes read and written to user space

 include/linux/vdpa.h              | 22 ++++-------
 drivers/vdpa/ifcvf/ifcvf_base.c   |  3 +-
 drivers/vdpa/ifcvf/ifcvf_main.c   |  8 +++-
 drivers/vdpa/mlx5/net/mlx5_vnet.c |  9 ++++-
 drivers/vdpa/vdpa.c               | 51 ++++++++++++++++++++++++
 drivers/vdpa/vdpa_sim/vdpa_sim.c  | 15 +++++---
 drivers/vhost/vdpa.c              | 64 ++++++++++++++++---------------
 drivers/virtio/virtio_vdpa.c      |  3 +-
 8 files changed, 116 insertions(+), 59 deletions(-)
```
