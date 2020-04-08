#### [GIT PULL 1/3] KVM: s390: vsie: Fix region 1 ASCE sanity shadow address checks
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11477963
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA9EA159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 11:42:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C395C2063A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 11:42:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728213AbgDGLmt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 07:42:49 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:44900 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728146AbgDGLmt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Apr 2020 07:42:49 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 037BYbOF078955
        for <kvm@vger.kernel.org>; Tue, 7 Apr 2020 07:42:48 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3082pebmax-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 07 Apr 2020 07:42:48 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Tue, 7 Apr 2020 12:42:18 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 7 Apr 2020 12:42:16 +0100
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 037Bgfj450659438
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 7 Apr 2020 11:42:41 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AF01F42042;
        Tue,  7 Apr 2020 11:42:41 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 85D8F4203F;
        Tue,  7 Apr 2020 11:42:41 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue,  7 Apr 2020 11:42:41 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 46CD8E08E5; Tue,  7 Apr 2020 13:42:41 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [GIT PULL 1/3] KVM: s390: vsie: Fix region 1 ASCE sanity shadow
 address checks
Date: Tue,  7 Apr 2020 13:42:38 +0200
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200407114240.156419-1-borntraeger@de.ibm.com>
References: <20200407114240.156419-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20040711-0020-0000-0000-000003C34280
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20040711-0021-0000-0000-0000221C0030
Message-Id: <20200407114240.156419-2-borntraeger@de.ibm.com>
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-07_03:2020-04-07,2020-04-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 mlxscore=0
 clxscore=1015 spamscore=0 lowpriorityscore=0 malwarescore=0 phishscore=0
 adultscore=0 mlxlogscore=999 suspectscore=0 bulkscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2004070095
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Hildenbrand <david@redhat.com>

In case we have a region 1 the following calculation
(31 + ((gmap->asce & _ASCE_TYPE_MASK) >> 2)*11)
results in 64. As shifts beyond the size are undefined the compiler is
free to use instructions like sllg. sllg will only use 6 bits of the
shift value (here 64) resulting in no shift at all. That means that ALL
addresses will be rejected.

The can result in endless loops, e.g. when prefix cannot get mapped.

Fixes: 4be130a08420 ("s390/mm: add shadow gmap support")
Tested-by: Janosch Frank <frankja@linux.ibm.com>
Reported-by: Janosch Frank <frankja@linux.ibm.com>
Cc: <stable@vger.kernel.org> # v4.8+
Signed-off-by: David Hildenbrand <david@redhat.com>
Link: https://lore.kernel.org/r/20200403153050.20569-2-david@redhat.com
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
[borntraeger@de.ibm.com: fix patch description, remove WARN_ON_ONCE]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/mm/gmap.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [GIT PULL] Second batch of KVM changes for Linux 5.7
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11478549
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB39592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 18:21:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A9DCB20771
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 18:21:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SkEJ3mbf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726699AbgDGSVS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 14:21:18 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:21585 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726605AbgDGSVR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Apr 2020 14:21:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586283676;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=IbMheVXmF0VacTTe2Hnfg/Xyo9y1cU/Y6NYWIzzzerg=;
        b=SkEJ3mbfIILtm+Xu6JDgBON0cQdguIZmsKGEEXMxK/R709hBhYcWaNGf+ft/HN3MnYRb6E
        9djHFZnfZ7FMmNpWcWk2+txYCZ2aBdiakYirTbmCnINjPUrKjJguCcClNbqPAuTVjCU4+q
        JK1LIm3xMyUiRudVMYlGQ7st8UdEj9I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-70-1XmFQbKJOvOaa9FylQnhcw-1; Tue, 07 Apr 2020 14:21:13 -0400
X-MC-Unique: 1XmFQbKJOvOaa9FylQnhcw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 333C08017FE;
        Tue,  7 Apr 2020 18:21:12 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9DF2360BEC;
        Tue,  7 Apr 2020 18:21:11 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for Linux 5.7
Date: Tue,  7 Apr 2020 14:21:11 -0400
Message-Id: <20200407182111.23659-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 8c1b724ddb218f221612d4c649bc9c7819d8d7a6:

  Merge tag 'for-linus' of git://git.kernel.org/pub/scm/virt/kvm/kvm (2020-04-02 15:13:15 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to dbef2808af6c594922fe32833b30f55f35e9da6d:

  KVM: VMX: fix crash cleanup when KVM wasn't used (2020-04-07 08:35:36 -0400)

----------------------------------------------------------------
s390:
* nested virtualization fixes

x86:
* split svm.c
* miscellaneous fixes

----------------------------------------------------------------
David Hildenbrand (3):
      KVM: s390: vsie: Fix region 1 ASCE sanity shadow address checks
      KVM: s390: vsie: Fix delivery of addressing exceptions
      KVM: s390: vsie: Fix possible race when shadowing region 3 tables

Joerg Roedel (4):
      kVM SVM: Move SVM related files to own sub-directory
      KVM: SVM: Move Nested SVM Implementation to nested.c
      KVM: SVM: Move AVIC code to separate file
      KVM: SVM: Move SEV code to separate file

Oliver Upton (1):
      KVM: nVMX: don't clear mtf_pending when nested events are blocked

Paolo Bonzini (1):
      Merge tag 'kvm-s390-master-5.7-1' of git://git.kernel.org/.../kvms390/linux into HEAD

Uros Bizjak (2):
      KVM: SVM: Split svm_vcpu_run inline assembly to separate file
      KVM: VMX: Remove unnecessary exception trampoline in vmx_vmenter

Vitaly Kuznetsov (1):
      KVM: VMX: fix crash cleanup when KVM wasn't used

