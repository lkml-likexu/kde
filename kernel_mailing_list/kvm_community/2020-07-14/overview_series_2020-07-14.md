#### [kvm-unit-tests PATCH v1 1/2] x86/cstart: Fix compilation issue in 32 bit mode
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11662315
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 592CB618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 11:09:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 487E922205
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 11:09:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726431AbgGNLJ2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 07:09:28 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:2432 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726041AbgGNLJ2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Jul 2020 07:09:28 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06EB2LPI158994;
        Tue, 14 Jul 2020 07:09:27 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3279k454tv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 07:09:27 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06EB2TKJ161223;
        Tue, 14 Jul 2020 07:09:26 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3279k454sr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 07:09:26 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06EB4ZCH008919;
        Tue, 14 Jul 2020 11:09:23 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03ams.nl.ibm.com with ESMTP id 327527u8p6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 11:09:23 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06EB9L1549545344
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 14 Jul 2020 11:09:21 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6A3B4A405C;
        Tue, 14 Jul 2020 11:09:21 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D1DB1A405B;
        Tue, 14 Jul 2020 11:09:20 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.7.230])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 14 Jul 2020 11:09:20 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com,
        drjones@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [kvm-unit-tests PATCH v1 1/2] x86/cstart: Fix compilation issue in 32
 bit mode
Date: Tue, 14 Jul 2020 13:09:18 +0200
Message-Id: <20200714110919.50724-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200714110919.50724-1-imbrenda@linux.ibm.com>
References: <20200714110919.50724-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-14_02:2020-07-14,2020-07-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 spamscore=0 malwarescore=0 phishscore=0 adultscore=0 mlxscore=0
 bulkscore=0 mlxlogscore=999 priorityscore=1501 impostorscore=0
 suspectscore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2007140081
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a typo in x86/cstart.S so that 32bit code can be compiled again on x86.

Fixes: d86ef58519645 ("cstart: do not assume CR4 starts as zero")
Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 x86/cstart.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/2] x86/cstart: Fix compilation issue in 32 bit mode
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11662841
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3BD5713B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 13:00:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E0EF22475
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 13:00:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728336AbgGNNAl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 09:00:41 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15454 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728294AbgGNNAl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Jul 2020 09:00:41 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06ECWiKO041884;
        Tue, 14 Jul 2020 09:00:38 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3298wuggb9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 09:00:38 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06ECfNJe085279;
        Tue, 14 Jul 2020 09:00:38 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3298wugga8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 09:00:38 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06ED0a0l016810;
        Tue, 14 Jul 2020 13:00:36 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 327527ubut-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 13:00:36 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06ED0XOv48234968
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 14 Jul 2020 13:00:33 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3597DAE089;
        Tue, 14 Jul 2020 13:00:32 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AA698AE076;
        Tue, 14 Jul 2020 13:00:31 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.7.230])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 14 Jul 2020 13:00:31 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com,
        drjones@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [kvm-unit-tests PATCH v2 1/2] x86/cstart: Fix compilation issue in 32
 bit mode
Date: Tue, 14 Jul 2020 15:00:29 +0200
Message-Id: <20200714130030.56037-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200714130030.56037-1-imbrenda@linux.ibm.com>
References: <20200714130030.56037-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-14_03:2020-07-14,2020-07-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 priorityscore=1501 lowpriorityscore=0 suspectscore=0 adultscore=0
 impostorscore=0 spamscore=0 phishscore=0 malwarescore=0 mlxscore=0
 mlxlogscore=999 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2007140095
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a typo in x86/cstart.S so that 32bit code can be compiled again on x86.

Fixes: d86ef58519645 ("cstart: do not assume CR4 starts as zero")
Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 x86/cstart.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/4] iommu: Check IOMMU_DEV_FEAT_AUX feature in aux api's
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11661459
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B69E13B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 06:01:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C79121D93
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 06:01:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726775AbgGNGBy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 02:01:54 -0400
Received: from mga03.intel.com ([134.134.136.65]:3745 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725876AbgGNGBw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jul 2020 02:01:52 -0400
IronPort-SDR: 
 IPjYTnMrSg3MjV5k2RAVAN+sn64h8zcgYR1ODEkZDL9eZCpUCt1HxU3pYvSb4RUPt3Dh3ZP5hm
 FNIqdg3auIKA==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="148812770"
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="148812770"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 23:01:52 -0700
IronPort-SDR: 
 DRuNNznlShmbBg/hXeyZXOHyQnvBnJVGJ9EUL1tNG54hFH5bs+YqLyY98X7Se6oqPAhLF2n9Vr
 xJMj4wloh6dQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="324450171"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by FMSMGA003.fm.intel.com with ESMTP; 13 Jul 2020 23:01:49 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v3 1/4] iommu: Check IOMMU_DEV_FEAT_AUX feature in aux api's
