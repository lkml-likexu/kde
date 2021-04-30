

#### [PATCH v3 0/2] KVM: x86: Enable dirty logging lazily for huge pages
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Apr 29 03:41:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12230367
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3562C433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 03:41:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9C8FA610A2
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 03:41:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236863AbhD2DmX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 23:42:23 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:17049 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229805AbhD2DmW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 23:42:22 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FW1S16H0DzPvQL;
        Thu, 29 Apr 2021 11:38:25 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Thu, 29 Apr 2021 11:41:25 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Ben Gardon <bgardon@google.com>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v3 0/2] KVM: x86: Enable dirty logging lazily for huge pages
Date: Thu, 29 Apr 2021 11:41:13 +0800
Message-ID: <20210429034115.35560-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Currently during start dirty logging, if we're with init-all-set,
we write protect huge pages and leave normal pages untouched, for
that we can enable dirty logging for these pages lazily.

Actually enable dirty logging lazily for huge pages is feasible
too, which not only reduces the time of start dirty logging, also
greatly reduces side-effect on guest when there is high dirty rate.

Thanks,
Keqian

Changelog:

v3:
 - Discussed with Ben and delete RFC comments. Thanks.

Keqian Zhu (2):
  KVM: x86: Support write protect gfn with min_level
  KVM: x86: Not wr-protect huge page with init_all_set dirty log

 arch/x86/kvm/mmu/mmu.c          | 38 ++++++++++++++++++++++++++-------
 arch/x86/kvm/mmu/mmu_internal.h |  3 ++-
 arch/x86/kvm/mmu/page_track.c   |  2 +-
 arch/x86/kvm/mmu/tdp_mmu.c      | 16 ++++++++++----
 arch/x86/kvm/mmu/tdp_mmu.h      |  3 ++-
 arch/x86/kvm/x86.c              | 37 +++++++++-----------------------
 6 files changed, 57 insertions(+), 42 deletions(-)
```
#### [PATCH v3 0/2] KVM: x86: guest interface for SEV live migration
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Thu Apr 29 10:47:05 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12230977
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D4EB6C433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 10:47:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A9E9613E8
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 10:47:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240494AbhD2KsC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 06:48:02 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41477 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232245AbhD2Kr7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Apr 2021 06:47:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619693232;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=N9yW175n2/Fko+VjOrEdOCUWNBA9vqG7mA8IcKObQLw=;
        b=hypsTPujQo9vhQoevNCS75yDH/CdF110XfJ6s2MpMPnPIP16LkrZ8MRAyrclCGw5dKHnAo
        JtY35d5lcBpwyXXf8P9VO2YxLGqlm4pRVD5cN5jt4gS/BD9YlHeFAYHHi2RaoYYjUA7+O+
        RmET/1S48elS03HAWTnHgDez9dU+9D4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-539-Y3VwTIlZNjG3KF0B0M7I0A-1; Thu, 29 Apr 2021 06:47:10 -0400
X-MC-Unique: Y3VwTIlZNjG3KF0B0M7I0A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DD55D8018A7;
        Thu, 29 Apr 2021 10:47:08 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 317EE5DF26;
        Thu, 29 Apr 2021 10:47:08 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: srutherford@google.com, seanjc@google.com, joro@8bytes.org,
        brijesh.singh@amd.com, thomas.lendacky@amd.com,
        ashish.kalra@amd.com
Subject: [PATCH v3 0/2] KVM: x86: guest interface for SEV live migration
Date: Thu, 29 Apr 2021 06:47:05 -0400
Message-Id: <20210429104707.203055-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a reviewed version of the guest interface (hypercall+MSR)
for SEV live migration.  The differences lie mostly in the API
for userspace.  In particular:

- the CPUID feature is not exposed in KVM_GET_SUPPORTED_CPUID

- the hypercall must be enabled manually with KVM_ENABLE_CAP

- the MSR has sensible behavior if not filtered

Compared to v2, the KVM-provided behavior of the MSR is different:
it is set to 0 if the guest memory is encrypted, and 1 if it is not.
The idea is that the MSR is read-only if KVM_FEATURE_HC_PAGE_ENC_STATUS
is not exposed to the guest (it should only be exposed if the guest has
encrypted memory), but it also has a sensible value for non-encrypted
guests.  QEMU could however expose a "0" value for the special "-cpu
host,migratable=no" mode if it wanted.

Because of this new behavior, the CPUID bit are split.

Paolo

Ashish Kalra (1):
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall

Paolo Bonzini (1):
  KVM: x86: add MSR_KVM_MIGRATION_CONTROL

 Documentation/virt/kvm/api.rst        | 14 +++++++
 Documentation/virt/kvm/cpuid.rst      |  9 +++++
 Documentation/virt/kvm/hypercalls.rst | 21 ++++++++++
 Documentation/virt/kvm/msr.rst        | 14 +++++++
 arch/x86/include/asm/kvm-x86-ops.h    |  1 +
 arch/x86/include/asm/kvm_host.h       |  3 ++
 arch/x86/include/uapi/asm/kvm_para.h  |  5 +++
 arch/x86/kvm/cpuid.c                  |  3 +-
 arch/x86/kvm/svm/svm.c                |  1 +
 arch/x86/kvm/vmx/vmx.c                |  7 ++++
 arch/x86/kvm/x86.c                    | 56 +++++++++++++++++++++++++++
 include/uapi/linux/kvm.h              |  1 +
 include/uapi/linux/kvm_para.h         |  1 +
 13 files changed, 135 insertions(+), 1 deletion(-)
```
#### [RFC 0/2] [RFC] Honor PCI prefetchable attributes for a virtual
##### From: Shanker Donthineni <sdonthineni@nvidia.com>

