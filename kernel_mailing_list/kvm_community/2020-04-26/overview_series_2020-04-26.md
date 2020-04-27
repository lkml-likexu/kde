#### [PATCH v3 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11510575
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C1EDB92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 12:39:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4039216FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 12:39:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726206AbgDZMjP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 08:39:15 -0400
Received: from out30-130.freemail.mail.aliyun.com ([115.124.30.130]:46856
 "EHLO
        out30-130.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726144AbgDZMjO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 26 Apr 2020 08:39:14 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R131e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e01419;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=37;SR=0;TI=SMTPD_---0TwgcTe9_1587904746;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0TwgcTe9_1587904746)
          by smtp.aliyun-inc.com(127.0.0.1);
          Sun, 26 Apr 2020 20:39:07 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, tsbogend@alpha.franken.de, paulus@ozlabs.org,
        mpe@ellerman.id.au, benh@kernel.crashing.org,
        borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, maz@kernel.org, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH v3 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
Date: Sun, 26 Apr 2020 20:38:59 +0800
Message-Id: <20200426123905.8336-2-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200426123905.8336-1-tianjia.zhang@linux.alibaba.com>
References: <20200426123905.8336-1-tianjia.zhang@linux.alibaba.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. Earlier than historical reasons, many kvm-related function
parameters retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time.
This patch does a unified cleanup of these remaining redundant parameters.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/s390/kvm/kvm-s390.c | 23 +++++++++++++++--------
 1 file changed, 15 insertions(+), 8 deletions(-)

```
#### [PATCH V2 1/2] vdpa: Support config interrupt in vhost_vdpa
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11510189
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 437B015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 06:13:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 36AA22080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 06:13:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726206AbgDZGNK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 02:13:10 -0400
Received: from mga12.intel.com ([192.55.52.136]:62050 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725468AbgDZGNJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 02:13:09 -0400
IronPort-SDR: 
 AOEt7buZprVCHjCKPlm/1m4iE4B+RmA7hOLP7Q85kQB/pvqmeDLqYNzMwe/cWKRRZA2v0W5bVS
 bqpBK2frx5Ow==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Apr 2020 23:13:09 -0700
IronPort-SDR: 
 bA2YZtnS2wBpvpfZutcyyRZrGUVGpuTqluW40H1PhtTGJ+AqQBTQz9csAGjvq0N6mZakhllOZC
 mpSRbsT6pE2A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,319,1583222400";
   d="scan'208";a="256865194"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga003.jf.intel.com with ESMTP; 25 Apr 2020 23:13:06 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 1/2] vdpa: Support config interrupt in vhost_vdpa
Date: Sun, 26 Apr 2020 14:09:43 +0800
Message-Id: <1587881384-2133-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1587881384-2133-1-git-send-email-lingshan.zhu@intel.com>
References: <1587881384-2133-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit implements config interrupt support in
vhost_vdpa layer.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c       | 47 ++++++++++++++++++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c      |  2 +-
 drivers/vhost/vhost.h      |  2 ++
 include/uapi/linux/vhost.h |  2 ++
 4 files changed, 52 insertions(+), 1 deletion(-)

```
#### [PATCH V3 1/2] vdpa: Support config interrupt in vhost_vdpa
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11510279
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFC5C913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 08:46:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C07A9208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 08:46:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726205AbgDZIqS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 04:46:18 -0400
Received: from mga17.intel.com ([192.55.52.151]:6125 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726108AbgDZIqR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 04:46:17 -0400
IronPort-SDR: 
 LWTREkodhXCWTPLncBfnTc18MYKVNQkWQrQ2MnIxm9wdbgwlQLIaLilwdopu9S+8INF6PNy7x+
 MmpiohmJ4cTw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Apr 2020 01:46:17 -0700
IronPort-SDR: 
 XaoyqdMZ+ojNv9RpevG1h5k8dwqqb5I38TDmtRurBTs00QpMutneiOs9eNoSdFI5uRdhvYOfL/
 TjOaHEM8Hjqg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,319,1583222400";
   d="scan'208";a="275128408"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga002.jf.intel.com with ESMTP; 26 Apr 2020 01:46:14 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 1/2] vdpa: Support config interrupt in vhost_vdpa
