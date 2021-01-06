

#### [PATCH 0/2] Enumerate and expose AVX_VNNI feature
##### From: Yang Zhong <yang.zhong@intel.com>

```c
From patchwork Tue Jan  5 00:49:07 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Zhong <yang.zhong@intel.com>
X-Patchwork-Id: 11997963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 54DF2C433E0
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 01:42:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29218225AC
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 01:42:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726980AbhAEBmk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 20:42:40 -0500
Received: from mga03.intel.com ([134.134.136.65]:49886 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726026AbhAEBmk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 20:42:40 -0500
IronPort-SDR: 
 BYYD49Ly8qt4XAtI8VpiGiqbFk+VV1Y2tJ8MNyOUqCwTlCwPafkxITdaIr5tXbHWaQYYHfjLdU
 hiab11EL4MeQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9854"; a="177136723"
X-IronPort-AV: E=Sophos;i="5.78,475,1599548400";
   d="scan'208";a="177136723"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jan 2021 17:41:59 -0800
IronPort-SDR: 
 cg/gx9202VTgH7fROrtiORB2QgDHwNlGyq3W6jb5D8KbBGYsMkSrptBnZ8pZVFrPybciWbFgdd
 qIpJJQY+VWxg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,475,1599548400";
   d="scan'208";a="350166544"
Received: from icx-2s.bj.intel.com ([10.240.192.119])
  by fmsmga008.fm.intel.com with ESMTP; 04 Jan 2021 17:41:55 -0800
From: Yang Zhong <yang.zhong@intel.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        tony.luck@intel.com, pbonzini@redhat.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, kyung.min.park@intel.com, yang.zhong@intel.com
Subject: [PATCH 0/2] Enumerate and expose AVX_VNNI feature
Date: Tue,  5 Jan 2021 08:49:07 +0800
Message-Id: <20210105004909.42000-1-yang.zhong@intel.com>
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
#### [PATCH 0/3] KVM: SVM: Refactor vcpu_load/put to use vmload/vmsave for
##### From: Michael Roth <michael.roth@amd.com>

```c
From patchwork Tue Jan  5 14:37:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 11999163
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0904C4332E
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 14:39:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 93C7F22BE9
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 14:39:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727342AbhAEOjl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 09:39:41 -0500
Received: from mail-dm6nam11hn2228.outbound.protection.outlook.com
 ([52.100.172.228]:6314
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725817AbhAEOjk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 09:39:40 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Ibax0GGSojuBDFWf/o84QaX/ivjkWU2np9f1CZiXCPItHBbJAYArUfq+9Mx/asYyjbG8Kr3lK59AfAGM6HLWWnZW0/rE74Ntvd3ujk4E22vGFqiQmZb1QUlEWgb8AP1toPaWb++grCrOdBuJiDotFC2wxmY4QVwky+SyOy8dohqed2ho1To0Nh0ncj5Mtphz5nZdw8Mmd7CetNRG4GvSCYcyKd/7J+1Nuz4zrluHlXFqhhbvYctDPGs4K3ykeLEQj6gcBg3uK0Ft64DaixT/5XWTnoN8oq10EWlNzfahjbshwkTk7tojDz7ec2fjZSC84l8deUWvbYbN2UnuKFuCxg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ehNs1Cd0ppuCZL394Qu1frD2rY8V/+cptk01PCn1Oa8=;
 b=GkMsO7bEmheK83wlXVSIXa6L2lgSaSjwzEhQtZmO35f8DbhmPF5dGYA+j8gLtalMiS8StvuUBLW/d5wXkgCPDihZNNYjib4Mamw3lqO8oL5tXZI1ZP6IFNP7sx91AT9F2hygZIIEb6yWcGpjib7Vcpsh2Qx4rRL71FRY3NkJTmZLnAwAG+k5ydXnobqFdSr8iGQTv80vCqzb2HgIoLwFBzSCyx6UkVnCfd1aODneMUj949XCZuy2MCrb52AVkEE3vmvSvIz80d+ldEr29HUguY1ixe7HfFItS5rPZdyUFILYy9I/3eKq1zkPFIOamgnma/sb3eFH1YJ+TSqQrfPYHw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ehNs1Cd0ppuCZL394Qu1frD2rY8V/+cptk01PCn1Oa8=;
 b=Xs2rWdfqIqmWK6j65jRwmLdGe9NBRp80TwcR8DQ4aSPZcvNJlKlTLxA/jeSTC4/TRqQy+hiV13cyPc9flLaavPwhPN/J1ljhiQEG7vIo0YhSAi3i3cgYr5Y5vnD+bXb9cQ1lL4bz7zzxlSzor6rn4PHzG2d8dwUi6Obg7LW4QUU=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
 by CH2PR12MB3957.namprd12.prod.outlook.com (2603:10b6:610:2c::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3721.20; Tue, 5 Jan
 2021 14:38:49 +0000
Received: from CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::b965:3158:a370:d81e]) by CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::b965:3158:a370:d81e%7]) with mapi id 15.20.3721.024; Tue, 5 Jan 2021
 14:38:49 +0000
