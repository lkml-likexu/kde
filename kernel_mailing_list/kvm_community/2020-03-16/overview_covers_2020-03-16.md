

#### [PATCH 0/2] KVM: selftests: steal_time cleanups and timespec rework
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Mon Mar 16 11:01:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11440183
Return-Path: <SRS0=tnJv=5B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C20413B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 11:01:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 01DE020719
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 11:01:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="biZ+sRUp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730760AbgCPLBm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 07:01:42 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:41831 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730694AbgCPLBm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Mar 2020 07:01:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584356501;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=N1jC2/AWjvaBo55ZEMscSwgEbXB+R/Dg9FugHDbXi9g=;
        b=biZ+sRUpDPl+n5Qne85dgB6wHy0cFQg+Fcp7q6q6PW321Ia0uHqrno/hlf4CC4UHAsBK+7
        EIHCmQneoNb/qKy3l6Tb+ykN23ki8+PkzzbVi5YE/W2aePbqJvPqCDCuYS+/1PTeIBC/lA
        QZtSXPpOyEw4tJWAeicYVhuN9y9h/5A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-216-DsIelGcpMkSRR6--wvCuwA-1; Mon, 16 Mar 2020 07:01:39 -0400
X-MC-Unique: DsIelGcpMkSRR6--wvCuwA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D5BB2107B119
        for <kvm@vger.kernel.org>; Mon, 16 Mar 2020 11:01:38 +0000 (UTC)
Received: from kamzik.brq.redhat.com (ovpn-204-240.brq.redhat.com
 [10.40.204.240])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E59C95E240;
        Mon, 16 Mar 2020 11:01:37 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 0/2] KVM: selftests: steal_time cleanups and timespec rework
Date: Mon, 16 Mar 2020 12:01:34 +0100
Message-Id: <20200316110136.31326-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch is a couple changes to steal_time that came to mind
after posting. The second one reworks the timespec functions and
their use. It then applies them to the fixing of the stop condition
of steal_time:do_steal_time

Andrew Jones (2):
  fixup! KVM: selftests: Introduce steal-time test
  KVM: selftests: Rework timespec functions and usage

 .../selftests/kvm/demand_paging_test.c        | 37 +++++++---------
 .../testing/selftests/kvm/include/test_util.h |  3 +-
 tools/testing/selftests/kvm/lib/test_util.c   | 42 +++++++++++--------
 tools/testing/selftests/kvm/steal_time.c      | 39 ++++++++---------
 4 files changed, 60 insertions(+), 61 deletions(-)
