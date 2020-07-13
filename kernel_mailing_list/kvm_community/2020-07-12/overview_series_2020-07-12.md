#### [PATCH 1/2] rculist : Introduce list/hlist_for_each_entry_srcu() macros
##### From: madhuparnabhowmik10@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
X-Patchwork-Id: 11658189
Return-Path: <SRS0=s85P=AX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB71A1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 13:10:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 93927206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 13:10:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="JhlgiLXk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728847AbgGLNKX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 12 Jul 2020 09:10:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49278 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728686AbgGLNKV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 12 Jul 2020 09:10:21 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 32A2AC061794;
        Sun, 12 Jul 2020 06:10:21 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id z3so4763833pfn.12;
        Sun, 12 Jul 2020 06:10:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=NRP39QoMA7cboQj2MMbTyFFjYJ67xWA6XbsSY/jB4dA=;
        b=JhlgiLXkD5O4zUGxXccVQPXMT+O9o31DADprV5OMtKmgXgwlyQDyU6AHHqfQhE5WDR
         gh5b7kg1tMcyp7AboKcI3mVUn5/qm89WJOEiNibftq/jOQEKkxQzTk37RfP+SpFJJd9L
         4TjLUq1DlQ19yLYAdhUXnAvimn3qmIX7ObMY5J2FOxASotv4BtIullWP63iJy4HsroOj
         U65y23wASAoSP20WQ6BwLVSu8J3+lE8szV/mSTbI3FCCUX9/L/nBKqwJsdlrs8NbFA1A
         ugtQV82lcIzXRaUNqb/D4kPjsUKXNmCZ5CTHMUXJ7R74r0HW9eEvKuqZUawq1z60LL84
         IqZQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=NRP39QoMA7cboQj2MMbTyFFjYJ67xWA6XbsSY/jB4dA=;
        b=d7PiObanZmbBIQ961R1LOM/mBvtnhEwtoK3Dj+wlkwr6Qu4ZXXF/oXspO8ao3k2R4e
         bSEMrAzIz2DRCxk7lTbbWi39jqVV02VnfFZzGX7J9r41OzCXG6+wWxobOFGIf4AQX9Yj
         ir59KuwdP39gJKanSAvM5J137RiwAqx5uxOyor6Bi3BWrtD9oHxMne3qHdydnCaINyGY
         HzOICjSu1i8zLFBpqTCmdedXNJDBnoBiefOc9qxFIy6Yv9MtQugpj/WDs2jyEVN9aHuO
         sVEYZqUqsOlNGU42kZkE9twbrcF7vxCuuam3F/igfc0ZaoLm+kzu599ICi8n1RF9/goq
         BUPQ==
X-Gm-Message-State: AOAM530JUACt+jbcqxdsK/NZvlJgGxcRY76OVkEl4vuezjjuTTvBgo1b
        uuELXNo0tZVeQu+p4w386A==
X-Google-Smtp-Source: 
 ABdhPJyrr3l21D86j8HF4DyLsuHvOdUtkQkflxGYyEfr832mw/NrHe0iwr46Z+tErL/jQPKe027rGQ==
X-Received: by 2002:a05:6a00:2286:: with SMTP id
 f6mr68025222pfe.303.1594559420452;
        Sun, 12 Jul 2020 06:10:20 -0700 (PDT)
Received: from localhost.localdomain
 ([2409:4071:200a:9520:4919:edd3:5dbd:ffec])
        by smtp.gmail.com with ESMTPSA id
 q24sm12093014pfg.95.2020.07.12.06.10.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 12 Jul 2020 06:10:19 -0700 (PDT)
From: madhuparnabhowmik10@gmail.com
To: paulmck@kernel.org, josh@joshtriplett.org, joel@joelfernandes.org,
        pbonzini@redhat.com
Cc: rcu@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org,
        kvm@vger.kernel.org, frextrite@gmail.com,
        Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
Subject: [PATCH 1/2] rculist : Introduce list/hlist_for_each_entry_srcu()
 macros
Date: Sun, 12 Jul 2020 18:40:02 +0530
Message-Id: <20200712131003.23271-1-madhuparnabhowmik10@gmail.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>

list/hlist_for_each_entry_rcu() provides an optional cond argument
to specify the lock held in the updater side.
However for SRCU read side, not providing the cond argument results
into false positive as whether srcu_read_lock is held or not is not
checked implicitly. Therefore, on read side the lockdep expression
srcu_read_lock_held(srcu struct) can solve this issue.

