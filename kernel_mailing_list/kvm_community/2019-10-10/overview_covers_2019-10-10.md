

#### [PATCH v6 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
From patchwork Thu Oct 10 05:16:55 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11182595
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 024E513BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 05:17:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D6E9B20659
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 05:17:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727806AbfJJFRB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 01:17:01 -0400
Received: from mga07.intel.com ([134.134.136.100]:13392 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726065AbfJJFRB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 01:17:01 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Oct 2019 22:17:01 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,279,1566889200";
   d="scan'208";a="193089168"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga008.fm.intel.com with ESMTP; 09 Oct 2019 22:16:59 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH v6 0/2] x86: Enable user wait instructions
Date: Thu, 10 Oct 2019 13:16:55 +0800
Message-Id: <20191010051657.28163-1-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v6:
	Only remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set.
        (Paolo)
v5:
	Remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set. (Paolo)
v4:
	Set IA32_UMWAIT_CONTROL 32bits
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"	
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 target/i386/cpu.c     |  3 ++-
 target/i386/cpu.h     |  3 +++
 target/i386/kvm.c     | 17 +++++++++++++++++
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 42 insertions(+), 1 deletion(-)
```
#### [RFC v2 0/2] kvm: Use host timekeeping in guest.
##### From: Suleiman Souhlal <suleiman@google.com>

```c
From patchwork Thu Oct 10 07:30:53 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suleiman Souhlal <suleiman@google.com>
X-Patchwork-Id: 11182815
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE7F51575
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 07:39:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E9B822468
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 07:39:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="oXEBvVog"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733127AbfJJHiJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 03:38:09 -0400
Received: from mail-qk1-f202.google.com ([209.85.222.202]:41501 "EHLO
        mail-qk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733058AbfJJHbD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 03:31:03 -0400
Received: by mail-qk1-f202.google.com with SMTP id z128so4611934qke.8
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 00:31:03 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=v+LLFtvEckUzputJIuZrPxx3By/lN1gL3OtSQmwVR94=;
        b=oXEBvVog+GYUFdZS6nbRFPX4kM5tulvoNbWDK0JlCK400aDOdG4fx5K78mB6fw1Fnb
         Fm/aDMafzZO4rtJf0joBPsIyrpFyATrh7QSU+3AYy74LjXVida1xyOxzXn7UrGELefsV
         lwHyei54XzSIN3/WPOjeNgX5yGAXeNFQtmWh8R7eBTihLnIqZV6YLz9yitStMSbpsVzY
         7IjUa8EkxXDbtnvlL7uTVehZkq+NCKBweJxZtau7cCa5rFxix2DPSA9XYlPJg3E4sgJb
         Ua07w0RDFseYndhi1zZK7z4vSrkgzhswMZOjck1bNu0VR4HLdJ6U3ZQlVflHjxLdUqPZ
         tyeA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=v+LLFtvEckUzputJIuZrPxx3By/lN1gL3OtSQmwVR94=;
        b=ChGRUiaOaJgCqS9MeM7CqDcakB6e+1aEzjF3oYVIzWBSBTD1UmcUQ7ePV+0bu454m3
         EvE0+WkwC1rtevOz5v2RotCa8YmeQ6mrcYkbUFkWZdJnFj8leRXg3TsvE6uKSrs6edaV
         mfwXnt+7R1mGlxd3Sthq6Z6qkM586P27y5s0VOWrWDx5zP5h6cylCn7XMf/Xc3G0YlSV
         iowN7rxFUfPliZkURgF62/kkuib5bb8pXp7rWuzm/76W6rGRb2gjH4eHugIGF4OiXJ31
         8d0d6yhAARlLxYD/izip/65XGmhqmBZ68QlpOOW3a0nAnLdJbM683B/JhDHGPXcXSYuA
         J0uA==
X-Gm-Message-State: APjAAAUkJP8ha0gZJ7d5rZS2m095Gu1DKHDahUfAzZ8NpFupme7YKEIq
        e79UUl1BeZf8cswFqeD/edkj5qzUPTM0fA==
X-Google-Smtp-Source: 
 APXvYqyD9HKOtk0SarlzT8pp42sYiLkFHwAn9eUk83sA8rOiisTkHGAPdmKoPBCuQTQeRxenoJbZZHPVIHB7Jw==
X-Received: by 2002:ac8:3158:: with SMTP id h24mr8582490qtb.370.1570692662399;
 Thu, 10 Oct 2019 00:31:02 -0700 (PDT)
Date: Thu, 10 Oct 2019 16:30:53 +0900
Message-Id: <20191010073055.183635-1-suleiman@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.581.g78d2f28ef7-goog
Subject: [RFC v2 0/2] kvm: Use host timekeeping in guest.
From: Suleiman Souhlal <suleiman@google.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, tglx@linutronix.de
Cc: john.stultz@linaro.org, sboyd@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        ssouhlal@freebsd.org, tfiga@chromium.org, vkuznets@redhat.com,
        Suleiman Souhlal <suleiman@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This RFC is to try to solve the following problem:

We have some applications that are currently running in their
own namespace, that still talk to other processes on the
machine, using IPC, and expect to run on the same machine.

We want to move them into a virtual machine, for the usual
benefits of virtualization.

However, some of these programs use CLOCK_MONOTONIC and
CLOCK_BOOTTIME timestamps, as part of their protocol, when talking
to the host.

Generally speaking, we have multiple event sources, for example
sensors, input devices, display controller vsync, etc and we would
like to rely on them in the guest for various scenarios.

As a specific example, we are trying to run some wayland clients
(in the guest) who talk to the server (in the host), and the server
gives input events based on host time. Additionally, there are also
vsync events that the clients use for timing their rendering.

Another use case we have are timestamps from IIO sensors and cameras.
There are applications that need to determine how the timestamps
relate to the current time and the only way to get current time is
clock_gettime(), which would return a value from a different time
domain than the timestamps.

In this case, it is not feasible to change these programs, due to
the number of the places we would have to change.

We spent some time thinking about this, and the best solution we
could come up with was the following:

Make the guest kernel return the same CLOCK_MONOTONIC and
CLOCK_GETTIME timestamps as the host.

To do that, I am changing kvmclock to request to the host to copy
its timekeeping parameters (mult, base, cycle_last, etc), so that
the guest timekeeper can use the same values, so that time can
be synchronized between the guest and the host.

Any suggestions or feedback would be highly appreciated.

Changes in v2:
- Move out of kvmclock and into its own clocksource and file.
- Remove timekeeping.c #ifdefs.
- Fix i386 build.

Suleiman Souhlal (2):
  kvm: Mechanism to copy host timekeeping parameters into guest.
  x86/kvmclock: Introduce kvm-hostclock clocksource.

 arch/x86/Kconfig                     |   9 ++
 arch/x86/include/asm/kvm_host.h      |   3 +
 arch/x86/include/asm/kvmclock.h      |  12 +++
 arch/x86/include/asm/pvclock-abi.h   |  27 ++++++
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kernel/Makefile             |   2 +
 arch/x86/kernel/kvmclock.c           |   5 +-
 arch/x86/kernel/kvmhostclock.c       | 130 +++++++++++++++++++++++++++
 arch/x86/kvm/x86.c                   | 121 +++++++++++++++++++++++++
 include/linux/timekeeper_internal.h  |   8 ++
 kernel/time/timekeeping.c            |   2 +
 11 files changed, 319 insertions(+), 1 deletion(-)
 create mode 100644 arch/x86/kernel/kvmhostclock.c
```
#### [PATCH v2 0/2] diag 9c improvements
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Thu Oct 10 11:05:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11183099
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B87371709
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 11:05:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A370C21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 11:05:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732990AbfJJLF2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 07:05:28 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:21956 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727116AbfJJLF0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 10 Oct 2019 07:05:26 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9A9RYMV157650
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 07:05:25 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vj0kdx4v8-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 07:05:25 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Thu, 10 Oct 2019 12:05:23 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 10 Oct 2019 12:05:19 +0100
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9AB4moI40108368
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 10 Oct 2019 11:04:48 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DEC5842047;
        Thu, 10 Oct 2019 11:05:18 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA1A342042;
        Thu, 10 Oct 2019 11:05:18 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu, 10 Oct 2019 11:05:18 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 79D3FE01C6; Thu, 10 Oct 2019 13:05:18 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH v2 0/2] diag 9c improvements
Date: Thu, 10 Oct 2019 13:05:16 +0200
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19101011-0028-0000-0000-000003A8D31E
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101011-0029-0000-0000-0000246ADB2A
Message-Id: <20191010110518.129256-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-10_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=402 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910100084
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Christian Borntraeger (2):
  KVM: s390: count invalid yields
  KVM: s390: Do not yield when target is already running

 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/kvm/diag.c             | 22 ++++++++++++++++++----
 arch/s390/kvm/kvm-s390.c         |  1 +
 3 files changed, 20 insertions(+), 4 deletions(-)
```
#### [kvm-unit-tests PATCH 0/3] Patches for clang compilation
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Thu Oct 10 18:35:03 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11184051
Return-Path: <SRS0=OAn+=YD=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00A8014DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 18:35:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D5ED220B7C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 10 Oct 2019 18:35:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="sLfik+Co"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726509AbfJJSfi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 10 Oct 2019 14:35:38 -0400
Received: from mail-vk1-f201.google.com ([209.85.221.201]:47718 "EHLO
        mail-vk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725901AbfJJSfi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Oct 2019 14:35:38 -0400
Received: by mail-vk1-f201.google.com with SMTP id h186so2464983vkg.14
        for <kvm@vger.kernel.org>; Thu, 10 Oct 2019 11:35:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=8qITtlfN7DfL4So8PtImqvXvjqN5KVqQfKSdHZjpQwI=;
        b=sLfik+CoQgyisPX1rVG1AxBqN8+xor9OJPAnqpsJopbYdTAgc3xH33PexjCwI31r8q
         hYG+Tp/Z99iVIjWsZ60vbvz8mbgAhOMdl3IvHuNi2vU70kozugqUkDGM+Iy9Yg0/HrIz
         WjDwuWZQFNELHdM+1rjKB4wq0W/mmi2Mg669/BZZ5X7D5+tKLeoez4XY4TnSgGTOkBAW
         qrnPXJkyckuZY51IkBS3fgRKx25HLUKQhtHORI6ZA/aAHUAcpIrC/Z5ciCljWjuf6Vjs
         GvwAD1VfRhD0HhGtoU88PHarF4uJsw5D0pJ43/PaqEY1smBkCf9XP2PsbPr10hPy1YX1
         u1gg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=8qITtlfN7DfL4So8PtImqvXvjqN5KVqQfKSdHZjpQwI=;
        b=jTMpVkr97S1Vs9kud6Xgu/KCSoIePnczpoIw3JfzTB2yw8AbSbSpudhU9Pt/fksGks
         zxS8USkX8ySGlqImDLUdcl2wR+U84jisuPelA+iqD8YqWLSIX9o+Yq+V8x5jPYxObnG0
         7SWk1WT0sqTOuPP50QWVvKzlSpTysAdagLz8bkRoxVxaryXo/xlaIfv8qvCRzxZU7MZ7
         JkyYoBH15YkxeLv7Algk/Q/zlQOBKFn4/jpv8XvdPQw6xO0QtUgmh8dASzbLMvxSY9tJ
         41leQ8zP0y1d4DTuBkhQlVVI/xt886NcEgJqIvWnzZ+VZK8qEHzOvvMHzD4b1HowJFfF
         I8ww==
X-Gm-Message-State: APjAAAVwWFNkZhMc3z+ljoeTxod8lsxQJT0dfImAvhpomn7bYIbscT5q
        BgRsIF6aCJtyF9dS8VOvG+v1ur+/8y8cGQY6jY5jIBxH5kIW6Tdm2cSvc6/b1kPxTfHfCm/uiOx
        dpf5v33l0kAaLoqRE8DWWN9Z3aVwLHrS4zDposFCKCoMrbmrcjukcgg==
X-Google-Smtp-Source: 
 APXvYqxxu7e1OVMjCAdG2h8urjxkXs88G8V4HqqHfmeAB6ebIKPJStoJzZ47IITOifPxPaFNLMUbQS5IYA==
X-Received: by 2002:a05:6102:2142:: with SMTP id
 h2mr6450721vsg.27.1570732537228;
 Thu, 10 Oct 2019 11:35:37 -0700 (PDT)
Date: Thu, 10 Oct 2019 11:35:03 -0700
Message-Id: <20191010183506.129921-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 0/3] Patches for clang compilation
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These three patches fixes some compilation issues that clang's
encountering. I ran the tests and there are no regressions with gcc.

Bill Wendling (3):
  x86: emulator: use "SSE2" for the target
  pci: use uint64_t for unsigned long values
  Makefile: use "-Werror" in cc-option

 Makefile       | 19 +++++++++++--------
 lib/pci.c      | 18 +++++++++---------
 lib/pci.h      |  4 ++--
 x86/emulator.c |  2 +-
 4 files changed, 23 insertions(+), 20 deletions(-)
```
