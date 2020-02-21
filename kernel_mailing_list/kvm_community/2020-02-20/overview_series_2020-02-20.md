#### [PATCH v3 01/20] scripts/git.orderfile: Display Cocci scripts before code modifications
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11394035
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0345B138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 13:06:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D6F77206ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 13:06:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="L5Tzuvlp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728111AbgBTNGE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 08:06:04 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:28392 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728096AbgBTNGD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 08:06:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582203962;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=4cFZx3MMvL5YTnq3TreW86G7x/AmeK47tUPtRXUhNQM=;
        b=L5TzuvlpkO9uNIY8gj81K7CcZbG7p3r9T2ifsbNM9N5Q72TzoQgYvkdOVGYm71TozyRz1m
        jXctls1kEgKYuCTwdDizHLWhkCLEWq4I3G+oU4hyEVCoCN+nWsnhVtVFVdHbD9HCrcX1ur
        A1SmwcvhR1HkKMByA1fq99HZSHvJGuM=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-263-TWaRNFNhM0eNq903i9Ik7A-1; Thu, 20 Feb 2020 08:05:59 -0500
X-MC-Unique: TWaRNFNhM0eNq903i9Ik7A-1
Received: by mail-wm1-f69.google.com with SMTP id g138so576732wmg.8
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 05:05:59 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=4cFZx3MMvL5YTnq3TreW86G7x/AmeK47tUPtRXUhNQM=;
        b=rZkIGQXUFNZnLO+UjKaqdaJrNj8w7QmkCB8aXZHts+hX3pD+RfszCJVqwraDUHK48f
         bLcqboEqebsyHESmPBK1RI96GMTtAg+QtvEzHHFKEB74YqS/QZ73h3CrBq9mBapp5E9F
         nHuBzhQg/LhufQ/n7e1f8IGm5adZXpr4GYrZg4XEDdm36Mpu6oevhBF6V5RAJci0EJ3K
         7Jr8SI7t9VQToFF2Q5V+rgR78WwFlbj9YFtp94BTsRyIPQxHw1kW1mdWu6fycnELzuGl
         QjDOGSw/oQt1CGgZeNiLvlpJtN3E8LxvVAl6JxuBW7IBMujrwrj3m1OS5b3Mkcy88uIw
         Y1OA==
X-Gm-Message-State: APjAAAXPIPtN5E2RiIVCF963ivlgLjB8qhJKgKrIFSlOcbro18UWmIOI
        skkAj5q32UEVbXzmo0TU/+JvIsyXPCtsNoZtHU58NKYs7QCeI4fWVHG2Puy8NA5foNwRnyQn1zV
        VdgRxZjQwdNwi
X-Received: by 2002:a05:600c:3d1:: with SMTP id
 z17mr4707588wmd.90.1582203958358;
        Thu, 20 Feb 2020 05:05:58 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqw5jcBfwQCBB55iS//J5oZ4nyff+vZw9LvNNuT8fCe2PE+cfM3f9N7yqnDLu5ddD34rthBOSw==
X-Received: by 2002:a05:600c:3d1:: with SMTP id
 z17mr4707497wmd.90.1582203957647;
        Thu, 20 Feb 2020 05:05:57 -0800 (PST)
Received: from localhost.localdomain (78.red-88-21-202.staticip.rima-tde.net.
 [88.21.202.78])
        by smtp.gmail.com with ESMTPSA id
 b67sm4594690wmc.38.2020.02.20.05.05.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 20 Feb 2020 05:05:57 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: Peter Maydell <peter.maydell@linaro.org>, qemu-devel@nongnu.org
