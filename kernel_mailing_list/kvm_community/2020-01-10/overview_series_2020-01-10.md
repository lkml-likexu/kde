#### [kvm-unit-tests PATCH v2 01/16] libcflat: Add other size defines
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11327513
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33BCC6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 14:54:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 044442082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 14:54:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SvFGWpfp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728209AbgAJOy3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 09:54:29 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:60680 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728137AbgAJOy3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 09:54:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578668068;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=g1Y7SAIkQ6YKL70iv+PevVOHVnPkk+5bW/+E3fVVoME=;
        b=SvFGWpfp3DVBDZfD4bM3aH/YFOrFPI6GT1BxVzDUMtp4MqSc96m5XvVWmenZhHsON659sC
        XLvKJzI05Cddvh2ajlWClozArJZTumC1AQn4DLAdK7K6vgY2hfSMdrYPPNZF/TxMpna2F3
        3OB5xvJCGAlk7iC662MCE8jhFXqe5Eo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-364-H6w6yrkENFmG85vKwnY_Qg-1; Fri, 10 Jan 2020 09:54:27 -0500
X-MC-Unique: H6w6yrkENFmG85vKwnY_Qg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7B37618B9FEF;
        Fri, 10 Jan 2020 14:54:25 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-117-108.ams2.redhat.com
 [10.36.117.108])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B178A7BA5F;
        Fri, 10 Jan 2020 14:54:20 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 01/16] libcflat: Add other size defines
Date: Fri, 10 Jan 2020 15:53:57 +0100
Message-Id: <20200110145412.14937-2-eric.auger@redhat.com>
In-Reply-To: <20200110145412.14937-1-eric.auger@redhat.com>
References: <20200110145412.14937-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
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
#### [PATCH] KVM: s390: Cleanup initial cpu reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11327425
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46E336C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 13:48:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2FC7420848
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 13:48:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727917AbgAJNsi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 08:48:38 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:16212 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727458AbgAJNsh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 08:48:37 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00ADlDZw117809
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 08:48:37 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xee3eudun-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 08:48:36 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 10 Jan 2020 13:48:34 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 10 Jan 2020 13:48:30 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00ADmTeU45154418
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 13:48:29 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 94CF411C04A;
        Fri, 10 Jan 2020 13:48:29 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5189811C054;
        Fri, 10 Jan 2020 13:48:28 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.153.163])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 10 Jan 2020 13:48:28 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [PATCH] KVM: s390: Cleanup initial cpu reset
Date: Fri, 10 Jan 2020 08:48:24 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <b01c38bf-5887-25d8-b787-271e5c2292e2@redhat.com>
References: <b01c38bf-5887-25d8-b787-271e5c2292e2@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011013-0016-0000-0000-000002DC3E0E
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011013-0017-0000-0000-0000333EC101
Message-Id: <20200110134824.37963-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-10_01:2020-01-10,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 adultscore=0
 impostorscore=0 lowpriorityscore=0 suspectscore=1 clxscore=1015
 phishscore=0 spamscore=0 malwarescore=0 mlxscore=0 mlxlogscore=999
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001100118
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The code seems to be quite old and uses lots of unneeded spaces for
alignment, which doesn't really help with readability.

Let's:
* Get rid of the extra spaces
* Remove the ULs as they are not needed on 0s
* Define constants for the CR 0 and 14 initial values
* Use the sizeof of the gcr array to memset it to 0

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---

Something like this?
Did I forget something?

