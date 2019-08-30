

#### [PATCH v2 0/4] KVM: selftests: Introduce VM_MODE_PXXV48_4K
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Thu Aug 29 02:21:13 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11120205
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 239A7112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 02:21:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0C9872077B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 02:21:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726330AbfH2CVa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 22:21:30 -0400
Received: from mx1.redhat.com ([209.132.183.28]:49228 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726079AbfH2CVa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 22:21:30 -0400
Received: from mail-pl1-f199.google.com (mail-pl1-f199.google.com
 [209.85.214.199])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 65706811DE
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 02:21:30 +0000 (UTC)
Received: by mail-pl1-f199.google.com with SMTP id p9so1120534pls.18
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 19:21:30 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=F0ntCxjTGtKbzFXJg3nlEr8z4Qg5JGGVYpSbuyABl2w=;
        b=c2BM2RLpsj7vnm7gv+7Lx3xX7Qsl5nTo7E7cP8Rvnb6ikVUvlpb3tQrssdq6MJk8MU
         V5gIkFvB8IgqS3bQL5mntzf0aBbmbVs4a3BItg36s/hje48vXivsnMMr1+4DcXAJ1dEH
         cm3eXFPl+S0+vhdGnPkKYY/SiZEPogEB5WmbdCD8e/uTRsA1KcwDZ33oxe1+hUfuNceL
         jTEd92tGomH4r2dFN/UgyaCLqP91W2zBTGnqOxnExCE8HDnhsOXORfjA3gTBxj6Nyydq
         Fsl9QQl63vxM2N9zrqY94RknD0UxryASGcNETeyaJ/4F/ZDnj7JXGZAFvwMtnSUmXFRr
         NMcA==
X-Gm-Message-State: APjAAAUi0eBElkuBXm1eQuxPfW4jX5t1wEgMn0INB4Ifsh4aPssLMJSA
        Ka2PvzjAgIYJ1seStqg0rvY/Ls+Kd1UX2l3UShEU2y2kdwotW/TOB2d1INH/Pc9MLP7u4sAWtk9
        7W74nC9loEOvK
X-Received: by 2002:a17:902:6a82:: with SMTP id
 n2mr7070926plk.53.1567045289861;
        Wed, 28 Aug 2019 19:21:29 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzMezApsFpPfMPo0+CoJhPhtkIA4wIFy3VnvhRI32O80EhZ8+FMosGoBfvA+xbB/1GKt6+MhA==
X-Received: by 2002:a17:902:6a82:: with SMTP id
 n2mr7070908plk.53.1567045289670;
        Wed, 28 Aug 2019 19:21:29 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 j187sm750140pfg.178.2019.08.28.19.21.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 28 Aug 2019 19:21:28 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>,
 peterx@redhat.com
Subject: [PATCH v2 0/4] KVM: selftests: Introduce VM_MODE_PXXV48_4K
Date: Thu, 29 Aug 2019 10:21:13 +0800
Message-Id: <20190829022117.10191-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- pick r-bs
- rebased to master
- fix pa width detect, check cpuid(1):edx.PAE(bit 6)
- fix arm compilation issue [Drew]
- fix indents issues and ways to define macros [Drew]
- provide functions for fetching cpu pa/va bits [Drew]

This series originates from "[PATCH] KVM: selftests: Detect max PA
width from cpuid" [1] and one of Drew's comments - instead of keeping
the hackish line to overwrite guest_pa_bits all the time, this series
introduced the new mode VM_MODE_PXXV48_4K for x86_64 platform.

The major issue is that even all the x86_64 kvm selftests are
currently using the guest mode VM_MODE_P52V48_4K, many x86_64 hosts
are not using 52 bits PA (and in most cases, far less).  If with luck
we could be having 48 bits hosts, but it's more adhoc (I've observed 3
x86_64 systems, they are having different PA width of 36, 39, 48).  I
am not sure whether this is happening to the other archs as well, but
it probably makes sense to bring the x86_64 tests to the real world on
always using the correct PA bits.

A side effect of this series is that it will also fix the crash we've
encountered on Xeon E3-1220 as mentioned [1] due to the
differenciation of PA width.

With [1], we've observed AMD host issues when with NPT=off.  However a
funny fact is that after I reworked into this series, the tests can
instead pass on both NPT=on/off.  It could be that the series changes
vm->pa_bits or other fields so something was affected.  I didn't dig
more on that though, considering we should not lose anything.

[1] https://lkml.org/lkml/2019/8/26/141

Peter Xu (4):
  KVM: selftests: Move vm type into _vm_create() internally
  KVM: selftests: Create VM earlier for dirty log test
  KVM: selftests: Introduce VM_MODE_PXXV48_4K
  KVM: selftests: Remove duplicate guest mode handling

 tools/testing/selftests/kvm/dirty_log_test.c  | 79 +++++--------------
 .../testing/selftests/kvm/include/kvm_util.h  | 16 +++-
 .../selftests/kvm/include/x86_64/processor.h  |  3 +
 .../selftests/kvm/lib/aarch64/processor.c     |  3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 67 ++++++++++++----
 .../selftests/kvm/lib/x86_64/processor.c      | 30 ++++++-
 6 files changed, 119 insertions(+), 79 deletions(-)
