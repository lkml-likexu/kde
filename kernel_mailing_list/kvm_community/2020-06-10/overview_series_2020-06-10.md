#### [PATCH 1/2] KVM: async_pf: Cleanup kvm_setup_async_pf()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11598531
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4B3A190
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 17:55:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3187B2070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 17:55:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Y0D40yWX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726823AbgFJRzm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 13:55:42 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:48798 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726095AbgFJRzm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 13:55:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591811740;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fT7MJxxe/N/GC6AUG3wTzK87t8/hohYB8InpgjdJuSE=;
        b=Y0D40yWXtiHwnfRMbdQWAiPQmnf0jxowC9I8FgwVi5hG8p0JUuZxrG44UCY4A/VJTH0cLG
        Q8YG19DutJDfiV44eDV1Mf8pSf5PWUMQCRmFK25M4VRqEZGMeZ5y2GZzRVlHWoihMb8yXD
        0IMbcMhoulhGGcq0/ZMlcOKjl6UxNfg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-261-4-i27Ty0MxuQ6YUuacqyWQ-1; Wed, 10 Jun 2020 13:55:39 -0400
X-MC-Unique: 4-i27Ty0MxuQ6YUuacqyWQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 89904461;
        Wed, 10 Jun 2020 17:55:37 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 415317BA14;
        Wed, 10 Jun 2020 17:55:34 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Vivek Goyal <vgoyal@redhat.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: async_pf: Cleanup kvm_setup_async_pf()
Date: Wed, 10 Jun 2020 19:55:31 +0200
Message-Id: <20200610175532.779793-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

schedule_work() returns 'false' only when the work is already on the queue
and this can't happen as kvm_setup_async_pf() always allocates a new one.
Also, to avoid potential race, it makes sense to to schedule_work() at the
very end after we've added it to the queue.

While on it, do some minor cleanup. gfn_to_pfn_async() mentioned in a
comment does not currently exist and, moreover, we can check
kvm_is_error_hva() at the very beginning, before we try to allocate work so
'retry_sync' label can go away completely.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 virt/kvm/async_pf.c | 19 ++++++-------------
 1 file changed, 6 insertions(+), 13 deletions(-)

