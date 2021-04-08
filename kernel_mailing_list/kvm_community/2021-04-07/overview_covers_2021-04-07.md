

#### [PATCH v2 00/19] Fix broken documentation file references
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Wed Apr  7 08:20:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12187419
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_NONE,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 37B7DC43603
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 08:21:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D052F613A7
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 08:21:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1347003AbhDGIVW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 04:21:22 -0400
Received: from mail.kernel.org ([198.145.29.99]:48644 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S240626AbhDGIVR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 04:21:17 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 8F450613CF;
        Wed,  7 Apr 2021 08:21:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1617783662;
        bh=1IWlmRG9OD413dWYIjvrcWiKG5N1mPS/69ftZBnxCPE=;
        h=From:To:Cc:Subject:Date:From;
        b=MU/hOdvwtzxehLxToSu65R5aOnRU3HIBxCz57ZiasngM+1MaaWazON3N+zEdOJZYr
         lE/KionJZjqUql+6V09QR1bUu6M/Qzp30HMFgSPenbnw9CCxb2i+Qqcl0VX7BDmpmR
         72Bj0HiREn8JRuhw+qPf2Z0zeTluUs0xTJtuLdltHzF1SvY7HcsWGui04BfyRIU/J3
         RBXvcAMPzUyJR/kmeTo5tEfpXoyEyzNJ088/ukU4X+xY5oshHbYlcUgWMGVUob0u3b
         6EIxlJUed/GABQ+UyyICvPqtEJrxu8Ym8Ad1HvtfmGdAqRpoZG0oW++4Tx/bGTfSnR
         oSZ3RBmaWKnhg==
Received: by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1lU3Qq-005i24-4N; Wed, 07 Apr 2021 10:21:00 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
 linux-kernel@vger.kernel.org,
 =?utf-8?q?Przemys=C5=82aw_Gaj?= <pgaj@cadence.com>,
 Akira Yokosawa <akiyks@gmail.com>,
 Alexandre Belloni <alexandre.belloni@bootlin.com>,
 Daniel Lustig <dlustig@nvidia.com>, Daniel Vetter <daniel@ffwll.ch>,
 David Airlie <airlied@linux.ie>, Dmitry Torokhov <dmitry.torokhov@gmail.com>,
 Federico Vaga <federico.vaga@vaga.pv.it>, Guenter Roeck <linux@roeck-us.net>,
 Harry Wei <harryxiyou@gmail.com>, Jean Delvare <jdelvare@suse.com>,
 Joel Fernandes <joel@joelfernandes.org>,
 Lars-Peter Clausen <lars@metafoo.de>,
 Matthias Brugger <matthias.bgg@gmail.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Peter Meerwald-Stadler <pmeerw@pmeerw.net>, Rob Herring <robh+dt@kernel.org>,
 Sebastian Reichel <sre@kernel.org>, Vitor Soares <vitor.soares@synopsys.com>,
 devicetree@vger.kernel.org, dri-devel@lists.freedesktop.org,
 kvm@vger.kernel.org, linux-arch@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, linux-hwmon@vger.kernel.org,
 linux-i3c@lists.infradead.org, linux-iio@vger.kernel.org,
 linux-input@vger.kernel.org, linux-media@vger.kernel.org,
 linux-mediatek@lists.infradead.org, linux-pm@vger.kernel.org
Subject: [PATCH v2 00/19] Fix broken documentation file references
Date: Wed,  7 Apr 2021 10:20:39 +0200
Message-Id: <cover.1617783062.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Jon,

As files keep being moved around and DT bindings are 
converted and renamed to yaml, their doc references get 
outdated, pointing to an invalid places.

This series address those. It is based on the top of docs-next tree,
and most patches here are independent from the other ones.

v2:
  - Dropped patches that were already applied, Most of those
    will be following via Jonathan Cameron's iio tree;
  - Dropped patches that don't apply on the top of docs next.
  - Added some new patches fixing other breakages.

PS.:  
  I placed the dropped patches on a separate branch. I'll track 
  them and re-submit any missing ones after -rc1.

Mauro Carvalho Chehab (19):
  MAINTAINERS: update ste,mcde.yaml reference
  MAINTAINERS: update brcm,bcm-v3d.yaml reference
  MAINTAINERS: update fsl,dpaa2-console.yaml reference
  MAINTAINERS: update mtk-sd.yaml reference
  MAINTAINERS: update snps,dw-axi-dmac.yaml reference
  dt-bindings: don't use ../dir for doc references
  dt-bindings: fix references for iio-bindings.txt
  dt-bindings: iommu: mediatek: update mediatek,iommu.yaml references
  dt-bindings: i3c: update i3c.yaml references
  dt-bindings:iio:adc: update motorola,cpcap-adc.yaml reference
  dt-bindings:iio:adc: update dlg,da9150-gpadc.yaml reference
  dt-bindings: power: supply: da9150: update da9150-charger.txt
    reference
  dt-bindings: power: supply: da9150: update da9150-fg.txt reference
  docs: update sysfs-platform_profile.rst reference
  docs: update rcu_dereference.rst reference
  docs: vcpu-requests.rst: fix reference for atomic ops
  docs: replace transation references for reporting-bugs.rst
  docs: translations/zh_CN: fix a typo at 8.Conclusion.rst
  docs: sched-bwc.rst: fix a typo on a doc name

 .../bindings/display/mediatek/mediatek,disp.txt  |  2 +-
 .../devicetree/bindings/hwmon/ntc_thermistor.txt |  2 +-
 .../devicetree/bindings/i3c/cdns,i3c-master.txt  |  6 +++---
 .../bindings/i3c/snps,dw-i3c-master.txt          |  6 +++---
 .../devicetree/bindings/iio/adc/ingenic,adc.yaml |  5 +++--
 .../devicetree/bindings/input/adc-joystick.yaml  |  4 +++-
 .../input/touchscreen/resistive-adc-touch.txt    |  5 ++++-
 .../bindings/media/mediatek-jpeg-decoder.txt     |  2 +-
 .../bindings/media/mediatek-jpeg-encoder.txt     |  2 +-
 .../devicetree/bindings/media/mediatek-mdp.txt   |  2 +-
 .../bindings/media/mediatek-vcodec.txt           |  2 +-
 Documentation/devicetree/bindings/mfd/ab8500.txt |  4 +++-
 Documentation/devicetree/bindings/mfd/da9150.txt |  8 ++++----
 .../devicetree/bindings/mfd/motorola-cpcap.txt   | 16 ++++++++--------
 .../bindings/power/supply/da9150-charger.txt     |  2 +-
 Documentation/scheduler/sched-bwc.rst            |  2 +-
 .../translations/it_IT/process/howto.rst         |  2 +-
 Documentation/translations/ja_JP/howto.rst       |  2 +-
 Documentation/translations/zh_CN/SecurityBugs    |  2 +-
 .../zh_CN/admin-guide/reporting-issues.rst       |  4 ++--
 .../translations/zh_CN/process/8.Conclusion.rst  |  2 +-
 .../translations/zh_CN/process/howto.rst         |  2 +-
 Documentation/virt/kvm/vcpu-requests.rst         |  2 +-
 MAINTAINERS                                      | 10 +++++-----
 include/linux/platform_profile.h                 |  2 +-
 tools/memory-model/Documentation/glossary.txt    |  2 +-
 26 files changed, 54 insertions(+), 46 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/7] s390: Add support for large pages
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Wed Apr  7 12:42:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12187949
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8CF7AC433ED
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 12:42:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B0D761359
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 12:42:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243168AbhDGMm1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 08:42:27 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:39246 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229615AbhDGMm0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Apr 2021 08:42:26 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 137CXUlZ083278;
        Wed, 7 Apr 2021 08:42:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=qiPZxDT5xpw5aEMhdIKhnmtraJWLLkMe/zzUUNH+roE=;
 b=nj6rRNmTXEHVM/40LZZpkqMIQgh/3ee8DNo1SyAO/bjSXASrVOuasgO70KPUYhdbfv3r
 Q6Zus/5lp9ptn15Y24dwjN68TdIZ+vWlIclmEfBoWOSMlG8otb0AD1ScU9EbUdA6MejX
 9G+gzYr6z8ldJH3xImzrVLRpZUC9V0UwfIWZRu5c9oUwxFXLBXV8wR2KKFPsaDPqd/62
 gewZk+lcrutcGLzec1XVwg4KpaJ74O0hVlLMzuEF+gK90MdNEfO2jF63TvfJdFYpinGI
 ot0z/HZcPodeFhUNyedzPn7U8vk/cwAdgIFU/cb84lZpRWo3VMZQDatmWHcNj1mtOfUE ug==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37rvn0g75r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Apr 2021 08:42:16 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 137CY4bB084987;
        Wed, 7 Apr 2021 08:42:15 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37rvn0g74j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Apr 2021 08:42:15 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 137CXqKh012941;
        Wed, 7 Apr 2021 12:42:13 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06fra.de.ibm.com with ESMTP id 37rvbw0cpx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Apr 2021 12:42:13 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 137CgAIR46203146
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 7 Apr 2021 12:42:10 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 951B65204E;
        Wed,  7 Apr 2021 12:42:10 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.2.56])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 3C5975204F;
        Wed,  7 Apr 2021 12:42:10 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 0/7] s390: Add support for large pages
