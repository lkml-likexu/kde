

#### [RFC PATCH 0/4] vfio-ccw: A couple trace changes
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Mon Oct 14 18:08:51 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11189269
Return-Path: <SRS0=utul=YH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA65415AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 18:09:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C4E7C21835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 18:09:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732788AbfJNSJF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 14:09:05 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30732 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732653AbfJNSJF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 14 Oct 2019 14:09:05 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9EHvdmv102552
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 14:09:04 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vmv8pbu54-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 14:09:04 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Mon, 14 Oct 2019 19:09:02 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 14 Oct 2019 19:09:01 +0100
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9EI8xoc49217666
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 14 Oct 2019 18:08:59 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0F3B64C052;
        Mon, 14 Oct 2019 18:08:59 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EE9954C050;
        Mon, 14 Oct 2019 18:08:58 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 14 Oct 2019 18:08:58 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 9B588E016E; Mon, 14 Oct 2019 20:08:58 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH 0/4] vfio-ccw: A couple trace changes
Date: Mon, 14 Oct 2019 20:08:51 +0200
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 19101418-4275-0000-0000-00000372042F
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101418-4276-0000-0000-00003885140A
Message-Id: <20191014180855.19400-1-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-14_09:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=647 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910140149
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Conny,

I mentioned these to you a while ago; just been caught up in other
things. These aren't really pre-reqs for anything in our pipe, but
they've been beneficial to me on their own, and simplify debugging
of future work (such as the FSM needs brought up by Halil).

While the first patch refactors the trace so new ones can be added
outside the FSM, none of the other patches in this series really do.
I imagine that would be beneficial in the future, so I think it
would be good to do that rework before we get too far along.

Eric Farman (4):
  vfio-ccw: Refactor how the traces are built
  vfio-ccw: Trace the FSM jumptable
  vfio-ccw: Add a trace for asynchronous requests
  vfio-ccw: Rename the io_fctl trace

 drivers/s390/cio/Makefile           |  4 +--
 drivers/s390/cio/vfio_ccw_cp.h      |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c     | 11 +++---
 drivers/s390/cio/vfio_ccw_private.h |  1 +
 drivers/s390/cio/vfio_ccw_trace.c   | 14 ++++++++
 drivers/s390/cio/vfio_ccw_trace.h   | 56 ++++++++++++++++++++++++++++-
 6 files changed, 79 insertions(+), 8 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c
```
#### [kvm-unit-tests PATCH 0/4] Patches for clang compilation
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Mon Oct 14 19:24:27 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11189349
Return-Path: <SRS0=utul=YH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 831F51390
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 19:24:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 637E921721
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 19:24:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="l+bq29zH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388523AbfJNTYi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 15:24:38 -0400
Received: from mail-yw1-f73.google.com ([209.85.161.73]:45334 "EHLO
        mail-yw1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388245AbfJNTYi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 15:24:38 -0400
Received: by mail-yw1-f73.google.com with SMTP id o204so14335542ywc.12
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 12:24:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=SRhEAAU8/+3Mdz5PZ+SYtqxO9uMOiDzHiECPRjG6fk0=;
        b=l+bq29zH/07IL5UknjGQNzWD1TY5zjol+t1p0ShYvjdH7d+4fPPivIYtOff1EAtXGp
         7fmzgW7frr+we72aiRHaJs9iGeTBKxMEBiM2w8tEiVN5OTjvQvNwCCd3L/V5jS+InitH
         BcO7mMdNVR81necewF4VtF4JNbM2NzsltoqPK20iofZQ1VK9jKtH7FkCit6LQOZSkRcP
         v0L4ORrZTC6vLtVxabJaOhd+qarB2vWatKVLTJC8RPTY4PUT71zgOmPzDRumPp7H6jHL
         Av2P1KGPNmjpYya4aNb2WsxWNdPpPJ1YSuLF2fR+6dDVVWz0KvSAMx19I3PT+KeDLiGl
         yWuw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=SRhEAAU8/+3Mdz5PZ+SYtqxO9uMOiDzHiECPRjG6fk0=;
        b=P/Oe2yXekeLi67sZA2prWF8yrZAfeyUKM8FwKwaSnVunl221oDBVIKjEIQrTFNUQY3
         JcSwo4HCSwbFBJxdDQuyEokm9E0wBqcBd0+quyddM1MW8wLKZCmdeMyL7YEGJJpeVbyo
         GQW2zFVDkAjMoCivrIOyHA03ZNCMwwW3BuqPrFkeS5rbc5sqU7IDjipW4BLIzNDl2oYz
         oWVTrxUqGmRFt/eiSNLlJ1BjqELcFqF58mPjwsgHYw5Ck2dUHGktUlGk4Va3fd50G4Us
         SnY5x7+21KTZDl58GlGEXBfTbsaeNR1uluRRTpOyp3eiLkpurp/j+eXTilJqgpqaZ7+n
         1kgA==
X-Gm-Message-State: APjAAAW54AnB+/0qaOsbZVRkZTiQaBD08/vedJFbQP6s3FQPTInFbZE+
        Q0IgRG+RzGqB4y9X/hG24zGf8s5w4PkHxkatfMPQ7APNXOhNDefRQCJ/B7ncSmx1MYKz16yc08Q
        S4jFarJieDdaBoOAFvkcbEn9cwXHXNRZaC8q15qPwA63keQ5OVoeICw==
X-Google-Smtp-Source: 
 APXvYqw8hW07KX6VM4ejcstU/6myeArsjYb1+/br9/qZMyyAisXytaL6jWrmalGvS9XISoSB0KQP/OBs6w==
X-Received: by 2002:a25:4292:: with SMTP id
 p140mr20256898yba.47.1571081077283;
 Mon, 14 Oct 2019 12:24:37 -0700 (PDT)
Date: Mon, 14 Oct 2019 12:24:27 -0700
In-Reply-To: <20191010183506.129921-1-morbo@google.com>
Message-Id: <20191014192431.137719-1-morbo@google.com>
Mime-Version: 1.0
References: <20191010183506.129921-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 0/4] Patches for clang compilation
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These four patches fix compilation issues that clang's encountering.

I ran the tests and there are no regressions with gcc.

Bill Wendling (4):
  x86: emulator: use "SSE2" for the target
  pci: cast the masks to the appropriate size
  Makefile: use "-Werror" in cc-option
  Makefile: add "cxx-option" for C++ builds

 Makefile       | 23 +++++++++++++++--------
 lib/pci.c      |  3 ++-
 x86/emulator.c |  2 +-
 3 files changed, 18 insertions(+), 10 deletions(-)
```
