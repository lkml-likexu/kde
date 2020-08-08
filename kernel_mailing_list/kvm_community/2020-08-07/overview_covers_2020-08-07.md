

#### [PATCH v4 00/12] SVM cleanup and INVPCID support for the AMD guests
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Fri Aug  7 00:46:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11704575
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B85D138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 00:46:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D2D82075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 00:46:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="bd4tz29a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726250AbgHGAq2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 20:46:28 -0400
Received: from mail-dm6nam12on2073.outbound.protection.outlook.com
 ([40.107.243.73]:24416
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726011AbgHGAq1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 20:46:27 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=nsxoatNi18iZ7aLtV5xNZb0LNidlPTcATdTvqyLXMwb+UhxJYqgATkzbdxJWA2TJXrL5x4i8ZskKJhK67SMIRhWWC6Ng0D+rc8rVIhP9t1fUotKM4IvAMGMSHg2LGmSxWJr10ECGYicKPS9a0yp80RtCKy3pKf92SvrR6VgkLHGJ6zz7ztIJdtM7mEElyy1Rzhyr60rtCFxPSlXt5IK0QOQbuomKtHYJM5rks1QnOu6JVUvP46ty0J0W65H2NrrvcHJC+e749s33nZmWIaSH1M1QSiczwW/G5pqzE4SP1HknvrPybKNyT2y1h1QW7hzBNSz3Q8p4R7B3Jv42cBSXwQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p7Fig27GH/SZKzuAM1l7HbKtV50j0Yv5t0+/zy87IIY=;
 b=LQ2n/g4fB0P2GIiz1SPSdECul1BUzKVF1EkVFkeNxMZDvdP5i25QrsARgB1YBoQGFdMGheX0LtAbPVuRYMZ7EXRa3tYnOlOlZaiXU/vq6+IaJFQpkNhrIBvVD7S+Z0uTmoahgeKF3Np9/5U534KmZ9ebCZa4IH5kbRnyRr+qQq32JVtH2ayd2xxIW6pnl8upyQlCf5xduY4aGPWkVajwihf+V/UYOtgiPNlT9nSEmGkA7N7NyFb7xemikXwq3kQh1Quu44ltlJMF5cGGgyzT5pDrY7yVnBt9Rx2IRp+T7Q9oqE8cDOSk0taDPezJZFrvLN08VVyqypcdg4VUVUWikg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p7Fig27GH/SZKzuAM1l7HbKtV50j0Yv5t0+/zy87IIY=;
 b=bd4tz29aWuGlXCxm34IAAnLdUmWiurLOm1vDCoiFe8BW0bJY92//mxzOdKA3sXMSe78E0hVVJVuruvE6bQ2vs1gQPtQWD0C5FQtbdm8DkEsQ0sPXGtLoxzfCzeCqYstzoCLgsxmEEn75NUte/0Te5ZMEsuKX16NPKm0GrOyeLrU=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4479.namprd12.prod.outlook.com (2603:10b6:806:95::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3261.19; Fri, 7 Aug
 2020 00:46:23 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::691c:c75:7cc2:7f2c]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::691c:c75:7cc2:7f2c%6]) with mapi id 15.20.3239.023; Fri, 7 Aug 2020
 00:46:23 +0000
Subject: [PATCH v4 00/12] SVM cleanup and INVPCID support for the AMD guests
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, vkuznets@redhat.com, wanpengli@tencent.com,
        sean.j.christopherson@intel.com, jmattson@google.com
Cc: kvm@vger.kernel.org, joro@8bytes.org, x86@kernel.org,
        linux-kernel@vger.kernel.org, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, tglx@linutronix.de
Date: Thu, 06 Aug 2020 19:46:20 -0500
Message-ID: <159676101387.12805.18038347880482984693.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: SN4PR0501CA0085.namprd05.prod.outlook.com
 (2603:10b6:803:22::23) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN4PR0501CA0085.namprd05.prod.outlook.com (2603:10b6:803:22::23) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3283.6 via Frontend
 Transport; Fri, 7 Aug 2020 00:46:21 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 73f4e03f-9959-464f-aa1e-08d83a6b4eb7
