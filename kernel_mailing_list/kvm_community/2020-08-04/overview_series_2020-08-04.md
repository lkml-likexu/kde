#### [PATCH 1/2] KVM: LAPIC: Return 0 when getting the tscdeadline timer if the lapic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11699759
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4C8C214DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 06:11:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A82220781
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 06:11:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="CXXo3e4F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728322AbgHDGK6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 02:10:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37164 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727076AbgHDGK6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 02:10:58 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4A483C06174A;
        Mon,  3 Aug 2020 23:10:58 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id s26so19602724pfm.4;
        Mon, 03 Aug 2020 23:10:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=BSDgawubjKZTjBa80whU7RPxG9HALrOtjtBrOe2a6/c=;
        b=CXXo3e4Fn//oKcVoftIyvz229kjYfndjtjhcOG7iFqjPULlGpd0vPxwhM7bfoUVD47
         A9riFUhG4SQ7YM3tA0OqqEHWX3W3LnkwJOySfvGqFgsouLtuGVov1XB6jS0tr+4r7olz
         uLdczamHmIDm1KufCksyNt58T7AZNLQ8Atf1W13AaRoMnVU753aG/sIqT34eVIuur25h
         llusk7yrHg8q61Q+c0pOoMbmynRVZdLxHq3BMWi9F3zK+oMCWTH90Q86GFUYssxXNu+M
         Lb9OCFrcC8GX6bElNdXWdIteL62oOltQsd2UGyz697AdEnF5R0l2lbog4omF9GmLFOfn
         6bjQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=BSDgawubjKZTjBa80whU7RPxG9HALrOtjtBrOe2a6/c=;
        b=bafmtS1tT1Pee5yfj50+j/i8OZXxVPyCWoj22poBJn0KeGvwfLZKV538nTfQxy0Lqk
         mZ1SZOfX5xKBX9zxsH8FaLaIb/T9aw9u16GXYa3BaNEIwBt78gGPFGt3/GSdoC9VQbuv
         iLIvXtLR8xa/G6lK4Zt3TPzv5i0+zWf+curXOgUhya5RF3M24AnzmgioHZRUXwZlAp4f
         yF8asYohmeQvf9I2gf6b6tWDoc9dkS+5E2abch9/g9UuL3vTYpvCm7B+qXRtW3Wy64K3
         E3rufvU9NV95b+5MaU3t53JPsSu7TXmJjFvNTU34Qpy7twKKBqxcsPiUc2lz9CIrUo8p
         hVTw==
X-Gm-Message-State: AOAM531T7DNqRzIk9NdS5d58TCl9eTL1zWwtsCzB3IK2EOEhUnRRWiKo
        Rt4MyPqTTT1qvHwIEHPIydaH0KVC
X-Google-Smtp-Source: 
 ABdhPJwjhVkCBOwIfQJd1BbYy7VJqkKlx4vZhImER3qR1wPDWN2a6Jq0LA2IPbi6RHnOzxrmLKuPlQ==
X-Received: by 2002:a63:e114:: with SMTP id
 z20mr15925406pgh.300.1596521457625;
        Mon, 03 Aug 2020 23:10:57 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 s8sm22093069pfc.122.2020.08.03.23.10.55
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 03 Aug 2020 23:10:57 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/2] KVM: LAPIC: Return 0 when getting the tscdeadline timer
 if the lapic is hw disabled
