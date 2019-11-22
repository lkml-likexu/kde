#### [RFC V1 1/2] vhost: IFC VF initialization functions
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11256243
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BD4846C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 13:37:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8C7D620715
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 13:37:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727040AbfKUNhA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 08:37:00 -0500
Received: from mga11.intel.com ([192.55.52.93]:27188 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726947AbfKUNg7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 08:36:59 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Nov 2019 05:36:59 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,226,1571727600";
   d="scan'208";a="238178535"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga002.fm.intel.com with ESMTP; 21 Nov 2019 05:36:55 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>,
        Xiao Wang <xiao.w.wang@intel.com>
Subject: [RFC V1 1/2] vhost: IFC VF initialization functions
Date: Thu, 21 Nov 2019 21:34:36 +0800
Message-Id: <1574343277-8835-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1574343277-8835-1-git-send-email-lingshan.zhu@intel.com>
References: <1574343277-8835-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit intends to add initialization functions for
IFC VF, including: probe / remove / mdev operations and
sysfs interfaces.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Signed-off-by: Xiao Wang <xiao.w.wang@intel.com>
Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
 drivers/vhost/Kconfig            |  12 ++
 drivers/vhost/Makefile           |   2 +
 drivers/vhost/ifcvf/Makefile     |   2 +
 drivers/vhost/ifcvf/ifcvf_base.c | 129 ++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 123 +++++++++++++++
 drivers/vhost/ifcvf/ifcvf_main.c | 315 +++++++++++++++++++++++++++++++++++++++
 6 files changed, 583 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/Makefile
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c

```
#### [PATCH] KVM: arm: get rid of unused arg in cpu_init_hyp_mode()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11255625
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 53CB8930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 07:16:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3D47F208A3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 07:16:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726975AbfKUHQF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 02:16:05 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:53750 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726358AbfKUHQE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 02:16:04 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id AAC8DC4C53B3229B3B3C;
        Thu, 21 Nov 2019 15:16:01 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.439.0; Thu, 21 Nov 2019
 15:15:52 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: arm: get rid of unused arg in cpu_init_hyp_mode()
Date: Thu, 21 Nov 2019 15:15:59 +0800
Message-ID: <1574320559-5662-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

As arg dummy is not really needed, there's no need to pass
NULL when calling cpu_init_hyp_mode(). So clean it up.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 virt/kvm/arm/arm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: expose "load IA32_PERF_GLOBAL_CTRL" controls
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11256233
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64AD86C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 13:32:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3AB8D20708
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 13:32:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="eYpeBUR8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726690AbfKUNcW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 08:32:22 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:41926 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726546AbfKUNcW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 08:32:22 -0500
Received: by mail-wr1-f66.google.com with SMTP id b18so4401619wrj.8;
        Thu, 21 Nov 2019 05:32:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=+C/cs017OrqlyrW+ijapSly866aUVTUkDdweWrl6lFE=;
        b=eYpeBUR8QAO1EAEZp+JARhcC6Wz+tdkK2dpTM8QAFn18v1PBrRBAoSxPNJNg1Oqs2N
         P81KObUNS4ZjP3MhCpJHcwXHNMK3WydTf5ILGcCLYVfTwM6mbPkDfEDtS6X+VLConr8P
         xiNkmSWRev6Ptm424zs55BDDz544q9oVrCEl2OAySET98SjgA7a3T7axjNKqqrv3sgLg
         kXB/JlLlRQdTSg0xhCcrlcz2pSJzx/bQ3HHuJ6+KK/s8FJkOpFdVPXREISyO7SvD8Zeg
         ePLeltpyddXJVzWcOvIrTCFS0FoBKJCh9tHXbBfQOEkV/RKupLEo4LnwEda2D2CK7s/G
         yMTg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=+C/cs017OrqlyrW+ijapSly866aUVTUkDdweWrl6lFE=;
        b=EkzgVI46OnSbyiLK4UlVxOj4OM061tkROOdqPAmxps0rjF8T8rH5BYxHmstyJnGAdt
         kkv0xQi/g+1QaiacEoxhfQvQrT7AkDA2aCu/vtk0KgGZHPW7/wDfg4EDqMvWScRpwvto
         EpGjSaVEhFxsrjjZXhXXwTodSZEU1r8uvwrFqA/9rIf9Aas8eX3diIb+/6GX5JjUZ0vG
         IVdESiKpainZgw6lCGzH1bmGHs1RO+k4zWqr3QWS87t0BuATzePtTrjvE0Zlk4M0yp87
         2ZVCsyBeCvN7xI2J9DILkhrcgciVEj/9TM6RNF1/WxPsGib1rHuYVROIUUiWCzKuL78F
         Ws0w==
X-Gm-Message-State: APjAAAXDRAkdOOb/YgrX1DOfg31PiuXirBZmZyM0k47oJbUf+sPvEJD1
        1ZsUSfhZp3DPLVPkQghi/g8yGD0T
X-Google-Smtp-Source: 
 APXvYqxgWF5Wbj1AfbjM8EnG5GkwL4TW9/QfOscwNry6IPTsj+6uG1pih6CfGBhNznygbNEwOUi0JQ==
X-Received: by 2002:a5d:51c8:: with SMTP id n8mr10632150wrv.302.1574343139817;
        Thu, 21 Nov 2019 05:32:19 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 m25sm2703329wmi.46.2019.11.21.05.32.18
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 21 Nov 2019 05:32:19 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Subject: [PATCH] KVM: nVMX: expose "load IA32_PERF_GLOBAL_CTRL" controls
Date: Thu, 21 Nov 2019 14:32:18 +0100
Message-Id: <1574343138-32015-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These controls have always been supported (or at least have been
supported for longer than nested_vmx_setup_ctls_msrs has existed),
so we should advertise them to userspace.

Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: nVMX: expose "load IA32_PERF_GLOBAL_CTRL" controls
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11256355
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26E086C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 14:29:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 05CF1206CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 14:29:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="XmX+M2Go"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727052AbfKUO3W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 09:29:22 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:33540 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726358AbfKUO3W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 09:29:22 -0500
Received: by mail-wr1-f66.google.com with SMTP id w9so4714810wrr.0;
        Thu, 21 Nov 2019 06:29:20 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=Uhe0Kiej1ea14TSjH1b0KQtAZR+V5aq929XhPTnEBZY=;
        b=XmX+M2GobM70kadqAmo9GOL17ztsH0GKJ5KTHDFedGV61V2IUJdyokp+KxbRsg2GeU
         DJ1fVP8goSFoZw2bUx+jeFX9Vfmgt/G7SEsUb5pBsifz9ugl77e6an8znqwXjOaDtlO6
         +r6iiWlNslbq//tbT/Htm2a8l7+bU+drRu156E2BrQWVDgSQ5ceHwA89BnwyQuNC+kSH
         r+gse+qnBhvQp5AaWbNhxILJdaQoumTGqyEZrcK0OKC0m8IgUJTE9DTTWFwhOLbAYPXD
         /FAoBMVBKseLxwg6tS897YWkyq2KAUoNEg3kyJwct+pCjlG/s4SDanqeHYIomgG7APHN
         qrIQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=Uhe0Kiej1ea14TSjH1b0KQtAZR+V5aq929XhPTnEBZY=;
        b=Aap2lZtw5OGLMVKFzmRhS5Whc9i8rkfszs84/4Vd3hyJH1/wNpLq0YiO7FVB8iRixW
         m8jGpkEgdShLi/3v3MbsagMfwvKLQq1ilSS9/uuBueL7wtZ696B3MmyRR337bNpP0Qjg
         qZIN03yU3USzENAA2TSwc05hLCB6PTMwqxA9YXH8Z4Ul2hXlkCANgzq5jl9Jz7HzNEaA
         BHeMaKo9KXHwVg65G6Uidp3ImAc/jjo5NT1OMg8/ZIJJnJ5G9aAjbciJzbVHBwui0ElV
         N3KoWyMQRPfxR1fdnA1wn5JDgKUY0i9GeKf1kSN0pqDRh2vtsDCZhaNav3IniryXsVYE
         3lbQ==
X-Gm-Message-State: APjAAAX6JzkZ7AKBflnSPO99pPcArO01pT56Li/YgayAEGjb1NE0jsWQ
        czVycE+SWEoJoCVfTKGPM9CjfPdw
X-Google-Smtp-Source: 
 APXvYqzE1Zl12m5/a5jql/gn02/XLRwp+3vetVbJpXY7FMZ8c6BKw9yg6j3FfBzLYAWx9MvZqqnyBg==
X-Received: by 2002:a5d:5224:: with SMTP id i4mr11101374wra.303.1574346559451;
        Thu, 21 Nov 2019 06:29:19 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b15sm3408693wrx.77.2019.11.21.06.29.18
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 21 Nov 2019 06:29:18 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Oliver Upton <oupton@google.com>
Subject: [PATCH] KVM: nVMX: expose "load IA32_PERF_GLOBAL_CTRL" controls
Date: Thu, 21 Nov 2019 15:29:17 +0100
Message-Id: <1574346557-18344-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These controls were added by the recent commit 03a8871add95 ("KVM:
nVMX: Expose load IA32_PERF_GLOBAL_CTRL VM-{Entry,Exit} control",
2019-11-13), so we should advertise them to userspace from
KVM_GET_MSR_FEATURE_INDEX_LIST, as well.

Cc: Oliver Upton <oupton@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: x86: create mmu/ subdirectory
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11256093
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 720FE1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 10:45:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5106F208CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 10:45:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="NMLOmZbG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726690AbfKUKps (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 05:45:48 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:39350 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726014AbfKUKps (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 05:45:48 -0500
Received: by mail-wm1-f68.google.com with SMTP id t26so3104350wmi.4;
        Thu, 21 Nov 2019 02:45:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=cxS5SnfMHCr10pDxeGM/7sjAasmtfI9lheTpz/ICL50=;
        b=NMLOmZbG1QR7h4UQQ4HZf1hVPYrxEm1ZJNehrqPfkOdCdfWlHrkopiy3UcAmeWWXPu
         46EUdDIIlNcH92rVn/4LIabijIkjTfKTwTBuFQIsx0UZj2M/998qHZEhVFjyCV0grzQs
         V9KHSnlF3ookG3Vb7mK3stgJbIQgH9sUPko33b+e0raVFDd+rU9jlRePXW0qC7J8SGal
         u8BPmeIdrwAaeT9KW8IfMnz0nFh7C1N7MHKPQ+ykh3k0X5090qbFW865LYHXlHXSH+jy
         M48ZZR0NzvTjY4m4z8mg5o8iTic2mlCtNlWqH5xKttE01xzDgrZaYFJJ9qK/HfhfcGxl
         rbyA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=cxS5SnfMHCr10pDxeGM/7sjAasmtfI9lheTpz/ICL50=;
        b=NWAo5RDhqKJeMp/yPIM6YrWwGIZNh750NJw498Y0xXuX6R/68XSKI6c5iP8SYnaPrg
         lIKqW0Ou7qDhONEugk17Un3aXmWDr4L9dtnCIVgEgLy9ZNZgbd+gZJ04Altzi2o3OnC3
         +/U92zARydFNkVRML09/3eJhn63Va86pJzR2Td43k2W9TxSG8HZSG/nSXRiDGLOsFEo0
         JkPzIJcVpLxXun2oZUW/4s11Clob8nEtqUXXAuOU73tUiIHAWXtaPvOV+HH5LEGQBz9X
         XoG3zWTe/QlyJDsfP5NqAGNiE9s6AvmcXc7AejG0eCqjPaT5v7WIOwL3vB8MVU2Zsein
         PVHQ==
X-Gm-Message-State: APjAAAXLNb8GQYT9DPwkOct0bbdxUIVG+HuTlcQNWseazFR9n2vjyolL
        tjyET1H7DO/B6IA7MqpPmLTPsVje
X-Google-Smtp-Source: 
 APXvYqxILiCiMhr9y5tsRaYve/TJEB3kVlTw+lE1x7awLVKtBnT5EdHOOOgqYiCiqzHchAY+PNQ0LA==
X-Received: by 2002:a7b:cb86:: with SMTP id m6mr9552009wmi.124.1574333145541;
        Thu, 21 Nov 2019 02:45:45 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 k1sm2871745wrp.29.2019.11.21.02.45.44
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 21 Nov 2019 02:45:45 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Peter Feiner <pfeiner@google.com>
Subject: [PATCH] KVM: x86: create mmu/ subdirectory
Date: Thu, 21 Nov 2019 11:45:43 +0100
Message-Id: <1574333143-27723-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Preparatory work for shattering mmu.c into multiple files.  Besides making it easier
to follow, this will also make it possible to write unit tests for various parts.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/Makefile                | 4 ++--
 arch/x86/kvm/{ => mmu}/mmu.c         | 0
 arch/x86/kvm/{ => mmu}/page_track.c  | 0
 arch/x86/kvm/{ => mmu}/paging_tmpl.h | 0
 4 files changed, 2 insertions(+), 2 deletions(-)
 rename arch/x86/kvm/{ => mmu}/mmu.c (100%)
 rename arch/x86/kvm/{ => mmu}/page_track.c (100%)
 rename arch/x86/kvm/{ => mmu}/paging_tmpl.h (100%)

```
#### [PATCH 1/2] KVM x86: Move kvm cpuid support out of svmFrom: Peter Gonda <pgonda@google.com>
##### From: Peter Gonda <pgonda@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Gonda <pgonda@google.com>
X-Patchwork-Id: 11256889
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 616FD930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 20:34:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 409B3206CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 20:34:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="S0cH232J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726747AbfKUUe2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 15:34:28 -0500
Received: from mail-vs1-f73.google.com ([209.85.217.73]:53381 "EHLO
        mail-vs1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726658AbfKUUe2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 15:34:28 -0500
Received: by mail-vs1-f73.google.com with SMTP id q189so880834vsb.20
        for <kvm@vger.kernel.org>; Thu, 21 Nov 2019 12:34:27 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Kacb+BmwjoTjHjJ+F3FWP7jSRbu4MID2mm6obnvWS8M=;
        b=S0cH232JJ4hnmeZeWNy53Q74IRYxRZKfSBOqFwAMBF/Rs+q99lYAwJA5uG7lGy+/Ch
         ZbPv7LCIlFWNWoZfv9Mtvu/bM298j6NTTe98gjG/GuYzjkunlpdtVJtK0IZssBipbEUY
         xvoqzgNa4Z2aUEgoOs4K3GjOkAoNmKZHR6R2+jdMCpzTbGScu7Ou6Wu/aE0Q65JtteYH
         y6s8vqlH2WC3hVc1Vgnd1xuGMCV+OFKxtC/sotRjbDxZSWgO4Vzi/bFY0OO8XjBVvEVS
         4XsMdcbcsoeC7L9ei7qBroDE3IlHI/6Ne/e8Y2bG7/DsLQBejsmH50uHal7Mrw4aBkCy
         SX8g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Kacb+BmwjoTjHjJ+F3FWP7jSRbu4MID2mm6obnvWS8M=;
        b=kI7oQpmhlLhdptpdJl5Fp2B6vsTKujYVW/bFr3zNK2eiFPl6BuXLSBmc8Bc9oT+wLi
         4JkHdKWrk4jr2wh9HLtaT4YKwFf5Wj29u3V1KWchJ3VMzPTi9WKRUqJmL/uoknI2yB/m
         lceXEZ3rzjyOHa7qy4jOI0T0NDbkMv99GZjOMH0I/bAgdEpcm0OxbsEW0jSsfunm8+y5
         lvhxdo/2N4mPnerDUUtp6/yWUGqWoC/foL+u4NSnumLEUkRzQTnU42vMGT5ucej4gGqC
         sTSulpkt68u8kFapYxClfnsBRphGfeU5lL9GWxbQm2e2jtecPEUZaUNh4i11NoD9432P
         D0cg==
X-Gm-Message-State: APjAAAUtY1Zb/Emrm2A5S7iht8NYutWuMB6HpPSp72Fm9dyt8xmOP9qL
        kBqjTIntyjUhJrcYsK1UrTbDNMQAf7s=
X-Google-Smtp-Source: 
 APXvYqzidnQxmrDfDCZgWfLuJrT1LoiPmUVXOL90CRBRhKlXVLajyUx2gn5KG2H90Aymz9QSn4bS7mIX9Q0=
X-Received: by 2002:a67:e3a3:: with SMTP id j3mr7162107vsm.133.1574368467060;
 Thu, 21 Nov 2019 12:34:27 -0800 (PST)
Date: Thu, 21 Nov 2019 12:33:43 -0800
In-Reply-To: <20191121203344.156835-1-pgonda@google.com>
Message-Id: <20191121203344.156835-2-pgonda@google.com>
Mime-Version: 1.0
References: <20191121203344.156835-1-pgonda@google.com>
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH 1/2] KVM x86: Move kvm cpuid support out of svm
From: Peter Gonda <pgonda@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Peter Gonda <pgonda@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Memory encryption support does not have module parameter dependencies
and can be moved into the general x86 cpuid __do_cpuid_ent function.
This changes maintains current behavior of passing through all of
CPUID.8000001F.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Peter Gonda <pgonda@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/cpuid.c | 5 +++++
 arch/x86/kvm/svm.c   | 7 -------
 2 files changed, 5 insertions(+), 7 deletions(-)

```
#### [PATCH v7 01/24] mm/gup: pass flags arg to __gup_device_* functions
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11255619
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F4060930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 07:16:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA35A2089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 07:16:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="gMl5VQep"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726840AbfKUHP2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 21 Nov 2019 02:15:28 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:4375 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727298AbfKUHOH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Nov 2019 02:14:07 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dd639350003>; Wed, 20 Nov 2019 23:13:57 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 20 Nov 2019 23:13:56 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 20 Nov 2019 23:13:56 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 21 Nov
 2019 07:13:55 +0000
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 21 Nov
 2019 07:13:55 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 21 Nov 2019 07:13:55 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dd639330002>; Wed, 20 Nov 2019 23:13:55 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 "Mauro Carvalho Chehab" <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, "Paul Mackerras" <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH v7 01/24] mm/gup: pass flags arg to __gup_device_* functions
Date: Wed, 20 Nov 2019 23:13:31 -0800
Message-ID: <20191121071354.456618-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191121071354.456618-1-jhubbard@nvidia.com>
References: <20191121071354.456618-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1574320437; bh=shQdk3aSV65MVp9nCFIR9V5hifAIbJq1aZuVoQR8zJ0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=gMl5VQepYNVpBXofZza0/ow/8Dn935aB6KBsCZ3lc9TtHFCtZyjmhmWYKFH6IWFRl
         TnRRGXEo+FQ1av+GEsBdTTibE5RnfRI0tvxbsmRxdI4PCW3jO/hquda7Nqn64ZXawG
         T+V/mOygdWd7MqVqN4z8k9KRlTyE13FGZfZ/+PDzYWF+aFUwKAGCLnX7kwEmv54wid
         3MAjQlavR9EuuEsEgQ/PitjNtZMvDTpGftK/rWJbNiEidCFo0rrQT4pTRQDQusw5qt
         gcHbrtSkK7sCuZHREU4ExJ34LPx8dY52thRmUp1xUZrjzb41EgN4GTlQH6yk+ltaIr
         FsssYdqLifkmg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A subsequent patch requires access to gup flags, so
pass the flags argument through to the __gup_device_*
functions.

Also placate checkpatch.pl by shortening a nearby line.

Reviewed-by: Jan Kara <jack@suse.cz>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Ira Weiny <ira.weiny@intel.com>
Cc: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH v4 1/2] KVM: VMX: FIXED+PHYSICAL mode single target IPI fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11255189
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C0544913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 03:17:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 85B6D2089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 03:17:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tB+HWlPF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726638AbfKUDRU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 22:17:20 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:33394 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725842AbfKUDRT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 22:17:19 -0500
Received: by mail-pf1-f196.google.com with SMTP id c184so914257pfb.0;
        Wed, 20 Nov 2019 19:17:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=afs5vPkDYDSkIEE429bn/bge2dwQpMMiXF8V7dNT+hw=;
        b=tB+HWlPF3ie8/BGAa9YnevvES0YAW+ZJcCXejpA13Dfy6JGmJHiqxm113ZOG/opi7/
         Unvq0ERP9FfZCzwrYvADU5P7bycYroBuTL9l7RcmiWACuD4Dnd6Nbd90PWuINaDopPjf
         4/LMnTlVB3Gk4TvcJxVJFaW7ZoVdIiOGcxlTMExVMu9tWlCUZCWLdLALYVi3riEUA/TR
         aE5DlsL/ejkK2zzIDyuRI8ZfB0VwQNGy4U8CnVJrnUcI8rB86aaN/1b0aiegB+UUo1Hy
         UCI7eLxugjYfYXMcqjIRyZa2yAgOx0RkRxB5BN/4E8EDTznqOnljfa9r6DPMk4IZfvBj
         F4wg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=afs5vPkDYDSkIEE429bn/bge2dwQpMMiXF8V7dNT+hw=;
        b=Mgm5ObwaisXE1Y+qIc54u+dnyjo6LnrekeYoXR9yX1XhOZ9pe5/WtV+2wu0y2d6no8
         CuD/2KAE0YnhQZk7Sz5aNWklTyc7zMWuxZBD+XDSHMydfpfKHvDw+wldy/ceNMwIKYt3
         740Yo45QT/04CY+hyvk9seAcPXhOHNWSgwcKy6UxcBsT/V7aMVCxJWPJ3CA608GcKVky
         PhsYryvD1WAtxqGqtVHYh/HJ5eSOfMoQj5Iu5/YSKKBOgvA4OKMJQaNEixe8DISytuab
         PuW52FEcFlQRwE+878Eu9B3CoK92XR1Ceyxl0OZOY+LuMNmjsqOV33VLKeWgD46Qlw0k
         34fQ==
X-Gm-Message-State: APjAAAVqw3rdOyCtxy3XXqFAm4hairM/QZlwOrUMkhMADTikSfa6szvj
        edRzq+jdzuGolAvAJuI/2ZQiSLX3
X-Google-Smtp-Source: 
 APXvYqxu0MbAOBUyK2JVbPRsRSbGsNOO7zgOUvr+9OsBpyViKK1eTPmAiAmXpkXUMqwPEjXskkalJw==
X-Received: by 2002:a63:5f49:: with SMTP id t70mr7048024pgb.219.1574306238549;
        Wed, 20 Nov 2019 19:17:18 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 q4sm639248pgp.30.2019.11.20.19.17.15
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 20 Nov 2019 19:17:17 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v4 1/2] KVM: VMX: FIXED+PHYSICAL mode single target IPI
 fastpath
Date: Thu, 21 Nov 2019 11:17:11 +0800
Message-Id: <1574306232-872-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

ICR and TSCDEADLINE MSRs write cause the main MSRs write vmexits in our 
product observation, multicast IPIs are not as common as unicast IPI like 
RESCHEDULE_VECTOR and CALL_FUNCTION_SINGLE_VECTOR etc.

This patch introduce a mechanism to handle certain performance-critical 
WRMSRs in a very early stage of KVM VMExit handler.

This mechanism is specifically used for accelerating writes to x2APIC ICR 
that attempt to send a virtual IPI with physical destination-mode, fixed 
delivery-mode and single target. Which was found as one of the main causes 
of VMExits for Linux workloads.

The reason this mechanism significantly reduce the latency of such virtual 
IPIs is by sending the physical IPI to the target vCPU in a very early stage 
of KVM VMExit handler, before host interrupts are enabled and before expensive
operations such as reacquiring KVM’s SRCU lock.
Latency is reduced even more when KVM is able to use APICv posted-interrupt
mechanism (which allows to deliver the virtual IPI directly to target vCPU 
without the need to kick it to host).

Testing on Xeon Skylake server:

The virtual IPI latency from sender send to receiver receive reduces 
more than 200+ cpu cycles.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v3 -> v4:
 * check !is_guest_mode(vcpu)
 * ACCEL_EXIT_SKIP_EMUL_INS don't need be -1
 * move comments on top of handle_accel_set_x2apic_icr_irqoff
 * update patch description
v2 -> v3:
 * for both VMX and SVM
 * vmx_handle_exit() get second parameter by value and not by pointer
 * rename parameter to “accel_exit_completion”
 * preserve tracepoint ordering
 * rename handler to handle_accel_set_msr_irqoff and more generic
 * add comments above handle_accel_set_msr_irqoff
 * msr index APIC_BASE_MSR + (APIC_ICR >> 4)
v1 -> v2:
 * add tracepoint
 * Instead of a separate vcpu->fast_vmexit, set exit_reason
  to vmx->exit_reason to -1 if the fast path succeeds.
 * move the "kvm_skip_emulated_instruction(vcpu)" to vmx_handle_exit
 * moving the handling into vmx_handle_exit_irqoff()

 arch/x86/include/asm/kvm_host.h | 11 ++++++++--
 arch/x86/kvm/svm.c              | 15 +++++++++----
 arch/x86/kvm/vmx/vmx.c          | 14 +++++++++---
 arch/x86/kvm/x86.c              | 48 +++++++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/x86.h              |  1 +
 5 files changed, 78 insertions(+), 11 deletions(-)

```
#### [PATCH 1/5] kvm: Introduce KVM irqchip change notifier
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11255093
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B8D414DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 00:58:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E1422208A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 00:58:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=gibson.dropbear.id.au
 header.i=@gibson.dropbear.id.au header.b="IcxKWzfs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726614AbfKUA6r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 19:58:47 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:44437 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726333AbfKUA6q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 19:58:46 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 47JLm41Hqpz9sNx; Thu, 21 Nov 2019 11:58:44 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1574297924;
        bh=fREJuuqgAEuiDzU2O79CZ0GSodqvDi8dVSOI0miZGuE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=IcxKWzfsNp+TDMm/FcmYOF/G6BK8Fwdx7sj3AbbpJBecSmOD3EvejoKZXJ9Hdo5X4
         GBJcG9PY7fmZVX3w/91Q8nXcqBSmyoGG35fPguQUP2szAqbFxrua9emPjVKUaoeYJL
         b8W+cjT9+2k1AAe70PVOMNqijScMEkmCl0xnVIm4=
From: David Gibson <david@gibson.dropbear.id.au>
To: Alex Williamson <alex.williamson@redhat.com>, clg@kaod.org
Cc: groug@kaod.org, philmd@redhat.com, qemu-ppc@nongnu.org,
 Paolo Bonzini <pbonzini@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Laurent Vivier <laurent@vivier.eu>,
 David Gibson <david@gibson.dropbear.id.au>, kvm@vger.kernel.org,
 qemu-devel@nongnu.org, Riku Voipio <riku.voipio@iki.fi>, =?utf-8?q?Marc-And?=
	=?utf-8?q?r=C3=A9_Lureau?= <marcandre.lureau@redhat.com>,
 Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH 1/5] kvm: Introduce KVM irqchip change notifier