X-MS-TrafficTypeDiagnostic: SA0PR12MB4479:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4479D3D29ADBCFB11711230495490@SA0PR12MB4479.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3383;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 3hBuPWcgDKx4nJb3hE01y6u03BMXfVpxGACzpaW5ImjTbHqabdTTTyoZdbhdr5UZ0L7BA9cO/UwuktLt1j/PYcaoYU2SeLZ8NdqTb80/NFCE8VM/QATw/rhBOMyeqSibPYXqR0Y/UwtXHq9sr8/+UQ6bVq6SH1LgryBZgftK2Nz0ZUnPOmEnqtE/A+D0D4g0mnqZeM/kB7uIMsViKI/5caQXY/Rk9GANaIVRyVQLwoxt6ZYx1pg8fkkF481C9cmjv6+A5cJPkh9yfX1wuCarUcq3Hw5Cf9P3dhEqLm00vuTeH0z+GEirkTsG8jDUbTRi+wLVJbB+ujoQPWhTCa9sHmnY8j9pGtr7JzwS9wEstUIMwWQqOeaMctN5o3ajJR4W1/hLP18yCpNruZIuBJqKnA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(7916004)(39860400002)(396003)(376002)(346002)(136003)(366004)(5660300002)(6486002)(52116002)(2906002)(16576012)(4326008)(83380400001)(7416002)(956004)(44832011)(33716001)(26005)(9686003)(8676002)(966005)(66476007)(66556008)(103116003)(66946007)(8936002)(86362001)(16526019)(186003)(478600001)(316002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 wMIJw4ofRllnmiIXP+Jo3CqITajFeiX6wi4+MtTr2sErmOPs2JVYj1x5KNIDU0afRvqFxTLd7nwLVuMK/oCJN/a4yTafR98mOXf+xEgsLlGK3PfcYcnhO4xXtTe/rBFY9MH++ZO3pzLoLp7FZ1ylhbXqIIj6MrkIt22L+Sk18229cKne+v1Q/d9S+YTzfjaTp7dFbc4otavVKiOjHTWoyvbXu3t2vSukwYToQBPDcgVlsXszjfgLWL49f9/2+Blp0llH2YTWqJ5Tf6iN5LGWuZY4pUII0oTUeQgIZ3O2GdKpXVjR7PIVrt0XbfG3y4CpzjIlrqImNuqfUngOyoYRzirGKlOdqn+1brDwQqjx4kzPqAtnMWGb+lEiLyOZLMuV0QeqpJMt1xnWuHWRzJbr20wpAVawvCNugu8dBKsuAKraYPXfcDyVL87oweA7uT4V/mQUqFLYjd8tNzw3R/m42C0L8i4k8RhlEmG9eVfAJgJToaw4qNd5zoCf+/y6hBMB4Md8v5gUmDExC+5X3sJrMrImdokw6qPz9hZzxJ9Xx7/v9eBQMkA5EJt1IZY4o74J7sE+FhtZwVj3Pkldwr3KpoaSclNbBLU6JibLePANrOqhnaH5NkwcHr1VG49Fp9OB5lpfb0HgjKjxpuJ2hUMbAw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 73f4e03f-9959-464f-aa1e-08d83a6b4eb7
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 Aug 2020 00:46:23.0875
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 3/ZFI7xZ+YrqEir8Zik72grNSVoDypoV86Hv7/NDra/yytJiv3a+BGX1YIvJPsXY
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4479
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following series adds the support for PCID/INVPCID on AMD guests.
While doing it re-structured the vmcb_control_area data structure to
combine all the intercept vectors into one 32 bit array. Makes it easy
for future additions. Re-arranged few pcid related code to make it common
between SVM and VMX.

INVPCID interceptions are added only when the guest is running with shadow
page table enabled. In this case the hypervisor needs to handle the tlbflush
based on the type of invpcid instruction.

For the guests with nested page table (NPT) support, the INVPCID feature
works as running it natively. KVM does not need to do any special handling.

AMD documentation for INVPCID feature is available at "AMD64 Architecture
Programmer’s Manual Volume 2: System Programming, Pub. 24593 Rev. 3.34(or later)"

The documentation can be obtained at the links below:
Link: https://www.amd.com/system/files/TechDocs/24593.pdf
Link: https://bugzilla.kernel.org/show_bug.cgi?id=206537
---
v4:
 1. Changed the functions __set_intercept/__clr_intercept/__is_intercept to
    to vmcb_set_intercept/vmcb_clr_intercept/vmcb_is_intercept by passing
    vmcb_control_area structure(Suggested by Paolo).
 2. Rearranged the commit 7a35e515a7055 ("KVM: VMX: Properly handle kvm_read/write_guest_virt*())
    to make it common across both SVM/VMX(Suggested by Jim Mattson).
 3. Took care of few other comments from Jim Mattson. Dropped "Reviewed-by"
    on few patches which I have changed since v3.

v3:
 https://lore.kernel.org/lkml/159597929496.12744.14654593948763926416.stgit@bmoger-ubuntu/
 1. Addressing the comments from Jim Mattson. Follow the v2 link below
    for the context.
 2. Introduced the generic __set_intercept, __clr_intercept and is_intercept
    using native __set_bit, clear_bit and test_bit.
 3. Combined all the intercepts vectors into single 32 bit array.
 4. Removed set_intercept_cr, clr_intercept_cr, set_exception_intercepts,
    clr_exception_intercept etc. Used the generic set_intercept and
    clr_intercept where applicable.
 5. Tested both L1 guest and l2 nested guests. 

v2:
  https://lore.kernel.org/lkml/159234483706.6230.13753828995249423191.stgit@bmoger-ubuntu/
  - Taken care of few comments from Jim Mattson.
  - KVM interceptions added only when tdp is off. No interceptions
    when tdp is on.
  - Reverted the fault priority to original order in VMX. 
  
v1:
  https://lore.kernel.org/lkml/159191202523.31436.11959784252237488867.stgit@bmoger-ubuntu/

Babu Moger (12):
      KVM: SVM: Introduce vmcb_set_intercept, vmcb_clr_intercept and vmcb_is_intercept
      KVM: SVM: Change intercept_cr to generic intercepts
      KVM: SVM: Change intercept_dr to generic intercepts
      KVM: SVM: Modify intercept_exceptions to generic intercepts
      KVM: SVM: Modify 64 bit intercept field to two 32 bit vectors
      KVM: SVM: Add new intercept vector in vmcb_control_area
      KVM: nSVM: Cleanup nested_state data structure
      KVM: SVM: Remove set_cr_intercept, clr_cr_intercept and is_cr_intercept
      KVM: SVM: Remove set_exception_intercept and clr_exception_intercept
      KVM: X86: Rename and move the function vmx_handle_memory_failure to x86.c
      KVM: X86: Move handling of INVPCID types to x86
      KVM:SVM: Enable INVPCID feature on AMD


 arch/x86/include/asm/svm.h      |  117 +++++++++++++++++++++++++----------
 arch/x86/include/uapi/asm/svm.h |    2 +
 arch/x86/kvm/svm/nested.c       |   66 +++++++++-----------
 arch/x86/kvm/svm/svm.c          |  131 ++++++++++++++++++++++++++-------------
 arch/x86/kvm/svm/svm.h          |   87 +++++++++-----------------
 arch/x86/kvm/trace.h            |   21 ++++--
 arch/x86/kvm/vmx/nested.c       |   12 ++--
 arch/x86/kvm/vmx/vmx.c          |   95 ----------------------------
 arch/x86/kvm/vmx/vmx.h          |    2 -
 arch/x86/kvm/x86.c              |  106 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              |    3 +
 11 files changed, 364 insertions(+), 278 deletions(-)

--
```
#### [PATCH 0/7] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID more
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Fri Aug  7 08:39:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11705141
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6BD2614DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:39:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5581922CF6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:39:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="E6LRou5/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727910AbgHGIj4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 04:39:56 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:41139 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726382AbgHGIj4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Aug 2020 04:39:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596789595;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=OlUdNVLkFbE86ANY/tbMVg0aRxa7c4aH/HL6yZUmDFI=;
        b=E6LRou5/49j++c8iZu6QbxelATJTmRSj4RBYngCMTXnIcmqUxYKB3ZKbY8bcnQDDEOJmTC
        E6l+2aledGjnGebMAJAU/HbM9yz3QbiPobnIx0N+vhcP1qQR1z9Q24OCk/HofVX8g/HFMA
        mFDsD/gQhQAwjjMFgjiRaA40xu+C8zs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-191-eRSuRYPAOOacnDWMSEeuCw-1; Fri, 07 Aug 2020 04:39:53 -0400
X-MC-Unique: eRSuRYPAOOacnDWMSEeuCw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E24928005B0;
        Fri,  7 Aug 2020 08:39:51 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.139])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 950025C1D2;
        Fri,  7 Aug 2020 08:39:48 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 0/7] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID more
 useful
Date: Fri,  7 Aug 2020 10:39:39 +0200
Message-Id: <20200807083946.377654-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_GET_SUPPORTED_HV_CPUID was initially implemented as a vCPU ioctl but
this is not very useful when VMM is just trying to query which Hyper-V
features are supported by the host prior to creating VM/vCPUs. The data
in KVM_GET_SUPPORTED_HV_CPUID is mostly static with a few exceptions but
it seems we can change this. Add support for KVM_GET_SUPPORTED_HV_CPUID as
a system ioctl as well.

QEMU specific description:
In some cases QEMU needs to collect the information about which Hyper-V
features are supported by KVM and pass it up the stack. For non-hyper-v
features this is done with system-wide KVM_GET_SUPPORTED_CPUID/
KVM_GET_MSRS ioctls but Hyper-V specific features don't get in the output
(as Hyper-V CPUIDs intersect with KVM's). In QEMU, CPU feature expansion
happens before any KVM vcpus are created so KVM_GET_SUPPORTED_HV_CPUID
can't be used in its current shape.

Vitaly Kuznetsov (7):
  KVM: x86: hyper-v: Mention SynDBG CPUID leaves in api.rst
  KVM: x86: hyper-v: disallow configuring SynIC timers with no SynIC
  KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID output independent
    of eVMCS enablement
  KVM: x86: hyper-v: always advertise HV_STIMER_DIRECT_MODE_AVAILABLE
  KVM: x86: hyper-v: drop now unneeded vcpu parameter from
    kvm_vcpu_ioctl_get_hv_cpuid()
  KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl
  KVM: selftests: test KVM_GET_SUPPORTED_HV_CPUID as a system ioctl

 Documentation/virt/kvm/api.rst                | 12 +--
 arch/x86/include/asm/kvm_host.h               |  2 +-
 arch/x86/kvm/hyperv.c                         | 30 ++++----
 arch/x86/kvm/hyperv.h                         |  3 +-
 arch/x86/kvm/vmx/evmcs.c                      |  8 +-
 arch/x86/kvm/vmx/evmcs.h                      |  2 +-
 arch/x86/kvm/x86.c                            | 44 ++++++-----
 include/uapi/linux/kvm.h                      |  4 +-
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 26 +++++++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 77 +++++++++----------
 11 files changed, 120 insertions(+), 90 deletions(-)
```
#### [RFC 0/7] KVM: PKS Virtualization support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Aug  7 08:48:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11705165
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 06C92913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:46:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EDC5022CAE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 08:46:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727120AbgHGIqp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 04:46:45 -0400
Received: from mga06.intel.com ([134.134.136.31]:65145 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726382AbgHGIqo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 04:46:44 -0400
IronPort-SDR: 
 CbtsCIDR6q+mkLh1K2pvuEuwRTwq93Tbc25iLu/0YtEctwWGifAZkn1MrAunKGF+UCmJ4hxFzb
 Z/1n2xfN7DTQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9705"; a="214565716"
X-IronPort-AV: E=Sophos;i="5.75,445,1589266800";
   d="scan'208";a="214565716"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Aug 2020 01:46:44 -0700
IronPort-SDR: 
 M0ulD5ZOVtxaO1LRSJ0sZZJarJy5PFWv+Z8cUPzeo/eSTZwi67YNWYRrSpWzW3czYvyq3tC7AB
 C9q4dWuK/M/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,445,1589266800";
   d="scan'208";a="307317136"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga002.jf.intel.com with ESMTP; 07 Aug 2020 01:46:41 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC 0/7] KVM: PKS Virtualization support
Date: Fri,  7 Aug 2020 16:48:34 +0800
Message-Id: <20200807084841.7112-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC series introduce the KVM support for PKS which have dependency
on PKS kernel patches for some definitions. The latest kernel patch set
can be found at
https://lore.kernel.org/lkml/20200717072056.73134-1-ira.weiny@intel.com/
---

Protection Keys for Supervisor Pages(PKS) is a feature that extends the
Protection Keys architecture to support thread-specific permission
restrictions on supervisor pages.

PKS works similar to an existing feature named PKU(protecting user pages).
They both perform an additional check after all legacy access
permissions checks are done. If violated, #PF occurs and PFEC.PK bit will
be set. PKS introduces MSR IA32_PKRS to manage supervisor protection key
rights. The MSR contains 16 pairs of ADi and WDi bits. Each pair
advertises on a group of pages with the same key which is set in the
leaf paging-structure entries(bits[62:59]). Currently, IA32_PKRS is not
supported by XSAVES architecture.

This patchset aims to add the virtualization of PKS in KVM. It
implemented PKS CPUID enumeration, vmentry/vmexit configuration, MSR
exposure, nested supported etc. Currently, PKS is not yet supported for
shadow paging. 

Detailed information about PKS can be found in the latest Intel 64 and
IA-32 Architectures Software Developer's Manual.

Chenyi Qiang (7):
  KVM: VMX: Introduce PKS VMCS fields
  KVM: VMX: Expose IA32_PKRS MSR
  KVM: MMU: Rename the pkru to pkr
  KVM: MMU: Refactor pkr_mask to cache condition
  KVM: MMU: Add support for PKS emulation
  KVM: X86: Expose PKS to guest and userspace
  KVM: VMX: Enable PKS for nested VM

 arch/x86/include/asm/kvm_host.h | 13 ++---
 arch/x86/include/asm/pkeys.h    |  1 +
 arch/x86/include/asm/vmx.h      |  6 +++
 arch/x86/kvm/cpuid.c            |  3 +-
 arch/x86/kvm/mmu.h              | 36 +++++++------
 arch/x86/kvm/mmu/mmu.c          | 78 +++++++++++++++-------------
 arch/x86/kvm/vmx/capabilities.h |  6 +++
 arch/x86/kvm/vmx/nested.c       | 33 ++++++++++++
 arch/x86/kvm/vmx/vmcs.h         |  1 +
 arch/x86/kvm/vmx/vmcs12.c       |  2 +
 arch/x86/kvm/vmx/vmcs12.h       |  6 ++-
 arch/x86/kvm/vmx/vmx.c          | 91 +++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h          |  1 +
 arch/x86/kvm/x86.c              |  7 ++-
 arch/x86/kvm/x86.h              |  6 +++
 arch/x86/mm/pkeys.c             |  6 +++
 include/linux/pkeys.h           |  4 ++
 17 files changed, 234 insertions(+), 66 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/3] PV tests part 1
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Aug  7 11:15:52 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11705523
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BD38138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 11:16:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 353312075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 11:16:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="eWJeJF2O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726466AbgHGLQH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 07:16:07 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:34878 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726058AbgHGLQF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Aug 2020 07:16:05 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 077B1k0E074946;
        Fri, 7 Aug 2020 07:16:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=XQhED+tjxcBk2z9E75rFyuvJ1LMrPUPqrx1hrdAqRtc=;
 b=eWJeJF2OOILOhqXPjoBfjKTJQXuwhbLau2+orlw9n7SFiGa8uNSLGO321ZULxEPc4aSC
 qwcZP6Kzki/3AsOSu68hHGvUmDXFHsBOeNk1430TAI2rSgnJ8I/Dpoi2zTDd8FdUsr+7
 2STYfAYXwoM3fmGcRhAhPhgtIvFJF/TPoVjAHiwnV/AF5E4Go8KplWrRvKZdsZkrIeGA
 JAbK+yOZkeE6pBvoep0Xl3uhEhejopF3iKaHpaqw+ynibiqRyvXlvxvY7ob0sih9Pji2
 aceXRld4UpyjTAdCxZ4CeIeHFL+qhiH+7Vd8PUuKIgBu0BCuKv4rOG1r8ZqXxERun/jr SQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32rg3p9wy3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Aug 2020 07:16:03 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 077B1xj4075530;
        Fri, 7 Aug 2020 07:16:03 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32rg3p9wxc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Aug 2020 07:16:03 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 077Asjp3002750;
        Fri, 7 Aug 2020 11:16:01 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 32n0186k0u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 07 Aug 2020 11:16:01 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 077BFwmQ13566346
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 7 Aug 2020 11:15:58 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 59A91AE057;
        Fri,  7 Aug 2020 11:15:58 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 96EADAE059;
        Fri,  7 Aug 2020 11:15:57 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  7 Aug 2020 11:15:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/3] PV tests part 1
