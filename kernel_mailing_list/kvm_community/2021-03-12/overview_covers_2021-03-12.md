

#### [kvm-unit-tests PATCH v6 0/6] CSS Mesurement Block
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Fri Mar 12 10:41:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12134261
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 86EC6C433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 10:42:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F03B65036
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 10:42:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233502AbhCLKmR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 05:42:17 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:5144 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232834AbhCLKmB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Mar 2021 05:42:01 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12CAXqXZ026375
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 05:42:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=W9YfApTZEIevFkpbGRU4KI4Um4jKSbrDeVz6GrgLw9A=;
 b=sZK+V53Xz6UeCKLwFnMcIG3AJAw6f9N5AHrR9Ud7ThWeziqkiefTuwTUBFET1F94nyJW
 qE07VQ36fzqKWPolmmZhye5U/MIlQb1omzd2yKpo/zVaSoN2ThWRsCazZu3/Ca8JndA2
 5jXoIzfJWp+jfWp3fUwQ8q+wOerWn0yR+gQ1p77p16EQVkFBkjjm9b2FFU/NKBxXftp9
 BSGWtumo7PAOZZWrg49CXFMNhUKfIQ0ru0nsqKP3FFUPt/Tvi/V1r8pVf2CHCZod8v0v
 wx5y5CwoOJxK/6QvCLFYBIRg2+XS3B/DhsgkaVh5rQzuR0DeykAQHbTz3KaMpBy6RTLB 1g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3774kyx442-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 05:42:01 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12CAYsDM030355
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 05:42:00 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3774kyx433-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Mar 2021 05:42:00 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12CAfq6Q009032;
        Fri, 12 Mar 2021 10:41:58 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03ams.nl.ibm.com with ESMTP id 3768t4jruu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Mar 2021 10:41:58 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12CAft2j56099136
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 12 Mar 2021 10:41:55 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 949F3AE05A;
        Fri, 12 Mar 2021 10:41:55 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4D24DAE051;
        Fri, 12 Mar 2021 10:41:55 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.32.251])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 12 Mar 2021 10:41:55 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v6 0/6] CSS Mesurement Block
Date: Fri, 12 Mar 2021 11:41:48 +0100
Message-Id: <1615545714-13747-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-12_03:2021-03-10,2021-03-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 impostorscore=0 phishscore=0 mlxlogscore=999 clxscore=1015
 priorityscore=1501 lowpriorityscore=0 bulkscore=0 malwarescore=0
 adultscore=0 mlxscore=0 spamscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2103120072
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We tests the update of the Mesurement Block (MB) format 0
and format 1 using a serie of senseid requests.

*Warning*: One of the tests for format-1 will unexpectedly fail for QEMU elf
unless the QEMU patch "css: SCHIB measurement block origin must be aligned"
is applied.
This patch has recently hit QEMU master ...
With Protected Virtualization, the PGM is correctly recognized.

The MB format 1 is only provided if the Extended mesurement Block
feature is available.

This feature is exposed by the CSS characteristics general features
stored by the Store Channel Subsystem Characteristics CHSC command,
consequently, we implement the CHSC instruction call and the SCSC CHSC
command.

In order to ease the writing of new tests using:
- interrupt
- enablement of a subchannel
- multiple I/O on a subchannel

We do the following simplifications:
- we create a CSS initialization routine
- we register the I/O interrupt handler on CSS initialization
- we do not enable or disable a subchannel in the senseid test,
  assuming this test is done after the enable test, this allows
  to create traffic using the SSCH used by senseid.
- failures not part of the feature under test will stop the tests.
- we add a css_enabled() function to test if a subchannel is enabled.

*note*:
    I rearranged the use of the senseid for the tests, by not modifying
    the existing test and having a dedicated senseid() function for
    the purpose of the tests.
    I think that it is in the rigght way so I kept the RB and ACK on
    the simplification, there are less changes, if it is wrong from me
    I suppose I will see this in the comments.
    Since the changed are moved inside the fmt0 test which is not approved
    for now I hope it is OK.

Regards,
Pierre

Pierre Morel (6):
  s390x: css: Store CSS Characteristics
  s390x: css: simplifications of the tests
  s390x: css: extending the subchannel modifying functions
  s390x: css: implementing Set CHannel Monitor
  s390x: css: testing measurement block format 0
  s390x: css: testing measurement block format 1

 lib/s390x/css.h     | 115 ++++++++++++++++++++-
 lib/s390x/css_lib.c | 236 ++++++++++++++++++++++++++++++++++++++++----
 s390x/css.c         | 216 ++++++++++++++++++++++++++++++++++++++--
 3 files changed, 539 insertions(+), 28 deletions(-)
