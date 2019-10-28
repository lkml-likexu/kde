#### [PATCH] KVM: arm/arm64: show halt poll counters in debugfs
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11214053
Return-Path: <SRS0=1Wg7=YU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F4B313B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Oct 2019 08:20:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1536C20873
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Oct 2019 08:20:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726579AbfJ0IUM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 27 Oct 2019 04:20:12 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:20930 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726002AbfJ0IUL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 27 Oct 2019 04:20:11 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9R8CXsp096943;
        Sun, 27 Oct 2019 04:20:00 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vvgy24um5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sun, 27 Oct 2019 04:19:59 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.27/8.16.0.27) with SMTP id x9R8Chbv097267;
        Sun, 27 Oct 2019 04:19:59 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vvgy24uky-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sun, 27 Oct 2019 04:19:59 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x9R8Gse5015131;
        Sun, 27 Oct 2019 08:19:58 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma04wdc.us.ibm.com with ESMTP id 2vvds6gxpk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sun, 27 Oct 2019 08:19:58 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9R8JvEr24248630
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sun, 27 Oct 2019 08:19:57 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A73706E050;
        Sun, 27 Oct 2019 08:19:57 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EE2FB6E04E;
        Sun, 27 Oct 2019 08:19:55 +0000 (GMT)
Received: from oc7455500831.ibm.com (unknown [9.145.36.74])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Sun, 27 Oct 2019 08:19:55 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Marc Zyngier <maz@kernel.org>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH] KVM: arm/arm64: show halt poll counters in debugfs
Date: Sun, 27 Oct 2019 09:19:50 +0100
Message-Id: <1572164390-5851-1-git-send-email-borntraeger@de.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-27_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=567 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910270086
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARM/ARM64 has counters halt_successful_poll, halt_attempted_poll,
halt_poll_invalid, and halt_wakeup but never exposed those in debugfs.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
This patch is untested
 arch/arm/kvm/guest.c   | 4 ++++
 arch/arm64/kvm/guest.c | 4 ++++
 2 files changed, 8 insertions(+)