Date: Fri,  7 Aug 2020 07:15:52 -0400
Message-Id: <20200807111555.11169-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-07_06:2020-08-06,2020-08-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 suspectscore=0
 bulkscore=0 priorityscore=1501 clxscore=1015 lowpriorityscore=0
 mlxlogscore=960 malwarescore=0 adultscore=0 mlxscore=0 spamscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008070077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's start bringing in some more PV related code.

Somehow I missed that we can also have a key in a exception new
PSW. The interesting bit is that if such a PSW is loaded on an
exception it will result in a specification exception and not a
special operation exception.

The third patch adds a basic guest UV call API test. It has mostly
been used for firmware testing but I also think it's good to have a
building block like this for more PV tests.


GIT: https://gitlab.com/frankja/kvm-unit-tests/-/tree/queue


v2:
	* Renamed pgm_int_func to pgm_cleanup_func() and moved the call to handle_pgm_int()
	* Added page allocation to UV test
	* Cleanups

Janosch Frank (3):
  s390x: Add custom pgm cleanup function
  s390x: skrf: Add exception new skey test and add test to unittests.cfg
  s390x: Ultravisor guest API test

 lib/s390x/asm/interrupt.h |   1 +
 lib/s390x/asm/uv.h        |  74 +++++++++++++++++
 lib/s390x/interrupt.c     |  12 ++-
 s390x/Makefile            |   1 +
 s390x/skrf.c              |  79 +++++++++++++++++++
 s390x/unittests.cfg       |   7 ++
 s390x/uv-guest.c          | 162 ++++++++++++++++++++++++++++++++++++++
 7 files changed, 335 insertions(+), 1 deletion(-)
 create mode 100644 lib/s390x/asm/uv.h
 create mode 100644 s390x/uv-guest.c
