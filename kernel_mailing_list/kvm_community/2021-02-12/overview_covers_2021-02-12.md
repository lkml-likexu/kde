

#### [PATCH 0/3] KVM: x86: SVM INVPCID fix, and cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Feb 12 00:34:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12084527
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CD1D1C433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 00:35:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 99D7464E4B
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 00:35:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230263AbhBLAfF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 19:35:05 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56988 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229948AbhBLAez (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 19:34:55 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E3461C061574
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 16:34:14 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id j128so7929340ybc.5
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 16:34:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=mCXu5yp4jt72DPFHwJr3l/cPyL+1tdNvx3HP8ciMZWI=;
        b=RshVkD31psjo3jq+kYicv60lao/jr62jKHN2nE2Km3dgWhxiOFwNwBGR3QLrHh57SW
         woR27bU2e+0N1jGoWbr6rGWZqjU7zbNFtlhpWBZYEFQbiYFr9cwXpxuPD4ah2sdbwOpa
         Hg0bAmmnqLLSSzgfyKCybkVkaD18EEJ7coY3Vu6jbMadehLOHoCuk4Wwo5NbwenkMk5Z
         6FwlZnXstpupgjO3zONOzZeQJ0LTwaXvRSQZp5fEcyq+5wr2NPPQRSD1qtQqjdHRDX4I
         zWdA5LN6UcRjhICwjkqnkVEwycpYvfk+6o6Lu8HMAMvcOrkq4xUY4gWeb84/Lja0XWXt
         rzIg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=mCXu5yp4jt72DPFHwJr3l/cPyL+1tdNvx3HP8ciMZWI=;
        b=uC51NVIn/RKp29pYJfg5msA52rZuMUsuCJYqZ1dS7pzxPqIs81HFpwlTEozDB8+4N9
         UINMxr3M9nqPvT50J5j7l4uDalOUf1UwBo494nkGC9yhMQ3x0eFUPE5bYnsWFnN6Q9H/
         Pinkj0v7Ed79ABZBtCuQerAGbu1UbnNKhhkESOjqkN7RpvlfjUcv0lItXQnWMN+wbiMr
         asrLR7yGtaFCRDyEm3TVCXeMeHz+gwd91z/A71U3fFcfYfT67J0Vazn2EDfwMJc160fL
         xOmj+Oyi7Wv1SnOCXt75wgrWHZmf4yD9KkIlXofl7oE45ULfCdex8jxnal+XxgD81Xd+
         uhvw==
X-Gm-Message-State: AOAM533gWEIQlTQ9jf0TToSsD8KWaTU3EyPeV8yL6QVz8DhaCiEgw7bk
        VQN5XwgTRwNDvc+DaM3+mB7uwzv18QU=
X-Google-Smtp-Source: 
 ABdhPJy7Cv4THKPOAN1VWhlB1DO4+fYemdbGtP0zVuWGIArV8rDPD59/g6CUVkC1S257vurJ/1bme+JFcjo=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f588:a708:f347:3ebb])
 (user=seanjc job=sendgmr) by 2002:a05:6902:706:: with SMTP id
 k6mr757884ybt.52.1613090054147; Thu, 11 Feb 2021 16:34:14 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 11 Feb 2021 16:34:08 -0800
Message-Id: <20210212003411.1102677-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 0/3] KVM: x86: SVM INVPCID fix, and cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Babu Moger <babu.moger@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix an INVPCID bug on SVM where it fails to injected a #UD when INVPCID is
supported but not exposed to the guest.  Do a bit of cleanup in patch 02
now that both VMX and SVM support PCID/INVPCID.

