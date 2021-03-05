#### [PATCH v3 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12115471
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 31C46C4332E
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 05:56:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0714764EFD
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 05:56:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234375AbhCDF4K (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 00:56:10 -0500
Received: from mga05.intel.com ([192.55.52.43]:42033 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234339AbhCDF4B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 00:56:01 -0500
IronPort-SDR: 
 fCF7//kvCZZIOHFYokHQcOKjsE5ZLLiGn33OsM59AzpFokmDEg9q/Gi8ZMUtdqFFk2KNPNVmny
 45PRe2kKdNFw==
X-IronPort-AV: E=McAfee;i="6000,8403,9912"; a="272348865"
X-IronPort-AV: E=Sophos;i="5.81,221,1610438400";
   d="scan'208";a="272348865"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Mar 2021 21:55:18 -0800
IronPort-SDR: 
 pbxHjRuU74YxtVwbSBylO0NH0GClKDGdkLvRHSHUmvIlE9QVphltD6fF7ozb/QQS7TQY2X/1+M
 sxx/h4p9U5cg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,221,1610438400";
   d="scan'208";a="407618090"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by orsmga008.jf.intel.com with ESMTP; 03 Mar 2021 21:55:16 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v3 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
Date: Thu,  4 Mar 2021 14:07:38 +0800
Message-Id: <20210304060740.11339-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210304060740.11339-1-weijiang.yang@intel.com>
References: <20210304060740.11339-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These fields are rarely updated by L1 QEMU/KVM, sync them when L1 is trying to
read/write them and after they're changed. If CET guest entry-load bit is not
set by L1 guest, migrate them to L2 manaully.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/nested.c | 30 ++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 3 files changed, 33 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] KVM: svm: add a test to observe the gain from clean bits
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12116647
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B2495C433DB
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 18:01:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8266464EFE
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 18:01:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232695AbhCDSBQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 13:01:16 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25717 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231789AbhCDSBD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Mar 2021 13:01:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614880777;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=g3BvVTqRZcHNF2bumxV68Pob+1+419O+zr+luXDJ/Hw=;
        b=NShRNXGuYnTfZe91xSe/wYUlDxhgvD42ul+RHQ2p0cHEHkL/GW7L9j+OHgjj8zzwrkiEG0
        zycJUjCJod3Pt7z+LAXNmJQC0V+SYPhOYxSttRJxam2FpuCWVwZ91om38tCqdyn3jbAu+h
        O9wk82dVqbchKfvQ3GWsdbbkvpKhuDM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-583-wyuwOdCCNg6cKDwheSBRyg-1; Thu, 04 Mar 2021 12:59:35 -0500
X-MC-Unique: wyuwOdCCNg6cKDwheSBRyg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B63181054F90
        for <kvm@vger.kernel.org>; Thu,  4 Mar 2021 17:59:34 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 82D2160C0F
        for <kvm@vger.kernel.org>; Thu,  4 Mar 2021 17:59:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] KVM: svm: add a test to observe the gain from
 clean bits
Date: Thu,  4 Mar 2021 12:59:34 -0500
Message-Id: <20210304175934.402058-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.h       | 24 +++++++++++++++++++++---
 x86/svm_tests.c |  9 +++++++++
 2 files changed, 30 insertions(+), 3 deletions(-)

