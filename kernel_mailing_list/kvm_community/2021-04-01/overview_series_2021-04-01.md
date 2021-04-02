#### [PATCH 01/20] iommu: remove the unused domain_window_disable method
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12178607
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61337C43462
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:45:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 49CF36136D
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:45:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235143AbhDARmT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:42:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57160 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234407AbhDARhL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 13:37:11 -0400
Received: from bombadil.infradead.org (bombadil.infradead.org
 [IPv6:2607:7c80:54:e::133])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EEB29C02D56E;
        Thu,  1 Apr 2021 08:53:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20210309; h=Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender
        :Reply-To:Content-Type:Content-ID:Content-Description;
        bh=bDulEFC5ArmGy+DYIEUW3EiV2iZECmYjHEkGluCYUVw=;
 b=uX9/ysk2c5yNZPrgqGa+LKrjjY
        CPo31KIQUr5iR8POv/BJJzIxOsBj3AtcHQZT4ZYyRDhN2hPxaUMrv3ZC33WIurTNlhicSccdFRrhH
        iVY5u1L8eBe6Bpiic6KX6G1Qecb3vN2VQ2toNFRHLaf56VeoCaD2qtQpnJgff3H//8x/auMMo23XQ
        bb/e9JWW1DkIbrk8f/YNVPRIiP2baTSrHdR85H1vQSKFoJV3J4TG+fMefpid8PQ+VVnAS5LZsjokM
        v2KIT4oKfgvPo9nNvUERBun216Eab+LPm2LkfQDNmuLRxyFeHTMmfifogA4ZXzoCCyxui7lrErfSp
        swXXamBQ==;
Received: from [2001:4bb8:180:7517:83e4:a809:b0aa:ca74] (helo=localhost)
        by bombadil.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lRzd9-00CiZs-Pd; Thu, 01 Apr 2021 15:53:12 +0000
From: Christoph Hellwig <hch@lst.de>
To: Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Li Yang <leoyang.li@nxp.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
        David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        linuxppc-dev@lists.ozlabs.org, linux-arm-msm@vger.kernel.org,
        dri-devel@lists.freedesktop.org, freedreno@lists.freedesktop.org,
        iommu@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH 01/20] iommu: remove the unused domain_window_disable method
Date: Thu,  1 Apr 2021 17:52:37 +0200
Message-Id: <20210401155256.298656-2-hch@lst.de>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210401155256.298656-1-hch@lst.de>
References: <20210401155256.298656-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 bombadil.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

domain_window_disable is wired up by fsl_pamu, but never actually called.

Signed-off-by: Christoph Hellwig <hch@lst.de>
Acked-by: Will Deacon <will@kernel.org>
Acked-by: Li Yang <leoyang.li@nxp.com>
---
 drivers/iommu/fsl_pamu_domain.c | 48 ---------------------------------
 include/linux/iommu.h           |  2 --
 2 files changed, 50 deletions(-)

```
#### [PATCH 1/2] kvm: update kernel headers for KVM_GUESTDBG_BLOCKEVENTS
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178621
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60218C43462
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:48:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4631D61155
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:48:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236813AbhDARrZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:47:25 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21620 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236247AbhDARoN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:44:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299053;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=rU3RIc7ZbPs0ZRexkYqTMuHou64+ARL6X0Qz2sJLr4c=;
        b=bVlmHUkJoIBN6AaDwOfB1SiGZ9C/qye5dFZM/JaAF3uxFs6V5n8sINHpaf2CnB7c1YItf7
        97bx4v6U22l3I5Y7ucoO1igAUW8/6PYBkpYqRiaPECt8f30CZSw7sywRI7O9bGbH115fsf
        TIrwdtHorrLT0H75TDsGDasIpffIDhg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-198-CuC3XtW2Mw2ABQ37Qga5OQ-1; Thu, 01 Apr 2021 10:42:02 -0400
X-MC-Unique: CuC3XtW2Mw2ABQ37Qga5OQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CEE24817473;
        Thu,  1 Apr 2021 14:41:57 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BD7245D6B1;
        Thu,  1 Apr 2021 14:41:55 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, kvm@vger.kernel.org,
 Cornelia Huck <cohuck@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] kvm: update kernel headers for KVM_GUESTDBG_BLOCKEVENTS
Date: Thu,  1 Apr 2021 17:41:51 +0300
Message-Id: <20210401144152.1031282-2-mlevitsk@redhat.com>
In-Reply-To: <20210401144152.1031282-1-mlevitsk@redhat.com>
References: <20210401144152.1031282-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 linux-headers/asm-x86/kvm.h | 2 ++
 linux-headers/linux/kvm.h   | 1 +
 2 files changed, 3 insertions(+)

```
#### [PATCH v4 05/25] x86/sgx: Introduce virtual EPC for use by KVM guests
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12177657
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 57C74C43462
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 09:44:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02A2C610CE
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 09:44:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233670AbhDAJna (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 05:43:30 -0400
Received: from mga01.intel.com ([192.55.52.88]:8037 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233491AbhDAJnN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 05:43:13 -0400
IronPort-SDR: 
 lOAzvlBqoZlKHyAXWcEKoUwjHNDaBRYPambg6sbjQbG9vfWrrfVpQaNIb8fNHZ+a3VEi0/id49
 M8FEJo1RmjRg==
X-IronPort-AV: E=McAfee;i="6000,8403,9940"; a="212459834"
X-IronPort-AV: E=Sophos;i="5.81,296,1610438400";
   d="scan'208";a="212459834"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Apr 2021 02:43:09 -0700
IronPort-SDR: 
 vhgVBikSwjoD6OXK1ANagg9C63GHr8928Wzot3CCNjM/qXNEPPbR+bMNsyb9CVf+NVpcxOoloy
 Pk6lpiM76uTg==
X-IronPort-AV: E=Sophos;i="5.81,296,1610438400";
   d="scan'208";a="517275442"
Received: from aemorris-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.254.67.39])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Apr 2021 02:43:05 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH v4 05/25] x86/sgx: Introduce virtual EPC for use by KVM guests
Date: Thu,  1 Apr 2021 22:42:44 +1300
Message-Id: 
 <189097b8ea95de231c7dd6e009060d4acebb1963.1617268051.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: 
 <0c38ced8c8e5a69872db4d6a1c0dabd01e07cad7.1616136308.git.kai.huang@intel.com>