Wanpeng Li (1):
      KVM: X86: Filter out the broadcast dest for IPI fastpath

 arch/s390/kvm/vsie.c                  |    1 +
 arch/s390/mm/gmap.c                   |    7 +-
 arch/x86/kvm/Makefile                 |    2 +-
 arch/x86/kvm/lapic.c                  |    3 -
 arch/x86/kvm/lapic.h                  |    3 +
 arch/x86/kvm/svm/avic.c               | 1027 ++++++
 arch/x86/kvm/svm/nested.c             |  823 +++++
 arch/x86/kvm/{pmu_amd.c => svm/pmu.c} |    0
 arch/x86/kvm/svm/sev.c                | 1187 ++++++
 arch/x86/kvm/{ => svm}/svm.c          | 6476 ++++++++-------------------------
 arch/x86/kvm/svm/svm.h                |  491 +++
 arch/x86/kvm/svm/vmenter.S            |  162 +
 arch/x86/kvm/vmx/nested.c             |    3 +-
 arch/x86/kvm/vmx/vmenter.S            |    8 +-
 arch/x86/kvm/vmx/vmx.c                |   12 +-
 arch/x86/kvm/x86.c                    |    3 +-
 16 files changed, 5219 insertions(+), 4989 deletions(-)
 create mode 100644 arch/x86/kvm/svm/avic.c
 create mode 100644 arch/x86/kvm/svm/nested.c
 rename arch/x86/kvm/{pmu_amd.c => svm/pmu.c} (100%)
 create mode 100644 arch/x86/kvm/svm/sev.c
 rename arch/x86/kvm/{ => svm}/svm.c (54%)
 create mode 100644 arch/x86/kvm/svm/svm.h
 create mode 100644 arch/x86/kvm/svm/vmenter.S
