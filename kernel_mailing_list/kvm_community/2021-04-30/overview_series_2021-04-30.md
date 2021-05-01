#### [PATCH Part1 RFC v2 01/20] x86/sev: Define the GHCB MSR protocol for AP reset hold
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12233169
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 81560C433B4
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:16:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2A04B61405
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:16:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232034AbhD3MRo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 08:17:44 -0400
Received: from mail-dm6nam12on2089.outbound.protection.outlook.com
 ([40.107.243.89]:57920
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231766AbhD3MRn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 08:17:43 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=f1Rzn9WahEob3qGaCdHcXyNd4Y+jd2dIDUxf4U6Di5RYHFCjrybS+hLksd3aaFxMoTyoJxcYSVXfOdoEHneKBli8cZnWTc5285z+3gNZ8FopTPxhVWAw9dRKBgAWHp0v/t9BKISBVjP8sUPSLakK8gxR3uGNODLEHhsg3Et5Nqv9HT1lXimfCgEyfHKOF6zFxUeDAvtK62Los1Swy/q5EQX0HjWRyoLgNdLmGlqUjziZjO8RqXKqMOB835o8ki3X5tOiXl9/ESMWvmnga1/45NeacWMGnzP2nKzCK+DTdEI0xwuy9jKn+Zm1WBgbuLoWe1vRfiEelzjYMR9vqA8k/w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=FSqjj79y9azdiLTw3J18Jb92HW5TNRtkirg8lS4kcv4=;
 b=nJTUtxS3+aT7KI6HxHXpdEPgGB3uj9LP+wV9VIGN+wz0fNaVl1s8+v0AEImcTTA6rWJ530rta/rXGhASWo6iO7CDFh8+QfaieQgzdBv3JULcgEzvKjs/XRoJp8m7C4OhtlM7vvwruTlihaJQ7JM1Nm5dOi0TOw9/qllyhSyuzPsz9ppRkCzu53pSQrAk6axF5GyoNy0rYAwlF8SQe7dFbhQUCPWVrtwujho5KuTnRAdbV3x2u3E30QePbPVDR9epu894kC/iw3SgCYSoIta7BkC+dA9VyFl7WAWYMvEsIfAMdla1mvWJ5dBWBSVA3pRlW48tB8t6/hf5ILsK+wJeFg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=FSqjj79y9azdiLTw3J18Jb92HW5TNRtkirg8lS4kcv4=;
 b=fN2yiPAZegR1bAjJqv0bu8eHFjk1eRgbuEXsgn63BeliKGsp1jyEyqJdZmITXNh9XxajWkZOEXELWHkHn/RyTsxPfjrQObr8ISkLg3aYm0HBB0Q28PyIwHxFUc7mlT33uH+5G1zrgDmnkpLL/I16bYnzEm5hWAl6kclzNlowai8=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4431.namprd12.prod.outlook.com (2603:10b6:806:95::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.26; Fri, 30 Apr
 2021 12:16:48 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Fri, 30 Apr 2021
 12:16:48 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, bp@alien8.de, jroedel@suse.de,
        thomas.lendacky@amd.com, pbonzini@redhat.com, mingo@redhat.com,
        dave.hansen@intel.com, rientjes@google.com, seanjc@google.com,
        peterz@infradead.org, hpa@zytor.com, tony.luck@intel.com,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH Part1 RFC v2 01/20] x86/sev: Define the GHCB MSR protocol for
 AP reset hold
Date: Fri, 30 Apr 2021 07:15:57 -0500
Message-Id: <20210430121616.2295-2-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210430121616.2295-1-brijesh.singh@amd.com>
References: <20210430121616.2295-1-brijesh.singh@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0401CA0021.namprd04.prod.outlook.com
 (2603:10b6:803:21::31) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0401CA0021.namprd04.prod.outlook.com (2603:10b6:803:21::31) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.27 via Frontend
 Transport; Fri, 30 Apr 2021 12:16:47 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 9c779ec0-efc2-4536-4761-08d90bd1d405
X-MS-TrafficTypeDiagnostic: SA0PR12MB4431:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB443140CB2B8B87242B6EEB41E55E9@SA0PR12MB4431.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3383;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 a4IXNfZ2kJrjBLR+hgx9Wse5C1E2io/tOoqsAm1AsYNwWvdNDEgGAPUdHtno1nF9hIRfrI6dAYewrDeml8DK25oDQEauRU0DH+exmoHSE+6LTM9yPOWr0DmVOS0tmtcquWCSVsRZmX4D2mB2z4TKHvmgyTDx40QhRlCSJH8AGHKUtQe4iuB2eKOpzZzzvRJasZ2AlETsQaIfxNaYImjHNtbQPWZJvwX59mwDwbD6wxfhoV+V6iHqHN2ZNv76/1sI/Y5CLZq65ekGZ3JKRFx0JrkvvjnckZJLs15Nk4BAq3/byfXLKK35GHlVJTtje2vna7ePIj0Xqt3dm5/oS6MhIR0f8DduI8nT3KnPUazvakWzsJ/tBs/f/afvZ3pvf8xD8/e60dUETxkLlnx8dZccPGLbluFQhQMSABG2zo99qop1A1Hk5Jgu5z0gbv2RB4jtnT6I5dyY4WHlkcht2QPVkHCYQyeauCuQpMMYpRrKijiDt227uQYVFuODRluzpw2XDm2qnkITZ3zykmoEbB0sD2bEAJd5hOthQxn/rxnOGqsmygIipd/bh0Bdo1X2j6ZKnnyEkIybISOuT6AErxJqgsmUP+WwObk9Jb9esxQ0sLbGzuVsClvtLGXu/SDcR77VMrwYHk5dJqLQHxAfdBHzhQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(376002)(346002)(366004)(39860400002)(396003)(6666004)(2906002)(38100700002)(8936002)(4744005)(316002)(5660300002)(38350700002)(478600001)(1076003)(16526019)(26005)(7696005)(7416002)(186003)(8676002)(52116002)(4326008)(36756003)(956004)(6486002)(2616005)(66946007)(66476007)(66556008)(86362001)(44832011);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 +IW/lbas180EnTIhXa3Gf1CTBIVtXI1gZXAolSreE3DVSNbO/c7U4RD69HQx0W9yhPyPbSZSBj4qHg8fwNnA0i5ZvNEyBmEplnV20+oE9UAucCu6R87sLpHugWTXDF2m+3Fgt+UDaay+RwcacFKn9uYZvrXVxYvNIu2SEuQkFB62rrqP6mwQFyVm4U/nYJGzIGHNj04fO69rsXb+3eEVABuvnMnnc2R6QqkzvPdkg8n5nlKv4F9c/xBWYz/ZLpT3SXkByjsNBd5vChi4y6BJ+MebPKHEBTqfS1ZX5IDfaY8TvAbVExHh+c6lFn98Hinvuhtzpr95YaQjditYhG5y6ySprTMfpGh08gfLrveGI77yvYSwFuZ6W/diabrSgk0H9Z4AkPD2CAiS4WfsboU9pi4+wkRynlHJG8vYqA4lI9SFUOFfQPkQ64Ht93+TWdFIu7gU4eVXMcpY36kn2u60FicxelyA8u6yTdpYE+ox7mKModjCZWmPBTbpisgV1oHwNjELbugSvzXz8+eJeN1j3lH5BDImwhdKq78UrT9o/37+BRe13DJ2euktJ2xZ3pVrLoxD08oOhha6vhjnoqvgwt8UJeFsJzHaRgeVtVlarwEGLBj2GMrY2+sT0dQ3ojVAqLXi8UUSDVI9o0YVPaeFj6UhuTO3Eham8LVyAaAa6FfFdCu2UyW6WHIkOh1lQzVh5c62cifuNdkb/rvVKQq5disoFrBMUL9kqkLVTVvW4dLUitMBp/BhEqyPXZA6E/oZ5OsTZYCLzp0o59qWA0ssiYUCPBogOt7qUfAob3oYJ9sdDW+JAnjVXCVOKyYihAoG4Q21NyT1OL2ijP8KukglP1uhF4O0c7onFwiktDn5GkO+vroKpGtMolimSkoR3EjaTAEXKkxcvLvBWB8KdAbbCCYEY3ZHo01PBAIOgQVYeirxPb4O8ZQYhHX9LRad5N6CfcbEzmLVM3gGYXLGeIWEoez8pwRIGkmT6b1RbYhbLEXeMT5tqtgWyop2oDrS4FuQWH71tqo3cR6lccLbzPytwOK3Krb9Q0uHzOl6K7t+hNOybZYt17A/hFMsphPuYSjLBrRE30RgAwQ++A/YAPbLV/d3xHlEPWwkJh/khobxreHgxBazQCfCxB9t22o0E5k0S138567+tpD7AQfbFClEdwLaZLvffXnWD2H+aSa1vj+Aitbr3458U7Da0aS6I50PjRtzFdW/tTw+o2gDRZo5jHGZrNhebHbl/gt3q0/347/Gq3eTQMmMdxb24geND2vLIHApjo6CG1delEmSShCqTM0eTERYF4SW2u4gabvb9EH+BoV+QQvnxRWeQbXdreit
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9c779ec0-efc2-4536-4761-08d90bd1d405
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Apr 2021 12:16:48.5010
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 FJ4sPVsIK147fIfxXnkYHBN2kk+qOU989EbT4ZjuaO6VwJUbDEJtNomkvItbp5leortLNoGPCHlRI0nvSzKwAQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4431
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Version 2 of the GHCB specification added the MSR protocol support for
the AP reset hold. See the GHCB specification for further details.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/include/asm/sev-common.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH Part2 RFC v2 01/37] KVM: SVM: Add support to handle AP reset MSR protocol
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12233281
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84D30C433B4
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:38:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 582A161480
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 12:38:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232276AbhD3Mjp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 08:39:45 -0400
Received: from mail-dm6nam10on2058.outbound.protection.outlook.com
 ([40.107.93.58]:15105
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231696AbhD3Mjo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 08:39:44 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=kbC6fntHx8WQrOFfS1oMo9M9Cv3ofqWnUxw5sYQZSpHAUNpzDPTZ3IXGpJ8C4FJQseoybP/QmbFGrGS6ALx4e27UBrheuAhkjrkXuAzDarNXbBUBGxPBO6yxB/yOncuKD2E7M88/MRSELUgQIOQ0ZJy7RvSZNmt4xAFa3OvfhAfp+a9i3lu+NmT1BMbxkToGuMfCRaykPudHJU9X/oN3zwjm6g3YfzpC+0Iud5QE/bh2XwATW1oo+nwkP1304shEWm+Bvf2KXXr46R4l1eVhiWuO6wdkVUdJAT4Kxm13Sb55g9f7uUbUDRCPQzTeWj7fvi9PFLWYgwK3hjw3pATROA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CMI48TF+FLivggMVMqIDTa5FlClU/ZB2/9LsP4EYhxc=;
 b=OfXt4B5SxIEqHEw0Z/A14rik2ywsF0qD0XcK7EoOaccNljSpB6knGLzK5/ARjk5i7unoNdOy9s8OtKMONW2pf/EViDc7zDTJn+PP7eSzI31kA5s8h5dev0hQKN/wM+rLZlDE4k4yRqZGXg99dmtKwfCCoyZP8SRgyurhKg9kbY1feVzb/pfNnEZKKD8OylG6B4dlv49pr+JDGUC2mj1w5GxEFCFoC0mJajKflcToMbmZp5RoU3Vuvm3+BimiB9HLwgIjD92xeA68KBx99trfr0KCjQg2FYaejtsn0+J4WSK5kZA8Jjwk96zjlxErwH9BANTOZEM9+njx6oXATmpmyg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CMI48TF+FLivggMVMqIDTa5FlClU/ZB2/9LsP4EYhxc=;
 b=ECVHdf0YyS4zXgsAP3XCPmRux3CASTYNQgRhemI5GRA6rnxcxN3ieUNYLihWaYaZ9HTe9i2IUvSmXmStQGvN8RM/Jzeh/qC4sihmP1QfztEhKeEkGZ9nCEWJ5lKGFanIucIF1ovmkRKb396I8s0usUPltOiSM++HsxZcpwPx7y8=
Authentication-Results: kernel.org; dkim=none (message not signed)
 header.d=none;kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4511.namprd12.prod.outlook.com (2603:10b6:806:95::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.26; Fri, 30 Apr
 2021 12:38:54 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Fri, 30 Apr 2021
 12:38:54 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, bp@alien8.de, jroedel@suse.de,
        thomas.lendacky@amd.com, pbonzini@redhat.com, mingo@redhat.com,
        dave.hansen@intel.com, rientjes@google.com, seanjc@google.com,
        peterz@infradead.org, hpa@zytor.com, tony.luck@intel.com,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH Part2 RFC v2 01/37] KVM: SVM: Add support to handle AP reset
 MSR protocol
Date: Fri, 30 Apr 2021 07:37:46 -0500
Message-Id: <20210430123822.13825-2-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210430123822.13825-1-brijesh.singh@amd.com>
References: <20210430123822.13825-1-brijesh.singh@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0501CA0089.namprd05.prod.outlook.com
 (2603:10b6:803:22::27) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0501CA0089.namprd05.prod.outlook.com (2603:10b6:803:22::27) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.8 via Frontend
 Transport; Fri, 30 Apr 2021 12:38:53 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 52723c5b-bd6f-469e-6175-08d90bd4ea66
X-MS-TrafficTypeDiagnostic: SA0PR12MB4511:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB45110BA51EC3A763128FD3A2E55E9@SA0PR12MB4511.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 bKkMUu348hk2Kfqx/0HAwNE+gm0+pOa+BtmTXdLGT3JpGaN+ufQ0y8rLC7r8aNrUEpI+WDR/WKEqHgiY8ObLG2l8t8GlGtQYa71v7LGi5voIcDGKpleUtF7i/6igteQsRVjfznzYmX4QUBVMTSuh+w9qby8tTCny6DVTcsyuA1GIureRxhpNhnmTfUuyylpPqwuDEHQq2tSs5eiNfgJJxdi4dBzBPA2xtCm8RkyfFmpzu/tSdB8jOwjBFrPnDX5SAFhHdQPawPkqUGkGVwV/Ofl5bduoUUf7B/q0KBPxJlxt2vZsrsg7Xb+6uOjjRwsx0K85anttN1YyTNsR2I+hu571rhi8DQMkO9ghMbpzm2loBI54gNEWimi/SoIMSBMyTVAFAsVZI3WgdJTzdXUzyHMPuO0V97taUKq1Md6z+MeWWn7JBNfLw3xd5iSn9CTfqbDJr9NV1vKHAoWxg1wdMntec+CA1O0dUIOM0xthO9P/HD5g7TnpB8+0Y8F3JaYrBf0GprsswkFeyO39Zw1mB/gvQPer4nSEGhqhx5Y+fuxzThkLyqmPXfV0PVuCk7q3GXnRLR8W2w2VnNtaUx6Juq3/5DP31WlEYjpyZvQake2uKVaf7AEmZfrtBjYm5Mfj0gWqJkFAjom/grzgneU7dw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(39860400002)(136003)(366004)(376002)(396003)(83380400001)(36756003)(8936002)(86362001)(66476007)(956004)(186003)(38350700002)(16526019)(6666004)(6486002)(44832011)(52116002)(5660300002)(38100700002)(7416002)(66556008)(2616005)(26005)(478600001)(4326008)(66946007)(316002)(2906002)(8676002)(7696005)(1076003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 QsxDGsIT6y2yu4v2fDHAPjEnFpKe2Wb7uh9FgMVh0NZnnYzPhM2nip6aWxqmBkWwYE6hy5GFhkhsTVQurAHI9ikoBpZEsTCmoG2tpC1gJ2eNiXUhsfoZAStVqVZgfoaIVutAxe2p2IxJmipz4mbYPOvBT0x0NqTzzHhcb1zvRtMTe7eIaa/gThZ9BPsut8P0+zgY+cpFzko9+el4ozLTKoJriyrpu+M4QonI9p6WHg+wO5D3Ygt1+iGBGyH0nKV5PqLq88GhkCECfsfjHhmy1uxWYIHPHnGOl6wkRQcbVjHk4aoWfZ7qujcdtf+M4F7EYTUWlENYyoYmBOsoxnmTK/8cYoCma1/DnloXuVO2IGwjhxvarBjFgkzBTI7MZRSKCH9WeX8Wit1jXWMhT8cuDqM5X9IJUM36AEJl/GI77HW0Xs4mr+uDVRKl4GvhQnK6td0XExB4HR8zrlbxbPEheBOWxRYN45+Io4KPf+pcmQGqqg4IfXVk+5yuAcuE9e7lYL8+Z3fBmVo7mResDU0k1mdSwK67Ut/FoG2XMdgnuU+/MTqCaxvpxMwwP2pCDZ70+TYnJKw7Voy3RcxwKDflumyLj1P2sRZ0D+eAHRsB/luV6oGCWgBLu8MZjIdgFB1mHMcR/Teaa2lh0VIJQ7nHfoXb9PAnA+gcBnNbM6kY3tzp6Ix9tv9mb2yAdDBiRgnSwKeQAeUl+YvmoJAoBo3Mk36WiS2wkIEd+KfqeXWHcsF5qCoeeC/5MDfyIHldfFN/8lOuAiLVn0/mOy4QMvKNg9oFgn2hpEiEF5kzolZoX8BmlLzs7VMp2nKXTiH22IBdFaLCNSz8btFMlcODXVa+f2Mmz6UP4oY2+0IN0PtLJGjM+AsY8er5QlQ3dHQtWqS2RLbrYwQznRmnnfTKV1dAWTwqlKSN3fsbmtOUCekxBkm/zQDOhtA4aHMtybyXBW5In8/SjRxxHunLhIWIfymxbmTaBZBtqZioAqDXAZGSaMGcm2TcY5gkqbN7JQI3FXLFl2d1ityEKgwItmUzhTXlMnY9nwe+D6vfQcgvjn4aqh/hcP5e7l/Syr24e5JKFoLhQnbnBcR/vLkKnbR5WvfAsug+YgFd2HiG9SD+9LlvwS3bc5+RQjLRQ5CAPHbZdxXQeEHrqL0d7F8Wxfl89Rhf1PZqdWpjhi9Ui9/dUlL8qmeyGKO5SqxQZbiPBt2dR82Dol9yAvN42tRD15GNGFDKa4WjeJBP9Ei9DzPfhLZ3bYACMkMEOVoD3f0WRLLo7Dgwr0MIL/5e7BX3EMHbomfyzhP6l1GBK7J1Aio2JxoS7/f88jsaI9CrDlewk/N/VtgW
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 52723c5b-bd6f-469e-6175-08d90bd4ea66
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 30 Apr 2021 12:38:54.4785
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 qqOh+R9Ma6e0o9qAVDj6v6ELY110rwcjXbnp0kOY6zuetzHctvzySumuPYMvn1xhXDEcjv3r1uUZQsccHBW2LA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4511
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Add support for AP Reset Hold being invoked using the GHCB MSR protocol,
available in version 2 of the GHCB specification.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/kvm/svm/sev.c | 56 ++++++++++++++++++++++++++++++++++++------
 arch/x86/kvm/svm/svm.h |  1 +
 2 files changed, 49 insertions(+), 8 deletions(-)

```
#### [PATCH v5 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12233569
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1DF8EC433B4
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 14:37:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9456613CC
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 14:37:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232992AbhD3Oiq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 10:38:46 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49156 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232776AbhD3Oiq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 10:38:46 -0400
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E6505C06174A
        for <kvm@vger.kernel.org>; Fri, 30 Apr 2021 07:37:57 -0700 (PDT)
Received: by mail-pj1-x104a.google.com with SMTP id
 k19-20020a17090aaa13b0290155dbdb3d87so3980090pjq.4
        for <kvm@vger.kernel.org>; Fri, 30 Apr 2021 07:37:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=d3hjGySdpM9UxSZKS8LI85s6ABUvlsW8K+gGAeHFH8s=;
        b=CD80udlBLO1SbI/OGasmDvuiDcLOWsVPAuiDA6hd1ge9Uj3GroPfJx/18L7C733H+w
         +rv9WImJXx7VU/QcbNGjc+OUagkiJ+2zWqAN2GPZbVbOaRUm8mN6BNi/iW2gUDbjG3Fe
         VrzOc2aQGHDEsMoKM0dZfou7Pa9biUplPtrifGLVQa7WYRznqrkCGvGcSBKYlP3HJvaA
         talmZB8/8FyfVA+ri0OBbWCh6aoSuD6wQCRuMOCjhDhmCO/Vx74+cYYHBN3UIuZSUCJ+
         LeEM9K5EHN6XagRR/GbZxhXrgw41qU5aYTwka7SdvRgc7LD8UDFwcn3kJN3jNnu3RqGZ
         t/uw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=d3hjGySdpM9UxSZKS8LI85s6ABUvlsW8K+gGAeHFH8s=;
        b=l5x7W0SJl7jup61oPwZAPiFxpg0125gttMNtBIlJaa8kBVlB+3zDoC44TPaXE2IMJ4
         Dc/93krw1UrkAnlJQDofaPpMW57mp8W4slWIX7y2GWJ27476OnEgpDPQRQNvtONv8DZV
         v/lvVZJzDHA9gG7bOv/boF4/lNWLA11Hz5qbE7Pc8pIrp86/nqNwDwjyZtnPUkcH4ag4
         Bk8gsKZz12RYEMpbGydBrDA0yY92JLXYCPd14oyUIGuBclsHlG12+iZTQwZuvSxPqnjv
         iwc3RSRTVPwtTrAfB7kkMPzrue9kTxClsfYNtt/seg2VNeA+nQInQ4f9vHUW7s8AjSsI
         flQQ==
X-Gm-Message-State: AOAM530zMn79x2xMYXbBjipLf/Yf+V9zX5zDP32rU+3HEqd9b2Xj+ORW
        VZ92bepq6jGOupA1Do+r+SExLW5T7Mdv0+in
X-Google-Smtp-Source: 
 ABdhPJwFfLzv8WBV/URCk0HRwZMWg5UdEnjMy+i9t5IaY0wJKhSyBPbt2/1gwMG6in+eu7m0GZJ6Ckwdm30mtMq8
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:250e:2425:2e40:acc])
 (user=aaronlewis job=sendgmr) by 2002:a05:6a00:1687:b029:253:f417:4dba with
 SMTP id k7-20020a056a001687b0290253f4174dbamr5222256pfc.5.1619793477365; Fri,
 30 Apr 2021 07:37:57 -0700 (PDT)
Date: Fri, 30 Apr 2021 07:37:50 -0700
In-Reply-To: <20210430143751.1693253-1-aaronlewis@google.com>
Message-Id: <20210430143751.1693253-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20210430143751.1693253-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v5 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 Documentation/virt/kvm/api.rst  | 21 +++++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 37 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 23 ++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 23 ++++++++++++++++++++
 5 files changed, 106 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Fix some return value error in kvm_tdp_mmu_map()
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12233741
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 82C39C433ED
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 16:03:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 401986145D
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 16:03:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230055AbhD3QEb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 12:04:31 -0400
Received: from mga03.intel.com ([134.134.136.65]:17650 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229712AbhD3QEb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 12:04:31 -0400
IronPort-SDR: 
 UJnQsHN391zdL/zBJLtqcFkAFqhVvUUquOzYqfa6roFkNMhClvTkIRSPvzH/kufQ0zr4iwUvCo
 XyizDb7uy/gw==
X-IronPort-AV: E=McAfee;i="6200,9189,9970"; a="197354225"
X-IronPort-AV: E=Sophos;i="5.82,263,1613462400";
   d="scan'208";a="197354225"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Apr 2021 09:01:52 -0700
IronPort-SDR: 
 MVaV2eEYVn773kkAXy/ucYO6x/eIC3XBGxzaqGXGrdNMj1EYCO2ZfPI+lOjr/p2IRqeZ3IB4mt
 Ms9CUDIGpgkQ==
X-IronPort-AV: E=Sophos;i="5.82,263,1613462400";
   d="scan'208";a="466864442"
Received: from rksparrx-mobl2.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.209.48.219])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Apr 2021 09:01:49 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH] KVM: x86/mmu: Fix some return value error in
 kvm_tdp_mmu_map()
Date: Sat,  1 May 2021 04:01:38 +1200
Message-Id: <20210430160138.100252-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are couple of issues in current tdp_mmu_map_handle_target_level()
regarding to return value which reflects page fault handler's behavior
-- whether it truely fixed page fault, or fault was suprious, or fault
requires emulation, etc:

1) Currently tdp_mmu_map_handle_target_level() return 0, which is
   RET_PF_RETRY, when page fault is actually fixed.  This makes
   kvm_tdp_mmu_map() also return RET_PF_RETRY in this case, instead of
   RET_PF_FIXED.

2) When page fault is spurious, tdp_mmu_map_handle_target_level()
   currently doesn't return immediately.  This is not correct, since it
   may, for instance, lead to double emulation for a single instruction.

3) One case of spurious fault is missing: when iter->old_spte is not
   REMOVED_SPTE, but still tdp_mmu_set_spte_atomic() fails on atomic
   exchange. This case means the page fault has already been handled by
   another thread, and RET_PF_SPURIOUS should be returned. Currently
   this case is not distinguished with iter->old_spte == REMOVED_SPTE
   case, and RET_PF_RETRY is returned.

Fix 1) by initializing ret to RET_PF_FIXED at beginning. Fix 2) & 3) by
explicitly adding is_removed_spte() check at beginning, and return
RET_PF_RETRY when it is true.  For other two cases (old spte equals to
new spte, and tdp_mmu_set_spte_atomic() fails), return RET_PF_SPURIOUS
immediately.

Fixes: bb18842e2111 ("kvm: x86/mmu: Add TDP MMU PF handler")
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH][next] KVM: x86: Fix potential fput on a null source_kvm_file
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin King <colin.king@canonical.com>
X-Patchwork-Id: 12233789
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D93FEC433B4
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 17:03:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFD95613D9
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 17:03:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230478AbhD3REQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 13:04:16 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:38233 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229750AbhD3REP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 13:04:15 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1lcWXf-0001yL-Cp; Fri, 30 Apr 2021 17:03:03 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        Nathan Tempelman <natet@google.com>, kvm@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH][next] KVM: x86: Fix potential fput on a null source_kvm_file
Date: Fri, 30 Apr 2021 18:03:03 +0100
Message-Id: <20210430170303.131924-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

The fget can potentially return null, so the fput on the error return
path can cause a null pointer dereference. Fix this by checking for
a null source_kvm_file before doing a fput.

Addresses-Coverity: ("Dereference null return")
Fixes: 54526d1fd593 ("KVM: x86: Support KVM VMs sharing SEV context")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 arch/x86/kvm/svm/sev.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2] kvm/x86: Fix 'lpages' kvm stat for TDM MMUThread-Topic: [PATCH v2] kvm/x86: Fix 'lpages' kvm stat for TDM MMU
##### From: "Shahin, Md Shahadat Hossain" <shahinmd@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Shahin, Md Shahadat Hossain" <shahinmd@amazon.de>
X-Patchwork-Id: 12233155
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,PDS_BAD_THREAD_QP_64,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F4A5C433ED
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 11:52:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F8B2613E8
	for <kvm@archiver.kernel.org>; Fri, 30 Apr 2021 11:52:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230020AbhD3Lxc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Apr 2021 07:53:32 -0400
Received: from smtp-fw-9103.amazon.com ([207.171.188.200]:58215 "EHLO
        smtp-fw-9103.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229875AbhD3Lxb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Apr 2021 07:53:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1619783564; x=1651319564;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=Dtx/M6xk+T/uqMTyekx1GTapviS8Xmbt6xkcI97Wv+c=;
  b=rnShq6/TRzXYXseTCKcSqbIzVCNOrTKuNduQnXbXy4Ql+DgVLKloNM2p
   pytkcoQy/DJtBrHQhqFq/PRRCDQVJWU4cl4fB630CXyBdmYKvzgh43GLF
   m76vGtOw7wRtDs2vflUptnIUoMy4bl2yewrbZKcI+UuwtllJMo9X9JW0R
   g=;
X-IronPort-AV: E=Sophos;i="5.82,262,1613433600";
   d="scan'208";a="930352322"
Received: from pdx4-co-svc-p1-lb2-vlan3.amazon.com (HELO
 email-inbound-relay-1a-af6a10df.us-east-1.amazon.com) ([10.25.36.214])
  by smtp-border-fw-9103.sea19.amazon.com with ESMTP;
 30 Apr 2021 11:52:34 +0000
Received: from EX13D49EUA004.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1a-af6a10df.us-east-1.amazon.com (Postfix) with
 ESMTPS id 107F0A1FB1;
        Fri, 30 Apr 2021 11:52:32 +0000 (UTC)
Received: from EX13D09EUA004.ant.amazon.com (10.43.165.157) by
 EX13D49EUA004.ant.amazon.com (10.43.165.250) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 30 Apr 2021 11:52:31 +0000
Received: from EX13D09EUA004.ant.amazon.com ([10.43.165.157]) by
 EX13D09EUA004.ant.amazon.com ([10.43.165.157]) with mapi id 15.00.1497.015;
 Fri, 30 Apr 2021 11:52:31 +0000
From: "Shahin, Md Shahadat Hossain" <shahinmd@amazon.de>
To: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
CC: "Szczepanek, Bartosz" <bsz@amazon.de>,
        "seanjc@google.com" <seanjc@google.com>,
        "bgardon@google.com" <bgardon@google.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>
Subject: [PATCH v2] kvm/x86: Fix 'lpages' kvm stat for TDM MMU
Thread-Topic: [PATCH v2] kvm/x86: Fix 'lpages' kvm stat for TDM MMU
Thread-Index: AQHXPbWN7k8o6AHTZ0CvACgVIr8ztw==
Date: Fri, 30 Apr 2021 11:52:31 +0000
Message-ID: <1619783551459.35424@amazon.de>
Accept-Language: en-GB, en-US
Content-Language: en-GB
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-ms-exchange-transport-fromentityheader: Hosted
x-originating-ip: [10.43.162.28]
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Large pages not being created properly may result in increased memory
access time. The 'lpages' kvm stat used to keep track of the current
number of large pages in the system, but with TDP MMU enabled the stat
is not showing the correct number.

This patch extends the lpages counter to cover the TDP case.

Signed-off-by: Md Shahadat Hossain Shahin <shahinmd@amazon.de>
Cc: Bartosz Szczepanek <bsz@amazon.de>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
