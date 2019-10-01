#### [kvm-unit-tests PATCH 1/3] lib: arm64: Add missing ISB in flush_tlb_page
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11166807
Return-Path: <SRS0=huOb=XZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44236112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 14:25:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B4EA21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 14:25:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731673AbfI3OZR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 10:25:17 -0400
Received: from foss.arm.com ([217.140.110.172]:55534 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731503AbfI3OZR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Sep 2019 10:25:17 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A8F061570;
        Mon, 30 Sep 2019 07:25:16 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 9799E3F706;
        Mon, 30 Sep 2019 07:25:15 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, maz@kernel.org,
        mark.rutland@arm.com, andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH 1/3] lib: arm64: Add missing ISB in
 flush_tlb_page
Date: Mon, 30 Sep 2019 15:25:06 +0100
Message-Id: <20190930142508.25102-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190930142508.25102-1-alexandru.elisei@arm.com>
References: <20190930142508.25102-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linux commit d0b7a302d58a made it abundantly clear that certain CPU
implementations require an ISB after a DSB. Add the missing ISB to
flush_tlb_page. No changes are required for flush_tlb_all, as the function
already had the ISB.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm64/asm/mmu.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] kvm: x86, powerpc: do not allow clearing largepages debugfs entry
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11166957
Return-Path: <SRS0=huOb=XZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8B58E15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 16:52:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 60754215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 16:52:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="ZKFO2Gko"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730095AbfI3Qwk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 12:52:40 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:55050 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726425AbfI3Qwk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Sep 2019 12:52:40 -0400
Received: by mail-wm1-f65.google.com with SMTP id p7so238636wmp.4;
        Mon, 30 Sep 2019 09:52:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=S4meV0NsaDpqLa7tBEXkvORH5DuiHJR7oObrl4NCVW4=;
        b=ZKFO2GkolErFUr68Pj8DzLdvfmN6K47nQm/2ypFNwkvAju1BtuE3hjRdgIslfArdCz
         tcSel3xQCWbcB9PQrXVWPcuH3PEHd/hwfhCl2SuSzh4zQFu09bkn5UKDvsSgV48XA3IQ
         wTXguVJwJVOrG22nKLayzi1SKn+1HdpDfx2i0URglXV/jfSSRFtVyGVfpdOy0GnJLv/8
         ojpfSrPFo/YhMqVgCF38LrBx2u/NPItz1UqQK0tl1bDKUayanqN5P+6FDgtaA2HKX/+X
         XtEYy4zUAt+Z4GNZDpFuC7GDd3hlHw46kI7Ko829sHQc3p9iGotQePXO/DoNFEA0pNyZ
         Qe2Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=S4meV0NsaDpqLa7tBEXkvORH5DuiHJR7oObrl4NCVW4=;
        b=An34awI32oh+EqjtLvtVntQq6PYzXZcsjDWTYLbVdcg/qRrvg39u33irWvTA+SShmp
         SNs9l4sdM/4MjnrpHm5AgzpzgKF17BjctMHY3T+xYiDxkKFQWaEczl41gCxXVpO7+d/P
         PHPHo0poOAOfmFnk0s7tDZvGSWP7RW+rMYVl/WvcyQWM6XaFKpDr+A0G3SYGqKb+4O+0
         UkR+EfbpgWFq98caK21xI94Rae7otbamU9KmNa14gg10YWmYfe6rcR4JDo2Oh6No3mHk
         upBgP1D7t8cVgrCLvCWiS8WD/ppa0PmnEbRS0XAe8QEzk1LZPaNCHeMSu+kOJeSFjdQW
         eVxg==
X-Gm-Message-State: APjAAAWASdhu/rXgrXRKEYlHa726Kgdr17VrARdDMHve3yyW/44exLCH
        JDWwv7aUOMV/ZkNtQZU+6WM6YusH
X-Google-Smtp-Source: 
 APXvYqzCLsczViMIVb7X3HfOf7obZBubZ1E1KCxx7eCgHu7Vt1z3KtWGQvxR+kz+c/TU/OFIY2h5pw==
