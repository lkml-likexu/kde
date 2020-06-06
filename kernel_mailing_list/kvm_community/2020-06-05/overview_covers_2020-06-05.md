

#### [PATCH RESEND 0/5] vDPA:config interrupt support and IRQ improvements
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Fri Jun  5 10:27:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11589409
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D586F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 10:31:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C42DC2074B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 10:31:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726563AbgFEKa5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 06:30:57 -0400
Received: from mga18.intel.com ([134.134.136.126]:57119 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726077AbgFEKa4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 06:30:56 -0400
IronPort-SDR: 
 HgTTl5rFinaru+pbSwF02zgyHaVdHfYMXjjn49YOUmQ+dfDQECEPALgZn13V0PspPGIFP35E0c
 lC8/tccTpqaw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jun 2020 03:30:56 -0700
IronPort-SDR: 
 f0WJCG+GZdUy4Koqo1sSzDk+cHeA6vF5M5kG1b6BlzQ4AajHHlbMjNeO6wofs1ElSQw9XHE6dI
 /i9r6KU9wbRg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,476,1583222400";
   d="scan'208";a="305024833"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by fmsmga002.fm.intel.com with ESMTP; 05 Jun 2020 03:30:53 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH RESEND 0/5] vDPA:config interrupt support and IRQ improvements
Date: Fri,  5 Jun 2020 18:27:10 +0800
Message-Id: <1591352835-22441-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to introduce:
(1) config interrupt in vhost_vdpa and IFCVF.
(2) handle datapath and IRQ managent in the status handler,
so that it would comply to virtio spec, and more reliable

Most patches already got ACKed, excepted for 
ifcvf: ignore continuous setting same staus value

Please help review

Zhu Lingshan (5):
  ifcvf: move IRQ request/free to status change handlers
  ifcvf: ignore continuous setting same staus value
  vhost_vdpa: Support config interrupt in vhost_vdpa
  vhost: replace -1 with VHOST_FILE_UNBIND in iotcls
  ifcvf: implement config interrupt in IFCVF

 drivers/vdpa/ifcvf/ifcvf_base.c |   3 +
 drivers/vdpa/ifcvf/ifcvf_base.h |   4 ++
 drivers/vdpa/ifcvf/ifcvf_main.c | 146 +++++++++++++++++++++++++++-------------
 drivers/vhost/vdpa.c            |  47 +++++++++++++
 drivers/vhost/vhost.c           |   8 +--
 include/uapi/linux/vhost.h      |   4 ++
 6 files changed, 160 insertions(+), 52 deletions(-)
