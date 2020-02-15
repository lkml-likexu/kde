#### [PATCH v4 01/20] irqchip/gic-v4.1: Skip absent CPUs while iterating over redistributors
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11382387
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD006109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:58:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD0E224654
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:58:35 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581692315;
	bh=vp25gJBgXMFgMMGI8FAoC/wlySuBXLyR+duOD9t1hb0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=1GkW1OjzJTq/WIFVmCAJkvAiAiINSMLrkOg3m73cpksHSkFPwW9tMhiSGEa5q8Y9L
	 Lbp66TiSBGWt1MK+sgp2ozBfVfa6kWhANepsIan9DcmEqYe5+moSlemLCLWsruKsdY
	 VKdddt5/e9mArMlYX2gx5HpSO8Fh47KAiFuM+M8s=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729380AbgBNO5s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 09:57:48 -0500
Received: from mail.kernel.org ([198.145.29.99]:50996 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729278AbgBNO5s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 09:57:48 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 7E9EF2467B;
        Fri, 14 Feb 2020 14:57:47 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581692267;
        bh=vp25gJBgXMFgMMGI8FAoC/wlySuBXLyR+duOD9t1hb0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=PkMQCTZmAfn9usdRlh4QN14cdIWg6apvsfuwYQvjTZiuL1PmDNM164trWu8q3hwGv
         Z+Q2Xxb7rM4tmRnTUqZw4wd3mDGJPhvC1FYnkuwSe3zP1XRIoasOxya/bq+J7ZYdvY
         VsX6mkd1xtXGW9A9Y98Ml9a1PiRz2i3y78kfSfZo=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j2cPZ-0057sw-Tu; Fri, 14 Feb 2020 14:57:46 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Jason Cooper <jason@lakedaemon.net>,
        Robert Richter <rrichter@marvell.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v4 01/20] irqchip/gic-v4.1: Skip absent CPUs while iterating
 over redistributors
Date: Fri, 14 Feb 2020 14:57:17 +0000
Message-Id: <20200214145736.18550-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200214145736.18550-1-maz@kernel.org>
References: <20200214145736.18550-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-kernel@vger.kernel.org, lorenzo.pieralisi@arm.com,
 jason@lakedaemon.net, rrichter@marvell.com, tglx@linutronix.de,
 yuzenghui@huawei.com, eric.auger@redhat.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In a system that is only sparsly populated with CPUs, we can end-up with
redistributors structures that are not initialized. Let's make sure we
don't try and access those when iterating over them (in this case when
checking we have a L2 VPE table).

Fixes: 4e6437f12d6e ("irqchip/gic-v4.1: Ensure L2 vPE table is allocated at RD level")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 drivers/irqchip/irq-gic-v3-its.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: Add the check and free to avoid unknown errors.
##### From: Haiwei Li <lihaiwei.kernel@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11383257
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6D3C139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 21:02:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B5237206CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 21:02:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="oGhvLCAq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730372AbgBNVCs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 16:02:48 -0500
Received: from mail-pg1-f193.google.com ([209.85.215.193]:41869 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728173AbgBNVCs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 16:02:48 -0500
Received: by mail-pg1-f193.google.com with SMTP id 70so5527750pgf.8;
        Fri, 14 Feb 2020 13:02:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=to:cc:from:subject:message-id:date:user-agent:mime-version
         :content-language:content-transfer-encoding;
        bh=a5vpABAOF4tMnz1rUUiLuId4s5LEubXLb2rqt5r8eCs=;
        b=oGhvLCAqTKogQhSrxAAZT/zL/XDtpVJlRejNsl7YHbdxcpkycNRIy3kJfXrLxJ0sh8
         wzYrmh3qZdrja7JJkuSVS9CWcG7phlIYdCr5Ofrx2sEZpFu693pZWbUqLWrUlrBsjV3d
         +t47E0/WXHBFQPPlalulQdq7ctlEOpZpS8qWfV9K5R2YJP1TkwwcvXz2BOwx0O+NqEqN
         8IJC1xq27p6Gb2BuJtaLPydhiYy4OKXVYd40bozSmWWTZhPkAPHIwTHgUoiq2q2yDdEb
         NVA4ieQqPmGa25XdKwTkyTxxw46UytcD6DDMae9DxA83pxYxiyFm3fmauU7mXzm8CFJw
         15Kw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:to:cc:from:subject:message-id:date:user-agent
         :mime-version:content-language:content-transfer-encoding;
        bh=a5vpABAOF4tMnz1rUUiLuId4s5LEubXLb2rqt5r8eCs=;
        b=Zgx8URsG2wN1FzG7Xg7Gfh3D5boO240QaBj6LmJS/UpiZZBZGsnsST0nj2lo5/xHm9
         thum0zPJaTlNlVY/CJyI3Dev4lHcaJHL5Tm0FCnd8H9eg5lgSvsmIDfkIOpRSF6PII5l
         UYKmMF7sS9slNU6HbBxwDAcqpRQfnqrJvINFcZyZgyeb+25UKMQeOyuJXmG5ICbFJtKK
         AECJPvMc2UIgOmGrKzjZA0+uftiI2I6BhI7Iw+r1WrLt46Pn/l1olcPg/Y7cI6+JUkv0
         Bk5/Q+OA4M8wS9SAj1YfwqRFr7Hhk3ss4Y40Wi0RHMsxWrrOic+ZW1P0ga/TL7N5tLtL
         JIjA==
X-Gm-Message-State: APjAAAUn9jWP2eqx7ZqSjs9dFJZiEgq+AP12eO6OGgfWkPiDtpsC4JWE
        GMck3dqaH19bCPmYZOvDLg==
X-Google-Smtp-Source: 
 APXvYqyj7hwkSoVtaBZ7FLTUEWmuCah+0sp4N5QxvC0rPRZrPVxxGsQBwJDGGMxPr3DUmDASbW3mqA==
X-Received: by 2002:a63:1c4:: with SMTP id 187mr5508035pgb.121.1581714166014;
        Fri, 14 Feb 2020 13:02:46 -0800 (PST)
Received: from [192.168.199.209] ([111.199.188.104])
        by smtp.gmail.com with ESMTPSA id
 q11sm7811030pff.111.2020.02.14.13.02.43
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Fri, 14 Feb 2020 13:02:45 -0800 (PST)
To: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>
From: Haiwei Li <lihaiwei.kernel@gmail.com>
Subject: [PATCH] KVM: Add the check and free to avoid unknown errors.
Message-ID: <aaac4289-f6b9-4ee5-eba3-5fe6a4b72645@gmail.com>
Date: Sat, 15 Feb 2020 05:02:29 +0800
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:68.0)
 Gecko/20100101 Thunderbird/68.4.2