Date: Tue, 14 Jul 2020 13:57:00 +0800
Message-Id: <20200714055703.5510-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200714055703.5510-1-baolu.lu@linux.intel.com>
References: <20200714055703.5510-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The iommu aux-domain api's work only when IOMMU_DEV_FEAT_AUX is enabled
for the device. Add this check to avoid misuse.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c | 16 +++++++++-------
 1 file changed, 9 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: SVM: Fix sev_pin_memory() error handling
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11662997
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0811E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 14:27:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E3F7422518
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 14:27:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="HtinuOMy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728370AbgGNO1T (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 10:27:19 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:38766 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726187AbgGNO1R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jul 2020 10:27:17 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06EENFcM063488;
        Tue, 14 Jul 2020 14:26:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=qMQnxDh7lLTem5GHBoFbTpsZAzURxuhHrYLIUSYBF3w=;
 b=HtinuOMygse0d//W2DL4O5yw/8+OI55evhgk1Zuz63nRJBCcHT7bl2iYf0hnfEw8sMgl
 i7K0OMObUZaMiHfs9u7tUCmSr4CrPl4GpgqtRKyckoVCT+nPiRIZNb/970Bt+zxUXK9t
 UpdYSri6c/SDsu0jw2VMbvB0MDlLiRnC85jr7rD1AzVuDxBXpV8knO2QzydUbWC8+xw1
 vZOMnQy15yZE6yKG86Cimej8qZ0A8cI0R2EFcdFCZorzejPEBSVCmnVNnvVY0bf1qh2y
 pu/4TPHBEQuxbWap7rq1QscDiwQlAyZ1uo8Uo+WBC6dQ1vn8Y2okmzNaoK90jiXMY96v 4A==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 32762ndhh4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 14 Jul 2020 14:26:07 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06EENaaZ163160;
        Tue, 14 Jul 2020 14:24:06 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 327q0pbjyd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 14 Jul 2020 14:24:06 +0000
Received: from abhmp0020.oracle.com (abhmp0020.oracle.com [141.146.116.26])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 06EEO03k016983;
        Tue, 14 Jul 2020 14:24:00 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 14 Jul 2020 07:23:59 -0700
Date: Tue, 14 Jul 2020 17:23:51 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, kernel-janitors@vger.kernel.org
Subject: [PATCH] KVM: SVM: Fix sev_pin_memory() error handling
Message-ID: <20200714142351.GA315374@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9681
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 malwarescore=0 spamscore=0
 mlxlogscore=999 bulkscore=0 adultscore=0 phishscore=0 suspectscore=2
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007140111
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9681
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 malwarescore=0 spamscore=0
 clxscore=1011 priorityscore=1501 mlxlogscore=999 lowpriorityscore=0
 bulkscore=0 suspectscore=2 phishscore=0 adultscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007140111
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The sev_pin_memory() function was modified to return error pointers
instead of NULL but there are two problems.  The first problem is that
if "npages" is zero then it still returns NULL.  Secondly, several of
the callers were not updated to check for error pointers instead of
NULL.

Either one of these issues will lead to an Oops.

Fixes: a8d908b5873c ("KVM: x86: report sev_pin_memory errors with PTR_ERR")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
---
 arch/x86/kvm/svm/sev.c   |   20 ++++++++++----------
 1 file changed, 10 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH] cstart: Fix typo in i386's cstart assembly
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11661359
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1ED57913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 04:19:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B65A207BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 04:19:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725877AbgGNETH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 00:19:07 -0400
Received: from mga02.intel.com ([134.134.136.20]:57766 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725497AbgGNETG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jul 2020 00:19:06 -0400
IronPort-SDR: 
 inhvhqZL3mTaf6/WCnU0Fgm/JIuUXJZYHa9BWXsx/5Bd8JdaVqwH8apx6/1MugNTCFfTttg6fJ
 Iam81+tNKOzQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="136946947"
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="136946947"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 21:19:06 -0700
IronPort-SDR: 
 2+tugN3/UebKnAOuXoR26kZzyBzvvT7js/ZgQpQjrGtrPVEkNEaefQj5GxesSKFeuE+XsZaRWP
 jEC6kuoLb5TA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="307712916"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 13 Jul 2020 21:19:06 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] cstart: Fix typo in i386's cstart assembly
