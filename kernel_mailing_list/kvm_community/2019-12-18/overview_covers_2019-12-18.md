

#### [PATCH kvm-unit-tests 0/2] svm: make preparation more flexible
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Wed Dec 18 17:33:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11301515
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05718138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 17:33:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D758B2072B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 17:33:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="i00TIWS7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727260AbfLRRdI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 12:33:08 -0500
Received: from mail-wm1-f44.google.com ([209.85.128.44]:55099 "EHLO
        mail-wm1-f44.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726960AbfLRRdI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 12:33:08 -0500
Received: by mail-wm1-f44.google.com with SMTP id b19so2705456wmj.4
        for <kvm@vger.kernel.org>; Wed, 18 Dec 2019 09:33:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=0KSQAOByRWNcFo6CmLFpjQla52nVgda6MjvtK71OjfQ=;
        b=i00TIWS7rVKXRnx5YSiXbdnnGV98R1qy3ySEMO4orhY0nAovV8Yql1oSxMx43zb2G/
         U0c9p58jW5/m+3PMROmWOsL/3cidlUpfempzLe9LJhLwR2pTnvJFqOnXrtta2eZj9J6i
         tK+1J5/MFwyQqmjgz43qCUZEkr6yahHfw73Eyj8FLGVYMJUyfHmFJ7I1NwdQCZdztWmH
         /8ZY7XdFdQIZq8TwvyjgScId78c8O7POOzhQ0EiqJGS7mYajmb5PJkd3AAX+786grXN9
         C12ZHwYqWAn+MK2TiHB0sJgm/dX5eZ6NrlMtZGB57HvsZjjWGabmTDlKIaqzNk/VDebx
         0ncQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=0KSQAOByRWNcFo6CmLFpjQla52nVgda6MjvtK71OjfQ=;
        b=LcpbvW4mESkHgyP5l5sUxJa4z+JNiu/3LIuWhTrV8js9C5THhfUTa3mFhoc2zQdc8c
         81olFOEI8C9BOAL9lEV8qf7zq0z/l57tJBP/ywigf17Ih6V4+zTmemhAOEYoHmCMZz+X
         e2MVqd5rmHIP0NrJnQ8Er6hyhKGRMnDlZfjnU6UwDha6H27jbLRraN6CFtQezxo/4Wwi
         lt2IV8fzLP+DguQduUvZkINPREVUISBmhgRr7aiJACXbCBvCP3H4yNieq9+MKADpx4aU
         mY/rfcWFFYQqPD9NP5ZRXI6uoQzFNbmJYZpz9CP9fOYhQUENr8Pe26HxcMXWokhfZqKw
         6OvA==
X-Gm-Message-State: APjAAAUkL+d58gDADj1fgm/F31c1sNrhaRCeeA+oFB3BHOmNPHUMWX3p
        zXU3fKeb3Z7Sb7ScxQEwronLyQSI
X-Google-Smtp-Source: 
 APXvYqzL0AzK3EDfnvD/oi1jeRWasRsBKrzwYeD5CLLUkYy9qmza4H1KUW9GlwROAMlQCG4XcSUfzg==
X-Received: by 2002:a05:600c:294d:: with SMTP id
 n13mr4355808wmd.130.1576690386161;
        Wed, 18 Dec 2019 09:33:06 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 u22sm3411362wru.30.2019.12.18.09.33.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 18 Dec 2019 09:33:05 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: cavery@redhat.com
Subject: [PATCH kvm-unit-tests 0/2] svm: make preparation more flexible
Date: Wed, 18 Dec 2019 18:33:01 +0100
Message-Id: <1576690383-16170-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the future we may want tests that inject events while GIF=0 (this is
nice to cover check_nested_events or lack thereof).  Adjust the SVM
test harness to make this easy and not ad hoc.

Paolo

Paolo Bonzini (2):
  svm: introduce prepare_gif_clear callback
  svm: replace set_host_if with prepare_gif_clear callback

 x86/svm.c | 132 +++++++++++++++++++++++++++++++++++++++-----------------------
 1 file changed, 84 insertions(+), 48 deletions(-)
```
#### [PATCH net-next v3 00/11] VSOCK: add vsock_test test suite
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Wed Dec 18 18:06:57 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11301573
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B9D28139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 18:07:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 98A95218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 18:07:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hE6eWyud"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727490AbfLRSH3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 13:07:29 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:60860 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727437AbfLRSH2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 13:07:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576692446;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=nmdGUwTvoHp9zBzsfUh31MNBzW9ZhcHvi1/dZfx3TSc=;
        b=hE6eWyud09yIZAHi4k6KGVy7oUMtKDydHL1aFOERgg7xlCJxUchVtymjBwzJVO4+nFyD57
        m8+UBKdGaaI/h1pXT/U3OjKHk2hiLtlxgSg1piSkBg+gc1YbvN1w8AGBx7qGEdPpy1Gm/X
        +kFYbVLsZviXXGCGX+yERL5dRkIawhI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-50-bjYQnByeNymkKKOVYrH73A-1; Wed, 18 Dec 2019 13:07:17 -0500
X-MC-Unique: bjYQnByeNymkKKOVYrH73A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1626E1088381;
        Wed, 18 Dec 2019 18:07:16 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-218.ams2.redhat.com
 [10.36.117.218])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1592E5D9E2;
        Wed, 18 Dec 2019 18:07:08 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: davem@davemloft.net
Cc: Jorgen Hansen <jhansen@vmware.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Dexuan Cui <decui@microsoft.com>, netdev@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Stefano Garzarella <sgarzare@redhat.com>
Subject: [PATCH net-next v3 00/11] VSOCK: add vsock_test test suite
Date: Wed, 18 Dec 2019 19:06:57 +0100
Message-Id: <20191218180708.120337-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vsock_diag.ko module already has a test suite but the core AF_VSOCK
functionality has no tests. This patch series adds several test cases that
exercise AF_VSOCK SOCK_STREAM socket semantics (send/recv, connect/accept,
half-closed connections, simultaneous connections).

The v1 of this series was originally sent by Stefan.

v3:
- Patch 6:
  * check the byte received in the recv_byte()
  * use send(2)/recv(2) instead of write(2)/read(2) to test also flags
    (e.g. MSG_PEEK)
- Patch 8:
  * removed unnecessary control_expectln("CLOSED") [Stefan].
- removed patches 9,10,11 added in the v2
- new Patch 9 add parameters to list and skip tests (e.g. useful for vmci
  that doesn't support half-closed socket in the host)
- new Patch 10 prints a list of options in the help
- new Patch 11 tests MSG_PEEK flags of recv(2)

v2: https://patchwork.ozlabs.org/cover/1140538/
v1: https://patchwork.ozlabs.org/cover/847998/

Stefan Hajnoczi (7):
  VSOCK: fix header include in vsock_diag_test
  VSOCK: add SPDX identifiers to vsock tests
  VSOCK: extract utility functions from vsock_diag_test.c
  VSOCK: extract connect/accept functions from vsock_diag_test.c
  VSOCK: add full barrier between test cases
  VSOCK: add send_byte()/recv_byte() test utilities
  VSOCK: add AF_VSOCK test cases

Stefano Garzarella (4):
  vsock_test: wait for the remote to close the connection
  testing/vsock: add parameters to list and skip tests
  testing/vsock: print list of options and description
  vsock_test: add SOCK_STREAM MSG_PEEK test

 tools/testing/vsock/.gitignore        |   1 +
 tools/testing/vsock/Makefile          |   9 +-
 tools/testing/vsock/README            |   3 +-
 tools/testing/vsock/control.c         |  15 +-
 tools/testing/vsock/control.h         |   2 +
 tools/testing/vsock/timeout.h         |   1 +
 tools/testing/vsock/util.c            | 376 +++++++++++++++++++++++++
 tools/testing/vsock/util.h            |  49 ++++
 tools/testing/vsock/vsock_diag_test.c | 202 ++++----------
 tools/testing/vsock/vsock_test.c      | 379 ++++++++++++++++++++++++++
 10 files changed, 883 insertions(+), 154 deletions(-)
 create mode 100644 tools/testing/vsock/util.c
 create mode 100644 tools/testing/vsock/util.h
 create mode 100644 tools/testing/vsock/vsock_test.c
```
#### [PATCH v1 0/2] MMIO mask fix for AMD memory encryption support
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Wed Dec 18 19:45:45 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11301815
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBF5E14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 19:46:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9A6D7227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 19:46:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="sL1fbY+j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727393AbfLRTqC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 14:46:02 -0500
Received: from mail-dm6nam11on2076.outbound.protection.outlook.com
 ([40.107.223.76]:1696
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726698AbfLRTqC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 14:46:02 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=FaKPSLHHdOEjgF92ZsOF/iejUXz8fudf8NbtloxDDbz2RoLp1HP4qiWoE4OnH1/aGXs3wWH1E9ZdV3S4mIRCzC3akNj5YHGEIdn+y3gYJ2sG12ixs4eWR2XAGfOi8opynr/xxYE6/RLFmTnmFYuyBNDeP6FYblmrW+2a+6scI5WFQEEhtklam6A73xBVUPFe5eAU4nGnMma16gNIxaolz3Z1aIOqu2KtCrZcZ8UFwshe9f8EumtfeGZgerjYRC5A2dLz3Q9zLRW0eE2J6BXWkE06daepJMn8uzRI+YIZrB7a3nIJjKmcXK9xv7SFRT8IT6y774rYp2y9v2zclQXkhw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=DS+wd211c5GVgPTI+LzvYI11OAw8vaK7Oez/K1s08lE=;
 b=jPz+T1zGgSxoyGM4QFzisFI9x137SMldqaCZc8h+O5Fu3TnV8sLj5m/PvwH9XRcpLqMDB6X5sbP5dFP/F8bNDjAhDvthIcn4phU3GdsSl28kwosKYTgVZYbrO0gyeejKle3KjnSrNTZ5jsrVWZp2bHnbYyvfeo6Y8STpdCAUTzeA8QWmOtFMrVtnTuUp+dDqG0Bzs0gXMEMHJcRPs8UhHD3hYBUVZMbzA/v0OUsapPy8iUUasnTHUXBs52BxWGNKbcdpoSnzTY/+tB1H0mRsPqf/EDxFQTw2zK/5NLeXW3pOH2D0bAKD6jBftlzkN8BbVDuRfCIuqIVXi5z3/J9+tA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=DS+wd211c5GVgPTI+LzvYI11OAw8vaK7Oez/K1s08lE=;
 b=sL1fbY+jxRVinSN84mkWd62KNRD5zPkyECzGIjipHGRXuQfTOsuvzToKbLSqaPGEIa+Ke0PSGDFzrXhDzGXEArMYbyYhFX/y/yz9ZnthhdihMLT1JnmFjKBp8SEePYD9UdqdT0qAdX/lPmaKODAlQvm+O1ShcKmkKac/tohbQe4=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (20.179.71.154) by
 DM6PR12MB2876.namprd12.prod.outlook.com (20.179.71.85) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2559.14; Wed, 18 Dec 2019 19:46:00 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::a0cd:463:f444:c270%7]) with mapi id 15.20.2538.019; Wed, 18 Dec 2019
 19:45:59 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v1 0/2] MMIO mask fix for AMD memory encryption support
