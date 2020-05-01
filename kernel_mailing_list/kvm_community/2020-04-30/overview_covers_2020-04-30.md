

#### [PATCH v7 00/18] Add AMD SEV guest live migration support
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Thu Apr 30 08:39:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11519475
Return-Path: <SRS0=DGI+=6O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3725E14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 08:40:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14FD72192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 08:40:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="xjByJDfZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726531AbgD3IkI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Apr 2020 04:40:08 -0400
Received: from mail-dm6nam12on2083.outbound.protection.outlook.com
 ([40.107.243.83]:6127
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726127AbgD3IkI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Apr 2020 04:40:08 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=eFNThh4XP+o5Koz5sEKYVzcNIqEOVKfDMvyVFG3ymCVmepOP+OC3hO2wfeJHqboGgu5L7FNeo3ERWE/CU1sAwg+oAl7SwzaqTCRX8rvgSOeQx/vru2cHvvgoWk+Frd8T2+IbB7OfM5KooOAc8vrs/kDIzrO6tznSWo43DfEBqsteMtH4+sJ/YlgOy885un9bXWZYU8FziAoosWHOS78RSmPJmXwil+iwpQ/JI4BTy0br6zKnj0ZIycf367VCeqZUm0QPH0sY9M4jtwwX3FuA+w4GptrCuhh9/ZAYszwMxj2vDDNgtYqnMVtFo7RFAzb+mbouP4k4HqrEsTJmiVONBg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=8JSvXoDvfk/PKQtqIWV3iyCle/egNbUegtRIAqJZ6gw=;
 b=CSg4PrtwEYDkI9EE1k661IRRvtajah79AP9pOBrwBfmq0VV8fzl0WShGD9uh+z4x1gPeuhdEImPHIeZWMr6D5T7KjG8ReZQeRGre4F0eprFVL1ZnWsyH7aWvXiFt1VXTCM9sqx0oT/LiuXccqqakPjw0MYaF0ykiIzs9x16R0laAUN0Coldqx3TSN+NhxyBgQtb4hFjuTqSNyUUl44Evsc+xiRpAiAWTf2TEiSlS4Er7P46r6zwdj44FyTrhcO0x5CAKh5yoXtz3JxVH9Qn5WynbcdwqwOECTPmSW+yXi3jm9O9P7Fud1iYMMaZ0rE3E6/4dLJjszFgk9fo5ktnCSA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=8JSvXoDvfk/PKQtqIWV3iyCle/egNbUegtRIAqJZ6gw=;
 b=xjByJDfZpTXRjREmRLcd0Gl07gBj5F/bCDputa5jZZPiWliwYl6LFB5wSnHyCd163VdwR97S4J1YrP3/od+87mbptJ5eY99pt/JRMftdkGzo+3UImtASttAuCoeOCbAPENe6B+Mh4MlvdE03mwdTnqwMlqMQSmFthzlIpSqhCCM=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1386.namprd12.prod.outlook.com (2603:10b6:3:77::9) by
 DM5PR12MB1194.namprd12.prod.outlook.com (2603:10b6:3:6e::10) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2937.22; Thu, 30 Apr 2020 08:40:01 +0000
Received: from DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c]) by DM5PR12MB1386.namprd12.prod.outlook.com
 ([fe80::969:3d4e:6f37:c33c%12]) with mapi id 15.20.2937.028; Thu, 30 Apr 2020
 08:40:01 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, rientjes@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v7 00/18] Add AMD SEV guest live migration support
Date: Thu, 30 Apr 2020 08:39:50 +0000
Message-Id: <cover.1588234824.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: SN6PR16CA0037.namprd16.prod.outlook.com
 (2603:10b6:805:ca::14) To DM5PR12MB1386.namprd12.prod.outlook.com
 (2603:10b6:3:77::9)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN6PR16CA0037.namprd16.prod.outlook.com (2603:10b6:805:ca::14) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.19 via Frontend
 Transport; Thu, 30 Apr 2020 08:40:00 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 5a33a662-3fe4-4840-a8e7-08d7ece21266