MIME-Version: 1.0
Content-Language: en-US
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

If 'kvm_create_vm_debugfs()' fails in 'kzalloc(sizeof(*stat_data), ...)',
'kvm_destroy_vm_debugfs()' will be called by the final fput(file) in
'kvm_dev_ioctl_create_vm()'.

Add the check and free to avoid unknown errors.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
  virt/kvm/kvm_main.c | 5 ++++-
  1 file changed, 4 insertions(+), 1 deletion(-)

--
1.8.3.1

```
#### [PATCH 1/2] KVM: arm64: Add PMU event filtering infrastructure
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11382983
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E19B1186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 18:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C021C24649
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 18:36:32 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581705392;
	bh=U47Cim1m36ncRf1F2X4HkjZI4B/fxmPv0g5AophOpgA=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=lwb8N/iDgtEANQSsLg36FpIWQAbxY15RE/1+n8LgPOF/di41esg5mpfhHlmrFN2qp
	 GRNvAUuAlRoLxRsqQkrN0zHye14pG6NkpKwSq2O5KmajYWbz5sgLZB+Jzv54sXaunN
	 l49jBT0GzZZVaYME8nLWOnUdjrNgbCLVjpe4ga1w=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388077AbgBNSgc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 13:36:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:37388 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729602AbgBNSgb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 13:36:31 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 27CE1222C2;
        Fri, 14 Feb 2020 18:36:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581705390;
        bh=U47Cim1m36ncRf1F2X4HkjZI4B/fxmPv0g5AophOpgA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=eJhR293pkuXcdRUeLf+A+a5MOkH+eBfFE4Kwin/ZWZlOCyHu6DIus/kBknxlwLH58
         tH2aUPG3KcPyZtTScRIDdIRvnIIrIqLgah7CS70dF4/bqz+Mf2n1buxSD3En2Qzhh3
         2k2rqsfuW1010yFz/XHAZSuvJndRy49pEJckG08I=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j2fpE-005J5c-Gy; Fri, 14 Feb 2020 18:36:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 1/2] KVM: arm64: Add PMU event filtering infrastructure
Date: Fri, 14 Feb 2020 18:36:14 +0000
Message-Id: <20200214183615.25498-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200214183615.25498-1-maz@kernel.org>
References: <20200214183615.25498-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It can be desirable to expose a PMU to a guest, and yet not want the
guest to be able to count some of the implemented events (because this
would give information on shared resources, for example.

For this, let's extend the PMUv3 device API, and offer a way to setup a
bitmap of the allowed events (the default being no bitmap, and thus no
filtering).

Userspace can thus allow/deny ranges of event. The default policy
depends on the "polarity" of the first filter setup (default deny if the
filter allows events, and default allow if the filter denies events).
This allows to setup exactly what is allowed for a given guest.

Note that although the ioctl is per-vcpu, the map of allowed events is
global to the VM (it can be setup from any vcpu until the vcpu PMU is
initialized).

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h |  6 +++
 arch/arm64/include/uapi/asm/kvm.h | 16 +++++++
 virt/kvm/arm/arm.c                |  2 +
 virt/kvm/arm/pmu.c                | 76 ++++++++++++++++++++++++++-----
 4 files changed, 88 insertions(+), 12 deletions(-)

```
#### [PATCH] kvm/emulate: fix a -Werror=cast-function-type
##### From: Qian Cai <cai@lca.pw>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Qian Cai <cai@lca.pw>
X-Patchwork-Id: 11382789
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F016930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 18:00:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 034E020873
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 18:00:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=lca.pw header.i=@lca.pw header.b="ovPYHpFI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389159AbgBNSAv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 13:00:51 -0500
Received: from mail-qt1-f194.google.com ([209.85.160.194]:35552 "EHLO
        mail-qt1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387735AbgBNP4V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 10:56:21 -0500
Received: by mail-qt1-f194.google.com with SMTP id n17so7265534qtv.2
        for <kvm@vger.kernel.org>; Fri, 14 Feb 2020 07:56:21 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=lca.pw; s=google;
        h=from:to:cc:subject:date:message-id;
        bh=6jSjfGtvFx4do4NAPL9uHx8+n+x5lxROSkL2jkHQC4Y=;
        b=ovPYHpFItMqqLAWAG5S/QB+rnCBig0/hdfLXqhp+WoudHfMZv8ItTZEURE/T2JN/fG
         hHlcOAIA6218GMm8dOC2tX+c6bzmMfE/SCjST9/1qO+PvQogsKtLhwgPlvrdl+4i2OVp
         BSIo5nZaGtE3HuqY9vBT9rWd+INyAaitqr5Itn9gVkjQ94r/bJ9+I9rGK1cpDJ/0sfq+
         IuxNGkagkPX5nxsu0eN3Aoh2LHQaBA1/Ds3xFYqRMQjs5QmLCZd2Om9GbVTvk2ZJrl4U
         1nJHOAQz+8VSrN0npIApaha+jOG5/VVTiYLsoZQYOA63vasiwiFWXZieLBmcvPvZThio
         JyOg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=6jSjfGtvFx4do4NAPL9uHx8+n+x5lxROSkL2jkHQC4Y=;
        b=S/HTLNhk/mlBJKoD4Q6RfGE7kINqA0xdJinx2OYJByd+oZmdyS300ZjmhL9Fd95wxP
         Z7hGnSHjAiU8640y1clVatogBsqrlPrNtGy1I1heJ+JUSyNFomed3RjdB2Y3B8tSy2tU
         K/zew6cALRGrzljcescFoebAKzKCOJ/A/k86225qQYF10hsGztnMF5CNLKRLAbQq+Abn
         VQiaBcu7eDK+CY5pToqRHqNjuL48ffUk5GrBUiUF/huF0rvT9HChcLLdM137sS3Ti4Ke
         Pem23WvPC/D/PoYX0xVj/bu4bFkNNtwbBmYYaECU5I6dL/BYqOhgF1JBuaP6GWbZhaD8
         3F/g==
X-Gm-Message-State: APjAAAVuyzKlKdxu4i2G8rr6mFi3oc2RjQqkz1KowJWOW+dGXR/FdYZY
        34RKpygZgcp8Bx005/FsulwoSA==
X-Google-Smtp-Source: 
 APXvYqwj23CiFbMj1wbnSnflDYnJuNbdcFJZX73WW4OaMAYoszvD8eOpzafx1TSsWDYcMrkV/LvINg==
X-Received: by 2002:ac8:33f8:: with SMTP id d53mr3067141qtb.86.1581695780463;
        Fri, 14 Feb 2020 07:56:20 -0800 (PST)
Received: from qcai.nay.com (nat-pool-bos-t.redhat.com. [66.187.233.206])
        by smtp.gmail.com with ESMTPSA id
 w9sm3449497qka.71.2020.02.14.07.56.19
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 14 Feb 2020 07:56:20 -0800 (PST)
From: Qian Cai <cai@lca.pw>
To: pbonzini@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Qian Cai <cai@lca.pw>
Subject: [PATCH] kvm/emulate: fix a -Werror=cast-function-type
Date: Fri, 14 Feb 2020 10:56:08 -0500
Message-Id: <1581695768-6123-1-git-send-email-cai@lca.pw>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

arch/x86/kvm/emulate.c: In function 'x86_emulate_insn':
arch/x86/kvm/emulate.c:5686:22: error: cast between incompatible
function types from 'int (*)(struct x86_emulate_ctxt *)' to 'void
(*)(struct fastop *)' [-Werror=cast-function-type]
    rc = fastop(ctxt, (fastop_t)ctxt->execute);

Fixes: 3009afc6e39e ("KVM: x86: Use a typedef for fastop functions")
Signed-off-by: Qian Cai <cai@lca.pw>
---
 arch/x86/kvm/emulate.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX: Fix some obsolete comments and grammar error
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11381587
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B0CD692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 02:42:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B058222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 02:42:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728406AbgBNCmf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 21:42:35 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10619 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728004AbgBNCmf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 21:42:35 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 7FACC6BB37394EE36B5A;
        Fri, 14 Feb 2020 10:42:31 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS413-HUB.china.huawei.com
 (10.3.19.213) with Microsoft SMTP Server id 14.3.439.0; Fri, 14 Feb 2020
 10:42:23 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: nVMX: Fix some obsolete comments and grammar error
Date: Fri, 14 Feb 2020 10:44:05 +0800
Message-ID: <1581648245-8414-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Fix wrong variable names and grammar error in comment.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/nested.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v2 01/42] mm:gup/writeback: add callbacks for inaccessible pages
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11383331
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6D617186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 22:27:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5601224650
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 22:27:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727790AbgBNW1M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 17:27:12 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:32906 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727772AbgBNW1M (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 14 Feb 2020 17:27:12 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01EMOkaM004709;
        Fri, 14 Feb 2020 17:27:08 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y5x3hvf6s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Feb 2020 17:27:08 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01EMR77o009131;
        Fri, 14 Feb 2020 17:27:07 -0500
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y5x3hvf6e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Feb 2020 17:27:07 -0500
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01EMP5k0007194;
        Fri, 14 Feb 2020 22:27:06 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma03dal.us.ibm.com with ESMTP id 2y5bc0cdq6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 14 Feb 2020 22:27:06 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01EMR31Z53871096
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 14 Feb 2020 22:27:03 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 474F813609A;
        Fri, 14 Feb 2020 22:27:03 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4A54C136099;
        Fri, 14 Feb 2020 22:27:02 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri, 14 Feb 2020 22:27:02 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        Andrew Morton <akpm@linux-foundation.org>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>, linux-mm@kvack.org,
        Will Deacon <will@kernel.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v2 01/42] mm:gup/writeback: add callbacks for inaccessible
 pages
