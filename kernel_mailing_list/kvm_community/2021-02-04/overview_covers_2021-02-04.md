

#### [PATCH 00/12] KVM: x86: Legal GPA fixes and cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Feb  4 00:01:05 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12065799
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ECD9FC433E0
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:02:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BAA5464F2C
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:02:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234096AbhBDACM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 19:02:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37646 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233893AbhBDACG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 19:02:06 -0500
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C948AC0613ED
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 16:01:26 -0800 (PST)
Received: by mail-qv1-xf49.google.com with SMTP id j4so814647qvi.8
        for <kvm@vger.kernel.org>; Wed, 03 Feb 2021 16:01:26 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=dJo6kFJmEbDB5bd7UwfejFyX5EAfXMAcoGeIEuOMPVE=;
        b=LXBrWS18jYUSu1XYyoRbNvnW7+RCLFt9G/CkNYIhWsRiIYBFSAclDZCqdSqGABk/f2
         rFYNe7EKHGinwliL71Ix0Qpajzv6M3Uvvthdhhza5TUPgda2gUY07pi2ugWK71AqBkEN
         tWYSxngdvvbj6OQSJHdiIvQNsHn23Iyx8sv+zxtHFLizh8HhHGrtGpw4IoH6+nUzGC1Q
         60Lt74GI5mnekorZnff5V3CExZAcjtTrB4QRh2Gcuezj73SOrNUyLCa2RuRlMWN2etOj
         9PJcOM9fWxcSm6WoraxMMY7TkQYh/UqgvnKR4wGirRIkkdPmywXPfO8fYEQl6ZdspbFt
         HopQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=dJo6kFJmEbDB5bd7UwfejFyX5EAfXMAcoGeIEuOMPVE=;
        b=nfmp5/P8hjWpaHIkudc+uhnuGMDSvFB/C0C/drJ0hMRSNRWe2y2fj+FA41wNbM5kww
         lxKQmkyy7r3/ECmGX/Wrrk0SY1OtfGUrvbrYj+5qxeSqjGtsaYhpJdCD4Si9JDYNBByS
         /5Hl1otN+/THXbWrF0O3Cvw8yaglmDyP3uynXiqJyD0i8+XH8unmr0tST2zNd0wAeF//
         YJAlC08pvXUsvoEl8zSN+zde6tleC+Thrhqcilg+OSO8t5nTKA3vFthA01QMJGrroKzm
         Xh+QhBfuvq0pqUm2uOV741/5OfMwIqJBOGIYwXtbQQ5pYDDTspWv4Wy2fAJAJ88q0UEb
         V2mA==
X-Gm-Message-State: AOAM533kpBKP3WS9KwABgKvyzCwyYDi65gBL7DmoMXPELjxl5809qBtn
        ZI+tWPqD1UJ7uBSiG7s59mkXmsou/CY=
X-Google-Smtp-Source: 
 ABdhPJzglTMM62OFGD8AVIT2ZfIrJ1rejTRBMaEUSi4jzKdS5oPhiunBh0RtUHhDNDPsxCPUKCg0dPhtkBc=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:a9a0:e924:d161:b6cb])
 (user=seanjc job=sendgmr) by 2002:ad4:4742:: with SMTP id
 c2mr5131928qvx.46.1612396885867;
 Wed, 03 Feb 2021 16:01:25 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed,  3 Feb 2021 16:01:05 -0800
Message-Id: <20210204000117.3303214-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH 00/12] KVM: x86: Legal GPA fixes and cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Rick Edgecombe <rick.p.edgecombe@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add helpers to consolidate the GPA reserved bits checks that are scattered
all over KVM, and fix a few bugs in the process.

The original motivation was simply to get rid of all the different open
coded variations of the checks (there were a lot), but this snowballed
into a more ambitious cleanup when I realized common helpers are more or
less required to correctly handle repurposed GPA bits, e.g. SEV's C-bit.

The last two patches (use nested VM-Enter failure tracepoints in SVM)
aren't directly related to the GPA checks, but the conflicts would be
rather messy, so I included them here.

Note, the SEV C-bit changes are technically bug fixes, but getting them in
stable kernels would require backporting this entire pile.  IMO, it's not
worth the effort given that it's extremely unlikely anyone will encounter
the bugs in anything but synthetic negative tests.