Date: Mon, 13 Jul 2020 21:19:05 -0700
Message-Id: <20200714041905.12848-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Replace a '%' with a '$' to encode a literal in when initializing CR4.
This fixes the build on i386 as gcc complains about a non-existent
register.

  x86/cstart.S: Assembler messages:
  x86/cstart.S:128: Error: bad register name `%(1<<4)'
  Makefile:101: recipe for target 'x86/cstart.o' failed

Fixes: d86ef58519645 ("cstart: do not assume CR4 starts as zero")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Nadav Amit <namit@vmware.com>
---
 x86/cstart.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] lib/alloc_page: Revert to 'unsigned long' for @size params
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11661361
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D296E913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 04:20:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C43C8221E9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 04:20:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725836AbgGNEUr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 00:20:47 -0400
Received: from mga14.intel.com ([192.55.52.115]:36617 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725497AbgGNEUr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jul 2020 00:20:47 -0400
IronPort-SDR: 
 WC5FvcJyh5a9a1jbh+hU61p8BZ1Yq0h84DoGKuQeWRhSFCOybTkAOhgajO/5E5yk18TQo7fHd9
 WIvR8nU8pMaQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="147933846"
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="147933846"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 21:20:47 -0700
IronPort-SDR: 
 f+TaMNHxkuirtQ3ImzLoVq2T847Pq4JhWcbXOci3WFLPT2F30cG6/92BgYp6hDNrZ1mMiZjys+
 hN+kWk7bVVOA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="268545172"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga007.fm.intel.com with ESMTP; 13 Jul 2020 21:20:47 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Andrew Jones <drjones@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [kvm-unit-tests PATCH] lib/alloc_page: Revert to 'unsigned long' for
 @size params
Date: Mon, 13 Jul 2020 21:20:46 -0700
Message-Id: <20200714042046.13419-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Revert to using 'unsigned long' instead of 'size_t' for free_pages() and
get_order().  The recent change to size_t for free_pages() breaks i386
with -Werror as the assert_msg() formats expect unsigned longs, whereas
size_t is an 'unsigned int' on i386 (though both longs and ints are 4
bytes).

Message formatting aside, unsigned long is the correct choice given the
current code base as alloc_pages() and free_pages_by_order() explicitly
expect, work on, and/or assert on the size being an unsigned long.

Fixes: 73f4b202beb39 ("lib/alloc_page: change some parameter types")
Cc: Claudio Imbrenda <imbrenda@linux.ibm.com>
Cc: Andrew Jones <drjones@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Tested-by: Thomas Huth <thuth@redhat.com>
---
 lib/alloc_page.c | 2 +-
 lib/alloc_page.h | 2 +-
 lib/bitops.h     | 2 +-
 3 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: Don't attempt to load PDPTRs when 64-bit mode is enabled
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11661321
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E84BC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 01:57:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D96F421BE5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 01:57:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726478AbgGNB5e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jul 2020 21:57:34 -0400
Received: from mga14.intel.com ([192.55.52.115]:24486 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726149AbgGNB5e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jul 2020 21:57:34 -0400
IronPort-SDR: 
 R4Tp2NX0R6+OCjQD1BEERhXhQtpoLAo5yAg8M1A+nzGkADw5dDP4FcOS2NoqErlYHC4hwGy85U
 Y2eveZtY7kCA==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="147905455"
X-IronPort-AV: E=Sophos;i="5.75,349,1589266800";
   d="scan'208";a="147905455"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 18:57:33 -0700
IronPort-SDR: 
 71eSYM25ykw/jOPCA7O/DMLEvwPLrpRSDX+xrnEOdBZFL3wjyP/ejX2oMXO+mw+/WirUYCm/fl
 O7CxzvWmGL5w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,349,1589266800";
   d="scan'208";a="307681797"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga004.fm.intel.com with ESMTP; 13 Jul 2020 18:57:33 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH] KVM: x86: Don't attempt to load PDPTRs when 64-bit mode is
 enabled
Date: Mon, 13 Jul 2020 18:57:32 -0700
Message-Id: <20200714015732.32426-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't attempt to load PDPTRs if EFER.LME=1, i.e. if 64-bit mode is
enabled.  A recent change to reload the PDTPRs when CR0.CD or CR0.NW is
toggled botched the EFER.LME handling and sends KVM down the PDTPR path
when is_paging() is true, i.e. when the guest toggles CD/NW in 64-bit
mode.

Split the CR0 checks for 64-bit vs. 32-bit PAE into separate paths.  The
64-bit path is specifically checking state when paging is toggled on,
i.e. CR0.PG transititions from 0->1.  The PDPTR path now needs to run if
the new CR0 state has paging enabled, irrespective of whether paging was
already enabled.  Trying to shave a few cycles to make the PDPTR path an
"else if" case is a mess.

Fixes: d42e3fae6faed ("kvm: x86: Read PDPTEs on CR0.CD and CR0.NW changes")
Cc: Jim Mattson <jmattson@google.com>
Cc: Oliver Upton <oupton@google.com>
Cc: Peter Shier <pshier@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

The other way to fix this, with a much smaller diff stat, is to simply
move the !is_page(vcpu) check inside (vcpu->arch.efer & EFER_LME).  But
that results in a ridiculous amount of nested conditionals for what is a
very straightforward check e.g.

	if (cr0 & X86_CR0_PG) {
		if (vcpu->arch.efer & EFER_LME) }
			if (!is_paging(vcpu)) {
				...
			}
		}
	}

Since this doesn't need to be backported anywhere, I didn't see any value
in having an intermediate step.

 arch/x86/kvm/x86.c | 24 ++++++++++++------------
 1 file changed, 12 insertions(+), 12 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] nVMX: Restore active host RIP/CR4 after test_host_addr_size()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11661191
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F428618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 00:24:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47D50218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 00:24:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726834AbgGNAX6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jul 2020 20:23:58 -0400
Received: from mga02.intel.com ([134.134.136.20]:36936 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726347AbgGNAX5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jul 2020 20:23:57 -0400
IronPort-SDR: 
 pahcKXbuCuu+gK2/YkwLG5SOE/RYdF4szZt4BAT4hg7t2r2J1KOwBVQeeglApbP+eYgo457oTC
 cAAQeoJhawyQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="136910634"
X-IronPort-AV: E=Sophos;i="5.75,349,1589266800";
   d="scan'208";a="136910634"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 17:23:56 -0700
IronPort-SDR: 
 jivkYAxrhZj2/1arEnDkQf/ghX/sfo78AkQA/TXkPLXkpQ9rqYysl07HrvMernpJnLnKhVAuKT
 n5TaiyD2QT6A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,349,1589266800";
   d="scan'208";a="268505774"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga007.fm.intel.com with ESMTP; 13 Jul 2020 17:23:56 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Karl Heubaum <karl.heubaum@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Subject: [kvm-unit-tests PATCH 1/2] nVMX: Restore active host RIP/CR4 after
 test_host_addr_size()
Date: Mon, 13 Jul 2020 17:23:54 -0700
Message-Id: <20200714002355.538-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
In-Reply-To: <20200714002355.538-1-sean.j.christopherson@intel.com>
References: <20200714002355.538-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Perform one last VMX transition to actually load the host's RIP and CR4
at the end of test_host_addr_size().  Simply writing the VMCS doesn't
restore the values in hardware, e.g. as is, CR4.PCIDE can be left set,
which causes spectacularly confusing explosions when other misguided
tests assume setting bit 63 in CR3 will cause a non-canonical #GP.

Fixes: 0786c0316ac05 ("kvm-unit-test: nVMX: Check Host Address Space Size on vmentry of nested guests")
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Cc: Karl Heubaum <karl.heubaum@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 x86/vmx_tests.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v6 1/2] virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11662439
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B4756C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 11:38:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D2012220C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 11:38:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728013AbgGNLir (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 07:38:47 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:53704 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726352AbgGNLiq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Jul 2020 07:38:46 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06EBWwVl005597;
        Tue, 14 Jul 2020 07:38:40 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3279du4sga-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 07:38:39 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06EBcdSR023280;
        Tue, 14 Jul 2020 07:38:39 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3279du4sfk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 07:38:39 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06EBQ4FQ001874;
        Tue, 14 Jul 2020 11:38:37 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03fra.de.ibm.com with ESMTP id 327527hnj0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 11:38:37 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06EBcYtU56229938
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 14 Jul 2020 11:38:34 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F361F4204B;
        Tue, 14 Jul 2020 11:38:33 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 66B8642045;
        Tue, 14 Jul 2020 11:38:26 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.162.148])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 14 Jul 2020 11:38:26 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v6 1/2] virtio: let arch validate VIRTIO features
Date: Tue, 14 Jul 2020 13:38:01 +0200
Message-Id: <1594726682-12076-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594726682-12076-1-git-send-email-pmorel@linux.ibm.com>
References: <1594726682-12076-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-14_02:2020-07-14,2020-07-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 lowpriorityscore=0 clxscore=1015 phishscore=0 mlxscore=0 adultscore=0
 bulkscore=0 spamscore=0 malwarescore=0 priorityscore=1501 suspectscore=1
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007140085
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may need to validate the VIRTIO devices features
based on architecture specifics.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 2 files changed, 20 insertions(+)

```
#### [kvm-unit-tests PATCH v12 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11662357
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D516413B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 11:17:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C2F9D2220C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 11:17:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728061AbgGNLRL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 07:17:11 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14018 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726801AbgGNLQL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 14 Jul 2020 07:16:11 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06EB5O9T089545;
        Tue, 14 Jul 2020 07:16:09 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3277k9drgw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 07:16:09 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06EB5VYF090266;
        Tue, 14 Jul 2020 07:16:09 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3277k9drfq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 07:16:08 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06EBFgng006226;
        Tue, 14 Jul 2020 11:16:07 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04ams.nl.ibm.com with ESMTP id 32752838rv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 14 Jul 2020 11:16:06 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06EBG4nJ30277792
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 14 Jul 2020 11:16:04 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BAF2EA4064;
        Tue, 14 Jul 2020 11:16:04 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 04E73A4065;
        Tue, 14 Jul 2020 11:16:04 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.162.148])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 14 Jul 2020 11:16:03 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v12 1/9] s390x: saving regs for interrupts
