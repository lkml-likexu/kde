

#### [PATCH v2 0/4] KVM: PPC: Power10 2nd DAWR enablement
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Tue Nov 24 10:59:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11927943
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BB016C56202
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 11:02:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 595C420782
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 11:02:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="FFC/r45L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732440AbgKXLBw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 06:01:52 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:48194 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732243AbgKXLBv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Nov 2020 06:01:51 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOAW7bM179577;
        Tue, 24 Nov 2020 06:01:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=LZBPkChyo3/20UhougbKb9Te/JdSFl+s/zG6QHX7z8U=;
 b=FFC/r45L7ZnomqcM3AOy/4q8VvmLpe1o5ak4LCVAykOvMu74Xnvth2144VlmvDLdleX7
 DEcGehgggIyHE1sM5Px1/pY9uTtFFoX8DZvP46kU2HoTj4NICWsJByTc+8XED5t6rv/k
 ZiKml3eXVd6RyQkB5FJ3+jjViX2FijELvM7668M648KR71sK2cD3YZPMUeC/+6uBPoeX
 fq353oz6pTN9lagpmOWBHoDaMkW9MVWqPcK1yUBpBDCtAyLjoKYTeK5FEAEBWMfL4KwA
 pbsmveO5OT6P7btzEj1QdungSFkypOg4XQEtUdIucjBIMeOVNtvZ6XRHx7GQ6HsnOVbj FQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 350rb0ysb6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 06:01:35 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AOAWRQA180968;
        Tue, 24 Nov 2020 06:01:34 -0500
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 350rb0ys80-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 06:01:33 -0500
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOAr6kV017839;
        Tue, 24 Nov 2020 11:01:29 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma02fra.de.ibm.com with ESMTP id 350cvrs0ta-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 11:01:29 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AOB0Cdp11600570
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Nov 2020 11:00:12 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E83DC4203F;
        Tue, 24 Nov 2020 11:00:11 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BD8CE42059;
        Tue, 24 Nov 2020 11:00:08 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.32.189])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 24 Nov 2020 11:00:08 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        leobras.c@gmail.com, pbonzini@redhat.com, christophe.leroy@c-s.fr,
        jniethe5@gmail.com, kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Subject: [PATCH v2 0/4] KVM: PPC: Power10 2nd DAWR enablement
Date: Tue, 24 Nov 2020 16:29:49 +0530
Message-Id: <20201124105953.39325-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-24_04:2020-11-24,2020-11-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 malwarescore=0
 mlxscore=0 priorityscore=1501 adultscore=0 clxscore=1015 spamscore=0
 lowpriorityscore=0 suspectscore=0 bulkscore=0 mlxlogscore=999
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011240061
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enable p10 2nd DAWR feature for Book3S kvm guest. DAWR is a hypervisor
resource and thus H_SET_MODE hcall is used to set/unset it. A new case
H_SET_MODE_RESOURCE_SET_DAWR1 is introduced in H_SET_MODE hcall for
setting/unsetting 2nd DAWR. Also, new capability KVM_CAP_PPC_DAWR1 has
been added to query 2nd DAWR support via kvm ioctl.

This feature also needs to be enabled in Qemu to really use it. I'll
post Qemu patches once kvm patches get accepted.

v1: https://lore.kernel.org/r/20200723102058.312282-1-ravi.bangoria@linux.ibm.com

v1->v2:
 - patch #1: New patch
 - patch #2: Don't rename KVM_REG_PPC_DAWR, it's an uapi macro
 - patch #3: Increment HV_GUEST_STATE_VERSION
 - Split kvm and selftests patches into different series
 - Patches rebased to paulus/kvm-ppc-next (cf59eb13e151) + few
   other watchpoint patches which are yet to be merged in
   paulus/kvm-ppc-next.