```
#### [PATCH 0/3 v2] kvm-unit-tests: nVMX: Test base and limit fields of
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Fri Jun  5 19:20:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11590433
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBC8D90
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:20:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2BCF206FA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 19:20:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="WMtHEHhI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727087AbgFETUk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 15:20:40 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:47224 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726963AbgFETUk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 15:20:40 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 055JIaDA192300;
        Fri, 5 Jun 2020 19:20:35 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=bMkflYSOYVoWdMH52y+bdI1S3snCBEUjXDeaQaP5oPc=;
 b=WMtHEHhIZomuuplk04ZvCEiQNiK7IwpNB4+4ItLuxtYuHyPVYdT08Uge9cRmiFIzRmnQ
 ES1tlvAX2Wk4ov/LuWcEeX/lBYAntEefAGCIYcn9kymTSKmW28Ue4xRRzoa2U70vXls6
 CTAkdozcFDEjInl+wmQ2sBQuHzwZ2ir4DPeHSUOzRaE0eWZfl+bBoiZmZ6EU/gEYenhr
 G1I2HEJx9djE3o7yFiVbaZw45ogsXCfSIWKwpkzkLilRvPr2jUrnCNHiCH9lXcH1X6iq
 kB12BiaqmGNqpN6ToDKZAyYu021gGv8DBWUUxNawwSsY3nY/fG7EwnM1DVlN8h7CD+jS 3w==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 31f9244d3q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 05 Jun 2020 19:20:35 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 055JIBYs012036;
        Fri, 5 Jun 2020 19:20:35 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 31f927mpr3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 05 Jun 2020 19:20:34 +0000
Received: from abhmp0009.oracle.com (abhmp0009.oracle.com [141.146.116.15])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 055JKXjV017164;
        Fri, 5 Jun 2020 19:20:33 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.231.182)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 05 Jun 2020 19:20:33 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 0/3 v2] kvm-unit-tests: nVMX: Test base and limit fields of
 guest GDTR and IDTR
Date: Fri,  5 Jun 2020 19:20:19 +0000
Message-Id: <1591384822-71784-1-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9643
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 phishscore=0
 mlxlogscore=695 bulkscore=0 suspectscore=13 adultscore=0 malwarescore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006050141
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9643
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1015
 impostorscore=0
 adultscore=0 priorityscore=1501 mlxlogscore=745 mlxscore=0 bulkscore=0
 lowpriorityscore=0 cotscore=-2147483648 phishscore=0 spamscore=0
 malwarescore=0 suspectscore=13 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006050141
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
        This only change is in patch# 1 where I have removed the '#ifdef __x86_64__' guard.


[PATCH 1/3 v2] KVM: kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and
[PATCH 2/3 v2] KVM: kvm-unit-tests: nVMX: Optimize test_guest_dr7() by
[PATCH 3/3 v2] KVM: kvm-unit-tests: nVMX: Test GUEST_LIMIT_GDTR and

 x86/vmx_tests.c | 50 ++++++++++++++++++++++++++++++++++----------------
 1 file changed, 34 insertions(+), 16 deletions(-)

Krish Sadhukhan (3):
      kvm-unit-tests: nVMX: Test GUEST_BASE_GDTR and GUEST_BASE_IDTR on vmentry 
      kvm-unit-tests: nVMX: Optimize test_guest_dr7() by factoring out the loops
      kvm-unit-tests: nVMX: Test GUEST_LIMIT_GDTR and GUEST_LIMIT_IDTR on vmentr
```
#### [PATCH v8 00/16] s390/vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Fri Jun  5 21:39:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11590655
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C248192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:42:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6CC9206DC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:42:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728654AbgFEVmk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 17:42:40 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:13200 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728786AbgFEVkT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Jun 2020 17:40:19 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 055LYjJw169334;
        Fri, 5 Jun 2020 17:40:12 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31fnwgqeaq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 05 Jun 2020 17:40:12 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 055LYjnP169429;
        Fri, 5 Jun 2020 17:40:12 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31fnwgqeaj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 05 Jun 2020 17:40:12 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 055LYdRM020860;
        Fri, 5 Jun 2020 21:40:11 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma01dal.us.ibm.com with ESMTP id 31bwg41kyn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 05 Jun 2020 21:40:11 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 055Le9Li39453072
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 5 Jun 2020 21:40:09 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 41C8AAC05B;
        Fri,  5 Jun 2020 21:40:09 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BD250AC05F;
        Fri,  5 Jun 2020 21:40:08 +0000 (GMT)
Received: from cpe-172-100-175-116.stny.res.rr.com.com (unknown
 [9.85.146.208])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri,  5 Jun 2020 21:40:08 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v8 00/16] s390/vfio-ap: dynamic configuration support
Date: Fri,  5 Jun 2020 17:39:48 -0400
Message-Id: <20200605214004.14270-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-05_07:2020-06-04,2020-06-05 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 lowpriorityscore=0 malwarescore=0 phishscore=0 mlxlogscore=999
 adultscore=0 clxscore=1015 spamscore=0 cotscore=-2147483648
 impostorscore=0 suspectscore=3 priorityscore=1501 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006050159
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note: Patch 1 - s390/ap: introduce new ap function ap_get_qdev() - is not
      a part of this series. It is a forthcoming patch that is a
      prerequisite to this series and is being provided so this series
      will compile.

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in a few 
deficiencies this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP 
   configuration becomes available to the guest when it is subsequently
   restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to
   either mask can result in AP queue devices being unbound from the
   vfio_ap device driver and bound to a zcrypt device driver even if a
   guest is using the queues, thus giving the host access to the guest's
   private crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   reference an AP queue device bound to the vfio_ap device driver. The
   AP architecture allows assignment of AP resources that are not
   available to the system, so this artificial restriction is not 
   compliant with the architecture.

