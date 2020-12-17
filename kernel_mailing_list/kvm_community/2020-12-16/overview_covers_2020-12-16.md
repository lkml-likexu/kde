

#### [PATCH 0/2] Enumerate and expose AVX_VNNI feature
##### From: Yang Zhong <yang.zhong@intel.com>

```c
From patchwork Wed Dec 16 02:01:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Zhong <yang.zhong@intel.com>
X-Patchwork-Id: 11976289
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E427C4361B
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 02:56:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0E4B323130
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 02:56:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725780AbgLPC4G (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 15 Dec 2020 21:56:06 -0500
Received: from mga09.intel.com ([134.134.136.24]:29831 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725710AbgLPC4F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Dec 2020 21:56:05 -0500
IronPort-SDR: 
 +Pz0CGGXVOIVx1aJ+co9iQGTc0iey7hGlXq2A2U9N7gXCSQpe32Zf/mfm/QJ47XaTBsrzeiaDb
 Sl9pos3io84w==
X-IronPort-AV: E=McAfee;i="6000,8403,9836"; a="175135304"
X-IronPort-AV: E=Sophos;i="5.78,423,1599548400";
   d="scan'208";a="175135304"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Dec 2020 18:55:48 -0800
IronPort-SDR: 
 1rQpOIgf5gRmVEWY1QU262a/Z7RX/jkCuKvmRyqgdHHfSfggL83ZnOrb02TqxeI2zqOPhz2eB+
 UDt9jbasmV7w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,423,1599548400";
   d="scan'208";a="451538766"
Received: from icx-2s.bj.intel.com ([10.240.192.119])
  by fmsmga001.fm.intel.com with ESMTP; 15 Dec 2020 18:55:45 -0800
From: Yang Zhong <yang.zhong@intel.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        tony.luck@intel.com, pbonzini@redhat.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, kyung.min.park@intel.com, yang.zhong@intel.com
Subject: [PATCH 0/2] Enumerate and expose AVX_VNNI feature
Date: Wed, 16 Dec 2020 10:01:27 +0800
Message-Id: <20201216020129.19875-1-yang.zhong@intel.com>
X-Mailer: git-send-email 2.29.2.334.gfaefdd61ec
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A processor supports AVX_VNNI instructions if CPUID.(EAX=7,ECX=1):EAX[bit 4]
is present.

This series includes kernel and kvm patches, kernel patch define this
new cpu feature bit and kvm expose this bit to guest. When this bit is
enabled on cpu or vcpu, the cpu feature flag is shown as "avx_vnni" in
/proc/cpuinfo of host and guest.

Detailed information on the instruction and CPUID feature flag can be
found in the latest "extensions" manual [1].

Reference:
[1]. https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html


Kyung Min Park (1):
  Enumerate AVX Vector Neural Network instructions

Yang Zhong (1):
  KVM: Expose AVX_VNNI instruction to guset

 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kvm/cpuid.c               | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)
```
#### [PATCH 00/21] Control VQ support in vDPA
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Dec 16 06:47:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11976721
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C9564C2BBD4
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 06:50:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A325123371
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 06:50:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725931AbgLPGuE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 01:50:04 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40000 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725274AbgLPGuE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 01:50:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608101317;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=spj9CMYtee5G5sWC8UnW3oUIg25fvwv0Y3rRIX8a8Gc=;
        b=D5SP3q4i4aKRxbLTgrbXteD+dCSvlvaX9U3+YQ4gjiqmIoDq5KqWQlsBi07yXQKikwrkfW
        h/2kl2l+EKEHxvb6vVqeNTS59YPEFhk0J33cfCgAsHH6Lc0XTR3ol5Q4HHxdfQoonKOI7f
        V1Vdhk6iBX/WOKJsViNF13wsUNT/35Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-459-PFy-QapTMuu9VuVWykG2Og-1; Wed, 16 Dec 2020 01:48:32 -0500
