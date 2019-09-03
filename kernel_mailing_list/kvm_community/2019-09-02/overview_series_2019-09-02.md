#### [PATCH] doc: kvm: fix return description of KVM_SET_MSRS
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11126321
Return-Path: <SRS0=jCHW=W5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2913F1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 10:26:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0CEF621882
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 10:26:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730788AbfIBK0i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Sep 2019 06:26:38 -0400
Received: from mga18.intel.com ([134.134.136.126]:47036 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730690AbfIBK0i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Sep 2019 06:26:38 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Sep 2019 03:26:36 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,457,1559545200";
   d="scan'208";a="183277100"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by fmsmga007.fm.intel.com with ESMTP; 02 Sep 2019 03:26:35 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] doc: kvm: fix return description of KVM_SET_MSRS
Date: Mon,  2 Sep 2019 18:12:14 +0800
Message-Id: <20190902101214.77833-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 Documentation/virt/kvm/api.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/5] mdev: Introduce sha1 based mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11125975
Return-Path: <SRS0=jCHW=W5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABF741398
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 04:25:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8D14D22DD6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 04:25:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729464AbfIBEZ2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Sep 2019 00:25:28 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:35654 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729457AbfIBEYu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Sep 2019 00:24:50 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 2 Sep 2019 07:24:44 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x824OeRL001225;
        Mon, 2 Sep 2019 07:24:42 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH v3 1/5] mdev: Introduce sha1 based mdev alias
Date: Sun,  1 Sep 2019 23:24:32 -0500
Message-Id: <20190902042436.23294-2-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20190902042436.23294-1-parav@mellanox.com>
References: <20190826204119.54386-1-parav@mellanox.com>
 <20190902042436.23294-1-parav@mellanox.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some vendor drivers want an identifier for an mdev device that is
shorter than the UUID, due to length restrictions in the consumers of
that identifier.

Add a callback that allows a vendor driver to request an alias of a
specified length to be generated for an mdev device. If generated,
that alias is checked for collisions.

It is an optional attribute.
mdev alias is generated using sha1 from the mdev name.

Signed-off-by: Parav Pandit <parav@mellanox.com>
---
Changelog:
v1->v2:
 - Kept mdev_device naturally aligned
 - Added error checking for crypt_*() calls
 - Corrected a typo from 'and' to 'an'
 - Changed return type of generate_alias() from int to char*
v0->v1:
 - Moved alias length check outside of the parent lock
 - Moved alias and digest allocation from kvzalloc to kzalloc
 - &alias[0] changed to alias
 - alias_length check is nested under get_alias_length callback check
 - Changed comments to start with an empty line
 - Fixed cleaunup of hash if mdev_bus_register() fails
 - Added comment where alias memory ownership is handed over to mdev device
 - Updated commit log to indicate motivation for this feature
---
 drivers/vfio/mdev/mdev_core.c    | 123 ++++++++++++++++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h |   5 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  13 ++--
 include/linux/mdev.h             |   4 +
 4 files changed, 135 insertions(+), 10 deletions(-)

