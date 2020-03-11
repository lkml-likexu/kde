

#### [PATCH v2 0/2] kvm: selftests: Introduce TEST_FAIL and convert
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Tue Mar 10 02:50:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11428323
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4653314B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 02:51:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1F5F724673
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 02:51:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I10mjx8D"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726558AbgCJCvN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 22:51:13 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29583 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726446AbgCJCvM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 22:51:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583808671;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=R6peiWc+YqZetn/lw3+wRj0vYCDROkZKsrBmpaORfr4=;
        b=I10mjx8DOQjXevohny2+BbnqasunkNN3m3vb3LXsaS9ujbKPj+B6PVmwglCF5hKOF8HGeh
        tVw0SFz41ZQ+zjSpzntxp5LosUAmxBXDp2FyB+Un5PnAy5BYQGK6HSAe583WGyMW5s35DR
        cfn8YwIs2WyLHWkf+/et2DNvBKNE3GU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-184-DaKKvYlVNG2EElH1V4v2nw-1; Mon, 09 Mar 2020 22:51:08 -0400
X-MC-Unique: DaKKvYlVNG2EElH1V4v2nw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D0FC0800D48;
        Tue, 10 Mar 2020 02:51:06 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-124.gru2.redhat.com
 [10.97.116.124])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E31235C1C3;
        Tue, 10 Mar 2020 02:51:02 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
        sean.j.christopherson@intel.com, shuah@kernel.org,
        tglx@linutronix.de, thuth@redhat.com
Subject: [PATCH v2 0/2] kvm: selftests: Introduce TEST_FAIL and convert
Date: Mon,  9 Mar 2020 23:50:57 -0300
Message-Id: <20200310025059.9301-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce the TEST_FAIL macro and change the tests/utilities
to use it.

v1 -> v2:
- Completed the conversion to TEST_FAIL.

v1:
- [RFC PATCH 0/1] kvm: selftests: Add TEST_FAIL macro
  https://lore.kernel.org/kvm/20200305172532.9360-1-wainersm@redhat.com/

Wainer dos Santos Moschetta (2):
  selftests: kvm: Introduce the TEST_FAIL macro
  selftests: kvm: Uses TEST_FAIL in tests/utilities

 tools/testing/selftests/kvm/dirty_log_test.c  |  7 +++----
 .../testing/selftests/kvm/include/test_util.h |  3 +++
 .../selftests/kvm/lib/aarch64/processor.c     | 17 +++++++--------
 .../testing/selftests/kvm/lib/aarch64/ucall.c |  2 +-
 tools/testing/selftests/kvm/lib/io.c          | 12 +++++------
 tools/testing/selftests/kvm/lib/kvm_util.c    | 21 ++++++++-----------
 .../selftests/kvm/lib/x86_64/processor.c      |  5 ++---
 .../kvm/x86_64/cr4_cpuid_sync_test.c          |  4 ++--
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  6 +++---
 .../testing/selftests/kvm/x86_64/state_test.c |  6 +++---
 .../selftests/kvm/x86_64/svm_vmcall_test.c    |  6 ++----
 .../kvm/x86_64/vmx_close_while_nested_test.c  |  4 ++--
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c |  6 +++---
 .../kvm/x86_64/vmx_tsc_adjust_test.c          |  4 ++--
 14 files changed, 49 insertions(+), 54 deletions(-)