Patch 03 address KVM behavior that has long confused the heck out of me.
KVM currently allows enabling INVPCID if and only if PCID is also enabled
for the guest, the justification being that the guest will see incorrect
fault behavior (#UD instead of #GP) due to the way the VMCS control works.

But that makes no sense, because nothing is forcing KVM to disable INVCPID
in the VMCS when PCID is disabled.  AFACIT, the myth was the result of a
bug in the original _submission_, not even the original _commit_ was buggy.

Digging back, the very original submission had this code, where
vmx_pcid_supported() was further conditioned on EPT being enabled.  This
would lead to the buggy scenario of unexpected #UD, as a host with PCID
and INVCPID would fail to enable INVPCID if EPT was disabled.

> > +	if (vmx_pcid_supported()) {
> > +		exec_control = vmcs_read32(SECONDARY_VM_EXEC_CONTROL);
> > +		if (exec_control & SECONDARY_EXEC_ENABLE_INVPCID) {
> > +			best = kvm_find_cpuid_entry(vcpu, 0x1, 0);
> > +			if (best && (best->ecx & bit(X86_FEATURE_PCID)))
> > +				vmx->invpcid_enabled = true;
> > +			else {
> > +				exec_control &= ~SECONDARY_EXEC_ENABLE_INVPCID;
> > +				vmcs_write32(SECONDARY_VM_EXEC_CONTROL,
> > +						exec_control);
> > +				best = kvm_find_cpuid_entry(vcpu, 0x7, 0);
> > +				best->ecx &= ~bit(X86_FEATURE_INVPCID);
> > +			}
> > +		}
> > +	}

The incorrect behavior is especially problematic now that SVM also
supports INVCPID, as KVM allows !PCID && INVPCID on SVM but not on VMX.

Patches to fix kvm-unit-tests are also incoming...

Sean Christopherson (3):
  KVM: SVM: Intercept INVPCID when it's disabled to inject #UD
  KVM: x86: Advertise INVPCID by default
  KVM: VMX: Allow INVPCID in guest without PCID

 arch/x86/kvm/cpuid.c   |  2 +-
 arch/x86/kvm/svm/svm.c | 11 ++++-------
 arch/x86/kvm/vmx/vmx.c | 14 ++------------
 3 files changed, 7 insertions(+), 20 deletions(-)
```
#### [kvm-unit-tests PATCH 0/4] x86: PCID test adjustments
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Feb 12 01:06:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12084559
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5BD4AC43381
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 01:08:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09B6764E39
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 01:08:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230270AbhBLBHq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 20:07:46 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35718 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230013AbhBLBHJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 20:07:09 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D7EF4C061797
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 17:06:10 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id h192so7914363ybg.23
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 17:06:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=XSE9ZrAc8g6z+kr2mmzp2erRamwsfZu1yo7TcWAeNjo=;
        b=PgAH98OVFY+muhTisqBwkN9mWpeeU4YRWdNAOhVL7M6j9ocfLNArMyMUAlJ+Mb1zpH
         0lJ/lzWXvyocsilDVzTsxmQuRGMQRQlRapBPUC/EtdHrc3UsB/B203t/DNCT+NVYyO9b
         PMMW3ADJF51w6Wr8Mzw9hBqdIgxpN4H5YcXE6bxjug7N3cYJqVdwIls2cYIVd+vGFZcy
         QArm6XFEjpfXOmzJQJzOIzZjGigBEiBHpqD1baBiDafqQN+DnVGIwSQt6ivOhmPG4aRZ
         poej0net+cT78GCzPcJQkuATHptsZLwdgIkjw0cDe4TrjEDWtwQgJa3jh7zO+lzlh4wD
         HkOQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=XSE9ZrAc8g6z+kr2mmzp2erRamwsfZu1yo7TcWAeNjo=;
        b=CYCYcRaDc+Q/jpKJ57NIxF1kEQ65u8B3ArjKKNi632vbA5Qg5aCK2zrJPTRXjeu6xc
         dYmTFW9cIj7aYSRTqJVIpR2EYWx2fHWxsPMdD8UNyeFS6Ok8rwsbfUldQuSOOhlPuCew
         5kP0j/dk1pNIZZCZIy9DwOgFK6BxXXX+1yjhOtkQ8OdSV+t0CGkEEaH7IUMz5iNM3QoT
         138gMKZRBOei0XW1lQXQX3Yqxk8elCi74cEAVW0s1b76R1NdlffEj4ue9hfWzPy8AaBK
         uQRBabUkN9S59s3mB2SneGSoR+n6I6qSJtzrAfCNfzwVbGkWTHe5BoQhNhZfTA9eQWEX
         BMEA==
X-Gm-Message-State: AOAM533ABPbzZph20WL51jEb8xuYMKoeA+RVH1wgPYXwGZRcRlM/ZFmW
        iAXjpUNsY8/C6eyVYbedTHx67iAVWiw=
X-Google-Smtp-Source: 
 ABdhPJwnp9WGWat8xRMUdoap4+ViiSwDKbuBcydP/Bk/jZStDqZmcXtxOP14L2BiPWGnEYjtXJRWhfAbGbk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f588:a708:f347:3ebb])
 (user=seanjc job=sendgmr) by 2002:a05:6902:1d2:: with SMTP id
 u18mr801490ybh.103.1613091970057; Thu, 11 Feb 2021 17:06:10 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 11 Feb 2021 17:06:02 -0800
Message-Id: <20210212010606.1118184-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [kvm-unit-tests PATCH 0/4] x86: PCID test adjustments
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Adjust the PCID test to remove the enforment that INVPCID is enabled iff
PCID is enabled, and add explicit coverage of the newly allowed scneario.

Sean Christopherson (4):
  x86: Remove PCID test that INVPCID isn't enabled without PCID
  x86: Iterate over all INVPCID types in the enabled test
  x86: Add a testcase for !PCID && INVPCID
  x86: Add a 'pcid' group for the various PCID+INVPCID permutations

 x86/pcid.c        | 35 ++++++++++++++++++-----------------
 x86/unittests.cfg | 10 +++++++++-
 2 files changed, 27 insertions(+), 18 deletions(-)
```
#### [PATCH v2 0/1] KVM: s390: diag9c forwarding
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Fri Feb 12 08:39:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12084937
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 560EAC433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 08:41:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 040DB64E56
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 08:41:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230107AbhBLIl0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 03:41:26 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:45620 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S230206AbhBLIk1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Feb 2021 03:40:27 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11C8W6MO156573;
        Fri, 12 Feb 2021 03:39:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=o6cejZ8DmI8Ug6OsLBpPZ6dJclSzOwfRxwbJ2SyiGVQ=;
 b=K7s/4v2O8LIMXcLruOA3tw+fG/2btj9OHM5//tNnrwakJpgJwYYdgaY2O26iQHy0xBZM
 ZC99rTiWDPkJCSwhSYbnXvpVLIpW5QTZzDnvnqo5bFZrrMLcSxTxaVQloJBwhi64XXaG
 +TB3bzBvgxmW61WX9e665Njw4BD3+A2h4rYJBDsj0iZkOLqcavpNNAyDs7TagAhGOU7X
 SElK4kIRai1ggq9OGISh7hq2GJ5WSxPR1Oh3s9WDb7IsxfrlHY2gGswapHFF+YpeUa/3
 vLevsUWjYNSgPx7hIQuLGLvPKEfMWE5jCApKgBrh2O7S6Lnl3O8D2z/Dl1A6YcMfxE9a Dg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36nnbq2229-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Feb 2021 03:39:43 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11C8WQtZ158399;
        Fri, 12 Feb 2021 03:39:43 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36nnbq2212-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Feb 2021 03:39:43 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11C8bYEr004263;
        Fri, 12 Feb 2021 08:39:41 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06ams.nl.ibm.com with ESMTP id 36j94wnr8a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Feb 2021 08:39:41 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11C8dRY834275794
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 12 Feb 2021 08:39:28 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 432AF42041;
        Fri, 12 Feb 2021 08:39:38 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C6C664203F;
        Fri, 12 Feb 2021 08:39:37 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.28.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 12 Feb 2021 08:39:37 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, cohuck@redhat.com, david@redhat.com,
        thuth@redhat.com, pmorel@linux.ibm.com
Subject: [PATCH v2 0/1] KVM: s390: diag9c forwarding
Date: Fri, 12 Feb 2021 09:39:35 +0100
Message-Id: <1613119176-20864-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-12_02:2021-02-12,2021-02-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 phishscore=0
 clxscore=1015 impostorscore=0 mlxscore=0 lowpriorityscore=0 spamscore=0
 bulkscore=0 suspectscore=0 mlxlogscore=953 priorityscore=1501 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2102120060
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch will forward the yieldto hypercall (diag9c) if in the host
the target CPU is also not running. As we do not yet have performance
data (and recommendations) the default is turned off, but this can
be changed during runtime.

Pierre Morel (1):
  s390:kvm: diag9c forwarding

 Documentation/virt/kvm/s390-diag.rst | 33 ++++++++++++++++++++++++++++
 arch/s390/include/asm/kvm_host.h     |  1 +
 arch/s390/include/asm/smp.h          |  1 +
 arch/s390/kernel/smp.c               |  1 +
 arch/s390/kvm/diag.c                 | 31 +++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c             |  6 +++++
 arch/s390/kvm/kvm-s390.h             |  8 +++++++
 7 files changed, 78 insertions(+), 3 deletions(-)
```
#### [PATCH 0/3] vfio: Device memory DMA mapping improvements
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Fri Feb 12 19:27:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12085975
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11044C433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 19:29:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFF9764E05
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 19:29:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231317AbhBLT27 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 14:28:59 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:58388 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229451AbhBLT25 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Feb 2021 14:28:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613158051;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=SmXdhYbUwFwSJYJWGAUkTJ3lEIS/O65yIUkUv4tH8U0=;
        b=PcRH+tD2GlQzWXafnbwHVPa7nqeKG1QZFUBxo3JXbTK2XiMvahQv7WO8NtvtInRMKO2izV
        oB4JmbLIG5lOTJCBtcsMO6Cq9oyEE+aW+fjcrAhGrWUkZrk5jjIubCCBzZXyXm27zThWS6
        GRgI2JbaNymjuATDZiVjgW3vZhU9FQ0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-316-tcLrF6fIMReCvCKocU0IpQ-1; Fri, 12 Feb 2021 14:27:28 -0500
X-MC-Unique: tcLrF6fIMReCvCKocU0IpQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6722A1934104;
        Fri, 12 Feb 2021 19:27:27 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A85F210502;
        Fri, 12 Feb 2021 19:27:20 +0000 (UTC)
Subject: [PATCH 0/3] vfio: Device memory DMA mapping improvements
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jgg@nvidia.com, peterx@redhat.com
Date: Fri, 12 Feb 2021 12:27:19 -0700
Message-ID: <161315658638.7320.9686203003395567745.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to improve some long standing issues with mapping
device memory through the vfio IOMMU interface (ie. P2P DMA mappings).
Unlike mapping DMA to RAM, we can't pin device memory, nor is it
always accessible.  We attempt to tackle this (predominantly the
first issue in this iteration) by creating a registration and
notification interface through vfio-core, between the IOMMU backend
and the bus driver.  This allows us to do things like automatically
remove a DMA mapping to device if it's closed by the user.  We also
keep references to the device container such that it remains isolated
while this mapping exists.

Unlike my previous attempt[1], this version works across containers.
For example if a user has device1 with IOMMU context in container1
and device2 in container2, a mapping of device2 memory into container1
IOMMU context would be removed when device2 is released.

What I don't tackle here is when device memory is disabled, such as
for a PCI device when the command register memory bit is cleared or
while the device is in reset.  Ideally is seems like it might be
nice to have IOMMU API interfaces that could remove r/w permissions
from the IOTLB entry w/o removing it entirely, but I'm also unsure
of the ultimate value in modifying the IOTLB entries at this point.

In the PCI example again, I'd expect a DMA to disabled or unavailable
device memory to get an Unsupported Request response.  If we play
with the IOTLB mapping, we might change this to an IOMMU fault for
either page permissions or page not present, depending on how we
choose to invalidate that entry.  However, it seems that a system that
escalates an UR error to fatal, through things like firmware first
handling, is just as likely to also make the IOMMU fault fatal.  Are
there cases where we expect otherwise, and if not is there value to
tracking device memory enable state to that extent in the IOMMU?

Jason, I'm also curious if this scratches your itch relative to your
suggestion to solve this with dma-bufs, and if that's still your
preference, I'd love an outline to accomplish this same with that
method.

Thanks,
Alex

[1]https://lore.kernel.org/kvm/158947414729.12590.4345248265094886807.stgit@gimli.home/
---

Alex Williamson (3):
      vfio: Introduce vma ops registration and notifier
      vfio/pci: Implement vm_ops registration
      vfio/type1: Implement vma registration and restriction


 drivers/vfio/pci/Kconfig            |    1 
 drivers/vfio/pci/vfio_pci.c         |   87 ++++++++++++++++
 drivers/vfio/pci/vfio_pci_private.h |    1 
 drivers/vfio/vfio.c                 |  120 ++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c     |  192 ++++++++++++++++++++++++++++-------
 include/linux/vfio.h                |   20 ++++
 6 files changed, 384 insertions(+), 37 deletions(-)
```