Date: Wed, 18 Dec 2019 13:45:45 -0600
Message-Id: <cover.1576698347.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.17.1
X-ClientProxiedBy: DM6PR21CA0007.namprd21.prod.outlook.com
 (2603:10b6:5:174::17) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:15e::26)
MIME-Version: 1.0
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: dbc974ea-6371-42d4-e631-08d783f2e80d
X-MS-TrafficTypeDiagnostic: DM6PR12MB2876:|DM6PR12MB2876:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB287694F5BE2052A70D22CB00EC530@DM6PR12MB2876.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:203;
X-Forefront-PRVS: 0255DF69B9
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(136003)(376002)(346002)(39860400002)(366004)(189003)(199004)(478600001)(5660300002)(81156014)(66946007)(81166006)(6486002)(6512007)(186003)(52116002)(54906003)(36756003)(86362001)(6666004)(4326008)(8676002)(66476007)(8936002)(4744005)(66556008)(2616005)(966005)(6506007)(2906002)(26005)(316002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB2876;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 m38ao21HFNkExqLhnmzcqELXjFMk3YYT+u1jZ4Bmyqc/5woQ/wD7KO2747fBlMeWZPYiqAqr+u8MpETNgaXA4aOtfFKBPL8V2qfPsoy1ihvg5BX8ymJnHMVWB8R7o+5lZXmZIZvwRASdLt6Dbf/RF6ldMMAO1yuFC568NHviT2mkXRGfihS8tBwKVc5OKF5fMsT5raYfjbNs2QbZFUy1xPIy/WkF2My+GuNzJB7gW1ZIZ17O5rKMD5DgXWfXwrs6/F0D3Jdx2wsS/fBbtFvjGRW/9zDVzdeFFaFLNtjixx1G/G5WnXZl37CTQlheZMcL04pkGmscO/1WS0yepeM99hJepdhsh8AMhvZGENPIwsZ5pO//NJm4TAx1E/VCOUyWOXxDfATt3FxDN0Onp/11TVIZAwy9hY/wru23FsH1FCWBRTCn9mg89hq8cGwJom4ljzWCacccNhdmKSiPEqnOfi7/1Np1pnIi957Q92CpmkM=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 dbc974ea-6371-42d4-e631-08d783f2e80d
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 18 Dec 2019 19:45:59.7392
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 nke1CMjiGZRQPYgxxaexU2yOwN0qjWBJgSPIBGf/FQrv9rqxrSjcbIW7dkoaaI2SnobPPRXCPPeoHc5W+SIkOg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2876
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series ensures that a valid MMIO SPTE mask can be generated
under SVM when memory encryption is enabled.

The patchset includes:
- Add an optional callback to return a reserved bit(s) mask
- Implement the callback in SVM
---

Patches based on https://git.kernel.org/pub/scm/virt/kvm/kvm.git next
commit:
  7d73710d9ca2 ("kvm: vmx: Stop wasting a page for guest_msrs")

Tom Lendacky (2):
  KVM: x86/mmu: Allow for overriding MMIO SPTE mask
  KVM: SVM: Implement reserved bit callback to set MMIO SPTE mask

 arch/x86/include/asm/kvm_host.h |  4 ++-
 arch/x86/kvm/mmu/mmu.c          | 54 +++++++++++++++++++++------------
 arch/x86/kvm/svm.c              | 42 +++++++++++++++++++++++++
 arch/x86/kvm/x86.c              |  2 +-
 4 files changed, 80 insertions(+), 22 deletions(-)
```
#### [PATCH v2 00/45]  KVM: Refactor vCPU creation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Dec 18 21:54:45 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11302251
Return-Path: <SRS0=UyFf=2I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A3DD114B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 22:00:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81CEA227BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Dec 2019 22:00:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726633AbfLRVze (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Dec 2019 16:55:34 -0500
Received: from mga02.intel.com ([134.134.136.20]:54823 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726387AbfLRVzd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Dec 2019 16:55:33 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Dec 2019 13:55:32 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,330,1571727600";
   d="scan'208";a="222107997"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 18 Dec 2019 13:55:31 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Marc Zyngier <maz@kernel.org>, James Hogan <jhogan@kernel.org>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Greg Kurz <groug@kaod.org>
Subject: [PATCH v2 00/45]  KVM: Refactor vCPU creation
Date: Wed, 18 Dec 2019 13:54:45 -0800
Message-Id: <20191218215530.2280-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The end goal of this series is to strip down the interface between common
KVM code and arch specific code so that there is precisely one arch hook
for creating a vCPU and one hook for destroying a vCPU.  In addition to
cleaning up the code base, simplifying the interface gives architectures
more freedom to organize their vCPU creation code.  Details below.

v2:
  - Rebase to commit e41a90be9659 ("KVM: x86/mmu: WARN if root_hpa is
    invalid when handling a page fault").  A few minor x86 (VMX) conflicts,
    and one straightforward arm conflict with commit 8564d6372a7d ("KVM:
    arm64: Support stolen time reporting via shared structure") in patch
    "KVM: ARM: Move all vcpu init code into kvm_arch_vcpu_create()".
  - Collect Reviews and Acks [Christoffer, Greg].
  - Fix a warning in "KVM: arm64: Free sve_state via arm specific hook"
    by using a "void" return type [Christoffer].
  - Fix a bug in "KVM: PPC: Move kvm_vcpu_init() invocation to common code"
    where the call in kvmppc_core_vcpu_create_e500mc() was inadvertantly
    left behind.


KVM's vCPU creation code is comically messy.  kvm_vm_ioctl_create_vcpu()
calls three separate arch hooks: init(), create() and setup().  The init()
call is especially nasty as it's hidden away in a common KVM function,
kvm_init_vcpu(), that for all intents and purposes must be immediately
invoked after the vcpu object is allocated.

Not to be outdone, vCPU destruction also has three arch hooks: uninit(),
destroy() and free(), the latter of which isn't actually invoked by common
KVM code, but the hook declaration still exists because architectures are
relying on its forward declaration.

Eliminating the extra arch hooks is relatively straightforward, just
tedious.  For the most part, there is no fundamental constraint that
necessitated the proliferation of arch hooks, rather they crept in over
time, usually when x86-centric code was moved out of generic KVM and into
x86 code.

E.g. kvm_arch_vcpu_setup() was added to allow x86 to do vcpu_load(), which
can only be done after preempt_notifier initialization, but adding setup()
overlooked the fact that the preempt_notifier was only initialized after
kvm_arch_vcpu_create() because preemption support was added when x86's MMU
setup (the vcpu_load() user) was called from common KVM code.

For all intents and purposes, there is no true functional change in this
series.  The order of some allocations will change, and a few memory leaks
are fixed, but the actual functionality of a guest should be unaffected.

Patches 01-03 are bug fixes in error handling paths that were found by
inspection when refactoring the associated code.

Patches 04-43 refactor each arch implementation so that the unwanted arch
hooks can be dropped without a functional change, e.g. move code out of
kvm_arch_vcpu_setup() so that all implementations are empty, then drop the
functions and caller.

Patches 44-45 are minor clean up to eliminate kvm_vcpu_uninit().

The net result is to go from this:

        vcpu = kvm_arch_vcpu_create(kvm, id);
               |
               |-> kvm_vcpu_init()
                   |
                   |-> kvm_arch_vcpu_init()

        if (IS_ERR(vcpu)) {
                r = PTR_ERR(vcpu);
                goto vcpu_decrement;
        }

        preempt_notifier_init(&vcpu->preempt_notifier, &kvm_preempt_ops);

        r = kvm_arch_vcpu_setup(vcpu);
        if (r)
                goto vcpu_destroy;


Sean Christopherson (45):
  KVM: PPC: Book3S HV: Uninit vCPU if vcore creation fails
  KVM: PPC: Book3S PR: Free shared page if mmu initialization fails
  KVM: x86: Free wbinvd_dirty_mask if vCPU creation fails
  KVM: VMX: Allocate VPID after initializing VCPU
  KVM: VMX: Use direct vcpu pointer during vCPU create/free
  KVM: SVM: Use direct vcpu pointer during vCPU create/free
  KVM: x86: Allocate vcpu struct in common x86 code
  KVM: x86: Move FPU allocation to common x86 code
  KVM: x86: Move allocation of pio_data page down a few lines
  KVM: x86: Move kvm_vcpu_init() invocation to common code
  KVM: PPC: e500mc: Add build-time assert that vcpu is at offset 0
  KVM: PPC: Allocate vcpu struct in common PPC code
  KVM: PPC: Book3S PR: Allocate book3s and shadow vcpu after common init
  KVM: PPC: e500mc: Move reset of oldpir below call to kvm_vcpu_init()
  KVM: PPC: Move kvm_vcpu_init() invocation to common code
  KVM: MIPS: Use kvm_vcpu_cache to allocate vCPUs
  KVM: MIPS: Drop kvm_arch_vcpu_free()
  KVM: PPC: Drop kvm_arch_vcpu_free()
  KVM: arm: Drop kvm_arch_vcpu_free()
  KVM: x86: Remove spurious kvm_mmu_unload() from vcpu destruction path
  KVM: x86: Remove spurious clearing of async #PF MSR
  KVM: x86: Drop kvm_arch_vcpu_free()
  KVM: Remove kvm_arch_vcpu_free() declaration
  KVM: Add kvm_arch_vcpu_precreate() to handle pre-allocation issues
  KVM: s390: Move guts of kvm_arch_vcpu_init() into
    kvm_arch_vcpu_create()
  KVM: s390: Invoke kvm_vcpu_init() before allocating sie_page
  KVM: MIPS: Invoke kvm_vcpu_uninit() immediately prior to freeing vcpu
  KVM: x86: Invoke kvm_vcpu_uninit() immediately prior to freeing vcpu
  KVM: Introduce kvm_vcpu_destroy()
  KVM: Move vcpu alloc and init invocation to common code
  KVM: Unexport kvm_vcpu_cache and kvm_vcpu_{un}init()
  KVM: Move initialization of preempt notifier to kvm_vcpu_init()
  KVM: x86: Move guts of kvm_arch_vcpu_setup() into
    kvm_arch_vcpu_create()
  KVM: MIPS: Move .vcpu_setup() call to kvm_arch_vcpu_create()
  KVM: s390: Manually invoke vcpu setup during kvm_arch_vcpu_create()
  KVM: PPC: BookE: Setup vcpu during kvmppc_core_vcpu_create()
  KVM: Drop kvm_arch_vcpu_setup()
  KVM: x86: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: MIPS: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: ARM: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: PPC: Move all vcpu init code into kvm_arch_vcpu_create()
  KVM: arm64: Free sve_state via arm specific hook
  KVM: Drop kvm_arch_vcpu_init() and kvm_arch_vcpu_uninit()
  KVM: Move putting of vcpu->pid to kvm_vcpu_destroy()
  KVM: Move vcpu->run page allocation out of kvm_vcpu_init()

 arch/arm/include/asm/kvm_host.h    |   2 +-
 arch/arm/kvm/guest.c               |   5 -
 arch/arm64/include/asm/kvm_host.h  |   2 +-
 arch/arm64/kvm/guest.c             |   5 -
 arch/arm64/kvm/reset.c             |   2 +-
 arch/mips/kvm/mips.c               |  84 ++++-------
 arch/powerpc/include/asm/kvm_ppc.h |   6 +-
 arch/powerpc/kvm/book3s.c          |   9 +-
 arch/powerpc/kvm/book3s_hv.c       |  27 +---
 arch/powerpc/kvm/book3s_pr.c       |  33 ++---
 arch/powerpc/kvm/booke.c           |  65 ++++----
 arch/powerpc/kvm/e500.c            |  34 +----
 arch/powerpc/kvm/e500mc.c          |  28 +---
 arch/powerpc/kvm/powerpc.c         |  70 ++++-----
 arch/s390/include/asm/kvm_host.h   |   1 -
 arch/s390/kvm/kvm-s390.c           | 110 +++++++-------
 arch/x86/include/asm/kvm_host.h    |   2 +-
 arch/x86/kvm/svm.c                 |  52 +------
 arch/x86/kvm/vmx/vmx.c             |  72 +++------
 arch/x86/kvm/x86.c                 | 230 ++++++++++++++---------------
 include/linux/kvm_host.h           |  13 +-
 virt/kvm/arm/arm.c                 |  80 ++++------
 virt/kvm/kvm_main.c                |  71 +++++----
 23 files changed, 385 insertions(+), 618 deletions(-)
```