Ravi Bangoria (4):
  KVM: PPC: Allow nested guest creation when L0 hv_guest_state > L1
  KVM: PPC: Rename current DAWR macros and variables
  KVM: PPC: Add infrastructure to support 2nd DAWR
  KVM: PPC: Introduce new capability for 2nd DAWR

 Documentation/virt/kvm/api.rst            |  2 +
 arch/powerpc/include/asm/hvcall.h         | 25 ++++++++-
 arch/powerpc/include/asm/kvm_host.h       |  6 +-
 arch/powerpc/include/uapi/asm/kvm.h       |  2 +
 arch/powerpc/kernel/asm-offsets.c         |  6 +-
 arch/powerpc/kvm/book3s_hv.c              | 65 ++++++++++++++++++----
 arch/powerpc/kvm/book3s_hv_nested.c       | 68 ++++++++++++++++++-----
 arch/powerpc/kvm/book3s_hv_rmhandlers.S   | 43 ++++++++++----
 arch/powerpc/kvm/powerpc.c                |  3 +
 include/uapi/linux/kvm.h                  |  1 +
 tools/arch/powerpc/include/uapi/asm/kvm.h |  2 +
 11 files changed, 181 insertions(+), 42 deletions(-)
```
#### [RFC, v2 0/1] msi support for platform devices
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
From patchwork Tue Nov 24 16:16:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11929337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.6 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,SPF_HELO_NONE,
	SPF_PASS,T_TVD_MIME_NO_HEADERS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5A373C63798
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 16:17:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E5D3320870
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 16:17:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=broadcom.com header.i=@broadcom.com
 header.b="X6VV2w3V"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390300AbgKXQRf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 11:17:35 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60026 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390081AbgKXQRf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Nov 2020 11:17:35 -0500
Received: from mail-pf1-x443.google.com (mail-pf1-x443.google.com
 [IPv6:2607:f8b0:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 17523C0617A6
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 08:17:35 -0800 (PST)
Received: by mail-pf1-x443.google.com with SMTP id x24so6680712pfn.6
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 08:17:35 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=0awVi4Mchy6FU9xHxN/rEIYV4viTpMcftI0q9+HKx1g=;
        b=X6VV2w3VTBFSEdgam1IizCosJk3n3pboRHccqjI3/OQlAj+B/iVoLtc+fxHwI1A8au
         u/cyfK8fJCU5NbdEBPZHfb/I9fT72zMlubnTQm6VKBHqRHPuY/hYVcqTwMcXeqNqn2E5
         aw8gDKxeS/Xtzh+wCjEc0LiJyO+9A2kim2AAQ=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=0awVi4Mchy6FU9xHxN/rEIYV4viTpMcftI0q9+HKx1g=;
        b=eaO2D7hG5+vEKNKCGruDeugjpPieztPlQVu/Rlg0uCnhJGYK3U7CxWxIg8X7K8gIyZ
         MREDXC8UwRG4rXlhG4CeNPO/iOq7H1EBsdIv/JoLpswbjpPmyX+1EfC1VC8Yze9ZTPWW
         rtMKPor00kWoe29+s4YYVKgq+LEoqeQKth2qRupXH+ScPfq47aW1KRKtT5cxooTOARYB
         nXLiqWuedp/WPjmvLJ/x5tdOS3v2f1+gAj9XG7z+viGHr4eJG/OEmxZqH3hEDSAJD9Eq
         56zu83cMbe1pQ9KEVCa2ZTX3WcfP6yPsUPDPGZsLJ1Se2GKBp7R4OOQIc/prtr2QhkqF
         i6YQ==
X-Gm-Message-State: AOAM531L0gJosGoL99PQSiCoFcdg105vPatbpnZ0x35qZg5IjRuMJS2C
        mlKDyjF7dbnyq4kstzUiO7ML/Gj7QwPnURNUnd7/ew==
X-Google-Smtp-Source: 
 ABdhPJwojqBzccB5bu89FllRpPMAi909Yd9PoVZKGKVNFflUAow+6FzaHTA9ezibuYHFF4NgR824TA==
X-Received: by 2002:a17:90a:fb87:: with SMTP id
 cp7mr5958416pjb.0.1606234654182;
        Tue, 24 Nov 2020 08:17:34 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 t9sm2798549pfq.39.2020.11.24.08.17.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 24 Nov 2020 08:17:32 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        ashwin.kamath@broadcom.com, zachary.schroff@broadcom.com,
        manish.kurup@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC, v2 0/1] msi support for platform devices
Date: Tue, 24 Nov 2020 21:46:45 +0530
Message-Id: <20201124161646.41191-1-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201112175852.21572-1-vikas.gupta@broadcom.com>
References: <20201112175852.21572-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC adds support for MSI for platform devices.
MSI block is added as an ext irq along with the existing
wired interrupt implementation.

Changes from:
-------------
 v1 to v2:
	1) IRQ allocation has been implemented as below:
	       ----------------------------
	       |IRQ-0|IRQ-1|....|IRQ-n|MSI|
       	       ----------------------------
		MSI block has msi contexts and its implemneted
		as ext irq.

	2) Removed vendor specific module for msi handling so
	   previously patch2 and patch3 are not required.

	3) MSI related data is exported to userspace using 'caps'.
	 Please note VFIO_IRQ_INFO_CAP_TYPE in include/uapi/linux/vfio.h implementation
	is taken from the Eric`s patch
        https://patchwork.kernel.org/project/kvm/patch/20201116110030.32335-8-eric.auger@redhat.com/


 v0 to v1:
   i)  Removed MSI device flag VFIO_DEVICE_FLAGS_MSI.
   ii) Add MSI(s) at the end of the irq list of platform IRQs.
       MSI(s) with first entry of MSI block has count and flag
       information.
       IRQ list: Allocation for IRQs + MSIs are allocated as below
       Example: if there are 'n' IRQs and 'k' MSIs
       -------------------------------------------------------
       |IRQ-0|IRQ-1|....|IRQ-n|MSI-0|MSI-1|MSI-2|......|MSI-k|
       -------------------------------------------------------
       MSI-0 will have count=k set and flags set accordingly.