X-MC-Unique: PFy-QapTMuu9VuVWykG2Og-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9DBE5801A9E;
        Wed, 16 Dec 2020 06:48:30 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-210.pek2.redhat.com [10.72.12.210])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 24FDD10013C1;
        Wed, 16 Dec 2020 06:48:19 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: eperezma@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, lulu@redhat.com, eli@mellanox.com,
        lingshan.zhu@intel.com, rob.miller@broadcom.com,
        stefanha@redhat.com, sgarzare@redhat.com
Subject: [PATCH 00/21] Control VQ support in vDPA
Date: Wed, 16 Dec 2020 14:47:57 +0800
Message-Id: <20201216064818.48239-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All:

This series tries to add the support for control virtqueue in vDPA.

Control virtqueue is used by networking device for accepting various
commands from the driver. It's a must to support multiqueue and other
configurations.

When used by vhost-vDPA bus driver for VM, the control virtqueue
should be shadowed via userspace VMM (Qemu) instead of being assigned
directly to Guest. This is because Qemu needs to know the device state
in order to start and stop device correctly (e.g for Live Migration).

This requies to isolate the memory mapping for control virtqueue
presented by vhost-vDPA to prevent guest from accesing it directly.

To achieve this, vDPA introduce two new abstractions:

- address space: identified through address space id (ASID) and a set
                 of memory mapping in maintained
- virtqueue group: the minimal set of virtqueues that must share an
                 address space

Device needs to advertise the following attributes to vDPA:

- the number of address spaces supported in the device
- the number of virtqueue groups supported in the device
- the mappings from a specific virtqueue to its virtqueue groups

The mappings from virtqueue to virtqueue groups is fixed and defined
by vDPA device driver. E.g:

- For the device that has hardware ASID support, it can simply
  advertise a per virtqueue virtqueue group.
- For the device that does not have hardware ASID support, it can
  simply advertise a single virtqueue group that contains all
  virtqueues. Or if it wants a software emulated control virtqueue, it
  can advertise two virtqueue groups, one is for cvq, another is for
  the rest virtqueues.

vDPA also allow to change the association between virtqueue group and
address space. So in the case of control virtqueue, userspace
VMM(Qemu) may use a dedicated address space for the control virtqueue
group to isolate the memory mapping.

The vhost/vhost-vDPA is also extend for the userspace to:

- query the number of virtqueue groups and address spaces supported by
  the device
- query the virtqueue group for a specific virtqueue
- assocaite a virtqueue group with an address space
- send ASID based IOTLB commands

This will help userspace VMM(Qemu) to detect whether the control vq
could be supported and isolate memory mappings of control virtqueue
from the others.

To demonstrate the usage, vDPA simulator is extended to support
setting MAC address via a emulated control virtqueue.

Please review.

Changes since RFC:

- tweak vhost uAPI documentation
- switch to use device specific IOTLB really in patch 4
- tweak the commit log
- fix that ASID in vhost is claimed to be 32 actually but 16bit
  actually
- fix use after free when using ASID with IOTLB batching requests
- switch to use Stefano's patch for having separated iov
- remove unused "used_as" variable
- fix the iotlb/asid checking in vhost_vdpa_unmap()

Thanks

Jason Wang (20):
  vhost: move the backend feature bits to vhost_types.h
  virtio-vdpa: don't set callback if virtio doesn't need it
  vhost-vdpa: passing iotlb to IOMMU mapping helpers
  vhost-vdpa: switch to use vhost-vdpa specific IOTLB
  vdpa: add the missing comment for nvqs in struct vdpa_device
  vdpa: introduce virtqueue groups
  vdpa: multiple address spaces support
  vdpa: introduce config operations for associating ASID to a virtqueue
    group
  vhost_iotlb: split out IOTLB initialization
  vhost: support ASID in IOTLB API
  vhost-vdpa: introduce asid based IOTLB
  vhost-vdpa: introduce uAPI to get the number of virtqueue groups
  vhost-vdpa: introduce uAPI to get the number of address spaces
  vhost-vdpa: uAPI to get virtqueue group id
  vhost-vdpa: introduce uAPI to set group ASID
  vhost-vdpa: support ASID based IOTLB API
  vdpa_sim: advertise VIRTIO_NET_F_MTU
  vdpa_sim: factor out buffer completion logic
  vdpa_sim: filter destination mac address
  vdpasim: control virtqueue support