References: 
 <0c38ced8c8e5a69872db4d6a1c0dabd01e07cad7.1616136308.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Add a misc device /dev/sgx_vepc to allow userspace to allocate "raw" EPC
without an associated enclave.  The intended and only known use case for
raw EPC allocation is to expose EPC to a KVM guest, hence the 'vepc'
moniker, virt.{c,h} files and X86_SGX_KVM Kconfig.

SGX driver uses misc device /dev/sgx_enclave to support userspace to
create enclave.  Each file descriptor from opening /dev/sgx_enclave
represents an enclave.  Unlike SGX driver, KVM doesn't control how guest
uses EPC, therefore EPC allocated to KVM guest is not associated to an
enclave, and /dev/sgx_enclave is not suitable for allocating EPC for KVM
guest.

Having separate device nodes for SGX driver and KVM virtual EPC also
allows separate permission control for running host SGX enclaves and
KVM SGX guests.

To use /dev/sgx_vepc to allocate a virtual EPC instance with particular
size, the userspace hypervisor opens /dev/sgx_vepc, and uses mmap()
with the intended size to get an address range of virtual EPC.  Then
it may use the address range to create one KVM memory slot as virtual
EPC for guest.

Implement the "raw" EPC allocation in the x86 core-SGX subsystem via
/dev/sgx_vepc rather than in KVM. Doing so has two major advantages:

  - Does not require changes to KVM's uAPI, e.g. EPC gets handled as
    just another memory backend for guests.

  - EPC management is wholly contained in the SGX subsystem, e.g. SGX
    does not have to export any symbols, changes to reclaim flows don't
    need to be routed through KVM, SGX's dirty laundry doesn't have to
    get aired out for the world to see, and so on and so forth.

The virtual EPC pages allocated to guests are currently not reclaimable.
Reclaiming EPC page used by enclave requires a special reclaim mechanism
separate from normal page reclaim, and that mechanism is not supported
for virutal EPC pages.  Due to the complications of handling reclaim
conflicts between guest and host, reclaiming virtual EPC pages is
significantly more complex than basic support for SGX virtualization.

Also add documenetation to explain what is virtual EPC, and suggest
users should be aware of virtual EPC pages are not reclaimable and take
this into account when deploying both host SGX applications and KVM SGX
guests on the same machine.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Co-developed-by: Kai Huang <kai.huang@intel.com>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
v3->v4:
 - Added documentation to explain virtual EPC, and suggest user what to do if
   user wants to run both host SGX apps and KVM SGX guests, since EPC pages
   assigned to guest is not reclaimable.
 - Added one paragraph in commit msg to say Documentation has been updated.
 - Changed to use EREMOVE_ERROR_MESSAGE in sgx_vepc_free_page().

---
 Documentation/x86/sgx.rst        |  16 ++
 arch/x86/Kconfig                 |  12 ++
 arch/x86/kernel/cpu/sgx/Makefile |   1 +
 arch/x86/kernel/cpu/sgx/sgx.h    |   9 ++
 arch/x86/kernel/cpu/sgx/virt.c   | 259 +++++++++++++++++++++++++++++++
 5 files changed, 297 insertions(+)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c