---
 arch/s390/include/asm/kvm_host.h |  5 +++++
 arch/s390/kvm/kvm-s390.c         | 18 +++++++-----------
 2 files changed, 12 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH] add .editorconfig definition
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 11327653
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 49FD2138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 15:17:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E76B2077C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 15:17:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="RU08XnoN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728137AbgAJPRo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 10:17:44 -0500
Received: from mail-wm1-f65.google.com ([209.85.128.65]:51652 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726402AbgAJPRn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jan 2020 10:17:43 -0500
Received: by mail-wm1-f65.google.com with SMTP id d73so2401064wmd.1
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 07:17:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=U0+HwA4wKFY9D6e/1hcl/iLuo/q00aJgCMGLLMkPfTQ=;
        b=RU08XnoN967TXrBDUnFfphysBqdJbjsXLSsoiOxFvS+DZrm+8KcwPD1tTMtiR4YDNL
         txD/4X4ga12WXq995CrbQctebIMtoUo5PD5JOQHIH6gLO28D28c72LdYV5QppSzh4AFS
         UnMU1XJp55syeAeD2Z0fiN+1Jve+abgoB6lWwGVVQGhYDJGkp6Hz1B9F2Y5J9KUnjcIK
         JIIZx1vi3VYuQZbCob1D0+9lpnqp+qmo8kJJBySjv2W4SiWvGR4dNbI1+IxhtnkAIB1v
         bCoqSnV91YwAIM2VxS1dsw+Vgy4o8lANclyjanXMX54cxx9LiStHhMBad5onMU9rLYN1
         sF/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=U0+HwA4wKFY9D6e/1hcl/iLuo/q00aJgCMGLLMkPfTQ=;
        b=Sma3n2IleUvW710adMrX+DTUiKMbw4iiUzVedVkQ/cuSIO7WMVDLS4IYfMLz6yfeJp
         szgoL99xx0Pc2N8HB4oHnNnMrWLrcOVkJx1dX5uIt0HTh7NuGwbhFuJJTY7ZAOy5jQQz
         +iC2ZfihCQG169W7F/pRubduZxZc2WUAM+lGixw5g+ddtR/DeMGqy+m/vGfPuW6UuNqE
         0vb9Yql6Bgik0XB9kw3No9xeR8OMDNuB92V0bh6xvKGAEZOhJArEu0sVcdiTuX05n+75
         dqJVnrbngHqpGoA2P3uJgRb6vBO7LXrUdf31+DX/U00MJdR31s3A2h8Mpltwt+6Cxlqc
         +6IA==
X-Gm-Message-State: APjAAAXlws/hDAwlkPmaxINW9X3rgPUaW2mJ3+Vqz+ThHkRYU57ZUjzU
        KGtUTTz7Xi9JCpx0dlrsJzTnJm6CfLY=
X-Google-Smtp-Source: 
 APXvYqx4jgl6wMC870+RmaBlX4RewIPMc0yLY5sWuP/jaAYWZeSHlRNxTnGTxaxPWoczBf74W1ok3g==
X-Received: by 2002:a05:600c:2549:: with SMTP id
 e9mr5125601wma.6.1578669461856;
        Fri, 10 Jan 2020 07:17:41 -0800 (PST)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 j12sm2532146wrt.55.2020.01.10.07.17.40
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 10 Jan 2020 07:17:40 -0800 (PST)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id C627B1FF87;
        Fri, 10 Jan 2020 15:17:39 +0000 (GMT)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-tests PATCH] add .editorconfig definition
Date: Fri, 10 Jan 2020 15:17:27 +0000
Message-Id: <20200110151727.7920-1-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a editor agnostic configuration file to specify the
indentation style for the project. It is supported by both Emacs and
Vim as well as some other inconsequential editors.

Signed-off-by: Alex Bennée <alex.bennee@linaro.org>
---
 .editorconfig | 15 +++++++++++++++
 1 file changed, 15 insertions(+)
 create mode 100644 .editorconfig

