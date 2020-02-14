

#### [PATCH 00/12] SEV Live Migration Patchset.
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Thu Feb 13 01:14:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11379537
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38C65921
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 01:14:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0E56F222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 01:14:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="GyFoSumQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729389AbgBMBOg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Feb 2020 20:14:36 -0500
Received: from mail-eopbgr690055.outbound.protection.outlook.com
 ([40.107.69.55]:14308
        "EHLO NAM04-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729185AbgBMBOf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Feb 2020 20:14:35 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=N6mPqeqcddBagHbkdT6WcaCBtwrqmDpH/FaEmRj59lA2h58Y9/J+nJftaT2iL3thhrL41f2sUgBOiIahU0ytYaWZgOxbzgA/vAARFKt5+ECoOayKXUWskYhzNUkXxdx3e5aRnahcSwMjm47gkQrUznLLwyRhxEEg7hBspmO6oLFYHQIJm+0SpPjBHIy7nhoCJZi0wSbhxRiDfIWV0xasUC4nypoohyEEZi9b+W1dkof2nlpFvE4cxSLpd9nykNQOFDEQbjYIdTDQ9Lm8otJyH+YqjHEjpjB6Uwl0FTaZ9TlkmIGDKlsqTtryDZR/T525ISYXbgYNaXMRD/3Cv+YDPA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xUhLNk/HS8C0w/YLxqkrz2cr/0fmX5874CDvWcMk8V8=;
 b=kUxwIC6oa3oM/PCmrCvMLbBW3As5VEgbl7FHsXXo9wAevRHX1klllpAx1l+Zsq8vWpo5MkO3gAC59qn9kiCt2rCz+IwryEBci6EuqCCwfwBpy8C79X9NY9ovsinZ+r9zIZS4Yltut1VV1rQELYiXyWz6Hv0wd4/5dbejm0U0Jpz/RyXBsEzpUQ571AexkfKWApg3LNI9IF8Qk3ZHhErjPlf4AX1xJ+RkJF1h9pgqtcF2+82EAgXAHLWpLIbnEOB+f+mCt73Km1qHv0P82i4zXeDF+ZermlWmh3B/r0ZFj7UQdhsSIoYLgy1AsX8t52kO0ho+0f3n8yvJ68pHMrTCNA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xUhLNk/HS8C0w/YLxqkrz2cr/0fmX5874CDvWcMk8V8=;
 b=GyFoSumQRb8qkXg1mzSBFFNLNYQnX4z78YSU8MBRycx1NhzRYODNlzcnslcjAdUzKuwNeJS9wY1U5Z7LgJkgFRjjwPd38ZgBOD7C+CO0aZ1ANM0nvW3xZ/0Ge2W9nlHw56Qt4IM5G1mZdRqqQou0CO2doLFK957kSyNF9OQKJZA=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Ashish.Kalra@amd.com;
Received: from SN1PR12MB2528.namprd12.prod.outlook.com (52.132.196.33) by
 SN1PR12MB2366.namprd12.prod.outlook.com (52.132.194.147) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2729.22; Thu, 13 Feb 2020 01:14:32 +0000
Received: from SN1PR12MB2528.namprd12.prod.outlook.com
 ([fe80::fd48:9921:dd63:c6e1]) by SN1PR12MB2528.namprd12.prod.outlook.com
 ([fe80::fd48:9921:dd63:c6e1%7]) with mapi id 15.20.2707.030; Thu, 13 Feb 2020
 01:14:31 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, rientjes@google.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 00/12] SEV Live Migration Patchset.
Date: Thu, 13 Feb 2020 01:14:21 +0000
Message-Id: <cover.1581555616.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: DM5PR21CA0029.namprd21.prod.outlook.com
 (2603:10b6:3:ed::15) To SN1PR12MB2528.namprd12.prod.outlook.com
 (2603:10b6:802:28::33)