From: Michael Roth <michael.roth@amd.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Andy Lutomirski <luto@amacapital.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] KVM: SVM: Refactor vcpu_load/put to use vmload/vmsave for
 host state
Date: Tue,  5 Jan 2021 08:37:47 -0600
Message-Id: <20210105143749.557054-1-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [165.204.54.211]
X-ClientProxiedBy: YT1PR01CA0069.CANPRD01.PROD.OUTLOOK.COM
 (2603:10b6:b01:2d::8) To CH2PR12MB4133.namprd12.prod.outlook.com
 (2603:10b6:610:7a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.54.211) by
 YT1PR01CA0069.CANPRD01.PROD.OUTLOOK.COM (2603:10b6:b01:2d::8) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.6 via Frontend
 Transport; Tue, 5 Jan 2021 14:38:49 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 3c23e8fa-a579-43c0-3b8b-08d8b1879da3
X-MS-TrafficTypeDiagnostic: CH2PR12MB3957:
X-Microsoft-Antispam-PRVS: 
 <CH2PR12MB3957FD06D89AB0F4974193B495D10@CH2PR12MB3957.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 HGoUkm9KMS8+s0FW2CeZnUFZjmR6UXOHhh5RO100MzGeu1IeIqftPmFhS723KxqJLX/R5lBeDweosNuRgD3rBKSD6xa3C36tD5sxU7Mi5P9V6UpIUgG3ulgN2DCmy8Atp9iUboPhJ4UCzOg2SUdMLaSFLycJgKkB+jdtKsmCnwRf3v3B9i6JjDgPfrn32dk+aQf6go8Ypb7IeRrPipM2B4+CT4ND81kaTXWcOmoEp94wUOf08owFi+dtl4VddVhubASRFN+WwcyE23MPYv3phoxuMQ+ccv1KSkplzJyBHFiVXiy/IdP+F/nOK3aPgHXfK2K9+MGvaUwGzloTZdKEFmh8vJ/lM+G2Xm3r7fVldXRl85RiKFNY1P53YkeJnrJEg5p3YNrpwJOeFTAIQlb4cQRuzAtMwArZrCbSOoB5kjc0wl/fCjXbrmsbVSeNU8TPbfHCRUqmVZuO8UV9AfsW5AmE3N859Gp/o7OG67htNJyYVASQTq6yfmBxL931XzJfLv6OGX3LEwpEvJyVk3ep3feGF1olntAahtztFuX0r8/0iJ0A7aJnUYK6y5itQ8ELYCFj+LCkfRW00w+f/IxJp5yy1HtZRWExUkI17TBNABYta5FK3saPXWwyuhDOhN1A34Jt+V8aXhhnY4jDogvzg2qzHGjlxHwvyaN26gPDzUrYGCC0/uOkI1oxYi2oqorfcyyx0n39SsqAj4WDiJhOgVG3A2YrHPrw8QUeiSQlzWAHY4kQumE23z1Gacu9V2lh
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:CH2PR12MB4133.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(39860400002)(136003)(366004)(376002)(346002)(396003)(83380400001)(2906002)(26005)(4326008)(52116002)(8936002)(8676002)(956004)(2616005)(44832011)(186003)(86362001)(16526019)(66476007)(66556008)(6486002)(5660300002)(66946007)(6496006)(36756003)(478600001)(7416002)(316002)(6916009)(1076003)(54906003)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 B0hsSTyYCQwSm7aGzw3MTeVozQOlEOObbf+fqMu7mo7vJTATdDI/IujR8hTLBVJGxUR7tJRzJFXiYvQb9ZgmL4aLD09Wh2BcDZg6cPQJJ7JfU70iMJ01TgBfD6pGW07KEKAi1tt/8Qfqdf/V8htUeNjIhDgRfD3QSQRg6PacDMjx+XLuPNYLvF1+z9R6DDB58WPlvO9JukMV7q7Tr2+XjZW27HA8RP7L/sQYW7lD4RS3M9CajMIhYWJYZopU6/ZdirchqNj/fnkrpHnLMsRuTmj5KS34iwfqxl9A8PbRFvvD+PlMGVAzuNphXSbUTXJZqfj/KiRrsI3Eqo+GhbSYM4VVo6D7qCUw7GshdTanrEgEZooKO22FvJVeZY/OHJkfmVemQSZgR2e8lD/sEQtG6xPg9SuPhmVIOU77Cpixjn9wrDRrV3jklNuTG92NYea/Uuw9crqkaTvysQsdg2voq9Twm0Hta0GsRsuUj4ne9K9OU6ir0xhPTY1mCOsFgKRuA9p6fefvscnJ3xb1UMH/ZRY+okg8W5F/zXTLxB8R5z7rmxOefQcVUzfIGlkVIQ15AfqJa39KYKF7wz0XjzVxsQYaqKwLWyYds8l2maRAY5mtiGejAfULvHexZaXuw8S1pfpLIJQky4gCwdUAsXqsL3RuR8IFPxQ6W/3yQ9sILFDDKeqxfU1KWlfCtiKo/vbmMV3UfZmGN5T//1H/hz+g5/zDkrHYGdVuG8xJvcbHOWXF7n7xwkZvQbaO5I989xQ3IkTeThXI7Flh1w2RpamqUVKS0xKPd7pElG6ZEnqolzNb4CbX7zgtvMJ2Old1S7wA+YbzE2skeSUusR8AwIEMWriMv2EDBYvd6nU40UqozDKYZKgHR02E+RUK7ypTxtawXbTRlNE83zI98WOM4Ng4jUCTw99yYHiDQDRBL2+6ahlrjyLkIKVRC1BLIXP3n4zNm9LGKeTWtgeHX+m63yJnocp5VrzspJ8pqxFx/FdPQa33AWCVGDpBCPbIT7pcKn+6
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CH2PR12MB4133.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 Jan 2021 14:38:49.5421
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3c23e8fa-a579-43c0-3b8b-08d8b1879da3
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Fwu8px4ZhjOUSoEUgAF97UYHQrV1U+eeBMQdUxtcx7BHqpbwSrWSN8k5SGDCd6sOve2qKpDKa0EuLiZUG586xw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CH2PR12MB3957
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series re-works the SVM KVM implementation to use vmload/vmsave to
handle saving/restoring additional host MSRs rather than explicit MSR
read/writes, resulting in a significant performance improvement for some
specific workloads and simplifying some of the save/load code (PATCH 1).

