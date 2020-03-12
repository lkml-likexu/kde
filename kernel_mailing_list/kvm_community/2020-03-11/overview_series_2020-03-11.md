#### [kvm-unit-tests PATCH v6 01/13] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11431799
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76165921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:51:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5336E222D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:51:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="BR52yY1k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729675AbgCKNvi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 09:51:38 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:37027 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729473AbgCKNvf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 09:51:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583934694;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=g1Y7SAIkQ6YKL70iv+PevVOHVnPkk+5bW/+E3fVVoME=;
        b=BR52yY1kALI/uZjf5+X2Itj1sm/vKwRESLjcHczeipmXdT4oFuvRxX2Z3Qttoo0GEgRoiv
        NWnrlMfZkbdmvCfNYRbJVLsWrBKxuGQNPYn1yvxN2NkM4UtIJF4WJ96PGjVEV5EJkb4J0r
        0eCH5Y9025iFsK52bOHYbji0a/QKp+A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-294-WVKaapncPDq1YirsLZ4soA-1; Wed, 11 Mar 2020 09:51:33 -0400
X-MC-Unique: WVKaapncPDq1YirsLZ4soA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 75D6C800D4E;
        Wed, 11 Mar 2020 13:51:31 +0000 (UTC)
Received: from laptop.redhat.com (unknown [10.36.118.12])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B323E9296C;
        Wed, 11 Mar 2020 13:51:27 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v6 01/13] libcflat: Add other size defines
Date: Wed, 11 Mar 2020 14:51:05 +0100
Message-Id: <20200311135117.9366-2-eric.auger@redhat.com>
In-Reply-To: <20200311135117.9366-1-eric.auger@redhat.com>
References: <20200311135117.9366-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce additional SZ_256, SZ_8K, SZ_16K macros that will
be used by ITS tests.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/libcflat.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/2] selftests: KVM: s390: fixup fprintf format error in reset.c
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11431707
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D318C138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:11:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBC1524655
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 13:11:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729515AbgCKNLs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 09:11:48 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14074 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729442AbgCKNLs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 09:11:48 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02BD4Nbn160683
        for <kvm@vger.kernel.org>; Wed, 11 Mar 2020 09:11:47 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ypyph9qbr-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Mar 2020 09:11:45 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Wed, 11 Mar 2020 13:11:00 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Mar 2020 13:10:58 -0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02BD9w1i48431552
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Mar 2020 13:09:58 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B8E9CA405D;
        Wed, 11 Mar 2020 13:10:57 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A7409A4059;
        Wed, 11 Mar 2020 13:10:57 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 11 Mar 2020 13:10:57 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 6AE6AE024B; Wed, 11 Mar 2020 14:10:57 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Subject: [PATCH 1/2] selftests: KVM: s390: fixup fprintf format error in
 reset.c
Date: Wed, 11 Mar 2020 14:10:55 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200311131056.140016-1-borntraeger@de.ibm.com>
References: <20200311131056.140016-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20031113-0012-0000-0000-0000038F669F
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20031113-0013-0000-0000-000021CC354D
Message-Id: <20200311131056.140016-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-11_05:2020-03-11,2020-03-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 clxscore=1015
 adultscore=0 suspectscore=0 bulkscore=0 phishscore=0 impostorscore=0
 priorityscore=1501 lowpriorityscore=0 mlxlogscore=999 mlxscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003110083
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

value is u64 and not string.