```
#### [PATCH] nSVM: Test VMLOAD/VMSAVE intercepts
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12116621
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B9B6EC433E0
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 17:26:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8E3BB64EE1
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 17:26:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239301AbhCDRZm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 12:25:42 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:54304 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231350AbhCDRZU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 12:25:20 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 124HJECZ047378;
        Thu, 4 Mar 2021 17:24:37 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=QI/01gCYJtbVwXjSZMN/T9wCYTg5pnHJm1SftJjKZlQ=;
 b=hnngr2vLV8TXie+FLtyLXxFz6G8GUOHWGQ15icIBwkBp9LCKVJbCb+thomCfZHZm59W0
 9KlIdQdchVNAdZg1VMkSBjiT2ZNYPe0zLtucEftMRrtM8HUD4Da5gwohlGRYG5WFyJW1
 7scdTlmc0LSgEDacs97pV7JsM+JIdjiZE1aobY2q41EPPXkHKRffVSl7dXhhr3gehw2m
 9ox5yIll1Z1c2BcH4q6+YdhjiejLpX/xGtiL8ZN5Z+fNiX82CiALaVgUOfKsc9+XMcwB
 pqepveLHL8nd8tc8dxpXJvkSobepgcC4TEd20Dx9AsI2h663KeJScHcdL6MwpHFmu6oq wg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 36ybkbfyen-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 04 Mar 2021 17:24:37 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 124HL8JE156527;
        Thu, 4 Mar 2021 17:24:37 GMT
Received: from nam10-mw2-obe.outbound.protection.outlook.com
 (mail-mw2nam10lp2107.outbound.protection.outlook.com [104.47.55.107])
        by userp3030.oracle.com with ESMTP id 37001143c5-2
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 04 Mar 2021 17:24:36 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=GQuODTMUDXBu38Z+dp0ZSWfY3eK+qOsWmEM+3x0ZXftWTphnLscGxdLpSmje6lfvQ6UrZJ89SwjrDLJZFEcWrES0AfrUURRM3bpEG8zvjD44mQY/qqwV1jFdzjOBRwVcfMKyDzPqtITGPK5GRVM6HOgqsv/67if/oVlJYjgSRshZ/wtySppyaQqdiARIdS74C2EaK47Odh4Gt/y4JewR0KSJnSsrAD9oclYflAifQ89bei8r3DZ+RQnRfoAbEVx9DnqOPZL+f/50HUekpuyizjGZmDZwJQ2weCfWVkvYDF8Kb1DoFaBiOMsm7E95XVG7StJWMKVT1icI8sGCGENNZg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=QI/01gCYJtbVwXjSZMN/T9wCYTg5pnHJm1SftJjKZlQ=;
 b=cYosle6c0tBD1hydm4DlGgkHX1M29BDXPjauzah/wQymCL2yji/dcVCqCebPFLKS0uyIQgnYLn6rQUPgCJyLpcQOVZBJNlLIiQVxlhkuCJl5SrxTcgDXhqqi5gOF2YoA2DNlCT5NdMsI/b38KKLbgR99F8SiWWbNKlgPaMk87KoJ/vIIwTGv9ru4I5Pg6QV0WV5rkm/zVnEVhO6a/ZMdxryt1pSEo7k/l/GO0JQchBICiutN53fR+neubE073J92chxgpOuYHs1zQmAQJJ78dnD/42knCjTPdmEFJ5WvvcBfPrfb1YjJl9MpuE6EqE08PT/A0YQCRAO9ybHRLXlP1Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=QI/01gCYJtbVwXjSZMN/T9wCYTg5pnHJm1SftJjKZlQ=;
 b=nNibweOppJOD/Z3RWkJ0fVHpKcgFpyPZb0qAcw1pZUwPlfCAxnBh8HYCVv3S4on2FDvKEY+6rXGRU47MsQYGIpTFJ0ibfHuWCMnyvi9zJBG7gKI+7tNPCZD1hnjiJaXEKLXsfYPXiVLmq7lps3/YZUjf2Ie205ptS9aatQtr42s=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4682.namprd10.prod.outlook.com (2603:10b6:806:110::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3890.20; Thu, 4 Mar
 2021 17:24:36 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3912.017; Thu, 4 Mar 2021
 17:24:36 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH] nSVM: Test VMLOAD/VMSAVE intercepts
Date: Thu,  4 Mar 2021 11:36:13 -0500
Message-Id: <20210304163613.42116-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210304163613.42116-1-krish.sadhukhan@oracle.com>
References: <20210304163613.42116-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.200.29]
X-ClientProxiedBy: CY4PR06CA0025.namprd06.prod.outlook.com
 (2603:10b6:903:77::11) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.200.29) by
 CY4PR06CA0025.namprd06.prod.outlook.com (2603:10b6:903:77::11) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Thu, 4 Mar 2021 17:24:35 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 8b0dc5e9-0ff4-4c04-f861-08d8df32620f
X-MS-TrafficTypeDiagnostic: SA2PR10MB4682:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB46824CEC6DD4ABE7EF9237F581979@SA2PR10MB4682.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1148;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 IoX/dEJf83hXkbAEexhFQWdXn0IyqXInxd5kVp0sBhQZ7RtApOyO/abubeJ5PEAKv0tOhQQl9DuoElX5OTnGer+uDHfVMVUbND9tq1JjosT8uI/zx7Gwi+S92U+gwtDvXkVL2p1iRETQncg/gtOi0oUd8DOC1lqMgF7sfQpRPcgrOcbkkUx6QoUrM0EY9YWxyo3V5QDGG9m3KhSR4UnwljatT1jbSEXa/B/S8oaAXMinVnurJDoEsWYrh2YKIqEuXWzZqS2lKPW8tNNNOGWkNKohTlEoZcvi1YQArBcBqoR1nseWKtarVhdlpeJ6OhiePEm2bNx/nP0rsm2eeSRRW8KVVdcLaOAIdO+vbL9bEQgDoK4YTpN+pap9YAYUVUqOROqzDOp9ZakECls4h49E8LZ688r7nLfM9eR7DHGaJ5hzbqwdAFu26AJsg71zZtFlfvFd5Q7uWGfqjhZvnjyrDxcac7voda7lZ+NPTGgVJfgxGkycNDhVSJX54CG0BdU72zZfSUyi0FynrLCXHT1kig==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(366004)(346002)(376002)(396003)(39860400002)(6916009)(186003)(83380400001)(316002)(36756003)(4326008)(8936002)(1076003)(16526019)(2906002)(5660300002)(26005)(44832011)(86362001)(6666004)(956004)(478600001)(52116002)(8676002)(7696005)(2616005)(66476007)(6486002)(66556008)(66946007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 xFnxcZGLCpXuQ48T7+B/at9XlPqkrmXPsKzgdSssZFG52AO9LUT223SLBp3jbIsJ9doKDbFqg77aNI2CDlCXDsUk4Z4KO6aYtHV7YRNxOLkyNovYYfYcrbI28f8lFPMK0zX7+JynqNlFKg/iw0kY9EnAsI9lKIHgjBWGPc6l1E0RoLlfhjwXBfruT+W6Gb6vcVJxYFrF1bCV8HZ6yuEzTX1QSE2EoQw6V2gZSZ0lltHO8FC5OWfhSrQynDugyL4IRZ3m/YRQTrmajiLuOXASSnMdB7OMViRaLcH0L0YPHqfhbQx3+MAmIhCh/RMy1JHYzBp4R8vulqCs/idcFtaDe6EiGnNe7ZDmsq+FLuuf8ycg7ihD4qjA6LKFQx1R4TSQIZwIKUl7Yypcq+EA97ayhv3412xWsPwSH9yUbV4dJq8c2c88rlAa37P/9gBcRshH6775gm3zs0nvpd2YzAu1bw89uLJMM58bwQiaHodXAwAPUFzelwCWCg8IjabJu5rJGC8ie/Ixji3cZ5cScRa2epAh+lbEwZguvIGYmNE62WD6yGxfzZQh93fCTFfPHw3tQXuY4CrrDPCrxPDV8lC0S7axXD7A/yy/rkYHbehX1xKg/0qw4NRdyBFBD1ut8Cc7Dz9O/Re/P5ZvflM5KABJOMJ7z+qO0EexMY5JmubSlTYPrIYcwYutqpEtS6o4gLQvIkWmJCyUmLq6OU5VPwbHBGZYvNfXHxmpcIas59HAfze9KeRav5O+iCQuVfIhjSrrLQ9yWzpK88XyZrTuX2BX+BGWKv/Xg0SVvhwr1GmjG+Z5xqpQEYWQJgbySwN7gqzT51y1ZOa3PIKW3zdqd0vlyNlelImANqYiySgHF12TEsRg7k3i9KGLxz59KN8ojD569K76bqfk0cWmO9l99Je5yUFPnGiFMRsCfD/o38bvKLbAW+ANq5IbWcmoxOqjp9voY/VwF0EeVcnmU9ne8tLc6TanEh+tO8nKiCJEcBPeUmWzguUD/WsgGXIPdr1yNGleheUAgTSzyHOIf2Qf52ksBX30mv0ugxDadPyDh9fzDVzNcrZFZXXynfvz/rtA/fsbCzvbOV5utUMiDs/tgWdCYfZEFCwpHWxlqJPX8y4bPa3Y2easNFE/IeAHnhdYBFa8ReynI7Vvmv2tB9DC+OGq6e3U0kcl7ktWGOaVy/HO82GoAngY3EI9Mu/wfECZL2xAbNG9TTYXqEgWXCgauKG+b0egDp6hs2WpAyWp7j7AlSlwPveFd9FtY8q5zHzsigwBq2uBrKB4EgdvMVN0nkBIcybKXcUzGBDDI3q+Xzk4yltDm37UPckF59EWvgZWS1PX
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8b0dc5e9-0ff4-4c04-f861-08d8df32620f
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Mar 2021 17:24:36.1596
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 53njGOpv9ikVOBj/Q5c/7T8p525tdjC6awlh0XzxjjR411D7ja7+eG9IlqnYTkARsX8e0fhlOsEPItTJpJg1LFsSpC0FkPV16ScjZM/+orI=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4682
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9913
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 phishscore=0
 malwarescore=0 spamscore=0 mlxlogscore=999 suspectscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103040081
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9913
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 impostorscore=0
 suspectscore=0 phishscore=0 bulkscore=0 mlxscore=0 lowpriorityscore=0
 clxscore=1015 mlxlogscore=999 adultscore=0 malwarescore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103040081
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If VMLOAD/VMSAVE intercepts are disabled, no respective #VMEXIT to host
happens. Enabling VMLOAD/VMSAVE intercept will cause respective #VMEXIT
to host.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/svm_tests.c | 64 +++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 64 insertions(+)

```
#### [PATCH v2] KVM: LAPIC: Advancing the timer expiration on guest initiated write
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12115297
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 79AC0C4332D
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 01:12:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51ED164FB2
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 01:12:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233473AbhCDBL7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Mar 2021 20:11:59 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52344 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1451777AbhCDAiF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Mar 2021 19:38:05 -0500
Received: from mail-pf1-x431.google.com (mail-pf1-x431.google.com
 [IPv6:2607:f8b0:4864:20::431])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B377CC0613E6;
        Wed,  3 Mar 2021 16:35:32 -0800 (PST)