Cc: "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 Anthony Perard <anthony.perard@citrix.com>, Fam Zheng <fam@euphon.net>,
	=?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>, =?utf-8?q?Philipp?=
	=?utf-8?q?e_Mathieu-Daud=C3=A9?= <philmd@redhat.com>, kvm@vger.kernel.org,
 Laurent Vivier <lvivier@redhat.com>, Thomas Huth <thuth@redhat.com>,
 Stefan Weil <sw@weilnetz.de>, Eric Auger <eric.auger@redhat.com>,
 Halil Pasic <pasic@linux.ibm.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, qemu-s390x@nongnu.org,
 Aleksandar Rikalo <aleksandar.rikalo@rt-rk.com>,
 David Gibson <david@gibson.dropbear.id.au>, Michael Walle <michael@walle.cc>,
 qemu-ppc@nongnu.org, Gerd Hoffmann <kraxel@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>, qemu-arm@nongnu.org,
 Alistair Francis <alistair@alistair23.me>, qemu-block@nongnu.org,
	=?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>,
 Jason Wang <jasowang@redhat.com>, xen-devel@lists.xenproject.org,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Dmitry Fleytman <dmitry.fleytman@gmail.com>,
 Matthew Rosato <mjrosato@linux.ibm.com>,
 Eduardo Habkost <ehabkost@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>,
 "Michael S. Tsirkin" <mst@redhat.com>, David Hildenbrand <david@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Stefano Stabellini <sstabellini@kernel.org>,
 Igor Mitsyanko <i.mitsyanko@gmail.com>, Paul Durrant <paul@xen.org>,
 Richard Henderson <rth@twiddle.net>, John Snow <jsnow@redhat.com>
Subject: [PATCH v3 01/20] scripts/git.orderfile: Display Cocci scripts before
 code modifications
Date: Thu, 20 Feb 2020 14:05:29 +0100
Message-Id: <20200220130548.29974-2-philmd@redhat.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200220130548.29974-1-philmd@redhat.com>
References: <20200220130548.29974-1-philmd@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we use a Coccinelle semantic script to do automatic
code modifications, it makes sense to look at the semantic
patch first.

Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Laurent Vivier <lvivier@redhat.com>
Reviewed-by: Eric Blake <eblake@redhat.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
---
 scripts/git.orderfile | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] KVM: apic: avoid calculating pending eoi from an uninitialized val
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11394325
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 742EA13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 15:36:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5DDC0207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 15:36:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728493AbgBTPgH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 10:36:07 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:52248 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728319AbgBTPgH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Feb 2020 10:36:07 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id E30F47E11A4E9CF39F13;
        Thu, 20 Feb 2020 23:35:53 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Thu, 20 Feb 2020
 23:35:12 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: apic: avoid calculating pending eoi from an
 uninitialized val
Date: Thu, 20 Feb 2020 23:36:46 +0800
Message-ID: <1582213006-488-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When get user eoi value failed, var val would be uninitialized and result
in calculating pending eoi from an uninitialized val. Initialize var val
to 0 to fix this case.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RFC 1/2] KVM: nVMX: clear PIN_BASED_POSTED_INTR from nested pinbased_ctls only when apicv is globally disabled
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11394703
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 324C014BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 17:22:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 08CC124673
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 17:22:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cRR+U8eu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728902AbgBTRWP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 12:22:15 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:37537 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728881AbgBTRWO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Feb 2020 12:22:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582219333;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=vXh0YutU9qoqkcD8FcXhGXyVijzyIFeaoys2bDNLpvY=;
        b=cRR+U8euGAo2P1c8sobZKKqgT2DKXJ1b7SkygR9qcWoXoungC82zcXV7Oa238BddquTYMW
        iMNKMpRhEQ2w3SfIiCxMip1YQnfUPUyz5byzPygAhuueDo5NGwLH+qt6pyu3lzTxkt8m1p
        yIwHgSnXym9y8ms3o6mHnY/6Xhq28Fo=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-328-cIn0mne9PEOjH-G2tJkhVg-1; Thu, 20 Feb 2020 12:22:10 -0500
