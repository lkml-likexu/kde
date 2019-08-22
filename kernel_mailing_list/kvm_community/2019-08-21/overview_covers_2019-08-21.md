

#### [PATCH v2 0/3] KVM: x86: fixes for speculation bug feature reporting
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed Aug 21 08:26:39 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11106101
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 527431395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 08:27:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2711D2339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 08:27:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="dT8WftTi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727393AbfHUI0r (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 04:26:47 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:55037 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726409AbfHUI0r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 04:26:47 -0400
Received: by mail-wm1-f65.google.com with SMTP id p74so1174913wme.4;
        Wed, 21 Aug 2019 01:26:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=8a1RxKgl4Ho99BSDrm3kp2pAknY5o067UUqOAsK0EP0=;
        b=dT8WftTimyE7Yxj68nlu4Izp6oOh20ppEAjBdSuZMO0uCVE6wu0b2+HOly3r1AQEYe
         sVD330ISGuOhleQRplfaMjsVooBZlMCryBWft8NYK5EUZUMg3i4FcFd+kCauPgsYVIX7
         nqrtRjqLbHddpMJfRxRSkv6p/0c43MYLUCY2dUg6Z6+A5KV3V0sbgAdaEpEe7CeMQkJh
         I/6UdtzDgD/J7EwEn+vc9lwWLR6KZgFFiM/Vb2AWiugKHbWDlLZMuC0gV/QEU5CJZYdm
         e9sLkBiJHPNu43V5Lf9e1lenVHuY1iXxDXb6dvXRZvY/QVSGCsaGtoR6aGuJ6cgrccXP
         Di0A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=8a1RxKgl4Ho99BSDrm3kp2pAknY5o067UUqOAsK0EP0=;
        b=sY5Pe4E5lpAUAGk+SS9nH6bBC2q5EJX6w8oSJaYW7fz9933ZG5NGeGCGLZcKQV537A
         U8bLs6axYtYmQWEC9ClEMnjtTl4hDYWjLE2G91qHsUOCKH1qa6fNnbovjm1vhHvFFN6t
         74EFRUxxaylH+gTMVlC45C0njXoJUYxo/+IIPlmGLJK2hMelwRfjmtCPxoUqproumdpr
         IFM31JGHmZ0omHc5phwPZ2RJoXw2O3bnBYpEIInsy5Ewx1Q5ktlEfWpw9Lrs/6B0kw9Q
         rsqXrrRawPcMXl0zEYwFE4MthAD7Pp4DBYp7leh/3+e+VsmNV5oTNgSuBip7U5Ujkvdq
         iF2Q==
X-Gm-Message-State: APjAAAXTxqaud7o4/nJrPHoJjlQ8lEBz+iptSv42mfwojafNHDAzorpM
        vvbH1rmKlYK+4MkiXgdUCms+5h1r+sE=
X-Google-Smtp-Source: 
 APXvYqyy/d0jhexMZME5uEI9ZADdvOfT+nlmvPZwLeJB1ms/t5JydsYI16TK5wdsJgX25jSNiAOIsQ==
X-Received: by 2002:a05:600c:2111:: with SMTP id
 u17mr4847080wml.64.1566376004647;
        Wed, 21 Aug 2019 01:26:44 -0700 (PDT)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w5sm2931892wmm.43.2019.08.21.01.26.43
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 01:26:43 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@redhat.com, ehabkost@redhat.com, konrad.wilk@oracle.com
Subject: [PATCH v2 0/3] KVM: x86: fixes for speculation bug feature reporting
Date: Wed, 21 Aug 2019 10:26:39 +0200
Message-Id: <1566376002-17121-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patches 1 and 2 are the same as the previous patch, but using
svm_get_supported_cpuid and with a fix to the placement of cpuid_mask.

Patch 3 is new and, unlike the previous one, will only be in kvm/next.

