

#### [PATCH v3 0/8] s390x/vfio-ccw: Channel Path Handling [KVM]
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Fri Apr 17 02:29:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11494019
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EADC8112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 02:30:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA8D921D93
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 02:30:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729338AbgDQCaL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 22:30:11 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:41906 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729250AbgDQCaK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 22:30:10 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03H2CCHi144096
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 22:30:08 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30f3f4gacg-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 22:30:08 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Fri, 17 Apr 2020 03:29:27 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 17 Apr 2020 03:29:25 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03H2Sugf48562642
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Apr 2020 02:28:56 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3A21A11C04A;
        Fri, 17 Apr 2020 02:30:02 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2739911C058;
        Fri, 17 Apr 2020 02:30:02 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 17 Apr 2020 02:30:02 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id AF636E026B; Fri, 17 Apr 2020 04:30:01 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v3 0/8] s390x/vfio-ccw: Channel Path Handling [KVM]
Date: Fri, 17 Apr 2020 04:29:53 +0200
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20041702-0016-0000-0000-00000305EC9C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20041702-0017-0000-0000-00003369F36A
Message-Id: <20200417023001.65006-1-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-16_10:2020-04-14,2020-04-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 mlxscore=0 mlxlogscore=870 bulkscore=0 spamscore=0
 phishscore=0 malwarescore=0 clxscore=1015 suspectscore=0 impostorscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004170010
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here is a new pass at the channel-path handling code for vfio-ccw.
Changes from previous versions are recorded in git notes for each patch.

I dropped the "Remove inline get_schid()" patch from this version.
When I made the change suggested in v2, it seemed rather frivolous and
better to just drop it for the time being.

I suspect that patches 5 and 7 would be better squashed together, but I
have not done that here.  For future versions, I guess.

With this, and the corresponding QEMU series (to be posted momentarily),
applied I am able to configure off/on a CHPID (for example, by issuing
"chchp -c 0/1 xx" on the host), and the guest is able to see both the
events and reflect the updated path masks in its structures.

v2: https://lore.kernel.org/kvm/20200206213825.11444-1-farman@linux.ibm.com/
v1: https://lore.kernel.org/kvm/20191115025620.19593-1-farman@linux.ibm.com/

Eric Farman (3):
  vfio-ccw: Refactor the unregister of the async regions
  vfio-ccw: Refactor IRQ handlers
  vfio-ccw: Add trace for CRW event

Farhan Ali (5):
  vfio-ccw: Introduce new helper functions to free/destroy regions
  vfio-ccw: Register a chp_event callback for vfio-ccw
  vfio-ccw: Introduce a new schib region
  vfio-ccw: Introduce a new CRW region
  vfio-ccw: Wire up the CRW irq and CRW region

 Documentation/s390/vfio-ccw.rst     |  35 +++++-
 drivers/s390/cio/Makefile           |   2 +-
 drivers/s390/cio/vfio_ccw_chp.c     | 148 +++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_drv.c     | 163 ++++++++++++++++++++++++++--
 drivers/s390/cio/vfio_ccw_ops.c     |  65 ++++++++---
 drivers/s390/cio/vfio_ccw_private.h |  16 +++
 drivers/s390/cio/vfio_ccw_trace.c   |   1 +
 drivers/s390/cio/vfio_ccw_trace.h   |  30 +++++
 include/uapi/linux/vfio.h           |   3 +
 include/uapi/linux/vfio_ccw.h       |  18 +++
 10 files changed, 453 insertions(+), 28 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_chp.c