```
#### [PATCH v2 0/3] KVM: x86: KVM_MEM_PCI_HOLE memory
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Fri Aug  7 14:12:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11705773
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 563F7138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 14:12:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F43822CF6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 14:12:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="brelYi7y"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726393AbgHGOMt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 10:12:49 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:48947 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726066AbgHGOMr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 Aug 2020 10:12:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596809566;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=tdAn3ys9U2kvewBUw2A+IAMoPy0rqtTds5Mt68OPGgQ=;
        b=brelYi7yuOfFBuGVs1Z9ELciAln/xl4AtJpoyPtM4399fXRILAnKf8Cl504g6cflw/urPU
        X2lxTrJiHyrO8Ix2OubRTDWtLP4Ckz4I+x3v7Rqmz/l/6A1rcj4iXHCsi0yyDvC7NfWlnJ
        SX6Mormd1Kqezr4CAxwh2UBGxJKyOlg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-267-mCUwJFpoNsOzgwbl7MG98w-1; Fri, 07 Aug 2020 10:12:44 -0400
X-MC-Unique: mCUwJFpoNsOzgwbl7MG98w-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 22CC119057A3;
        Fri,  7 Aug 2020 14:12:43 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.139])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CD7BB5C1D3;
        Fri,  7 Aug 2020 14:12:33 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Xu <peterx@redhat.com>, Michael Tsirkin <mst@redhat.com>,
        Julia Suvorova <jsuvorov@redhat.com>,
        Andy Lutomirski <luto@kernel.org>,
        Andrew Jones <drjones@redhat.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] KVM: x86: KVM_MEM_PCI_HOLE memory
Date: Fri,  7 Aug 2020 16:12:29 +0200
Message-Id: <20200807141232.402895-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1:
- Better KVM_SET_USER_MEMORY_REGION flags description, minor tweaks to
  the code [Drew Jones]
- BUG_ON() condition in __gfn_to_hva_memslot() adjusted.

This is a continuation of "[PATCH RFC 0/5] KVM: x86: KVM_MEM_ALLONES
memory" work: 
https://lore.kernel.org/kvm/20200514180540.52407-1-vkuznets@redhat.com/
and pairs with Julia's "x86/PCI: Use MMCONFIG by default for KVM guests":
https://lore.kernel.org/linux-pci/20200722001513.298315-1-jusual@redhat.com/

PCIe config space can (depending on the configuration) be quite big but
usually is sparsely populated. Guest may scan it by accessing individual
device's page which, when device is missing, is supposed to have 'pci
hole' semantics: reads return '0xff' and writes get discarded.

When testing Linux kernel boot with QEMU q35 VM and direct kernel boot
I observed 8193 accesses to PCI hole memory. When such exit is handled
in KVM without exiting to userspace, it takes roughly 0.000001 sec.
Handling the same exit in userspace is six times slower (0.000006 sec) so
the overal; difference is 0.04 sec. This may be significant for 'microvm'
ideas.

Note, the same speed can already be achieved by using KVM_MEM_READONLY
but doing this would require allocating real memory for all missing
devices and e.g. 8192 pages gives us 32mb. This will have to be allocated
for each guest separately and for 'microvm' use-cases this is likely
a no-go.

Introduce special KVM_MEM_PCI_HOLE memory: userspace doesn't need to
back it with real memory, all reads from it are handled inside KVM and
return '0xff'. Writes still go to userspace but these should be extremely
rare.

The original 'KVM_MEM_ALLONES' idea had additional optimizations: KVM
was mapping all 'PCI hole' pages to a single read-only page stuffed with
0xff. This is omitted in this submission as the benefits are unclear:
KVM will have to allocate SPTEs (either on demand or aggressively) and
this also consumes time/memory. We can always take a look at possible
optimizations later.

Vitaly Kuznetsov (3):
  KVM: x86: move kvm_vcpu_gfn_to_memslot() out of try_async_pf()
  KVM: x86: introduce KVM_MEM_PCI_HOLE memory
  KVM: selftests: add KVM_MEM_PCI_HOLE test

 Documentation/virt/kvm/api.rst                |  18 ++-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/mmu/mmu.c                        |  19 +--
 arch/x86/kvm/mmu/paging_tmpl.h                |  10 +-
 arch/x86/kvm/x86.c                            |  10 +-
 include/linux/kvm_host.h                      |   3 +
 include/uapi/linux/kvm.h                      |   2 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  81 +++++++------
 .../kvm/x86_64/memory_slot_pci_hole.c         | 112 ++++++++++++++++++
 virt/kvm/kvm_main.c                           |  39 ++++--
 12 files changed, 239 insertions(+), 58 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/memory_slot_pci_hole.c
```
#### [PATCH v5 0/3] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Fri Aug  7 15:56:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11705825
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2292722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 15:57:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8ACE22224D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 15:57:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="r9DSZhRn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726386AbgHGP5G (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 11:57:06 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:65242 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725993AbgHGP5F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 11:57:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596815825; x=1628351825;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=aRi9Uy05R53LS40Cl2TUQpYE2SoFuLjkjihkP3mfagk=;
  b=r9DSZhRnLAY3Lh6WxwtvX3DDXDaKH9jxGXflXD9pZy/Sz4SZcuitD84+
   H2uvc+IM/6DDhlbPRTgmSN5ZYWafYjJcpgKUBYFR3UK82ujDWfJU7J9S9
   tjn39cgpvI3go0c5c53dBMEDiuvCdz/wtZBKu0AhMrUvPc63PXyumoFty
   w=;