Date: Tue, 14 Jul 2020 13:15:40 +0200
Message-Id: <1594725348-10034-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594725348-10034-1-git-send-email-pmorel@linux.ibm.com>
References: <1594725348-10034-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-14_02:2020-07-14,2020-07-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1 phishscore=0
 spamscore=0 adultscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999
 bulkscore=0 malwarescore=0 lowpriorityscore=0 clxscore=1015
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007140081
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers, the floating point registers and the floating point
control register on the stack in case of I/O interrupts

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/cstart64.S | 41 +++++++++++++++++++++++++++++++++++++++--
 1 file changed, 39 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/5] PCI: Add Intel QuickAssist device IDs
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11661509
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E78EE913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 06:36:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D810E221F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 06:36:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726786AbgGNGgq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 02:36:46 -0400
Received: from mga07.intel.com ([134.134.136.100]:33942 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725306AbgGNGgp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jul 2020 02:36:45 -0400
IronPort-SDR: 
 4nFB9RidGD7Uz0m6cDLSUCduwtpBoHxGYDsvrCeH0A9mbOvdAFLpvY67nMyb71JlOTZQT/2iX2
 zWN/D9g1hG1g==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="213632484"
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="213632484"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 23:36:44 -0700
IronPort-SDR: 
 I4HnTb5tyE8mAIwm6iR2na6s+YT52WCITvWOOvWkwf3Ls+3pP/oQYcrFJPMLlvi2DgiEpTlbw6
 XmGqWL7XUtJQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,350,1589266800";
   d="scan'208";a="299435533"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by orsmga002.jf.intel.com with ESMTP; 13 Jul 2020 23:36:41 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v2 1/5] PCI: Add Intel QuickAssist device IDs