Date: Sun, 26 Apr 2020 16:42:51 +0800
Message-Id: <1587890572-39093-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1587890572-39093-1-git-send-email-lingshan.zhu@intel.com>
References: <1587890572-39093-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit implements config interrupt support in
vhost_vdpa layer.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c       | 47 ++++++++++++++++++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c      |  2 +-
 include/uapi/linux/vhost.h |  4 ++++
 3 files changed, 52 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: Remove unneeded __ASM_SIZE usage with POP instruction
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11510547
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A40C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 12:31:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7C082074F
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 12:31:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="AsA3ppnk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726142AbgDZMat (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 08:30:49 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46842 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726139AbgDZMas (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 26 Apr 2020 08:30:48 -0400
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 57FB5C09B04F
        for <kvm@vger.kernel.org>; Sun, 26 Apr 2020 05:30:48 -0700 (PDT)
Received: by mail-wr1-x443.google.com with SMTP id d17so17155795wrg.11
        for <kvm@vger.kernel.org>; Sun, 26 Apr 2020 05:30:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=zZ4RXNvMIlD6HNwpFjr0pliVf/jgEqSPZK6SSI3jXkE=;
        b=AsA3ppnkWiWKWgebL0ITYk0Rz8cYQOeX2ahsJCtPtEIVcxjEb7lXV1GQTV++N/j6tB
         XP9cB8EmJ4EvcSCffaIPU6f2vTWOU/g9RcT2FJhtQQORy5GAaFjPACDnzEbj7IXMDVcE
         Fl9sXifb3EBSggwhUW3TbHgaeZ3+DdCs4bgMjpFLZSXIQmN0rpFzYIxfXYSkPXEgvpAw
         EeUPeIkLwHBBJP1QTEOUw1zOAjX54X6O++rIZP0z/NGhZaBs+KTD2ASxBnl4DG5fi/Kk
         2XeCaQMbcD0xVrVYlQQIfOtJ2QW/hWFDaL0kgtaE/yyc82hiKlwvj7Q+pyfItWuAA85h
         1ApA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=zZ4RXNvMIlD6HNwpFjr0pliVf/jgEqSPZK6SSI3jXkE=;
        b=g9RcoL05WCE7pJsNAb/VcQ1EiuVTYVKBh8RjCeOjLt0g5xftF1/ZITQpDtE6de2IDV
         /0fIiCx18HUhzNZPxm1msTYhFR6CREoUd9YK3KdIZrjyaSg+v+HdPmOHCLKmXEp4zKS4
         uaSatwV2cLDBagle7lMfcgUgGCr6nSzQee0oxL2rC+atchIEjrxthy2CtYahQFxq7jyy
         Dt8qYl1okPibfaQJmujtNYnkvmsxW00htNLoU4PI2Bg6lS2aYEn89STFKs4VEkIDVktD
         bsGUhq8fCTjVA4YgmO38lLyErUOaSiF9YApoHQFfEfI+l21a7dOKi1FiIY68lqnqbxYb
         9BiQ==
X-Gm-Message-State: AGi0Pub2h+XJxo771q0NW98RQoWA25es2pPLpy9xW1o3t3F/ik09zhlS
        HP55q0SNVrVA8HJy1+5zRBWj5j7h0fc=
X-Google-Smtp-Source: 
 APiQypI4IefkO31jzEh5+mkcVC/Du+SgcRbmCPzZalXTmujkNJn4Os4jb5lPoI0EoL3Vjg3ejXIrlQ==
X-Received: by 2002:a05:6000:108e:: with SMTP id
 y14mr23747920wrw.292.1587904246700;
        Sun, 26 Apr 2020 05:30:46 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 y18sm12572230wmc.45.2020.04.26.05.30.45
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 26 Apr 2020 05:30:46 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: VMX: Remove unneeded __ASM_SIZE usage with POP
 instruction
Date: Sun, 26 Apr 2020 14:30:38 +0200
Message-Id: <20200426123038.359779-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