```
#### [PATCH 0/4] KVM: selftests: Various cleanups and fixes
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Tue Mar 10 09:15:52 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11428883
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27686138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 09:16:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 071A42467F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 09:16:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QQWLBOFU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726414AbgCJJQJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 05:16:09 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:35528 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726205AbgCJJQI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Mar 2020 05:16:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583831767;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=s05C/YvWsTJ9Ho/uMXOcY/OoycpWuoeOVEWtOZICQtA=;
        b=QQWLBOFUOE8dfStOU0rzB41XMpgdH3sxYel6hAcc9ELE7TFA+l6Q6xdA0C7udtNon8YIBP
        glS93ERk5H+tiKrXNoAgCXXFqF4KlVJEVl2ovSFpKuSTg/a4JyDD+Dr0WDig70DUgs1yNa
        wm7IZDoeabDaCz24oqYjYtUf1FSZrm0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-191-Y6JvnMlUPu6uJD4-GUa9Xw-1; Tue, 10 Mar 2020 05:16:06 -0400
X-MC-Unique: Y6JvnMlUPu6uJD4-GUa9Xw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id F3D02800D4E;
        Tue, 10 Mar 2020 09:16:04 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1F8BD60C05;
        Tue, 10 Mar 2020 09:15:57 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, peterx@redhat.com,
        thuth@redhat.com
Subject: [PATCH 0/4] KVM: selftests: Various cleanups and fixes
Date: Tue, 10 Mar 2020 10:15:52 +0100
Message-Id: <20200310091556.4701-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Andrew Jones (4):
  fixup! selftests: KVM: SVM: Add vmcall test
  KVM: selftests: Share common API documentation
  KVM: selftests: Enable printf format warnings for TEST_ASSERT
  KVM: selftests: Use consistent message for test skipping

 tools/testing/selftests/kvm/.gitignore        |   5 +-
 .../selftests/kvm/demand_paging_test.c        |   6 +-
 tools/testing/selftests/kvm/dirty_log_test.c  |   3 +-
 .../testing/selftests/kvm/include/kvm_util.h  | 100 ++++++++-
 .../testing/selftests/kvm/include/test_util.h |   5 +-
 .../selftests/kvm/lib/aarch64/processor.c     |  17 --
 tools/testing/selftests/kvm/lib/assert.c      |   6 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |  10 +-
 .../selftests/kvm/lib/kvm_util_internal.h     |  48 +++++
 .../selftests/kvm/lib/s390x/processor.c       |  74 -------
 tools/testing/selftests/kvm/lib/test_util.c   |  12 ++
 .../selftests/kvm/lib/x86_64/processor.c      | 196 ++++--------------
 tools/testing/selftests/kvm/lib/x86_64/svm.c  |   2 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   2 +-
 tools/testing/selftests/kvm/s390x/memop.c     |   2 +-
 .../selftests/kvm/s390x/sync_regs_test.c      |   2 +-
 .../kvm/x86_64/cr4_cpuid_sync_test.c          |   2 +-
 .../testing/selftests/kvm/x86_64/evmcs_test.c |   6 +-
 .../selftests/kvm/x86_64/hyperv_cpuid.c       |   8 +-
 .../selftests/kvm/x86_64/mmio_warning_test.c  |   4 +-
 .../selftests/kvm/x86_64/platform_info_test.c |   3 +-
 .../kvm/x86_64/set_memory_region_test.c       |   3 +-
 .../testing/selftests/kvm/x86_64/state_test.c |   4 +-
 .../selftests/kvm/x86_64/svm_vmcall_test.c    |   3 +-
 .../selftests/kvm/x86_64/sync_regs_test.c     |   4 +-
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c |   2 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c    |   4 +-
 .../selftests/kvm/x86_64/xss_msr_test.c       |   2 +-
 28 files changed, 243 insertions(+), 292 deletions(-)
```
#### [PATCH 0/5] selftests: KVM: s390: Accumulated fixes and extensions
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Tue Mar 10 13:01:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11429319
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4DC8139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 13:22:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E185222D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 13:22:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730955AbgCJNWP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 09:22:15 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:33740 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730309AbgCJNBs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Mar 2020 09:01:48 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02ACxjpj137733;
        Tue, 10 Mar 2020 09:01:47 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ynr9dc1mx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 09:01:47 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 02AD0qgK009377;
        Tue, 10 Mar 2020 09:01:46 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2ynr9dc1mb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 09:01:46 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 02ACtbBU024222;
        Tue, 10 Mar 2020 13:01:46 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma02wdc.us.ibm.com with ESMTP id 2ym386jqhd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 13:01:46 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 02AD1jBT12518034
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Mar 2020 13:01:45 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A9BAD28060;
        Tue, 10 Mar 2020 13:01:45 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9B6F128058;
        Tue, 10 Mar 2020 13:01:45 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 10 Mar 2020 13:01:45 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 0/5] selftests: KVM: s390: Accumulated fixes and extensions
Date: Tue, 10 Mar 2020 09:01:39 -0400
Message-Id: <20200310130144.9921-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-10_06:2020-03-10,2020-03-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 spamscore=0
 suspectscore=0 malwarescore=0 adultscore=0 mlxscore=0 bulkscore=0
 lowpriorityscore=0 clxscore=1015 impostorscore=0 phishscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003100087
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- do more and better testing for reset
- fix fprintf formats (thanks to Andrew Jones)

Paolo, I would schedule this for next and not for master. ok?