X-MC-Unique: cIn0mne9PEOjH-G2tJkhVg-1
Received: by mail-wm1-f70.google.com with SMTP id y125so1188057wmg.1
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 09:22:10 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=vXh0YutU9qoqkcD8FcXhGXyVijzyIFeaoys2bDNLpvY=;
        b=bMtAPSIOn5wmWPr0e+w1ZBXO43D24/JYlQ+PFMn+62UeQ2nj6f1uMguHoMF3/9Rw1I
         Rybq5emQi9Ziu9MCgoHiUwT8sqUIODYiqbJ25AO28JQva9mU56ObDlzgGHWnrAw5Xten
         hm9YwQCnEhyPLDdaMLolOlKnr+s2EI+TZdIC/+Fyd6blpRPXtI9yRKqw7T690PTgzA2c
         0wj1RvVlYPXkS2aSrfhVhad3rPqrweCfjv0S5ozIQpMwB4+T8lv3b8epCeHVBCxJbtGR
         rb7eu6A0Ox6Cr87+EOsGglDAUjfy8/FW5yhEi5/kak4YcOOZkY6PJH3QnicmB0HGMC04
         ItNw==
X-Gm-Message-State: APjAAAXlAB4rjZdOaww3PhLYsjQMh8DUqX8meBdvaBJyp8O4A0CkfxCR
        RGW8yO09xL2oURfnvxMnVB6gj20CV1rm0D6o9xsyZb2Iwcn2Yo/ltDWlmfKDLN++fA786yPfSDb
        gBoZlWKPA3JEt
X-Received: by 2002:a1c:4e02:: with SMTP id g2mr5738543wmh.131.1582219329476;
        Thu, 20 Feb 2020 09:22:09 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwjPMNGd6W5n2fR2ezNTcPuzWvxZ6/kAyOLdN6JXfJNlYpHkQt54qct+8w0ddDZP86sZhBmQg==
X-Received: by 2002:a1c:4e02:: with SMTP id g2mr5738512wmh.131.1582219329112;
        Thu, 20 Feb 2020 09:22:09 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 a184sm5355891wmf.29.2020.02.20.09.22.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 20 Feb 2020 09:22:08 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH RFC 1/2] KVM: nVMX: clear PIN_BASED_POSTED_INTR from nested
 pinbased_ctls only when apicv is globally disabled
Date: Thu, 20 Feb 2020 18:22:04 +0100
Message-Id: <20200220172205.197767-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200220172205.197767-1-vkuznets@redhat.com>
References: <20200220172205.197767-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When apicv is disabled on a vCPU (e.g. by enabling KVM_CAP_HYPERV_SYNIC*),
nothing happens to VMX MSRs on the already existing vCPUs, however, all new
ones are created with PIN_BASED_POSTED_INTR filtered out. This is very
confusing and results in the following picture inside the guest:

$ rdmsr -ax 0x48d
ff00000016
7f00000016
7f00000016
7f00000016

This is observed with QEMU and 4-vCPU guest: QEMU creates vCPU0, does
KVM_CAP_HYPERV_SYNIC2 and then creates the remaining three.

L1 hypervisor may only check CPU0's controls to find out what features
are available and it will be very confused later. Switch to setting
PIN_BASED_POSTED_INTR control based on global 'enable_apicv' setting.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/capabilities.h |  1 +
 arch/x86/kvm/vmx/nested.c       |  5 ++---
 arch/x86/kvm/vmx/nested.h       |  3 +--
 arch/x86/kvm/vmx/vmx.c          | 10 ++++------
 4 files changed, 8 insertions(+), 11 deletions(-)