```
#### [RFC v1 0/9] PEBS enabling in KVM guest
##### From: Luwei Kang <luwei.kang@intel.com>

```c
From patchwork Thu Aug 29 05:34:00 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kang, Luwei" <luwei.kang@intel.com>
X-Patchwork-Id: 11120323
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65ED714D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:38:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4811C22CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:38:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727307AbfH2Fio (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 01:38:44 -0400
Received: from mga07.intel.com ([134.134.136.100]:2355 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725847AbfH2Fio (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 01:38:44 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Aug 2019 22:38:43 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,442,1559545200";
   d="scan'208";a="210416043"
Received: from icl-2s.bj.intel.com ([10.240.193.48])
  by fmsmga002.fm.intel.com with ESMTP; 28 Aug 2019 22:38:40 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        x86@kernel.org, ak@linux.intel.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Luwei Kang <luwei.kang@intel.com>
Subject: [RFC v1 0/9] PEBS enabling in KVM guest
Date: Thu, 29 Aug 2019 13:34:00 +0800
Message-Id: <1567056849-14608-1-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel new hardware introduces some Precise Event-Based Sampling (PEBS)
extensions that output the PEBS record to Intel PT stream instead of
DS area. The PEBS record will be packaged in a specific format when
outputing to Intel PT.

This patch set will enable PEBS functionality in KVM Guest by PEBS
output to Intel PT. The native driver as [1] (still under review).

[1] https://www.spinics.net/lists/kernel/msg3215354.html

Luwei Kang (9):
  KVM: x86: Add base address parameter for get_fixed_pmc function
  KVM: x86: PEBS via Intel PT HW feature detection
  KVM: x86: Implement MSR_IA32_PEBS_ENABLE read/write emulation
  KVM: x86: Implement counter reload MSRs read/write emulation
  KVM: x86: Allocate performance counter for PEBS event
  KVM: x86: Add shadow value of PEBS status
  KVM: X86: Expose PDCM cpuid to guest
  KVM: X86: MSR_IA32_PERF_CAPABILITIES MSR emulation
  KVM: x86: Expose PEBS feature to guest

 arch/x86/include/asm/kvm_host.h  |  8 ++++
 arch/x86/include/asm/msr-index.h | 12 ++++++
 arch/x86/kvm/cpuid.c             |  3 +-
 arch/x86/kvm/pmu.c               | 57 ++++++++++++++++++++++----
 arch/x86/kvm/pmu.h               | 11 ++---
 arch/x86/kvm/pmu_amd.c           |  2 +-
 arch/x86/kvm/svm.c               | 12 ++++++
 arch/x86/kvm/vmx/capabilities.h  | 21 ++++++++++
 arch/x86/kvm/vmx/pmu_intel.c     | 88 +++++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/vmx/vmx.c           | 24 ++++++++++-
 arch/x86/kvm/x86.c               | 22 +++++++---
 11 files changed, 229 insertions(+), 31 deletions(-)
```
#### [PATCH v3 0/2] fix emulation error on Windows bootup
##### From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>

```c
From patchwork Thu Aug 29 08:23:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
X-Patchwork-Id: 11120627
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0717D1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:23:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D06CE2341C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:23:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="brQvV7Xa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726330AbfH2IXV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 04:23:21 -0400
Received: from mail-eopbgr10099.outbound.protection.outlook.com
 ([40.107.1.99]:44097
        "EHLO EUR02-HE1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725782AbfH2IXU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 04:23:20 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=M3ZYvM47F2+QioH738DfKf2/2FVmj0r+upFRboI03M8xCG/Q4ZIJM7PTnvg0f4IG6e0gnD315VB1ksMnYK/7ckDOMkaEUrwFpRuR4Q8x29qw1Ld/20QjqLz4h94ZIXQZ3a0wmYFFHKt+1HiODot/YLe13zg33mhTBIb88ODUqTeIzR0eiCn+F9M45eQROlcPZWtfX1wbxmU8w0WJUZV7qDgsPY0agMToWYY5K+FVmpNzaAz2UxwuHJJpMeOof0zDkHUa9npBoJcm7V0M2LtU/wiCy+hPYqK1ySuHw37y8Qvbi1TVwPeubo6fpgGoi5nAvNyy8BoocOne2tdXKjYjVw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=oOjr3QaL9caWv5QYfhTa9inH921VgNgBHYPoRqxQsqA=;
 b=YRf0y/U7fQo7cMJlcczVOYzPv5la5y9bgmPSF5A7Y2CGKEtM8dwIoqH6DYeK/EdSkkZX5eRqWo5WDpJIUmHhaGQnfJYxCK0AxtcwUwG1yK7o3+7LZRijNxh7SSHd/CwN0aqQ4mGrIdbOMdWAh3HFX+qvJQsGr3y88Hq3mD9UQyfdP9PazCoONvjWXlY6WIlRCcfEaYC/nYzbg3KHp1KPowlYnJRwX2ons9l2m4Z4Vtlq2H335FKo0VdkVeY1vZthbh2NCh0FV+BwIl6jBHxdIfNDQX3/wBze9qcKLjPsUGiArLN8+W0KNWlk0Un4Eci0frMHzUKqmAIBPwn+JX3/RQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=oOjr3QaL9caWv5QYfhTa9inH921VgNgBHYPoRqxQsqA=;
 b=brQvV7XaeCZZqlQfRUhCIX47h7yw+S0YnuH6dhaSPvNLUoIcmpDpmtL+DjCTwzsDhvrxbjiPJh+EXU7JlJWpliL4XnVPakA3JQtuZfh9TD79Kf146gRr7E6HwoTyxtbalLq6rjTbw0BGDT0Xy/Z371nGvEvtF/Es/UplU2lFvTw=
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com (10.170.236.143) by
 VI1PR08MB3342.eurprd08.prod.outlook.com (52.134.31.141) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2220.18; Thu, 29 Aug 2019 08:23:17 +0000
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a]) by VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a%3]) with mapi id 15.20.2178.023; Thu, 29 Aug 2019
 08:23:16 +0000