diff --git a/.editorconfig b/.editorconfig
new file mode 100644
index 0000000..46d4ac6
--- /dev/null
+++ b/.editorconfig
@@ -0,0 +1,15 @@
+# EditorConfig is a file format and collection of text editor plugins
+# for maintaining consistent coding styles between different editors
+# and IDEs. Most popular editors support this either natively or via
+# plugin.
+#
+# Check https://editorconfig.org for details.
+
+root = true
+
+[*]
+end_of_line = lf
+insert_final_newline = true
+charset = utf-8
+indent_style = tab
+indent_size = 8
```
#### [kvm-unit-tests PATCH] arm: expand the timer tests
##### From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
X-Patchwork-Id: 11327797
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2D01492A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 16:05:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0B9782087F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 16:05:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="ZGts9mEs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728549AbgAJQF3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 11:05:29 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:38485 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728458AbgAJQF1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jan 2020 11:05:27 -0500
Received: by mail-wr1-f66.google.com with SMTP id y17so2323637wrh.5
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 08:05:26 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/DmvPJlY9Tmv4EyIG/NDnFk433eow2vkRfUSRyghGd0=;
        b=ZGts9mEsV07oqMlH5CGwSt00UWM0Vhti8vRXxb5TEq9QRrXQJuYE7jQMZqw8HkyyAS
         sV/PLumRLEtdMsCQeerA3sVA2vS7CrLAEQ7hwe0cIMc+mToYOAxqRm/Pe52vxzA02HfA
         PFPISdEWNRntwUhvfwVSkiVgxtgs3PmKbjkYAEy0e3PN828LfaH9kiQq3ZgPHuJ4rybp
         FNfwTYKFCs3OdjzPHPk1WZ+Oajm3TxK8owHm/HfsLF0DOyMl0QNKjyiyApvsOQ4YH2MP
         UvZ+5hfmtLRzrHEwCA3Sv1mdagoBY/97MR1UDieUNaC6N4CX2GpiamxSKcaDcaYG7V8i
         5vKQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=/DmvPJlY9Tmv4EyIG/NDnFk433eow2vkRfUSRyghGd0=;
        b=BrD4gUk1CER+j7kXJoEWZ6owZmjzuepScGIc+cG6uv5T6/wXXrJR2hT5zyb4qlsxKk
         I1lT/YrtJMI9IJFWEJEOGKDDTP5c8X3rpDRfyhM9iJjoXy4dOBJ5+Rsetmc8YD2S1SsF
         i0TTgifdHxrZ1R5pUahxjxOCKaUdXhmu6fNRnZY4I1nvRko+Rv+xCiqGcPtl/aA5dWkd
         EqRm+EpGcx0rOOBFrmiwIIV50z5p7V7Er8I78EZaS9xa7BIVv5NRB0H+eIohIRGoorS4
         5cWxZL43O7VW2qQv/YeBllpyneiFrzlZ3fZQBUgbuM+ooGs7cpO2L1W/97LqAmPjNA2/
         LTKg==
X-Gm-Message-State: APjAAAUXeGGEL5zmEes98OTAVczXekcbvQv0dECQ993gIuKA+r84ZDvl
        34H56M6B6K58Ni7tInffki7I/A==
X-Google-Smtp-Source: 
 APXvYqwIgQwXtS11bXhGVH9Pe2V3XwcTTGW7CWEBZv0DL+719DfIpRZwWKHhcoYjgXjNyQ3lv3A/JQ==
X-Received: by 2002:adf:f5cb:: with SMTP id k11mr4164701wrp.71.1578672325294;
        Fri, 10 Jan 2020 08:05:25 -0800 (PST)
Received: from zen.linaroharston ([51.148.130.216])
        by smtp.gmail.com with ESMTPSA id
 p17sm2684593wmk.30.2020.01.10.08.05.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 10 Jan 2020 08:05:23 -0800 (PST)
Received: from zen.lan (localhost [127.0.0.1])
        by zen.linaroharston (Postfix) with ESMTP id 2601D1FF87;
        Fri, 10 Jan 2020 16:05:23 +0000 (GMT)
From: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, christoffer.dall@arm.com, maz@kernel.org,
	=?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-tests PATCH] arm: expand the timer tests
Date: Fri, 10 Jan 2020 16:05:11 +0000
Message-Id: <20200110160511.17821-1-alex.bennee@linaro.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This was an attempt to replicate a QEMU bug. However to trigger the
bug you need to have an offset set in EL2 which kvm-unit-tests is
unable to do. However it does exercise some more corner cases.

Bug: https://bugs.launchpad.net/bugs/1859021
Signed-off-by: Alex Bennée <alex.bennee@linaro.org>
---
 arm/timer.c | 27 ++++++++++++++++++++++++++-
 1 file changed, 26 insertions(+), 1 deletion(-)

```
#### [PATCH RFC 01/10] mm: Add pmd support for _PAGE_SPECIAL
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11328287
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A9444930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 19:06:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7EF2F208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 19:06:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="AnMka1g1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729021AbgAJTGJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 14:06:09 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:53634 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728900AbgAJTGD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 10 Jan 2020 14:06:03 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00AJ3Br1100944;
        Fri, 10 Jan 2020 19:04:44 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2019-08-05;
 bh=lmAqIjgm7HVbSyXw06vW1C3Rvk9MKSm3/YBzLlEguL0=;
 b=AnMka1g154EpkiM9ty3oJyhJn5eWfNl5iaIKez8elA1e04Peo9Aeateeo2qtcXUoJqKc
 ZxPNkT/ypti5w79K0d/0fReEG/D5KXOdi5es5Lmd6MKy2mEmpMTZnJLE+CLzoaJJXZj+
 zz37gPKnTkH0pMZ9NJWSZS/cM1b2LJs/Hq1pviSEV9L/wdxQbHsjZRhlTE3A01NiWZEt
 wMjuLQhx+lkmMDA1Ue6GN/WswconK96BMLUfVc/vYO3TOUstM6vCaeqGUfsCoDmXOroU
 dK2wo1Vpn6XP6n261naL7aPuAAppyBiaP24Mf9Nv+06hJejovTX9lYKCAD3Iwv/ks8b+ WA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 2xajnqm1aq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 19:04:43 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00AJ49CZ069268;
        Fri, 10 Jan 2020 19:04:43 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 2xevfebtjk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 19:04:43 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 00AJ4gMM020986;
        Fri, 10 Jan 2020 19:04:42 GMT