```
#### [PATCH v4 1/8] KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12177539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 35D52C433ED
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 08:53:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8443610C7
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 08:53:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233701AbhDAIxP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 04:53:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:47687 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233024AbhDAIwv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 04:52:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617267171;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=uFDgWrjWMSMk4v/p6l+GMMcTkNEPFqFBG4PiCpy+Kw0=;
        b=d/wuCJFZYv0UnnB3OHCMqfXX09C9hyig/1F4xlb0VXkBW+vC+Tq62JdwKWue3gEZ7eU9St
        nZcisXiv0fyM2nWl6g1U2fUCNm4+9ywWSZUp6YBBjhMovPXSDxOF6FW+y+jv6oyDTZALSG
        T5WSCq2IqpAuNCsarT56QrRRyfkdDGM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-278-p5EPH6ZUNQKtzQKx8K0sdQ-1; Thu, 01 Apr 2021 04:52:47 -0400
X-MC-Unique: p5EPH6ZUNQKtzQKx8K0sdQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 71D751005D54;
        Thu,  1 Apr 2021 08:52:46 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-13.ams2.redhat.com [10.36.112.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 692A45D9CC;
        Thu,  1 Apr 2021 08:52:43 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com
Cc: james.morse@arm.com, suzuki.poulose@arm.com, shuah@kernel.org,
        pbonzini@redhat.com
Subject: [PATCH v4 1/8] KVM: arm64: vgic-v3: Fix some error codes when setting
 RDIST base
Date: Thu,  1 Apr 2021 10:52:31 +0200
Message-Id: <20210401085238.477270-2-eric.auger@redhat.com>
In-Reply-To: <20210401085238.477270-1-eric.auger@redhat.com>
References: <20210401085238.477270-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_DEV_ARM_VGIC_GRP_ADDR group doc says we should return
-EEXIST in case the base address of the redist is already set.
We currently return -EINVAL.

However we need to return -EINVAL in case a legacy REDIST address
is attempted to be set while REDIST_REGIONS were set. This case
is discriminated by looking at the count field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

v1 -> v2:
- simplify the check sequence
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 15 +++++++--------
 1 file changed, 7 insertions(+), 8 deletions(-)

```
#### [PATCH v2 1/9] scripts/gdb: rework lx-symbols gdb script
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178871
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 74AADC43461
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:02:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55E2C611BD
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:02:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236316AbhDASCS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 14:02:18 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29947 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236560AbhDAR6C (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:58:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299882;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/dm8QNSV3W7Q2lqn5B08UjvbkkAU4JlmGE1UT9JWvOc=;
        b=FTqQx+kfblLSKw7Q4+/P86WRGaLZHih6IuxmZwqTOoC97GmugjZuIBacqheFekb7FTTfF+
        pfkn/O/0MjffFHO4pjwcmc3biOOsfHtSP75aktF8+2ad10OpNUMeW6xObcVtLbUP7gT3Gr
        J68UtY0wLxomCn87cY/k4AXDq1R1Ghc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-254-yq_OfL5MPOGvWLd5Bn-5ug-1; Thu, 01 Apr 2021 09:55:29 -0400
X-MC-Unique: yq_OfL5MPOGvWLd5Bn-5ug-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 368F41084CA4;
        Thu,  1 Apr 2021 13:55:11 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0E0395D6B1;
        Thu,  1 Apr 2021 13:55:02 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Ingo Molnar <mingo@redhat.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <seanjc@google.com>,
        Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        linux-kernel@vger.kernel.org (open list),
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Jonathan Corbet <corbet@lwn.net>, Jessica Yu <jeyu@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Jan Kiszka <jan.kiszka@siemens.com>,
        Will Deacon <will@kernel.org>,
        kvmarm@lists.cs.columbia.edu (open list:KERNEL VIRTUAL MACHINE FOR
        ARM64 (KVM/arm64)), Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Joerg Roedel <joro@8bytes.org>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Jim Mattson <jmattson@google.com>,
        Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org (open list:S390),
        Heiko Carstens <hca@linux.ibm.com>,
        Kieran Bingham <kbingham@kernel.org>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION),
        linux-arm-kernel@lists.infradead.org (moderated list:KERNEL VIRTUAL
        MACHINE FOR ARM64 (KVM/arm64)), James Morse <james.morse@arm.com>
Subject: [PATCH v2 1/9] scripts/gdb: rework lx-symbols gdb script
Date: Thu,  1 Apr 2021 16:54:43 +0300
Message-Id: <20210401135451.1004564-2-mlevitsk@redhat.com>
In-Reply-To: <20210401135451.1004564-1-mlevitsk@redhat.com>
References: <20210401135451.1004564-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix several issues that are present in lx-symbols script:

