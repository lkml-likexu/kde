

#### [PATCH RFC 00/13] vhost: format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Tue Jun  2 13:05:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11583807
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90EED13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 13:08:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 72D6B206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 13:08:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Xy2qJhbj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727921AbgFBNGF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 09:06:05 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:30093 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726839AbgFBNGB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Jun 2020 09:06:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591103159;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=vdmj+Tg8SGx2NrYVAizct++/zxOMWuxvcR8U68lSB2Q=;
        b=Xy2qJhbjXoyS70Z86Z5bNfgNPwUttpmJ6dVZ8IF+MteBfqU2aQFQQ0CmT3r5lESWZVB9kS
        ckU6rnubx4qZkypXiWORAHNmc6sJAsrW5iE2s9x2NfVAX6EoVFSmK/zE2DaEGtlwxxUEbB
        wA5CkJO02FJwjJ/AoS+nSmyK5ezmd80=
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-286-hYdAybLvOyOb1FVWHJD7YA-1; Tue, 02 Jun 2020 09:05:58 -0400
X-MC-Unique: hYdAybLvOyOb1FVWHJD7YA-1
Received: by mail-wr1-f69.google.com with SMTP id w4so1378873wrl.13
        for <kvm@vger.kernel.org>; Tue, 02 Jun 2020 06:05:57 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=vdmj+Tg8SGx2NrYVAizct++/zxOMWuxvcR8U68lSB2Q=;
        b=rPqtLYLC4doIL0BCSCnrRp/KRqdmo4QG3K4Ms7QmLLNfCFa+b5/XRuWvtgCkKsTstV
         WessR7Eup++tv6GNST8PjJQ95Lyy6RRC6NyfofoOzXgikN9prQSEOgHcEoC7hSd1Ie5p
         fdLUPKWz0XrpGU+qhx29qqTplNkGnIscK2O/DLYNuwO91O5kyFBXw4unuMVEmXlS1/Ub
         7Vz/PQc/TrHWlzq9EWzxibh4xRY6r4Tw0BSkvyhAkjKo9LGkPALqeNgxtkmGPaAQkszj
         JvmuZNDLsHlc5iYHUKAq4klRx9IbqQYTyNokzqEfV4PRICrdTVgdVZeEYE8dd3bugkcQ
         1Idg==
X-Gm-Message-State: AOAM533zUGG83PQWKMf0enCVWPMIEhv9Jyc/KW2rxq9YWTBb2CCgFwO1
        x6Ig/Sabtr056EcrTN3ZUQpv7QeV5YKuc19zQR+9E4b+KpWA7xu3VELsbRq0+rNT4w+fWhsLcWU
        cx9xKptxOgFZj
X-Received: by 2002:a1c:e355:: with SMTP id a82mr3952749wmh.1.1591103156750;
        Tue, 02 Jun 2020 06:05:56 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzxhvL+9CoWDlbet28l8cBoDZ1y4Jq12uY4hkhtEZgSR8vXHFkGEgf8rds3ZCLy2cNng3Lahg==
X-Received: by 2002:a1c:e355:: with SMTP id a82mr3952727wmh.1.1591103156470;
        Tue, 02 Jun 2020 06:05:56 -0700 (PDT)
Received: from redhat.com (bzq-109-64-41-91.red.bezeqint.net. [109.64.41.91])
        by smtp.gmail.com with ESMTPSA id 5sm3408485wmz.16.2020.06.02.06.05.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 02 Jun 2020 06:05:55 -0700 (PDT)
Date: Tue, 2 Jun 2020 09:05:54 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Eugenio =?utf-8?b?UMOpcmV6?= <eperezma@redhat.com>,
 Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
 virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH RFC 00/13] vhost: format independence
Message-ID: <20200602130543.578420-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We let the specifics of the ring format seep through to vhost API
callers - mostly because there was only one format so it was
hard to imagine what an independent API would look like.
Now that there's an alternative in form of the packed ring,
it's easier to see the issues, and fixing them is perhaps
the cleanest way to add support for more formats.

This patchset does this by indtroducing two new structures: vhost_buf to
represent a buffer and vhost_desc to represent a descriptor.
Descriptors aren't normally of interest to devices but do occationally
get exposed e.g. for logging.

Perhaps surprisingly, the higher level API actually makes things a bit
easier for callers, as well as allows more freedom for the vhost core.
The end result is basically unchanged performance (based on preliminary
testing) even though we are forced to go through a format conversion.

The conversion also exposed (more) bugs in vhost scsi - which isn't
really surprising, that driver needs a lot more love than it's getting.

Very lightly tested. Would appreciate feedback and testing.