Date: Fri, 14 Feb 2020 17:26:17 -0500
Message-Id: <20200214222658.12946-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200214222658.12946-1-borntraeger@de.ibm.com>
References: <20200214222658.12946-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-14_08:2020-02-14,2020-02-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 malwarescore=0
 clxscore=1015 adultscore=0 mlxlogscore=928 priorityscore=1501 spamscore=0
 bulkscore=0 mlxscore=0 impostorscore=0 suspectscore=2 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002140165
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Claudio Imbrenda <imbrenda@linux.ibm.com>

With the introduction of protected KVM guests on s390 there is now a
concept of inaccessible pages. These pages need to be made accessible
before the host can access them.

While cpu accesses will trigger a fault that can be resolved, I/O
accesses will just fail.  We need to add a callback into architecture
code for places that will do I/O, namely when writeback is started or
when a page reference is taken.

This is not only to enable paging, file backing etc, it is also
necessary to protect the host against a malicious user space. For
example a bad QEMU could simply start direct I/O on such protected
memory.  We do not want userspace to be able to trigger I/O errors and
thus we the logic is "whenever somebody accesses that page (gup) or
doing I/O, make sure that this page can be accessed. When the guest
tries to access that page we will wait in the page fault handler for
writeback to have finished and for the page_ref to be the expected
value.