From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: Jan Dakinevich <jan.dakinevich@virtuozzo.com>,
 Denis Lunev <den@virtuozzo.com>, Roman Kagan <rkagan@virtuozzo.com>,
 Denis Plotnikov <dplotnikov@virtuozzo.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?iso-8859-2?q?Radim_Kr=E8m=E1=F8?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H. Peter Anvin" <hpa@zytor.com>,
 "x86@kernel.org" <x86@kernel.org>,
 "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v3 0/2] fix emulation error on Windows bootup
Thread-Topic: [PATCH v3 0/2] fix emulation error on Windows bootup
Thread-Index: AQHVXkMCmLX7ptsowU6uxciM+lstmw==
Date: Thu, 29 Aug 2019 08:23:16 +0000
Message-ID: <1567066988-23376-1-git-send-email-jan.dakinevich@virtuozzo.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: HE1PR05CA0274.eurprd05.prod.outlook.com
 (2603:10a6:3:fc::26) To VI1PR08MB2782.eurprd08.prod.outlook.com
 (2603:10a6:802:19::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=jan.dakinevich@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.1.4
x-originating-ip: [185.231.240.5]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 76af0b90-7fa4-4b8a-6405-08d72c5a2461
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(5600166)(711020)(4605104)(1401327)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(2017052603328)(7193020);SRVR:VI1PR08MB3342;
x-ms-traffictypediagnostic: VI1PR08MB3342:
x-ms-exchange-purlcount: 2
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <VI1PR08MB3342B6F9234F50F95F0987568AA20@VI1PR08MB3342.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:8882;
x-forefront-prvs: 0144B30E41
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(136003)(346002)(39850400004)(396003)(366004)(376002)(199004)(189003)(66476007)(66946007)(66556008)(966005)(50226002)(64756008)(66446008)(4744005)(2351001)(2501003)(36756003)(14454004)(8936002)(86362001)(66066001)(81156014)(81166006)(6436002)(5640700003)(6512007)(6306002)(71200400001)(71190400001)(44832011)(486006)(476003)(6916009)(5660300002)(52116002)(54906003)(14444005)(53936002)(102836004)(99286004)(2906002)(6486002)(478600001)(8676002)(6506007)(386003)(2616005)(26005)(186003)(7416002)(305945005)(4326008)(3846002)(25786009)(7736002)(256004)(6116002)(316002);DIR:OUT;SFP:1102;SCL:1;SRVR:VI1PR08MB3342;H:VI1PR08MB2782.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 NExFHAo7/g7fLIRFeE6GMtYfmWh94Odxs8IJlWd2zjSDh3Jq5L/f+6+ys98rfJ/ZYzrkSTpX/+5Q1bvKcSHopCv7xMIVjOrFfv5otXJxbomnJRg7d257y64mcSKYhouuMvMS1OhEcOQY2WIRz4ch2/iJJjepUqK8RElXpKiru5OLDncH8G4fCXBOoJtbnNMyVM4Z8bFqIEJ3LPsFAxZNs0QoJFhDuou7dtvBnXjtHXohXpA5/viiyXp7YYbsFvG1sR/QviGNrptykyexS0k/7u10q8j20pR5zioBQjq2Uc7vM76Vo2waz30g9+NW2BrwgWU0KrO5bPWHKBHGg0snDpXtzIaRdx7t/lENlskauZAhZAV/4EjCyg6pTh4QnaxYxREMiV1nSpYa3JCQ6lno7Gdd6FOV864V5/E/bvJI88U=
Content-Type: text/plain; charset="iso-8859-2"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 76af0b90-7fa4-4b8a-6405-08d72c5a2461
X-MS-Exchange-CrossTenant-originalarrivaltime: 29 Aug 2019 08:23:16.8203
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 tsNzXykSfnMB4/apFFWLx1tbrU1YdmJ5+J2pVLZ3iP3LQecUR5NraprvjkPwxueT+ssl0X8JHWWvOHgW5uLgdOtFpFP8QNEP+xUwCTmIj4E=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: VI1PR08MB3342
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intended to fix (again) a bug that was a subject of the 
following change:

  6ea6e84 ("KVM: x86: inject exceptions produced by x86_decode_insn")

Suddenly, that fix had a couple mistakes. First, ctxt->have_exception was 
not set if fault happened during instruction decoding. Second, returning 
value of inject_emulated_instruction was used to make the decision to 
reenter guest, but this could happen iff on nested page fault, that is not 
the scope where this bug could occur.

v1:
  https://lkml.org/lkml/2019/8/27/881

v2:
  https://lkml.org/lkml/2019/8/28/879

v3:
  - do sanity check in caller code
  - drop patch, that moved emulation_type() function

Jan Dakinevich (2):
  KVM: x86: always stop emulation on page fault
  KVM: x86: set ctxt->have_exception in x86_decode_insn()

 arch/x86/kvm/emulate.c | 2 ++
 arch/x86/kvm/x86.c     | 7 ++++++-
 2 files changed, 8 insertions(+), 1 deletion(-)
```
#### [PATCH kernel v3 0/5] powerpc/powernv/kvm: Invalidate multiple TCEs
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
From patchwork Thu Aug 29 08:52:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11120665
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DFAA14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:52:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 170F22339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:52:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726926AbfH2Iw5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 04:52:57 -0400
Received: from ozlabs.ru ([107.173.13.209]:49750 "EHLO ozlabs.ru"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726009AbfH2Iw5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 04:52:57 -0400
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id 6E65FAE80037;
        Thu, 29 Aug 2019 04:52:32 -0400 (EDT)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Alex Williamson <alex.williamson@redhat.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel v3 0/5] powerpc/powernv/kvm: Invalidate multiple TCEs
 at once
Date: Thu, 29 Aug 2019 18:52:47 +1000
Message-Id: <20190829085252.72370-1-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far TCE cache updates (IOMMU translation cache on POWER8/9
PHB/NPU units) were barely noticeable; however with 100+GB guests
we now see RCU stall warnings in guests because we spend too much
time in the host system firmware which does actual TCE cache
updates, hence this patchset.

This is a rework of
https://patchwork.ozlabs.org/patch/1149003/
https://patchwork.ozlabs.org/patch/1152985/ (cannot post link to the series
as it appears empty because of broken patchworks)

This depends on KVM-PPC's bugfix: https://patchwork.ozlabs.org/patch/1152937/

I expect 1/5 to go via the PPC tree, 2/5 via the KVM-PPC tree,
3/5 via the VFIO tree and the rest via the PPC tree.

Changes:
v3:
* added 4/5 to fix compile error from 5/5
* added "Book3S" to 2/5's subject line


This is based on sha1
42ac26d253eb Santosh Sivaraj "powerpc: add machine check safe copy_to_user".

Please comment. Thanks.



Alexey Kardashevskiy (5):
  powerpc/powernv/ioda: Split out TCE invalidation from TCE updates
  KVM: PPC: Book3S: Invalidate multiple TCEs at once
  vfio/spapr_tce: Invalidate multiple TCEs at once
  powerpc/pseries/iommu: Switch to xchg_no_kill
  powerpc/powernv/ioda: Remove obsolete iommu_table_ops::exchange
    callbacks

 arch/powerpc/include/asm/iommu.h          | 21 ++++++---
 arch/powerpc/kernel/iommu.c               | 23 ++++++----
 arch/powerpc/kvm/book3s_64_vio.c          | 29 ++++++++----
 arch/powerpc/kvm/book3s_64_vio_hv.c       | 38 +++++++++++----
 arch/powerpc/platforms/powernv/pci-ioda.c | 56 ++++-------------------
 arch/powerpc/platforms/pseries/iommu.c    |  5 +-
 drivers/vfio/vfio_iommu_spapr_tce.c       | 18 +++++---
 7 files changed, 99 insertions(+), 91 deletions(-)
```
#### [PATCH v2 0/6] Introduce variable length mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
From patchwork Thu Aug 29 11:18:58 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11121039
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3A5914F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 11:19:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B00423403
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 11:19:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728122AbfH2LTQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 07:19:16 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:43722 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728083AbfH2LTO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 07:19:14 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 29 Aug 2019 14:19:11 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x7TBJ8v1020002;
        Thu, 29 Aug 2019 14:19:09 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH v2 0/6] Introduce variable length mdev alias