X-Received: by 2002:a7b:c4c9:: with SMTP id g9mr141219wmk.150.1569862355607;
        Mon, 30 Sep 2019 09:52:35 -0700 (PDT)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 n22sm139924wmk.19.2019.09.30.09.52.34
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 30 Sep 2019 09:52:34 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, kvm-ppc@vger.kernel.org
Subject: [PATCH] kvm: x86,
 powerpc: do not allow clearing largepages debugfs entry
Date: Mon, 30 Sep 2019 18:52:31 +0200
Message-Id: <1569862351-19760-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The largepages debugfs entry is incremented/decremented as shadow
pages are created or destroyed.  Clearing it will result in an
underflow, which is harmless to KVM but ugly (and could be
misinterpreted by tools that use debugfs information), so make
this particular statistic read-only.

Cc: kvm-ppc@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/powerpc/kvm/book3s.c |  8 ++++----
 arch/x86/kvm/x86.c        |  6 +++---
 include/linux/kvm_host.h  |  2 ++
 virt/kvm/kvm_main.c       | 10 +++++++---
 4 files changed, 16 insertions(+), 10 deletions(-)

```
#### [PATCH net-next v2] vsock/virtio: add support for MSG_PEEK
##### From: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
X-Patchwork-Id: 11167619
Return-Path: <SRS0=huOb=XZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD480912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 21:11:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC0ED206BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 21:11:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="F2+krCW9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732647AbfI3VLH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 17:11:07 -0400
Received: from mail-wr1-f68.google.com ([209.85.221.68]:41505 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731678AbfI3VLH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Sep 2019 17:11:07 -0400
Received: by mail-wr1-f68.google.com with SMTP id h7so12939710wrw.8;
        Mon, 30 Sep 2019 14:11:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=Km4VVTEePyhHsFimVMjuG3mAp67V52rIi2SimlK34MU=;
        b=F2+krCW9h4/vWnl412e0O5+BiYynOmqsu1GTfc8j8T1hPDRh/+RAH2TS+9oShSfFht
         +DRLSK6QkQUf/q9kVU0q0Wjwa/b7b9EPcbkMCthJ69y2UmK0Q9ohogmqOrjvF3Faovgn
         +c+DRShui0gK74MGaLgAd+Mf6ouSNMGaMZtUGB974GaAdsw7mHblL4mtYB9yIaygJ98L
         wHtVcQy0rnKX+4Eg8KQdFXrAf+QZ225nTNmyyTIW9Y+3Tcwls5KigSdvTnen9WScAozr
         V1YfI0PzPyhC3A2E1YaljJhKI3DQ0gqiXoBGXQvDawlO+2yHbso2owB0J6vnmQjBJ596
         HWuQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=Km4VVTEePyhHsFimVMjuG3mAp67V52rIi2SimlK34MU=;
        b=hdUmpW5NtPz1aEE3eSuI2QLkdaVczahFRDjXhBwb/rUkcdAtjXpRhYxiLPDgnwn2FI
         OU8hYZxAncPCf1OHFMAlrVAUT2D0ybUl3pacMk0W46ONaJ530s+eSJsSA+3+XA+oFWjN
         OYHupB1OOnD+iiojEt4elJI0EJvnKHLhY1UCCE3aGzz5jmOfIjFcZY/y3QXc2ta3nmMk
         5LO1AU4b1KsUz1WqpzwV87IalgNml3xqsI3sYO0JAcrSy6oM434tmvXDyyWGJoNRCyq1
         t3E+8nqCwJc6PkagwONvC8lSV29Zv91uTPsxLoglBBeKak4cP3sfMIYjkPsQ/UorVJJY
         sSFw==
X-Gm-Message-State: APjAAAVrPRZ4XK7Ii0ZU3Cvc68xKIanmjtwhWDx3lW/fE3JPCWxZC8w/
        43XhK0HOhE8S5cfYzpoIRLgteVmFj/Cm7Q==
X-Google-Smtp-Source: 
 APXvYqzy7y5NjgWswAUhrWkzobKoCPCU2cj3zemHxu/pZIy6qbKJmrWtc0rOICC1+bZexktMTIyuxA==
X-Received: by 2002:a5d:4d8c:: with SMTP id
 b12mr14184701wru.198.1569867973583;
        Mon, 30 Sep 2019 11:26:13 -0700 (PDT)
Received: from scw-93ddc8.cloud.online.net ([2001:bc8:4400:2400::302d])
        by smtp.googlemail.com with ESMTPSA id
 r20sm15672256wrg.61.2019.09.30.11.26.12
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Mon, 30 Sep 2019 11:26:13 -0700 (PDT)
From: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
To: stefanha@redhat.com
Cc: davem@davemloft.net, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, matiasevara@gmail.com,
        sgarzare@redhat.com, eric.dumazet@gmail.com
Subject: [PATCH net-next v2] vsock/virtio: add support for MSG_PEEK
Date: Mon, 30 Sep 2019 18:25:23 +0000
Message-Id: <1569867923-28200-1-git-send-email-matiasevara@gmail.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch adds support for MSG_PEEK. In such a case, packets are not
removed from the rx_queue and credit updates are not sent.

Signed-off-by: Matias Ezequiel Vara Larsen <matiasevara@gmail.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
Tested-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 55 +++++++++++++++++++++++++++++++--
 1 file changed, 52 insertions(+), 3 deletions(-)

```
#### [PATCH net v3] vsock: Fix a lockdep warning in __vsock_release()Thread-Topic: [PATCH net v3] vsock: Fix a lockdep warning in __vsock_release()
##### From: Dexuan Cui <decui@microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dexuan Cui <decui@microsoft.com>
X-Patchwork-Id: 11167421
Return-Path: <SRS0=huOb=XZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35FA516C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 20:42:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 00E52224FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 20:42:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=microsoft.com header.i=@microsoft.com
 header.b="ONatBT9r"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730637AbfI3UmZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 16:42:25 -0400