```
#### [PATCH V2] x86/Hyper-V: Fix overflow issue in the fill_gva_list()
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11126605
Return-Path: <SRS0=jCHW=W5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BC4CC14F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 12:42:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9C9FB21881
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 12:42:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Wl35b6Q2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730515AbfIBMmD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Sep 2019 08:42:03 -0400
Received: from mail-pl1-f194.google.com ([209.85.214.194]:37745 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729844AbfIBMmC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Sep 2019 08:42:02 -0400
Received: by mail-pl1-f194.google.com with SMTP id b10so1489648plr.4;
        Mon, 02 Sep 2019 05:42:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=6bMBJGLXpJhft8Uqn8LI3hEGKJdQ2rbX77O2fwCWI2E=;
        b=Wl35b6Q2vhQOwMbHRjRpL84HFK8WhqSwlYtxUV+0x2B3gqQ03umc3iEHozseCfzpOp
         4P3fbqiqSRS3obSnqmP9B/FpYu3hmibxC/sZwM/rhee086SZtgvQmvo9eaUg69WkVFIx
         wbdCcRK6vOsSeTMJUHgHlWXRaYojtAFYN7tduaAutWDdDrJjxTpuQ6yKda8o1YywuIxM
         r/lR41obOtSjX/jBaqKjMKP4e3RqEg7lJ4068KAycK1Zn6zf024uXHWRcDXxja0V2uOB
         Dj4XYxuH7MzniF4f/glaRRgR1xuTMqDd3i2UggJ3lKJ8MWgVOIhkCu5nHYjsmE1iZE1d
         is9Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=6bMBJGLXpJhft8Uqn8LI3hEGKJdQ2rbX77O2fwCWI2E=;
        b=dtmzixKKqAQL5rLJcXzQGYEhmOQ0qfXC5SLc1bvByNiW+PbsL/4xVbea/+B+aFxf4t
         VPV6rcXkDFKW7Ft5swSJqH9zWyC37dqzv+QF4VcvyJmlb31HYrziOSwfr4AKGq+6Ry8Q
         VD5GhUfEJ9gAFy2/FImG0q2OfKK7FQ13PeOXZg1snbMwk77zA3WbgzAbFxG6wDFIAGj3
         vUVO+p80smJSxL2/oFhH7IimETKBF0eC+I/KNr0TU1cdPz/zAfpbdXUbO0qli+FsBTj1
         LNNzCYHNnXxSZ2fWLuGTt9PoytmE5cuQgACNmTELtoXqX10jIltdmIzb6Uyfv0ZtFcql
         mWSA==
X-Gm-Message-State: APjAAAXqkAywDoQMZ7oV6BkatUcIGAWQ5N1nzW956gsHGeT44POAxDxN
        f0h0xTNz0fQWy5dgG0BzxYw=
X-Google-Smtp-Source: 
 APXvYqwL8FuvpT89PhUcwAWXg2lJsDj/gqyiSZZDDqJbgrkM/4x/NHTlG0g63mGuez68xRVcnuk+jQ==
X-Received: by 2002:a17:902:346:: with SMTP id
 64mr29692851pld.151.1567428122261;
        Mon, 02 Sep 2019 05:42:02 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.52])
        by smtp.googlemail.com with ESMTPSA id
 y194sm15942600pfg.116.2019.09.02.05.41.57
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Mon, 02 Sep 2019 05:42:01 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        sashal@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, x86@kernel.org,
        alex.williamson@redhat.com, cohuck@redhat.com,
        michael.h.kelley@microsoft.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>,
        linux-hyperv@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH V2] x86/Hyper-V: Fix overflow issue in the fill_gva_list()
Date: Mon,  2 Sep 2019 20:41:43 +0800
Message-Id: <20190902124143.119478-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

When the 'start' parameter is >=  0xFF000000 on 32-bit
systems, or >= 0xFFFFFFFF'FF000000 on 64-bit systems,
fill_gva_list gets into an infinite loop.  With such inputs,
'cur' overflows after adding HV_TLB_FLUSH_UNIT and always
compares as less than end.  Memory is filled with guest virtual
addresses until the system crashes

Fix this by never incrementing 'cur' to be larger than 'end'.

Reported-by: Jong Hyun Park <park.jonghyun@yonsei.ac.kr>
Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
Fixes: 2ffd9e33ce4a ("x86/hyper-v: Use hypercall for remote TLB flush")
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
---
Change since v1:
     - Simply the commit message 

 arch/x86/hyperv/mmu.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH v3] cpuidle-haltpoll: vcpu hotplug support
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11126347
Return-Path: <SRS0=jCHW=W5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C30E14F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 10:43:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F0503217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  2 Sep 2019 10:43:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="YivH4ogz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730584AbfIBKnR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Sep 2019 06:43:17 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:43464 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730013AbfIBKnR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Sep 2019 06:43:17 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x82AdEn1163436;
        Mon, 2 Sep 2019 10:41:34 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=w+G+MVA2YN07SA3UzChr+LYUeDR77rQPujOEa86rr/M=;
 b=YivH4ogzTkrVZ4L/v7Zsi3AicDuo49zoVJeXpXOn2MMKZ7HZvvaH9OnkGas7dbNc7cyj
 zI2JDeB1COr6kzMc/ePUPo23okASg63RjKXv3uleXjgwuXaJqryOU6rFJlQJgptXS3I1
 CHam049rqgEB79plAMDFpvIB9N9/z3G2Nb6MxYDGScqYgi8hczcHBlPOOhd/PnXwkcvO
 sUU9woMbp+QCtGfftZajX7zo5kttShWsDEWAp4LpTdW2I2jtVZOhm7/KLOD1IU1e0YJE
 WTFeEGo9AgVxBbJp2V8HFfyiqsfbDEsI0r+SmQar68HvHAePbhi7QQg7wTygHlTtUIv8 ig==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 2us1d7816c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 02 Sep 2019 10:41:34 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x82AcAaB014454;
        Mon, 2 Sep 2019 10:41:34 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 2urww6ds8y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 02 Sep 2019 10:41:33 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x82AfTDZ020042;
        Mon, 2 Sep 2019 10:41:29 GMT
Received: from paddy.uk.oracle.com (/10.175.163.45)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 02 Sep 2019 03:41:27 -0700
From: Joao Martins <joao.m.martins@oracle.com>
To: kvm@vger.kernel.org
Cc: Joao Martins <joao.m.martins@oracle.com>,
 Marcelo Tosatti <mtosatti@redhat.com>, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 "Rafael J. Wysocki" <rjw@rjwysocki.net>,
 Daniel Lezcano <daniel.lezcano@linaro.org>, linux-pm@vger.kernel.org,
 Boris Ostrovsky <boris.ostrovsky@oracle.com>
Subject: [PATCH v3] cpuidle-haltpoll: vcpu hotplug support
Date: Mon,  2 Sep 2019 11:40:31 +0100
Message-Id: <20190902104031.9296-1-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9367
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=3
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1909020122
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9367
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=3 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1909020122
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When cpus != maxcpus cpuidle-haltpoll will fail to register all vcpus
past the online ones and thus fail to register the idle driver.
This is because cpuidle_add_sysfs() will return with -ENODEV as a
consequence from get_cpu_device() return no device for a non-existing
CPU.

Instead switch to cpuidle_register_driver() and manually register each
of the present cpus through cpuhp_setup_state() callbacks and future
ones that get onlined or offlined. This mimmics similar logic that
intel_idle does.

Fixes: fa86ee90eb11 ("add cpuidle-haltpoll driver")
Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Reviewed-by: Marcelo Tosatti <mtosatti@redhat.com>
---
v3:
* register the teardown callback for correct handling of hotunplug
and error cases. In case cpuhp_setup_state calls fails (e.g. in one of
the cpus that it invoked the callback) it will then call the teardown of
the previously enabled devices; so no need to handle that manually in
haltpoll_uninit().
* use the cpuhp_setup_state() returned dyn allocated state when it
succeeds. And use that state in haltpoll_unint() to call
cpuhp_remove_state() instead of looping online cpus manually. This
is because cpuhp_remove_state() invokes the teardown/offline callback.
* fix subsystem name to 'cpuidle' instead of 'idle' in cpuhp_setup_state()

v2:
* move cpus_read_unlock() after unregistering all cpuidle_devices;
(Marcello Tosatti)
* redundant usage of cpuidle_unregister() when only
cpuidle_unregister_driver() suffices; (Marcelo Tosatti)
* cpuhp_setup_state() returns a state (> 0) for CPUHP_AP_ONLINE_DYN
---
 arch/x86/include/asm/cpuidle_haltpoll.h |  4 +-
 arch/x86/kernel/kvm.c                   | 18 +++----
 drivers/cpuidle/cpuidle-haltpoll.c      | 68 +++++++++++++++++++++++--
 include/linux/cpuidle_haltpoll.h        |  4 +-
 4 files changed, 73 insertions(+), 21 deletions(-)

```
