

#### [PATCH net-next 00/14] vsock: add multi-transports support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Wed Oct 23 09:55:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11206191
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 942771390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 09:56:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 69CF42064B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 09:56:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="b5zDXq8J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390946AbfJWJ4M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 05:56:12 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:30080 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390390AbfJWJ4L (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Oct 2019 05:56:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571824571;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=PjIrWxilILjTXJMM4pZ+a2frsZYLFCvzVYmdT4dKHeA=;
        b=b5zDXq8J97LwC5WX8PDjo+cfJdZZOnEezlbTMRhRHpU2HUGLbaQxaw+As7v+urTLtBvPCO
        jM5JM27+/lVGh8aIP74TVhqRuUiISgaAurfsQFsZZn7yRTifKcU5ghkF4R+odbPzYeFbAN
        WSNSePJTMlPVIAqAazHXU5EXB1LqDpc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-45-AIB5fJO8MnCfZd5pS6ln_A-1; Wed, 23 Oct 2019 05:56:07 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B56EC1800DD0;
        Wed, 23 Oct 2019 09:56:05 +0000 (UTC)
Received: from steredhat.redhat.com (unknown [10.36.118.164])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1BEEB5C1B2;
        Wed, 23 Oct 2019 09:55:54 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Dexuan Cui <decui@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Jorgen Hansen <jhansen@vmware.com>,
        Sasha Levin <sashal@kernel.org>, linux-kernel@vger.kernel.org,
        Arnd Bergmann <arnd@arndb.de>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-hyperv@vger.kernel.org,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        virtualization@lists.linux-foundation.org
Subject: [PATCH net-next 00/14] vsock: add multi-transports support
Date: Wed, 23 Oct 2019 11:55:40 +0200
Message-Id: <20191023095554.11340-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: AIB5fJO8MnCfZd5pS6ln_A-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds the multi-transports support to vsock, following
this proposal: https://www.spinics.net/lists/netdev/msg575792.html

With the multi-transports support, we can use VSOCK with nested VMs
(using also different hypervisors) loading both guest->host and
host->guest transports at the same time.
Before this series, vmci-transport supported this behavior but only
using VMware hypervisor on L0, L1, etc.

RFC: https://patchwork.ozlabs.org/cover/1168442/
RFC -> v1:
- Added R-b/A-b from Dexuan and Stefan
- Fixed comments and typos in several patches (Stefan)
- Patch 7: changed .notify_buffer_size return to void (Stefan)
- Added patch 8 to simplify the API exposed to the transports (Stefan)
- Patch 11:
  + documented VSOCK_TRANSPORT_F_* flags (Stefan)
  + fixed vsock_assign_transport() when the socket is already assigned
  + moved features outside of struct vsock_transport, and used as
    parameter of vsock_core_register() as a preparation of Patch 12
- Removed "vsock: add 'transport_hg' to handle g2h\h2g transports" patch
- Added patch 12 to register vmci_transport only when VMCI guest/host
  are active

The first 9 patches are cleanups and preparations, maybe some of
these can go regardless of this series.

Patch 10 changes the hvs_remote_addr_init(). setting the
VMADDR_CID_HOST as remote CID instead of VMADDR_CID_ANY to make
the choice of transport to be used work properly.

Patch 11 adds multi-transports support.

Patch 12 touch a little bit the vmci_transport and the vmci driver
to register the vmci_transport only when there are active host/guest.

Patch 13 prevents the transport modules unloading while sockets are
assigned to them.

Patch 14 fixes an issue in the bind() logic discoverable only with
the new multi-transport support.

I've tested this series with nested KVM (vsock-transport [L0,L1],
virtio-transport[L1,L2]) and with VMware (L0) + KVM (L1)
(vmci-transport [L0,L1], vhost-transport [L1], virtio-transport[L2]).

Dexuan successfully tested the RFC series on HyperV with a Linux guest.