```
#### [GIT PULL v2] vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11477837
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F81815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 09:53:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0AD3120719
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 09:53:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YSqQnMy7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728138AbgDGJxp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 05:53:45 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:55418 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726725AbgDGJxo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Apr 2020 05:53:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586253222;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=oLjV0dR06CVtDijV8G+MbnTLMMQSd3QfbOWe/4e1HKY=;
        b=YSqQnMy7xmtlRwvuU4fnUxQ5/6CFxjD8l39mCM7g1iPvzUpu8Q8NkTNMDcWtBGZ00XfHhG
        SnYpTRQs6h+v/RQJn9Jwj0Bmj85jOol8M7WjpfYzne5hgj6LpvZIWFKrcwrjJew+ZEry+i
        Jc+Xdm9IUMhlzt5/cCPxS9GMFCFG2dA=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-111-zAA50Ze6NOGU49ZTyKLSuw-1; Tue, 07 Apr 2020 05:53:38 -0400
X-MC-Unique: zAA50Ze6NOGU49ZTyKLSuw-1
Received: by mail-wm1-f72.google.com with SMTP id f9so486606wme.7
        for <kvm@vger.kernel.org>; Tue, 07 Apr 2020 02:53:38 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=oLjV0dR06CVtDijV8G+MbnTLMMQSd3QfbOWe/4e1HKY=;
        b=j9C492pEk4D0ACC6Gi8YwGzDfRiwvFwfcmKueRmhvzD3ocNM+iHwhH4banftQXa7R7
         4s5RWIBtOFL9yvYoLWWG0axIdwWWT/V5o/HScSW4kyLn2kGQnw7BbtG2yrFolNEewPJN
         X+yoT+OsVf57ZIZbRsWvrmCYIWMfKDrVRRQ8fThVRiTCrvXqwgK4QIwrA/MZDdeb1d/S
         ITahrae1ry3XrZg047etWdmUBeW7I3r/NdW7+9BBCIebIZjJJUSb36TruCMbc0ItzEPB
         sEUn+bO7asS11XrYRMIzi5CXr4NNVSP5waO3p/ItJcibs+vVlX0ErNVIbwPyxxQligmo
         oOjQ==
X-Gm-Message-State: AGi0PuaSIrWbL1G6p3I7Syvkc+X1Bdp9lNpx9Kt+216ac+54jEU2j8zX
        WbxBOCZZpt2HLpfww0FikOTE4EcnrlHooGK/fdbpDXK56doONB/8fgcwy4NBXbM/8toGNWQfqms
        +67uIiiRcQmvL
X-Received: by 2002:a1c:f205:: with SMTP id s5mr1517474wmc.101.1586253217555;
        Tue, 07 Apr 2020 02:53:37 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypK618C35lkaLXiYs/X9jCrBU5V7/q45Do9tU/BXiD39k7buPrgl8FVD4cfYPT2PEopWOaQJtQ==
X-Received: by 2002:a1c:f205:: with SMTP id s5mr1517441wmc.101.1586253217223;
        Tue, 07 Apr 2020 02:53:37 -0700 (PDT)
Received: from redhat.com (bzq-79-176-51-222.red.bezeqint.net.
 [79.176.51.222])
        by smtp.gmail.com with ESMTPSA id
 v7sm30308497wrs.96.2020.04.07.02.53.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 07 Apr 2020 02:53:36 -0700 (PDT)
Date: Tue, 7 Apr 2020 05:53:34 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        alexander.h.duyck@linux.intel.com, david@redhat.com,
        eperezma@redhat.com, jasowang@redhat.com, lingshan.zhu@intel.com,
        mhocko@kernel.org, mst@redhat.com, namit@vmware.com,
        rdunlap@infradead.org, rientjes@google.com, tiwei.bie@intel.com,
        tysand@google.com, wei.w.wang@intel.com, xiao.w.wang@intel.com,
        yuri.benditovich@daynix.com
Subject: [GIT PULL v2] vhost: cleanups and fixes
Message-ID: <20200407055334-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes from PULL v1:
	reverted a commit that was also in Andrew Morton's tree,
	to resolve a merge conflict:
	this is what Stephen Rothwell was doing to resolve it
	in linux-next.


Now that many more architectures build vhost, a couple of these (um, and
arm with deprecated oabi) have reported build failures with randconfig,
however fixes for that need a bit more discussion/testing and will be
merged separately.

Not a regression - these previously simply didn't have vhost at all.
Also, there's some DMA API code in the vdpa simulator is hacky - if no
solution surfaces soon we can always disable it before release:
it's not a big deal either way as it's just test code.


The following changes since commit 16fbf79b0f83bc752cee8589279f1ebfe57b3b6e:

  Linux 5.6-rc7 (2020-03-22 18:31:56 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 835a6a649d0dd1b1f46759eb60fff2f63ed253a7:

  virtio-balloon: Revert "virtio-balloon: Switch back to OOM handler for VIRTIO_BALLOON_F_DEFLATE_ON_OOM" (2020-04-07 05:44:57 -0400)

----------------------------------------------------------------
virtio: fixes, vdpa

Some bug fixes.
The new vdpa subsystem with two first drivers.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
David Hildenbrand (1):
      virtio-balloon: Switch back to OOM handler for VIRTIO_BALLOON_F_DEFLATE_ON_OOM

Jason Wang (7):
      vhost: refine vhost and vringh kconfig
      vhost: allow per device message handler
      vhost: factor out IOTLB
      vringh: IOTLB support
      vDPA: introduce vDPA bus
      virtio: introduce a vDPA based transport
      vdpasim: vDPA device simulator

Michael S. Tsirkin (3):
      tools/virtio: option to build an out of tree module
      vdpa: move to drivers/vdpa
      virtio-balloon: Revert "virtio-balloon: Switch back to OOM handler for VIRTIO_BALLOON_F_DEFLATE_ON_OOM"

Tiwei Bie (1):
      vhost: introduce vDPA-based backend

Yuri Benditovich (3):
      virtio-net: Introduce extended RSC feature
      virtio-net: Introduce RSS receive steering feature
      virtio-net: Introduce hash report feature

Zhu Lingshan (1):
      virtio: Intel IFC VF driver for VDPA

 MAINTAINERS                      |   3 +
 arch/arm/kvm/Kconfig             |   2 -
 arch/arm64/kvm/Kconfig           |   2 -
 arch/mips/kvm/Kconfig            |   2 -
 arch/powerpc/kvm/Kconfig         |   2 -
 arch/s390/kvm/Kconfig            |   4 -
 arch/x86/kvm/Kconfig             |   4 -
 drivers/Kconfig                  |   4 +
 drivers/Makefile                 |   1 +
 drivers/misc/mic/Kconfig         |   4 -
 drivers/net/caif/Kconfig         |   4 -
 drivers/vdpa/Kconfig             |  37 ++
 drivers/vdpa/Makefile            |   4 +
 drivers/vdpa/ifcvf/Makefile      |   3 +
 drivers/vdpa/ifcvf/ifcvf_base.c  | 389 +++++++++++++++++
 drivers/vdpa/ifcvf/ifcvf_base.h  | 118 ++++++
 drivers/vdpa/ifcvf/ifcvf_main.c  | 435 +++++++++++++++++++
 drivers/vdpa/vdpa.c              | 180 ++++++++
 drivers/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/vdpa/vdpa_sim/vdpa_sim.c | 629 ++++++++++++++++++++++++++++
 drivers/vhost/Kconfig            |  45 +-
 drivers/vhost/Kconfig.vringh     |   6 -
 drivers/vhost/Makefile           |   6 +
 drivers/vhost/iotlb.c            | 177 ++++++++
 drivers/vhost/net.c              |   5 +-
 drivers/vhost/scsi.c             |   2 +-
 drivers/vhost/vdpa.c             | 883 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/vhost.c            | 233 ++++-------
 drivers/vhost/vhost.h            |  45 +-
 drivers/vhost/vringh.c           | 421 ++++++++++++++++++-
 drivers/vhost/vsock.c            |   2 +-
 drivers/virtio/Kconfig           |  13 +
 drivers/virtio/Makefile          |   1 +
 drivers/virtio/virtio_vdpa.c     | 396 ++++++++++++++++++
 include/linux/vdpa.h             | 253 +++++++++++
 include/linux/vhost_iotlb.h      |  47 +++
 include/linux/vringh.h           |  36 ++
 include/uapi/linux/vhost.h       |  24 ++
 include/uapi/linux/vhost_types.h |   8 +
 include/uapi/linux/virtio_net.h  | 102 ++++-
 tools/virtio/Makefile            |  27 +-
 41 files changed, 4310 insertions(+), 251 deletions(-)
 create mode 100644 drivers/vdpa/Kconfig
 create mode 100644 drivers/vdpa/Makefile
 create mode 100644 drivers/vdpa/ifcvf/Makefile
 create mode 100644 drivers/vdpa/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vdpa/ifcvf/ifcvf_base.h
 create mode 100644 drivers/vdpa/ifcvf/ifcvf_main.c
 create mode 100644 drivers/vdpa/vdpa.c
 create mode 100644 drivers/vdpa/vdpa_sim/Makefile
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim.c
 delete mode 100644 drivers/vhost/Kconfig.vringh
 create mode 100644 drivers/vhost/iotlb.c
 create mode 100644 drivers/vhost/vdpa.c
 create mode 100644 drivers/virtio/virtio_vdpa.c
 create mode 100644 include/linux/vdpa.h
 create mode 100644 include/linux/vhost_iotlb.h
```
#### [PATCH kvm-unit-tests v2] arch-run: Add reserved variables to the default environ
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11477955
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E9131392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 11:33:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 63122206F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 11:33:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CjtTacJq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728088AbgDGLda (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 07:33:30 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:23506 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728023AbgDGLda (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Apr 2020 07:33:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586259207;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=rsbs0O7/78AiRM450j13mYXwpKUUUkTpFVXutreoHB0=;
        b=CjtTacJqLkFMycVhvyCBr3vORgjc3PZtdckNgJ1Gie9mJMrDS3VvWaVSU0p3k7FR0OwOh3
        8ZEqQHPj+wR5JiT4JcIqzhEgrh8QAB7ggI85S1mJIIvsI0hop6hGJFA9s4z71I2CvZERYO
        WeeMZyG7hyA1lWByD1RmtrYUBid0ul4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-387-dyttFci9PCGhnmtHE0AwZw-1; Tue, 07 Apr 2020 07:33:26 -0400
X-MC-Unique: dyttFci9PCGhnmtHE0AwZw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1CC82107ACC9;
        Tue,  7 Apr 2020 11:33:25 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.126])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5BAA460BEC;
        Tue,  7 Apr 2020 11:33:20 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: lvivier@redhat.com, thuth@redhat.com, david@redhat.com,
        frankja@linux.ibm.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests v2] arch-run: Add reserved variables to the
 default environ
