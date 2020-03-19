#### [PATCH v14 Kernel 1/7] vfio: KABI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11445879
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7C45D90
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 20:14:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 488A12077A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 20:14:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="roSMOVFg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726839AbgCRUOz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 16:14:55 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:11661 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726822AbgCRUOz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Mar 2020 16:14:55 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e7280db0000>; Wed, 18 Mar 2020 13:13:15 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 18 Mar 2020 13:14:52 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 18 Mar 2020 13:14:52 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 18 Mar
 2020 20:14:52 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 18 Mar 2020 20:14:45 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v14 Kernel 1/7] vfio: KABI for migration interface for device
 state
Date: Thu, 19 Mar 2020 01:11:08 +0530
Message-ID: <1584560474-19946-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1584560474-19946-1-git-send-email-kwankhede@nvidia.com>
References: <1584560474-19946-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1584562395; bh=0ZjfEcEiUXBdRywKyc/OSpDD6GbPXaTampjnU8oIFR4=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=roSMOVFgc+UaeDyDASVzwqN56UkjOdygerFPVKhmE0MzDltyIMAykEm5R3SXmnaob
         RpMmP0Q3LFAAjIZTWN78pYRPswghM4piADOOvzU1dBbocn7TpbPQrs+wAdDiTBokzc
         RuTgmErKixEw7cszp+M6lCdd/7nTAKvlKrEAdVKfwfyiazwaJdx6464V3RFE/l43qs
         kMx5vx/nEI/ugUQdM0phtSBaRBxFfIRGx3YUfV3RuuHrcqbr6+3k1a1SURY43SCCrr
         pXRaQFDshagXHpCrYuqp20cQePoYxsd19/IudvQ6BPdWAjNacJXK4aTj3U8jdrMDGv
         AgMbrqoyTFHLw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 227 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 227 insertions(+)