* Track module unloads by placing another software breakpoint at
  'free_module'
  (force uninline this symbol just in case), and use remove-symbol-file
  gdb command to unload the symobls of the module that is unloading.

  That gives the gdb a chance to mark all software breakpoints from
  this module as pending again.
  Also remove the module from the 'known' module list once it is unloaded.

* Since we now track module unload, we don't need to reload all
  symbols anymore when 'known' module loaded again
  (that can't happen anymore).
  This allows reloading a module in the debugged kernel to finish
  much faster, while lx-symbols tracks module loads and unloads.

* Disable/enable all gdb breakpoints on both module load and unload
  breakpoint hits, and not only in 'load_all_symbols' as was done before.
  (load_all_symbols is no longer called on breakpoint hit)
  That allows gdb to avoid getting confused about the state of the
  (now two) internal breakpoints we place.
  Otherwise it will leave them in the kernel code segment, when
  continuing which triggers a guest kernel panic as soon as it skips
  over the 'int3' instruction and executes the garbage tail of the optcode
  on which the breakpoint was placed.

* Block SIGINT while symbols are reloading as this seems to crash gdb.
  (new in V2)

* Add a basic check that kernel is already loaded into the guest memory
  to avoid confusing errors.
  (new in V2)

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 kernel/module.c              |   8 +-
 scripts/gdb/linux/symbols.py | 203 +++++++++++++++++++++++------------
 2 files changed, 143 insertions(+), 68 deletions(-)

```
#### [PATCH 1/4] KVM: x86: pending exceptions must not be blocked by an injected event
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 479B7C43617
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:43:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 247ED61284
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:43:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235664AbhDARnF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:43:05 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:55662 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234879AbhDARlC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:41:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617298862;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=vyMr3QsOTroXcgjRtUdx7Du8y9HMmuw3i24kPeKgTH4=;
        b=UHSK70C492TvpRcA0lqKu2Hc6kpLnsc0ij9XZ3CSuswQW2Cxx1HgQLNitosZwepeOR9W0Y
        c5juV6oTIUabVUcJ/XP/4JSoUnhfE4xEuQKOuvUhomXLA8eUC/olmFwnDi+781bC39dLPN
        fusSJ8dfJ/3p7fkrDRZ90cdqWKjv/90=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-160-e6V2UZJlPB-u618cERGpDg-1; Thu, 01 Apr 2021 10:39:30 -0400
X-MC-Unique: e6V2UZJlPB-u618cERGpDg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D39B784B99E;
        Thu,  1 Apr 2021 14:38:25 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 86BB45D9CA;
        Thu,  1 Apr 2021 14:38:22 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Sean Christopherson <seanjc@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/4] KVM: x86: pending exceptions must not be blocked by an
 injected event
Date: Thu,  1 Apr 2021 17:38:14 +0300
Message-Id: <20210401143817.1030695-2-mlevitsk@redhat.com>
In-Reply-To: <20210401143817.1030695-1-mlevitsk@redhat.com>
References: <20210401143817.1030695-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Injected interrupts/nmi should not block a pending exception,
but rather be either lost if nested hypervisor doesn't
intercept the pending exception (as in stock x86), or be delivered
in exitintinfo/IDT_VECTORING_INFO field, as a part of a VMexit
that corresponds to the pending exception.

The only reason for an exception to be blocked is when nested run
is pending (and that can't really happen currently
but still worth checking for).

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c |  8 +++++++-
 arch/x86/kvm/vmx/nested.c | 10 ++++++++--
 2 files changed, 15 insertions(+), 3 deletions(-)

```
#### [PATCH v17 01/17] RISC-V: Add hypervisor extension related CSR defines
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 12178959
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8FFF9C43616
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:06:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A3FA610C7
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:06:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235735AbhDASGv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 14:06:51 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:59599 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237414AbhDAR76 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 1 Apr 2021 13:59:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1617299999; x=1648835999;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:content-transfer-encoding:mime-version;
  bh=vumkxA54k8bzMPc+ScIMUROu21oDKZ744XYCE6mvFR8=;
  b=NwUcZTj8rKNFSqO6pK5/stidhO1S/RfY42NWkRk3vDhXq8DKwD91o7LS
   VJclrZiciQVUzcu5Vq3pxgr1n0/QyV690evJW40veB29FxbSDU04OaWq8
   N2rysOIBkiVSxjY4SnU5UzgmylOE9YILb9+AybFJp5Elamm09IOX7+lBX
   qcMC4RdNhgUfW+i7ikiVUvmCfJAjTgLshcjvP5t42xJNabc61wRXFyuH5
   uEw9CMBLXEz6/TKaEF5+yR+GjE1IHxoDsUfHmZbpTTzrdamqtkxGr2kMa
   YNm6OS7xGAks4jLQB5YKiI3IvrL9yz4733mMtkwWqNtPf91yNh7uWQhHg
   Q==;
IronPort-SDR: 
 OY7+8wGJdmn/qYaD3iA8PKPDYr0YBDzAUvvcl6gxHAyRFmmxWFUPvcvdHhW1Kf2NP9pZa6G4vJ
 YWzS0KeZ9bC3rzaguNNUqidivWwHQv5Es476/uuDxgnw6lVVJ3zwdHNUttlEz9JdYHbwNaeDdE
 Ksi5PB6uYpZDKnXnA+5UC9uKLp3NCarRMR340o6ZlSVlo9VoH5iUe5tnaNqsEPmJAQjjMTb4WE
 jN+UWjdqjGvMPTWXO+F3Q5YWGLD3rZdtAa1RTr3AaSHQuUziiW+xZXu7Neic7gG5PUD1FKeKNB
 9fE=
X-IronPort-AV: E=Sophos;i="5.81,296,1610380800";
   d="scan'208";a="163447197"
Received: from mail-dm3nam07lp2045.outbound.protection.outlook.com (HELO
 NAM02-DM3-obe.outbound.protection.outlook.com) ([104.47.56.45])
  by ob1.hgst.iphmx.com with ESMTP; 01 Apr 2021 21:35:39 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=aZMg8HQV48oOfntnWdwIsPYgy5cVTn1ljQWOAur9bzgdDuAwYAp6/cuUHIzHRrdt/oM8Pn26CHum6CS6kjoLqTaJ7P8gwgiGwzyAwyy1/PKE39Nz4Bjpi2BsUyErFyL03i1zC/pXSq6eYaQaS5uETiPmZLhZi/D9+oIaDETq/buisvDTT4VsZ21ikbpaQAXBHSS6tymhRYmumRYOqSdZaPn6oNVh2xxNTtS8Vtt3Wp8/e7g6IaCJcJle6HhQSCWlX6WycZAxRkpaIVQQ/kaWTuAQPcbXbPUPENsDMjj5prehP0XR0FW0QDNS7lbi5LaB1AmMLu7lB7nDFzcApx0fpA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WMFbBdH20e9gmuUIgGAsu8DFOU20JzHlhs9rWAYeIQk=;
 b=kimfkAhw1sLSbdBQTgX/sIO7QJUwSKS4IQynEhFSBl6FsEj33IjP+rPtfA7sZTWvOy+L0GS8GEOAxodydUanq8ReW7gjvT9m/tsju+hxAboTmVie9OoRF2oJbBh5wjOomE38WG9GaDtFLqKqxJXEXsl2c8HT5B6eVv/Rqe96+qN0h9mKZ6Xhx056I3LKCuEYpVPqEaFjenul6N+m2UMImHoGLwOhPDI4N2fEuwCZ5400A2nQN9IV7y1MdiEzxM5R4lGdy+Fw4zoCAvTrDUiuhRIrViC/PtkXYdcA4thRU7SMD68ncl39hR0kNVSdSZ2dow6lOM6VVcjWdTsO1PXZVA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WMFbBdH20e9gmuUIgGAsu8DFOU20JzHlhs9rWAYeIQk=;
 b=nZdXft0JCtEKBChIcDgxqR4V7d0p9IfNpG1sPpWreCAG8UbDeKJsj/fufMof6QknVnKJN1ZwIoYkPEBFEs2gyu6FrHruQq/ghIPLsThpopydg93H63VlJ0bRuQPt68uLK3NeRA2qVanlAOMLgOgXYEYzkUacSheQGsLHDRd427Y=
Authentication-Results: dabbelt.com; dkim=none (message not signed)
 header.d=none;dabbelt.com; dmarc=none action=none header.from=wdc.com;
Received: from DM6PR04MB6201.namprd04.prod.outlook.com (2603:10b6:5:127::32)
 by DM6PR04MB3865.namprd04.prod.outlook.com (2603:10b6:5:ac::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28; Thu, 1 Apr
 2021 13:35:33 +0000
Received: from DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::38c0:cc46:192b:1868]) by DM6PR04MB6201.namprd04.prod.outlook.com
 ([fe80::38c0:cc46:192b:1868%7]) with mapi id 15.20.3977.033; Thu, 1 Apr 2021
 13:35:33 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Palmer Dabbelt <palmerdabbelt@google.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <damien.lemoal@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org,
        linux-kernel@vger.kernel.org, Anup Patel <anup.patel@wdc.com>