```
#### [GIT PULL] virtio: features, fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11596933
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC096912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 04:45:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8DC2C20734
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 04:45:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="N4FQ1E4s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726098AbgFJEpP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 00:45:15 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:43233 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726081AbgFJEpM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Jun 2020 00:45:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591764310;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=VxmhQ3VVJqCwy8aaYD5pSLwJjZ0VIqyd7EjfATRpmNc=;
        b=N4FQ1E4sY/97yjIcbn4mLhxfA7ua4XGg5sJe0dsnbOY5hDWjjOZIgJKYMAwTE8eixYdi5M
        k+AvEgkbmWe2k1YeKhzKGX3KBy6u9DG+E0gFabINgfNxUjxGtz0EtCAuGPEm70rjcjKng2
        BYoUPqTiJTHLeliUlIelw+e59ewuHRA=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-316-bW36XoevOTOY_M9HXwOAfg-1; Wed, 10 Jun 2020 00:45:07 -0400
X-MC-Unique: bW36XoevOTOY_M9HXwOAfg-1
Received: by mail-wr1-f70.google.com with SMTP id r5so528443wrt.9
        for <kvm@vger.kernel.org>; Tue, 09 Jun 2020 21:45:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=VxmhQ3VVJqCwy8aaYD5pSLwJjZ0VIqyd7EjfATRpmNc=;
        b=kDPszzKKQJ79n7n9pG1djzQnclsWw4Kwlwlz2RlP4eSpSKShimgdU4k/ZZULxE77Ze
         0UuK0S8zJP+16aL7jxgzflCOYF9kQ9Ejvxa/AK1AB23xuGONP46tsAdPuimk5UqE4VZF
         y9ptre42jKwpmrk/CUStRLTKaDrlQYJJyjv0mTccx7to2RhLy9R0H/nkAWnoOC3E5Nt4
         bKMm/Hmk0Z+4ZmtCR9gJmicRQqCN+3toJIMrz2HhWB64kkX7i+xSp3zajXD4jR6+kdyM
         HXfM62Rw55wpDJwEPxCYTYiiPpMUzXdJ/ejy8tQCdTvrVpvqnvtsHzzuIJ77iphjlPXq
         /UvA==
X-Gm-Message-State: AOAM531tXIemWO6HFg1WP3Xnixm+0tnInVOs2AbWK+hf8Mq+gFxVNDbW
        fsWqvshGVwXKvHpfVtbawPUbNYYZsbmL4j07fnwAF2C9Wo4g13DqXzsVpJ+SPoveVw7ZF8AGQfL
        hyKIhY/NyJ9YV
X-Received: by 2002:a5d:5001:: with SMTP id e1mr1496107wrt.56.1591764305573;
        Tue, 09 Jun 2020 21:45:05 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJywRytP6FIoM+W4oWypswZZXFPjrrjECTCkbmv+pP0bloGWVKqtSdiGopJ/ccnY8HzNdJNBwg==
X-Received: by 2002:a5d:5001:: with SMTP id e1mr1496086wrt.56.1591764305280;
        Tue, 09 Jun 2020 21:45:05 -0700 (PDT)
Received: from redhat.com (bzq-79-181-55-232.red.bezeqint.net.
 [79.181.55.232])
        by smtp.gmail.com with ESMTPSA id
 q128sm5199346wma.38.2020.06.09.21.45.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 09 Jun 2020 21:45:04 -0700 (PDT)
Date: Wed, 10 Jun 2020 00:44:55 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        akpm@linux-foundation.org, alexander.h.duyck@linux.intel.com,
        anshuman.khandual@arm.com, anthony.yznaga@oracle.com,
        arei.gonglei@huawei.com, cai@lca.pw, clabbe@baylibre.com,
        dan.j.williams@intel.com, davem@davemloft.net, david@redhat.com,
        dyoung@redhat.com, elfring@users.sourceforge.net,
        glider@google.com, gregkh@linuxfoundation.org,
        guennadi.liakhovetski@linux.intel.com, hannes@cmpxchg.org,
        herbert@gondor.apana.org.au, hulkci@huawei.com,
        imammedo@redhat.com, jasowang@redhat.com, jgross@suse.com,
        kernelfans@gmail.com, konrad.wilk@oracle.com, lenb@kernel.org,
        lingshan.zhu@intel.com, linux-acpi@vger.kernel.org, lkp@intel.com,
        longpeng2@huawei.com, matej.genci@nutanix.com,
        mgorman@techsingularity.net, mhocko@kernel.org, mhocko@suse.com,
        mst@redhat.com, osalvador@suse.com, osalvador@suse.de,
        pankaj.gupta.linux@gmail.com, pasha.tatashin@soleen.com,
        pavel.tatashin@microsoft.com, rafael@kernel.org,
        richard.weiyang@gmail.com, rjw@rjwysocki.net, rppt@linux.ibm.com,
        stable@vger.kernel.org, stefanha@redhat.com,
        teawaterz@linux.alibaba.com, vbabka@suse.cz, zou_wei@huawei.com
Subject: [GIT PULL] virtio: features, fixes
Message-ID: <20200610004455-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There's a single commit here that I tweaked since linux-next - the
change is in printk format string which I consider trivial enough not
force wait for more testing. A couple of hashes are different from
what's in linux-next though.  I also upgraded the machine I used to sign
the tag (didn't change the key) - hope the signature is still ok. If not
pls let me know!

The following changes since commit 3d77e6a8804abcc0504c904bd6e5cdf3a5cf8162:

  Linux 5.7 (2020-05-31 16:49:15 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 044e4b09223039e571e6ec540e25552054208765:

  vhost/test: fix up after API change (2020-06-09 06:42:06 -0400)

----------------------------------------------------------------
virtio: features, fixes

virtio-mem
doorbell mapping for vdpa
config interrupt support in ifc
fixes all over the place

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Alexander Duyck (1):
      virtio-balloon: Disable free page reporting if page poison reporting is not enabled

David Hildenbrand (17):
      MAINTAINERS: Add myself as virtio-balloon co-maintainer
      virtio-mem: Paravirtualized memory hotplug
      MAINTAINERS: Add myself as virtio-mem maintainer
      virtio-mem: Allow to specify an ACPI PXM as nid
      virtio-mem: Paravirtualized memory hotunplug part 1
      virtio-mem: Paravirtualized memory hotunplug part 2
      mm: Allow to offline unmovable PageOffline() pages via MEM_GOING_OFFLINE
      virtio-mem: Allow to offline partially unplugged memory blocks
      mm/memory_hotplug: Introduce offline_and_remove_memory()
      virtio-mem: Offline and remove completely unplugged memory blocks
      virtio-mem: Better retry handling
      virtio-mem: Add parent resource for all added "System RAM"
      virtio-mem: Drop manual check for already present memory
      virtio-mem: Unplug subblocks right-to-left
      virtio-mem: Use -ETXTBSY as error code if the device is busy
      virtio-mem: Try to unplug the complete online memory block first
      virtio-mem: Don't rely on implicit compiler padding for requests

Guennadi Liakhovetski (1):
      vhost: (cosmetic) remove a superfluous variable initialisation

Jason Wang (4):
      vhost: allow device that does not depend on vhost worker
      vhost: use mmgrab() instead of mmget() for non worker device
      vdpa: introduce get_vq_notification method
      vhost_vdpa: support doorbell mapping via mmap

Longpeng(Mike) (3):
      crypto: virtio: Fix src/dst scatterlist calculation in __virtio_crypto_skcipher_do_req()
      crypto: virtio: Fix use-after-free in virtio_crypto_skcipher_finalize_req()
      crypto: virtio: Fix dest length calculation in __virtio_crypto_skcipher_do_req()

Markus Elfring (1):
      virtio-mmio: Delete an error message in vm_find_vqs()

Matej Genci (1):
      virtio: add VIRTIO_RING_NO_LEGACY

Michael S. Tsirkin (6):
      virtio: force spec specified alignment on types
      vhost: revert "vhost: disable for OABI"
      vhost_vdpa: disable doorbell mapping for !MMU
      virtio-mem: drop unnecessary initialization
      virtio_mem: convert device block size into 64bit
      vhost/test: fix up after API change

Samuel Zou (1):
      vdpasim: Fix some coccinelle warnings

Zhu Lingshan (5):
      ifcvf: move IRQ request/free to status change handlers
      ifcvf: ignore continuous setting same status value
      vhost_vdpa: Support config interrupt in vdpa
      vhost: replace -1 with VHOST_FILE_UNBIND in ioctls
      ifcvf: implement config interrupt in IFCVF

 MAINTAINERS                                |   18 +-
 drivers/acpi/numa/srat.c                   |    1 +
 drivers/crypto/virtio/virtio_crypto_algs.c |   21 +-
 drivers/misc/mic/Kconfig                   |    2 +-
 drivers/net/caif/Kconfig                   |    2 +-
 drivers/vdpa/Kconfig                       |    2 +-
 drivers/vdpa/ifcvf/ifcvf_base.c            |    3 +
 drivers/vdpa/ifcvf/ifcvf_base.h            |    4 +
 drivers/vdpa/ifcvf/ifcvf_main.c            |  146 ++-
 drivers/vdpa/vdpa_sim/vdpa_sim.c           |    7 +-
 drivers/vhost/Kconfig                      |   17 +-
 drivers/vhost/net.c                        |    2 +-
 drivers/vhost/scsi.c                       |    2 +-
 drivers/vhost/test.c                       |    2 +-
 drivers/vhost/vdpa.c                       |  112 +-
 drivers/vhost/vhost.c                      |  100 +-
 drivers/vhost/vhost.h                      |    8 +-
 drivers/vhost/vringh.c                     |    6 +-
 drivers/vhost/vsock.c                      |    2 +-
 drivers/virtio/Kconfig                     |   17 +
 drivers/virtio/Makefile                    |    1 +
 drivers/virtio/virtio_balloon.c            |    9 +-
 drivers/virtio/virtio_mem.c                | 1965 ++++++++++++++++++++++++++++
 drivers/virtio/virtio_mmio.c               |    4 +-
 drivers/virtio/virtio_pci_modern.c         |    1 +
 include/linux/memory_hotplug.h             |    1 +
 include/linux/page-flags.h                 |   10 +
 include/linux/vdpa.h                       |   16 +
 include/linux/vringh.h                     |    6 +-
 include/uapi/linux/vhost.h                 |    4 +
 include/uapi/linux/virtio_ids.h            |    1 +
 include/uapi/linux/virtio_mem.h            |  211 +++
 include/uapi/linux/virtio_ring.h           |   48 +-
 mm/memory_hotplug.c                        |   81 +-
 mm/page_alloc.c                            |   26 +
 mm/page_isolation.c                        |    9 +
 36 files changed, 2723 insertions(+), 144 deletions(-)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h
```
#### [PATCH] kselftest: runner: fix TAP output for skipped tests
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11598141
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E7F96138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 15:44:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC9242072F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 15:44:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hIfFOo+m"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730280AbgFJPo4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 11:44:56 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:60073 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727973AbgFJPo4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 11:44:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591803895;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=uLvH8zEFZY1KRuBInn1TdRSK/ogUjKzscMti6QJ2sY0=;
        b=hIfFOo+mXrXxdSGd99Gt+OKb2SpKRMjRbx2qe3wbGoMPzgf7bqlnfef9z77Rjk/3Hc6sLg
        Lka2quu9j7tCbn9aUZwAMRR47KCkLxKZ3R6GCF4WneMGucCVwItWj2wW5busane1kVPOf+
        wQqNsUAejEmfo+hu0SLC6bLZoQn9lIA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-266-6-x7pXxcOiCHHVYqISxEdA-1; Wed, 10 Jun 2020 11:44:50 -0400