Date: Thu, 29 Aug 2019 06:18:58 -0500
Message-Id: <20190829111904.16042-1-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20190826204119.54386-1-parav@mellanox.com>
References: <20190826204119.54386-1-parav@mellanox.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To have consistent naming for the netdevice of a mdev and to have
consistent naming of the devlink port [1] of a mdev, which is formed using
phys_port_name of the devlink port, current UUID is not usable because
UUID is too long.

UUID in string format is 36-characters long and in binary 128-bit.
Both formats are not able to fit within 15 characters limit of netdev
name.

It is desired to have mdev device naming consistent using UUID.
So that widely used user space framework such as ovs [2] can make use
of mdev representor in similar way as PCIe SR-IOV VF and PF representors.

Hence,
(a) mdev alias is created which is derived using sha1 from the mdev name.
(b) Vendor driver describes how long an alias should be for the child mdev
created for a given parent.
(c) Mdev aliases are unique at system level.
(d) alias is created optionally whenever parent requested.
This ensures that non networking mdev parents can function without alias
creation overhead.

This design is discussed at [3].

An example systemd/udev extension will have,

1. netdev name created using mdev alias available in sysfs.

mdev UUID=83b8f4f2-509f-382f-3c1e-e6bfe0fa1001
mdev 12 character alias=cd5b146a80a5

netdev name of this mdev = enmcd5b146a80a5
Here en = Ethernet link
m = mediated device

2. devlink port phys_port_name created using mdev alias.
devlink phys_port_name=pcd5b146a80a5

This patchset enables mdev core to maintain unique alias for a mdev.

Patch-1 Introduces mdev alias using sha1.
Patch-2 Ensures that mdev alias is unique in a system.
Patch-3 Exposes mdev alias in a sysfs hirerchy.
Patch-4 Introduces mdev_alias() API.
Patch-5 Updated sysfs documentation
Patch-6 Extends mtty driver to optionally provide alias generation.
This also enables to test UUID based sha1 collision and trigger
error handling for duplicate sha1 results.