With those changes some commonalities emerge between SEV-ES and normal
vcpu_load/vcpu_put paths, which we then take advantage of to share more code,
as well as refactor them in a way that more closely aligns with the VMX
implementation (PATCH 2 and 3).

v3:
 - rebased on kvm-next
 - remove uneeded braces from host MSR save/load loops (Sean)
 - use page_to_phys() in place of page_to_pfn() and shifting (Sean)
 - use stack instead of struct field to cache host save area outside of
   per-cpu storage, and pass as an argument to __svm_vcpu_run() to
   handle the VMLOAD in ASM code rather than inlining ASM (Sean/Andy)
 - remove now-uneeded index/sev_es_restored fields from
   host_save_user_msrs list
 - move host-saving/guest-loading of registers to prepare_guest_switch(),
   and host-loading of registers to prepare_host_switch, for both normal
   and sev-es paths (Sean)

v2:
 - rebase on latest kvm/next
 - move VMLOAD to just after vmexit so we can use it to handle all FS/GS
   host state restoration and rather than relying on loadsegment() and
   explicit write to MSR_GS_BASE (Andy)
 - drop 'host' field from struct vcpu_svm since it is no longer needed
   for storing FS/GS/LDT state (Andy)

 arch/x86/kvm/svm/sev.c     |  30 +-----------------------------
 arch/x86/kvm/svm/svm.c     | 112 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++------------------------------------------------------
 arch/x86/kvm/svm/svm.h     |  31 ++++++-------------------------
 arch/x86/kvm/svm/vmenter.S |  10 ++++++++++
 4 files changed, 75 insertions(+), 108 deletions(-)