```c
From patchwork Thu Apr 29 16:29:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shanker R Donthineni <sdonthineni@nvidia.com>
X-Patchwork-Id: 12231545
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CF5C8C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:29:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 924E961407
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:29:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240816AbhD2Qah (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 12:30:37 -0400
Received: from mail-dm6nam11on2084.outbound.protection.outlook.com
 ([40.107.223.84]:15136
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233302AbhD2Qag (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 12:30:36 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=DV0ATN2ybJSbGaOcgFaNG/5ubyTqtTCUSepKDkSAbYrLRGcqR6Vh0lgja/IFKAB+eprKzyxSEKlGEW98Glt3n4iw26lcffhbenGJeNDew4oXC9ld4FVZb/JcgZJo2aNxsB6jB2vM8RcWJMNV7i9SpZJCP6PsZe977bDqScMADC0BlaUjMiFTQe0KeEn9lRdRK3ufjiHN8nY/Y9e1dgu4/QV6Ejlbno+ps8SoWm1ufC1zMyPBBwS8lViRACYJKdgvMFNiFqaMcTkyenVZqpWOCPTzuRVB8P/vLsS89PQ2l/euZgumZFBoxQgZcyq5kHBzvkpGWrXmzFQoBIN9mXYrBA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MKwmcvJlnAryc2O6/Z+gYUK6HFhpJR4lqcr9k33pB4Q=;
 b=bnHOH34+Dn/8QRkgfLQ/LH05BqShguZrvZEzkltsbJi1I2kv454U+8E9eJK2+UbW//Vx4dCmGZ3tUOmfyv0r+PbLsg/IqLQB+jHq3pWlEBZHthepfTB1erTIqUp4fB9e+dfhmUOqrLPvlrN0ONUPVn3wGyj3MXLTFSNmxLA77oYbnqpba0t2Xn+9rFy/LctpVqGSlGLFaoWVu6mLoGPTgC7xAQeoYLbByiGwK4L9FCvvJ3qYtRcRWLrFmmcFL0E4o4NQ3I7XlPwK9gBD0xF9FcZGoR8dqh5jLoEexq9ltbP2k16ck40IWgMb/xCdJDsb71OQZhJqJzGgDMXgBrcMwQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.34) smtp.rcpttodomain=lists.cs.columbia.edu
 smtp.mailfrom=nvidia.com; dmarc=pass (p=none sp=none pct=100) action=none
 header.from=nvidia.com; dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MKwmcvJlnAryc2O6/Z+gYUK6HFhpJR4lqcr9k33pB4Q=;
 b=Y0lgFBEp0B8kAw0Fr8k3f8yyD758FK8fHHglbbkNtXSwd9zeTMkI75ZCpON3U7/2Pzb1SCFng6fp2ICrjV1s4KGy7oP1HZ/sOeFASp5Rp3BJf4UcYjS11AcVvw/qRIAT3DEUka9OWOQ/QXu7iIGQM2KQkRs8RrrCHMR3A7sWkic7WwVTBCOQZvGCoLQtSmWGMNZRvqAlyJsC4bwpu6nwZ/DLbmd2dJerxN0WHuNkK7+WafHe20shc1/ih3sQVw+T4Vr1nnDWGGByCnIdhCp7DcKmpdqJO7RJbTRCIUIzGGicBcYsWqEzNCRafUxCPwTzfubPmyaH70gtSx/wHopheQ==
Received: from DS7PR05CA0028.namprd05.prod.outlook.com (2603:10b6:5:3b9::33)
 by CY4PR12MB1399.namprd12.prod.outlook.com (2603:10b6:903:38::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21; Thu, 29 Apr
 2021 16:29:48 +0000
Received: from DM6NAM11FT015.eop-nam11.prod.protection.outlook.com
 (2603:10b6:5:3b9:cafe::87) by DS7PR05CA0028.outlook.office365.com
 (2603:10b6:5:3b9::33) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.8 via Frontend
 Transport; Thu, 29 Apr 2021 16:29:48 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.34)
 smtp.mailfrom=nvidia.com; lists.cs.columbia.edu; dkim=none (message not
 signed) header.d=none;lists.cs.columbia.edu; dmarc=pass action=none
 header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.34 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.34; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.34) by
 DM6NAM11FT015.mail.protection.outlook.com (10.13.172.133) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.4087.32 via Frontend Transport; Thu, 29 Apr 2021 16:29:48 +0000
Received: from SDONTHINENI-DESKTOP.nvidia.com (172.20.145.6) by
 HQMAIL107.nvidia.com (172.20.187.13) with Microsoft SMTP Server (TLS) id
 15.0.1497.2; Thu, 29 Apr 2021 16:29:46 +0000
From: Shanker Donthineni <sdonthineni@nvidia.com>
To: Marc Zyngier <maz@kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>
CC: Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>, Vikram Sethi <vsethi@nvidia.com>,
        Shanker Donthineni <sdonthineni@nvidia.com>,
        "Jason Sequeira" <jsequeira@nvidia.com>
Subject: [RFC 0/2] [RFC] Honor PCI prefetchable attributes for a virtual
 machine on ARM64
Date: Thu, 29 Apr 2021 11:29:04 -0500
Message-ID: <20210429162906.32742-1-sdonthineni@nvidia.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [172.20.145.6]
X-ClientProxiedBy: HQMAIL107.nvidia.com (172.20.187.13) To
 HQMAIL107.nvidia.com (172.20.187.13)
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 2330b376-b545-4e6b-6277-08d90b2c0196
X-MS-TrafficTypeDiagnostic: CY4PR12MB1399:
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB13991218BC5E5EC130F7FDA4C75F9@CY4PR12MB1399.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 oTdymT9Lxt922Nr8khytSCv3ci8vzPYf62xPKnj3uzn2oPBcisRsn2ajRLpXPm0KqvEPKiEw/DjGVegozQFePTGXhq5Pl8fnOWh8p0ycnwFd6mGF/xRd1rrcZzjdLyrz+xdONwk0gdyKOnErytdfKnWIm4jW4PVYKLKVU9c1PkY2FRv8aeNzfWgENccoBNzMlpM8zPV74NDaGRopAtXXK16mhzIqeBYesUyCWaHqvHZBduB82Yd2Mx4dLsu1/GMDA3fjNQXXpGSIXrk8Z8meaUCOua/E1imp1D3gb1Hf9+FxMJZSXFrxZ2Kg/k38QD3Cg4/Uk1JAmoITEvQKgMejelfZFHVmfvqkcvjNdN0v7R8txzxoXmvUbErmwl3hgGzhCSWC6Y4W+qJzzPJEclyU2TZpVpPJLX8SZlN5tSEJcLjP3Ydvhu0F8a84bgNmDKmoSTa3/2JcUg0Nkhp7TYi1VRBwNe7pF3Hw2SuNSS2VI+aK7vjQRiH3wI3RcAwx5/IAhGQr6RCOSzCrtW1XZ0IoWU30hynKIa/5mGINRs05vK1KGTtMzvd0NuIrX4g6qZAI1hywDWrVzYBxPW5Ze1odtPffz6vB8Vy1YItXUdZbCtkJqj+GfixmT3fKwvWPQaA8ipcTDYoNamDyUPznwrHLR+a9yh7+syvtc1cpwUI5LpE=
X-Forefront-Antispam-Report: 
 CIP:216.228.112.34;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid03.nvidia.com;CAT:NONE;SFS:(4636009)(396003)(346002)(376002)(136003)(39850400004)(46966006)(36840700001)(36756003)(7696005)(70586007)(70206006)(2906002)(2616005)(8936002)(356005)(8676002)(86362001)(5660300002)(83380400001)(336012)(7636003)(36860700001)(82310400003)(1076003)(47076005)(110136005)(82740400003)(107886003)(54906003)(316002)(26005)(16526019)(186003)(36906005)(478600001)(6666004)(4326008)(426003);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Apr 2021 16:29:48.0066
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2330b376-b545-4e6b-6277-08d90b2c0196
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.34];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DM6NAM11FT015.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1399
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Problem statement: Virtual machine crashes when NVIDIA GPU driver access a prefetchable BAR space due to the unaligned reads/writes for pass-through devices. The same binary works fine as expected in the host kernel. Only one BAR has control & status registers (CSR) and other PCI BARs are marked as prefetchable. NVIDIA GPU driver uses the write-combine feature for mapping the prefetchable BARs to improve performance. This problem applies to all other drivers which want to enable WC.
 
Solution: Honor PCI prefetchable attributes for the guest operating systems.
 
Proposal: ARM64-KVM uses VMA struct for the needed information e.g. region physical address, size, and memory-type (struct page backed mapping or anonymous memory) for setting up a stage-2 page table. Right now memory region either can be mapped as DEVICE (strongly ordered) or NORMAL (write-back cache) depends on the flag VM_PFNMAP in VMA. VFIO-PCI will keep the prefetchable (write-combine) information in vma->vm_page_prot similar to other fields, and KVM will prepare stage-2 entries based on the memory-type attribute that was set in VMA.

Shanker Donthineni (2):
  vfio/pci: keep the prefetchable attribute of a BAR region in VMA
  KVM: arm64: Add write-combine support for stage-2 entries

 arch/arm64/include/asm/kvm_mmu.h     |  3 ++-
 arch/arm64/include/asm/kvm_pgtable.h |  2 ++
 arch/arm64/include/asm/memory.h      |  4 +++-
 arch/arm64/kvm/hyp/pgtable.c         |  9 +++++++--
 arch/arm64/kvm/mmu.c                 | 22 +++++++++++++++++++---
 arch/arm64/kvm/vgic/vgic-v2.c        |  2 +-
 drivers/vfio/pci/vfio_pci.c          |  6 +++++-
 7 files changed, 39 insertions(+), 9 deletions(-)
```
#### [PATCH kvm-unit-tests v3 0/8] arm/arm64: Prepare for target-efi
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Thu Apr 29 16:41:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12231561
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D3D6FC433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:41:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8B72161407
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:41:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240748AbhD2Qma (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 12:42:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43700 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233099AbhD2Qm3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Apr 2021 12:42:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619714502;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=KJvPIMRIaEUaTRVTXR0nZcXfhBmX/xq1gsZgnD2mQyg=;
        b=DP6ld4Q0wi3klN3RBagLgIncNpgmjQ5AN9yI2Xj5vwd9IGypQXMzxcYwsgrLNpzlPzR7L4
        vIBQL6BUwndeEShqk4SN8efdQhIc5atUI99+dq3thCqxQyf3Mwe0FllZP5o2zcZznRrMms
        bCOTwqi57Ewmr8VdEtt6/NlPcTfCWqw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-495-5vcgWDx7O0Ge58de1s8vJw-1; Thu, 29 Apr 2021 12:41:39 -0400
X-MC-Unique: 5vcgWDx7O0Ge58de1s8vJw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 865F91B18BC8;
        Thu, 29 Apr 2021 16:41:38 +0000 (UTC)
Received: from gator.redhat.com (unknown [10.40.192.243])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AF3DF64184;
        Thu, 29 Apr 2021 16:41:31 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: alexandru.elisei@arm.com, nikos.nikoleris@arm.com,
        andre.przywara@arm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests v3 0/8] arm/arm64: Prepare for target-efi