If wanted by others, the callbacks can be extended with error handlin
and a parameter from where this is called.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 include/linux/gfp.h | 6 ++++++
 mm/gup.c            | 2 ++
 mm/page-writeback.c | 1 +
 3 files changed, 9 insertions(+)

```
#### [PATCH 01/13] HACK: Ensure __NR_userfaultfd is defined
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11382401
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4417E138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:59:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 199932467B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:59:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SQbq36dc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387471AbgBNO7c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 09:59:32 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:48189 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729475AbgBNO7b (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 14 Feb 2020 09:59:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581692371;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=gvpxTHTAPtZtzgXZ+Vsyf3goMgALrnpynweu0cvjJ/w=;
        b=SQbq36dc4m0YIDfdIXSfscxd8Juxz/fhy5nhLEjnW5EQADmbOszQ5djCpzFoQLc5TCLP8l
        vBcWQmj8ikqAcDHG6UXTBlTcNJJLf4zmvH+0aDg4KkzG8bpgYr5g/axjV/KVm6Pov5zVMp
        OuCV2S11DOI4XKCELdL59eDsSAcDDSY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-301-Z8PjcnaSPayVwNimC8ARFA-1; Fri, 14 Feb 2020 09:59:29 -0500
X-MC-Unique: Z8PjcnaSPayVwNimC8ARFA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 25AB3107ACC7;
        Fri, 14 Feb 2020 14:59:28 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6C75119E9C;
        Fri, 14 Feb 2020 14:59:26 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, thuth@redhat.com, peterx@redhat.com
Subject: [PATCH 01/13] HACK: Ensure __NR_userfaultfd is defined
Date: Fri, 14 Feb 2020 15:59:08 +0100
Message-Id: <20200214145920.30792-2-drjones@redhat.com>
In-Reply-To: <20200214145920.30792-1-drjones@redhat.com>
References: <20200214145920.30792-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Without this hack kvm/queue kvm selftests don't compile for x86_64.
---
 tools/testing/selftests/kvm/demand_paging_test.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: x86: don't notify userspace IOAPIC on edge-triggered interrupt EOI
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11381563
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF64C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 02:31:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D9809218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 02:31:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728154AbgBNCbJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 21:31:09 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:58672 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727988AbgBNCbJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 21:31:09 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 827C46388C85363FF681;
        Fri, 14 Feb 2020 10:31:06 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.439.0; Fri, 14 Feb 2020
 10:30:56 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: don't notify userspace IOAPIC on edge-triggered
 interrupt EOI
Date: Fri, 14 Feb 2020 10:32:38 +0800
Message-ID: <1581647558-8216-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Commit 13db77347db1 ("KVM: x86: don't notify userspace IOAPIC on edge
EOI") said, edge-triggered interrupts don't set a bit in TMR, which means
that IOAPIC isn't notified on EOI. And var level indicates level-triggered
interrupt.
But commit 3159d36ad799 ("KVM: x86: use generic function for MSI parsing")
replace var level with irq.level by mistake. Fix it by changing irq.level
to irq.trig_mode.

Fixes: 3159d36ad799 ("KVM: x86: use generic function for MSI parsing")
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/irq_comm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### KVM: X86: Grab KVM's srcu lock when accessing hv assist pageTo: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11381919
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC4C1930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 08:49:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CB99422314
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 08:49:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="R0uUESk3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728775AbgBNItx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 03:49:53 -0500
Received: from mail-oi1-f194.google.com ([209.85.167.194]:41736 "EHLO
        mail-oi1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727965AbgBNItw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 03:49:52 -0500
Received: by mail-oi1-f194.google.com with SMTP id i1so8700910oie.8;
        Fri, 14 Feb 2020 00:49:52 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=63V0t6Y+v/yU31L4w6jaW53E7T9mH+a6FE6ph40izng=;
        b=R0uUESk3MsiC5YP1WOZfAT8n+/ojmsNrrE5g7LzkcOPSJYaEUCugsokO96Hx/q6B6o
         MwOAZEg7NYg7lJk8R4UwCGC1F0jkKzSKHsDrTNn8OG7PvbXzH55heh5tugj+ynlrAHI9
         xF19P9vrVUGcS3oyXST+dOzahIUYJSRGLJ53YRaxn0/9rsX3RNgGcr6169KP78Zrmr0h
         XZB83bFxDx9gVlIp9HENGVLscimNvUi4xgVJaE5QCB2cvVnd8pGPlwq3F7D5yFpHkrFU
         XHCXuUXN5FzGRWvOOKmd13ZbhHM7dKx3zfnU3zBQQXIVQMMEJDNz8HCx/QtN2G/qh1Yv
         LRxA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=63V0t6Y+v/yU31L4w6jaW53E7T9mH+a6FE6ph40izng=;
        b=mudyMEcnqomqREq5yb65hLNAkV9fNDUoCMgdhDVXKRh18njPYm//gSLJpmoqFQhg+1
         +kDETo24vmKmr/Il60koo3X2NZyq5q3EIuISZsxXb5YMrvWeVrQd0/Rdaia+FxxXKUEy
         sPuDv1Xa77Lpg2ni/WIygR3Fot+JCFgGdXtXQxD70aPb+cTr/X0VoPmEZAeQOp/qxKLS
         TX5Vs/aRF7U0JWZyLKlml3rvrlQd/LR2Avl7E4Zw4i+ZVV8sxLPJslALp4ZKHUjMLLJ0
         thFYHmDTICBrMVFyzA8/TzZE7GpOq3l+Oc5yv/F72y9IlHYwRiX2Udv30NjlFZ8H8KpJ
         k4vg==
X-Gm-Message-State: APjAAAWYm3PkEFr8AKV2wLIPMiWbRbhPELHeuk6yhGtLDoNLhR6WRnRF
        ebuEBL++fK0Y0tJKapmUGGgWlrzD0neken0jTHznDCRaPjU=
X-Google-Smtp-Source: 
 APXvYqxSR7hdkvVWpfTtP8bXIo9KPG+2Up1I5vbFN/ZlGRPnCSxrUUcnNtc2e57PBd7YJZI52LQJ6Ykx01+ilb/Fx9A=
X-Received: by 2002:aca:8d5:: with SMTP id 204mr1088854oii.141.1581670191637;
 Fri, 14 Feb 2020 00:49:51 -0800 (PST)
MIME-Version: 1.0
From: Wanpeng Li <kernellwp@gmail.com>
Date: Fri, 14 Feb 2020 16:49:40 +0800
Message-ID: 
 <CANRm+Cy5ChjkMf4k9BCnzApxvgNUFcbMSLPmvTkOkCougXF1jA@mail.gmail.com>
Subject: KVM: X86: Grab KVM's srcu lock when accessing hv assist page
To: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Acquire kvm->srcu for the duration of mapping eVMCS to fix a bug where accessing
hv assist page derefences ->memslots without holding ->srcu or ->slots_lock.

It can be reproduced by running KVM's evmcs_test selftest.

  =============================
  WARNING: suspicious RCU usage
  5.6.0-rc1+ #53 Tainted: G        W IOE
  -----------------------------
  ./include/linux/kvm_host.h:623 suspicious rcu_dereference_check() usage!

  other info that might help us debug this:

   rcu_scheduler_active = 2, debug_locks = 1
  1 lock held by evmcs_test/8507:
   #0: ffff9ddd156d00d0 (&vcpu->mutex){+.+.}, at:
kvm_vcpu_ioctl+0x85/0x680 [kvm]

  stack backtrace:
  CPU: 6 PID: 8507 Comm: evmcs_test Tainted: G        W IOE     5.6.0-rc1+ #53
  Hardware name: Dell Inc. OptiPlex 7040/0JCTF8, BIOS 1.4.9 09/12/2016
  Call Trace:
   dump_stack+0x68/0x9b
   kvm_read_guest_cached+0x11d/0x150 [kvm]
   kvm_hv_get_assist_page+0x33/0x40 [kvm]
   nested_enlightened_vmentry+0x2c/0x60 [kvm_intel]
   nested_vmx_handle_enlightened_vmptrld.part.52+0x32/0x1c0 [kvm_intel]
   nested_sync_vmcs12_to_shadow+0x439/0x680 [kvm_intel]
   vmx_vcpu_run+0x67a/0xe60 [kvm_intel]
   vcpu_enter_guest+0x35e/0x1bc0 [kvm]
   kvm_arch_vcpu_ioctl_run+0x40b/0x670 [kvm]
   kvm_vcpu_ioctl+0x370/0x680 [kvm]
   ksys_ioctl+0x235/0x850
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x77/0x780
   entry_SYSCALL_64_after_hwframe+0x49/0xbe

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/nested.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

         copy_vmcs12_to_enlightened(vmx);
--
2.7.4

```
#### [PATCH] kvm: x86: Print "disabled by bios" only once per host
##### From: Erwan Velu <erwanaliasr1@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Erwan Velu <erwanaliasr1@gmail.com>
X-Patchwork-Id: 11382323
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 036DA13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:33:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D590C206B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 14:33:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="gAGGyVyS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729417AbgBNOdX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 09:33:23 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:35154 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726191AbgBNOdX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 09:33:23 -0500
Received: by mail-wm1-f68.google.com with SMTP id b17so10863628wmb.0;
        Fri, 14 Feb 2020 06:33:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=I7FmDXyfboRLEPAe8bo8K3mXwXolpPNpCrODWfL+mak=;
        b=gAGGyVySMmr2ATay53+kqMswj1tPiJDsz3jS4++s3wXWDQlHnkpWf2HL70eWdJ+fsv
         CQvQV1BddgIFW0e4KztZJD7K4semtYzzKwObmrXtXYQ/cxD8Qzy6aTxMTRNqh6cRubpF
         r1mn7IPnxTtShGYjCl7ka+xqU3DkAAl59gyDCf6L/mYm7eFQ7XNxMEWhLhC5inUVRkjG
         b3lWZWNLQKotrlB26P93uU+wUAvI9uiOrpPMGRWGQwTatskOO7SGxBeGQoOg8tiuvbvj
         b02BwS2WnHhy3I04PFR9L9ZP6j0IWJ9ssjt+UJS+QH/c2pmOi3Ohh3JE9B08BgCSKO/U
         JhWA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=I7FmDXyfboRLEPAe8bo8K3mXwXolpPNpCrODWfL+mak=;
        b=GpmBROZNhghhymDlmg1EU/EIZhu3Mej5TqB08f5v71VF2Ro8vbA1VtM0McNRTtaeeu
         FxsXBKVs1iy5fV275QDcOztFwuNSIW5tUnhuvxVeBHr2LDlTlH7nUMfqyW2ioTTTkg9w
         gqL9qLXEhM/+q9qL5w+LuENpCCrSqFXf9RuI69V0RiJtMlBzqK6xrRiNw+qjxcKEiV8k
         w+MCdC5hxtWUoZ4ush5onATQzGEIjgIzCw+345Zn+9u8jyTQTAjE7NGdxPnCyiYhd7J0
         Ea+b1Rl35cDMW4zsbQjvZHwkfKyp+DfZqwP6njRsoU0+zxNntW585wgvnhJy18FLRIUo
         GwDA==