[1] http://man7.org/linux/man-pages/man8/devlink-port.8.html
[2] https://docs.openstack.org/os-vif/latest/user/plugins/ovs.html
[3] https://patchwork.kernel.org/cover/11084231/
---
Changelog:
v1->v2:
 - Corrected a typo from 'and' to 'an'
 - Addressed comments from Alex Williamson
 - Kept mdev_device naturally aligned
 - Added error checking for crypt_*() calls
 - Moved alias NULL check at beginning
 - Added mdev_alias() API
 - Updated mtty driver to show example mdev_alias() usage
 - Changed return type of generate_alias() from int to char*
v0->v1:
 - Addressed comments from Alex Williamson, Cornelia Hunk and Mark Bloch
 - Moved alias length check outside of the parent lock
 - Moved alias and digest allocation from kvzalloc to kzalloc
 - &alias[0] changed to alias
 - alias_length check is nested under get_alias_length callback check
 - Changed comments to start with an empty line
 - Added comment where alias memory ownership is handed over to mdev device
 - Fixed cleaunup of hash if mdev_bus_register() fails
 - Updated documentation for new sysfs alias file
 - Improved commit logs to make description more clear
 - Fixed inclusiong of alias for NULL check
 - Added ratelimited debug print for sha1 hash collision error

Parav Pandit (6):
  mdev: Introduce sha1 based mdev alias
  mdev: Make mdev alias unique among all mdevs
  mdev: Expose mdev alias in sysfs tree
  mdev: Introduce an API mdev_alias
  mdev: Update sysfs documentation
  mtty: Optionally support mtty alias

 .../driver-api/vfio-mediated-device.rst       |   5 +
 drivers/vfio/mdev/mdev_core.c                 | 142 +++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h              |   5 +-
 drivers/vfio/mdev/mdev_sysfs.c                |  26 +++-
 include/linux/mdev.h                          |   5 +
 samples/vfio-mdev/mtty.c                      |  13 ++
 6 files changed, 186 insertions(+), 10 deletions(-)
```
#### [kvm-unit-tests PATCH 0/6] s390x: Add multiboot and smp
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Aug 29 12:14:53 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11121265
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99D3314F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:15:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 82BF22080F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:15:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727171AbfH2MPY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 08:15:24 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15180 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727061AbfH2MPY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Aug 2019 08:15:24 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TC7xAt090385
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 08:15:23 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2updvy1gra-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 08:15:22 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 29 Aug 2019 13:15:18 +0100
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 29 Aug 2019 13:15:17 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7TCFGkK45088842
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 12:15:16 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0C0AF52050;
        Thu, 29 Aug 2019 12:15:16 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.55.105])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id D2AA652057;
        Thu, 29 Aug 2019 12:15:14 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 0/6] s390x: Add multiboot and smp
Date: Thu, 29 Aug 2019 14:14:53 +0200
X-Mailer: git-send-email 2.17.0
X-TM-AS-GCONF: 00
x-cbid: 19082912-0012-0000-0000-000003443F0B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082912-0013-0000-0000-0000217E7F8C
Message-Id: <20190829121459.1708-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-29_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=775 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908290135
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cross testing emulated instructions has in the past brought up some
issues on all available IBM Z hypervisors. So let's upstream the last
part of multiboot: sclp interrupts and line mode console.

SMP tests are a great way to excercise external interruptions, cpu
resets and sigp. The smp library is always initialized and provides
very rudimentary CPU management for now.

Janosch Frank (6):
  s390x: Use interrupts in SCLP and add locking
  s390x: Add linemode console
  s390x: Add linemode buffer to fix newline on every print
  s390x: Add initial smp code
  s390x: Prepare for external calls
  s390x: SMP test

 lib/s390x/asm/arch_def.h  |  13 ++
 lib/s390x/asm/interrupt.h |   5 +
 lib/s390x/asm/sigp.h      |  29 +++-
 lib/s390x/interrupt.c     |  28 +++-
 lib/s390x/io.c            |   5 +-
 lib/s390x/sclp-console.c  | 243 +++++++++++++++++++++++++++++++---
 lib/s390x/sclp.c          |  54 +++++++-
 lib/s390x/sclp.h          |  59 ++++++++-
 lib/s390x/smp.c           | 272 ++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.h           |  51 +++++++
 s390x/Makefile            |   2 +
 s390x/cstart64.S          |   7 +
 s390x/smp.c               | 242 +++++++++++++++++++++++++++++++++
 13 files changed, 983 insertions(+), 27 deletions(-)
 create mode 100644 lib/s390x/smp.c
 create mode 100644 lib/s390x/smp.h
 create mode 100644 s390x/smp.c
```
#### [PATCH v6 00/21] KVM RISC-V Support
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
From patchwork Thu Aug 29 13:55:12 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11121355
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1565814E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 13:55:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D42C2215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 13:55:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="XSfhoHIl";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="npFXRh3T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727294AbfH2NzT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 09:55:19 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:35007 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727087AbfH2NzS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 09:55:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1567086917; x=1598622917;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=JS/Tsi4+P8HxOlIpZs7O+5vwS6yKHpjAv47A0OU0fUg=;
  b=XSfhoHIlvHszChAJuYjr+Emu+wIo7J79TWElT9jO+ZIbj6eYDGGbAMkB
   gKJw/QB/ToyDTVPQFRJ+VQ5Hgqmh9NX2ERWFoT9XO5LVV8D718id2r8pF
   JS065kSU0HIzdPe/1YqXiqz9f/wLfUCqmYgDnCqN4hMECkxw9ZWIdlGFX
   URXdlnwgQP0q8bR4NI8s26KJlG1fGjwSFbjZ+k53sQd1cxaBgt87vLneM
   3aUEPebS73p5XZcknAvwpxfGB6bJCEWeb06fBcZ0viodTGuLOCW1p3tPh
   FqfajEuRK/M0EEnQRrgcc5OxsEIFEKHnqnoc6Ozw5hQHWBbglrYAaWKUu
   Q==;