IronPort-SDR: 
 y4XqMm+0kzfvW4yIpAFwF1Tu+qCceBTtGffx1tonMt08r4cNIV5o41CNIGp5ooiDazwJVjVxQj
 gmheqMJRHdNg==
X-IronPort-AV: E=Sophos;i="5.75,446,1589241600";
   d="scan'208";a="46730315"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-e34f1ddc.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 07 Aug 2020 15:57:03 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan3.iad.amazon.com [10.40.159.166])
        by email-inbound-relay-1a-e34f1ddc.us-east-1.amazon.com (Postfix) with
 ESMTPS id 9A85FA211B;
        Fri,  7 Aug 2020 15:56:59 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 7 Aug 2020 15:56:58 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.140) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 7 Aug 2020 15:56:55 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v5 0/3] Allow user space to restrict and augment MSR emulation
Date: Fri, 7 Aug 2020 17:56:45 +0200
Message-ID: <20200807155648.8602-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.140]
X-ClientProxiedBy: EX13D29UWA001.ant.amazon.com (10.43.160.187) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While tying to add support for the MSR_CORE_THREAD_COUNT MSR in KVM,
I realized that we were still in a world where user space has no control
over what happens with MSR emulation in KVM.

That is bad for multiple reasons. In my case, I wanted to emulate the
MSR in user space, because it's a CPU specific register that does not
exist on older CPUs and that really only contains informational data that
is on the package level, so it's a natural fit for user space to provide
it.

