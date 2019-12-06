#### [PATCH v15 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11275187
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 611BA14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:24:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3F3B124648
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:24:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="MoDAOdDL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729956AbfLEQY1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 11:24:27 -0500
Received: from mail-qk1-f194.google.com ([209.85.222.194]:35199 "EHLO
        mail-qk1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729022AbfLEQY0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 11:24:26 -0500
Received: by mail-qk1-f194.google.com with SMTP id v23so3859742qkg.2;
        Thu, 05 Dec 2019 08:24:26 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=MoDAOdDLiXkd2mmrv89OI8/1XQi/spAoBOcO0B90RXtvWez6nZ2Vw/gw5fhMl6hy23
         tX7wmDr4PeDibNua9+HL3ONCbzZXQzsBPy/nVc1JEdHw74+q1h6/e3bk1WJfJ5sDH9Cz
         nC2XlOnYNdfjU3BNBE4Jd25qXkmn4Q97ryT5gKoxSMeojdRtJ7X6Hfc2l6/wj3UAqz2y
         XdZN2SduJvSVlGQ2oG9a0kPGzmshnNgkU6C2TnxkG3ado6v7whAS3xDKqQvqtf57HnTy
         gM51eMIcSVlXbhJyJUy7VYyErZbCCJb5EsWbecOoq/oaRirDWRXKDHrMlndpN0Fpj0tp
         EzFQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=VitjQQFQG7H0A5JYqbYhHy/YWDiYO6QESupJyX3H62U=;
        b=hOUmk77pGUzGDGOll4Ws2IlBA/2i0QzC/YORbiOHJ7ty74omtnVpdi8RI5wv1If88X
         +lHbX/OXCrxn5h+ok486S1KkOk7LMxRhPd2LBe+qA83bZkGbv0PgGg4Pzjf8lM0O0/p8
         Qvi+h9iM4NP4EBH1tVd6qJHcv0jm6okdCZ4Ls1pNG2+TTvU+LYxK7TpxXZ6Q7eyfj+Y7
         j+Ftf+ScPpkQIm48PQtq/jwQUSOXLYarNVApqSwGR6oAEZsNPYYLGU4HScRgW7eYwd+5
         Is9wHToVMKvlmI/9n0HHwtekHXWb6W7Ear8L3w90TFWQYeV9htXaHrqb9P+cxYBnYOwn
         cUcw==
X-Gm-Message-State: APjAAAXNHY9jmMEcDFBjfdp+Yr1MhGT/gkci45bkcjqejMsqzjGY7Nay
        DEIGMH5UFo7LnqcB1QtcRqY=
X-Google-Smtp-Source: 
 APXvYqwbhhV9N6SY1MyzCV7zGOyh0Ck15qjiRFB99mBVTj/3p1/lpntOgFfoR4xVFUGQs+b4j2ihug==
X-Received: by 2002:a05:620a:100d:: with SMTP id
 z13mr9428194qkj.475.1575563065667;
        Thu, 05 Dec 2019 08:24:25 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 17sm5111246qkk.81.2019.12.05.08.24.23
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Dec 2019 08:24:25 -0800 (PST)
Subject: [PATCH v15 QEMU 2/3] virtio-balloon: Add bit to notify guest of
 unused page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Thu, 05 Dec 2019 08:24:22 -0800
Message-ID: <20191205162422.19737.57728.stgit@localhost.localdomain>
In-Reply-To: <20191205161928.19548.41654.stgit@localhost.localdomain>
References: <20191205161928.19548.41654.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH v15 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11275191
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D4A113A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:24:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E3572464D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:24:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="rZy8V/vY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730106AbfLEQYh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 11:24:37 -0500
Received: from mail-qt1-f195.google.com ([209.85.160.195]:36654 "EHLO
        mail-qt1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730025AbfLEQYf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 11:24:35 -0500
Received: by mail-qt1-f195.google.com with SMTP id k11so4080933qtm.3;
        Thu, 05 Dec 2019 08:24:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=rZy8V/vYjGvdbgJlSFDtmo8ogCsBeJGr6yuSCLQteDkgYJTOlDnBamwOQxlrK2xI3Z
         EoqHXHkvYA5Rzl8VAkLsvudDATzeFfXjQK4e+rRSVN8xUoBXBxS1xlzH0lWDP1DdM+mC
         +v5Zkh5NMc1XHazTbBnfZIQSpjiC129hvAyrRhiLSSpKg/pyMTiZVoteLjnYb1Sy5LG7
         tTRhQ7OIWfag0kwcI2RCK2UVftjRGuaLUIATqtm97TbEQ7JvLl6fS4qmQKeIVt5mKBtr
         SfWzRbSkTLAsLHjLFn8IWi7YYje8A4y2fygga4aBsVmNy9zlMJFttmKhMf8KPoksWYL/
         duTg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=IYnIZF3ya8GRMyw0Z8v44wRFjachYcZ/Qaw0Oz7Yqys=;
        b=DOnCwxzwwp/wF8uNmifg3j0T3VfnBNYVA7wQc1TkRuYa5pGRXjWfUww13Gfjex8H2c
         WzW5xpUEGXQBnrfgSiAyFGP4nC4HvY+a5YUmevdX1IK0icYabfDUdS+q4TeessnXzOv/
         bi2NCuO6V3yh1aG2seNM9+TX9bNCtyS6TG9nDay2VNjM9CxNoFJZeMQwf/a0VKznUnKc
         QvvgnqafqyKRa2QoRxhGCxJ9ThjuVFuPxKc+WFHkBQA/dblCpPZQ1vQjwvPAArRWvkKa
         OpqdkkiyFn+fnzAgXdnvHYntoTHTYYFQfIWcaqhC4Pg2+9qiBUrclj/fgTrsS2AXPLH+
         x5XA==
X-Gm-Message-State: APjAAAUy8sBsEJkRN/DlIHD1MSA6iTPH4cRhQRQFOxo8wYWCxh+UJmJ1
        UEr89++v82Q1Zbplx7oBaik=
X-Google-Smtp-Source: 
 APXvYqyHkpEt+nyTFEI72kz7jPPyhHyR1sq3FFWTrrVMlKqbT1JWZmRDdTHVkJmw4SOSMOkOJJlhSw==
X-Received: by 2002:aed:3344:: with SMTP id u62mr8242458qtd.73.1575563074222;
        Thu, 05 Dec 2019 08:24:34 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 w40sm5442163qtw.26.2019.12.05.08.24.31
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Dec 2019 08:24:33 -0800 (PST)
Subject: [PATCH v15 QEMU 3/3] virtio-balloon: Provide a interface for unused
 page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Thu, 05 Dec 2019 08:24:30 -0800
Message-ID: <20191205162430.19737.266.stgit@localhost.localdomain>
In-Reply-To: <20191205161928.19548.41654.stgit@localhost.localdomain>
References: <20191205161928.19548.41654.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH v15 QEMU 4/3 RFC] memory: Add support for MADV_FREE as mechanism to lazy discard pages
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11275197
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4557C14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:26:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1977724648
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:26:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="t9/xggbg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729723AbfLEQ00 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 11:26:26 -0500
Received: from mail-qk1-f195.google.com ([209.85.222.195]:43493 "EHLO
        mail-qk1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729708AbfLEQ00 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 11:26:26 -0500
Received: by mail-qk1-f195.google.com with SMTP id q28so3797653qkn.10;
        Thu, 05 Dec 2019 08:26:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=R+UOvEIvAKvV92s1Oao0n2zpHAWrzhC1LqeTb2UW2HA=;
        b=t9/xggbgalebn6gtzdADEpP2/88JmWDKLzkeui44+kXEH3yIEPk1BxlAMh11unW+I2
         qftiJxiIjiuVECscqgrDeB9oxETvsz7r5Khvd9/YHQ1qQzx82VBHaBb1u9b6trQmHI7l
         e172VxQDb8t7ysTyKdE4i9Mei2eFccxv8FNDvhNtrvAdCHaYIjllf4BTlVpEkDHgCT3j
         x1qWbuT1O8gT/LcSoJATuT/8kngQdCHQPtAfW11Inded8NvkEnqlvyumbR4UJuiKkEne
         bJoGbxGyyL7S53BXenqdFXLK+oGd0/WFLIkBVrOEOWzFedrqt1zwNT2gJOYMMKaaAOv1
         mCCw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=R+UOvEIvAKvV92s1Oao0n2zpHAWrzhC1LqeTb2UW2HA=;
        b=cPXZb3O5XdHA4Xr/HeKtk1uktXo5XaAPSP4gg3W48pDzOsCYYDOerv6tpVdEpiiT0D
         dAkBhyFB9heZGcul5avJtEYDWVwcKYRWFIricE14Fb36HbC8k3NxhyKqrFCkinTCl/nM
         ldQcVK+d7J1gsqDklK/F2iDRREUpAfpbip8sAIRDt+Qcan5Nc0ylHXp204DOIk6FhZN1
         CZK3b2BsNOYkozyvSwiELgAa449t9PjIUbjFEYYCg7dm0fu+re9pJwt8WQ7CkqBKWkIM
         GKl4GrISN4EaDXzQEcnvnMp7SHqFoPDOLmovdCf8kew+WHppjV/HdFrl9/an2mjb5JZ9
         s1qg==
X-Gm-Message-State: APjAAAU4eiVVoKEw0dWChhB9gEO815GmbcyTqNGqlzJwnokEKmvz+Q4F
        C++g9YiRyd8hlMhWp1vWvvDvvXQoQLM=
X-Google-Smtp-Source: 
 APXvYqxQsrpv2glIesTz+k0UmeB6q7vj3K9YresKbkETkdYqb3mZ9tuz2kYKduaGva/09sx0k0qxng==
X-Received: by 2002:a37:aa11:: with SMTP id t17mr9525332qke.60.1575563184711;
        Thu, 05 Dec 2019 08:26:24 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 j1sm3758151qkl.86.2019.12.05.08.26.21
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Dec 2019 08:26:23 -0800 (PST)
Subject: [PATCH v15 QEMU 4/3 RFC] memory: Add support for MADV_FREE as
 mechanism to lazy discard pages
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Thu, 05 Dec 2019 08:26:21 -0800
Message-ID: <20191205162506.19787.9449.stgit@localhost.localdomain>
In-Reply-To: <20191205161928.19548.41654.stgit@localhost.localdomain>
References: <20191205161928.19548.41654.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for the MADV_FREE advice argument when discarding pages.
Specifically we add an option to perform a lazy discard for use with free
page reporting as this allows us to avoid expensive page zeroing in the
case that the system is not under memory pressure.

To enable this I simply extended the ram_block_discard_range function to
add an extra parameter for "lazy" freeing. I then renamed the function,
wrapped it in a function defined using the original name and defaulting
lazy to false. From there I created a second wrapper for
ram_block_free_range and updated the page reporting code to use that.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 exec.c                     |   39 +++++++++++++++++++++++++++------------
 hw/virtio/virtio-balloon.c |    2 +-
 include/exec/cpu-common.h  |    1 +
 3 files changed, 29 insertions(+), 13 deletions(-)

```
#### [RFC PATCH 1/9] vfio/pci: introduce mediate ops to intercept vfio-pci ops
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11274099
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF6346C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:34:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8221F2073B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:34:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728560AbfLEDd7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 22:33:59 -0500
Received: from mga11.intel.com ([192.55.52.93]:22205 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728132AbfLEDd7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 22:33:59 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 04 Dec 2019 19:33:58 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,279,1571727600";
   d="scan'208";a="243094895"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.9])
  by fmsmga002.fm.intel.com with ESMTP; 04 Dec 2019 19:33:56 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        libvir-list@redhat.com, qemu-devel@nongnu.org, cohuck@redhat.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH 1/9] vfio/pci: introduce mediate ops to intercept vfio-pci
 ops
Date: Wed,  4 Dec 2019 22:25:36 -0500
Message-Id: <20191205032536.29653-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191205032419.29606-1-yan.y.zhao@intel.com>
References: <20191205032419.29606-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

when vfio-pci is bound to a physical device, almost all the hardware
resources are passthroughed.
Sometimes, vendor driver of this physcial device may want to mediate some
hardware resource access for a short period of time, e.g. dirty page
tracking during live migration.

Here we introduce mediate ops in vfio-pci for this purpose.

Vendor driver can register a mediate ops to vfio-pci.
But rather than directly bind to the passthroughed device, the
vendor driver is now either a module that does not bind to any device or
a module binds to other device.
E.g. when passing through a VF device that is bound to vfio-pci modules,
PF driver that binds to PF device can register to vfio-pci to mediate
VF's regions, hence supporting VF live migration.

The sequence goes like this:
1. Vendor driver register its vfio_pci_mediate_ops to vfio-pci driver

2. vfio-pci maintains a list of those registered vfio_pci_mediate_ops

3. Whenever vfio-pci opens a device, it searches the list and call
vfio_pci_mediate_ops->open() to check whether a vendor driver supports
mediating this device.
Upon a success return value of from vfio_pci_mediate_ops->open(),
vfio-pci will stop list searching and store a mediate handle to
represent this open into vendor driver.
(so if multiple vendor drivers support mediating a device through
vfio_pci_mediate_ops, only one will win, depending on their registering
sequence)

4. Whenever a VFIO_DEVICE_GET_REGION_INFO ioctl is received in vfio-pci
ops, it will chain into vfio_pci_mediate_ops->get_region_info(), so that
vendor driver is able to override a region's default flags and caps,
e.g. adding a sparse mmap cap to passthrough only sub-regions of a whole
region.

5. vfio_pci_rw()/vfio_pci_mmap() first calls into
vfio_pci_mediate_ops->rw()/vfio_pci_mediate_ops->mmaps().
if pt=true is rteturned, vfio_pci_rw()/vfio_pci_mmap() will further
passthrough this read/write/mmap to physical device, otherwise it just
returns without touch physical device.

6. When vfio-pci closes a device, vfio_pci_release() chains into
vfio_pci_mediate_ops->release() to close the reference in vendor driver.

7. Vendor driver unregister its vfio_pci_mediate_ops when driver exits

Cc: Kevin Tian <kevin.tian@intel.com>

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/pci/vfio_pci.c         | 146 ++++++++++++++++++++++++++++
 drivers/vfio/pci/vfio_pci_private.h |   2 +
 include/linux/vfio.h                |  16 +++
 3 files changed, 164 insertions(+)

```
#### [PATCH] KVM: explicitly set rmap_head->val to 0 in pte_list_desc_remove_entry()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11274131
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 69E9B930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:40:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 508F5206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:40:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728470AbfLEDkb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 22:40:31 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:44090 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728321AbfLEDkb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 22:40:31 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id E28AD3E158DAB2F72557;
        Thu,  5 Dec 2019 11:40:28 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Thu, 5 Dec 2019
 11:40:22 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: explicitly set rmap_head->val to 0 in
 pte_list_desc_remove_entry()
Date: Thu, 5 Dec 2019 11:40:16 +0800
Message-ID: <1575517216-5571-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When we reach here, we have desc->sptes[j] = NULL with j = 0.
So we can replace desc->sptes[0] with 0 to make it more clear.
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: get rid of var page in kvm_set_pfn_dirty()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11274091
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DE606930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:05:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA86E206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 03:05:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728522AbfLEDF0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 22:05:26 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:6754 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728132AbfLEDF0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 22:05:26 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 873A727D263DBA667E76;
        Thu,  5 Dec 2019 11:05:24 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.439.0; Thu, 5 Dec 2019
 11:05:09 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
Subject: [PATCH] KVM: get rid of var page in kvm_set_pfn_dirty()
Date: Thu, 5 Dec 2019 11:05:05 +0800
Message-ID: <1575515105-19426-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

We can get rid of unnecessary var page in
kvm_set_pfn_dirty() , thus make code style
similar with kvm_set_pfn_accessed().
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 virt/kvm/kvm_main.c | 7 ++-----
 1 file changed, 2 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: s390: ENOTSUPP -> EOPNOTSUPP fixups
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11274709
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8FBEA112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 12:51:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 775022464D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 12:51:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729385AbfLEMv4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 07:51:56 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26690 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729260AbfLEMvz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Dec 2019 07:51:55 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xB5ClW24139278
        for <kvm@vger.kernel.org>; Thu, 5 Dec 2019 07:51:54 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wq1ky1ym3-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 05 Dec 2019 07:51:54 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 5 Dec 2019 12:51:51 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 5 Dec 2019 12:51:49 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xB5Cp7E343778516
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Dec 2019 12:51:07 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 28E5242042;
        Thu,  5 Dec 2019 12:51:48 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 139534203F;
        Thu,  5 Dec 2019 12:51:48 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu,  5 Dec 2019 12:51:48 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id AB58BE0193; Thu,  5 Dec 2019 13:51:47 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>,
        Julian Wiedmann <jwi@linux.ibm.com>
Subject: [PATCH] KVM: s390: ENOTSUPP -> EOPNOTSUPP fixups
Date: Thu,  5 Dec 2019 13:51:47 +0100
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19120512-0012-0000-0000-000003719A08
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19120512-0013-0000-0000-000021AD5E69
Message-Id: <20191205125147.229367-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-05_03:2019-12-04,2019-12-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 clxscore=1015
 mlxlogscore=585 malwarescore=0 priorityscore=1501 impostorscore=0
 mlxscore=0 bulkscore=0 phishscore=0 lowpriorityscore=0 suspectscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912050108
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no ENOTSUPP for userspace

Reported-by: Julian Wiedmann <jwi@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 arch/s390/kvm/interrupt.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] gitlab-ci.yml: Remove ioapic from the x86 tests
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11274925
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B999930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 15:16:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D2494224F8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 15:16:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G59JhW1P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729703AbfLEPQX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 10:16:23 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:51368 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725909AbfLEPQW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 10:16:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575558981;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=cnoBSQm0lwSHMe37ahohej7X57A4qxkFsgbHask0LpA=;
        b=G59JhW1PaxF6izmTWqOYyn6ibdC6jCOY/CIPGEAfkPwzTyLiGYw9rVYZxeuLFlX17cNGIC
        MW1rL9ibjilIAn0DtnD0PYmQh6J3uO4t0ildQ5MgqTszyLz0hj2V9JYugeqAJAK6h9F4oA
        PDlyVcR46g/6Wy4V2ZhdlUdqN8bscPc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-35-n5uzlMnuPfOQZeu6wlO0Cg-1; Thu, 05 Dec 2019 10:16:19 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E0AAD18557CF
        for <kvm@vger.kernel.org>; Thu,  5 Dec 2019 15:16:18 +0000 (UTC)
Received: from thuth.com (ovpn-116-87.ams2.redhat.com [10.36.116.87])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4D5CC5C1B5;
        Thu,  5 Dec 2019 15:16:15 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Nitesh Narayan Lal <nitesh@redhat.com>
Subject: [kvm-unit-tests PATCH] gitlab-ci.yml: Remove ioapic from the x86
 tests
Date: Thu,  5 Dec 2019 16:16:10 +0100
Message-Id: <20191205151610.19299-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: n5uzlMnuPfOQZeu6wlO0Cg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test recently started to fail (likely do to a recent change to
"x86/ioapic.c). According to Nitesh, it's not required to keep this
test running with TCG, and we already check it with KVM on Travis,
so let's simply disable it here now.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .gitlab-ci.yml | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] travis.yml: Run 32-bit tests with KVM, too
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11275215
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40C2E138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 17:04:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1EC2A2464D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 17:04:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CaTmBXyY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729450AbfLEREr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 12:04:47 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:43029 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726028AbfLEREq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Dec 2019 12:04:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1575565485;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=16IYc5dS6zYO/z7QMm0aTUaEXtYpTed94MKFrF8nPi0=;
        b=CaTmBXyYZykR1f9h4HaF3Q5KlvU66DErScSwWNAX2SQ1o13MFkivDKeRb+lH0P50ZmAs2I
        n1/bs52t21iN8OvNQxZDd9ykOWrrM7jFLTqdZRsdw44CJkDoyZj2MHNGCRpa/AoD9TdHkZ
        rBsAkV6H/4Sf79yQF8fcR/wMlImyyFY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-371-EU3TYODrN9K18sfHxsP0rw-1; Thu, 05 Dec 2019 12:04:44 -0500
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 528A889A084
        for <kvm@vger.kernel.org>; Thu,  5 Dec 2019 17:04:43 +0000 (UTC)
Received: from thuth.com (ovpn-116-87.ams2.redhat.com [10.36.116.87])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5C70B77340;
        Thu,  5 Dec 2019 17:04:42 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] travis.yml: Run 32-bit tests with KVM, too
Date: Thu,  5 Dec 2019 18:04:39 +0100
Message-Id: <20191205170439.11607-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: EU3TYODrN9K18sfHxsP0rw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM works on Travis in 32-bit, too, so we can enable more tests there.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: vmx: remove unreachable statement in vmx_get_msr_feature()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11274083
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9463313B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 02:24:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7BEC5206DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 02:24:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728548AbfLECYy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Dec 2019 21:24:54 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:6752 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728321AbfLECYy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Dec 2019 21:24:54 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id D14B59F30D9FE1D13864;
        Thu,  5 Dec 2019 10:24:52 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Thu, 5 Dec 2019
 10:24:42 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: vmx: remove unreachable statement in
 vmx_get_msr_feature()
Date: Thu, 5 Dec 2019 10:24:38 +0800
Message-ID: <1575512678-22058-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

We have no way to reach the final statement, remove it.
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v15 1/7] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11275151
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 099CC14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:22:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D1B8524249
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:22:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="uIfAEHq6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729802AbfLEQWS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 11:22:18 -0500
Received: from mail-qv1-f65.google.com ([209.85.219.65]:33446 "EHLO
        mail-qv1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729535AbfLEQWS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 11:22:18 -0500
Received: by mail-qv1-f65.google.com with SMTP id z3so1511428qvn.0;
        Thu, 05 Dec 2019 08:22:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=vRTdXLGlIRX6PGjWF3qAFy+h5lzWEe6Gf9rZrQkRSH8=;
        b=uIfAEHq6JimSlQBcMBhmaULOeAD7Vvh2X5L8lzGiyu0Ry/6Y5+C9JT+PaXCVpSLCt6
         zjTTboECeXwVD3xXnTWKQR+Uov+X64pLr7ZvtqGeBdO6YAC6Ew/iZmGl5mkPaog5aGHG
         XP6RJj1ToWmY7/SPzrWt7bdhoBO3lZcdg7mkZfakQgQMOZnjrahVu8MdtoNwQjABMjrw
         /oaS/28gV7xznVBmNuHblADEyHwIzt7DztrJ2GsUyWvJQDFPRVljl038STMkoV0MCSyn
         LQwjYJbk49Rsjtn1QNBYQikbK00xS0gVRY2z/GhkfPkgKXqnjFN5/OH5MmsZvrnlcoo2
         J/7Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=vRTdXLGlIRX6PGjWF3qAFy+h5lzWEe6Gf9rZrQkRSH8=;
        b=seQ8UsGxxTnTczlpYMV8DekHLFsUmY+qFdPW4LPPeolcrWwM6TfDxUPzYWyuLpHwVc
         ZIeGWbA9MWZvkD6UWC8pS/wx+4wrJWpfAse9BYRly8rYfNO2mIKJlHjFCLBTs6Gnh2BK
         FTHayq5ASAGFySxlnM9fY7xD7k8ZgBzwDQ8+18fU4tstQVb+HpUDQC3b7UBiQQV0TbCZ
         TVtuh77ID5hyAQUquLWh9l7BkFrCyapYQ+iFtWml02ucFZjxehHiaOYS9AWAQZSC7Xcl
         PacMGgHOIsL+NPtzQ5l+WCKQ65wGk0ZjPDVyWE/7I+LZCTAT6vOBMzhEEOCotsx2I+zU
         ZAOg==
X-Gm-Message-State: APjAAAVvQTwI7zw0zX21VKM7orBWLtaanTp5hXwaZPQK0UUDljPGAPkC
        RVpVahMj+tmAK/8298Q2ENQ=
X-Google-Smtp-Source: 
 APXvYqwnGSyW1+3kT6T8to6/Da1ka4NOZRDmwiSEfwCbqd5xsIDbQSsXest4DBdRS+z9vmXboVV6Ag==
X-Received: by 2002:a05:6214:38c:: with SMTP id
 l12mr8254725qvy.224.1575562936266;
        Thu, 05 Dec 2019 08:22:16 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 t2sm5038677qkc.31.2019.12.05.08.22.13
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Dec 2019 08:22:15 -0800 (PST)
Subject: [PATCH v15 1/7] mm: Adjust shuffle code to allow for future
 coalescing
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Thu, 05 Dec 2019 08:22:12 -0800
Message-ID: <20191205162212.19548.68878.stgit@localhost.localdomain>
In-Reply-To: <20191205161928.19548.41654.stgit@localhost.localdomain>
References: <20191205161928.19548.41654.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH v15 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11275183
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D981F13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:24:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ACD1724648
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 16:24:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="IY/c7tBV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729850AbfLEQYS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 11:24:18 -0500
Received: from mail-qv1-f65.google.com ([209.85.219.65]:40609 "EHLO
        mail-qv1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729022AbfLEQYS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Dec 2019 11:24:18 -0500
Received: by mail-qv1-f65.google.com with SMTP id i3so1489287qvv.7;
        Thu, 05 Dec 2019 08:24:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=IY/c7tBVGp0dCi3cvAYPJY/SgaeppYt3/QVWerBgbLa28snETBe67Z+akPo/uEQD8G
         CXzRqiSVpsANwxS+QyG712YReJ7pIlafiztVBgsQB0hu8h646TKeV0ErSfNHStTc/qyJ
         1X/Sw90IrgAIf3CP5ukylBRuXjFkpvmgsNIK2NK+e5qAoH7Ok3ih2MVKsjfiLAHE8Gu2
         mVR0LmV8n8gmOHRxEiK33x2eRfJlk6s0+P4MFVAkFvYRFSnI5AEPQKVSyYagM6xlJymR
         TNQ71amc6LR9lPYFZKsyOrAN7gThx1z5WB4L/ycbGYHcYRUOyqZm+nBYy/YP9bui078w
         DzmA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=yOvpSx16yNanZpbvFfAUMxFv0SM7m3MFplEES/wscuI=;
        b=qfS/jbIlQuePYCuqsVStXpecgo1BZXydERqiOgBWE9B+aAFhB/wGoh0UPUCbW29Y0I
         Huy9NYMtqmdh8QjXVxAwtZaHYgmIw8M0bsHF21gc5vwCo2pASUpM0HNrqLKkCjzkbW1b
         agzCQn3FknHjc0AiuYfmGfCVOyZm2UFRENRlFobkWSXIja2TLfjYkANPvDAjIb5h9obL
         ibbf3hC9LUhOxP1wYWQ5KNKjEMGcXSbxLg3+7F85Cqo7EQ5kMuqPVzOfG0A0DVsx0wv7
         A3clCrSTvpAsseg2iowvOGU48ngxzXOMskwqMPIsFJJbho+mOFonkKq66AB9QYdqxKKU
         vIbQ==
X-Gm-Message-State: APjAAAVIfnEJY1kESg60uv51z6zI6Jji04i2rPkNRhV9oaomsgJRx2jI
        4QhrJY/zgix6odYwaWZIAyk=
X-Google-Smtp-Source: 
 APXvYqxJ3i0l+FEOzYiFPbv93BX8TjI95vYQH98PYBO1KUPXzjcQKY2u/EBBF21DBCUkn68iLFTeuQ==
X-Received: by 2002:a05:6214:6ad:: with SMTP id
 s13mr8030151qvz.208.1575563057135;
        Thu, 05 Dec 2019 08:24:17 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 s27sm3648216qkm.97.2019.12.05.08.24.14
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 05 Dec 2019 08:24:16 -0800 (PST)
Subject: [PATCH v15 QEMU 1/3] virtio-ballon: Implement support for page
 poison tracking feature
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        mgorman@techsingularity.net, vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Thu, 05 Dec 2019 08:24:13 -0800
Message-ID: <20191205162413.19737.43311.stgit@localhost.localdomain>
In-Reply-To: <20191205161928.19548.41654.stgit@localhost.localdomain>
References: <20191205161928.19548.41654.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
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
#### [PATCH v3] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11274689
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 434E3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 12:10:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1EB3A224F8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 12:10:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729332AbfLEMKI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 07:10:08 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:63394 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729048AbfLEMKH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Dec 2019 07:10:07 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xB5BxL0O097920
        for <kvm@vger.kernel.org>; Thu, 5 Dec 2019 07:10:06 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2wpupb6jce-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 05 Dec 2019 07:10:05 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 5 Dec 2019 12:10:04 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 5 Dec 2019 12:10:01 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xB5CA11o30343360
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Dec 2019 12:10:01 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DE0CCA405B;
        Thu,  5 Dec 2019 12:10:00 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 10C60A4062;
        Thu,  5 Dec 2019 12:10:00 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.146])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  5 Dec 2019 12:09:59 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH v3] KVM: s390: Add new reset vcpu API
