#### [PATCH v2 1/2] vfio-mdev: Wire in a request handler for mdev parent
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11921513
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 422F0C63798
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:08:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6C502245A
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:08:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="VpOlQaN9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729688AbgKTSHw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 13:07:52 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:32418 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729284AbgKTSHw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Nov 2020 13:07:52 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AKI47DT006530;
        Fri, 20 Nov 2020 13:07:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=7eJtt7jySeBBBAuHDda7603FpWhcUCOIkSBdm6WMkrs=;
 b=VpOlQaN9t82XWI5+nGR77tnwI2iwnYF3BC6VKxIUcwhkKrDg+aOIcaxleOPDycd4tn8k
 ogY4f22GJj1rxb9u/8rQTotqGaaiD0ZVCq7CJd0khp52kPCEIa7P10pbh9GA9ZclCoek
 yRLsU9HuHmFRRcD6jYb5Fvk4QKOPSuNsYk5LRj97ZYMshyaP6x+F42McXf8Fhwdin4D0
 daxHFVEKQaHqMSE4jhtckjLbMP6wVc47BjlffbP9CdLdizWhCs2KknW7fYSF5vam/RBs
 VWMXfGBVSJNXDrhJRNuXY2vnj6ZS6wp9YksiJkiW/WHwNiDeFtL8+MykNBbmjy2hi0Ax Cw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34xgu84e4j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 20 Nov 2020 13:07:49 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AKI7Mep021171;
        Fri, 20 Nov 2020 13:07:48 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34xgu84e37-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 20 Nov 2020 13:07:48 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AKI7kxn030282;
        Fri, 20 Nov 2020 18:07:46 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06ams.nl.ibm.com with ESMTP id 34w4yfjc53-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 20 Nov 2020 18:07:46 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AKI7hYD62062850
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 20 Nov 2020 18:07:43 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 799E5A405F;
        Fri, 20 Nov 2020 18:07:43 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6274CA4062;
        Fri, 20 Nov 2020 18:07:43 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 20 Nov 2020 18:07:43 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 10407E23B2; Fri, 20 Nov 2020 19:07:43 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v2 1/2] vfio-mdev: Wire in a request handler for mdev parent
Date: Fri, 20 Nov 2020 19:07:39 +0100
Message-Id: <20201120180740.87837-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201120180740.87837-1-farman@linux.ibm.com>
References: <20201120180740.87837-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-20_09:2020-11-20,2020-11-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 clxscore=1015
 lowpriorityscore=0 adultscore=0 mlxscore=0 bulkscore=0 malwarescore=0
 priorityscore=1501 phishscore=0 suspectscore=0 spamscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011200120
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While performing some destructive tests with vfio-ccw, where the
paths to a device are forcible removed and thus the device itself
is unreachable, it is rather easy to end up in an endless loop in
vfio_del_group_dev() due to the lack of a request callback for the
associated device.

In this example, one MDEV (77c) is used by a guest, while another
(77b) is not. The symptom is that the iommu is detached from the
mdev for 77b, but not 77c, until that guest is shutdown:

    [  238.794867] vfio_ccw 0.0.077b: MDEV: Unregistering
    [  238.794996] vfio_mdev 11f2d2bc-4083-431d-a023-eff72715c4f0: Removing from iommu group 2
    [  238.795001] vfio_mdev 11f2d2bc-4083-431d-a023-eff72715c4f0: MDEV: detaching iommu
    [  238.795036] vfio_ccw 0.0.077c: MDEV: Unregistering
    ...silence...

Let's wire in the request call back to the mdev device, so that a
device being physically removed from the host can be (gracefully?)
handled by the parent device at the time the device is removed.

Add a message when registering the device if a driver doesn't
provide this callback, so a clue is given that this same loop
may be encountered in a similar situation.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/mdev/mdev_core.c |  4 ++++
 drivers/vfio/mdev/vfio_mdev.c | 10 ++++++++++
 include/linux/mdev.h          |  4 ++++
 3 files changed, 18 insertions(+)