```
#### [PATCH v2 0/6] KVM: arm: vgic fixes for 5.7
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Apr 17 08:33:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11494457
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9562913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 08:33:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C924D221F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 08:33:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587112418;
	bh=ow4RCTCsHairYh31RKkXUJ67Orlffoz/KgRIiU9/xD0=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=dnj/YnEE6ZRtdDxoNqfG0n62AiItax3ws1A07iRrdaVHretymik7pZBSxuhgYT9jT
	 0up+sBEc7+bS9g7k0/I2Ls8Y8e4cNreiEXp82pKH4M4m2gABpE4zpLB/kYoBBsgbSN
	 YJxQz6NYoUNCWa0GM6gLR7Cvd9L0ihEkvpoilQ2U=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729755AbgDQIdi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 04:33:38 -0400
Received: from mail.kernel.org ([198.145.29.99]:59312 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729166AbgDQIdh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Apr 2020 04:33:37 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 03FC22137B;
        Fri, 17 Apr 2020 08:33:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587112417;
        bh=ow4RCTCsHairYh31RKkXUJ67Orlffoz/KgRIiU9/xD0=;
        h=From:To:Cc:Subject:Date:From;
        b=AUYZg2TH0dZxNaOepILkxW+Ra012+kuvwrSXHloeyp4ALuW9GUq7t7hjc8bhCVi4c
         WBWhdY5bBSg/xFSQJxvaF4KuGC1220VTm0NzW4sm3XRWzoAeoaYvbEs9+AG7w+/PCp
         9cVVbvmAJlCdEIR34eUSduigKNatkMPUkXlFgHTc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jPMRL-00473f-4u; Fri, 17 Apr 2020 09:33:35 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        Andre Przywara <Andre.Przywara@arm.com>,
        Julien Grall <julien@xen.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v2 0/6] KVM: arm: vgic fixes for 5.7
Date: Fri, 17 Apr 2020 09:33:13 +0100
Message-Id: <20200417083319.3066217-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, yuzenghui@huawei.com,
 eric.auger@redhat.com, Andre.Przywara@arm.com, julien@xen.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here's a few vgic fixes I've been piling on during the merge window,
plus a couple that Zenghui contributed, and which I added to the mix.

The first patch is a silly off-by-one bug in the ACTIVE handling code,
where we miss fail to stop the guest if writing to the first set of
GICv2 SPIs. Oopsie boo.

The second patch improves the handling of the ACTIVE registers, which
we never synchronise on the read side (the distributor state can only
be updated when the vcpu exits). Let's fix it the same way we do it on
the write side (stop-the-world, read, restart). Yes, this is
expensive.

The following two patches deal with an issue where we consider the HW
state of an interrupt when responding to a userspace access. We should
never do this, as the guest shouldn't be running at this stage and if
it is, it is absolutely fine to return random bits to userspace. It
could also be that there is no active guest context at this stage, and
you end up with an Oops, which nobody really enjoys.

The last two patches fix a couple of memory leaks.

Marc Zyngier (4):
  KVM: arm: vgic: Fix limit condition when writing to GICD_I[CS]ACTIVER
  KVM: arm: vgic: Synchronize the whole guest on GIC{D,R}_I{S,C}ACTIVER
    read
  KVM: arm: vgic: Only use the virtual state when userspace accesses
    enable bits
  KVM: arm: vgic-v2: Only use the virtual state when userspace accesses
    pending bits

Zenghui Yu (2):
  KVM: arm64: vgic-v3: Retire all pending LPIs on vcpu destroy
  KVM: arm64: vgic-its: Fix memory leak on the error path of
    vgic_add_lpi()

 virt/kvm/arm/vgic/vgic-init.c    |   6 +
 virt/kvm/arm/vgic/vgic-its.c     |  11 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c |  16 ++-
 virt/kvm/arm/vgic/vgic-mmio-v3.c |  28 +++--
 virt/kvm/arm/vgic/vgic-mmio.c    | 183 +++++++++++++++++++++++++------
 virt/kvm/arm/vgic/vgic-mmio.h    |  19 ++++
 6 files changed, 207 insertions(+), 56 deletions(-)
```
#### [PATCH 0/2] KVM: fix set_memory_region_test on AMD
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Apr 17 16:38:41 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11495569
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D618F912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:38:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BECEC20780
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:38:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RczFRMmC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726459AbgDQQis (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 12:38:48 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:49119 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726372AbgDQQir (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Apr 2020 12:38:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587141526;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=V7W+fUTy17m2U7Vvai/9OLLIkPQEcn4WJeVrBwLoseU=;
        b=RczFRMmC1ti2j27jwyEijWrNV/VrHdmwnI++sc3pB9jAAKmUvHH+xs1TEi/unZr422PaLr
        buPlwRHgGUGHUXHX+qaqwBOjglBwI4Js42SCGWmeAp0xFvkjh1UnPPF8iE2u6IlAOeb6NG
        iMfJxDC6mD/bW+307NixllnFJ4OBkZ4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-97-7z7eowszM7abL1uDXzgRMg-1; Fri, 17 Apr 2020 12:38:45 -0400
X-MC-Unique: 7z7eowszM7abL1uDXzgRMg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F0F9D8024D4;
        Fri, 17 Apr 2020 16:38:43 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 978B55DA84;
        Fri, 17 Apr 2020 16:38:43 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 0/2] KVM: fix set_memory_region_test on AMD
Date: Fri, 17 Apr 2020 12:38:41 -0400
Message-Id: <20200417163843.71624-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The set_memory_region_test selftest is failing on AMD machines, this
series fixes two bugs in it.

Paolo Bonzini (2):
  KVM: SVM: avoid infinite loop on NPF from bad address
  selftests: kvm/set_memory_region_test: do not check RIP if the guest
    shuts down

 arch/x86/kvm/svm/svm.c                              |  7 +++++++
 .../testing/selftests/kvm/set_memory_region_test.c  | 13 +++++++++----
 virt/kvm/kvm_main.c                                 |  1 +
 3 files changed, 17 insertions(+), 4 deletions(-)
```
#### [PATCH 0/3] KVM: x86: move nested-related kvm_x86_ops to a separate
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Apr 17 16:44:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11495581
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6B78913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:44:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCE5222202
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:44:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PzpfaCEA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726775AbgDQQos (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 12:44:48 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:26408 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726694AbgDQQos (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Apr 2020 12:44:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587141887;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=FFr7Xpb7/1UqdoZBjTKNeIgRsFQa+LGb0mOrrAFMJFY=;
        b=PzpfaCEAnd4iBWwWnxx3RiNb7pvLnsO7Vno4qQCv8xQRjl35xzn+WJuy6nJa2J7Ct36LSb
        PlOIz5V50pQOd2oSvpEqmzU+xG7PvDz4tg+hKZ0PBBPckjIDjma+ViJ/57ktvZHILqKwO/
        lSctwX5Rne7Zir12nXV0jrTpW34SmYE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-433-uWHtHPv_NXmCRHfLaDQP3g-1; Fri, 17 Apr 2020 12:44:45 -0400
X-MC-Unique: uWHtHPv_NXmCRHfLaDQP3g-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 89D2B1934100;
        Fri, 17 Apr 2020 16:44:14 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 007331001920;
        Fri, 17 Apr 2020 16:44:13 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH 0/3] KVM: x86: move nested-related kvm_x86_ops to a separate
 struct
Date: Fri, 17 Apr 2020 12:44:10 -0400
Message-Id: <20200417164413.71885-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 3 follows the lead of the kvm_pmu_ops and moves callbacks related
to nested virtualization to a separate struct.  Patches 1 and 2 are
preparation (patch 1 mostly makes some lines shorter, while patch 2
avoids semantic changes in KVM_GET_SUPPORTED_HV_CPUID).

While this reintroduces some pointer chasing that was removed in
afaf0b2f9b80 ("KVM: x86: Copy kvm_x86_ops by value to eliminate layer
of indirection", 2020-03-31), the cost is small compared to retpolines
and anyway most of the callbacks are not even remotely on a fastpath.
In fact, only check_nested_events should be called during normal VM
runtime.  When static calls are merged into Linux my plan is to use them
instead of callbacks, and that will finally make things fast again by
removing the retpolines.

Thanks,

Paolo

Paolo Bonzini (3):
  KVM: x86: check_nested_events is never NULL
  KVM: eVMCS: check if nesting is enabled
  KVM: x86: move nested-related kvm_x86_ops to a separate struct

 arch/x86/include/asm/kvm_host.h | 29 +++++++++++++++-------------
 arch/x86/kvm/hyperv.c           |  4 ++--
 arch/x86/kvm/svm/nested.c       |  6 +++++-
 arch/x86/kvm/svm/svm.c          | 13 +++++--------
 arch/x86/kvm/svm/svm.h          |  3 ++-
 arch/x86/kvm/vmx/evmcs.c        |  4 +++-
 arch/x86/kvm/vmx/nested.c       | 16 +++++++++-------
 arch/x86/kvm/vmx/nested.h       |  2 ++
 arch/x86/kvm/vmx/vmx.c          |  7 +------
 arch/x86/kvm/x86.c              | 34 ++++++++++++++++-----------------
 10 files changed, 62 insertions(+), 56 deletions(-)
```
#### [PATCH 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
From patchwork Fri Apr 17 18:29:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11495899
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 53BBA912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:27:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A8742223C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:27:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730611AbgDQS13 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 14:27:29 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:36778 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730256AbgDQS12 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 14:27:28 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03HI3P1X066209;
        Fri, 17 Apr 2020 14:27:28 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30fe1pyfyk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Apr 2020 14:27:28 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03HI4GrO069361;
        Fri, 17 Apr 2020 14:27:27 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30fe1pyfy7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Apr 2020 14:27:27 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03HIPnij021481;
        Fri, 17 Apr 2020 18:27:26 GMT
Received: from b01cxnp22034.gho.pok.ibm.com (b01cxnp22034.gho.pok.ibm.com
 [9.57.198.24])
        by ppma02dal.us.ibm.com with ESMTP id 30b5h7scy4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Apr 2020 18:27:26 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp22034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 03HIRQe539846214
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Apr 2020 18:27:26 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DE49AAE05C;
        Fri, 17 Apr 2020 18:27:25 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 98712AE063;
        Fri, 17 Apr 2020 18:27:25 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.151.210])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri, 17 Apr 2020 18:27:25 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Fri, 17 Apr 2020 14:29:38 -0400