Paolo Bonzini (3):
  KVM: x86: fix reporting of AMD speculation bug CPUID leaf
  KVM: x86: always expose VIRT_SSBD to guests
  KVM: x86: use Intel speculation bugs and features as derived in
    generic x86 code

 arch/x86/kvm/cpuid.c | 27 +++++++++++++++++++--------
 arch/x86/kvm/svm.c   | 13 +++++++++----
 arch/x86/kvm/x86.c   |  7 +++++++
 3 files changed, 35 insertions(+), 12 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/4] s390x: More emulation tests
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Aug 21 10:47:32 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11106343
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B289C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 10:48:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B4AD233A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 10:48:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727138AbfHUKsl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 06:48:41 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:62106 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727099AbfHUKsk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 21 Aug 2019 06:48:40 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7LAmZMR021096
        for <kvm@vger.kernel.org>; Wed, 21 Aug 2019 06:48:39 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2uh2wdm7tw-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 21 Aug 2019 06:48:37 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 21 Aug 2019 11:48:16 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 21 Aug 2019 11:48:13 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7LAmCh846792894
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 21 Aug 2019 10:48:12 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 67314AE051;
        Wed, 21 Aug 2019 10:48:12 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6869AAE04D;
        Wed, 21 Aug 2019 10:48:11 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.3.179])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 21 Aug 2019 10:48:11 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/4] s390x: More emulation tests
Date: Wed, 21 Aug 2019 12:47:32 +0200
X-Mailer: git-send-email 2.17.0
X-TM-AS-GCONF: 00
x-cbid: 19082110-0008-0000-0000-0000030B6A65
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082110-0009-0000-0000-00004A299507
Message-Id: <20190821104736.1470-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-21_04:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=741 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908210116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch allows for CECSIM booting via PSW restart.
The other ones add diag288 and STSI tests.

v2:

* Tested under TCG
* Split out stsi into library
* Addressed review

Janosch Frank (4):
  s390x: Support PSW restart boot
  s390x: Diag288 test
  s390x: Move stsi to library
  s390x: STSI tests

 lib/s390x/asm/arch_def.h |  17 +++++
 s390x/Makefile           |   2 +
 s390x/diag288.c          | 131 +++++++++++++++++++++++++++++++++++++++
 s390x/flat.lds           |  14 +++--
 s390x/skey.c             |  18 ------
 s390x/stsi.c             |  84 +++++++++++++++++++++++++
 s390x/unittests.cfg      |   7 +++
 7 files changed, 250 insertions(+), 23 deletions(-)
 create mode 100644 s390x/diag288.c
 create mode 100644 s390x/stsi.c