```
#### [PATCH 1/3] Documentation: KVM: change description of vcpu ioctls KVM_(GET|SET)_ONE_REG
##### From: <darkhan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: darkhan@amazon.com
X-Patchwork-Id: 11920215
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45BE4C5519F
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 12:56:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D4A6B22264
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 12:56:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="bG7qJjH3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727843AbgKTM44 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 07:56:56 -0500
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:50174 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726391AbgKTM4z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Nov 2020 07:56:55 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1605877015; x=1637413015;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=ceMWn8T0CAbjITH4HkGnzvZ7dokgaqs2qfmig/tZCQk=;
  b=bG7qJjH3g5PXpkAjG027lYbrDevtounJ22utoyeja6JXJ6U+yWk1r3D0
   NB495EVZjIcM1BvXuCj7LvvZ8cfo/gddxUDFCKunua0dst1B5XPyKhhK2
   gQNYn8V44BG96TWFyImaD1EKBR4CXrQ//auf9hGu7l+wFAhXlUh/bkK5I
   U=;
X-IronPort-AV: E=Sophos;i="5.78,356,1599523200";
   d="scan'208";a="65113057"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1e-c7c08562.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 20 Nov 2020 12:56:54 +0000
Received: from EX13D50EUA002.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1e-c7c08562.us-east-1.amazon.com (Postfix) with
 ESMTPS id 0D9E5240C32;
        Fri, 20 Nov 2020 12:56:50 +0000 (UTC)
Received: from EX13D52EUA002.ant.amazon.com (10.43.165.139) by
 EX13D50EUA002.ant.amazon.com (10.43.165.201) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 20 Nov 2020 12:56:49 +0000
Received: from uc995cb558fb65a.ant.amazon.com (10.43.162.50) by
 EX13D52EUA002.ant.amazon.com (10.43.165.139) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 20 Nov 2020 12:56:44 +0000
From: <darkhan@amazon.com>
To: <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, <corbet@lwn.net>, <maz@kernel.org>,
        <james.morse@arm.com>, <catalin.marinas@arm.com>,
        <chenhc@lemote.com>, <paulus@ozlabs.org>, <frankja@linux.ibm.com>,
        <mingo@redhat.com>, <acme@redhat.com>, <graf@amazon.de>,
        <darkhan@amazon.de>, Darkhan Mukashov <darkhan@amazon.com>
Subject: [PATCH 1/3] Documentation: KVM: change description of vcpu ioctls
 KVM_(GET|SET)_ONE_REG
Date: Fri, 20 Nov 2020 13:56:14 +0100
Message-ID: <20201120125616.14436-2-darkhan@amazon.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201120125616.14436-1-darkhan@amazon.com>
References: <20201120125616.14436-1-darkhan@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.162.50]
X-ClientProxiedBy: EX13D32UWB001.ant.amazon.com (10.43.161.248) To
 EX13D52EUA002.ant.amazon.com (10.43.165.139)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Darkhan Mukashov <darkhan@amazon.com>

KVM APIs KVM_GET_ONE_REG and KVM_SET_ONE_REG are not implemented
in x86. They are handled in architecture specific "kvm_arch_vcpu_ioctl"
functions. There are no handlers for KVM_GET_ONE_REG and KVM_SET_ONE_REG
in "kvm_arch_vcpu_ioctl" in x86. -EINVAL is returned when both are called.
Therefore, architectures supported by KVM_(GET|SET)_ONE_REG should be
"all except x86" rather than "all".

KVM_GET_ONE_REG accepts a struct kvm_one_reg and writes value of a register
indicated by 'id' field of the struct to the memory location pointed by
'addr' field of the struct. As nothing is written to the struct
kvm_one_reg, parameter type should be "in" rather than "in/out".

Signed-off-by: Darkhan Mukashov <darkhan@amazon.com>
---
 Documentation/virt/kvm/api.rst | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] kvm/x86/mmu: use the correct inherited permissions to get shadow page
##### From: Lai Jiangshan <jiangshanlai@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lai Jiangshan <jiangshanlai@gmail.com>
X-Patchwork-Id: 11919693
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4664DC6379F
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 08:55:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E0581223B0
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 08:55:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="T1qI09CM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727348AbgKTIys (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 03:54:48 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36570 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726799AbgKTIyr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Nov 2020 03:54:47 -0500
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6899FC0613CF;
        Fri, 20 Nov 2020 00:54:47 -0800 (PST)
Received: by mail-pf1-x443.google.com with SMTP id g7so7232244pfc.2;
        Fri, 20 Nov 2020 00:54:47 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=J/GGZ6aBy0fAJHljiYm9GCn8PhX9nN8QvN23eDsxWuk=;
        b=T1qI09CMPKnjLyDYy5sS1ZvKis/W3pvPci8guN7/8hK87Tzs/WoHCgxsuwGdXrhURS
         aBnSfNwCs6wmBWQBBi0kfPVEJvfImuz3ZjK5Utw2DDXHlmSBC6q5Y3UpgagZZgy1eqi/
         yIWa84v8guKk08Wsq/+Jl18AtYuCPNUO2yuGoUUb0pLWBG8GljbWiJ9q8r1h38MDlrgz
         q/J4F0A6W3Jx/knO+EnmHsdJ3a2uTaVVq6HtYxnyDfe9hUnvv/vsUpF156stnorc5scJ
         4bfFw1p8aGUAL66NGMj51G5A4mHc/Q/wLG2sYKIe75SDBplUBVCnw3mvBcYoOCDn2EVg
         +mUQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=J/GGZ6aBy0fAJHljiYm9GCn8PhX9nN8QvN23eDsxWuk=;
        b=Wa6/WrnfvaG29/mmeTVj4AvvO/yOaaEH9aWRIdTGKO2BUwzHslFrKJDzvQMimXkWQh
         6o8RrNnqPAj6Huy47jQ1RdJj2ZT1QocIT//iXlearNyXQawkKQUAqyIZSXcxQ28mOYoO
         p4fHybmU9UtOBtT2poLJlcAcI3Zfe46/ZLSHdm4aiBT1VENWWjlolGa5OXs35HESdw4F
         C6+gyGE54Mfbmb4CigIUDVvA1DC7bDR7v7KrLyRKIymAHkdq4GuNO7ELnLfbUDU8ToWQ
         dXkcJ2BBtAf2C4PYvWDkoXFhmwOkbk1xoT/c16oy4bOI1Bd9PWMrkJOPqmYo6/Alre25
         rsNQ==
X-Gm-Message-State: AOAM532tqvQ6OUPrgWFnnCGfit/Q8eZ1BARr0x4xgfQ4BOQRON39s7lm
        +x0Uhqki/JUfjqICZMKVUSmjQ2JB6+g=
X-Google-Smtp-Source: 
 ABdhPJywHQyJ4kLhi69aEm0AdkK7Bpe/GnTHUS4lbV9KMn5cRw1YJ4PoVKVXo/A811o9pUjYqKjN4g==
X-Received: by 2002:a17:90b:208:: with SMTP id
 fy8mr9132287pjb.204.1605862486817;
        Fri, 20 Nov 2020 00:54:46 -0800 (PST)
Received: from localhost ([47.251.4.198])
        by smtp.gmail.com with ESMTPSA id
 s189sm2734936pfb.60.2020.11.20.00.54.45
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 20 Nov 2020 00:54:46 -0800 (PST)
From: Lai Jiangshan <jiangshanlai@gmail.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Lai Jiangshan <laijs@linux.alibaba.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Avi Kivity <avi@qumranet.com>, linux-doc@vger.kernel.org
Subject: [PATCH] kvm/x86/mmu: use the correct inherited permissions to get
 shadow page
Date: Fri, 20 Nov 2020 17:55:17 +0800
Message-Id: <20201120095517.19211-1-jiangshanlai@gmail.com>
X-Mailer: git-send-email 2.19.1.6.gb485710b
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Lai Jiangshan <laijs@linux.alibaba.com>

Commit 41074d07c78b ("KVM: MMU: Fix inherited permissions for emulated
guest pte updates") said role.access is common access permissions for
all ptes in this shadow page, which is the inherited permissions from
the parent ptes.

But the commit did not enforce this definition when kvm_mmu_get_page()
is called in FNAME(fetch). Rather, it uses a random (last level pte's
combined) access permissions. And the permissions won't be checked again
in next FNAME(fetch) since the spte is present. It might fail to meet
guest's expectation when guest sets up spaghetti pagetables.

Fixes: 41074d07c78b ("KVM: MMU: Fix inherited permissions for emulated guest pte updates")
Signed-off-by: Lai Jiangshan <laijs@linux.alibaba.com>
---
 Documentation/virt/kvm/mmu.rst |  4 ++--
 arch/x86/kvm/mmu/paging_tmpl.h | 14 +++++++++-----
 2 files changed, 11 insertions(+), 7 deletions(-)

```
#### [PATCH net] vsock/virtio: discard packets only when socket is really closed
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11920045
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8F108C63777
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 10:48:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31F6E22255
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 10:48:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cXkKSbgm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727327AbgKTKrx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 05:47:53 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37887 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726460AbgKTKrw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Nov 2020 05:47:52 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605869270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=FWeqzBmZlLWAnJm9w9KD07ccv+2odS4qEQoYooXswuk=;
        b=cXkKSbgmjG6ii2sVCxbDNQVsJWAsKtm6eOOIpyMOq67WZVdsP4BhDJnPw+blN0ZLQZ+ld0
        bMawmSVwXYWNiomh7rt25XLZ5MIM9ej86nOpPhppKvJP1AW8OYFz+WTSb00O+XtJfynKtd
        94JUYi9jX50rJVOFim6PHR2jBMvR7dM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-141-z5gMOlHWMvOuFb6u_w9ZmA-1; Fri, 20 Nov 2020 05:47:47 -0500
