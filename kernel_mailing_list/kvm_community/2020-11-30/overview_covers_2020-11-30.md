

#### [PATCH 0/2] RFC: Precise TSC migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Nov 30 13:35:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11940567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C1AE9C71156
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:37:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67DAE2084C
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:37:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PwtM3134"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727105AbgK3Nho (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 08:37:44 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:35470 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727033AbgK3Nhn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Nov 2020 08:37:43 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606743377;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JaI15Fwv38N9n7wxFz/5+sDT0HAIaiSWwhif2Atz1Yc=;
        b=PwtM3134C40LSexFIBNXvHoDHzNooHIDUxg3FMAltcZR6yjm2FrVP0933nB2CgsnI6rpA5
        JuE+2qXfA2UxE3yCE5Jakh3xEdyTexozxPt/Ex4cqKCfoFKixQHuLJErybPSRzV2cnIGVR
        lFKnkrVo+fQ+OckPpsDb1laTQnqtckk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-444-9NiJFdElNYeSCtULP1O3pw-1; Mon, 30 Nov 2020 08:36:13 -0500
X-MC-Unique: 9NiJFdElNYeSCtULP1O3pw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 32FEA8144E0;
        Mon, 30 Nov 2020 13:36:11 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.90])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E6F3860C62;
        Mon, 30 Nov 2020 13:36:00 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org (open list),
        Marcelo Tosatti <mtosatti@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] RFC: Precise TSC migration
Date: Mon, 30 Nov 2020 15:35:57 +0200
Message-Id: <20201130133559.233242-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

This is the first version of the work to make TSC migration more accurate,
as was defined by Paulo at:
https://www.spinics.net/lists/kvm/msg225525.html

I have a few thoughts about the kvm masterclock synchronization,
which relate to the Paulo's proposal that I implemented.

The idea of masterclock is that when the host TSC is synchronized
(or as kernel call it, stable), and the guest TSC is synchronized as well,
then we can base the kvmclock, on the same pair of
(host time in nsec, host tsc value), for all vCPUs.

This makes the random error in calculation of this value invariant
across vCPUS, and allows the guest to do kvmclock calculation in userspace
(vDSO) since kvmclock parameters are vCPU invariant.

To ensure that the guest tsc is synchronized we currently track host/guest tsc
writes, and enable the master clock only when roughly the same guest's TSC value
was written across all vCPUs.

Recently this was disabled by Paulo and I agree with this, because I think
that we indeed should only make the guest TSC synchronized by default
(including new hotplugged vCPUs) and not do any tsc synchronization beyond that.
(Trying to guess when the guest syncs the TSC can cause more harm that good).

Besides, Linux guests don't sync the TSC via IA32_TSC write,
but rather use IA32_TSC_ADJUST which currently doesn't participate
in the tsc sync heruistics.
And as far as I know, Linux guest is the primary (only?) user of the kvmclock.

I *do think* however that we should redefine KVM_CLOCK_TSC_STABLE
in the documentation to state that it only guarantees invariance if the guest
doesn't mess with its own TSC.

Also I think we should consider enabling the X86_FEATURE_TSC_RELIABLE
in the guest kernel, when kvm is detected to avoid the guest even from trying
to sync TSC on newly hotplugged vCPUs.

(The guest doesn't end up touching TSC_ADJUST usually, but it still might
in some cases due to scheduling of guest vCPUs)

(X86_FEATURE_TSC_RELIABLE short circuits tsc synchronization on CPU hotplug,
and TSC clocksource watchdog, and the later we might want to keep).

For host TSC writes, just as Paulo proposed we can still do the tsc sync,
unless the new code that I implemented is in use.

Few more random notes:

I have a weird feeling about using 'nsec since 1 January 1970'.
Common sense is telling me that a 64 bit value can hold about 580 years,
but still I see that it is more common to use timespec which is a (sec,nsec) pair.

I feel that 'kvm_get_walltime' that I added is a bit of a hack.
Some refactoring might improve things here.

For example making kvm_get_walltime_and_clockread work in non tsc case as well
might make the code cleaner.

Patches to enable this feature in qemu are in process of being sent to
qemu-devel mailing list.

Best regards,
       Maxim Levitsky

Maxim Levitsky (2):
  KVM: x86: implement KVM_SET_TSC_PRECISE/KVM_GET_TSC_PRECISE
  KVM: x86: introduce KVM_X86_QUIRK_TSC_HOST_ACCESS

 Documentation/virt/kvm/api.rst  | 56 +++++++++++++++++++++
 arch/x86/include/uapi/asm/kvm.h |  1 +
 arch/x86/kvm/x86.c              | 88 +++++++++++++++++++++++++++++++--
 include/uapi/linux/kvm.h        | 14 ++++++
 4 files changed, 154 insertions(+), 5 deletions(-)