Message-Id: <20200417182939.11460-1-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-17_08:2020-04-17,2020-04-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 mlxlogscore=693
 mlxscore=0 lowpriorityscore=0 priorityscore=1501 phishscore=0
 malwarescore=0 spamscore=0 impostorscore=0 clxscore=1011 suspectscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004170141
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check is not needed as all Linux channel programs are intended
to use prefetch and will be executed in the same way regardless.

Jared Rossi (1):
  vfio-ccw: Enable transparent CCW IPL from DASD

 drivers/s390/cio/vfio_ccw_cp.c  | 16 ++++------------
 drivers/s390/cio/vfio_ccw_cp.h  |  2 +-
 drivers/s390/cio/vfio_ccw_fsm.c |  6 +++---
 3 files changed, 8 insertions(+), 16 deletions(-)
```
#### [kvm PATCH 0/2] *** Enable VMX preemption timer migration ***
##### From: Makarand Sonare <makarandsonare@google.com>

```c
From patchwork Fri Apr 17 18:34:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11495927
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFFAF912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:35:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B5AF420780
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:35:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="saLskT3+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728189AbgDQSfF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 14:35:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45286 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726750AbgDQSfE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 14:35:04 -0400
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C1092C061A0C
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 11:35:04 -0700 (PDT)
Received: by mail-pf1-x44a.google.com with SMTP id t3so2728151pfd.5
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 11:35:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=10I06/r4iTnXuchMXI1U1SbADc47sHPNKITtLRQr7RA=;
        b=saLskT3+VVd25bTiJd4nN31vp+/BCCchUNT6BXsEaSltmwOLaytJWTUvOexw6uds1i
         KZ7796FcfscXYt7WOGeVlEyg+4siioMRbDMvZzsCCFBzV/aNyX7lEY1YUulz3ve/OMe6
         2fHBzCPOvybv3DP8Yy9rGXLvzb6XMFH2Nquf9GX58+PSFRIZvOeiXXiGkBjChYyXMXdf
         16p37jv4JFYe6+WStBLwKh4r66rQ4SldTXQ1SCGRSwdo5fXDEzHhAIZhEC5zeqg5nTrK
         vcERhtaaPlZ602Ah0r5qYRjQC8FP1TXstZUMjLtavd+fJz3tZrsOSACjggDbcX71wc1X
         06/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=10I06/r4iTnXuchMXI1U1SbADc47sHPNKITtLRQr7RA=;
        b=Cnpu4BB5cmraAfua85soHxbO2/uyRR8YInAy9atqhMM9llcN19uBUCLfWL6DesOLqV
         wdBjUm6WaRC1o/K22oaGzyfrDCCMfCT9GM/9SyFdTQJ1SzD4EafXdMg2bHGQbnkqVRy9
         17nZmmNGZFmEDP+/tMTkG77MH4/hQgN7Z/n25Frmwl2Pmz7cSLVzdoJaszi4t5N3/Lc8
         ZNpbbHRaboBXbLIpwAuwqXA/3PjGdhqySpDhSv7TV6t/PIo6f26zA17Z42EGPzTMmbyo
         hEvZSQUw6J4WjNmz1ih7hyFyHxwk1sQ3Nj7HS97Xv3F2G7Fgcx6svzqCuVaAjopZrkMe
         HyCQ==