```
#### [PATCH v3 0/8] x86/seves: Support 32-bit boot path and other updates
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Fri Mar 12 12:38:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12134525
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44A22C433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 12:39:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E4A264D73
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 12:39:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229907AbhCLMi4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 07:38:56 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35110 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229913AbhCLMie (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 07:38:34 -0500
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 545BEC061574;
        Fri, 12 Mar 2021 04:38:34 -0800 (PST)
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 724822A6;
        Fri, 12 Mar 2021 13:38:30 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v3 0/8] x86/seves: Support 32-bit boot path and other updates
Date: Fri, 12 Mar 2021 13:38:16 +0100
Message-Id: <20210312123824.306-1-joro@8bytes.org>
X-Mailer: git-send-email 2.30.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

these patches add support for the 32-bit boot in the decompressor
code. This is needed to boot an SEV-ES guest on some firmware and grub
versions. The patches also add the necessary CPUID sanity checks and a
32-bit version of the C-bit check.

Other updates included here:

        1. Add code to shut down exception handling in the
           decompressor code before jumping to the real kernel.
           Once in the real kernel it is not safe anymore to jump
           back to the decompressor code via exceptions.

        2. Replace open-coded hlt loops with proper calls to
           sev_es_terminate().

Please review.

Thanks,

	Joerg

Changes v2->v3:

	- Added a patch to remove the check for the Hypervisor CPUID
	  bit for detecting SEV

Changes v1->v2:

	- Addressed Boris' review comments.
	- Fixed a bug which caused the cbit-check to never be
	  executed even in an SEV guest.

Joerg Roedel (8):
  x86/boot/compressed/64: Cleanup exception handling before booting
    kernel
  x86/sev: Do not require Hypervisor CPUID bit for SEV guests
  x86/boot/compressed/64: Reload CS in startup_32
  x86/boot/compressed/64: Setup IDT in startup_32 boot path
  x86/boot/compressed/64: Add 32-bit boot #VC handler
  x86/boot/compressed/64: Add CPUID sanity check to 32-bit boot-path
  x86/boot/compressed/64: Check SEV encryption in 32-bit boot-path
  x86/sev-es: Replace open-coded hlt-loops with sev_es_terminate()

 arch/x86/boot/compressed/head_64.S     | 170 ++++++++++++++++++++++++-
 arch/x86/boot/compressed/idt_64.c      |  14 ++
 arch/x86/boot/compressed/mem_encrypt.S | 130 ++++++++++++++++++-
 arch/x86/boot/compressed/misc.c        |   7 +-
 arch/x86/boot/compressed/misc.h        |   6 +
 arch/x86/boot/compressed/sev-es.c      |  12 +-
 arch/x86/kernel/sev-es-shared.c        |  16 +--
 arch/x86/mm/mem_encrypt_identity.c     |  35 ++---
 8 files changed, 340 insertions(+), 50 deletions(-)
```
#### [PATCH v3 0/8] KVM/ARM: Some vgic fixes and init sequence KVM
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Mar 12 17:31:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12135549
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0E1DC433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 17:33:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE3DC64F6F
	for <kvm@archiver.kernel.org>; Fri, 12 Mar 2021 17:33:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232362AbhCLRcg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 12:32:36 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:55659 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231679AbhCLRcT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Mar 2021 12:32:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615570338;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xhSFUQdlA2GO6iSQiZu6P1gE7L7SnxGWpmNseOtj/Ow=;
        b=JPnwpiXnSIMjIKGfj6BihXg8W36ZlxfFUjHxGOG59/ZhfJX9n1/AhCTOrrdJkY9QpiXfiB
        Wa+3Ieu0pbUqtYvnk7yQzuEo2naHtJywdm6HtywoWEDMyUTAqNt+6UajHAbm/0ZiTIhWk8
        hPXYD2sPKpwPD9OSmWI4KyQ3DOJc2SA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-187-bNhvwPppMU-fq2HEo5pAkw-1; Fri, 12 Mar 2021 12:32:15 -0500
X-MC-Unique: bNhvwPppMU-fq2HEo5pAkw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5FA65192D786;
        Fri, 12 Mar 2021 17:32:13 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-254.ams2.redhat.com
 [10.36.112.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 60CC410023AB;
        Fri, 12 Mar 2021 17:32:04 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com
Cc: james.morse@arm.com, julien.thierry.kdev@gmail.com,
        suzuki.poulose@arm.com, shuah@kernel.org, pbonzini@redhat.com
Subject: [PATCH v3 0/8] KVM/ARM: Some vgic fixes and init sequence KVM
 selftests
Date: Fri, 12 Mar 2021 18:31:54 +0100
Message-Id: <20210312173202.89576-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While writting vgic v3 init sequence KVM selftests I noticed some
relatively minor issues. This was also the opportunity to try to
fix the issue laterly reported by Zenghui, related to the RDIST_TYPER
last bit emulation. The final patch is a first batch of VGIC init
sequence selftests. Of course they can be augmented with a lot more
register access tests, but let's try to move forward incrementally ...

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/vgic_kvmselftests_v3

History:
v2 ->v3:
- reworked last bit read accessor to handle contiguous redist
  regions and rdist not registered in ascending order
- removed [PATCH 5/9] KVM: arm: move has_run_once after the
  map_resources

v1 -> v2:
- Took into account all comments from Marc and Alexandru's except
  the has_run_once still after the map_resources (this would oblige
  me to revisit in depth the selftests)

Eric Auger (8):
  KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
  KVM: arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION read
  KVM: arm64: vgic-v3: Fix error handling in vgic_v3_set_redist_base()
  KVM: arm/arm64: vgic: Reset base address on kvm_vgic_dist_destroy()
  docs: kvm: devices/arm-vgic-v3: enhance KVM_DEV_ARM_VGIC_CTRL_INIT doc
  KVM: arm64: Simplify argument passing to vgic_uaccess_[read|write]
  KVM: arm64: vgic-v3: Expose GICR_TYPER.Last for userspace
  KVM: selftests: aarch64/vgic-v3 init sequence tests

 .../virt/kvm/devices/arm-vgic-v3.rst          |   2 +-
 arch/arm64/kvm/vgic/vgic-init.c               |  13 +-
 arch/arm64/kvm/vgic/vgic-kvm-device.c         |   3 +
 arch/arm64/kvm/vgic/vgic-mmio-v3.c            | 116 ++-
 arch/arm64/kvm/vgic/vgic-mmio.c               |  10 +-
 arch/arm64/kvm/vgic/vgic.h                    |   1 +
 include/kvm/arm_vgic.h                        |   3 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/aarch64/vgic_init.c | 672 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   5 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  51 ++
 11 files changed, 827 insertions(+), 50 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/vgic_init.c
```
