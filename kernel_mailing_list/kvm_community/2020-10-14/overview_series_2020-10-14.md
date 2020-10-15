#### [PATCH kvm-unit-tests 1/3] lib/string: Fix getenv name matching
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11838199
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D5771130
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 19:14:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71D912222C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 19:14:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Po/ftOj0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390270AbgJNTOw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 15:14:52 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:20666 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2390300AbgJNTOw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 15:14:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602702891;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=j7eyIpDAmINftMkywYO90JMOsADYfEqnN57dGxmdomA=;
        b=Po/ftOj06eDp0iBjFHEae1y7LmQg8CgbVnWAmflFmGD2AXGtyNMRORtoysOikX3+JKuulX
        W2uOnwJ4Hh7y4ZBkyHU5rqlaKBErC+Ou6zMt+o4fZxqN3IHiZbVGwe6cM3aFcrhoS2WmJs
        mbcGeAoW7WU1+3jvLZhgJk/t7P9Bx0s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-303-zTJfI4sQM_2FXgbJyehWKg-1; Wed, 14 Oct 2020 15:14:49 -0400
X-MC-Unique: zTJfI4sQM_2FXgbJyehWKg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 81F5A86ABD9
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 19:14:48 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.195.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 44A025577C;
        Wed, 14 Oct 2020 19:14:47 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [PATCH kvm-unit-tests 1/3] lib/string: Fix getenv name matching