Stefano Garzarella (14):
  vsock/vmci: remove unused VSOCK_DEFAULT_CONNECT_TIMEOUT
  vsock: remove vm_sockets_get_local_cid()
  vsock: remove include/linux/vm_sockets.h file
  vsock: add 'transport' member in the struct vsock_sock
  vsock/virtio: add transport parameter to the
    virtio_transport_reset_no_sock()
  vsock: add 'struct vsock_sock *' param to vsock_core_get_transport()
  vsock: handle buffer_size sockopts in the core
  vsock: add vsock_create_connected() called by transports
  vsock: move vsock_insert_unbound() in the vsock_create()
  hv_sock: set VMADDR_CID_HOST in the hvs_remote_addr_init()
  vsock: add multi-transports support
  vsock/vmci: register vmci_transport only when VMCI guest/host are
    active
  vsock: prevent transport modules unloading
  vsock: fix bind() behaviour taking care of CID

 drivers/misc/vmw_vmci/vmci_driver.c     |  50 ++++
 drivers/misc/vmw_vmci/vmci_driver.h     |   2 +
 drivers/misc/vmw_vmci/vmci_guest.c      |   2 +
 drivers/misc/vmw_vmci/vmci_host.c       |   7 +
 drivers/vhost/vsock.c                   |  96 +++---
 include/linux/virtio_vsock.h            |  18 +-
 include/linux/vm_sockets.h              |  15 -
 include/linux/vmw_vmci_api.h            |   2 +
 include/net/af_vsock.h                  |  44 +--
 include/net/vsock_addr.h                |   2 +-
 net/vmw_vsock/af_vsock.c                | 376 ++++++++++++++++++------
 net/vmw_vsock/hyperv_transport.c        |  70 ++---
 net/vmw_vsock/virtio_transport.c        | 177 ++++++-----
 net/vmw_vsock/virtio_transport_common.c | 131 +++------
 net/vmw_vsock/vmci_transport.c          | 137 +++------
 net/vmw_vsock/vmci_transport.h          |   3 -
 net/vmw_vsock/vmci_transport_notify.h   |   1 -
 17 files changed, 627 insertions(+), 506 deletions(-)
 delete mode 100644 include/linux/vm_sockets.h