Subject: [PATCH v17 01/17] RISC-V: Add hypervisor extension related CSR
 defines
Date: Thu,  1 Apr 2021 19:04:19 +0530
Message-Id: <20210401133435.383959-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210401133435.383959-1-anup.patel@wdc.com>
References: <20210401133435.383959-1-anup.patel@wdc.com>
X-Originating-IP: [122.179.112.210]
X-ClientProxiedBy: MA1PR01CA0104.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:1::20) To DM6PR04MB6201.namprd04.prod.outlook.com
 (2603:10b6:5:127::32)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (122.179.112.210) by
 MA1PR01CA0104.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00:1::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28 via Frontend
 Transport; Thu, 1 Apr 2021 13:35:18 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 62b32f04-dece-4653-de90-08d8f5130637
X-MS-TrafficTypeDiagnostic: DM6PR04MB3865:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR04MB38650249BED103895ED2AD1F8D7B9@DM6PR04MB3865.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:11;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Eb+TD7uiuH6SZKkgTa/TFh4SFX9jkwqya7PR0Lpm97R2V2P06XQiQt21dbkhgsupkE7+ogsVsNyCErtpaJnN84GSy9uo0HidMa7Ce2U+ekz3PphnvS+aIJXbi+GJj3h6Z1bypbtD14NBp7mhFxGISjn6AgEw5w9YLIHiHWVBJH/UmGhM6lQXeIlCe7frVszm+7ZEeYED53ypIUczmR+NHC0Sq/hGPut4+cfhMgeBFGs7uiG+f5aUh2IRs1KS3YXuQMEtf/nJVwkqQqFzDuTaqHND2cP8jSoDXLwwddHnpHcRIxrMG+36J/mfYfsjmfCnWZfRMseHanSJ3sbS0P/4Ksna4rnRb7+gIoXKglAyMnfic3E6zUpXnP4tsmmWlDovmMxrT/ccvqZeQMFgIGUs5iUlTdfjgvJHo+lsxRCAPFZs2Jm+cILTWYTzL2tUfCbkbXDgGazk3AAJr9naLNkfJTY9S0uvOiAc0sqJTYrW0BCrx3yiGeHDlMbbDZo/AgQnN2vMy5UVNQIIcNMMQ18kVNizp/IubnFD0WHnRZ834Q+Urjj4mDym82PH+1DkxV2D2cinju22RCcSlq93uKnjrtxvKFJWqerNC02RXHMijV8pSy2LdA6D8x882RrCRdj1GI53HN8WPZUWacZfHj2d6GNi1ZbRkrxHo6GeSphpQCo=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR04MB6201.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(396003)(136003)(376002)(366004)(39860400002)(36756003)(55016002)(26005)(2906002)(83380400001)(66556008)(66476007)(5660300002)(66946007)(7416002)(186003)(16526019)(7696005)(956004)(2616005)(8886007)(38100700001)(8936002)(52116002)(44832011)(54906003)(110136005)(8676002)(316002)(86362001)(4326008)(1076003)(478600001);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 jgLO8nSWkrsDLfY1c4luFAMI1aEo27QJTaKcE9QCvHi6H7UuOcCNuVXkNcqNSEXu2DdWzJaVTGkPGUJHbgDZPJ3gKmFHmpph6ghX3jOWrTAXVabSNqnz25hoJC3pPSlQM6fQGCjqBJB+9agXDUDGjVGrDFwNO6aeMYOinJnV89BkLELBz9KVSDgYbP7Sar4LEJy+9oinfOfae6mffTPKh/RXMSmSySk19/O3c55SNI3L3YBy0t7L0kDOJh3YCWKenrtX7gZX7UgrycO3EZOw9NEwEhxxpILMdzAh+t5h1z+OF39irwSAyRSc/iLN26MFdoxfEFHWX3bKpVsymjZUcbFINEDELq5Q7JvGfaCo6s0/iy+GRnfugPWadpXz0Za1SmxYUJw9GBNvzShQd+UuONWO3AkHksz8edYxNCkk45pAIXEXwTFgh5l/ycKmuNY5QufklU8HzG7KdU5FL+bDc4IoUFpkKoiss6ZKoUnjvKEbY7kJWGiW3o6PDbu/BMVzlLHhc7DhtTBsOu08ji12+YX90BXT70rH2jCzvMgHAaftdlTGLngg9qAGl04iflP2z+yha3Ek91AElDigrExzT1lpT4RLRsxWStOUDiIEkB2kGFjX5dRgAJmxbYE0v7MbihA4R1Fas9theVD4twCPIOWvH/Yaa/G06KloMln3SL2yruSuCyB9w8/01W/cDe1j0UXPP03Z97SKxiMsKlrFFA7QYB5L4ns3Qvr8FoNM6+WWuxEYhYGcHsctrOZp+uRfiy7Dsv0UdxMmsZLxUDVqJ5M6wBwy4fCSNcevsIDylwVtgxIYz5WzyGIKI2Fo97pqWZy4M1c3bHtEB+Ja4HfJ4/wNbcj/JZ1WmgDBtz1PeHRT31ETU2Z25jTbKTzfimth1XSevStLZGjkj2NMCCq4afIFGGvYEcBqM9/UMBNj98aR79hP5yVcxsujJMTikh7kMh9W2qTnWGZYBSoY79i187i6QUJgrqd62o90FtP6V6jSpABJEqFoyeMmL4mr9Ok6YuIuSJg0De6/RO6Qk1CVAQWmqBYpT8bMm1NnaPaCzNdO7EZaAtbkF9nlDBVScThDI6FX0tRpQdyWicNxrsAzvSJ6biEnABdtQb/6E0Ba/UFUXkQvwrndnadQqvnLmk6/c7eNd16kli5/vsJ92Gq1Z0Bx9CYxoGQR1DIz/PcfMLQM8ouZfe/bS7pgA2KUuHpzQO7ccwHT5QFsR/5Bh9xkSYUx/rL7RjZe6gCgl5p3qAZSVaexOjpI7UvhrR9X6H+p3yy8M/UE6ooBGuxQKcVbII42QVCAUicgsHZOG2Kj1eaBBRmB1ua5/10NKiTwG0vsnhTgAnDX5kZXEWjZwqSJPw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 62b32f04-dece-4653-de90-08d8f5130637
X-MS-Exchange-CrossTenant-AuthSource: DM6PR04MB6201.namprd04.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 01 Apr 2021 13:35:33.5680
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 +pQZpyP8hzdlu9jKQv3sNKgT9px2kRNJ+Pf974YvDiT10CJjTNcY/GWkXB4o6kig8xkpoCT3HWWYUEYxbzjYcQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR04MB3865
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch extends asm/csr.h by adding RISC-V hypervisor extension
related defines.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 arch/riscv/include/asm/csr.h | 89 ++++++++++++++++++++++++++++++++++++
 1 file changed, 89 insertions(+)

