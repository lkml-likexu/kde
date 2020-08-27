

#### [PATCH v4 00/10] vfio/fsl-mc: VFIO support for FSL-MC device
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

The patches are dependent on some changes in the mc-bus (bus/fsl-mc)
driver. The changes were needed in order to re-use code and to export
some more functions that are needed by the VFIO driver.
Currenlty the mc-bus patches are under review:
https://www.spinics.net/lists/kernel/msg3639226.html

v3 --> v4
- use bus provided functions to tear down the DPRC
- added reset support

v2 --> v3
- There is no need to align region size to page size
- read/write implemented for all DPAA2 objects
- review fixes

v1 --> v2
- Fixed the container reset, a new flag added to the firmware command
- Implement a bus notifier for setting driver_override


Bharat Bhushan (1):
  vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (9):
  vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
  vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
  vfio/fsl-mc: Added lock support in preparation for interrupt handling
  vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
  vfio/fsl-mc: trigger an interrupt via eventfd
  vfio/fsl-mc: Add read/write support for fsl-mc devices
  vfio/fsl-mc: Add support for device reset

 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 684 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 221 +++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  56 ++
 include/uapi/linux/vfio.h                 |   1 +
 9 files changed, 983 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
```
#### [PATCH v5 0/4] Add a vhost RPMsg API
##### From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>

```c
From patchwork Wed Aug 26 17:46:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Guennadi Liakhovetski
 <guennadi.liakhovetski@linux.intel.com>