Date: Tue,  4 Aug 2020 14:10:47 +0800
Message-Id: <1596521448-4010-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Return 0 when getting the tscdeadline timer if the lapic is hw disabled

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/6] KVM: x86: Add ioctl for accepting a userspace provided MSR list
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11699707
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 931F914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 04:21:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3B362070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 04:21:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="IkaSQ7KA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728516AbgHDEU4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 00:20:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48276 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725807AbgHDEU4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 00:20:56 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 55EB5C06174A
        for <kvm@vger.kernel.org>; Mon,  3 Aug 2020 21:20:56 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id v65so3614348ybv.9
        for <kvm@vger.kernel.org>; Mon, 03 Aug 2020 21:20:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Z431tMDqsp9z1m5bwGOkLYrKaoTeC+PaEXx+R0OqLl4=;
        b=IkaSQ7KAsLov+1Y9FM84mIgY3sQcUiqR7PcUtyaC3DwSknXaq0yWUX2jBgtuNCoph7
         9/3cTjJvdcqTiJ96sas7a8Z8JJ6aQigGsgZMmkheia3ox39wd0fNlQ84cq2QrQZKoIKj
         xcmwhmm3Qjfxbb+OixQZ4/RapEWx1quGb3natZUJP9UjSt+3Tp3iU8Qo2yvBtu0OPAYU
         b9MxcGHxxSSGa0N/MaQUvhP9lt+ibp7Od3f0ogHLrKkEhbK+HWSmtnIlj0JLjESIlEYI
         AqrbgQDg3xW8+SV+B71GLRRS7u2n8bdTWeKJBKZ+w5eg8Z+0p5E7NoOcP/LDslcBEdJr
         Rjaw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Z431tMDqsp9z1m5bwGOkLYrKaoTeC+PaEXx+R0OqLl4=;
        b=LCcd25vmfEc8EoYpmXLEyMtm3Ubzc7SllDRV/Ico++1VbXlCSynA5732LKB60iU1U3
         k2G6Kfrh29ywtqkcREJPwOnQxOAXh1eZTSIT878KkLS737SZDUpsCow/PBpTtF+8ieXA
         HI2K1btBaV8LUJfY8ukXb1QQA/ZnLTqW6j8/IjNACNakPrqiJDkf9ZexJ+2nfenUmUiB
         uHsre/8M5EI31QHy6A/+KbEgnucsEA3Xm6z1yOwxFJSrslYYmcRd2xH4mR18OMbOdwFL
         h/9cC6Z1psmsERTYsoa5GNQr3d+oT17J8w+/0RD2VIemHdVjvZ12TkH0JUlbfIYtSfef
         zClw==
X-Gm-Message-State: AOAM533i+lHZngBMMX4QUmvzRivhya6n+ETSFKwHedPk4qvK3K266UDP
        xQJDCk6goQ843AvC27ryDEeZlcpU5zRttr/m
X-Google-Smtp-Source: 
 ABdhPJx0/0dFy/QKqK0nD6PiCmVNgbluFHwVOwSlm4VQGu5cqAF8U+GGTkX4YeLfHdR8pdH+4CsPd0/l2jFZs93G
X-Received: by 2002:a25:9885:: with SMTP id l5mr33250745ybo.0.1596514855556;
 Mon, 03 Aug 2020 21:20:55 -0700 (PDT)
Date: Mon,  3 Aug 2020 21:20:38 -0700
In-Reply-To: <20200804042043.3592620-1-aaronlewis@google.com>
Message-Id: <20200804042043.3592620-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20200804042043.3592620-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.28.0.163.g6104cc2f0b6-goog
Subject: [PATCH 1/6] KVM: x86: Add ioctl for accepting a userspace provided
 MSR list
From: Aaron Lewis <aaronlewis@google.com>
To: jmattson@google.com, graf@amazon.com
Cc: pshier@google.com, oupton@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add KVM_SET_EXIT_MSRS ioctl to allow userspace to pass in a list of MSRs
that force an exit to userspace when rdmsr or wrmsr are used by the
guest.

KVM_SET_EXIT_MSRS will need to be called before any vCPUs are
created to protect the 'user_exit_msrs' list from being mutated while
vCPUs are running.

Add KVM_CAP_SET_MSR_EXITS to identify the feature exists.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 Documentation/virt/kvm/api.rst  | 24 +++++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/x86.c              | 41 +++++++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h        |  2 ++
 4 files changed, 69 insertions(+)