```
#### [PATCH kvm-unit-tests] x86: msr: test vendor-specific behavior for MSR_IA32_SYSENTER_ESP and MSR_IA32_SYSENTER_EIP
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12178873
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 985B2C433ED
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:02:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6AB4E61130
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 18:02:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235414AbhDASCX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 14:02:23 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:24905 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235986AbhDAR6L (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:58:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299890;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=MqiD/niNzs8sPdCIMyr36j8rRSsuwo1vckKf82UwdpU=;
        b=EtRR1FaQ7n2jde3ICyjYWn0q3XBhfPUT7Vufza2ukRFZnaaj4VPLeZhP6Y6k4tqu/Vrij7
        bDH0bO+PJz63jnht1dHI7nwDqmJmPrFhjs3oJYr1jEZ0FyEVSuMLpoz85hLbQWkZPgHkSk
        cKwmmyUl49OQJQr4Jsms9ZdYmQPPA+E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-581-ANfHcb41OpqlxX3p4ARpgQ-1; Thu, 01 Apr 2021 09:55:27 -0400
X-MC-Unique: ANfHcb41OpqlxX3p4ARpgQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 128CC1084D94
        for <kvm@vger.kernel.org>; Thu,  1 Apr 2021 13:55:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D4131424D
        for <kvm@vger.kernel.org>; Thu,  1 Apr 2021 13:55:14 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: msr: test vendor-specific behavior for
 MSR_IA32_SYSENTER_ESP and MSR_IA32_SYSENTER_EIP
Date: Thu,  1 Apr 2021 09:55:14 -0400
Message-Id: <20210401135514.1095274-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These MSRs are only 32 bits wide on AMD processors, and KVM will emulate
this starting with Linux 5.12.  Add support for this in the msr.flat
test.

Unfortunately QEMU does not have this behavior, so we have to disable the
tests in CI.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 .gitlab-ci.yml                |  6 ++--
 ci/cirrus-ci-fedora.yml       |  1 -
 ci/cirrus-ci-macos-x86-64.yml |  1 -
 lib/x86/processor.h           | 20 ++++++++++++
 x86/msr.c                     | 59 +++++++++++++++++++++++++----------
 5 files changed, 65 insertions(+), 22 deletions(-)

```
#### [PATCH 1/2] kvm: update kernel headers for KVM_{GET|SET}_SREGS2
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178687
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88F97C433ED
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:53:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6696460FF3
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:53:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235856AbhDARxY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:53:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43650 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235248AbhDARrI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:47:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299227;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=UuqX1vaXGK/rRIbLo5826fQo7T0UET7bCEj3dtAWeOc=;
        b=IBXTIT0Mc7+FiXvO06mIaQbK1Q0sjJOQQFsXA223UamnbbwjDiC5SAU92E3BggalHkjYjq
        6DVEK6qAHl9uF/i5i7pLqnWXPwwujlW1xQW+ZmW0Sazzuidx+5jZPgKjjAFXF78J7zEMz5
        Orb8PLDWBYfRs9t1KOOFDb/rILZE9m0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-203-xZzA3Ac2M0ewcgkKFRjlbQ-1; Thu, 01 Apr 2021 10:46:11 -0400