4. The AP configuration profile can be dynamically changed for the linux
   host after a KVM guest is started. For example, a new domain can be
   dynamically added to the configuration profile via the SE or an HMC
   connected to a DPM enabled lpar. Likewise, AP adapters can be 
   dynamically configured (online state) and deconfigured (standby state)
   using the SE, an SCLP command or an HMC connected to a DPM enabled
   lpar. This can result in inadvertent sharing of AP queues between the
   guest and host.

5. A root user can manually unbind an AP queue device representing a 
   queue in use by a KVM guest via the vfio_ap device driver's sysfs 
   unbind attribute. In this case, the guest will be using a queue that
   is not bound to the driver which violates the device model.

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement
more of the AP architecture:

1. A root user will be prevented from making changes to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the ownership of an APQN
   changes from the vfio_ap device driver to a zcrypt driver when the
   APQN is assigned to a matrix mdev.

2. Allow a root user to hot plug/unplug AP adapters, domains and control
   domains using the matrix mdev's assign/unassign attributes.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if
   it results in assignment of an APQN that does not reference an AP
   queue device bound to the vfio_ap device driver, as long as the APQN
   is not reserved for use by the default zcrypt drivers (also known as
   over-provisioning of AP resources). Allowing over-provisioning of AP
   resources better models the architecture which does not preclude
   assigning AP resources that are not yet available in the system. Such
   APQNs, however, will not be assigned to the guest using the matrix
   mdev; only APQNs referencing AP queue devices bound to the vfio_ap
   device driver will actually get assigned to the guest.

5. Handle dynamic changes to the AP device model. 

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source.

2. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes 
reconfiguring a guest's AP matrix much less disruptive.

3. Rationale for allowing over-provisioning of AP resources:
----------------------------------------------------------- 
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will be given access to it. If an APQN
is dynamically unassigned from the underlying host system, it will 
automatically become unavailable to the guest.

Change log v6-v7:
----------------
* Added callbacks to AP bus:
  - on_config_changed: Notifies implementing drivers that
    the AP configuration has changed since last AP device scan.
  - on_scan_complete: Notifies implementing drivers that the device scan
    has completed.
  - implemented on_config_changed and on_scan_complete callbacks for
    vfio_ap device driver.
  - updated vfio_ap device driver's probe and remove callbacks to handle
    dynamic changes to the AP device model. 
* Added code to filter APQNs when assigning AP resources to a KVM guest's
  CRYCB

Change log v7-v8:
----------------
* Now logging a message when an attempt to reserve APQNs for the zcrypt
  drivers will result in taking a queue away from a KVM guest to provide
  the sysadmin a way to ascertain why the sysfs operation failed.

* Created locked and unlocked versions of the ap_parse_mask_str() function.

* Now using new interface provided by an AP bus patch -
  s390/ap: introduce new ap function ap_get_qdev() - to retrieve
  struct ap_queue representing an AP queue device. This patch is not a
  part of this series but is a prerequisite for this series. 

Change log v6-v7:
----------------

Change log v5-v6:
----------------
* Fixed a bug in ap_bus.c introduced with patch 2/7 of the v5 
  series. Harald Freudenberer pointed out that the mutex lock
  for ap_perms_mutex in the apmask_store and aqmask_store functions
  was not being freed. 

* Removed patch 6/7 which added logging to the vfio_ap driver
  to expedite acceptance of this series. The logging will be introduced
  with a separate patch series to allow more time to explore options
  such as DBF logging vs. tracepoints.