However, it is also bad on a platform compatibility level. Currrently,
KVM has no way to expose different MSRs based on the selected target CPU
type.

This patch set introduces a way for user space to indicate to KVM which
MSRs should be handled in kernel space. With that, we can solve part of
the platform compatibility story. Or at least we can not handle AMD specific
MSRs on an Intel platform and vice versa.

In addition, it introduces a way for user space to get into the loop
when an MSR access would generate a #GP fault, such as when KVM finds an
MSR that is not handled by the in-kernel MSR emulation or when the guest
is trying to access reserved registers.

In combination with the allow list, the user space trapping allows us
to emulate arbitrary MSRs in user space, paving the way for target CPU
specific MSR implementations from user space.

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case
  - new patch: KVM: x86: Introduce allow list for MSR emulation
  - new patch: KVM: selftests: Add test for user space MSR handling

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code
  - document flags for KVM_X86_ADD_MSR_ALLOWLIST
  - generalize exit path, always unlock when returning
  - s/KVM_CAP_ADD_MSR_ALLOWLIST/KVM_CAP_X86_MSR_ALLOWLIST/g
  - Add KVM_X86_CLEAR_MSR_ALLOWLIST
  - Add test to clear whitelist
  - Adjust to reply-less API
  - Fix asserts
  - Actually trap on MSR_IA32_POWER_CTL writes