X-MC-Unique: 6-x7pXxcOiCHHVYqISxEdA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4A3F0107ACF5;
        Wed, 10 Jun 2020 15:44:49 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AB2115D9D3;
        Wed, 10 Jun 2020 15:44:48 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: shuah@kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH] kselftest: runner: fix TAP output for skipped tests
Date: Wed, 10 Jun 2020 11:44:47 -0400
Message-Id: <20200610154447.15826-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the TAP specification, a skipped test must be marked as "ok"
and annotated with the SKIP directive, for example

   ok 23 # skip Insufficient flogiston pressure.
   (https://testanything.org/tap-specification.html)

Fix the runner script to match this.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 tools/testing/selftests/kselftest/runner.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/4] KVM: arm64: Save the host's PtrAuth keys in non-preemptible context
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11597523
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8BA0E739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:34:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6CA3820812
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:34:19 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591788859;
	bh=TrZf3M3cHAQOb0xV50khGwwPsW73cXBhqp8dOirlr8A=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=dYEVILIjeiTH/aXKZM7E0a1NXmhBXI+naWU7k/Yrdoqt2Y/2F6ZaTsP2j6OrpQP0Z
	 9KmeO6x6+WRbSJrTpRCH+RsTHd51ygv6UlENB0kjqQn6WlIPuCn8AW8tzwStu2+Qsh
	 y8fydJLelDpNyLH8p/gLHLH5HLa53nFF+jScsEmk=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728547AbgFJLeS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 07:34:18 -0400