X-MS-TrafficTypeDiagnostic: DM5PR12MB1194:|DM5PR12MB1194:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB1194F067C704E473CF68D02C8EAA0@DM5PR12MB1194.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2150;
X-Forefront-PRVS: 0389EDA07F
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1386.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(346002)(136003)(396003)(366004)(376002)(39860400002)(4326008)(6486002)(6916009)(66476007)(66946007)(52116002)(186003)(36756003)(7696005)(6666004)(316002)(5660300002)(26005)(86362001)(2906002)(8676002)(478600001)(66556008)(8936002)(956004)(2616005)(7416002)(966005)(16526019)(136400200001);DIR:OUT;SFP:1101;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Rd2znMkmZAzUAjAwO8CC/g9xIJQSuGuvSx6WyOzsQRM3ijF4XLZnsOHR/p4NX/BTDsJvXb225ZKlcQvHkc0geuIOe9Q6VYSohFOJ/SZzPI3Rdx00xSqFjkw7w8QuKSWCdDsevz3hLuS84lXwlU1FN1a4GoJSJ0DZsCmvI9RlIyw1Jix9mOKB4+tNvqcgfUW96GwjIBqahvJOu4ldfPrVbHwoTxCAmZ7xjCefW0kJXy/0bN9LPOJVlFx/hXi1f6D01kSnrIXT8RYEVg30GXjCiX/IgecpLZobWePb/pnyyt1+LrY2/QtC6TI8xhrZwbSZ30Jj591oh4c01BH43xYmLRnHerzSvut35fM300g9IfbO/kUjkwZxHp/O5oksLhPXhTPk+buY4BnNRpeDQxIktCA+tfptTFi8QGSuwDgKbHh9MiKSR7icW6i1+T00zzKmoXsboPgd/SjxENM/eBiIYvLJQAmuUZz4CRlTfgEZk/DWFZRMJu742ADJY/bLON2PoT88siJ+QALKD/frsL4De+tzKdKJadhwUoIO42jlZUgdnRZt4IsscuuXI8s7LJXuIXXc9TrSfUykzPS+xoxz8w==
X-MS-Exchange-AntiSpam-MessageData: 
 wrKrbeRYi/Vv1G+W+D3gB2FfCz9xYbrjB74lu+/XWC0FTkQD8sB+dBef4XxIB1xdXmgowlyCw3hTJV2TAxLLbhV9LImFq5I7m+c1v2+B3wztC1rzYTvsBZxLns89XMdiv54ZErAyXW28a2Y4xJZ4Mx5QzDtIAw5X0CPgJ0AYOwhlgr4VdYTwCx7OfgtARUi+l2tp1GVR9pWdqvHvJVNTBtyx7jT4vD4HCH7EM+lVWCmVOaQRnn5W+T96bbe9mzMz2ixK1I5ook11CSpD4gm0HouDgiAQP1km4crOmQ3+GcG/Wjt1BbYhkFXflBghKylYuqz66noew6gnuU+w8NGJDEswC2ebLQHBgrYVfhbEKPBTVFw4s++N7RQs+bUirT/VZZWTfs8JoxDKw7fPaqO47m2ZPrSNWwrUTcjDCX7eXnX1ov7P2YetEA0X3w+MqMZRlcnl5c0zjQmS3Ko4kgWjX18k5TA2MO20ALqtq93p11RKwhL8HJFPoi0TuRUt+nWQ/2ETRP63GBzRKczxoMNQYhwVIP6M1HZsctZdtsLBJJudHhTXj1oDufA8l2jV6+8safDuSNdxYetkFTWiL2/msrfh9MglZIp+z1KeZjxmaPiluF1fraOvISyl9GiIn8QU+3DRfj1BEThPjynG+u6cQXmQCSL2I6w09lLWh6wzv5/TVA60wAcmNSMb2w6A9yH4SF1XAcXVpWQmKuhgNXgCDUWAIhxdycnwS6H/rJDsQzAS0ooLVos1ctk4mlaMyn9SaKQ7zySmwVuoqHYvPQH8g5dqvtHiCxFGDBZG70QtyJI=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5a33a662-3fe4-4840-a8e7-08d7ece21266
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Apr 2020 08:40:01.3685
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 iXV29ma58TsRYDZapts0Rr6iWsycB2UdtGufwhxgJfZX8+yScL+FdQnfWoZOwthn2AmhgRZOad7C0RdvmyQ6Lg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1194
Sender: kvm-owner@vger.kernel.org
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

The patch adds new ioctls KVM_{SET,GET}_PAGE_ENC_BITMAP. The ioctl can be used
by the qemu to get the page encrypted bitmap. Qemu can consult this bitmap
during the migration to know whether the page is encrypted.

[1] https://developer.amd.com/wp-content/resources/55766.PDF

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


