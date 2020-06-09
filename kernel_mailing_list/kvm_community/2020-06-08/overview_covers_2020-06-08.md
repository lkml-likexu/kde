

#### [kvm-unit-tests PATCH v8 00/12] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Jun  8 08:12:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11592723
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC86460D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:13:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D377C206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 08:13:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729070AbgFHINK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 04:13:10 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14370 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729033AbgFHINJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Jun 2020 04:13:09 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05884jv5193967;
        Mon, 8 Jun 2020 04:13:08 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31g5fbpt8t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Jun 2020 04:13:08 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05885Ogw001800;
        Mon, 8 Jun 2020 04:13:07 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31g5fbpt7u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Jun 2020 04:13:07 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 058867pL011843;
        Mon, 8 Jun 2020 08:13:05 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04fra.de.ibm.com with ESMTP id 31g2s7se33-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 08 Jun 2020 08:13:05 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0588D3rI66126270
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 8 Jun 2020 08:13:03 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2956E4C050;
        Mon,  8 Jun 2020 08:13:03 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C64164C04A;
        Mon,  8 Jun 2020 08:13:02 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.43.245])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  8 Jun 2020 08:13:02 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v8 00/12] s390x: Testing the Channel Subsystem
 I/O
Date: Mon,  8 Jun 2020 10:12:49 +0200
Message-Id: <1591603981-16879-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-08_04:2020-06-08,2020-06-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 clxscore=1015
 priorityscore=1501 mlxscore=0 spamscore=0 mlxlogscore=999 malwarescore=0
 lowpriorityscore=0 suspectscore=1 phishscore=0 cotscore=-2147483648
 bulkscore=0 impostorscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006080062
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All,

Goal of the series is to have a framework to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test program to define its own
interrupt handler. We need to do special work under interrupt like acknowledging
the interrupt.
  
Being working on PSW bits to allow I/O interrupt, we define new PSW bits
in arch_def.h and use __ASSEMBLER__ define to be able to include this header
in an assembler source file.

This series presents four major tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled, retrying a predefined count on failure
	to enable the channel
        Checks MSCH       
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analyzing the answer and expecting
        the Control unit type being 0x3832, a.k.a. virtio-net-ccw.
        Checks SSCH(READ) and IO-IRQ

Note:
- The following patches are general usage and may be pulled first:
  s390x: Use PSW bits definitions in cstart
  s390x: Move control register bit definitions and add AFP to them
  s390x: saving regs for interrupts
  s390x: interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays caluculations
  s390x: define function to wait for interrupt
  s390x: retrieve decimal and hexadecimal kernel parameters

- These 4 patches are really I/O oriented:
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

Regards,
Pierre

Pierre Morel (12):
  s390x: Use PSW bits definitions in cstart
  s390x: Move control register bit definitions and add AFP to them
  s390x: saving regs for interrupts
  s390x: interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays caluculations
  s390x: define function to wait for interrupt
  s390x: retrieve decimal and hexadecimal kernel parameters
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

 lib/s390x/asm/arch_def.h |  32 ++++-
 lib/s390x/asm/time.h     |  51 +++++++
 lib/s390x/css.h          | 277 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 153 +++++++++++++++++++++
 lib/s390x/css_lib.c      | 176 +++++++++++++++++++++++++
 lib/s390x/interrupt.c    |  23 +++-
 lib/s390x/interrupt.h    |   8 ++
 lib/s390x/kernel-args.c  |  60 +++++++++
 lib/s390x/kernel-args.h  |  18 +++
 s390x/Makefile           |   4 +
 s390x/css.c              | 229 ++++++++++++++++++++++++++++++++
 s390x/cstart64.S         |  58 ++++++--
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 14 files changed, 1078 insertions(+), 26 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 lib/s390x/kernel-args.c
 create mode 100644 lib/s390x/kernel-args.h
 create mode 100644 s390x/css.c
```
#### [PATCH kvm-unit-tests 0/2] svm: INIT test and test_run on selected
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Mon Jun  8 12:27:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11593263
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 71917739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:28:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 588C32078C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:28:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CGmjLXtF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729756AbgFHM2Q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:28:16 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:60701 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729752AbgFHM2O (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 08:28:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591619293;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ClBDHBDktbLIW5J/z+Ht3YsS2xmoHHnGoFvx6CMwhtw=;
        b=CGmjLXtFwDoYABl2dcAvyD11d3SqPlnYPHOdf/BA+XuuqM86yyRVBWbaFm1D1F1kvO5QZ5
        XtpxItbXlo2rUuW/js/8FKLYMWPvx/2h486sEcOlxlMy1ima48qcrWx2RflriaASmfFJiq
        +Nx11HKWNi740WA9fxsb6AvKCowzq6M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-461-WOF0bhi7OyuMdL1nq3ePNg-1; Mon, 08 Jun 2020 08:28:04 -0400
X-MC-Unique: WOF0bhi7OyuMdL1nq3ePNg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 74999107ACF2;
        Mon,  8 Jun 2020 12:28:02 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C69E57BFE3;
        Mon,  8 Jun 2020 12:28:01 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests 0/2] svm: INIT test and test_run on selected
 vcpu
Date: Mon,  8 Jun 2020 08:27:58 -0400
Message-Id: <20200608122800.6315-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

INIT intercept test and the ability to execute test_run
on a selected vcpu.

Cathy Avery (2):
  svm: Add ability to execute test via test_run on a vcpu other than
    vcpu 0
  svm: INIT intercept test

 x86/svm.c       | 49 ++++++++++++++++++++++++++++++++++++++++++++++++-
 x86/svm.h       | 13 +++++++++++++
 x86/svm_tests.c | 40 ++++++++++++++++++++++++++++++++++++++++
 3 files changed, 101 insertions(+), 1 deletion(-)
```
#### [PATCH RFC v6 00/11] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Mon Jun  8 12:52:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11593287
Return-Path: <SRS0=GUoK=7V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23C9790
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:53:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 08D6B206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  8 Jun 2020 12:52:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NN+up0Nc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729180AbgFHMw7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 8 Jun 2020 08:52:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29632 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728245AbgFHMw6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Jun 2020 08:52:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591620776;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=gjI/Xc/cqqYk/lSVknmdrxtI4JosdROOwhqNKTqv88I=;
        b=NN+up0NcCTUYLGSto74dqIaj288wsdjwMReMgxuG5xHIC6uKe+pm2l+F2uEzqtTaZGQPtx
        8lnBaH4juCamqVOBunK/5J1j5ZPFD3xsTFOF0kSH2fsYwn6exM3U6/OjdZxBNQNeCR+8mL
        KmeQZKvR/AF+SbMqgCMEEIv+6vXfP+s=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-118-0XukzesxPYaj3BgPXm0wiw-1; Mon, 08 Jun 2020 08:52:55 -0400
