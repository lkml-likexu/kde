#### [PATCH 1/1] kvm: mmu: zap pages when zapping only parentFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11687553
Return-Path: <SRS0=pIbL=BG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7CC1614E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 20:33:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 625D42075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 20:33:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="SGMEjLSs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726196AbgG0Uda (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 16:33:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38720 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728254AbgG0Ud3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jul 2020 16:33:29 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E5903C0619D2
        for <kvm@vger.kernel.org>; Mon, 27 Jul 2020 13:33:28 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id j187so22152395ybj.7
        for <kvm@vger.kernel.org>; Mon, 27 Jul 2020 13:33:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=8+GWCqToRsYuSGreGCapWzOVpnWd7snaZLCa1XNJr0I=;
        b=SGMEjLSsF+Ur+M/B7vxrNKGkbM9VGYJ4OL16bAu+jA4wlVRqUKmhkovlTjCvo5cwU9
         /GR6A4itCCVvgEwtK6ZdxnsEsFauXhRtDAeadxCpTuMTAFSYGn3km+Wp/WDZ5pV/gE4h
         5OPZoJf92JLkU7KvFmGXdg4/sOkHWtZBnadjwZtWWIw3EWWfeUUoEaQa7B/7pGV01SWb
         m1h0X+ZNhWSnCC/KQ7tVoclpMbFgTjvcOXkHZJ5eTjyTTCkc12F3Xg9ylL2tYHwxh9iF
         RMSKvHSOapmw+rwteyyXBBlypKDGCfdEQfDDkF+XzY69jwq96n38yxI8cUB000mfvGjj
         CEMQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=8+GWCqToRsYuSGreGCapWzOVpnWd7snaZLCa1XNJr0I=;
        b=PCglBYXn61eDcoBKV9LA28FG1EibChHfepF0XjROy/zmY7X41cLm1ZJYMdKp8UrYQw
         m0PiunItiUAnANO5G1vpOCcdJIhMzF6EXmsF18aMvpzEMkidIT3xYZsyTJ66pphnpfCK
         qmHY0hgLypX7adq0QR+BjFZrgM55Cp5Nw3UbcKtDyeAtzDH/xeKIN7+N45N6X6wTnLVK
         1c3XyrfT5Lfjlu0mGjOYderBYRPb6b14oIiCqy2AeZDIuRwQVlHoK0ChfM4zt35iU23K
         hvHfR4WzpNle3ZBWA4Pv93elOcK5J1+YeaiWlfwFRpTXvBRElwoB1s48pu5ZHecpjgSE
         nk3w==
X-Gm-Message-State: AOAM531ue3fhb2feoCc797wv7kI6sURLOZD3VjJmaSjSnchIJ9wCEJfA
        ic2nU1MmS9jDcVzH+AagPI1irIn5CQdv
X-Google-Smtp-Source: 
 ABdhPJyJorpxq2jFPepAV9fDiih8wuRQXMoiV5SISAnOdfN1gBNWXGfdqI5rYs7ErSZFfzEXT7vNGuGHGtL8
X-Received: by 2002:a25:31d4:: with SMTP id
 x203mr37893178ybx.396.1595882008151;
 Mon, 27 Jul 2020 13:33:28 -0700 (PDT)
Date: Mon, 27 Jul 2020 13:33:24 -0700
Message-Id: <20200727203324.2614917-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.rc0.142.g3c755180ce-goog
Subject: [PATCH 1/1] kvm: mmu: zap pages when zapping only parent
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Ben Gardon <bgardon@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the KVM MMU zaps a page, it will recursively zap the unsynced child
pages, but not the synced ones. This can create problems over time when
running many nested guests because it leaves unlinked pages which will not
be freed until the page quota is hit. With the default page quota of 20
shadow pages per 1000 guest pages, this looks like a memory leak and can
degrade MMU performance.

In a recent benchmark, substantial performance degradation was observed:
An L1 guest was booted with 64G memory.
2G nested Windows guests were booted, 10 at a time for 20
iterations. (200 total boots)
Windows was used in this benchmark because they touch all of their
memory on startup.
By the end of the benchmark, the nested guests were taking ~10% longer
to boot. With this patch there is no degradation in boot time.
Without this patch the benchmark ends with hundreds of thousands of
stale EPT02 pages cluttering up rmaps and the page hash map. As a
result, VM shutdown is also much slower: deleting memslot 0 was
observed to take over a minute. With this patch it takes just a
few miliseconds.

If TDP is enabled, zap child shadow pages when zapping the only parent
shadow page.

Tested by running the kvm-unit-tests suite on an Intel Haswell machine.
No regressions versus
commit c34b26b98cac ("KVM: MIPS: clean up redundant 'kvm_run' parameters"),
or warnings.

Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 49 +++++++++++++++++++++++++++++++++++++-----
 1 file changed, 44 insertions(+), 5 deletions(-)

