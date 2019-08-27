#### [PATCH 1/2] KVM: VMX: Introduce exit reason for receiving INIT signal on guest-mode
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11114331
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B38D13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 10:25:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E2D032070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 10:25:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Mwlfe31i"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729909AbfHZKZj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 06:25:39 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:42530 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729713AbfHZKZj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 06:25:39 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QANtdL180807;
        Mon, 26 Aug 2019 10:25:22 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=0+6TQbTOfjgPGnk0mmhKb+lU/1ufITZyvfUTwWdfu+w=;
 b=Mwlfe31ioElwhL+JYh2DTU+wXtjGglPwIyNBiVXBKfjV8/OELX0kUs/dWL0sRrP6CV6X
 bsgADdq8ifCY/7S5PpR52PD/54jrPq49ZOkqiaj5k1yKUa9ptZl5okZLUJnu+zmQxQXL
 wwsbfDgMnkjhp97DjKo+C9FDsjhcVkijwFDWYJ1X9GfHMtE7QzNf8lqWyMMujhVeeYD8
 /ZbAgI9dDWRTJcI7Ml7jf+/G26mjjqgXhmFKYMN1hvgPygxuKiZe/m/JRGrV5NhIIHwM
 D5X75xr7gatyTnwFb4a4cWUno8QEChqlzmgTcONc6RLw+DVVGdfeA0G6nc+v/yLaiff6 XQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 2ujw70052u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 10:25:21 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QAO3Wv103452;
        Mon, 26 Aug 2019 10:25:21 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3020.oracle.com with ESMTP id 2ujw6hmjst-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 10:25:21 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x7QAPKEJ009879;
        Mon, 26 Aug 2019 10:25:20 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 26 Aug 2019 10:25:19 +0000
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Bhavesh Davda <bhavesh.davda@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Nikita Leshenko <nikita.leshchenko@oracle.com>
Subject: [PATCH 1/2] KVM: VMX: Introduce exit reason for receiving INIT signal
 on guest-mode
Date: Mon, 26 Aug 2019 13:24:48 +0300
Message-Id: <20190826102449.142687-2-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190826102449.142687-1-liran.alon@oracle.com>
References: <20190826102449.142687-1-liran.alon@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9360
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=604
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908260115
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9360
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=666 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908260116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to Intel SDM section 25.2 "Other Causes of VM Exits",
When INIT signal is received on a CPU that is running in VMX
non-root mode it should cause an exit with exit-reason of 3.
(See Intel SDM Appendix C "VMX BASIC EXIT REASONS")

This patch introduce the exit-reason definition.