Date: Thu, 21 Nov 2019 11:56:03 +1100
Message-Id: <20191121005607.274347-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20191121005607.274347-1-david@gibson.dropbear.id.au>
References: <20191121005607.274347-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Awareness of an in kernel irqchip is usually local to the machine and its
top-level interrupt controller.  However, in a few cases other things need
to know about it.  In particular vfio devices need this in order to
accelerate interrupt delivery.

If interrupt routing is changed, such devices may need to readjust their
connection to the KVM irqchip.  pci_bus_fire_intx_routing_notifier() exists
to do just this.

However, for the pseries machine type we have a situation where the routing
remains constant but the top-level irq chip itself is changed.  This occurs
because of PAPR feature negotiation which allows the guest to decide
between the older XICS and newer XIVE irq chip models (both of which are
paravirtualized).

To allow devices like vfio to adjust to this change, introduce a new
notifier for the purpose kvm_irqchip_change_notify().

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Alexey Kardashevskiy <aik@ozlabs.ru>

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
---
 accel/kvm/kvm-all.c    | 18 ++++++++++++++++++
 accel/stubs/kvm-stub.c | 12 ++++++++++++
 include/sysemu/kvm.h   |  5 +++++
 3 files changed, 35 insertions(+)

```
#### [PATCH] virt: Fix Kconfig indentation
##### From: Krzysztof Kozlowski <krzk@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krzysztof Kozlowski <krzk@kernel.org>
X-Patchwork-Id: 11255273
Return-Path: <SRS0=EBfH=ZN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35FAA913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 03:25:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 167C02089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 21 Nov 2019 03:25:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1574306718;
	bh=NQZEd8v97Kx8SQRm2lC/02RuQn2Hi0S1xJaELXyodjA=;
	h=From:To:Subject:Date:List-ID:From;
	b=wKFNSDr69/LiS152+c3l4RQHA2y1j2upn3chukIvJYaV7psNWdH+9r5XWUiVQcID0
	 bvj1gQbYBmNwqIPv/PB5nm02a2JqwvJ4emJpfoKcGUth2+N92zMjOMqSF2gVALV9K3
	 Jq1LnNcm+03VLh+QX/HOZqjKaVJVWzidrhq0yNsg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727050AbfKUDZO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 22:25:14 -0500
Received: from mail.kernel.org ([198.145.29.99]:37548 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725936AbfKUDZM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 22:25:12 -0500
Received: from PC-kkoz.proceq.com (unknown [213.160.61.66])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B452B20721;
        Thu, 21 Nov 2019 03:25:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1574306711;
        bh=NQZEd8v97Kx8SQRm2lC/02RuQn2Hi0S1xJaELXyodjA=;
        h=From:To:Subject:Date:From;
        b=tjuF777b81OZLTIAEISe06O6iDt7pAlIM62+iBtTa7iDAgoQaOeOYqiwRledc6MmZ
         SYGM0S2jQSfuxk4O+A15KLBbZ0pASLcDvEf0naZPGQu0FGiAxkuAUxLhlb4j9obI2X
         zqkjvTESFPubj46tdActXy/4psdWpw6I5odTw+9I=
From: Krzysztof Kozlowski <krzk@kernel.org>
To: Jiri Kosina <trivial@kernel.org>, linux-kernel@vger.kernel.org,
 kernel-janitors@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Krzysztof Kozlowski <krzk@kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
 Greg Kroah-Hartman <gregkh@linuxfoundation.org>, kvm@vger.kernel.org
Subject: [PATCH] virt: Fix Kconfig indentation
Date: Thu, 21 Nov 2019 04:25:02 +0100
Message-Id: <1574306702-7834-1-git-send-email-krzk@kernel.org>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Adjust indentation from spaces to tab (+optional two spaces) as in
coding style with command like:
	$ sed -e 's/^        /\t/' -i */Kconfig

Signed-off-by: Krzysztof Kozlowski <krzk@kernel.org>
---

Changes since v1:
1. Fix also 7-space and tab+1 space indentation issues.
---
 drivers/virt/Kconfig | 10 +++++-----
 virt/kvm/Kconfig     | 42 +++++++++++++++++++++---------------------
 2 files changed, 26 insertions(+), 26 deletions(-)

```
