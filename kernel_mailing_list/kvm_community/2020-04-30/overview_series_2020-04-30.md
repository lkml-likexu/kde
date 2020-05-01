#### [PATCH] vhost: add mutex_lock/unlock for vhost_vq_reset
##### From: Jia He <justin.he@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Justin He <justin.he@arm.com>
X-Patchwork-Id: 11519089
Return-Path: <SRS0=DGI+=6O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5FE0E1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 02:41:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4352F2083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 02:41:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726828AbgD3Clv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 22:41:51 -0400
Received: from foss.arm.com ([217.140.110.172]:47946 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726180AbgD3Clv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 22:41:51 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 742771063;
        Wed, 29 Apr 2020 19:41:50 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-02.shanghai.arm.com
 [10.169.138.57])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 D915F3F68F;
        Wed, 29 Apr 2020 19:41:47 -0700 (PDT)
From: Jia He <justin.he@arm.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        Kaly.Xin@arm.com, Jia He <justin.he@arm.com>
Subject: [PATCH] vhost: add mutex_lock/unlock for vhost_vq_reset
Date: Thu, 30 Apr 2020 10:41:40 +0800
Message-Id: <20200430024140.42065-1-justin.he@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vq->mutex is to protect any vq accessing, hence adding mutex_lock/unlock
makes sense to avoid potential race condition.

Signed-off-by: Jia He <justin.he@arm.com>
---
 drivers/vhost/vhost.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] vhost: vsock: don't send pkt when vq is not started
##### From: Jia He <justin.he@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Justin He <justin.he@arm.com>
X-Patchwork-Id: 11519083
Return-Path: <SRS0=DGI+=6O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 19196912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 02:13:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B46620656
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 02:13:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726784AbgD3CN0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 22:13:26 -0400
Received: from foss.arm.com ([217.140.110.172]:47702 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726180AbgD3CN0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 22:13:26 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C31E61063;
        Wed, 29 Apr 2020 19:13:25 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-02.shanghai.arm.com
 [10.169.138.57])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 2019D3F68F;
        Wed, 29 Apr 2020 19:13:22 -0700 (PDT)
From: Jia He <justin.he@arm.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        Kaly.Xin@arm.com, Jia He <justin.he@arm.com>
Subject: [PATCH] vhost: vsock: don't send pkt when vq is not started
Date: Thu, 30 Apr 2020 10:13:14 +0800
Message-Id: <20200430021314.6425-1-justin.he@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ning Bo reported an abnormal 2-second gap when booting Kata container [1].
The unconditional timeout is caused by VSOCK_DEFAULT_CONNECT_TIMEOUT of
connect at client side. The vhost vsock client tries to connect an
initlizing virtio vsock server.

The abnormal flow looks like:
host-userspace           vhost vsock                       guest vsock
==============           ===========                       ============
connect()     -------->  vhost_transport_send_pkt_work()   initializing
   |                     vq->private_data==NULL
   |                     will not be queued
   V
schedule_timeout(2s)
                         vhost_vsock_start()  <---------   device ready
                         set vq->private_data

wait for 2s and failed

connect() again          vq->private_data!=NULL          recv connecting pkt

1. host userspace sends a connect pkt, at that time, guest vsock is under
initializing, hence the vhost_vsock_start has not been called. So
vq->private_data==NULL, and the pkt is not been queued to send to guest.
2. then it sleeps for 2s
3. after guest vsock finishes initializing, vq->private_data is set.
4. When host userspace wakes up after 2s, send connecting pkt again,
everything is fine.

This fixes it by checking vq->private_data in vhost_transport_send_pkt,
and return at once if !vq->private_data. This makes user connect()
be returned with ECONNREFUSED.

After this patch, kata-runtime (with vsock enabled) boottime reduces from
3s to 1s on ThunderX2 arm64 server.

[1] https://github.com/kata-containers/runtime/issues/1917

Reported-by: Ning Bo <n.b@live.com>
Signed-off-by: Jia He <justin.he@arm.com>
---
 drivers/vhost/vsock.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### =?utf-8?b?562U5aSNOiBbUEFUQ0hdW3YyXSBrdm06IHg4NjogZW11bGF0ZSBBUEVS?=	=?utf-8?b?Ri9NUEVSRiByZWdpc3RlcnM=?=