Reported-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 tools/testing/selftests/kvm/s390x/resets.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH -next 015/491] KERNEL VIRTUAL MACHINE FOR MIPS (KVM/mips): Use fallthrough;
##### From: Joe Perches <joe@perches.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joe Perches <joe@perches.com>
X-Patchwork-Id: 11430669
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2CDA0921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 05:07:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 15CF222464
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 05:07:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728226AbgCKFHR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 01:07:17 -0400
Received: from smtprelay0162.hostedemail.com ([216.40.44.162]:51800 "EHLO
        smtprelay.hostedemail.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728130AbgCKFHO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 01:07:14 -0400
Received: from filter.hostedemail.com (clb03-v110.bra.tucows.net
 [216.40.38.60])
        by smtprelay01.hostedemail.com (Postfix) with ESMTP id 4B629101684F2;
        Wed, 11 Mar 2020 05:07:13 +0000 (UTC)
X-Session-Marker: 6A6F6540706572636865732E636F6D
X-Spam-Summary: 
 50,0,0,,d41d8cd98f00b204,joe@perches.com,,RULES_HIT:41:355:379:541:800:960:967:973:982:988:989:1260:1311:1314:1345:1359:1437:1515:1534:1541:1711:1730:1747:1777:1792:2393:2525:2560:2563:2682:2685:2859:2902:2933:2937:2939:2942:2945:2947:2951:2954:3022:3138:3139:3140:3141:3142:3352:3865:3866:3867:3868:3870:3934:3936:3938:3941:3944:3947:3950:3953:3956:3959:4321:5007:6261:9025:9036:10004:11026:11658:11914:12043:12296:12297:12438:12555:12679:12895:12986:13069:13255:13311:13357:13894:14181:14384:14394:14721:21080:21433:21627:21811:21939:30054,0,RBL:none,CacheIP:none,Bayesian:0.5,0.5,0.5,Netcheck:none,DomainCache:0,MSF:not
 bulk,SPF:,MSBL:0,DNSBL:none,Custom_rules:0:0:0,LFtime:1,LUA_SUMMARY:none
X-HE-Tag: queen12_21d50d9d4a639
X-Filterd-Recvd-Size: 2278
Received: from joe-laptop.perches.com (unknown [47.151.143.254])
        (Authenticated sender: joe@perches.com)
        by omf16.hostedemail.com (Postfix) with ESMTPA;
        Wed, 11 Mar 2020 05:07:12 +0000 (UTC)
From: Joe Perches <joe@perches.com>
To: linux-kernel@vger.kernel.org
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH -next 015/491] KERNEL VIRTUAL MACHINE FOR MIPS (KVM/mips): Use
 fallthrough;
Date: Tue, 10 Mar 2020 21:51:29 -0700
Message-Id: 
 <5a1ee76be0f502af626f50313456730d75fe424b.1583896348.git.joe@perches.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <cover.1583896344.git.joe@perches.com>
References: <cover.1583896344.git.joe@perches.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Convert the various uses of fallthrough comments to fallthrough;

Done via script
Link: https://lore.kernel.org/lkml/b56602fcf79f849e733e7b521bb0e17895d390fa.1582230379.git.joe.com/

Signed-off-by: Joe Perches <joe@perches.com>
Acked-by: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
---
 arch/mips/kvm/emulate.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: s390: mark sie block as 512 byte aligned
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11431045
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 199B692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 08:33:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0237E20848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 08:33:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728571AbgCKIdO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 04:33:14 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28158 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728562AbgCKIdN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 04:33:13 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02B8RGvZ161249
        for <kvm@vger.kernel.org>; Wed, 11 Mar 2020 04:33:13 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ypv8b8xyu-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 11 Mar 2020 04:33:12 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Wed, 11 Mar 2020 08:33:09 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 11 Mar 2020 08:33:06 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02B8X5sM51511348
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 11 Mar 2020 08:33:05 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 755B2AE055;
        Wed, 11 Mar 2020 08:33:05 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 64043AE04D;
        Wed, 11 Mar 2020 08:33:05 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 11 Mar 2020 08:33:05 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id E4DFCE0251; Wed, 11 Mar 2020 09:33:04 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH] KVM: s390: mark sie block as 512 byte aligned
