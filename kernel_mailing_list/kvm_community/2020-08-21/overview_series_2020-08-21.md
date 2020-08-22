#### [PATCH] KVM: LAPIC: Don't kick vCPU which is injecting already-expired timer
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11728679
Return-Path: <SRS0=QNYh=B7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A8A71575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 09:17:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EEAB208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 09:17:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="u5imW/ob"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727074AbgHUJRu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Aug 2020 05:17:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52338 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725855AbgHUJRt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 21 Aug 2020 05:17:49 -0400
Received: from mail-pj1-x1042.google.com (mail-pj1-x1042.google.com
 [IPv6:2607:f8b0:4864:20::1042])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BD962C061385;
        Fri, 21 Aug 2020 02:17:49 -0700 (PDT)
Received: by mail-pj1-x1042.google.com with SMTP id d4so559975pjx.5;
        Fri, 21 Aug 2020 02:17:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=FowiN7wGUIsFhFJkyzUhtvp+B7SgUmBl2oc4E8odKUg=;
        b=u5imW/obXnthlptyuM+UmZMrIJpnkZhelXsiU1c0RPMDUbj3oQWZdP0i9N4UfPSleC
         KfJ/OfpP0+MYveLl9IG5eAvuVZrZxxi0NB63ep5eZsz2hD99jBPZJQC0VkarKWVs7c+m
         2qzbfQOKImRQONRgimycy8is1Ho47cs+XGHJRcTSTa4hnzhi3dqhZ9IphiTAgGSZykl7
         36NmF4e8k7/DPRUQcxW4i/DonSqdJAtMDycWwa19T1Z8As5IMjLJkRXTbQ/JeOYi7YWk
         YsMPSgpTyFyYHsflZ8QzTReDRcTciU7WF1+e39v+mZe8aV5axhVeFOzivWEOGNdQawP6
         AAkg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=FowiN7wGUIsFhFJkyzUhtvp+B7SgUmBl2oc4E8odKUg=;
        b=FGNivJNRu8Ap6dDiffaLT0JzahEKWmo36JrHQtCoXRRBildcW9WZ/y0JS1Gwk0aiQ8
         anF//EJpJKPb8x+cKWq6XGLu36rXMszbEdnA+XdznfDKXLnZUxb2tYEmsjYQO6VWZdbN
         meg8k0AnT6gkAUIwd5wvufYIzFcB+ICc6G98ahB/tTnDAxH19FgF8vUjUxDBA7GvEBHq
         97pHpV4R/oylc56TC8sg//CPNUguymamRsAAisObl1hC9d/qiZa+x654zDY6lBR0NFLa
         pIUL6FfxfzUeAwdNX5qAjqfhQO+00eK1tmh1OE6w1ghnGLKI06DHwUeBfMTBisfp1b+Y
         wOIQ==
X-Gm-Message-State: AOAM53050MGsIvoNDsrOdewfdwha5CygnJJAHr14l9m/dMWktcQ6W6vE
        /t9n4T+3isHJFA3dqVnI962qF30Z/WU=
X-Google-Smtp-Source: 
 ABdhPJzNNdQKEjdNXXETsWvOfEIJS9o3AaeMqd6oRQlM6ML8PWimk/XtWQ755wUwRXMeFh9RI3JzRQ==
X-Received: by 2002:a17:90a:ee08:: with SMTP id
 e8mr1840282pjy.86.1598001468857;
        Fri, 21 Aug 2020 02:17:48 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 b26sm1961190pff.54.2020.08.21.02.17.46
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 21 Aug 2020 02:17:48 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Don't kick vCPU which is injecting
 already-expired timer