Date: Thu, 29 Apr 2021 18:41:22 +0200
Message-Id: <20210429164130.405198-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
 - Picked up Alex's r-b on patch 1 and 5
 - Removed useless cast in pci_host_bridge_get_paddr [Andre]
 - Added XN bits when mapping I/O pages [Alex]
 - Tweaks to patch 6 suggested by Alex and myself
 - Improved patch 8 commit message and changed psci-invoke's input
   and output parameter types

v2:
 - Addressed all comments from Nikos and Alex
 - The biggest changes are
   * dropping the weird persistent map stuff that I never liked by taking
     Alex's suggestion to just create the idmap early
   * adding mem_region_add() to clean up memory region adding code, also
     improved the assignment of region fields
 - Also, while we found that we still have a memory map assumption
   (3G-4G reserved for virtual memory allocation), I only make that
   assumption clear. I've left removing it for an additional patch
   for another day.
 - Added psci_invoke_none() to use prior to the PSCI method being set
 - Added r-b's for each patch given, unless the commit changed too much
 - Didn't take Alex's suggestion to use x5 for stacktop when calling
   setup from start. I prefer explicitly loading it again.


This series is a collection of patches derived from [1] that pave the
way for new targets, e.g. target-efi[2]. These patches mostly address
the elimination of memory map assumptions and they shouldn't have any
functional changes. The last two patches are a couple of patches not
related to the memory map, but they also prepare for bare metal targets.
I tossed them in since I don't think they should be too controversial.
This patch series is also available here [3].