```
#### [PATCH v3 01/37] mm:gup/writeback: add callbacks for inaccessible pages
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11393785
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CEA76924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 10:40:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA37B24656
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 10:40:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728081AbgBTKkq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 05:40:46 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:3200 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727984AbgBTKkc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 05:40:32 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01KAZLhU057372;
        Thu, 20 Feb 2020 05:40:26 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y8uc13ytx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 20 Feb 2020 05:40:26 -0500
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01KAZQSq057826;
        Thu, 20 Feb 2020 05:40:25 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y8uc13ytf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 20 Feb 2020 05:40:25 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01KAGSwO027415;
        Thu, 20 Feb 2020 10:40:24 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma02wdc.us.ibm.com with ESMTP id 2y6896uvdp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 20 Feb 2020 10:40:24 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01KAeNDk16122860
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 20 Feb 2020 10:40:23 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DE206112066;
        Thu, 20 Feb 2020 10:40:22 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D7EED112063;
        Thu, 20 Feb 2020 10:40:22 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 20 Feb 2020 10:40:22 +0000 (GMT)
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
        Will Deacon <will@kernel.org>
Subject: [PATCH v3 01/37] mm:gup/writeback: add callbacks for inaccessible
 pages
Date: Thu, 20 Feb 2020 05:39:44 -0500
Message-Id: <20200220104020.5343-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200220104020.5343-1-borntraeger@de.ibm.com>
References: <20200220104020.5343-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-20_02:2020-02-19,2020-02-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 phishscore=0 impostorscore=0 mlxscore=0 mlxlogscore=822 priorityscore=1501
 lowpriorityscore=0 bulkscore=0 clxscore=1015 suspectscore=2 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002200078
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

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: Will Deacon <will@kernel.org>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 include/linux/gfp.h |  6 ++++++
 mm/gup.c            | 15 ++++++++++++---
 mm/page-writeback.c |  5 +++++
 3 files changed, 23 insertions(+), 3 deletions(-)

```
#### [PATCH 01/10] KVM: VMX: Use vpid_sync_context() directly when possible
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11394989
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68206109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 20:44:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 52BB424650
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 20:44:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729286AbgBTUot (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 15:44:49 -0500
Received: from mga12.intel.com ([192.55.52.136]:13654 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728618AbgBTUn6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Feb 2020 15:43:58 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Feb 2020 12:43:58 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,465,1574150400";
   d="scan'208";a="349237091"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 20 Feb 2020 12:43:58 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 01/10] KVM: VMX: Use vpid_sync_context() directly when
 possible
Date: Thu, 20 Feb 2020 12:43:47 -0800
Message-Id: <20200220204356.8837-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200220204356.8837-1-sean.j.christopherson@intel.com>
References: <20200220204356.8837-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use vpid_sync_context() directly for flows that run if and only if
enable_vpid=1, or more specifically, nested VMX flows that are gated by
vmx->nested.msrs.secondary_ctls_high.SECONDARY_EXEC_ENABLE_VPID being
set, which is allowed if and only if enable_vpid=1.  Because these flows
call __vmx_flush_tlb() with @invalidate_gpa=false, the if-statement that
decides between INVEPT and INVVPID will always go down the INVVPID path,
i.e. call vpid_sync_context() because
"enable_ept && (invalidate_gpa || !enable_vpid)" always evaluates false.

This helps pave the way toward removing @invalidate_gpa and @vpid from
__vmx_flush_tlb() and its callers.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH][resend] KVM: fix error handling in svm_cpu_init
##### From: Li RongQing <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11393513
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8669B138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 07:48:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 71170208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 07:48:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726821AbgBTHsq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 02:48:46 -0500
Received: from mx60.baidu.com ([61.135.168.60]:28371 "EHLO
        tc-sys-mailedm05.tc.baidu.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726501AbgBTHsq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 02:48:46 -0500
X-Greylist: delayed 540 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 20 Feb 2020 02:48:44 EST
Received: from localhost (cp01-cos-dev01.cp01.baidu.com [10.92.119.46])
        by tc-sys-mailedm05.tc.baidu.com (Postfix) with ESMTP id E37C61EBA001;
        Thu, 20 Feb 2020 15:39:32 +0800 (CST)
From: Li RongQing <lirongqing@baidu.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH][resend] KVM: fix error handling in svm_cpu_init
Date: Thu, 20 Feb 2020 15:39:32 +0800
Message-Id: <1582184372-15876-1-git-send-email-lirongqing@baidu.com>
X-Mailer: git-send-email 1.7.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