Date: Fri, 21 Aug 2020 17:17:34 +0800
Message-Id: <1598001454-11709-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The kick after setting KVM_REQ_PENDING_TIMER is used to handle the timer 
fires on a different pCPU which vCPU is running on, we don't need this 
kick when injecting already-expired timer, this kick is expensive since 
memory barrier, rcu, preemption disable/enable operations. This patch 
reduces the overhead by don't kick vCPU which is injecting already-expired 
timer.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 arch/x86/kvm/x86.c   | 5 +++--
 arch/x86/kvm/x86.h   | 2 +-
 3 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH v10 01/16] s390/vfio-ap: add version vfio_ap module
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11730503
Return-Path: <SRS0=QNYh=B7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94235618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 20:01:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E6F820791
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 20:01:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="m/hgqOb6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727003AbgHUT4g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Aug 2020 15:56:36 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:3948 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726306AbgHUT4c (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 21 Aug 2020 15:56:32 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07LJWxB5023963;
        Fri, 21 Aug 2020 15:56:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=1PGyV5xOIEUjK9z3Jg4QxXcPpDhZXcE3sZY/Qjg8gwg=;
 b=m/hgqOb6xYkIo2JBgQ4vwLXlYtOPuBTDm8FJSm5gXVV9YWphk4Tn+cBZcQhbwU+kSQYq
 dplXEUnQEnSiZCqEVhbLVXA96AUXd3g//V3V14reif3WsA958GtJPaXKa6VYFx4e2v6K
 hQubKbUzI7Ov5DmYwv2rhwKhc2jk7b1idk7Qj+DX4uIo6kUVPHRiIMr5+2rFdA6+PzIs
 Mv9P3WkjmgPXCQsYHCqzwtO38cBwiyEQCu/KrBrPRPYicvzeDNvp5vf+GlDre3xubmut
 i/iJISzCa0EVrpylb+/2j/fSKquUAQIuH6QlPf1CkcDJ+qsBS4KCE4vXy5cX2g9D7VOR 4Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 332dw6vavh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Aug 2020 15:56:29 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07LJYAfO027332;
        Fri, 21 Aug 2020 15:56:29 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 332dw6vava-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Aug 2020 15:56:29 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07LJsM76005387;
        Fri, 21 Aug 2020 19:56:28 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma03wdc.us.ibm.com with ESMTP id 3304ceprww-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Aug 2020 19:56:28 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07LJuPFW47841588
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 21 Aug 2020 19:56:25 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C41F778060;
        Fri, 21 Aug 2020 19:56:25 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 475C27805C;
        Fri, 21 Aug 2020 19:56:24 +0000 (GMT)
Received: from cpe-172-100-175-116.stny.res.rr.com.com (unknown [9.85.191.76])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri, 21 Aug 2020 19:56:24 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        imbrenda@linux.ibm.com, hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v10 01/16] s390/vfio-ap: add version vfio_ap module
Date: Fri, 21 Aug 2020 15:56:01 -0400
Message-Id: <20200821195616.13554-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200821195616.13554-1-akrowiak@linux.ibm.com>
References: <20200821195616.13554-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-21_09:2020-08-21,2020-08-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015
 priorityscore=1501 suspectscore=3 mlxlogscore=999 spamscore=0
 impostorscore=0 mlxscore=0 adultscore=0 lowpriorityscore=0 malwarescore=0
 phishscore=0 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008210183
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's set a version for the vfio_ap module so that automated regression
tests can determine whether dynamic configuration tests can be run or
not.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PATCH 1/2] runtime.bash: remove outdated comment
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11729345
Return-Path: <SRS0=QNYh=B7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DDBB1722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 12:38:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C1BC320724
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 12:38:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="mfCRIJC+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728582AbgHUMih (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Aug 2020 08:38:37 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:55268 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728550AbgHUMif (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 21 Aug 2020 08:38:35 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07LCW73e059935
        for <kvm@vger.kernel.org>; Fri, 21 Aug 2020 08:38:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=DspWVj5sAZNSyaOmyzuAOl6gPUo0dAvPlhjF9HxSnKQ=;
 b=mfCRIJC+A7eDlVFkfwst66hZbwaFjyUscCSnYy1giClMg/L4sCsapUGkg4XdFjMiznAs
 9Xl1Zu1HFybeLvMjqWxVx/bBzPaegU0BW4tcluYj3lb4m6RbfmMtJt9uXqgsdFP6gGZC
 wIBzl8agzQqGGbTEQ5LiAB/uf0F6l3F82Z5BfqJbMEepK6hrt7ikTXn+swHMKQGyuQAf
 PEwjfJT09VHsqGJquai6pBJAh+YL/uufn9nFMNZFexugFAZaQ1QMXAcWzO4dRh2f4QLB
 pt9DicvYVvjvcrAVYbWvFwq5H2z9XkgQrP0wDTdrfT17X+8S6b12S5W6hkK+W3j+Wrps mA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 331uj4e7yn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 21 Aug 2020 08:38:35 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07LCWcOu061373
        for <kvm@vger.kernel.org>; Fri, 21 Aug 2020 08:38:34 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 331uj4e7y2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Aug 2020 08:38:34 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07LCZS8f013979;
        Fri, 21 Aug 2020 12:38:32 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 3304um4b29-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Aug 2020 12:38:32 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07LCcUXQ27853176
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 21 Aug 2020 12:38:30 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3CF124C063;
        Fri, 21 Aug 2020 12:38:30 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D4AD24C05A;
        Fri, 21 Aug 2020 12:38:29 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.60.23])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 21 Aug 2020 12:38:29 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH 1/2] runtime.bash: remove outdated comment
