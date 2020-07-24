#### [PATCH] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and {vmx|svm}_nested_ops via macro
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11681741
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E1BC6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 22:33:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30222207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 22:33:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="GpU9rin1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727775AbgGWWdF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 18:33:05 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:60848 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726608AbgGWWdE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jul 2020 18:33:04 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06NMLOkG081949;
        Thu, 23 Jul 2020 22:32:52 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=92kUA74Ian40HlxMnm3Y3R2uvKyQcBqSZ1k45VxFz94=;
 b=GpU9rin1B32XuNiRU3NdAoal8HG4qBdQHiHFn5KyJ9Om9PLqWkWO+7pdruAdmAPMv5Tf
 dSdSdrsp+IAlMoXxhPrtQ5vMgh7+i7lsxqrUlZ9CSn5zSBep9EROIAOGZEgyoEJKX5y5
 B0NoHZiMARXImDVR90RFzdShxFix4PpnkdYzWZc12i4/EXsw2BAjdL5WgtGNBTYMkpte
 k60o5a+Rxcwle5HTFeDKSOFu/i9kRc72eT07eSpRSON2MBiADeqKf/jXi9hfQP4BRLY9
 nK0HG0VsvF9EKSTFdnfo7rYcqpnwvRkVNUoiaBOahlfX66ZqGc4y+RHyLpnTkvh7rUlQ yg==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 32bs1mv6nb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Thu, 23 Jul 2020 22:32:52 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06NMWgON023993;
        Thu, 23 Jul 2020 22:32:51 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3020.oracle.com with ESMTP id 32ffm7xcmc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jul 2020 22:32:51 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 06NMW82a009000;
        Thu, 23 Jul 2020 22:32:08 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 23 Jul 2020 15:32:07 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com
Subject: [PATCH] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
 {vmx|svm}_nested_ops via macro
Date: Thu, 23 Jul 2020 22:31:58 +0000
Message-Id: <1595543518-72310-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1595543518-72310-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1595543518-72310-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9691
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 suspectscore=4
 mlxlogscore=999 mlxscore=0 spamscore=0 phishscore=0 malwarescore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007230156
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9691
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=4
 bulkscore=0 adultscore=0
 lowpriorityscore=0 mlxlogscore=999 malwarescore=0 clxscore=1015
 spamscore=0 mlxscore=0 impostorscore=0 phishscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007230156
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The names of some of the implemented kvm_x86_ops do not have a corresponding
'vmx_' or 'svm_' prefix. Also, the order of the words in some of the names
do not conform to that in the kvm_x86_ops structure. Fixing the naming will
help in better readability and maintenance of the code.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  12 +-
 arch/x86/kvm/svm/avic.c         |   4 +-
 arch/x86/kvm/svm/nested.c       |  16 +--
 arch/x86/kvm/svm/sev.c          |   4 +-
 arch/x86/kvm/svm/svm.c          | 218 ++++++++++++++++++------------------
 arch/x86/kvm/svm/svm.h          |   8 +-
 arch/x86/kvm/vmx/nested.c       |  26 +++--
 arch/x86/kvm/vmx/nested.h       |   2 +-
 arch/x86/kvm/vmx/vmx.c          | 238 ++++++++++++++++++++--------------------
 arch/x86/kvm/vmx/vmx.h          |   2 +-
 arch/x86/kvm/x86.c              |  20 ++--
 11 files changed, 279 insertions(+), 271 deletions(-)