```
#### [PATCH v2 1/6] KVM: arm64: pvtime: steal-time is only supported when configured
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11700731
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 063CB14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 17:08:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00B05208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 17:08:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PRbBgmSp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729778AbgHDRId (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 13:08:33 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:37624 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729022AbgHDRIX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 Aug 2020 13:08:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596560902;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=u3R78I0xIcTidytSUpGka2ZN17jeItCiL5JpEI42hQQ=;
        b=PRbBgmSpYM1C7bDlwK9Wb1QpY8pXzDTZraUEXeKdZbH7OpxNLhKIAWfGFKYGHhvHxuSP8I
        ygdjLmvKOEuh8QyLydFITrP1i4YmRQDnsgRbVM/SjxmuyqiiShbOszLWXz1OzAc9TvM1N0
        oT0/B9iUXkzJgmxVeq51eshZ49HVhho=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-31-jk7L9GsZP6OljFwiSKzfAQ-1; Tue, 04 Aug 2020 13:06:10 -0400
X-MC-Unique: jk7L9GsZP6OljFwiSKzfAQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8E32910059AB;
        Tue,  4 Aug 2020 17:06:09 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.120])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E048888D6B;
        Tue,  4 Aug 2020 17:06:07 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, steven.price@arm.com, pbonzini@redhat.com
Subject: [PATCH v2 1/6] KVM: arm64: pvtime: steal-time is only supported when
 configured
Date: Tue,  4 Aug 2020 19:05:59 +0200
Message-Id: <20200804170604.42662-2-drjones@redhat.com>
In-Reply-To: <20200804170604.42662-1-drjones@redhat.com>
References: <20200804170604.42662-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't confuse the guest by saying steal-time is supported when
it hasn't been configured by userspace and won't work.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arch/arm64/kvm/pvtime.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH RESEND v2] x86: tscdeadline timer testing when apic disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11699327
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB73E14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 00:39:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00F1B2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 00:39:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="sE2zzvp+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727779AbgHDAjf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 20:39:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42638 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726130AbgHDAjf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 20:39:35 -0400
Received: from mail-pf1-x444.google.com (mail-pf1-x444.google.com
 [IPv6:2607:f8b0:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 45836C06174A
        for <kvm@vger.kernel.org>; Mon,  3 Aug 2020 17:39:35 -0700 (PDT)
Received: by mail-pf1-x444.google.com with SMTP id f193so8843355pfa.12
        for <kvm@vger.kernel.org>; Mon, 03 Aug 2020 17:39:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=P7K1/or27Q5kuNX+G726+alc8/6c9ST1cR6CdnWA9Ek=;
        b=sE2zzvp+3n8gXNBzs1nAoCGBiFS/us8VMTP5rvpCJdHhaQ0xMm4+SWWplfOk3oTBOo
         qBQ39Iid9wIFlsjXqSS4SAbvzL1HLf9jjr8q15KuJdJwqXrbZixDHcnb1xBNrVHifT7N
         L4fgdzUm48L6j5g2mfW9O4IhzM4jg3geakAz8I+IO/HnCCRgW3N0rfcr5tLbawLa7Utt
         onrUAjYtU1VOwqTn6NsMdfQ2S3D7pfquZ1PomSZdoMOKBlf1ON26msbFsk0hJGl29dZc
         ClFCB3/5x/n5Ug3PFy3491pzXE+4MbDY38FmwEeFJjyjCyQNS/D9m6KDhcLc8Bmxo9Kp
         IX1w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=P7K1/or27Q5kuNX+G726+alc8/6c9ST1cR6CdnWA9Ek=;
        b=a39i50OeUiAKO8kkWZ8YJPya+6tg3jI2qK5QhV3nPPiJV+A5itsPqlEDMm3jrOyxgl
         Kv95OyZOnKQKJ9TWrMXl7coGNSrn9L9VDRuCU2yB6/608/HmWE0pxSH/UY5ItklEjMk7
         fkSi9aLhGYxhOHAyCVYpjiI1F9rt8vwYQJsYgPfNkNrAl5hA8RMH1W/RG2d5w7Xrg39e
         HDt89mEyaIobpaSRlBZ/VWFI2Jpq9dlZQpLJWpQRv9jdec92Ls3lnb48dBXMalOJNeKJ
         3SbQclVdhZCqIJfzcgvJfm+mPtu/xW1471CwEmYUbSxVwPUTQPuRY7/T2/CyuxJRPa6s
         EpCg==
X-Gm-Message-State: AOAM533ji34RNA4J0xjHGug8VD6Nnc9qXgt0zYhHvr9ixpGEZA0YvBLG
        ZWqYvEa8ew8va4YnnwjXDYWlgg19
X-Google-Smtp-Source: 
 ABdhPJw4o7EGEKLPsrHpIa9TFgV/JQQ1z3OM+JXUuEvqMEfeVaHT9ac1Q3vS2pyuLzsqpbgMkqE+Lw==
X-Received: by 2002:a63:1a44:: with SMTP id a4mr17241160pgm.281.1596501574581;
        Mon, 03 Aug 2020 17:39:34 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 mp3sm2426610pjb.0.2020.08.03.17.39.32
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 03 Aug 2020 17:39:34 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [kvm-unit-tests PATCH RESEND v2] x86: tscdeadline timer testing when
 apic disabled
Date: Tue,  4 Aug 2020 08:39:19 +0800
Message-Id: <1596501559-22385-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch adds tscdeadline timer testing when apic is hw disabled.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v1 -> v2:
 * check tscdeadline timer didn't fire

 x86/apic.c | 29 +++++++++++++++++++++++------
 1 file changed, 23 insertions(+), 6 deletions(-)

```
#### [PATCH  v1 1/3] arm64: allow de-selection of ThunderX PCI controllers
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 11700369
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 539A9722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 12:46:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C722208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 12:46:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="T8YDxwS+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726210AbgHDMqQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 08:46:16 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41192 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728311AbgHDMo3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 08:44:29 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0B82AC0617A0
        for <kvm@vger.kernel.org>; Tue,  4 Aug 2020 05:44:24 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id x5so2548582wmi.2
        for <kvm@vger.kernel.org>; Tue, 04 Aug 2020 05:44:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=bN3d8Ia77BH2nBiHDQ6zBNPByWQO01hAGf1Nc3k/FjU=;
        b=T8YDxwS+GAi/l87EqEDVnHA6L2vWdoJLRomogp4zswguktwRhtfY6a3S80oC+la+7Y
         uBOGZPkWUazcUyhEPQsfO3QZ16muTbOfxNxa4uXdYwfXdmkfVzoMRSW4m/T7f0i4RLf7
         dX+k8C7kUSi09yoGq/WkXRUuQWQIUOu80qSJ8B9K9QLhl5toYoFUrNUqUcTwdRw8GrmH
         fMUA0SnmjEveRBv57i02a+TxYyxNXCrEDBzYs7JuFuOONWrjDdCFY0ND5r47wpeLc24V
         fJMl0bur8BNgusZj++pQeoEnXBDmf1q7b4PbFj3Wzq0ri29fof8CCFp8ai4icK9pDdY1
         JhtQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=bN3d8Ia77BH2nBiHDQ6zBNPByWQO01hAGf1Nc3k/FjU=;
        b=NkaEweb9yetJcUncRn7xsPJo7ymD3GUjbl9IZe+2HEpVuVFV+IE6UcvnyaXluCL3Tx
         g6zXtw1z/iuMXszvN7OD7dRELw5wee+EEal0x8odhMV0HhLDQsmQzTONs71Sh81tFGbY
         dBGyh+hTBFr0HvIKirwoQdAJ6ebGGhSrmoyVfnFRLldz0vFIfcCkMeSqDNMVn2Ohc4z7
         7LXzQgKlC73DwJ96ZtdzFCCBTomrM4iU9YPdVjBxrvw0kBtb9ehc/v4sXKk/uU/mRmHc
         L8kdK6hZoAm0lta5pzetmygQcISg04wq7RoAr8t3ktQ2wj+aCbq+0DeaNAgWM0pTTHLs
         YZnQ==
