

#### [PATCH v2 0/9] Add AMD SEV page encryption bitmap support.
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Tue Dec  1 00:45:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11941709
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CA44BC63777
	for <kvm@archiver.kernel.org>; Tue,  1 Dec 2020 00:46:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8758120715
	for <kvm@archiver.kernel.org>; Tue,  1 Dec 2020 00:46:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="SUh+b275"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730801AbgLAAqX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 19:46:23 -0500
Received: from mail-bn8nam11on2085.outbound.protection.outlook.com
 ([40.107.236.85]:46025
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726316AbgLAAqW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Nov 2020 19:46:22 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PlObJkakEgRwY0TKc28IF1rPQCuecymDRlF7wYO5PSoFSrSXZuo9zIsU2OtVB44Qt6IV4qRh0SgZhwwCrKgT+r98qNPDz0giH/DQ0nVwYo5WzbUia48wzvEDZxx7q4Twn55h3z0U3Iu+Mc+det+0GQUgO0+GcxG+b/GFhkYtFY51XZkvt/4HM60b3FIbG0cJQUKjQ27Wt9x49KjyjRW40y7eaYVRjFqkAFUFm1Ks2a08GDig//1gfUVO6N46F+SRjQE2Y2UfpJJPFlJnwB5SUBi3hfqzq/WfKXVvMN227rd4DnkNFFBFLZn0IsYqyFjnHrHBosvEF38m39LPdw7nSg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4lfoO3QA7skrQsdPAxz4gzne8UEC0DsVrNta4uQtUUg=;
 b=g3z5u2UTOsNEEmQ/Tnp47o5IKvBy5ELhMKaP7b16tk5+uOXKAnHw/IJhoIIJRerFLv48MUWyGF6x7cTrUIMXlVvc1+DdQLGbu3rZ9gdOfSGicP5SRJLCG1FCk98+AbP5dUOpTxBSsf7Rp2KVoyoomW5PTLfaK61IIw9onM2esivlefl56DGHokiIVyOB0VNWqlSfSDX6yDfYAvC5DWS98hMloiGEi8o0XAXqI4Ed8iKr+IO9n0Rts89diG4AoUgfZWF79jMVkEajXg5NjmTHEy7yxq3vnFvGCG1rdlW9RnAEmFfsOqb+UuM05rgfpnxdTBLOrdYbb0MYD1O+8i3U8Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4lfoO3QA7skrQsdPAxz4gzne8UEC0DsVrNta4uQtUUg=;
 b=SUh+b2753uqOiYYjmNSCHMJUOCbmJtVZaRTPIbg/HjMZZJa3wceNZwLXZoxaqfGD5b8zXj/8BWYm9BKBgayEj5nCmwtknmkbLhpTMpQLE2j1mUT9duGX10bs0aUvFLVIvy278e5jjra1Q+ZOjpvP03ws8SOGvDF2zaqLf0YXe5A=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2832.namprd12.prod.outlook.com (2603:10b6:805:eb::30) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3611.25; Tue, 1 Dec
 2020 00:45:28 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3611.025; Tue, 1 Dec 2020
 00:45:28 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, brijesh.singh@amd.com,
        dovmurik@linux.vnet.ibm.com, tobin@ibm.com, jejb@linux.ibm.com,
        frankeh@us.ibm.com, dgilbert@redhat.com
Subject: [PATCH v2 0/9] Add AMD SEV page encryption bitmap support.
Date: Tue,  1 Dec 2020 00:45:16 +0000
Message-Id: <cover.1606782580.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR12CA0017.namprd12.prod.outlook.com (2603:10b6:4:1::27)
 To SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM5PR12CA0017.namprd12.prod.outlook.com (2603:10b6:4:1::27) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3611.20 via Frontend
 Transport; Tue, 1 Dec 2020 00:45:27 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: b8922b2f-3dbf-4c88-0e69-08d895926626
X-MS-TrafficTypeDiagnostic: SN6PR12MB2832:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB28323E26652BD6F180E3E4938EF40@SN6PR12MB2832.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 cfqcIhO6Iv6ZOYTKDoY9wLM4YU3Pd7JXwmpk40XGhNOn4gZqzrHK1gHgN44zo2dMJ7jlJh4Zg0Pn2dV6yHxfSHdkexfK7Wl32nXgSQmo4d4rThkSMoyCjKKdUkwq+NmTewedLV0sxBMvDHTVyDm5hUKd2p57XDPxTtMoDw+T+9OhyXAhLI3oWet6yHsq8cO8QjRv7IqrNY3oE1KVrYxA9pYdBvLQ+1cj6WzcgMJaKJjmkv5dtaUMeK4f8yElv0VPtmoTrDdGtmal0xN4ojIYk9CDIcMgaV+sav2EIgA6kp4hAI7PECOnpdHxT0sI/wkmx2iS4ajiiTdEEWnbn932ZGfcUFXhWcms/y8TyaDojqjCslYl3zbAG9DhnJ6Qbl/JOQrMa6eHf5C2Is9F998AOw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(376002)(346002)(396003)(136003)(39860400002)(7416002)(16526019)(66946007)(6666004)(83380400001)(26005)(966005)(2906002)(66476007)(186003)(956004)(2616005)(316002)(7696005)(36756003)(52116002)(86362001)(4326008)(478600001)(6486002)(6916009)(5660300002)(8676002)(8936002)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?bFqdigP4CkyoXg5mY4ghZiS4KSjVJN?=
	=?utf-8?q?Q/LFNLIu5Oi//Z9YIS63xqKKbQoHOuH/twnxS+u6tWgA+DrfJK/lKGIQdY57EDJYg?=
	=?utf-8?q?SDrZ6WYgueoSPKLhNQGLY9nwK0KvixjC9ahjbAUSxcNlql9tjkTjHNE+LZABgzkTi?=
	=?utf-8?q?I1vAftER13Gc3ufq88QRT4WNGh366d3o85Kh81bybab89cyxoQq3pleCq5Z02fmcI?=
	=?utf-8?q?R2lG7TQsArrcAXSZZuP7xf3yuIlzt7iPqTEDWoJ+bYTOZccO2lbTT7GcUT2qVzell?=
	=?utf-8?q?+Gf0WEiuSLvZwk4FLESWx6H2N8UlCxjbmiDkH36xyJXn4ZK9ZONHgPHVlwx3GcXSf?=
	=?utf-8?q?+Eo5eWIbf8bIW0JP+8zSQHvVtpyA/+h4BejtEw6XPpiKpEtTSC6XRP8TKZCEYhboJ?=
	=?utf-8?q?TRJeb8qRcw7dVN2xodzaleB/kIy5QFqzI8gM21O0ah8URVAMzyg3WSWCVO6Ov2u1B?=
	=?utf-8?q?MIdcvVwyW6ArgjOa/DuqeSVO+TWXc+cU3+clSHznLYdBW2EflOeHr1YZsacCtMcVC?=
	=?utf-8?q?IORqRCaoylzCATG8XugnKokZy1+3Dy0WdJqugNOYR3EORmZcUn3MBu3yPN0N3w4f0?=
	=?utf-8?q?6Ej0G8oOj9obilU6N3ZX3B+6Dzvgs7eKBHrCsqYrk5WiUZnPcRwzFu51uBJ16zsF7?=
	=?utf-8?q?Sc/BPc7eiTQJU+8C7uNbVgP95vu7AqSONlPulLMIZVVbAZoRIn/dB65tUaJsxdYhv?=
	=?utf-8?q?jCQPVTOnA3fNNjcTShaXt7GzGoGLlydicqqfa6BV361Knz6iznX7glG1hSLZzNP/n?=
	=?utf-8?q?jHHZokxUtezSQFyS44MuyxUENioFMdzBRXr97PGy3P9CzkKyULgJ5Ca95UY7sCMsj?=
	=?utf-8?q?KfBGtQvK4RX/V0luSCKdIbf0L26/Y4l/yXWJm+WmnwYcmtt+84zriJK/0GMFO56Yc?=
	=?utf-8?q?v4FxHqAW0AtXl7UtjVZh8jQiS3eEiUvN4+O2taGyES47u/vOMCIrISHG/VGZpyi27?=
	=?utf-8?q?i0tM3sfJL0RbqVfZGFA?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b8922b2f-3dbf-4c88-0e69-08d895926626
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 01 Dec 2020 00:45:28.6428
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6i/d2kZfCmOWYz0dfuTbechz9FwpLMdYqAhfp8Yj9R92bLc/SEAY++lx27AmIogotOx8xE7udo2xAByxIZjCew==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2832
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series add support for AMD SEV page encryption bitmap.

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.

The patch adds new ioctls KVM_{SET,GET}_PAGE_ENC_BITMAP. The ioctl can be used
by qemu to get the page encryption bitmap. Qemu can consult this bitmap
during guest live migration / page migration and/or guest debugging to know
whether the page is encrypted.

The page encryption bitmap support is required for SEV guest live migration,
guest page migration and guest debugging.

The patch-set also adds support for bypassing unencrypted guest memory
regions for DBG_DECRYPT API calls, guest memory region encryption status
in sev_dbg_decrypt() is now referenced using the page encryption bitmap.

A branch containing these patches is available here:
https://github.com/AMDESE/linux/tree/sev-page-encryption-bitmap-v2

Changes since v1:
 - Fix in sev_dbg_crypt() to release RCU read lock if hva_to_gfn() fails
   when bypassing DBG_DECRYPT API calls for unencrypted guest memory.
 - Comment fix for Patch 7/9. 

Ashish Kalra (4):
  KVM: SVM: Add support for static allocation of unified Page Encryption
    Bitmap.
  KVM: x86: Mark _bss_decrypted section variables as decrypted in page
    encryption bitmap.
  KVM: x86: Add kexec support for SEV page encryption bitmap.
  KVM: SVM: Bypass DBG_DECRYPT API calls for unecrypted guest memory.

Brijesh Singh (5):
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce KVM_GET_PAGE_ENC_BITMAP ioctl
  mm: x86: Invoke hypercall when page encryption status is changed.
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

 Documentation/virt/kvm/api.rst        |  71 ++++++
 Documentation/virt/kvm/hypercalls.rst |  15 ++
 arch/x86/include/asm/kvm_host.h       |   7 +
 arch/x86/include/asm/kvm_para.h       |  12 +
 arch/x86/include/asm/mem_encrypt.h    |   4 +
 arch/x86/include/asm/paravirt.h       |  10 +
 arch/x86/include/asm/paravirt_types.h |   2 +
 arch/x86/kernel/kvm.c                 |  28 +++
 arch/x86/kernel/kvmclock.c            |  12 +
 arch/x86/kernel/paravirt.c            |   1 +
 arch/x86/kvm/svm/sev.c                | 321 ++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c                |   5 +
 arch/x86/kvm/svm/svm.h                |   7 +
 arch/x86/kvm/vmx/vmx.c                |   1 +
 arch/x86/kvm/x86.c                    |  35 +++
 arch/x86/mm/mem_encrypt.c             |  63 ++++-
 arch/x86/mm/pat/set_memory.c          |   7 +
 include/uapi/linux/kvm.h              |  13 ++
 include/uapi/linux/kvm_para.h         |   1 +
 19 files changed, 614 insertions(+), 1 deletion(-)
```