Christian Borntraeger (5):
  selftests: KVM: s390: fix early guest crash
  selftests: KVM: s390: test more register variants for the reset ioctl
  selftests: KVM: s390: check for registers to NOT change on reset
  selftests: KVM: s390: fixup fprintf format error in reset.c
  selftests: KVM: s390: fix format strings for access reg test

 tools/testing/selftests/kvm/s390x/resets.c    | 132 ++++++++++++++----
 .../selftests/kvm/s390x/sync_regs_test.c      |  11 +-
 2 files changed, 116 insertions(+), 27 deletions(-)
```
#### [kvm-unit-tests PATCH v5 00/13] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Tue Mar 10 14:53:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11429553
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F5DA14BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 14:54:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E443D20674
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 14:54:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DdVNuPgw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727460AbgCJOyZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 10:54:25 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:34418 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727390AbgCJOyZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Mar 2020 10:54:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583852063;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=abFuB6UupSAbj5Uii0ujQcwLeLzAp81W5ty1h0cqZu4=;
        b=DdVNuPgwdyRhhC/bo4ok8MT7lsl9dKAXob23/aNXLbWzxbuzlnPC3DWufqwqXGRMjjQ9wu
        Y2/uX8TcrfuCAx5n83tkUo6D8PkJo76HV893v1pOi/L0ubluGOwaltW9eyakSJP2OeJI0K
        tzStCHvPN3wTDtcV7l8ENDqOW1e764k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-155-QwUxF7bNOPWOI1gJGvvNaw-1; Tue, 10 Mar 2020 10:54:22 -0400
X-MC-Unique: QwUxF7bNOPWOI1gJGvvNaw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6CA718017CC;
        Tue, 10 Mar 2020 14:54:20 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-117-85.ams2.redhat.com [10.36.117.85])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B599B60C88;
        Tue, 10 Mar 2020 14:54:14 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v5 00/13] arm/arm64: Add ITS tests
Date: Tue, 10 Mar 2020 15:53:57 +0100
Message-Id: <20200310145410.26308-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a revival of an RFC series sent in Dec 2016 [1].
Given the amount of code and the lack of traction at that time,
I haven't respinned until now. However a recent bug found related
to the ITS migration convinced me that this work may deserve to be
respinned and enhanced.

Tests exercise main ITS commands and also test migration.
With the migration framework, we are able to trigger the
migration from guest and that is very practical actually.

What is particular with the ITS programming is that most of
the commands are passed through queues and there is real error
handling. Invalid commands are just ignored and that is not
really tester friendly.

The series can be fount at:
https://github.com/eauger/kut/tree/its-v5

Best Regards

Eric

History:
v4 -> v5:
- 32b stubs moved back to arm/gic.c
- some changes reordering
- minor style issues

v3 -> v4:
- addressed comments from Drew and Zenghui
- added "page_alloc: Introduce get_order()"
- removed "arm: gic: Provide per-IRQ helper functions"
- ITS files moved to lib64
- and many more, see individual logs

v2 -> v3:
- fix 32b compilation
- take into account Drew's comments (see individual diff logs)

v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

Execution:
x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

Eric Auger (13):
  libcflat: Add other size defines
  page_alloc: Introduce get_order()
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: gicv3: Set the LPI config and pending tables
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: Commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.arm64         |   1 +
 arm/Makefile.common        |   2 +-
 arm/gic.c                  | 477 +++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  38 +++
 lib/alloc_page.c           |   7 +-
 lib/alloc_page.h           |   1 +
 lib/arm/asm/gic-v3-its.h   |  22 ++
 lib/arm/asm/gic-v3.h       |  34 +++
 lib/arm/asm/processor.h    |   2 +
 lib/arm/gic-v3.c           |  78 ++++++
 lib/arm/gic.c              |  34 ++-
 lib/arm/io.c               |  28 +++
 lib/arm64/asm/gic-v3-its.h | 172 +++++++++++++
 lib/arm64/gic-v3-its-cmd.c | 463 +++++++++++++++++++++++++++++++++++
 lib/arm64/gic-v3-its.c     | 172 +++++++++++++
 lib/libcflat.h             |   3 +
 17 files changed, 1507 insertions(+), 29 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm64/asm/gic-v3-its.h
 create mode 100644 lib/arm64/gic-v3-its-cmd.c
 create mode 100644 lib/arm64/gic-v3-its.c
```
