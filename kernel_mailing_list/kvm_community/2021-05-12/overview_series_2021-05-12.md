#### [PATCH v2 kvm-unit-tests 1/2] libcflat: clean up and complete long division routines
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12253335
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3178AC433ED
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 10:54:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DFF45613F9
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 10:54:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230289AbhELKzy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 06:55:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42004 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230211AbhELKzw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 06:55:52 -0400
Received: from mail-ej1-x635.google.com (mail-ej1-x635.google.com
 [IPv6:2a00:1450:4864:20::635])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4216EC06175F
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 03:54:44 -0700 (PDT)
Received: by mail-ej1-x635.google.com with SMTP id c22so6197893ejd.12
        for <kvm@vger.kernel.org>; Wed, 12 May 2021 03:54:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=XWgAsOmnprNK2skeWGppDbTh40fKVhmJp00QypGoM2k=;
        b=MraJAz0HI7UmqDdHOLpC69mGNLqWbEVwA0L7nKwLIS/+vXQlFGpS2+92ERofya2IO3
         32ygsxDvJRJ+Dorery3U1PUb/sNOAZIqqVSzL4j/zpGgYH4MvufElz0geWAgJ/tvmz/V
         w9ePMTRtH//TRbZ7p+mW+qZcwAiL4OwzlCVjP7WKCNKPotuM7N3L3ymwh0xjZpf8eYGQ
         Mu247fjQyAzRA686m7FAnO6YyShacqnPAFDRFelh58xMNwlAvK5CibBOLzqcnByOV1MU
         YLI4I8bKgUpteXkBOkF6jV2mLEhnYedata+o7IQADh63tzE02YvHWzxRYgWVekzsjFYL
         Ppgw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=XWgAsOmnprNK2skeWGppDbTh40fKVhmJp00QypGoM2k=;
        b=CTbl8HJBUilaN/+jdiKx6Hee/e/3+pKsI6qAmw0etzesI/dq3IaJg9nHZQy/j63HTZ
         3Op5YomXgWsnUR6EzAgRfCyL/J7jTm40LVwNx7/3X9jG2++RiZxXxVKY0CBrPrilnJjm
         +CBRO7oumeqUJblZHG3iBm5WB1M+31I9FJ+uZk9N7M7QpRBhPL5c7Af5I4NNzNjLNDLv
         JtgK3pU1pw+8Eh1sxmNeXS6ZCtDNVn+soU4ZvMCAJABCzglnHPAx3u+dpVHFQ88T6jnP
         8U91zjTDFoKwm+UrToOV9+Jv+CuG2BPXR4+XXC6bh3L7IpcSOonmz+gYPtaI0NCZDcMb
         S8Kw==
X-Gm-Message-State: AOAM532qaQAKebKdXsrHJLaMZK8HpC1v3mIzRzdHUwwfLSqg4Y7UtYFv
        /4nt4II2QfgTyWzlAf8Ke2EdtzKd8AI=
X-Google-Smtp-Source: 
 ABdhPJzigDhlUEFhg9q6amk4thrZa+of/18EGmVGYFbGF3OGaz8W5MPMklCYns/17wJN3V0j1ZleeA==
X-Received: by 2002:a17:906:1f54:: with SMTP id
 d20mr18427747ejk.94.1620816883017;
        Wed, 12 May 2021 03:54:43 -0700 (PDT)
Received: from avogadro.lan ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 b19sm16829624edd.66.2021.05.12.03.54.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 12 May 2021 03:54:42 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH v2 kvm-unit-tests 1/2] libcflat: clean up and complete long
 division routines
Date: Wed, 12 May 2021 12:54:39 +0200
Message-Id: <20210512105440.748153-2-pbonzini@redhat.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210512105440.748153-1-pbonzini@redhat.com>
References: <20210512105440.748153-1-pbonzini@redhat.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Avoid possible uninitialized variables on machines where
division by zero does not trap.  Add __divmoddi4, and
use it in __moddi3 and __divdi3.

Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/ldiv32.c | 40 ++++++++++++++++++++++++----------------
 1 file changed, 24 insertions(+), 16 deletions(-)