```
#### [PATCH v6 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Wed Aug 21 14:59:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11107225
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9D461399
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 14:59:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A4E7E2339F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 14:59:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="f0fycqMF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728524AbfHUO72 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 10:59:28 -0400
Received: from mail-pf1-f194.google.com ([209.85.210.194]:35666 "EHLO
        mail-pf1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726530AbfHUO71 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 10:59:27 -0400
Received: by mail-pf1-f194.google.com with SMTP id d85so1611057pfd.2;
        Wed, 21 Aug 2019 07:59:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=Z5zNV+aGEXnZe0+CPgdtnFJ8dRf/r2ygP8Iohve0Rps=;
        b=f0fycqMFGS1JWxp1KhvwIftJwqDZPus1tTQemthJDQYeojm77cFV7cVWmH5S1Gac4V
         EprUkqhJletcvmlAj1qn9J3/X5GtO5Ba1MJjYPyhBg17L3ymOQILNaNynrz322LN9KMn
         ozCbINmOAl05/syfAkDa8J2ppNOPXR4kQr+k8VytHd+4Bj12QnYc2FtR5jx1lUEu2rFB
         XLF0YeUfPnVuaBtNPkigEZnTKdzINmRTFb6yG00JjThyNla6wNXxc8xX33tMWJnhVVry
         xw3dNLW7LJth/U7S71Mdl+g5ukquPnozyRuUpAGh3hQxXfvMgPjg1d4u+jw6e5tUaezs
         w0WA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=Z5zNV+aGEXnZe0+CPgdtnFJ8dRf/r2ygP8Iohve0Rps=;
        b=FB193W0gefwKI2s9xOGISxaR8qGojEQfgKkosP6XxPufhYR8bTLmOq1WUkTidVjgxf
         pKao4j25A6zS+P8kOA+ChQBGK/mpQptjlXf4AatLArBZWNt+pAHEm8NzF6xmBk+D6rbb
         WXDWdI0R7uJbwE5cUMCXrFFJG1D9X1lKo8lfXAjQ/DaGorKFx0SiuzM5Q6JYk644AqQi
         v3rdk13Xn/519JuC4zHQW58hzoW0PYbd6F+ue10cpF3A6EWZRUByS+0rFl5OMsvQmOgk
         bqv2N1DLbQeo8DCUdo76UhiUe2tciSe08obxwIZZl/OiJP63Ca01jtELBjkANFFWJZre
         JYkw==
X-Gm-Message-State: APjAAAXOq40iPqsYAFZvRt0JL/4l91dAw005HUy5Ox364YSelRiRbb+U
        FHiDhW9UBD97Eno+xBpQF2I=
X-Google-Smtp-Source: 
 APXvYqzrFyVlorWkueXx9HRBuLKcOcy2Opun+O4OOr1HVzfU2JfHa3PQ1/39vsylKSV3Xcp4yieOtQ==
X-Received: by 2002:a17:90a:8991:: with SMTP id
 v17mr410994pjn.120.1566399566511;
        Wed, 21 Aug 2019 07:59:26 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 f12sm22513826pgo.85.2019.08.21.07.59.25
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 21 Aug 2019 07:59:25 -0700 (PDT)
Subject: [PATCH v6 0/6] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: nitesh@redhat.com, kvm@vger.kernel.org, mst@redhat.com,
        david@redhat.com, dave.hansen@intel.com,
        linux-kernel@vger.kernel.org, willy@infradead.org,
        mhocko@kernel.org, linux-mm@kvack.org, akpm@linux-foundation.org,
        virtio-dev@lists.oasis-open.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com, riel@surriel.com,
        konrad.wilk@oracle.com, lcapitulino@redhat.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com
Date: Wed, 21 Aug 2019 07:59:24 -0700
Message-ID: <20190821145806.20926.22448.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as unused page reporting

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of reported pages in a given free area.
When the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page reporting which consists of
pulling pages off of free list and placing them into a scatter list. The
scatterlist is then given to the page reporting device and it will perform
the required action to make the pages "reported", in the case of
virtio-balloon this results in the pages being madvised as MADV_DONTNEED
and as such they are forced out of the guest. After this they are placed
back on the free list, and an additional bit is added if they are not
merged indicating that they are a reported buddy page instead of a
standard buddy page. The cycle then repeats with additional non-reported
pages being pulled until the free areas all consist of reported pages.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints. The upper limit for this is based on the size of the
queue used to store the scattergather list.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 40g on a 40g guest and watching the total
free memory via /proc/meminfo on the host. With this I have verified most
of the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. I have modified it to use Transparent Huge Pages. With this I
see almost no difference, -0.08%, with the patches applied and the feature
disabled. I see a regression of -0.86% with the feature enabled, but the
madvise disabled in the hypervisor due to a device being assigned. With
the feature fully enabled I see a regression of -3.27% versus the baseline
without these patches applied. In my testing I found that most of the
overhead was due to the page zeroing that comes as a result of the pages
having to be faulted back into the guest.

One side effect of these patches is that the guest becomes much more
resilient in terms of NUMA locality. With the pages being freed and then
reallocated when used it allows for the pages to be much closer to the
active thread, and as a result there can be situations where this patch
set will out-perform the stock kernel when the guest memory is not local
to the guest vCPUs. To avoid that in my testing I set the affinity of all
the vCPUs and QEMU instance to the same node.

Changes from the RFC:
https://lore.kernel.org/lkml/20190530215223.13974.22445.stgit@localhost.localdomain/
Moved aeration requested flag out of aerator and into zone->flags.
Moved boundary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.

Changes from v1:
https://lore.kernel.org/lkml/20190619222922.1231.27432.stgit@localhost.localdomain/
Dropped "waste page treatment" in favor of "page hinting"
Renamed files and functions from "aeration" to "page_hinting"
Moved from page->lru list to scatterlist
Replaced wait on refcnt in shutdown with RCU and cancel_delayed_work_sync
Virtio now uses scatterlist directly instead of intermediate array
Moved stats out of free_area, now in separate area and pointed to from zone
Merged patch 5 into patch 4 to improve review-ability
Updated various code comments throughout

Changes from v2:
https://lore.kernel.org/lkml/20190724165158.6685.87228.stgit@localhost.localdomain/
Dropped "page hinting" in favor of "page reporting"
Renamed files from "hinting" to "reporting"
Replaced "Hinted" page type with "Reported" page flag
Added support for page poisoning while hinting is active
Add QEMU patch that implements PAGE_POISON feature

Changes from v3:
https://lore.kernel.org/lkml/20190801222158.22190.96964.stgit@localhost.localdomain/
Added mutex lock around page reporting startup and shutdown
Fixed reference to "page aeration" in patch 2
Split page reporting function bit out into separate QEMU patch
Limited capacity of scatterlist to vq size - 1 instead of vq size
Added exception handling for case of virtio descriptor allocation failure

Changes from v4:
https://lore.kernel.org/lkml/20190807224037.6891.53512.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_cycle()
Dropped if/continue for ternary operator in page_reporting_process()
Added checks for isolate and cma types to for_each_reporting_migratetype_order
Added virtio-dev, Michal Hocko, and Oscar Salvador to to:/cc:
Rebased on latest linux-next and QEMU git trees

Changes from v5:
https://lore.kernel.org/lkml/20190812213158.22097.30576.stgit@localhost.localdomain/
Replaced spin_(un)lock with spin_(un)lock_irq in page_reporting_startup()
Updated shuffle code to use "shuffle_pick_tail" and updated patch description
Dropped storage of order and migratettype while page is being reported
Used get_pfnblock_migratetype to determine migratetype of page
Renamed put_reported_page to free_reported_page, added order as argument
Dropped check for CMA type as I believe we should be reporting those
Added code to allow moving of reported pages into and out of isolation
Defined page reporting order as minimum of Huge Page size vs MAX_ORDER - 1
Cleaned up use of static branch usage for page_reporting_notify_enabled
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   84 ++++++++-
 include/linux/mmzone.h              |  124 ++++++++-----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |  177 ++++++++++++++++++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/internal.h                       |   18 ++
 mm/memory_hotplug.c                 |    1 
 mm/page_alloc.c                     |  216 ++++++++++++++++-------
 mm/page_reporting.c                 |  336 +++++++++++++++++++++++++++++++++++
 mm/shuffle.c                        |   40 +++-
 mm/shuffle.h                        |   12 +
 14 files changed, 896 insertions(+), 131 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

--
```
#### [PATCH v3 00/10] arm64: Stolen time support
##### From: Steven Price <steven.price@arm.com>