sd->save_area should be freed in error path

Fixes: 70cd94e60c733 ("KVM: SVM: VMRUN should use associated ASID when SEV is enabled")
Signed-off-by: Li RongQing <lirongqing@baidu.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [RFC PATCH] KVM: Add module for platform IRQ forwarding
##### From: Micah Morton <mortonm@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Micah Morton <mortonm@chromium.org>
X-Patchwork-Id: 11394869
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22CEC14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 18:47:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D97B824673
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 18:47:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=chromium.org header.i=@chromium.org
 header.b="QCnpxIcG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728701AbgBTSrl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 13:47:41 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:41119 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728315AbgBTSrl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Feb 2020 13:47:41 -0500
Received: by mail-pf1-f196.google.com with SMTP id j9so2341399pfa.8
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 10:47:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7aRCDbas/HcYtWGOs4W2DTHaQ7qF0Fyp7zUrR3sl6LM=;
        b=QCnpxIcGR+C9XBFqDXDDYmC4CqVwoknAF+jVuMqrjNffLNBkFGOUqOzPH847B7tQPd
         Pm1AlTqGenScgfOpZXd+TS2q9fu84Myz89ixnMV4WwrLO1+N2kPNK/DZAZA/llooUJYD
         poW42jXr2YTHPC0VEuIH21u3YMEBnjUZaF1og=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=7aRCDbas/HcYtWGOs4W2DTHaQ7qF0Fyp7zUrR3sl6LM=;
        b=EUip4OWJEFxgkkzuAarpApeZ6biDe7nPovq5fqQP3t59YQoaizlW53+qXWrDA+LA0R
         5AqXjcTiNOdURBjkTSGoB4Tka4S5Q7Dug+C934lNLQ70zKDswAbr8xtEa2qZ6mqf5voQ
         oNOP3K+Kh7qnMyXC5pv1FnkI1BpHq3YscqavJau2F7+FBp03+H3niDmxnsi1BTSSsV/K
         VGG8vTH20xZlB+fEt9ATiVzmBaegOQgpn5MuogYyQhOZBFtgsAKGbT8q3/diwyd6TYS0
         jbuH0kZuOTNBw5mkih8OG2o8TvUVJqGrRwuKZv3M3sjjv3YQi7n1yQI8VD6RFSewYB/r
         E5gQ==
X-Gm-Message-State: APjAAAVVj0+Kgou0+/hw5ZoFX8cVBP13eLRZBMBXgUuxdkSBg6wcOmYz
        XoyMZYuz61IrmsG79BkqYPaUwZ5HDYY=
X-Google-Smtp-Source: 
 APXvYqxiCpOD6+89YBYkcDSs4+YQRH2MXWEKmqofjD0aH6eYaAZIX2Jufv5loHkByP+1sm0deNcM1A==
X-Received: by 2002:aa7:9ec9:: with SMTP id r9mr33510418pfq.85.1582224459338;
        Thu, 20 Feb 2020 10:47:39 -0800 (PST)
Received: from localhost ([2620:15c:202:200:c921:befc:7379:cdab])
        by smtp.gmail.com with ESMTPSA id s7sm169503pjk.22.2020.02.20.10.47.38
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Thu, 20 Feb 2020 10:47:38 -0800 (PST)
From: Micah Morton <mortonm@chromium.org>
To: kvm@vger.kernel.org, vfio-users@redhat.com
Cc: Micah Morton <mortonm@chromium.org>
Subject: [RFC PATCH] KVM: Add module for platform IRQ forwarding
Date: Thu, 20 Feb 2020 10:47:36 -0800
Message-Id: <20200220184736.112830-1-mortonm@chromium.org>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, KVM/VFIO offers no way to forward interrupts into a guest VM
when those interrupts are generated by a platform device that sits
behind a PCI bus controller which is given to the VM. This module allows
for forwarding arbitrary interrupts on the host system into the guest,
supporting this platform-device-behind-PCI-controller scenario.