Date: Wed,  7 Apr 2021 14:42:02 +0200
Message-Id: <20210407124209.828540-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: _INqaYQC7DlcsZij8mxTyGRTsqQyqp8D
X-Proofpoint-ORIG-GUID: ZjK8AdcJiE9Qi0nxHaZ0jKwtKaPtBW6v
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-07_07:2021-04-07,2021-04-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 phishscore=0
 mlxlogscore=999 bulkscore=0 lowpriorityscore=0 suspectscore=0 adultscore=0
 spamscore=0 mlxscore=0 malwarescore=0 impostorscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104070087
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce support for large (1M) and huge (2G) pages.

Add a simple testcase for EDAT1 and EDAT2.

v2->v3
* Add proper macros for control register bits
* Improved patch titles and descriptions
* Moved definition of TEID bits to library
* Rebased on the lastest upstream branch

v1->v2

* split patch 2 -> new patch 2 and new patch 3
* patch 2: fixes pgtable.h, also fixes wrong usage of REGION_TABLE_LENGTH
  instead of SEGMENT_TABLE_LENGTH
* patch 3: introduces new macros and functions for large pages
* patch 4: remove erroneous double call to pte_alloc in get_pte
* patch 4: added comment in mmu.c to bridge the s390x architecural names
  with the Linux ones used in the kvm-unit-tests
