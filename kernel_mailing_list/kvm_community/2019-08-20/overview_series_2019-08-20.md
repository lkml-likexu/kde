#### [PATCH] KVM: PPC: Book3S HV: Define usage types for rmap array in guest memslot
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
X-Patchwork-Id: 11102937
Return-Path: <SRS0=1Zbj=WQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 917D2184E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 06:14:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 70CDD22CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 06:14:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="qCrE+7Gv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729208AbfHTGOC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 20 Aug 2019 02:14:02 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:45652 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728777AbfHTGOC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Aug 2019 02:14:02 -0400
Received: by mail-pg1-f193.google.com with SMTP id o13so2575954pgp.12;
        Mon, 19 Aug 2019 23:14:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=mhB3UhKa2apbmILstVtC2PuBpKp+KIhCo43t5hvhotg=;
        b=qCrE+7Gv+siL4APdA5TNSgsXbN8MDTadgi8WtA9BzoUSsgHRYilJOs8fJvNB9Ei0KT
         WitL6q4cCiwUx3de5plYEsnKBcS5MW6CHclZIaJNdrcZF+BrGB5j4gatGs+7ZNW4c3Cp
         yDT4+SJMw/ZcYoitRjlz3Q8HnrVP6UUrMKVb0CRWGW21ee+MXjrv4MVwp/gMrIt55BZW
         PFnxMVEIIYa+0vvtSmhJl49Tzvs8ITIGHwW4IE8KL6etlIQzQHnT8kH0l+EW4tLIAFOm
         IVyWcnQhRbYenh2Jox0+d45itZDeb8uiFOiUwpU/Y14rgIYXPfRt7N7LPo34cjJp/n1D
         WazQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=mhB3UhKa2apbmILstVtC2PuBpKp+KIhCo43t5hvhotg=;
        b=GoMn920+ZPsDoe+A6gi7ynvdYW969Qy/sOAwiTfPja9hUNTR+NACqEvMdeKMrq04eA
         FTgiKoKp5phPExFog1dQVMrCz9f1btuOv1Vct2WSjU9/gKRzYP/SVrO2DbqZsgOD9zOV
         5FljvpAgBavzfN84mVdZe5jK1WmjOQx+e4dL+In5Ronl4EsUKcVn6iYGw8FYAwJdopbW
         uOWsGl3WCnQ06b86A9OEJXF+KTFOc9Qg7JEcxEkUJ3ji/iAeZil1WkHUL5RKKxU63xwk
         LcdONblNa7Gp0f/i0YjpXONJDjIoEPcH8p64IjeKwp422fic+niQR3YSXplJ/HtBaOIn
         BUow==
X-Gm-Message-State: APjAAAVL18dkCSSA3HRJ7M4SyoVHRolJJQzwJsEQ96+0oB+JO3gMYXOH
        W58eAnLqe2C/WyhcDAcrNJIyBba1
X-Google-Smtp-Source: 
 APXvYqwnE1DCcQVDEpP87tHqgAuQNly7+QuZ9z1c9GXF4bR0TCPwj2dU6DdIERh2C5MBaeGgjrl+dQ==
X-Received: by 2002:aa7:93cc:: with SMTP id
 y12mr24691671pff.246.1566281641237;
        Mon, 19 Aug 2019 23:14:01 -0700 (PDT)
Received: from surajjs2.ozlabs.ibm.com ([122.99.82.10])
        by smtp.gmail.com with ESMTPSA id
 y13sm10276581pfb.48.2019.08.19.23.13.59
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Mon, 19 Aug 2019 23:14:00 -0700 (PDT)
From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
To: kvm-ppc@vger.kernel.org
Cc: paulus@ozlabs.org, kvm@vger.kernel.org,
        Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Subject: [PATCH] KVM: PPC: Book3S HV: Define usage types for rmap array in
 guest memslot