Ashish Kalra (7):
  x86/paravirt: Add hypervisor specific hypercall for SEV live
    migration.
  KVM: SVM: Add support for static allocation of unified Page Encryption
    Bitmap.
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  KVM: x86: Add guest support for detecting and enabling SEV Live
    Migration feature.
  KVM: x86: Mark _bss_decrypted section variables as decrypted in page
    encryption bitmap.
  KVM: x86: Add kexec support for SEV Live Migration.

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
  mm: x86: Invoke hypercall when page encryption status is changed
  KVM: x86: Introduce KVM_SET_PAGE_ENC_BITMAP ioctl

 .../virt/kvm/amd-memory-encryption.rst        | 120 +++
 Documentation/virt/kvm/api.rst                |  71 ++
 Documentation/virt/kvm/cpuid.rst              |   5 +
 Documentation/virt/kvm/hypercalls.rst         |  15 +
 Documentation/virt/kvm/msr.rst                |  10 +
 arch/x86/include/asm/kvm_host.h               |   7 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |  11 +
 arch/x86/include/asm/paravirt.h               |  10 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/include/asm/x86_init.h               |  10 +-
 arch/x86/include/uapi/asm/kvm_para.h          |   5 +
 arch/x86/kernel/kvm.c                         | 102 +++
 arch/x86/kernel/kvmclock.c                    |  12 +
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/svm/sev.c                        | 723 +++++++++++++++++-
 arch/x86/kvm/svm/svm.c                        |  21 +
 arch/x86/kvm/svm/svm.h                        |   9 +
 arch/x86/kvm/vmx/vmx.c                        |   1 +
 arch/x86/kvm/x86.c                            |  35 +
 arch/x86/mm/mem_encrypt.c                     |  69 +-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/efi.h                           |   1 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  52 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 26 files changed, 1310 insertions(+), 10 deletions(-)