POP instruction always operates in word size, no need to
use __ASM_SIZE macro to force operating mode.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmenter.S | 14 +++++++-------
 1 file changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH v2] KVM: VMX: Improve handle_external_interrupt_irqoff inline assembly
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11510509
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 84A26912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 11:53:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C1DD2075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 11:53:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="b4XCUq7P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726137AbgDZLxF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 07:53:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41020 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726125AbgDZLxF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 07:53:05 -0400
Received: from mail-wr1-x441.google.com (mail-wr1-x441.google.com
 [IPv6:2a00:1450:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CED53C061A0E
        for <kvm@vger.kernel.org>; Sun, 26 Apr 2020 04:53:04 -0700 (PDT)
Received: by mail-wr1-x441.google.com with SMTP id k1so17128056wrx.4
        for <kvm@vger.kernel.org>; Sun, 26 Apr 2020 04:53:04 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XHG/8raY/sNsCvqJxNKRfA970Dv5Wyt5EYrzke/beHI=;
        b=b4XCUq7PlQRs0ksWZgSlunAMQSnV1kPIMQyqkc6EbU7JgSk1MLfLZ/Ggie2G35aPHK
         GRMdF8ts0WKc+gY4/T8wS63LX/W+04fSQYABLIOE9e+S0QhS0Vrxtqlau03Vjhm5GMPp
         tFg/GONDORkbh74dUg/hsW0UNP0/zyavovzIfujGGmxCPG9dt9Q49m+i3LugZJU6sCtL
         tKXYuz4Jjo1ocKlPoS3V21XzzKxsh/S/MwA48T34tg4TNqFtLTMLfqurzgXwwdZIK3bp
         tOfh0J1x6HemeW5UE4cKaucFxCo6gOlZ3aBYcEn/KxVDfZyWa87b//ftH9AZwEZi29gA
         hjew==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XHG/8raY/sNsCvqJxNKRfA970Dv5Wyt5EYrzke/beHI=;
        b=YvAv7y2Tcqs4oshjky4nVV4eqzZ3cZiUCPAIaNpRyDWP6Vq36axoikCPnPPgR/lH2/
         7/GgeEsZjoyXSe8C7JYmHvASi9Fj3HGyv/BWAENRqsJ0P5a8gnCXa55lmNX0p4M7Hq4s
         1lgvSG5l6KpR2Km6b1mPhrI+hFNGfM65l2tUJrcLprorztWe2MC/azMlgnZ6lQ3DGT3h
         /i2QdOp8F8q+67pn0tAoo4ngMkgnEGdt1t+DL214lDQMBvqENwG0Sc5CEtyRpPObUqWN
         O50NBnl/yLOGZaK0P9ioDCYaCSYfvt0fcvutncqiV1sM0n7tHHfZVnY+Vf5Gj6DR4dbh
         Sk6Q==
X-Gm-Message-State: AGi0Pubc5EFCKZS5hErijGln7AgoMRajrywqXaV7zMFIBS4BP23+H8NG
        MPxSMvnRiOrUdLc7UlrCTBv4wjJ92vw=
X-Google-Smtp-Source: 
 APiQypKT6U5iFWVWGfBb8r2IYcT670b2zDQ6YjkSiDSmQiKGrbBpFpAeMuVc2nS2y+e0N0qtu45rvQ==
X-Received: by 2002:adf:9d85:: with SMTP id p5mr22726396wre.101.1587901983275;
        Sun, 26 Apr 2020 04:53:03 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 g6sm16387565wrw.34.2020.04.26.04.53.02
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 26 Apr 2020 04:53:02 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v2] KVM: VMX: Improve handle_external_interrupt_irqoff inline
 assembly
Date: Sun, 26 Apr 2020 13:52:55 +0200
Message-Id: <20200426115255.305060-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Improve handle_external_interrupt_irqoff inline assembly in several ways:
- use "n" operand constraint instead of "i" and remove
  unneeded %c operand modifiers and "$" prefixes
- use %rsp instead of _ASM_SP, since we are in CONFIG_X86_64 part
- use $-16 immediate to align %rsp
- remove unneeded use of __ASM_SIZE macro
- define "ss" named operand only for X86_64

The patch introduces no functional changes.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH V4 1/3] vdpa: Support config interrupt in vhost_vdpa
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11510491
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E62AE1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 11:46:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9A47206CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 11:46:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726177AbgDZLqp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 07:46:45 -0400
Received: from mga05.intel.com ([192.55.52.43]:11883 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726125AbgDZLqp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 07:46:45 -0400
IronPort-SDR: 
 PlZnLfSujQeR3HqofkJqsF1Dx5ZXOLuafCfCVRknTID7pe8Siq0Whnu2yamhOltHosjxUuP/1A
 boIsBtgobeoA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Apr 2020 04:46:44 -0700
IronPort-SDR: 
 l+ZU0uhM0fxpY3LvQhJVkAac5hdBqVKU5u4s2Wb6ZNGuq+NNTTZcRu8FEH0NND0ZP3glmyncmI
 rJpxW7D11GAA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,320,1583222400";
   d="scan'208";a="275155044"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga002.jf.intel.com with ESMTP; 26 Apr 2020 04:46:41 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 1/3] vdpa: Support config interrupt in vhost_vdpa