Date: Tue,  7 Apr 2020 13:33:12 +0200
Message-Id: <20200407113312.65587-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the already reserved (see README) variables to the default
environ. To do so neatly we rework the environ creation a bit too.
mkstandalone also learns to honor config.mak as to whether or not
to make environs, and we allow the $ERRATATXT file to be selected
at configure time.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---

v2: Improve error handling of missing erratatxt files.

 configure               |  13 ++++-
 scripts/arch-run.bash   | 125 +++++++++++++++++++++++++---------------
 scripts/mkstandalone.sh |   9 ++-
 3 files changed, 97 insertions(+), 50 deletions(-)

```
#### [PATCH] KVM: x86: Fixes posted interrupt check for IRQs delivery modes
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11477607
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 53F6A112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 06:13:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 328B520748
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 06:13:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="pCGTwxkz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726817AbgDGGNX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 02:13:23 -0400
Received: from mail-eopbgr760043.outbound.protection.outlook.com
 ([40.107.76.43]:9670
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725802AbgDGGNX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Apr 2020 02:13:23 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=gnHHZ0DJJKNbViHKBgKcWig9nym4WeFl9OfvcTdHbosEjv++iKq/+jbzxDtVQKH7om35X0o2EXIW+aGgSd572nUn5aFse93DlY5G+RKu/s+PKOmc+cZCXxB1nfXHQEHeeOaoWH+UTauG9zGU+utY5vXyXmtYf9cbjhlaGmWmpXe+Esc/uqIHajY15klI1dK9iOCG7xJptYCz30jzoAovISqDE0qEudnGu5+18jto7d6wycjUR1LPykH9hqESRZb312q44yWo1wpX95XMnBXITLSgG2zeF1zvdBpi90tSRdRqjAhrFbuF0GDWrrVZH1W/UWD6deeaj9S4XhlWkAhNfg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Dg7ZqmOdtpnlk1OQiets3N5Y3HSftsSf1ihldmuggoQ=;
 b=nec/ST07CRFjo+xG57nVEWGSZaOZyZyMGtMdc6FieUDLhd33jZxNUkCKZY2Qxirq/z+S8XtYSkSsI0EpW+neIaYNzzWVon2C2fOZtLDPIKrLlOc4oqTPkiH88BtaQkySzrahliiMTg1AX49SELhU+FvX7JjiG/Qb96tSZGOwfhNdic7/4j/0fdHMHZu5g24WfO2yJ3s3tlEGbncpIqbXT0uNa+rlpEDADblz6hbXhmX53wrZQo7O+xDjtp/BldIsjNiMpnmnTH42CdpO2v+WnLiKCOGoit1LZK8hEF5R9XwB6rpA3rd3185Z0GqKYg/6jSw14/j2ZTyj4JIb9p6ARw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Dg7ZqmOdtpnlk1OQiets3N5Y3HSftsSf1ihldmuggoQ=;
 b=pCGTwxkzg76JecwiwPDtWlfbcVs479jInPtotEEQaBbOnGW+mnIAwb9ocH/PUuIRrTxwwSB8s+ZxMFC0IEfYe5Xc3T8cAErwZzdRp6oEtxiVinzszUNWpULGvdUc6J2zKu430WIrmUs8WInW/eYaYuj9M+wXeaHPrd6fLSx/JC0=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Suravee.Suthikulpanit@amd.com;
Received: from DM6PR12MB3865.namprd12.prod.outlook.com (2603:10b6:5:1c4::14)
 by DM6SPR01MB0036.namprd12.prod.outlook.com (2603:10b6:5:61::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2878.15; Tue, 7 Apr
 2020 06:13:18 +0000
Received: from DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::2d84:ed9d:cba4:dcfd]) by DM6PR12MB3865.namprd12.prod.outlook.com
 ([fe80::2d84:ed9d:cba4:dcfd%3]) with mapi id 15.20.2878.018; Tue, 7 Apr 2020
 06:13:18 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, joro@8bytes.org, jon.grimm@amd.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>,
        Alexander Graf <graf@amazon.com>
Subject: [PATCH] KVM: x86: Fixes posted interrupt check for IRQs delivery
 modes
Date: Tue,  7 Apr 2020 01:13:09 -0500
Message-Id: <1586239989-58305-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: DM5PR21CA0037.namprd21.prod.outlook.com
 (2603:10b6:3:ed::23) To DM6PR12MB3865.namprd12.prod.outlook.com
 (2603:10b6:5:1c4::14)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 DM5PR21CA0037.namprd21.prod.outlook.com (2603:10b6:3:ed::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2921.6 via Frontend
 Transport; Tue, 7 Apr 2020 06:13:17 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 2c1ade45-3bd7-4a8f-41ee-08d7dabac3bc
X-MS-TrafficTypeDiagnostic: DM6SPR01MB0036:|DM6SPR01MB0036:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6SPR01MB00368BF3D5E1477B1A142214F3C30@DM6SPR01MB0036.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4502;
X-Forefront-PRVS: 036614DD9C
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3865.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(10009020)(4636009)(366004)(346002)(376002)(39860400002)(396003)(136003)(2906002)(956004)(8936002)(54906003)(5660300002)(81166006)(81156014)(316002)(36756003)(8676002)(44832011)(66946007)(6486002)(86362001)(66556008)(478600001)(2616005)(186003)(52116002)(7696005)(66476007)(26005)(6666004)(4326008)(16526019)(21314003);DIR:OUT;SFP:1101;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 GXNSa4tnlLTCGXhu9z+dOi3CaAO4BTCvTJ9SpTOfeHikfrXNwhnrXZyC+7y1S4pZONXi6iXchoOa8cHCjktjp3NzloDouEwJd2UNRsSjqysTn/rku6ikRy9UZ2MZa/zjf1d3yJjlSvAoaAmzre00BIxvJ7sqXq0Gl+1EXZJSUQWYiezRPbhfb2U5MxpDsjIUYQDySd1w0QgqAk0jqfAQjCFupHCnXLG+QB9CMhu/fVNEEFQdmG2Td56uflTaCbxZpyZBOmxI1YqdbqUyx6fyRWEJ3F+WNy3PJi/8AGiOSVKjM3aKayftN9tzBbP+UMYDTT0XOZ43BLWl5y8JN1PTS3dcru1N8OYZ+rJe/YMIf0BWSCii0DY/5Wp5KlBOrhTiEqLTIU+lp1P4Oplw/bzuDnVhsc6BLGwg5bIV9SEKJ1xc/RKgCCA3ruyUQymbvPHekLtS4Bxl9e4dMIciD9JVR/zqT2XIE1eW38zsw7CmeAk=
X-MS-Exchange-AntiSpam-MessageData: 
 3TwdOSKPhKyqR26FG4cqQRe/5hLHHPDNI+Y+H+OIn/znZvnUsmYpGz5DNwkVnbufDXzK5q8/34oLf+65VdKrlhO4SUDnJ+THQkkjK2iqNqErA6fbXAW98vYD4N95/l+5X+yqyD8SPxj4IZEEhPTXfA==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2c1ade45-3bd7-4a8f-41ee-08d7dabac3bc
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 Apr 2020 06:13:18.1500
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 EDc84LflynubXaR4UALvBYVSbl1nETR1hviNoH0G9LMvekeOypSoPkEY2Lsi8HWaKOlnE2A2g20m7CgLFyiaig==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6SPR01MB0036
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current logic incorrectly uses the enum ioapic_irq_destination_types
to check the posted interrupt destination types. However, the value was
set using APIC_DM_XXX macros, which are left-shifted by 8 bits.

Fixes by using the APIC_DM_FIXED and APIC_DM_LOWEST instead.

Fixes: (fdcf75621375 'KVM: x86: Disable posted interrupts for non-standard IRQs delivery modes')
Cc: Alexander Graf <graf@amazon.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/include/asm/kvm_host.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: X86: Ultra fast single target IPI fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11477707
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5547714DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 08:28:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 298C220753
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 08:28:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="N2Rgae8z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727942AbgDGI2u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 04:28:50 -0400
Received: from mail-pj1-f66.google.com ([209.85.216.66]:50373 "EHLO
        mail-pj1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726767AbgDGI2t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Apr 2020 04:28:49 -0400
Received: by mail-pj1-f66.google.com with SMTP id v13so435997pjb.0;
        Tue, 07 Apr 2020 01:28:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=QwWmobyOdR5r+7JJZxSrwfB56TjLUl825BwGgH9NRNQ=;
        b=N2Rgae8zms+3LBxcOrnLBU6jO9Vokq7alwIwdkajm2FUP1feOjiHVPKSETTl9o9lJe
         e7OTGKpv440s5Lfcetiy6u8IiLz7+Y65DDE1Du0iTM9Jc128kZeLDcwZDP2wvDVveaIc
         7RE1k4T2JIo9iPgOk01c9xZ9YKhpy340rKlsPtWfXLmi3Rl4PlnuJxanwfKZO6hF/8M1
         F74iN54bpM1rgEA+G2heoGYtF9uMSouwpX+N28YAE6gIllNTnzbD3G8DzQ6dtk3f1XX+
         Ov0kmUIwGI1h6dIrIBQQX/RiKzAEJqbvWRGeU4xATH0LIQGyIeubVEtJ+ioJT0f5KCDv
         ZI7w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=QwWmobyOdR5r+7JJZxSrwfB56TjLUl825BwGgH9NRNQ=;
        b=bcMP05UarBvvw2ZLczV8sX8k1eoW4D+8Co1Jm3BDnZbseGIaG2D0bF2UU32Itc1Yv+
         NcGeXswQhpm/vzWU2E0xv/qYhUAthPgU4FHQhjvwsua81DXCJElScTbvcGEixYkRNMcH
         /8+r9eR7K6ekeiWwGefsxOWR0KvhCyI7M0H268YamJvWC6jzjhVgNxUpmFT7qfNAF8ZL
         D/cucOGbHjp1miUo8f0zFvVFU/ymByDwDAaz+2hGocZp+uq/DnnpffBTkst2ZEEnZWMr
         QX+5yi+JJzaO8twUkUHuSZpg/k4oLP5avbUDvYEm+NO9v+hKUHDW/Pi3zwv/F0YmDQe0
         SDgA==
X-Gm-Message-State: AGi0PuYiNAA8xo0camTArksjQVK+BSZMumlpUc+bOCzE1lqlpJpUWQIz
        bkBRGCfCoBraFEyAzAj6byOsIZbq01Y=
X-Google-Smtp-Source: 
 APiQypJ4MXFHCvLmE8SCVaL1WlvfgUE4X19jgukoo7Kk6ggpuOGHWgDPmWpJtOQeHusGT0nP3uKCxA==
X-Received: by 2002:a17:902:8ec1:: with SMTP id
 x1mr1381741plo.325.1586248128475;
        Tue, 07 Apr 2020 01:28:48 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 h2sm13520526pfr.220.2020.04.07.01.28.45
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 07 Apr 2020 01:28:48 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: X86: Ultra fast single target IPI fastpath
Date: Tue,  7 Apr 2020 16:28:38 +0800
Message-Id: <1586248118-19607-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

IPI and Timer cause the main MSRs write vmexits in cloud environment 
observation, let's optimize virtual IPI latency more aggressively to 
inject target IPI as soon as possible.

Running kvm-unit-tests/vmexit.flat IPI testing on SKX server, disable 
adaptive advance lapic timer and adaptive halt-polling to avoid the 
interference, this patch can give another 7% improvement.

w/o fastpath -> fastpath            4238 -> 3543  16.4%
fastpath     -> ultra fastpath      3543 -> 3293     7%
w/o fastpath -> ultra fastpath      4338 -> 3293    24%

This also revises the performance data in commit 1e9e2622a1 (KVM: VMX: 
FIXED+PHYSICAL mode single target IPI fastpath), that testing exposes
mwait to kvm-unit-tests guest which is unnecessary.

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  6 +++---
 arch/x86/kvm/svm.c              | 21 ++++++++++++++-------
 arch/x86/kvm/vmx/vmx.c          | 19 +++++++++++++------
 arch/x86/kvm/x86.c              |  4 ++--
 4 files changed, 32 insertions(+), 18 deletions(-)

```
#### [PATCH v7 10/19] vhost: force spec specified alignment on types
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11477103
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E6E0913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 01:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5BF492078A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 01:07:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FoIXAgI5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726679AbgDGBH4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Apr 2020 21:07:56 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29702 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726659AbgDGBHz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Apr 2020 21:07:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586221674;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=b+P99eoGOE59dzJri6nDdYTRF/iHp1rUM821OiEBSWI=;
        b=FoIXAgI5OWoA2jtao11ABKn7i0yKHhLWShNWQidugju9gptmfDJxOgQuxG7GoF8Uw99NWi
        3NrEIjJwI9EMVTpRKt+jfiK8Na2Q5Z4/PUEXpIHif0/qmyIOiUpOIq6obboECVIAJeQwdA
        mcz1p8bM7T5bk/xcbFGciGK4MIQSLLI=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-46-BLxZWCsaPZSa0tmgwk5y8g-1; Mon, 06 Apr 2020 21:07:50 -0400