```
#### [PATCH v7 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11445697
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D75214DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 16:37:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6C7BE20768
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 16:37:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f1S2ZcGb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727144AbgCRQhk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 12:37:40 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:31286 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726780AbgCRQhj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Mar 2020 12:37:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584549458;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=f1S2ZcGb/eznpxnamB2o67jeD9sm+wmL3Tt8CgNwexV8q3xaG9DP2aw69JXiSFbX7aRB+C
        IGT+0IPn78wOv6VHGtZGoh4UajG1DTQLl1wV2LvKgmB9VEnY3Nz7t4aXsRrURN2tKA3Vhk
        trfWPrnyo3STXmB1No3SAEvYs9bKOww=
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-412-fkYh-RI7Pde95Oqop3DYnw-1; Wed, 18 Mar 2020 12:37:37 -0400
X-MC-Unique: fkYh-RI7Pde95Oqop3DYnw-1
Received: by mail-wr1-f71.google.com with SMTP id t10so6313230wrp.15
        for <kvm@vger.kernel.org>; Wed, 18 Mar 2020 09:37:36 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=NprzEmCqXT6Vgx05Bag9qdQtDSrLAVNfxGtaCpmKZSR3o406GEwwlrB1MmwC99Wn81
         XBtY4IPJnITWPb42WFizmApcnxarNZmYnEEiiecMy8Nr35HfDOKc8R/RShay0OXTV1nG
         iv501pYHOtUJ6sSSg2nBl2Il2eiQ6JAKehz3GH53F7t0AmwhfOX37OIddUT9EwGABDpS
         9uLzHQ8XNioOlvxQPjXpbbP6DWx3xJb1gwRdCap/ZsMwG54lTtD8qt9V0aB8ncqxYhlG
         4eIVUTjNhmLANN8dgIRlVlcjJRM972uYRnRTme+tOxPjbcF/rh/AE7iuoa1aO4ub4OVc
         FWIQ==
X-Gm-Message-State: ANhLgQ2VSNDHdtJKuOk79NFqKLCHwdWrUVgUQsXZ0ylbz+612IdU013z
        FGv0bIx+vSFzoIeC7RecPTT/AEaERJifyfSTIdyYhr4NhREsVmxBGoEHpG+isKYF4/0V9K5pzKI
        dyr34DP2nJC1O
X-Received: by 2002:a7b:c159:: with SMTP id z25mr6176868wmi.102.1584549454928;
        Wed, 18 Mar 2020 09:37:34 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vtaqPeKFAd0yJQbAvVJ4mrbLJ6/dwU/B+4yuG+/8bXFj+8dfwUAPMZMNYYT/9jRyaygaGLA2Q==
X-Received: by 2002:a7b:c159:: with SMTP id z25mr6176842wmi.102.1584549454675;
        Wed, 18 Mar 2020 09:37:34 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 t1sm10315662wrq.36.2020.03.18.09.37.30
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 09:37:33 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Michael S . Tsirkin" <mst@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Yan Zhao <yan.y.zhao@intel.com>, peterx@redhat.com,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v7 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Wed, 18 Mar 2020 12:37:07 -0400
Message-Id: <20200318163720.93929-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200318163720.93929-1-peterx@redhat.com>
References: <20200318163720.93929-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: nSVM: check for EFER.SVME=1 before entering guest
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11445189
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2501714B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 12:41:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 04E042076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 12:41:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="lA1QKFmt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726842AbgCRMlq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 08:41:46 -0400
Received: from mail-wr1-f68.google.com ([209.85.221.68]:33511 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726546AbgCRMlq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Mar 2020 08:41:46 -0400
Received: by mail-wr1-f68.google.com with SMTP id a25so30200031wrd.0;
        Wed, 18 Mar 2020 05:41:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=8f0u3uYCqa658PohJX3v+iK274a06tw/ySj5+mHDlzA=;
        b=lA1QKFmtAJu0DF/Qp0x2qESDwbw293Dcduj0/ib0aE+immiOhwJmlzB1eZWgO5InGO
         Cs6Lp+afJwVMKya4VJnd5VIxIoChV/u1OHZG8PfaC5AvBE5rC5U9G7UDIUJG2EOgUZOw
         YeV1Lgp2av+pMr3ivDZMQhcBaoW5sfVNpBILRq2h179PcXqTJo/ZK+auFlCYGwx5g8Ox
         N5cwJgLWny1ryZ0ieImVqtUwY3zOmou6fQ4mZ41u/goOl5nS04t/ZSwWxXxkG94+/b/n
         VdhcdhR/nyoDGmDtFha4sM6dfD8UKjku/NtaL9qi7bjjmCAvLspw7JypZOZZsYfDLUkS
         GmKQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=8f0u3uYCqa658PohJX3v+iK274a06tw/ySj5+mHDlzA=;
        b=rdSlXMN4VnlUkL/dkfftzGYA+Eo4BWBrwjtuuU4GzR9UIjHP/5AtkoHRkcs9zOpIMg
         0Pm1Etq2Exm7AlCI5fuB3f2VbXOBb7APBq20fwtc0IeVOnTbG6iAfnAaDDOVKj390XyQ
         XmUUg8zi280srBT4M29Y8U1vZzOu34uvwhV4alw14uQecH+jidojyqOZFCo6HpYF7H/y
         yKdMJQL8m9x2hYJl+boaLqYTUHhWPJg93GD10jXPVxmn2RuIe0sDTvpk+jh3cvgVxo5N
         yZTadtaK3byEbeixNBW4R/iIo3GShtWKIPbIuSS3oujeZIs23ISivzm4KeuEOdlP+jfx
         qUvw==
X-Gm-Message-State: ANhLgQ1D4HulFLV4PtJafEi9kDLjYiNh5dkNXJ7a2R95YHKnSOXhvRMU
        I2a9k4jmznT6iEBYlNIWG/IuFheJ
X-Google-Smtp-Source: 
 ADFU+vtf/D6MSULsPgcg3Ot8TazUpuJrBwQkuucH5iTNC5sbpCrGZMb1ZWS0I4LKHjIVMYRC8yzdNg==
X-Received: by 2002:a5d:69c1:: with SMTP id s1mr5711074wrw.351.1584535304261;
        Wed, 18 Mar 2020 05:41:44 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.174.5])
        by smtp.gmail.com with ESMTPSA id l8sm3752726wmj.2.2020.03.18.05.41.43
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Mar 2020 05:41:43 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: nSVM: check for EFER.SVME=1 before entering guest
Date: Wed, 18 Mar 2020 13:41:40 +0100
Message-Id: <1584535300-6571-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EFER is set for L2 using svm_set_efer, which hardcodes EFER_SVME to 1 and hides
an incorrect value for EFER.SVME in the L1 VMCB.  Perform the check manually
to detect invalid guest state.

Reported-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v4 1/2] KVM: VMX: rename 'kvm_area' to 'vmxon_region'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11445763
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 710D51667
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 17:18:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 522BA2076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 17:18:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WpYlUaFn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727093AbgCRRSA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 13:18:00 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:24955 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726765AbgCRRSA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Mar 2020 13:18:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584551879;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=CuFclgdlUZIfeKH6zTx3SlLSiEPACrqlHVtYi2J2TNQ=;
        b=WpYlUaFnlWylZ513qp5TgFMbdYwe99EwASrSJhPJnuBT8teUpUL1laW9Zuxl5VzCTr0SLZ
        ihIGcSCy/Ko3yqrhKduOdBC/i0WrklBNDTwArU7abYGoI4oCcTMw4cefCA57aHOrmqDwaK
        h2jN0eO/kTIagYpxcJVAY/tjTJJt5AA=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-464-czp_yaSVNKa7agPMLyOJaA-1; Wed, 18 Mar 2020 13:17:57 -0400
X-MC-Unique: czp_yaSVNKa7agPMLyOJaA-1
Received: by mail-wm1-f72.google.com with SMTP id 20so1344565wmk.1
        for <kvm@vger.kernel.org>; Wed, 18 Mar 2020 10:17:57 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=CuFclgdlUZIfeKH6zTx3SlLSiEPACrqlHVtYi2J2TNQ=;
        b=sV74q+0UEMcLPQhE87MXdr0dzW7FbvGYQ0ZXLvfR7sqccjDfVFfy77/2ZXUIuEfpYr
         /+yljcosjXOkJvAybL7dbT11qSgPEvQQwwZiW/kjVYutxl3m6Paq8NqKLZYktmtd4w0b
         K00n5kZyOAmHlt5DQMsdcKCAQEV1rjrDO8j2/V3mYUe4LWL0zoby8UqrXOdB5wa6bfi1
         kTW0so9nUL0qrrqSEFW9500YSwHvNSsr+Tub8OEsKTZfa6ylznu9rcwA57PJ1CSJMCQQ
         ooXzliqR2sm1AeXrVNbZV9fgfChP82zND4bsgXJd9Z2pDLLNLjZdheoJGY5k/IMX0WiC
         Qe2w==
X-Gm-Message-State: ANhLgQ1iEH4W0CBz6iv8R+JmIh7/kVHF30gvx7MXqprs0d0P0NAQkNni
        ElTO5G9Ka3QaPs5KCdr7VIjHIbv6nigwH3ewORP0RDGsLP/ziREmpf6eUCzqQapJ1LWhPfCVJAR
        TORWXVZHPlc23
X-Received: by 2002:a7b:c7d9:: with SMTP id z25mr6495678wmk.25.1584551876380;
        Wed, 18 Mar 2020 10:17:56 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vvLZDXsCkofLpkMC/8OH/AOs7wrSc1tcFIGLwrcu+GaQO7Kk/aiDF8sstgwLmu6SXzAqfxDMA==
X-Received: by 2002:a7b:c7d9:: with SMTP id z25mr6495646wmk.25.1584551876087;
        Wed, 18 Mar 2020 10:17:56 -0700 (PDT)
Received: from vitty.brq.redhat.com (g-server-2.ign.cz. [91.219.240.2])
        by smtp.gmail.com with ESMTPSA id
 r3sm10531597wrw.76.2020.03.18.10.17.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 10:17:55 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v4 1/2] KVM: VMX: rename 'kvm_area' to 'vmxon_region'
Date: Wed, 18 Mar 2020 18:17:51 +0100
Message-Id: <20200318171752.173073-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200318171752.173073-1-vkuznets@redhat.com>
References: <20200318171752.173073-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The name 'kvm_area' is misleading (as we have way too many areas which are
KVM related), what alloc_kvm_area()/free_kvm_area() functions really do is
allocate/free VMXON region for all CPUs. Rename accordingly.

No functional change intended.

Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: VMX: Disable Intel PT before VM-entry
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Luwei Kang <luwei.kang@intel.com>
X-Patchwork-Id: 11444475
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADB6E14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 03:51:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9769920754
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 03:51:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727113AbgCRDvM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 23:51:12 -0400
Received: from mga14.intel.com ([192.55.52.115]:57668 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726229AbgCRDvL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 23:51:11 -0400
IronPort-SDR: 
 JiYt3whZZc5rWcXYQjE9lZ0QWtm+Lx4F1ybZGVxtr7O+lvkYsIwK7Mr5yLmjyIXlkER81tSf3q
 a4C7MRwCGRLw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2020 20:51:11 -0700
IronPort-SDR: 
 9bUF4H9QQNe3a8MQitbBFyw8f9tSiDyCfhjvRRegxTcaEa61P4rY7aAkTgy9i/WeNGTaHtWTYI
 3rVfHzAzi7vg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,566,1574150400";
   d="scan'208";a="268215257"
Received: from icx-2s.bj.intel.com ([10.240.192.138])
  by fmsmga004.fm.intel.com with ESMTP; 17 Mar 2020 20:51:09 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH] KVM: VMX: Disable Intel PT before VM-entry
Date: Wed, 18 Mar 2020 11:48:18 +0800
Message-Id: <1584503298-18731-1-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the logical processor is operating with Intel PT enabled (
IA32_RTIT_CTL.TraceEn = 1) at the time of VM entry, the “load
IA32_RTIT_CTL” VM-entry control must be 0(SDM 26.2.1.1).

The first disabled the host Intel PT(Clear TraceEn) will make all the
buffered packets are flushed out of the processor and it may cause
an Intel PT PMI. The host Intel PT will be re-enabled in the host Intel
PT PMI handler.

handle_pmi_common()
    -> intel_pt_interrupt()
            -> pt_config_start()

This patch will disable the Intel PT twice to make sure the Intel PT
is disabled before VM-Entry.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)

```
#### [PATCH rebase] KVM: x86: Expose AVX512 VP2INTERSECT in cpuid for TGL
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11444459
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 77C64913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 03:27:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6100B206F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 03:27:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726763AbgCRD1k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Mar 2020 23:27:40 -0400
Received: from mga01.intel.com ([192.55.52.88]:51491 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726250AbgCRD1k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Mar 2020 23:27:40 -0400
IronPort-SDR: 
 j1bzBZWkTKzwFBQy3dC/qEO+S9pmlaYt7zaNQGp3nSwgTOifOWVUCKyd+BNtxS/GBVz3snA7B7
 JFA90OyCwz0g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Mar 2020 20:27:41 -0700
IronPort-SDR: 
 IBUl3rotRx+sX8oYFfTYc6Pg4ZsoSrCZiAk3u71icpdrD859zYVd9jLt9ldVJEYS1UyTIyt/yn
 OSomqr/U0eJw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,566,1574150400";
   d="scan'208";a="291188370"
Received: from kaiwang3-mobl2.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.249.174.200])
  by FMSMGA003.fm.intel.com with ESMTP; 17 Mar 2020 20:27:38 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "Zhong, Yang" <yang.zhong@intel.com>
