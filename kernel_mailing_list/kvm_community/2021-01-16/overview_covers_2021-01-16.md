

#### [PATCH 0/3 v2] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Sat Jan 16 02:20:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12024535
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 51CF0C433E6
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:21:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D8D32256F
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:21:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728694AbhAPCVg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 21:21:36 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:48626 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725919AbhAPCVf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 21:21:35 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10G24LVK125385;
        Sat, 16 Jan 2021 02:20:52 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=s+hKv2Hsgem2IKtJX/pjAPHvUqbzAyi0SIY3rNiY9/g=;
 b=jUGrAM+jqX96Qz3tGU9PDnoO8KQ4N4Tk2L2Mu+Zkbwr0le6qbkR0Mw7jNt/cPsAtidR8
 JzeISBNYSVvH2XFKpbZCal6eEn0FfOmgqQ1mEjW4rcxWWeRtZlnD8vMRlhFuZ/z1/eiI
 Ve3GiUwIIElToVxo9yNc306OhUlJj3IFVPqobhxjltRqKU4B9zNGQrxQGhS6QHuaLJlg
 N9oecmbJScUNWENR80Y2WF/imjJmEU0akdKgeOoE3CM02dXKeRBVbfpgE51127VBZqCD
 AeA+1+aVbAvLF6T2VRpRMEfOdP1Mr1ys5h9Kx3kjgv1dytPpcb9uYs7BJ0Surq/UTpax /Q==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2130.oracle.com with ESMTP id 363nna83gt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 16 Jan 2021 02:20:52 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10G25u8h004140;
        Sat, 16 Jan 2021 02:20:51 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 360kfbuvsn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 16 Jan 2021 02:20:51 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 10G2KonK019552;
        Sat, 16 Jan 2021 02:20:50 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 15 Jan 2021 18:20:50 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/3 v2] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Sat, 16 Jan 2021 02:20:36 +0000
Message-Id: <20210116022039.7316-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9865
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 mlxlogscore=999 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101160010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9865
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 impostorscore=0
 spamscore=0
 mlxlogscore=999 clxscore=1015 bulkscore=0 adultscore=0 lowpriorityscore=0
 suspectscore=0 phishscore=0 mlxscore=0 malwarescore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101160010
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	In patch# 1, the parameter to nested_vmcb_check_controls() has been
	changed to 'struct kvm_vcpu' from 'struct vcpu_svm'. This necessiated
	relevant changes to its callers.
	Also, the new checks in nested_vmcb_check_controls() now use
	page_address_valid() instead of duplicating code.

	It has also been rebased to v5.11-rc3.


[PATCH 1/3 v2] nSVM: Check addresses of MSR and IO bitmap
[PATCH 2/3 v2] Test: nSVM: Test MSR and IO bitmap address
[PATCH 3/3 v2] Test: SVM: Use ALIGN macro when aligning 'io_bitmap_area'

 arch/x86/kvm/svm/nested.c | 18 ++++++++++++------
 1 file changed, 12 insertions(+), 6 deletions(-)

Krish Sadhukhan (1):
      nSVM: Check addresses of MSR and IO bitmap

 x86/svm.c       |  2 +-
 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 2 files changed, 39 insertions(+), 1 deletion(-)

