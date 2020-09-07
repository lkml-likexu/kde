

#### [PATCH v5.4.y 0/3] vfio: Fix for CVE-2020-12888
##### From: Ajay Kaher <akaher@vmware.com>

```c
From patchwork Sun Sep  6 14:07:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11759509
Return-Path: <SRS0=jq9b=CP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 538C913B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Sep 2020 14:16:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 43CEC207BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Sep 2020 14:16:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728785AbgIFOQe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 6 Sep 2020 10:16:34 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:50007 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728887AbgIFONB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 6 Sep 2020 10:13:01 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Sun, 6 Sep 2020 07:12:25 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 973FD408D3;
        Sun,  6 Sep 2020 07:12:25 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v5.4.y 0/3] vfio: Fix for CVE-2020-12888
Date: Sun, 6 Sep 2020 19:37:57 +0530
Message-ID: <1599401277-32172-4-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1599401277-32172-1-git-send-email-akaher@vmware.com>
References: <1599401277-32172-1-git-send-email-akaher@vmware.com>
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CVE-2020-12888 Kernel: vfio: access to disabled MMIO space of some
devices may lead to DoS scenario
    
The VFIO modules allow users (guest VMs) to enable or disable access to the
devices' MMIO memory address spaces. If a user attempts to access (read/write)
the devices' MMIO address space when it is disabled, some h/w devices issue an
interrupt to the CPU to indicate a fatal error condition, crashing the system.
This flaw allows a guest user or process to crash the host system resulting in
a denial of service.
    
Patch 1/ is to force the user fault if PFNMAP vma might be DMA mapped
before user access.
    
Patch 2/ setup a vm_ops handler to support dynamic faulting instead of calling
remap_pfn_range(). Also provides a list of vmas actively mapping the area which
can later use to invalidate those mappings.
    
Patch 3/ block the user from accessing memory spaces which is disabled by using
new vma list support to zap, or invalidate, those memory mappings in order to
force them to be faulted back in on access.
    
Upstreamed patches link:
https://lore.kernel.org/kvm/158871401328.15589.17598154478222071285.stgit@gimli.home
        
[PATCH v5.4.y 1/3]:
Backporting of upsream commit 41311242221e:
vfio/type1: Support faulting PFNMAP vmas
        
[PATCH v5.4.y 2/3]:
Backporting of upsream commit 11c4cd07ba11:
vfio-pci: Fault mmaps to enable vma tracking
        
[PATCH v5.4.y 3/3]:
Backporting of upsream commit abafbc551fdd:
vfio-pci: Invalidate mmaps and block MMIO access on disabled memory
```