v3 -> v4:

  - Mention exit reasons in re-enter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field
  - lock allow check and clearing
  - free bitmaps on clear

v4 -> v5:

  - use srcu 

Alexander Graf (3):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Introduce allow list for MSR emulation
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 157 ++++++++++-
 arch/x86/include/asm/kvm_host.h               |  13 +
 arch/x86/include/uapi/asm/kvm.h               |  15 +
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/x86.c                            | 266 +++++++++++++++++-
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  15 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 221 +++++++++++++++
 9 files changed, 699 insertions(+), 9 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
#### [RFC PATCH 0/7] metricfs metric file system and examples
##### From: Jonathan Adams <jwadams@google.com>

```c
From patchwork Fri Aug  7 21:29:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jonathan Adams <jwadams@google.com>
X-Patchwork-Id: 11706117
Return-Path: <SRS0=9T0J=BR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9BDF5722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 21:31:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D11B22D03
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  7 Aug 2020 21:31:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="W4JL+gkP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727050AbgHGV3f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 17:29:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53446 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726891AbgHGV3f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 17:29:35 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2793CC061A27
        for <kvm@vger.kernel.org>; Fri,  7 Aug 2020 14:29:35 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id g127so4354558ybf.11
        for <kvm@vger.kernel.org>; Fri, 07 Aug 2020 14:29:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=2Epbq3zd+57RV+c5a3tR14Y8EZnVI9kXEnkZqe3uwAA=;
        b=W4JL+gkPyvYfdfwk6ydvYnTnosTt4pvJ7tL6kLXU+WUTb6rftiPRdMePYrbZabnBTD
         +ISkyoN5LHfFW3Z6CwOyFJX0djyFH2uNFR35eVqx4/Y/Qi47Gs+4ceJ48kzO4YJo7Gux
         deL3jBPiYpM3y+EqgYB+N5By3UQ0F55MxwqLYjl/Awc3revSFDBw4yahIaJqx+SGgXOg
         vquf/jHyOotjcNWthbAW3uUC7wpRsVMjWeVPbcdTZppHRp2GfKlamKeJ1xDUvV2FIBM8
         PYK8Tlv+XXASS++2PpJDsFc0cd4D+NzUwhVxDOepLelhsNX9Zlr+hx87Y8ZZOIZF3C1g
         i+rw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=2Epbq3zd+57RV+c5a3tR14Y8EZnVI9kXEnkZqe3uwAA=;
        b=sxNOq+oyKL3fFi8QLm0ni8E5yyzRJDnXS+hB0R5sU0CjPi9PuDisKeDzWrH9N/A4gn
         YY/Sv6O2+nzv4o/VXOl5nDod2oRtDabNAr2CL6i1mLxYX8m//UiEAvuklrjAfRsqyqPU
         uzMpxhBdLaVoAMNadU38dkMpaojDASAKTAeZulXtnG04JciRZEc9maKKN9MD+BbVqU01
         adoYQDm9bzlAe/OSEP7Rf2FgxD1HpoRHLGahp358ADQoD0LhXQbr4JiiWbH7SmJ2ZaTp
         DF+mK7U1mbfSkPt4IC2jWJxlIKG2Pwya8vc5hbq1pmRiGGMfJvm4ofnkBd+dYVoNm5DA
         YBmw==
X-Gm-Message-State: AOAM531KWdNASqhvGoTOvN5oE6SqvRGkrR9e8jGUpI0AdEIHLob0kDuF
        2smj7aXVhB1sJK7Ui2gxDEEHWbDUy20=
X-Google-Smtp-Source: 
 ABdhPJwpYiGEXI6N/WmSc1sNe+MKpn0dLtZLyveRHzfSP1IyYqPUCszF3totD/1mcAxmqwETOm6E5qQykQ85
X-Received: by 2002:a25:d709:: with SMTP id o9mr21697023ybg.392.1596835774334;
 Fri, 07 Aug 2020 14:29:34 -0700 (PDT)
Date: Fri,  7 Aug 2020 14:29:09 -0700
Message-Id: <20200807212916.2883031-1-jwadams@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [RFC PATCH 0/7] metricfs metric file system and examples
From: Jonathan Adams <jwadams@google.com>
To: linux-kernel@vger.kernel.org, linux-fsdevel@vger.kernel.org
Cc: netdev@vger.kernel.org, kvm@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>,
        Greg KH <gregkh@linuxfoundation.org>,
        Jim Mattson <jmattson@google.com>,
        David Rientjes <rientjes@google.com>,
        Jonathan Adams <jwadams@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[resending to widen the CC lists per rdunlap@infradead.org's suggestion
original posting to lkml here: https://lkml.org/lkml/2020/8/5/1009]

To try to restart the discussion of kernel statistics started by the
statsfs patchsets (https://lkml.org/lkml/2020/5/26/332), I wanted
to share the following set of patches which are Google's 'metricfs'
implementation and some example uses.  Google has been using metricfs
internally since 2012 as a way to export various statistics to our
telemetry systems (similar to OpenTelemetry), and we have over 200
statistics exported on a typical machine.

These patches have been cleaned up and modernized v.s. the versions
in production; I've included notes under the fold in the patches.
They're based on v5.8-rc6.

The statistics live under debugfs, in a tree rooted at:

	/sys/kernel/debug/metricfs

Each metric is a directory, with four files in it.  For example, the '
core/metricfs: Create metricfs, standardized files under debugfs.' patch
includes a simple 'metricfs_presence' metric, whose files look like:
/sys/kernel/debug/metricfs:
 metricfs_presence/annotations
  DESCRIPTION A\ basic\ presence\ metric.
 metricfs_presence/fields
  value
  int
 metricfs_presence/values
  1
 metricfs_presence/version
  1

(The "version" field always says '1', and is kind of vestigial)

An example of a more complicated stat is the networking stats.
For example, the tx_bytes stat looks like:

net/dev/stats/tx_bytes/annotations
  DESCRIPTION net\ device\ transmited\ bytes\ count
  CUMULATIVE
net/dev/stats/tx_bytes/fields
  interface value
  str int
net/dev/stats/tx_bytes/values
  lo 4394430608
  eth0 33353183843
  eth1 16228847091
net/dev/stats/tx_bytes/version
  1

The per-cpu statistics show up in the schedulat stat info and x86
IRQ counts.  For example:

stat/user/annotations
  DESCRIPTION time\ in\ user\ mode\ (nsec)
  CUMULATIVE
stat/user/fields
  cpu value
  int int
stat/user/values
  0 1183486517734
  1 1038284237228
  ...
stat/user/version
  1

The full set of example metrics I've included are:

core/metricfs: Create metricfs, standardized files under debugfs.
  metricfs_presence
core/metricfs: metric for kernel warnings
  warnings/values
core/metricfs: expose scheduler stat information through metricfs
  stat/*
net-metricfs: Export /proc/net/dev via metricfs.
  net/dev/stats/[tr]x_*
core/metricfs: expose x86-specific irq information through metricfs
  irq_x86/*

The general approach is called out in kernel/metricfs.c:

The kernel provides:
  - A description of the metric
  - The subsystem for the metric (NULL is ok)
  - Type information about the metric, and
  - A callback function which supplies metric values.

Limitations:
  - "values" files are at MOST 64K. We truncate the file at that point.
  - The list of fields and types is at most 1K.
  - Metrics may have at most 2 fields.

Best Practices:
  - Emit the most important data first! Once the 64K per-metric buffer
    is full, the emit* functions won't do anything.
  - In userspace, open(), read(), and close() the file quickly! The kernel
    allocation for the metric is alive as long as the file is open. This
    permits users to seek around the contents of the file, while
    permitting an atomic view of the data.

Note that since the callbacks are called and the data is generated at
file open() time, the relative consistency is only between members of
a given metric; the rx_bytes stat for every network interface will
be read at almost the same time, but if you want to get rx_bytes
and rx_packets, there could be a bunch of slew between the two file
opens.  (So this doesn't entirely address Andrew Lunn's comments in
https://lkml.org/lkml/2020/5/26/490)

This also doesn't address one of the basic parts of the statsfs work:
moving the statistics out of debugfs to avoid lockdown interactions.

Google has found a lot of value in having a generic interface for adding
these kinds of statistics with reasonably low overhead (reading them
is O(number of statistics), not number of objects in each statistic).
There are definitely warts in the interface, but does the basic approach
make sense to folks?

Thanks,
- Jonathan

Jonathan Adams (5):
  core/metricfs: add support for percpu metricfs files
  core/metricfs: metric for kernel warnings
  core/metricfs: expose softirq information through metricfs
  core/metricfs: expose scheduler stat information through metricfs
  core/metricfs: expose x86-specific irq information through metricfs

Justin TerAvest (1):
  core/metricfs: Create metricfs, standardized files under debugfs.

Laurent Chavey (1):
  net-metricfs: Export /proc/net/dev via metricfs.

 arch/x86/kernel/irq.c      |  80 ++++
 fs/proc/stat.c             |  57 +++
 include/linux/metricfs.h   | 131 +++++++
 kernel/Makefile            |   2 +
 kernel/metricfs.c          | 775 +++++++++++++++++++++++++++++++++++++
 kernel/metricfs_examples.c | 151 ++++++++
 kernel/panic.c             | 131 +++++++
 kernel/softirq.c           |  45 +++
 lib/Kconfig.debug          |  18 +
 net/core/Makefile          |   1 +
 net/core/net_metricfs.c    | 194 ++++++++++
 11 files changed, 1585 insertions(+)
 create mode 100644 include/linux/metricfs.h
 create mode 100644 kernel/metricfs.c
 create mode 100644 kernel/metricfs_examples.c
 create mode 100644 net/core/net_metricfs.c
```