Date: Tue, 14 Jul 2020 07:36:06 +0100
Message-Id: <20200714063610.849858-2-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200714063610.849858-1-giovanni.cabiddu@intel.com>
References: <20200714063610.849858-1-giovanni.cabiddu@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add device IDs for the following Intel QuickAssist devices: DH895XCC,
C3XXX and C62X.

The defines in this patch are going to be referenced in two independent
drivers, qat and vfio-pci.

Signed-off-by: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Acked-by: Bjorn Helgaas <bhelgaas@google.com>
---
 include/linux/pci_ids.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] x86/bugs/multihit: Fix mitigation reporting when KVM is not in use
##### From: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
X-Patchwork-Id: 11661231
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 84F6413A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 01:24:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69095206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 01:24:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726758AbgGNBYq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 13 Jul 2020 21:24:46 -0400
Received: from mga12.intel.com ([192.55.52.136]:3555 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726364AbgGNBYq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 13 Jul 2020 21:24:46 -0400
IronPort-SDR: 
 SIGcOZgvAqjfH//LbaTL/KD/vLUq4oLQendT9QYk+KT9Vc/gGkuPgu+UzIWhuWJ4SapHoLU21S
 Rprxhe2HE5tg==
X-IronPort-AV: E=McAfee;i="6000,8403,9681"; a="128335352"
X-IronPort-AV: E=Sophos;i="5.75,349,1589266800";
   d="scan'208";a="128335352"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jul 2020 18:24:45 -0700
IronPort-SDR: 
 zTuwavoXlFX6hjRzlLozhiHIC7rdTX3dDznO7Xsbcd+TcvNnPRYsMfxCNvEFbKCCwi91T5suab
 2Nu9R/xpPjRg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,349,1589266800";
   d="scan'208";a="485691184"
Received: from guptapadev.jf.intel.com (HELO guptapadev.amr) ([10.54.74.188])
  by fmsmga005.fm.intel.com with ESMTP; 13 Jul 2020 18:24:44 -0700
Date: Mon, 13 Jul 2020 18:18:54 -0700
From: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
To: Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>
Cc: x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        Tony Luck <tony.luck@intel.com>,
        "Gomez Iglesias, Antonio" <antonio.gomez.iglesias@intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Vincenzo Frascino <vincenzo.frascino@arm.com>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Mark Gross <mgross@linux.intel.com>,
        Waiman Long <longman@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Jonathan Corbet <corbet@lwn.net>
Subject: [PATCH] x86/bugs/multihit: Fix mitigation reporting when KVM is not
 in use
Message-ID: 
 <267631f4db4fd7e9f7ca789c2efaeab44103f68e.1594689154.git.pawan.kumar.gupta@linux.intel.com>
MIME-Version: 1.0
Content-Disposition: inline
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On systems that have virtualization disabled or KVM module is not
loaded, sysfs mitigation state of X86_BUG_ITLB_MULTIHIT is reported
incorrectly as:

  $ cat /sys/devices/system/cpu/vulnerabilities/itlb_multihit
  KVM: Vulnerable

System is not vulnerable to DoS attack from a rogue guest when:
 - KVM module is not loaded or
 - Virtualization is disabled in the hardware or
 - Kernel was configured without support for KVM

Change the reporting to "Currently not affected (KVM not in use)" for
such cases.

Reported-by: Nelson Dsouza <nelson.dsouza@linux.intel.com>
Fixes: b8e8c8303ff2 ("kvm: mmu: ITLB_MULTIHIT mitigation")
Signed-off-by: Pawan Gupta <pawan.kumar.gupta@linux.intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
---
 .../admin-guide/hw-vuln/multihit.rst          |  5 +++-
 arch/x86/include/asm/processor.h              |  6 +++++
 arch/x86/kernel/cpu/bugs.c                    | 24 +++++++++----------
 arch/x86/kvm/mmu/mmu.c                        |  9 +++++--
 4 files changed, 29 insertions(+), 15 deletions(-)

```
#### [PATCH v4 01/75] KVM: SVM: Add GHCB definitions
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11662673
Return-Path: <SRS0=PKWe=AZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC3BC13B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 12:18:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC901223C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 14 Jul 2020 12:18:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728111AbgGNMKh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jul 2020 08:10:37 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60588 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726354AbgGNMKg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jul 2020 08:10:36 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 76084C061794;
        Tue, 14 Jul 2020 05:10:36 -0700 (PDT)
Received: from cap.home.8bytes.org (p5b006776.dip0.t-ipconnect.de
 [91.0.103.118])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id C708A293;
        Tue, 14 Jul 2020 14:10:33 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v4 01/75] KVM: SVM: Add GHCB definitions
Date: Tue, 14 Jul 2020 14:08:03 +0200
Message-Id: <20200714120917.11253-2-joro@8bytes.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200714120917.11253-1-joro@8bytes.org>
References: <20200714120917.11253-1-joro@8bytes.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Extend the vmcb_safe_area with SEV-ES fields and add a new
'struct ghcb' which will be used for guest-hypervisor communication.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/svm.h | 45 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c     |  2 ++
 2 files changed, 46 insertions(+), 1 deletion(-)

```