Vikas Gupta (1):
  vfio/platform: add support for msi

 drivers/vfio/platform/vfio_platform_common.c  |  99 ++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 260 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  16 ++
 include/uapi/linux/vfio.h                     |  43 +++
 4 files changed, 401 insertions(+), 17 deletions(-)
```
#### [PATCH v12 00/17] s390/vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Tue Nov 24 21:39:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11929895
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EFE06C56202
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 21:40:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92499206E5
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 21:40:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="scfvOmOE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732891AbgKXVkc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 16:40:32 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26884 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732876AbgKXVkb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Nov 2020 16:40:31 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOLWE2G116423;
        Tue, 24 Nov 2020 16:40:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=2KFHnNhCEzkeE19BfhWGUVMq9/7FyfaCPZgYtyMrMOQ=;
 b=scfvOmOEiRlQcygJBT0oZEkcLhHz8TlstuUVJKyG1aGmkRfpsfZtjuvmweHht0kqiXoo
 vW7fPGoDno0K7B0cNdqHOmbfNmgoBWsgk+fUjUaQ0CtMB4HVH61Kb/+M0pFeE5HxpHwU
 X0a7CQ6OAOcxWp3Wp5862ik7b62GVUQywINGTekYeCX2Ic7SlRai5HFray4bVQ8uMB0G
 DPbwWVDX78DlkBtFPH7jpvEOXuVowp5vJ9RlLnKYJPacX7Yz54xLFuys81UnWqwzXVoE
 2R3qRDZD8SP8EtrCb7/LiQ8rmvW6DDjjjWQNLSEp8j2P/CN9afjee8lcdsdvWFdCZnKX jw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 350rkptynq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 16:40:30 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AOLWMZ1117098;
        Tue, 24 Nov 2020 16:40:29 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 350rkptyna-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 16:40:29 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOLccUp009144;
        Tue, 24 Nov 2020 21:40:28 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma04wdc.us.ibm.com with ESMTP id 34xth92m7x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 21:40:28 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0AOLeQfG2097674
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Nov 2020 21:40:26 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C02D2AE05F;
        Tue, 24 Nov 2020 21:40:26 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EA489AE05C;
        Tue, 24 Nov 2020 21:40:25 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.195.249])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 24 Nov 2020 21:40:25 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v12 00/17] s390/vfio-ap: dynamic configuration support
Date: Tue, 24 Nov 2020 16:39:59 -0500
Message-Id: <20201124214016.3013-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-24_07:2020-11-24,2020-11-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 suspectscore=3 priorityscore=1501 mlxlogscore=999 spamscore=0 bulkscore=0
 lowpriorityscore=0 phishscore=0 mlxscore=0 adultscore=0 clxscore=1015
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011240125
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in a few 
deficiencies this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP 
   configuration becomes available to the guest when it is subsequently
   restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to
   either mask can result in AP queue devices being unbound from the
   vfio_ap device driver and bound to a zcrypt device driver even if a
   guest is using the queues, thus giving the host access to the guest's
   private crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   reference an AP queue device bound to the vfio_ap device driver. The
   AP architecture allows assignment of AP resources that are not
   available to the system, so this artificial restriction is not 
   compliant with the architecture.

4. The AP configuration profile can be dynamically changed for the linux
   host after a KVM guest is started. For example, a new domain can be
   dynamically added to the configuration profile via the SE or an HMC
   connected to a DPM enabled lpar. Likewise, AP adapters can be 
   dynamically configured (online state) and deconfigured (standby state)
   using the SE, an SCLP command or an HMC connected to a DPM enabled
   lpar. This can result in inadvertent sharing of AP queues between the
   guest and host.

5. A root user can manually unbind an AP queue device representing a 
   queue in use by a KVM guest via the vfio_ap device driver's sysfs 
   unbind attribute. In this case, the guest will be using a queue that
   is not bound to the driver which violates the device model.

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement
more of the AP architecture:

1. A root user will be prevented from making edits to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the change would transfer
   ownership of an APQN from the vfio_ap device driver to a zcrypt driver
   while the APQN is assigned to a matrix mdev.

2. Allow a root user to hot plug/unplug AP adapters, domains and control
   domains for a KVM guest using the matrix mdev via its sysfs
   assign/unassign attributes.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if
   it results in assignment of an APQN that does not reference an AP
   queue device bound to the vfio_ap device driver, as long as the APQN
   is not reserved for use by the default zcrypt drivers (also known as
   over-provisioning of AP resources). Allowing over-provisioning of AP
   resources better models the architecture which does not preclude
   assigning AP resources that are not yet available in the system. Such
   APQNs, however, will not be assigned to the guest using the matrix
   mdev; only APQNs referencing AP queue devices bound to the vfio_ap
   device driver will actually get assigned to the guest.

5. Handle dynamic changes to the AP device model. 

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source.

2. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes 
reconfiguring a guest's AP matrix much less disruptive.

3. Rationale for allowing over-provisioning of AP resources:
----------------------------------------------------------- 
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will be given access to it. If an APQN
is dynamically unassigned from the underlying host system, it will 
automatically become unavailable to the guest.

Change log v11-v12:
------------------
* Moved matrix device lock to protect group notifier callback

* Split the 'No need to disable IRQ after queue reset' patch into
  multiple patches for easier review (move probe/remove callback
  functions and remove disable IRQ after queue reset)

* Added code to decrement reference count for KVM in group notifier
  callback

* Using mutex_trylock() in functions implementing the sysfs assign_adapter
  and assign_domain as well as the in_use callback to avoid deadlock 
  between the AP bus's ap_perms mutex and the matrix device lock used by
  vfio_ap driver.

* The sysfs guest_matrix attribute of the vfio_ap mdev will now display
  the shadow APCB regardless of whether a guest is using the mdev or not

* Replaced vfio_ap mdev filtering function with a function that initializes
  the guest's APCB by filtering the vfio_ap mdev by APID.

* No longer using filtering function during adapter/domain assignment
  to/from the vfio_ap mdev; replaced with new hot plug/unplug 
  adapter/domain functions.

* No longer using filtering function during bind/unbind; replaced with
  hot plug/unplug queue functions.

* No longer using filtering function for bulk assignment of new adapters
  and domains in on_scan_complete callback; replaced with new hot plug
  functions.    
  

Change log v10-v11:
------------------
* The matrix mdev's configuration is not filtered by APID so that if any
  APQN assigned to the mdev is not bound to the vfio_ap device driver,
  the adapter will not get plugged into the KVM guest on startup, or when
  a new adapter is assigned to the mdev.

* Replaced patch 8 by squashing patches 8 (filtering patch) and 15 (handle 
  probe/remove).

* Added a patch 1 to remove disable IRQ after a reset because the reset
  already disables a queue.

* Now using filtering code to update the KVM guest's matrix when
  notified that AP bus scan has completed.

* Fixed issue with probe/remove not inititiated by a configuration change
  occurring within a config change.


Change log v9-v10:
-----------------
* Updated the documentation in vfio-ap.rst to include information about the
  AP dynamic configuration support

Change log v8-v9:
----------------
* Fixed errors flagged by the kernel test robot

* Fixed issue with guest losing queues when a new queue is probed due to
  manual bind operation.

Change log v7-v8:
----------------
* Now logging a message when an attempt to reserve APQNs for the zcrypt
  drivers will result in taking a queue away from a KVM guest to provide
  the sysadmin a way to ascertain why the sysfs operation failed.

* Created locked and unlocked versions of the ap_parse_mask_str() function.

* Now using new interface provided by an AP bus patch -
  s390/ap: introduce new ap function ap_get_qdev() - to retrieve
  struct ap_queue representing an AP queue device. This patch is not a
  part of this series but is a prerequisite for this series. 

Change log v6-v7:
----------------
* Added callbacks to AP bus:
  - on_config_changed: Notifies implementing drivers that
    the AP configuration has changed since last AP device scan.
  - on_scan_complete: Notifies implementing drivers that the device scan
    has completed.
  - implemented on_config_changed and on_scan_complete callbacks for
    vfio_ap device driver.
  - updated vfio_ap device driver's probe and remove callbacks to handle
    dynamic changes to the AP device model. 
* Added code to filter APQNs when assigning AP resources to a KVM guest's
  CRYCB

Change log v5-v6:
----------------
* Fixed a bug in ap_bus.c introduced with patch 2/7 of the v5 
  series. Harald Freudenberer pointed out that the mutex lock
  for ap_perms_mutex in the apmask_store and aqmask_store functions
  was not being freed. 

* Removed patch 6/7 which added logging to the vfio_ap driver
  to expedite acceptance of this series. The logging will be introduced
  with a separate patch series to allow more time to explore options
  such as DBF logging vs. tracepoints.

* Added 3 patches related to ensuring that APQNs that do not reference
  AP queue devices bound to the vfio_ap device driver are not assigned
  to the guest CRYCB:

  Patch 4: Filter CRYCB bits for unavailable queue devices
  Patch 5: sysfs attribute to display the guest CRYCB
  Patch 6: update guest CRYCB in vfio_ap probe and remove callbacks

* Added a patch (Patch 9) to version the vfio_ap module.

* Reshuffled patches to allow the in_use callback implementation to
  invoke the vfio_ap_mdev_verify_no_sharing() function introduced in
  patch 2. 

Change log v4-v5:
----------------
* Added a patch to provide kernel s390dbf debug logs for VFIO AP

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from 
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic 
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (17):
  s390/vfio-ap: move probe and remove callbacks to vfio_ap_ops.c
  s390/vfio-ap: decrement reference count to KVM
  390/vfio-ap: use new AP bus interface to search for queue devices
  s390/vfio-ap: No need to disable IRQ after queue reset
  s390/vfio-ap: manage link between queue struct and matrix mdev
  s390/zcrypt: driver callback to indicate resource in use
  s390/vfio-ap: implement in-use callback for vfio_ap driver
  s390/vfio-ap: introduce shadow APCB
  s390/vfio-ap: sysfs attribute to display the guest's matrix
  s390/vfio-ap: initialize the guest apcb
  s390/vfio-ap: allow assignment of unavailable AP queues to mdev device
  s390/vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390/vfio-ap: hot plug/unplug queues on bind/unbind of queue device
  s390/zcrypt: Notify driver on config changed and scan complete
    callbacks
  s390/vfio-ap: handle host AP config change notification
  s390/vfio-ap: handle AP bus scan completed notification
  s390/vfio-ap: update docs to include dynamic config support

 Documentation/s390/vfio-ap.rst        |  401 ++++++---
 drivers/s390/crypto/ap_bus.c          |  243 +++++-
 drivers/s390/crypto/ap_bus.h          |   16 +
 drivers/s390/crypto/vfio_ap_drv.c     |   52 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 1113 +++++++++++++++++++------
 drivers/s390/crypto/vfio_ap_private.h |   30 +-
 6 files changed, 1418 insertions(+), 437 deletions(-)
```