Received: from mail-eopbgr730136.outbound.protection.outlook.com
 ([40.107.73.136]:25596
        "EHLO NAM05-DM3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726425AbfI3UmY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Sep 2019 16:42:24 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=XD5PAy6VlrMFtYHfmwZiEwHxVRjdBd2r/AFMbS3msZLgHaIekAiAUHnFGTjrKEixyOIEuHwMbRfAg49DuZazAkwZyxv756CuucpLqPs2Xdx6kCZV8osn7gGsUth3BY5NuAoeekbzs1mJV9CjxuEP+rEOcI7NGA5il1y0guoTzEjmiVP3eB66A2wob6DjKgte/oZ5rG/JX/LanZsz7eYHIOlLUBD9Af2obES2Cfwy77vhp/2WPX2ZYQhU6+uUuw97YkIGbRV21YgSZ45qAEQcFl0Xh0YF4lf109dNMCNItrPyPX9tJxhOdT+Yr3kscKp+tYWEs7p6ZQx3X1nLbxYd3Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4VLe6uWWiY/qpEe3s/bHgLDaeTsdh1kwDEUaDim+pJY=;
 b=Pe4ge3OjxiimrmuGfpnPFq1fba6Cs1TmLh7vlsc30+5kc00ZuJjLZpvZg8wg3nrlCSvlu++cGbiP5IqSEVxKsYFRfXPGEv3WDhqLhnv9jdHJlGgBJ15HJ9fsmwsvOR9CKcqTtatTxHQRpPLDmmnz/glvVx7TnDIP9RLZcSg51f2C9QNeuoRYh80ElQMWFjrzv4NrMZ2se+S/lRxkaGVdSIKbVb2xgOroIaxpJzvG8M330tu8c/SHXl1FsHVk+QIi2lSjqDNLgCe/YXSDb7pVNlVo2eo8wpGZIWWx7NXjdkHSW/nTj3jmiOFZ0FT3LonjaZRBmf19XAMWbCfm7bv7hA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=microsoft.com; dmarc=pass action=none
 header.from=microsoft.com; dkim=pass header.d=microsoft.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=4VLe6uWWiY/qpEe3s/bHgLDaeTsdh1kwDEUaDim+pJY=;
 b=ONatBT9rpDxOkGRRVqhVR8UPRpAK3xAvTTXxs4RUvFk581fVuzTNsftZHmvGwWPuxZqwLAPOz2t6TgCTq+j8jI9pCjz2hRsdNy/TYgXcgBR8dl1+8JktQFkoDvcHrp+5UCmgOO5zdfC0PegXZkk14zJh9i0UOvLI2BWrs0oe+nQ=
Received: from MW2PR2101MB0937.namprd21.prod.outlook.com (52.132.146.10) by
 MW2PR2101MB0972.namprd21.prod.outlook.com (52.132.146.21) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2327.3; Mon, 30 Sep 2019 18:43:50 +0000
Received: from MW2PR2101MB0937.namprd21.prod.outlook.com
 ([fe80::adb9:3e84:c02f:a6e5]) by MW2PR2101MB0937.namprd21.prod.outlook.com
 ([fe80::adb9:3e84:c02f:a6e5%4]) with mapi id 15.20.2305.017; Mon, 30 Sep 2019
 18:43:50 +0000
From: Dexuan Cui <decui@microsoft.com>
To: "davem@davemloft.net" <davem@davemloft.net>,
        KY Srinivasan <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        "sashal@kernel.org" <sashal@kernel.org>,
        "stefanha@redhat.com" <stefanha@redhat.com>,
        "gregkh@linuxfoundation.org" <gregkh@linuxfoundation.org>,
        "arnd@arndb.de" <arnd@arndb.de>,
        "deepa.kernel@gmail.com" <deepa.kernel@gmail.com>,
        Dexuan Cui <decui@microsoft.com>,
        "ytht.net@gmail.com" <ytht.net@gmail.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "netdev@vger.kernel.org" <netdev@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "linux-hyperv@vger.kernel.org" <linux-hyperv@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "virtualization@lists.linux-foundation.org"
        <virtualization@lists.linux-foundation.org>,
        Michael Kelley <mikelley@microsoft.com>,
        "sgarzare@redhat.com" <sgarzare@redhat.com>,
        "jhansen@vmware.com" <jhansen@vmware.com>
Subject: [PATCH net v3] vsock: Fix a lockdep warning in __vsock_release()
Thread-Topic: [PATCH net v3] vsock: Fix a lockdep warning in __vsock_release()
Thread-Index: AQHVd77/dTwgXN3aQEytMriZU2+CuA==
Date: Mon, 30 Sep 2019 18:43:50 +0000
Message-ID: <1569868998-56603-1-git-send-email-decui@microsoft.com>
Reply-To: Dexuan Cui <decui@microsoft.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MWHPR21CA0032.namprd21.prod.outlook.com
 (2603:10b6:300:129::18) To MW2PR2101MB0937.namprd21.prod.outlook.com
 (2603:10b6:302:4::10)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=decui@microsoft.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 1.8.3.1
x-originating-ip: [13.77.154.182]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 4298583d-c9ee-4ebb-fdf9-08d745d62258
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: MW2PR2101MB0972:|MW2PR2101MB0972:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MW2PR2101MB097223F7D12543FBEA0CC0CCBF820@MW2PR2101MB0972.namprd21.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:497;
x-forefront-prvs: 01762B0D64
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(136003)(39860400002)(366004)(396003)(346002)(376002)(199004)(189003)(1511001)(102836004)(6506007)(22452003)(71200400001)(25786009)(66476007)(316002)(64756008)(52116002)(386003)(66946007)(2201001)(66556008)(2906002)(2616005)(186003)(8936002)(10090500001)(7736002)(8676002)(81166006)(486006)(50226002)(5660300002)(99286004)(86362001)(66446008)(305945005)(3450700001)(14454004)(256004)(478600001)(3846002)(476003)(26005)(4720700003)(36756003)(10290500003)(71190400001)(81156014)(14444005)(66066001)(2501003)(7416002)(6116002)(6512007)(43066004)(110136005)(6486002)(6436002)(921003)(1121003);DIR:OUT;SFP:1102;SCL:1;SRVR:MW2PR2101MB0972;H:MW2PR2101MB0937.namprd21.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: microsoft.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 VMot/gftkqjyeSWsI/zrWW/qP8FQE1ymAm8MNEeuLIGn+sF4U+5JE2NbeRF85thVKR+sL0xHdd6nOw0OV/IFlrcEkGJaX5Nzjat8bb3e8ZlBvN6BCx+Dup1JKq/uCuwiZwcJZBXlRCkpOT7A6+XqzJe28eAH7dNuJHE3X6ugGMAW6p+cNM6HK4geTQws+5f+OHkhZUqLapCpgflRs4oWyZAfgyn5nQRbIW4q2/sPbXX80oXb311SpGk/kqJb8wpD9A8W6+1A1YIXe/xyGaQj7tN7vcCC9pprlue9uICWZ4848+ONa4LCnEkN7bbX+jgJmwNNf+pIpCi9KpJ1SfQ5BSXN1cZbms//jBghmxNt16VJ9Fe8uwEzwB8FD+RtFdaNeaBC4uhf/oGUyWZ9ScpiimiTK7SqGxJb3YuBBXAgK74=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: microsoft.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 4298583d-c9ee-4ebb-fdf9-08d745d62258
X-MS-Exchange-CrossTenant-originalarrivaltime: 30 Sep 2019 18:43:50.2117
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 72f988bf-86f1-41af-91ab-2d7cd011db47
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 L6ytQc6JCDshj5jqInJdpnwy7kABz1ERGzhroQb12qbDXo+ISQM+aj64Dd8fEOixszkMZnbkzXXgQpV0NoDzXg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MW2PR2101MB0972
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Lockdep is unhappy if two locks from the same class are held.

Fix the below warning for hyperv and virtio sockets (vmci socket code
doesn't have the issue) by using lock_sock_nested() when __vsock_release()
is called recursively:

============================================
WARNING: possible recursive locking detected
5.3.0+ #1 Not tainted
--------------------------------------------
server/1795 is trying to acquire lock:
ffff8880c5158990 (sk_lock-AF_VSOCK){+.+.}, at: hvs_release+0x10/0x120 [hv_sock]

but task is already holding lock:
ffff8880c5158150 (sk_lock-AF_VSOCK){+.+.}, at: __vsock_release+0x2e/0xf0 [vsock]

other info that might help us debug this:
 Possible unsafe locking scenario:

       CPU0
       ----
  lock(sk_lock-AF_VSOCK);
  lock(sk_lock-AF_VSOCK);

 *** DEADLOCK ***

 May be due to missing lock nesting notation

2 locks held by server/1795:
 #0: ffff8880c5d05ff8 (&sb->s_type->i_mutex_key#10){+.+.}, at: __sock_release+0x2d/0xa0
 #1: ffff8880c5158150 (sk_lock-AF_VSOCK){+.+.}, at: __vsock_release+0x2e/0xf0 [vsock]

stack backtrace:
CPU: 5 PID: 1795 Comm: server Not tainted 5.3.0+ #1
Call Trace:
 dump_stack+0x67/0x90
 __lock_acquire.cold.67+0xd2/0x20b
 lock_acquire+0xb5/0x1c0
 lock_sock_nested+0x6d/0x90
 hvs_release+0x10/0x120 [hv_sock]
 __vsock_release+0x24/0xf0 [vsock]
 __vsock_release+0xa0/0xf0 [vsock]
 vsock_release+0x12/0x30 [vsock]
 __sock_release+0x37/0xa0
 sock_close+0x14/0x20
 __fput+0xc1/0x250
 task_work_run+0x98/0xc0
 do_exit+0x344/0xc60
 do_group_exit+0x47/0xb0
 get_signal+0x15c/0xc50
 do_signal+0x30/0x720
 exit_to_usermode_loop+0x50/0xa0
 do_syscall_64+0x24e/0x270
 entry_SYSCALL_64_after_hwframe+0x49/0xbe
RIP: 0033:0x7f4184e85f31

Tested-by: Stefano Garzarella <sgarzare@redhat.com>
Signed-off-by: Dexuan Cui <decui@microsoft.com>
---

Changes in v2:
  Avoid the duplication of code in v1.
  Also fix virtio socket code.


Changes in v3:
  Use "lock_sock_nested(sk, level);" -- suggested by Stefano.
  Add Stefano's Tested-by.

 net/vmw_vsock/af_vsock.c                | 16 ++++++++++++----
 net/vmw_vsock/hyperv_transport.c        |  2 +-
 net/vmw_vsock/virtio_transport_common.c |  2 +-
 3 files changed, 14 insertions(+), 6 deletions(-)

```
#### [PULL 01/12] MAINTAINERS: Update S390 PCI Maintainer
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11166685
Return-Path: <SRS0=huOb=XZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1ACD9112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 13:20:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F29B1215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 13:20:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731269AbfI3NUH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 09:20:07 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:4947 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731261AbfI3NUG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Sep 2019 09:20:06 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8UDIFdr133970
        for <kvm@vger.kernel.org>; Mon, 30 Sep 2019 09:20:04 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vbjd70bqc-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 30 Sep 2019 09:20:03 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Mon, 30 Sep 2019 14:20:01 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 30 Sep 2019 14:19:57 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8UDJuvC57606168
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 30 Sep 2019 13:19:56 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 09AEA52051;
        Mon, 30 Sep 2019 13:19:56 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id E972D5204F;
        Mon, 30 Sep 2019 13:19:55 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id A82B0E020F; Mon, 30 Sep 2019 15:19:55 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Peter Maydell <peter.maydell@linaro.org>
Cc: qemu-devel <qemu-devel@nongnu.org>,
        qemu-s390x <qemu-s390x@nongnu.org>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Thomas Huth <thuth@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Collin Walling <walling@linux.ibm.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Igor Mammedov <imammedo@redhat.com>, kvm@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PULL 01/12] MAINTAINERS: Update S390 PCI Maintainer
Date: Mon, 30 Sep 2019 15:19:44 +0200
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190930131955.101131-1-borntraeger@de.ibm.com>
References: <20190930131955.101131-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19093013-0008-0000-0000-0000031C6F95
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19093013-0009-0000-0000-00004A3B15FC
Message-Id: <20190930131955.101131-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-30_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=890 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909300138
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Matthew Rosato <mjrosato@linux.ibm.com>

As discussed previously with Collin, I will take over maintaining
s390 pci.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Message-Id: <1569590461-12562-1-git-send-email-mjrosato@linux.ibm.com>
Acked-by: Collin Walling <walling@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/hyperv: make vapic support x2apic modeThread-Topic: [PATCH] x86/hyperv: make vapic support x2apic mode
##### From: Roman Kagan <rkagan@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Kagan <rkagan@virtuozzo.com>
X-Patchwork-Id: 11167409
Return-Path: <SRS0=huOb=XZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 564D216C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 20:38:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B8D122516
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 30 Sep 2019 20:38:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="XIAoqFeu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731025AbfI3Uie (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Sep 2019 16:38:34 -0400
Received: from mail-eopbgr30103.outbound.protection.outlook.com
 ([40.107.3.103]:38787
        "EHLO EUR03-AM5-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726576AbfI3Uie (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Sep 2019 16:38:34 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=V100/ncP1ZCn1VlFtDtXI1juYVDyd3wONJrV6ltT7OsRjbY8y/HpqhxaZg7skuiNhXjHQ7lOtGGHGr9Deh4irWDS8lGdzGz5PUrPkBWzJ8vswXM08YfBlQ2PWxjV7nRLR2X+wyJkvCJ8+lB5xUrcTQoe89uYhqEJ/lg9UFPas2fxuU0TD0llmXDHUgNn5J03eS3jZcASaPutZFZaVEIdDT0tNeDF6cVRsiNNOtfniCSIIPIQYYm2wNyM5Cv6T5vql5CcER9uWDcf7rB9BxDjkYoRj/p6LW9QoA53D8SEl0hpgMZ/o1XU+J3mZW/d1+ZJRnFBn8FCyqQToYoyb1wTFw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=gUL/gxQRJkx6o5iqAU4uhq64IBw13J1KOJkiYkGiQoM=;
 b=KbjW3vaaafp2Y7Eo2MjM4swiQwoy7jGRhgNrtzUTnrLgcfTlcX/w6azcqMMtd73gaRZvmdvzF8nooKZlxwJl2FEw6+7kZHznYpvC/16EK5kNvLi8GZL04Gcj1GjZbmHKQTCiJrb0lfCq8cIIb/QxRAVkK97gaBYJetwQ4Y1/oaD7RONrhWTLHowGmRNnT5BNE9zLacrHEwnx1OR+h/U0q2u/Bx19OSfcqbczhIqVuoFl7FY2wvQs8QF4DlPuypAUOYTnKTmlQWIOhM3CfLKaOAvS2QreJhCUYa4phYVWnCdV/jMyLBE7HkBKUw9jUbIf5qNKc/ytSkiHeWIzUo1rGQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=gUL/gxQRJkx6o5iqAU4uhq64IBw13J1KOJkiYkGiQoM=;
 b=XIAoqFeu721f0vIJEiLx8ZeemATyTq/GoH5OcFEXjSM01YK0Xl1EN0KPB+1Fz2NZmob3ml9mjHWAyHjsoBFYET0TDjw1ZtZdgOqLhfAWnCBqKRFIZCpjb72zFuVKYqs5zXOqEB7sEXFSWckt/xE/6TuEizJUS6gy3SiNHif4olQ=
Received: from AM0PR08MB5537.eurprd08.prod.outlook.com (20.179.36.87) by
 AM0PR08MB3954.eurprd08.prod.outlook.com (20.178.202.77) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2305.20; Mon, 30 Sep 2019 17:33:41 +0000
Received: from AM0PR08MB5537.eurprd08.prod.outlook.com
 ([fe80::a8ea:5223:db78:dd3]) by AM0PR08MB5537.eurprd08.prod.outlook.com
 ([fe80::a8ea:5223:db78:dd3%7]) with mapi id 15.20.2305.017; Mon, 30 Sep 2019
 17:33:41 +0000
From: Roman Kagan <rkagan@virtuozzo.com>
To: Michael Kelley <mikelley@microsoft.com>,
        Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Joerg Roedel <jroedel@suse.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Sasha Levin <sashal@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "x86@kernel.org" <x86@kernel.org>,
        "linux-hyperv@vger.kernel.org" <linux-hyperv@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH] x86/hyperv: make vapic support x2apic mode
Thread-Topic: [PATCH] x86/hyperv: make vapic support x2apic mode
Thread-Index: AQHVd7Uz7GLeEx2RZ0ukSyO6D+H5XQ==
Date: Mon, 30 Sep 2019 17:33:40 +0000
Message-ID: <20190930173332.13655-1-rkagan@virtuozzo.com>
Accept-Language: en-US, ru-RU
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [185.231.240.5]
x-clientproxiedby: HE1PR05CA0241.eurprd05.prod.outlook.com
 (2603:10a6:3:fb::17) To AM0PR08MB5537.eurprd08.prod.outlook.com
 (2603:10a6:208:148::23)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=rkagan@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.21.0
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: ddd9e317-1093-430f-ed6b-08d745cc558f
x-ms-traffictypediagnostic: AM0PR08MB3954:
x-microsoft-antispam-prvs: 
 <AM0PR08MB3954D52D4D5179D11AACDEF4C9820@AM0PR08MB3954.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:7691;
x-forefront-prvs: 01762B0D64
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(346002)(366004)(136003)(39840400004)(396003)(376002)(199004)(189003)(6512007)(1076003)(2201001)(4326008)(86362001)(99286004)(478600001)(2501003)(2906002)(52116002)(50226002)(14454004)(8936002)(81156014)(81166006)(3846002)(8676002)(6116002)(6436002)(102836004)(6486002)(66066001)(66446008)(66476007)(386003)(26005)(186003)(316002)(1511001)(6506007)(476003)(25786009)(486006)(2616005)(305945005)(66556008)(64756008)(71190400001)(71200400001)(7736002)(36756003)(66946007)(7416002)(110136005)(5660300002)(256004)(14444005)(921003)(1121003);DIR:OUT;SFP:1102;SCL:1;SRVR:AM0PR08MB3954;H:AM0PR08MB5537.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 46tZ8n/dj5uKvHz9iulYq+EaHaWald0SRU9t85AZCICfsEdV8xkNbnExJAr5J2kn37zqHxMOpSwlzrAo/2tzhajndVsDXQcvNYy1x4q9DnbIZKbxbvucyLhBz9DcOqdrZDFhX2vAsdSK6/X+v4XuLD9CBdJKjUlF93v79DFpct3HoXdQa8J8YXJ1piecSy2O9tMNxhAIxezTSzvCKsEVxreupvp1hYE5+CWVl4OBrxL8VFUnj6jn3J7KVED8JDuu8edSkNa+5/FurxGD4UnDQDWPvkc64CBsYXQD0nvTCGcJREXIaG8FxgkJYFIxmdIbqMo7fyVbS29QTPg/uBtNjc9Y66F7umY7s3wBs+OYDLQosc7bf1rzPv2oV2lgHEB9ARaSzR+7LO1edxn3P1nB75gC9Ml/VHo+yb1tmT0aJ/o=
x-ms-exchange-transport-forked: True
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ddd9e317-1093-430f-ed6b-08d745cc558f
X-MS-Exchange-CrossTenant-originalarrivaltime: 30 Sep 2019 17:33:41.0653
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 N3mkV5k6K15VZFpYM5pNmyJM1JXRLdlFnM3VsI7GFtcysXR4IrHPdtI102reKDvnUfCFebR3wptS8x7q3lmF8w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM0PR08MB3954
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that there's Hyper-V IOMMU driver, Linux can switch to x2apic mode
when supported by the vcpus.

However, the apic access functions for Hyper-V enlightened apic assume
xapic mode only.

As a result, Linux fails to bring up secondary cpus when run as a guest
in QEMU/KVM with both hv_apic and x2apic enabled.

I didn't manage to make my instance of Hyper-V expose x2apic to the
guest; nor does Hyper-V spec document the expected behavior.  However,
a Windows guest running in QEMU/KVM with hv_apic and x2apic and a big
number of vcpus (so that it turns on x2apic mode) does use enlightened
apic MSRs passing unshifted 32bit destination id and falls back to the
regular x2apic MSRs for less frequently used apic fields.

So implement the same behavior, by replacing enlightened apic access
functions (only those where it makes a difference) with their
x2apic-aware versions when x2apic is in use.

Fixes: 29217a474683 ("iommu/hyper-v: Add Hyper-V stub IOMMU driver")
Fixes: 6b48cb5f8347 ("X86/Hyper-V: Enlighten APIC access")
Cc: stable@vger.kernel.org
Signed-off-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/hyperv/hv_apic.c | 48 ++++++++++++++++++++++++++++++++++++---
 1 file changed, 45 insertions(+), 3 deletions(-)

```