```
#### [PATCH v4 00/19] Manually convert  thermal,
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Thu Apr 30 16:18:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11520887
Return-Path: <SRS0=DGI+=6O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C7A1913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 16:19:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F307208CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 16:19:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588263578;
	bh=ugCY3y9aPneko9xp0OW8Y5PqnnRdwIA6ZnhjiQw0pbg=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=jgqlWimw6yzFHHRTIixOUXQ4SlA+gqbQGUxZeOnnq/2eXmH7Gvf9THcYuQF5CivcH
	 38xHBfmPo+aRmD9ggoQ31v6xh161gNHQ8gBtcibP95BmIrX2FQxLFr6C6uqrRhcPyB
	 6RGSVUxe5ZBn7yeor8a7A/4e7Mp5Ap71cSPEI4FI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728178AbgD3QSk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Apr 2020 12:18:40 -0400
Received: from mail.kernel.org ([198.145.29.99]:58600 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726431AbgD3QSi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Apr 2020 12:18:38 -0400
Received: from mail.kernel.org (ip5f5ad5c5.dynamic.kabel-deutschland.de
 [95.90.213.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A7673208D5;
        Thu, 30 Apr 2020 16:18:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1588263517;
        bh=ugCY3y9aPneko9xp0OW8Y5PqnnRdwIA6ZnhjiQw0pbg=;
        h=From:To:Cc:Subject:Date:From;
        b=jkbiKuotKQWoJifXoYaYKWd4u1OUCkFJTCeaJ2hFfc8Mmzm6hL99xXi+5i8oLaR6e
         GJ1b6u5OLXCuKZdQPYYbqcEoGl4qcjUVxJHvEaPOc1nGKIjtw42GlkxhXUFJCRfzBO
         IWB28xT442895dIcuie8By96F883CyyppOigyJ4o=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1jUBtT-00Axgb-Pl; Thu, 30 Apr 2020 18:18:35 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        linux-pm@vger.kernel.org, keyrings@vger.kernel.org,
        linux-crypto@vger.kernel.org, dmaengine@vger.kernel.org,
        linux-pci@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linuxppc-dev@lists.ozlabs.org, linux-sh@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH v4 00/19] Manually convert  thermal,
 crypto and misc devices to ReST
Date: Thu, 30 Apr 2020 18:18:14 +0200
Message-Id: <cover.1588263270.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Manually convert some files from thermal, crypto and misc-devices
to ReST format.

This series is against linux-next 20200430 tag (as I rebased it, in order
to check if some patch were already merged via some other tree),
but it should very likely merge fine against docs-next.

The full series (including those ones) are at:

	https://git.linuxtv.org/mchehab/experimental.git/log/?h=misc-docs

The documents touched on this patch, converted to HTML via the 
building system are at (together with patches from other series):

	https://www.infradead.org/~mchehab/kernel_docs/


v4:

- added some acks.

v3:

- removed the cpu-freq patches from this series, as Rafael should
  be applying it on his tree.

v2: 

- a small change at patch 2 to avoid uneeded whitespace changes;
- added 13 new patches at the end


Mauro Carvalho Chehab (19):
  docs: thermal: convert cpu-idle-cooling.rst to ReST
  docs: crypto: convert asymmetric-keys.txt to ReST
  docs: crypto: convert api-intro.txt to ReST format
  docs: crypto: convert async-tx-api.txt to ReST format
  docs: crypto: descore-readme.txt: convert to ReST format
  docs: misc-devices/spear-pcie-gadget.txt: convert to ReST
  docs: misc-devices/pci-endpoint-test.txt: convert to ReST
  docs: misc-devices/pci-endpoint-test.txt: convert to ReST
  docs: misc-devices/c2port.txt: convert to ReST format
  docs: misc-devices/bh1770glc.txt: convert to ReST
  docs: misc-devices/apds990x.txt: convert to ReST format
  docs: pci: endpoint/function/binding/pci-test.txt convert to ReST
  docs: arm64: convert perf.txt to ReST format
  docs: powerpc: convert vcpudispatch_stats.txt to ReST
  docs: sh: convert new-machine.txt to ReST
  docs: sh: convert register-banks.txt to ReST
  docs: trace: ring-buffer-design.txt: convert to ReST format
  docs: kvm: get read of devices/README
  docs: misc-devices: add uacce to the index.rst

 .../endpoint/function/binding/pci-test.rst    |  26 +
 .../endpoint/function/binding/pci-test.txt    |  19 -
 Documentation/PCI/endpoint/index.rst          |   2 +
 Documentation/arm64/index.rst                 |   1 +
 Documentation/arm64/{perf.txt => perf.rst}    |   7 +-
 .../crypto/{api-intro.txt => api-intro.rst}   | 186 ++--
 ...symmetric-keys.txt => asymmetric-keys.rst} |  91 +-
 .../{async-tx-api.txt => async-tx-api.rst}    | 253 +++---
 ...{descore-readme.txt => descore-readme.rst} | 152 +++-
 Documentation/crypto/index.rst                |   5 +
 Documentation/driver-api/dmaengine/client.rst |   2 +-
 .../driver-api/dmaengine/provider.rst         |   2 +-
 .../driver-api/thermal/cpu-idle-cooling.rst   |  18 +-
 Documentation/driver-api/thermal/index.rst    |   1 +
 .../{ad525x_dpot.txt => ad525x_dpot.rst}      |  24 +-
 .../{apds990x.txt => apds990x.rst}            |  31 +-
 .../{bh1770glc.txt => bh1770glc.rst}          |  45 +-
 .../misc-devices/{c2port.txt => c2port.rst}   |  58 +-
 Documentation/misc-devices/index.rst          |   7 +
 .../misc-devices/pci-endpoint-test.rst        |  56 ++
 .../misc-devices/pci-endpoint-test.txt        |  41 -
 .../misc-devices/spear-pcie-gadget.rst        | 170 ++++
 .../misc-devices/spear-pcie-gadget.txt        | 130 ---
 Documentation/powerpc/index.rst               |   1 +
 ...patch_stats.txt => vcpudispatch_stats.rst} |  17 +-
 Documentation/security/keys/core.rst          |   2 +-
 Documentation/sh/index.rst                    |   6 +
 .../sh/{new-machine.txt => new-machine.rst}   | 195 +++--
 ...{register-banks.txt => register-banks.rst} |  13 +-
 Documentation/trace/index.rst                 |   1 +
 ...ffer-design.txt => ring-buffer-design.rst} | 802 ++++++++++--------
 Documentation/virt/kvm/devices/README         |   1 -
 Documentation/virt/kvm/devices/index.rst      |   3 +
 MAINTAINERS                                   |   4 +-
 arch/sh/Kconfig.cpu                           |   2 +-
 crypto/asymmetric_keys/asymmetric_type.c      |   2 +-
 crypto/asymmetric_keys/public_key.c           |   2 +-
 crypto/asymmetric_keys/signature.c            |   2 +-
 drivers/misc/Kconfig                          |   2 +-
 drivers/misc/ad525x_dpot.c                    |   2 +-
 include/crypto/public_key.h                   |   2 +-
 include/keys/asymmetric-parser.h              |   2 +-
 include/keys/asymmetric-subtype.h             |   2 +-
 include/keys/asymmetric-type.h                |   2 +-
 44 files changed, 1358 insertions(+), 1034 deletions(-)
 create mode 100644 Documentation/PCI/endpoint/function/binding/pci-test.rst
 delete mode 100644 Documentation/PCI/endpoint/function/binding/pci-test.txt
 rename Documentation/arm64/{perf.txt => perf.rst} (95%)
 rename Documentation/crypto/{api-intro.txt => api-intro.rst} (70%)
 rename Documentation/crypto/{asymmetric-keys.txt => asymmetric-keys.rst} (91%)
 rename Documentation/crypto/{async-tx-api.txt => async-tx-api.rst} (55%)
 rename Documentation/crypto/{descore-readme.txt => descore-readme.rst} (81%)
 rename Documentation/misc-devices/{ad525x_dpot.txt => ad525x_dpot.rst} (85%)
 rename Documentation/misc-devices/{apds990x.txt => apds990x.rst} (86%)
 rename Documentation/misc-devices/{bh1770glc.txt => bh1770glc.rst} (83%)
 rename Documentation/misc-devices/{c2port.txt => c2port.rst} (59%)
 create mode 100644 Documentation/misc-devices/pci-endpoint-test.rst
 delete mode 100644 Documentation/misc-devices/pci-endpoint-test.txt
 create mode 100644 Documentation/misc-devices/spear-pcie-gadget.rst
 delete mode 100644 Documentation/misc-devices/spear-pcie-gadget.txt
 rename Documentation/powerpc/{vcpudispatch_stats.txt => vcpudispatch_stats.rst} (94%)
 rename Documentation/sh/{new-machine.txt => new-machine.rst} (73%)
 rename Documentation/sh/{register-banks.txt => register-banks.rst} (88%)
 rename Documentation/trace/{ring-buffer-design.txt => ring-buffer-design.rst} (55%)
 delete mode 100644 Documentation/virt/kvm/devices/README
```
#### [PATCH v2 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
From patchwork Thu Apr 30 21:29:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11521647
Return-Path: <SRS0=DGI+=6O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C70141392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 21:27:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B91922166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 21:27:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727078AbgD3V1f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Apr 2020 17:27:35 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:26366 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726616AbgD3V1f (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Apr 2020 17:27:35 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03UL24PW135712;
        Thu, 30 Apr 2020 17:27:34 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30r5cma6u6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Apr 2020 17:27:33 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03UL2FeX136877;
        Thu, 30 Apr 2020 17:27:33 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30r5cma6tv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Apr 2020 17:27:33 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03ULN8bT012382;
        Thu, 30 Apr 2020 21:27:33 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma02dal.us.ibm.com with ESMTP id 30mcu7cr8a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Apr 2020 21:27:32 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03ULRUQA12452328
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Apr 2020 21:27:30 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 52FE27805F;
        Thu, 30 Apr 2020 21:27:31 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 91E7578063;
        Thu, 30 Apr 2020 21:27:30 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.180.191])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 30 Apr 2020 21:27:30 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Thu, 30 Apr 2020 17:29:58 -0400
Message-Id: <20200430212959.13070-1-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-30_12:2020-04-30,2020-04-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 clxscore=1015
 impostorscore=0 lowpriorityscore=0 mlxscore=0 suspectscore=0 bulkscore=0
 priorityscore=1501 mlxlogscore=999 malwarescore=0 adultscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004300152
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check is not needed in practice as all Linux channel programs
are intended to use prefetch.

Version 2 improves logging by issuing a warning if a non-prefetch
ORB is encountered. A kernel warning is printed when an ORB without
the p-bit set is initialized.  The warning is limited to once per
five seconds because, if encountered, non-prefetch ORBs tend to
appear in bursts of hundreds per second.

The commit message is expanded to highlight the potential for
future risk if non-prefetch dependent channel programs become
prevalent.  Furthermore, a note of prefetch only support is
added to the limitations section of the vfio-ccw.rst.

Jared Rossi (1):
  vfio-ccw: Enable transparent CCW IPL from DASD

 Documentation/s390/vfio-ccw.rst |  4 ++++
 drivers/s390/cio/vfio_ccw_cp.c  | 16 +++++++---------
 2 files changed, 11 insertions(+), 9 deletions(-)
```