Date: Wed, 14 Oct 2020 21:14:42 +0200
Message-Id: <20201014191444.136782-2-drjones@redhat.com>
In-Reply-To: <20201014191444.136782-1-drjones@redhat.com>
References: <20201014191444.136782-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Without confirming that the name length exactly matches too, then
the string comparison would return the same value for VAR* as for
VAR, when VAR came first in the environ array.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 lib/string.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/20] kvm: x86/mmu: Separate making SPTEs from set_spteFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11838131
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D19D814B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 18:27:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A58C42222A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 18:27:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MogfLG0Y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388136AbgJNS1K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 14:27:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40040 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388073AbgJNS1H (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Oct 2020 14:27:07 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7CF69C061755
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 11:27:06 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id co16so2369pjb.1
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 11:27:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=4bjkl7LU/ijpP4j3wkVH8RGMkGEhF98fqB9pEclfJrk=;
        b=MogfLG0Ygib8pC0aC4AVyfrCXTiWPZ+I8kFw8RCzn3NdcLonBPkaOwCYFHij0wrUAI
         FC7DasDbwNlLO+rUZlGNaSlybrvy7GnhjbIu+ybG2F207pU+7yDQ3pZwjyA7mz7Se71Y
         IbGhUgcX8ZusRoGk1n+nJVPB5ijxIuMYWUe8jNExK5+bFn/SX2CZz8r0nexXNXueUQ/E
         9x+skWzS9XR/eIuI+oPRvPlaI8ytWfXAyfH7Ve1uqyOucO9S6Nw9Blw5xvSWhcB1PUKI
         sb9+2pWbAnF5Bl7Co9B2gAVjAn4JQKg1Y1w9zfsCP97MMQdo8gsk6cNChxbaeq/oLx/Q
         lfaw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=4bjkl7LU/ijpP4j3wkVH8RGMkGEhF98fqB9pEclfJrk=;
        b=cumnB+4ZcEVdtMgFfaWsc7UFZFaZRgIyYB6h3HECZnX3E/KUeYEPX6LpPXhb501fdg
         J0Q/NwreW38Ad8+214atPZZx9OOYzDynHyzdy7HCFAPBm0nLqvpPzMLNexdP7x77Yw/V
         Rb0mgW3sxOMtEeI7igr3PcCyCk5Xz21ETrjkuvtqOCPmxh4+Ukuv/qU9qQjWchLdsYC8
         FfsK8Y2r5lZ+UIS8HRqzoZxmgMifiPpPf/EfEsetAAUEDNLtNiRvLbpPxDO5dXlQudhl
         NOpiNmF2Klix2p1QVZZxjfCVJCzqvJPjFfgKtM0ztpQMVGI9lt5qGruW8BeCVjj3kWXe
         B6fg==
X-Gm-Message-State: AOAM533ANK0NXGYbjULV9QFvvlqE4zLp3OByin8JO3js1++br1Ovaj7B
        q7UCEk9AeAJXU9Aaj/E3M8f0IdqSFOS/
X-Google-Smtp-Source: 
 ABdhPJy35YA8qiNQX7ZBjgjicHgSqdVWg6euqKaGUEbJi3LTSM58YPkjX30wFc214EhwPbtHDhSobtXpgdka
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a62:884d:0:b029:152:1a5f:1123 with SMTP id
 l74-20020a62884d0000b02901521a5f1123mr580761pfd.28.1602700025984; Wed, 14 Oct
 2020 11:27:05 -0700 (PDT)
Date: Wed, 14 Oct 2020 11:26:41 -0700
In-Reply-To: <20201014182700.2888246-1-bgardon@google.com>
Message-Id: <20201014182700.2888246-2-bgardon@google.com>
Mime-Version: 1.0
References: <20201014182700.2888246-1-bgardon@google.com>
X-Mailer: git-send-email 2.28.0.1011.ga647a8990f-goog
Subject: [PATCH v2 01/20] kvm: x86/mmu: Separate making SPTEs from set_spte
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cannon Matthews <cannonmatthews@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Separate the functions for generating leaf page table entries from the
function that inserts them into the paging structure. This refactoring
will facilitate changes to the MMU sychronization model to use atomic
compare / exchanges (which are not guaranteed to succeed) instead of a
monolithic MMU lock.

No functional change expected.

Tested by running kvm-unit-tests and KVM selftests on an Intel Haswell
machine. This commit introduced no new failures.

This series can be viewed in Gerrit at:
	https://linux-review.googlesource.com/c/virt/kvm/kvm/+/2538

Signed-off-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 49 ++++++++++++++++++++++++++++--------------
 1 file changed, 33 insertions(+), 16 deletions(-)

```
#### [RFC v2 1/7] KVM: VMX: Introduce PKS VMCS fields
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11836631
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A58341580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 02:09:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 920AF21D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 02:09:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729022AbgJNCJt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 22:09:49 -0400
Received: from mga06.intel.com ([134.134.136.31]:51139 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725874AbgJNCJr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 22:09:47 -0400
IronPort-SDR: 
 U15kODlCu8xgK2h7oRkpa6Ky8CR13pQ555m9Ck1R0F1cOAezpD9bDqe4ry50ow38oNreSiHtgv
 XVWw24hsSLDQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9773"; a="227659787"
X-IronPort-AV: E=Sophos;i="5.77,373,1596524400";
   d="scan'208";a="227659787"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Oct 2020 19:09:47 -0700
IronPort-SDR: 
 kVFpELbcsuQC3I3CucF2zICCDVrPqhyTa8jZu/23UKwxnjc4pzbbb73VOp03nmU2PUcjXieht3
 hKmfhhSSALWw==
X-IronPort-AV: E=Sophos;i="5.77,373,1596524400";
   d="scan'208";a="530645100"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Oct 2020 19:09:45 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v2 1/7] KVM: VMX: Introduce PKS VMCS fields
Date: Wed, 14 Oct 2020 10:11:50 +0800
Message-Id: <20201014021157.18022-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201014021157.18022-1-chenyi.qiang@intel.com>
References: <20201014021157.18022-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PKS(Protection Keys for Supervisor Pages) is a feature that extends the
Protection Key architecture to support thread-specific permission
restrictions on supervisor pages.

A new PKS MSR(PKRS) is defined in kernel to support PKS, which holds a
set of permissions associated with each protection domian.

Two VMCS fields {HOST,GUEST}_IA32_PKRS are introduced in
{host,guest}-state area to store the value of PKRS.

Every VM exit saves PKRS into guest-state area.
If VM_EXIT_LOAD_IA32_PKRS = 1, VM exit loads PKRS from the host-state
area.
If VM_ENTRY_LOAD_IA32_PKRS = 1, VM entry loads PKRS from the guest-state
area.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/vmx.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH kvm-unit-tests] runtime.bash: skip test when checked file doesn't exist
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11837969
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C7A3514B3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 15:43:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 928152222F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 15:43:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CBp4B1EX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730421AbgJNPnE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 11:43:04 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29124 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726954AbgJNPnE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 11:43:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602690183;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Tt3lce95cbC+mW0urx5sc6gHao7nV9e5qYYhDPu3nuY=;
        b=CBp4B1EX+qDNV2BNpUtQLy1cqEfagoNQ5MYGcWe6CVdSQBIBXoVJuCvziYH9UUKA/6wSUW
        i4KGiiNs9I8Ks+2sOgDoNiYWoNq9GiiIdr34DLE/MLzX6yyahl3GEMT7Tv349gabJnM65E
        67uZzPqz2RVtR26WpcyxGXc9bszKB9E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-385-m7za7t61M726hxser23Faw-1; Wed, 14 Oct 2020 11:43:01 -0400
X-MC-Unique: m7za7t61M726hxser23Faw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 90396801FDD
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 15:43:00 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3D52C1002C00;
        Wed, 14 Oct 2020 15:42:58 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>
Subject: [PATCH kvm-unit-tests] runtime.bash: skip test when checked file
 doesn't exist
Date: Wed, 14 Oct 2020 17:42:58 +0200
Message-Id: <20201014154258.2437510-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we have the following check condition in x86/unittests.cfg:

check = /sys/module/kvm_intel/parameters/allow_smaller_maxphyaddr=Y

the check, however, passes successfully on AMD because the checked file
is just missing. This doesn't sound right, reverse the check: fail
if the content of the file doesn't match the expectation or if the
file is not there.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 scripts/runtime.bash | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Add tests for PKS
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11836637
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 988401580
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 02:10:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8157D21775
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 02:10:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729360AbgJNCKK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 22:10:10 -0400
Received: from mga06.intel.com ([134.134.136.31]:51186 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727278AbgJNCKG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 22:10:06 -0400
IronPort-SDR: 
 ugeXjjgCbbx/xwkmkUvlRTGf+AXuvsBKB065PZS1Py+t7Md1XxN6+1TjiXQuUdvkJoGtSTeaXM
 Man0lLyYOw7g==
X-IronPort-AV: E=McAfee;i="6000,8403,9773"; a="227659815"
X-IronPort-AV: E=Sophos;i="5.77,373,1596524400";
   d="scan'208";a="227659815"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Oct 2020 19:10:05 -0700
IronPort-SDR: 
 XaY3fNslOB1hqTy01d8Qtg8d3am+kNaTF46EQL5xAu9OjhmG3wYhb3yu2vJY0UFtYXWfhYJcJ9
 javbOV7xCiWA==
X-IronPort-AV: E=Sophos;i="5.77,373,1596524400";
   d="scan'208";a="530645260"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Oct 2020 19:10:03 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Add tests for PKS
Date: Wed, 14 Oct 2020 10:11:57 +0800
Message-Id: <20201014021157.18022-9-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201014021157.18022-1-chenyi.qiang@intel.com>
References: <20201014021157.18022-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test the KVM support for Protection Keys
for Supervisor Pages (PKS). If CR4.PKS is set in long mode, supervisor
pkeys are checked in addition to normal paging protections and Access or
Write can be disabled via a MSR update without TLB flushes when
permissions change.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 lib/x86/msr.h       |   1 +
 lib/x86/processor.h |   2 +
 x86/Makefile.x86_64 |   1 +
 x86/pks.c           | 146 ++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg   |   5 ++
 5 files changed, 155 insertions(+)
 create mode 100644 x86/pks.c

```
#### [PATCH] KVM: VMX: eVMCS: make evmcs_sanitize_exec_ctrls() work again
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11837281
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2C8514B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 10:07:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B72FA2068E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 10:07:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OOeAam35"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728925AbgJNKHR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 06:07:17 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:52092 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725985AbgJNKHR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 06:07:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602670035;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=D5KqYEUpfycrQPhzEmIDML2TPVxdekkeeWQmKWvWXAo=;
        b=OOeAam359ErtXF3/0bSrVsJmcGvBWcbKijqJqAyBFsfFx8rXW/fBbCQdF1I18aBoLJu9NM
        94r9wCzE/uU0+c5WOL6vQl3l9kw/xGo1g0vxa6XFyiFPo+KiXf8jd/L5kzV88/ceNT6cPd
        Pj6rWoVe34d8APTU1B30L0sj0FBfSbw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-221-wwy8auPNM-WqgPCwHeU1sQ-1; Wed, 14 Oct 2020 06:07:12 -0400
X-MC-Unique: wwy8auPNM-WqgPCwHeU1sQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 033068BAF69;
        Wed, 14 Oct 2020 10:07:05 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA9EF7B7A9;
        Wed, 14 Oct 2020 10:06:59 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Yang Weijiang <weijiang.yang@intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: eVMCS: make evmcs_sanitize_exec_ctrls() work again
Date: Wed, 14 Oct 2020 12:06:58 +0200
Message-Id: <20201014100658.2346024-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was noticed that evmcs_sanitize_exec_ctrls() is not being executed
nowadays despite the code checking 'enable_evmcs' static key looking
correct. Turns out, static key magic doesn't work in '__init' section
(and it is unclear when things changed) but setup_vmcs_config() is called
only once per CPU so we don't really need it to. Switch to checking
'enlightened_vmcs' instead, it is supposed to be in sync with
'enable_evmcs'.

Opportunistically make evmcs_sanitize_exec_ctrls '__init' and drop unneeded
extra newline from it.

Reported-by: Yang Weijiang <weijiang.yang@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 arch/x86/kvm/vmx/evmcs.c | 3 +--
 arch/x86/kvm/vmx/evmcs.h | 2 +-
 arch/x86/kvm/vmx/vmx.c   | 2 +-
 3 files changed, 3 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Filter out more Intel-specific PMU MSRs in kvm_init_msr_list()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11837613
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4BED14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 12:50:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A55FC22246
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 12:50:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JJVoI9zz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730893AbgJNMu3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 08:50:29 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41692 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727061AbgJNMu2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 08:50:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602679827;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=MMxmagzUGQGP4XInFkt7451v8xVF11xKUk5UyjYEMMU=;
        b=JJVoI9zz4deLypUhW762AihleYHLZ7f4lcEii20kkMbgbBEh+9VZzw8+6UKDzjwulA8lz/
        3WtYI9rz9sZe8myICylAt8HeuXcGQg41P8/gVk6ioXTwueSy7juVS6YXibroi5XesagPbs
        MG0YpPnvM/mGQwExmDriq035XmLR/K4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-153-2Lq70kDlO0Sv7pwogcjvXg-1; Wed, 14 Oct 2020 08:50:25 -0400
X-MC-Unique: 2Lq70kDlO0Sv7pwogcjvXg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E12571062721;
        Wed, 14 Oct 2020 12:50:23 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D0C9760BE2;
        Wed, 14 Oct 2020 12:50:21 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Filter out more Intel-specific PMU MSRs in
 kvm_init_msr_list()
Date: Wed, 14 Oct 2020 14:50:20 +0200
Message-Id: <20201014125020.2406434-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running KVM selftest in a Hyper-V VM they stumble upon

  Unexpected result from KVM_GET_MSRS, r: 14 (failed MSR was 0x309)

MSR_ARCH_PERFMON_FIXED_CTR[0..3] along with MSR_CORE_PERF_FIXED_CTR_CTRL,
MSR_CORE_PERF_GLOBAL_STATUS, MSR_CORE_PERF_GLOBAL_CTRL,
MSR_CORE_PERF_GLOBAL_OVF_CTRL are only valid for Intel PMU ver > 1 but
Hyper-V instances have CPUID.0AH.EAX == 0 (so perf code falls back to
p6_pmu instead of intel_pmu). Surprisingly, unlike on AMD hardware for
example, our rdmsr_safe() check passes and MSRs are not filtered out.

MSR_ARCH_PERFMON_FIXED_CTR[0..3] can probably be checked against
x86_pmu.num_counters_fixed and the rest is only present with
x86_pmu.version > 1.

Unfortunately, full elimination of the disconnection between system-wide
KVM_GET_MSR_INDEX_LIST/KVM_GET_MSR_FEATURE_INDEX_LIST and per-VCPU
KVM_GET_MSRS/KVM_SET_MSRS seem to be impossible as per-vCPU PMU setup
depends on guest CPUIDs which can always be altered.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH v1] nitro_enclaves: Fixup type of the poll result assigned value
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11837085
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3486D61C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 09:05:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 08E1A20B1F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 09:05:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="qOkMFX5s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728292AbgJNJFf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 05:05:35 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:65507 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726032AbgJNJFe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Oct 2020 05:05:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1602666335; x=1634202335;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=y4uF4ZEBK32Jc4xw6gI6FEIourHHlYCRqz8nki0gYyI=;
  b=qOkMFX5sufrRtwI98Q7oKihHHXk37ODwvS3A6bG83oyN/IH2ycib0lcC
   Q2oxQIV+Cy0C5pQbEnXqWfgUwEYH0txiSN45eecLiplhhORP/4moc1i+u
   /CRwTHoO9JFt68ueghICBuh2Ugl5sx94+Wr3LvJHmflQd9DIDH7LUsGgj
   I=;