Michael S. Tsirkin (13):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched version by default
  vhost: batching fetches
  vhost: cleanup fetch_buf return code handling
  vhost/net: pass net specific struct pointer
  vhost: reorder functions
  vhost: format-independent API for used buffers
  vhost/net: convert to new API: heads->bufs
  vhost/net: avoid iov length math
  vhost/test: convert to the buf API
  vhost/scsi: switch to buf APIs
  vhost/vsock: switch to the buf API
  vhost: drop head based APIs

 drivers/vhost/net.c   | 173 +++++++++----------
 drivers/vhost/scsi.c  |  73 ++++----
 drivers/vhost/test.c  |  22 +--
 drivers/vhost/vhost.c | 375 +++++++++++++++++++++++++++---------------
 drivers/vhost/vhost.h |  46 ++++--
 drivers/vhost/vsock.c |  30 ++--
 6 files changed, 436 insertions(+), 283 deletions(-)
```
#### [PATCH 0/3] avoid unnecessary memslot rmap walks
##### From: Anthony Yznaga <anthony.yznaga@oracle.com>

```c
From patchwork Tue Jun  2 20:07:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anthony Yznaga <anthony.yznaga@oracle.com>
X-Patchwork-Id: 11584309
Return-Path: <SRS0=c+BJ=7P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8EB3890
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 20:10:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 772B220872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  2 Jun 2020 20:10:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="z+tGXNWX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728313AbgFBUKs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 2 Jun 2020 16:10:48 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:53716 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728101AbgFBUKr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Jun 2020 16:10:47 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 052JvxMj163024;
        Tue, 2 Jun 2020 20:09:41 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=Zy+9hIUOD1wHoEjv0iqcOdN6XDgnng/gMIII196nKXk=;
 b=z+tGXNWXcpe4kITTBT32god173s9pokQEK6VzOFsdQ3siX5keWyR1QMHN2W70Ff8C+B+
 rxDToZRd+1zqTyC8u7HAggP6i0MWWS1eFES8BEs89ChlGn/sNu3YsWQNVQEBTjR3B12M
 42Cd8MmRWKocBTsEMS+W6DVOgSBuLlazO9u2LU9tXUA6uFuUodnU44Z/MNnxnPJJG7IC
 F8Nc/DsSHdVA7XEEGea7sxqM8frdxX6LX63nW5EX5tCDlwm6Sv3WFfVwc/8E5sJevIzi
 lV7fVZAsi9s3tlf7LNo/knOZz3+7H2bV0+pbbyAUJ6+zgfC+Lb9XkwWxVW5OOkteWklk jw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 31bewqwyhp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 02 Jun 2020 20:09:41 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 052JxIK9135342;
        Tue, 2 Jun 2020 20:07:41 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3030.oracle.com with ESMTP id 31c1dxtrmr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 02 Jun 2020 20:07:41 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 052K7b5o013919;
        Tue, 2 Jun 2020 20:07:37 GMT
Received: from ayz-linux.us.oracle.com (/10.154.185.88)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 02 Jun 2020 13:07:36 -0700
From: Anthony Yznaga <anthony.yznaga@oracle.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        steven.sistare@oracle.com, anthony.yznaga@oracle.com
Subject: [PATCH 0/3] avoid unnecessary memslot rmap walks
Date: Tue,  2 Jun 2020 13:07:27 -0700
Message-Id: <1591128450-11977-1-git-send-email-anthony.yznaga@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9640
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 mlxlogscore=999
 spamscore=0 bulkscore=0 adultscore=0 suspectscore=0 mlxscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2006020146
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9640
 signatures=668686
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 bulkscore=0
 phishscore=0 suspectscore=0 impostorscore=0 cotscore=-2147483648
 lowpriorityscore=0 mlxscore=0 adultscore=0 spamscore=0 mlxlogscore=999
 malwarescore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006020146
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While investigating optimizing qemu start time for large memory guests
I found that kvm_mmu_slot_apply_flags() is walking rmaps to update
existing sptes when creating or moving a slot but that there won't be
any existing sptes to update and any sptes inserted once the new memslot
is visible won't need updating.  I can't find any reason for this not to
be the case, but I've taken a more cautious approach to fixing this by
dividing things into three patches.

Anthony Yznaga (3):
  KVM: x86: remove unnecessary rmap walk of read-only memslots
  KVM: x86: avoid unnecessary rmap walks when creating/moving slots
  KVM: x86: minor code refactor and comments fixup around dirty logging

 arch/x86/kvm/x86.c | 106 +++++++++++++++++++++++++----------------------------
 1 file changed, 49 insertions(+), 57 deletions(-)
```