Date: Fri, 21 Aug 2020 14:37:43 +0200
Message-Id: <20200821123744.33173-2-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200821123744.33173-1-mhartmay@linux.ibm.com>
References: <20200821123744.33173-1-mhartmay@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-21_06:2020-08-21,2020-08-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 lowpriorityscore=0 priorityscore=1501 malwarescore=0 clxscore=1015
 mlxlogscore=999 mlxscore=0 adultscore=0 spamscore=0 suspectscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008210112
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit 6e1d3752d7ca ("tap13: list testcases individually") the
comment is no longer valid. Therefore let's remove it.

Signed-off-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 scripts/runtime.bash | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH v2] x86/entry/64: Do not use RDPID in paranoid entry to accomodate KVM
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11729019
Return-Path: <SRS0=QNYh=B7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8731613B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 10:53:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7000520656
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 10:53:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="El0qSMCJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728046AbgHUKx1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Aug 2020 06:53:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:59636 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726975AbgHUKwi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 21 Aug 2020 06:52:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598007155;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=m+sWpLL8B15YiBoZkjZFY9ODFpvPLxIevI4EtwVXHWs=;
        b=El0qSMCJGzsYDAaoaZMJq8enBQysbCREZe9LIdwAow3Yyskwb2ZnpSP892PQcb0mX6fVEo
        LyTFs3+BCcjbt0S3ZMQ+OdfZ3k0rtQbBhyRVtTzWL+6IOTiiVkgGVwrvTTBok6dCAph6wm
        3Zq2sfuCJdM2XFoos1fCSwKPw12BdcI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-475-Arr460QEMU-dEeMrVD4xNw-1; Fri, 21 Aug 2020 06:52:33 -0400
X-MC-Unique: Arr460QEMU-dEeMrVD4xNw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3B9761885D89;
        Fri, 21 Aug 2020 10:52:31 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 397977C533;
        Fri, 21 Aug 2020 10:52:30 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: x86@kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Dave Hansen <dave.hansen@intel.com>,
        Chang Seok Bae <chang.seok.bae@intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sasha Levin <sashal@kernel.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Andy Lutomirski <luto@kernel.org>
Subject: [PATCH v2] x86/entry/64: Do not use RDPID in paranoid entry to
 accomodate KVM
Date: Fri, 21 Aug 2020 06:52:29 -0400
Message-Id: <20200821105229.18938-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Don't use RDPID in the paranoid entry flow, as it can consume a KVM
guest's MSR_TSC_AUX value if an NMI arrives during KVM's run loop.

In general, the kernel does not need TSC_AUX because it can just use
__this_cpu_read(cpu_number) to read the current processor id.  It can
also just block preemption and thread migration at its will, therefore
it has no need for the atomic rdtsc+vgetcpu provided by RDTSCP.  For this
reason, as a performance optimization, KVM loads the guest's TSC_AUX when
a CPU first enters its run loop.  On AMD's SVM, it doesn't restore the
host's value until the CPU exits the run loop; VMX is even more aggressive
and defers restoring the host's value until the CPU returns to userspace.

This optimization obviously relies on the kernel not consuming TSC_AUX,
which falls apart if an NMI arrives during the run loop and uses RDPID.
Removing it would be painful, as both SVM and VMX would need to context
switch the MSR on every VM-Enter (for a cost of 2x WRMSR), whereas using
LSL instead RDPID is a minor blip.