Date: Tue, 20 Aug 2019 16:13:49 +1000
Message-Id: <20190820061349.28995-1-sjitindarsingh@gmail.com>
X-Mailer: git-send-email 2.13.6
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The rmap array in the guest memslot is an array of size number of guest
pages, allocated at memslot creation time. Each rmap entry in this array
is used to store information about the guest page to which it
corresponds. For example for a hpt guest it is used to store a lock bit,
rc bits, a present bit and the index of a hpt entry in the guest hpt
which maps this page. For a radix guest which is running nested guests
it is used to store a pointer to a linked list of nested rmap entries
which store the nested guest physical address which maps this guest
address and for which there is a pte in the shadow page table.

As there are currently two uses for the rmap array, and the potential
for this to expand to more in the future, define a type field (being the
top 8 bits of the rmap entry) to be used to define the type of the rmap
entry which is currently present and define two values for this field
for the two current uses of the rmap array.

Since the nested case uses the rmap entry to store a pointer, define
this type as having the two high bits set as is expected for a pointer.
Define the hpt entry type as having bit 56 set (bit 7 IBM bit ordering).

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/include/asm/kvm_host.h | 22 ++++++++++++++++++----
 arch/powerpc/kvm/book3s_hv_rm_mmu.c |  2 +-
 2 files changed, 19 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] s390x: Support PSW restart boot
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11103559
Return-Path: <SRS0=1Zbj=WQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B64D1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 10:56:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E8B6B22CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 10:56:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729698AbfHTK4O (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 20 Aug 2019 06:56:14 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:29662 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728842AbfHTK4N (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Aug 2019 06:56:13 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7KArNmx119407
        for <kvm@vger.kernel.org>; Tue, 20 Aug 2019 06:56:11 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ugd9epbhp-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 20 Aug 2019 06:56:10 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 20 Aug 2019 11:56:09 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 20 Aug 2019 11:56:07 +0100
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7KAu6tu41812184
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 20 Aug 2019 10:56:06 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F015E4C046;
        Tue, 20 Aug 2019 10:56:05 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 45D314C040;
        Tue, 20 Aug 2019 10:56:05 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 20 Aug 2019 10:56:05 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 1/3] s390x: Support PSW restart boot
Date: Tue, 20 Aug 2019 12:55:48 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190820105550.4991-1-frankja@linux.ibm.com>
References: <20190820105550.4991-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082010-0012-0000-0000-00000340AA36
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082010-0013-0000-0000-0000217ACDD3
Message-Id: <20190820105550.4991-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-20_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908200114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a boot PSW to PSW restart new, so we can also boot via a PSW
restart.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/flat.lds | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)

