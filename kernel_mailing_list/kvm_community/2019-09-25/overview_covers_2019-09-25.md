

#### [PATCH 0/5] arm64: KVM: Add workaround for errata 1319367 and 1319537
##### From: Marc Zyngier <maz@kernel.org>

```c
From patchwork Wed Sep 25 11:19:36 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11160451
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 704521709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 11:19:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4443121D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 11:19:57 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1569410397;
	bh=87PQvrUP9H9IHcIyzFEMvU+vHO6KPy65fWLTapdtfAk=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=Oyuww7/XdxQebR1mCM/VSkRwiQqjvuWxXlXjulJq00koH/m+bhONe+fBzDc4QWZrc
	 pzDRAfbNWEejPkjwe+djr33TlV6TboSg6YzF7PAUM6gWl3gJf0mbqnwQJY+CTxuLgZ
	 sLDnuHedxD0UR535Fiuv5sWDK2z2dU11HjDnDR3c=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732154AbfIYLT4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 07:19:56 -0400
Received: from foss.arm.com ([217.140.110.172]:46854 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725913AbfIYLT4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 07:19:56 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 825A71570;
        Wed, 25 Sep 2019 04:19:55 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 49A813F694;
        Wed, 25 Sep 2019 04:19:54 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Subject: [PATCH 0/5] arm64: KVM: Add workaround for errata 1319367 and 1319537
Date: Wed, 25 Sep 2019 12:19:36 +0100
Message-Id: <20190925111941.88103-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Similarily to erratum 1165522 that affects Cortex-A76, our good old
friends A57 and A72 respectively suffer from errata 1319367 and
1319537, potentially resulting in TLB corruption if the CPU speculates
an AT instruction while switching guests.

The fix is slightly more involved since we don't have VHE to help us
here, but the idea is the same: When switching a guest in, we must
prevent any speculated AT from being able to parse the page tables
until S2 is up and running. Only at this stage can we allow AT to take
place.

For this, we always restore the guest sysregs first, except for its
SCTLR and TCR registers, which must be set with SCTLR.M=1 and
TCR.EPD{0,1} = {1, 1}, effectively disabling the PTW and TLB
allocation. Once S2 is setup, we restore the guest's SCTLR and
TCR. Similar things must be done on TLB invalidation... Fun.

This has been tested on an AMD Seattle box.

Marc Zyngier (5):
  arm64: Add ARM64_WORKAROUND_1319367 for all A57 and A72 versions
  arm64: KVM: Reorder system register restoration and stage-2 activation
  arm64: KVM: Disable EL1 PTW when invalidating S2 TLBs
  arm64: KVM: Prevent speculative S1 PTW when restoring vcpu context
  arm64: Enable and document ARM errata 1319367 and 1319537

 Documentation/arm64/silicon-errata.rst |  4 +++
 arch/arm64/Kconfig                     | 10 ++++++
 arch/arm64/include/asm/cpucaps.h       |  3 +-
 arch/arm64/kernel/cpu_errata.c         | 13 +++++--
 arch/arm64/kvm/hyp/switch.c            | 48 ++++++++++++++++++++++----
 arch/arm64/kvm/hyp/sysreg-sr.c         | 14 ++++++--
 arch/arm64/kvm/hyp/tlb.c               | 23 ++++++++++++
 7 files changed, 103 insertions(+), 12 deletions(-)
```
#### [kvm-unit-tests PATCH 0/2] s390x: Quick fixes
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Sep 25 13:56:21 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11160759
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7986814DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:56:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5787321D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:56:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2407088AbfIYN4h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 09:56:37 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:10736 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2406628AbfIYN4h (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Sep 2019 09:56:37 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8PDq6I7128563
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 09:56:36 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v893m1brm-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 09:56:36 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 25 Sep 2019 14:56:33 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 25 Sep 2019 14:56:29 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8PDu1CT35062144
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 25 Sep 2019 13:56:01 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A19F9A4066;
        Wed, 25 Sep 2019 13:56:28 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 045FBA4060;
        Wed, 25 Sep 2019 13:56:28 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 25 Sep 2019 13:56:27 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 0/2] s390x: Quick fixes
Date: Wed, 25 Sep 2019 09:56:21 -0400
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19092513-4275-0000-0000-0000036AF4DF
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092513-4276-0000-0000-0000387D705A
Message-Id: <20190925135623.9740-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-25_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=3 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=602 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909250140
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Missing free and missing import.

