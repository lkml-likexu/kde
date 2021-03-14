

#### [PATCH v2 00/14] Embed struct vfio_device in all sub-structures
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Sat Mar 13 00:55:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12136221
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A38ACC4332E
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 00:57:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8310364F9E
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 00:57:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232709AbhCMA43 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 19:56:29 -0500
Received: from mail-dm6nam12on2065.outbound.protection.outlook.com
 ([40.107.243.65]:30549
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229959AbhCMA4K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 19:56:10 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=cAv2QVqhbg89hoC3S4zIl8FAOlURnGE6Usk0EWzsm8zNuDGdLM/OUu7u0/y+TTqfaxE4DyEO4Q9PvUzXpg9D6y+C96MUFm72lxCX5TRoNUzpdA3FJwO6OVDTR6bBnGJvQlBTaTojkEW+uJqcMfojV1o7Ib+s77U8TwjldYZ0XPhYv6mFSsmwNJQet1r/gc9QMBW2KNRf6XlBLMzh31whn3yA7C8OvNUhJAipfVu9zEtsyMFvGpVl2eGhZW379Ea0caZ/C5dnOPBOTyIn2dpBb/wsjrUii1nUEnDoZcWmlb8VugTXKVk5wlzy7/DnsaXtIHoAVE852MXH5wS6LXGlSA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=dfZfJwbQhdI1YgeZ+xB768O6H93NqnwVr+eb7vnctMo=;
 b=jKM6fUORRv1J9TMy3CLbn4oQV6qM5UpNt8Mbp5oaLPa0HWEwPwmaZ231oSqDYo6g0wS28irM/EPpoZ3eVw4syIubCBOMEU+JT3ftu9Tm1QHC93UDGyku3zviLwoEEBWtaSRjpRk8c2fca46LLYdfYNJU3Rlii59FpVsMpgbWa1ygd+w4JT8N/8TGhGuP7A3+ppZmLnxdbqKT/rxkVpDqz3hA8hciqyMSCrctGEUTYhYPXmujcOez7PzE+kfXCpafh769XbPW4+QyrNUhysEXa1b+J7eJIKzvC0xQz751W22fMUQjOn2LeDNkJG99Zbo4CfDwBX6jMEksQ5R3PHAbNQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=dfZfJwbQhdI1YgeZ+xB768O6H93NqnwVr+eb7vnctMo=;
 b=WwgNzbl9SdcM9gQS4cIfz67X3hRsAWlb+FXL3+eIK9oCAZ6fL0Q9Rsyy9yfZ2JWekNJ/6hoOSQu7Bi9cM1pfzQK1VZUdgJuHPBBz+EbEH+YbZn94Q5nvh38sbASHxsa0g7lXd/U7RV8jVrhrPVjLBUP+oPorwqiXfIZfj8kxjL91jKsfoWgamBf7wozn6XzkhG3Q8gt7eObRLQ1J+3AhRoHHNM76YQQ3bYYccYJUynBBQnsBOCk/h3E9b5Qqxp4o/jzM4YpvTcI0grvGkrXSLbSYFv0lfIuG5UJCVzFlhzW3UEI/q1tadd150IcGkX0A20RHwRierhXYyFyjaauVgQ==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB2940.namprd12.prod.outlook.com (2603:10b6:5:15f::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3933.31; Sat, 13 Mar
 2021 00:56:09 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3933.032; Sat, 13 Mar 2021
 00:56:08 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Diana Craciun <diana.craciun@oss.nxp.com>,
        Eric Auger <eric.auger@redhat.com>, kvm@vger.kernel.org,
        Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Bharat Bhushan <Bharat.Bhushan@nxp.com>,
        Christian Ehrhardt <christian.ehrhardt@canonical.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Daniel Vetter <daniel@ffwll.ch>,
        Christoph Hellwig <hch@lst.de>,
        Kevin Tian <kevin.tian@intel.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>,
        Liu Yi L <yi.l.liu@intel.com>
Subject: [PATCH v2 00/14] Embed struct vfio_device in all sub-structures
Date: Fri, 12 Mar 2021 20:55:52 -0400
Message-Id: <0-v2-20d933792272+4ff-vfio1_jgg@nvidia.com>
X-Originating-IP: [142.162.115.133]
X-ClientProxiedBy: BL1PR13CA0214.namprd13.prod.outlook.com
 (2603:10b6:208:2bf::9) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0214.namprd13.prod.outlook.com (2603:10b6:208:2bf::9) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.11 via Frontend
 Transport; Sat, 13 Mar 2021 00:56:08 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lKsZa-00EMAi-Mt; Fri, 12 Mar 2021 20:56:06 -0400
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 1ce6aa1c-bcf8-4231-5789-08d8e5bac98d
X-MS-TrafficTypeDiagnostic: DM6PR12MB2940:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB2940E412DBB4A8D380052CD6C26E9@DM6PR12MB2940.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 rVDs1S74kehohrn4ctBoVcsysqRVzAOI+5Fmh+rjA7DvRambjx0rxyss8Lb+mAGuiENHa/SEe3k6QnjrsbnvGbwinM2ar4niy9b9vRhk08BwunOwJBRRmV8pyOshft+fpKyaEQQuK16cPAr3lz1vFPNuC6dGkYx0o1TVTVlnoTMHPbMrPN4uVXD4YyM5t5yvisOdtJVRKt1UskVI3aRj34ApLx6LtaoRELZ92V+iDhNlRvFPn6ZbYZCyGI5/cwNnhWmnwaevJt8xfSXYv0Hb+SPxS4a3TwACRf5XxIJ4iBNN8+wwLRHf6FqflM6hPiJzxONjt/qoM+9wWSFs7i9PJXa2o53Dsv/qRSCMO7SIoijSpRefoOlJLvcFvHXtMhbBGEkTMOyeYwL1tKTu56OkkJLPbpp4A7S7VYs/rbrOc2+piKeVW6btM/I5XFCrBiBv0h3YZx8zi29QJ2AUf/U4R33TBGbGSotkuI3T+3V/pte6v9z3GnM8NjmqjS5CsLyqp9UFcGFBO51NKSctUjxf1ZCdFp7xelmy3afBT4a61GYMJJYdRaLvVQS6qGDjGscc30TEykyHrRFf/pdKoBKzkBdZnuXTw4Gk/cAejvgM28j03XyZa6MKGwPfTmiT5BSXrVss4rcWPir4jL/y4uFYZQJssNjrUW1Pdra9CKYhDUkakdlq64Ga4qL7qQqCsvW3
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(396003)(136003)(366004)(346002)(9746002)(9786002)(8676002)(6666004)(4326008)(54906003)(8936002)(5660300002)(36756003)(316002)(110136005)(83380400001)(66946007)(966005)(66556008)(186003)(26005)(66476007)(478600001)(2906002)(426003)(86362001)(7416002)(2616005)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 B0DHdN1jmP7BmUKC6iNZMe4/Hi7UyVEqFwJaqbxbCtwXRv/TOlm+QqqKulj/pcXXNtLvukOGr/P/kXrGmh8rR2vk5amEo5HPGLoTFX3M0BjzFiEkYc14i/22y6/Ao1qfc6MdQr3flKukBZit+RVDxiBiWizeVwKyxU7tnf1O2f5oHTOaCvW769rYbHoEYEa3Ajh4kfXIJ6HRF1xJrzAnsUQ98LtzVNgazv1dqbyZvbZqYfulKrOUzT+U+XjWir1o3UZoZIxuFwIjcZ5VZLifSHgDeXxBCLKLOI5gXnqydpfuLsPDYtes+Wn9egHJta1YcwKhEOH0D66VjEGYar2wfUbElQ72MoNKPecWselIfzQFD0hhtLwjFyB4V8EgumnQqO+PkpQI1+C89ToDkZ8g348Wh0SaNsc6AHX+8cx3VgO4kqhvmlqZZ4Ay1tr4RPwDJ0bj0lFp6b2DBfN7P/HMy1Q+yD5/Y5sMg9UH5J8xG39rgoQHi/DmzYbh6g2+0JNZcDkQu4BCOyQ6Uomg4sRhNlkup6kJAdBOhLVqXcUxob0ZlYg8mPNJ7L155yuCkqP+ZXpSCoQ0J5a+/Q+giS3iuoqd6pZmMBt40j5zd2atbwpaaTUjkSUiLxbb0GSECCjWil2nvCQ8oQ/vELOGwkoC8CwX7aP5fhDgFlryDKBSJGonpksOlXy74rx30sKa1jdUk8DoFKT8xgZ8a7fUFiOaq8M6KEpgA/tECeWOiCqgrU1lVc18zsyOXS+xSv7DynTLkZTo9+wTLAmwoLFe29PiflF/Uced5ox98Lt42gnHd3rLoYruqIn0cxXZr6RCK8Jz4bzA3IK/4198fhDzPokbZhsWufayuZsInJPL/w3xY5zlwBD6Ma+G+MFbyAgA2BzslfQW58yf6qV7v/WHJ5VqMsqB5Srw/o5sCLg3mf8lEQxDKK5rdDShHH5UqlRQMEUr4mb4HkJDW8+YEFVKRRI8a8nzpE7v+saz2gb+Y5KUtvKFEBGiSTnk8/913cRr0RUOprYVmuk70IdLsWXqv09a3Toq2tuW7J+w411w6y69CiKi0Ce610ac9LLyEQOlYcFsBscYfZdOLo3UFRLsGpNY4TKjBSbIktWWdVkSPCb7h6boulYUYhPnGP3bf63E+YpQwNQxvt2a5rEpKXKMECMJduJ3dfC4vsPx5ZIdyuQaanA8V152D5MjpKpoQjOBhFldkuh7kOhJoEvbxcnNXOFXU2RoGXzCbVwsTFwZ/jODRid+2dw8UPFVPL4RChtmR5s/zGozZMgZNqdViTbGSxZeOsD6wPFNxtxSSrd7NtpZkv+BzRUQwRUXam/eVl1xgHjyk2mMFwJuNfSfUiQMX8L5kQ==
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 1ce6aa1c-bcf8-4231-5789-08d8e5bac98d
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 Mar 2021 00:56:08.8941
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 UYl84cafL/0JNDi3lLEPHimY1Y/RrOStjgYCqNZpnGpm08fKiAZ53jimiW8jfvvU
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2940
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The main focus of this series is to make VFIO follow the normal kernel
convention of structure embedding for structure inheritance instead of
linking using a 'void *opaque'. Here we focus on moving the vfio_device to
be a member of every struct vfio_XX_device that is linked by a
vfio_add_group_dev().

In turn this allows 'struct vfio_device *' to be used everwhere, and the
public API out of vfio.c can be cleaned to remove places using 'struct
device *' and 'void *' as surrogates to refer to the device.

While this has the minor trade off of moving 'struct vfio_device' the
clarity of the design is worth it. I can speak directly to this idea, as
I've invested a fair amount of time carefully working backwards what all
the type-erased APIs are supposed to be and it is certainly not trivial or
intuitive.

When we get into mdev land things become even more inscrutable, and while
I now have a pretty clear picture, it was hard to obtain. I think this
agrees with the kernel style ideal of being explicit in typing and not
sacrificing clarity to create opaque structs.

After this series the general rules are:
 - Any vfio_XX_device * can be obtained at no cost from a vfio_device *
   using container_of(), and the reverse is possible by &XXdev->vdev

   This is similar to how 'struct pci_device' and 'struct device' are
   interrelated.

   This allows 'device_data' to be completely removed from the vfio.c API.

 - The drvdata for a struct device points at the vfio_XX_device that
   belongs to the driver that was probed. drvdata is removed from the core
   code, and only used as part of the implementation of the struct
   device_driver.

 - The lifetime of vfio_XX_device and vfio_device are identical, they are
   the same memory.

   This follows the existing model where vfio_del_group_dev() blocks until
   all vfio_device_put()'s are completed. This in turn means the struct
   device_driver remove() blocks, and thus under the driver_lock() a bound
   driver must have a valid drvdata pointing at both vfio device
   structs. A following series exploits this further.

Most vfio_XX_device structs have data that duplicates the 'struct
device *dev' member of vfio_device, a following series removes that
duplication too.

v2:
 - Split the get/put changes out of "Simlpify the lifetime logic for
   vfio_device"
 - Add a patch to fix probe ordering in fsl-mc and remove FIXME
 - Add a patch to re-org pci probe
 - Add a patch to fix probe odering in pci and remove FIXME
 - Remove the **pf_dev output from get_pf_vdev()
v1: https://lore.kernel.org/r/0-v1-7355d38b9344+17481-vfio1_jgg@nvidia.com

Thanks,
Jason

Jason Gunthorpe (14):
  vfio: Remove extra put/gets around vfio_device->group
  vfio: Simplify the lifetime logic for vfio_device
  vfio: Split creation of a vfio_device into init and register ops
  vfio/platform: Use vfio_init/register/unregister_group_dev
  vfio/fsl-mc: Re-order vfio_fsl_mc_probe()
  vfio/fsl-mc: Use vfio_init/register/unregister_group_dev
  vfio/pci: Move VGA and VF initialization to functions
  vfio/pci: Re-order vfio_pci_probe()
  vfio/pci: Use vfio_init/register/unregister_group_dev
  vfio/mdev: Use vfio_init/register/unregister_group_dev
  vfio/mdev: Make to_mdev_device() into a static inline
  vfio: Make vfio_device_ops pass a 'struct vfio_device *' instead of
    'void *'
  vfio/pci: Replace uses of vfio_device_data() with container_of
  vfio: Remove device_data from the vfio bus driver API

 Documentation/driver-api/vfio.rst             |  48 ++--
 drivers/vfio/fsl-mc/vfio_fsl_mc.c             |  96 ++++---
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h     |   1 +
 drivers/vfio/mdev/mdev_private.h              |   5 +-
 drivers/vfio/mdev/vfio_mdev.c                 |  57 ++--
 drivers/vfio/pci/vfio_pci.c                   | 253 ++++++++++--------
 drivers/vfio/pci/vfio_pci_private.h           |   1 +
 drivers/vfio/platform/vfio_amba.c             |   8 +-
 drivers/vfio/platform/vfio_platform.c         |  21 +-
 drivers/vfio/platform/vfio_platform_common.c  |  56 ++--
 drivers/vfio/platform/vfio_platform_private.h |   5 +-
 drivers/vfio/vfio.c                           | 210 +++++----------
 include/linux/vfio.h                          |  37 ++-
 13 files changed, 397 insertions(+), 401 deletions(-)
```
#### [PATCH v4 0/6] KVM: arm64: Add VLPI migration support on GICv4.1
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Sat Mar 13 08:38:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12136631
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 571EDC433E9
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 08:40:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BECA64F1D
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 08:40:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233170AbhCMIj6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Mar 2021 03:39:58 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:14327 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230441AbhCMIjg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Mar 2021 03:39:36 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DyGJz6DxKz8wxp;
        Sat, 13 Mar 2021 16:37:39 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.498.0; Sat, 13 Mar 2021 16:39:21 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v4 0/6] KVM: arm64: Add VLPI migration support on GICv4.1
Date: Sat, 13 Mar 2021 16:38:54 +0800
Message-ID: <20210313083900.234-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

In GICv4.1, migration has been supported except for (directly-injected)
VLPI. And GICv4.1 Spec explicitly gives a way to get the VLPI's pending
state (which was crucially missing in GICv4.0). So we make VLPI migration
capable on GICv4.1 in this series.

In order to support VLPI migration, we need to save and restore all
required configuration information and pending states of VLPIs. But
in fact, the configuration information of VLPIs has already been saved
(or will be reallocated on the dst host...) in vgic(kvm) migration.
So we only have to migrate the pending states of VLPIs specially.

Below is the related workflow in migration.

On the save path:
	In migration completion:
		pause all vCPUs
				|
		call each VM state change handler:
			pause other devices (just keep from sending interrupts, and
			such as VFIO migration protocol has already realized it [1])
					|
			flush ITS tables into guest RAM
					|
			flush RDIST pending tables (also flush VLPI pending states here)
				|
		...
On the resume path:
	load each device's state:
		restore ITS tables (include pending tables) from guest RAM
				|
		for other (PCI) devices (paused), if configured to have VLPIs,
		establish the forwarding paths of their VLPIs (and transfer
		the pending states from kvm's vgic to VPT here)

We have tested this series in VFIO migration, and found some related
issues in QEMU [2].

Links:
[1] vfio: UAPI for migration interface for device state:
    https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=a8a24f3f6e38103b77cf399c38eb54e1219d00d6
[2] vfio: Some fixes and optimizations for VFIO migration:
    https://patchwork.ozlabs.org/project/qemu-devel/cover/20210310030233.1133-1-lushenming@huawei.com/

History:

v3 -> v4
 - Nit fixes.
 - Add a CPU cache invalidation right after unmapping the vPE. (Patch 1)
 - Drop the setting of PTZ altogether. (Patch 2)
 - Bail out if spot !vgic_initialized(). (in Patch 4)
 - Communicate the state change (clear pending_latch) via
   vgic_queue_irq_unlock. (in Patch 5)

Thanks a lot for the suggestions from Marc!

v2 -> v3
 - Add the vgic initialized check to ensure that the allocation and enabling
   of the doorbells have already been done before unmapping the vPEs.
 - Check all get_vlpi_state related conditions in save_pending_tables in one place.
 - Nit fixes.

v1 -> v2:
 - Get the VLPI state from the KVM side.
 - Nit fixes.

Thanks,
Shenming


Marc Zyngier (1):
  irqchip/gic-v3-its: Add a cache invalidation right after vPE unmapping

Shenming Lu (4):
  irqchip/gic-v3-its: Drop the setting of PTZ altogether
  KVM: arm64: GICv4.1: Add function to get VLPI state
  KVM: arm64: GICv4.1: Try to save VLPI state in save_pending_tables
  KVM: arm64: GICv4.1: Give a chance to save VLPI state

Zenghui Yu (1):
  KVM: arm64: GICv4.1: Restore VLPI pending state to physical side

 .../virt/kvm/devices/arm-vgic-its.rst         |  2 +-
 arch/arm64/kvm/vgic/vgic-its.c                |  6 +-
 arch/arm64/kvm/vgic/vgic-v3.c                 | 66 +++++++++++++++++--
 arch/arm64/kvm/vgic/vgic-v4.c                 | 37 +++++++++++
 arch/arm64/kvm/vgic/vgic.h                    |  1 +
 drivers/irqchip/irq-gic-v3-its.c              | 21 +++++-
 6 files changed, 121 insertions(+), 12 deletions(-)
```
