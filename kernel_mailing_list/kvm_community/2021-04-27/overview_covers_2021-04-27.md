

#### [PATCH 0/3] x86/sev-es: rename file and other cleanup
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
From patchwork Tue Apr 27 11:16:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12226445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C89DEC433B4
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 11:17:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 99AB2613C6
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 11:17:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237883AbhD0LR4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 07:17:56 -0400
Received: from mail-eopbgr750082.outbound.protection.outlook.com
 ([40.107.75.82]:21193
        "EHLO NAM02-BL2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S238097AbhD0LRh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 07:17:37 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jLs9sngoJVM4X9Etf7HwtekW8pvLG2jQPhyLrAP6zKbW7BYXGbCK1SX0Tj91TtdYZGlmtdcUV3Ju+pEco5y91ZDcGeud4yuHKp+IPAgpKaPHVc9h/A1BuhwdGNHlI1jvvVCwTcaHpQ+nnBGHvvTtRMQTm9hI0CELj+rc9IHsIRoAbrBHes3UIfs+dDbqtWQyQUuNt/aughPh4FNDzVjaE/6Tc3RhL2QtlmzuvLE7u6583tLavOW/99vym1Rd3CdqFtxlPwiXKtP2/MQccR3yy9Z5P81k9qlJDEU5787aRUE0c2v4OCj138cjhuPFY4vtQo8I3TaiWdYFI//wuU/Mng==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JvPH0fI22wBUZMMSlZxQodwdd8QP7uYw63eep1jq+fs=;
 b=aD+5SDDIFJp1ziRZ6MKktcyM21ezEWN5auWCFOYewDri57mp6/0+OOR2UxMjGkuQOmqIpC1HcrRuBKSnbbUhhMuQ/wGI4XaCwiDXkcXmlC6rNGeA667OErVz03/8K4216fOjgSYmMHoNh1o3nnlrZtf2+KMOLos5Lnd3Gzg6APeOVme7wC5+mxnv1tvXZ12K6/A3t0Vze42+YsTKPeACqfwWrxM+KN2jYuz6Uk1ZW/di+TzGItyNWm3oMf9/UKFnGZ0STHSLCga5h9+de8TfXyS8xgVYJ0vDr6J1JDWnZyTQYRXSupmCCryva5/9aY7woYRSIItp2i3f6es5yd9MHA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=JvPH0fI22wBUZMMSlZxQodwdd8QP7uYw63eep1jq+fs=;
 b=TNptPs6wydXDH2TtXqYj+iYbRGm9P1AvCgdZnlXdX4YmZQG03w5OZFs+1DayX1ANDrAVzSKL1pE7PCb/nBmOZ1KbNEWz37ZSiuA5CU3yydmdGmKmghDty8MGg7qHNKd0oNeRIy/Gw08AYTWmR3bv2OaIxn49kU9oDLs3TbI728E=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4432.namprd12.prod.outlook.com (2603:10b6:806:98::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.26; Tue, 27 Apr
 2021 11:16:49 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Tue, 27 Apr 2021
 11:16:49 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: x86@kernel.org
Cc: tglx@linutronix.de, bp@alien8.de, jroedel@suse.de,
        thomas.lendacky@amd.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, pbonzini@redhat.com,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH 0/3] x86/sev-es: rename file and other cleanup
Date: Tue, 27 Apr 2021 06:16:33 -0500
Message-Id: <20210427111636.1207-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0201CA0054.namprd02.prod.outlook.com
 (2603:10b6:803:20::16) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0201CA0054.namprd02.prod.outlook.com (2603:10b6:803:20::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.25 via Frontend
 Transport; Tue, 27 Apr 2021 11:16:49 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 885cc2cf-997a-4ded-8b04-08d9096df395
X-MS-TrafficTypeDiagnostic: SA0PR12MB4432:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4432FAF700438398D9A4EEC3E5419@SA0PR12MB4432.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1247;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 PYlWMFh8Zaftl/7ofBKmf9qtPHH7qYT4ui57bj+voZExjNJd1+MGrq/M7A968Ykg1VKlYSA4qOHFS3jw8uZKEfBIQkQldm3g+C5rc9jh2vByjEW3kF55nxeZu2NgNzVKbMKVRdtGj8RNfQ8EpBgD41C8etgOV/jbrWVLJwt7qFxR2M9GL+Q+YnZkxibcVC0I/VbWj1VKCundsaHEx+f6e+A7+oF7FT0V6cRLd7619ZJAtoMAWYFHMKguT9aCoa7xL7+DHk2qEZOuP0t/DNai1f6aFOY4n30+UQqHvkc7k0M5qyVWzTd0KiCUSKjKtk7XXXWz8ruyrRlFpsHeVacKONom66DPZ9Ygt6XNkzWToTqRZ7+lhLRbZYf0EVJIr3WupUYlQ7nWaHVtPV6NwIblW5KW33r2kOZ1kmHJQe4jW4UJaBdEn4Yzah6DdsPRgiP2KoaWG0ngNPiy6UOczvI1w0hRN9lCBzubaqYAl7QAh7IJ49/LDT3AY1Q385DAsDCLKbxKRX3pHoWJRRZ+ilghzb9oolj5IGNNyZ8lfcQ14ugkPw7DCJSgC+0RvvtUYsAC7IqyeI4u/YCo0sCl3Tg5zmsReuD/tZVnkkqW3635jq1PxMpJSXULV47sVXhURO1a0ApqmeqC1XVQFqophU9FFb6hqkBq4u+Vxx3Okb6Rg3I=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(396003)(136003)(366004)(376002)(39860400002)(66556008)(66476007)(5660300002)(2616005)(956004)(478600001)(316002)(6916009)(66946007)(6666004)(44832011)(52116002)(86362001)(7696005)(1076003)(36756003)(8676002)(26005)(8936002)(16526019)(4326008)(2906002)(6486002)(83380400001)(186003)(38100700002)(38350700002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 5m4N7Nkf/cI0NCv7MYclmYRZUjJic7mPf3BuSn/4I27WDP06TehMlmXbgmSPR8ZMbWgc29CX9RCQ6046QMEPnZEstZb+4JZlWQyjUt69vsxotYJrGJU+NjHe2/OTJCc89g0NE+ZwlNa/O8+boHeABsBMaTe7oF+NBOO00/vnRTGz4eWMshCMzn9ob6GHKZDI9kpBO8jf2kivoJrW1Pwddpj91TaIuJAGP7ZgBn3bPgPH8UuBq42FKRbhWNsvlUz/Sd2ymoe5IJfOfRUMDA+YbiQcMLqe9HUxakFJjCwVfaXt77MacXeHtOOIIYBUqcdGPaP77VOChyJJP7BaBkwG3/7vgA/aU5dzCAvWk7SKJ6VvcqoxwSAFidnCoDQytmvX7DOymDBxU1NT7d7F96z22RS3LjxZhpxWN5S/SLclT9Ur46YAmDsJjSODFPWGlOLgLASIvE3z/gxIkFVY5cHiprzp9jwfJHd29uNcHJ+pxW3z0v1R3ELwd9jMxiBOXKG9pk9ZwFvrYZ6xTnj7DcEtvbH/+w6EBACcTCDV8AQs63JzSpcVASE/qJy2ijFhK5hsmd6PveH9XoB1f7qu1BjhY5AxPbCg1nxtfrXo9SlPUyAIvAB3/eJxbIj2Hf1oqKkqW2Wv1goJByktJUUkcKKx7BD6QjcRMBB37YUz4XIfHheKfHgqI26fR9k/WMP0NIGtiquIJ7PPlI+Bs2TX1Ocl4DWU9KfHHnBI7aoOc+ebbxem0ln3Ijp0x3FcH+frmpB5thJZif/1zD4mLdFkjNNV/BdnjKOmIo0CK9tDpcCoJa9zYWfTbU55XyWI0vzWErqL9NN9ChZBIw4PEE2aW0ibYJV1goCX+M8EwTR2nOGdWndmkTf85gFNVn+UfarWWFrAH/LpTY01PMDkKTzumlKJNC1YNk/Ba5iYLHU86CX3+bqwr24L7c+pCUemo2xDVcxv8UdkwQLQsf8OuLPrCB9VlFQUSuC9LBVwVKInQT+j0An58dojSoCD1NlIW/wO124JKJWvKkHp0mnN+Tb/gmWXejY2vKOIBycy4KqtD4t3zQRuewPesfV2vUza1jj93kCHEs6rkqdsv3GUnqDV9UhQbM5KWu9/xeM32dStmWGftqKJrcp1TtsTdl3bn5GIek9qkSm/H+NUMqshvrFXsI1OmRw4rpoAPRk9O/1EdXEHA6fgPu+6128ZtvmxdoS+L07lJpcrW82uTcS+rHQeIRqHS3EzgZbgho/3Q/5aqhpa3fd4Nd3dSchqGqgGwJxCppcob3paXFmwIMh0DqoaZe3zNLYqpkBkDG+pe4aMZV11Re26NPKgaeYXdhnIvpUA4Hpg
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 885cc2cf-997a-4ded-8b04-08d9096df395
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 27 Apr 2021 11:16:49.4213
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 WezU6hkagyeyI7xk3uxfS+/hbVxZ4s2gcFG0il9bVZwn+9eAvFc/SCe4zfZ9of/L8FyqFAIk34fGYBIapbAoDg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4432
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is developed based on the feedbacks on SEV-SNP RFCv1.

The SEV-SNP depends on SEV-ES functionality, so rename the sev-es.c
to sev.c so that we can consolidate all the SEV support in one file.

The series applies on top of commit (tip/master)
eb4fae8d3b9e (origin/master, origin/HEAD, master) Merge tag 'v5.12' 

Brijesh Singh (3):
  x86/sev-es: Rename sev-es.{ch} to sev.{ch}
  x86/sev: Move GHCB MSR protocol and NAE definitions in a common header
  x86/msr: Rename MSR_K8_SYSCFG to MSR_AMD64_SYSCFG

 .../virt/kvm/amd-memory-encryption.rst        |  2 +-
 Documentation/x86/amd-memory-encryption.rst   |  6 +-
 arch/x86/boot/compressed/Makefile             |  6 +-
 arch/x86/boot/compressed/{sev-es.c => sev.c}  |  4 +-
 arch/x86/include/asm/msr-index.h              |  6 +-
 arch/x86/include/asm/sev-common.h             | 62 +++++++++++++++++++
 arch/x86/include/asm/{sev-es.h => sev.h}      | 30 ++-------
 arch/x86/kernel/Makefile                      |  6 +-
 arch/x86/kernel/cpu/amd.c                     |  4 +-
 arch/x86/kernel/cpu/mtrr/cleanup.c            |  2 +-
 arch/x86/kernel/cpu/mtrr/generic.c            |  4 +-
 arch/x86/kernel/head64.c                      |  2 +-
 arch/x86/kernel/mmconf-fam10h_64.c            |  2 +-
 arch/x86/kernel/nmi.c                         |  2 +-
 .../kernel/{sev-es-shared.c => sev-shared.c}  | 20 +++---
 arch/x86/kernel/{sev-es.c => sev.c}           |  4 +-
 arch/x86/kvm/svm/svm.c                        |  4 +-
 arch/x86/kvm/svm/svm.h                        | 38 ++----------
 arch/x86/kvm/x86.c                            |  2 +-
 arch/x86/mm/extable.c                         |  2 +-
 arch/x86/mm/mem_encrypt_identity.c            |  6 +-
 arch/x86/pci/amd_bus.c                        |  2 +-
 arch/x86/platform/efi/efi_64.c                |  2 +-
 arch/x86/realmode/init.c                      |  2 +-
 arch/x86/realmode/rm/trampoline_64.S          |  4 +-
 drivers/edac/amd64_edac.c                     |  2 +-
 tools/arch/x86/include/asm/msr-index.h        |  6 +-
 27 files changed, 121 insertions(+), 111 deletions(-)
 rename arch/x86/boot/compressed/{sev-es.c => sev.c} (98%)
 create mode 100644 arch/x86/include/asm/sev-common.h
 rename arch/x86/include/asm/{sev-es.h => sev.h} (70%)
 rename arch/x86/kernel/{sev-es-shared.c => sev-shared.c} (96%)
 rename arch/x86/kernel/{sev-es.c => sev.c} (99%)
```
#### [PATCH v4 0/2] kvm: x86: Allow userspace to handle emulation errors
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Tue Apr 27 16:59:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12227021
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F25E4C43461
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 17:01:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AE39961165
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 17:01:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238733AbhD0RCg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 13:02:36 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60742 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236627AbhD0RCe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 13:02:34 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E74C1C061574
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 10:01:50 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id
 o7-20020a0cf4c70000b02901a53a28706fso21080905qvm.19
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 10:01:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Qg5Ee0t3O4ULaTp1MifOKduMGn8W4DB1DYGG/KAxPOA=;
        b=ckeZVXD4I1jR43ADeaLseamGFJ9weSz+agtatcaC7O1Isd0ujDOXxDs5F/2WdvMUmX
         +utQiJVTjVnPiSwVFTI3UY2K7Np2k6sV43Xhj6PpJMNb5LlWhdzHEEhTGZ3VIRCrnHQC
         Ph51S19RxpSWwhu1ZnZJRijMzrsYG49Z7TSz/2d1VDIAwptsJlMn96JBotyfm572vW8m
         DcLnxqITIIxsMWLoV/UrXtw2NhJjgx1r5/ajeN/R5v9WSnfSChqeuHmn1GMp4q//8Pqs
         AWsoAQkD2Rekx8xyKC7sqFIw9n6qFLkImViZQslnIH7qlpa0EFlldznWQbXNv1y/v5V2
         fQxA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Qg5Ee0t3O4ULaTp1MifOKduMGn8W4DB1DYGG/KAxPOA=;
        b=NAl+aOxT4YUEhxLLCUydUZ3hd/N1Z1DdKrcKQyZx0TmHtx5rllgFaSoSnPM2svPwPF
         BF1uQvrMMMxFyZRbp/WPsF2650KpC4bF3A2L2gveJhJ4RMk+A8xqoeL1BYm7JkngJ7Lf
         24rGllxQultMU4TeZEjKTJ7lLjUQXYMJR2wRLupfjN2bX2+SPT7hWIebUJ2e2fBFkR2D
         T9RRrCf4ZEipcSV5ntgcePu3stSuZDaddOlBws3oZGIIDcdOipZAaGIq27EPXxpzVgrb
         ynF+IIIqhbZfOqaEwyVto15Tqg2cSjXm5IL2pGHtH3HLuXgSBCQsOPB0+hU0fYaAZL0i
         5gcA==
X-Gm-Message-State: AOAM531POGPQyxrByQYYWoFnTE1MQCOB4qkaga51Ip5FbfcdmOL9WwAZ
        Bl/H0caREjdHMwFPPtDPf4TnkoNpBCl/LkuB
X-Google-Smtp-Source: 
 ABdhPJxDJ7pDKR0HPyjDsrGZJmmh/cI4Gs+3jL1WzHZWC/qXT1Cukr3r8HRmiKIfH61Qd6E8qR0JBxbtVIE+udhE
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:de04:ef9c:253d:9ead])
 (user=aaronlewis job=sendgmr) by 2002:ad4:4312:: with SMTP id
 c18mr23824516qvs.44.1619542910062; Tue, 27 Apr 2021 10:01:50 -0700 (PDT)
Date: Tue, 27 Apr 2021 09:59:57 -0700
Message-Id: <20210427165958.705212-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v4 0/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset allows userspace to be a fallback for handling emulation errors.

v1 -> v2:

 - Added additional documentation for KVM_CAP_EXIT_ON_EMULATION_FAILURE.
 - In prepare_emulation_failure_exit():
   - Created a local variable for vcpu->run.
   - Cleared the flags, emulation_failure.flags.
   - Or'd the instruction bytes flag on to emulation_failure.flags.
 - Updated the comment for KVM_INTERNAL_ERROR_EMULATION flags on how they are
   to be used.
 - Updated the comment for struct emulation_failure.

v2 -> v3:

 - Update documentation for KVM_CAP_EXIT_ON_EMULATION_FAILURE.
 - Fix spacing in prepare_emulation_failure_exit().

v3 -> v4:

 - In prepare_emulation_failure_exit():
   - Clear instruction bytes to 0x90.
   - Copy over insn_size bytes rather than sizeof(ctxt->fetch.data).
 - set_page_table_entry() takes a pte rather than mask.
 - In _vm_get_page_table_entry():
   - Removed check for page aligned addresses only.
   - Added canonical check.
   - Added a check to make sure no reserved bits are set along the walk except
     for the final pte (the pte cannot have the reserved bits checked otherwise
     the test would fail).
   - Added check to ensure superpage bits are clear.
 - Added check in test for 'allow_smaller_maxphyaddr' module parameter.
 - If the is_flds() check fails, only look at the first byte.
 - Don't use labels to increment the RIP.  Decode the instruction well enough to
   ensure it is only 2-bytes.

Aaron Lewis (2):
  kvm: x86: Allow userspace to handle emulation errors
  selftests: kvm: Allows userspace to handle emulation errors.

 Documentation/virt/kvm/api.rst                |  18 ++
 arch/x86/include/asm/kvm_host.h               |   6 +
 arch/x86/kvm/x86.c                            |  37 ++-
 include/uapi/linux/kvm.h                      |  23 ++
 tools/include/uapi/linux/kvm.h                |  23 ++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   3 +
 .../selftests/kvm/lib/x86_64/processor.c      |  79 ++++++
 .../kvm/x86_64/emulator_error_test.c          | 224 ++++++++++++++++++
 10 files changed, 411 insertions(+), 4 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/emulator_error_test.c
```
#### [PATCH v4 0/7] Hyper-V nested virt enlightenments for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
From patchwork Tue Apr 27 20:54:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12227323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D553DC43460
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 20:55:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BABF961404
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 20:55:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239083AbhD0Uzv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 16:55:51 -0400
Received: from linux.microsoft.com ([13.77.154.182]:35558 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239040AbhD0Uzt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 16:55:49 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id BE8B220B8000;
        Tue, 27 Apr 2021 13:55:05 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com BE8B220B8000
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1619556905;
        bh=xqElmAcSUSaDejhXkc1b8y5LQbBrxkMdgKVlO7kAJ9k=;
        h=From:To:Cc:Subject:Date:From;
        b=iIPEsY/RWWfQ3JvBDrepFpdoykwTO1WUSIHuIn29dZd24W4pUZGXbwhbP1w43LYpX
         Jt6l5k0kIVrenJk0orisZZPNsoZt8GqSWuOoCriOF1O0B1KtbwXHxYRvHo58bmrXbc
         dv2z0RlXPp2V7ukVL5KKG3trWkSVIs8EZfQmE3VA=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v4 0/7] Hyper-V nested virt enlightenments for SVM
Date: Tue, 27 Apr 2021 20:54:49 +0000
Message-Id: <cover.1619556430.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series enables the nested virtualization enlightenments for
SVM. This is very similar to the enlightenments for VMX except for the
fact that there is no enlightened VMCS. For SVM, VMCB is already an
architectural in-memory data structure.

The supported enlightenments are:

Enlightened TLB Flush: If this is enabled, ASID invalidations invalidate
only gva -> hpa entries. To flush entries derived from NPT, hyper-v
provided hypercalls (HvFlushGuestPhysicalAddressSpace or
HvFlushGuestPhysicalAddressList) should be used.

Enlightened MSR bitmap(TLFS 16.5.3): "When enabled, L0 hypervisor does
not monitor the MSR bitmaps for changes. Instead, the L1 hypervisor must
invalidate the corresponding clean field after making changes to one of
the MSR bitmaps."

Direct Virtual Flush(TLFS 16.8): The hypervisor exposes hypercalls
(HvFlushVirtualAddressSpace, HvFlushVirtualAddressSpaceEx,
HvFlushVirtualAddressList, and HvFlushVirtualAddressListEx) that allow
operating systems to more efficiently manage the virtual TLB. The L1
hypervisor can choose to allow its guest to use those hypercalls and
delegate the responsibility to handle them to the L0 hypervisor. This
requires the use of a partition assist page."

L2 Windows boot time was measured with and without the patch. Time was
measured from power on to the login screen and was averaged over a
consecutive 5 trials:
  Without the patch: 42 seconds
  With the patch: 29 seconds
---

Changes from v3
- Included definitions for software/hypervisor reserved fields in SVM
  architectural data structures.
- Consolidated Hyper-V specific code into svm_onhyperv.[ch] to reduce
  the "ifdefs". This change applies only to SVM, VMX is not touched and
  is not in the scope of this patch series.

Changes from v2:
- Refactored the Remote TLB Flush logic into separate hyperv specific
  source files (kvm_onhyperv.[ch]).
- Reverted the VMCB Clean bits macro changes as it is no longer needed.

Changes from v1:
- Move the remote TLB flush related fields from kvm_vcpu_hv and kvm_hv
  to kvm_vcpu_arch and kvm_arch.
- Modify the VMCB clean mask runtime based on whether L1 hypervisor
  is running on Hyper-V or not.
- Detect Hyper-V nested enlightenments based on
  HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS.
- Address other minor review comments.
---

Vineeth Pillai (7):
  hyperv: Detect Nested virtualization support for SVM
  hyperv: SVM enlightened TLB flush support flag
  KVM: x86: hyper-v: Move the remote TLB flush logic out of vmx
  KVM: SVM: Software reserved fields
  KVM: SVM: hyper-v: Remote TLB flush for SVM
  KVM: SVM: hyper-v: Enlightened MSR-Bitmap support
  KVM: SVM: hyper-v: Direct Virtual Flush support

 arch/x86/include/asm/hyperv-tlfs.h |   9 ++
 arch/x86/include/asm/kvm_host.h    |  14 +++
 arch/x86/include/asm/svm.h         |   9 +-
 arch/x86/include/uapi/asm/svm.h    |   3 +
 arch/x86/kernel/cpu/mshyperv.c     |  10 +-
 arch/x86/kvm/Makefile              |   9 ++
 arch/x86/kvm/kvm_onhyperv.c        |  94 +++++++++++++++++++
 arch/x86/kvm/kvm_onhyperv.h        |  33 +++++++
 arch/x86/kvm/svm/svm.c             |  13 +++
 arch/x86/kvm/svm/svm.h             |  22 ++++-
 arch/x86/kvm/svm/svm_onhyperv.c    |  41 +++++++++
 arch/x86/kvm/svm/svm_onhyperv.h    | 141 +++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c             |  97 ++------------------
 arch/x86/kvm/vmx/vmx.h             |  10 --
 arch/x86/kvm/x86.c                 |   8 ++
 15 files changed, 406 insertions(+), 107 deletions(-)
 create mode 100644 arch/x86/kvm/kvm_onhyperv.c
 create mode 100644 arch/x86/kvm/kvm_onhyperv.h
 create mode 100644 arch/x86/kvm/svm/svm_onhyperv.c
 create mode 100644 arch/x86/kvm/svm/svm_onhyperv.h
```
#### [PATCH 0/6] Lazily allocate memslot rmaps
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue Apr 27 22:36:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12227645
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C2CB1C433B4
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 22:36:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A51266105A
	for <kvm@archiver.kernel.org>; Tue, 27 Apr 2021 22:36:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237012AbhD0Wh0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 27 Apr 2021 18:37:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50026 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235382AbhD0WhY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Apr 2021 18:37:24 -0400
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A05D8C061574
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 15:36:39 -0700 (PDT)
Received: by mail-qk1-x749.google.com with SMTP id
 s143-20020a3745950000b029028274263008so24058401qka.9
        for <kvm@vger.kernel.org>; Tue, 27 Apr 2021 15:36:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=tTxyuPdn4rgY+Ver4IyXpo1lEOrhYEkf7++g5p9MMkg=;
        b=Em3n9hB7Hvpo19frVT+W+lf6YpZN5+Lr/0LqsFFv0gNvnZnCBzxm85s0fMMnF+6ztv
         NKgRvI3OiEknf83jl0j/hk084leCvhzoTUmE9ZrF/gymP1jb4V1UkbftHvSRYXenOpQz
         3Xg3YuF6ncGvV2eV2iUfGUECxCAnkHYkMCrmgkfCT81klWMmMVFOzQ+LSDHr9+9E0D4L
         CYpXFr3jJ9XUcovYwMVuaNobPazmLKJ0LwIbuHRlQ7+LH4yLe5Y8lKXzpd8nbtsTr8hD
         LRqSj7wVd8no/fUL/noDSo5qeP4INm6gbF8Xr4kp0LuBnnSUr09Jbcik3UTksPFUmrB3
         2BLg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=tTxyuPdn4rgY+Ver4IyXpo1lEOrhYEkf7++g5p9MMkg=;
        b=BSTueGlKffopAFRmg1VZ7onDPeSYYdX45N0U6mVniXIKO2POw/JdzJ9BJXNXGjQtHN
         tol4JOggq9Q38x4ZIBKYN7E8pUM1M8X9nx3ZyVWCIkgf+9D1DwGoRtZ++AmRhMq9ymhf
         MrdsMcH/M4eGFyb/SHrtuKTQDCQj0VyR0USny9ItjwH45fLYK6yPYasBgBibDUVZqPh1
         Dsn/uwF3YdMXjE2asNrjrjs6RN1tECUC/WCs5CCDGbvplTSV96G4cr6av3S4oIyOFIuL
         aPfos6RH9nUns8ybsPkRkubvPBREtjOLvxG+yAdJvEiEmyproBJ4sgh4yMgHV2+JLnTA
         to/w==
X-Gm-Message-State: AOAM533yCt4rma6l+TB+neMhaVQIO2Y07L+hZ6fCZtqFvukBjzWtNAWS
        ns9S6QRkCc9Dz3FA/APUtxvcCsnds99K
X-Google-Smtp-Source: 
 ABdhPJyBV1BpEZC1fi84zDfcUk6+MVZdQs5cnGvWQPszmzv2+tAOFaBcUjcAEo/m2GY/QPZ2WqzP5avG/frm
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:d0b5:c590:c6b:bd9c])
 (user=bgardon job=sendgmr) by 2002:a05:6214:246a:: with SMTP id
 im10mr25700282qvb.7.1619562998354; Tue, 27 Apr 2021 15:36:38 -0700 (PDT)
Date: Tue, 27 Apr 2021 15:36:29 -0700
Message-Id: <20210427223635.2711774-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 0/6] Lazily allocate memslot rmaps
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
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

This series enables KVM to save memory when using the TDP MMU by waiting
to allocate memslot rmaps until they are needed. To do this, KVM tracks
whether or not a shadow root has been allocated. In order to get away
with not allocating the rmaps, KVM must also be sure to skip operations
which iterate over the rmaps. If the TDP MMU is in use and we have not
allocated a shadow root, these operations would essentially be op-ops
anyway. Skipping the rmap operations has a secondary benefit of avoiding
acquiring the MMU lock in write mode in many cases, substantially
reducing MMU lock contention.

This series was tested on an Intel Skylake machine. With the TDP MMU off
and on, this introduced no new failures on kvm-unit-tests or KVM selftests.

Ben Gardon (6):
  KVM: x86/mmu: Track if shadow MMU active
  KVM: x86/mmu: Skip rmap operations if shadow MMU inactive
  KVM: x86/mmu: Deduplicate rmap freeing in allocate_memslot_rmap
  KVM: x86/mmu: Factor out allocating memslot rmap
  KVM: x86/mmu: Protect kvm->memslots with a mutex
  KVM: x86/mmu: Lazily allocate memslot rmaps

 arch/x86/include/asm/kvm_host.h |  20 +++++
 arch/x86/kvm/mmu/mmu.c          | 153 +++++++++++++++++++++-----------
 arch/x86/kvm/mmu/mmu_internal.h |   2 +
 arch/x86/kvm/mmu/tdp_mmu.c      |   6 +-
 arch/x86/kvm/mmu/tdp_mmu.h      |   4 +-
 arch/x86/kvm/x86.c              | 133 +++++++++++++++++++++++----
 include/linux/kvm_host.h        |   2 +
 virt/kvm/kvm_main.c             |  48 +++++++---
 8 files changed, 283 insertions(+), 85 deletions(-)
```