Received: by mail-pf1-x431.google.com with SMTP id j12so17525402pfj.12;
        Wed, 03 Mar 2021 16:35:32 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=NzpsCCGXP4ItyQsT4XoNqFxXYXsUAk2E6LWEAjyLuuo=;
        b=tXZgkVEN2lrE004AVMareVAbW5CSpAXGQHu4TYul0hUvEIt3U77pNG1Y3h2bMU2scU
         dHy75x5mdr30iW5JFblz0qIPTdqqvDYSoakbHvxmQAJbO6sTvwoFuktUGTAyHGqRa9kh
         ekBnqEWsPRIl+wbQCGa8ssHhpoyr9ryrhCDfMLoMwsRmd17+P+owjb0q5D+YpDf1ZUmF
         N6Im/b+xicod/UGSxvCoaTOnNsDyJ2A3SA4+hK/LIaZ+2d1+o3aoB2kwURaO0DnXXOum
         HDQ9LyaxEU3F2PNrs818HgChWT3JjV2mxYpkJ2ZpP6x51CQdOBnLY/bWH+O4j8qxVA2Z
         g7bg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=NzpsCCGXP4ItyQsT4XoNqFxXYXsUAk2E6LWEAjyLuuo=;
        b=a62baNkijeWU/3XywiGQU6l+Jh/tqEtrEmXaWBq9n5NTINMqiXHwN1kK7VLJ3VM7Sm
         dNGJPLhhfxrDLjpCZ3TzJ/SZkjpUfWeN/tlDMS+BxBVgS1geFl6fVJL0flhncodB9Jpa
         EpamShn0dAD+25OegysVw6/yDUwpp4HWsbEesFZHVxxJQYwkRgnptK4V05DtkV08TgA/
         aobe2846CQhCtmdOaqsE3bX+9oPleK3UrCoROyTTpA5567VxIaOpTSO+nX+onO8KBlct
         Z5mIduClHFI1ek1iqqGfH/V61ENAuiCQ3hkqawQQvXBkknl86d/Q618Fn/H7sYWoHh4P
         vVBA==
