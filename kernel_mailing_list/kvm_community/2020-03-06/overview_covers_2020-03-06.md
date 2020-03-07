

#### [PATCH v1 0/3] PEBS virtualization enabling via DS in Qemu
##### From: Luwei Kang <luwei.kang@intel.com>

```c
From patchwork Fri Mar  6 10:20:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kang, Luwei" <luwei.kang@intel.com>
X-Patchwork-Id: 11422939
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D26C139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 02:21:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3211F2073B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 02:21:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726413AbgCFCVi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 21:21:38 -0500
Received: from mga18.intel.com ([134.134.136.126]:19708 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726178AbgCFCVh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 21:21:37 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Mar 2020 18:21:37 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,520,1574150400";
   d="scan'208";a="413742155"
Received: from snr.bj.intel.com ([10.240.193.90])
  by orsmga005.jf.intel.com with ESMTP; 05 Mar 2020 18:21:35 -0800
From: Luwei Kang <luwei.kang@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mst@redhat.com, marcel.apfelbaum@gmail.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org,
        Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH v1 0/3] PEBS virtualization enabling via DS in Qemu
Date: Fri,  6 Mar 2020 18:20:02 +0800
Message-Id: <1583490005-27761-1-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PEBS virtualization will be first supported on ICELAKE server.
This patchset introduce a new CPU parameter "pebs"(e.g.
"-cpu Icelake-Server,pmu=true,pebs=true") that use for enable PEBS
feature in KVM guest, and add the support for save/load PEBS MSRs.

Luwei Kang (3):
  i386: Add "pebs" parameter to enable PEBS feature
  i386: Add support for save/load PEBS MSRs
  i386: Add support for save/load IA32_PEBS_DATA_CFG MSR

 hw/i386/pc.c          |  1 +
 target/i386/cpu.c     | 14 ++++++++++++++
 target/i386/cpu.h     | 15 +++++++++++++++
 target/i386/kvm.c     | 43 +++++++++++++++++++++++++++++++++++++++++++
 target/i386/machine.c | 49 +++++++++++++++++++++++++++++++++++++++++++++++++
 5 files changed, 122 insertions(+)
```
#### [PATCH 0/7] tools/kvm_stat: add logfile support
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
From patchwork Fri Mar  6 11:42:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 11423657
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4240914B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 11:42:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2CA272084E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 11:42:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726565AbgCFLm6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 06:42:58 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:1270 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725827AbgCFLm6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Mar 2020 06:42:58 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 026BdqUB123878
        for <kvm@vger.kernel.org>; Fri, 6 Mar 2020 06:42:57 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yk4jpyrc1-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 06 Mar 2020 06:42:57 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <raspl@linux.ibm.com>;
        Fri, 6 Mar 2020 11:42:54 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 6 Mar 2020 11:42:53 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 026BgqHp59310254
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 6 Mar 2020 11:42:52 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4240D42041;
        Fri,  6 Mar 2020 11:42:52 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 195C242047;
        Fri,  6 Mar 2020 11:42:52 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  6 Mar 2020 11:42:52 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: rkrcmar@redhat.com, pbonzini@redhat.com
Subject: [PATCH 0/7] tools/kvm_stat: add logfile support
Date: Fri,  6 Mar 2020 12:42:43 +0100
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20030611-4275-0000-0000-000003A8F1EF
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20030611-4276-0000-0000-000038BE045B
Message-Id: <20200306114250.57585-1-raspl@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-06_03:2020-03-06,2020-03-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 mlxlogscore=906
 priorityscore=1501 lowpriorityscore=0 malwarescore=0 mlxscore=0
 impostorscore=0 clxscore=1011 spamscore=0 suspectscore=1 bulkscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003060084
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series provides a couple of new options to make logging to
files feasible.
Specifically, we add command line switches to specify an arbitrary time
interval for logging, and to toggle between a .csv and the previous
file format. Furthermore, we allow logging to files, where we utilize a
rotating set of 6 logfiles, each with its own header for easy post-
processing, especially when using .csv format.
Since specifying logfile size limits might be a non-trivial exercise,
we're throwing in yet another command line option that allows to
specify the minimum timeframe that should be covered by logs.
Finally, there's a minimal systemd unit file to deploy kvm_stat-based
logging in Linux distributions.
Note that the decision to write our own logfiles rather than to log to
e.g. systemd journal is a conscious one: It is effectively impossible to
write csv records into the systemd journal, the header will either
disappear after a while or has to be repeated from time to time, which
defeats the purpose of having a .csv format that can be easily post-
processed, etc.
See individual patch description for further details.