Received: from paddy.uk.oracle.com (/10.175.192.165)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 10 Jan 2020 11:04:41 -0800
From: Joao Martins <joao.m.martins@oracle.com>
To: linux-nvdimm@lists.01.org
Cc: Dan Williams <dan.j.williams@intel.com>,
        Vishal Verma <vishal.l.verma@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Ira Weiny <ira.weiny@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        Andrew Morton <akpm@linux-foundation.org>, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        Liran Alon <liran.alon@oracle.com>,
        Nikita Leshenko <nikita.leshchenko@oracle.com>,
        Barret Rhoden <brho@google.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Matthew Wilcox <willy@infradead.org>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Subject: [PATCH RFC 01/10] mm: Add pmd support for _PAGE_SPECIAL
Date: Fri, 10 Jan 2020 19:03:04 +0000
Message-Id: <20200110190313.17144-2-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
In-Reply-To: <20200110190313.17144-1-joao.m.martins@oracle.com>
References: <20200110190313.17144-1-joao.m.martins@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9496
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-2001100154
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9496
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-2001100154
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently vmf_insert_pfn_pmd only works with devmap
and BUG_ON otherwise. Add support for handling
page special when pfn_t has it marked with PFN_SPECIAL.

Usage of page special aren't expected to do GUP
hence return no pages on gup_huge_pmd() much like how
it is done for ptes on gup_pte_range().

This allows a DAX driver to handle 2M hugepages without
struct pages.

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
---
 arch/x86/include/asm/pgtable.h | 16 +++++++++++++++-
 mm/gup.c                       |  3 +++
 mm/huge_memory.c               |  7 ++++---
 mm/memory.c                    |  3 ++-
 4 files changed, 24 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH v7 1/4] s390x: export sclp_setup_int
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11328239
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E5FF930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 18:41:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 17B002072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 18:41:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728650AbgAJSlD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 13:41:03 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:18554 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728083AbgAJSk7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 13:40:59 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00AIbK6B119764
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 13:40:58 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xef1umnu4-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 13:40:57 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Fri, 10 Jan 2020 18:40:56 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 10 Jan 2020 18:40:53 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00AIep1951642400
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 18:40:51 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BD572AE053;
        Fri, 10 Jan 2020 18:40:51 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 788C7AE04D;
        Fri, 10 Jan 2020 18:40:51 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.108])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 10 Jan 2020 18:40:51 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v7 1/4] s390x: export sclp_setup_int
Date: Fri, 10 Jan 2020 19:40:47 +0100
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200110184050.191506-1-imbrenda@linux.ibm.com>
References: <20200110184050.191506-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011018-0020-0000-0000-0000039FA39C
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011018-0021-0000-0000-000021F70C84
Message-Id: <20200110184050.191506-2-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-10_01:2020-01-10,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 priorityscore=1501 lowpriorityscore=0 mlxlogscore=999 malwarescore=0
 suspectscore=1 clxscore=1015 adultscore=0 mlxscore=0 bulkscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001100150
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export sclp_setup_int() so that it can be used in tests.

Needed for an upcoming unit test.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/sclp.h | 1 +
 lib/s390x/sclp.c | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v5] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11327067
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68F87109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 09:47:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3270C2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 09:47:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727310AbgAJJrM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 04:47:12 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:51786 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727274AbgAJJrL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 04:47:11 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00A9hM0H130627
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 04:47:10 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xea2kcdks-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 04:47:10 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 10 Jan 2020 09:47:08 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 10 Jan 2020 09:47:05 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00A9kGE042926480
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 09:46:16 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 48A1DA405C;
        Fri, 10 Jan 2020 09:47:04 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 91641A405B;
        Fri, 10 Jan 2020 09:47:02 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.153.163])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 10 Jan 2020 09:47:02 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [PATCH v5] KVM: s390: Add new reset vcpu API