X-Gm-Message-State: AOAM532KTsWRvdMH1Zgz81t67Aa7mK442fmHg3k4HmVLPaCb3RPQBF4g
        GJqwGZpO8WazZZRLOAoW5uGgPnKttfk=
X-Google-Smtp-Source: 
 ABdhPJzrDCJsduLA3BLhJ/QQO6D0co84IVwpPVmwEn29+QHuww5vNQPL75DG4pm1u+B1hQG6ngiLqw==
X-Received: by 2002:aa7:83cf:0:b029:1ee:f550:7d48 with SMTP id
 j15-20020aa783cf0000b02901eef5507d48mr1342108pfn.12.1614818132055;
        Wed, 03 Mar 2021 16:35:32 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 e185sm26316479pfe.117.2021.03.03.16.35.29
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 03 Mar 2021 16:35:31 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] KVM: LAPIC: Advancing the timer expiration on guest
 initiated write
Date: Thu,  4 Mar 2021 08:35:18 +0800
Message-Id: <1614818118-965-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Advancing the timer expiration should only be necessary on guest initiated 
writes. When we cancel the timer and clear .pending during state restore, 
clear expired_tscdeadline as well.

Reviewed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * update patch description

 arch/x86/kvm/lapic.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH RFC 1/2] virtio/s390: add parameter for minimum revision
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 12116267
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49E1EC43381
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 13:29:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2648264F40
	for <kvm@archiver.kernel.org>; Thu,  4 Mar 2021 13:29:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241339AbhCDN3Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 08:29:25 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:46198 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233758AbhCDN24 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 4 Mar 2021 08:28:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1614864450;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=U25hfNafb9SuM5dJFfJmewNpYbdjseyyxBquOrBCTHM=;
        b=U9XOFaPixZ2WdhZIirGXv8lTq8BTIIE5Hv40PA6wGI3HhxJL5G393G76pzd84JN+uBUTbj
        jOihn1OQAO5HdOAQta5NN8WgYMZCVsj1cstZ18Hb9Jis7JPvAFvlCZRj82rQ5EZj0aCUtT
        NISWNmOVLkWry6lT84f0kTrROLpQFZk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-522-P_KvLWMVMT21oGPPTfUxxw-1; Thu, 04 Mar 2021 08:27:26 -0500