X-MC-Unique: BLxZWCsaPZSa0tmgwk5y8g-1
Received: by mail-wr1-f70.google.com with SMTP id 91so864874wro.1
        for <kvm@vger.kernel.org>; Mon, 06 Apr 2020 18:07:50 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=b+P99eoGOE59dzJri6nDdYTRF/iHp1rUM821OiEBSWI=;
        b=AI0wjgAFO1rFAjFQERpfdWO4InUieslzYRdn/4YBb4NuVlqZd80rhxXqJWYI8Tn3zr
         ZHTI8mupt+cryqrMXZ7uXwwe4NkI+gKWxXI5GgNp+uXAsV35UlL4DrUHntEKpztw0vsI
         /7dutoremu9XihvGhOIahQRn1zaDOxdnhe61QLChF4dNkwYfw+aJ2BCcite8/dq+Ne5I
         gmUOGpnR0omg9mEezAUfEtKFkXwOhHHUG10HXBT5V8ENHWxhTe5F3oLNEueR1c0b6oii
         UtG0Bp5SUhzew3E7beMi+bgbUbOdkhLWcZZax5nXd/hysJ+WvRpHGO1iGARv4NI7Hpwy
         jJAg==
X-Gm-Message-State: AGi0PuY8VJolNDHNuzNiLzvz1obiYGC/VsHvjnulZ4yD8nfhsx7Yg51F
        LbQGizI5V3SEEhJmP/w0qyVsVQCeL7oYwplQFI5C9kuK4uHya+f/WUkV+2TV0jHLevnJrZkTfgT
        1kUW9NsO8YGL3
