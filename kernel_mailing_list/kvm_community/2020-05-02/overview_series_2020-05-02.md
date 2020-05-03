#### [PATCH 01/10] KVM: x86: Save L1 TSC offset in 'struct kvm_vcpu_arch'
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11523633
Return-Path: <SRS0=JxFu=6Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E7218139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  2 May 2020 04:33:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9B4524957
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  2 May 2020 04:33:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727853AbgEBEcj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 2 May 2020 00:32:39 -0400
Received: from mga09.intel.com ([134.134.136.24]:55783 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726058AbgEBEci (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 2 May 2020 00:32:38 -0400
IronPort-SDR: 
 gc6Godd/p1nzJby0DmhrQQPkI6AlRi2eyZLb1IRDhThfCJFP7sKKHR/c/zFG4B6sD/wtPcrMVx
 Ufj+NaQC8i4w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 May 2020 21:32:37 -0700
IronPort-SDR: 
 s3SItXf8FI90I6c37wagDESUOHL5GVAE2rxu3biDT6VwsjSDLuVtjNGRVeC7Ba+HaUHZii854K
 OuhDlfk5tXug==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,342,1583222400";
   d="scan'208";a="433516114"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga005.jf.intel.com with ESMTP; 01 May 2020 21:32:37 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 01/10] KVM: x86: Save L1 TSC offset in 'struct kvm_vcpu_arch'
Date: Fri,  1 May 2020 21:32:25 -0700
Message-Id: <20200502043234.12481-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200502043234.12481-1-sean.j.christopherson@intel.com>
References: <20200502043234.12481-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Save L1's TSC offset in 'struct kvm_vcpu_arch' and drop the kvm_x86_ops
hook read_l1_tsc_offset().  This avoids a retpoline (when configured)
when reading L1's effective TSC, which is done at least once on every
VM-Exit.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/svm/svm.c          | 11 -----------
 arch/x86/kvm/vmx/vmx.c          | 12 ------------
 arch/x86/kvm/x86.c              |  9 ++++-----
 4 files changed, 5 insertions(+), 29 deletions(-)

```
#### [PATCH v2] kvm: ioapic: Introduce arch-specific check for lazy update EOI mechanism
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11523791
Return-Path: <SRS0=JxFu=6Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 25CD713B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  2 May 2020 09:25:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0811924961
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  2 May 2020 09:25:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="W17IrbT3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726900AbgEBJZI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 2 May 2020 05:25:08 -0400
Received: from mail-bn8nam11on2085.outbound.protection.outlook.com
 ([40.107.236.85]:6070
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726488AbgEBJZH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 2 May 2020 05:25:07 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YEN65vG+7qnWUOMPMRJtDyDlt+K79CwUUeddvvMRktvQICkdY+6FzTAM1DedpdXpjqf8Bx3vIRn/hcI0rVsHS8PvC4qRU4a0vn5617dprYTC4UWv3IKMwcPD+TcWYf/QFZmilYogL63p58a0uzFBkfjELwuIfVpo1a82EYYgCI+DNi/AFNUZyncbOKZo+nhyZYC/9wU0DZko0JMjpz4g8nVzrfYA9Pf8VxskQ0sTOr+7nieqjknvB+nTtSzGLIz24vH7tO5XSAlwL2V8tKPhJkRNI4X8CYhTNdmmyyTA4fQEE3mV86bl5zRvGaOUo2B2Jv/6hkvm+UZobMeFu5xF8g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IJejiRr8Xs88REwngCdKafHzmG56UtE4ZZYx7Zkph6k=;
 b=T9o7/24akZqH847zu8FFBUA8B94qxpwKnfPfEckfYW+SKNUvyaiHVAEvkOV/mxATpRimikExNCw8tdxNCWbWOxsY9NywIZwgFoZz5xBgpuAeuGkTNd95MkzE9n9iQhU5mrDmOzRZEMpl6kqT7eECyll0OhuAqwMINuSeHscZNoCB56KGyovjrHCRO2uCswfqSDGYjGWRKsj4Ql+3lJkVm3Xz8T/OcRdCPghWbbebM+PEMx7GcXE8C/6HqXakOH7BlfRzrN/37phT8ivUp1/9HighcfEEwxwkuwxLNuc9Xvkv8jrS7FpVddFaLm6LvUgr+yfcrZPr66fIKORgWeduZQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IJejiRr8Xs88REwngCdKafHzmG56UtE4ZZYx7Zkph6k=;
 b=W17IrbT3peb60RM7G6nOxet8g6mTG3jNyPUbsZBcYcrQArO2s8hRxoHQmqEfmOS15vMfDX6d7PvzKcAN2LHaToCV7zawH1KczQmHIFRmZfI7R/puksUHgYV3dbNPpOnoC0HfwvfA5+kPijfgdAxbEywoAfPn9LEo3b1HzeSlhu8=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) by
 DM5PR12MB1625.namprd12.prod.outlook.com (2603:10b6:4:b::13) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2937.22; Sat, 2 May 2020 09:25:02 +0000
Received: from DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744]) by DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744%4]) with mapi id 15.20.2937.034; Sat, 2 May 2020
 09:25:02 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, joro@8bytes.org,
        jon.grimm@amd.com, borisvk@bstnet.org,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH v2] kvm: ioapic: Introduce arch-specific check for lazy update
 EOI mechanism
Date: Sat,  2 May 2020 04:24:55 -0500
Message-Id: <1588411495-202521-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: SN4PR0701CA0025.namprd07.prod.outlook.com
 (2603:10b6:803:2d::22) To DM5PR12MB1163.namprd12.prod.outlook.com
 (2603:10b6:3:7a::18)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 SN4PR0701CA0025.namprd07.prod.outlook.com (2603:10b6:803:2d::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.20 via Frontend
 Transport; Sat, 2 May 2020 09:25:01 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 58d32d48-8f49-4bae-8c43-08d7ee7ab124
X-MS-TrafficTypeDiagnostic: DM5PR12MB1625:|DM5PR12MB1625:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB16257633ADBF4A27A223B709F3A80@DM5PR12MB1625.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:901;
X-Forefront-PRVS: 039178EF4A
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1163.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(136003)(346002)(39860400002)(366004)(396003)(376002)(8936002)(66946007)(16526019)(2906002)(15650500001)(66556008)(2616005)(66476007)(36756003)(186003)(316002)(6486002)(8676002)(44832011)(956004)(26005)(86362001)(52116002)(7696005)(5660300002)(6666004)(4326008)(966005)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 20ZUizVh01Q2X94KXX1NyitCGEJ/rrj8MAOHYe0bLyP01hQ22mQ1W5qmWcvEaxDrAG7TrQ5HBNR5UUOjdUpuNLhcmYtnE9GUBwQhaXv0AmDxHnUQI93DSgpfQNjYnz8lXnxtgxg+tm/rz1xwbP8Tf5Kpmw66QLzSsyxDiVPrGtbXugsozQ6xMTEjpy00fFh7+NzrwRXm9CVdWrSe1ZKnRQTWvK+VduSo4nRaG4P3pBsWa6Z+L43kEY8qowqe3H7UxEDphy+I8ePzvqMlf6Cab7xG99t/O5sT6LTmUjD5Avr3qvkLTUkktXbNe6W0oNLN0droK3TJ1YPcBp8TzuUYCRx9p+L/DqNj/w6cGeN0ZFqa8thB3UGczvFcqjsPDGpPp+c3C0AZnvQ4Vh2ey3ChB8gktmfHqcWhxhRmFbOECiEZ7BEZ7cvuiPWNa1/RpZS/SuPLPHM9niYpwiHyuxF9z/n4HjtHNx9VMWx8uyyvDy6rXgKPm3iVEL2Pv73FPx0pVDHMg/ixEEOsivAloymxQg==
X-MS-Exchange-AntiSpam-MessageData: 
 WZlTGTa6wnLwsuUD+ApuL3ZugizXE9LYors5MfDr+Z6lr76qr+IQnMVz/QdUitA6OBQIgZid/uY+CzaXxUZweZj+LDMlMTGvThEc64XQDkiO/SCBTc6cDrPKjZmGB0tFN33/2whgPNqY1Y4FgHx2WLv8TIN9f1iD1zBn2k5ZQM2UdKcqf9awrnS/eKCQRI9dK/+OREX+Cp3s9iVBqv3UohLLnZGmC1cYxODTSR0aTHhbE3h8CK0humlu92Mf9Ex2B4e/lOGadlXqnr6TXbfHMCVMab2jYnrHibqEKv4WKzgdck8hZDuWMISdQi1LaTL8IovvjbPb+3n2DQeq3BMvq4DeOpOOA/FXGLRkexXBG9p4vx+im/B+jSRUtQwsSJntLVYo/1AsrUtxPTwTlbIDfhw8Y+aqY53B6pUsgQ0GdxxC9l6FLbufjnUomkXfXj0/GR8Rrb7zBMM5TpjJ2C8w3SO07YKJTQfRtGgASEhGcK6zz5WfXOw2+vsyjEwwI+ptCVmOsg+pmb1vUtKEhmAb1mu9bd6RAlKhVRnjM78q+MHylocEKUpHn2DEpXrp/GXY1Iux3mhJ5uLei+46UqBFKtAvoMwFaH5lY3NdIX5MzJKu6W9VN3SEQ1VS3OehT8YK/xtdXtJoABdQ20hpDfVN8siN5j7YqkX3HUcgRDUIZCoQx3NEjwWKKM2zXNvwW4p6u8jwmJ+JcGWyJz+CgdzATi1jFJ6qja6sc+ca2nB+0cPGwaa/gmao9ZoWhX8VPyKjsTCaPFvv5Xsy5mkjyBnf1xM2OphtKx19FA0posVXKLw=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 58d32d48-8f49-4bae-8c43-08d7ee7ab124
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 May 2020 09:25:02.4356
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 C2f5NXZupxPDVZ2/6tq6gOVPQP9S3VRV0ndT/klLQ1f2IUgKLLkZZIeTdsbUs2tkGEcvXm9XlLF5+vObn/9aEA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1625
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI") introduces
the following regression.

BUG: stack guard page was hit at 000000008f595917 \
(stack is 00000000bdefe5a4..00000000ae2b06f5)
kernel stack overflow (double-fault): 0000 [#1] SMP NOPTI
RIP: 0010:kvm_set_irq+0x51/0x160 [kvm]
Call Trace:
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
 irqfd_resampler_ack+0x32/0x90 [kvm]
 kvm_notify_acked_irq+0x62/0xd0 [kvm]
 kvm_ioapic_update_eoi_one.isra.0+0x30/0x120 [kvm]
 ioapic_set_irq+0x20e/0x240 [kvm]
 kvm_ioapic_set_irq+0x5c/0x80 [kvm]
 kvm_set_irq+0xbb/0x160 [kvm]
 ? kvm_hv_set_sint+0x20/0x20 [kvm]
....

This is due to re-entrancy of the lazy update EOI logic
when enable APICv with VFIO pass-through device, which
sets up kvm_irqfd() w/ KVM_IRQFD_FLAG_RESAMPLE.

Fixes by adding re-entrancy check logic.

Reported-by: borisvk@bstnet.org
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Link: https://www.spinics.net/lists/kvm/msg213512.html
Fixes: f458d039db7e ("kvm: ioapic: Lazy update IOAPIC EOI")
Bugzilla: https://bugzilla.kernel.org/show_bug.cgi?id=207489
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/ioapic.c | 11 +++++++++++
 arch/x86/kvm/ioapic.h |  1 +
 2 files changed, 12 insertions(+)

```