[1] https://github.com/rhdrjones/kvm-unit-tests/commits/target-efi
[2] https://www.youtube.com/watch?v=kvaufVrL0J0
[3] https://gitlab.com/rhdrjones/kvm-unit-tests/-/commits/efiprep

Thanks,
drew


Andrew Jones (8):
  arm/arm64: Reorganize cstart assembler
  arm/arm64: Move setup_vm into setup
  pci-testdev: ioremap regions
  arm/arm64: mmu: Stop mapping an assumed IO region
  arm/arm64: mmu: Remove memory layout assumptions
  arm/arm64: setup: Consolidate memory layout assumptions
  chr-testdev: Silently fail init
  arm/arm64: psci: Don't assume method is hvc

 arm/cstart.S                |  92 ++++++++++++-------
 arm/cstart64.S              |  45 ++++++---
 arm/flat.lds                |  23 +++++
 arm/selftest.c              |  34 ++-----
 lib/arm/asm/io.h            |   6 ++
 lib/arm/asm/mmu.h           |   3 +
 lib/arm/asm/page.h          |   2 +
 lib/arm/asm/pgtable-hwdef.h |   1 +
 lib/arm/asm/psci.h          |  10 +-
 lib/arm/asm/setup.h         |   7 +-
 lib/arm/mmu.c               |  53 +++++++----
 lib/arm/psci.c              |  35 +++++--
 lib/arm/setup.c             | 177 +++++++++++++++++++++---------------
 lib/arm64/asm/io.h          |   6 ++
 lib/arm64/asm/mmu.h         |   1 +
 lib/arm64/asm/page.h        |   2 +
 lib/chr-testdev.c           |   5 +-
 lib/pci-host-generic.c      |   5 +-
 lib/pci-host-generic.h      |   4 +-
 lib/pci-testdev.c           |   4 +
 20 files changed, 335 insertions(+), 180 deletions(-)
