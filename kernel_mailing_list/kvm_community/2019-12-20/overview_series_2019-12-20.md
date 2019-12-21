#### [PATCH v2 01/18] dt-bindings: ARM SPE: highlight the need for PPI partitions on heterogeneous systems
##### From: Andrew Murray <andrew.murray@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Murray <Andrew.Murray@arm.com>
X-Patchwork-Id: 11305671
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D85D7109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 14:34:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B6CAA206CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 14:34:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727768AbfLTOaf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 09:30:35 -0500
Received: from foss.arm.com ([217.140.110.172]:51180 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727754AbfLTOaf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 09:30:35 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 8CAC431B;
        Fri, 20 Dec 2019 06:30:34 -0800 (PST)
Received: from e119886-lin.cambridge.arm.com (unknown [10.37.6.20])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B39603F718;
        Fri, 20 Dec 2019 06:30:32 -0800 (PST)
From: Andrew Murray <andrew.murray@arm.com>
To: Marc Zyngier <marc.zyngier@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will.deacon@arm.com>
Cc: Sudeep Holla <sudeep.holla@arm.com>, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Mark Rutland <mark.rutland@arm.com>
Subject: [PATCH v2 01/18] dt-bindings: ARM SPE: highlight the need for PPI
 partitions on heterogeneous systems
Date: Fri, 20 Dec 2019 14:30:08 +0000
Message-Id: <20191220143025.33853-2-andrew.murray@arm.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191220143025.33853-1-andrew.murray@arm.com>
References: <20191220143025.33853-1-andrew.murray@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sudeep Holla <sudeep.holla@arm.com>

It's not entirely clear for the binding document that the only way to
express ARM SPE affined to a subset of CPUs on a heterogeneous systems
is through the use of PPI partitions available in the interrupt
controller bindings.

Let's make it clear.

Signed-off-by: Sudeep Holla <sudeep.holla@arm.com>
Signed-off-by: Andrew Murray <andrew.murray@arm.com>
---
 Documentation/devicetree/bindings/arm/spe-pmu.txt | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH v2 01/17] KVM: Remove kvm_read_guest_atomic()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306297
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F0AA314B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:02:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CF0BB2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:02:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fNYWrw5q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727709AbfLTVCi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 16:02:38 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23920 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727422AbfLTVBy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 16:01:54 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576875713;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=fNYWrw5qfL3/XbVBGlXSem0gmj2Ftrav4SJ8/nRY0p+9jOcPZgarhiqpBEhUDfLZFb/vcS
        RSQ/uantnIgt9PUzXJAfsnoDWRQjzYtwd5eMTjzR2feQnKTsLOK55oc2/j+UZ+x82gryNW
        Pv88dYD6vczxYFeL0fyZkN0l8agqTZg=