X-Gm-Message-State: AGi0Pua68rPhHEQwmJXlV5OgBYmTPgmch/srWvr3Jqkg16r6DlQLHIvI
        MK/0uwAuNZtNHqlrUc3nwJJjCjM9M/zpIp8WaDHy9HGSocxlX96uGclU65a4I8aiKiPpNPEV5SK
        IS0HQFAiRO/GY++mU5GtcMh3R//SFPxOuD8jrITok6N+sXTmx5FT3qIdNXbYhk2gBXnK0GRdutF
        hR43s=
X-Google-Smtp-Source: 
 APiQypK+ejrOVqpVq6jHDAWtC597DDwBUuk7xHj60xEd6jyuBeP78cAPpr3y+uUSldVXnesTc56rIh9btjg0Y/llD8U1LQ==
X-Received: by 2002:a17:90b:2388:: with SMTP id
 mr8mr5502296pjb.97.1587148504158;
 Fri, 17 Apr 2020 11:35:04 -0700 (PDT)
Date: Fri, 17 Apr 2020 11:34:50 -0700
Message-Id: <20200417183452.115762-1-makarandsonare@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [kvm PATCH 0/2] *** Enable VMX preemption timer migration ***
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

*** BLURB HERE ***

Makarand Sonare (1):
  KVM: nVMX: Don't clobber preemption timer in the VMCS12 before L2 ran

Peter Shier (1):
  KVM: nVMX - enable VMX preemption timer migration

 Documentation/virt/kvm/api.rst        |  4 ++
 arch/x86/include/uapi/asm/kvm.h       |  2 +
 arch/x86/kvm/vmx/nested.c             | 64 +++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.h                |  1 +
 arch/x86/kvm/x86.c                    |  1 +
 include/uapi/linux/kvm.h              |  1 +
 tools/arch/x86/include/uapi/asm/kvm.h |  2 +
 7 files changed, 67 insertions(+), 8 deletions(-)
---
2.26.1.301.g55bc3eb7cb9-goog
```
