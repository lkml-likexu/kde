#### KVM: x86: switch KVMCLOCK base to monotonic raw clock
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 11215655
Return-Path: <SRS0=3Yfw=YV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E7EE912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Oct 2019 14:36:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E63CA21721
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Oct 2019 14:36:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Yj16+7d0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390195AbfJ1Og6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Oct 2019 10:36:58 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:23888 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729377AbfJ1Og5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 28 Oct 2019 10:36:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572273416;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=1tDPTKYm0gFl0ElnSqLHmBt0Ic2EiYyOwiQjqnXl2sU=;
        b=Yj16+7d0I+62dNWIEo+1xle/yq4IWH0X5rZXZXP+pIWyzYqSwD89ZMBP2GIdY1TL6XTET4
        jhcnlUM82lHH0fq0dXdSKA7i2AM0DnhzGSKpuczQu1xUDx6Kfv25FZxtI2XuRk/x7oFn3B
        aRu5ZoR0NCP1ODRMi4Ie4Qf44gsd3L4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-196-eRFzfWePNUSNu7Gi3UzFWg-1; Mon, 28 Oct 2019 10:36:54 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 52CD7180491C
        for <kvm@vger.kernel.org>; Mon, 28 Oct 2019 14:36:53 +0000 (UTC)
Received: from amt.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A6AAE5D6AE;
        Mon, 28 Oct 2019 14:36:45 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 31BFB105153;
        Mon, 28 Oct 2019 12:36:27 -0200 (BRST)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x9SEaMxL014838;
        Mon, 28 Oct 2019 12:36:22 -0200
Date: Mon, 28 Oct 2019 12:36:22 -0200
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Subject: KVM: x86: switch KVMCLOCK base to monotonic raw clock
Message-ID: <20191028143619.GA14370@amt.cnet>
MIME-Version: 1.0
User-Agent: Mutt/1.5.21 (2010-09-15)
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: eRFzfWePNUSNu7Gi3UzFWg-1
X-Mimecast-Spam-Score: 0
Content-Disposition: inline
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 0bc48bea36d1 ("KVM: x86: update master clock before computing
kvmclock_offset")
switches the order of operations to avoid the conversion 

TSC (without frequency correction) ->
system_timestamp (with frequency correction), 

which might cause a time jump.

However, it leaves any other masterclock update unsafe, which includes, 
at the moment:

        * HV_X64_MSR_REFERENCE_TSC MSR write.
        * TSC writes.
        * Host suspend/resume.

Avoid the time jump issue by using frequency uncorrected
CLOCK_MONOTONIC_RAW clock. 

Its the guests time keeping software responsability
to track and correct a reference clock such as UTC.

This fixes forward time jump (which can result in 
failure to bring up a vCPU) during vCPU hotplug:

Oct 11 14:48:33 storage kernel: CPU2 has been hot-added
Oct 11 14:48:34 storage kernel: CPU3 has been hot-added
Oct 11 14:49:22 storage kernel: smpboot: Booting Node 0 Processor 2 APIC 0x2          <-- time jump of almost 1 minute
Oct 11 14:49:22 storage kernel: smpboot: do_boot_cpu failed(-1) to wakeup CPU#2
Oct 11 14:49:23 storage kernel: smpboot: Booting Node 0 Processor 3 APIC 0x3
Oct 11 14:49:23 storage kernel: kvm-clock: cpu 3, msr 0:7ff640c1, secondary cpu clock

Which happens because:

                /*                                                               
                 * Wait 10s total for a response from AP                         
                 */                                                              
                boot_error = -1;                                                 
                timeout = jiffies + 10*HZ;                                       
                while (time_before(jiffies, timeout)) { 
                         ...
                }

Analyzed-by: Igor Mammedov <imammedo@redhat.com>
Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

```