Received: from mail-qk1-f197.google.com (mail-qk1-f197.google.com
 [209.85.222.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-422-Lx9IvbrxOOi0p0UI5zVTBw-1; Fri, 20 Dec 2019 16:01:51 -0500
X-MC-Unique: Lx9IvbrxOOi0p0UI5zVTBw-1
Received: by mail-qk1-f197.google.com with SMTP id n128so6735442qke.19
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 13:01:51 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=V1Gjmfnvikemx41IX79lWkwCxsivHbc/XpFfD0xH9vfs2aFcJgfPg5jugrcCxW5D9k
         7nAiOU/ztpXqPotwWoPTkjy0vrNqKE3k9oqqtmQyRMGsL62mU3LjRp5azx9yWEsa7W1y
         ycrN3tas1xcbbX7vEtyR7QoGE8Wotm1cmCu8bVCEhiZJ/EiO/Mo2Si3XCPcb4Hg5L7Tf
         0WvnfEtAneRXou/yOar+ZLivd83ojd/d1TE7fPaUedZsOF/cWw0AIV4wU+X/bWQis8JO
         AWv4DcgKCviRmwO7gpx559EStwirc6aJG1EdB0tXaQdkq6aOF59ZLgSmtDdzwXq9IUqG
         MaCQ==
X-Gm-Message-State: APjAAAX3tL8gGhPjTOicqMRl7wpNE5vUdydhRz1l4+SCbMcSVOmSsc0/
        epKuCBNwmyhSXTCMkdUxFs+w/VQd0eboLVMfP0WJvXiO4YaRIGKhEkhFBldZPg678Hl9BnBkxwy
        4Se80+YKmLdsD
X-Received: by 2002:ac8:7201:: with SMTP id a1mr13291512qtp.51.1576875710501;
        Fri, 20 Dec 2019 13:01:50 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwRoak70ZtDSXTrsL5BKFgZ8eU8b8vS29Tx8wICbfjkV/PqQRqigL5g2qPUrK/6ZAtRLM0GFw==
X-Received: by 2002:ac8:7201:: with SMTP id a1mr13291492qtp.51.1576875710346;
        Fri, 20 Dec 2019 13:01:50 -0800 (PST)
Received: from xz-x1.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 q25sm3243836qkq.88.2019.12.20.13.01.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 13:01:49 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, peterx@redhat.com,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>
Subject: [PATCH v2 01/17] KVM: Remove kvm_read_guest_atomic()
Date: Fri, 20 Dec 2019 16:01:31 -0500
Message-Id: <20191220210147.49617-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191220210147.49617-1-peterx@redhat.com>
References: <20191220210147.49617-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove kvm_read_guest_atomic() because it's not used anywhere.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  2 --
 virt/kvm/kvm_main.c      | 11 -----------
 2 files changed, 13 deletions(-)

```
#### [PATCH v2 01/17] KVM: Remove kvm_read_guest_atomic()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306301
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24B3E14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:03:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0382621655
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:03:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hov/puDt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727577AbfLTVDg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 16:03:36 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:50966 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727730AbfLTVDe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Dec 2019 16:03:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576875813;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=hov/puDtQHvNvWohlhaKQ3YJmaHFG7oHz1Chhy1SMre/gyIWSWLxg3wOPvbXPuTe3MZPDF
        hAbqcvanMcrcpMKAbS+QmRoQtqj3MKB822n0FnpjBPcACXsqpsyUrq4Wv9/3QV5eMaWtQ7
        BDz5C8pnlcYFgtaECJvGpGgp7aoPj44=
Received: from mail-qv1-f72.google.com (mail-qv1-f72.google.com
 [209.85.219.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-243-wb3gFqIjPBWklJFfeB_KtQ-1; Fri, 20 Dec 2019 16:03:31 -0500
X-MC-Unique: wb3gFqIjPBWklJFfeB_KtQ-1
Received: by mail-qv1-f72.google.com with SMTP id di5so1662368qvb.3
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 13:03:31 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=RqHdWa3C67jDbAxE5qBKvQ2HeotB80h4OiIy6rDdMxq9AtJKq3sdvyN8bUzcqd+UkB
         CniOKVSC4j49ejY+jBDADopXzStE7zsbC2hgMzKZZf/F3nVO/I/KNyeKHysfay1nY0KD
         evXTs7uWn9CsFoa4lWZu4jtCMlOzu7O/B1BX5uUjWgfROW6HcLzp7RIbbymh6+/xZ4As
         cPffHFiH+vLIoWmiDHH2hz32PPiV7iGLhl1ueLrjrUS1EjPn1nNQl5y7JzRPfll+jdr2
         rw+ceXQe0YGW3WCBaX7LJbuIfMFCo/ausJRL34JQWpK1+ty+v5abBtJJmD35WXwQrgN0
         pONw==
X-Gm-Message-State: APjAAAWu1sD7HxCbmqzWOqF9vjHjxEBUBZw0omUWU0bVMnUBSJ/ljKJw
        XZxMflC6NQM2lDZIgRSqItp66DnUUCdYW0Owd851NYlywtOKuHfFRSVi8CRoq9vMJesQtdPTFDn
        tXk1GXe4I4w5s
X-Received: by 2002:ac8:4456:: with SMTP id
 m22mr13436033qtn.362.1576875810875;
        Fri, 20 Dec 2019 13:03:30 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwjedy9vJO9QU3awwLVGvmg81TcgWXkz+6waubY5bhmdyM90H3Ldeop7O/CBvSPdtrUYJzuww==
X-Received: by 2002:ac8:4456:: with SMTP id
 m22mr13436025qtn.362.1576875810722;
        Fri, 20 Dec 2019 13:03:30 -0800 (PST)
Received: from xz-x1.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 a9sm3061018qtb.36.2019.12.20.13.03.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 13:03:29 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH v2 01/17] KVM: Remove kvm_read_guest_atomic()
Date: Fri, 20 Dec 2019 16:03:10 -0500
Message-Id: <20191220210326.49949-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191220210326.49949-1-peterx@redhat.com>
References: <20191220210326.49949-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove kvm_read_guest_atomic() because it's not used anywhere.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  2 --
 virt/kvm/kvm_main.c      | 11 -----------
 2 files changed, 13 deletions(-)

```
#### [PATCH v2 01/17] KVM: Remove kvm_read_guest_atomic()
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306337
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ED88B13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:17:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CCCD221655
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:17:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XKfypzCn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727688AbfLTVR3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 16:17:29 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:42081 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727504AbfLTVQl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Dec 2019 16:16:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576876600;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=XKfypzCnnuG8ym16HqYjIAMV/6Jx0su0I62m3jXSoXXerZSvjEZzMVNCXlmqg0eShinQFt
        ckNZZ+StSvBoPDLVM8ubNPXRudfz+8BkTCIpJ5VbRJRrdNCXdV2uahWkFXuNJPB1r+c7U0
        +9ukiSVntmtl6EQAhXGg+3NdcDFGK24=
Received: from mail-qk1-f200.google.com (mail-qk1-f200.google.com
 [209.85.222.200]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-49--7EbwAZjOGKS7wiqA20p3w-1; Fri, 20 Dec 2019 16:16:39 -0500
X-MC-Unique: -7EbwAZjOGKS7wiqA20p3w-1
Received: by mail-qk1-f200.google.com with SMTP id l7so6777028qke.8
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 13:16:39 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=5u+NdTdcxJqnd4CDcK36kvrGYVN4B69rZJAB5gjRDOQ=;
        b=KC46hHQI4txyPfmL7gz6B/uFdo5ogx2JRFrc0WFrGJKcrA958DOOpg9Vc7bV8e0/X1
         /QeNJMYcRGmfsuAP0frF/1ldTvwXQoRjNShFQPZbyHUv5nf+zW0VA+L0FnNHXuVdEu4w
         MeHuiK8eOB82w0tg09SUMOIyk6H8fxP+sHNOWZCPx1SacMZgBKBtpAPvsp3T6qo4kmck
         gz4xd7+KSqgxjbBJ4Jd2wieX+wKYO54B6uzpt1cwt4r3mj9qQjv0QOSwdyiVYU4pykA4
         LCMfIOUOxbYxvr5J91/iA9OIY16ja5el+HjLWV4BvYTYlKf1Auh9r7RFNIqJJrXFgcIR
         OKiA==
X-Gm-Message-State: APjAAAXtvcUh7xgjLGqiMz+nlJHNiBk9Qr2p7WI+2yb3O30dhaVO9IW9
        CDy+vEEcuxWFqdMGNGcnOEnwC5tGgbiW5lnZ4M8j9CbJchDIWqz/6yJpxKA2Y6+VxvnHKigTPOQ
        YQbdNMUkQBv2Y
X-Received: by 2002:ad4:478b:: with SMTP id
 z11mr14206440qvy.185.1576876598687;
        Fri, 20 Dec 2019 13:16:38 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxoKvokYa9wz/VYk7DXc6sLhq1nQIWkintnAX/rU5VixNiHjfptm5B8929S8w9MKyIcQEcPLA==
X-Received: by 2002:ad4:478b:: with SMTP id
 z11mr14206426qvy.185.1576876598497;
        Fri, 20 Dec 2019 13:16:38 -0800 (PST)
Received: from xz-x1.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 d25sm3385231qtq.11.2019.12.20.13.16.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 13:16:37 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Michael S . Tsirkin" <mst@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Jason Wang <jasowang@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>
Subject: [PATCH v2 01/17] KVM: Remove kvm_read_guest_atomic()
Date: Fri, 20 Dec 2019 16:16:18 -0500
Message-Id: <20191220211634.51231-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20191220211634.51231-1-peterx@redhat.com>
References: <20191220211634.51231-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove kvm_read_guest_atomic() because it's not used anywhere.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  2 --
 virt/kvm/kvm_main.c      | 11 -----------
 2 files changed, 13 deletions(-)

```
#### [RFC 1/2] KVM: X86: Add CR pin MSRs
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11304531
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6928B1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 00:13:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 50CEE2467F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 00:13:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727128AbfLTANb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Dec 2019 19:13:31 -0500
Received: from mga06.intel.com ([134.134.136.31]:64772 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726967AbfLTANb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Dec 2019 19:13:31 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 19 Dec 2019 16:13:30 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,333,1571727600";
   d="scan'208";a="241340281"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga004.fm.intel.com with ESMTP; 19 Dec 2019 16:13:29 -0800
From: John Andersen <john.s.andersen@intel.com>
To: kvm@vger.kernel.org
Cc: John Andersen <john.s.andersen@intel.com>
Subject: [RFC 1/2] KVM: X86: Add CR pin MSRs
Date: Thu, 19 Dec 2019 16:13:21 -0800
Message-Id: <20191220001322.22317-2-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191220001322.22317-1-john.s.andersen@intel.com>
References: <20191220001322.22317-1-john.s.andersen@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a CR pin feature bit to the KVM cpuid. Add read only MSRs to KVM
which guests use to identify which bits they may request be pinned. Add
CR pinned MSRs to KVM. Allow guests to request that KVM pin certain
bits within control register 0 or 4 via the CR pinned MSRs. Writes to
the MSRs fail if they include bits which aren't allowed. Host userspace
may clear or modify pinned bits at any time. Once pinned bits are set,
the guest may pin additional allowed bits, but not clear any. The guest
may never read pinned bits. If an attacker were to read the CR pinned
MSRs, they might decide to preform another attack which would not cause
a general protection fault.

In the event that the guest vcpu attempts to disable any of the pinned
bits, send that vcpu a general protection fault, and leave the register
unchanged. Entering SMM unconditionally clears various CR0/4 bits, some
of which may be pinned by the OS. To avoid trigerring shutdown on SMIs,
pinning isn't enforced when the vCPU is running in SMM.

Should userspace expose the CR pinning CPUID feature bit, it must zero
CR pinned MSRs on reboot. If it does not, it runs the risk of having the
guest enable pinning and subsequently cause general protection faults on
next boot due to early boot code setting control registers to values
which do not contain the pinned bits. Userspace is responsible for
migrating the contents of the CR* pinned MSRs. If userspace fails to
migrate the MSRs the protection will no longer be active.

Pinning of sensitive CR bits has already been implemented to protect
against exploits directly calling native_write_cr*(). The current
protection cannot stop ROP attacks which jump directly to a MOV CR
instruction.

https://web.archive.org/web/20171029060939/http://www.blackbunny.io/linux-kernel-x86-64-bypass-smep-kaslr-kptr_restric/

Guests running with paravirtualized CR pinning are now protected against
the use of ROP to disable CR bits. The same bits that are being pinned
natively may be pinned via the CR pinned MSRs. These bits are WP in CR0,
and SMEP, SMAP, and UMIP in CR4.

Other hypervisors such as HyperV have implemented similar protections
for Control Registers and MSRs; which security researchers have found
effective.

https://www.abatchy.com/2018/01/kernel-exploitation-4

Future patches could implement similar MSR and hypercall combinations
to protect bits in MSRs. The NXE bit of the EFER MSR is a prime
candidate.

Patches for QEMU are required to expose the CR pin cpuid feature bit. As
well as clear the MSRs on reboot and enable migration.

https://github.com/qemu/qemu/commit/e7a0ff8a8dcde1ef2b83a9d93129614f512752ae
https://github.com/qemu/qemu/commit/7e8c770c91616ae8d2d6b15bcc2865be594c8852

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 Documentation/virt/kvm/msr.txt       | 38 +++++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h      |  2 ++
 arch/x86/include/uapi/asm/kvm_para.h |  5 ++++
 arch/x86/kvm/cpuid.c                 |  3 +-
 arch/x86/kvm/x86.c                   | 45 ++++++++++++++++++++++++++++
 5 files changed, 92 insertions(+), 1 deletion(-)

```
#### [RESEND RFC 1/2] KVM: X86: Add CR pin MSRs
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11306247
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 259CC109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 19:27:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED7A4222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 19:27:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727558AbfLTT1k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 14:27:40 -0500
Received: from mga17.intel.com ([192.55.52.151]:28192 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727473AbfLTT1k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 14:27:40 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Dec 2019 11:27:39 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,336,1571727600";
   d="scan'208";a="222547140"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga001.fm.intel.com with ESMTP; 20 Dec 2019 11:27:38 -0800
From: John Andersen <john.s.andersen@intel.com>
To: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        pbonzini@redhat.com
Cc: hpa@zytor.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        John Andersen <john.s.andersen@intel.com>
Subject: [RESEND RFC 1/2] KVM: X86: Add CR pin MSRs
Date: Fri, 20 Dec 2019 11:27:00 -0800
Message-Id: <20191220192701.23415-2-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191220192701.23415-1-john.s.andersen@intel.com>
References: <20191220192701.23415-1-john.s.andersen@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a CR pin feature bit to the KVM cpuid. Add read only MSRs to KVM
which guests use to identify which bits they may request be pinned. Add
CR pinned MSRs to KVM. Allow guests to request that KVM pin certain
bits within control register 0 or 4 via the CR pinned MSRs. Writes to
the MSRs fail if they include bits which aren't allowed. Host userspace
may clear or modify pinned bits at any time. Once pinned bits are set,
the guest may pin additional allowed bits, but not clear any. The guest
may never read pinned bits. If an attacker were to read the CR pinned
MSRs, they might decide to preform another attack which would not cause
a general protection fault.

In the event that the guest vCPU attempts to disable any of the pinned
bits, send that vCPU a general protection fault, and leave the register
unchanged. Entering SMM unconditionally clears various CR0/4 bits, some
of which may be pinned by the OS. To avoid triggering shutdown on SMIs,
pinning isn't enforced when the vCPU is running in SMM.

Should userspace expose the CR pinning CPUID feature bit, it must zero
CR pinned MSRs on reboot. If it does not, it runs the risk of having the
guest enable pinning and subsequently cause general protection faults on
next boot due to early boot code setting control registers to values
which do not contain the pinned bits. Userspace is responsible for
migrating the contents of the CR* pinned MSRs. If userspace fails to
migrate the MSRs the protection will no longer be active.

Pinning of sensitive CR bits has already been implemented to protect
against exploits directly calling native_write_cr*(). The current
protection cannot stop ROP attacks which jump directly to a MOV CR
instruction.

https://web.archive.org/web/20171029060939/http://www.blackbunny.io/linux-kernel-x86-64-bypass-smep-kaslr-kptr_restric/

Guests running with paravirtualized CR pinning are now protected against
the use of ROP to disable CR bits. The same bits that are being pinned
natively may be pinned via the CR pinned MSRs. These bits are WP in CR0,
and SMEP, SMAP, and UMIP in CR4.

Other hypervisors such as HyperV have implemented similar protections
for Control Registers and MSRs; which security researchers have found
effective.

https://www.abatchy.com/2018/01/kernel-exploitation-4

Future patches could implement similar MSR and hypercall combinations
to protect bits in MSRs. The NXE bit of the EFER MSR is a prime
candidate.

Patches for QEMU are required to expose the CR pin cpuid feature bit. As
well as clear the MSRs on reboot and enable migration.

https://github.com/qemu/qemu/commit/e7a0ff8a8dcde1ef2b83a9d93129614f512752ae
https://github.com/qemu/qemu/commit/7e8c770c91616ae8d2d6b15bcc2865be594c8852

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 Documentation/virt/kvm/msr.txt       | 38 +++++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h      |  2 ++
 arch/x86/include/uapi/asm/kvm_para.h |  5 ++++
 arch/x86/kvm/cpuid.c                 |  3 +-
 arch/x86/kvm/x86.c                   | 45 ++++++++++++++++++++++++++++
 5 files changed, 92 insertions(+), 1 deletion(-)

```