```
#### [PATCH 1/7] powerpc/watchpoint/kvm: Rename current DAWR macros and variables
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11680555
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EA5626C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:22:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC319208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:22:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728420AbgGWKWo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 06:22:44 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10622 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728402AbgGWKWm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Jul 2020 06:22:42 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06NA2a8w180188;
        Thu, 23 Jul 2020 06:22:22 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32d91x43q0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:22:21 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06NA2kUl180815;
        Thu, 23 Jul 2020 06:22:15 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32d91x43mc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:22:15 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06NAHOHl010106;
        Thu, 23 Jul 2020 10:22:10 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06fra.de.ibm.com with ESMTP id 32brbgu68r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 10:22:10 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06NAKfGE63439106
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jul 2020 10:20:41 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E322FA4064;
        Thu, 23 Jul 2020 10:22:05 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 75FC9A4062;
        Thu, 23 Jul 2020 10:22:02 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.40.160])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Jul 2020 10:22:02 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        pbonzini@redhat.com, christophe.leroy@c-s.fr, jniethe5@gmail.com,
        pedromfc@br.ibm.com, rogealve@br.ibm.com, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, linux-kselftest@vger.kernel.org
Subject: [PATCH 1/7] powerpc/watchpoint/kvm: Rename current DAWR macros and
 variables
Date: Thu, 23 Jul 2020 15:50:52 +0530
Message-Id: <20200723102058.312282-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200723102058.312282-1-ravi.bangoria@linux.ibm.com>
References: <20200723102058.312282-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-23_03:2020-07-22,2020-07-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 malwarescore=0
 spamscore=0 priorityscore=1501 impostorscore=0 mlxscore=0 bulkscore=0
 lowpriorityscore=0 adultscore=0 suspectscore=0 clxscore=1015
 mlxlogscore=994 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007230072
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Power10 is introducing second DAWR. Use real register names (with
suffix 0) from ISA for current macros and variables used by kvm.

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 Documentation/virt/kvm/api.rst            |  4 +--
 arch/powerpc/include/asm/kvm_host.h       |  4 +--
 arch/powerpc/include/uapi/asm/kvm.h       |  4 +--
 arch/powerpc/kernel/asm-offsets.c         |  4 +--
 arch/powerpc/kvm/book3s_hv.c              | 32 +++++++++++------------
 arch/powerpc/kvm/book3s_hv_nested.c       |  8 +++---
 arch/powerpc/kvm/book3s_hv_rmhandlers.S   | 20 +++++++-------
 tools/arch/powerpc/include/uapi/asm/kvm.h |  4 +--
 8 files changed, 40 insertions(+), 40 deletions(-)

```
#### [PATCH 1/2] ppc: Rename current DAWR macros
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11680585
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F75A13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:43:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 721C02086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 10:43:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728424AbgGWKnB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 06:43:01 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:38182 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725911AbgGWKnB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Jul 2020 06:43:01 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06NAW0Jx065827;
        Thu, 23 Jul 2020 06:42:37 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32e1vsu8n8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:42:37 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06NAXVPc071167;
        Thu, 23 Jul 2020 06:42:36 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32e1vsu8m9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 06:42:36 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06NAd0bi026128;
        Thu, 23 Jul 2020 10:42:34 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06fra.de.ibm.com with ESMTP id 32brbgu6p7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 23 Jul 2020 10:42:34 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06NAgUnA63504602
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Jul 2020 10:42:30 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 51AC811C050;
        Thu, 23 Jul 2020 10:42:30 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A043811C058;
        Thu, 23 Jul 2020 10:42:26 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.40.160])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Jul 2020 10:42:26 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        pbonzini@redhat.com, christophe.leroy@c-s.fr, jniethe5@gmail.com,
        pedromfc@br.ibm.com, rogealve@br.ibm.com, cohuck@redhat.com,
        mst@redhat.com, clg@kaod.org, qemu-ppc@nongnu.org,
        qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH 1/2] ppc: Rename current DAWR macros
Date: Thu, 23 Jul 2020 16:12:19 +0530
Message-Id: <20200723104220.314671-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200723104220.314671-1-ravi.bangoria@linux.ibm.com>
References: <20200723104220.314671-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-23_03:2020-07-22,2020-07-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 malwarescore=0 mlxlogscore=947 phishscore=0 spamscore=0 impostorscore=0
 lowpriorityscore=0 adultscore=0 suspectscore=0 clxscore=1015
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007230076
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Power10 is introducing second DAWR. Use real register names (with
suffix 0) from ISA for current macros.

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 include/hw/ppc/spapr.h          | 2 +-
 linux-headers/asm-powerpc/kvm.h | 4 ++--
 target/ppc/cpu.h                | 4 ++--
 target/ppc/translate_init.inc.c | 8 ++++----
 4 files changed, 9 insertions(+), 9 deletions(-)

```
#### [PATCH v3 1/5] PCI: Add Intel QuickAssist device IDs
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11681665
Return-Path: <SRS0=LskN=BC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8190C14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 21:47:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6931420825
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Jul 2020 21:47:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727950AbgGWVr3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Jul 2020 17:47:29 -0400
Received: from mga04.intel.com ([192.55.52.120]:44370 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727109AbgGWVr2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Jul 2020 17:47:28 -0400
IronPort-SDR: 
 DsfrAZaSCnT0702YBjfVULOaBKEQawkyO7hUY5NzPQyA3Dw1juj1YZOIsPY4ofuaJ6R+yvdaPO
 lcU679I4xQtw==
X-IronPort-AV: E=McAfee;i="6000,8403,9691"; a="148119979"
X-IronPort-AV: E=Sophos;i="5.75,388,1589266800";
   d="scan'208";a="148119979"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Jul 2020 14:47:28 -0700
IronPort-SDR: 
 9F0MLbkevq401E5W0qh64MuYhgXWKZRIo1g8Fe7vp4XBwBaKK0EnqRSSWoJ68qj1Zt45eR1Vtp
 cuE89jkDGqLw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,388,1589266800";
   d="scan'208";a="311183956"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by fmsmga004.fm.intel.com with ESMTP; 23 Jul 2020 14:47:25 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        fiona.trahe@intel.com, qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH v3 1/5] PCI: Add Intel QuickAssist device IDs
Date: Thu, 23 Jul 2020 22:47:01 +0100
Message-Id: <20200723214705.5399-2-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200723214705.5399-1-giovanni.cabiddu@intel.com>
References: <20200723214705.5399-1-giovanni.cabiddu@intel.com>
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
---
 include/linux/pci_ids.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
