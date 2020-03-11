#### [kvm-unit-tests PATCH v5 01/13] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11429567
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3C891800
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 14:55:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 89245205F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 14:55:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Q1MXEk3x"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727663AbgCJOzD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 10:55:03 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:35925 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727654AbgCJOzD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Mar 2020 10:55:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583852102;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=g1Y7SAIkQ6YKL70iv+PevVOHVnPkk+5bW/+E3fVVoME=;
        b=Q1MXEk3xFv6bkIgyQvt6o1CVxR0MB5W9lYYWBAYsodifmCsFNcqD4pv2rpS2UKmy0B8TRn
        VeS1xBY/KhU/zdlT7woTUPnpz74LXRglc+bkgw0QpwqHC83mHD0bo9ed4x66aU0ZUueLZe
        9O/ySJXjumT2APycfxAZA8Sr5JGpolY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-11-iCXgruqYP3KD12YZLIk2GA-1; Tue, 10 Mar 2020 10:54:25 -0400
X-MC-Unique: iCXgruqYP3KD12YZLIk2GA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AACCF8017CC;
        Tue, 10 Mar 2020 14:54:23 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-117-85.ams2.redhat.com [10.36.117.85])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C111E60F89;
        Tue, 10 Mar 2020 14:54:20 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v5 01/13] libcflat: Add other size defines
Date: Tue, 10 Mar 2020 15:53:58 +0100
Message-Id: <20200310145410.26308-2-eric.auger@redhat.com>
In-Reply-To: <20200310145410.26308-1-eric.auger@redhat.com>
References: <20200310145410.26308-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce additional SZ_256, SZ_8K, SZ_16K macros that will
be used by ITS tests.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/libcflat.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### kvm/queue demand paging test and s390Autocrypt: addr=borntraeger@de.ibm.com; prefer-encrypt=mutual; keydata=
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11429919
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFCA714B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 16:55:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A48EC20873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 16:55:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726605AbgCJQzJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 12:55:09 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:41008 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726462AbgCJQzJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Mar 2020 12:55:09 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02AGpFKI052600
        for <kvm@vger.kernel.org>; Tue, 10 Mar 2020 12:55:07 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ym8n8up3j-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 10 Mar 2020 12:55:07 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Tue, 10 Mar 2020 16:55:04 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 10 Mar 2020 16:55:01 -0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02AGt0AU43647278
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Mar 2020 16:55:00 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2280AA4053;
        Tue, 10 Mar 2020 16:55:00 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DD849A4051;
        Tue, 10 Mar 2020 16:54:59 +0000 (GMT)
Received: from oc7455500831.ibm.com (unknown [9.152.224.141])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 10 Mar 2020 16:54:59 +0000 (GMT)
To: Ben Gardon <bgardon@google.com>
Cc: kvm list <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
From: Christian Borntraeger <borntraeger@de.ibm.com>
Subject: kvm/queue demand paging test and s390
Autocrypt: addr=borntraeger@de.ibm.com; prefer-encrypt=mutual; keydata=
 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
 nS4h0HDFPrrp1C2EMVYIQrMokWvlFZbCpsdYbBI=
Date: Tue, 10 Mar 2020 17:54:59 +0100
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101
 Thunderbird/68.4.1
MIME-Version: 1.0
Content-Language: en-US
X-TM-AS-GCONF: 00
x-cbid: 20031016-0012-0000-0000-0000038F1256
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20031016-0013-0000-0000-000021CBDE2F
Message-Id: <c845637e-d662-993e-2184-fa34bae79495@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-10_11:2020-03-10,2020-03-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 mlxlogscore=766 mlxscore=0 suspectscore=0 spamscore=0
 phishscore=0 bulkscore=0 malwarescore=0 clxscore=1015 impostorscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003100103
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For s390 the guest memory size must be 1M aligned. I need something like the following to make this work:


any better idea how to do that?