Stefano Garzarella (1):
  vdpa_sim: split vdpasim_virtqueue's iov field in out_iov and in_iov

 drivers/vdpa/ifcvf/ifcvf_main.c   |   9 +-
 drivers/vdpa/mlx5/net/mlx5_vnet.c |  11 +-
 drivers/vdpa/vdpa.c               |   8 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c  | 292 ++++++++++++++++++++++++------
 drivers/vhost/iotlb.c             |  23 ++-
 drivers/vhost/vdpa.c              | 246 ++++++++++++++++++++-----
 drivers/vhost/vhost.c             |  23 ++-
 drivers/vhost/vhost.h             |   4 +-
 drivers/virtio/virtio_vdpa.c      |   2 +-
 include/linux/vdpa.h              |  42 ++++-
 include/linux/vhost_iotlb.h       |   2 +
 include/uapi/linux/vhost.h        |  25 ++-
 include/uapi/linux/vhost_types.h  |  10 +-
 13 files changed, 561 insertions(+), 136 deletions(-)
```
#### [PATCH v3 0/4] KVM: PPC: Power10 2nd DAWR enablement
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Wed Dec 16 10:42:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11977211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D49C6C2BBCF
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 10:44:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A07B423357
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 10:44:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726327AbgLPKoc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 05:44:32 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:55098 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726288AbgLPKob (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 05:44:31 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGAVUGp074045;
        Wed, 16 Dec 2020 05:43:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=sTi5ENDvNYn/Nu6cWCNyjnsbtTWHyVrZRsMwWRoJwmY=;
 b=fWdZdtSr52y3gdyvh7hsCHrC5li8W4aI7388ehhNFlT4btNADdIxDgn9AigPkrJHYV/r
 3HS01300rQjpv3DlzEdTiCBOZ+ugLOsl5LQAKG3UCAUBNPVG3WuFTBKP4RrivtamUp68
 inPZgmNdOtaS8pVhiZBZNjWt5Cax78gR3sNlS7HsivDGbkwiyYPH1YB7Xs8V7/62AjPy
 IksFq4HHWB4k0a4aw1FpOGAJVo1TTpxnsh44cPSSrsNRH4jo79Hwq2J5k3ZwoiavqTpu
 ThmSUNkYMhN3LHvx5bQv8E9eHs0Omazti0j2VCKJ1zKVAY9IFieyU0XKizK1VINLEQPc lA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35ff7k2p3u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 05:43:16 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BGAVZHu074484;
        Wed, 16 Dec 2020 05:43:15 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35ff7k2p36-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 05:43:15 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGAhE7P011329;
        Wed, 16 Dec 2020 10:43:14 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04fra.de.ibm.com with ESMTP id 35cng8a66n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 10:43:13 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BGAhBKf29557034
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Dec 2020 10:43:11 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8DF7E11C052;
        Wed, 16 Dec 2020 10:43:11 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 62C7D11C05C;
        Wed, 16 Dec 2020 10:43:08 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.41.249])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 16 Dec 2020 10:43:08 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        leobras.c@gmail.com, pbonzini@redhat.com, christophe.leroy@c-s.fr,
        jniethe5@gmail.com, kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Subject: [PATCH v3 0/4] KVM: PPC: Power10 2nd DAWR enablement
Date: Wed, 16 Dec 2020 16:12:15 +0530
Message-Id: <20201216104219.458713-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-16_04:2020-12-15,2020-12-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 lowpriorityscore=0 mlxlogscore=966 adultscore=0 spamscore=0 mlxscore=0
 malwarescore=0 priorityscore=1501 phishscore=0 bulkscore=0 impostorscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012160063
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enable p10 2nd DAWR feature for Book3S kvm guest. DAWR is a hypervisor
resource and thus H_SET_MODE hcall is used to set/unset it. A new case
H_SET_MODE_RESOURCE_SET_DAWR1 is introduced in H_SET_MODE hcall for
setting/unsetting 2nd DAWR. Also, new capability KVM_CAP_PPC_DAWR1 has
been added to query 2nd DAWR support via kvm ioctl.

This feature also needs to be enabled in Qemu to really use it. I'll
post Qemu patches once kvm patches get accepted.

v2: https://lore.kernel.org/kvm/20201124105953.39325-1-ravi.bangoria@linux.ibm.com

v2->v3:
 - Patch #1. If L0 version > L1, L0 hv_guest_state will contain some
   additional fields which won't be filled while reading from L1
   memory and thus they can contain garbage. Initialize l2_hv with 0s
   to avoid such situations.
 - Patch #3. Introduce per vm flag dawr1_enabled.
 - Patch #4. Instead of auto enabling KVM_CAP_PPC_DAWR1, let user check
   and enable it manually. Also move KVM_CAP_PPC_DAWR1 check / enable
   logic inside #if defined(CONFIG_KVM_BOOK3S_HV_POSSIBLE).
 - Explain KVM_CAP_PPC_DAWR1 in Documentation/virt/kvm/api.rst 
 - Rebased on top of 5.10-rc3.

v1->v2:
 - patch #1: New patch
 - patch #2: Don't rename KVM_REG_PPC_DAWR, it's an uapi macro
 - patch #3: Increment HV_GUEST_STATE_VERSION
 - Split kvm and selftests patches into different series
 - Patches rebased to paulus/kvm-ppc-next (cf59eb13e151) + few
   other watchpoint patches which are yet to be merged in
   paulus/kvm-ppc-next.

Ravi Bangoria (4):
  KVM: PPC: Allow nested guest creation when L0 hv_guest_state > L1
  KVM: PPC: Rename current DAWR macros and variables
  KVM: PPC: Add infrastructure to support 2nd DAWR
  KVM: PPC: Introduce new capability for 2nd DAWR

 Documentation/virt/kvm/api.rst            | 12 ++++
 arch/powerpc/include/asm/hvcall.h         | 25 ++++++-
 arch/powerpc/include/asm/kvm_host.h       |  7 +-
 arch/powerpc/include/asm/kvm_ppc.h        |  1 +
 arch/powerpc/include/uapi/asm/kvm.h       |  2 +
 arch/powerpc/kernel/asm-offsets.c         |  6 +-
 arch/powerpc/kvm/book3s_hv.c              | 79 +++++++++++++++++++----
 arch/powerpc/kvm/book3s_hv_nested.c       | 70 ++++++++++++++++----
 arch/powerpc/kvm/book3s_hv_rmhandlers.S   | 43 +++++++++---
 arch/powerpc/kvm/powerpc.c                | 10 +++
 include/uapi/linux/kvm.h                  |  1 +
 tools/arch/powerpc/include/uapi/asm/kvm.h |  2 +
 tools/include/uapi/linux/kvm.h            |  1 +
 13 files changed, 216 insertions(+), 43 deletions(-)
```
#### [kvm-unit-tests PATCH v1 00/12] Fix and improve the page allocator
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Wed Dec 16 20:11:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11978509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7859FC2BBCF
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 20:13:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5449A23619
	for <kvm@archiver.kernel.org>; Wed, 16 Dec 2020 20:13:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728691AbgLPUNG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 16 Dec 2020 15:13:06 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49262 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728533AbgLPUNF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 16 Dec 2020 15:13:05 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGK32qD080471
        for <kvm@vger.kernel.org>; Wed, 16 Dec 2020 15:12:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=hHo7bpbeDEZcxPJM7AREYpbKK7jPpoDEl9OMqA2Unjo=;
 b=djFLrdmSxg5sTOcNwYrhAxTah9vmiefmijJwsWPPKs+O7gv1GJJcusTXc9NzdwnZMisO
 nLOHzMliAPmpgONQXGxOnk3QSv+gBQFM8buuxGIfdjSY6XKZM60wwvZFOL83ZRcnepn5
 8yCnNbvDdHSVmaNfGTuJXE0jNK/yQZDq9gNvTeoAIAgDKcMJ0TZh7aN5tg8G5V5bn0UW
 0Vxtz4ki52Nijs/ENLjVVbdMN5mtvWyyRJsyvFnDsyUDjBslWDpTeyljTYOm7EETBJXG
 LSxp4TA5JSfMoNo3ajks75k6eXzWYuI3z9Nfvy399Avu5hUKGNjjNCVqs8fzq5rorZr9 SQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35fqbqtvs0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 16 Dec 2020 15:12:24 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BGK35Zg080708
        for <kvm@vger.kernel.org>; Wed, 16 Dec 2020 15:12:24 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35fqbqtvrm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 15:12:24 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BGK7DJl016243;
        Wed, 16 Dec 2020 20:12:22 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 35cng8adtp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 16 Dec 2020 20:12:22 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BGKCK0734013564
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 16 Dec 2020 20:12:20 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E379242054;
        Wed, 16 Dec 2020 20:12:19 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7A6904204B;
        Wed, 16 Dec 2020 20:12:19 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.74])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 16 Dec 2020 20:12:19 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        pbonzini@redhat.com, cohuck@redhat.com, lvivier@redhat.com,
        nadav.amit@gmail.com