```
#### [PATCH 1/3] selftests: kvm: do not set guest mode flag
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11686887
Return-Path: <SRS0=pIbL=BG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5A05F722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 13:39:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40AEF21744
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 13:39:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G8gfpvLC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729131AbgG0Njt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 09:39:49 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:57050 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729112AbgG0Njr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Jul 2020 09:39:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595857185;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=j7vAEtPkblIb/FUeLn/+GN2wLSCH8Au5AcbyR00wCiM=;
        b=G8gfpvLCvtg6vsfQFBNVU1cUi64uyy0cAiBLi59HHJEya7imHnEGoUbl8e00Ml4T9wfqcX
        B0DbWXFAbw3hl4EWiGrbQvDjdZnEtd/fLPTNEnoeN+aw6C6iXYvOXYruUYgZ8noWtIJtpp
        wmdXd/VaDhNYc4pU0kPPmyQCs1M7nPY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-296-BQFNoj0ZMhmuUwC_RoTqxQ-1; Mon, 27 Jul 2020 09:39:40 -0400
X-MC-Unique: BQFNoj0ZMhmuUwC_RoTqxQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CBA401005510;
        Mon, 27 Jul 2020 13:39:39 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3E3205D9F3;
        Mon, 27 Jul 2020 13:39:37 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, aaronlewis@google.com
Subject: [PATCH 1/3] selftests: kvm: do not set guest mode flag
Date: Mon, 27 Jul 2020 09:39:32 -0400
Message-Id: <20200727133934.25482-2-pbonzini@redhat.com>
In-Reply-To: <20200727133934.25482-1-pbonzini@redhat.com>
References: <20200727133934.25482-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Setting KVM_STATE_NESTED_GUEST_MODE enables various consistency checks
on VMCS12 and therefore causes KVM_SET_NESTED_STATE to fail spuriously
with -EINVAL.  Do not set the flag so that we're sure to cover the
conditions included by the test, and cover the case where VMCS12 is
set and KVM_SET_NESTED_STATE is called with invalid VMCS12 contents.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 .../kvm/x86_64/vmx_set_nested_state_test.c      | 17 +++++++++--------
 1 file changed, 9 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/1] s390x: fix inline asm on gcc10
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11686719
Return-Path: <SRS0=pIbL=BG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 996E1913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 10:26:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 843832075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 10:26:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728049AbgG0K0v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 06:26:51 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:1060 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726744AbgG0K0v (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Jul 2020 06:26:51 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06RA2X0V179822
        for <kvm@vger.kernel.org>; Mon, 27 Jul 2020 06:26:49 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32hrnkqbcu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 27 Jul 2020 06:26:49 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06RA2gc4180568
        for <kvm@vger.kernel.org>; Mon, 27 Jul 2020 06:26:49 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32hrnkqbc9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 06:26:49 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06RAQCLd016343;
        Mon, 27 Jul 2020 10:26:47 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06ams.nl.ibm.com with ESMTP id 32gcqgj3kr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 10:26:47 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06RAQicx50528330
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 27 Jul 2020 10:26:44 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 96ECF11C05E;
        Mon, 27 Jul 2020 10:26:44 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3979A11C04A;
        Mon, 27 Jul 2020 10:26:44 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.171])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 27 Jul 2020 10:26:44 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, david@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v1 1/1] s390x: fix inline asm on gcc10
Date: Mon, 27 Jul 2020 12:26:43 +0200
Message-Id: <20200727102643.15439-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-27_06:2020-07-27,2020-07-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=0
 mlxlogscore=888 adultscore=0 clxscore=1015 impostorscore=0 phishscore=0
 mlxscore=0 spamscore=0 bulkscore=0 lowpriorityscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007270069
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix compilation issues on 390x with gcc 10.

Simply mark the inline functions that lead to a .insn with a variable
opcode as __always_inline, to make gcc 10 happy.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/cpacf.h |  5 +++--
 s390x/emulator.c      | 25 +++++++++++++------------
 2 files changed, 16 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/3] s390x: Add custom pgm cleanup function
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11686703
Return-Path: <SRS0=pIbL=BG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD2421392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 09:54:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9C03120786
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 09:54:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727804AbgG0Jyc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 05:54:32 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:22694 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727032AbgG0Jya (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Jul 2020 05:54:30 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06R9W9BW163640;
        Mon, 27 Jul 2020 05:54:30 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32hs8sx8uk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 05:54:30 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06R9WIet164612;
        Mon, 27 Jul 2020 05:54:29 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32hs8sx8tu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 05:54:29 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06R9kDIF015670;
        Mon, 27 Jul 2020 09:54:27 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06ams.nl.ibm.com with ESMTP id 32gcqgj2mg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 09:54:27 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06R9sODR54460854
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 27 Jul 2020 09:54:24 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 627E04C062;
        Mon, 27 Jul 2020 09:54:24 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A80EC4C052;
        Mon, 27 Jul 2020 09:54:23 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 27 Jul 2020 09:54:23 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/3] s390x: Add custom pgm cleanup function
Date: Mon, 27 Jul 2020 05:54:13 -0400
Message-Id: <20200727095415.494318-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200727095415.494318-1-frankja@linux.ibm.com>
References: <20200727095415.494318-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-27_06:2020-07-27,2020-07-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0 mlxscore=0
 impostorscore=0 clxscore=1015 mlxlogscore=999 priorityscore=1501
 adultscore=0 bulkscore=0 phishscore=0 malwarescore=0 suspectscore=1
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007270066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sometimes we need to do cleanup which we don't necessarily want to add
to interrupt.c, so lets add a way to register a cleanup function.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/interrupt.h |  1 +
 lib/s390x/interrupt.c     | 10 ++++++++++
 2 files changed, 11 insertions(+)

```