Both SAVE_AND_SET_GSBASE and GET_PERCPU_BASE are only used in paranoid entry,
therefore the patch can just remove the RDPID alternative.

Fixes: eaad981291ee3 ("x86/entry/64: Introduce the FIND_PERCPU_BASE macro")
Cc: Dave Hansen <dave.hansen@intel.com>
Cc: Chang Seok Bae <chang.seok.bae@intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Reported-by: Tom Lendacky <thomas.lendacky@amd.com>
Debugged-by: Tom Lendacky <thomas.lendacky@amd.com>
Suggested-by: Andy Lutomirski <luto@kernel.org>
Suggested-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/entry/calling.h | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/entry/64: Disallow RDPID in paranoid entry if KVM is enabled
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11727455
Return-Path: <SRS0=QNYh=B7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4608722
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 02:51:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C668520855
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Aug 2020 02:51:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727125AbgHUCvF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Aug 2020 22:51:05 -0400
Received: from mga11.intel.com ([192.55.52.93]:54690 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726975AbgHUCvE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Aug 2020 22:51:04 -0400
IronPort-SDR: 
 9Uc10Ob7R9FsPpKarIjdIuuxfXhNp6CcWtxjfaaXzEHFeHjjwvB8begXQv/CE/vbVBwQk1z/NP
 /kjA59XcBG9g==
X-IronPort-AV: E=McAfee;i="6000,8403,9719"; a="153051709"
X-IronPort-AV: E=Sophos;i="5.76,335,1592895600";
   d="scan'208";a="153051709"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Aug 2020 19:51:04 -0700
IronPort-SDR: 
 QaK6LNpXa1ocVtIBAx1I+9UT+UaUgCzWAQaqs+chC4eT3+5mLHuK46MVaPy6psrJhb4UpnanRb
 f21Mov7iOfLQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,335,1592895600";
   d="scan'208";a="278797794"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga007.fm.intel.com with ESMTP; 20 Aug 2020 19:51:03 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        Dave Hansen <dave.hansen@intel.com>,
        Chang Seok Bae <chang.seok.bae@intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sasha Levin <sashal@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] x86/entry/64: Disallow RDPID in paranoid entry if KVM is
 enabled
Date: Thu, 20 Aug 2020 19:50:50 -0700
Message-Id: <20200821025050.32573-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't use RDPID in the paranoid entry flow if KVM is enabled as doing so
can consume a KVM guest's MSR_TSC_AUX value if an NMI arrives in KVM's
run loop.

As a performance optimization, KVM loads the guest's TSC_AUX when a CPU
first enters its run loop, and on AMD's SVM doesn't restore the host's
value until the CPU exits the run loop.  VMX is even more aggressive and
defers restoring the host's value until the CPU returns to userspace.
This optimization obviously relies on the kernel not consuming TSC_AUX,
which falls apart if an NMI arrives in the run loop.

Removing KVM's optimizaton would be painful, as both SVM and VMX would
need to context switch the MSR on every VM-Enter (2x WRMSR + 1x RDMSR),
whereas using LSL instead RDPID is a minor blip.

Fixes: eaad981291ee3 ("x86/entry/64: Introduce the FIND_PERCPU_BASE macro")
Cc: Dave Hansen <dave.hansen@intel.com>
Cc: Chang Seok Bae <chang.seok.bae@intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Reported-by: Tom Lendacky <thomas.lendacky@amd.com>
Debugged-by: Tom Lendacky <thomas.lendacky@amd.com>
Suggested-by: Andy Lutomirski <luto@kernel.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Andy, I know you said "unconditionally", but it felt weird adding a
comment way down in GET_PERCPU_BASE without plumbing a param in to help
provide context.  But, paranoid_entry is the only user so adding a param
that is unconditional also felt weird.  That being said, I definitely
don't have a strong opinion one way or the other.

 arch/x86/entry/calling.h  | 10 +++++++---
 arch/x86/entry/entry_64.S |  7 ++++++-
 2 files changed, 13 insertions(+), 4 deletions(-)

```