X-Gm-Message-State: APjAAAXiMstNfoeoc7ap6jGDRIX2AOI1ixK8Gl8bC37zMkKpx5mCaPIi
        tI4wuW63ZRlgxJcZppHchOAx2snMNgiWjQ==
X-Google-Smtp-Source: 
 APXvYqx1QmY2R3J7t7fyqRZrLDCCPv+AondDOF0VmfUJgnj3oPdg3EMRb9Zs6jCDFFBEg13lUluE9g==
X-Received: by 2002:a7b:cf12:: with SMTP id l18mr5265928wmg.66.1581690799833;
        Fri, 14 Feb 2020 06:33:19 -0800 (PST)
Received: from t1700.criteois.lan ([91.199.242.236])
        by smtp.gmail.com with ESMTPSA id
 w13sm7511520wru.38.2020.02.14.06.33.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 14 Feb 2020 06:33:19 -0800 (PST)
From: Erwan Velu <erwanaliasr1@gmail.com>
X-Google-Original-From: Erwan Velu <e.velu@criteo.com>
Cc: Erwan Velu <e.velu@criteo.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] kvm: x86: Print "disabled by bios" only once per host
Date: Fri, 14 Feb 2020 15:30:35 +0100
Message-Id: <20200214143035.607115-1-e.velu@criteo.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
To: unlisted-recipients:; (no To-header on input)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current behavior is to print a "disabled by bios" message per CPU thread.
As modern CPUs can have up to 64 cores, 128 on a dual socket, and turns this
printk to be a pretty noisy by showing up to 256 times the same line in a row.