X-MC-Unique: z5gMOlHWMvOuFb6u_w9ZmA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CA5A9801B1C;
        Fri, 20 Nov 2020 10:47:45 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-114-22.ams2.redhat.com
 [10.36.114.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0495F1F0;
        Fri, 20 Nov 2020 10:47:36 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: Sergio Lopez <slp@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Jia He <justin.he@arm.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org,
        Jakub Kicinski <kuba@kernel.org>
Subject: [PATCH net] vsock/virtio: discard packets only when socket is really
 closed
Date: Fri, 20 Nov 2020 11:47:36 +0100
Message-Id: <20201120104736.73749-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Starting from commit 8692cefc433f ("virtio_vsock: Fix race condition
in virtio_transport_recv_pkt"), we discard packets in
virtio_transport_recv_pkt() if the socket has been released.

When the socket is connected, we schedule a delayed work to wait the
RST packet from the other peer, also if SHUTDOWN_MASK is set in
sk->sk_shutdown.
This is done to complete the virtio-vsock shutdown algorithm, releasing
the port assigned to the socket definitively only when the other peer
has consumed all the packets.

If we discard the RST packet received, the socket will be closed only
when the VSOCK_CLOSE_TIMEOUT is reached.

Sergio discovered the issue while running ab(1) HTTP benchmark using
libkrun [1] and observing a latency increase with that commit.

To avoid this issue, we discard packet only if the socket is really
closed (SOCK_DONE flag is set).
We also set SOCK_DONE in virtio_transport_release() when we don't need
to wait any packets from the other peer (we didn't schedule the delayed
work). In this case we remove the socket from the vsock lists, releasing
the port assigned.

[1] https://github.com/containers/libkrun

Fixes: 8692cefc433f ("virtio_vsock: Fix race condition in virtio_transport_recv_pkt")
Cc: justin.he@arm.com
Reported-by: Sergio Lopez <slp@redhat.com>
Tested-by: Sergio Lopez <slp@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
Acked-by: Jia He <justin.he@arm.com>
---
 net/vmw_vsock/virtio_transport_common.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [RFC PATCH 01/27] vhost: Add vhost_dev_can_log
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11921939
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DECAC2D0E4
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:52:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 180A82242B
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 18:52:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AaKAOrM3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731996AbgKTSvj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 13:51:39 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21503 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731980AbgKTSvi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Nov 2020 13:51:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605898297;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=VF68uyWFilZpHj5bABsThH0akvfjRoVBR9ksieJzwHo=;
        b=AaKAOrM3/iaSHqnaOU1KU0SrKPOCueZr/jrwytmWXXexRDqFDpXT6e6cCVMKgx92Jp4OkK
        JpSpY5eJ1T0jkULUERwbAlM7W30vj9NiMncv42CTW+1jBsriH+XfBCzD2NmyX2KEn6hUBJ
        u4fsjXNA593wo0h+qls6XsOrCVMghZs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-125-5oC7RBGnOfe3nRKgW98M6A-1; Fri, 20 Nov 2020 13:51:33 -0500
X-MC-Unique: 5oC7RBGnOfe3nRKgW98M6A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C2F0E1842159;
        Fri, 20 Nov 2020 18:51:30 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-88.ams2.redhat.com
 [10.36.112.88])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 440965C1D5;
        Fri, 20 Nov 2020 18:51:23 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: qemu-devel@nongnu.org
Cc: Lars Ganrot <lars.ganrot@gmail.com>,
        virtualization@lists.linux-foundation.org,
        Salil Mehta <mehta.salil.lnk@gmail.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Liran Alon <liralon@gmail.com>,
        Rob Miller <rob.miller@broadcom.com>,
        Max Gurtovoy <maxgu14@gmail.com>,
        Alex Barba <alex.barba@broadcom.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Jim Harford <jim.harford@broadcom.com>,
        Jason Wang <jasowang@redhat.com>,
        Harpreet Singh Anand <hanand@xilinx.com>,
        Christophe Fontaine <cfontain@redhat.com>,
        vm <vmireyno@marvell.com>, Daniel Daly <dandaly0@gmail.com>,
        Michael Lilja <ml@napatech.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Nitin Shrivastav <nitin.shrivastav@broadcom.com>,
        Lee Ballard <ballle98@gmail.com>,
        Dmytro Kazantsev <dmytro.kazantsev@gmail.com>,
        Juan Quintela <quintela@redhat.com>, kvm@vger.kernel.org,
        Howard Cai <howard.cai@gmail.com>,
        Xiao W Wang <xiao.w.wang@intel.com>,
        Sean Mooney <smooney@redhat.com>,
        Parav Pandit <parav@mellanox.com>,
        Eli Cohen <eli@mellanox.com>, Siwei Liu <loseweigh@gmail.com>,
        Stephen Finucane <stephenfin@redhat.com>
Subject: [RFC PATCH 01/27] vhost: Add vhost_dev_can_log
Date: Fri, 20 Nov 2020 19:50:39 +0100
Message-Id: <20201120185105.279030-2-eperezma@redhat.com>
In-Reply-To: <20201120185105.279030-1-eperezma@redhat.com>
References: <20201120185105.279030-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Just syntactic sugar.

Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 hw/virtio/vhost.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v2 06/12] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?SsO8cmdlbiBHcm/Dnw==?= <jgross@suse.com>
X-Patchwork-Id: 11920165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC4F3C63798
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 11:47:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 77AC322253
	for <kvm@archiver.kernel.org>; Fri, 20 Nov 2020 11:47:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=suse.com header.i=@suse.com
 header.b="QP/BG5uj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728114AbgKTLq5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 20 Nov 2020 06:46:57 -0500