Subject: [PATCH rebase] KVM: x86: Expose AVX512 VP2INTERSECT in cpuid for TGL
Date: Wed, 18 Mar 2020 11:27:39 +0800
Message-Id: <20200318032739.3745-1-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <dcc9899c-f5af-9a4f-3ac2-f37fd8b930f7@redhat.com>
References: <dcc9899c-f5af-9a4f-3ac2-f37fd8b930f7@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Tigerlake new AVX512 VP2INTERSECT feature is available.
This trys to expose it for KVM supported cpuid.

Cc: "Zhong, Yang" <yang.zhong@intel.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V6 1/8] vhost: allow per device message handler
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11444681
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DC17159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 08:04:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E13D42076F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 08:04:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EuRoLDgf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727361AbgCRIED (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 04:04:03 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:29184 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727319AbgCRIED (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Mar 2020 04:04:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584518642;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Qv2sf5ZLe8MVzng446R1oQxVfhG/+fRJUSulJ/I8CAY=;
        b=EuRoLDgfXx49L3nfHzOiANjPOEEAsrzS7fpfzRwdAS8qLAjo8Q+3Q7g8sE3VQmtci9Yzmj
        3xaYmhLUYUw4y7lrIKC7khivYPHB0v54SDZAve9byAaXemKS+bmUFT5GW/BLEMCGhMSvry
        81KGxHF56fwHWKxz+EGxCJublsSmlH8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-168-OCU501FROFGJI-3DsIivUA-1; Wed, 18 Mar 2020 04:04:00 -0400
X-MC-Unique: OCU501FROFGJI-3DsIivUA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 41814800D50;
        Wed, 18 Mar 2020 08:03:57 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-166.pek2.redhat.com [10.72.13.166])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 164B119C58;
        Wed, 18 Mar 2020 08:03:47 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, lulu@redhat.com,
        parav@mellanox.com, kevin.tian@intel.com, stefanha@redhat.com,
        rdunlap@infradead.org, hch@infradead.org, aadam@redhat.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com, gdawar@xilinx.com, saugatm@xilinx.com,
        vmireyno@marvell.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V6 1/8] vhost: allow per device message handler
Date: Wed, 18 Mar 2020 16:03:20 +0800
Message-Id: <20200318080327.21958-2-jasowang@redhat.com>
In-Reply-To: <20200318080327.21958-1-jasowang@redhat.com>
References: <20200318080327.21958-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch allow device to register its own message handler during
vhost_dev_init(). vDPA device will use it to implement its own DMA
mapping logic.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/net.c   |  3 ++-
 drivers/vhost/scsi.c  |  2 +-
 drivers/vhost/vhost.c | 12 ++++++++++--
 drivers/vhost/vhost.h |  6 +++++-
 drivers/vhost/vsock.c |  2 +-
 5 files changed, 19 insertions(+), 6 deletions(-)

```