Subject: [kvm-unit-tests PATCH v1 00/12] Fix and improve the page allocator
Date: Wed, 16 Dec 2020 21:11:48 +0100
Message-Id: <20201216201200.255172-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-16_08:2020-12-15,2020-12-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 bulkscore=0
 priorityscore=1501 phishscore=0 impostorscore=0 malwarescore=0 mlxscore=0
 lowpriorityscore=0 spamscore=0 mlxlogscore=999 adultscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2012160120
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

My previous patchseries was rushed and not polished enough. Furthermore it
introduced some regressions.

This patchseries fixes hopefully all the issues reported, and introduces
some new features.

It also simplifies the code and hopefully makes it more readable.

Fixed:
* allocated memory is now zeroed by default

New features:
* per-allocation flags to specify not just the area (like before) but also
  other parameters
  - zero flag: the allocation will be zeroed
  - fresh flag: the returned memory has never been read or written to before
* default flags: it's possible to specify which flags should be enabled
  automatically at each allocation; by default the zero flag is set.


I would appreciate if people could test these patches, especially on
strange, unusual or exotic hardware (I tested only on s390x)


GitLab:
  https://gitlab.com/imbrenda/kvm-unit-tests/-/tree/page_allocator_fixes
CI:
  https://gitlab.com/imbrenda/kvm-unit-tests/-/pipelines/229689192


