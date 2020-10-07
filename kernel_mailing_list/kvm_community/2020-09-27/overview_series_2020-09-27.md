#### [PATCH][v3] KVM: x86/mmu: fix counting of rmap entries in pte_list_add
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11801999
Return-Path: <SRS0=CJLp=DE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 639FC139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Sep 2020 08:45:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5194A23977
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Sep 2020 08:45:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728284AbgI0IpO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 27 Sep 2020 04:45:14 -0400
Received: from mx58.baidu.com ([61.135.168.58]:52547 "EHLO
        tc-sys-mailedm02.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727369AbgI0IpO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 27 Sep 2020 04:45:14 -0400
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm02.tc.baidu.com (Postfix) with ESMTP id AD22711C0039;
        Sun, 27 Sep 2020 16:44:57 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: lirongqing@baidu.com, kvm@vger.kernel.org, x86@kernel.org,
        sean.j.christopherson@intel.com
Subject: [PATCH][v3] KVM: x86/mmu: fix counting of rmap entries in
 pte_list_add
Date: Sun, 27 Sep 2020 16:44:57 +0800
Message-Id: <1601196297-24104-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix an off-by-one style bug in pte_list_add() where it failed to
account the last full set of SPTEs, i.e. when desc->sptes is full
and desc->more is NULL.

Merge the two "PTE_LIST_EXT-1" checks as part of the fix to avoid
an extra comparison.

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v2: Sean suggest to merge the two "PTE_LIST_EXT-1" checks
v3: Sean suggest to rewrite commit header

 arch/x86/kvm/mmu/mmu.c | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```