X-Received: by 2002:adf:f98b:: with SMTP id f11mr1998832wrr.259.1586221669692;
        Mon, 06 Apr 2020 18:07:49 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJ7vAsHxvjmiu+bo7NHbyExOgBSbxXMZd7IkvuAC9tnfoRSEzkPJmWDYEX8+2JgtuNqELnN8w==
X-Received: by 2002:adf:f98b:: with SMTP id f11mr1998816wrr.259.1586221669436;
        Mon, 06 Apr 2020 18:07:49 -0700 (PDT)
Received: from redhat.com (bzq-79-176-51-222.red.bezeqint.net.
 [79.176.51.222])
        by smtp.gmail.com with ESMTPSA id
 j11sm28630487wrt.14.2020.04.06.18.07.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 06 Apr 2020 18:07:48 -0700 (PDT)
Date: Mon, 6 Apr 2020 21:07:47 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v7 10/19] vhost: force spec specified alignment on types
Message-ID: <20200407010700.446571-11-mst@redhat.com>
References: <20200407010700.446571-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200407010700.446571-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ring element addresses are passed between components with different
alignments assumptions. Thus, if guest/userspace selects a pointer and
host then gets and dereferences it, we might need to decrease the
compiler-selected alignment to prevent compiler on the host from
assuming pointer is aligned.