This code is mostly inspired/taken from the equivalent code in VFIO. I
don't necessarily expect this exact code or code that closely resembles
this to be merged -- just sharing this patch that I've written/tested to
show an example of the kind of functionality I'm looking to gain support
for in KVM. (At the very least some of the code duplication from VFIO
should probably be eliminated).

One obvious question would be why not just add this support to VFIO?
See https://www.redhat.com/archives/vfio-users/2019-December/msg00008.html
and the encompassing thread for a discussion as to why this probably
isn't the way to go.

Forwarding arbitrary IRQs to a guest VM does require the VMM to "tell"
the guest about the interrupt (e.g. through ACPI), since such info is
not discoverable by the guest like it is for PCI devices. So separate
logic is needed in the VMM to set this up -- this isn't something done
by the module shared here.

What do people think? Forwarding platform IRQs can have a big payoff for
getting platform devices to work in a guest, especially when the
platform devices sit behind a PCI bus controller that can be easily
passed through to the guest. On an Intel device I'm using for
development, this module allowed me to get multiple devices (keyboard,
touchscreen, touchpad) working in a VM guest on the device that wouldn't
have worked otherwise -- straight out of the box after passing through
the PCI bus controller with vfio-pci (plus constructing some AML for the
guest in the VMM).

NOTE: This code works for forwarding IRQs to a guest (with the VMM
calling the appropriate ioctls with the appropriate args), although it's
missing some code and testing related to shutdown/irq disable/reboot.
Works well enough to demonstrate the feasibility though.

Signed-off-by: Micah Morton <mortonm@chromium.org>
---
 include/linux/miscdevice.h          |   1 +
 include/linux/plat_irqfd.h          |  20 ++
 include/uapi/linux/platirqforward.h |  55 ++++++
 virt/lib/Kconfig                    |   3 +
 virt/lib/Makefile                   |   1 +
 virt/lib/plat_irqfd.c               | 146 ++++++++++++++
 virt/lib/platirqforward.c           | 289 ++++++++++++++++++++++++++++
 7 files changed, 515 insertions(+)
 create mode 100644 include/linux/plat_irqfd.h
 create mode 100644 include/uapi/linux/platirqforward.h
 create mode 100644 virt/lib/plat_irqfd.c
 create mode 100644 virt/lib/platirqforward.c