X-MC-Unique: 0XukzesxPYaj3BgPXm0wiw-1
Received: by mail-wm1-f71.google.com with SMTP id g84so5214970wmf.4
        for <kvm@vger.kernel.org>; Mon, 08 Jun 2020 05:52:54 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=gjI/Xc/cqqYk/lSVknmdrxtI4JosdROOwhqNKTqv88I=;
        b=B/yzb0vI4iRr4QNhESMqYBKeWj5jgM8OXTDw8TWJQ7w9u+Ew35FKMjdC391lZSgd9K
         xfKbxAiNfVuu/UNtuNogJylPouF9uxkfo2/J2aW9yyts2KcFJHJFJZWmgT1rEpwPpIES
         slNLEZl7ppeij/QgZDHmp/z8MTAajhjq9nglySUKJnibTjSoOOPuLaGtAw9U0N+PFARq
         2JUhKTMDonL09dx6pqaqu1eJoQblYO9b3OlWdyNR0xEXwr4DxYw57WtQBW5fpeIsXdel
         94I+vqGdmiw1eI5j8D3WiRoe6ntWQmQ3HlqWELqFNno7+G2Hre++CIN2A16vnvMBuvjn
         nvrA==
X-Gm-Message-State: AOAM532aSqowdpcH55wAFDzPyoHOrLPf69gopxUIRXWXxB0Fd2mus8dj
        BOkv6nkIMmVvKeLc5cG8g7mTwCIK0ZNa64w+ZR1Mfqq6EQNSHhn12KYOaWJQJQ54ep2Vju6OnEN
        kb/aa2ilkWmcb
X-Received: by 2002:a05:6000:1ce:: with SMTP id
 t14mr23504279wrx.300.1591620773840;
        Mon, 08 Jun 2020 05:52:53 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwDSI+/ZbdtAMbTo/u8TmLBd4nOMtF+iSAUbirR2p1aEeZspsKsHQ+oW3THKUaNWxC1PVL/dQ==
X-Received: by 2002:a05:6000:1ce:: with SMTP id
 t14mr23504259wrx.300.1591620773666;
        Mon, 08 Jun 2020 05:52:53 -0700 (PDT)
Received: from redhat.com (bzq-109-64-41-91.red.bezeqint.net. [109.64.41.91])
        by smtp.gmail.com with ESMTPSA id
 y19sm21769323wmi.6.2020.06.08.05.52.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 08 Jun 2020 05:52:52 -0700 (PDT)
Date: Mon, 8 Jun 2020 08:52:51 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v6 00/11] vhost: ring format independence
Message-ID: <20200608125238.728563-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This adds infrastructure required for supporting
multiple ring formats.

The idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

Used ring is similar: we fetch into an independent struct first,
convert that to IOV later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

For used descriptors, this allows keeping track of the buffer length
without need to rescan IOV.

This seems to perform exactly the same as the original
code based on a microbenchmark.
Lightly tested.
More testing would be very much appreciated.

changes from v5:
	- addressed comments by Jason: squashed API changes, fixed up discard

changes from v4:
	- added used descriptor format independence
	- addressed comments by jason
	- fixed a crash detected by the lkp robot.

changes from v3:
        - fixed error handling in case of indirect descriptors
        - add BUG_ON to detect buffer overflow in case of bugs
                in response to comment by Jason Wang
        - minor code tweaks

Changes from v2:
	- fixed indirect descriptor batching
                reported by Jason Wang

Changes from v1:
	- typo fixes


Michael S. Tsirkin (11):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched get_vq_desc version
  vhost/net: pass net specific struct pointer
  vhost: reorder functions
  vhost: format-independent API for used buffers
  vhost/net: convert to new API: heads->bufs
  vhost/net: avoid iov length math
  vhost/test: convert to the buf API
  vhost/scsi: switch to buf APIs
  vhost/vsock: switch to the buf API
  vhost: drop head based APIs

 drivers/vhost/net.c   | 174 ++++++++++---------
 drivers/vhost/scsi.c  |  73 ++++----
 drivers/vhost/test.c  |  22 +--
 drivers/vhost/vhost.c | 382 +++++++++++++++++++++++++++---------------
 drivers/vhost/vhost.h |  44 +++--
 drivers/vhost/vsock.c |  30 ++--
 6 files changed, 443 insertions(+), 282 deletions(-)
```