Received: from mx2.suse.de ([195.135.220.15]:56100 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727818AbgKTLqi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Nov 2020 06:46:38 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1605872796;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=6h75cJ6hW/g0BHQC3u27wm1+Z2/S1ONImoNRdCX4YvI=;
        b=QP/BG5ujOKxmmUSP7oXldFmPl9nNGKmTun/Fr3P44ouLG0mnuu7kt4LHiIIq7QjKsTJQKK
        mJcL8UWeRWXKkYvNYE4Cn2iJV/YzTxrtpbsaMihX4lL+BR1qg44fQqOYL9/u8+g6B0POMG
        4B2TjS0ZEcL9tb8rgc9CjC/PMRMxCzA=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id 10C79AD89;
        Fri, 20 Nov 2020 11:46:36 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        linux-kernel@vger.kernel.org, linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Cc: peterz@infradead.org, luto@kernel.org,
        Juergen Gross <jgross@suse.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>
Subject: [PATCH v2 06/12] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Fri, 20 Nov 2020 12:46:24 +0100
Message-Id: <20201120114630.13552-7-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201120114630.13552-1-jgross@suse.com>
References: <20201120114630.13552-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Due to include hell this requires to split out the time interfaces
into a new header file.

Signed-off-by: Juergen Gross <jgross@suse.com>
---
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       | 11 --------
 arch/x86/include/asm/paravirt.h       | 14 ----------
 arch/x86/include/asm/paravirt_time.h  | 38 +++++++++++++++++++++++++++
 arch/x86/include/asm/paravirt_types.h |  6 -----
 arch/x86/kernel/cpu/vmware.c          |  5 ++--
 arch/x86/kernel/kvm.c                 |  3 ++-
 arch/x86/kernel/kvmclock.c            |  3 ++-
 arch/x86/kernel/paravirt.c            | 16 ++++++++---
 arch/x86/kernel/tsc.c                 |  3 ++-
 arch/x86/xen/time.c                   | 12 ++++-----
 drivers/clocksource/hyperv_timer.c    |  5 ++--
 drivers/xen/time.c                    |  3 ++-
 kernel/sched/sched.h                  |  1 +
 14 files changed, 71 insertions(+), 50 deletions(-)
 create mode 100644 arch/x86/include/asm/paravirt_time.h

```