```
#### [PATCH v2 01/10] math64.h: Add mul_s64_u64_shr()
##### From: Ilias Stamatis <ilstam@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ilias Stamatis <ilstam@amazon.com>
X-Patchwork-Id: 12254079
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F153C2B9F2
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 15:16:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B5DD61979
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 15:16:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232307AbhELPRL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 11:17:11 -0400
Received: from smtp-fw-80006.amazon.com ([99.78.197.217]:49139 "EHLO
        smtp-fw-80006.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233423AbhELPNY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 11:13:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1620832336; x=1652368336;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=dd+cfBA8UFfC6dBFQo/XyrQ8fEmJ+IwhldFGtGJFtIU=;
  b=m8EqzTjxxfM+pZFyDTOxUJKnkFgbKCb3k8KJCFLWynWhIABS1mkQVP4b
   XnHqRUdMV8+sAVWuvmgcLoKUm9ycYxFOv/nKSoarasVINBpSgAJAU9Upl
   vINoNlli4mnx6ke2u0Bhan0TWG/UBcKJ+4Q6qZ+CR1LXvW7Jd+dFxhuxk
   c=;
X-IronPort-AV: E=Sophos;i="5.82,293,1613433600";
   d="scan'208";a="1007669"
Received: from pdx4-co-svc-p1-lb2-vlan2.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.25.36.210])
  by smtp-border-fw-80006.pdx80.corp.amazon.com with ESMTP;
 12 May 2021 15:12:04 +0000
Received: from EX13MTAUEB001.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id AE104A24EF;
        Wed, 12 May 2021 15:12:00 +0000 (UTC)
Received: from EX13D08UEB003.ant.amazon.com (10.43.60.11) by
 EX13MTAUEB001.ant.amazon.com (10.43.60.129) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 12 May 2021 15:11:45 +0000
Received: from EX13MTAUEB002.ant.amazon.com (10.43.60.12) by
 EX13D08UEB003.ant.amazon.com (10.43.60.11) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Wed, 12 May 2021 15:11:45 +0000
Received: from uae075a0dfd4c51.ant.amazon.com (10.106.82.24) by
 mail-relay.amazon.com (10.43.60.234) with Microsoft SMTP Server id
 15.0.1497.2 via Frontend Transport; Wed, 12 May 2021 15:11:43 +0000
From: Ilias Stamatis <ilstam@amazon.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <pbonzini@redhat.com>
CC: <mlevitsk@redhat.com>, <seanjc@google.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <zamsden@gmail.com>, <mtosatti@redhat.com>, <dwmw@amazon.co.uk>,
        <ilstam@amazon.com>
Subject: [PATCH v2 01/10] math64.h: Add mul_s64_u64_shr()
Date: Wed, 12 May 2021 16:09:36 +0100
Message-ID: <20210512150945.4591-2-ilstam@amazon.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210512150945.4591-1-ilstam@amazon.com>
References: <20210512150945.4591-1-ilstam@amazon.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This function is needed for the nested TSC scaling code where we need to
multiply the signed TSC offset with the unsigned TSC multiplier.

Signed-off-by: Ilias Stamatis <ilstam@amazon.com>
---
 include/linux/math64.h | 19 +++++++++++++++++++
 1 file changed, 19 insertions(+)

```
#### [PATCH 1/3] KVM: nVMX: Move 'nested_run' counter to enter_guest_mode()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12252649
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A5BFC433B4
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 03:58:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 566CD61205
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 03:58:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229597AbhELEAE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 00:00:04 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:51640 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229447AbhELEAD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 00:00:03 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 14C2ZY7E029450;
        Wed, 12 May 2021 02:37:13 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=T6DXo5D3HpC7gxwXj2dOrWQonakJF0RILsSsA4/u6Tk=;
 b=TQQ4PRrom+kBoeEN/eh4/a87tlsCEt0gEYOA4IslF4OTv6Q6vCatPL5gQRPjaOOol7Pu
 eWlyv/GE4m2wUB97RXHV5L9On3IUpWGMHF3fVCCFIrNU+J1+/e14jM3t3+AwZYxgd9hN
 DzXZT8FXI+CE3FddN0Nt2Jq7eWTcFmpZLBLyj71kCim+En5ozWidVsOXnW++g2WvFx4L
 x7vHrr1ggWTlbnVDhFGaFmvj/0JAebKU/+nXSkJ+LNCgbhFsFCMeTbMgyWJAEcLvVD3M
 /pu89sEkepScCwtDG335gnFY3aQ3GjNf+/BmyZFHYsBqafzKx0XXqfniPyyn3PYJlV4m dA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 38dg5bgrn5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 May 2021 02:37:13 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 14C2YgI4168780;
        Wed, 12 May 2021 02:37:12 GMT