This actually triggers on ARM with -mabi=apcs-gnu - which is a
deprecated configuration, but it seems safer to handle this
generally.

I verified that the produced binary is exactly identical on x86.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.h       |  6 +++---
 include/linux/virtio_ring.h | 24 +++++++++++++++++++++---
 2 files changed, 24 insertions(+), 6 deletions(-)

```
#### [PATCH v8 10/19] vhost: force spec specified alignment on types
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11477143
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F0E41392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 01:16:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4D8A92082D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 01:16:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FL5cL9jB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726709AbgDGBQz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Apr 2020 21:16:55 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:48234 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726692AbgDGBQx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 6 Apr 2020 21:16:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586222213;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=b+P99eoGOE59dzJri6nDdYTRF/iHp1rUM821OiEBSWI=;
        b=FL5cL9jB/jv3Cw8c0R7qvL4Fr6L6684qHMIGeLvRn49FmU0NAjyiVhOH2dTCfHtVcwNLTT
        /fKTvnPA8fBXt1d1mTRvRISYxbpwz2TZ3uzW9C1r2QkluBXsCQt8fjbqw8CNvpeNm1trai
        9qnn1PPCSS8PgevWzuuC3b3MAZBt08o=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-297-7fDUsodKMdCg6RvFQ31-8w-1; Mon, 06 Apr 2020 21:16:51 -0400
X-MC-Unique: 7fDUsodKMdCg6RvFQ31-8w-1
Received: by mail-wm1-f70.google.com with SMTP id 2so17613wmf.1
        for <kvm@vger.kernel.org>; Mon, 06 Apr 2020 18:16:51 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=b+P99eoGOE59dzJri6nDdYTRF/iHp1rUM821OiEBSWI=;
        b=dJ4hzESvI+LAWh/3vXLYlF2O8Ubyk3uW21DFGrj65EL23ZmgmC+IoI5JywBGOug25R
         3F+2iMEFkQguvCdMFxMcdTtb+CxdlpjHPUStV9huGv87vQqJaLGShOhByOJBCnKKrhqK
         hlrjiB9Ce2oPOXwElf/ypEoG+sGsf6yBc9cy6+52eKWzEM+rVOJJ/FLP/mI1ZRqmE6zh
         t2audoFB2KkixlX25/QPygarkYV8PDG2ADlREKsvs7oZrdmQouqNuWXndYk4jjfWCe2P
         RTmoRjOxEfX9YxqTPIwXviyAu4goxoLQ9UmrEbHvowJjPc2WJrG5W3cNLU/hR3ozyk8W
         T5Lg==
X-Gm-Message-State: AGi0PubDTsfCssdTZdRGWrtwohVL3UiCWZM466e/g0Ydv3mpGT22Q1F4
        P7g8nDW59ymahb8JP5gmBCS3/iXzwJdjhJAbbTuBklANh4SUfgDobDaIyX4NKuf/QXacA0sKrAs
        mzzSeYa/Kcbgm
X-Received: by 2002:adf:fe52:: with SMTP id m18mr2041300wrs.162.1586222210550;
        Mon, 06 Apr 2020 18:16:50 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJn5DjBcjpMzTbrTEAm6PtADPd35uHLc30DK0aLGHH0mu1pODoic12Kr5dEmc3NA5QUWXhA1A==
X-Received: by 2002:adf:fe52:: with SMTP id m18mr2041286wrs.162.1586222210287;
        Mon, 06 Apr 2020 18:16:50 -0700 (PDT)
Received: from redhat.com (bzq-79-176-51-222.red.bezeqint.net.
 [79.176.51.222])
        by smtp.gmail.com with ESMTPSA id
 u13sm30079813wru.88.2020.04.06.18.16.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 06 Apr 2020 18:16:49 -0700 (PDT)
Date: Mon, 6 Apr 2020 21:16:48 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v8 10/19] vhost: force spec specified alignment on types
Message-ID: <20200407011612.478226-11-mst@redhat.com>
References: <20200407011612.478226-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200407011612.478226-1-mst@redhat.com>
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ring element addresses are passed between components with different
alignments assumptions. Thus, if guest/userspace selects a pointer and
host then gets and dereferences it, we might need to decrease the
compiler-selected alignment to prevent compiler on the host from
assuming pointer is aligned.

This actually triggers on ARM with -mabi=apcs-gnu - which is a
deprecated configuration, but it seems safer to handle this
generally.

I verified that the produced binary is exactly identical on x86.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.h       |  6 +++---
 include/linux/virtio_ring.h | 24 +++++++++++++++++++++---
 2 files changed, 24 insertions(+), 6 deletions(-)

```
#### [PATCH v7 01/15] s390/vfio-ap: store queue struct in hash table for quick access
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11478933
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE09D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 19:21:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 84F2A2082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 19:21:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727026AbgDGTUf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 15:20:35 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:7208 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726339AbgDGTUe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Apr 2020 15:20:34 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 037J37UY034644;
        Tue, 7 Apr 2020 15:20:32 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3082nx33xe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Apr 2020 15:20:32 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 037J3LIG036064;
        Tue, 7 Apr 2020 15:20:32 -0400
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3082nx33x3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Apr 2020 15:20:31 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 037JKDlF007745;
        Tue, 7 Apr 2020 19:20:30 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma05wdc.us.ibm.com with ESMTP id 306hv6jffp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Apr 2020 19:20:30 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 037JKTSo31064438
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 7 Apr 2020 19:20:29 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3C76128060;
        Tue,  7 Apr 2020 19:20:29 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7772328071;
        Tue,  7 Apr 2020 19:20:28 +0000 (GMT)
