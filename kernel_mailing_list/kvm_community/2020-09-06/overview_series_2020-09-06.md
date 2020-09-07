#### [PATCH v5.4.y 1/3] vfio/type1: Support faulting PFNMAP vmas
##### From: Ajay Kaher <akaher@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11759525
Return-Path: <SRS0=jq9b=CP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A07F892C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Sep 2020 14:31:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9236C20759
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Sep 2020 14:31:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728846AbgIFOMU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 6 Sep 2020 10:12:20 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:38470 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726931AbgIFOMK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 6 Sep 2020 10:12:10 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Sun, 6 Sep 2020 07:12:04 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id B392B408D4;
        Sun,  6 Sep 2020 07:12:03 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v5.4.y 1/3] vfio/type1: Support faulting PFNMAP vmas
Date: Sun, 6 Sep 2020 19:37:54 +0530
Message-ID: <1599401277-32172-1-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 41311242221e3482b20bfed10fa4d9db98d87016 upstream.

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Ajay Kaher <akaher@vmware.com>
---
 drivers/vfio/vfio_iommu_type1.c | 36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
