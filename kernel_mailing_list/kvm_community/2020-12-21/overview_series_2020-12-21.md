#### [PATCH 1/9] tests/docker: Add dockerfile for Alpine Linux
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11984049
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45820C433DB
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 00:54:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D63C21D95
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 00:54:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726509AbgLUAy1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 20 Dec 2020 19:54:27 -0500
Received: from new2-smtp.messagingengine.com ([66.111.4.224]:44175 "EHLO
        new2-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726027AbgLUAy1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 20 Dec 2020 19:54:27 -0500
Received: from compute6.internal (compute6.nyi.internal [10.202.2.46])
        by mailnew.nyi.internal (Postfix) with ESMTP id 1AB015803F8;
        Sun, 20 Dec 2020 19:53:41 -0500 (EST)
Received: from mailfrontend1 ([10.202.2.162])
  by compute6.internal (MEProxy); Sun, 20 Dec 2020 19:53:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=flygoat.com; h=
        from:to:cc:subject:date:message-id:in-reply-to:references
        :mime-version:content-transfer-encoding; s=fm1; bh=ld7CKW5vB77WI
        lvV4wV47qN/agE7Mm627Lyt8Dw6I+8=; b=VbDRe6BhmOr/FLXZ04jZwqRWcsiSE
        +mZ5syHy6w3ggZ2WvyAIvV+UGj2dwVPGx5lUgGnZFoNQcIv7Wn/o8AjOwvMOoerr
        tzeDagLJ2Yfc1uoR3krKhWLWVdW83zaC2ifhxVT7ojsyDFOczjFlH4ATPKrzYm7x
        Rk3esHNtiRPaJaFcDTxsZ3vE7yf0ElFrClmMVadSnwIc7TFTy/8bIUFoQCD4E6q+
        vkzswXkYNBsHxKFExC+1WCRFcdVE2pWkAqCDhC+LBogClPaDUP4VEY9IzypBdh/S
        aLjjADp8KPv7s3me94Z+7IVeyt55nBXL/ip94GP+3VsZkn56UYUBlkNKg==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :in-reply-to:message-id:mime-version:references:subject:to
        :x-me-proxy:x-me-proxy:x-me-sender:x-me-sender:x-sasl-enc; s=
        fm1; bh=ld7CKW5vB77WIlvV4wV47qN/agE7Mm627Lyt8Dw6I+8=; b=DP8AhrES
        wUBmG1vdl7vtLE97r+OrKSVGunFvkFQQbgdiFf4RKmhIHlyyDRh2msAjWlAFD2mB
        O8iFSsCckNMRGEfNODCRv5CeuF3L0z+q0eeQn0CN6NLsIuPt/QmuMLPkRk2aw1oi
        5Hopcb/w8yfR+25IrBXn/a6+rJncsGTaEVDuiuzmTOO8MGmFG9QkM7jKdcBBVRk0
        iSCrlIW6BP2JOuXCsExvVw51pn+D+Xpl4U8Ndt0wA6FooHxjUobzi/bOnX7SeeZX
        NaL2Z17EJdYz8ob1nE7aMGeIUb48kMinTu1N9tn4RSx15lthfA8sTfooWzgyGrCI
        obshvFFBdZvdkQ==
X-ME-Sender: <xms:FPLfX24a8VisuVr_LPH-sqUNNoxM06by7-F2y8phaJmzRbFPazA2dw>
    <xme:FPLfX_4wxYWX6nR0zZ1idZkYflGWi1lYBhSWVM0qPe61CjPq9t6vjsK4nMC9YKUDs
    VijTEhWCjhTlkW0GKY>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgedujedrvddtuddgvdekucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffojghfggfgsedtkeertdertddtnecuhfhrohhmpeflihgrgihu
    nhcujggrnhhguceojhhirgiguhhnrdihrghnghesfhhlhihgohgrthdrtghomheqnecugg
    ftrfgrthhtvghrnhepjeeuhfekgeehhefftefgueevuedvueekveekieegudfhhffgvddv
    heehhfffhfdunecuffhomhgrihhnpegrlhhpihhnvghlihhnuhigrdhorhhgnecukfhppe
    eghedrfeefrdehtddrvdehgeenucevlhhushhtvghrufhiiigvpedtnecurfgrrhgrmhep
    mhgrihhlfhhrohhmpehjihgrgihunhdrhigrnhhgsehflhihghhorghtrdgtohhm
X-ME-Proxy: <xmx:FPLfX1dogoQ3mhTe_E3EtuRa1puwsO-A0JH-D8IDh4G2rTdA1tTVSg>
    <xmx:FPLfXzIDXHzP4lH9w-JwSz_kCE1opnrjgx_Yy7Is316RO-VPzV6uuQ>
    <xmx:FPLfX6IMaChvbEp2_6a2XZCLcOV68e7IEzHuQ3rdQ9EYPMPCw_Q2Og>
    <xmx:FPLfX8j1NJSusrn0wJNIDurb048IU7JL5JaihxM6LwD6voiTzv7c5mdE26P2YMP1>
Received: from strike.U-LINK.com (li1000-254.members.linode.com
 [45.33.50.254])
        by mail.messagingengine.com (Postfix) with ESMTPA id A112F24005C;
        Sun, 20 Dec 2020 19:53:33 -0500 (EST)
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: qemu-devel@nongnu.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>, Thomas Huth <thuth@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>, =?utf-8?q?Alex?=
	=?utf-8?q?_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Viktor Prutyanov <viktor.prutyanov@phystech.edu>,
 Kevin Wolf <kwolf@redhat.com>, Max Reitz <mreitz@redhat.com>,
 Fam Zheng <fam@euphon.net>, Laurent Vivier <lvivier@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Greg Kurz <groug@kaod.org>,
 Alistair Francis <alistair@alistair23.me>, kvm@vger.kernel.org,
 qemu-block@nongnu.org, qemu-ppc@nongnu.org
Subject: [PATCH 1/9] tests/docker: Add dockerfile for Alpine Linux
Date: Mon, 21 Dec 2020 08:53:10 +0800
Message-Id: <20201221005318.11866-2-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201221005318.11866-1-jiaxun.yang@flygoat.com>
References: <20201221005318.11866-1-jiaxun.yang@flygoat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Alpine Linux[1] is a security-oriented, lightweight Linux distribution
based on musl libc and busybox.

It it popular among Docker guests and embedded applications.

Adding it to test against different libc.

[1]: https://alpinelinux.org/

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
---
 tests/docker/dockerfiles/alpine.docker | 56 ++++++++++++++++++++++++++
 1 file changed, 56 insertions(+)
 create mode 100644 tests/docker/dockerfiles/alpine.docker

diff --git a/tests/docker/dockerfiles/alpine.docker b/tests/docker/dockerfiles/alpine.docker
new file mode 100644
index 0000000000..a1b80f08d2
--- /dev/null
+++ b/tests/docker/dockerfiles/alpine.docker
@@ -0,0 +1,56 @@
+
+FROM alpine:edge
+
+RUN apk update
+RUN apk upgrade
+
+# Please keep this list sorted alphabetically
+ENV PACKAGES \
+	alsa-lib-dev \
+	bash \
+	bison \
+	build-base \
+	coreutils \
+	curl-dev \
+	flex \
+	git \
+	glib-dev \
+	glib-static \
+	gnutls-dev \
+	gtk+3.0-dev \
+	libaio-dev \
+	libcap-dev \
+	libcap-ng-dev \
+	libjpeg-turbo-dev \
+	libnfs-dev \
+	libpng-dev \
+	libseccomp-dev \
+	libssh-dev \
+	libusb-dev \
+	libxml2-dev \
+	linux-headers \
+	lzo-dev \
+	mesa-dev \
+	mesa-egl \
+	mesa-gbm \
+	meson \
+	ncurses-dev \
+	ninja \
+	paxmark \
+	perl \
+	pulseaudio-dev \
+	python3 \
+	py3-sphinx \
+	snappy-dev \
+	spice-dev \
+	texinfo \
+	usbredir-dev \
+	util-linux-dev \
+	vde2-dev \
+	virglrenderer-dev \
+	vte3-dev \
+	xfsprogs-dev \
+	zlib-dev \
+	zlib-static
+
+RUN apk add $PACKAGES

From patchwork Mon Dec 21 00:53:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11984055
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90385C433E0
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 00:55:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5864A21D95
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 00:55:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726589AbgLUAyz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 20 Dec 2020 19:54:55 -0500
Received: from new2-smtp.messagingengine.com ([66.111.4.224]:46517 "EHLO
        new2-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725956AbgLUAyz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 20 Dec 2020 19:54:55 -0500
Received: from compute6.internal (compute6.nyi.internal [10.202.2.46])
        by mailnew.nyi.internal (Postfix) with ESMTP id 536F2580413;
        Sun, 20 Dec 2020 19:53:49 -0500 (EST)
Received: from mailfrontend1 ([10.202.2.162])
  by compute6.internal (MEProxy); Sun, 20 Dec 2020 19:53:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=flygoat.com; h=
        from:to:cc:subject:date:message-id:in-reply-to:references
        :mime-version:content-transfer-encoding; s=fm1; bh=KWLNfn6cch3ST
        kJIn9ZITmEXeddtBMzmWKV1IAEIciA=; b=SIelJS4Fke3A/aeRfSeo5JZd7hpoo
        lGPByjwCuuxZZSdIaz5cO5929SskOcL0ukg0hPUgyWQuvuGqm7lg/ObLoHZbMvBY
        xfdkJ9zqRhXOIUPTAuf6YuZLXp+XMLtd/MzkCTM/B/sP58UI0XrIMJhtCjf6zTK1
        B3wv3LCN3BJOmT/6DdNQWM8QKAmKd/qfAj22xjk+6mCFiiVpNRcxq7NMK0Flo75v
        /U95VeXOXneGZw9zeDMnRpWH9bOwG8T+WARTQuGsFcr8AwjNr/DLejg2g/kIvLOH
        K80WrgvFTPeowZCv1YJifdyS6g955nYxkCC+2mG28cGMF7S6/XXSl3IHg==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :in-reply-to:message-id:mime-version:references:subject:to
        :x-me-proxy:x-me-proxy:x-me-sender:x-me-sender:x-sasl-enc; s=
        fm1; bh=KWLNfn6cch3STkJIn9ZITmEXeddtBMzmWKV1IAEIciA=; b=TdJUcTr4
        tJAhXwVjbuSZj2bwRxiwq3vjLrSeGQJhBOxVsxauF1dRlQxau4X89dB8t+iVW8EO
        BrFTJevYoqc1S7HC0N9M2IsKxW+OFc8O4h4BeODsAqw2yEoPqPCri9RHE/mBvKgO
        23/XADnLaiLPa7OGVzWqsdRibjcgUetjU3yPx2cZlBwqov6eLwcC1xnlE9Vqc549
        4QPXmmOwJ4ENMshP2Kdyqrc4EpPrDM8Yeexw57Gsbb/dXXdLKOxlGLw78ipee+Mx
        VOi3EqRJzMpUx8djRCzGqsGelVw+2EjXXpqGPXsgyN2xyyF1inWWQayYouqj5hQp
        jMxdXVOz33Vz9w==
X-ME-Sender: <xms:HPLfXzE5WPIREl4Aa5KPmO_-btAmCMXTG6QfeDBm0U4zyAhYPwOa9Q>
    <xme:HPLfXwV8FPKLkeF6mTKWkSWrxC49-cOfhJfjRg-lP1-kUwsZiOyipOvcHelbv9GFh
    6XnEYVVIwk3onwT-8I>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgedujedrvddtuddgvdekucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffojghfggfgsedtkeertdertddtnecuhfhrohhmpeflihgrgihu
    nhcujggrnhhguceojhhirgiguhhnrdihrghnghesfhhlhihgohgrthdrtghomheqnecugg
    ftrfgrthhtvghrnhepjeeihffgteelkeelffdukedtheevudejvdegkeekjeefhffhhfet
    udetgfdtffeunecukfhppeeghedrfeefrdehtddrvdehgeenucevlhhushhtvghrufhiii
    gvpedtnecurfgrrhgrmhepmhgrihhlfhhrohhmpehjihgrgihunhdrhigrnhhgsehflhih
    ghhorghtrdgtohhm
X-ME-Proxy: <xmx:HPLfX1KkIRxG_Ykal9Up_fkfsPPDCsoR2__lED_Wc8lmgbWB9o5OoA>
    <xmx:HPLfXxEPcBCBla-cwjKt1tjuKmsmar9qh9byjfQ3vMqfhBLPcOuTkw>
    <xmx:HPLfX5V0L4vcwQQKUFsxwoqBXyhdXYTQ-swo_GMvyrRCwhvTEr5pJg>
    <xmx:HfLfX6tYE8V6oc3zFe1YgpRfrG_5yKbEsaCX0mOD8S21Mg_REO-yJfo-rqAk8fkq>
Received: from strike.U-LINK.com (li1000-254.members.linode.com
 [45.33.50.254])
        by mail.messagingengine.com (Postfix) with ESMTPA id 7E63A240057;
        Sun, 20 Dec 2020 19:53:41 -0500 (EST)
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: qemu-devel@nongnu.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>, Thomas Huth <thuth@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>, =?utf-8?q?Alex?=
	=?utf-8?q?_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Viktor Prutyanov <viktor.prutyanov@phystech.edu>,
 Kevin Wolf <kwolf@redhat.com>, Max Reitz <mreitz@redhat.com>,
 Fam Zheng <fam@euphon.net>, Laurent Vivier <lvivier@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Greg Kurz <groug@kaod.org>,
 Alistair Francis <alistair@alistair23.me>, kvm@vger.kernel.org,
 qemu-block@nongnu.org, qemu-ppc@nongnu.org
Subject: [PATCH 2/9] configure: Add sys/timex.h to probe clk_adjtime
Date: Mon, 21 Dec 2020 08:53:11 +0800
Message-Id: <20201221005318.11866-3-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20201221005318.11866-1-jiaxun.yang@flygoat.com>
References: <20201221005318.11866-1-jiaxun.yang@flygoat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is not a part of standard time.h. Glibc put it under
time.h however musl treat it as a sys timex extension.

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
---
 configure | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3] KVM/x86: Move definition of __ex to x86.h
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11985279
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0F64C433DB
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 19:49:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BF31F22C9C
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 19:49:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725849AbgLUTt0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 21 Dec 2020 14:49:26 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37024 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725780AbgLUTt0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Dec 2020 14:49:26 -0500
Received: from mail-ed1-x52f.google.com (mail-ed1-x52f.google.com
 [IPv6:2a00:1450:4864:20::52f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 972AEC0613D3;
        Mon, 21 Dec 2020 11:48:45 -0800 (PST)
Received: by mail-ed1-x52f.google.com with SMTP id i24so10725960edj.8;
        Mon, 21 Dec 2020 11:48:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=REHRRpEqcqIxtzDgCEnLfnlCBNOPVwyGaF2sWG0peaw=;
        b=I75EkRKy9tco2xXRkMTScAvl0XTsFdcdghintw0/yakTylDRDM0gY0iwi/2B1f0LMI
         KybCNLMyFEx5wL+UY9IMHQrheJEYGLXeno66GKp8M2xyeCFgk3rUxvJhyt8SyuZp93+z
         DIXtFRzPnrVn//ijRv6ZsF9hbnOrvOzBDQCPILTih8MckZWCPfCInQySmzmMfDdMhVJq
         DWE3KoDdWQjdk8lnHQ/R5yoKuAm501e3/qp8nksov+UcM8kf/KewUDDMQVxcZVrqkDHs
         rZD8Jivs82lgws0/dVrDqsHo1Ep3jyzpO5yBMHNyVlee455JOTibQHKKhxWs+5t2pycr
         c5Zw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=REHRRpEqcqIxtzDgCEnLfnlCBNOPVwyGaF2sWG0peaw=;
        b=WX/Cj8tLagua4Hl4K4gUUxE/VPVxJHTa4vPB/bIUY+c4Nh2L+HRnVuzLZnxhQucUzb
         GIJ5CkGHdqJp7kp/yynzHjgT9dtOOAhLPFYDgV3IVcCRDAmJaN2Ipsv/2gNpz+9vtLPU
         +Lu6XzhOlley/KLjpQyWqVMnz8Ro1hz6Clkhd/jWtuzYVV66+5UHRvkorVsM9V6pZ3Ms
         5K/dGlxhczgdvuJvH1CjXf/2bEAvuEjwAQgP3tyd06uGntYfHtOaUWwh+6woVtSw0q83
         S+plRabQp0+FRAzly1PCyxmtHdmjxjVo6etEeZ3LXhwyKH7cfJ4YFsGytRzkNvSv0Kpe
         nAQg==
X-Gm-Message-State: AOAM532AYWguduLASa3zx2FkQr7uK/Dfbk0o+Kyho4f453SJ4diimLnV
        x6qxmST5r/ZNx3Muo/fYcNcOfOdZVvFP6g==
X-Google-Smtp-Source: 
 ABdhPJx6v9VyJ2Qck17brnwjDjndTtBIhNvf5t6aDkT7+bbFSUQiA4206Z/iyEWbbZazfWPw2X4OLQ==
X-Received: by 2002:a50:c3c5:: with SMTP id i5mr17332512edf.166.1608580123766;
        Mon, 21 Dec 2020 11:48:43 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 qp16sm9450347ejb.74.2020.12.21.11.48.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 21 Dec 2020 11:48:43 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH v3] KVM/x86: Move definition of __ex to x86.h
Date: Mon, 21 Dec 2020 20:48:00 +0100
Message-Id: <20201221194800.46962-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Merge __kvm_handle_fault_on_reboot with its sole user
and move the definition of __ex to a common include to be
shared between VMX and SVM.

v2: Rebase to the latest kvm/queue.

v3: Incorporate changes from review comments.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/kvm_host.h | 25 -------------------------
 arch/x86/kvm/svm/sev.c          |  2 --
 arch/x86/kvm/svm/svm.c          |  2 --
 arch/x86/kvm/vmx/vmx.c          |  4 +---
 arch/x86/kvm/vmx/vmx_ops.h      |  4 +---
 arch/x86/kvm/x86.h              | 24 ++++++++++++++++++++++++
 6 files changed, 26 insertions(+), 35 deletions(-)

```
#### [PATCH v4] s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11985225
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 148A7C433E6
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 18:57:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CFF29225AC
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 18:57:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726000AbgLUS5R (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 21 Dec 2020 13:57:17 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17212 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725883AbgLUS5Q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 21 Dec 2020 13:57:16 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BLIht5P076431;
        Mon, 21 Dec 2020 13:56:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=kbzJ7ryv5p0ZhVmMAUh4iYRadSfOtNqvQimC3qmEzr4=;
 b=NYwSTIrM6c5YtXbTQWRM78oYqSJTJwQXBzEWD0WWdK9oQIgGUtX2/CkoCJ2h6GAbhRNd
 aJJCzrCymeb8yKyo8ae6YaAGeAQP8yNIqSCp4vWkxsH/FaSUu88hchdhNCsZ/iy/9v+q
 c46GxlWwNzM4eHAMlh7gyTDIgbHIDhBpUDfQNwEyyPWEU0M944cyQ8o2xI0mNdJ7NgZ9
 CUbDztWXv7KksgOtGJWq+5khidr3Hm2gcbdx6rAa7DF8pHoPbpI3GyIAo1/1dGR+IQCo
 8xQ30G3YZ2Rbj/Cv/+RpIUcMgIutruwfeCPJB1wU+TOMaVzzn+ApLGLXEkA0bhkCTz4F 4g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35k181r9mq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 21 Dec 2020 13:56:35 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BLIiUt3080528;
        Mon, 21 Dec 2020 13:56:35 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 35k181r9mb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 21 Dec 2020 13:56:35 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BLIr7kp031425;
        Mon, 21 Dec 2020 18:56:34 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma02dal.us.ibm.com with ESMTP id 35h958wn7k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 21 Dec 2020 18:56:34 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BLIuWWL19857870
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 21 Dec 2020 18:56:32 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E26F6E04C;
        Mon, 21 Dec 2020 18:56:32 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5F9AF6E04E;
        Mon, 21 Dec 2020 18:56:31 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.193.150])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 21 Dec 2020 18:56:31 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Subject: [PATCH v4] s390/vfio-ap: clean up vfio_ap resources when KVM pointer
 invalidated
Date: Mon, 21 Dec 2020 13:56:25 -0500
Message-Id: <20201221185625.24914-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-21_10:2020-12-21,2020-12-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=0 adultscore=0 mlxlogscore=999 priorityscore=1501 mlxscore=0
 phishscore=0 clxscore=1015 spamscore=0 impostorscore=0 bulkscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012210128
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_ap device driver registers a group notifier with VFIO when the
file descriptor for a VFIO mediated device for a KVM guest is opened to
receive notification that the KVM pointer is set (VFIO_GROUP_NOTIFY_SET_KVM
event). When the KVM pointer is set, the vfio_ap driver takes the
following actions:
1. Stashes the KVM pointer in the vfio_ap_mdev struct that holds the state
   of the mediated device.
2. Calls the kvm_get_kvm() function to increment its reference counter.
3. Sets the function pointer to the function that handles interception of
   the instruction that enables/disables interrupt processing.
4. Sets the masks in the KVM guest's CRYCB to pass AP resources through to
   the guest.

In order to avoid memory leaks, when the notifier is called to receive
notification that the KVM pointer has been set to NULL, the vfio_ap device
driver should reverse the actions taken when the KVM pointer was set.

Fixes: 258287c994de ("s390: vfio-ap: implement mediated device open callback")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 42 +++++++++++++++++--------------
 1 file changed, 23 insertions(+), 19 deletions(-)

```