IronPort-SDR: 
 wzRquYKiZSp3sSWXbBLmh58I0NQjX1ZWiC5kBa+Hlc9XkOuv02ZdvKOLtR5kAE/0/+hG9JK+hq
 /tlzgGQnrAS9oV/P0FyJxp2Wb4zWsQ6xW6SHhvHBJKKvZ6z8KpWQVufKrUejv33skzTHSOtaDE
 DmMyA+Ok9d07rwJuKxbQqzIMh3DEznT35WZAkkcgQWbk7SEVsMQfJoBSKhkYOuV/HHbpBpZuMK
 sauPubLTeOKyNiwgBky6K2raBdBvhPbnOYbfbhIjKSuR+vnQ5LIcE5OhP8S2jlRuE4vUzsi6zK
 RSg=
X-IronPort-AV: E=Sophos;i="5.64,443,1559491200";
   d="scan'208";a="116951578"
Received: from mail-by2nam05lp2051.outbound.protection.outlook.com (HELO
 NAM05-BY2-obe.outbound.protection.outlook.com) ([104.47.50.51])
  by ob1.hgst.iphmx.com with ESMTP; 29 Aug 2019 21:55:14 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=SDSRcJ7xuX1pPOcZJIaCo2lO+5GMVFMqp756jwH96PwIStrvYhSPsotR0lVxO1Be32aAxhJUgY1sd9XU/hatwH3qIYyOxxNWNQ1xssMuoD75fOdIBTjrX38cV+tlh+xUjhs7zitdwwGcRQjrdUu08g3AmQ07uvrRJDm2oM39gVrkNLZ1pskwNmY5Gksot03GCK1HUe7fT7Ljy0VIgwrJzkRHhqqI8Qq5drqi50C6MgMNg/+Qs2FhHIhGJSBsrIznp52ft8ZAQJhpvMf0V0d6Luf/I0HXBmhOXuIju6uh3/f80I8R5b1gsVK3p03ew1exbah7jgFDG7mx4X4C1/eFSA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PZG59nV+nh6UIccqNk7O5taqylaiNHLzKjXy5EKXVrY=;
 b=g2SnEWaBZjSl33rPny9/KB/lMWqQ0XuaDV8iS7lXQsaaCCzmOeiCieNn7fZMQCYZb/okE6W01wGj2blm3jGWuQOMyuCLDGTBHGN9xUFf+BLheaWpUFDvyZ6EuJ5dJnr0LYMSt/zv579EyOL+jDbvPGpX7pSOKfz5MrCl7GyLJz/kxSW4A6cYou9+SKR7BZa1XdO7i0zG97xTv46apbZcRCLdwn8/r8cIIDpr7utRcU7QL9e34eynfA1MHkqZIhMkhdPULP3K6UkgsHvC8DtSKlrlEfUnFcEQshA4muvEnXjB9VLshgXji3soTKYd4IqcP/iE+b2vh2Pu5Jg7Gua2YQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PZG59nV+nh6UIccqNk7O5taqylaiNHLzKjXy5EKXVrY=;
 b=npFXRh3TpoarsogBdDGHJ53fHRKUxKMSEUMe2+injil0/MJGzuuSk3dCftE9P3F8sfyQoFD3bxlNIk45qpJNlvQ75GlITuNM/MdaZzo8bILCr/j8ijdzdtNlmZEt4L2Rpj+Wi3OQmIs1Uw3s38azdV6KrKXboxj9cHT/zg30DUQ=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB5616.namprd04.prod.outlook.com (20.179.22.29) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2199.21; Thu, 29 Aug 2019 13:55:13 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::e1a5:8de2:c3b1:3fb0]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::e1a5:8de2:c3b1:3fb0%7]) with mapi id 15.20.2220.013; Thu, 29 Aug 2019
 13:55:13 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v6 00/21] KVM RISC-V Support