Claudio Imbrenda (12):
  lib/x86: fix page.h to include the generic header
  lib/list.h: add list_add_tail
  lib/vmalloc: add some asserts and improvements
  lib/asm: Fix definitions of memory areas
  lib/alloc_page: fix and improve the page allocator
  lib/alloc.h: remove align_min from struct alloc_ops
  lib/alloc_page: Optimization to skip known empty freelists
  lib/alloc_page: rework metadata format
  lib/alloc: replace areas with more generic flags
  lib/alloc_page: Wire up ZERO_FLAG
  lib/alloc_page: Properly handle requests for fresh blocks
  lib/alloc_page: default flags and zero pages by default

 lib/asm-generic/memory_areas.h |   9 +-
 lib/arm/asm/memory_areas.h     |  11 +-
 lib/arm64/asm/memory_areas.h   |  11 +-
 lib/powerpc/asm/memory_areas.h |  11 +-
 lib/ppc64/asm/memory_areas.h   |  11 +-
 lib/s390x/asm/memory_areas.h   |  13 +-
 lib/x86/asm/memory_areas.h     |  27 +--
 lib/x86/asm/page.h             |   4 +-
 lib/alloc.h                    |   1 -
 lib/alloc_page.h               |  66 ++++++--
 lib/list.h                     |   9 +
 lib/alloc_page.c               | 291 ++++++++++++++++++++-------------
 lib/alloc_phys.c               |   9 +-
 lib/s390x/smp.c                |   2 +-
 lib/vmalloc.c                  |  21 +--
 15 files changed, 286 insertions(+), 210 deletions(-)
```