##### From: "Li,Rongqing" <lirongqing@baidu.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Li RongQing <lirongqing@baidu.com>
X-Patchwork-Id: 11519061
Return-Path: <SRS0=DGI+=6O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2F82912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 02:01:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9EE982083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Apr 2020 02:01:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726511AbgD3CBa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Apr 2020 22:01:30 -0400
Received: from mx22.baidu.com ([220.181.50.185]:38918 "EHLO baidu.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726282AbgD3CBa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Apr 2020 22:01:30 -0400
Received: from BC-Mail-Ex16.internal.baidu.com (unknown [172.31.51.56])
        by Forcepoint Email with ESMTPS id 7AD7E984D2F571FACB69;
        Thu, 30 Apr 2020 09:45:30 +0800 (CST)
Received: from BJHW-Mail-Ex13.internal.baidu.com (10.127.64.36) by
 BC-Mail-Ex16.internal.baidu.com (172.31.51.56) with Microsoft SMTP Server
 (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id
 15.1.1531.3; Thu, 30 Apr 2020 09:45:30 +0800
Received: from BJHW-Mail-Ex13.internal.baidu.com ([100.100.100.36]) by
 BJHW-Mail-Ex13.internal.baidu.com ([100.100.100.36]) with mapi id
 15.01.1713.004; Thu, 30 Apr 2020 09:45:30 +0800
From: "Li,Rongqing" <lirongqing@baidu.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>
CC: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "x86@kernel.org" <x86@kernel.org>, "hpa@zytor.com" <hpa@zytor.com>,
        "bp@alien8.de" <bp@alien8.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "tglx@linutronix.de" <tglx@linutronix.de>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "jmattson@google.com" <jmattson@google.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "sean.j.christopherson@intel.com" <sean.j.christopherson@intel.com>
Subject: =?utf-8?b?562U5aSNOiBbUEFUQ0hdW3YyXSBrdm06IHg4NjogZW11bGF0ZSBBUEVS?=
	=?utf-8?b?Ri9NUEVSRiByZWdpc3RlcnM=?=
Thread-Topic: [PATCH][v2] kvm: x86: emulate APERF/MPERF registers
Thread-Index: AQHWHgPRaxq7VoyE2kqvmC7wjQtzhaiPXbuAgAGG2mA=
Date: Thu, 30 Apr 2020 01:45:30 +0000
Message-ID: <bea20279850d48848e0b21f7cbb39bdb@baidu.com>
References: <1588139196-23802-1-git-send-email-lirongqing@baidu.com>
 <20200429085440.GG13592@hirez.programming.kicks-ass.net>
 <201824a4-6b0f-9061-ec21-26d71fa11bc4@redhat.com>
In-Reply-To: <201824a4-6b0f-9061-ec21-26d71fa11bc4@redhat.com>
Accept-Language: zh-CN, en-US
Content-Language: zh-CN
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-originating-ip: [172.22.198.11]
x-baidu-bdmsfe-datecheck: 1_BC-Mail-Ex16_2020-04-30 09:45:30:295
x-baidu-bdmsfe-viruscheck: BC-Mail-Ex16_GRAY_Inside_WithoutAtta_2020-04-30
 09:45:30:186
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

> -----邮件原件-----
> 发件人: Paolo Bonzini [mailto:pbonzini@redhat.com]
> 发送时间: 2020年4月29日 18:21
> 收件人: Peter Zijlstra <peterz@infradead.org>; Li,Rongqing
> <lirongqing@baidu.com>
> 抄送: linux-kernel@vger.kernel.org; kvm@vger.kernel.org; x86@kernel.org;
> hpa@zytor.com; bp@alien8.de; mingo@redhat.com; tglx@linutronix.de;
> joro@8bytes.org; jmattson@google.com; wanpengli@tencent.com;
> vkuznets@redhat.com; sean.j.christopherson@intel.com
> 主题: Re: [PATCH][v2] kvm: x86: emulate APERF/MPERF registers
> 
> On 29/04/20 10:54, Peter Zijlstra wrote:
> > On Wed, Apr 29, 2020 at 01:46:36PM +0800, Li RongQing wrote:
> >> Guest kernel reports a fixed cpu frequency in /proc/cpuinfo, this is
> >> confused to user when turbo is enable, and aperf/mperf can be used to
> >> show current cpu frequency after 7d5905dc14a
> >> "(x86 / CPU: Always show current CPU frequency in /proc/cpuinfo)"
> >> so we should emulate aperf mperf to achieve it
> >>
> >> the period of aperf/mperf in guest mode are accumulated as emulated
> >> value, and add per-VM knod to enable emulate mperfaperf
> >>
> >> diff v1:
> >> 1. support AMD
> >> 2. support per-vm capability to enable
> > Would it make sense to provide a pass-through APERF/MPERF for
> > KVM_HINTS_REALTIME ? Because that hint guarantees we have a 1:1
> > vCPU:CPU binding and guaranteed no over-commit.
> >
> 
> Yes but that's up to userspace.
> 
> Paolo

Seem kernel should give the capability to userspace to disable the intercept mperf/aperf for KVM_HINTS_REALTIME

So I will change this patch to support three mode mperfaperf:  none, software emulate, and pt




-Li

```