Thread-Topic: [PATCH v6 00/21] KVM RISC-V Support
Thread-Index: AQHVXnFh/T6OyZ2noUKvsCDCsgPnHQ==
Date: Thu, 29 Aug 2019 13:55:12 +0000
Message-ID: <20190829135427.47808-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MAXPR0101CA0072.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:e::34) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [49.207.51.114]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 4a110188-2b99-40f3-fb52-08d72c88836a
x-ms-office365-filtering-ht: Tenant
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(7168020)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(4618075)(2017052603328)(7193020);SRVR:MN2PR04MB5616;
x-ms-traffictypediagnostic: MN2PR04MB5616:
x-ms-exchange-purlcount: 2
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB5616A36CB97B8DCC7EACB0968DA20@MN2PR04MB5616.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:1360;
x-forefront-prvs: 0144B30E41
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(39860400002)(136003)(366004)(376002)(346002)(396003)(189003)(199004)(7416002)(52116002)(81166006)(316002)(6506007)(386003)(25786009)(7736002)(81156014)(305945005)(2906002)(36756003)(71190400001)(14454004)(99286004)(1076003)(256004)(14444005)(4326008)(66946007)(66446008)(64756008)(66556008)(66476007)(6306002)(102836004)(6116002)(50226002)(55236004)(476003)(6512007)(966005)(3846002)(71200400001)(5660300002)(26005)(186003)(44832011)(86362001)(66066001)(6436002)(8936002)(6486002)(110136005)(54906003)(2616005)(486006)(53936002)(478600001)(8676002);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB5616;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 xV5Gaq3DwyWvsOeptdD7Ha0WWG+9oMOghsSEKju0jBFYuKlJZTmtexM1MRy08A5ezcE2T8xC+pKA7K6CLIQ+f8m3PfgzogCPrXA8hOLWGL+dJlIRrdRL57bnqSoFGZKAHk1oeMAwk1kF1yym/7wBIVEVUuBcjg924PsTnPorDU+DAeMFcmXFuEc+miLcku2Etcrrn9/b19iK42kSXcBL90UrFDtbUsvhLbEQ1zDIdajbnekSX+shSgaT7k172c3ygAjW2PA0K4GDUHivHBa/OlKuSv3aeNraCI7MRHEAqfbeefDoUCnbtKtV6xLZoi8hheyzfJmi5Bwy/SHPA/FpcaurvNrYRdLVMzIWvc1vXb3WtB1o/9BICUah7HeGSUS8bxLuiPc+qQdVOte9WyTiFPT93OeiDq2S/dxeUVMHoOI=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 4a110188-2b99-40f3-fb52-08d72c88836a
X-MS-Exchange-CrossTenant-originalarrivaltime: 29 Aug 2019 13:55:13.0873
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 qk3Trb2tt9GvfGvyycR0/fLWmnPnag7meXNtxwj4zt1JWbMAXQ6swQ7k4QEUUXxFdF2EkdWZrWSJHjbldi+w7w==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB5616
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space. In-kernel PLIC emulation, will
   be added in future.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.

Here's a brief TODO list which we will work upon after this series:
1. Implement recursive stage2 page table programing
2. SBI v0.2 emulation in-kernel
3. SBI v0.2 hart hotplug emulation in-kernel
4. In-kernel PLIC emulation
5. ..... and more .....

This series can be found in riscv_kvm_v6 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v1 branch at:
https//github.com/avpatel/kvmtool.git

We need OpenSBI with RISC-V hypervisor extension support which can be
found in hyp_ext_changes_v1 branch at:
https://github.com/riscv/opensbi.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in riscv-hyp-work.next branch at:
https://github.com/alistair23/qemu.git

To play around with KVM RISC-V, here are few reference commands:
1) To cross-compile KVMTOOL:
   $ make lkvm-static
2) To launch RISC-V Host Linux:
   $ qemu-system-riscv64 -monitor null -cpu rv64,h=true -M virt \
   -m 512M -display none -serial mon:stdio \
   -kernel opensbi/build/platform/qemu/virt/firmware/fw_jump.elf \
   -device loader,file=build-riscv64/arch/riscv/boot/Image,addr=0x80200000 \
   -initrd ./rootfs_kvm_riscv64.img \
   -append "root=/dev/ram rw console=ttyS0 earlycon=sbi"
3) To launch RISC-V Guest Linux with 9P rootfs:
   $ ./apps/lkvm-static run -m 128 -c2 --console serial \
   -p "console=ttyS0 earlycon=uart8250,mmio,0x3f8" -k ./apps/Image --debug
4) To launch RISC-V Guest Linux with initrd:
   $ ./apps/lkvm-static run -m 128 -c2 --console serial \
   -p "console=ttyS0 earlycon=uart8250,mmio,0x3f8" -k ./apps/Image \
   -i ./apps/rootfs.img --debug

Changes since v5:
- Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
  KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
- Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
- Use switch case instead of illegal instruction opcode table for simplicity
- Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
- Handle all unsupported SBI calls in default case of
  kvm_riscv_vcpu_sbi_ecall() function
- Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
- Improved unprivilege reads to handle traps due to Guest stage1 page table
- Added separate patch to document RISC-V specific things in
  Documentation/virt/kvm/api.txt

Changes since v4:
- Rebased patches on Linux-5.3-rc5
- Added Paolo's Acked-by and Reviewed-by
- Updated mailing list in MAINTAINERS entry

Changes since v3:
- Moved patch for ISA bitmap from KVM prep series to this series
- Make vsip_shadow as run-time percpu variable instead of compile-time
- Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
- Removed references of KVM_REQ_IRQ_PENDING from all patches
- Use kvm->srcu within in-kernel KVM run loop
- Added percpu vsip_shadow to track last value programmed in VSIP CSR
- Added comments about irqs_pending and irqs_pending_mask
- Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
  in system_opcode_insn()
- Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
- Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
- Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
- Fixed compile errors in building KVM RISC-V as module
- Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
- Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
- Made vmid_version as unsigned long instead of atomic
- Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
- Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
- Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
- Updated ONE_REG interface for CSR access to user-space
- Removed irqs_pending_lock and use atomic bitops instead
- Added separate patch for FP ONE_REG interface
- Added separate patch for updating MAINTAINERS file