```
#### [kvm-unit-tests PATCH v5 01/10] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11393875
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6093A14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 12:00:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A7ED20722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 12:00:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727984AbgBTMAw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 07:00:52 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:24928 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727772AbgBTMAw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 07:00:52 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01KBrrmF097306
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 07:00:51 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y99pfr5kf-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 07:00:50 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Thu, 20 Feb 2020 12:00:48 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 20 Feb 2020 12:00:45 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01KC0i1p45089016
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 20 Feb 2020 12:00:44 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 85420AE064;
        Thu, 20 Feb 2020 12:00:44 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4BDDFAE05F;
        Thu, 20 Feb 2020 12:00:44 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.152.222.41])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 20 Feb 2020 12:00:44 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v5 01/10] s390x: saving regs for interrupts
Date: Thu, 20 Feb 2020 13:00:34 +0100
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1582200043-21760-1-git-send-email-pmorel@linux.ibm.com>
References: <1582200043-21760-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20022012-0012-0000-0000-000003889713
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022012-0013-0000-0000-000021C52DA1
Message-Id: <1582200043-21760-2-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-20_03:2020-02-19,2020-02-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 lowpriorityscore=0 mlxscore=0 phishscore=0 clxscore=1011 bulkscore=0
 impostorscore=0 malwarescore=0 adultscore=0 spamscore=0 mlxlogscore=567
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002200090
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers and the floating point registers on the stack.

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 s390x/cstart64.S | 23 +++++++++++++++++++++--
 1 file changed, 21 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: x86: enable dirty log gradually in small chunks
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jay Zhou <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11393279
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05B6013A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 04:28:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C6B3C20801
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 04:28:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727747AbgBTE2n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 23:28:43 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10656 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727370AbgBTE2n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Feb 2020 23:28:43 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 308414037D832686A4A8;
        Thu, 20 Feb 2020 12:28:39 +0800 (CST)
Received: from localhost (10.133.205.84) by DGGEMS411-HUB.china.huawei.com
 (10.3.19.211) with Microsoft SMTP Server id 14.3.439.0; Thu, 20 Feb 2020
 12:28:31 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <peterx@redhat.com>,
        <wangxinxin.wang@huawei.com>, <weidong.huang@huawei.com>,
        <jianjay.zhou@huawei.com>, <sean.j.christopherson@intel.com>,
        <liu.jinsong@huawei.com>
Subject: [PATCH v2] KVM: x86: enable dirty log gradually in small chunks
Date: Thu, 20 Feb 2020 12:28:28 +0800
Message-ID: <20200220042828.27464-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.133.205.84]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It could take kvm->mmu_lock for an extended period of time when
enabling dirty log for the first time. The main cost is to clear
all the D-bits of last level SPTEs. This situation can benefit from
manual dirty log protect as well, which can reduce the mmu_lock
time taken. The sequence is like this:

1. Initialize all the bits of the dirty bitmap to 1 when enabling
   dirty log for the first time
2. Only write protect the huge pages
3. KVM_GET_DIRTY_LOG returns the dirty bitmap info
4. KVM_CLEAR_DIRTY_LOG will clear D-bit for each of the leaf level
   SPTEs gradually in small chunks

Under the Intel(R) Xeon(R) Gold 6152 CPU @ 2.10GHz environment,
I did some tests with a 128G windows VM and counted the time taken
of memory_global_dirty_log_start, here is the numbers:

VM Size        Before    After optimization
128G           460ms     10ms

Signed-off-by: Jay Zhou <jianjay.zhou@huawei.com>
---
v2:
  * add new bit to KVM_ENABLE_CAP for KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 [Paolo]
  * support non-PML path [Peter]
  * delete the unnecessary ifdef and make the initialization of bitmap
    more clear [Sean]
  * document the new bits and tweak the testcase

 Documentation/virt/kvm/api.rst               | 23 +++++++++++++++++------
 arch/x86/kvm/mmu/mmu.c                       |  8 ++++++--
 arch/x86/kvm/vmx/vmx.c                       |  3 ++-
 include/linux/kvm_host.h                     |  7 ++++++-
 tools/testing/selftests/kvm/dirty_log_test.c |  3 ++-
 virt/kvm/kvm_main.c                          | 25 ++++++++++++++++++-------
 6 files changed, 51 insertions(+), 18 deletions(-)

```
#### [PATCH V3 1/5] vhost: factor out IOTLB
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11393213
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13F5917F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 03:57:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C562524672
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 03:57:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bBo0XqyB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728014AbgBTD5f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 22:57:35 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:23160 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727983AbgBTD5e (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Feb 2020 22:57:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582171053;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=InMMaPmBZEN0kp7GqlMpQKaNZlf+ck9CZeN5m+rsIH4=;
        b=bBo0XqyB17fIkeDNwuwjyjMie8aVGaHpsIt973tQ8THIpCSFZBoQEOGaI4LtpDRGy3if9q
        g/QhnFVWSeMSmAJjqwsgOeBCIYQL5BsYS44siBDUuEC/4NIDppDWXQ+gcjvHSUozlN/0UV
        4TunjUhDgCLj0H4OQ+aYTtT1oUptOB4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-2j-Inw8QMuKzWq6bE_2EPg-1; Wed, 19 Feb 2020 22:57:29 -0500
X-MC-Unique: 2j-Inw8QMuKzWq6bE_2EPg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ED33E477;
        Thu, 20 Feb 2020 03:57:26 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-159.pek2.redhat.com [10.72.12.159])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 373FD5C651;
        Thu, 20 Feb 2020 03:57:11 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jiri@mellanox.com,
        shahafs@mellanox.com, hanand@xilinx.com, mhabets@solarflare.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V3 1/5] vhost: factor out IOTLB