X-Gm-Message-State: AOAM532/u1CQkhlqOb3Obxr5KFWmE7p8WuffHQxzYGATSZjoephTTEYS
        06XLg+jjBTF/ziO2hWYs8wLudg==
X-Google-Smtp-Source: 
 ABdhPJz9A0fUr0s+57vaSQaPT8GQEVwMIBWtT6cib6RQGYxAGZypLJ4R2NHV8/yEEKGRo0R1n0bqCQ==
X-Received: by 2002:a7b:c257:: with SMTP id b23mr3829607wmj.164.1596545062751;
        Tue, 04 Aug 2020 05:44:22 -0700 (PDT)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 b137sm4843577wmb.9.2020.08.04.05.44.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 04 Aug 2020 05:44:18 -0700 (PDT)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id 860581FF87;
        Tue,  4 Aug 2020 13:44:17 +0100 (BST)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Cc: linux-kernel@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 christoffer.dall@arm.com, maz@kernel.org,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Robert Richter <rrichter@marvell.com>, linux-pci@vger.kernel.org
Subject: [PATCH  v1 1/3] arm64: allow de-selection of ThunderX PCI controllers
Date: Tue,  4 Aug 2020 13:44:15 +0100
Message-Id: <20200804124417.27102-2-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200804124417.27102-1-alex.bennee@linaro.org>
References: <20200804124417.27102-1-alex.bennee@linaro.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For a pure VirtIO guest bringing in all the PCI quirk handling adds a
significant amount of bloat to kernel we don't need. Solve this by
adding a CONFIG symbol for the ThunderX PCI devices and allowing it to
be turned off. Saving over 300k from the uncompressed vmlinux:

  -rwxr-xr-x 1 alex alex  85652472 Aug  3 16:48 vmlinux*
  -rwxr-xr-x 1 alex alex  86033880 Aug  3 16:39 vmlinux.orig*