```
#### [PATCH] KVM: vmx, svm: always run with EFER.NXE=1 when shadow paging is active
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11214173
Return-Path: <SRS0=1Wg7=YU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C780B13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Oct 2019 15:23:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A425721850
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Oct 2019 15:23:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="IpzaTN65"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727269AbfJ0PXa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 27 Oct 2019 11:23:30 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:42272 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726682AbfJ0PX3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 27 Oct 2019 11:23:29 -0400
Received: by mail-wr1-f67.google.com with SMTP id r1so7274644wrs.9;
        Sun, 27 Oct 2019 08:23:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=6igW15FTNZ7FtCx0WIgyCMA7DFyAcrqLMXtjwXRNmLA=;
        b=IpzaTN653x/VMl1PRi17h+qZEKf0SkYms86/7yjWeyCLKorH0aA4rIJZCOEtoKR7hs
         zXrChV5UqjC6nwsIt8LeW3HgC7I/FAAQwcftiLpA88QJp7Dt/j/0XSsWXC6/kffekQ33
         b4bHt4zO7n/L0w6m7irP8CA50P0yGXoyQTigACshScNaWvf65llgJp1MYokVU1l5wKzQ
         td4WcUNEzvSZyU9tgSrCNxod3e6IJg45eGAt9p5cJtn/KaRUyr5/IKeMxs2gKQHjoyfC
         tE/WhkzB9IFfyFXbE+k0F3GHieLdiFZSKc/eu639a1+DK/RhB3AJMyZFcpykePl+CuFz
         A5ag==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=6igW15FTNZ7FtCx0WIgyCMA7DFyAcrqLMXtjwXRNmLA=;
        b=a7I6mdG2Ii8T6JZwmVObw1kt8jpLpX+AmEVyfNmbxwPkTPuDHanA6GriDwvt9s6A2e
         DoJrRKubbGprhe7Wcita7Dc18RVoH8E0y2Wx7KPK4ZHYv1efbIh34nWOpwPBBs/dVbfc
         ao/T8xGLQdxXgbWyCsIoUW/XEE+MkC8uYhIJngvU4g1HuG4ch9+lx8w0Mg1EPHOWfoTt
         AWaJmOuNjPXhmpway7XEYLaUK1AF/lVvmJc8AlWu341x7FuF+MJibEHUBcYHArnSor74
         QvPqJlPJ3mvxd0YGtL3uLX2Vcf0gfJEW/oYjrTqSm/SxUIgMEkt8VRDXiKsmWIbW1WMT
         pXNQ==
X-Gm-Message-State: APjAAAU/oWc0kr74xNqEAkyJXGgjQ/2JPp3+tO21+5rnEyvfeH31E52B
        6qVCYummTVXdEyeoOQvsZDL8frQt
X-Google-Smtp-Source: 
 APXvYqyUIc8eYKFqH39Ikktps0DnWgYsp2ek8Y5cJ/Z2DcRo5ITOuExB++Squxhm8XxeSkzWItMuWw==
X-Received: by 2002:adf:f4cb:: with SMTP id
 h11mr12546506wrp.260.1572189806902;
        Sun, 27 Oct 2019 08:23:26 -0700 (PDT)
Received: from localhost.localdomain (mob-2-43-145-251.net.vodafone.it.
 [2.43.145.251])
        by smtp.gmail.com with ESMTPSA id
 z15sm8490315wrr.19.2019.10.27.08.23.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 27 Oct 2019 08:23:26 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: stable@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH] KVM: vmx,
 svm: always run with EFER.NXE=1 when shadow paging is active
Date: Sun, 27 Oct 2019 16:23:23 +0100
Message-Id: <20191027152323.24326-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMX already does so if the host has SMEP, in order to support the combination of
CR0.WP=1 and CR4.SMEP=1.  However, it is perfectly safe to always do so, and in
fact VMX already ends up running with EFER.NXE=1 on old processors that lack the
"load EFER" controls, because it may help avoiding a slow MSR write.  Removing
all the conditionals simplifies the code.

SVM does not have similar code, but it should since recent AMD processors do
support SMEP.  So this patch also makes the code for the two vendors more similar
while fixing NPT=0, CR0.WP=1 and CR4.SMEP=1 on AMD processors.

Cc: stable@vger.kernel.org
Cc: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c     | 10 ++++++++--
 arch/x86/kvm/vmx/vmx.c | 14 +++-----------
 2 files changed, 11 insertions(+), 13 deletions(-)

```
#### [PATCH v1 1/8] KVM: x86: Add base address parameter for get_fixed_pmc function
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Luwei Kang <luwei.kang@intel.com>
X-Patchwork-Id: 11214059
Return-Path: <SRS0=1Wg7=YU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A9B4113BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Oct 2019 11:12:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 91C1020717
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 27 Oct 2019 11:12:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726800AbfJ0LMe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 27 Oct 2019 07:12:34 -0400
Received: from mga02.intel.com ([134.134.136.20]:12491 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726469AbfJ0LMe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 27 Oct 2019 07:12:34 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Oct 2019 04:12:33 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,236,1569308400";
   d="scan'208";a="282690140"
Received: from unknown (HELO snr.jf.intel.com) ([10.54.39.141])
  by orsmga001.jf.intel.com with ESMTP; 27 Oct 2019 04:12:31 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        x86@kernel.org, ak@linux.intel.com, thomas.lendacky@amd.com,
        peterz@infradead.org, acme@kernel.org, mark.rutland@arm.com,
        alexander.shishkin@linux.intel.com, jolsa@redhat.com,
        namhyung@kernel.org, Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH v1 1/8] KVM: x86: Add base address parameter for get_fixed_pmc
 function
Date: Sun, 27 Oct 2019 19:11:10 -0400
Message-Id: <1572217877-26484-2-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1572217877-26484-1-git-send-email-luwei.kang@intel.com>
References: <1572217877-26484-1-git-send-email-luwei.kang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PEBS output to Inte PT introduces some new MSRs(MSR_RELOAD_FIXED_CTRx)
for fixed function counters that use for autoload the preset
value after writing out a PEBS event.

Introduce base MSRs address parameter to make this function can
get kvm performance monitor counter structure by
MSR_RELOAD_FIXED_CTRx registers.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/pmu.h           |  5 ++---
 arch/x86/kvm/vmx/pmu_intel.c | 14 +++++++++-----
 2 files changed, 11 insertions(+), 8 deletions(-)

```