X-Patchwork-Id: 11739235
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C10213B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 17:46:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D5422078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 17:46:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726740AbgHZRql (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Aug 2020 13:46:41 -0400
Received: from mga07.intel.com ([134.134.136.100]:49544 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726187AbgHZRqk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Aug 2020 13:46:40 -0400
IronPort-SDR: 
 gpce1UmP34tPutiLd6xAsI70/cckO4WHcFg4mgpJVMcM1r/4+y8Ll/1UP2jFdhFWcdLiC2k3pm
 Im9ForHRWGhg==
X-IronPort-AV: E=McAfee;i="6000,8403,9725"; a="220607111"
X-IronPort-AV: E=Sophos;i="5.76,356,1592895600";
   d="scan'208";a="220607111"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Aug 2020 10:46:40 -0700
IronPort-SDR: 
 NvVKc6XJtzEuvejT10T0ZfgUmLOsrZhgFX0TcsLcHbcsrq3JnXyqD5FwhmIvmidyChl+uEYnqe
 KndxEbdQSPsg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,356,1592895600";
   d="scan'208";a="299553450"
Received: from gliakhov-mobl2.ger.corp.intel.com (HELO
 ubuntu.ger.corp.intel.com) ([10.252.54.141])
  by orsmga006.jf.intel.com with ESMTP; 26 Aug 2020 10:46:37 -0700
From: Guennadi Liakhovetski <guennadi.liakhovetski@linux.intel.com>
To: kvm@vger.kernel.org
Cc: linux-remoteproc@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        sound-open-firmware@alsa-project.org,
        Pierre-Louis Bossart <pierre-louis.bossart@linux.intel.com>,
        Liam Girdwood <liam.r.girdwood@linux.intel.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Vincent Whitchurch <vincent.whitchurch@axis.com>
Subject: [PATCH v5 0/4] Add a vhost RPMsg API
Date: Wed, 26 Aug 2020 19:46:32 +0200
Message-Id: <20200826174636.23873-1-guennadi.liakhovetski@linux.intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Next update:

v5:
- don't hard-code message layout

v4:
- add endianness conversions to comply with the VirtIO standard

v3:
- address several checkpatch warnings
- address comments from Mathieu Poirier

v2:
- update patch #5 with a correct vhost_dev_init() prototype
- drop patch #6 - it depends on a different patch, that is currently
  an RFC
- address comments from Pierre-Louis Bossart:
  * remove "default n" from Kconfig

Linux supports RPMsg over VirtIO for "remote processor" / AMP use
cases. It can however also be used for virtualisation scenarios,
e.g. when using KVM to run Linux on both the host and the guests.
This patch set adds a wrapper API to facilitate writing vhost
drivers for such RPMsg-based solutions. The first use case is an
audio DSP virtualisation project, currently under development, ready
for review and submission, available at
https://github.com/thesofproject/linux/pull/1501/commits

Thanks
Guennadi

Guennadi Liakhovetski (4):
  vhost: convert VHOST_VSOCK_SET_RUNNING to a generic ioctl
  rpmsg: move common structures and defines to headers
  rpmsg: update documentation
  vhost: add an RPMsg API

 Documentation/rpmsg.txt          |   6 +-
 drivers/rpmsg/virtio_rpmsg_bus.c |  78 +------
 drivers/vhost/Kconfig            |   7 +
 drivers/vhost/Makefile           |   3 +
 drivers/vhost/rpmsg.c            | 373 +++++++++++++++++++++++++++++++
 drivers/vhost/vhost_rpmsg.h      |  74 ++++++
 include/linux/virtio_rpmsg.h     |  83 +++++++
 include/uapi/linux/rpmsg.h       |   3 +
 include/uapi/linux/vhost.h       |   4 +-
 9 files changed, 551 insertions(+), 80 deletions(-)
 create mode 100644 drivers/vhost/rpmsg.c
 create mode 100644 drivers/vhost/vhost_rpmsg.h
 create mode 100644 include/linux/virtio_rpmsg.h
```
#### [PATCH v5 00/12] SVM cleanup and INVPCID feature support
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Wed Aug 26 19:13:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11739525
Return-Path: <SRS0=WeJu=CE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E69613A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 19:13:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40EF72083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Aug 2020 19:13:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="oGdAwHLv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727105AbgHZTNt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Aug 2020 15:13:49 -0400
Received: from mail-eopbgr770071.outbound.protection.outlook.com
 ([40.107.77.71]:40778
        "EHLO NAM02-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726191AbgHZTNs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Aug 2020 15:13:48 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Pn+wPMPjT4h5A8oijsKTlgRe3fj+25d8se20bElm6DOL1eRUr71bZeZkwAufrVRxixMVhvRjKoRhGQypRMUR1yGu4cWgfL4bHwtEBTpzOMX2tftSUDSMM6p7TiIzFb556jA50NXIqx/ml/GEMQcnXMiDRRhO2qjhsEasEKGUGx/rVp2oz3D8hg82Qir3lQhZRe2O1pZFpeu6rkooK862sEuHQRbHaE9rAzied6Pfqq0u33zMoN/FWpTEX1Y6F9wDxVxYGr+aiWfEa/iVN4aMWIXmy4AqC0SPwABPAS7Y6+E4EYf0pVujEH8prVTWlb5MLK78BRBPnHU9sFXMQ+sulw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=nh4OqxKc1FcR8uXcuV9gqsIFIqN6sczGPryFOBwIDNc=;
 b=DSGFK8jrZe4WcNHEIztpNgOGKNhy+AGBVAsanDH7qoL/c2biP2COvwNa9M+6Msf7irk/oxe5Uz6rZTU+ZbxCsmYqSUZ6JZkE1/n0Ek9rGnwoegPJJ9+X4J3zxp8QILXD1GJWPuU+mEpxPEq5B9Ibkoem4dhQ0z/C8xHvrEbSrR2x7Ng4zCgwbIzTV/H/pha2rxbtdo0hmDUKoyOYweNYI/9WHV3zSqulUKYb78zrqHPcFifWxhOOXjMST+oPO6Wc7SYB0w2uR++TVOgQNHgCdvdzzjekfbZIcRqoIzhlyauOKmUVXEmCidzQ7UufeF4gIxWZ+2tC0o9fAedOWYc7BQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=nh4OqxKc1FcR8uXcuV9gqsIFIqN6sczGPryFOBwIDNc=;
 b=oGdAwHLvf18ajDeoYdDivB6CjXPzmZRSsQZkS9fqqUH9W7WTBoeRE5BEbkZ+jUTikPePFNVNDOC1A2uLB03Fp4kXK2n9wCNFW9djBXPT3s3FyYTpodyfvymeHOVBk18AcKt3BMowWcUY/fYu7Xb5s4WgksNo76UTiz9a67cItEA=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2384.namprd12.prod.outlook.com (2603:10b6:802:25::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3305.26; Wed, 26 Aug
 2020 19:13:45 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::ccd9:728:9577:200d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::ccd9:728:9577:200d%4]) with mapi id 15.20.3305.026; Wed, 26 Aug 2020
 19:13:45 +0000
Subject: [PATCH v5 00/12] SVM cleanup and INVPCID feature support
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, jmattson@google.com
Cc: wanpengli@tencent.com, kvm@vger.kernel.org, joro@8bytes.org,
        x86@kernel.org, linux-kernel@vger.kernel.org, babu.moger@amd.com,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com, tglx@linutronix.de
Date: Wed, 26 Aug 2020 14:13:43 -0500
Message-ID: <159846887637.18873.14677728679411578606.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: DM6PR21CA0026.namprd21.prod.outlook.com
 (2603:10b6:5:174::36) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from 255.255.255.255 (255.255.255.255) by
 DM6PR21CA0026.namprd21.prod.outlook.com (2603:10b6:5:174::36) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3348.3 via Frontend
 Transport; Wed, 26 Aug 2020 19:13:44 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 512a4934-e640-4ff9-dc70-08d849f4272a
X-MS-TrafficTypeDiagnostic: SN1PR12MB2384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB2384EF6FDA2832E7AEED94A495540@SN1PR12MB2384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3383;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 tI3k6A/0ldOQNGM5AR5XY6dpFQjhdseOzAVQSC7A799F/DNYLU2NJXZdkDekHIVXuUsxenV4RkHcxJBRJocABXPWpRflsuoXvXqtAf0BMnuoSTaL99dAv2uCkdENOd3+jFbjUkX5XZkhiPCwPvj/7Wn7nxzf2PBHC4aHxqep/22RWnMmHxBlWRCk28D33IBpj/t8py5KaYGQ2RS7bAu0WofZGa3u5KLNKJA5yIE3OtrVRpPVSnhBvBoJaqNSr+1jHkf+bsTAP5i0JIiTZy1KAUvBwvpIsikXGsS8vkBAsyXw++WLmFzFRIL4irYilrpvqe5U7Y5Z2rTJmNBcg+QCAhKXtHZSwg2byb9jS+8yFuNqk22oC17PrCpEjNLwxIykvk/tDxSVfJMYL1/ovNJtdg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(346002)(366004)(136003)(376002)(396003)(39860400002)(103116003)(4326008)(186003)(966005)(66946007)(5660300002)(66476007)(66556008)(44832011)(86362001)(33716001)(9686003)(52116002)(7416002)(83380400001)(6486002)(8936002)(8676002)(16576012)(2906002)(316002)(26005)(478600001)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Lc22HPGXU4XNt6HBxBGLZGd2P0C8hY87wYVU0N3v4zGGHYDnt1ErVrjlCkWiVC/381PAypYTyZv2oigqaDKqJUVjCoqkhey5rK8JpHNLpvdon+knpshBClcGe/WMxZX0tWOyn/vdQp8014YvbPhjFalsesWS23+RqqaqtZD6jCmzo7vQ1AleWmPxLgRrtPX08pvf88RTKqeg80TRc4TGX5NvD3WT6L5wFWU7cDmyH+Rze6JY7DG1/O/+Vg2wlEj08xhvFxxKtUxN23A1MJvLXzE0hQQ8/RIdHBjtBdWslCcJj6llWTPqQR2aCMGbV8R0sk+0Bx2T56+OOpAOcNHDnYd4sosj1HLKPQJ+cAzVxSz0xHZ7kocktu0VxeEDbpeuIdmVMbtDxxTNga2rwMTt0G6VYBtlKG6SpNsPUy0j9FQ+0VkspVPsuDKO/xZmfCpRhXLQnsnBoP0Nt+rpKCNBFAcBM2Z7Oru4073BhKBh/UYvhzWQe7BnELtVa6ldLRBbeehOl2gaUkxGKc4JRNmJ+7wbudNTdWmLTLCPqoEQtTBCgih5uSP7l9Ech0BfKimI89HbiJLpSuKMGMh3MFjsKWHQ/ZaeV0LEQcQNTRPnH+2sUqSZIsXJ+wffjvG6bflwLKU/nnWCGSKvn0O4TkdUnw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 512a4934-e640-4ff9-dc70-08d849f4272a
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Aug 2020 19:13:45.2392
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 56UM813fz+FsVPkG9dMnyVj7+nfxunPxds5TRoAyByUjOyJAw7gj+WmpFvW5JzF2
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2384
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
v5:
 All the changes are related to rebase.
 Aplies cleanly on mainline and kvm(master) tree. 
 Resending it to get some attention.

v4:
 https://lore.kernel.org/lkml/159676101387.12805.18038347880482984693.stgit@bmoger-ubuntu/
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
      KVM: SVM: Introduce vmcb_(set_intercept/clr_intercept/_is_intercept)
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
Signature
```