Date: Fri, 10 Jan 2020 04:46:59 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011009-0012-0000-0000-0000037C308F
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011009-0013-0000-0000-000021B85457
Message-Id: <20200110094659.4118-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-10_01:2020-01-10,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 mlxscore=0
 malwarescore=0 suspectscore=1 spamscore=0 clxscore=1015 priorityscore=1501
 mlxlogscore=999 impostorscore=0 lowpriorityscore=0 phishscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001100083
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that on a normal reset.

Let's implement an interface for the missing normal and clear resets
and reset all local IRQs, registers and control structures as stated
in the architecture.

Userspace might already reset the registers via the vcpu run struct,
but as we need the interface for the interrupt clearing part anyway,
we implement the resets fully and don't rely on userspace to reset the
rest.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 Documentation/virt/kvm/api.txt |  45 +++++++++++++
 arch/s390/kvm/kvm-s390.c       | 111 +++++++++++++++++++++++----------
 include/uapi/linux/kvm.h       |   5 ++
 3 files changed, 127 insertions(+), 34 deletions(-)

```
#### [PATCH v6] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11327133
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9A26930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 10:19:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC09F2080D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 10:19:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727458AbgAJKTQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 05:19:16 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21276 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727362AbgAJKTQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 05:19:16 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00AACYu9008313
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 05:19:15 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xe7m3b3x6-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 05:19:15 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 10 Jan 2020 10:19:13 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 10 Jan 2020 10:19:10 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00AAIL7n28508434
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 10:18:21 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8C7F1A405C;
        Fri, 10 Jan 2020 10:19:09 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 07412A4054;
        Fri, 10 Jan 2020 10:19:08 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.153.163])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 10 Jan 2020 10:19:07 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [PATCH v6] KVM: s390: Add new reset vcpu API
Date: Fri, 10 Jan 2020 05:19:06 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011010-0012-0000-0000-0000037C32B6
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011010-0013-0000-0000-000021B8568F
Message-Id: <20200110101906.54291-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-10_01:2020-01-10,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=1
 impostorscore=0 mlxscore=0 clxscore=1015 phishscore=0 mlxlogscore=999
 lowpriorityscore=0 bulkscore=0 priorityscore=1501 adultscore=0 spamscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001100088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that on a normal reset.

Let's implement an interface for the missing normal and clear resets
and reset all local IRQs, registers and control structures as stated
in the architecture.

Userspace might already reset the registers via the vcpu run struct,
but as we need the interface for the interrupt clearing part anyway,
we implement the resets fully and don't rely on userspace to reset the
rest.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

Based on the irc discussion.

---
 Documentation/virt/kvm/api.txt |  43 ++++++++++++
 arch/s390/kvm/kvm-s390.c       | 115 +++++++++++++++++++++++----------
 include/uapi/linux/kvm.h       |   5 ++
 3 files changed, 130 insertions(+), 33 deletions(-)

```
#### [PATCH v7] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11327203
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D28B892A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 11:45:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A699320661
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 11:45:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727750AbgAJLpw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 06:45:52 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39622 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727689AbgAJLpw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 06:45:52 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00ABi29t074004
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 06:45:50 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xerex0bca-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 06:45:50 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 10 Jan 2020 11:45:49 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 10 Jan 2020 11:45:46 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00ABjjHf28967004
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 11:45:45 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7BC524C059;
        Fri, 10 Jan 2020 11:45:45 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F0FCA4C052;
        Fri, 10 Jan 2020 11:45:43 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.153.163])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 10 Jan 2020 11:45:43 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [PATCH v7] KVM: s390: Add new reset vcpu API
Date: Fri, 10 Jan 2020 06:45:40 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011011-0008-0000-0000-000003483C0B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011011-0009-0000-0000-00004A688591
Message-Id: <20200110114540.90713-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-10_01:2020-01-10,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 lowpriorityscore=0 malwarescore=0 suspectscore=1 clxscore=1015 bulkscore=0
 mlxscore=0 adultscore=0 priorityscore=1501 phishscore=0 mlxlogscore=999
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001100100
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that on a normal reset.

Let's implement an interface for the missing normal and clear resets
and reset all local IRQs, registers and control structures as stated
in the architecture.

Userspace might already reset the registers via the vcpu run struct,
but as we need the interface for the interrupt clearing part anyway,
we implement the resets fully and don't rely on userspace to reset the
rest.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virt/kvm/api.txt |  43 +++++++++++++
 arch/s390/kvm/kvm-s390.c       | 112 +++++++++++++++++++++++----------
 include/uapi/linux/kvm.h       |   5 ++
 3 files changed, 127 insertions(+), 33 deletions(-)

```