Signed-off-by: Alex Bennée <alex.bennee@linaro.org>
Cc: Robert Richter <rrichter@marvell.com>
Cc: linux-pci@vger.kernel.org
Cc: linux-arm-kernel@lists.infradead.org
---
 arch/arm64/Kconfig.platforms    | 2 ++
 arch/arm64/configs/defconfig    | 1 +
 drivers/pci/controller/Kconfig  | 7 +++++++
 drivers/pci/controller/Makefile | 4 ++--
 4 files changed, 12 insertions(+), 2 deletions(-)

```
#### [PATCH v1] vfio: platform: use platform_get_resource()
##### From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
X-Patchwork-Id: 11700437
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D2C1722
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 13:56:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8089C2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 13:56:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728616AbgHDN4a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 09:56:30 -0400
Received: from mga05.intel.com ([192.55.52.43]:51588 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726887AbgHDN42 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 09:56:28 -0400
IronPort-SDR: 
 voATJnc/sswHb5kLwOpUaMX7IicBrKKf62v1Tn5Z4IOneJk1ljFWE2xAAs0QwS36Z9ocYT7u6v
 gHjOo/ldl8bQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9702"; a="237170552"
X-IronPort-AV: E=Sophos;i="5.75,434,1589266800";
   d="scan'208";a="237170552"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Aug 2020 06:56:26 -0700
IronPort-SDR: 
 57O1IX73IgUM+mN6NBg+lrNuHF+iCZ9XBdzoZgVlBCCoQN5s0nqS40/M2O8FUO5iY7mqivH7gG
 AdexYfJtPnzA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,434,1589266800";
   d="scan'208";a="492901361"
Received: from black.fi.intel.com ([10.237.72.28])
  by fmsmga005.fm.intel.com with ESMTP; 04 Aug 2020 06:56:24 -0700
Received: by black.fi.intel.com (Postfix, from userid 1003)
        id 83A2F11C; Tue,  4 Aug 2020 16:56:23 +0300 (EEST)
From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
To: Eric Auger <eric.auger@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        kvm@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>
Cc: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
Subject: [PATCH v1] vfio: platform: use platform_get_resource()
Date: Tue,  4 Aug 2020 16:56:22 +0300
Message-Id: <20200804135622.11952-1-andriy.shevchenko@linux.intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use platform_get_resource() to fetch the memory resource
instead of open-coded variant.

Signed-off-by: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
---
 drivers/vfio/platform/vfio_platform.c | 16 +++++-----------
 1 file changed, 5 insertions(+), 11 deletions(-)

```
#### [PATCH v2 kvmtool] virtio: Fix ordering of virtio_queue__should_signal()
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11700541
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0390414E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 14:52:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0892222B42
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 14:52:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729200AbgHDOwa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 10:52:30 -0400
Received: from foss.arm.com ([217.140.110.172]:44952 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728097AbgHDOw0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 10:52:26 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2299431B;
        Tue,  4 Aug 2020 07:52:26 -0700 (PDT)
Received: from monolith.localdoman (unknown [10.37.12.88])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D86BE3F718;
        Tue,  4 Aug 2020 07:52:24 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: milon@wq.cz, julien.thierry.kdev@gmail.com, will@kernel.org,
        jean-philippe@linaro.org, andre.przywara@arm.com,
        Anvay Virkar <anvay.virkar@arm.com>
Subject: [PATCH v2 kvmtool] virtio: Fix ordering of
 virtio_queue__should_signal()
Date: Tue,  4 Aug 2020 15:53:17 +0100
Message-Id: <20200804145317.51633-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest programs used_event in the avail ring to let the host know when
it wants a notification from the device. The host notifies the guest when
the used ring index passes used_event. It is possible for the guest to
submit a buffer, and then go into uninterruptible sleep waiting for this
notification.

The virtio-blk guest driver, in the notification callback virtblk_done(),
increments the last known used ring index, then sets used_event to this
value, which means it will get a notification after the next buffer is
consumed by the host. virtblk_done() exits after the value of the used
ring idx has been propagated from the host thread.

On the host side, the virtio-blk device increments the used ring index,
then compares it to used_event to decide if a notification should be sent.

This is a common communication pattern between two threads, called store
buffer. Memory barriers are needed in order for the pattern to work
correctly, otherwise it is possible for the host to miss sending a required
notification.

Initial state: vring.used.idx = 2, vring.used_event = 1 (idx passes
used_event, which means kvmtool notifies the guest).

	GUEST (in virtblk_done())	| KVMTOOL (in virtio_blk_complete())
					|
(increment vq->last_used_idx = 2)	|
// virtqueue_enable_cb_prepare_split():	| // virt_queue__used_idx_advance():
write vring.used_event = 2		| write vring.used.idx = 3
// virtqueue_poll():			|
mb()					| wmb()
// virtqueue_poll_split():		| // virt_queue__should_signal():
read vring.used.idx = 2			| read vring.used_event = 1
// virtblk_done() exits.		| // No notification.

The write memory barrier on the host side is not enough to prevent
reordering of the read in the kvmtool thread, which can lead to the guest
thread waiting forever for IO to complete. Replace it with a full memory
barrier to get the correct store buffer pattern described in the Linux
litmus test SB+fencembonceonces.litmus, which forbids both threads reading
the initial values.

Also move the barrier in virtio_queue__should_signal(), because the barrier
is needed for notifications to work correctly, and it makes more sense to
have it in the function that determines if the host should notify the
guest.

Reported-by: Anvay Virkar <anvay.virkar@arm.com>
Suggested-by: Anvay Virkar <anvay.virkar@arm.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe@linaro.org>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
Changes in v2:
- Updated commit message with suggestions from Jean. Hoping that now it's
  clearer that the hang is caused by kvmtool not implementing the store
  buffer pattern correctly.

I've added a link to the online herd7 memory model tool with the store
buffer pattern [1]. The DMB SY can be replaced with DMB ST in one of
the threads, to mimic what kvmtool does, and the forbidden behaviour
becomes possible.

This was observed by Anvay, where both the guest and kvmtool read the
previous values of used.idx, and used_event respectively. The guest goes
into uninterruptible sleep and the notification is not sent.

I *think* this also fixes the VM hang reported in [2], where several
processes in the guest were stuck in uninterruptible sleep. I am not
familiar with the block layer, but my theory is that the threads were stuck
in wait_for_completion_io(), from blk_execute_rq() executing a flush
request. Milan has agreed to give this patch a spin [3], but that might
take a while because the bug is not easily reproducible. I believe the
patch can be merged on its own.

[1] http://diy.inria.fr/www/index.html?record=aarch64&cat=aarch64-v04&litmus=SB%2Bdmb.sys&cfg=new-web
[2] https://www.spinics.net/lists/kvm/msg204543.html
[3] https://www.spinics.net/lists/kvm/msg222201.html

 virtio/core.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)