```
#### [PATCH v8 0/5] Add a unified parameter "nopvspin"
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
From patchwork Wed Oct 23 11:16:19 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11206359
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D0BD14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 11:19:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 70DE921906
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 11:19:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="lzYZ37nd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404640AbfJWLTQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 07:19:16 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:44992 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404543AbfJWLTQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 07:19:16 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9NB9Wjn044781;
        Wed, 23 Oct 2019 11:17:11 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2019-08-05;
 bh=9IpjYxNkQXUflfRwtoJIwSIYGnGJ9sg16wFTmhQflww=;
 b=lzYZ37ndJIEKT/pu34sev7qhitguoliLqMoCY4GoUWcJlLmRrGZfgQAwrwigw4awQ7RZ
 NVgF4CUt3R4lscy/LZDaTlksZw3WYtm061o9w+KBIovr13WLYYO93Hi8+WoE2NJ3WOKz
 oGjo8HWFWDaJ6i0bt1Kk8e5tiPD5BryyzLBPM/6p4VmtCxS7VjRZu19vAp70iBYt1OrL
 1vmzfOSc1JtQ0XB1IXR8fvvX5mdOS8u0D/1OZdEh9aEqiSySaof8u+WpHo68WL/WxvR5
 FAGtQbpoYJ2Wnz7YJak/kAlDwAsvr5oleqrxogca3M1/V3pPEhP6yaM76mcaXLn1x3UE NQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 2vqu4qvenw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Oct 2019 11:17:10 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9NBDPIt145394;
        Wed, 23 Oct 2019 11:17:10 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 2vt2hf4au7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 23 Oct 2019 11:17:09 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x9NBH39m014839;
        Wed, 23 Oct 2019 11:17:03 GMT
Received: from z2.cn.oracle.com (/10.182.71.218)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 23 Oct 2019 04:17:02 -0700
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        pbonzini@redhat.com, rkrcmar@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        boris.ostrovsky@oracle.com, jgross@suse.com, peterz@infradead.org,
        will@kernel.org, linux-hyperv@vger.kernel.org, kvm@vger.kernel.org,
        mikelley@microsoft.com, kys@microsoft.com, haiyangz@microsoft.com,
        sthemmin@microsoft.com, sashal@kernel.org,
        Zhenzhong Duan <zhenzhong.duan@oracle.com>
Subject: [PATCH v8 0/5] Add a unified parameter "nopvspin"
Date: Wed, 23 Oct 2019 19:16:19 +0800
Message-Id: <1571829384-5309-1-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9418
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910230114
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9418
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910230114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are cases folks want to disable spinlock optimization for
debug/test purpose. Xen and hyperv already have parameters "xen_nopvspin"
and "hv_nopvspin" to support that, but kvm doesn't.

The first patch adds that feature to KVM guest with "nopvspin".

For compatibility reason original parameters "xen_nopvspin" and
"hv_nopvspin" are retained and marked obsolete.

v8:
PATCH2: use 'kvm-guest' instead of 'kvm_guest'        [Sean Christopherson]
PATCH3: add a comment to explain missed 'return'      [Sean Christopherson]

v7:
PATCH3: update comment and use goto, add RB              [Vitaly Kuznetsov]

v6:
PATCH1: add Reviewed-by                                  [Vitaly Kuznetsov]
PATCH2: change 'pv' to 'PV', add Reviewed-by             [Vitaly Kuznetsov]
PATCH3: refactor 'if' branch in kvm_spinlock_init()      [Vitaly Kuznetsov]

v5:
PATCH1: new patch to revert a currently unnecessory commit,
        code is simpler a bit after that change.         [Boris Ostrovsky]
PATCH3: fold 'if' statement,add comments on virt_spin_lock_key,
        reorder with PATCH2 to better reflect dependency                               
PATCH4: fold 'if' statement, add Reviewed-by             [Boris Ostrovsky]
PATCH5: add Reviewed-by                                  [Michael Kelley]

v4:
PATCH1: use variable name nopvspin instead of pvspin and
        defined it as __initdata, changed print message,
        updated patch description                     [Sean Christopherson]
PATCH2: remove Suggested-by, use "kvm-guest:" prefix  [Sean Christopherson]
PATCH3: make variable nopvsin and xen_pvspin coexist
        remove Reviewed-by due to code change         [Sean Christopherson]
PATCH4: make variable nopvsin and hv_pvspin coexist   [Sean Christopherson]

v3:
PATCH2: Fix indentation

v2:
PATCH1: pick the print code change into separate PATCH2,
        updated patch description             [Vitaly Kuznetsov]
PATCH2: new patch with print code change      [Vitaly Kuznetsov]
PATCH3: add Reviewed-by                       [Juergen Gross]

Zhenzhong Duan (5):
  Revert "KVM: X86: Fix setup the virt_spin_lock_key before static key
    get initialized"
  x86/kvm: Change print code to use pr_*() format
  x86/kvm: Add "nopvspin" parameter to disable PV spinlocks
  xen: Mark "xen_nopvspin" parameter obsolete
  x86/hyperv: Mark "hv_nopvspin" parameter obsolete

 Documentation/admin-guide/kernel-parameters.txt | 14 ++++-
 arch/x86/hyperv/hv_spinlock.c                   |  4 ++
 arch/x86/include/asm/qspinlock.h                |  1 +
 arch/x86/kernel/kvm.c                           | 79 ++++++++++++++++---------
 arch/x86/xen/spinlock.c                         |  4 +-
 kernel/locking/qspinlock.c                      |  7 +++
 6 files changed, 76 insertions(+), 33 deletions(-)
```
#### [patch V2 00/17] entry: Provide generic implementation for host and
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Wed Oct 23 12:27:05 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11206605
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 08999913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 12:33:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E486F21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 12:33:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391379AbfJWMbk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 08:31:40 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:49085 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388581AbfJWMbk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 08:31:40 -0400
Received: from localhost ([127.0.0.1] helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtp (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1iNFna-00016r-NM; Wed, 23 Oct 2019 14:31:34 +0200
Message-Id: <20191023122705.198339581@linutronix.de>
User-Agent: quilt/0.65
Date: Wed, 23 Oct 2019 14:27:05 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Andy Lutomirski <luto@kernel.org>,
        Will Deacon <will@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org, Mike Rapoport <rppt@linux.ibm.com>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Miroslav Benes <mbenes@suse.cz>
Subject: [patch V2 00/17] entry: Provide generic implementation for host and
 guest entry/exit work
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When working on a way to move out the posix cpu timer expiry out of the
timer interrupt context, I noticed that KVM is not handling pending task
work before entering a guest. A quick hack was to add that to the x86 KVM
handling loop. The discussion ended with a request to make this a generic
infrastructure possible with also moving the per arch implementations of
the enter from and return to user space handling generic.

  https://lore.kernel.org/r/89E42BCC-47A8-458B-B06A-D6A20D20512C@amacapital.net

The series implements the syscall enter/exit and the general exit to
userspace work handling along with the pre guest enter functionality.

Changes vs. RFC version:

  - Dropped ARM64 conversion as requested by ARM64 folks

  - Addressed various review comments (Peter, Andy, Mike, Paolo, Josh,
    Miroslav)

  - Picked up, fixed and completed Peter's patch which makes interrupt
    enable/disable symmetric in trap handlers

  - Completed the removal of irq disabling / irq tracing from low level
    ASM code

  - Moved KVM specific parts of the enter guest mode handling to KVM
    (Paolo)

The series is also available from git:

   git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git WIP/core.entry

Thanks,

        tglx

RFC version: https://lore.kernel.org/r/20190919150314.054351477@linutronix.de
Acked-by: Peter Zijlstra (Intel) <peterz@infradead.org>
---
 /Makefile                             |    3 
 arch/Kconfig                          |    3 
 arch/x86/Kconfig                      |    1 
 arch/x86/entry/calling.h              |   12 +
 arch/x86/entry/common.c               |  264 ++------------------------------
 arch/x86/entry/entry_32.S             |   41 ----
 arch/x86/entry/entry_64.S             |   32 ---
 arch/x86/entry/entry_64_compat.S      |   30 ---
 arch/x86/include/asm/irqflags.h       |    8 
 arch/x86/include/asm/paravirt.h       |    9 -
 arch/x86/include/asm/signal.h         |    1 
 arch/x86/include/asm/thread_info.h    |    9 -
 arch/x86/kernel/signal.c              |    2 
 arch/x86/kernel/traps.c               |   33 ++--
 arch/x86/kvm/x86.c                    |   17 --
 arch/x86/mm/fault.c                   |    7 
 b/arch/x86/include/asm/entry-common.h |  104 ++++++++++++
 b/arch/x86/kvm/Kconfig                |    1 
 b/include/linux/entry-common.h        |  280 ++++++++++++++++++++++++++++++++++
 b/kernel/entry/common.c               |  184 ++++++++++++++++++++++
 include/linux/kvm_host.h              |   64 +++++++
 kernel/Makefile                       |    1 
 virt/kvm/Kconfig                      |    3 
 23 files changed, 735 insertions(+), 374 deletions(-)
```
#### [PATCH V5 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Oct 23 13:07:46 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11206773
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D64AD1920
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 13:11:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A251C21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 13:11:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SVdwwb3S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405655AbfJWNLN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 09:11:13 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:50515 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726032AbfJWNLM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Oct 2019 09:11:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1571836270;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=qtx994Rd94G9nH4lOA8VDgGSSgdKvPnh3lGGKTP7LFQ=;
        b=SVdwwb3SZtWmAkLmuDWi8EZvmUmD4OvaVhUpkLUMoxSoEjFt5JzmStxkoldpJc0fDcrKgk
        z3sT6purAl8lWn1ChrwyrsF/a1haJFPEqFEh3fKPN2Jgo+bvD3Bm9SHCSABu4QYqrlUzG/
        jKK3OnRDS8VOeiYLH5h5Rp7pvE3SJe4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-295-RJarepR0PYeS969OfkOvEw-1; Wed, 23 Oct 2019 09:11:04 -0400
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2E8E047B;
        Wed, 23 Oct 2019 13:10:58 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-126.pek2.redhat.com [10.72.12.126])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CB482600CC;
        Wed, 23 Oct 2019 13:07:58 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V5 0/6] mdev based hardware virtio offloading support
Date: Wed, 23 Oct 2019 21:07:46 +0800
Message-Id: <20191023130752.18980-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: RJarepR0PYeS969OfkOvEw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

There are hardwares that can do virtio datapath offloading while
having its own control path. This path tries to implement a mdev based
unified API to support using kernel virtio driver to drive those
devices. This is done by introducing a new mdev transport for virtio
(virtio_mdev) and register itself as a new kind of mdev driver. Then
it provides a unified way for kernel virtio driver to talk with mdev
device implementation.

Though the series only contains kernel driver support, the goal is to
make the transport generic enough to support userspace drivers. This
means vhost-mdev[1] could be built on top as well by resuing the
transport.

A sample driver is also implemented which simulate a virito-net
loopback ethernet device on top of vringh + workqueue. This could be
used as a reference implementation for real hardware driver.

Also a real ICF VF driver was also posted here[2] which is a good
reference for vendors who is interested in their own virtio datapath
offloading product.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific parents ops out of the common ones.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/10/22/262
[2] https://lkml.org/lkml/2019/10/15/1226

Changes from V4:

- keep mdev_set_class() for the device that doesn't use device ops
- use union for device ops pointer in mdev_device
- introduce class specific helper for getting is device ops
- use WARN_ON instead of BUG_ON in mdev_set_virtio_ops
- explain details of get_mdev_features() and get_vendor_id()
- distinguish the optional virito device ops from mandatory ones and
  make get_generation() optional
- rename vfio_mdev.h to vfio_mdev_ops.h, rename virito_mdev.h to
  virtio_mdev_ops.h
- don't abuse version fileds in virtio_mdev structure, use features
  instead
- fix warning during device remove
- style & docs tweaks and typo fixes

Changes from V3:

- document that class id (device ops) must be specified in create()
- add WARN() when trying to set class_id when it has already set
- add WARN() when class_id is not specified in create() and correctly
  return an error in this case
- correct the prototype of mdev_set_class() in the doc
- add documention of mdev_set_class()
- remove the unnecessary "class_id_fail" label when class id is not
  specified in create()
- convert id_table in vfio_mdev to const
- move mdev_set_class and its friends after mdev_uuid()
- suqash the patch of bus uevent into patch of introducing class id
- tweak the words in the docs per Cornelia suggestion
- tie class_id and device ops through class specific initialization
  routine like mdev_set_vfio_ops()
- typos fixes in the docs of virtio-mdev callbacks
- document the usage of virtqueues in struct virtio_mdev_device
- remove the useless vqs array in struct virtio_mdev_device
- rename MDEV_ID_XXX to MDEV_CLASS_ID_XXX

Changes from V2:

- fail when class_id is not specified
- drop the vringh patch
- match the doc to the code
- tweak the commit log
- move device_ops from parent to mdev device
- remove the unused MDEV_ID_VHOST

Changes from V1:

- move virtio_mdev.c to drivers/virtio
- store class_id in mdev_device instead of mdev_parent
- store device_ops in mdev_device instead of mdev_parent
- reorder the patch, vringh fix comes first
- really silent compiling warnings
- really switch to use u16 for class_id
- uevent and modpost support for mdev class_id
- vraious tweaks per comments from Parav

Changes from RFC-V2:

- silent compile warnings on some specific configuration
- use u16 instead u8 for class id
- reseve MDEV_ID_VHOST for future vhost-mdev work
- introduce "virtio" type for mvnet and make "vhost" type for future
  work
- add entries in MAINTAINER
- tweak and typos fixes in commit log

Changes from RFC-V1:

- rename device id to class id
- add docs for class id and device specific ops (device_ops)
- split device_ops into seperate headers
- drop the mdev_set_dma_ops()
- use device_ops to implement the transport API, then it's not a part
  of UAPI any more
- use GFP_ATOMIC in mvnet sample device and other tweaks
- set_vring_base/get_vring_base support for mvnet device

Jason Wang (6):
  mdev: class id support
  modpost: add support for mdev class id
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  38 +-
 MAINTAINERS                                   |   2 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  59 ++
 drivers/vfio/mdev/mdev_driver.c               |  22 +
 drivers/vfio/mdev/mdev_private.h              |   8 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |   7 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 413 +++++++++++
 include/linux/mdev.h                          |  57 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev_ops.h                 |  52 ++
 include/linux/virtio_mdev_ops.h               | 159 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 691 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  10 +
 24 files changed, 1594 insertions(+), 91 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev_ops.h
 create mode 100644 include/linux/virtio_mdev_ops.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH v2 0/3] kcov: collect coverage from usb and vhost
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
From patchwork Wed Oct 23 15:24:28 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11207023
Return-Path: <SRS0=2s9g=YQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 10FE71515
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 15:25:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E2A3921928
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 23 Oct 2019 15:25:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ghJIP1Ct"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406668AbfJWPYi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Oct 2019 11:24:38 -0400
Received: from mail-wr1-f73.google.com ([209.85.221.73]:48575 "EHLO
        mail-wr1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390590AbfJWPYi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 23 Oct 2019 11:24:38 -0400
Received: by mail-wr1-f73.google.com with SMTP id h4so11169888wrx.15
        for <kvm@vger.kernel.org>; Wed, 23 Oct 2019 08:24:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=sl8Rii3oW8FrPppkHNfXTlYWCFHCdXZbJp62ZIanwPg=;
        b=ghJIP1Ctautskm3gCcyff8Fxk9XjUZJnGCzEtm3Rl/xa3OQaA7z8Hj2K2nk/9K0ZVV
         OF+hfWb+AgK9wd8dgydPemrquzm2MQhbeGLmyaDDzkHnJbU6bTw4am6muwzKs1pG0gMl
         ViCBVAS6V8lonROATMQ/xHp4LMBWEuofzZhWqM+57MOvtOV6KIQiMs91jjbuC1SjFMGQ
         TJ/G+y0wWzii5SyCE4xCYBgtIQas6JpF8l6FkKmIrRdoyJTr31mPOxcMkwBwaQ7eOSIi
         WNIVEkpKXUoPyA5U3Rj8yghYjCOUpqT2B9yQusYIqZ18ZfTLxbudeUdV6xgfDpt47nqA
         jmNg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=sl8Rii3oW8FrPppkHNfXTlYWCFHCdXZbJp62ZIanwPg=;
        b=iI+KsYFY0t+md4Jk9EX4EO+jZE++uLm6GQPypZPZCuJ2LBXcyFEEOHqhuKcx6z/2rP
         62fmCUZ0VRCJn4kECLrNB0A6q+Rehr/VqUljMthlG1DoW5jJ4wRX8j52HdlP8Htg+qj8
         lTxDq8T2xauJGTZWuib6lX6SrixErGOjFfJDG7WmzN0IBm6RCMxp4OnTRSS5ZY2Tdbq8
         kHTpoNp8X0OIoMYTpJCS+dih8KHlNPDC2Xo/AN9GHAnniDBwshuLpvgRxUp8jigI2AuC
         7eGSgggC6Cer3pHBRDSEPjEjKObriGvEWy+cw2kxjR/JAlSgyVLYsLGzpSJjqsLJOokk
         E+2A==
X-Gm-Message-State: APjAAAWW/c2jwpQlpYBd6bxC3W36y5n5SAhdmAdOPQbak0+oOjsmzgLX
        qc62o5hpXEOze0lZQHW12TR5UQG67ocJkOgi
X-Google-Smtp-Source: 
 APXvYqyjuZuZmULkMOG81SOZwdNmn4nrXac1sf+c/F+14+2oEH7lN31t5wlahvJCBOuTrGSQ8vrMv/7kGc0xWT1F
X-Received: by 2002:a5d:4491:: with SMTP id j17mr8733249wrq.46.1571844275774;
 Wed, 23 Oct 2019 08:24:35 -0700 (PDT)
Date: Wed, 23 Oct 2019 17:24:28 +0200
Message-Id: <cover.1571844200.git.andreyknvl@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [PATCH v2 0/3] kcov: collect coverage from usb and vhost
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Alexander Potapenko <glider@google.com>,
        Marco Elver <elver@google.com>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset extends kcov to allow collecting coverage from the USB
subsystem and vhost workers. See the first patch description for details
about the kcov extension. The other two patches apply this kcov extension
to USB and vhost.

These patches have been used to enable coverage-guided USB fuzzing with
syzkaller for the last few years, see the details here:

https://github.com/google/syzkaller/blob/master/docs/linux/external_fuzzing_usb.md

This patchset has been pushed to the public Linux kernel Gerrit instance:

https://linux-review.googlesource.com/c/linux/kernel/git/torvalds/linux/+/1524

Changes v1 -> v2:
- Changed common_handle type back to u64 (to allow extending it in the
  future).
- Reworked kcov_remote_handle() helpers.
- Fixed vhost annotations when CONFIG_KCOV is not enabled.
- Use kcov_disable() instead of kcov_remote_reset() when
  KCOV_REMOTE_ENABLE fails.

Changes RFC v1 -> v1:
- Remove unnecessary #ifdef's from drivers/vhost/vhost.c.
- Reset t->kcov when area allocation fails in kcov_remote_start().
- Use struct_size to calculate array size in kcov_ioctl().
- Add a limit on area_size in kcov_remote_arg.
- Added kcov_disable() helper.
- Changed encoding of kcov remote handle ids, see the documentation.
- Added a comment reference for kcov_sequence task_struct field.
- Change common_handle type to u32.
- Add checks for handle validity into kcov_ioctl_locked() and
    kcov_remote_start().
- Updated documentation to reflect the changes.

Andrey Konovalov (3):
  kcov: remote coverage support
  usb, kcov: collect coverage from hub_event
  vhost, kcov: collect coverage from vhost_worker

 Documentation/dev-tools/kcov.rst | 128 +++++++++
 drivers/usb/core/hub.c           |   5 +
 drivers/vhost/vhost.c            |   6 +
 drivers/vhost/vhost.h            |   1 +
 include/linux/kcov.h             |  23 ++
 include/linux/sched.h            |   6 +
 include/uapi/linux/kcov.h        |  25 ++
 kernel/kcov.c                    | 480 ++++++++++++++++++++++++++++---
 8 files changed, 639 insertions(+), 35 deletions(-)
```
