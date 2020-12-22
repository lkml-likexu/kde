

#### [PATCH 0/9] Alpine Linux build fix and CI pipeline
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
From patchwork Mon Dec 21 00:53:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11984051
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 576C3C433E6
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 00:54:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 294A2221EC
	for <kvm@archiver.kernel.org>; Mon, 21 Dec 2020 00:54:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726537AbgLUAyl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 20 Dec 2020 19:54:41 -0500
Received: from new2-smtp.messagingengine.com ([66.111.4.224]:38821 "EHLO
        new2-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725956AbgLUAyk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 20 Dec 2020 19:54:40 -0500
Received: from compute6.internal (compute6.nyi.internal [10.202.2.46])
        by mailnew.nyi.internal (Postfix) with ESMTP id B230C5803E8;
        Sun, 20 Dec 2020 19:53:34 -0500 (EST)
Received: from mailfrontend1 ([10.202.2.162])
  by compute6.internal (MEProxy); Sun, 20 Dec 2020 19:53:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=flygoat.com; h=
        from:to:cc:subject:date:message-id:mime-version
        :content-transfer-encoding; s=fm1; bh=sUtRj3NPtex5SKNHchbwBlkxCW
        UTwtJkEMqd19YdEoo=; b=rb3+vnOYw47nGA793QjNFj305dzdpLD0QiQPynvhsx
        Ow1dPKfaRS147GloYsVpnqAaJ5lRUvW2VJcONc921QpDCWb5P9hoUgXuCh4EJ4uO
        /qjJaE1ghoREl/tXvXcxg/2aBxtDUrbniwtEJK7RaEK8BjJwNFydQ9ys/q2ocUZG
        ioDSU4KEEQB7zWyXc6GE7gcNPA0NIDaZHg0Xr8+V5HIZ5b4poukzNj1FtNJALZt8
        aWuSX6UvBEtyS3KHgipa9KFcku5UfMDqOaMEj12RgN6c7TB82QtvQxX95oppndmJ
        sb0EndTvPdGZmKsCIUASAFFIN7msMA0TYcs374Qjk4SA==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :message-id:mime-version:subject:to:x-me-proxy:x-me-proxy
        :x-me-sender:x-me-sender:x-sasl-enc; s=fm1; bh=sUtRj3NPtex5SKNHc
        hbwBlkxCWUTwtJkEMqd19YdEoo=; b=dOLFE8uc6ZJIIZoxWj5Xym7QRVGeUMcms
        VwGPlcFrC4f1eBQxjbxbEG9F9BW3+zY/tUChD1BPSq+YydnIud8TSa+3omR4RJkX
        TYXeNDC7biKtYnDzhIGgTwvGzBaX5IPxApz/6fjSAospZvr1VGrc2tMZeMSifdTU
        RN97AG8qxnC5VmH5qki2Sdr0/9v/I+1bq5/X4iBFtQ6PZpdS0ZcsHSFAv6GTw3CH
        O8pVLGhowHfmHr5mCECRo7KW5wU/7QwHvWqI9+KZOtY7iJVU/9fez9cVN+AXFehH
        Lyd0WYzzGCgRg5xk8ojigIaoq7d0Pf5eyoJvaRdppQAIJHHOWZ9Lw==
X-ME-Sender: <xms:DPLfX_Qby4D_Z-T_otFR0awzCRzM_eWzY6DxSo1W0xBa98NI04Bu2Q>
    <xme:DPLfXww7fvYz5BwIjFVq1ermLCS5WdZjVBkmMpOhsTF_kdfd82371ol_Bj28dKPUS
    f1uJIJU91wu4FiUUks>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgedujedrvddtuddgvdekucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffoggfgsedtkeertdertddtnecuhfhrohhmpeflihgrgihunhcu
    jggrnhhguceojhhirgiguhhnrdihrghnghesfhhlhihgohgrthdrtghomheqnecuggftrf
    grthhtvghrnhepffdtheduudetvdeijefgjeegleeiudeikeekjeffheeiteejffduiefh
    leehvedunecuffhomhgrihhnpegrlhhpihhnvghlihhnuhigrdhorhhgpdhgihhtlhgrsg
    drtghomhenucfkphepgeehrdeffedrhedtrddvheegnecuvehluhhsthgvrhfuihiivgep
    tdenucfrrghrrghmpehmrghilhhfrhhomhepjhhirgiguhhnrdihrghnghesfhhlhihgoh
    grthdrtghomh
X-ME-Proxy: <xmx:DPLfX01EPCvMjPPRWlIdC2ZvexfT6qmWqo9YEgZIMfUbzK8s3EuP_g>
    <xmx:DPLfX_Cu5Y8jXiaGj7XHEQg0vvvwJVTl6MZN1XzYO_eJd-OfyHYLJQ>
    <xmx:DPLfX4jgekGth9QEmV8rRSV_5fm4pcJBhZIeGWfn2WYrxzxx3nr01w>
    <xmx:DvLfX47_ys_J75tgycK8JorROAT7nEQHrm4q-KZh6pKEibCqmxtDBZWbkiBNOryd>
Received: from strike.U-LINK.com (li1000-254.members.linode.com
 [45.33.50.254])
        by mail.messagingengine.com (Postfix) with ESMTPA id 7995B24005A;
        Sun, 20 Dec 2020 19:53:24 -0500 (EST)
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
Subject: [PATCH 0/9] Alpine Linux build fix and CI pipeline
Date: Mon, 21 Dec 2020 08:53:09 +0800
Message-Id: <20201221005318.11866-1-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Alpine Linux[1] is a security-oriented, lightweight Linux distribution
based on musl libc and busybox.

It it popular among Docker guests and embedded applications.

Adding it to test against different libc.

[1]: https://alpinelinux.org/

Tree avilable at: https://gitlab.com/FlyGoat/qemu/-/tree/alpine_linux_v1

Jiaxun Yang (9):
  tests/docker: Add dockerfile for Alpine Linux
  configure: Add sys/timex.h to probe clk_adjtime
  configure/meson: Only check sys/signal.h on non-Linux
  libvhost-user: Include poll.h instead of sys/poll.h
  elf2dmp: Rename PAGE_SIZE to ELF2DMP_PAGE_SIZE
  hw/block/nand: Rename PAGE_SIZE to NAND_PAGE_SIZE
  accel/kvm: avoid using predefined
  tests: Rename PAGE_SIZE definitions
  gitlab-ci: Add alpine to pipeline

 .gitlab-ci.d/containers.yml               |  5 ++
 .gitlab-ci.yml                            | 23 ++++++++
 accel/kvm/kvm-all.c                       |  3 +
 configure                                 |  1 +
 contrib/elf2dmp/addrspace.c               |  4 +-
 contrib/elf2dmp/addrspace.h               |  6 +-
 contrib/elf2dmp/main.c                    | 18 +++---
 hw/block/nand.c                           | 40 ++++++-------
 meson.build                               |  5 +-
 subprojects/libvhost-user/libvhost-user.h |  2 +-
 tests/docker/dockerfiles/alpine.docker    | 56 ++++++++++++++++++
 tests/migration/stress.c                  | 10 ++--
 tests/qtest/libqos/malloc-pc.c            |  4 +-
 tests/qtest/libqos/malloc-spapr.c         |  4 +-
 tests/qtest/m25p80-test.c                 | 54 ++++++++---------
 tests/tcg/multiarch/system/memory.c       |  6 +-
 tests/test-xbzrle.c                       | 70 +++++++++++------------
 17 files changed, 201 insertions(+), 110 deletions(-)
 create mode 100644 tests/docker/dockerfiles/alpine.docker
```