```c
From patchwork Wed Aug 21 15:36:46 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11107387
Return-Path: <SRS0=nXzg=WR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C2F91813
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:38:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 54B942339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 21 Aug 2019 15:38:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729287AbfHUPhO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 21 Aug 2019 11:37:14 -0400
Received: from foss.arm.com ([217.140.110.172]:60322 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728848AbfHUPhO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Aug 2019 11:37:14 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 6C3FB337;
        Wed, 21 Aug 2019 08:37:13 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 609123F718;
        Wed, 21 Aug 2019 08:37:11 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v3 00/10] arm64: Stolen time support
Date: Wed, 21 Aug 2019 16:36:46 +0100
Message-Id: <20190821153656.33429-1-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series add support for paravirtualized time for arm64 guests and
KVM hosts following the specification in Arm's document DEN 0057A:

https://developer.arm.com/docs/den0057/a

It implements support for stolen time, allowing the guest to
identify time when it is forcibly not executing.

It doesn't implement support for Live Physical Time (LPT) as there are
some concerns about the overheads and approach in the above
specification, and I expect an updated version of the specification to
be released soon with just the stolen time parts.

NOTE: Patches 8 and 9 will conflict with Mark Rutland's series[1] cleaning
up the SMCCC conduit. I do feel that the addition of an _invoke() call
makes a number of call sites cleaner and it should be possible to
integrate both this and Mark's other cleanups.

[1] https://lore.kernel.org/linux-arm-kernel/20190809132245.43505-1-mark.rutland@arm.com/

Also available as a git tree:
git://linux-arm.org/linux-sp.git stolen_time/v3

Changes from v2:
https://lore.kernel.org/lkml/20190819140436.12207-1-steven.price@arm.com/
 * Switched from using gfn_to_hva_cache to a new macro kvm_put_guest()
   that can provide the single-copy atomicity required (on arm64). This
   macro is added in patch 4.
 * Tidied up the locking for kvm_update_stolen_time().
   pagefault_disable() was unnecessary and the caller didn't need to
   take kvm->srcu as the function does it itself.
 * Removed struct kvm_arch_pvtime from the arm implementation, replaced
   instead with inline static functions which are empty for arm.
 * Fixed a few checkpatch --strict warnings.

Changes from v1:
https://lore.kernel.org/lkml/20190802145017.42543-1-steven.price@arm.com/
 * Host kernel no longer allocates the stolen time structure, instead it
   is allocated by user space. This means the save/restore functionality
   can be removed.
 * Refactored the code so arm has stub implementations and to avoid
   initcall
 * Rebased to pick up Documentation/{virt->virtual} change
 * Bunch of typo fixes

Christoffer Dall (1):
  KVM: arm/arm64: Factor out hypercall handling from PSCI code

Steven Price (9):
  KVM: arm64: Document PV-time interface
  KVM: arm64: Implement PV_FEATURES call
  KVM: Implement kvm_put_guest()
  KVM: arm64: Support stolen time reporting via shared structure
  KVM: Allow kvm_device_ops to be const
  KVM: arm64: Provide a PV_TIME device to user space
  arm/arm64: Provide a wrapper for SMCCC 1.1 calls
  arm/arm64: Make use of the SMCCC 1.1 wrapper
  arm64: Retrieve stolen time as paravirtualized guest

 Documentation/virt/kvm/arm/pvtime.txt | 100 ++++++++++++++
 arch/arm/include/asm/kvm_host.h       |  30 +++++
 arch/arm/kvm/Makefile                 |   2 +-
 arch/arm/kvm/handle_exit.c            |   2 +-
 arch/arm/mm/proc-v7-bugs.c            |  13 +-
 arch/arm64/include/asm/kvm_host.h     |  28 +++-
 arch/arm64/include/asm/paravirt.h     |   9 +-
 arch/arm64/include/asm/pvclock-abi.h  |  17 +++
 arch/arm64/include/uapi/asm/kvm.h     |   8 ++
 arch/arm64/kernel/cpu_errata.c        |  80 ++++-------
 arch/arm64/kernel/paravirt.c          | 148 +++++++++++++++++++++
 arch/arm64/kernel/time.c              |   3 +
 arch/arm64/kvm/Kconfig                |   1 +
 arch/arm64/kvm/Makefile               |   2 +
 arch/arm64/kvm/handle_exit.c          |   4 +-
 include/kvm/arm_hypercalls.h          |  43 ++++++
 include/kvm/arm_psci.h                |   2 +-
 include/linux/arm-smccc.h             |  58 ++++++++
 include/linux/cpuhotplug.h            |   1 +
 include/linux/kvm_host.h              |  28 +++-
 include/linux/kvm_types.h             |   2 +
 include/uapi/linux/kvm.h              |   2 +
 virt/kvm/arm/arm.c                    |  11 ++
 virt/kvm/arm/hypercalls.c             |  68 ++++++++++
 virt/kvm/arm/psci.c                   |  84 +-----------
 virt/kvm/arm/pvtime.c                 | 182 ++++++++++++++++++++++++++
 virt/kvm/kvm_main.c                   |   6 +-
 27 files changed, 780 insertions(+), 154 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