```
#### [PATCH v2] x86: tscdeadline timer testing when apic disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11699325
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E85AD13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 00:32:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BD3922CAE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 00:32:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="nWO/47bG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729279AbgHDAcB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 20:32:01 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41488 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729221AbgHDAcA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 20:32:00 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B4A25C06174A
        for <kvm@vger.kernel.org>; Mon,  3 Aug 2020 17:32:00 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id o13so21157889pgf.0
        for <kvm@vger.kernel.org>; Mon, 03 Aug 2020 17:32:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ai8WbK+SXwuJDxkBKbMxeQLFCKmPAxXHO5IzqCRJqVQ=;
        b=nWO/47bGThgdVWwFmm/sXPM+Pkhj9f5jB7BK/bARXm/59F0OAi3Pnq2f/QFly+e8X2
         kPql01AcjTjHQzAoG2ARe/+KfCKPYwk01I8UwKvAdKWvpAClVIBUTPpGHhe/6fdTFBo0
         do37T6PeNbAFHzOXq3DTPg/1MHemey/TRnsqHCznYMRmXe5fDnQzMS6fexVCJ20gte6l
         Z3MGUvrKGD3wJwJ+X+wYQ/EAnNngba+7scdMzxJvMB4+4Rl6v7ALAjpuskrPnGtUKhwU
         gPWq9nmep0z8vOQG3JbNmdU5cRp69PAYjpVLGxZTpRg4EXmjc9SQXviIlEQiGeiAvO0x
         eb2w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ai8WbK+SXwuJDxkBKbMxeQLFCKmPAxXHO5IzqCRJqVQ=;
        b=EKVijLCKjUTye1+7lkPrFDN1stCGG0gXWvw+o1e+NUyQSygwgNdTWx08CMWfDzvu63
         chiozg4kH4ZBRiysxyHSmoOZWclvxjX8444DUJaShCKE8y+BaKZ+onxxiXL/qjGE27BK
         XgibG/VkHVQBFcX0FZ5w4co0K9hH8fOiZKwKKZBqhg9XkfveN63XU7ABcrMwqBZD/8sJ
         heVg418ypqN27SXdeP7GvLR5VZkuFW2bYFOOmmXPIY9uOyw+ooc2u5zNnh94JkkzkhuS
         aHEGrGJ641CSwloTM4FBEBNcr7u7/HLQR968k3PA5stT1TH30EUBr2KbFdR/TK5nDgQM
         OVQQ==
X-Gm-Message-State: AOAM530rAu5W7QbbndQr8EHqIHNkslbeVumA135Nbbmeb2+7OS2oVl2w
        sVrnUUil3jY6oSSFJIfFRte+JfkI
X-Google-Smtp-Source: 
 ABdhPJzzM8dc24JxlNdGyMx3aclJAJ8LBSFX5LszRE/moZVybJwdBjWtO3EqdK343GxogtHJFGl4cw==
X-Received: by 2002:a62:1951:: with SMTP id 78mr18280488pfz.137.1596501119886;
        Mon, 03 Aug 2020 17:31:59 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 e3sm19950714pgu.40.2020.08.03.17.31.57
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 03 Aug 2020 17:31:59 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] x86: tscdeadline timer testing when apic disabled
Date: Tue,  4 Aug 2020 08:31:50 +0800
Message-Id: <1596501110-22239-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

This patch adds tscdeadline timer testing when apic is hw disabled.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 x86/apic.c | 29 +++++++++++++++++++++++------
 1 file changed, 23 insertions(+), 6 deletions(-)

```
#### [PATCH] vDPA: dont change vq irq after DRIVER_OK
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11700195
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90FB413B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 10:24:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A962022CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 10:24:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726282AbgHDKYW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 06:24:22 -0400
Received: from mga01.intel.com ([192.55.52.88]:27856 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726041AbgHDKYV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 06:24:21 -0400
IronPort-SDR: 
 pGgonrDIf3FCYUPilCyJI7mjUfEsSkaP7/R6F6R+TnGNlbz99g2tmII5nZ0DiPTcq0fP9DufuZ
 Jau4IqwTrW6Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9702"; a="170370091"
X-IronPort-AV: E=Sophos;i="5.75,433,1589266800";
   d="scan'208";a="170370091"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Aug 2020 03:24:21 -0700
IronPort-SDR: 
 86o3INU0VufP9AJUY0ckrtrmVzSO3vgJqrYDM5ELIDtL/cHRB0+ZKUiRCQhpZtJwebCAVpRgJB
 xz0gEKowJIMQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,433,1589266800";
   d="scan'208";a="288512752"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga003.jf.intel.com with ESMTP; 04 Aug 2020 03:24:19 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] vDPA: dont change vq irq after DRIVER_OK