Janosch Frank (2):
  s390x: Add missing include in smp.h
  s390x: Free allocated page in iep test

 lib/s390x/smp.h | 2 ++
 s390x/iep.c     | 1 +
 2 files changed, 3 insertions(+)
Acked-by: David Hildenbrand <david@redhat.com>
```
#### [PATCH kvm-unit-tests 0/4] test GUEST_EFER field and address size
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed Sep 25 16:14:22 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11161049
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8DA5014E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:14:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6BAA721D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:14:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="W2oyofFO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2501923AbfIYQOb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 12:14:31 -0400
Received: from mail-wr1-f50.google.com ([209.85.221.50]:40856 "EHLO
        mail-wr1-f50.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2501879AbfIYQOb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 12:14:31 -0400
Received: by mail-wr1-f50.google.com with SMTP id l3so7639393wru.7
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 09:14:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=jH89YR3V+7ra19Tk0nEdNwJtpzPMPzTno2dxgTzS6Tc=;
        b=W2oyofFO5CPfsaHaaTmqs84aktbCVYjXDIdtmG6Lo752EqaQC69+xy599vV77wnIpP
         ijuSpcsWd9NS7GrDSj8hErnLarSq1lKqvtAJaI/9X9vzksUG7irsN7fS6SEaS/sYNcoB
         Vjh0LaJIYEjNXwVBbNdt5TlJvhMs53fE5bUPH1q2zfwKzmbb9Blv0OZQy1vwYAtv9e6P
         D5rHGri5fCUssSZKd7CgQafqZawInZI0VGHS95MEBxi1F7o74M5yT6M8Ew2K/lsUgbhv
         ZlV/r3bVPjmZ2Lqf6POGLM6cFN5ZtN62bhZZ88Cb9bpC2tFe/FsrvGV7KH6fS/XtPFzE
         5g5g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=jH89YR3V+7ra19Tk0nEdNwJtpzPMPzTno2dxgTzS6Tc=;
        b=ngJzXTKZ9Jp7McSCujbEWf1YEkUCPhEeVhRJDQt/+aw6Q+fhleZRiUxgkbtzRQLbgE
         ZI0PlrjlbqypC/qG8wBh4MLOK9wtWkotXcsoAYMI/m+3s6EQkr5uKIZF4BMcKw/Nck8x
         ozeb6wdfl2+sWch1ynGv8X7e5DE38aoS+1/9wE331rZZ5kXHUUBpJFf/0pdg3KQxT24T
         tPqTAUnol3hv/idC2ElcJr5ai6ZvIsWp5JKVb7AnMk+KjeMMpYfLYPaGLBhWrTkv2ysb
         L0FjEVDa4Kme1R0O1RNkAg8nc2LAPkXPQca6Jq82qQqO52Tp21bw3ufxFt3Uf00d3gdd
         GI0g==
X-Gm-Message-State: APjAAAXwbcRfw9YOdoRCgjf81Zsc+EeVube7wBYumqg5UVfgJCKoAp+G
        w5X7rUyRHxParXmCRmf0GE/mv483
X-Google-Smtp-Source: 
 APXvYqyk5MKWkphEFJErfhbHZJJGVxKzbTWVbpALHTGbpsv9DD7wITvI+6OMACYY5tvexuU1lO/xyQ==
X-Received: by 2002:adf:e546:: with SMTP id z6mr10157421wrm.113.1569428068575;
        Wed, 25 Sep 2019 09:14:28 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 a71sm4055293wme.11.2019.09.25.09.14.27
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 25 Sep 2019 09:14:27 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH kvm-unit-tests 0/4] test GUEST_EFER field and address size
 controls
Date: Wed, 25 Sep 2019 18:14:22 +0200
Message-Id: <1569428066-27894-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series extends the HOST_EFER tests to test the host address size
(patch 2) and adds matching tests for GUEST_EFER (patches 3-4).

Paolo Bonzini (4):
  x86: vmx_tests: gate load guest PAT tests on the correct bit
  x86: vmx_tests: extend HOST_EFER tests
  x86: vmx_tests: prepare for extending guest state area tests
  x86: vmx_tests: add GUEST_EFER tests

 x86/vmx_tests.c | 219 +++++++++++++++++++++++++++++++++++++-------------------
 1 file changed, 145 insertions(+), 74 deletions(-)
```