Reviewed-by: Bhavesh Davda <bhavesh.davda@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Co-developed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Signed-off-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/uapi/asm/vmx.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/4] mdev: Introduce sha1 based mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11115527
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F9D514DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 20:42:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1DC0B2186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 20:42:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728327AbfHZUle (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 16:41:34 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:37883 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726562AbfHZUle (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 16:41:34 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 26 Aug 2019 23:41:30 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x7QKfPDP021168;
        Mon, 26 Aug 2019 23:41:28 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH 1/4] mdev: Introduce sha1 based mdev alias
Date: Mon, 26 Aug 2019 15:41:16 -0500
Message-Id: <20190826204119.54386-2-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20190826204119.54386-1-parav@mellanox.com>
References: <20190826204119.54386-1-parav@mellanox.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Whenever a parent requests to generate mdev alias, generate a mdev
alias.
It is an optional attribute that parent can request to generate
for each of its child mdev.
mdev alias is generated using sha1 from the mdev name.

Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c    | 98 +++++++++++++++++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h |  5 +-
 drivers/vfio/mdev/mdev_sysfs.c   | 13 +++--
 include/linux/mdev.h             |  4 ++
 4 files changed, 111 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S: Enable XIVE native capability only if OPAL has required functions
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11114243
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A19114DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 08:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1712D2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 08:15:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="aUeXEFmQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730487AbfHZIPD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 04:15:03 -0400
Received: from ozlabs.org ([203.11.71.1]:54345 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729726AbfHZIPC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 04:15:02 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 46H4Yb1nHqz9sBF; Mon, 26 Aug 2019 18:14:59 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1566807299; bh=4YBpWCa0qHZ3ULuoBl2RuWy1RhuSnNm3HEuyOK5cDew=;
        h=Date:From:To:Cc:Subject:From;
        b=aUeXEFmQEuUNsMdxMjs+42Tyu4AuTeSMYdo18sG0oRt37GyCIGUl2MOKsTWpNBQXj
         gUGtvIUodNo6Mu9nhv/3LqkYbwKVAMj1l9H0824UQGOAv0tEjIv6fIv6d48fHlglYt
         VcVu6/Bwpmfq5x93Ip4HDvXQvxkEqxLgGUMBPytr7hVHp//BehN2zC5akkfF1AyzHc
         Rb7VIgF1KpfPfVY9l0+lQeTUa9RUO0AW9BKbhRZGNQ80PLkZZJsKT7PTetqt0hlol2
         CJwSKpRh+U2YvhbzlZi3d5++HtXuZ0sbRdmVPTc7C+4NijCPXiChgKxfYpW0erOC14
         KOC1N/tiMipsQ==
Date: Mon, 26 Aug 2019 18:14:55 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org, linuxppc-dev@ozlabs.org
Cc: kvm-ppc@vger.kernel.org, David Gibson <david@gibson.dropbear.id.au>,
	=?iso-8859-1?q?C=E9dric?= Le Goater <clg@kaod.org>
Subject: [PATCH] KVM: PPC: Book3S: Enable XIVE native capability only if OPAL
 has required functions
Message-ID: <20190826081455.GA7402@blackberry>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are some POWER9 machines where the OPAL firmware does not support
the OPAL_XIVE_GET_QUEUE_STATE and OPAL_XIVE_SET_QUEUE_STATE calls.
The impact of this is that a guest using XIVE natively will not be able
to be migrated successfully.  On the source side, the get_attr operation
on the KVM native device for the KVM_DEV_XIVE_GRP_EQ_CONFIG attribute
will fail; on the destination side, the set_attr operation for the same
attribute will fail.

This adds tests for the existence of the OPAL get/set queue state
functions, and if they are not supported, the XIVE-native KVM device
is not created and the KVM_CAP_PPC_IRQ_XIVE capability returns false.
Userspace can then either provide a software emulation of XIVE, or
else tell the guest that it does not have a XIVE controller available
to it.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/include/asm/kvm_ppc.h    | 1 +
 arch/powerpc/include/asm/xive.h       | 1 +
 arch/powerpc/kvm/book3s.c             | 8 +++++---
 arch/powerpc/kvm/book3s_xive_native.c | 5 +++++
 arch/powerpc/kvm/powerpc.c            | 3 ++-
 arch/powerpc/sysdev/xive/native.c     | 7 +++++++
 6 files changed, 21 insertions(+), 4 deletions(-)

```
#### [PATCH 01/23] KVM: PPC: Book3S HV: Use __gfn_to_pfn_memslot in HPT page fault handler
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
X-Patchwork-Id: 11113963
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4EB114DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:21:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A86BF2190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:21:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="pv6uA8tC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729555AbfHZGVT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 02:21:19 -0400
Received: from mail-pg1-f195.google.com ([209.85.215.195]:39411 "EHLO
        mail-pg1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725446AbfHZGVT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 02:21:19 -0400
Received: by mail-pg1-f195.google.com with SMTP id u17so9935240pgi.6;
        Sun, 25 Aug 2019 23:21:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=G4/GIjjvxQI6MZGovIhdNXi5RGCGvdzZ9iU6E6ba0z4=;
        b=pv6uA8tCkUQu2/nzFDxIxT78ahycnFFOeTFVUFDVPpPWhrs2oCkKw3LXYse67U1uFY
         MaCXWUjxnNYV2+/r8CbKolvnWezc5lA4VIhSMeu0vpBsFwrlCT3lFNbZnJibpV+gTkj8
         Y7s1OFhCxLYomdFTW8pTweBWTWpxIADG3ucY70LtcAyLlAOiMzv5XVodQ8wCGrT9p+UF
         +ypfMFIFhk0fMhjQwj0+3gcLkqg26YMxJLaQgjrwjRHHQ5IveZbVoDd6XAJzSB4X94qa
         Y+FYe/pa26frBL1rKYWSaJVR+curfeylq8eHeHZ/w/UkFHK4EvI64OsKUs09/BONcxdb
         6L3w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=G4/GIjjvxQI6MZGovIhdNXi5RGCGvdzZ9iU6E6ba0z4=;
        b=qYXIJzczt4Qc2J/d1nnDbzyzhGEJzS/mV3s+mtIwSnp13IwlpGQBpNZ0FnOP/pEiH3
         wwBw7nrXsd/IU55OkGxzXn4Cor+R5EUeRO/elTj3bDiyplCWbsNwUTqi9l6Asq4QCvgr
         ruaPuaVCiq4V8SdVDhHKzLinesvLHmUjdRblfJx721RBdmGbgE6hDSgZj6lU/9qUqzuy
         a7ufnroC+skOYuRdxC4+iqyOqSS+O1Hm1QwiLHeYqL53fTZZ9m3pwaKwZpwfYeJdosAP
         Dg4N4nxwPJdK1hLj2jCKHNa0O2kc8xCYPOEerR3ur9TsfgT5ltvejewR2wVcaef9yd7c
         9VGA==
X-Gm-Message-State: APjAAAXr/nJ/fKtDqAR1hmm3tEbCVomLjlHgGjfrA2LUMzjGHmyLdJf4
        SoLknuf8OGfUR+rOH+r5Fn/aszyxFTQ=
X-Google-Smtp-Source: 
 APXvYqybaO9sjrfaugxybOpcCXMBQkduatZKnmL2LTTR4B2fuAcxwH0ch7R3VSJ0zUvoUw9+3eZweQ==
X-Received: by 2002:a63:e14d:: with SMTP id
 h13mr14903966pgk.431.1566800478353;
        Sun, 25 Aug 2019 23:21:18 -0700 (PDT)
Received: from surajjs2.ozlabs.ibm.com.ozlabs.ibm.com ([122.99.82.10])
        by smtp.gmail.com with ESMTPSA id
 f7sm10030353pfd.43.2019.08.25.23.21.16
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Sun, 25 Aug 2019 23:21:17 -0700 (PDT)
From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
To: kvm-ppc@vger.kernel.org
Cc: paulus@ozlabs.org, kvm@vger.kernel.org
Subject: [PATCH 01/23] KVM: PPC: Book3S HV: Use __gfn_to_pfn_memslot in HPT
 page fault handler
Date: Mon, 26 Aug 2019 16:20:47 +1000
Message-Id: <20190826062109.7573-2-sjitindarsingh@gmail.com>
X-Mailer: git-send-email 2.13.6
In-Reply-To: <20190826062109.7573-1-sjitindarsingh@gmail.com>
References: <20190826062109.7573-1-sjitindarsingh@gmail.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Paul Mackerras <paulus@ozlabs.org>

This makes the same changes in the page fault handler for HPT guests
that commits 31c8b0d0694a ("KVM: PPC: Book3S HV: Use __gfn_to_pfn_memslot()
in page fault handler", 2018-03-01), 71d29f43b633 ("KVM: PPC: Book3S HV:
Don't use compound_order to determine host mapping size", 2018-09-11)
and 6579804c4317 ("KVM: PPC: Book3S HV: Avoid crash from THP collapse
during radix page fault", 2018-10-04) made for the page fault handler
for radix guests.

In summary, where we used to call get_user_pages_fast() and then do
special handling for VM_PFNMAP vmas, we now call __get_user_pages_fast()
and then __gfn_to_pfn_memslot() if that fails, followed by reading the
Linux PTE to get the host PFN, host page size and mapping attributes.

This also brings in the change from SetPageDirty() to set_page_dirty_lock()
which was done for the radix page fault handler in commit c3856aeb2940
("KVM: PPC: Book3S HV: Fix handling of large pages in radix page fault
handler", 2018-02-23).

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c | 118 +++++++++++++++++-------------------
 1 file changed, 57 insertions(+), 61 deletions(-)

```
#### [PATCH] KVM: selftests: Detect max PA width from cpuid
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11114241
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 203751395
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 07:57:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 072492087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 07:57:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730266AbfHZH5l (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 03:57:41 -0400
Received: from mx1.redhat.com ([209.132.183.28]:41418 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730061AbfHZH5l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 03:57:41 -0400
Received: from mail-pf1-f199.google.com (mail-pf1-f199.google.com
 [209.85.210.199])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E6BB181F0E
        for <kvm@vger.kernel.org>; Mon, 26 Aug 2019 07:57:40 +0000 (UTC)
Received: by mail-pf1-f199.google.com with SMTP id 191so5584800pfz.8
        for <kvm@vger.kernel.org>; Mon, 26 Aug 2019 00:57:40 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=nx/uKVsNPrj4sLskCBDR38LskLWX/kbZNssKjw3uHhE=;
        b=lLgAhINwLFKpGAFK3YtNF6PLdunYE4SB9T7G023iS6y7b17tj247Y4QjMD4wApDCKl
         e4T+XWVe8i1THdxfNWg5RTb+FMeM+AzXUeMdQbeb3x1jgwuHeA7Aqo04Q08f0QBojOze
         rNtBAC7gh7+EVbVpiJ70l7/BLqv8w0wtae75YIrXQdoZyLe8LFdcqAZegJ07K/R8g0r9
         VEElSX9eb3nWhVI9v55LF0ReMdzhZyLFrnp1pWFCyo4CMvqP0oNAKqMJFMvp4rP1G/F1
         l3V5IdU5hmSmf68dtOZaGlGd83JqQvno5CPzPidH4FbDksAk7tluSnir/f7uaWOQy61G
         ZYnQ==
X-Gm-Message-State: APjAAAVud4y0fHSlhxOFXyu1QdLI9pfftLPELf1mesgtg74+LceWSl35
        9j6XLOUJTeeZfwuD1RrpbCoipaLn7mgRILqjNcxuCh9ZrjFaTdysqCL4aXPr58Z7TOrTDlQ/eoU
        4HTk3sMTV5Zld
X-Received: by 2002:a63:2807:: with SMTP id o7mr15459232pgo.131.1566806260339;
        Mon, 26 Aug 2019 00:57:40 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqziiG4ZLc+6KzG9IuAf9INJzIEZAmrquQXKtVmCmpvt5i2FFNbVKwAktGcQe/Gl3lvc7Tl0FA==
X-Received: by 2002:a63:2807:: with SMTP id o7mr15459215pgo.131.1566806259994;
        Mon, 26 Aug 2019 00:57:39 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 r137sm12038058pfc.145.2019.08.26.00.57.36
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 26 Aug 2019 00:57:39 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
 Andrew Jones <drjones@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>
Subject: [PATCH] KVM: selftests: Detect max PA width from cpuid
Date: Mon, 26 Aug 2019 15:57:28 +0800
Message-Id: <20190826075728.21646-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The dirty_log_test is failing on some old machines like Xeon E3-1220
with tripple faults when writting to the tracked memory region:

  Test iterations: 32, interval: 10 (ms)
  Testing guest mode: PA-bits:52, VA-bits:48, 4K pages
  guest physical test memory offset: 0x7fbffef000
  ==== Test Assertion Failure ====
  dirty_log_test.c:138: false
  pid=6137 tid=6139 - Success
     1  0x0000000000401ca1: vcpu_worker at dirty_log_test.c:138
     2  0x00007f3dd9e392dd: ?? ??:0
     3  0x00007f3dd9b6a132: ?? ??:0
  Invalid guest sync status: exit_reason=SHUTDOWN

It's because previously we moved the testing memory region from a
static place (1G) to the top of the system's physical address space,
meanwhile we stick to 39 bits PA for all the x86_64 machines.  That's
not true for machines like Xeon E3-1220 where it only supports 36.

Let's unbreak this test by dynamically detect PA width from CPUID
0x80000008.  Meanwhile, even allow kvm_get_supported_cpuid_index() to
fail.  I don't know whether that could be useful because I think
0x80000008 should be there for all x86_64 hosts, but I also think it's
not really helpful to assert in the kvm_get_supported_cpuid_index().

Fixes: b442324b581556e
CC: Paolo Bonzini <pbonzini@redhat.com>
CC: Andrew Jones <drjones@redhat.com>
CC: Radim Krčmář <rkrcmar@redhat.com>
CC: Thomas Huth <thuth@redhat.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c  | 22 +++++++++++++------
 .../selftests/kvm/lib/x86_64/processor.c      |  3 ---
 2 files changed, 15 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: VMX: Set VMENTER_L1D_FLUSH_NOT_REQUIRED if !X86_BUG_L1TF
##### From: Waiman Long <longman@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Waiman Long <longman@redhat.com>
X-Patchwork-Id: 11115415
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 04E1B1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 19:30:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E07C22342D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 19:30:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732863AbfHZTan (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 15:30:43 -0400
Received: from mx1.redhat.com ([209.132.183.28]:57594 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729201AbfHZTan (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 15:30:43 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 2C22B8D5B99;
        Mon, 26 Aug 2019 19:30:43 +0000 (UTC)
Received: from llong.com (dhcp-17-160.bos.redhat.com [10.18.17.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 45EE0600C8;
        Mon, 26 Aug 2019 19:30:39 +0000 (UTC)
From: Waiman Long <longman@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Waiman Long <longman@redhat.com>
Subject: [PATCH] KVM: VMX: Set VMENTER_L1D_FLUSH_NOT_REQUIRED if !X86_BUG_L1TF
Date: Mon, 26 Aug 2019 15:30:23 -0400
Message-Id: <20190826193023.23293-1-longman@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.69]);
 Mon, 26 Aug 2019 19:30:43 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The l1tf_vmx_mitigation is only set to VMENTER_L1D_FLUSH_NOT_REQUIRED
when the ARCH_CAPABILITIES MSR indicates that L1D flush is not required.
However, if the CPU is not affected by L1TF, l1tf_vmx_mitigation will
still be set to VMENTER_L1D_FLUSH_AUTO. This is certainly not the best
option for a !X86_BUG_L1TF CPU.

So force l1tf_vmx_mitigation to VMENTER_L1D_FLUSH_NOT_REQUIRED to make it
more explicit in case users are checking the vmentry_l1d_flush parameter.

Signed-off-by: Waiman Long <longman@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### 
##### 

```c
```
#### [PATCH] KVM: x86: Only print persistent reasons for kvm disabled once
##### From: Tony Luck <tony.luck@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Luck <tony.luck@intel.com>
X-Patchwork-Id: 11115255
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8A60112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 18:23:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE1332186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 18:23:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733203AbfHZSXW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 14:23:22 -0400
Received: from mga05.intel.com ([192.55.52.43]:48759 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729274AbfHZSXW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 14:23:22 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Aug 2019 11:23:22 -0700
X-IronPort-AV: E=Sophos;i="5.64,433,1559545200";
   d="scan'208";a="174287956"
Received: from agluck-desk2.sc.intel.com ([10.3.52.68])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Aug 2019 11:23:21 -0700
From: Tony Luck <tony.luck@intel.com>
To: kvm@vger.kernel.org
Cc: Tony Luck <tony.luck@intel.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: x86: Only print persistent reasons for kvm disabled once
Date: Mon, 26 Aug 2019 11:23:20 -0700
Message-Id: <20190826182320.9089-1-tony.luck@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When I boot my server I'm treated to a console log with:

[   40.520510] kvm: disabled by bios
[   40.551234] kvm: disabled by bios
[   40.607987] kvm: disabled by bios
[   40.659701] kvm: disabled by bios
[   40.691224] kvm: disabled by bios
[   40.718786] kvm: disabled by bios
[   40.750122] kvm: disabled by bios
[   40.797170] kvm: disabled by bios
[   40.828408] kvm: disabled by bios

 ... many, many more lines, one for every logical CPU

Since it isn't likely that BIOS is going to suddenly enable
KVM between bringing up one CPU and the next, we might as
well just print this once.

Same for a few other unchanging reasons that might keep
kvm from being initialized.

Signed-off-by: Tony Luck <tony.luck@intel.com>
---
 arch/x86/kvm/x86.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Return to userspace with internal error on unexpected exit reason
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11114329
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 10CCD13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 10:17:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E1BF421883
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 10:17:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Mv2J7SCF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730853AbfHZKRc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 06:17:32 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:41536 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730379AbfHZKRb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 06:17:31 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QAEdQQ140930;
        Mon, 26 Aug 2019 10:17:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=5TqsifU5bVW0lTygAbeTjhINiSyDVg+Ft396Wv4qiY4=;
 b=Mv2J7SCFNVUk7pQ1bGZzzejbGMErFD7vUdRB47uthleYnXiTcK0dVoNxBimwbOWQl7X8
 xnYbEtb5Bs7ibBDU3GLjiqW0i5NT3k/iXSaUoVWbqQzXBskxcbVbi7vXQ0GgzN6RiXjl
 KLWBsh0nQpOh7nULq9Q+H7k9vHz/EsqRZs9e6NU16VfVN/yam6l00v/wqACGco3vy+dR
 hsSR8p01auv2FMal64MI9VbixNSj5q5vlzpP9+L70SZumU0DJTTfGdKVC1AHw9eUJivm
 GVGQTefLQywpbsE2YdH8AI0nSi1fkAd/zwyHDrAchmJNBf+kjwrOVvNevTAh7wsbxrsa 7w==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2ujw7182er-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 10:17:08 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QADnBf079920;
        Mon, 26 Aug 2019 10:17:08 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2ujw6hmb0k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 10:17:07 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7QAH6kj028121;
        Mon, 26 Aug 2019 10:17:06 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 26 Aug 2019 03:17:06 -0700
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Mihai Carabas <mihai.carabas@oracle.com>,
        Nikita Leshenko <nikita.leshchenko@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] KVM: x86: Return to userspace with internal error on
 unexpected exit reason
Date: Mon, 26 Aug 2019 13:16:43 +0300
Message-Id: <20190826101643.133750-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9360
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908260113
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9360
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908260114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Receiving an unexpected exit reason from hardware should be considered
as a severe bug in KVM. Therefore, instead of just injecting #UD to
guest and ignore it, exit to userspace on internal error so that
it could handle it properly (probably by terminating guest).

In addition, prefer to use vcpu_unimpl() instead of WARN_ONCE()
as handling unexpected exit reason should be a rare unexpected
event (that was expected to never happen) and we prefer to print
a message on it every time it occurs to guest.

Furthermore, dump VMCS/VMCB to dmesg to assist diagnosing such cases.

Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c       | 11 ++++++++---
 arch/x86/kvm/vmx/vmx.c   |  9 +++++++--
 include/uapi/linux/kvm.h |  2 ++
 3 files changed, 17 insertions(+), 5 deletions(-)

```
#### [PATCH kernel v2 1/4] powerpc/powernv/ioda: Split out TCE invalidation from TCE updates
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11113949
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E996B174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:17:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D19942190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 06:17:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729518AbfHZGRU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 02:17:20 -0400
Received: from ozlabs.ru ([107.173.13.209]:55936 "EHLO ozlabs.ru"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725385AbfHZGRT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 02:17:19 -0400
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id 9A820AE801D4;
        Mon, 26 Aug 2019 02:16:56 -0400 (EDT)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Alex Williamson <alex.williamson@redhat.com>,
        Michael Ellerman <mpe@ellerman.id.au>,
        Paul Mackerras <paulus@ozlabs.org>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel v2 1/4] powerpc/powernv/ioda: Split out TCE
 invalidation from TCE updates
Date: Mon, 26 Aug 2019 16:17:02 +1000
Message-Id: <20190826061705.92048-2-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190826061705.92048-1-aik@ozlabs.ru>
References: <20190826061705.92048-1-aik@ozlabs.ru>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At the moment updates in a TCE table are made by iommu_table_ops::exchange
which update one TCE and invalidates an entry in the PHB/NPU TCE cache
via set of registers called "TCE Kill" (hence the naming).
Writing a TCE is a simple xchg() but invalidating the TCE cache is
a relatively expensive OPAL call. Mapping a 100GB guest with PCI+NPU
passed through devices takes about 20s.

Thankfully we can do better. Since such big mappings happen at the boot
time and when memory is plugged/onlined (i.e. not often), these requests
come in 512 pages so we call call OPAL 512 times less which brings 20s
from the above to less than 10s. Also, since TCE caches can be flushed
entirely, calling OPAL for 512 TCEs helps skiboot [1] to decide whether
to flush the entire cache or not.

This implements 2 new iommu_table_ops callbacks:
- xchg_no_kill() to update a single TCE with no TCE invalidation;
- tce_kill() to invalidate multiple TCEs.
This uses the same xchg_no_kill() callback for IODA1/2.

This implements 2 new wrappers on top of the new callbacks similar to
the existing iommu_tce_xchg().

This does not use the new callbacks yet, the next patches will;
so this should not cause any behavioral change.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 arch/powerpc/include/asm/iommu.h          | 17 ++++++++++++++
 arch/powerpc/kernel/iommu.c               | 27 +++++++++++++++++++++++
 arch/powerpc/platforms/powernv/pci-ioda.c | 12 ++++++++++
 3 files changed, 56 insertions(+)

```
#### [kvm-unit-tests PATCH v3 1/5] s390x: Support PSW restart boot
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11115053
Return-Path: <SRS0=XRLU=WW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E14C184E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 16:35:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EAA5821852
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 26 Aug 2019 16:35:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732458AbfHZQfU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 12:35:20 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:33732 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728459AbfHZQfU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Aug 2019 12:35:20 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7QGOc7h077164
        for <kvm@vger.kernel.org>; Mon, 26 Aug 2019 12:35:19 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2umgym5a6s-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 26 Aug 2019 12:35:19 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 26 Aug 2019 17:35:17 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 26 Aug 2019 17:35:15 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7QGZErU42795100
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Aug 2019 16:35:14 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BAF9D11C04A;
        Mon, 26 Aug 2019 16:35:14 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A08E911C050;
        Mon, 26 Aug 2019 16:35:13 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.27.33])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 26 Aug 2019 16:35:13 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/5] s390x: Support PSW restart boot
Date: Mon, 26 Aug 2019 18:34:58 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190826163502.1298-1-frankja@linux.ibm.com>
References: <20190826163502.1298-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082616-0008-0000-0000-0000030D893D
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082616-0009-0000-0000-00004A2BC289
Message-Id: <20190826163502.1298-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-26_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908260162
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a boot PSW to PSW restart new, so we can also boot via a PSW
restart.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/flat.lds | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)

```