This patch offer to only print the message once per host considering the BIOS will
disabled the feature for all sockets/cores at once and not on a per core basis.

Signed-off-by: Erwan Velu <e.velu@criteo.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RESEND] KVM: X86: Grab KVM's srcu lock when accessing hv assist page
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11381925
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2F02930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 08:51:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A26B620873
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 08:51:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="HW3SWoPM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729028AbgBNIvs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 03:51:48 -0500
Received: from mail-oi1-f193.google.com ([209.85.167.193]:40887 "EHLO
        mail-oi1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726179AbgBNIvs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 03:51:48 -0500
Received: by mail-oi1-f193.google.com with SMTP id a142so8710681oii.7;
        Fri, 14 Feb 2020 00:51:47 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=63V0t6Y+v/yU31L4w6jaW53E7T9mH+a6FE6ph40izng=;
        b=HW3SWoPMAWcziUXejTkkg3tJQaxTLuOcvMfS1u7iXWG4qTREGVNOIA8n7j4odk9xS7
         cJe3jRrGJX+xMTRDlDm0vroKYXPufsoD3B+UQJeCCSh+FQ7j7HjWFq/W4/lRfHAlO8Jb
         KuD8qjITfSzr9SeVUMoUH8OSnMIRhwA3KJ5yInw7w0kDjOV4Tkc/hSu036QHmbofsDKd
         NIG1rGHCD2/7ihQoa6kpjivDs1Ue/AfhFemnGRa4ZM3X5Ie/2s6FM02JImYWFkM11W6I
         rM3tyN6utg8T76cWcF/0+l7XZcdRBoRoJ/wVlwGjGsNXEXK5QHaf543+DBFF3s3JXXGQ
         facQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=63V0t6Y+v/yU31L4w6jaW53E7T9mH+a6FE6ph40izng=;
        b=Hq6VeisiqmPn5QiO8Qcwk8vZPv86Ho4v0pMKlTJbNARdPagDdUPo8cJ/GqwWxIEuK2
         ZS7//n+Xg81m1Zvbf4mf0f8o40uGX8K4wT+iboXU72xiFdaCOPwGyU9Ca4BquGuOmkrk
         rglbrxHY9wySoriHrzQFfNCGDWr1SHUnJlQBxSF8B1K6PAyp7lWGvd1k3pe50Q8lqTH8
         OL+DpTdJEI5xGitKE8ayrCa+Byu6LeUkBMmiWy/FAi12Lv6M/hWztaTK2qGCa8SkmrTj
         Xp+Q/pgv4ME1BQrUh6UKKv91RycGgZbXoWeYizzQQTzMJ1OyNu2YCO/PvUFhCSypHWCs
         /kWw==
X-Gm-Message-State: APjAAAV4UveUuMB6iZbGCzM3UcayXC5DTUS+vaZj9jjPMingrOC2054g
        kOugQa+KVEvAYxlDwsSUhLxwDz79Csd9Q8XNUUF07fSTy94=
X-Google-Smtp-Source: 
 APXvYqzzT/hXgE2DdlxSNcSrYssedfnMU72KPc54edfHOxHDky+PtYBpJAGzIQX2Grl1StRVMAViAAW1GYp6zeO/aIA=
X-Received: by 2002:a05:6808:249:: with SMTP id
 m9mr1179982oie.5.1581670307046;
 Fri, 14 Feb 2020 00:51:47 -0800 (PST)
MIME-Version: 1.0
From: Wanpeng Li <kernellwp@gmail.com>
Date: Fri, 14 Feb 2020 16:51:36 +0800
Message-ID: 
 <CANRm+CwmVnJqCzN1sWhBOKZBCqpL2ZfRbT-V+tHMGFwPjCZGvw@mail.gmail.com>
Subject: [PATCH RESEND] KVM: X86: Grab KVM's srcu lock when accessing hv
 assist page
To: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Acquire kvm->srcu for the duration of mapping eVMCS to fix a bug where accessing
hv assist page derefences ->memslots without holding ->srcu or ->slots_lock.

It can be reproduced by running KVM's evmcs_test selftest.

  =============================
  WARNING: suspicious RCU usage
  5.6.0-rc1+ #53 Tainted: G        W IOE
  -----------------------------
  ./include/linux/kvm_host.h:623 suspicious rcu_dereference_check() usage!

  other info that might help us debug this:

   rcu_scheduler_active = 2, debug_locks = 1
  1 lock held by evmcs_test/8507:
   #0: ffff9ddd156d00d0 (&vcpu->mutex){+.+.}, at:
kvm_vcpu_ioctl+0x85/0x680 [kvm]

  stack backtrace:
  CPU: 6 PID: 8507 Comm: evmcs_test Tainted: G        W IOE     5.6.0-rc1+ #53
  Hardware name: Dell Inc. OptiPlex 7040/0JCTF8, BIOS 1.4.9 09/12/2016
  Call Trace:
   dump_stack+0x68/0x9b
   kvm_read_guest_cached+0x11d/0x150 [kvm]
   kvm_hv_get_assist_page+0x33/0x40 [kvm]
   nested_enlightened_vmentry+0x2c/0x60 [kvm_intel]
   nested_vmx_handle_enlightened_vmptrld.part.52+0x32/0x1c0 [kvm_intel]
   nested_sync_vmcs12_to_shadow+0x439/0x680 [kvm_intel]
   vmx_vcpu_run+0x67a/0xe60 [kvm_intel]
   vcpu_enter_guest+0x35e/0x1bc0 [kvm]
   kvm_arch_vcpu_ioctl_run+0x40b/0x670 [kvm]
   kvm_vcpu_ioctl+0x370/0x680 [kvm]
   ksys_ioctl+0x235/0x850
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x77/0x780
   entry_SYSCALL_64_after_hwframe+0x49/0xbe

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/nested.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

         copy_vmcs12_to_enlightened(vmx);
--
2.7.4

```
#### [PATCH 1/3] Add a new LSM-supporting anonymous inode interfaceFrom: Daniel Colascione <dancol@google.com>
##### From: Daniel Colascione <dancol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11381621
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 19A5F139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 03:27:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DA24D24649
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 03:27:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="uh3VLcrb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728613AbgBND1A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 22:27:00 -0500
Received: from mail-pf1-f201.google.com ([209.85.210.201]:44543 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728089AbgBND07 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 22:26:59 -0500
Received: by mail-pf1-f201.google.com with SMTP id r127so5120690pfc.11
        for <kvm@vger.kernel.org>; Thu, 13 Feb 2020 19:26:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Qmc32O47mLrX2+XyhMVdXZr4iejtzZNLfPrmboXtlaE=;
        b=uh3VLcrbun/qMQhu4nd1+eaGYqgMlEQPowqmIpbEdcA4ykyJngLFyTS8qPWPXiBr8B
         jgBpWhsjyfOXzmzeoPJ6vygOHofOvCU37iUMxOdgcWuDGbkg+j4ZCqf4/j4tRY/5QnEp
         QOw/JMfyoXkZbjj5azMFroP00me5MntgbGZR86zqNsqCpJXHrrcFhVhqmRn6a6s6i1/1
         6Z43cc/a8I9EiVxeMz3PJF5xblpyxW69rKhQ/RPxa4aJVel6lgKQvwsU/qK0p7VW3nJz
         TXWVPaHWMlTGJWpvk1pJSVFdCKWs6yTgnJZXT8zewrJVEXFAaM0GZtnY7zuH+lYqjDuG
         s1pA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Qmc32O47mLrX2+XyhMVdXZr4iejtzZNLfPrmboXtlaE=;
        b=ki8Yq1vxl+M0WbvEjcE5IUj34QJfqj/8xSCCuqFosJXbEY6nDt0r2SQwUzoyrNxSjd
         5EKLKEu76oK9WJi26msPUAa+uEI6dU5OppH2ZRpXjGJDr6KOPVkCUUUBlbroTFcwMiH2
         bJ7QCnCqIRV4FtNOPKnKheERdQ2vQF/cpLxNae4T6kEzu1kcn+YI+1a1Bamwhonkx/+z
         n2EP1avJJn99es7ZXix/mEM17tLOQ+o8bvrn+n83LR3WoTcRrTHpe1ciIs9NXXfzDa73
         MgzZJCj9xKl9xEx2WSU2vTf0izEY2H0FACjK02maGQj6ugmwbHL+BmOaont8DvfPsGr6
         YRQA==
X-Gm-Message-State: APjAAAV8bp+JSuWbtB31F6FbkacAR7BFrEisGOh6/wmVGJEKsr8FD73/
        TKQVPXwZLtDFT2Ac3Y9UEpxlTnqLVEs=
X-Google-Smtp-Source: 
 APXvYqz0S5IBOrFMOS6B4Vp9EU70qYgr/Lf58sD/J+YQva9G7ILZsp/jlA90GOgvk0ZhdGV6Z5A3FJL+DLs=
X-Received: by 2002:a63:36c2:: with SMTP id d185mr1267436pga.59.1581650818137;
 Thu, 13 Feb 2020 19:26:58 -0800 (PST)
Date: Thu, 13 Feb 2020 19:26:33 -0800
In-Reply-To: <20200214032635.75434-1-dancol@google.com>
Message-Id: <20200214032635.75434-2-dancol@google.com>
Mime-Version: 1.0
References: <20200211225547.235083-1-dancol@google.com>
 <20200214032635.75434-1-dancol@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [PATCH 1/3] Add a new LSM-supporting anonymous inode interface
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds two new functions, anon_inode_getfile_secure and
anon_inode_getfd_secure, that create anonymous-node files with
individual non-S_PRIVATE inodes to which security modules can apply
policy. Existing callers continue using the original singleton-inode
kind of anonymous-inode file. We can transition anonymous inode users
to the new kind of anonymous inode in individual patches for the sake
of bisection and review.

The new functions accept an optional context_inode parameter that
callers can use to provide additional contextual information to
security modules, e.g., indicating that one anonymous struct file is a
logical child of another, allowing a security model to propagate
security information from one to the other.

Signed-off-by: Daniel Colascione <dancol@google.com>
---
 fs/anon_inodes.c            | 196 ++++++++++++++++++++++++++++--------
 fs/userfaultfd.c            |   4 +-
 include/linux/anon_inodes.h |  13 +++
 include/linux/lsm_hooks.h   |   9 ++
 include/linux/security.h    |   4 +
 security/security.c         |  10 ++
 6 files changed, 191 insertions(+), 45 deletions(-)

```
#### [PATCH v2] KVM: X86: Grab KVM's srcu lock when accessing hv assist page
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11381987
Return-Path: <SRS0=AN0r=4C=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37E4D138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 09:16:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1573D2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 14 Feb 2020 09:16:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="OhzdPMys"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728994AbgBNJQj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 04:16:39 -0500
Received: from mail-oi1-f193.google.com ([209.85.167.193]:45022 "EHLO
        mail-oi1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728864AbgBNJQj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 04:16:39 -0500
Received: by mail-oi1-f193.google.com with SMTP id d62so8747075oia.11;
        Fri, 14 Feb 2020 01:16:39 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=yJIG2+5rAA/omb/XOuOyU/XY01fpqVjXiUmRI7jlVsY=;
        b=OhzdPMysleAxFIa7tsDq1Ei3imWZgu66zPkITqJATuRSJ02hM2QCWESz8Zzr2N6+Kv
         zqZQdVVuAa1ZpqS/pLAVL+Tgx6LBFzqvgP3t3ott9+2BIaR25/sW5pEpT3CWXyq8wr2o
         CWgRR/+239LizvfgZfvKDsSSS9/SRV7oytIrycLS20rD/TLNCzGB2HkjtM1/5PGhpM6G
         1H6Hu86r+oGeHLebNrDSgFJjAH7njngDfFN981JpsCl1w9A6llOhArl28ePzuKv4mFfP
         qhivzjXS/9o7xLwq0p3wlZFeUs7UPJdorISawh1e0s1cXsR1+D8Z97eeTZWswGkOmyaD
         EK4Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=yJIG2+5rAA/omb/XOuOyU/XY01fpqVjXiUmRI7jlVsY=;
        b=sY0CjFqiSymf/pfc/x7RPNOi/nHr4sdKrMaRZZAjNcPAYIZ2bPQp88dAzEx91sqbCp
         zVZG9Mv8YUVZWmxaXERJvJioe32T2BQ7jlLratmYpuZ/QHLbcdRR6Ihj5Uksqg61eg1d
         QrP01tnUN8FmGru01fl09Yj0GM1N7IcoPcxJB7onwRtYEcw0ugZH4U9hAjBHG1ull8yz
         s5Y/E1Nv7L0N07mguploCi4NAGQ0GC1KnSxnqkURRSh8+PH/Aj5vlo8/JxIGa4sVU/9Y
         VsEWQIzoBwDRC8iVlBYmwsF01YItYPLtcGANAd//p1mhNyu8oH+PxJLifqqiFzfBftdR
         pnyw==
X-Gm-Message-State: APjAAAWv7kKtFDJToVe/KAHiwMYMe48l8gzQPgtHJx3+J1VIf3Jm9cZv
        GnmuzJ7S/T2j2MYkJVu5yXxWKs9S8oF2SLmoI4vW0tG0lg4=
X-Google-Smtp-Source: 
 APXvYqy46/3PWFWzsB9YfYAq2ltYbwzagbLttlQg6ScSiwe+seEKxbquh7gEBmLKFz1xqkzDM1lIM31Q/N61CtrCeqE=
X-Received: by 2002:aca:8d5:: with SMTP id 204mr1147247oii.141.1581671798823;
 Fri, 14 Feb 2020 01:16:38 -0800 (PST)
MIME-Version: 1.0
From: Wanpeng Li <kernellwp@gmail.com>
Date: Fri, 14 Feb 2020 17:16:28 +0800
Message-ID: 
 <CANRm+CznPq3LQUyiXr8nA7uP5q+d8Ud-Ki-W7vPCo_BjDJtOSw@mail.gmail.com>
Subject: [PATCH v2] KVM: X86: Grab KVM's srcu lock when accessing hv assist
 page
To: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: wanpeng li <wanpengli@tencent.com>

For the duration of mapping eVMCS, it derefences ->memslots without holding
->srcu or ->slots_lock when accessing hv assist page. This patch fixes it by
moving nested_sync_vmcs12_to_shadow to prepare_guest_switch, where the SRCU
is already taken.

It can be reproduced by running kvm's evmcs_test selftest.

  =============================
  warning: suspicious rcu usage
  5.6.0-rc1+ #53 tainted: g        w ioe
  -----------------------------
  ./include/linux/kvm_host.h:623 suspicious rcu_dereference_check() usage!

  other info that might help us debug this:

   rcu_scheduler_active = 2, debug_locks = 1
  1 lock held by evmcs_test/8507:
   #0: ffff9ddd156d00d0 (&vcpu->mutex){+.+.}, at:
kvm_vcpu_ioctl+0x85/0x680 [kvm]

  stack backtrace:
  cpu: 6 pid: 8507 comm: evmcs_test tainted: g        w ioe     5.6.0-rc1+ #53
  hardware name: dell inc. optiplex 7040/0jctf8, bios 1.4.9 09/12/2016
  call trace:
   dump_stack+0x68/0x9b
   kvm_read_guest_cached+0x11d/0x150 [kvm]
   kvm_hv_get_assist_page+0x33/0x40 [kvm]
   nested_enlightened_vmentry+0x2c/0x60 [kvm_intel]
   nested_vmx_handle_enlightened_vmptrld.part.52+0x32/0x1c0 [kvm_intel]
   nested_sync_vmcs12_to_shadow+0x439/0x680 [kvm_intel]
   vmx_vcpu_run+0x67a/0xe60 [kvm_intel]
   vcpu_enter_guest+0x35e/0x1bc0 [kvm]
   kvm_arch_vcpu_ioctl_run+0x40b/0x670 [kvm]
   kvm_vcpu_ioctl+0x370/0x680 [kvm]
   ksys_ioctl+0x235/0x850
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x77/0x780
   entry_syscall_64_after_hwframe+0x49/0xbe

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

--
2.7.4

```