```
#### [PATCH v3 00/19] Support disabling TCG on ARM (part 2)
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Mon Mar 16 16:06:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11440661
Return-Path: <SRS0=tnJv=5B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6A7613B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 16:13:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A43BA20674
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 16:13:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="SOJHqX1O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731923AbgCPQND (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 12:13:03 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:42076 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731505AbgCPQND (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Mar 2020 12:13:03 -0400
X-Greylist: delayed 372 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 16 Mar 2020 12:13:01 EDT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584375181;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=P5yP2gI3jZwVa/ROqUBqAiUPezN5j8lwPUWA/Pi42tY=;
        b=SOJHqX1OpTIwds4NuTinOwQkasmLOaVUm1Q2HuJ04+YF1bjV27gxqNI9np6mddxt/G7eUn
        Pvxt/t+/8BuY48AKAfa42PVtd1/BzVkektRmcpypYMSOof3qhtNlMG26D3bmzwsO17M/OQ
        XGugJ+FxXsdrWh3jF9eQ4Cicfh0Ty9s=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-198-OlHjdzvbNV6Tcz7aIiRruQ-1; Mon, 16 Mar 2020 12:06:38 -0400
X-MC-Unique: OlHjdzvbNV6Tcz7aIiRruQ-1
Received: by mail-wr1-f70.google.com with SMTP id t4so6313645wrv.9
        for <kvm@vger.kernel.org>; Mon, 16 Mar 2020 09:06:38 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=P5yP2gI3jZwVa/ROqUBqAiUPezN5j8lwPUWA/Pi42tY=;
        b=g/8Tow63oxbfeYofC29Aolgdu3fVMOY5jFVvrmYcnysMxkaVCwu/qCQVgtmzlupwEa
         rRBbf28ol7Euz4hBoMxHCBnERWh3xYlI7N/VHRUrQ1nJ2Lv1AqnjBiuCBFcPieXkNhGB
         vbiYWZuiDbyXO6XFjWoalMCxCXlDyMqPgnM88LR4iRVpJE028GSxLD6KKMUG7HBqaaQw
         wvQAxbWRy46hsMMdoAV4qMLhO1td+h9mNrLEDl2Er+UfZhJBnzZ09EhbD4BmLA8SnkLD
         O48KCpUNGH3bg0xBi2M3FPXGN/pue11WKLZwNE95Fes8Z6ylRZ0LXr1+kn5nU6iZ7Bmc
         q0yw==
X-Gm-Message-State: ANhLgQ0cMxD1/xuf909CCI5LpIEh9j0Xaqsjp2MjBCTbTWOlGuuUYiNf
        URn63U/wL59rwIX/T98JStQAOmZJ30DVyeNjR1BT7krpw8pvRGbPJcyv8/7to9RPktWqSEI6r2L
        8nS91CYKKq5V2
X-Received: by 2002:adf:a343:: with SMTP id d3mr105732wrb.50.1584374797652;
        Mon, 16 Mar 2020 09:06:37 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vt2iuZ7H3FhJLGjMjjY+SMihUpUN452/lUvxyCtpgGQsOh0snwxYqeNt3N03YZvD05ipB9yBA==
X-Received: by 2002:adf:a343:: with SMTP id d3mr105710wrb.50.1584374797395;
        Mon, 16 Mar 2020 09:06:37 -0700 (PDT)
Received: from localhost.localdomain (96.red-83-59-163.dynamicip.rima-tde.net.
 [83.59.163.96])
        by smtp.gmail.com with ESMTPSA id s7sm478457wri.61.2020.03.16.09.06.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 16 Mar 2020 09:06:36 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 kvm@vger.kernel.org, Thomas Huth <thuth@redhat.com>, qemu-arm@nongnu.org,
 Fam Zheng <fam@euphon.net>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>,
 Richard Henderson <richard.henderson@linaro.org>
Subject: [PATCH v3 00/19] Support disabling TCG on ARM (part 2)
Date: Mon, 16 Mar 2020 17:06:15 +0100
Message-Id: <20200316160634.3386-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cover from Samuel Ortiz from (part 1) [1]:

  This patchset allows for building and running ARM targets with TCG
  disabled. [...]

  The rationale behind this work comes from the NEMU project where we're
  trying to only support x86 and ARM 64-bit architectures, without
  including the TCG code base. We can only do so if we can build and run
  ARM binaries with TCG disabled.

v3 almost 18 months later:
- Rebased
- Addressed Thomas review comments
- Added Travis-CI job to keep building --disable-tcg on ARM

v2 [2]:
- Addressed review comments from Richard and Thomas from v1 [3]

Regards,

Phil.

[1]: https://lists.gnu.org/archive/html/qemu-devel/2018-11/msg02451.html
[2]: https://www.mail-archive.com/qemu-devel@nongnu.org/msg641796.html
[3]: https://lists.gnu.org/archive/html/qemu-devel/2019-08/msg05003.html

Based-on: <20200316120049.11225-1-philmd@redhat.com>
"accel: Allow targets to use Kconfig, disable semihosting by default"
https://lists.gnu.org/archive/html/qemu-devel/2020-03/msg04653.html

Philippe Mathieu-Daudé (15):
  target/arm: Rename KVM set_feature() as kvm_set_feature()
  target/arm: Restrict DC-CVAP instruction to TCG accel
  target/arm: Restric the Address Translate operations to TCG accel
  target/arm: Restrict Virtualization Host Extensions instructions to
    TCG
  target/arm: Move Makefile variable restricted to CONFIG_TCG
  target/arm: Add semihosting stub to allow building without TCG
  target/arm: Move ARM_V7M Kconfig from hw/ to target/
  target/arm: Restrict ARMv4 cpus to TCG accel
  target/arm: Restrict ARMv5 cpus to TCG accel
  target/arm: Restrict ARMv6 cpus to TCG accel
  target/arm: Restrict ARMv7 R-profile cpus to TCG accel
  target/arm: Restrict ARMv7 M-profile cpus to TCG accel
  hw/arm: Automatically select the 'virt' machine on KVM
  hw/arm: Do not build to 'virt' machine on Xen
  .travis.yml: Add a KVM-only Aarch64 job

Samuel Ortiz (1):
  target/arm: Do not build TCG objects when TCG is off

Thomas Huth (3):
  target/arm: Make set_feature() available for other files
  target/arm: Make cpu_register() available for other files
  target/arm: Make m_helper.c optional via CONFIG_ARM_V7M

 default-configs/aarch64-softmmu.mak |   1 -
 default-configs/arm-softmmu.mak     |  30 --
 target/arm/cpu-qom.h                |   9 +-
 target/arm/cpu.h                    |   7 +
 target/arm/internals.h              |  10 +
 target/arm/arm-semi-stub.c          |  13 +
 target/arm/cpu.c                    | 651 +---------------------------
 target/arm/cpu64.c                  |  19 +-
 target/arm/cpu_v4.c                 |  65 +++
 target/arm/cpu_v5.c                 | 266 ++++++++++++
 target/arm/cpu_v6.c                 | 171 ++++++++
 target/arm/cpu_v7m.c                | 207 +++++++++
 target/arm/cpu_v7r.c                |  83 ++++
 target/arm/helper.c                 |  54 +--
 target/arm/kvm32.c                  |  10 +-
 target/arm/kvm64.c                  |  16 +-
 target/arm/m_helper-stub.c          |  59 +++
 .travis.yml                         |  32 ++
 hw/arm/Kconfig                      |  17 +-
 target/Kconfig                      |   2 +-
 target/arm/Kconfig                  |  19 +
 target/arm/Makefile.objs            |  17 +-
 22 files changed, 1016 insertions(+), 742 deletions(-)
 create mode 100644 target/arm/arm-semi-stub.c
 create mode 100644 target/arm/cpu_v4.c
 create mode 100644 target/arm/cpu_v5.c
 create mode 100644 target/arm/cpu_v6.c
 create mode 100644 target/arm/cpu_v7m.c
 create mode 100644 target/arm/cpu_v7r.c
 create mode 100644 target/arm/m_helper-stub.c
 create mode 100644 target/arm/Kconfig
```
#### [PATCH v2 0/2] KVM: selftests: steal_time cleanups and timespec
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Mon Mar 16 17:37:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11441043
Return-Path: <SRS0=tnJv=5B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7873E14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 17:59:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4E23620674
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Mar 2020 17:59:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UCS0cKYG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732232AbgCPR7t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Mar 2020 13:59:49 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:34836 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730437AbgCPR7t (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Mar 2020 13:59:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584381588;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0YiQO4coq/kq6AWRYGg1EQj7mM3S8BzHCJuadCYG5Uw=;
        b=UCS0cKYGRkGak/RiBcTo1ZKvhCEBhPbwY3E6Xi6SiEh5MpM2N6zJOuvS0SGdqs7awnelBs
        kQAaUIqtOGcYZU8ET+LWMbq0l1idLTQsN2cjRcdAISzotD6ninMy4Ze/KBaOwcplHye8Mf
        fxxI7P/sxGzyzHITZMN0pyAtaaWP8Eg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-408-ysGXlS5BMFK639s8Fde17A-1; Mon, 16 Mar 2020 13:59:47 -0400
X-MC-Unique: ysGXlS5BMFK639s8Fde17A-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 697A4921923
        for <kvm@vger.kernel.org>; Mon, 16 Mar 2020 17:37:12 +0000 (UTC)
Received: from kamzik.brq.redhat.com (ovpn-204-240.brq.redhat.com
 [10.40.204.240])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5AC797E304;
        Mon, 16 Mar 2020 17:37:11 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH v2 0/2] KVM: selftests: steal_time cleanups and timespec
 rework
Date: Mon, 16 Mar 2020 18:37:01 +0100
Message-Id: <20200316173703.12785-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch is a couple changes to steal_time that came to mind
after posting. The second one reworks the timespec functions and
their use. It then applies them to the fixing of the stop condition
of steal_time:do_steal_time

v2:
 - Drank a cup of coffee and discovered division... Use division instead
   of loop in timespec_add_ns.

Andrew Jones (2):
  fixup! KVM: selftests: Introduce steal-time test
  KVM: selftests: Rework timespec functions and usage

 .../selftests/kvm/demand_paging_test.c        | 37 ++++++++----------
 .../testing/selftests/kvm/include/test_util.h |  3 +-
 tools/testing/selftests/kvm/lib/test_util.c   | 37 ++++++++----------
 tools/testing/selftests/kvm/steal_time.c      | 39 +++++++++----------
 4 files changed, 52 insertions(+), 64 deletions(-)
```