* Added 3 patches related to ensuring that APQNs that do not reference
  AP queue devices bound to the vfio_ap device driver are not assigned
  to the guest CRYCB:

  Patch 4: Filter CRYCB bits for unavailable queue devices
  Patch 5: sysfs attribute to display the guest CRYCB
  Patch 6: update guest CRYCB in vfio_ap probe and remove callbacks

* Added a patch (Patch 9) to version the vfio_ap module.

* Reshuffled patches to allow the in_use callback implementation to
  invoke the vfio_ap_mdev_verify_no_sharing() function introduced in
  patch 2. 

Change log v4-v5:
----------------
* Added a patch to provide kernel s390dbf debug logs for VFIO AP

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from 
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic 
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Harald Freudenberger (2):
  s390/ap: introduce new ap function ap_get_qdev()
  s390/zcrypt: Notify driver on config changed and scan complete
    callbacks

Tony Krowiak (14):
  s390/vfio-ap: use new AP bus interface to search for queue devices
  s390/vfio-ap: manage link between queue struct and matrix mdev
  s390/zcrypt: driver callback to indicate resource in use
  s390/vfio-ap: implement in-use callback for vfio_ap driver
  s390/vfio-ap: introduce shadow APCB
  s390/vfio-ap: sysfs attribute to display the guest's matrix
  s390/vfio-ap: filter matrix for unavailable queue devices
  s390/vfio_ap: add qlink from ap_matrix_mdev struct to vfio_ap_queue
    struct
  s390/vfio-ap: allow assignment of unavailable AP queues to mdev device
  s390/vfio-ap: allow configuration of matrix mdev in use by a KVM guest
  s390/vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390/vfio-ap: handle host AP config change notification
  s390/vfio-ap: handle AP bus scan completed notification
  s390/vfio-ap: handle probe/remove not due to host AP config changes

 drivers/s390/crypto/ap_bus.c          |  417 +++++++--
 drivers/s390/crypto/ap_bus.h          |   41 +-
 drivers/s390/crypto/ap_card.c         |   47 +-
 drivers/s390/crypto/ap_queue.c        |   10 +-
 drivers/s390/crypto/vfio_ap_drv.c     |   34 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 1165 ++++++++++++++++++++-----
 drivers/s390/crypto/vfio_ap_private.h |   23 +-
 7 files changed, 1339 insertions(+), 398 deletions(-)