```
#### [PATCH 0/2] RFC: Precise TSC migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Mon Nov 30 13:38:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11940573
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 83631C64E8A
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:40:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 261AF20643
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 13:40:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MR483c4X"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727301AbgK3NkX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 08:40:23 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:59388 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726960AbgK3NkW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Nov 2020 08:40:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1606743536;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=5sWo7oHI2vIdCqH/ZBIudC4hEIMfpuKFF5jtRagIg90=;
        b=MR483c4XTRPtaa1lXunZShYKyoegJ2znJilbCvJOCyEciTussSo/JPM7rmRAphqgE++5UB
        PBMyzbSwgme6Ho3uBk8tLkSr7BBiHhGyvSGlwBq5nck3vXxT6ga4iyW3LDxKVhPXNb7s4V
        yBmUTfCNoLpdEEInp+c85X0h46QxBR0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-324-WK7D0nzVMpySt2bDnigDVA-1; Mon, 30 Nov 2020 08:38:54 -0500
X-MC-Unique: WK7D0nzVMpySt2bDnigDVA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AFCDB805BE0;
        Mon, 30 Nov 2020 13:38:53 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.90])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E2D5760867;
        Mon, 30 Nov 2020 13:38:46 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <richard.henderson@linaro.org>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] RFC: Precise TSC migration
Date: Mon, 30 Nov 2020 15:38:43 +0200
Message-Id: <20201130133845.233552-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note that to use this feature you need the kernel patches which are
posted to LKML and kvm@vger.kernel.org

Currently the feature is disabled by default, and enabled with
x-precise-tsc cpu feature.

Also I changed the TSC and TSC adjust read/write code to go though a special
function kvm_get_tsc/kvm_set_tsc regardless of enablement of this feature.

The side effect of this is that now we upload to the kernel the TSC_ADJUST
msr only on KVM_PUT_RESET_STATE reset level.
This shouldn't matter as I don't think that qemu changes this msr on its own.

For migration I added new state field 'tsc_nsec_info', where I save the
'nsec since epoch' timestamp, which is the only new thing that was added to the
migration state.

First patch in this series is temporary and it just updates the kernel
headers to make qemu compile.

When the feature is merged to the kernel, a kernel header sync will bring
the same changes to the qemu, making this patch unnecessary.

Best regards,
    Maxim Levitsky

Maxim Levitsky (2):
  Update the kernel headers for 5.10-rc5 + TSC
  Implement support for precise TSC migration

 include/standard-headers/asm-x86/kvm_para.h |   1 +
 linux-headers/asm-x86/kvm.h                 |   2 +
 linux-headers/linux/kvm.h                   |  70 +++++++++-
 target/i386/cpu.c                           |   1 +
 target/i386/cpu.h                           |   4 +
 target/i386/kvm.c                           | 141 ++++++++++++++++----
 target/i386/machine.c                       |  20 +++
 7 files changed, 211 insertions(+), 28 deletions(-)
```
#### [PATCH 0/2 v3] KVM: nSVM: Check reserved values for 'Type' and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Nov 30 22:53:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11941453
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61391C71155
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 22:56:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14E5B2076C
	for <kvm@archiver.kernel.org>; Mon, 30 Nov 2020 22:56:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Jl8Ac1LT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388052AbgK3W4A (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 17:56:00 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:34802 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730857AbgK3W4A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Nov 2020 17:56:00 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AUMcsel171270;
        Mon, 30 Nov 2020 22:55:16 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=oyWjxkrHuqfLKrcgjwyTjeeBCvz6gVxbR5c8SxNaFvM=;
 b=Jl8Ac1LTRh8wOh2Y39a1uv0vhPiNHBCwnjAMt4R5GcFo25Lc4+0ffzZOOSAYOM3eNLRc
 S64svPO188trfoo9HR6oSpu2dF6lT5f7m1L4zP51s3IjMRjS3qBEZJymh3AaSU7MvQDj
 IueISE6bgAIFQ3Yd8/ndrUIY+9LiuyfBDnVSHA9DIFpLWSCUzzYbXvcabVmEhJPxDiYH
 GvG9gB+yL2Mcnr0M/WvOjFpBfb2soyj4zWCkvMjy//7rkF9HSUIhWhIM+aRZsCEkqk5+
 n0XThKqa1363TlakW7o0J3DqZ034IZNAxKCVPXqmCtF0GAwYbGqlpUjKXTMFR4y1QJ/M fg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 353c2aqvy5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 30 Nov 2020 22:55:16 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AUMfItj185798;
        Mon, 30 Nov 2020 22:53:15 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 3540fvwe9a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Nov 2020 22:53:15 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0AUMrEOB026955;
        Mon, 30 Nov 2020 22:53:14 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 30 Nov 2020 14:53:14 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/2 v3] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Mon, 30 Nov 2020 22:53:04 +0000
Message-Id: <20201130225306.15075-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9821
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 suspectscore=1
 phishscore=0 mlxlogscore=845 adultscore=0 mlxscore=0 bulkscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011300141
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9821
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 lowpriorityscore=0
 clxscore=1015 bulkscore=0 mlxlogscore=857 phishscore=0 malwarescore=0
 spamscore=0 adultscore=0 mlxscore=0 priorityscore=1501 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011300141
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2 -> v3:
	1. Rebased to kvm.git's nested-svm branch.
	2. Simplied bracing in patch# 1.


According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2,

    VMRUN exits with VMEXIT_INVALID error code if either:
      - Reserved values of TYPE have been specified, or
      - TYPE = 3 (exception) has been specified with a vector that does not
	correspond to an exception (this includes vector 2, which is an NMI,
	not an exception).

Patch# 1 adds these checks to KVM.
Patch# 2 adds tests for these checks.


[PATCH 1/2 v3] KVM: nSVM: Check reserved values for 'Type' and invalid
[PATCH 2/2 v3] nSVM: Test reserved values for 'Type' and invalid vectors in

 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

Krish Sadhukhan (1):
      KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ

 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

Krish Sadhukhan (1):
      nSVM: Test reserved values for 'Type' and invalid vectors in EVENTINJ
```