```
#### [PATCH v2 1/2] selftests: kvm: Introduce the TEST_FAIL macro
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11428327
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48F5814B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 02:51:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1FFE224673
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 02:51:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iLBoYZP+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726803AbgCJCvQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 22:51:16 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23565 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726402AbgCJCvP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 22:51:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583808674;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=X5rRvUDvsTgQao4JkzzYjt+VB8uH8OR/+ZrMMAk7Ask=;
        b=iLBoYZP+w/HPf0A1m8WsMcOPAIRahlNXSsYuiMMfI1Mo/YTFG3kVzODKScBMnVkPCfQzPw
        gfMlUs7IyZPs1oEfvW88AzT2LyYSm+o2dXzmxoktNSXT4/BWVMyahdI+jWawJ711HqI/My
        Jia8lMEm2Uxj6XQKfBUYaPq8BChflgU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-302-6H4BNnzzOGSeQ8-6mYA9tw-1; Mon, 09 Mar 2020 22:51:12 -0400
X-MC-Unique: 6H4BNnzzOGSeQ8-6mYA9tw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 62495184C800;
        Tue, 10 Mar 2020 02:51:11 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-124.gru2.redhat.com
 [10.97.116.124])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 863605C1C3;
        Tue, 10 Mar 2020 02:51:07 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
        sean.j.christopherson@intel.com, shuah@kernel.org,
        tglx@linutronix.de, thuth@redhat.com
Subject: [PATCH v2 1/2] selftests: kvm: Introduce the TEST_FAIL macro
Date: Mon,  9 Mar 2020 23:50:58 -0300
Message-Id: <20200310025059.9301-2-wainersm@redhat.com>
In-Reply-To: <20200310025059.9301-1-wainersm@redhat.com>
References: <20200310025059.9301-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some tests/utilities use the TEST_ASSERT(false, ...) pattern to
indicate a failure and stop execution.

This change introduces the TEST_FAIL macro which is a wrap around
TEST_ASSERT(false, ...) and so provides a direct alternative for
failing a test.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/include/test_util.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/4] fixup! selftests: KVM: SVM: Add vmcall test
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11428885
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13EAC138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 09:16:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DCA0824682
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 09:16:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fyrqurvJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726469AbgCJJQL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 05:16:11 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:46615 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726205AbgCJJQK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Mar 2020 05:16:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583831770;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=FzPIqR890Y9eu8VzNTrV4cbF4Y6Tc/k/pnAetrDWzf4=;
        b=fyrqurvJaZhuNXAy7bhFH46QlFjpuc6XhMBmMZH5KYsu9QxFJw2zV1T6VqiJI+KSagaAaQ
        iPseMrvYbbWBsXPam7HFU83jOHpWOVvYvxqttkLPib35W6Ph56pe80z4sM3z6Pu5DfZIaO
        23glkC1KpiJA+4IicB9kGbreeR0W4go=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-235-s0tz10t2PxWZP64Q0gyA6Q-1; Tue, 10 Mar 2020 05:16:08 -0400
X-MC-Unique: s0tz10t2PxWZP64Q0gyA6Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 25BB5477;
        Tue, 10 Mar 2020 09:16:07 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 492E760C05;
        Tue, 10 Mar 2020 09:16:05 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, peterx@redhat.com,
        thuth@redhat.com
Subject: [PATCH 1/4] fixup! selftests: KVM: SVM: Add vmcall test
Date: Tue, 10 Mar 2020 10:15:53 +0100
Message-Id: <20200310091556.4701-2-drjones@redhat.com>
In-Reply-To: <20200310091556.4701-1-drjones@redhat.com>
References: <20200310091556.4701-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[Add svm_vmcall_test to gitignore list, and realphabetize it.]
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: access: Shadow CR0, CR4 and EFER to avoid unnecessary VM-Exits
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11428427
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87D6C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 03:54:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 70F562465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 03:54:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726202AbgCJDye (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 23:54:34 -0400
Received: from mga02.intel.com ([134.134.136.20]:29917 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725845AbgCJDye (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 23:54:34 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Mar 2020 20:54:33 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,535,1574150400";
   d="scan'208";a="242182623"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga003.jf.intel.com with ESMTP; 09 Mar 2020 20:54:33 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: access: Shadow CR0,
 CR4 and EFER to avoid unnecessary VM-Exits
Date: Mon,  9 Mar 2020 20:54:32 -0700
Message-Id: <20200310035432.3447-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Track the last known CR0, CR4, and EFER values in the access test to
avoid taking a VM-Exit on every. single. test.  The EFER VM-Exits in
particular absolutely tank performance when running the test in L1.

Opportunistically tweak the 5-level test to print that it's starting
before configuring 5-level page tables, e.g. in case enabling 5-level
paging runs into issues.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/access.c | 45 +++++++++++++++++++++++++++------------------
 1 file changed, 27 insertions(+), 18 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Reload SS when switching to 5-level page tables
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11428425
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94F2517D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 03:47:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7ED842465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 03:47:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726269AbgCJDrb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 23:47:31 -0400
Received: from mga06.intel.com ([134.134.136.31]:21693 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726170AbgCJDrb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 23:47:31 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Mar 2020 20:47:30 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,535,1574150400";
   d="scan'208";a="388781384"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga004.jf.intel.com with ESMTP; 09 Mar 2020 20:47:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Reload SS when switching to 5-level page
 tables
Date: Mon,  9 Mar 2020 20:47:29 -0700
Message-Id: <20200310034729.2941-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Load SS with a valid segment when switching to 5-level page tables to
avoid taking a #SS due to a NULL segment when making a CALL with paging
disabled.

The "access" test calls setup_5level_page_table()/switch_to_5level()
after generating and handling usermode exceptions.  Per Intel's SDM,
SS is nullified on an exception that changes CPL:

  The new SS is set to NULL if there is a change in CPL.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/cstart64.S | 3 +++
 1 file changed, 3 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Run unit tests with --no-reboot so shutdowns show up as failures
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11428335
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 86EF414B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 02:52:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7104624676
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 02:52:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726520AbgCJCwu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 9 Mar 2020 22:52:50 -0400
Received: from mga18.intel.com ([134.134.136.126]:63496 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726156AbgCJCwu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Mar 2020 22:52:50 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 09 Mar 2020 19:52:49 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,535,1574150400";
   d="scan'208";a="235913626"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga008.jf.intel.com with ESMTP; 09 Mar 2020 19:52:49 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH] x86: Run unit tests with --no-reboot so
 shutdowns show up as failures
Date: Mon,  9 Mar 2020 19:52:49 -0700
Message-Id: <20200310025249.30961-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Run tests with --no-reboot so that triple fault shutdowns get reported
as failures.  By default, Qemu automatically reboots on shutdown, i.e.
automatically restarts the test, eventually leading to a timeout.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

I don't think there are any tests would run afoul of --no-reboot?

 x86/run | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: access regs array in vmenter.S in its natural order
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11429963
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0594714B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 17:10:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D9DE621D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 17:10:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mcGrcW4N"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726716AbgCJRKi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 13:10:38 -0400
Received: from mail-wr1-f65.google.com ([209.85.221.65]:42627 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726681AbgCJRKh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Mar 2020 13:10:37 -0400
Received: by mail-wr1-f65.google.com with SMTP id v11so16853608wrm.9
        for <kvm@vger.kernel.org>; Tue, 10 Mar 2020 10:10:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=w1HtT6GncF2D/jICWHxCXiDFA3NuhpTuwzMHtGs5MNk=;
        b=mcGrcW4NkNBmlcjsAjrf+ecneR5Y8x01BDF+MPm0+vjv1NaAdFAMFz/jTxagXLN7Rd
         xAF8GdwIM4IQEvmfZy4PvSpdb6vEnxLmxNRUaXWG685IBNeGOk4oVCyr5Pnto0M6/iqK
         VD8Uu6HJjdrMED7vwGpCWzl2EPVacg5jxD7RjUOFIj5k/4/BHP4bcN+47e2Bl0UcGAuI
         U6P/ySQxuQIsSXuAJDJ0KNYL1yv79io6wTREiWmx4ygDkQESmbZFMeEX7ia+nqUacVPY
         CewxNH159dGcrwwLTQEdwFfyXTdUqYbbAXcyiXwRzn5wh617j+j8xmVeURhhx+/PiZDU
         tRdQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=w1HtT6GncF2D/jICWHxCXiDFA3NuhpTuwzMHtGs5MNk=;
        b=nv7UmSo856QF6hCE+TDgucvoBcZ/bYLeNwT0Zx54LNanTQpiM5c2GJ7hOUUVWCCnrZ
         6bRrwbh3lUVa7WwIj1KeahS2nqo03bGBmIPVD4JzIbxISdbgTfqRSbScTrwQjA1ke4zk
         GxGa2JraEAExN0K4am5HJJxTp0uEmOBSjogXDlU+D4JlL3Vv7pVFD1P54lLogvu5Zd9w
         BpilAUK92QtU4+iid5Wzrco+FfNERkYD9OdnRrOl6LzJ7RNhi16MvB5Ihj8jjrYZm3cf
         67hffPUq4q+KQMr7qlM1lq4DZRov7S+VUPT0l1+HYeLSJJhosb46elweY3+dIrWHHGZk
         /grQ==
X-Gm-Message-State: ANhLgQ0GK9pDxgGd+dJl2ylOw8b5D79/L9Q3imKc8Tb8uqGArO7XGedp
        igPIvE2FXtVb4btwPC7TOvxFMwjR
X-Google-Smtp-Source: 
 ADFU+vv8BRQdbL05cC3CzdOkgz6AEdVXpErwTgGxX7NDtWqhKIn8UQGfkx1qoFW2Cf4zgBey9pnO+g==
X-Received: by 2002:adf:ecca:: with SMTP id
 s10mr29621943wro.255.1583860233892;
        Tue, 10 Mar 2020 10:10:33 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id v2sm4308734wme.2.2020.03.10.10.10.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 10 Mar 2020 10:10:33 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Uros Bizjak <ubizjak@gmail.com>
Subject: [PATCH] KVM: VMX: access regs array in vmenter.S in its natural order
Date: Tue, 10 Mar 2020 18:10:24 +0100
Message-Id: <20200310171024.15528-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Registers in "regs" array are indexed as rax/rcx/rdx/.../rsi/rdi/r8/...
Reorder access to "regs" array in vmenter.S to follow its natural order.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmenter.S | 14 +++++++-------
 1 file changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: X86: Don't load/put guest FPU context for sleeping AP
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11428585
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 247751731
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 07:01:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 034B02467C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 07:01:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Ch9tuHA5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726258AbgCJHB0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 03:01:26 -0400
Received: from mail-pl1-f196.google.com ([209.85.214.196]:44678 "EHLO
        mail-pl1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726195AbgCJHB0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Mar 2020 03:01:26 -0400
Received: by mail-pl1-f196.google.com with SMTP id d9so5059926plo.11;
        Tue, 10 Mar 2020 00:01:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=YVCc+DwPWWPXpUGQIKeRYvwB/hOaYmc0ZXRCQL5h/QI=;
        b=Ch9tuHA5mP7aZFRWp0dUFohQRYj+RTodiPvpCIpy4uvOXMytCkwdiMZ8Fwni/PV1Nj
         gUjFzAIGWPoFoGnUY4THtMnyY/X+jN3DJJ/BxpHSt3HVYYq22nZ59dxdQqW/co+r7VYN
         Q0ZQvxNXcEsmMocQ6TZGyvzuK7zrhPG75zitXlYJzcwYg0B/QADaBME/215jJcAe6t3e
         0ZBrSTlKoZRb6o4kiw3ItxxWf44Bea+Mz142XjKc/nR0uuGB5RGH6nheTo2d5g+va3Vw
         2yweAWeEhHJ2kF1UhpbB2jCnYSF2UsHsaxTqwXnK/dIzivkulWBYkDHbrA0Tq3TRASph
         CuWA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=YVCc+DwPWWPXpUGQIKeRYvwB/hOaYmc0ZXRCQL5h/QI=;
        b=twlSLYhPvXzTu9HmseqhisVOvU8lSxXW9Xnc3fktx6cMBgXrVZcG11SoCvhuxePCIA
         SHw/OYjp3z+sSirf164pj3kzAlDzFHV4CWBpzJ5ZjMxXopN2J40cZJB+RU0x+rxorrcr
         PD2ave4wm7J+3HwR1fuQ+xEZeavAsQjl7njhbx3j9OgfulFxGvdb76iTOZr5xBFovaDD
         8S5uKfZ02yYj6oea2eQVX8FdxU9/2sDOB0qJH1n5HhCTEDv3jQX9Z3oUT53DOvjOUnnh
         079PwwcnPwI2oce2/VDzYSDkQ78NmxRCfNp8TsIE8QTtQ/QxFVlOjYOum4qzusMzYAVg
         fCng==
X-Gm-Message-State: ANhLgQ1Um/tRwTfz9tjiWBqRxC6Xelc9cpJT4hh4EqA8VEN8Hk+aFjtb
        AE5obU77nr/66it+KBhdBtP2lww9
X-Google-Smtp-Source: 
 ADFU+vtWyb9wxDCHh+eWg5cFe/KSNXdnPSQSZLGp23dJF5fr7mZVeuzE2lhp5gRqVxgsx9KRANH4EA==
X-Received: by 2002:a17:90a:a409:: with SMTP id
 y9mr261468pjp.103.1583823685319;
        Tue, 10 Mar 2020 00:01:25 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 k14sm1645934pje.3.2020.03.10.00.01.22
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 10 Mar 2020 00:01:24 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: X86: Don't load/put guest FPU context for sleeping AP
Date: Tue, 10 Mar 2020 15:01:19 +0800
Message-Id: <1583823679-17648-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

kvm_load_guest_fpu() and kvm_put_guest_fpu() each consume more than 14us 
observed by ftrace, the qemu userspace FPU is swapped out for the guest 
FPU context for the duration of the KVM_RUN ioctl even if sleeping AP, 
we shouldn't load/put guest FPU context for this case especially for 
serverless scenario which sensitives to boot time.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH 1/5] selftests: KVM: s390: fix early guest crash
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11429311
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44412139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 13:22:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2F26D222D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 13:22:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730326AbgCJNBu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 09:01:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:45596 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730311AbgCJNBt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Mar 2020 09:01:49 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02AD0P9k147201;
        Tue, 10 Mar 2020 09:01:48 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ym8cajr0j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 09:01:48 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 02AD0Uxr000802;
        Tue, 10 Mar 2020 09:01:47 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ym8cajqyh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 09:01:47 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 02AD1Xkn029878;
        Tue, 10 Mar 2020 13:01:46 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma04dal.us.ibm.com with ESMTP id 2ym386sdyb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 13:01:46 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 02AD1jki14746148
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Mar 2020 13:01:45 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BC95A2806D;
        Tue, 10 Mar 2020 13:01:45 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B79902806A;
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
Subject: [PATCH 1/5] selftests: KVM: s390: fix early guest crash
Date: Tue, 10 Mar 2020 09:01:40 -0400
Message-Id: <20200310130144.9921-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200310130144.9921-1-borntraeger@de.ibm.com>
References: <20200310130144.9921-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-10_06:2020-03-10,2020-03-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 bulkscore=0
 lowpriorityscore=0 priorityscore=1501 phishscore=0 suspectscore=0
 impostorscore=0 spamscore=0 adultscore=0 mlxlogscore=999 malwarescore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003100087
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest crashes very early due to changes in the control registers
used by dynamic address translation. Let us use different registers
that will not crash the guest.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 tools/testing/selftests/kvm/s390x/resets.c | 27 +++++++++++-----------
 1 file changed, 13 insertions(+), 14 deletions(-)

```
#### [PATCH v2] KVM: s390: Also reset registers in sync regs for initial cpu reset
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11429277
Return-Path: <SRS0=8lGI=43=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 77BD3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 13:12:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6032920409
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Mar 2020 13:12:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731573AbgCJNMc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Mar 2020 09:12:32 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30834 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731558AbgCJNMa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Mar 2020 09:12:30 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02ADC3v3016421;
        Tue, 10 Mar 2020 09:12:29 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ynraxnm8c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 09:12:29 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 02ADCDuN017656;
        Tue, 10 Mar 2020 09:12:28 -0400
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ynraxnm7e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 09:12:28 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 02ADC0Nn030386;
        Tue, 10 Mar 2020 13:12:27 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma05wdc.us.ibm.com with ESMTP id 2ym386junm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 10 Mar 2020 13:12:27 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02ADCQr554788370
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Mar 2020 13:12:26 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B0EBBC6057;
        Tue, 10 Mar 2020 13:12:26 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 328A4C6059;
        Tue, 10 Mar 2020 13:12:26 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue, 10 Mar 2020 13:12:26 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, linux-s390 <linux-s390@vger.kernel.org>,
        Cornelia Huck <cohuck@redhat.com>, stable@vger.kernel.org
Subject: [PATCH v2] KVM: s390: Also reset registers in sync regs for initial
 cpu reset
Date: Tue, 10 Mar 2020 09:12:23 -0400
Message-Id: <20200310131223.10287-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-10_06:2020-03-10,2020-03-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 spamscore=0
 malwarescore=0 mlxlogscore=999 lowpriorityscore=0 bulkscore=0 mlxscore=0
 phishscore=0 impostorscore=0 suspectscore=0 clxscore=1015
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003100088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we do the initial CPU reset we must not only clear the registers
in the internal data structures but also in kvm_run sync_regs. For
modern userspace sync_regs is the only place that it looks at.

Cc: stable@vger.kernel.org
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 18 +++++++++++++++++-
 1 file changed, 17 insertions(+), 1 deletion(-)

```