```
#### [PATCH] selftests: kvm: fix state save/load on processors without XSAVE
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11104097
Return-Path: <SRS0=1Zbj=WQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 56A1B912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 15:36:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 358F322DBF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 15:36:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Q3aduewA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728618AbfHTPg3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 20 Aug 2019 11:36:29 -0400
Received: from mail-wm1-f68.google.com ([209.85.128.68]:54941 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726550AbfHTPg3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Aug 2019 11:36:29 -0400
Received: by mail-wm1-f68.google.com with SMTP id p74so3014713wme.4;
        Tue, 20 Aug 2019 08:36:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=VMBAs+uLqXnI9IwrpGIH72gdXUySmwFWOLfMIvLIRqw=;
        b=Q3aduewAEjklJX9l3q7fNNeDNihlNGNa03YzufK5MLFbraHno5JHCLedoFBxcN7J4/
         wSb0yv7swMC4A/vgYZAWYg5Pnw/fEnpeCP/+/WD1VEyEdXh1+Clr4b9b/UhCFn4TT5ZA
         R0IzU1r6sFN8XS7Eh/OO1tb3V/+0atKTIROGIaGm4fgsK2QmVAt6CIIUD+ldWcqLNHrn
         1wew4naeyVY3ccq83vMBganN2mfBr35YkMJ7RxoIlqwi/YrNB8VNvpeNGqfn9A6AV4li
         QSAi+uo+6qc9rHQ4AQOVLT20v6lwviblYJvxzlqdkWcww2IY/HAjy3ofxccwdUPQePKx
         DY+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=VMBAs+uLqXnI9IwrpGIH72gdXUySmwFWOLfMIvLIRqw=;
        b=Rz9VBrU6vQ1FyfkMoi8IsbPY5r6YhgmZLNN5GebHr0TQT1TrCOHwJ40hapLyFfGqU4
         DoJnjEKhWE9fQjVMcI3BYKNXaZezitiVuT1V7MO9wiZE2rclzeXaIGZP+n4OIxLnP7rl
         R4iUmwXEEe5Kh6sBPRqfxNNbbrg5CO/LnBjI8h3QfsKtoBQSPan3DCVjqWuXqENE7KUs
         KfHxcRqvNc6pkX6L5e8WZSgCycQVKwmQk72JIG1xN8dmhEWTuS9+U57V5zdx0vUgMCgL
         BpnY1a3TFSO13Cx6nDb9f1jdy0qtXwKlgpLdQFHdIafUgTqAGfpa5eSsMw2T6K/gz1Z1
         6mow==
X-Gm-Message-State: APjAAAX0/SQo8zRWDnBjZay6VYbVSOupDc/TPyOPFmxq/Hhhd75AVoJp
        9h5CBxdjpsKjgEao94Wi8EH31bgi9zg=
X-Google-Smtp-Source: 
 APXvYqzr+dnJ/vQhc/+wT4H+W8aeBVX2OjchyzrlmPtMEWY/2vhR0GSKORtdbgw8MfbzVEqN/xNVdA==
X-Received: by 2002:a7b:ce0b:: with SMTP id m11mr630379wmc.151.1566315386768;
        Tue, 20 Aug 2019 08:36:26 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 v124sm587415wmf.23.2019.08.20.08.36.25
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 20 Aug 2019 08:36:26 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] selftests: kvm: fix state save/load on processors without
 XSAVE
Date: Tue, 20 Aug 2019 17:36:24 +0200
Message-Id: <1566315384-34848-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

state_test and smm_test are failing on older processors that do not
have xcr0.  This is because on those processor KVM does provide
support for KVM_GET/SET_XSAVE (to avoid having to rely on the older
KVM_GET/SET_FPU) but not for KVM_GET/SET_XCRS.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 16 ++++++++++------
 1 file changed, 10 insertions(+), 6 deletions(-)

```
#### [PATCH] vhost: Remove unnecessary variable
##### From: Yunsheng Lin <linyunsheng@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yunsheng Lin <linyunsheng@huawei.com>
X-Patchwork-Id: 11103765
Return-Path: <SRS0=1Zbj=WQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D470D1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 12:38:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD3E622CF7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 20 Aug 2019 12:38:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729997AbfHTMih (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 20 Aug 2019 08:38:37 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:47074 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729383AbfHTMih (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Aug 2019 08:38:37 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id C1A3D5E0898FACBBEEA4;
        Tue, 20 Aug 2019 20:38:34 +0800 (CST)
Received: from localhost.localdomain (10.67.212.75) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.439.0; Tue, 20 Aug 2019 20:38:33 +0800
From: Yunsheng Lin <linyunsheng@huawei.com>
To: <mst@redhat.com>, <jasowang@redhat.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] vhost: Remove unnecessary variable
Date: Tue, 20 Aug 2019 20:36:32 +0800
Message-ID: <1566304592-233922-1-git-send-email-linyunsheng@huawei.com>
X-Mailer: git-send-email 2.8.1
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.67.212.75]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is unnecessary to use ret variable to return the error
code, just return the error code directly.

Signed-off-by: Yunsheng Lin <linyunsheng@huawei.com>
---
 drivers/vhost/vhost.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