Received: from cpe-172-100-173-215.stny.res.rr.com.com (unknown
 [9.85.207.206])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue,  7 Apr 2020 19:20:28 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pmorel@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        jjherne@linux.ibm.com, fiuczy@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v7 01/15] s390/vfio-ap: store queue struct in hash table for
 quick access
Date: Tue,  7 Apr 2020 15:20:01 -0400
Message-Id: <20200407192015.19887-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200407192015.19887-1-akrowiak@linux.ibm.com>
References: <20200407192015.19887-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-07_08:2020-04-07,2020-04-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 impostorscore=0 mlxscore=0 mlxlogscore=999 malwarescore=0
 lowpriorityscore=0 suspectscore=3 adultscore=0 clxscore=1015
 priorityscore=1501 spamscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2003020000 definitions=main-2004070153
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rather than looping over potentially 65535 objects, let's store the
structures for caching information about queue devices bound to the
vfio_ap device driver in a hash table keyed by APQN.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 28 +++------
 drivers/s390/crypto/vfio_ap_ops.c     | 90 ++++++++++++++-------------
 drivers/s390/crypto/vfio_ap_private.h | 10 ++-
 3 files changed, 60 insertions(+), 68 deletions(-)

```
#### [PATCH v3 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11478319
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6E00815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 15:38:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4CE772075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 15:38:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YQq2rpqq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729449AbgDGPhu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 11:37:50 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:60615 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729183AbgDGPht (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Apr 2020 11:37:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586273868;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=YBQ+zxeaLD0yw/RzmwmvvS9Gvxa0mxHzlEt+c4z9U6U=;
        b=YQq2rpqqaeCRDML8KNfu+Uyslbmvoo63if7P/k+MCfOh30rMik058AJCDvxhRidF9Me1qj
        WYupyBOL8Nb/F+qXqbERmFYIAkp88efQm9yyYF67blrGxEb0jBLRrj6JMFNFZJ8AIlBSQG
        n1jgutc34NYOpJF82smkMtj5LDrK7vA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-187-oqR3U8ezOiqn97kazvQiqA-1; Tue, 07 Apr 2020 11:37:45 -0400
X-MC-Unique: oqR3U8ezOiqn97kazvQiqA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 706AE18C43C2;
        Tue,  7 Apr 2020 15:37:44 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6E1CE272A6;
        Tue,  7 Apr 2020 15:37:39 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Subject: [PATCH v3 1/2] selftests: kvm: Add vm_get_fd() in kvm_util
Date: Tue,  7 Apr 2020 12:37:30 -0300
Message-Id: <20200407153731.3236-2-wainersm@redhat.com>
In-Reply-To: <20200407153731.3236-1-wainersm@redhat.com>
References: <20200407153731.3236-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduces the vm_get_fd() function in kvm_util which returns
the VM file descriptor.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 1 +
 tools/testing/selftests/kvm/lib/kvm_util.c     | 5 +++++
 2 files changed, 6 insertions(+)

```
#### [PATCH] vfio-ccw: document possible errors
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11477941
Return-Path: <SRS0=YjMM=5X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2123B159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 11:16:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F3A7E20731
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Apr 2020 11:16:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F+yalRsD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728290AbgDGLQP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Apr 2020 07:16:15 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:21069 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725883AbgDGLQP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Apr 2020 07:16:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586258173;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3du99pETZoLILFx0f95jymvWmustW+PUAhmPmiIjcqo=;
        b=F+yalRsD096JlStHI9519bR9va9nWYI4RcfogVbepHuN4fPdwb0O6fEpBPC+LSihrMlzIO
        hRipGSfIDPg/J8u5Otb1mYbbnNQ5Drn/4Jj7TPbXh2OkDIaB86w1sUdyhKO7+dGBG6NjaL
        WRb+PALPc2N/mMRjWfCqAZT1q5eLHNg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-182-nWnCS009Pn2sk1k5pxSguQ-1; Tue, 07 Apr 2020 07:16:11 -0400
X-MC-Unique: nWnCS009Pn2sk1k5pxSguQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C516100DFC3;
        Tue,  7 Apr 2020 11:16:09 +0000 (UTC)
Received: from localhost (ovpn-112-38.ams2.redhat.com [10.36.112.38])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id DD9C260BEC;
        Tue,  7 Apr 2020 11:16:08 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Eric Farman <farman@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] vfio-ccw: document possible errors
Date: Tue,  7 Apr 2020 13:16:05 +0200
Message-Id: <20200407111605.1795-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Interacting with the I/O and the async regions can yield a number
of errors, which had been undocumented so far. These are part of
the api, so remedy that.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/s390/vfio-ccw.rst | 54 ++++++++++++++++++++++++++++++++-
 1 file changed, 53 insertions(+), 1 deletion(-)

```