Date: Sun, 26 Apr 2020 19:43:24 +0800
Message-Id: <1587901406-27400-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1587901406-27400-1-git-send-email-lingshan.zhu@intel.com>
References: <1587901406-27400-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit implements config interrupt support in
vhost_vdpa layer.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c       | 47 ++++++++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vhost.h |  4 ++++
 2 files changed, 51 insertions(+)

```
#### [PATCH V4 2/3] vhost: replace -1 with  VHOST_FILE_UNBIND in iotcls
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11510493
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E77514DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 11:46:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EBB12206CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 11:46:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726208AbgDZLqu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 07:46:50 -0400
Received: from mga05.intel.com ([192.55.52.43]:11883 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726125AbgDZLqs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 07:46:48 -0400
IronPort-SDR: 
 1kmjzcgEZGhXMZ5240bJFIEsZMmNXrEtpKZ5um1F28UhXnZmTXKN58CFJtorsRriwiCbCVTVUK
 hBrFxwq2e/gw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Apr 2020 04:46:48 -0700
IronPort-SDR: 
 SMOXoiLc6kHuQmCO2n6hhlMkAhxQScaMIpQ9oww2q9IyNt0nF9Tapx7GOZJKMp85xZkqoWzTWD
 0fnuec71TfAQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,320,1583222400";
   d="scan'208";a="275155057"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by orsmga002.jf.intel.com with ESMTP; 26 Apr 2020 04:46:45 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 2/3] vhost: replace -1 with  VHOST_FILE_UNBIND in iotcls
Date: Sun, 26 Apr 2020 19:43:25 +0800
Message-Id: <1587901406-27400-3-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1587901406-27400-1-git-send-email-lingshan.zhu@intel.com>
References: <1587901406-27400-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit replaces -1 with VHOST_FILE_UNBIND in ioctls since
we have added such a macro in the uapi header for vdpa_host.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vhost.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio/mdev: Add vfio-mdev device request interface
##### From: Yingtai Xie <xieyingtai@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yingtai Xie <xieyingtai@huawei.com>
X-Patchwork-Id: 11510195
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12B9492C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 06:40:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EFF242071C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 06:40:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726188AbgDZGkE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 02:40:04 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:3299 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726108AbgDZGkE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 02:40:04 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 912E0C13748A6CD909A3;
        Sun, 26 Apr 2020 14:40:02 +0800 (CST)
Received: from DESKTOP-FJ48AOJ.china.huawei.com (10.173.221.6) by
 DGGEMS410-HUB.china.huawei.com (10.3.19.210) with Microsoft SMTP Server id
 14.3.487.0; Sun, 26 Apr 2020 14:39:52 +0800
From: Yingtai Xie <xieyingtai@huawei.com>
To: <kwankhede@nvidia.com>
CC: <alex.williamson@redhat.com>, <kvm@vger.kernel.org>,
        <xieyingtai@huawei.com>, <wu.wubin@huawei.com>
Subject: [PATCH] vfio/mdev: Add vfio-mdev device request interface
Date: Sun, 26 Apr 2020 14:35:42 +0800
Message-ID: <20200426063542.16548-1-xieyingtai@huawei.com>
X-Mailer: git-send-email 2.8.3.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.221.6]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is setup the same way as vfio-pci to indicate
userspace that the device should be released.

Signed-off-by: Yingtai Xie <xieyingtai@huawei.com>
---
 drivers/vfio/mdev/vfio_mdev.c | 10 ++++++++++
 include/linux/mdev.h          |  4 ++++
 2 files changed, 14 insertions(+)

```
####  =?eucgb2312_cn?b?tPC4tDogW1BBVENIXSBbUkZDXSBrdm06IHg4NjogZW11bGF0ZSBBUEVS?=
##### From: "Li,Rongqing" <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Li,Rongqing" <lirongqing@baidu.com>
X-Patchwork-Id: 11510275
Return-Path: <SRS0=1xJ8=6K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7EC2D92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 08:30:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6FFDC2071C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 26 Apr 2020 08:30:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726165AbgDZIas (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 26 Apr 2020 04:30:48 -0400
Received: from mx22.baidu.com ([220.181.50.185]:50150 "EHLO baidu.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726141AbgDZIas (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 26 Apr 2020 04:30:48 -0400
Received: from Bc-Mail-Ex13.internal.baidu.com (unknown [172.31.51.53])
        by Forcepoint Email with ESMTPS id 0CDCC1A3C048E6D289AF;
        Sun, 26 Apr 2020 16:30:27 +0800 (CST)
Received: from BJHW-Mail-Ex13.internal.baidu.com (10.127.64.36) by
 Bc-Mail-Ex13.internal.baidu.com (172.31.51.53) with Microsoft SMTP Server
 (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id
 15.1.1531.3; Sun, 26 Apr 2020 16:30:26 +0800
Received: from BJHW-Mail-Ex13.internal.baidu.com ([100.100.100.36]) by
 BJHW-Mail-Ex13.internal.baidu.com ([100.100.100.36]) with mapi id
 15.01.1713.004; Sun, 26 Apr 2020 16:30:26 +0800
From: "Li,Rongqing" <lirongqing@baidu.com>
To: Peter Zijlstra <peterz@infradead.org>
CC: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>, "hpa@zytor.com" <hpa@zytor.com>,
        "bp@alien8.de" <bp@alien8.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "jmattson@google.com" <jmattson@google.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "sean.j.christopherson@intel.com" <sean.j.christopherson@intel.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>
Subject: 
 =?eucgb2312_cn?b?tPC4tDogW1BBVENIXSBbUkZDXSBrdm06IHg4NjogZW11bGF0ZSBBUEVS?=
	=?eucgb2312_cn?b?Ri9NUEVSRiByZWdpc3RlcnM=?=
Thread-Topic: [PATCH] [RFC] kvm: x86: emulate APERF/MPERF registers
Thread-Index: AQHWGh9bZdasuQhOo023NQfHi2P1S6iLC0mA
Date: Sun, 26 Apr 2020 08:30:26 +0000
Message-ID: <4fecc02b00f6469e81ffc40de4f7188c@baidu.com>
References: <1587704935-30960-1-git-send-email-lirongqing@baidu.com>
 <20200424100143.GZ20730@hirez.programming.kicks-ass.net>
In-Reply-To: <20200424100143.GZ20730@hirez.programming.kicks-ass.net>
Accept-Language: zh-CN, en-US
Content-Language: zh-CN
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [172.22.198.27]
x-baidu-bdmsfe-datecheck: 1_Bc-Mail-Ex13_2020-04-26 16:30:26:950
x-baidu-bdmsfe-viruscheck: Bc-Mail-Ex13_GRAY_Inside_WithoutAtta_2020-04-26
 16:30:26:919
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

> 
> But then here you only emulate it for VMX, which then results in SVM guests
> going wobbly.
> 
> Also, on Intel, the moment you advertise APERFMPERF, we'll try and read
> MSR_PLATFORM_INFO / MSR_TURBO_RATIO_LIMIT*, I don't suppose you're
> passing those through as well?
> 

init_freq_invariance(void) is trying read MSR_PLATFORM_INFO / MSR_TURBO_RATIO_LIMIT*,
should we add a check of turbo status in init_freq_invariance, to avoid the reading?

It is unnecessary to call intel_set_max_freq_ratio  If turbo is disabled

-Li

```