However, the function still fails to check the cases where srcu
protected list is traversed with rcu_read_lock() instead of
srcu_read_lock(). Therefore, to remove the false negative,
this patch introduces two new list traversal primitives :
list_for_each_entry_srcu() and hlist_for_each_entry_srcu().

Both of the functions have non-optional cond argument
as it is required for both read and update side, and simply checks
if the cond is true. For regular read side the lockdep expression
srcu_read_lock_head() can be passed as the cond argument to
list/hlist_for_each_entry_srcu().

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
---
 include/linux/rculist.h | 48 +++++++++++++++++++++++++++++++++++++++++
 1 file changed, 48 insertions(+)

```
#### [RFC v8 01/25] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11658085
Return-Path: <SRS0=s85P=AX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C675013B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 11:19:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B401020725
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 11:19:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728783AbgGLLTn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 12 Jul 2020 07:19:43 -0400
Received: from mga09.intel.com ([134.134.136.24]:46276 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728715AbgGLLTm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 12 Jul 2020 07:19:42 -0400
IronPort-SDR: 
 Poay6IuvfcDoJr9utB4wuDlWVrkYOAGRXnG+0YNWPdvvka0oXfIKrZiYJARDNef1khs9ydy9s/
 AaJsymwBI1Ag==
X-IronPort-AV: E=McAfee;i="6000,8403,9679"; a="149953092"
X-IronPort-AV: E=Sophos;i="5.75,343,1589266800";
   d="scan'208";a="149953092"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Jul 2020 04:19:41 -0700
IronPort-SDR: 
 IbEpF/SfMFDotCTAHk0Kk3ipGF/urtGbg0qvT9GmOY5PjIAKy7IXHVPTeo7+mCwMzPMiDfvINp
 1A8oWUpgwSWA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,343,1589266800";
   d="scan'208";a="307121375"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga004.fm.intel.com with ESMTP; 12 Jul 2020 04:19:41 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        jasowang@redhat.com, Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v8 01/25] scripts/update-linux-headers: Import iommu.h
Date: Sun, 12 Jul 2020 04:25:57 -0700
Message-Id: <1594553181-55810-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1594553181-55810-1-git-send-email-yi.l.liu@intel.com>
References: <1594553181-55810-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### 
##### 

```c
```
#### [PATCH 2/2] kvm: mmu: page_track: Fix RCU list API usage
##### From: madhuparnabhowmik10@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
X-Patchwork-Id: 11658191
Return-Path: <SRS0=s85P=AX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD201722
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 13:10:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4B4820725
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 13:10:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="CDx8EbSN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728862AbgGLNK3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 12 Jul 2020 09:10:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49296 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728857AbgGLNK1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 12 Jul 2020 09:10:27 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A36DCC061794;
        Sun, 12 Jul 2020 06:10:27 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id x72so4784506pfc.6;
        Sun, 12 Jul 2020 06:10:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=QlHdcq1NMFZUiVr/PWZTQMUwB+nApvKctneHSUoV9JI=;
        b=CDx8EbSNzRbyCNhyw7LW1mm97sOqmMXjqAFWs4mxTiPuHBDb0GM1lk1UwKagomOVR5
         pFVN5rAHmjjq0wHMbWdUctDF6J0OpGVsK21gv74z/DHVdqRe5Cv0V4OkzuaqOKRu0VDc
         3tUtThRmTJNUYnY/olbPHMAUcalI2BDfArzx0sfEk26J8q21cHTwII/j0FwMwPCBNZyy
         7ACuD6Ua+HhLe4dh9NmV0YWtHilYo+WvHMXXGIr8Lu3Sy7gHi1RC4Q8ehTMGvQ3DJq6+
         hMcnS9E7DoQ/qiqvzI58Ye1eQ5fc2U3FyqXTfIRE+TQCDhRH6S7kaOUDIz8tmxyAaN2k
         yCkw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=QlHdcq1NMFZUiVr/PWZTQMUwB+nApvKctneHSUoV9JI=;
        b=BXGEm/TW7bWqZ8wZO/nYWXPy420IVu7s/mFp0HvEiYg8W4omPnY06C5Ps72oJ9CUI0
         Qbqw8zvFEerjLWDJ6ansvx4vRa2Tj4mEJLI9Modox69LvmM3Dpix/ZiXlQuyFAtcz1Ve
         izCZIg2C/1s4ATsIx+s28gdkaSiPe1N/c+8/IJIigfKD6UWcbzvVNb+GvUIk6bf2WWjj
         AYv98ymZtz8vLYAJ4Ab+nDCtCl8ZdsGGo4fZcAktKo8d5HfoK6qoEJhI3HSitXHEoHM7
         IDZIeMGgBwYv/svo8bgNv/Iwk06L2yQ2vyX4zO+g8xF9//UxenBv3sGi0ubzIIMZaUtQ
         Z/eQ==
X-Gm-Message-State: AOAM533DkuRoVrjx+dISyVlzc67zyclnv77C9Dhk6tTYipDNDhyqDmy9
        5BaYaZNrNzFawgf5nabfzg==
X-Google-Smtp-Source: 
 ABdhPJzGCWqeGrl0pmni+0aENWLJwun+oPUDiRCIjS3IwjlN3XTVOCk6hJo4EVWSlnu21qMCqiR/Cg==
X-Received: by 2002:a62:b413:: with SMTP id
 h19mr17778687pfn.142.1594559427253;
        Sun, 12 Jul 2020 06:10:27 -0700 (PDT)
Received: from localhost.localdomain
 ([2409:4071:200a:9520:4919:edd3:5dbd:ffec])
        by smtp.gmail.com with ESMTPSA id
 q24sm12093014pfg.95.2020.07.12.06.10.22
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 12 Jul 2020 06:10:26 -0700 (PDT)
From: madhuparnabhowmik10@gmail.com
To: paulmck@kernel.org, josh@joshtriplett.org, joel@joelfernandes.org,
        pbonzini@redhat.com
Cc: rcu@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org,
        kvm@vger.kernel.org, frextrite@gmail.com,
        Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
Subject: [PATCH 2/2] kvm: mmu: page_track: Fix RCU list API usage
Date: Sun, 12 Jul 2020 18:40:03 +0530
Message-Id: <20200712131003.23271-2-madhuparnabhowmik10@gmail.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200712131003.23271-1-madhuparnabhowmik10@gmail.com>
References: <20200712131003.23271-1-madhuparnabhowmik10@gmail.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>

Use hlist_for_each_entry_srcu() instead of hlist_for_each_entry_rcu()
as it also checkes if the right lock is held.
Using hlist_for_each_entry_rcu() with a condition argument will not
report the cases where a SRCU protected list is traversed using
rcu_read_lock(). Hence, use hlist_for_each_entry_srcu().

Signed-off-by: Madhuparna Bhowmik <madhuparnabhowmik10@gmail.com>
---
 arch/x86/kvm/mmu/page_track.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v5 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11658053
Return-Path: <SRS0=s85P=AX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9ED6D14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 11:14:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 857222070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 12 Jul 2020 11:14:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728844AbgGLLOi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 12 Jul 2020 07:14:38 -0400
Received: from mga09.intel.com ([134.134.136.24]:45842 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728686AbgGLLOd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 12 Jul 2020 07:14:33 -0400
IronPort-SDR: 
 VqkYwc3I8YF/LZLRHSOp8nxhOh5o6HJjdlbzfk/TOKwi2ueykT5nh+HriStYwaZ2JuTP8cHG6I
 OntGkTe/l4WA==
X-IronPort-AV: E=McAfee;i="6000,8403,9679"; a="149952678"
X-IronPort-AV: E=Sophos;i="5.75,343,1589266800";
   d="scan'208";a="149952678"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Jul 2020 04:14:29 -0700
IronPort-SDR: 
 RDFOsVSqdfGZ7Yo4heef9dnurGq/VoLKyeHN0O56086a9mvE4JPn5XQ3/5UtUp10Z2t40eC66j
 hbZvRUhIiiyQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,343,1589266800";
   d="scan'208";a="315788552"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 12 Jul 2020 04:14:29 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v5 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
Date: Sun, 12 Jul 2020 04:20:56 -0700
Message-Id: <1594552870-55687-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1594552870-55687-1-git-send-email-yi.l.liu@intel.com>
References: <1594552870-55687-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch refactors the vfio_iommu_type1_ioctl() to use switch instead of
if-else, and each command got a helper function.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Suggested-by: Christoph Hellwig <hch@infradead.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
v4 -> v5:
*) address comments from Eric Auger, add r-b from Eric.
---
 drivers/vfio/vfio_iommu_type1.c | 394 ++++++++++++++++++++++------------------
 1 file changed, 213 insertions(+), 181 deletions(-)

```