Date: Wed, 11 Mar 2020 09:33:04 +0100
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20031108-4275-0000-0000-000003AA84B3
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20031108-4276-0000-0000-000038BF9FFF
Message-Id: <20200311083304.3725276-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-11_02:2020-03-10,2020-03-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 mlxscore=0
 lowpriorityscore=0 clxscore=1015 mlxlogscore=668 malwarescore=0
 bulkscore=0 impostorscore=0 phishscore=0 priorityscore=1501 adultscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003110055
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The sie block must be aligned to 512 bytes. Mark it as such.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [Patch v1] KVM: x86: Initializing all kvm_lapic_irq fields
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11432497
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8F657921
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 18:34:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19A80206E9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 18:34:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YCnKRxLd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730788AbgCKSev (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 14:34:51 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:36124 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730641AbgCKSev (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 14:34:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583951690;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=ck66yOynV6oFFHDYrIkPfdq+bgw9rigHmyCYwCoQaaQ=;
        b=YCnKRxLd5UwZNa/x/5YENQoSuWGGqRqJUD5HpZtYKiZSRzVcw/TP03RTS63iZYK60gaTBF
        6feKpn87pSCZ/NmfXncNyLxpDt8+hUKK/CG4DbW7VtX4QVMjb4Ypj0rEUMy20oytF6b3ic
        dyrgCESgD466cpiZAsRwYqwYSObKxnY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-426-Yf2UNswrNKGu9r_EIxvw3w-1; Wed, 11 Mar 2020 14:34:48 -0400
X-MC-Unique: Yf2UNswrNKGu9r_EIxvw3w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 092A8107ACCC;
        Wed, 11 Mar 2020 18:34:47 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BB6B884779;
        Wed, 11 Mar 2020 18:34:45 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        mtosatti@redhat.com, vkuznets@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, pbonzini@redhat.com
Subject: [Patch v1] KVM: x86: Initializing all kvm_lapic_irq fields
Date: Wed, 11 Mar 2020 14:34:45 -0400
Message-Id: <1583951685-202743-1-git-send-email-nitesh@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously all fields of structure kvm_lapic_irq were not initialized
before it was passed to kvm_bitmap_or_dest_vcpus(). Which will cause
an issue when any of those fields are used for processing a request.
This patch initializes all the fields of kvm_lapic_irq based on the
values which are passed through the ioapic redirect_entry object.

Fixes: 7ee30bc132c6("KVM: x86: deliver KVM IOAPIC scan request to target vCPUs")
Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 arch/x86/kvm/ioapic.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/7] vfio: Include optional device match in vfio_device_ops callbacks
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11432867
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9ED02139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 21:58:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 931C520749
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 21:58:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="On0tNK9s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729328AbgCKV6q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 17:58:46 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:39171 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729726AbgCKV6p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Mar 2020 17:58:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583963924;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/UO6irQAkGyQ/Cqy5oQ7oIcu+pBDHAQ9auYgdZN2lko=;
        b=On0tNK9szZtUsWucECCX3m6GZPoSjb51MsmzxhV0Ful/M3+CJCed99gX8bbtjfm97t8jU5
        ag8uqUUFTHyMGWtNosrO2aH3HFep/1y6lzPeeOQYf/8cN57zbkuTTyBbOM0ZXqvXnAiPJN
        THrqmXRT4eepZNWpMXWcobffZHL9Aqw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-305-ywR8Vb8LMEGvUWxOGU69gg-1; Wed, 11 Mar 2020 17:58:40 -0400
X-MC-Unique: ywR8Vb8LMEGvUWxOGU69gg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8AF501088388;
        Wed, 11 Mar 2020 21:58:38 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DBC1E92972;
        Wed, 11 Mar 2020 21:58:34 +0000 (UTC)
Subject: [PATCH v3 1/7] vfio: Include optional device match in
 vfio_device_ops callbacks
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com, kevin.tian@intel.com
Date: Wed, 11 Mar 2020 15:58:34 -0600
Message-ID: <158396391448.5601.14344561558422706517.stgit@gimli.home>
In-Reply-To: <158396044753.5601.14804870681174789709.stgit@gimli.home>
References: <158396044753.5601.14804870681174789709.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allow bus drivers to provide their own callback to match a device to
the user provided string.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c  |   20 ++++++++++++++++----
 include/linux/vfio.h |    4 ++++
 2 files changed, 20 insertions(+), 4 deletions(-)

```
#### [PATCH v2 01/10] virtio-mem: Paravirtualized memory hotplug
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11432301
Return-Path: <SRS0=PMbP=44=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 938C614B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 17:15:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 07BC82074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 11 Mar 2020 17:15:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Ksqbb5xa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730457AbgCKRP1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 11 Mar 2020 13:15:27 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:26903 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730236AbgCKRP1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Mar 2020 13:15:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583946925;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=W3qMvu3y9HuygQEhMiYh58F8vYLUNiXtBkf6fkPcIJM=;
        b=Ksqbb5xaFLSZltQikisDoaFSoq7y+jsf8BjnfTtZ7wif+hG/FysLYif6LdJthhlfnHwnOA
        DFh4+idRv3SuKHBBvY249W6xTLS9XWRcUosgcdUOHO3Bb+GJqL6AQN2Qnq0OoXPR7IdvvH
        oPa+O6MPqG6H6RZLh0repgeTm+71U4Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-425-zZtSZq3IOt2uGisqnPVWfQ-1; Wed, 11 Mar 2020 13:15:21 -0400
X-MC-Unique: zZtSZq3IOt2uGisqnPVWfQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 913861005513;
        Wed, 11 Mar 2020 17:15:19 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-116-132.ams2.redhat.com [10.36.116.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0F16091D9B;
        Wed, 11 Mar 2020 17:14:55 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Oscar Salvador <osalvador@suse.de>,
        Igor Mammedov <imammedo@redhat.com>,
        Dave Young <dyoung@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Len Brown <lenb@kernel.org>, linux-acpi@vger.kernel.org
Subject: [PATCH v2 01/10] virtio-mem: Paravirtualized memory hotplug
Date: Wed, 11 Mar 2020 18:14:13 +0100
Message-Id: <20200311171422.10484-2-david@redhat.com>
In-Reply-To: <20200311171422.10484-1-david@redhat.com>
References: <20200311171422.10484-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Each virtio-mem device owns exactly one memory region. It is responsible
for adding/removing memory from that memory region on request.

When the device driver starts up, the requested amount of memory is
queried and then plugged to Linux. On request, further memory can be
plugged or unplugged. This patch only implements the plugging part.

On x86-64, memory can currently be plugged in 4MB ("subblock") granularity.
When required, a new memory block will be added (e.g., usually 128MB on
x86-64) in order to plug more subblocks. Only x86-64 was tested for now.

The online_page callback is used to keep unplugged subblocks offline
when onlining memory - similar to the Hyper-V balloon driver. Unplugged
pages are marked PG_offline, to tell dump tools (e.g., makedumpfile) to
skip them.

User space is usually responsible for onlining the added memory. The
memory hotplug notifier is used to synchronize virtio-mem activity
against memory onlining/offlining.

Each virtio-mem device can belong to a NUMA node, which allows us to
easily add/remove small chunks of memory to/from a specific NUMA node by
using multiple virtio-mem devices. Something that works even when the
guest has no idea about the NUMA topology.

One way to view virtio-mem is as a "resizable DIMM" or a DIMM with many
"sub-DIMMS".

This patch directly introduces the basic infrastructure to implement memory
unplug. Especially the memory block states and subblock bitmaps will be
heavily used there.

Notes:
- In case memory is to be onlined by user space, we limit the amount of
  offline memory blocks, to not run out of memory. This is esp. an
  issue if memory is added faster than it is getting onlined.
- Suspend/Hibernate is not supported due to the way virtio-mem devices
  behave. Limited support might be possible in the future.
- Reloading the device driver is not supported.

Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: Oscar Salvador <osalvador@suse.de>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: Dave Young <dyoung@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Pavel Tatashin <pasha.tatashin@soleen.com>
Cc: Stefan Hajnoczi <stefanha@redhat.com>
Cc: Vlastimil Babka <vbabka@suse.cz>
Cc: "Rafael J. Wysocki" <rjw@rjwysocki.net>
Cc: Len Brown <lenb@kernel.org>
Cc: linux-acpi@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 drivers/virtio/Kconfig          |   17 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1526 +++++++++++++++++++++++++++++++
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  200 ++++
 5 files changed, 1745 insertions(+)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h

```