Anup Patel (16):
  KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
  RISC-V: Add bitmap reprensenting ISA features common across CPUs
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Document RISC-V specific parts of KVM API.
  RISC-V: Enable VIRTIO drivers in RV64 and RV32 defconfig
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (5):
  RISC-V: Export few kernel symbols
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.txt          | 140 +++-
 MAINTAINERS                             |  10 +
 arch/riscv/Kconfig                      |   2 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/configs/defconfig            |  11 +
 arch/riscv/configs/rv32_defconfig       |  11 +
 arch/riscv/include/asm/csr.h            |  58 ++
 arch/riscv/include/asm/hwcap.h          |  26 +
 arch/riscv/include/asm/kvm_host.h       | 255 ++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |  30 +
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       | 104 +++
 arch/riscv/kernel/asm-offsets.c         | 148 ++++
 arch/riscv/kernel/cpufeature.c          |  79 +-
 arch/riscv/kernel/smp.c                 |   2 +-
 arch/riscv/kernel/time.c                |   1 +
 arch/riscv/kvm/Kconfig                  |  34 +
 arch/riscv/kvm/Makefile                 |  14 +
 arch/riscv/kvm/main.c                   |  92 +++
 arch/riscv/kvm/mmu.c                    | 911 +++++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  43 +
 arch/riscv/kvm/vcpu.c                   | 998 ++++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 607 ++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 104 +++
 arch/riscv/kvm/vcpu_switch.S            | 377 +++++++++
 arch/riscv/kvm/vcpu_timer.c             | 113 +++
 arch/riscv/kvm/vm.c                     |  86 ++
 arch/riscv/kvm/vmid.c                   | 123 +++
 drivers/clocksource/timer-riscv.c       |   8 +
 include/clocksource/timer-riscv.h       |  16 +
 include/uapi/linux/kvm.h                |   1 +
 31 files changed, 4396 insertions(+), 11 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
---
2.17.1
```
#### [PATCH 0/4] KVM: nVMX: Check GUEST_DEBUGCTL and GUEST_DR7 on vmentry
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Thu Aug 29 20:56:31 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11122471
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02F2C14DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 21:27:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D38BB22CEA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 21:27:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="sj0AKfhB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727546AbfH2V1g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 17:27:36 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:58878 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727234AbfH2V1g (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 17:27:36 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TLP4T8165925;
        Thu, 29 Aug 2019 21:27:19 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=WwwNCFkwDLUAzglbHUOnYAvCmaEVb+qt+sraM/XXYX8=;
 b=sj0AKfhBCX3P9USg/w74ykiyBRfSUZWBtkKKqG/1mokQgoi3fbvVey9L4m9c0fheknF3
 g0Spzlxy4NYbZyuQquJzsNRug5TLCzwb+qIr0nGc3NRAOMQuc6697cPCenFWnt4Bssee
 r6ZV2OH/kHkZC//v8+bCecBdL3+XzH5VG70wVPVj3bB1oizxGeRWownxs1tbVl/IC7B+
 Fa/TYtqPEqzPayJDmi9wj/4V779ahy1u9dGbHCEPRuNVee+3nDJr/4LGIHjtDTDMQkuX
 syNiIXypIWpHi0LDSCIvLJdm0xzKCsnFnBqZyXlbGPnT5UOvgGoTZdjV/09D+Jh2a+nA WA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 2uppjc00rq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 21:27:19 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TLE6Zl085260;
        Thu, 29 Aug 2019 21:25:19 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 2uphaub0fa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 21:25:18 +0000
Received: from abhmp0018.oracle.com (abhmp0018.oracle.com [141.146.116.24])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x7TLPHS1027445;
        Thu, 29 Aug 2019 21:25:17 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 29 Aug 2019 14:25:17 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: rkrcmar@redhat.com, pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 0/4] KVM: nVMX: Check GUEST_DEBUGCTL and GUEST_DR7 on vmentry
 of nested guests
Date: Thu, 29 Aug 2019 16:56:31 -0400
Message-Id: <20190829205635.20189-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9364
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=705
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908290214
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9364
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=766 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908290215
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1: Adds KVM check for GUEST_DEBUGCTL
Patch 2: Adds KVM check for GUEST_DR7
Patch 3: Fixes a bug in __enter_guest() in kvm-unit-test source
Patch 4: Adds kvm-unit-tests related to patch# 1 and 2


[PATCH 1/4] KVM: nVMX: Check GUEST_DEBUGCTL on vmentry of nested guests
[PATCH 2/4] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
[PATCH 3/4] kvm-unit-test: nVMX: __enter_guest() should not set "launched" state
[PATCH 4/4] kvm-unit-test: nVMX: Check GUEST_DEBUGCTL and GUEST_DR7 on vmentry of

 arch/x86/kvm/vmx/nested.c | 10 ++++++++++
 arch/x86/kvm/x86.c        |  2 +-
 arch/x86/kvm/x86.h        | 12 ++++++++++++
 3 files changed, 23 insertions(+), 1 deletion(-)

Krish Sadhukhan (2):
      nVMX: Check GUEST_DEBUGCTL on vmentry of nested guests
      nVMX: Check GUEST_DR7 on vmentry of nested guests

 x86/vmx.c       |  9 +++++----
 x86/vmx_tests.c | 59 +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 64 insertions(+), 4 deletions(-)

Krish Sadhukhan (2):
      nVMX: __enter_guest() should not set "launched" state when VM-entry fails
      nVMX: Check GUEST_DEBUGCTL and GUEST_DR7 on vmentry of nested guests
```