Received: from nam12-bn8-obe.outbound.protection.outlook.com
 (mail-bn8nam12lp2176.outbound.protection.outlook.com [104.47.55.176])
        by aserp3020.oracle.com with ESMTP id 38djfadpax-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 May 2021 02:37:12 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=gHCr0jyku5Mco1YF6HP7pziGaL0GtA+hoBgxnmZFQJSYwtcmxLdWp47SlYjVyPgYeswzDepXIHPtwOTSPmQIIBkEixOqu+y6Nl01szdU60KQ+8UETjxM+syWVkf0y4PLaw6f0RgT8SdwSZzP+nuYEScPCnLwLtf6NHgBoY4v/zw4L7W0f86gsNV3y99G1lGjsdnQ+wTRHzwopavOrlxSoieSIJVz2xhK622Rwo6mQ6sm1F09ykta2GVwsDw5leTf1DbRnF/ijcDwojFgOzO6RdwY1EFTrBr9UagSqSzsHFrFCQJv4jj9c8XQ9cTFP/QN1T81rbOhowdoxSGgl8zzRA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=T6DXo5D3HpC7gxwXj2dOrWQonakJF0RILsSsA4/u6Tk=;
 b=OzaACOOGJhbUYo6GOLQBJumKlF9tyfkrDdeGedy8fyjrQN+bMHYFsFXG1QMIagqGQvoAgStM2Mo/jGsOaP4WisMoB5o0v4eAEhPBMVQTKJz45ZOUnSw37USxGZkD0eIbV+QF4FehtR8bYUB++Sd/DSgVovsJizrv2oEL1Yb9nIDapdbfj7dcFZvzGLUeSOqbBw0sXDWnYKRYmqbl6vdwPAW7T1Qr/OQtYJf77hU7gqMR8qt+KaYokXdmXUx6SpfiS3torN+nRLqPn27x8Yz6HsEIkQp5RWF5SCnO4ncOi5popLEYW/5GsyhH055GD1RhAJNynNpfMIuXRwrQ7a/8Kw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=T6DXo5D3HpC7gxwXj2dOrWQonakJF0RILsSsA4/u6Tk=;
 b=PXpdh8wAskDbR1xBps/IFXvCWoONKWuApkEJudT2KZCsoV7PaIXuNmlj/0/pcdimYnOjB/dK3Uq0z88/dcqn5MbLgI2MMn21GX59okbPSOCiEsCZQ7HRT0DnOybjtm22EGT0xAutRSu9v1e6wOj+WGyMv+U28kEWoTiibN4p2y0=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4425.namprd10.prod.outlook.com (2603:10b6:806:11b::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.26; Wed, 12 May
 2021 02:37:11 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.4108.031; Wed, 12 May 2021
 02:37:11 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/3] KVM: nVMX: Move 'nested_run' counter to
 enter_guest_mode()
