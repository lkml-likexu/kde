#### [Patch v5 1/2] cgroup: svm: Add Encryption ID controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12024543
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2CCB8C433E0
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:33:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E01F6238D6
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:33:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727964AbhAPCc7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 21:32:59 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50602 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725781AbhAPCc6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 21:32:58 -0500
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 90BEDC061795
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 18:32:17 -0800 (PST)
Received: by mail-qt1-x849.google.com with SMTP id l7so9057177qth.15
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 18:32:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=bBcMZzMcXgUU9mEbbNH+yQZtvn8W3c9CVOe1v78v/l0=;
        b=BXpCgaj1z13jX8PFSV9vfl56vj0cupr/qQWq2nrGwVm0Ugjb2dXkoImGRRLbBxtOCI
         +n50jVjofl2eEmiFAhz2KgNI96ANx5BCTHFTwzosvSCAyfJQVv/HVutz6KfDxwaJVl/R
         hS1l/su0tJy+Smv4bM3EzIEnNcXBFOcnHADkZ3BFxTvOCmLQAdscD+XtG+gCDnF8GIt6
         4QzIEEN1wzR5lQilKhN/qrgQFuKBNiFlz6UdoYBBfFCdpRx2M1X8z3fUd2GypohF4bta
         KsUESPpdtSFa84HT/2PkhIonihTmA4uuvZ1nuUbkg0h5xOcV9pSlOqzRC4OW1JPuQgWp
         qSvg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=bBcMZzMcXgUU9mEbbNH+yQZtvn8W3c9CVOe1v78v/l0=;
        b=jx9Dd/FRToPhuTl5fHlgpLJKlj7kSHgYpHn7NAAgRx9aOw0xW5aTIN6hGL4bnrJ100
         ve1SFzytCyYzkgDgFbxtLYzOoAfeIGQVH2bwhtnO3Sy6bByEQkKipOg2UM/ycWruwnPh
         kZWt7U7Z1SCU+YO7FzXpX5PqYkaUK4UE/iL2J+fKOi/m7RWirUBTxSjsJkOzO9R8wsFM
         ikty/R3kov7mh+JkQgpZzMCIueMJeh45DVBUMT9ZP7xQ1pe8X2dmPEKQNUGOxQVZW8us
         3ht8LYe/PfoK+z4SBIhxUJWjQRvWxjLztsWKzJkCuxgEz/qOC/YqLNWD8CtWLXbLR9XL
         TlNA==
X-Gm-Message-State: AOAM531PSrFsFPOCd7UyPl5amTwOnUlDaWqZVMdhAcfOhXN52W0CCAuG
        4Dh8dA5hEjYbvr98ssMl+P0ImHv6lcFl
X-Google-Smtp-Source: 
 ABdhPJxE92pJV4Cs1Cq8RCacskmfNxRDYdi9Zk03+a1Tjoc+Y2IQ4wVS97LCjypd/8NHqel8d3+EC98gAzuX
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:ad4:4431:: with SMTP id
 e17mr14732338qvt.21.1610764336750; Fri, 15 Jan 2021 18:32:16 -0800 (PST)
Date: Fri, 15 Jan 2021 18:32:03 -0800
In-Reply-To: <20210116023204.670834-1-vipinsh@google.com>
Message-Id: <20210116023204.670834-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20210116023204.670834-1-vipinsh@google.com>
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [Patch v5 1/2] cgroup: svm: Add Encryption ID controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, hannes@cmpxchg.org, frankja@linux.ibm.com,
        borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hardware memory encryption is available on multiple generic CPUs. For
example AMD has Secure Encrypted Virtualization (SEV) and SEV -
Encrypted State (SEV-ES).

These memory encryptions are useful in creating encrypted virtual
machines (VMs) and user space programs.

There are limited number of encryption IDs that can be used
simultaneously on a machine for encryption. This generates a need for
the system admin to track, limit, allocate resources, and optimally
schedule VMs and user workloads in the cloud infrastructure. Some
malicious programs can exhaust all of these resources on a host causing
starvation of other workloads.