X-IronPort-AV: E=Sophos;i="5.77,374,1596499200";
   d="scan'208";a="83212214"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2b-c7131dcf.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 14 Oct 2020 09:05:21 +0000
Received: from EX13D16EUB003.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2b-c7131dcf.us-west-2.amazon.com (Postfix) with
 ESMTPS id 10167A2236;
        Wed, 14 Oct 2020 09:05:16 +0000 (UTC)
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.161.71) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 14 Oct 2020 09:05:06 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: linux-kernel <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Karen Noel <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v1] nitro_enclaves: Fixup type of the poll result assigned
 value
Date: Wed, 14 Oct 2020 12:05:00 +0300
Message-ID: <20201014090500.75678-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.161.71]
X-ClientProxiedBy: EX13D43UWC001.ant.amazon.com (10.43.162.69) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update the assigned value of the poll result to be EPOLLHUP instead of
POLLHUP to match the __poll_t type.

Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/virt/nitro_enclaves/ne_misc_dev.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v1] self_tests/kvm: sync_regs and reset tests for diag318
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11838235
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E65D91592
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 19:27:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F866214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 19:27:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="F63YmDiT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390622AbgJNT13 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 15:27:29 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:16886 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2389668AbgJNT13 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 15:27:29 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09EJI0hC190995
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 15:27:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=RdrNMfvPfUwm8ntPfHZMrkgielRTP7iofjXSHaev1aA=;
 b=F63YmDiTVmuTUpwzB7bd2/ECBUh6Jq9K8z1LJBoGcdPxpWSJRaHV3fiVHcQp3oiDYATC
 Z3MkvCsoCt6DzuN4r+pBgzWzaLqpey5sOh6mlIgrBJHEqXGVXkmg5BCkJXPrF1TH/Wt8
 l0P+0b0vT0PzIJ5Fu8MlpGE4fK54zA0iIuWfVvNAfj2E69nIBdKvun81AgYHT4HE0lim
 yKMPM3QtvDwUrpkhmjGyXggNXV5RJ9nU5sqcx/3ce1YrQaIszxMLcIhjkZFDGg7lImnM
 AnuhgHGokOWEyu0EBdin7LHSu3CPr6O4EotY6cldTWyKHErX+ivJyInWKTSoQvI0krs0 SQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3467a5rbkt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 15:27:28 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09EJIVCB195054
        for <kvm@vger.kernel.org>; Wed, 14 Oct 2020 15:27:28 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3467a5rbjx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 14 Oct 2020 15:27:28 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09EJN476021354;
        Wed, 14 Oct 2020 19:27:25 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma04wdc.us.ibm.com with ESMTP id 3434k93qcq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 14 Oct 2020 19:27:25 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 09EJRK2g48300390
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 14 Oct 2020 19:27:20 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E426E136055;
        Wed, 14 Oct 2020 19:27:24 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6C115136053;
        Wed, 14 Oct 2020 19:27:24 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.130.217])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed, 14 Oct 2020 19:27:24 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com