Stefan Raspl (7):
  tools/kvm_stat: rework command line sequence and message texts
  tools/kvm_stat: switch to argparse
  tools/kvm_stat: add command line switch '-s' to set update interval
  tools/kvm_stat: add command line switch '-c' to log in csv format
  tools/kvm_stat: add rotating log support
  tools/kvm_stat: add command line switch '-T'
  tools/kvm_stat: add sample systemd unit file

 tools/kvm/kvm_stat/kvm_stat         | 434 +++++++++++++++++++++-------
 tools/kvm/kvm_stat/kvm_stat.service |  15 +
 tools/kvm/kvm_stat/kvm_stat.txt     |  59 ++--
 3 files changed, 384 insertions(+), 124 deletions(-)
 create mode 100644 tools/kvm/kvm_stat/kvm_stat.service
```
#### [PATCH v3 0/2] KVM: VMX: cleanup VMXON region allocation
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Fri Mar  6 13:02:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11423841
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29AE4921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 13:02:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0AE34208CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 13:02:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZVZZH3KE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726533AbgCFNCX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 08:02:23 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23670 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726368AbgCFNCW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Mar 2020 08:02:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583499741;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=9kyJgQMNNTtILNB3efmK9JnspOevwrPmN1Q1JAEBpAU=;
        b=ZVZZH3KEegGKb7gGBcYxrD1JWwJZgUR40LY0l6V6CZ5GWKbBxGkXF5me4MNdvtLFxXyOnO
        uMLTlnP+WY7BUdW2olEkgFjRycF1yCfg6huR0F/cefB3UdPvV4S9P2ovGW/BaP43ynsYCB
        Vsyr6rnbDotfErU0C2CQJH6lp48NO5M=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-430-jUFJfcEZPgC7HIE4ySuW5A-1; Fri, 06 Mar 2020 08:02:19 -0500
X-MC-Unique: jUFJfcEZPgC7HIE4ySuW5A-1
Received: by mail-wm1-f71.google.com with SMTP id c18so865283wml.0
        for <kvm@vger.kernel.org>; Fri, 06 Mar 2020 05:02:19 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=9kyJgQMNNTtILNB3efmK9JnspOevwrPmN1Q1JAEBpAU=;
        b=M+Y+jLIQtQdDLsPfLofe97wJshvjW+QIzZmsbIWt9b6sPjB7SKca8/GmCAbG6pO9Qp
         1/1CuFvX0RYrR3mtvtpILGcOImzAfINqnat82zUWYPmxgu9Td/jlNCYTsUcf0nUtwj+9
         Kelg8cWq5bhxlANUcX9LU1L/R4H3qDPT64/2nE7yFLS58B++ZMaDB4j6EWme4LznfDZ7
         FruGAtQPBiI4mX1RBRHrIiL2o7EP7cal9VGQ8tex16qBmHQAPjOtz2CIumnDWonoDXqF
         b695BS1f6vqqjoPYlFKyKwURAkA1mRWcA9jaNOxgdjGElbfmX92U+bp7Rbe5K9akT5ZC
         7HkQ==
X-Gm-Message-State: ANhLgQ2YRBTdG5Q4xuUEpEeQlPU1l3O9BOO3ecTG7WJt5QetQP55j+cm
        c+XCCfm9H7w21mrENX8RUrjnCeP9erMVty273HES+pyrOA22aLBzB9JCbEcxGu2OcC6mdUTL2dO
        RI02nqF2E2MBt
X-Received: by 2002:adf:de0d:: with SMTP id b13mr3989698wrm.297.1583499738505;
        Fri, 06 Mar 2020 05:02:18 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vsKYoaK09agc4K6ttjmJfCHwezyd4P5yvpgDy7QZx84bx8Hc+dQIFutDBEvtnkB7At6SeYHAQ==
X-Received: by 2002:adf:de0d:: with SMTP id b13mr3989672wrm.297.1583499738253;
        Fri, 06 Mar 2020 05:02:18 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 i67sm26613243wri.50.2020.03.06.05.02.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 06 Mar 2020 05:02:17 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/2] KVM: VMX: cleanup VMXON region allocation
Date: Fri,  6 Mar 2020 14:02:13 +0100
Message-Id: <20200306130215.150686-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor cleanup with no functional change (intended):
- Rename 'kvm_area' to 'vmxon_region'
- Simplify setting revision_id for VMXON region when eVMCS is in use

Changes since v1:
- Pass 'enum vmcs_type' parameter to alloc_vmcs() too [Sean Christopherson <sean.j.christopherson@intel.com>]

Vitaly Kuznetsov (2):
  KVM: VMX: rename 'kvm_area' to 'vmxon_region'
  KVM: VMX: untangle VMXON revision_id setting when using eVMCS

 arch/x86/kvm/vmx/nested.c |  2 +-
 arch/x86/kvm/vmx/vmx.c    | 44 ++++++++++++++++++---------------------
 arch/x86/kvm/vmx/vmx.h    | 12 ++++++++---
 3 files changed, 30 insertions(+), 28 deletions(-)
```
#### [PATCH v3 0/5] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Fri Mar  6 16:39:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11424309
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 79404138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 16:39:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 59D292073D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 16:39:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LkGXvpX0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726873AbgCFQjL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 11:39:11 -0500
Received: from mail-wm1-f67.google.com ([209.85.128.67]:54823 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726751AbgCFQjL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Mar 2020 11:39:11 -0500
Received: by mail-wm1-f67.google.com with SMTP id i9so3171262wml.4;
        Fri, 06 Mar 2020 08:39:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rbE3tgX9IDkq6AOPA7A4EoyYR/J2nofK1ZsBKFjymL0=;
        b=LkGXvpX06maPjCBjn0DVOiVmp7mTGiFcWZPIO6OiAKfscrub3qXMJq8hha8ExqwbR7
         APRVJxtve78UPfSEpC6vIh36dmZUJfp9KmLK08FoIVhKSyTo1JT8ehVgq3Qy0G0sJY4p
         t0qiiMvn7nEqD0XM3s6lxy6o7QOGxGL83gVMCvpNFxTnd2Yv/pqQL5W/qaqb92Fu427R
         cMVzGBSLnnEKDgLa8eyAFcEOiPTcgXM0SnMd2d337cV4XvYrLc2T2E2AmNH7eKr2UHgM
         R8vl8IbZOTtI6ZzmT6dg9FQ6gXyyogqYWY0f7Pmrep721xWyFE+r4sJ5OhUm+qVo5sOF
         owRA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rbE3tgX9IDkq6AOPA7A4EoyYR/J2nofK1ZsBKFjymL0=;
        b=bN22h3friZ+PDZCa5J8l6brD3VDvrl0UIa8pReI6LS7Pa1knxoPbaFcZRnlhUxfJk2
         Q3TkZPiTa3k8dOMv+l67qrqSRMzjF0g6sVqmJ/Kmf2GnPgztn9ETlwiGOyHVF8OHQKfI
         1mEWfjx4ARt1KUED3a/y8sa3CPitzjna7gtzTbti7h+KDUrimBK4O7CVhci1BilLhRc6
         Qi0p2m32DrwE8vsE36odZMt3fpRgyJMA31pguZi/Gi+vNHPz1KA6Kq1JZsurATdfS24/
         VoK5sXwSBaoh46hlsEhAqZt4ABvbJmsJG6Pg4Ld6sj3h55IQHeoF0qn1EOkltugLrXX6
         DiGg==
X-Gm-Message-State: ANhLgQ2aOA+zwIBPlClW4lcvohpT4NUVUmMMKigE/IEuJs5Xn0XsAGEH
        MvJNXf3sMPVVvaFaPkuHyHU5QtTL
X-Google-Smtp-Source: 
 ADFU+vsjnUAaIK6l49ok4fI+XxVUgl1BAY7j37FFk3An892kplijaY+tUbx05ukFUzcibVLoqRnJ9g==
X-Received: by 2002:a7b:cc04:: with SMTP id f4mr4718806wmh.134.1583512748761;
        Fri, 06 Mar 2020 08:39:08 -0800 (PST)
Received: from linux.local ([199.203.162.213])
        by smtp.gmail.com with ESMTPSA id
 n24sm8812760wra.61.2020.03.06.08.39.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 06 Mar 2020 08:39:08 -0800 (PST)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v3 0/5] x86/kvm/hyper-v: add support for synthetic debugger
Date: Fri,  6 Mar 2020 18:39:04 +0200
Message-Id: <20200306163909.1020369-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

In the first patch the first mode is being implemented in the sense that
it simply exits to user-space when a control MSR is being written and
when the pending MSR is being set, then it's up-to userspace to
implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

Jon Doron (5):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |  26 +++++
 arch/x86/include/asm/kvm_host.h    |  13 +++
 arch/x86/kvm/hyperv.c              | 161 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |   5 +
 arch/x86/kvm/trace.h               |  48 +++++++++
 arch/x86/kvm/x86.c                 |   9 ++
 include/uapi/linux/kvm.h           |  11 ++
 7 files changed, 271 insertions(+), 2 deletions(-)
```