Encryption ID controller allows control of these resources using
Cgroups.

Controller is enabled by CGROUP_ENCRYPTION_IDS config option.
Encryption controller provide 3 interface files for each encryption ID
type. For example, in SEV:

1. encids.sev.max
	Sets the maximum usage of SEV IDs in the cgroup.
2. encids.sev.current
	Current usage of SEV IDs in the cgroup and its children.
3. encids.sev.stat
	Shown only at the root cgroup. Displays total SEV IDs available
	on the platform and current usage count.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
Reviewed-by: Dionna Glaze <dionnaglaze@google.com>
Acked-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/kvm/svm/sev.c                |  52 +++-
 include/linux/cgroup_subsys.h         |   4 +
 include/linux/encryption_ids_cgroup.h |  72 +++++
 include/linux/kvm_host.h              |   4 +
 init/Kconfig                          |  14 +
 kernel/cgroup/Makefile                |   1 +
 kernel/cgroup/encryption_ids.c        | 421 ++++++++++++++++++++++++++
 7 files changed, 556 insertions(+), 12 deletions(-)
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c

```
#### [PATCH 1/3 v2] nSVM: Check addresses of MSR and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12024541
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 54F36C433DB
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:23:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 015FE2256F
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 02:23:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728698AbhAPCXg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 21:23:36 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:49876 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725833AbhAPCXg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 21:23:36 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10G24taN125791;
        Sat, 16 Jan 2021 02:22:52 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=GiA7Wx2KS5t1Hb9isnMosVuN4QXjqyqUQrz7pk10Szc=;
 b=r3MccLJyUQGpl8CzidwLbMJoRNEUpPNmx8eqjgGfsYCw5QUJyhCOmU1ruRwkYZ3moTnr
 SQXmhMP0BVRSKb5lvS6MRqssU++LSiQ1CbkjSUutnKxyo4xvzIZFD8PEciljzK2nrHf1
 PgFrnNsPz9BQ4UwoKOWVsnGEgxNnPXd1DITKEUe5ZH/7Av6hOmSXdclIsG2+8WHsHOcU
 IqjMU82FPBrXpJqDvUa5lQ1mkgvY9WXab8dFhVsDDDGsHeysaQDVDFT2L7m8oTtO7zq3
 rhAjQPdaC4GbrJ+11dAOCIe2htpamPIpyq4K21f9YbKXaCifkj9UZBuMprC113dV3s6W 1g==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 363nna83jp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 16 Jan 2021 02:22:52 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10G26M3w194851;
        Sat, 16 Jan 2021 02:20:52 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3020.oracle.com with ESMTP id 360kebux94-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 16 Jan 2021 02:20:51 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 10G2KoZO019555;
        Sat, 16 Jan 2021 02:20:50 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 15 Jan 2021 18:20:50 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/3 v2] nSVM: Check addresses of MSR and IO bitmap
Date: Sat, 16 Jan 2021 02:20:37 +0000
Message-Id: <20210116022039.7316-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210116022039.7316-1-krish.sadhukhan@oracle.com>
References: <20210116022039.7316-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9865
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 suspectscore=0 spamscore=0
 mlxlogscore=999 malwarescore=0 bulkscore=0 mlxscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101160010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9865
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 impostorscore=0
 spamscore=0
 mlxlogscore=999 clxscore=1015 bulkscore=0 adultscore=0 lowpriorityscore=0
 suspectscore=0 phishscore=0 mlxscore=0 malwarescore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101160010
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol 2,
the following guest state is illegal:

        "The MSR or IOIO intercept tables extend to a physical address that
         is greater than or equal to the maximum supported physical address."

Also check that these addresses are aligned on page boundary.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/nested.c | 18 ++++++++++++------
 1 file changed, 12 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: update depracated and inappropriate jump label API
##### From: Cun Li <cun.jia.li@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cun Li <cun.jia.li@gmail.com>
X-Patchwork-Id: 12024609
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9DEEC433DB
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 05:52:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AACF0221E2
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 05:52:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725899AbhAPFw1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 16 Jan 2021 00:52:27 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36710 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725767AbhAPFw0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 16 Jan 2021 00:52:26 -0500
Received: from mail-pl1-x636.google.com (mail-pl1-x636.google.com
 [IPv6:2607:f8b0:4864:20::636])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6294FC061757;
        Fri, 15 Jan 2021 21:51:46 -0800 (PST)
Received: by mail-pl1-x636.google.com with SMTP id x18so5807683pln.6;
        Fri, 15 Jan 2021 21:51:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=kJi8OyxBgJcmL4B472BQ0mzfLLWlPkT298GTPpTLjcA=;
        b=MQPEHpzZhuo0F9dqSaZPlcyUZIR0JKOP39ow70obWFY8IaxAwpUeak0QPJmG99bgRJ
         rBS/QfhW9ezk7B7Q8rlaFlsC7t4JRcbTAXzHyhWVztHbkRMzeIRxoYoq6FFfV7hzaNL3
         NaFT/FuuisnGWN59a6PocAnBAAjsd7Us06C1mmnJvMTcNzW9iFcaJsRPTJW+TTL5OLrJ
         EX5155ihjtMLEctBP3CIDAAOsEDzbWd2RlPktF2tRl0tUsaRyq+qc6yzcUU7wN6/fAj9
         QxX/gbPHElc9wBRLoQKA//LMlEyHhMhQAVWrmoHaYHT1jB/g8daOWJZrjkbFj9yBYirc
         zQuQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=kJi8OyxBgJcmL4B472BQ0mzfLLWlPkT298GTPpTLjcA=;
        b=oFZEt4ulZXNuBbYIEhjC7M93B5/fnjBe2u1GByj0lwoVFbHizBMU0A0yLcVUiQ0KRZ
         RFYnHaPB5aOe2njYL8Uqec0ubn3q+Qr4hfgc9kqRfE7b/Hdtk0Vmo7369I1HkPHqylST
         5T4YF1UmaKtXXGGM2OK5nzGObPhLUUE8S8wmk0KHmrR46niBt4dvcAwEiZGV70s7yVMp
         RzlJ87Udm96lS7owPJmn9/VwRYnwZdHGvkvcD9SCEZ7nhO8/RRZideSO9cRgYvY3DAe4
         5UxyGyHHa4mAY/fX/grSlRCRX1xxLTe0tj99AYL6wsI3vbBVh4DryvzryGk3RrbDH5yX
         KogA==
X-Gm-Message-State: AOAM532vwRCN8kHhk3O4o/dFOZlDzxrH6v1WKP9160BQ0SPiK28XU9pl
        ZuvoyfR0FFT98vnOAQtgtab7UoUZ9zB6bdAT
X-Google-Smtp-Source: 
 ABdhPJzpVgI2SDFxZr1C5Lo/baIDflCfeNcbWY7iuaozCumA2ar1xjeb66bG3LuL6byqpTDjxPk/7w==
X-Received: by 2002:a17:90a:13c8:: with SMTP id
 s8mr14696288pjf.6.1610776305616;
        Fri, 15 Jan 2021 21:51:45 -0800 (PST)
Received: from thinkerpad.loongson.cn ([114.242.206.180])
        by smtp.gmail.com with ESMTPSA id
 4sm10242052pjn.14.2021.01.15.21.51.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 15 Jan 2021 21:51:44 -0800 (PST)
From: Cun Li <cun.jia.li@gmail.com>
To: vkuznets@redhat.com
Cc: pbonzini@redhat.com, seanjc@google.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Cun Li <cun.jia.li@gmail.com>
Subject: [PATCH] KVM: update depracated and inappropriate jump label API
Date: Sat, 16 Jan 2021 13:50:09 +0800
Message-Id: <20210116055009.118377-1-cun.jia.li@gmail.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <87h7nn8ke8.fsf@vitty.brq.redhat.com>
References: <87h7nn8ke8.fsf@vitty.brq.redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The use of 'struct static_key' and 'static_key_false' is
deprecated. Use the new API.

mmu_audit_key can only be true or false so it would be nice to use
static_branch_enable()/static_branch_disable() for it and not
static_key_slow_inc()/static_key_slow_dec().

Signed-off-by: Cun Li <cun.jia.li@gmail.com>
---
 arch/x86/kvm/lapic.h         | 6 +++---
 arch/x86/kvm/mmu/mmu_audit.c | 8 ++++----
 arch/x86/kvm/x86.c           | 6 +++---
 3 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: x86/MMU: Do not check unsync status for root SP.
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yu Zhang <yu.c.zhang@linux.intel.com>
X-Patchwork-Id: 12023237
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 72AF6C433DB
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 16:41:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EDD422473
	for <kvm@archiver.kernel.org>; Fri, 15 Jan 2021 16:41:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727162AbhAOQle (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 11:41:34 -0500
Received: from mga01.intel.com ([192.55.52.88]:47243 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726560AbhAOQle (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 11:41:34 -0500
IronPort-SDR: 
 X61q8rdyMaBJMgQGl8judovh7+fqShB3BxGyzrAn6o5dujqVj/CPg8fVHGFge5kW7uVOoeKOIc
 Br3XY1gCx+KQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9864"; a="197242510"
X-IronPort-AV: E=Sophos;i="5.79,349,1602572400";
   d="scan'208";a="197242510"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jan 2021 08:39:47 -0800
IronPort-SDR: 
 RrEB2VPQ6fmVivwsyoWos3bubN3OdgSMLVj/pIs2xh2DeSGw07aXxNksiS65+g4n7oEugX9lyP
 uJmyM3VgL68w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,349,1602572400";
   d="scan'208";a="354358704"
Received: from zhangyu-optiplex-7040.bj.intel.com ([10.238.154.148])
  by fmsmga008.fm.intel.com with ESMTP; 15 Jan 2021 08:39:45 -0800
From: Yu Zhang <yu.c.zhang@linux.intel.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org
Subject: [PATCH] KVM: x86/MMU: Do not check unsync status for root SP.
Date: Sat, 16 Jan 2021 08:21:00 +0800
Message-Id: <20210116002100.17339-1-yu.c.zhang@linux.intel.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In shadow page table, only leaf SPs may be marked as unsync.
And for non-leaf SPs, we use unsync_children to keep the number
of the unsynced children. In kvm_mmu_sync_root(), sp->unsync
shall always be zero for the root SP, hence no need to check it.

Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] x86/sev: Add AMD_SEV_ES_GUEST Kconfig for including SEV-ES support
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12024421
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 000D4C433E6
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 00:26:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B95F023B03
	for <kvm@archiver.kernel.org>; Sat, 16 Jan 2021 00:26:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726282AbhAPA0Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 15 Jan 2021 19:26:25 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51810 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725833AbhAPA0X (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 Jan 2021 19:26:23 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 79DC4C061757
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 16:25:43 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id m203so8911261ybf.1
        for <kvm@vger.kernel.org>; Fri, 15 Jan 2021 16:25:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=5Xh+0MnLMzYI0OJ8focr3Akua/pV4W8qCz0oH6KGf6w=;
        b=hqcOGOcqHtxF4SnZ8IdhBD0El88pZXu5Sh/jtw/dh2D65OMKUIJzci97KAo9TluJ1e
         h8qnZEZbbSSnA/atSXXdcED1KYGg382zH8lMBuUs8HJ83SRZoWk5T8x++Qxq9oxcYE1s
         8omOgMFfeWfVqRGYltLeX/2N2AG3IxrYt38oADCknHzbuJEjELxewjcErG+RA0wUjXtg
         5oY0uAj88fonQXJQnnN2hNTkYmQDnc9bJ2fGtyeYn2RT4IVmP972afBiCKb4Mddr/5hQ
         p/xYTNvYjjxEcS8uREXEG2KfGMiBfTlTNLbgLWo46izmWiZgjDOuuMPP7aUWTteQbTqz
         fb7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=5Xh+0MnLMzYI0OJ8focr3Akua/pV4W8qCz0oH6KGf6w=;
        b=IHw1ii90K97L387cLVQPKCEOytm+1UkV0udx5SnTfyMWx7sWw74xrCXN3t2Zv7Ojoa
         p5srnag1ua55Dz+d2vgom5qImXFueBt+UlFoCNSCzKRxreAizm8Ib+YYlLqFZFsYduz0
         qd7gsnZeAxi/LqN/WXycfF9LwZOMD6P7OxP+X5/qObbEbrmJgSLelZCYDURLpvgSnWiB
         z2llz/7Dl8uoT6ezVgLOcxQeLZtk7TaUtvEYpYr8juffrAEBlLH1hifSN9Q9TSr4L54B
         imXYgjMNdZ2hdVpgNXzwWiaocktwI021tJbURURV6mClmbUbWCeMWMi4wF4FI77CADL5
         x7NQ==
X-Gm-Message-State: AOAM530dwWkTk3bWoZiffG5/7Dz9TsWHimvRrdW1vS6kieVmZOOLsKaI
        JpvHQHH1tOLvSDDBPyGKW21Q/KiOqKM=
X-Google-Smtp-Source: 
 ABdhPJxB0ixWeqKwE7tvB5HHmo61Ym+cn/1dJzvX7nOcfKy5rG+t4qqYwh1Gc0aWidOlzYZgerEB65GJeKM=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:1241:: with SMTP id
 62mr22331296ybs.366.1610756742619;
 Fri, 15 Jan 2021 16:25:42 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 15 Jan 2021 16:25:17 -0800
Message-Id: <20210116002517.548769-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH] x86/sev: Add AMD_SEV_ES_GUEST Kconfig for including SEV-ES
 support
From: Sean Christopherson <seanjc@google.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, Andy Lutomirski <luto@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a new Kconfig, AMD_SEV_ES_GUEST, to control the inclusion of
support for running as an SEV-ES guest.  Pivoting on AMD_MEM_ENCRYPT for
guest SEV-ES support is undesirable for host-only kernel builds as
AMD_MEM_ENCRYPT is also required to enable KVM/host support for SEV and
SEV-ES.

A dedicated Kconfig also makes it easier to understand exactly what is
and isn't support in a given configuration.

Opportunistically update the AMD_MEM_ENCRYPT help text to note that it
also enables support for SEV guests.

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

Tested everything except an actual SEV-ES guest, I don't yet have a
workflow for testing those.

 arch/x86/Kconfig                           | 13 ++++++++++++-
 arch/x86/boot/compressed/Makefile          |  2 +-
 arch/x86/boot/compressed/idt_64.c          |  7 ++++---
 arch/x86/boot/compressed/idt_handlers_64.S |  2 +-
 arch/x86/boot/compressed/misc.h            |  5 ++++-
 arch/x86/entry/entry_64.S                  |  2 +-
 arch/x86/include/asm/idtentry.h            |  2 +-
 arch/x86/include/asm/mem_encrypt.h         | 12 ++++++++----
 arch/x86/include/asm/realmode.h            |  4 ++--
 arch/x86/include/asm/sev-es.h              |  2 +-
 arch/x86/kernel/Makefile                   |  2 +-
 arch/x86/kernel/head64.c                   |  6 +++---
 arch/x86/kernel/head_64.S                  |  6 +++---
 arch/x86/kernel/idt.c                      |  2 +-
 arch/x86/kernel/kvm.c                      |  4 ++--
 arch/x86/mm/mem_encrypt.c                  |  2 ++
 arch/x86/realmode/rm/header.S              |  2 +-
 arch/x86/realmode/rm/trampoline_64.S       |  4 ++--
 18 files changed, 50 insertions(+), 29 deletions(-)

```