Subject: [PATCH v1] self_tests/kvm: sync_regs and reset tests for diag318
Date: Wed, 14 Oct 2020 15:27:10 -0400
Message-Id: <20201014192710.66578-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-14_11:2020-10-14,2020-10-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 impostorscore=0 spamscore=0 suspectscore=38 priorityscore=1501 bulkscore=0
 lowpriorityscore=0 mlxscore=0 malwarescore=0 clxscore=1011 adultscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010140132
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The DIAGNOSE 0x0318 instruction, unique to s390x, is a privileged call
that must be intercepted via SIE, handled in userspace, and the
information set by the instruction is communicated back to KVM.

To test the instruction interception, an ad-hoc handler is defined which
simply has a VM execute the instruction and then userspace will extract
the necessary info. The handler is defined such that the instruction
invocation occurs only once. It is up the the caller to determine how the
info returned by this handler should be used.

The diag318 info is communicated from userspace to KVM via a sync_regs
call. This is tested during a sync_regs test, where the diag318 info is
requested via the handler, then the info is stored in the appropriate
register in KVM via a sync registers call.

The diag318 info is checked to be 0 after a normal and clear reset.

If KVM does not support diag318, then the tests will print a message
stating that diag318 was skipped, and the asserts will simply test
against a value of 0.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
---
 tools/testing/selftests/kvm/Makefile          |  2 +-
 .../kvm/include/s390x/diag318_test_handler.h  | 13 +++
 .../kvm/lib/s390x/diag318_test_handler.c      | 80 +++++++++++++++++++
 tools/testing/selftests/kvm/s390x/resets.c    |  6 ++
 .../selftests/kvm/s390x/sync_regs_test.c      | 16 +++-
 5 files changed, 115 insertions(+), 2 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/diag318_test_handler.h
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/diag318_test_handler.c

