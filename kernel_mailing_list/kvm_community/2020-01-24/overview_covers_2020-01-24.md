

#### [PATCH v1 0/1] vfio-ccw: Fix interrupt handling for HALT/CLEAR
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Fri Jan 24 14:54:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11350533
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD30E92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 14:55:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9542E20704
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 14:55:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730287AbgAXOzG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jan 2020 09:55:06 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:5996 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729567AbgAXOzG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 24 Jan 2020 09:55:06 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00OElged049141
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 09:55:05 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xr1yf9myb-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 09:55:04 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Fri, 24 Jan 2020 14:55:02 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 24 Jan 2020 14:54:59 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00OEs7uY43778436
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 24 Jan 2020 14:54:07 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E4209A405B;
        Fri, 24 Jan 2020 14:54:57 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D2E32A4054;
        Fri, 24 Jan 2020 14:54:57 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 24 Jan 2020 14:54:57 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 64D24E0379; Fri, 24 Jan 2020 15:54:57 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: "Jason J . Herne" <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v1 0/1] vfio-ccw: Fix interrupt handling for HALT/CLEAR
Date: Fri, 24 Jan 2020 15:54:54 +0100
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20012414-0012-0000-0000-0000038053B6
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012414-0013-0000-0000-000021BC9E2C
Message-Id: <20200124145455.51181-1-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-24_04:2020-01-24,2020-01-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=2 phishscore=0
 priorityscore=1501 mlxlogscore=999 malwarescore=0 clxscore=1015 mlxscore=0
 adultscore=0 impostorscore=0 lowpriorityscore=0 bulkscore=0 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-1910280000
 definitions=main-2001240124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Conny,

As I mentioned offline, I have been encountering some problems while
testing the channel path code.  By pure coincidence, I found some
really good clues that led me to this proposed fix.  I moved this
commit to the head of my channel path v2 code, but think maybe it
should be sent by itself so it doesn't get lost in that noise.

Figure 16-6 in SA22-7832-12 (POPS) goes into great detail of the
contents of the irb.cpa based on the other bits in the IRB.
Both the existing code and this new patch treates the irb.cpa as
valid all the time, even though that table has many many entries
where the cpa contents are "unpredictable."  Methinks that this
is partially how we got into this mess, so maybe I need to write
some smarter logic here anyway?  Thoughts?

(Disclaimer1:  I didn't go back and re-read the conversations
that were had for the commit I marked in the "Fixes:" tag,
but will just to make sure we didn't miss something.)

(Disclaimer2:  This makes my torturing-of-the-chpids test run
quite nicely, but I didn't go back to try some of the other
cruel-and-unusual tests at my disposable to ensure this patch
doesn't cause any other regressions.  That's on today's agenda.)

Eric Farman (1):
  vfio-ccw: Don't free channel programs for unrelated interrupts

 drivers/s390/cio/vfio_ccw_cp.c  | 11 +++++++++--
 drivers/s390/cio/vfio_ccw_cp.h  |  2 +-
 drivers/s390/cio/vfio_ccw_drv.c |  4 ++--
 3 files changed, 12 insertions(+), 5 deletions(-)
```
#### [PATCH 0/2] KVM: selftests: Rework debug message printing
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Fri Jan 24 15:37:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11350603
Return-Path: <SRS0=8och=3N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24806924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 15:37:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED9D0214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 24 Jan 2020 15:37:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JxNPj6PJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388639AbgAXPhm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jan 2020 10:37:42 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29697 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388568AbgAXPhm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jan 2020 10:37:42 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579880261;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Brgw6GVwy3CvgHQuefLbql5hhy8ODrGyqdPirPSGpyQ=;
        b=JxNPj6PJF+6tGD3pds9gTd1jhZUfxsxrhrHEpSYfSyE9e0/kOZw2kOCW+zfHH0BJG25Ubh
        eyadYAqxmGRGdQlEzDVp8EQB2BdOqGaXxBlj1pK66dJvObzk2iDN6I5vIelazIcLU5o3RM
        vS1fdAaLBGgqNiLK6I1g/yJk4IRjmJQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-266-M2yXUG6rOFq1gU3qzpsirQ-1; Fri, 24 Jan 2020 10:37:38 -0500
X-MC-Unique: M2yXUG6rOFq1gU3qzpsirQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4BB52B1B73
        for <kvm@vger.kernel.org>; Fri, 24 Jan 2020 15:37:29 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7120F1001B28;
        Fri, 24 Jan 2020 15:37:28 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/2] KVM: selftests: Rework debug message printing
Date: Fri, 24 Jan 2020 16:37:24 +0100
Message-Id: <20200124153726.15455-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix some issues with how we output debug and info messages.

Andrew Jones (2):
  KVM: selftests: Rework debug message printing
  KVM: selftests: Convert some printf's to pr_info's

 tools/testing/selftests/kvm/dirty_log_test.c     | 16 +++++++++-------
 tools/testing/selftests/kvm/include/kvm_util.h   | 13 ++++++++++---
 .../testing/selftests/kvm/kvm_create_max_vcpus.c |  8 ++++----
 .../selftests/kvm/lib/aarch64/processor.c        |  2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c       |  7 ++++---
 .../selftests/kvm/x86_64/mmio_warning_test.c     |  2 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c    |  2 +-
 tools/testing/selftests/kvm/x86_64/state_test.c  |  2 +-
 .../selftests/kvm/x86_64/vmx_tsc_adjust_test.c   |  4 ++--
 .../testing/selftests/kvm/x86_64/xss_msr_test.c  |  2 +-
 10 files changed, 34 insertions(+), 24 deletions(-)
```