Date: Thu, 20 Feb 2020 11:56:46 +0800
Message-Id: <20200220035650.7986-2-jasowang@redhat.com>
In-Reply-To: <20200220035650.7986-1-jasowang@redhat.com>
References: <20200220035650.7986-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch factors out IOTLB into a dedicated module in order to be
reused by other modules like vringh. User may choose to enable the
automatic retiring by specifying VHOST_IOTLB_FLAG_RETIRE flag to fit
for the case of vhost device IOTLB implementation.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 MAINTAINERS                 |   1 +
 drivers/vhost/Kconfig       |   7 ++
 drivers/vhost/Makefile      |   2 +
 drivers/vhost/net.c         |   2 +-
 drivers/vhost/vhost.c       | 221 +++++++++++-------------------------
 drivers/vhost/vhost.h       |  36 ++----
 drivers/vhost/vhost_iotlb.c | 171 ++++++++++++++++++++++++++++
 include/linux/vhost_iotlb.h |  45 ++++++++
 8 files changed, 304 insertions(+), 181 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 include/linux/vhost_iotlb.h

```
#### [PATCH V4 1/5] vhost: factor out IOTLB
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11393403
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EFEF3930
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 06:12:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B637520801
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 06:12:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WMsTV//Z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726825AbgBTGM0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 01:12:26 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:49321 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725995AbgBTGM0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 01:12:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582179145;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ml9H1AmRrIhm2m0bwg8M889YMUbt04Z+O1VPWamuLiM=;
        b=WMsTV//ZNCUF3/M/2oHSpF0LUhXh7H9k2Nk+2DixdmkhIN2cJCmB+X8B+WuaTQ/21h6Yy9
        UGnWDp7CNXEcpVGDhToA8QEbh4D3fgSQJA3SGgIqP5pxu1mo6MCesxfkwdHpueH9g7BfI4
        wt1BjgXiALS/xp9fR0+9odxPvkmVH3k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-54-BFPKBvJrMI6mUXkyRS4x6g-1; Thu, 20 Feb 2020 01:12:23 -0500
X-MC-Unique: BFPKBvJrMI6mUXkyRS4x6g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B88CE18A5502;
        Thu, 20 Feb 2020 06:12:20 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-159.pek2.redhat.com [10.72.12.159])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4C0975D9E2;
        Thu, 20 Feb 2020 06:12:01 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jiri@mellanox.com,
        shahafs@mellanox.com, hanand@xilinx.com, mhabets@solarflare.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V4 1/5] vhost: factor out IOTLB
Date: Thu, 20 Feb 2020 14:11:37 +0800
Message-Id: <20200220061141.29390-2-jasowang@redhat.com>
In-Reply-To: <20200220061141.29390-1-jasowang@redhat.com>
References: <20200220061141.29390-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch factors out IOTLB into a dedicated module in order to be
reused by other modules like vringh. User may choose to enable the
automatic retiring by specifying VHOST_IOTLB_FLAG_RETIRE flag to fit
for the case of vhost device IOTLB implementation.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 MAINTAINERS                 |   1 +
 drivers/vhost/Kconfig       |   6 +
 drivers/vhost/Makefile      |   2 +
 drivers/vhost/net.c         |   2 +-
 drivers/vhost/vhost.c       | 221 +++++++++++-------------------------
 drivers/vhost/vhost.h       |  36 ++----
 drivers/vhost/vhost_iotlb.c | 171 ++++++++++++++++++++++++++++
 include/linux/vhost_iotlb.h |  45 ++++++++
 8 files changed, 303 insertions(+), 181 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 include/linux/vhost_iotlb.h

```
