#### [PATCH v10 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11151099
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC9E1912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:53:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C9195207FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:53:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="H3wKs22G"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729111AbfIRRxy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 13:53:54 -0400
Received: from mail-oi1-f196.google.com ([209.85.167.196]:41663 "EHLO
        mail-oi1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726369AbfIRRxy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 13:53:54 -0400
Received: by mail-oi1-f196.google.com with SMTP id w17so339275oiw.8;
        Wed, 18 Sep 2019 10:53:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=H3wKs22GCSuuo47NHL84cjAcqIxVWe5raJSaPJYEEjR4SjLfOrFfKt6MqETcP09nzp
         mQwVOuGJiDyTUO34zz/FxTfyeK93Ym+rSqbDgLoT/Du3oNzP1D0AIlwxjhzYcrzwwKIs
         xtuGXJ2uADX6hCimeVVU5uKTm/0RBb5zaza/2xkqpEofa5+pRdcP/FX/pDjy6nqeQhrz
         wjIwWTS1OwEhcVqKPV+UX49i5jyRIkdBII/ejcvGqW6cFvW/aBaQMvKszzUiDF4oubCx
         FgrHvJ+7pmJW4fOmM+9tKSwU3cS7m7q8ml0xlT15/H7ej/2b2YhZqe7ipz773fsTquBb
         b4Uw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=kIbIakxBKm9YFDXzbMAXKJZt0MpC7UrVVKUCZPkoPP96rMj7PGP8DFp7FHtqJcOczF
         gIageJyTYENynA+ozskJtWF9vDvm9EiTBYcPXliUNGPgmCACFIvfDwKlaAz4OhisqIM7
         c+uRCAE08OJmkfRi/CKxYAgc1/AvocjVHuuy78kcKdRPLHkNo41HvkPBljH8rT80Y+nZ
         6vEZ8DD9Qqhlccl1lBTXTmaAmw96tll9WSz0F5/D3twrUeIo8B2mXQYX/jdkaKcRntlS
         /P4M3rllB++r2/eJts0j70OO+mgXnBLnsY1FP0XDiWpjEKTsvT0Rygp8BLc0cLSMDMAD
         llrw==
X-Gm-Message-State: APjAAAVM5nG3yAwmVsVSNpPPPKYkHU3s4XoBisDjQoSFGdKuxjCybWeR
        JvGxmHQqYX1COacZk1CGnKY=
X-Google-Smtp-Source: 
 APXvYqx0/em4LyihxJp1UfPCVlfU74a3jjEiza4M/rCWhu2/BqxunUOAE7tRJ9fzvgWCTQRlNSJFbA==
X-Received: by 2002:aca:dcd5:: with SMTP id
 t204mr3293467oig.138.1568829232972;
        Wed, 18 Sep 2019 10:53:52 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 o184sm1837530oia.28.2019.09.18.10.53.50
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 10:53:52 -0700 (PDT)
Subject: [PATCH v10 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, vbabka@suse.cz,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        linux-arm-kernel@lists.infradead.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Wed, 18 Sep 2019 10:53:50 -0700
Message-ID: <20190918175350.23606.70808.stgit@localhost.localdomain>
In-Reply-To: <20190918175109.23474.67039.stgit@localhost.localdomain>
References: <20190918175109.23474.67039.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add a bit for the page reporting feature provided by virtio-balloon.

This patch should be replaced once the feature is added to the Linux kernel
and the bit is backported into this exported kernel header.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v10 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11151105
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD21114DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:54:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ADC7121907
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:54:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LTNZIrLw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730415AbfIRRyE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 13:54:04 -0400
Received: from mail-oi1-f195.google.com ([209.85.167.195]:45144 "EHLO
        mail-oi1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726369AbfIRRyD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 13:54:03 -0400
Received: by mail-oi1-f195.google.com with SMTP id o205so310828oib.12;
        Wed, 18 Sep 2019 10:54:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=R9EIePxtKgh7rutMNGBvqWvR/nyIQIv1yBQVlI6lc80=;
        b=LTNZIrLwNpo92TNcI8W1IT3U3577/c3Jf88Jz4fjWPt6ckGenXS4Aj+ubn6fknNPte
         dFeh5GMIWCel3raxfV+/wgQsENSBqB9ur0TcFOuBPRBuXAFjAcQxE1/pSHMiiqXfaOtW
         089YD96NofSWv8xxPbCJ76Cj03mfxamPzjaxt2Cs9aAtvSF9Kmz7ClA38Q/7hlaD8pKE
         res37qYDQQtNDHE6M6UPpYhyi6Bo9od2ePymsGudW80c2dPMiQDUo+zHO8vFKCJazJLL
         tUJvQhkYX0Q7tpXdmdf0o8fexnZV6zxDWQTtvql2/Uq/h86UcQwQMojV9lerwKIUXxnA
         qtvA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=R9EIePxtKgh7rutMNGBvqWvR/nyIQIv1yBQVlI6lc80=;
        b=q3+inol2K1czBDZ7JGAehjbPYoTzweQiVrohxiK52j2583d/Po5VmS09i2OyR8XxzT
         VpzXcxh9p4iK17SqzFgCCWkZ6s1ZK2walhMNhCgcdU62Imts+Voljo9rbJd96kHtT7Sh
         oTf9BtdBnGubZ34WSUzemYw8CI6HmgrRUXu0zdMqgwjv4UnFkj+Z25Ktf0z6XEu6fa1l
         XCwtcL72jNBR2Mmc3U+XYMTec6XLKfGIHiA8clRC9b7qdqGtLl4xmos8o4JONbngYThp
         4k3fHhS756IVveCcQRjrPzwsLJkLfugAHLR677rAKaOw4JzYV0E25KBro/emoK4CrvxR
         zqhg==
X-Gm-Message-State: APjAAAX/oY6ZeblsotifEdgctnUc6AQiti7tWskiE8OMC9znC/FQXT9O
        MUDaHePpTl6NnDdJgIdgEgQ=
X-Google-Smtp-Source: 
 APXvYqyEYqDoFoDB3Jq5Cx0XqTh1k3BdQAaRYyAqWuTQQjfDrJkZ+I2Lkjh0apNqfqsxVUfFMhQF2Q==
X-Received: by 2002:aca:5252:: with SMTP id g79mr3227961oib.72.1568829240890;
        Wed, 18 Sep 2019 10:54:00 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 l17sm465658oic.24.2019.09.18.10.53.58
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 10:54:00 -0700 (PDT)
Subject: [PATCH v10 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, vbabka@suse.cz,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        linux-arm-kernel@lists.infradead.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Wed, 18 Sep 2019 10:53:58 -0700
Message-ID: <20190918175358.23606.22732.stgit@localhost.localdomain>
In-Reply-To: <20190918175109.23474.67039.stgit@localhost.localdomain>
References: <20190918175109.23474.67039.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   46 ++++++++++++++++++++++++++++++++++--
 include/hw/virtio/virtio-balloon.h |    2 +-
 2 files changed, 45 insertions(+), 3 deletions(-)

```
#### [RFC PATCH v3 1/6] psci: Export psci_ops.conduit symbol as modules will use it.
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Jianyong Wu (Arm Technology China)"
 <jianyong.wu@arm.com>
X-Patchwork-Id: 11149819
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1480214E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 08:07:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F026620882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 08:07:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729539AbfIRIHh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 04:07:37 -0400
Received: from foss.arm.com ([217.140.110.172]:36768 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729510AbfIRIHg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 04:07:36 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3EA731570;
        Wed, 18 Sep 2019 01:07:36 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 28F5B3F59C;
        Wed, 18 Sep 2019 01:07:30 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com,
        Will.Deacon@arm.com, suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com,
        linux-arm-kernel@lists.infradead.org
Subject: [RFC PATCH v3 1/6] psci: Export psci_ops.conduit symbol as modules
 will use it.
Date: Wed, 18 Sep 2019 04:07:11 -0400
Message-Id: <20190918080716.64242-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190918080716.64242-1-jianyong.wu@arm.com>
References: <20190918080716.64242-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If arm_smccc_1_1_invoke used in modules, psci_ops.conduit should
be export.

Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 drivers/firmware/psci/psci.c | 6 ++++++
 include/linux/arm-smccc.h    | 2 +-
 include/linux/psci.h         | 1 +
 3 files changed, 8 insertions(+), 1 deletion(-)

```
#### [GIT PULL] Urgent KVM fix
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11150447
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D19DD16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 14:22:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AF32221920
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 14:22:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="sHvaxBqP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729301AbfIROWh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 10:22:37 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:36588 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726484AbfIROWh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 10:22:37 -0400
Received: by mail-wm1-f67.google.com with SMTP id t3so285986wmj.1;
        Wed, 18 Sep 2019 07:22:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=6nKowSJkmj6y8SDyX3nXm1VDFEY4+KARvCaZgONZgTY=;
        b=sHvaxBqPoh9HdPutDdOHYNG2SiQafQqOoadtmSUHyz4TErj7HkOAVFdD3fLxc1PVw1
         lpqaAH51OsWTKx8X84zmbkSqZgFQhhFGjJqKE1ov9OuP6FIXbGEBwQQhqy8+1Ce5pAf3
         VUaUWu3i8/CW+QmemKXDsJM/WfwkC/bBbjxlz9kKSZgeMwwINkDivaEp/HfTCGuvTU14
         4jB4VoH5Wqsfbf+Xqg3kURDJ4nT6Xjkv1KHFx0VF1wgXnjlXpclZbq4U6UVvmz/qKd3Z
         JbGq8HyiiCxAtqGObSJ2bAXe6jge6XbJrNNTO5AmIu41RCgeXFXFN8BYojJddSg1kv8v
         poUA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=6nKowSJkmj6y8SDyX3nXm1VDFEY4+KARvCaZgONZgTY=;
        b=SDCwECkup0cPakP6adTzco2rnMk4zoPguBFBEpQVKJT9ztkYhIi7zq/14TQwZNVP6M
         DcNWxNZpBQDdSAiBgTZIwDNTh9HBs+wehvpB0dUwKBr+Xw9z99l371SqBasnulrDvprq
         ACjZBwessEHjnGcqwajR6OtH8jnigiwqsTbYRD985zBQRRjspakqWER4Oi7hUXgG/tQf
         2GFJKx5AoaAWJGUHHYIynHDZ83SkBMejBuSfbfTMpXtHDUpCClrCY1tkVwaLrMJ1MjVZ
         WFcoVysgCTJZuHfKeJl9IjLdaCtSPWdSRdrW9IqSUAdEUlL2b8b/MhkZDt7DpES4rZs/
         4BLg==
X-Gm-Message-State: APjAAAVSXOrFSk7xxAXOuBmPKkf9qzn86mrA6T3f9JsV9ttonVwSVJv8
        MCZXY15juoYa6AjolEGPklpHtV9A
X-Google-Smtp-Source: 
 APXvYqzCiXXfMRBxI/rS2G2gjm1hhgWe8jjxTZ2GV+783JJXtxbjxzg3RbvVoB2WwI7yT9MKS+K5RA==
X-Received: by 2002:a1c:1d85:: with SMTP id d127mr3358148wmd.14.1568816555351;
        Wed, 18 Sep 2019 07:22:35 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 q19sm10849959wra.89.2019.09.18.07.22.34
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 07:22:34 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] Urgent KVM fix
Date: Wed, 18 Sep 2019 16:22:33 +0200
Message-Id: <1568816553-26210-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

this pull request is independent of the merge window.  Please pull it as it
fixes a longstanding bug that was recently found by both Google humans
and bots (syzkaller).

The following changes since commit a9c20bb0206ae9384bd470a6832dd8913730add9:

  Merge tag 'kvm-s390-master-5.3-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-master (2019-09-14 09:25:30 +0200)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus-urgent

for you to fetch changes up to b60fe990c6b07ef6d4df67bc0530c7c90a62623a:

  KVM: coalesced_mmio: add bounds checking (2019-09-18 15:56:55 +0200)

----------------------------------------------------------------
Fix missing bounds-checking in coalesced_mmio (CVE-2019-14821).

----------------------------------------------------------------
Matt Delco (1):
      KVM: coalesced_mmio: add bounds checking

 virt/kvm/coalesced_mmio.c | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)
```
#### [PATCH] KVM: coalesced_mmio: add bounds checking
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11150437
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DCD55112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 14:01:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBFCF21927
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 14:01:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="XgiMB28S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729535AbfIROBs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 10:01:48 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:35753 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726038AbfIROBs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 10:01:48 -0400
Received: by mail-wm1-f67.google.com with SMTP id y21so207668wmi.0;
        Wed, 18 Sep 2019 07:01:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=sIYpPV0gwYoKAB5S6WKsIvLkhM2b1flwKz65XoEniwc=;
        b=XgiMB28SY8wROslEuzRRNotbmYHYT9AJlCfFHcf7rriCyJKEi10dDd4yXKJFmMGlSp
         XL0V5RK/nWqO4twAvYM1D6fURQWDSzpIL6Oh8jlRly74iueAWptAEqFVEBDujCYrmXJv
         tfg9KsUEWuepePhXPrKU7hC7BOkpuMQfOos/urLJ42FckYo+ojfqQcSCn8JmnOFobD5p
         ck6veQ5rqAN8jjRbfI5cR3iaX2ntZIqMPYTNLeluHFu+VE4FsPZk9PzK2uh9ngofTn3t
         y4Y97zzjg6aLAZpY75/c5ZfiRZg+Z4Kt6of4CaFU+DgwzfFIk+o0BnfVKRY2UahRnWg4
         Co+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=sIYpPV0gwYoKAB5S6WKsIvLkhM2b1flwKz65XoEniwc=;
        b=SWcH00m1wzKA4kBl8sn47iwHp1KYJ9G/Mf9WbzKAScHY+DuhiErWPvaEH3bgfxtcRM
         Pxt3Yry1hmTxpypeuxRHKw7rLXtqA4G+e3CpGoQaBc/1b/y+j2sfa13D1VORKLf3Nmq0
         /8JGL7YDWYLf7qJr1dhEE+DFRIuMgkQHFOI4c7bXHgnhAXmJ4MJEu9FW/KJCfUe3T3w6
         qoXBwiA2AvEvLHi1CJbL8Gp+1zVezbYu4MuqtxEMjcIfq3Vp8zRyAKbQA3avgIaS4Vsr
         Mxh5ydNZJ2I3TANBQ4aQulov+gJYW5yY3C3xso9VFnKC2IowuuxukjK//8GO7qAoiuLL
         n+5w==
X-Gm-Message-State: APjAAAXvF3Pl1yr2IwiHKo6+50gCkX1vyN/BzU9dlzZ19zBPo37+akM9
        tHSipuytYBD7kakEnc4EgRlxgKVt
X-Google-Smtp-Source: 
 APXvYqwjPp6K7bF9k3yhxybpD/fzOc9ct3mAUrtnxNYLvvW/bLkgaizftrHvDWLgszNtQcvTaqzsAA==
X-Received: by 2002:a1c:a8d8:: with SMTP id
 r207mr2985299wme.135.1568815304882;
        Wed, 18 Sep 2019 07:01:44 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 f143sm4030710wme.40.2019.09.18.07.01.43
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 07:01:43 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: will@kernel.org, kernellwp@gmail.com, gregkh@linuxfoundation.org,
        Matt Delco <delco@chromium.org>, stable@vger.kernel.org,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH] KVM: coalesced_mmio: add bounds checking
Date: Wed, 18 Sep 2019 16:01:42 +0200
Message-Id: <1568815302-21319-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Matt Delco <delco@chromium.org>

The first/last indexes are typically shared with a user app.
The app can change the 'last' index that the kernel uses
to store the next result.  This change sanity checks the index
before using it for writing to a potentially arbitrary address.

This fixes CVE-2019-14821.

Cc: stable@vger.kernel.org
Fixes: 5f94c1741bdc ("KVM: Add coalesced MMIO support (common part)")
Signed-off-by: Matt Delco <delco@chromium.org>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reported-by: syzbot+983c866c3dd6efa3662a@syzkaller.appspotmail.com
[Use READ_ONCE. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Acked-by: Will Deacon <will@kernel.org>
---
 virt/kvm/coalesced_mmio.c | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)

```
#### [PATCH] kvm: Ensure writes to the coalesced MMIO ring are within bounds
##### From: Will Deacon <will@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Will Deacon <will@kernel.org>
X-Patchwork-Id: 11150351
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2037C912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 13:15:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F139C21848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 13:15:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1568812556;
	bh=wdv0YRFrnwocEp/J8v75uH7+80bZiAugwxHW/XSKkOQ=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=VYfiKcxqrVXeVznfCT/PpCUwiZPdZPnxwdlWydl/zcdvS2hgIp+QdS15Cbo9aCbV0
	 qTpAKuJh5XcjnrtJYVIgu/mQgInLVgHcjE+AMATpzEo9nMfRhmBmidZFtxC0/jBXB6
	 GJonncdJt2UR+RgZAfEpmibBihg847Z7dSGaE6yc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729177AbfIRNPw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 09:15:52 -0400
Received: from mail.kernel.org ([198.145.29.99]:37134 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726268AbfIRNPv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 09:15:51 -0400
Received: from localhost.localdomain (236.31.169.217.in-addr.arpa
 [217.169.31.236])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id CFF972067B;
        Wed, 18 Sep 2019 13:15:49 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1568812551;
        bh=wdv0YRFrnwocEp/J8v75uH7+80bZiAugwxHW/XSKkOQ=;
        h=From:To:Cc:Subject:Date:From;
        b=WG8IjvxASneWPVKCuK2j4lojJ8lyWBz8byWFLNq4gLQ7fbZmRtmpSudO7gBlXgeCl
         +FG7r+4UAC6/V1tGIvd4fodNE4EpwKRiKUdjUyo+UxcZnR86f34igN5JchBAfAA2ZN
         Y8C20v+JzeegvOFcLwOEjuHHQLzTQ2ehwDhqXHOo=
From: Will Deacon <will@kernel.org>
To: kvm@vger.kernel.org
Cc: kernellwp@gmail.com, linux-kernel@vger.kernel.org,
        Will Deacon <will@kernel.org>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "# 5 . 2 . y" <stable@kernel.org>
Subject: [PATCH] kvm: Ensure writes to the coalesced MMIO ring are within
 bounds
Date: Wed, 18 Sep 2019 14:15:45 +0100
Message-Id: <20190918131545.6405-1-will@kernel.org>
X-Mailer: git-send-email 2.11.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When records are written to the coalesced MMIO ring in response to a
vCPU MMIO exit, the 'ring->last' field is used to index the ring buffer
page. Although we hold the 'kvm->ring_lock' at this point, the ring
structure is mapped directly into the host userspace and can therefore
be modified to point at arbitrary pages within the kernel.

Since this shouldn't happen in normal operation, simply bound the index
by KVM_COALESCED_MMIO_MAX to contain the accesses within the ring buffer
page.

Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: <stable@kernel.org> # 5.2.y
Fixes: 5f94c1741bdc ("KVM: Add coalesced MMIO support (common part)")
Reported-by: Bill Creasey <bcreasey@google.com>
Signed-off-by: Will Deacon <will@kernel.org>
Reviewed-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---

I think there are some other fixes kicking around for this, but they
still rely on 'ring->last' being stable, which isn't necessarily the
case. I'll send the -stable backport for kernels prior to 5.2 once this
hits mainline.

 virt/kvm/coalesced_mmio.c | 13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [kvm-unit-tests PULL 1/9] s390x: Support PSW restart boot
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11150185
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 374B413BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 12:04:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 149C021907
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 12:04:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730537AbfIRMEi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 08:04:38 -0400
Received: from mx1.redhat.com ([209.132.183.28]:30416 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730527AbfIRMEh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 08:04:37 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 888643061424;
        Wed, 18 Sep 2019 12:04:37 +0000 (UTC)
Received: from thuth.com (ovpn-116-90.ams2.redhat.com [10.36.116.90])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 18702600CC;
        Wed, 18 Sep 2019 12:04:35 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, =?utf-8?b?UmFk?=
	=?utf-8?b?aW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>
Subject: [kvm-unit-tests PULL 1/9] s390x: Support PSW restart boot
Date: Wed, 18 Sep 2019 14:04:18 +0200
Message-Id: <20190918120426.20832-2-thuth@redhat.com>
In-Reply-To: <20190918120426.20832-1-thuth@redhat.com>
References: <20190918120426.20832-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Wed, 18 Sep 2019 12:04:37 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Add a boot PSW to PSW restart new, so we can also boot via a PSW
restart.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Message-Id: <20190826163502.1298-2-frankja@linux.ibm.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/flat.lds | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH v5 1/2] x86: nvmx: fix bug in __enter_guest()From: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11151261
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6BD2814DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 22:24:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 416B021848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 22:24:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="anjpHJqB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729968AbfIRWYD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 18:24:03 -0400
Received: from mail-pg1-f201.google.com ([209.85.215.201]:33521 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727562AbfIRWYC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 18:24:02 -0400
Received: by mail-pg1-f201.google.com with SMTP id a13so899529pgw.0
        for <kvm@vger.kernel.org>; Wed, 18 Sep 2019 15:24:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=qH+qWV7M5iG2j6Q45JOR9JSuN6XQU2iyO+O7k8OW1Ww=;
        b=anjpHJqBn3YEVXzbE3K2uMX3ufxmcDac5XfwfabrWSgGVMlHgtwkEvlAkDksCphd3b
         0NFxnQgwL28QmO2EuaNKs9DOkw41Zdw7Nl01QGhpvISkG4UA0svxpq/24cdIDMxIb21w
         ZZIdonGJOIIODZbLvpCOaNZq0j+8H/Z3v9dQFM5KspN3Xe5dVLwMB9j7WtyMTKUTh6Ps
         Yg6jjKXtVul1CBphfgZ9YSvaJE02AVcYMcry8G4GyN8Vze0CNz9y7sErL6ESeuwnyOFK
         mzH69rcA1S2r393Hr6Gu0iwKC5sRePNsIDZ1QuIz85vBQStJB0bPdGdxjaz27lYSWNji
         4tDQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=qH+qWV7M5iG2j6Q45JOR9JSuN6XQU2iyO+O7k8OW1Ww=;
        b=bb4DFkf8v1aWtGcNNqjQgHwWqZHmioZIWoMwGmxWFmPFFsTs4qtyl6+r2/VIEz58wx
         hZHq53tl74CC4z1QzHs9auU5EXV/ezlqSpk6r8YTw/hJ5Ynxh6Yc70u0QPfp1fOifCdf
         viGvmM/D0gWbtPzzuPLhpKL5Ubrlh1dxBBjaHJ61rKtveETA5TkBUn6GykDEzUZpLlAh
         wRjPqULrBSAZ9BaM4j6Fby1bPMioi3dPL2Uf2MSlPRjkcYSNH7o/xvQM1J93MC33ZQZE
         wiuA8WGVTfQ0SNBqovG/3u34myE8Pj8lVS4LRcX89YjsK1+wr1E/LpaHL5yxtuuP2/p6
         JO0A==
X-Gm-Message-State: APjAAAWA/fyBoQeOtcZyzWDyJyXw6BeziQIT66LN4leKgKksYbsMiWej
        hJbNi3Gwy9R5Nvt4l4Kpsuw34wYMjvQ2pX/NhOp7wuQyYfmHfu6E+rWRyIZKBVw3BBPj756trAs
        GD5C3C+S6FtZtiiFJuIV0bd3rsX6OYKOEtYHE8uMNVAxN8mxqn9Ore6WkXJ3f
X-Google-Smtp-Source: 
 APXvYqzAn/zuNvnvtbD3oNRIrEIj1jyK+LcaWplwQC4UpH4h4LuaCMSQNxUvnpFcf8ZRqZCesmidVK5uDLN7
X-Received: by 2002:a63:2c44:: with SMTP id s65mr6085828pgs.158.1568845440158;
 Wed, 18 Sep 2019 15:24:00 -0700 (PDT)
Date: Wed, 18 Sep 2019 15:23:53 -0700
Message-Id: <20190918222354.184162-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [kvm-unit-tests PATCH v5 1/2] x86: nvmx: fix bug in __enter_guest()
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com,
        sean.j.christopherson@intel.com, krish.sadhukhan@oracle.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__enter_guest() should only set the launched flag when a launch has
succeeded. Thus, don't set the launched flag when the VMX_ENTRY_FAILURE,
bit 31, is set in the VMCS exit reason.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v10 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11151063
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99A7B196C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:52:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6E69421924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:52:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="kY3Nlxw4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729506AbfIRRwj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 13:52:39 -0400
Received: from mail-ot1-f67.google.com ([209.85.210.67]:42808 "EHLO
        mail-ot1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726369AbfIRRwj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 13:52:39 -0400
Received: by mail-ot1-f67.google.com with SMTP id c10so618266otd.9;
        Wed, 18 Sep 2019 10:52:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=JWWH0nLE5gW80rwb17oSZfM6VHlugSoNSjEeC143ARI=;
        b=kY3Nlxw4jpobVoe1JNyEjEGVhrVb4uyehLGgS2nDS2Limxn/shG8A6UvTSmRmamYf2
         vpwJWEl0pAb1fTuvIm0LsMimt1aZGBGW7khdC8YTa6mZMWQBgNcgOjhkth8enlqk8txQ
         Ae58XB9KDodcprJ1+qW2Vd2g3Hj7eg/CzfS+9/r+j6C/7zwelWxgfjiiVIBKflrizYNg
         dLiTBEYyiQYtg7ouCjOE7MeRbNcfZPYmM4OpCYleG6Pv7X2Laj/RmtQzO8GQPnw7QWfJ
         sfV41kc38Vx9O9JU4Osh/nqinznN8zZcm/K3WaI5q2HT2bNdBne56siHa6p/8uFHnYXR
         XmZw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=JWWH0nLE5gW80rwb17oSZfM6VHlugSoNSjEeC143ARI=;
        b=ELuNAsZadH8QpBpZV2Y06ySgTkYqbPFmnK9Vd4Zx86YF78hscDQvb4MSpopsh82krx
         YtUy0h5YyJdu6RjmgqHfizLnQOEsLJjRFejh1VeQL+OPL7YnxEi9g4UrmS8mxhyESAP7
         vozlwnKwaURRvsqmH6zb4k7oRPgkk+rLynEJ0Lpv9IzNpDdhe9iXACiZAGlZUJlW16fD
         /qi3ggOU2Cnjl0yJcb4ueJ4iaNCwXj0Pz+5lSby8z7oevPYm9z3Yf6Zk9oOH+qluEgZi
         rKkqwHCZ35LbJfHMEyR5N2CssO2hCHukKoQZtN8g1prbnBbZuwxwHaE6YxcgUuwwieKO
         U2WQ==
X-Gm-Message-State: APjAAAWIoE4jFeXgAAl9UJi+/GJYMa4qpnKOc7EAF4zjqcHjylJrtdNe
        sEbqsVUE8AYpIstxwe0j0Qc=
X-Google-Smtp-Source: 
 APXvYqyH5jZB85XcGwqiW8u/CLFVrXYTftFKTWVpkVfA0lyvGzPyLpjSrqJtEvx3oszxU7OaB0xUKw==
X-Received: by 2002:a05:6830:214d:: with SMTP id
 r13mr3623505otd.121.1568829156454;
        Wed, 18 Sep 2019 10:52:36 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 e5sm1998110otr.81.2019.09.18.10.52.34
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 10:52:35 -0700 (PDT)
Subject: [PATCH v10 1/6] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, vbabka@suse.cz,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        linux-arm-kernel@lists.infradead.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Wed, 18 Sep 2019 10:52:33 -0700
Message-ID: <20190918175233.23474.93686.stgit@localhost.localdomain>
In-Reply-To: <20190918175109.23474.67039.stgit@localhost.localdomain>
References: <20190918175109.23474.67039.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Move the head/tail adding logic out of the shuffle code and into the
__free_one_page function since ultimately that is where it is really
needed anyway. By doing this we should be able to reduce the overhead
and can consolidate all of the list addition bits in one spot.

Acked-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   71 ++++++++++++++++++++++++++++--------------------
 mm/shuffle.c           |   12 ++++----
 mm/shuffle.h           |    6 ++++
 4 files changed, 54 insertions(+), 47 deletions(-)

```
#### [PATCH v10 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11151095
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 25531912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:53:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ECAF921924
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 17:53:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mxVRZRFo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730117AbfIRRxq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 13:53:46 -0400
Received: from mail-ot1-f66.google.com ([209.85.210.66]:43226 "EHLO
        mail-ot1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729111AbfIRRxq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 13:53:46 -0400
Received: by mail-ot1-f66.google.com with SMTP id b2so615214otq.10;
        Wed, 18 Sep 2019 10:53:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=a/jqoVnZMS4gCQHlsNMs0Wm0i9/bhDBfzuCMndLKGiI=;
        b=mxVRZRFofqB9VHPpnhAT0D2qY2vxDZ1aVOC8Ivg4ywPf0SoSqKkBkA0lErA+py0cOi
         Phoq68J5mWdb6Axadc87lebiz/yrt/Lt7XLsSf435rrSNrRmzw4YQitb5g4DJ43TmEfO
         bQWaa+eSzH50E0UlwKyPdM1f67Zbeu9B+6JNe0wyXmI+d8QFE0/ghL8e1hSSFe4ZelmR
         RtC37PGkriZyTxAS6cG+cJVCRG0tEqODfQEwbThwEPAk3D+9faNHzeAjTusBuL82Gk0b
         aYa6aDo58PZy43PBNx+jYufKFoA7j7I2A3YTfkK3efHTtU8DLE/ijZzPEqBgp0uBqJ8S
         7PxA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=a/jqoVnZMS4gCQHlsNMs0Wm0i9/bhDBfzuCMndLKGiI=;
        b=MXvtUKyObIywd2kylmOpOVO4R65PnuRHj4uchgAA33DCnx+ckWdb/kh41VKERyocGC
         wBhGZ3L1GOsnfd6nlKoDgVIRa2wE/uTn/J3wVK9TbUaho0lDYBNc8Egj5eQcp/5fvU5X
         //czU+p81wXY29lbePTVeaVRuX36MoN0QATiNLaL/Ggx7exMWxIoLmldA1ZP6yaV1ARK
         TqJfrAXFQoArJZL4o8cAcvWgnX20RVj2kuvEPTg3D4vgWLa/6+8TP8ihLgc/29Sm65mF
         /Ximztiz1GAa+j2uAbl1Q9iDsNSBcestoD2hlCm16wI6AIYSLYs4nz/n4/kJGjBzGPLu
         ntrQ==
X-Gm-Message-State: APjAAAXwQwWjt+FxaKjr76JEUjW6ZVUeJBmICoYHVris1zEG2rF3HXjr
        6tRayF4Ix9YN/FxW2JXA0lA=
X-Google-Smtp-Source: 
 APXvYqz0t5+ebI92vteMOWlqyFLfZiS195d+evCqucFxo/9o5+zuvvtyuNCeouoflWGA34VVfNklXQ==
X-Received: by 2002:a9d:2007:: with SMTP id n7mr3756897ota.132.1568829225129;
        Wed, 18 Sep 2019 10:53:45 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 w201sm2029870oie.44.2019.09.18.10.53.42
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Sep 2019 10:53:44 -0700 (PDT)
Subject: [PATCH v10 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, vbabka@suse.cz,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        linux-arm-kernel@lists.infradead.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        pbonzini@redhat.com, dan.j.williams@intel.com,
        alexander.h.duyck@linux.intel.com
Date: Wed, 18 Sep 2019 10:53:42 -0700
Message-ID: <20190918175342.23606.12400.stgit@localhost.localdomain>
In-Reply-To: <20190918175109.23474.67039.stgit@localhost.localdomain>
References: <20190918175109.23474.67039.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [PATCH v3] KVM: X86: Fix userspace set invalid CR4
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11150007
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4161014DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 09:50:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 14F7321920
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 09:50:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ahAQSlgQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727048AbfIRJuW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 05:50:22 -0400
Received: from mail-pf1-f196.google.com ([209.85.210.196]:38189 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726257AbfIRJuW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 05:50:22 -0400
Received: by mail-pf1-f196.google.com with SMTP id h195so4039740pfe.5;
        Wed, 18 Sep 2019 02:50:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=H0Psu3PhVMw4W2UhvH+UB9Pvbou3FZjlccsYwKn7bM4=;
        b=ahAQSlgQn+DpqeTBcw+FkvdwHW++TZRDbKgIrEkmvidIcVZEhJ7jsHf587MdjE8/lY
         gXaXJNs1CTtq7ZNrP9MUn3QZsSqH+GnLMTVs5ye72FSvjD2uGDkRVjnKzvqST5XkMfJ2
         q21Y6UhoFJbm+mL0X4r0hj2uJoRkK6FkSMFAIDtURRPt4plGOsDhu9wospOYGlqIO2NY
         wQAg2zxYYBcA297PcKLbOs/5NiUD72bqRoxDfpb4502sKZXO2IsFGA5H9/LcD+1G/Txl
         VXK0yujKvgiR38nbdWPPAnhGFkhAwJgMh3j2qLCNhWLNlHDbbxYEdVlW+tEP1CzQTQWU
         AW5w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=H0Psu3PhVMw4W2UhvH+UB9Pvbou3FZjlccsYwKn7bM4=;
        b=Pn06wVi4E81MKZm43aTKV9if0wCiFW7ORd0JhjoRdFosiCMUOao43CJWj0RqrNZ6EL
         qjLebLQ/2hKv2ZdNRmzWNtj63/tuAtbd2iAYV0K7bWdHf15XeZUsDFUxHpz01X8tJJZN
         DBWgLiAzcBbHldPI9z5JKZLLmSvwFSwwZxO/i1rvtlpvXOSZrz+BPo8IW6Nx+zqDpcHy
         j/E3MkQ8DsSyvtUmAs5BSRAZi8xxr4L7n+bEPlfbA6004fPTiL2+xYaOhrQrohLq+WdW
         Va6PmwsbaSZaHGM8vRjIcBHoA5LOYVUar0MC9Zcr8qzjYpfrzj1b+OXDpqPpjDheP0Ob
         K+5w==
X-Gm-Message-State: APjAAAW2Z1dq737u5w7nwXzB3k0VdAKvtcvxexgZv+ItccxZXfGsw2tQ
        PZWy4Ag/B5ZEVFZhz+aR4PnvBnj1
X-Google-Smtp-Source: 
 APXvYqxC9/NkTpM8jBHZ9ArfFP0frb/EJYTyB9VpuWjutvkwWhf+7i3r2zMFEogdqVw0iFhG+xKgzw==
X-Received: by 2002:a63:70d:: with SMTP id 13mr3195301pgh.326.1568800220986;
        Wed, 18 Sep 2019 02:50:20 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 g24sm8496563pgn.90.2019.09.18.02.50.18
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Wed, 18 Sep 2019 02:50:20 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 stable@vger.kernel.org
Subject: [PATCH v3] KVM: X86: Fix userspace set invalid CR4
Date: Wed, 18 Sep 2019 17:50:10 +0800
Message-Id: <1568800210-3127-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Reported by syzkaller:

	WARNING: CPU: 0 PID: 6544 at /home/kernel/data/kvm/arch/x86/kvm//vmx/vmx.c:4689 handle_desc+0x37/0x40 [kvm_intel]
	CPU: 0 PID: 6544 Comm: a.out Tainted: G           OE     5.3.0-rc4+ #4
	RIP: 0010:handle_desc+0x37/0x40 [kvm_intel]
	Call Trace:
	 vmx_handle_exit+0xbe/0x6b0 [kvm_intel]
	 vcpu_enter_guest+0x4dc/0x18d0 [kvm]
	 kvm_arch_vcpu_ioctl_run+0x407/0x660 [kvm]
	 kvm_vcpu_ioctl+0x3ad/0x690 [kvm]
	 do_vfs_ioctl+0xa2/0x690
	 ksys_ioctl+0x6d/0x80
	 __x64_sys_ioctl+0x1a/0x20
	 do_syscall_64+0x74/0x720
	 entry_SYSCALL_64_after_hwframe+0x49/0xbe

When CR4.UMIP is set, guest should have UMIP cpuid flag. Current
kvm set_sregs function doesn't have such check when userspace inputs
sregs values. SECONDARY_EXEC_DESC is enabled on writes to CR4.UMIP
in vmx_set_cr4 though guest doesn't have UMIP cpuid flag. The testcast
triggers handle_desc warning when executing ltr instruction since
guest architectural CR4 doesn't set UMIP. This patch fixes it by
adding valid CR4 and CPUID combination checking in __set_sregs.

syzkaller source: https://syzkaller.appspot.com/x/repro.c?x=138efb99600000

Reported-by: syzbot+0f1819555fbdce992df9@syzkaller.appspotmail.com
Cc: stable@vger.kernel.org
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 38 +++++++++++++++++++++-----------------
 1 file changed, 21 insertions(+), 17 deletions(-)

```
#### [PATCH RESEND v4 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11149721
Return-Path: <SRS0=6oZb=XN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 229E216B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 07:23:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0A74D218AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Sep 2019 07:23:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728674AbfIRHXg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Sep 2019 03:23:36 -0400
Received: from mga07.intel.com ([134.134.136.100]:60890 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726077AbfIRHXg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Sep 2019 03:23:36 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Sep 2019 00:23:35 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,519,1559545200";
   d="scan'208";a="187694685"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga007.fm.intel.com with ESMTP; 18 Sep 2019 00:23:33 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH RESEND v4 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
Date: Wed, 18 Sep 2019 15:23:28 +0800
Message-Id: <20190918072329.1911-2-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190918072329.1911-1-tao3.xu@intel.com>
References: <20190918072329.1911-1-tao3.xu@intel.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

No changes in v4.
---
 target/i386/cpu.c | 3 ++-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 4 ++++
 3 files changed, 7 insertions(+), 1 deletion(-)

```