```
#### [PATCH 00/21] KVM: Cleanup and unify kvm_mmu_memory_cache usage
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Jun  5 21:38:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11590725
Return-Path: <SRS0=rHMY=7S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B70C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:44:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4A275206DC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  5 Jun 2020 21:44:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728899AbgFEVoT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 5 Jun 2020 17:44:19 -0400
Received: from mga17.intel.com ([192.55.52.151]:49307 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728252AbgFEVjJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Jun 2020 17:39:09 -0400
IronPort-SDR: 
 2Or+nb5QSrbNGG7DCqPdG+mjxgBds6PccMYmRydoM6QdEq5r5A7AZAe5Xii6uPgDU2uKU0h4OU
 cCuZTAzRZPEQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jun 2020 14:39:07 -0700
IronPort-SDR: 
 3kU6BlJ3ZElEdj1AHWXLHsdk52pJvqNGjfnKdDIaTU1hErrl7iwvq5Lps986iLm32Az8kC2WKh
 ius/kdGV8mzw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,477,1583222400";
   d="scan'208";a="287860865"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga002.jf.intel.com with ESMTP; 05 Jun 2020 14:39:07 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Peter Feiner <pfeiner@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Ben Gardon <bgardon@google.com>,
        Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH 00/21] KVM: Cleanup and unify kvm_mmu_memory_cache usage
Date: Fri,  5 Jun 2020 14:38:32 -0700
Message-Id: <20200605213853.14959-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series resurrects Christoffer Dall's series[1] to provide a common
MMU memory cache implementation that can be shared by x86, arm64 and MIPS.

It also picks up a suggested change from Ben Gardon[2] to clear shadow
page tables during initial allocation so as to avoid clearing entire
pages while holding mmu_lock.

The front half of the patches do house cleaning on x86's memory cache
implementation in preparation for moving it to common code, along with a
fair bit of cleanup on the usage.  The middle chunk moves the patches to
common KVM, and the last two chunks convert arm64 and MIPS to the common
implementation.

Cleanup aside, the notable difference from Christoffer and Ben's proposed
patches is to make __GFP_ZERO optional, e.g. to allow x86 to skip zeroing
for its gfns array and to provide line of sight for my
cannot-yet-be-discussed-in-detail use case for non-zero initialized shadow
page tables[3].

Tested on x86 only, no testing whatsoever on arm64 or MIPS.

[1] https://lkml.kernel.org/r/20191105110357.8607-1-christoffer.dall@arm.com
[2] https://lkml.kernel.org/r/20190926231824.149014-4-bgardon@google.com
[3] https://lkml.kernel.org/r/20191127180731.GC16845@linux.intel.com

Sean Christopherson (21):
  KVM: x86/mmu: Track the associated kmem_cache in the MMU caches
  KVM: x86/mmu: Consolidate "page" variant of memory cache helpers
  KVM: x86/mmu: Use consistent "mc" name for kvm_mmu_memory_cache locals
  KVM: x86/mmu: Remove superfluous gotos from mmu_topup_memory_caches()
  KVM: x86/mmu: Try to avoid crashing KVM if a MMU memory cache is empty
  KVM: x86/mmu: Move fast_page_fault() call above
    mmu_topup_memory_caches()
  KVM: x86/mmu: Topup memory caches after walking GVA->GPA
  KVM: x86/mmu: Clean up the gorilla math in mmu_topup_memory_caches()
  KVM: x86/mmu: Separate the memory caches for shadow pages and gfn
    arrays
  KVM: x86/mmu: Make __GFP_ZERO a property of the memory cache
  KVM: x86/mmu: Zero allocate shadow pages (outside of mmu_lock)
  KVM: x86/mmu: Skip filling the gfn cache for guaranteed direct MMU
    topups
  KVM: x86/mmu: Prepend "kvm_" to memory cache helpers that will be
    global
  KVM: Move x86's version of struct kvm_mmu_memory_cache to common code
  KVM: Move x86's MMU memory cache helpers to common KVM code
  KVM: arm64: Drop @max param from mmu_topup_memory_cache()
  KVM: arm64: Use common code's approach for __GFP_ZERO with memory
    caches
  KVM: arm64: Use common KVM implementation of MMU memory caches
  KVM: MIPS: Drop @max param from mmu_topup_memory_cache()
  KVM: MIPS: Account pages used for GPA page tables
  KVM: MIPS: Use common KVM implementation of MMU memory caches

 arch/arm64/include/asm/kvm_host.h    |  11 ---
 arch/arm64/include/asm/kvm_types.h   |   8 ++
 arch/arm64/kvm/arm.c                 |   2 +
 arch/arm64/kvm/mmu.c                 |  54 +++--------
 arch/mips/include/asm/kvm_host.h     |  11 ---
 arch/mips/include/asm/kvm_types.h    |   7 ++
 arch/mips/kvm/mmu.c                  |  44 ++-------
 arch/powerpc/include/asm/kvm_types.h |   5 ++
 arch/s390/include/asm/kvm_types.h    |   5 ++
 arch/x86/include/asm/kvm_host.h      |  14 +--
 arch/x86/include/asm/kvm_types.h     |   7 ++
 arch/x86/kvm/mmu/mmu.c               | 129 +++++++++------------------
 arch/x86/kvm/mmu/paging_tmpl.h       |  10 +--
 include/linux/kvm_host.h             |   7 ++
 include/linux/kvm_types.h            |  19 ++++
 virt/kvm/kvm_main.c                  |  55 ++++++++++++
 16 files changed, 178 insertions(+), 210 deletions(-)
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/powerpc/include/asm/kvm_types.h
 create mode 100644 arch/s390/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h
```