Date: Tue, 11 May 2021 21:47:57 -0400
Message-Id: <20210512014759.55556-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210512014759.55556-1-krish.sadhukhan@oracle.com>
References: <20210512014759.55556-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BY5PR03CA0016.namprd03.prod.outlook.com
 (2603:10b6:a03:1e0::26) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BY5PR03CA0016.namprd03.prod.outlook.com (2603:10b6:a03:1e0::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.25 via Frontend
 Transport; Wed, 12 May 2021 02:37:10 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 5ab18957-70f2-441e-a896-08d914eed847
X-MS-TrafficTypeDiagnostic: SA2PR10MB4425:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB442555D7DCE9E9117210505D81529@SA2PR10MB4425.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:167;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 7WfyLZIoF8JTblOjz4u0cJ1U5dJOGR5mZ2OFwn06mn3EJolQCc/wv6cipgy9frq5NWHX1sEeYNpl3sl9fMNFeNtWKiixLq5JwKWZUeA5YaMhipT1bWQxmmnO5ODzlhNf1+Wky5H0QnhlY6wUkt75CBa2bDXBAgjJgM4NAMsyL2Fd/BMEpuV/XNSXnzpeiB/gPeQJvHvYbSm7bXkvi2LfsjPVNEwjiRI2D6EyE5DIUAonsCl1SBARU3+T8DLBs8o7eqimxtAohpHyoHvDCTFnmfP22ABy7Pym9+I5dJxK+ak3U1rd/N7QvZarXZugzAXkLXWZHE9rCJ2vyVKXzMhquon7cISScGYL1DgoMHizac4vBU7m85CmvI3K1fiixS6J6jMeDnSD2M3vhGFjLJjDn0uGVPvlVYsMoDCjSRAB8fW0AdqEU3VCj/j1GLCahtZ7uvItf4au1mMPxd0JPk6Lmreehg8N6OM+iOS8YGt4Fc/u2+/Ifg554TJu/GkU/37SeABLfTwbhniJKT+VQaheMqQVLtTluPW6vYAwZD51So4TlLjr7+KdkFUcPgejUBg8pmt74NaR+oyskmhGz/0Fh1XfFuyqWSiSrEV8H31jrRDFeS0/HxL5CQQWxCzjBaoBbOgYewNbpHDSuDeEo9fqHg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(136003)(39860400002)(366004)(396003)(376002)(66946007)(8936002)(66556008)(478600001)(6486002)(2906002)(1076003)(36756003)(5660300002)(83380400001)(186003)(16526019)(66476007)(316002)(86362001)(6666004)(52116002)(38100700002)(8676002)(26005)(4326008)(38350700002)(6916009)(2616005)(44832011)(7696005)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 CxkE+bVebwM3Vu7Z7vzAszxgq+9fWHogGmshp05Hiw0nzUleDispzVd5d1A3KicdCDvdixLOoxHXeWl/0FM3IDMXmZaShLxFBCwhzc2ooPNzjVM4z0rbGrnIhEqgdyMDs7O28NLq8G5wxQFK0TJqYJBvIyFqjqSxbWqBbMS02OYdgIjZ70js5o7eXut4RYpvbHZ/S4ZIBYldXmwDb3Gk0dfLLrZHkAUqTA/LyMXFEVxcUdQ1b55JM41jiOSPnp1mFktkwv+f5ooVDfocgchaFyIKUWZD+2LdhTJ1QR+GSPsutPf/CfwIikoNXJtEFknrrrfYfHblqBotDuvHh/TOlbDdabPxcIQOkc++p4l51umm8wbNPC2jWJ2DjzaAm4o5B93HUHoOi4xNvcBRSuReBgEdbyMfF97yImeSm6HDxSjS8WNaC4zOR2X0Bvawy1GhzXKO+IAeW0bdIVMRzmBhgsioHVIdExkFy1CcjhdssysP5lbdBNli4cw9YZ9H+4VWeY3avVwbxgsYfRz81NjZjqhDqqiJOOO01lRvkzY+cR/GkPDcuwemnQfsjAwrIU4+KP6jKlYGOOGpSTyHdcXeQcPFjxf9FgT/Ws6YhDQ6rk1ZhaxZTzU5OmcMyrwf6X/B0hQ/JSQiW1Y4NfCHQfraynj4GPXa4elRdUMG25j/SzCdzm++LGNDboVjwTU7sNrqxccTDwxGUQDnQgpgZiSUFfXBLiSTB07+PE5jM7Fsq+Q5FSyvv0chC5TNEqdUptvhdYXLbFkEXnRP21eV3rYy1eOStPAP8NMSlPCoTioF95is1LNOCLTqW3oTdC/Ugyie+4mOYChuvt+1piX+QBAVrOpCLhbaSvlx0DeXoA0eq/vLpFFQdd/BVW2X16CaPfQogu+Su8HOphVGSd3KmxJkbkMLLR1HDSpmJqHlHl8bdTRg6q0KOCF9CKjtumF4dptb4c3uBWOflWp9tSbocMT1vJ5GfO8tNbtUvJrOoM6C5lQEndjy9uSqgyXgw7YTi/3SUWbYLAa+CG0p+Boy0DeoiFeeTKQUFjQKczJYbfR4Zej6d4Mj8jqWjqzSCUb690+kRfFL5yaY4zFo+m2cFolaE3ucH5sevZ9/N6hDbfylH94D/Wu/WVHwDoBOttZswmE31kHj1Pkn333sJ/BLZlrFQo43LDsqUOkbwjs32bf7jTzQaloIkJzPPznT0ULoTIslg04vX9QSC8aUEJF0aP/bJGWhexthT++aFLYqHw90dC9lxs8lFUdUtJXabIwQYXps9gdDl+wyn2VQwwfCZ2fGAG8BYHgd8OBJ1oRQBZ9oS88FkmHX6vO9EM7NkCAzOyxn
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5ab18957-70f2-441e-a896-08d914eed847
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 May 2021 02:37:11.5511
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ItByUtnHszcqDynPqTbYWlNpiqM/jCuhX0//sKrina7LhbRvK+Xgz1uN3d9AsbR3djQ23NTaAw361ntio4K4kr0tHfxY8rE4NEpEmjz8hUk=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4425
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9981
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 spamscore=0 mlxlogscore=999
 adultscore=0 phishscore=0 mlxscore=0 suspectscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104190000
 definitions=main-2105120018
X-Proofpoint-GUID: AQ7doeTnY4gdNViQQ8m7Uhss2P90yM6B
X-Proofpoint-ORIG-GUID: AQ7doeTnY4gdNViQQ8m7Uhss2P90yM6B
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9981
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 malwarescore=0
 bulkscore=0 spamscore=0 clxscore=1015 priorityscore=1501 adultscore=0
 mlxlogscore=999 mlxscore=0 suspectscore=0 impostorscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104190000
 definitions=main-2105120018
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move 'nested_run' counter to enter_guest_mode() because,
    i) This counter is common to both Intel and AMD and can be incremented
       from a common place,
    ii) guest mode is a more finer-grained state than the beginning of
	nested_svm_vmrun() and nested_vmx_run().