```
#### [PATCH v2] KVM: VMX: eVMCS: make evmcs_sanitize_exec_ctrls() work again
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11837731
Return-Path: <SRS0=7LGy=DV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0552914B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 14:33:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D3861212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Oct 2020 14:33:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LAqK5dUk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727891AbgJNOdz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Oct 2020 10:33:55 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33374 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727698AbgJNOdz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Oct 2020 10:33:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602686033;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VBEPTvJ9Pz1lmUaui+vxyvm9Ew7ufHeZNz2SJQIN2VQ=;
        b=LAqK5dUkewuj7sK2D+8eZzieu8W0Fx+/Li+rwhaWifeMCEi9JDkzkxHF8jqEM/t5Y2sH2a
        0+L4aLgf0CX5BN1B1MZOLbkfgU+ty++o8K/E5cDaIIwpXmzkke4hHAykYtD9xzE2etjDYm
        PaOfPAzP/JYh5/MwcaCiwY6xpCc66Ac=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-282-DnJPaNMCOme2JxgkrZRGpg-1; Wed, 14 Oct 2020 10:33:52 -0400
X-MC-Unique: DnJPaNMCOme2JxgkrZRGpg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 604D818A08CC;
        Wed, 14 Oct 2020 14:33:50 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DBBF46EF53;
        Wed, 14 Oct 2020 14:33:47 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Yang Weijiang <weijiang.yang@intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: VMX: eVMCS: make evmcs_sanitize_exec_ctrls() work
 again
Date: Wed, 14 Oct 2020 16:33:46 +0200
Message-Id: <20201014143346.2430936-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was noticed that evmcs_sanitize_exec_ctrls() is not being executed
nowadays despite the code checking 'enable_evmcs' static key looking
correct. Turns out, static key magic doesn't work in '__init' section
(and it is unclear when things changed) but setup_vmcs_config() is called
only once per CPU so we don't really need it to. Switch to checking
'enlightened_vmcs' instead, it is supposed to be in sync with
'enable_evmcs'.

Opportunistically make evmcs_sanitize_exec_ctrls '__init' and drop unneeded
extra newline from it.

Reported-by: Yang Weijiang <weijiang.yang@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- Changes since v1:
  put '#if IS_ENABLED(CONFIG_HYPERV)' around enlightened_vmcs check
  [ktest robot]
---
 arch/x86/kvm/vmx/evmcs.c | 3 +--
 arch/x86/kvm/vmx/evmcs.h | 3 +--
 arch/x86/kvm/vmx/vmx.c   | 4 +++-
 3 files changed, 5 insertions(+), 5 deletions(-)

```