* patch 5: added and fixed lots of comments to explain what's going on
* patch 5: set FC for region 3 after writing the canary, like for segments
* patch 5: use uintptr_t instead of intptr_t for set_prefix
* patch 5: introduce new macro PGD_PAGE_SHIFT instead of using magic value 41
* patch 5: use VIRT(0) instead of mem to make it more clear what we are
  doing, even though VIRT(0) expands to mem

Claudio Imbrenda (7):
  s390x: lib: add and use macros for control register bits
  libcflat: add SZ_1M and SZ_2G
  s390x: lib: fix pgtable.h
  s390x: lib: Add idte and other huge pages functions/macros
  s390x: lib: add PGM_TEID_* macros
  s390x: mmu: add support for large pages
  s390x: edat test

 s390x/Makefile            |   1 +
 lib/s390x/asm/arch_def.h  |  12 ++
 lib/s390x/asm/float.h     |   4 +-
 lib/s390x/asm/interrupt.h |  10 +-
 lib/s390x/asm/pgtable.h   |  44 +++++-
 lib/libcflat.h            |   2 +
 lib/s390x/mmu.h           |  73 +++++++++-
 lib/s390x/mmu.c           | 260 +++++++++++++++++++++++++++++++----
 lib/s390x/sclp.c          |   4 +-
 s390x/diag288.c           |   2 +-
 s390x/edat.c              | 279 ++++++++++++++++++++++++++++++++++++++
 s390x/gs.c                |   2 +-
 s390x/iep.c               |   4 +-
 s390x/skrf.c              |   2 +-
 s390x/smp.c               |   8 +-
 s390x/vector.c            |   2 +-
 s390x/unittests.cfg       |   3 +
 17 files changed, 663 insertions(+), 49 deletions(-)
 create mode 100644 s390x/edat.c