Also, rename it to 'nested_runs'.

Signed-off-by: Krish Sadhukhan <Krish.Sadhukhan@oracle.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/kvm_cache_regs.h   | 1 +
 arch/x86/kvm/svm/nested.c       | 2 --
 arch/x86/kvm/vmx/nested.c       | 2 --
 arch/x86/kvm/x86.c              | 2 +-
 5 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: SVM/VMX: Use %rax instead of %__ASM_AX within CONFIG_X86_64
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 12253357
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A7CE0C433ED
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 11:21:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70CA9613CF
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 11:21:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230182AbhELLWo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 07:22:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48014 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230037AbhELLWo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 07:22:44 -0400
Received: from mail-ej1-x62c.google.com (mail-ej1-x62c.google.com
 [IPv6:2a00:1450:4864:20::62c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 12C13C061574;
        Wed, 12 May 2021 04:21:35 -0700 (PDT)
Received: by mail-ej1-x62c.google.com with SMTP id w3so34443151ejc.4;
        Wed, 12 May 2021 04:21:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MHzreHuweH97osIdaXwbfq/+CLsH9zkDVNipBCZFdw8=;
        b=NN/KgV2Yh68bcHPu0DFZE2mIb6JkHVqGKhAM1BUUN9OSI2tKsPy7+/pKdP/8RFjjsO
         NI8z+Y3I4XH1zMeAGEE0xhb+TxvqljEC1q1KY7PYUQ1LguKqtiw+o2AJ7Z4uDNwzHqF4
         SXvKIvfGFOjok6OAzc91MG/r4bSq35o07qdcq3ZXr99+GsoCJBqk7oFQ0iVIGVj5ko+m
         G7EIbWkftBHrAGk9rmr9zfdvOTA3TZPUlb7eFwjuI0+HllDUP/tqyK/VH7ygrg/eaPeO
         D1280JzzEJeNi3TPoVsHjXPrybb4p9vHccTqfgp7hJh9lb+tDH5ZpWag7eO1xY2kCG6t
         eZxQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=MHzreHuweH97osIdaXwbfq/+CLsH9zkDVNipBCZFdw8=;
        b=jtxFhybpST1BNuNg3f997SYyqrmBvM21cZvRi6ic/lp4iAYZ0H7p+kB8xulVMEVHzI
         9gCRxeEukughCoo6hIoqNeVr5CvFQLz32HemJfa7ntE4T/XV6Fq5nO/YclJ7WKfXgOml
         je8ZJJ7LgMdQvtLCsGvn/5VmRFiRMl69g8AdKCU9Ak399dco8E3FUngKlgR5zjBFQkA0
         HtYcL9XrJm/erp34x1VcWa3EPZV/IDCLnQok0WKwI2S1xaTb79giF6zakl6rx4faf08t
         lpw7Wn8OUZRbWu+1UcyNLfq2u9Rcst1E0WXAKQCYGn2JoOrLxubqtG5DQ7KapYI2+OKN
         HJ/Q==
X-Gm-Message-State: AOAM530CfWlJyq0XDIziuv89WOdkGmIZeA7DHnd0LZppP4EtmmRRzYRX
        qXTagAZ57boGDC9vX7pq0SdYsCYC/uuXYQ==
X-Google-Smtp-Source: 
 ABdhPJwGNuBiiVAKjqaj/eiwSGpnSYkfNx81epAAbGKk5DYCb8fuTybvOZb+uEo84xR+OYNQLp8ddg==
X-Received: by 2002:a17:907:11db:: with SMTP id
 va27mr36365589ejb.174.1620818493453;
        Wed, 12 May 2021 04:21:33 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 w6sm11763192edc.25.2021.05.12.04.21.32
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 12 May 2021 04:21:33 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: SVM/VMX: Use %rax instead of %__ASM_AX within
 CONFIG_X86_64
Date: Wed, 12 May 2021 13:21:15 +0200
Message-Id: <20210512112115.70048-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no need to use %__ASM_AX within CONFIG_X86_64. The macro
will always expand to %rax.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm/vmenter.S | 44 +++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmenter.S | 32 +++++++++++++--------------
 2 files changed, 38 insertions(+), 38 deletions(-)

```
#### [PATCH v3 1/5] KVM: x86/pmu: Add pebs_vmx support for ATOM_TREMONT
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12253079
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BEC6FC433ED
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 08:45:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89BDF613CB
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 08:45:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230196AbhELIqq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 04:46:46 -0400
Received: from mga17.intel.com ([192.55.52.151]:10038 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230411AbhELIqm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 04:46:42 -0400
IronPort-SDR: 
 eCWfj3GGgRr7hdiMm0uOivpq9iBLi4mZslg34g/ieXzPar6nq8a5cORYC5AJQEyNwxsKK3177x
 J2XXzoKJs0mQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9981"; a="179918820"
X-IronPort-AV: E=Sophos;i="5.82,293,1613462400";
   d="scan'208";a="179918820"
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 May 2021 01:45:33 -0700
IronPort-SDR: 
 2RfI0KCX8hls62HKYhihrH2SGRZJJ1OhtCA6lZscHNUH198yTQy8dErxYul8K1+3DWn2v41rU0
 YGyU0isipdAw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,293,1613462400";
   d="scan'208";a="392636333"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga006.jf.intel.com with ESMTP; 12 May 2021 01:45:29 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, peterz@infradead.org
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        eranian@google.com, wei.w.wang@intel.com, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>,
        Andi Kleen <andi.kleen@intel.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>
Subject: [PATCH v3 1/5] KVM: x86/pmu: Add pebs_vmx support for ATOM_TREMONT
Date: Wed, 12 May 2021 16:44:42 +0800
Message-Id: <20210512084446.342526-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210512084446.342526-1-like.xu@linux.intel.com>
References: <20210512084446.342526-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ATOM_TREMONT platform also supports the EPT-Friendly PEBS capability
and we can also safely enable guest PEBS. Per Intel SDM, the PDIR counter
on non-Ice Lake platforms is always GP counter 1;

Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Andi Kleen <andi.kleen@intel.com>
Cc: Alexander Shishkin <alexander.shishkin@linux.intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/events/intel/core.c | 1 +
 arch/x86/kvm/pmu.c           | 5 ++---
 2 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] selftests: kvm: Fix a potential elf loading issue
##### From: Zhenzhong Duan <zhenzhong.duan@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@intel.com>
X-Patchwork-Id: 12250829
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.6 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_12_24,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4CCA4C433ED
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 12:30:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 260FA61927
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 12:30:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231527AbhEKMbf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 08:31:35 -0400
Received: from mga14.intel.com ([192.55.52.115]:23526 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230225AbhEKMbe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 08:31:34 -0400
IronPort-SDR: 
 CvsD45L9PuIr9SJD+hpXmTpC498oL5h+Diw2b5r324ektfrmS9fJ9DcNydyfTbu7uKgZGxOJ2B
 rPifdYLvgSgw==
X-IronPort-AV: E=McAfee;i="6200,9189,9980"; a="199108946"
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="199108946"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2021 05:30:28 -0700
IronPort-SDR: 
 LSSDBtLdcphiCsXB/4quGD+UMacuYngM3MvfRNb4+AkMb2XnYUyoQ61Y+0Fmg5ds/XySGXAQHA
 JYDZEo5ljoDw==
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="436634148"
Received: from duan-client-optiplex-7080.bj.intel.com ([10.238.156.114])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2021 05:30:26 -0700
From: Zhenzhong Duan <zhenzhong.duan@intel.com>
To: linux-kernel@vger.kernel.org
Cc: linux-kselftest@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, shuah@kernel.org,
        Zhenzhong Duan <zhenzhong.duan@intel.com>
Subject: [PATCH] selftests: kvm: Fix a potential elf loading issue
Date: Wed, 12 May 2021 12:31:07 +0800
Message-Id: <20210512043107.30076-2-zhenzhong.duan@intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210512043107.30076-1-zhenzhong.duan@intel.com>
References: <20210512043107.30076-1-zhenzhong.duan@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vm_vaddr_alloc() setup GVA to GPA mapping page by page, then GPA may not be
continuous if same memslot is used for data and page table allocation.

kvm_vm_elf_load() expects a continuous memory of GPA or else it need to
read file data page by page. Fix it by adding a check in vm_vaddr_alloc()
to ensure memory is allocated in a whole if same memslot is used for data
and page table.

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@intel.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH] selftests: kvm: make allocation of extra memory take effect
##### From: Zhenzhong Duan <zhenzhong.duan@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@intel.com>
X-Patchwork-Id: 12250831
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.6 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_12_24,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89767C43462
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 12:30:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55F836191C
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 12:30:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231560AbhEKMbg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 08:31:36 -0400
Received: from mga14.intel.com ([192.55.52.115]:23526 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231432AbhEKMbf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 08:31:35 -0400
IronPort-SDR: 
 ZMp9bP8vZBOS/6OitNw0BHzbQoZBmM0F6hUTnPgbkYLOAfoot52Cemoku/6oR18g88W7twWrBp
 5W4H+qJRh4Sg==
X-IronPort-AV: E=McAfee;i="6200,9189,9980"; a="199108941"
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="199108941"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2021 05:30:26 -0700
IronPort-SDR: 
 iZsLdeOIW/rdw0bWGu15JHNiN+raV5v41OwxlkIvP9QvlOABntQoU6krP2S5Held2csza33y9g
 18uqcib9GL6g==
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="436634130"
Received: from duan-client-optiplex-7080.bj.intel.com ([10.238.156.114])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 May 2021 05:30:24 -0700
From: Zhenzhong Duan <zhenzhong.duan@intel.com>
To: linux-kernel@vger.kernel.org
Cc: linux-kselftest@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, shuah@kernel.org,
        Zhenzhong Duan <zhenzhong.duan@intel.com>
Subject: [PATCH] selftests: kvm: make allocation of extra memory take effect
Date: Wed, 12 May 2021 12:31:06 +0800
Message-Id: <20210512043107.30076-1-zhenzhong.duan@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The extra memory pages is missed to be allocated during VM creating.
perf_test_util and kvm_page_table_test use it to alloc extra memory
currently.

Fix it by adding extra_mem_pages to the total memory calculation before
allocate.

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@intel.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 39/40] docs: virt: kvm: api.rst: Use ASCII subset instead of UTF-8 alternate symbols
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12253475
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A9043C43462
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 12:52:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 76A2061104
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 12:52:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231419AbhELMxk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 08:53:40 -0400
Received: from mail.kernel.org ([198.145.29.99]:53084 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230430AbhELMxH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 08:53:07 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id C788F6143A;
        Wed, 12 May 2021 12:51:47 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1620823907;
        bh=Rep4488btcGkKQJG3baQdJ6X/088U7ci2M0IySOvCVY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=lZYXQeY0yNNPJboL2kgoqrNjfjMdnZkfgCFBi8X/c4xbPFeCb5SLp/VQ5ORLH1zUu
         MolJyllNaINbgtFp6ABZYNl5noK6VwqP8kfnCz4cIyraZqncso/rdYhw10c+dpTw2m
         OZ277cM8h0g2RpeiJ0anr7hwBSjNgx6abKraoCTHdYl5g3e37bJlbKAdafe1v9/wMc
         +rCUYGJGbw9AvKZHQZuhpuw4ff8gNFSEkg0iONw9D2pSBtZ7RTr+4fRPds2dfJz+tv
         NevzAYmGCrlwQ/ocDe8dp7GIsc/5rS8LRf5BIv/GoTlvAmLSttP5RJxbxLBceg7SN+
         isuP0dfdNj3GA==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1lgoL3-0018nv-TQ; Wed, 12 May 2021 14:51:45 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 39/40] docs: virt: kvm: api.rst: Use ASCII subset instead
 of UTF-8 alternate symbols
Date: Wed, 12 May 2021 14:50:43 +0200
Message-Id: 
 <504e06926ded9368f1e754b20d380d483d84a221.1620823573.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <cover.1620823573.git.mchehab+huawei@kernel.org>
References: <cover.1620823573.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The conversion tools used during DocBook/LaTeX/Markdown->ReST conversion
and some automatic rules which exists on certain text editors like
LibreOffice turned ASCII characters into some UTF-8 alternatives that
are better displayed on html and PDF.

While it is OK to use UTF-8 characters in Linux, it is better to
use the ASCII subset instead of using an UTF-8 equivalent character
as it makes life easier for tools like grep, and are easier to edit
with the some commonly used text/source code editors.

Also, Sphinx already do such conversion automatically outside literal blocks:
   https://docutils.sourceforge.io/docs/user/smartquotes.html

So, replace the occurences of the following UTF-8 characters:

	- U+00a0 (' '): NO-BREAK SPACE

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/api.rst | 28 ++++++++++++++--------------
 1 file changed, 14 insertions(+), 14 deletions(-)

```
#### [PATCH 1/6] x86/sev-es: Don't return NULL from sev_es_get_ghcb()
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12252957
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E0486C43461
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 07:55:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD2A5613B4
	for <kvm@archiver.kernel.org>; Wed, 12 May 2021 07:55:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230301AbhELH4U (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 12 May 2021 03:56:20 -0400
Received: from 8bytes.org ([81.169.241.247]:38564 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230137AbhELH4R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 May 2021 03:56:17 -0400
Received: from cap.home.8bytes.org (p549ad305.dip0.t-ipconnect.de
 [84.154.211.5])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id E9F862A5;
        Wed, 12 May 2021 09:55:07 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org, Hyunwook Baek <baekhw@google.com>
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        stable@vger.kernel.org, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-coco@lists.linux.dev, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org
Subject: [PATCH 1/6] x86/sev-es: Don't return NULL from sev_es_get_ghcb()
Date: Wed, 12 May 2021 09:54:40 +0200
Message-Id: <20210512075445.18935-2-joro@8bytes.org>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210512075445.18935-1-joro@8bytes.org>
References: <20210512075445.18935-1-joro@8bytes.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

The sev_es_get_ghcb() is called from several places, but only one of
them checks the return value. The reaction to returning NULL is always
the same: Calling panic() and kill the machine.

Instead of adding checks to all call-places, move the panic() into the
function itself so that it will no longer return NULL.

Fixes: 0786138c78e7 ("x86/sev-es: Add a Runtime #VC Exception Handler")
Cc: stable@vger.kernel.org # v5.10+
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kernel/sev.c | 25 ++++++++++++-------------
 1 file changed, 12 insertions(+), 13 deletions(-)

```