Date: Tue,  4 Aug 2020 18:20:21 +0800
Message-Id: <20200804102021.69917-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IRQ of a vq is not expected to be changed in a DRIVER_OK ~ !DRIVER_OK
period for irq offloading purposes. Place this comment at the side of
bus ops get_vq_irq than in set_status in vhost_vdpa.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c | 1 -
 include/linux/vdpa.h | 1 +
 2 files changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vDPA: dont change vq irq after DRIVER_OK
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11700197
Return-Path: <SRS0=wIAV=BO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61B9F13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 10:25:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B1402177B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  4 Aug 2020 10:25:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728401AbgHDKZ2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 4 Aug 2020 06:25:28 -0400
Received: from mga05.intel.com ([192.55.52.43]:29375 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726041AbgHDKZZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 Aug 2020 06:25:25 -0400
IronPort-SDR: 
 B93MxYmO4K3WeJ3o2QVOa8Bdk9By1tAfxEQft+BTVuQy1ki8fi0L3g615Rh2USfv9ysIw+v1S5
 6jIQoyyp/DAA==
X-IronPort-AV: E=McAfee;i="6000,8403,9702"; a="237146609"
X-IronPort-AV: E=Sophos;i="5.75,433,1589266800";
   d="scan'208";a="237146609"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Aug 2020 03:25:25 -0700
IronPort-SDR: 
 /0RVEfgju9VaF9xmo8ygzfV/HOYmfFaIf2GRKeBWFsOMbiohTJlfu1lhlD65XmfvJziaMnydV3
 Nv3Gendtu4qQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,433,1589266800";
   d="scan'208";a="330560245"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by FMSMGA003.fm.intel.com with ESMTP; 04 Aug 2020 03:25:23 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] vDPA: dont change vq irq after DRIVER_OK
Date: Tue,  4 Aug 2020 18:21:23 +0800
Message-Id: <20200804102123.69978-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IRQ of a vq is not expected to be changed in a DRIVER_OK ~ !DRIVER_OK
period for irq offloading purposes. Place this comment at the side of
bus ops get_vq_irq than in set_status in vhost_vdpa.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vdpa.c | 1 -
 include/linux/vdpa.h | 1 +
 2 files changed, 1 insertion(+), 1 deletion(-)

```