MIME-Version: 1.0
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM5PR21CA0029.namprd21.prod.outlook.com (2603:10b6:3:ed::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2750.2 via Frontend
 Transport; Thu, 13 Feb 2020 01:14:30 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: eedf4823-c427-4b74-eed4-08d7b0221460
X-MS-TrafficTypeDiagnostic: SN1PR12MB2366:|SN1PR12MB2366:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB23662CFB0AFBEB3B7607B73F8E1A0@SN1PR12MB2366.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1247;
X-Forefront-PRVS: 031257FE13
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(346002)(136003)(366004)(376002)(39860400002)(396003)(199004)(189003)(8936002)(5660300002)(66946007)(66476007)(66556008)(7416002)(2906002)(6916009)(6666004)(4326008)(7696005)(52116002)(316002)(36756003)(6486002)(86362001)(956004)(2616005)(81156014)(478600001)(8676002)(81166006)(26005)(16526019)(186003);DIR:OUT;SFP:1101;SCL:1;SRVR:SN1PR12MB2366;H:SN1PR12MB2528.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 vm5Oekg1PzDWUCfnTR0TIfEjWaJ0leaqTiRUi/Mhj29wKq6nhYUSyeanCwRiiPhgMwrXd+y/a6keh+TRlZmQVopi5nKeawslfLeyc8dXRoTglxPcbLJB2ouMDKHKDhivadEHfW6MB756832L4cTT9+h2L2B4HeHyHFxkKizoDTWfisGNAY63NEYOMc89Q6v+eWoQ3q8dCAKn/ZR+ECM/cxlAjld05JWB4sVuTdBd2pjROGC8SuDM3bHK+nOUZ/SHZDAoZSqwwMaA7DdJqLhFCg0KxreojQUcMN4rimiVq4SEsbpK+VdOph7MXzfAFb3J1oAW3FQV6SLHELCG/cFGoWdxobpvOPwZVQ32VHIxjC+fGiBO+nC2z3/RqZjAKnNQULjXNufLjVzH3yCSMvkPzpQPbw2fTQKThU0hw3wEjGjySIx9VxLlv13V/0PplCcT
X-MS-Exchange-AntiSpam-MessageData: 
 q5JB4ccMyH2CN/rV7N2s9NF/MQrXpw6SQsJ3Ti0oHrb6MUtTU+mY15tEd35PqTk76ymEEtKNwNUnVEY0LDTYjvzXoxmaDfm1fpRikkgQjHsTLeO7px2sd9cbEeWX4LR2sr0aNr5p2IU9UU2kXNvyCg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 eedf4823-c427-4b74-eed4-08d7b0221460
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 Feb 2020 01:14:31.8515
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 9KTkE11OHu1RrD8JI+CwScZ38w1u4PCbU7xoU5WrSsK1cxHJsSkQ09spjk9cLj2JBkHL2MPcKavWGzDzgV/vDg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2366
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

This patchset adds support for SEV Live Migration on KVM/QEMU.

Ashish Kalra (1):
  KVM: x86: Introduce KVM_PAGE_ENC_BITMAP_RESET ioctl

Brijesh Singh (11):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce KVM_GET_PAGE_ENC_BITMAP ioctl
  mm: x86: Invoke hypercall when page encryption status  is changed
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

 .../virt/kvm/amd-memory-encryption.rst        | 120 ++++
 Documentation/virt/kvm/api.txt                |  59 ++
 Documentation/virt/kvm/hypercalls.txt         |  14 +
 arch/x86/include/asm/kvm_host.h               |   7 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/paravirt.h               |   6 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/svm.c                            | 662 +++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  36 +
 arch/x86/mm/mem_encrypt.c                     |  57 +-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  53 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 16 files changed, 1037 insertions(+), 9 deletions(-)
```
#### [PATCH kvm-unit-tests 0/2] runtime: Allow additional VMM parameters
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Thu Feb 13 14:32:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11380449
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 88EE7138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 14:33:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5E42C222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 14:33:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ToepIe89"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727199AbgBMOdS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 09:33:18 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:36026 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726780AbgBMOdS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 09:33:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581604397;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=oGtow9nh8dtc4aTC5O2Xg5N2hKJc+xrZ4V6BZwWGSEA=;
        b=ToepIe898AY/pwiwUV13t+5hiFlsMgo8ZMZh2EwDLY1ITPuMuP4O5h1mg3iKLFd3usUyl4
        ssuH9Qt39w+LtLZjsCh3boYp+MKfVoVW7awgolSBP2dSOb4CtDGI7jZhBhTEmNjcbN17n9
        AW4lwflt1SLzJgQH/m1uDpJuKoNhBHo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-240-n9XcrUVLNd6SMX6P5o8RMg-1; Thu, 13 Feb 2020 09:33:10 -0500
X-MC-Unique: n9XcrUVLNd6SMX6P5o8RMg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D09FD1902EA0;
        Thu, 13 Feb 2020 14:33:08 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A4B475C1D6;
        Thu, 13 Feb 2020 14:33:01 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: peter.maydell@linaro.org, alex.bennee@linaro.org,
        pbonzini@redhat.com, lvivier@redhat.com, thuth@redhat.com,
        david@redhat.com, frankja@linux.ibm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests 0/2] runtime: Allow additional VMM parameters
 to be provided
Date: Thu, 13 Feb 2020 15:32:58 +0100
Message-Id: <20200213143300.32141-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Occasionally users want to temporarily add additional VMM (QEMU)
parameters to all tests (run_tests.sh) or to tests executed with
$ARCH/run. With $ARCH/run it's already easy to do, just append
them to the command line, but with run_tests.sh there wasn't any
way to do it. This series provides two ways. It allows the
parameters to be appended to the $QEMU environment variable,
which is reasonable thing to expect to work, but doesn't
solve the problem of providing parameters that override what
is specified in the unittests.cfg file. So VMM_PARAMS is also
introduced, which is another environment variable just for
the additional parameters, and that variable takes care to
show up on the command line in the appropriate places, depending
on how the tests are being invoked.

Thanks,
drew


Andrew Jones (2):
  arch-run: Allow $QEMU to include parameters
  runtime: Introduce VMM_PARAMS

 README.md             |  5 +++++
 arm/run               |  4 +++-
 powerpc/run           |  4 +++-
 s390x/run             |  1 +
 scripts/arch-run.bash | 14 +++++++++++++-
 scripts/runtime.bash  |  4 +++-
 x86/run               |  4 +++-
 7 files changed, 31 insertions(+), 5 deletions(-)
```
#### [RFC PATCH 0/3] KVM: x86: honor guest memory type
##### From: Chia-I Wu <olvaffe@gmail.com>

```c
From patchwork Thu Feb 13 21:30:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chia-I Wu <olvaffe@gmail.com>
X-Patchwork-Id: 11381323
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A3DE92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 21:30:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EDDDB20848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 21:30:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="dTiM0Mz/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387410AbgBMVaj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 16:30:39 -0500
Received: from mail-pj1-f68.google.com ([209.85.216.68]:51271 "EHLO
        mail-pj1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728682AbgBMVaj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 16:30:39 -0500
Received: by mail-pj1-f68.google.com with SMTP id fa20so2937206pjb.1
        for <kvm@vger.kernel.org>; Thu, 13 Feb 2020 13:30:39 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=UjVzNJBK83ikW0TIlSzbtH1BgwGaguqWKS1Uh0bPMR8=;
        b=dTiM0Mz/slq1uUJKEcofNHhqiUiy7xB79p/2HWlp3laiLYDRlanVmv3B8fHGkWuNmG
         yzNk+Kf2OaG7UYgZ9A7v4voYtOSO6A7JeYhJo4K0oLnKldbLXjrdldMSlwwdfd9hwmAj
         u3qY3vh6IN6M7aP/dB6pXf6BpjJZw5VLmyqlMxeSS1SU9MFZW7BjJRRCw2X6oT0i0VVT
         luAobTHEoP9utgoebAvgXbND66i1qqR0Qpm/fnGAxfLog89sj3CDq4TVNufkTkJcBehj
         JbRpscT+pLn99ueAjpSGZ+SeX4RvFIrleYVCnr4h6WxpM8JnKtlu1zNzIjIK2zFNVQVo
         2eXQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=UjVzNJBK83ikW0TIlSzbtH1BgwGaguqWKS1Uh0bPMR8=;
        b=QVYanljZhg3XCklsRyFji2gtGs5wczw6zaezINnv7jnVFjAQq9glkF9NjNw1WZUgCC
         eJg3FaIn8RCPUlhkFXS6yyzQiQcLSnt4gOG9IchD+dRngA7nsktLDPgLi0XU6QUEMYX9
         Hs7Rd5OmA9dhzC2DdVgDUbx+rCngTZAsjcYY+WEJcsAaOgpyJgvAgTKmQuFFV01c3u/Y
         jb7AD1L6N/xLIh9F+tgK+6RxWGon7V+pscbZ29lNsYqhemU/RdNfIbgTw/+mDwdK+qcv
         9NpdVWUSN0oaBGcyjP6QQVekId0d3w0QsTvnDvjPCjVsTb0F0ZHH0oNMX4Q6BxsPWzeL
         YZKg==
X-Gm-Message-State: APjAAAUENkGXo9tasRO5iarKm0xwZIkeZ59z1+z8dqi9cX8W3bP0YgWQ
        X80V83N5Xun+0j4V2Zm1EaeC5HLd
X-Google-Smtp-Source: 
 APXvYqzp6i4zNTju3fPQFtSvmNIUZa6xjTh/ZBrude8YNxGPXiOUyGFvHEPV8DEPau1cdMHscsnW5g==
X-Received: by 2002:a17:90a:20c4:: with SMTP id
 f62mr7709341pjg.70.1581629438674;
        Thu, 13 Feb 2020 13:30:38 -0800 (PST)
Received: from olv0.mtv.corp.google.com
 ([2620:15c:202:201:9649:82d6:f889:b307])
        by smtp.gmail.com with ESMTPSA id
 s130sm4346683pfc.62.2020.02.13.13.30.37
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 13 Feb 2020 13:30:38 -0800 (PST)
From: Chia-I Wu <olvaffe@gmail.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, gurchetansingh@chromium.org,
        kraxel@redhat.com, dri-devel@lists.freedesktop.org
Subject: [RFC PATCH 0/3] KVM: x86: honor guest memory type
Date: Thu, 13 Feb 2020 13:30:33 -0800
Message-Id: <20200213213036.207625-1-olvaffe@gmail.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Host GPU drivers like to give userspace WC mapping.  When the userspace makes
the mapping available to a guest, it also tells the guest to create a WC
mapping.  However, even when the guest kernel picks the correct memory type,
it gets ignored because of VMX_EPT_IPAT_BIT on Intel.

This series adds a new flag to KVM_SET_USER_MEMORY_REGION, which tells the
host kernel to honor the guest memory type for the memslot.  An alternative
fix is for KVM to unconditionally honor the guest memory type (unless it is
MMIO, to avoid MCEs on Intel).  I believe the alternative fix is how things
are on ARM, and probably also how things are on AMD.

I am new to KVM and HW virtualization technologies.  This series is meant as
an RFC.
```