```
#### [PATCH V1 0/5] vfio virtual address update
##### From: Steve Sistare <steven.sistare@oracle.com>

```c
From patchwork Tue Jan  5 15:36:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Sistare <steven.sistare@oracle.com>
X-Patchwork-Id: 11999661
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8E282C433E6
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 16:05:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 690F822C9F
	for <kvm@archiver.kernel.org>; Tue,  5 Jan 2021 16:05:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727921AbhAEQEp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 11:04:45 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:45488 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725936AbhAEQEo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 11:04:44 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 105Ftaxt138051;
        Tue, 5 Jan 2021 16:04:00 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=+WNDGZkjkmbGjD0qeySWyhmpjWQiseiHSGHdw478vEY=;
 b=zyRRCjc06y2W0yacgp6ggzXAJQYzv81TOoHS/IqqFQC9Ku290PZG33y7jOj232N1BqdQ
 fSYniiGhU54EMnl/lRhnnozjp1QV50InHPgwAI4GKB37FWLejycz6jlMZ2lQyAQdAfyD
 pmGq7QcMtsm9XJoCaRg3EC0znfaDKU0hmU6sl9+1NZUr/xso9cYOHbEo7nvyXtK2Fq0L
 UfcGqmksXowujSfGOjFej+klgorfUFZ8ND0nWyNOFkl6KiZgNZkajaU2B0S7VJkaCDQe
 jYiJHBVQ7izmr+U7KmRpdMH5duBBYujrOTYSy40KXB6JOajGa9ARrbuQTu2XKBvjOwT/ Ew==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 35tg8r1g67-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 05 Jan 2021 16:04:00 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 105Fuk53187327;
        Tue, 5 Jan 2021 16:03:59 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 35v1f8sedd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 05 Jan 2021 16:03:59 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 105G3vhM015328;
        Tue, 5 Jan 2021 16:03:58 GMT
Received: from ca-dev63.us.oracle.com (/10.211.8.221)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 05 Jan 2021 16:03:57 +0000
From: Steve Sistare <steven.sistare@oracle.com>
To: kvm@vger.kernel.org
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Steve Sistare <steven.sistare@oracle.com>
Subject: [PATCH V1 0/5] vfio virtual address update
Date: Tue,  5 Jan 2021 07:36:48 -0800
Message-Id: <1609861013-129801-1-git-send-email-steven.sistare@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9855
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=917
 phishscore=0
 suspectscore=0 spamscore=0 bulkscore=0 adultscore=0 mlxscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101050099
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9855
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1015
 phishscore=0 bulkscore=0
 spamscore=0 impostorscore=0 suspectscore=0 adultscore=0 mlxlogscore=938
 mlxscore=0 malwarescore=0 lowpriorityscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101050099
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add interfaces that allow the underlying memory object of an iova range
to be mapped to a new virtual address in the host process:

  - VFIO_DMA_UNMAP_FLAG_SUSPEND for VFIO_IOMMU_UNMAP_DMA
  - VFIO_DMA_MAP_FLAG_RESUME flag for VFIO_IOMMU_MAP_DMA
  - VFIO_SUSPEND extension for VFIO_CHECK_EXTENSION

The suspend interface blocks vfio translation of host virtual addresses in
a range, but DMA to already-mapped pages continues.  The resume interface
records the new base VA and resumes translation.  The implementation
supports iommu type1 and mediated devices.

This functionality is necessary for live update, in which a host process
such as qemu exec's an updated version of itself, while preserving its
guest and vfio devices.  The process suspends vfio VA translation, exec's
its new self, mmap's the memory object(s) underlying vfio object, and
resumes VA translation.  For a working example that uses these new
interfaces, see the QEMU patch series "[PATCH V2] Live Update".

Patch 1 modifies the iova rbtree to allow iteration over ranges with gaps,
  without deleting each entry.  This is required by patch 4.
Patch 2 adds an option to unmap all ranges, which simplifies userland code.
Patch 3 adds an interface to detect if an iommu_group has a valid container,
  which patch 5 uses to release a blocked thread if a container is closed.
Patch 4 implements the new ioctl's.
Patch 5 adds blocking to complete the implementation .

Steve Sistare (5):
  vfio: maintain dma_list order
  vfio: option to unmap all
  vfio: detect closed container
  vfio: VA suspend interface
  vfio: block during VA suspend

 drivers/vfio/vfio.c             |  12 ++++
 drivers/vfio/vfio_iommu_type1.c | 122 ++++++++++++++++++++++++++++++++++------
 include/linux/vfio.h            |   1 +
 include/uapi/linux/vfio.h       |  19 ++++++-
 4 files changed, 135 insertions(+), 19 deletions(-)
```