```
#### [PATCH v4 0/4] KVM statistics data fd-based binary interface
##### From: Jing Zhang <jingzhangos@google.com>

```c
From patchwork Thu Apr 29 20:37:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12231903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5640DC433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 20:37:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 34E5D61423
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 20:37:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232532AbhD2Uid (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 16:38:33 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37166 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233664AbhD2Uic (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 16:38:32 -0400
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 788EFC06138F
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 13:37:44 -0700 (PDT)
Received: by mail-pj1-x104a.google.com with SMTP id
 11-20020a17090a194bb0290155426bcf44so502816pjh.4
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 13:37:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=AGPbcGDitssQwR2vRkOkuDZa9dX2kbuG1ibqn3VGykk=;
        b=vKUaHf8Js7ssAthsBYE69zLm1fhKC668a4XSogrAS2/Dj/o0DGFMmmsqCnsDdBK3r8
         fU72HhuLV+N91HbI4pSgh5Tv0i1PzUEBWXj5fFX67L+XU+lVL8pWWznsP0NVQAQ5lUN8
         tnGqagWLjEKhm+kdYP0z5D1VFGd6D7c5iZaQMTCVsEY02BoS0mnuzX3PxsSzTzAH96TW
         tg88Vd5GmUxj49R4qFOrP19khvrv7Uk7Z12xOA/41VGF6xIzWWzGX5Ujhfw/yE2w/sDo
         5qe4eKKz4NBm3zmwuvIwm9mkX7c0VkNxwjlxlY2NlKl+E9wZZUof0MbYVFwoGUhzfAhm
         LpEQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=AGPbcGDitssQwR2vRkOkuDZa9dX2kbuG1ibqn3VGykk=;
        b=XtI8MO3tEcPV9ThvmXZOVn/XV0lXEDBZME2z+1IPF9gJr83ZKf5QkMmft4AC/zijwU
         zAWGzoWcmhHz8uizT9AOTOlRLgaQXuKMCVBwQWzGptLEfzDyxOeAAFQWQqo9io4tOqcS
         fBXradZCQU0qk3EMlblooSPb3o2OE3NY8U6v+kOtIRg6ziINGxcx/egWQoq1wHxoTOkv
         I3u9rAeTOTadcbwnrjPZ37JTBLNV/yN0x3qI1t/vnzAH+gRhRXp+7YMIhjs/mOIRbP38
         OwEUDgI40AqHRUgF+ZcpLzs6yRYmwDVTtkRJdb6VQwEXD6t1b0FdsM3u7r1NGvg/2fIa
         rTZg==
X-Gm-Message-State: AOAM5303LZVWrlx2VdGw0kL+pbDzGy35tP9VuG3ugLFqOZW8nhMLR0yr
        FuehlYUDi2vBE4Iu6UMrOO3ERNvouzz6nabr1sjew5BApfcHFqdFEg7lqqnd82BSOEiqbtxNQi+
        8a7omWKVOpL4tcxsI6vYpn8E9mGDzIu21031wVfymyoX9RF/y1hBRO7wnygCpx9HFK7h6jGM=
X-Google-Smtp-Source: 
 ABdhPJxa1nzLFdFJjcOVu7fh1Y6W8Fs7WxRv4NSYd6yoIxBYT8+4qmIZrtv36CAWNU9/OaCLxfjmfxSFKptxvj1z1A==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:aa7:8e0d:0:b029:214:a511:d88b with
 SMTP id c13-20020aa78e0d0000b0290214a511d88bmr1651129pfr.2.1619728663762;
 Thu, 29 Apr 2021 13:37:43 -0700 (PDT)
Date: Thu, 29 Apr 2021 20:37:36 +0000
Message-Id: <20210429203740.1935629-1-jingzhangos@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v4 0/4] KVM statistics data fd-based binary interface
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a file descriptor for every VM and VCPU to read
KVM statistics data in binary format.
It is meant to provide a lightweight, flexible, scalable and efficient
lock-free solution for user space telemetry applications to pull the
statistics data periodically for large scale systems. The pulling
frequency could be as high as a few times per second.
In this patchset, every statistics data are treated to have some
attributes as below:
  * architecture dependent or common
  * VM statistics data or VCPU statistics data
  * type: cumulative, instantaneous,
  * unit: none for simple counter, nanosecond, microsecond,
    millisecond, second, Byte, KiByte, MiByte, GiByte. Clock Cycles
Since no lock/synchronization is used, the consistency between all
the statistics data is not guaranteed. That means not all statistics
data are read out at the exact same time, since the statistics date
are still being updated by KVM subsystems while they are read out.
---

* v3 -> v4
  - Rebase to kvm/queue, commit 9f242010c3b4 ("KVM: avoid "deadlock"
    between install_new_memslots and MMU notifier")
  - Use C-stype comments in the whole patch
  - Fix wrong count for x86 VCPU stats descriptors
  - Fix KVM stats data size counting and validity check in selftest

* v2 -> v3
  - Rebase to kvm/queue, commit edf408f5257b ("KVM: avoid "deadlock"
    between install_new_memslots and MMU notifier")
  - Resolve some nitpicks about format

* v1 -> v2
  - Use ARRAY_SIZE to count the number of stats descriptors
  - Fix missing `size` field initialization in macro STATS_DESC

[1] https://lore.kernel.org/kvm/20210402224359.2297157-1-jingzhangos@google.com
[2] https://lore.kernel.org/kvm/20210415151741.1607806-1-jingzhangos@google.com
[3] https://lore.kernel.org/kvm/20210423181727.596466-1-jingzhangos@google.com

---

Jing Zhang (4):
  KVM: stats: Separate common stats from architecture specific ones
  KVM: stats: Add fd-based API to read binary stats data
  KVM: stats: Add documentation for statistics data binary interface
  KVM: selftests: Add selftest for KVM statistics data binary interface

 Documentation/virt/kvm/api.rst                | 171 ++++++++
 arch/arm64/include/asm/kvm_host.h             |   9 +-
 arch/arm64/kvm/guest.c                        |  42 +-
 arch/mips/include/asm/kvm_host.h              |   9 +-
 arch/mips/kvm/mips.c                          |  67 ++-
 arch/powerpc/include/asm/kvm_host.h           |   9 +-
 arch/powerpc/kvm/book3s.c                     |  68 +++-
 arch/powerpc/kvm/book3s_hv.c                  |  12 +-
 arch/powerpc/kvm/book3s_pr.c                  |   2 +-
 arch/powerpc/kvm/book3s_pr_papr.c             |   2 +-
 arch/powerpc/kvm/booke.c                      |  63 ++-
 arch/s390/include/asm/kvm_host.h              |   9 +-
 arch/s390/kvm/kvm-s390.c                      | 133 +++++-
 arch/x86/include/asm/kvm_host.h               |   9 +-
 arch/x86/kvm/x86.c                            |  71 +++-
 include/linux/kvm_host.h                      | 132 +++++-
 include/linux/kvm_types.h                     |  12 +
 include/uapi/linux/kvm.h                      |  50 +++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 .../selftests/kvm/kvm_bin_form_stats.c        | 380 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  11 +
 virt/kvm/kvm_main.c                           | 237 ++++++++++-
 24 files changed, 1415 insertions(+), 90 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_bin_form_stats.c


base-commit: 9f242010c3b46e63bc62f08fff42cef992d3801b
```
#### [PATCH v2 0/7] Lazily allocate memslot rmaps
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Thu Apr 29 21:18:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12231953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B8A68C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 21:18:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8870961445
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 21:18:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237173AbhD2VTe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 17:19:34 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46580 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233293AbhD2VTe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 17:19:34 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4BDB8C06138B
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 14:18:47 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 i8-20020a0569020688b02904ef3bd00ce7so7065256ybt.7
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 14:18:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=5NDzCDKCGCk6XFMagA6CzP44uT46tOEAvw4LLjGAeOA=;
        b=rsK1XDnr5jWG+rKZO/5mZTxX0XfQb3/H8ivcRXIm8gWzPRbayNlE2dbGbIR2G21tnP
         CjdzicccsKnXkgCxrKknP2hlgTb2OvTbwkjMYfsSoG41gsJ6+v4Ot2toYnKn6Tu48ua8
         YwBI7l6OYQKS4jyWdgj7zcEY1jk2KSRxCUfOAgQy4rmguySN0O28l7NAS8qKBcGukhpy
         EtuKxQnFHjmTeMhFTjMMS2enzygdfISkubtywX1Kwnm+iL/fLlYd25Ylo69pqwXLbfi3
         yHJLPy9wsIxUHVlV1GqJUe4sJA8EuEsU3wgJy4AlznwRc1IjXxZrPO2GuumB9IhoMUnr
         XR6g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=5NDzCDKCGCk6XFMagA6CzP44uT46tOEAvw4LLjGAeOA=;
        b=RJnE1f0dk+1kWswiVG651eSupLBNnKo04q+tRU1dfC4xth8rvePuee//wo2+r+Ihty
         nJpT6Vv1Gci3Vx5rWOZVwrhkDlSNu5ehHSzdrvdqnQOV2eCN2rdqaMPx9GM4oUZwCfCA
         rYVD5mNZrrwYS1NVqEH0ROiOqhuG2SiLDu696F1bdwvLYOmtyqqP3vKOwibC52wX3Opn
         OJ+PS2k3Kyt8d4uwFGjLX7EJ496Vuc8mp8iFNFNWst7rtGdvua4WWSfLMzzhNAWv2RgO
         Tu8O7BMRzkpEcX4NinbeNAK6AbltvZVcv5+Qq4XJlzm027wbTda0rxMgRr7N8Wr+fxIY
         FtUg==
X-Gm-Message-State: AOAM533MKWgjFkh1cfzNeFiuOmflLKDqTX9TSbuXVT0krayzBTRD8GvL
        uPhD0azb5/4ug0ceJH4VnJ20FFO03olw
X-Google-Smtp-Source: 
 ABdhPJzMnmNUqhweoATHShUFOm2WiU0N4e30hQvigpqsUZJG3TEf8qs9lU0gYxxmgEWAVvG1Ltgqrz6ePbmj
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:1a18:9719:a02:56fb])
 (user=bgardon job=sendgmr) by 2002:a5b:611:: with SMTP id
 d17mr2257989ybq.421.1619731126562;
 Thu, 29 Apr 2021 14:18:46 -0700 (PDT)
Date: Thu, 29 Apr 2021 14:18:26 -0700
Message-Id: <20210429211833.3361994-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v2 0/7] Lazily allocate memslot rmaps
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

Changelog:
v2:
	Incorporated feedback from Paolo and Sean
	Replaced the memslot_assignment_lock with slots_arch_lock, which
	has a larger critical section.

Ben Gardon (7):
  KVM: x86/mmu: Track if shadow MMU active
  KVM: x86/mmu: Skip rmap operations if shadow MMU inactive
  KVM: x86/mmu: Deduplicate rmap freeing
  KVM: x86/mmu: Factor out allocating memslot rmap
  KVM: mmu: Refactor memslot copy
  KVM: mmu: Add slots_arch_lock for memslot arch fields
  KVM: x86/mmu: Lazily allocate memslot rmaps

 arch/x86/include/asm/kvm_host.h |  13 +++
 arch/x86/kvm/mmu/mmu.c          | 153 +++++++++++++++++++++-----------
 arch/x86/kvm/mmu/mmu_internal.h |   2 +
 arch/x86/kvm/mmu/tdp_mmu.c      |   6 +-
 arch/x86/kvm/mmu/tdp_mmu.h      |   4 +-
 arch/x86/kvm/x86.c              | 110 +++++++++++++++++++----
 include/linux/kvm_host.h        |   9 ++
 virt/kvm/kvm_main.c             |  54 ++++++++---
 8 files changed, 264 insertions(+), 87 deletions(-)
```