X-MC-Unique: P_KvLWMVMT21oGPPTfUxxw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B1B4D800D53;
        Thu,  4 Mar 2021 13:27:25 +0000 (UTC)
Received: from gondolin.redhat.com (ovpn-114-163.ams2.redhat.com
 [10.36.114.163])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2D3C5175BD;
        Thu,  4 Mar 2021 13:27:24 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Halil Pasic <pasic@linux.ibm.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH RFC 1/2] virtio/s390: add parameter for minimum revision
Date: Thu,  4 Mar 2021 14:27:14 +0100
Message-Id: <20210304132715.1587211-2-cohuck@redhat.com>
In-Reply-To: <20210304132715.1587211-1-cohuck@redhat.com>
References: <20210304132715.1587211-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We use transport revisions in virtio-ccw for introducing new commands
etc.; revision 1 denotes operating according to the standard. Legacy
devices do not understand the command to set a revision; for those, we
presume to operate at revision 0.

Add a parameter min_revision to be able to actively restrict use of
old transport revisions. In particular, setting a minimum revision
of 1 makes our driver act as a non-transitional driver.

With the default min_revision of 0, we continue to act as a
transitional driver.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/virtio/virtio_ccw.c | 21 +++++++++++++++++++--
 1 file changed, 19 insertions(+), 2 deletions(-)

```