```
#### [PATCH 0/7] Hyper-V nested virt enlightenments for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
From patchwork Wed Apr  7 14:41:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12188583
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 36634C43470
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 14:41:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0877061359
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 14:41:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1344982AbhDGOlx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 10:41:53 -0400
Received: from linux.microsoft.com ([13.77.154.182]:52636 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233143AbhDGOlt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 10:41:49 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id 60D1220B5680;
        Wed,  7 Apr 2021 07:41:39 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com 60D1220B5680
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1617806499;
        bh=RW3dGYVmkQJ81p9LCGjxdTOdnRHf5p6gzfOsmE15srA=;
        h=From:To:Cc:Subject:Date:From;
        b=Us9lf1tq6SKsXOX+Gk+BQdwovWevpXxp5hu+/E96tUiFLiEJuPMLz8AkIaAYze5GT
         DZ82VSEuGo5lgEZeVhKduwj9EyrocE65Lt3ViUvUYjDKFLHpOOfXFAzYXLZRs1G/vA
         SZCcLItDLOtjouYdZpaytaAB6fxqDnv3wmm6gg4E=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH 0/7] Hyper-V nested virt enlightenments for SVM
Date: Wed,  7 Apr 2021 14:41:21 +0000
Message-Id: <cover.1617804573.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series enables the nested virtualization enlightenments for
SVM. This is very similar to the enlightenments for VMX except for the
fact that there is no enlightened VMCS. For SVM, VMCB is already an
in-memory data structure. The supported enlightenments are:

Enlightened TLB Flush: If this is enabled, ASID invalidations invalidate
only gva -> hpa entries. To flush entries derived from NPT, hyper-v
provided hypercalls (HvFlushGuestPhysicalAddressSpace or
HvFlushGuestPhysicalAddressList) should be used.

Enlightened MSR bitmap(TLFS 16.5.3): "When enabled, L0 hypervisor does
not monitor the MSR bitmaps for changes. Instead, the L1 hypervisor must
invalidate the corresponding clean field after making changes to one of
the MSR bitmaps."

Direct Virtual Flush(TLFS 16.8): The hypervisor exposes hypercalls
(HvFlushVirtualAddressSpace, HvFlushVirtualAddressSpaceEx,
HvFlushVirtualAddressList, and HvFlushVirtualAddressListEx) that allow
operating systems to more efficiently manage the virtual TLB. The L1
hypervisor can choose to allow its guest to use those hypercalls and
delegate the responsibility to handle them to the L0 hypervisor. This
requires the use of a partition assist page."

L2 Windows boot time was measured with and without the patch. Time was
measured from power on to the login screen and was averaged over a
consecutive 5 trials:
  Without the patch: 42 seconds
  With the patch: 29 seconds
---

Vineeth Pillai (7):
  hyperv: Detect Nested virtualization support for SVM
  hyperv: SVM enlightened TLB flush support flag
  KVM: x86: hyper-v: Move the remote TLB flush logic out of vmx
  KVM: SVM: hyper-v: Nested enlightenments in VMCB
  KVM: SVM: hyper-v: Remote TLB flush for SVM
  KVM: SVM: hyper-v: Enlightened MSR-Bitmap support
  KVM: SVM: hyper-v: Direct Virtual Flush support

 arch/x86/include/asm/hyperv-tlfs.h |   9 +++
 arch/x86/include/asm/kvm_host.h    |  15 ++++
 arch/x86/include/asm/svm.h         |  24 ++++++-
 arch/x86/kernel/cpu/mshyperv.c     |  10 ++-
 arch/x86/kvm/hyperv.c              |  89 +++++++++++++++++++++++
 arch/x86/kvm/hyperv.h              |  12 ++++
 arch/x86/kvm/svm/svm.c             | 110 +++++++++++++++++++++++++++++
 arch/x86/kvm/svm/svm.h             |  30 +++++++-
 arch/x86/kvm/vmx/vmx.c             |  97 ++-----------------------
 arch/x86/kvm/vmx/vmx.h             |  10 ---
 10 files changed, 302 insertions(+), 104 deletions(-)
```
#### [PATCH kvm-unit-tests 0/8] arm/arm64: Prepare for target-efi
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Wed Apr  7 18:59:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12189183
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6DF5EC433ED
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 18:59:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C8B961205
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 18:59:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239544AbhDGS7n (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 14:59:43 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:41650 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229512AbhDGS7l (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Apr 2021 14:59:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617821970;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=NkCAWgC0VrbjMRUHCeE8lLva3Zw4UiswnpFOb19Ka4g=;
        b=O4oPzVfedPljaDmbAnG/+ryxfETShl8yvtcPQqM6y/maVfwaBopf8DhQDKKOlSZECJyVom
        TC6he1Px/h0J+7v9ZEv5Sw0librPl6vP11SueW5S2LUJvjlwb1/HH0UpTMo/7p1De46068
        uYC6iffpcSuBdPr0leN1C8vIj/lfOU0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-189-tRVJ4OjSPcu8CB9D7xiMKQ-1; Wed, 07 Apr 2021 14:59:26 -0400
X-MC-Unique: tRVJ4OjSPcu8CB9D7xiMKQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 81A671006C85;
        Wed,  7 Apr 2021 18:59:25 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 370AC60CEA;
        Wed,  7 Apr 2021 18:59:20 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: alexandru.elisei@arm.com, nikos.nikoleris@arm.com,
        andre.przywara@arm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests 0/8] arm/arm64: Prepare for target-efi
Date: Wed,  7 Apr 2021 20:59:10 +0200
Message-Id: <20210407185918.371983-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a collection of patches derived from [1] that pave the
way for new targets, e.g. target-efi[2]. These patches mostly address
the elimination of memory map assumptions and they shouldn't have any
functional changes. The last two patches are a couple of patches not
related to the memory map, but they also prepare for bare metal targets.
I tossed them in since I don't think they should be too controversial.
This patch series is also available here [3].

[1] https://github.com/rhdrjones/kvm-unit-tests/commits/target-efi
[2] https://www.youtube.com/watch?v=kvaufVrL0J0
[3] https://gitlab.com/rhdrjones/kvm-unit-tests/-/commits/efiprep

Thanks,
drew


Andrew Jones (8):
  arm/arm64: Reorganize cstart assembler
  arm/arm64: Move setup_vm into setup
  pci-testdev: ioremap regions
  arm/arm64: mmu: Stop mapping an assumed IO region
  arm/arm64: mmu: Remove memory layout assumptions
  arm/arm64: setup: Consolidate memory layout assumptions
  chr-testdev: Silently fail init
  arm/arm64: psci: don't assume method is hvc

 arm/cstart.S           |  72 +++++++--------
 arm/cstart64.S         |  29 +++---
 arm/flat.lds           |  23 +++++
 arm/selftest.c         |  34 ++------
 lib/arm/asm/io.h       |   6 ++
 lib/arm/asm/mmu-api.h  |   1 +
 lib/arm/asm/mmu.h      |   1 +
 lib/arm/asm/page.h     |   2 +
 lib/arm/asm/psci.h     |   9 +-
 lib/arm/asm/setup.h    |   7 +-
 lib/arm/mmu.c          |  94 +++++++++++++++++---
 lib/arm/psci.c         |  17 +++-
 lib/arm/setup.c        | 194 +++++++++++++++++++++++++----------------
 lib/arm64/asm/io.h     |   6 ++
 lib/arm64/asm/mmu.h    |   1 +
 lib/arm64/asm/page.h   |   2 +
 lib/chr-testdev.c      |   5 +-
 lib/pci-host-generic.c |   5 +-
 lib/pci-host-generic.h |   4 +-
 lib/pci-testdev.c      |   4 +
 20 files changed, 339 insertions(+), 177 deletions(-)
```
#### [PATCH v4 00/11] KVM SGX virtualization support (KVM part)
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Wed Apr  7 20:49:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12189387
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AEA20C433B4
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 20:50:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 82DF7611CC
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 20:50:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231239AbhDGUuV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 16:50:21 -0400
Received: from mga05.intel.com ([192.55.52.43]:47225 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229586AbhDGUuV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 16:50:21 -0400
IronPort-SDR: 
 WXZ8l/OYZtr8quJD0NfBkywV9p1Gy2e7ulp/jteAO5ccq1KhevpdpqEPrTzG+F9uHOHgRMslk+
 jn8j2k0UwKnQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9947"; a="278660295"
X-IronPort-AV: E=Sophos;i="5.82,204,1613462400";
   d="scan'208";a="278660295"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2021 13:49:59 -0700
IronPort-SDR: 
 vFe3+KXld1UIaBO7mIXpjTMZ4P6NxTcooMCdqrrX59OChSLU2EuIE7PZ1fVLW0dnaVmdayqu/D
 /xRKS3NIjtKQ==
X-IronPort-AV: E=Sophos;i="5.82,204,1613462400";
   d="scan'208";a="415437309"
Received: from tkokeray-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.254.113.100])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2021 13:49:56 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, linux-sgx@vger.kernel.org
Cc: seanjc@google.com, pbonzini@redhat.com, bp@alien8.de,
        jarkko@kernel.org, dave.hansen@intel.com, luto@kernel.org,
        rick.p.edgecombe@intel.com, haitao.huang@intel.com
Subject: [PATCH v4 00/11] KVM SGX virtualization support (KVM part)
Date: Thu,  8 Apr 2021 08:49:24 +1200
Message-Id: <cover.1617825858.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo, Sean,

Boris has merged x86 part patches to the tip/x86/sgx. This series is KVM part
patches. Due to some code change in x86 part patches, two KVM patches need
update so this is the new version. Please help to review. Thanks!

Specifically, x86 patch (x86/sgx: Add helpers to expose ECREATE and EINIT to
KVM) was changed to return -EINVAL directly w/o setting trapnr when 
access_ok()s fail on any user pointers, so KVM patches:

KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)

were updated to handle this case.

This seris is still based on tip/x86/sgx (which is based on 5.12-rc3), since it
requires x86 patches to work. I tried to rebase them to latest kvm/queue, but
found patch 

KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
KVM: x86: Add capability to grant VM access to privileged SGX aattribute

have merge conflict, but the conflict is quite easy to resolve, so I didn't sent
out the resolved version. Please let me know how would you like to proceed.

Thank you all guys!

Sean Christopherson (11):
  KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}() for SGX (VMX)
  KVM: x86: Define new #PF SGX error code bit
  KVM: x86: Add support for reverse CPUID lookup of scattered features
  KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
  KVM: VMX: Add basic handling of VM-Exit from SGX enclave
  KVM: VMX: Frame in ENCLS handler for SGX virtualization
  KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
  KVM: VMX: Add emulation of SGX Launch Control LE hash MSRs
  KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)
  KVM: VMX: Enable SGX virtualization for SGX1, SGX2 and LC
  KVM: x86: Add capability to grant VM access to privileged SGX
    attribute

 Documentation/virt/kvm/api.rst  |  23 ++
 arch/x86/include/asm/kvm_host.h |   5 +
 arch/x86/include/asm/vmx.h      |   1 +
 arch/x86/include/uapi/asm/vmx.h |   1 +
 arch/x86/kvm/Makefile           |   2 +
 arch/x86/kvm/cpuid.c            |  89 +++++-
 arch/x86/kvm/cpuid.h            |  50 +++-
 arch/x86/kvm/vmx/nested.c       |  28 +-
 arch/x86/kvm/vmx/nested.h       |   5 +
 arch/x86/kvm/vmx/sgx.c          | 500 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h          |  34 +++
 arch/x86/kvm/vmx/vmcs12.c       |   1 +
 arch/x86/kvm/vmx/vmcs12.h       |   4 +-
 arch/x86/kvm/vmx/vmx.c          | 109 ++++++-
 arch/x86/kvm/vmx/vmx.h          |   2 +
 arch/x86/kvm/x86.c              |  23 ++
 include/uapi/linux/kvm.h        |   1 +
 17 files changed, 855 insertions(+), 23 deletions(-)
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [PATCH 0/4] Add support for XMM fast hypercalls
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
From patchwork Wed Apr  7 21:29:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12189439
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6EBA2C433B4
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 21:29:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 392E8611C9
	for <kvm@archiver.kernel.org>; Wed,  7 Apr 2021 21:29:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233250AbhDGVaE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 7 Apr 2021 17:30:04 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:18869 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232890AbhDGVaD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Apr 2021 17:30:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1617830994; x=1649366994;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=JJX07rFbUFSCmW7iMNBNJnLHN/ul/VCQMW2GB/8R+9w=;
  b=XuM5o68lErS/35iEYt03BoBEByEaahVaBHuJa1mkJTjtL7oqtuH4qY75
   iHu/dvbICz0zXNhP1ddHr25oFnbgtLcCgGPG+q8hNSdhD8CqAcyKizvdw
   EtNrMXQZ35Xqp6ZkE0YzgelKhIdzmKX9cdTxmNqAbgJBpcmVkHT4Wtduy
   Y=;
X-IronPort-AV: E=Sophos;i="5.82,204,1613433600";
   d="scan'208";a="100206498"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-2c-cc689b93.us-west-2.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 07 Apr 2021 21:29:51 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2c-cc689b93.us-west-2.amazon.com (Postfix) with
 ESMTPS id 18D5C1200AB;
        Wed,  7 Apr 2021 21:29:50 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.162.68) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 7 Apr 2021 21:29:41 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: <kys@microsoft.com>, <haiyangz@microsoft.com>,
        <sthemmin@microsoft.com>, <wei.liu@kernel.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <x86@kernel.org>, <hpa@zytor.com>, <pbonzini@redhat.com>,
        <seanjc@google.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>
CC: <sidcha@amazon.de>, <graf@amazon.com>, <eyakovl@amazon.de>,
        <linux-hyperv@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH 0/4] Add support for XMM fast hypercalls
Date: Wed, 7 Apr 2021 23:29:26 +0200
Message-ID: <20210407212926.3016-1-sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.68]
X-ClientProxiedBy: EX13D01UWA003.ant.amazon.com (10.43.160.107) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-V supports the use of XMM registers to perform fast hypercalls.
This allows guests to take advantage of the improved performance of the
fast hypercall interface even though a hypercall may require more than
(the current maximum of) two general purpose registers.

The XMM fast hypercall interface uses an additional six XMM registers
(XMM0 to XMM5) to allow the caller to pass an input parameter block of
up to 112 bytes. Hyper-V can also return data back to the guest in the
remaining XMM registers that are not used by the current hypercall.

Although the Hyper-v TLFS mentions that a guest cannot use this feature
unless the hypervisor advertises support for it, some hypercalls which
we plan on upstreaming in future uses them anyway. This patchset adds
necessary infrastructure for handling input/output via XMM registers and
patches kvm_hv_flush_tlb() to use xmm input arguments.

~ Sid.

Siddharth Chandrasekaran (4):
  KVM: x86: Move FPU register accessors into fpu.h
  KVM: hyper-v: Collect hypercall params into struct
  KVM: x86: kvm_hv_flush_tlb use inputs from XMM registers
  KVM: hyper-v: Advertise support for fast XMM hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |   4 +-
 arch/x86/kvm/emulate.c             | 138 +++--------------
 arch/x86/kvm/fpu.h                 | 140 +++++++++++++++++
 arch/x86/kvm/hyperv.c              | 241 +++++++++++++++++++----------
 4 files changed, 322 insertions(+), 201 deletions(-)
 create mode 100644 arch/x86/kvm/fpu.h
```