Received: from mail.kernel.org ([198.145.29.99]:42736 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728491AbgFJLeR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 07:34:17 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5F0252074B;
        Wed, 10 Jun 2020 11:34:16 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591788856;
        bh=TrZf3M3cHAQOb0xV50khGwwPsW73cXBhqp8dOirlr8A=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=kz5/b6I8eEptc7qCxkktqA6xHjPypRFgozSjLyGxuMvE0SHEwR5uOnAZN/kGXtrE4
         qIuZfTRZjcp8yp/xv3rlc0uh8XPEvesRzj0amgcXBi1XOPfTuAPuhYbAv1T3/KMGcD
         39T6HHLrUn/1Mc42A6lJGJZtYLqqswR5Ukf/QYPc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jiyzm-001lrp-UW; Wed, 10 Jun 2020 12:34:15 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Andrew Scull <ascull@google.com>, kernel-team@android.com,
        stable@vger.kernel.org
Subject: [PATCH v2 1/4] KVM: arm64: Save the host's PtrAuth keys in
 non-preemptible context
Date: Wed, 10 Jun 2020 12:34:03 +0100
Message-Id: <20200610113406.1493170-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200610113406.1493170-1-maz@kernel.org>
References: <20200610113406.1493170-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 catalin.marinas@arm.com, mark.rutland@arm.com, ascull@google.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using the PtrAuth feature in a guest, we need to save the host's
keys before allowing the guest to program them. For that, we dump
them in a per-CPU data structure (the so called host context).

But both call sites that do this are in preemptible context,
which may end up in disaster should the vcpu thread get preempted
before reentering the guest.

Instead, save the keys eagerly on each vcpu_load(). This has an
increased overhead, but is at least safe.

Cc: stable@vger.kernel.org
Reviewed-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_emulate.h |  6 ------
 arch/arm64/kvm/arm.c                 | 18 +++++++++++++++++-
 arch/arm64/kvm/handle_exit.c         | 19 ++-----------------
 3 files changed, 19 insertions(+), 24 deletions(-)

```
#### [PATCH 1/2] KVM: selftests: do not substitute SVM/VMX check with KVM_CAP_NESTED_STATE check
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11597985
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C56A5739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 13:59:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9F4C0207C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 13:59:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aFQ63lMI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729603AbgFJN7D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 09:59:03 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:41793 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729573AbgFJN7B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 09:59:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591797539;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=2zqN7aOxv4tYIAbVvJMVgvhtAxpCc7lYrNw+p+JSJLQ=;
        b=aFQ63lMI0TBlD3yZRsyNzF+h9NldhxF2Po6pvctwc9e27NKOiVhTqRlYcwz2WhpPWrZ7MA
        MgHv5dw8T1KCUUgWW0wUH7gj2ZybJdjzoATiszrEMYFr2RRodx0OPMxjWZ36EmZnfOOhvb
        HLmQwdQ3us0qk1eg1JOvGv5ZQZ7M0ZA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-99-7bJ9JlWGMhiuq4ovUsxOoA-1; Wed, 10 Jun 2020 09:58:56 -0400
X-MC-Unique: 7bJ9JlWGMhiuq4ovUsxOoA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1D572805731;
        Wed, 10 Jun 2020 13:58:55 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A0B65C298;
        Wed, 10 Jun 2020 13:58:53 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: selftests: do not substitute SVM/VMX check with
 KVM_CAP_NESTED_STATE check
Date: Wed, 10 Jun 2020 15:58:46 +0200
Message-Id: <20200610135847.754289-2-vkuznets@redhat.com>
In-Reply-To: <20200610135847.754289-1-vkuznets@redhat.com>
References: <20200610135847.754289-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

state_test/smm_test use KVM_CAP_NESTED_STATE check as an indicator for
nested VMX/SVM presence and this is incorrect. Check for the required
features dirrectly.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../testing/selftests/kvm/include/x86_64/svm_util.h |  1 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h    |  1 +
 tools/testing/selftests/kvm/lib/x86_64/svm.c        | 10 +++++++---
 tools/testing/selftests/kvm/lib/x86_64/vmx.c        |  9 +++++++--
 tools/testing/selftests/kvm/x86_64/smm_test.c       | 13 +++++++------
 tools/testing/selftests/kvm/x86_64/state_test.c     | 13 +++++++------
 6 files changed, 30 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: selftests: fix sync_with_host() in smm_test
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11598333
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15E36739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 16:41:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE130206F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 16:41:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PCJVU6gT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726307AbgFJQlg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 12:41:36 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:40441 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726095AbgFJQlf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Jun 2020 12:41:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591807294;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JjmEXwM2z+xW1VlWIW84dTFtD9mhLZeCe5kD1Da0GoU=;
        b=PCJVU6gTARkLBeTSc4H1dlsXrEe8I1OsyNWQ+f0JRgADF05R/AOrV30s+f8tqWfz8GRp4B
        BIyvHG1Zt6zwYikyEYH7Y8paBq5fWi7FNHc6bAApHTMdihDTfDtR4xZTs/xEnAm9OcsJrf
        /l2qOnfUmJYraU9yLuYaGJTmymfU4VQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-227-ShVyT7k7OSCrrFC0vmj9gw-1; Wed, 10 Jun 2020 12:41:32 -0400
X-MC-Unique: ShVyT7k7OSCrrFC0vmj9gw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D24791B2C980;
        Wed, 10 Jun 2020 16:41:30 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AC5017C3B9;
        Wed, 10 Jun 2020 16:41:17 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Bandeira Condotta <mcondotta@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: selftests: fix sync_with_host() in smm_test
Date: Wed, 10 Jun 2020 18:41:16 +0200
Message-Id: <20200610164116.770811-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was reported that older GCCs compile smm_test in a way that breaks
it completely:

  kvm_exit:             reason EXIT_CPUID rip 0x4014db info 0 0
  func 7ffffffd idx 830 rax 0 rbx 0 rcx 0 rdx 0, cpuid entry not found
  ...
  kvm_exit:             reason EXIT_MSR rip 0x40abd9 info 0 0
  kvm_msr:              msr_read 487 = 0x0 (#GP)
  ...

Note, '7ffffffd' was supposed to be '80000001' as we're checking for
SVM. Dropping '-O2' from compiler flags help. Turns out, asm block in
sync_with_host() is wrong. We us 'in 0xe, %%al' instruction to sync
with the host and in 'AL' register we actually pass the parameter
(stage) but after sync 'AL' gets written to but GCC thinks the value
is still there and uses it to compute 'EAX' for 'cpuid'.

smm_test can't fully use standard ucall() framework as we need to
write a very simple SMI handler there. Fix the immediate issue by
making RAX input/output operand. While on it, make sync_with_host()
static inline.

Reported-by: Marcelo Bandeira Condotta <mcondotta@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 tools/testing/selftests/kvm/x86_64/smm_test.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] s390: protvirt: virtio: Refuse device without IOMMU
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11597895
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 369E5912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 13:12:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2678E206F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 13:12:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729197AbgFJNMB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 09:12:01 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32074 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728826AbgFJNMA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Jun 2020 09:12:00 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05AD3D1S038699;
        Wed, 10 Jun 2020 09:11:58 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31k02k8aaa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Jun 2020 09:11:58 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05AD4fTd050863;
        Wed, 10 Jun 2020 09:11:57 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31k02k8a98-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Jun 2020 09:11:57 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05AD0Rpt008390;
        Wed, 10 Jun 2020 13:11:55 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03fra.de.ibm.com with ESMTP id 31jf1grhpf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Jun 2020 13:11:55 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05ADBrZY29491288
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 10 Jun 2020 13:11:53 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EA9584C050;
        Wed, 10 Jun 2020 13:11:52 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6D3544C04E;
        Wed, 10 Jun 2020 13:11:52 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.158.19])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 10 Jun 2020 13:11:52 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH] s390: protvirt: virtio: Refuse device without IOMMU
Date: Wed, 10 Jun 2020 15:11:51 +0200
Message-Id: <1591794711-5915-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-10_07:2020-06-10,2020-06-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 spamscore=0 impostorscore=0 clxscore=1011 cotscore=-2147483648 mlxscore=0
 malwarescore=0 phishscore=0 bulkscore=0 priorityscore=1501 adultscore=0
 mlxlogscore=779 suspectscore=1 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006100093
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Protected Virtualisation protects the memory of the guest and
do not allow a the host to access all of its memory.

Let's refuse a VIRTIO device which does not use IOMMU
protected access.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/virtio/virtio_ccw.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH RFC v7 01/14] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11597569
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A830739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:38:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E06F62078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:38:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="H0+B0rDg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728571AbgFJLgG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 07:36:06 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:57948 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728338AbgFJLgG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Jun 2020 07:36:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591788962;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=pyZgoc1IoaMWB9Jefr7e/GoAFJJxo7imj3dgpBB/etA=;
        b=H0+B0rDgheh2eKx84RIOPRHMr06LQqn1WZ+iKKW+7ZFRwChEtEZJxlWO1J+7wVbUVyi6DX
        rL0IEH1ZGF6PLTvsJ624xGlwsWiAbzpRKtBcGL9WBmx7eaRissQt8gPmQiB7u8Xvul2LhC
        sYoEmgBxQ402QHzCtNLmVmEKncghN10=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-425-ppScX3NmMWaOHqpNRJv79Q-1; Wed, 10 Jun 2020 07:36:01 -0400
X-MC-Unique: ppScX3NmMWaOHqpNRJv79Q-1
Received: by mail-wr1-f72.google.com with SMTP id c14so957154wrw.11
        for <kvm@vger.kernel.org>; Wed, 10 Jun 2020 04:36:01 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:content-transfer-encoding
         :in-reply-to;
        bh=pyZgoc1IoaMWB9Jefr7e/GoAFJJxo7imj3dgpBB/etA=;
        b=pfDFjHX1vqma+wIirGMYnfFuXOM4DI62PuUXY+et8TapbpDg38yMp2+H12nOx4JiTh
         dTLjzEvGoCngxVWZKqYL1RaXkzNelynqh2xHWTnQLuIpY411QwC5S5/ftFknBJuUFsKv
         Bw6Qq7Ykjix/GALStEcOHP5Atugrf8XrMz9cahKxjqKp0guOwendQTf6+5dipKlKvxri
         gEYyo3A6h+3bOu1UAJ44TbgSglljxO/MXYuoYt1QfiRtVlRCsGGoDUXGTPNxothBb64T
         jciFi8H3o3+9KqZ6VADcToNVfT3wF3a392+Lap6RGuUZhZI7069NR8uyxJge0JAuek7r
         2UTw==
X-Gm-Message-State: AOAM530p8wp8DlFAehfuIGVNR/7xEz39qnPrUA1twqOgGi6hVh/ERJlp
        RdC/uEfNBu83VfRSjFF/Z499tVS1/HDqLL6PztuqG1p0AkVUMmqkQCH6VL5HYtPFnkg09R5eP60
        zN+++XhlyCr6A
X-Received: by 2002:adf:bbc5:: with SMTP id z5mr3253346wrg.269.1591788959997;
        Wed, 10 Jun 2020 04:35:59 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxRnisEyiSe77VgOXdspneG3+R5Whgn51TWUKnQmdwoU0/5KTvFQ8dV5mziKKbguFJ0mnBDtQ==
X-Received: by 2002:adf:bbc5:: with SMTP id z5mr3253304wrg.269.1591788959418;
        Wed, 10 Jun 2020 04:35:59 -0700 (PDT)
Received: from redhat.com ([212.92.121.57])
        by smtp.gmail.com with ESMTPSA id
 j5sm7713166wrq.39.2020.06.10.04.35.48
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 10 Jun 2020 04:35:49 -0700 (PDT)
Date: Wed, 10 Jun 2020 07:35:47 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v7 01/14] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20200610113515.1497099-2-mst@redhat.com>
References: <20200610113515.1497099-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200610113515.1497099-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
Link: https://lore.kernel.org/r/20200401183118.8334-2-eperezma@redhat.com
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 305 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 320 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost_vdpa: Fix potential underflow in vhost_vdpa_mmap()
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11597413
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9BD6618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 09:01:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D02672063A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 09:01:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="mFt9tzzp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727021AbgFJJBF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 05:01:05 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:51298 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726794AbgFJJBF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Jun 2020 05:01:05 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 05A8udnF120664;
        Wed, 10 Jun 2020 09:01:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=UzV7BGBI0LNcf2w3aD2vO/2rGl64hgFteuySfYtV4YM=;
 b=mFt9tzzp2LD1ykbmhrFfb6U9M/TYw9CygDYESgzwZupwQY9ASDDjDLOFSkJUJE0E9RkO
 2W7TCRBs65A1b6+x7Z5Cdej3k4+XVcTlk4ePQPKG8IVxRu0A/3yrwvYblCBibnKAW61e
 gD9SObkOE4+loSoCk03YEAxiG8Pw1ZB+OcdSzfS09O8E1Ax7MmnWobJp/EjOU1cJAlgC
 0vhwbMBB4MqILg5j24tuwO9evkiMhJXe6rAAkbCSxVthjhe16c6/UfIC6CDfxvu74Oid
 IXYpwS/OHMCzZ7vOx18VPqUd5RK7zRnUUp+Wr2nSKEDjXT74FnUM1Gbw6X91AKmGE6da aw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 31g3sn14y2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 10 Jun 2020 09:01:01 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 05A8vjnp053786;
        Wed, 10 Jun 2020 08:59:00 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 31gn2y4d36-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 10 Jun 2020 08:59:00 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 05A8wxpC013936;
        Wed, 10 Jun 2020 08:58:59 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 10 Jun 2020 01:58:59 -0700
Date: Wed, 10 Jun 2020 11:58:52 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        kernel-janitors@vger.kernel.org
Subject: [PATCH] vhost_vdpa: Fix potential underflow in vhost_vdpa_mmap()
Message-ID: <20200610085852.GB5439@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9647
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 phishscore=0 malwarescore=0
 bulkscore=0 adultscore=0 mlxlogscore=999 spamscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006100069
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9647
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 priorityscore=1501
 lowpriorityscore=0 impostorscore=0 cotscore=-2147483648 suspectscore=0
 spamscore=0 bulkscore=0 malwarescore=0 phishscore=0 mlxscore=0
 mlxlogscore=999 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006100069
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "vma->vm_pgoff" variable is an unsigned long so if it's larger than
INT_MAX then "index" can be negative leading to an underflow.  Fix this
by changing the type of "index" to "unsigned long".

Fixes: ddd89d0a059d ("vhost_vdpa: support doorbell mapping via mmap")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
---
 drivers/vhost/vdpa.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 01/21] exec: Introduce ram_block_discard_(disable|require)()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11597601
Return-Path: <SRS0=Uci1=7X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 50CDB138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:54:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 35FF02074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 10 Jun 2020 11:54:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="N6kPDq9G"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728728AbgFJLyt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 10 Jun 2020 07:54:49 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:60176 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728497AbgFJLys (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Jun 2020 07:54:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591790086;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=U68jIOHuvNFPHE8HVjN9BLo12zDx2a4qnBp0EnzJr9o=;
        b=N6kPDq9GUHKnVFn89FGMwRHiUeNvT4ptvngs2Moi7z52dkElst5pMgOI/0d3m1y5HaA4UE
        +p5XK8Jk0iDL0yQONpbZ7pd9LUQeXYu1d6vwRzZn9NBUddtOs6TuIDszC/pGQ0IeL2I+mF
        9LQVdDjkIAGF/kcXNz9UgrBOHrk5kr4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-283-LYF1y1dlMwuABbJGim0Zvg-1; Wed, 10 Jun 2020 07:54:40 -0400
X-MC-Unique: LYF1y1dlMwuABbJGim0Zvg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9C04E193F560;
        Wed, 10 Jun 2020 11:54:39 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-114-42.ams2.redhat.com [10.36.114.42])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BC3F25D9D3;
        Wed, 10 Jun 2020 11:54:37 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        Richard Henderson <rth@twiddle.net>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [PATCH v4 01/21] exec: Introduce
 ram_block_discard_(disable|require)()
Date: Wed, 10 Jun 2020 13:53:59 +0200
Message-Id: <20200610115419.51688-2-david@redhat.com>
In-Reply-To: <20200610115419.51688-1-david@redhat.com>
References: <20200610115419.51688-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We want to replace qemu_balloon_inhibit() by something more generic.
Especially, we want to make sure that technologies that really rely on
RAM block discards to work reliably to run mutual exclusive with
technologies that effectively break it.

E.g., vfio will usually pin all guest memory, turning the virtio-balloon
basically useless and make the VM consume more memory than reported via
the balloon. While the balloon is special already (=> no guarantees, same
behavior possible afer reboots and with huge pages), this will be
different, especially, with virtio-mem.

Let's implement a way such that we can make both types of technology run
mutually exclusive. We'll convert existing balloon inhibitors in successive
patches and add some new ones. Add the check to
qemu_balloon_is_inhibited() for now. We might want to make
virtio-balloon an acutal inhibitor in the future - however, that
requires more thought to not break existing setups.

Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Richard Henderson <rth@twiddle.net>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 balloon.c             |  3 ++-
 exec.c                | 52 +++++++++++++++++++++++++++++++++++++++++++
 include/exec/memory.h | 41 ++++++++++++++++++++++++++++++++++
 3 files changed, 95 insertions(+), 1 deletion(-)

```