Date: Thu,  5 Dec 2019 07:09:56 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19120512-4275-0000-0000-0000038BB754
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19120512-4276-0000-0000-0000389F5C59
Message-Id: <20191205120956.50930-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-05_03:2019-12-04,2019-12-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 suspectscore=1
 lowpriorityscore=0 phishscore=0 malwarescore=0 clxscore=1015
 impostorscore=0 adultscore=0 mlxlogscore=999 mlxscore=0 priorityscore=1501
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912050100
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that. Now that we have a new interface, let's
properly clear out local IRQs and let this commit be a reminder.

Also we add a ioctl for the clear reset to have all resets exposed to
userspace. Currently the clear reset falls back to the initial reset,
but we plan to have clear reset specific code in the future.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 Documentation/virt/kvm/api.txt | 45 ++++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.c       | 14 +++++++++++
 include/uapi/linux/kvm.h       |  5 ++++
 3 files changed, 64 insertions(+)

```
#### [PATCH v4] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11274703
Return-Path: <SRS0=8IBs=Z3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2458138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 12:28:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8FCF62464D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Dec 2019 12:28:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729099AbfLEM2i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Dec 2019 07:28:38 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:20468 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729048AbfLEM2i (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Dec 2019 07:28:38 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xB5CMGeQ145681
        for <kvm@vger.kernel.org>; Thu, 5 Dec 2019 07:28:37 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2wq1pngnff-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 05 Dec 2019 07:28:37 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 5 Dec 2019 12:28:35 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 5 Dec 2019 12:28:16 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xB5CRZ8K49938712
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Dec 2019 12:27:35 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DD835A405C;
        Thu,  5 Dec 2019 12:28:15 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 12287A405B;
        Thu,  5 Dec 2019 12:28:15 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.146])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  5 Dec 2019 12:28:14 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH v4] KVM: s390: Add new reset vcpu API
Date: Thu,  5 Dec 2019 07:28:10 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191205131930.1b78f78b.cohuck@redhat.com>
References: <20191205131930.1b78f78b.cohuck@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19120512-0012-0000-0000-00000371978F
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19120512-0013-0000-0000-000021AD5BD9
Message-Id: <20191205122810.10672-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-12-05_03:2019-12-04,2019-12-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 mlxlogscore=999
 mlxscore=0 malwarescore=0 priorityscore=1501 lowpriorityscore=0
 bulkscore=0 impostorscore=0 phishscore=0 suspectscore=1 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1912050104
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that. Now that we have a new interface, let's
properly clear out local IRQs.

Also we add a ioctl for the clear reset to have all resets exposed to
userspace. Currently the clear reset falls back to the initial reset,
but we plan to have clear reset specific code in the future.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virt/kvm/api.txt | 48 ++++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.c       | 14 ++++++++++
 include/uapi/linux/kvm.h       |  5 ++++
 3 files changed, 67 insertions(+)

```