Krish Sadhukhan (2):
      nSVM: Test MSR and IO bitmap address
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
```
#### [Patch v5 0/2] cgroup: KVM: New Encryption IDs cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Sat Jan 16 02:32:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12024545
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C7BE2C433E6
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:33:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9136F238D7
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:33:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728324AbhAPCdB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 21:33:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50586 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725781AbhAPCdA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 21:33:00 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9B098C0613D3
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 18:32:14 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id x74so9972789qkb.12
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 18:32:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=bK7/dTmSR86C29WgdGxGU8MYCwIuJFaDUK2eSVHNrX4=;
        b=sxCHu/OuwVoHklKKuzYAF3YsaoWE9hexH3rykqnuF4Wa1pLx0+47yDulZFXTH0z6UR
         lN1cYFqW2c25FiOwJmS3zmeJkpRkqtUGZdl8y6vtKIEBU8+r9EhEZ2rRX84KdZH/x8l1
         sLMnYBccUlFvPDG/uqbFCIPzXC+bBTmbJHP3EZfwKpedZs1BPJJ0GqFSKc560A0bgH/T
         7TiDfF625MkvdOAtu394qMmd1073/f9aGb+zxUt394QKEwpQy7hJYWYGBZy9k5J0ADkx
         tSP8iSsMYb9yV/NoQbVJg/7K9WCO111I+F0VjQhCpQgiqf3lZwr9omaJnGgSme+njipm
         xdnA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=bK7/dTmSR86C29WgdGxGU8MYCwIuJFaDUK2eSVHNrX4=;
        b=lWYhK6CRm1gH3qxCFhtqrv90+aHvEkfeO5smJ5DpVpm0mjjW4KSXWEmwLdE+FVLRCj
         aapdnc3Y9Iz3VUKJ3RiuDCLAQMgEoankT4UKlKXYSylN/lFBWpnGqa/KCJg21QZA9G32
         uamrEuQrW1q7520QTFc3ftzssy2RvNG9L29KPOmNxx4TlRCCCmz7176WTEXQLQZ1N+yS
         AseUQayFwezErLhGVsR7HIAw2BQNyRNMWd2l5Z2OI/3/UfgUeKouVpU7VQ3HzIatr0oS
         3J2S64uyEBPP+4v/IKdE80aXQP0sC1f2NAo/5J86HjF6FWogEBLfL0JBBqErirohMJ6s
         EBwQ==
X-Gm-Message-State: AOAM533gDHU3eA2dEy8nLOYOo3fGqJjehseDi1Vbn8EdvXDiiUmzPiLu
        xxB+GFzX2iWjg+G+JO1HTQVjkgydQSFJ
X-Google-Smtp-Source: 
 ABdhPJx8zg6GHMhhgyZyzbY0pMKP05X/oObg4+gTaSfWzbBiuE54CPTESrNjdV7FtuFvVuyrM+3U2lobDBxW
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:a0c:fe47:: with SMTP id
 u7mr15197077qvs.4.1610764333565; Fri, 15 Jan 2021 18:32:13 -0800 (PST)
Date: Fri, 15 Jan 2021 18:32:02 -0800
Message-Id: <20210116023204.670834-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [Patch v5 0/2] cgroup: KVM: New Encryption IDs cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, hannes@cmpxchg.org, frankja@linux.ibm.com,
        borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch adds a new cgroup controller, Encryption IDs, to track and
limit the usage of encryption IDs on a host.

AMD provides Secure Encrypted Virtualization (SEV) and SEV with
Encrypted State (SEV-ES) to encrypt the guest OS's memory using limited
number of Address Space Identifiers (ASIDs).

This limited number of ASIDs creates issues like SEV ASID starvation and
unoptimized scheduling in the cloud infrastucture.

In the RFC patch v1, I provided only SEV cgroup controller but based
on the feedback and discussion it became clear that this cgroup
controller can be extended to be used by Intel's Trusted Domain
Extension (TDX) and s390's protected virtualization Secure Execution IDs
(SEID)

This patch series provides a generic Encryption IDs controller with
tracking support of the SEV and SEV-ES ASIDs.

Changes in v5:
- Changed controller filenames from encryption_ids.*.* to encids.*.*
- Documentation of cgroup v1 now points to cgroup v2.

Changes in v4:
- The max value can be set lower than the current.
- Added SEV-ES support.

Changes in v3:
- Fixes a build error when CONFIG_CGROUP is disabled.

Changes in v2:
- Changed cgroup name from sev to encryption_ids.
- Replaced SEV specific names in APIs and documentations with generic
  encryption IDs.
- Providing 3 cgroup files per encryption ID type. For example in SEV,
  - encryption_ids.sev.stat (only in the root cgroup directory).
  - encryption_ids.sev.max
  - encryption_ids.sev.current

[1] https://lore.kernel.org/lkml/20200922004024.3699923-1-vipinsh@google.com/
[2] https://lore.kernel.org/lkml/20201208213531.2626955-1-vipinsh@google.com/
[3] https://lore.kernel.org/lkml/20201209205413.3391139-1-vipinsh@google.com/
[4] https://lore.kernel.org/lkml/20210108012846.4134815-1-vipinsh@google.com/

Vipin Sharma (2):
  cgroup: svm: Add Encryption ID controller
  cgroup: svm: Encryption IDs cgroup documentation.

 .../admin-guide/cgroup-v1/encryption_ids.rst  |   1 +
 Documentation/admin-guide/cgroup-v2.rst       |  78 +++-
 arch/x86/kvm/svm/sev.c                        |  52 ++-
 include/linux/cgroup_subsys.h                 |   4 +
 include/linux/encryption_ids_cgroup.h         |  72 +++
 include/linux/kvm_host.h                      |   4 +
 init/Kconfig                                  |  14 +
 kernel/cgroup/Makefile                        |   1 +
 kernel/cgroup/encryption_ids.c                | 421 ++++++++++++++++++
 9 files changed, 633 insertions(+), 14 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/encryption_ids.rst
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c
```