Based on kvm/queue, commit 3f87cb8253c3 ("KVM: X86: Expose bus lock debug
exception to guest").

Sean Christopherson (12):
  KVM: x86: Set so called 'reserved CR3 bits in LM mask' at vCPU reset
  KVM: nSVM: Don't strip host's C-bit from guest's CR3 when reading
    PDPTRs
  KVM: x86: Add a helper to check for a legal GPA
  KVM: x86: Add a helper to handle legal GPA with an alignment
    requirement
  KVM: VMX: Use GPA legality helpers to replace open coded equivalents
  KVM: nSVM: Use common GPA helper to check for illegal CR3
  KVM: x86: SEV: Treat C-bit as legal GPA bit regardless of vCPU mode
  KVM: x86: Use reserved_gpa_bits to calculate reserved PxE bits
  KVM: x86/mmu: Add helper to generate mask of reserved HPA bits
  KVM: x86: Add helper to consolidate "raw" reserved GPA mask
    calculations
  KVM: x86: Move nVMX's consistency check macro to common code
  KVM: nSVM: Trace VM-Enter consistency check failures

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/cpuid.c            |  20 +++++-
 arch/x86/kvm/cpuid.h            |  24 +++++--
 arch/x86/kvm/mmu/mmu.c          | 110 ++++++++++++++++----------------
 arch/x86/kvm/mtrr.c             |  12 ++--
 arch/x86/kvm/svm/nested.c       |  35 +++++-----
 arch/x86/kvm/svm/svm.c          |   2 +-
 arch/x86/kvm/vmx/nested.c       |  34 +++-------
 arch/x86/kvm/vmx/vmx.c          |   2 +-
 arch/x86/kvm/x86.c              |  11 ++--
 arch/x86/kvm/x86.h              |   8 +++
 11 files changed, 140 insertions(+), 120 deletions(-)
```
#### [PATCH v10 00/17] Add AMD SEV guest live migration support
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Thu Feb  4 00:35:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12065841
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F41D6C433DB
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:36:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D7F564F6B
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:36:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234167AbhBDAgb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 19:36:31 -0500
Received: from mail-bn7nam10on2044.outbound.protection.outlook.com
 ([40.107.92.44]:55968
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233575AbhBDAg0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 19:36:26 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=EbnKD/8As3O3Uw+57afmgabbka8JMNFgIi6LFO9du1Lq0R2wLfGFdtOzFcJu2YCbrJr9F0HXuqqb1ypuhC/CFFtaQJ4bm5XLhrwOjY7UbwGIgqXVFXrYV+TyCOL/CHA7Gwdos58tbvRQ1HaZDjPb6mZHc1tCz8K4L5+Kn7gGJU7yOH0Oftr1KMezs/5pVLqWdzRtseg+GHg0gL01jOVSQH1+p63YqR5C9OHy5UXr6xQtgyS7HWZF9Sm1LkXwagKrEbkjx0BaEvH61vh3nSQt2BU/xIbohCNg+GNGpMqcppi4ud6Cwb6GjgW78RbNOnftAaZTRtBYZO9Xwx80rW0JVQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=R7T+vhpMPPLIGK0XLHtGgpLkvORNt5FKH7o03p7ELsM=;
 b=gK/smQp8m4XR7uxYHNK3h/QP/0V3c0JidqzIWAu1p0LOtQKpPT0RW/P2xwz0ppl9uiAKidMlubbg1nWZuaaW4tmP42ZPy9OFUZsJPnQeL7C0YTOIc0rBom7gGp3IkEyQ6cLiiW63KOdXXTOVqxcQL7vw0eaAEjNf4K+Y98UQpdL72spH4pdF5QylN/Lo05PqhTdNdfF7qGr27U5RF+aS7ufPmscOgNEeqYaDK59ifwBta4eP2r6/PssaM8YdargldBlCXq5YL+9JyMsjJKISGRh3xHzBI8MDnLHrI8hUbVPnPuCN47EwTelYZubMQqK2vm6PLFKyed6YepWeM6/OJQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=R7T+vhpMPPLIGK0XLHtGgpLkvORNt5FKH7o03p7ELsM=;
 b=xa7aiyUGxQYn1oM0HElhTdTkdfQ3mBHWyMRb0tLhpXdRhvc50lh+SWOLOS99Qgtkxr/oYYUUW+m1BjEvydr0WPJvPCpN8k4c2/EU3XQYPSmuycUZAEg4tfN+haguGypwpHFBQp4a/Lr6oRgwClIQtNmuW3JS4OUSMzwdgSjQlGo=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4384.namprd12.prod.outlook.com (2603:10b6:806:9f::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16; Thu, 4 Feb
 2021 00:35:31 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::24bb:3e53:c95e:cb8e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::24bb:3e53:c95e:cb8e%7]) with mapi id 15.20.3805.028; Thu, 4 Feb 2021
 00:35:31 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, srutherford@google.com,
        seanjc@google.com, venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v10 00/17] Add AMD SEV guest live migration support
Date: Thu,  4 Feb 2021 00:35:22 +0000
Message-Id: <cover.1612398155.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0091.namprd04.prod.outlook.com
 (2603:10b6:806:122::6) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN7PR04CA0091.namprd04.prod.outlook.com (2603:10b6:806:122::6) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.17 via Frontend
 Transport; Thu, 4 Feb 2021 00:35:31 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 89a5064d-b174-47d2-7f88-08d8c8a4c718
X-MS-TrafficTypeDiagnostic: SA0PR12MB4384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4384B002174F2A217CDF1BA08EB39@SA0PR12MB4384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:229;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 UDhpB7XIkMq81uygGRz+7QFBZtnAin1f8YWN0zOFZVbFWl52d0b+EYRXHpDOe54GtfKaRuUADyMtxEU90zWc6oqTr4O2sGTqZSCu60Uv77b9MXy3tnE2ukjxQYqkn3Ca+t7c+jep7gE6xHeGrw9FBp4pwj3mSfhPvdJQ7Z4mk+MVkjCzjeQiPnm0IEghGId2dEVhaip0Uml58khVULHnCTF33R2RTlce6iUizBFZaiNPGx2qDo+sMSjUwvGFLBeXplpl9l1s56LeslxHHPuFeZWeROiRIbXLR/cm3vpO9A+FRCWwaDy9K56uBH19I91I4vwO3/tpC4eEi5c8YMKAEkjmXkbMYPe6Lyzn1ELkY9mSEkZflkv8Zy4GHdpH3rzJBd9+im9Czvbw38+1S4s1vbpP838seWKKmTO+YSZ8cv4dkUVdIaUX52e1U56zJAgh1zoJvLRY6e5/qN4KM81FVrdVN3M2z1uvqKgiwTMMUZJ4U/a0j9qrlkEIkUG0iQin+7bBzuCq2VcQuJDtBjcp4dj7DP32fSU2odRCMjrJcNn4ucRDa1aykUJ/hq0YqPd4Z12CkVb9LVS+EEYaEPA2F3+z6VB99MjgdRkR/U4DNT8=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(39860400002)(366004)(346002)(376002)(396003)(8936002)(4326008)(66556008)(86362001)(6666004)(66476007)(2906002)(186003)(478600001)(26005)(6916009)(6486002)(966005)(5660300002)(52116002)(16526019)(36756003)(7696005)(7416002)(66946007)(83380400001)(8676002)(956004)(2616005)(316002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?bCz38WJnIgbSyONxmR7JSMUQIgw1hJ?=
	=?utf-8?q?LPv3rv8YsM1Pa7gWdtDU058JH+Cze2rznOzyYppqYFw9S4Rk9D5BcfWu5tzRL+/pU?=
	=?utf-8?q?hHypWMwus67Tb9pL5pu1Jb5xyyP0UjPxJ13HhxjNCXXR3E8gIbHx/Es9v99TcZDC0?=
	=?utf-8?q?BFzRMgPeMHuwgn/3+6hJm5bTvcpKcF5sApjLqWp3ey7Rvca7fcr5cQf43kurPdcLH?=
	=?utf-8?q?8o5VcYP+r4XbptDdUENB1R8UOsLs+d/IbvfPgkCB44aRPMDQG5bxGXX+9+mtct+bv?=
	=?utf-8?q?bTKVV1zPcNftHU51R7ckPy9BnYqhQY5HQURa+qUra5kSoHzdXH5zneHplqVQWnbo8?=
	=?utf-8?q?LoQoq6GHWvA54qPwPIlSB2PJtDe3soNYsrR7MCLmC2fDxtVtfKKMph0pTRglV09qf?=
	=?utf-8?q?B8TueKOKcqS33mCYWtfnBBoCymjcu8v9+M4DtaLDe4a1DyBZoC2P/q7/Op7hwKhB7?=
	=?utf-8?q?THDQSMOPPmJCoGYfvpI/C8U+1s7TxLWI6sbG+iLc1VEl2sRRHHcXUZ8mF7vGSYiIf?=
	=?utf-8?q?QK8/M3YM8+bgiDFDoB+w3Yn3sWh8VGmk/kJyz7iOgVyw13ToUfcfdx/SUH1/4wPDp?=
	=?utf-8?q?kCpZPOIynS0hubXRksd6qcgKDz+RCcGMV9xUp5ebUW9YkAfnufp4MXTfQzYjFZB9y?=
	=?utf-8?q?h6Q0Eg/3zT6AuGCURQ2oz5R7W4cAUv0pAVZ0PDGIMZPVe6nH9NqUx7ITIMa95jt8p?=
	=?utf-8?q?nMexjJZvxx+Ka53f42zVOI6zMjay4OVpWxoDw1f0yrVhFHMWdHjRYCeFUKRkDz5JZ?=
	=?utf-8?q?wGH6cYl9s+ZARInsPqdM3J3vW6f/n0eGugKOr8aItEW1vGCW+xUa7fh99u6Ql/M8R?=
	=?utf-8?q?pjIXNgO64Hm5AlobISbGE1ucVlWM/UE6wBbO1bg2wbEyizSEqw69Nw7RltW/6ku3V?=
	=?utf-8?q?LYH+K+w98cfXPlWKLtIfwICi1fWuMQ/6t42EFltVIs9ng1Sijl0uROJh6C9Opfrii?=
	=?utf-8?q?rEiYW+pwzA+vvQWyteb4VOOqRAaJwc7IUMumWUIbB+8OAdz9ypDWU/NcloWaz+ITQ?=
	=?utf-8?q?g7i743QKb8kp8grfxTmrduaA0BnQzqIKBb3KcIyFPWnVeZH3hFaDUddqSjx22Vt83?=
	=?utf-8?q?Q4nILvtb0gCoGndI1I48592Z48sjEnxZg3U7BFGAdv3aCeX+CMAMPc5DLWHi+7lZK?=
	=?utf-8?q?K/0zusaTDyKwNkspKyjl88MdG9ZaUp3Nm94/S9lomTwUbNRbzLc/1zxUjUi6dxHTk?=
	=?utf-8?q?S+cw1uBYIPmIVdlGfdwH6vFOI7gKT5mHnkKcSvUh2GGwKVLIQo1KcsCbfHGjV7Xeq?=
	=?utf-8?q?GsF+3IXAz89vGj?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 89a5064d-b174-47d2-7f88-08d8c8a4c718
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Feb 2021 00:35:31.5357
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 sXHXYWnGVuvXxb0p1dD/quLF+LKX7H1h8QZOq34cbfSbnFuqRvTVPx066pOSwaYo2h4zcp5CJ+WrChzewjqo3g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4384
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series add support for AMD SEV guest live migration commands. To protect the
confidentiality of an SEV protected guest memory while in transit we need to
use the SEV commands defined in SEV API spec [1].

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The commands provided by the SEV FW are meant to be used
for the private memory only. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.
If the page is encrypted with guest specific-key then we use SEV command during
the migration. If page is not encrypted then fallback to default.

The patch adds new ioctls KVM_{SET,GET}_SHARED_PAGES_LIST. The ioctl can be used
by the qemu to get the shared pages list. Qemu can consult this list
during the migration to know whether the page is encrypted.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR. The host returns error as part of
KVM_GET_SHARED_PAGES_LIST ioctl if guest has not enabled live migration.

A branch containing these patches is available here:
https://github.com/AMDESE/linux/tree/sev-migration-v10

[1] https://developer.amd.com/wp-content/resources/55766.PDF

Changes since v9:
- Transitioning from page encryption bitmap to the shared pages list
  to keep track of guest's shared/unencrypted memory regions.
- Move back to marking the complete _bss_decrypted section as 
  decrypted in the shared pages list.
- Invoke a new function check_kvm_sev_migration() via kvm_init_platform()
  for guest to query for host-side support for SEV live migration 
  and to enable the SEV live migration feature, to avoid
  #ifdefs in code 
- Rename MSR_KVM_SEV_LIVE_MIG_EN to MSR_KVM_SEV_LIVE_MIGRATION.
- Invoke a new function handle_unencrypted_region() from 
  sev_dbg_crypt() to bypass unencrypted guest memory regions.

Changes since v8:
- Rebasing to kvm next branch.
- Fixed and added comments as per review feedback on v8 patches.
- Removed implicitly enabling live migration for incoming VMs in
  in KVM_SET_PAGE_ENC_BITMAP, it is now done via KVM_SET_MSR ioctl.
- Adds support for bypassing unencrypted guest memory regions for
  DBG_DECRYPT API calls, guest memory region encryption status in
  sev_dbg_decrypt() is referenced using the page encryption bitmap.

Changes since v7:
- Removed the hypervisor specific hypercall/paravirt callback for
  SEV live migration and moved back to calling kvm_sev_hypercall3 
  directly.
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>, specifically fixed
  build error when CONFIG_HYPERVISOR_GUEST=y and
  CONFIG_AMD_MEM_ENCRYPT=n.
- Implicitly enabled live migration for incoming VM(s) to handle 
  A->B->C->... VM migrations.
- Fixed Documentation as per comments on v6 patches.
- Fixed error return path in sev_send_update_data() as per comments 
  on v6 patches. 

Changes since v6:
- Rebasing to mainline and refactoring to the new split SVM
  infrastructre.
- Move to static allocation of the unified Page Encryption bitmap
  instead of the dynamic resizing of the bitmap, the static allocation
  is done implicitly by extending kvm_arch_commit_memory_region() callack
  to add svm specific x86_ops which can read the userspace provided memory
  region/memslots and calculate the amount of guest RAM managed by the KVM
  and grow the bitmap.
- Fixed KVM_SET_PAGE_ENC_BITMAP ioctl to set the whole bitmap instead
  of simply clearing specific bits.
- Removed KVM_PAGE_ENC_BITMAP_RESET ioctl, which is now performed using
  KVM_SET_PAGE_ENC_BITMAP.
- Extended guest support for enabling Live Migration feature by adding a
  check for UEFI environment variable indicating OVMF support for Live
  Migration feature and additionally checking for KVM capability for the
  same feature. If not booted under EFI, then we simply check for KVM
  capability.
- Add hypervisor specific hypercall for SEV live migration by adding
  a new paravirt callback as part of x86_hyper_runtime.
  (x86 hypervisor specific runtime callbacks)
- Moving MSR handling for MSR_KVM_SEV_LIVE_MIG_EN into svm/sev code 
  and adding check for SEV live migration enabled by guest in the 
  KVM_GET_PAGE_ENC_BITMAP ioctl.
- Instead of the complete __bss_decrypted section, only specific variables
  such as hv_clock_boot and wall_clock are marked as decrypted in the
  page encryption bitmap

Changes since v5:
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>

Changes since v4:
- Host support has been added to extend KVM capabilities/feature bits to 
  include a new KVM_FEATURE_SEV_LIVE_MIGRATION, which the guest can
  query for host-side support for SEV live migration and a new custom MSR
  MSR_KVM_SEV_LIVE_MIG_EN is added for guest to enable the SEV live
  migration feature.
- Ensure that _bss_decrypted section is marked as decrypted in the
  page encryption bitmap.
- Fixing KVM_GET_PAGE_ENC_BITMAP ioctl to return the correct bitmap
  as per the number of pages being requested by the user. Ensure that
  we only copy bmap->num_pages bytes in the userspace buffer, if
  bmap->num_pages is not byte aligned we read the trailing bits
  from the userspace and copy those bits as is. This fixes guest
  page(s) corruption issues observed after migration completion.
- Add kexec support for SEV Live Migration to reset the host's
  page encryption bitmap related to kernel specific page encryption
  status settings before we load a new kernel by kexec. We cannot
  reset the complete page encryption bitmap here as we need to
  retain the UEFI/OVMF firmware specific settings.

Changes since v3:
- Rebasing to mainline and testing.
- Adding a new KVM_PAGE_ENC_BITMAP_RESET ioctl, which resets the 
  page encryption bitmap on a guest reboot event.
- Adding a more reliable sanity check for GPA range being passed to
  the hypercall to ensure that guest MMIO ranges are also marked
  in the page encryption bitmap.

Changes since v2:
 - reset the page encryption bitmap on vcpu reboot

Changes since v1:
 - Add support to share the page encryption between the source and target
   machine.
 - Fix review feedbacks from Tom Lendacky.
 - Add check to limit the session blob length.
 - Update KVM_GET_PAGE_ENC_BITMAP icotl to use the base_gfn instead of
   the memory slot when querying the bitmap.

Ashish Kalra (5):
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  KVM: x86: Add guest support for detecting and enabling SEV Live
    Migration feature.
  KVM: x86: Add kexec support for SEV Live Migration.
  KVM: SVM: Bypass DBG_DECRYPT API calls for unencrypted guest memory.

Brijesh Singh (11):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  mm: x86: Invoke hypercall when page encryption status is changed
  KVM: x86: Introduce KVM_GET_SHARED_PAGES_LIST ioctl
  KVM: x86: Introduce KVM_SET_SHARED_PAGES_LIST ioctl

 .../virt/kvm/amd-memory-encryption.rst        | 120 +++
 Documentation/virt/kvm/api.rst                |  44 +-
 Documentation/virt/kvm/cpuid.rst              |   5 +
 Documentation/virt/kvm/hypercalls.rst         |  15 +
 Documentation/virt/kvm/msr.rst                |  12 +
 arch/x86/include/asm/kvm_host.h               |   6 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |   8 +
 arch/x86/include/asm/paravirt.h               |  10 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/include/uapi/asm/kvm_para.h          |   4 +
 arch/x86/kernel/kvm.c                         |  80 ++
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/svm/sev.c                        | 861 ++++++++++++++++++
 arch/x86/kvm/svm/svm.c                        |  20 +
 arch/x86/kvm/svm/svm.h                        |   9 +
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  30 +
 arch/x86/mm/mem_encrypt.c                     |  98 +-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/efi.h                           |   1 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  49 +
 include/uapi/linux/kvm_para.h                 |   1 +
 24 files changed, 1398 insertions(+), 6 deletions(-)
```
#### [PATCH v2 0/6] Add SBI v0.2 support for KVM
##### From: Atish Patra <atish.patra@wdc.com>

```c
From patchwork Thu Feb  4 05:32:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Atish Patra <atish.patra@wdc.com>
X-Patchwork-Id: 12066315
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6F0F7C433DB
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 05:34:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16EEA64F47
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 05:34:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231301AbhBDFeC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 00:34:02 -0500
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:38827 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230296AbhBDFd7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Feb 2021 00:33:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1612416838; x=1643952838;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=20GUJPs0xyqN+1X8CUwsioLenuUNs3sUWwKF/m/Mk9Y=;
  b=p4yaqB2PxgzGYeWbUZxufrfBz7e1OeBZ9RJBJexX1wHnWGm/YYbeFScl
   d6F61RIIrSFciNdM6Qmx/f8urloQQKB4s7Z5PZw6+KlKfBacRC5Vh1788
   v+jvgFFGh6V6znBz2qsw75lfsM4dNOfJyRD3gV4hV2mNCnIl1lcwtz+fe
   0AANyQ3W1RS6NXZjECIL4i6EXdR+chgGUIcvEYTRa7bfy1AFkFZ5IUK1t
   w/ZapTXQfKH1DslkYFmXkRqHJ83UnorO+VM2p/z7sOeM0jVtCGcTsO1nr
   JuDdw3oP8P8ACIbddcfBqn0mzF1TWsuh6VpMiWmJy8FT8uiuaypPaif9w
   g==;
IronPort-SDR: 
 seXQQEioeE7HRMTe6vg8MmP5TuN9qB8sRCqrHzhXOEeKKhek8gz6T9WccNDOFRWlA2gZomWTQS
 FE8wS4nzzPkDbjav87WRsdlR878ndj84OEiMjHlOHke4SFDKtqWA5R1y9TTmaS2WnwSgMQUR06
 36ShjSarMcGPHAsTA/d8TrDfT7CjyyEK+iIbDsDEmhDpEKN8fXjRunzsQStttaKuuCkYs2Br1C
 S44JPX4J/2bF39J2uvly7Imk00V1NiQFtTlvdtSKDwWmgWQR1CeJAmem46oXgw19epqtMJKQoy
 tlo=
X-IronPort-AV: E=Sophos;i="5.79,400,1602518400";
   d="scan'208";a="159086429"
Received: from uls-op-cesaip01.wdc.com (HELO uls-op-cesaep01.wdc.com)
 ([199.255.45.14])
  by ob1.hgst.iphmx.com with ESMTP; 04 Feb 2021 13:32:53 +0800
IronPort-SDR: 
 73oREEvUI6kSAfKFCfpaLH+9dS0vfMqpSFHJw6yYQauYgEaS5bvGbau9Ay01zs2y8r19rM1O9k
 ub9n4xYxB8xKHD1xsXaJaGtwrbfRemxISTjrMrz6yvwzkdA3TFLBZRUXBkcB8SGofqgx2k+Dm/
 vVlxF17t2ezOUABxdwokkJk1+6FRLP85oj3Ndt88eNokfJTjAv2hRbUbmxoFV/xu+3khIXJsDv
 TjrQ32t7cCth2+WlRVHcY7X8svnEhwOhbjSOUJelRTpQz+GIBljYrxznjE+xdddAcmeVyqgcWV
 qigmNXFp1xeFh5VsDdxNNH1Q
Received: from uls-op-cesaip02.wdc.com ([10.248.3.37])
  by uls-op-cesaep01.wdc.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 21:16:53 -0800
IronPort-SDR: 
 /PPwS0VvJF+wkXfdg85sqhiMnov/J2WUM+ZcZeMpj7Oy/VR1taKs8zTdU2Zgkbp0Qpag7T8Efe
 /FCe9i/YXycJ9hbVk3o2oJsLfVpqZTukVrhD8tCO9JxVV42JfdN/FK/GmODHyqo97074r/3K2L
 qdRk2b0AEUEWkl7JUuNHSiHNjmPAG0bK5ucvPOIV1by4hoQkxyQzc73hN38QAob/H18LO1n8nb
 fNzv9cMCSTcaUSbVKmYCbm46fkqNhD4uJLR7UYrnOVF4F4RNo2aeJZwhHLc1/2ZYq17W/oR8+f
 RTY=
WDCIronportException: Internal
Received: from cnf008142.ad.shared (HELO jedi-01.hgst.com) ([10.86.63.165])
  by uls-op-cesaip02.wdc.com with ESMTP; 03 Feb 2021 21:32:53 -0800
From: Atish Patra <atish.patra@wdc.com>
To: linux-kernel@vger.kernel.org
Cc: Atish Patra <atish.patra@wdc.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Anup Patel <anup.patel@wdc.com>,
        Kefeng Wang <wangkefeng.wang@huawei.com>,
        kvm-riscv@lists.infradead.org, kvm@vger.kernel.org,
        linux-riscv@lists.infradead.org,
        Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>
Subject: [PATCH v2 0/6] Add SBI v0.2 support for KVM
Date: Wed,  3 Feb 2021 21:32:33 -0800
Message-Id: <20210204053239.1609558-1-atish.patra@wdc.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Supervisor Binary Interface(SBI) specification[1] now defines a
base extension that provides extendability to add future extensions
while maintaining backward compatibility with previous versions.
The new version is defined as 0.2 and older version is marked as 0.1.

This series adds following features to RISC-V Linux KVM.
1. Adds support for SBI v0.2 in KVM
2. SBI Hart state management extension (HSM) in KVM
3. Ordered booting of guest vcpus in guest Linux
4. SBI Reset extension in KVM

This series depends on the base kvm support series v16[2].

Guest kernel needs to also support SBI v0.2 and HSM extension in Kernel
to boot multiple vcpus. Linux kernel supports both starting v5.7.
In absense of that, guest can only boot 1 vcpu.

Changes from v1->v2:
1. Sent the patch 1 separately as it can merged independently.
2. Added Reset extension functionality.

Tested on Qemu and FPGA with Rocket core design.

[1] https://github.com/riscv/riscv-sbi-doc/blob/master/riscv-sbi.adoc
[2] http://lists.infradead.org/pipermail/linux-riscv/2021-January/004251.html

Atish Patra (6):
RISC-V: Mark the existing SBI v0.1 implementation as legacy
RISC-V: Reorganize SBI code by moving legacy SBI to its own file
RISC-V: Add SBI v0.2 base extension
RISC-V: Add v0.1 replacement SBI extensions defined in v02
RISC-V: Add SBI HSM extension in KVM
RISC-V: Add SBI RESET extension in KVM

arch/riscv/include/asm/kvm_vcpu_sbi.h |  33 +++++
arch/riscv/include/asm/sbi.h          |   9 ++
arch/riscv/kvm/Makefile               |   4 +-
arch/riscv/kvm/vcpu.c                 |  19 +++
arch/riscv/kvm/vcpu_sbi.c             | 189 +++++++++++++-------------
arch/riscv/kvm/vcpu_sbi_base.c        |  73 ++++++++++
arch/riscv/kvm/vcpu_sbi_hsm.c         | 109 +++++++++++++++
arch/riscv/kvm/vcpu_sbi_legacy.c      | 114 ++++++++++++++++
arch/riscv/kvm/vcpu_sbi_replace.c     | 180 ++++++++++++++++++++++++
9 files changed, 635 insertions(+), 95 deletions(-)
create mode 100644 arch/riscv/include/asm/kvm_vcpu_sbi.h
create mode 100644 arch/riscv/kvm/vcpu_sbi_base.c
create mode 100644 arch/riscv/kvm/vcpu_sbi_hsm.c
create mode 100644 arch/riscv/kvm/vcpu_sbi_legacy.c
create mode 100644 arch/riscv/kvm/vcpu_sbi_replace.c
---
2.25.1
```
#### [PATCH v2 0/2] KVM: x86: cleanups for MOV from/to DR
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Feb  4 14:54:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12067813
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9CEB8C433E0
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 16:42:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 556CC64F43
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 16:42:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236983AbhBDQl6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 11:41:58 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51203 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236828AbhBDO4E (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Feb 2021 09:56:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612450479;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ryp3p6DrRmlDDRDQgmrayD8IdcDXnf65jisZJnC4oKY=;
        b=OcHPZspHx+UZLaRSgUsH1xJL9+st3Cfoln7p5MygJgwpE5dvelcw/7mEQUm7WEuPmY0YFH
        BKoM8XuX4pBQb0CMBtYYifCsvUaPEiwY9yLA1eXvJLGIuV8s/a4iDzb4ca87NJRgqaH/bn
        WLTHjYjBPCqRrATjp9kxxuOeXdIPzp0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-74-vmuJiG3TMniMS0-JCckPLg-1; Thu, 04 Feb 2021 09:54:35 -0500
X-MC-Unique: vmuJiG3TMniMS0-JCckPLg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 664AB100C612;
        Thu,  4 Feb 2021 14:54:34 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1768060BE2;
        Thu,  4 Feb 2021 14:54:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com
Subject: [PATCH v2 0/2] KVM: x86: cleanups for MOV from/to DR
Date: Thu,  4 Feb 2021 09:54:31 -0500
Message-Id: <20210204145433.243806-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the new version of the "KVM: x86: move kvm_inject_gp up from
kvm_set_dr to callers" patch.

Paolo Bonzini (2):
  KVM: x86: reading DR cannot fail
  KVM: x86: move kvm_inject_gp up from kvm_set_dr to callers

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/kvm_emulate.h      |  2 +-
 arch/x86/kvm/svm/svm.c          | 13 +++++--------
 arch/x86/kvm/vmx/vmx.c          | 20 +++++++++++---------
 arch/x86/kvm/x86.c              | 28 +++++++++-------------------
 5 files changed, 27 insertions(+), 38 deletions(-)
```
#### [PATCH v3 00/13] vdpa: add vdpa simulator for block device
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Feb  4 17:22:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12068011
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 75D66C433E0
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 17:24:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3836F64F65
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 17:24:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238470AbhBDRYd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 12:24:33 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:36392 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S238465AbhBDRYK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Feb 2021 12:24:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612459362;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=Zc+XWtfGtASjsMASpHkffR1pL11AhNAnMUdubmKUbE8=;
        b=HDqF/3CD1/j+1U2Nr7g260J0ChyEqqwEL3QfH1OqilRzY7xcjyu/Mt+7vo+viGXpcGSanI
        o4lCf8yUU5C7483MXbxnTBbIrRf2Ag7BU5n1vCIHHtOrlUjq7dNeV7lFLogcKtNVQp5FeV
        kgEKH9bmGYVsVvQwyepNrCRkxKtU4pI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-530-GuaFadePOfu83dcFO57M_A-1; Thu, 04 Feb 2021 12:22:41 -0500
X-MC-Unique: GuaFadePOfu83dcFO57M_A-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E2E1C879A0D;
        Thu,  4 Feb 2021 17:22:39 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-213.ams2.redhat.com
 [10.36.113.213])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4092D1A87C;
        Thu,  4 Feb 2021 17:22:31 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: Stefano Garzarella <sgarzare@redhat.com>,
        Xie Yongji <xieyongji@bytedance.com>, kvm@vger.kernel.org,
        Laurent Vivier <lvivier@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        linux-kernel@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>
Subject: [PATCH v3 00/13] vdpa: add vdpa simulator for block device
Date: Thu,  4 Feb 2021 18:22:17 +0100
Message-Id: <20210204172230.85853-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
- added new patches
  - 'vringh: explain more about cleaning riov and wiov'
  - 'vdpa: add return value to get_config/set_config callbacks'
  - 'vhost/vdpa: remove vhost_vdpa_config_validate()'
- split Xie's patch 'vhost/vdpa: Remove the restriction that only supports
  virtio-net devices'
- updated Mellanox copyright to NVIDIA [Max]
- explained in the 'vdpa: add vdpa simulator for block device' commit
  message that inputs are validated in subsequent patches [Stefan]

v2: https://lore.kernel.org/lkml/20210128144127.113245-1-sgarzare@redhat.com/
v1: https://lore.kernel.org/lkml/93f207c0-61e6-3696-f218-e7d7ea9a7c93@redhat.com/

This series is the second part of the v1 linked above. The first part with
refactoring of vdpa_sim has already been merged.

The patches are based on Max Gurtovoy's work and extend the block simulator to
have a ramdisk behaviour.

As mentioned in the v1 there was 2 issues and I fixed them in this series:
1. The identical mapping in the IOMMU used until now in vdpa_sim created issues
   when mapping different virtual pages with the same physical address.
   Fixed by patch "vdpa_sim: use iova module to allocate IOVA addresses"

2. There was a race accessing the IOMMU between the vdpasim_blk_work() and the
   device driver that map/unmap DMA regions. Fixed by patch "vringh: add
   'iotlb_lock' to synchronize iotlb accesses"

I used the Xie's patch coming from VDUSE series to allow vhost-vdpa to use
block devices. As Jason suggested I split it into two patches and I added
a return value to get_config()/set_config() callbacks.

The series also includes small fixes for vringh, vdpa, and vdpa_sim that I
discovered while implementing and testing the block simulator.

Thanks for your feedback,
Stefano

Max Gurtovoy (1):
  vdpa: add vdpa simulator for block device

Stefano Garzarella (11):
  vdpa_sim: use iova module to allocate IOVA addresses
  vringh: add 'iotlb_lock' to synchronize iotlb accesses
  vringh: reset kiov 'consumed' field in __vringh_iov()
  vringh: explain more about cleaning riov and wiov
  vringh: implement vringh_kiov_advance()
  vringh: add vringh_kiov_length() helper
  vdpa_sim: cleanup kiovs in vdpasim_free()
  vdpa: add return value to get_config/set_config callbacks
  vhost/vdpa: remove vhost_vdpa_config_validate()
  vdpa_sim_blk: implement ramdisk behaviour
  vdpa_sim_blk: handle VIRTIO_BLK_T_GET_ID

Xie Yongji (1):
  vhost/vdpa: Remove the restriction that only supports virtio-net
    devices

 drivers/vdpa/vdpa_sim/vdpa_sim.h     |   2 +
 include/linux/vdpa.h                 |  18 +-
 include/linux/vringh.h               |  19 +-
 drivers/vdpa/ifcvf/ifcvf_main.c      |  24 ++-
 drivers/vdpa/mlx5/net/mlx5_vnet.c    |  17 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c     | 134 ++++++++-----
 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c | 288 +++++++++++++++++++++++++++
 drivers/vhost/vdpa.c                 |  47 ++---
 drivers/vhost/vringh.c               |  69 +++++--
 drivers/vdpa/Kconfig                 |   8 +
 drivers/vdpa/vdpa_sim/Makefile       |   1 +
 11 files changed, 504 insertions(+), 123 deletions(-)
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c
```