X-MC-Unique: xZzA3Ac2M0ewcgkKFRjlbQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E30A88015B6;
        Thu,  1 Apr 2021 14:45:51 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9F96A5C8AA;
        Thu,  1 Apr 2021 14:45:49 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <richard.henderson@linaro.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] kvm: update kernel headers for KVM_{GET|SET}_SREGS2
Date: Thu,  1 Apr 2021 17:45:44 +0300
Message-Id: <20210401144545.1031704-2-mlevitsk@redhat.com>
In-Reply-To: <20210401144545.1031704-1-mlevitsk@redhat.com>
References: <20210401144545.1031704-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 linux-headers/asm-x86/kvm.h | 13 +++++++++++++
 linux-headers/linux/kvm.h   |  5 +++++
 2 files changed, 18 insertions(+)

```
#### [PATCH 1/2] KVM: x86: add guest_cpuid_is_intel
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178613
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_NONE
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 48E1BC43619
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:47:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01D576112E
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:47:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236380AbhDARrH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:47:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33751 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235223AbhDARm0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:42:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617298946;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=FIS/0wQGTd5OK3BSslmwGX7RkKLHKjJnfRIzlG6zbaM=;
        b=V29QjL5AGlfYxOZsKL7ipNev9ipJUHXCvFQejsOHPGdxJlHM9p/nlY43zQLVRJaQNiW9ym
        /BM5ILTiJ/jK9Hs2J+Pgio8yI6coTILfd8xxDojkvLw6uLj93tOeYJmDjFiB3RxJSOyVXy
        2xM5mK+BYtu82J4ullOCwf0Y6DrUR0s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-256-8mIH6vSUOoe_4kFyAEEnQg-1; Thu, 01 Apr 2021 07:16:25 -0400
X-MC-Unique: 8mIH6vSUOoe_4kFyAEEnQg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3787E8030C9;
        Thu,  1 Apr 2021 11:16:24 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4293B1378E;
        Thu,  1 Apr 2021 11:16:20 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Thomas Gleixner <tglx@linutronix.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] KVM: x86: add guest_cpuid_is_intel
Date: Thu,  1 Apr 2021 14:16:13 +0300
Message-Id: <20210401111614.996018-2-mlevitsk@redhat.com>
In-Reply-To: <20210401111614.996018-1-mlevitsk@redhat.com>
References: <20210401111614.996018-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is similar to existing 'guest_cpuid_is_amd_or_hygon'

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/cpuid.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v2 1/2] KVM: x86: add guest_cpuid_is_intel
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12178783
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 490DCC433ED
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:53:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 12FDA61139
	for <kvm@archiver.kernel.org>; Thu,  1 Apr 2021 17:53:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236086AbhDARxq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 1 Apr 2021 13:53:46 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:27886 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237272AbhDARvN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 1 Apr 2021 13:51:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617299472;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=FIS/0wQGTd5OK3BSslmwGX7RkKLHKjJnfRIzlG6zbaM=;
        b=OYmka3utoOkydLxvmY/rLcaliMdQfBiZa48epWfgW/wxeh/7/C67cs7jtrpVJ6fVN99VPt
        Tl2aOA9qs2A6OZ3VFx649Ua/Am5vNl6CvOay/iiyUe1fyDzpkQSZCTk6QRxRsZG8PE+Cpf
        FH5wUJDogEDJa0l14zD+X9/dM9PsFEk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-586-IBYy-VNRN3KYZxwmugfmAg-1; Thu, 01 Apr 2021 07:19:37 -0400
X-MC-Unique: IBYy-VNRN3KYZxwmugfmAg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4E6FD800D53;
        Thu,  1 Apr 2021 11:19:36 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 070F25F9B8;
        Thu,  1 Apr 2021 11:19:32 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/2] KVM: x86: add guest_cpuid_is_intel
Date: Thu,  1 Apr 2021 14:19:27 +0300
Message-Id: <20210401111928.996871-2-mlevitsk@redhat.com>
In-Reply-To: <20210401111928.996871-1-mlevitsk@redhat.com>
References: <20210401111928.996871-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is similar to existing 'guest_cpuid_is_amd_or_hygon'

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/cpuid.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
