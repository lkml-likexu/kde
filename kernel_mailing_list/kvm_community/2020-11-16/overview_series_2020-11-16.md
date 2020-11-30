#### [PATCH 01/11] memattrs: add debug attribute
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11910533
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 86D01C2D0A3
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:49:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 317B422240
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:49:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="LMP2I6jy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728374AbgKPStO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 13:49:14 -0500
Received: from mail-dm6nam12on2066.outbound.protection.outlook.com
 ([40.107.243.66]:51856
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727852AbgKPStN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 13:49:13 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=WSOoHZYEQt7rSjvh+y1UKPb0pFFz5alAkW99LX7zEbsTswOWzQIl62YcJkLYz5CUGtpdmLXsBJagB1IXRRxaCp65TK25mX5k8x9ethDU5WIL4BO5dEZPu+kKDCicowWAtlpnVahNn751uhCyq/HufQJj5V2rlvqS1Tva75aFwLyWmCORCSnbrmOHs/0T6iMFVd6KHNeXG9guO9zNuW5GoYjBieejUqj4esjXbHI1AiFGcWSzvgg5ipVZPVFQqYwRq3MsSjjPEv3JHEUSxOTnBqmr99tBuwAijS2MrI4CG5HmEj2hGzwlV1tHCzrZvsGZw5P/1VCqpQ36yuCyPsIZzw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qOaakQFQt0d0LxUoW9Kngs89oPksHsauj8Gp5tZmEUI=;
 b=Gh8O8Kmdf3dkPEfYtWz+vgfQLFw+B2zwNPet/UppV4At9ZYbW5snE94Wr+Uu+w+mTQwLxXm7Jg4iRBnGYD8zwd4B977scSLvkGI0Afq75B4Z5AsVL9PjRBuFVvfFvYYE5rYwSSx12Firw77XLGE7hS//evGplSRIu3lfdydjGYOH7OOB8PHuDdg+OPHy4eCxT6J5QckQx7/jvODWyl1cq1LZcPRs6yreb55gZ7kELSeL0jM1kEcHEDe4x+u62q6pXrbpS2fyBA7hsNKcVMcYYkpOdfPnLA/eYg1RNND0wBILm0rKVWAzOjwKkKtKjxMPeyjXt/+KEonr9fUCQhBXUQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qOaakQFQt0d0LxUoW9Kngs89oPksHsauj8Gp5tZmEUI=;
 b=LMP2I6jyLON3lKJgMFvHoZUIqdqwvHRp1xi55zxSwQFVEz4GrjagTJ7WMOOvFZJimXnJDF/4mZnijDOOumsDj0+pUks2wy+pgFxD5xi2yi3U4aWQn628sUXiTILkemvwYdh/+Y3DTbGiBEjA6iPz4tDeK0X54NGJU3ly6ydslwI=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2782.namprd12.prod.outlook.com (2603:10b6:805:73::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3499.19; Mon, 16 Nov
 2020 18:49:10 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3541.025; Mon, 16 Nov 2020
 18:49:10 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: qemu-devel@nongnu.org, rth@twiddle.net, armbru@redhat.com,
        dgilbert@redhat.com, ehabkost@redhat.com, kvm@vger.kernel.org,
        mst@redhat.com, marcel.apfelbaum@gmail.com, mtosatti@redhat.com,
        Thomas.Lendacky@amd.com, brijesh.singh@amd.com,
        ssg.sos.patches@amd.com
Subject: [PATCH 01/11] memattrs: add debug attribute
Date: Mon, 16 Nov 2020 18:48:59 +0000
Message-Id: 
 <2ba88b512ec667eff66b2ece2177330a28e657c0.1605316268.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1605316268.git.ashish.kalra@amd.com>
References: <cover.1605316268.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM6PR06CA0075.namprd06.prod.outlook.com
 (2603:10b6:5:336::8) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM6PR06CA0075.namprd06.prod.outlook.com (2603:10b6:5:336::8) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3564.25 via Frontend
 Transport; Mon, 16 Nov 2020 18:49:09 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: ca3a6828-35e9-4d48-9a69-08d88a604e11
X-MS-TrafficTypeDiagnostic: SN6PR12MB2782:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB278246CC6F2675F8373789BB8EE30@SN6PR12MB2782.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4714;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 XhT5TLSCx5jyqYPkOlElw939/Nr3EwiY0afv/PCFoeQ/frAlXNHqgyHHnplVXPvdNeHnlOv4Ol5VN7aSM+7/ri8HQqGKUACNcfmpPkYiF5IM6DKge0vr3Ee7VtrSoeWbWGVJ7NsHyIrjQhiqE9r7Vt2MNxj+DFopVpKUbCMoa35CbsGOoS8HGdEorXt8DcV9bzYDtdIoB76vyjgeo4E+ZcZqQaeJSc0FK7LZtaC6CYMz7AF/dtlpWrTVm1scae2Ssw3xgOkOUMKUW54pdFrbnpTDo1/0gv3GgMoFFacKJzFsHFIEiqw64tAlnZjNfvdM894KYf3CUrrahKuZCDPYzQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(376002)(39860400002)(366004)(396003)(346002)(7416002)(6666004)(186003)(83380400001)(478600001)(4326008)(5660300002)(8936002)(2616005)(66556008)(8676002)(66476007)(6916009)(16526019)(66946007)(86362001)(316002)(7696005)(36756003)(52116002)(2906002)(26005)(6486002)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 6h5BPgt4Y51bSqz+F2p4Sarq96fJHGaPDK2TJLTGJD+FE72QqoDNr/r+Pb89RyaREBFlEcekFNl6MzQnBLwf2mQVGnM6hCHNXNFvabVCGGAkCRkBIxP2+m2WBbFFCi8K4/75QE44Tk1foPoXOgZrcFI2PzZyS1wYK9BtZqu2XB8KSVZhVDmfoMhx0Y/6Aw7pnCtJMK0DYrA3F4mTcSMfglp3HE1z6g6uJCju6O3Wxr66cMHeUVwLItSBv/hGJDQRNGRMTvCkZLrtSBpj33G6vztlDYQ8M96XcyKUSy2O8RJeIF4ttf+02UajTy+VH7NhIhUo+DkPUh78HO4d/MXtP2BpXfdK57BSrAwhuHrDxvJrEKaVbdvzB8rh1U3TUErbnH0wQmM4zk8UElqq8C6jQ8z8Tot0BmPHzd64Lryh7jRGQW+HVibu19U1+XrYnOEZ/8f4PKnTMsKVsckpN9B/ii6wkNnLmuNLUdnxBNUzn5gwbLiEy6rSvm2q3S/NWYyabuG7O441rQyBowBCgSA9W4VLfZc5QyTo+OtdqFdZHBzGJYsqQvV3lqX7ngcY7A43HETC1gilS3fEpwwSUvWGmYSuE3tcsWGSbeEsPFzYVW2CIQspfmgyQ2D4V/cCWk3fcsBni3TL8aNCawBxi2EeCd2n52ht1gZ1/DPjDLxr/fy7Yop35OlCTWT+yy+YrBIDNUy6ZoJ+y/UWnNZCBGpHdL2Hz83qLt0MTgY/r03cCesblObMIz7Es3oALp/SgYUky8Bw10KrSn2wVigqnO4RC9bFpICuYgypLJ/JkhYrArJYe4jeXHAoqCqz49aLUXMJXlGDCWkLG4jYdn6JO8DQ1nF650BIYMQfr4BAkGL/mYxsiXo/T2GSZM2Oh8cojbSfD6RePlZxEkh1Xm3/pkj4yg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ca3a6828-35e9-4d48-9a69-08d88a604e11
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 16 Nov 2020 18:49:10.7083
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 9EApdeOuPwkIInSgH1wAyMY6oN4UKHBH/X6q4MQ6az9jPaxzBFtnCImbUc6uisQKrb9z1JoT3guUwf/DB+/bnw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2782
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <brijesh.singh@amd.com>

From: Brijesh Singh <brijesh.singh@amd.com>

Extend the MemTxAttrs to include a 'debug' flag. The flag can be used as
general indicator that operation was triggered by the debugger.

A subsequent patch will set the debug=1 when issuing a memory access
from the gdbstub or HMP commands. This is a prerequisite to support
debugging an encrypted guest. When a request with debug=1 is seen, the
encryption APIs will be used to access the guest memory.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 include/exec/memattrs.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [GIT PULL 1/2] KVM: s390: pv: Mark mm as protected after the set secure parameters and improve cleanup
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11908365
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C874CC84516
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:38:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 797AB20855
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:38:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="iuuhzgMs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730051AbgKPMUl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 07:20:41 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:36370 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729933AbgKPMUk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 07:20:40 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AGC1UdC024953;
        Mon, 16 Nov 2020 07:20:40 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=VNrSzwXlIs1GJ3IrKrrWJiVtMsGpmbn/qA5egjFTdW8=;
 b=iuuhzgMsFcaHjAqOhRxbMs5Cjci7/8DedpCHThx4tEqMi4JjyjcT25OjuI+wfh5mg0lQ
 usCv/aBTtaOOfhPVOze6nCbfJfdLzh5NaAmuFIyVGmEgzyFlIm5MYyjnl6x5iSB6W1Rs
 sCR7qUvW9uTm8V6nb3Cr/6bc7ip0ZU7kEk4c/NLxB9lp5jEEdH8Kp9d2dKUdf4yBgUnV
 QVYpss+bYKEbG7R7Qb/GadNwt6CJl4B0RBMCTqax3YYn4o4Zcm62aJrJgslBMH3q3gGo
 N41CjBIwwsUYcvkx7Xx5AKZtxbqmNmQWCd6mNP11X3H08YFZGaah2eq4e+3NBiKpoDPu wg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34uhy02ms5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 16 Nov 2020 07:20:40 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AGC1f30026223;
        Mon, 16 Nov 2020 07:20:39 -0500
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34uhy02mra-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 16 Nov 2020 07:20:39 -0500
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AGCC8Y5009575;
        Mon, 16 Nov 2020 12:20:37 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma05fra.de.ibm.com with ESMTP id 34t6v891pw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 16 Nov 2020 12:20:37 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AGCKYPA6750948
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 16 Nov 2020 12:20:34 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4627B11C04C;
        Mon, 16 Nov 2020 12:20:34 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 326BA11C04A;
        Mon, 16 Nov 2020 12:20:34 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 16 Nov 2020 12:20:34 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id E8011E0367; Mon, 16 Nov 2020 13:20:33 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Collin Walling <walling@linux.ibm.com>
Subject: [GIT PULL 1/2] KVM: s390: pv: Mark mm as protected after the set
 secure parameters and improve cleanup
Date: Mon, 16 Nov 2020 13:20:32 +0100
Message-Id: <20201116122033.382372-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201116122033.382372-1-borntraeger@de.ibm.com>
References: <20201116122033.382372-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-16_03:2020-11-13,2020-11-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 spamscore=0 mlxlogscore=999 priorityscore=1501 malwarescore=0
 impostorscore=0 bulkscore=0 mlxscore=0 clxscore=1015 adultscore=0
 phishscore=0 suspectscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2011160069
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

We can only have protected guest pages after a successful set secure
parameters call as only then the UV allows imports and unpacks.

By moving the test we can now also check for it in s390_reset_acc()
and do an early return if it is 0.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Fixes: 29b40f105ec8 ("KVM: s390: protvirt: Add initial vm and cpu lifecycle handling")
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 arch/s390/kvm/pv.c       | 3 ++-
 arch/s390/mm/gmap.c      | 2 ++
 3 files changed, 5 insertions(+), 2 deletions(-)

```
#### [GIT PULL] vhost,vdpa: fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11908463
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D561CC4742C
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 13:15:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7512A2223D
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 13:15:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WOUzmNZ2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728675AbgKPNOd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 08:14:33 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:46102 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728017AbgKPNOc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 08:14:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605532470;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=bcklXraRLL6YuQnGUW+mYhCFhDJ3s3DEvlUM79PK4ZQ=;
        b=WOUzmNZ28cAjLHIltbASIsz4OTsABrafVH6b2Xv68AUq0weDd6udm26u37997q51YuYZvC
        tKTbo1p7UB8TXJTS4evAxEOJmJsGWGcbhdy+MsiSIlNX8xL1ja7X5iVFKHKr9BAxxvTtFi
        ISYqSnLXxuVn1ywWp2AEaBvC96RL/rg=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-462-NJoeVSMdN7qdmjcPj7Nf4Q-1; Mon, 16 Nov 2020 08:14:28 -0500
X-MC-Unique: NJoeVSMdN7qdmjcPj7Nf4Q-1
Received: by mail-wm1-f70.google.com with SMTP id s3so10273135wmj.6
        for <kvm@vger.kernel.org>; Mon, 16 Nov 2020 05:14:28 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=bcklXraRLL6YuQnGUW+mYhCFhDJ3s3DEvlUM79PK4ZQ=;
        b=G3K+L+Dv1jvf7xl7R2SnwV3uRFT1IrzHTDI2lRWLWFTiSA6o3h92qesf49F4oJblk2
         2xiSrNIow6fu9fOsjWdc+G4HzcpyJIzMs79JBKSXE4Ob51PpO7SOGEYvWtn7d6STTl9v
         PA7EHEKYnItq+F0UE8C0TWKJe5b/TvV6KGPDLTp0+PynGJaujfSV4FCjWuuXuu3Y+vJf
         MBdh9nMPjqqoL0j6roN+QhvhsCC5X4alrm6TnABcBgWDL4c94tplOMhS6g0LYRurO2Tm
         3ozyBgxNy5JIHQO2SDeAv+nezxv9rKZnxtG5Nqn8UHDkIF/0htO4j75Z4K4Ih9MAyv4h
         EfrQ==
X-Gm-Message-State: AOAM532w6XQOwlGu6vBY1cVmnp3WwgUn10/uzziJOOZokKfQNh09oK3o
        gCASZJuHofR2AFKSGa0UjlBaWNWjhlp57j5yBIFdX4kg+L9VMUIFWKBf2yfMcA2wf5a97fpKby+
        UxIUKZIpTTOZc
X-Received: by 2002:a1c:6002:: with SMTP id u2mr14508769wmb.29.1605532467574;
        Mon, 16 Nov 2020 05:14:27 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJyoKOhCtfX4RQPxreiVjgYctq5k6WupqM3uofRLxRDRD1VbWHuNBhZz0uRXMRsQybcwkP1lsQ==
X-Received: by 2002:a1c:6002:: with SMTP id u2mr14508747wmb.29.1605532467415;
        Mon, 16 Nov 2020 05:14:27 -0800 (PST)
Received: from redhat.com ([147.161.8.56])
        by smtp.gmail.com with ESMTPSA id
 e5sm21249161wrs.84.2020.11.16.05.14.22
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 16 Nov 2020 05:14:26 -0800 (PST)
Date: Mon, 16 Nov 2020 08:14:20 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jasowang@redhat.com, lkp@intel.com, lvivier@redhat.com,
        michael.christie@oracle.com, mst@redhat.com, rdunlap@infradead.org,
        sfr@canb.auug.org.au, stefanha@redhat.com
Subject: [GIT PULL] vhost,vdpa: fixes
Message-ID: <20201116081420-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 0c86d774883fa17e7c81b0c8838b88d06c2c911e:

  vdpasim: allow to assign a MAC address (2020-10-30 04:04:35 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to efd838fec17bd8756da852a435800a7e6281bfbc:

  vhost scsi: Add support for LUN resets. (2020-11-15 17:30:55 -0500)

----------------------------------------------------------------
vhost,vdpa: fixes

Fixes all over the place, most notably vhost scsi IO error fixes.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Laurent Vivier (1):
      vdpasim: fix "mac_pton" undefined error

Mike Christie (5):
      vhost: add helper to check if a vq has been setup
      vhost scsi: alloc cmds per vq instead of session
      vhost scsi: fix cmd completion race
      vhost scsi: add lun parser helper
      vhost scsi: Add support for LUN resets.

Stephen Rothwell (1):
      swiotlb: using SIZE_MAX needs limits.h included

 drivers/vdpa/Kconfig    |   1 +
 drivers/vhost/scsi.c    | 397 ++++++++++++++++++++++++++++++++++--------------
 drivers/vhost/vhost.c   |   6 +
 drivers/vhost/vhost.h   |   1 +
 include/linux/swiotlb.h |   1 +
 5 files changed, 289 insertions(+), 117 deletions(-)
```
#### [PATCH] kvm/i386: Set proper nested state format for SVM
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11909781
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6A73BC63697
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 17:03:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0011F20E65
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 17:03:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ER0ESuLF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732517AbgKPRCe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 12:02:34 -0500
Received: from mail-dm6nam11on2051.outbound.protection.outlook.com
 ([40.107.223.51]:16737
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732502AbgKPRCe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 12:02:34 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=XEil32iAGq+WuwvOY8EzR5lTZHzVQrpndhhU00DffZsIsoYIvPMug7YF3+u3gjQyoOYx1wDIho49YZW7zqR2KZZNaoBxZ1GiVkTINhmVXdjyxEDrI0vqyvFWQAoGEHIhdwivpiPEUhPLS4G/fnRqDHmmmgxSXO/6L1VbzES4ejI9fEVQzCZAZfgQv+piX6E7CmBb1SpNWxlFBGWuNyv9elSnbFJCHL5kTlIRLP9Z6rgaCCV6P1XRrwlGWM0AakvXk3+G637GmiA1gxED2QfMGPbZCgGaJ5OHr6ag3MUvGp87zw9XKCKCX90gzw4Zqbdo7H49ufMV3gy7NiAfatuiQA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5HwLxd1NROFUCuu7wqamBzkODr/KJ5H+JQDwMutOx44=;
 b=RGoKdAtso+Ihiv2d9bJnN8cH3+TIjueNmuSoYdTXg34lRG457SvUlH+skFG9KdrX8KVjxVmMJ4ZBgxk59BDnMpGzD2Yzu9ajMs4tEn6U1yfmKp+HkrwTx0fbr/KYWdcnYtkTs8DfZqwWEVi6DOUFLB4a9QydJnv6g86zGMC114/Y5gimnkAICgk8VCtMd0ZvsBXOee0Y+bPE7SkkO1qYKwOP5WiSm3F+JsVZZ4OF0TVzaJxu8pgFTvE8YMXzs8s9ryjKdrKNn62X1jKT7NowDdM+zn4bZ2Uve0wz36QnRDjQEALeb6HivItO73nKDhYRso5RicwfpqiuYmHKJ3TTxw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5HwLxd1NROFUCuu7wqamBzkODr/KJ5H+JQDwMutOx44=;
 b=ER0ESuLF5uHqI/RNTM3O+lHYg+yhhGHL6bARCEBoMLStilAmuk/65ND3xnpOazOKh61H670AO6aycdVGZLkKZVzRt5FQFEBj9JNTYULgQGE4KyHxOMRizJfoC+egqu2PwfiXsihb1+ocVHBR1Cupj2Ply6j3LPwZp+GVXZX+IMk=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4603.namprd12.prod.outlook.com (2603:10b6:5:166::11) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3564.28; Mon, 16 Nov 2020 17:02:31 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::dcda:c3e8:2386:e7fe]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::dcda:c3e8:2386:e7fe%12]) with mapi id 15.20.3564.028; Mon, 16 Nov
 2020 17:02:31 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <richard.henderson@linaro.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH] kvm/i386: Set proper nested state format for SVM
Date: Mon, 16 Nov 2020 11:02:20 -0600
Message-Id: 
 <fe53d00fe0d884e812960781284cd48ae9206acc.1605546140.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR10CA0021.namprd10.prod.outlook.com (2603:10b6:4:2::31)
 To DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR10CA0021.namprd10.prod.outlook.com (2603:10b6:4:2::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3564.28 via Frontend
 Transport; Mon, 16 Nov 2020 17:02:30 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 875cb946-18a7-4e67-76ee-08d88a5167cf
X-MS-TrafficTypeDiagnostic: DM6PR12MB4603:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB460391EDD637742E792ADBF9ECE30@DM6PR12MB4603.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 fPKmZAgwSpKl6m6q8IK5TGQNMQSgMW0LIC3Pvh/PxLcqOJ11JrMRZkcwqzXunSeEYbbjC6TAqPQf5rFFP3A9HDHzz7oxCFKjoeuyIU1mu8rfj6sV3r1Vv3OErJEORhwsct6GpzuUtQlGpdFN52wc6UMT9euzq3QQyqKwr0YXrSWgHcfPKap1f1aPLeuXBSP0gyY6PesvlLNi52W6npcxJcHQCkt8632A7vSj27+W6eJvJhG0pgk45+xowJ767AAgbe4jijgq39F550GCmVIKXUrCRtyNIPnLxKacT47UutBDHF25yue/q9D+wh9YDRIT
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(136003)(346002)(376002)(366004)(39860400002)(2906002)(16526019)(26005)(86362001)(478600001)(7696005)(2616005)(956004)(186003)(54906003)(5660300002)(66476007)(36756003)(83380400001)(52116002)(6486002)(8936002)(66556008)(316002)(66946007)(6666004)(4326008)(8676002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Ama0HmYMx3TxCYmLVioRy6yghQrO8Xn+frrRoeIIvot4SCaE7tZdfnn/kc6IVw8hCGRRSoX2S8H2sjo7sYLwnJgEOEc62zbhWXKs6DJE1HPfRQrrpEKEChn5EkYAh4Op/dTo6E8EFoTW9uqAgsooN695xMknaqQ9GjaaYGf29Zg+dZQHOVcbSDbTM7mhF5ubwN74uPHI4IdM2TlvjwWcblQN6jMFTr+/6GE/7ArgiS7flktBBiNFlCm0gUh/iISo1nvcrHlgrNhXG0Rqin++/6ypeYorggYLbDLCcNtE6AvKlgyTRTp864Ngjs8BWIiGN5VCF8x4zIRrkSnzb6OixlmLQMhNb2TDdePN3BkKkbcAXHAKacKOEMuCunC5UxGM4ritZvoWW49pXuFwrMaHB4Etyw8cT9CojG8r4CYOp144Fjr89pB0Qp8a6GcL+A2JQNTeIrIFOAFBpkDgQRyNQXKXPnyOzWjDPuqq1NNs9kX7wqEs3hQoJ0Byy+WNWDaH6ssjU9gy/QDXB1lOT1iqqtc4BD9H676SSU24eNNkfzH4hmqhwG1pk7BLLkAMkrzms1yqOIYwcAYwM4ZrJKiSfvCrwG+wTy0ygdPj/QvKwSAfDOmMNLsuLVj7I+dM4nudzwMtkeRkCPxDEp4N+6igCQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 875cb946-18a7-4e67-76ee-08d88a5167cf
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 16 Nov 2020 17:02:31.3787
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 tvA3bHV6Q6lZsRygMJmsxMSl702ZKa5vXFedCxONPDJAOeAEJQonPOQI/2ikTLyv2blqiX3S2DudHGeiAoaLgg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4603
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Currently, the nested state format is hardcoded to VMX. This will result
in kvm_put_nested_state() returning an error because the KVM SVM support
checks for the nested state to be KVM_STATE_NESTED_FORMAT_SVM. As a
result, kvm_arch_put_registers() errors out early.

Update the setting of the format based on the virtualization feature:
  VMX - KVM_STATE_NESTED_FORMAT_VMX
  SVM - KVM_STATE_NESTED_FORMAT_SVM

Also, fix the code formatting while at it.

Fixes: b16c0e20c7 ("KVM: add support for AMD nested live migration")
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Richard Henderson <richard.henderson@linaro.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 target/i386/kvm.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH v3 1/4] KVM: selftests: Factor out guest mode code
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11908361
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A6BB3C84512
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:38:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B87C2227F
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:38:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LvW0SlJ0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730030AbgKPMT6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 07:19:58 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51990 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727027AbgKPMT5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 07:19:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605529193;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=m2AuRZIZPSyj7OBOSQhXvDj7HBZVz1DqcYgooI8nn5c=;
        b=LvW0SlJ0SyKyCb28dnvr9HG+ehKb/xdaZF/iT/l9+Zv7YnMQNwefckTUkNXsYeTbd0lfxh
        NyfAsGc4qyg4PBNw/soh3EvJLg9gu4gaEDZQbtmCtweQH3QTq0FQ1Pldiutcef7BwwKSsj
        88SMtyIciKfmUB6pTjruLVukTSjWlSM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-466-Kq_ZPWnxOki8JFTWs9Q1gg-1; Mon, 16 Nov 2020 07:19:52 -0500
X-MC-Unique: Kq_ZPWnxOki8JFTWs9Q1gg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 11A4D100F946;
        Mon, 16 Nov 2020 12:19:51 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.122])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1856860BF1;
        Mon, 16 Nov 2020 12:19:48 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH v3 1/4] KVM: selftests: Factor out guest mode code
Date: Mon, 16 Nov 2020 13:19:39 +0100
Message-Id: <20201116121942.55031-2-drjones@redhat.com>
In-Reply-To: <20201116121942.55031-1-drjones@redhat.com>
References: <20201116121942.55031-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

demand_paging_test, dirty_log_test, and dirty_log_perf_test have
redundant guest mode code. Factor it out.

Also, while adding a new include, remove the ones we don't need.

Reviewed-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/demand_paging_test.c        | 107 ++++-----------
 .../selftests/kvm/dirty_log_perf_test.c       | 121 +++++------------
 tools/testing/selftests/kvm/dirty_log_test.c  | 125 ++++++------------
 .../selftests/kvm/include/guest_modes.h       |  21 +++
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 ++++++++++
 6 files changed, 189 insertions(+), 257 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c

```
#### [PATCH] KVM: SVM: check CR4 changes against vcpu->arch
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11910269
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 861A1C2D0A3
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:12:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 417412078E
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:12:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OXpaTSlR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731100AbgKPSLd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 13:11:33 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:25972 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730775AbgKPSLc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 13:11:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605550292;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xf1LJn8hGte4D+k0k0YeB9oW653XA/c4TK7Y8k7TCcw=;
        b=OXpaTSlRQlisd2LLVGYNkbeTRarapVHiGg/pwK38QgipXP71zdcFTDtZc/3PLvX+/sIZZj
        8iPX0xPwG15wdyITpNphcCjrCv4mUcMHVlE0Z1egLNAuoLNN7d8IRPOpjNbaSmTQTgz20p
        zgw6J0zz5uA+Rv3Hy848f5/Xd8b+Myg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-79-VP9hCMv8MP6yJjyKGGRZHw-1; Mon, 16 Nov 2020 13:11:28 -0500
X-MC-Unique: VP9hCMv8MP6yJjyKGGRZHw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3C8571084D72;
        Mon, 16 Nov 2020 18:11:27 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E0D8A5C1CF;
        Mon, 16 Nov 2020 18:11:26 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>
Subject: [PATCH] KVM: SVM: check CR4 changes against vcpu->arch
Date: Mon, 16 Nov 2020 13:11:26 -0500
Message-Id: <20201116181126.2008838-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Similarly to what vmx/vmx.c does, use vcpu->arch.cr4 to check if CR4
bits PGE, PKE and OSXSAVE have changed.  When switching between VMCB01
and VMCB02, CPUID has to be adjusted every time if CR4.PKE or CR4.OSXSAVE
change; without this patch, instead, CR4 would be checked against the
previous value for L2 on vmentry, and against the previous value for
L1 on vmexit, and CPUID would not be updated.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH 01/67] x86/cpufeatures: Add synthetic feature flag for TDX (in host)
##### From: isaku.yamahata@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: isaku.yamahata@intel.com
X-Patchwork-Id: 11910311
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 789ECC2D0A3
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:28:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 395AB24671
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:28:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732594AbgKPS1y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 13:27:54 -0500
Received: from mga06.intel.com ([134.134.136.31]:20622 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731107AbgKPS1y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 13:27:54 -0500
IronPort-SDR: 
 7mHO8jlN6Dn0HGliqXULyPj81wm/4iYjeFfNDUob6RnUJCM9UiAsW00f62CtrP0ai/HrRh3o0y
 0WKH4G9BuseA==
X-IronPort-AV: E=McAfee;i="6000,8403,9807"; a="232409990"
X-IronPort-AV: E=Sophos;i="5.77,483,1596524400";
   d="scan'208";a="232409990"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Nov 2020 10:27:52 -0800
IronPort-SDR: 
 AYXSg0NKU9zQuWlZqFPWBZjv+zY822RMK8oxUZs0JuX8ax32iouwi6HYMmbi9MT8AKwv8SHWZ6
 Dj0iZHxmX9dA==
X-IronPort-AV: E=Sophos;i="5.77,483,1596524400";
   d="scan'208";a="400527729"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Nov 2020 10:27:52 -0800
From: isaku.yamahata@intel.com
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, x86@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: isaku.yamahata@intel.com, isaku.yamahata@gmail.com,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [RFC PATCH 01/67] x86/cpufeatures: Add synthetic feature flag for TDX
 (in host)
Date: Mon, 16 Nov 2020 10:25:46 -0800
Message-Id: 
 <9a74fb153bc21dc5cac46e84913b88182f216d1b.1605232743.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1605232743.git.isaku.yamahata@intel.com>
References: <cover.1605232743.git.isaku.yamahata@intel.com>
In-Reply-To: <cover.1605232743.git.isaku.yamahata@intel.com>
References: <cover.1605232743.git.isaku.yamahata@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v12 01/15] iommu: Introduce attach/detach_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11908169
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9B79EC61DD8
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4225922265
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:07:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="g4niAzQ/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729301AbgKPKnp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 05:43:45 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:21495 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728707AbgKPKno (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 05:43:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605523422;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=LrTV0RIEKcY2jhDkMqIw4KTQQ1U/7NxXelAKS27XTjU=;
        b=g4niAzQ/Mjc7RGIXMDpn/3Zx34g7uwToDXIXGlr8kpfLxJtj8tUINGiE6WT8kM+OjCFmUr
        xfrHYRHZdmuawUaEzzvKKUwwJtUfQA5xPVGIn5Yii31FYRJX1nr70mV2sbgpt+2t74EENZ
        dXFQTjDEr0dM+yKq2QpsV61oHvO/92k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-377-7zBCR7tlNGGP5rXVZZWErQ-1; Mon, 16 Nov 2020 05:43:38 -0500
X-MC-Unique: 7zBCR7tlNGGP5rXVZZWErQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4248C10074CE;
        Mon, 16 Nov 2020 10:43:35 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-230.ams2.redhat.com
 [10.36.113.230])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9FB075C716;
        Mon, 16 Nov 2020 10:43:30 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com, alex.williamson@redhat.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com, tn@semihalf.com,
        nicoleotsuka@gmail.com
Subject: [PATCH v12 01/15] iommu: Introduce attach/detach_pasid_table API
Date: Mon, 16 Nov 2020 11:43:02 +0100
Message-Id: <20201116104316.31816-2-eric.auger@redhat.com>
In-Reply-To: <20201116104316.31816-1-eric.auger@redhat.com>
References: <20201116104316.31816-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on the guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/Intel terminology) while the host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set/unset the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reported-by: kernel test robot <lkp@intel.com>
---

v11 -> v12:
- add argsz, name the union
---
 drivers/iommu/iommu.c      | 67 ++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h      | 21 ++++++++++++
 include/uapi/linux/iommu.h | 54 ++++++++++++++++++++++++++++++
 3 files changed, 142 insertions(+)

```
#### [PATCH v11 01/13] vfio: VFIO_IOMMU_SET_PASID_TABLE
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11908243
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 159D5C4742C
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:31:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D3A9204EF
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:31:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LLvqTUD+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729284AbgKPLBA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 06:01:00 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:46362 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729347AbgKPLBA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 06:01:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605524459;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=INg+bLsiYU9C1vucl39JD+cerJHDcpbNC+/F3Yla0Ho=;
        b=LLvqTUD+ZSVZ1YSLfHDDCwNgf8xPh9ugHdCHb7+kaN/+Vv9cHMCzIX7YZTcHj7llP6t4Bt
        8xA017g9KnfSbC5RPDQUEp6Pc5Pcidaz+j1urxIWNaJhwYg13zqC+RWMuxz+gcPgqD+rbr
        6obVnU+O0vUPGy9+CdIvXF0gd9L1k0g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-520-2swPiuBXOXKqstqVjmBTwA-1; Mon, 16 Nov 2020 06:00:54 -0500
X-MC-Unique: 2swPiuBXOXKqstqVjmBTwA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6221164179;
        Mon, 16 Nov 2020 11:00:52 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-230.ams2.redhat.com
 [10.36.113.230])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D15B75C716;
        Mon, 16 Nov 2020 11:00:47 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com,
        alex.williamson@redhat.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com, tn@semihalf.com,
        nicoleotsuka@gmail.com, yuzenghui@huawei.com
Subject: [PATCH v11 01/13] vfio: VFIO_IOMMU_SET_PASID_TABLE
Date: Mon, 16 Nov 2020 12:00:18 +0100
Message-Id: <20201116110030.32335-2-eric.auger@redhat.com>
In-Reply-To: <20201116110030.32335-1-eric.auger@redhat.com>
References: <20201116110030.32335-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Liu, Yi L" <yi.l.liu@linux.intel.com>

This patch adds an VFIO_IOMMU_SET_PASID_TABLE ioctl
which aims to pass the virtual iommu guest configuration
to the host. This latter takes the form of the so-called
PASID table.

Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reported-by: kernel test robot <lkp@intel.com>
---
v11 -> v12:
- use iommu_uapi_set_pasid_table
- check SET and UNSET are not set simultaneously (Zenghui)

v8 -> v9:
- Merge VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE into a single
  VFIO_IOMMU_SET_PASID_TABLE ioctl.

v6 -> v7:
- add a comment related to VFIO_IOMMU_DETACH_PASID_TABLE

v3 -> v4:
- restore ATTACH/DETACH
- add unwind on failure

v2 -> v3:
- s/BIND_PASID_TABLE/SET_PASID_TABLE

v1 -> v2:
- s/BIND_GUEST_STAGE/BIND_PASID_TABLE
- remove the struct device arg
---
 drivers/vfio/vfio_iommu_type1.c | 65 +++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       | 19 ++++++++++
 2 files changed, 84 insertions(+)

```
#### [PATCH v2] drivers/virt: vmgenid: add vm generation id driverThread-Topic: [PATCH v2] drivers/virt: vmgenid: add vm generation id driver
##### From: "Catangiu, Adrian Costin" <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Catangiu, Adrian Costin" <acatan@amazon.com>
X-Patchwork-Id: 11909651
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B6472C4742C
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 15:35:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6656E221F9
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 15:35:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="bBXxFr98"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731307AbgKPPfK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 10:35:10 -0500
Received: from smtp-fw-9101.amazon.com ([207.171.184.25]:15925 "EHLO
        smtp-fw-9101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730925AbgKPPfJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 10:35:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1605540905; x=1637076905;
  h=from:to:cc:subject:date:message-id:content-id:
   mime-version:content-transfer-encoding;
  bh=IVRXiVf5gxb/g5OZ2zSe3Lwa7wiWugG+Gg3i/98JqUQ=;
  b=bBXxFr98RYUA6xo9svNg4TTgK2croibUUAzhxAnACTV62LeMovoRTbqO
   XXRbn8yg2YjT8mIoodH+xTC56SpGEjRQ3yrbz5VH3PTaFjVjxIzL5TnIW
   BhDqVWU/CUNzZ5vmDreHu3Vq+tmTaZ1AhduhdCUvkeV2Kyip+5jzG9RK1
   g=;
X-IronPort-AV: E=Sophos;i="5.77,482,1596499200";
   d="scan'208";a="87555932"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9101.sea19.amazon.com with ESMTP;
 16 Nov 2020 15:34:51 +0000
Received: from EX13D07EUB004.ant.amazon.com
 (pdx1-ws-svc-p6-lb9-vlan3.pdx.amazon.com [10.236.137.198])
        by email-inbound-relay-2b-4ff6265a.us-west-2.amazon.com (Postfix) with
 ESMTPS id 3E1ACA0678;
        Mon, 16 Nov 2020 15:34:48 +0000 (UTC)
Received: from EX13D08EUB004.ant.amazon.com (10.43.166.158) by
 EX13D07EUB004.ant.amazon.com (10.43.166.234) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 16 Nov 2020 15:34:46 +0000
Received: from EX13D08EUB004.ant.amazon.com ([10.43.166.158]) by
 EX13D08EUB004.ant.amazon.com ([10.43.166.158]) with mapi id 15.00.1497.006;
 Mon, 16 Nov 2020 15:34:46 +0000
From: "Catangiu, Adrian Costin" <acatan@amazon.com>
To: "Graf (AWS), Alexander" <graf@amazon.de>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        "Jason A. Donenfeld" <Jason@zx2c4.com>,
        Jann Horn <jannh@google.com>
CC: Willy Tarreau <w@1wt.eu>,
        "MacCarthaigh, Colm" <colmmacc@amazon.com>,
        "Andy Lutomirski" <luto@kernel.org>,
        "Theodore Y. Ts'o" <tytso@mit.edu>,
        "Eric Biggers" <ebiggers@kernel.org>,
        "open list:DOCUMENTATION" <linux-doc@vger.kernel.org>,
        kernel list <linux-kernel@vger.kernel.org>,
        "Woodhouse, David" <dwmw@amazon.co.uk>,
        "bonzini@gnu.org" <bonzini@gnu.org>,
        "Singh, Balbir" <sblbir@amazon.com>,
        "Weiss, Radu" <raduweis@amazon.com>,
        "oridgar@gmail.com" <oridgar@gmail.com>,
        "ghammer@redhat.com" <ghammer@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        "Qemu Developers" <qemu-devel@nongnu.org>,
        KVM list <kvm@vger.kernel.org>,
        "Michal Hocko" <mhocko@kernel.org>,
        "Rafael J. Wysocki" <rafael@kernel.org>,
        "Pavel Machek" <pavel@ucw.cz>,
        Linux API <linux-api@vger.kernel.org>,
        "mpe@ellerman.id.au" <mpe@ellerman.id.au>,
        linux-s390 <linux-s390@vger.kernel.org>,
        "areber@redhat.com" <areber@redhat.com>,
        "Pavel Emelyanov" <ovzxemul@gmail.com>,
        Andrey Vagin <avagin@gmail.com>,
        "Mike Rapoport" <rppt@kernel.org>,
        Dmitry Safonov <0x7f454c46@gmail.com>,
        "Pavel Tikhomirov" <ptikhomirov@virtuozzo.com>,
        "gil@azul.com" <gil@azul.com>,
        "asmehra@redhat.com" <asmehra@redhat.com>,
        "dgunigun@redhat.com" <dgunigun@redhat.com>,
        "vijaysun@ca.ibm.com" <vijaysun@ca.ibm.com>
Subject: [PATCH v2] drivers/virt: vmgenid: add vm generation id driver
Thread-Topic: [PATCH v2] drivers/virt: vmgenid: add vm generation id driver
Thread-Index: AQHWvC4DvA631jYeWky3kvXgY6iRJA==
Date: Mon, 16 Nov 2020 15:34:46 +0000
Message-ID: <3E05451B-A9CD-4719-99D0-72750A304044@amazon.com>
Accept-Language: en-US
Content-Language: en-GB
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-ms-exchange-messagesentrepresentingtype: 1
x-ms-exchange-transport-fromentityheader: Hosted
x-originating-ip: [10.43.164.242]
Content-ID: <9C6FE809E61EEE4C91611B73714F06CE@amazon.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background

The VM Generation ID is a feature defined by Microsoft (paper:
http://go.microsoft.com/fwlink/?LinkId=260709) and supported by
multiple hypervisor vendors.

The feature is required in virtualized environments by apps that work
with local copies/caches of world-unique data such as random values,
uuids, monotonically increasing counters, etc.
Such apps can be negatively affected by VM snapshotting when the VM
is either cloned or returned to an earlier point in time.

The VM Generation ID is a simple concept meant to alleviate the issue
by providing a unique ID that changes each time the VM is restored
from a snapshot. The hw provided UUID value can be used to
differentiate between VMs or different generations of the same VM.

- Problem

The VM Generation ID is exposed through an ACPI device by multiple
hypervisor vendors but neither the vendors or upstream Linux have no
default driver for it leaving users to fend for themselves.

Furthermore, simply finding out about a VM generation change is only
the starting point of a process to renew internal states of possibly
multiple applications across the system. This process could benefit
from a driver that provides an interface through which orchestration
can be easily done.

- Solution

This patch is a driver that exposes a monotonic incremental Virtual
Machine Generation u32 counter via a char-dev FS interface that
provides sync and async VmGen counter updates notifications. It also
provides VmGen counter retrieval and confirmation mechanisms.

The hw provided UUID is not exposed to userspace, it is internally
used by the driver to keep accounting for the exposed VmGen counter.
The counter starts from zero when the driver is initialized and
monotonically increments every time the hw UUID changes (the VM
generation changes).

On each hw UUID change, the new hypervisor-provided UUID is also fed
to the kernel RNG.

This patch builds on top of Or Idgar <oridgar@gmail.com>'s proposal
https://lkml.org/lkml/2018/3/1/498

- Future improvements

Ideally we would want the driver to register itself based on devices'
_CID and not _HID, but unfortunately I couldn't find a way to do that.
The problem is that ACPI device matching is done by
'__acpi_match_device()' which exclusively looks at
'acpi_hardware_id *hwid'.

There is a path for platform devices to match on _CID when _HID is
'PRP0001' - but this is not the case for the Qemu vmgenid device.

Guidance and help here would be greatly appreciated.

- v1 -> v2:

  - expose to userspace a monotonically increasing u32 Vm Gen Counter
    instead of the hw VmGen UUID
  - since the hw/hypervisor-provided 128-bit UUID is not public
    anymore, add it to the kernel RNG as device randomness
  - insert driver page containing Vm Gen Counter in the user vma in
    the driver's mmap handler instead of using a fault handler
  - turn driver into a misc device driver to auto-create /dev/vmgenid
  - change ioctl arg to avoid leaking kernel structs to userspace
  - update documentation
  - various nits (license, unnecessary casting, Kconfig, others)
  - rebase on top of linus latest

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---
 Documentation/virt/vmgenid.rst | 228 ++++++++++++++++++++++++
 drivers/virt/Kconfig           |  17 ++
 drivers/virt/Makefile          |   1 +
 drivers/virt/vmgenid.c         | 390 +++++++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vmgenid.h   |  13 ++
 5 files changed, 649 insertions(+)
 create mode 100644 Documentation/virt/vmgenid.rst
 create mode 100644 drivers/virt/vmgenid.c
 create mode 100644 include/uapi/linux/vmgenid.h

diff --git a/Documentation/virt/vmgenid.rst b/Documentation/virt/vmgenid.rst
new file mode 100644
index 0000000..603e8a5
--- /dev/null
+++ b/Documentation/virt/vmgenid.rst
@@ -0,0 +1,228 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+============
+VMGENID
+============
+
+The VM Generation ID is a feature defined by Microsoft (paper:
+http://go.microsoft.com/fwlink/?LinkId=260709) and supported by
+multiple hypervisor vendors.
+
+The feature is required in virtualized environments by apps that work
+with local copies/caches of world-unique data such as random values,
+uuids, monotonically increasing counters, etc.
+Such apps can be negatively affected by VM snapshotting when the VM
+is either cloned or returned to an earlier point in time.
+
+The VM Generation ID is a simple concept meant to alleviate the issue
+by providing a unique ID that changes each time the VM is restored
+from a snapshot. The hw provided UUID value can be used to
+differentiate between VMs or different generations of the same VM.
+
+The VM Generation ID is exposed through an ACPI device by multiple
+hypervisor vendors. The driver for it lives at
+``drivers/virt/vmgenid.c``
+
+The driver exposes a monotonic incremental Virtual Machine Generation
+u32 counter via a char-dev FS interface that provides sync and async
+VmGen counter updates notifications. It also provides VmGen counter
+retrieval and confirmation mechanisms.
+
+The hw provided UUID is not exposed to userspace, it is internally
+used by the driver to keep accounting for the exposed VmGen counter.
+The counter starts from zero when the driver is initialized and
+monotonically increments every time the hw UUID changes (the VM
+generation changes).
+
+On each hw UUID change, the new UUID is also fed to the kernel RNG.
+
+Driver interface:
+
+``open()``:
+  When the device is opened, a copy of the current Vm-Gen-Id (counter)
+  is associated with the open file descriptor. The driver now tracks
+  this file as an independent *watcher*. The driver tracks how many
+  watchers are aware of the latest Vm-Gen-Id counter and how many of
+  them are *outdated*; outdated being those that have lived through
+  a Vm-Gen-Id change but not yet confirmed the new generation counter.
+
+``read()``:
+  Read is meant to provide the *new* VM generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date - until HW vm gen id
+  changes - at which point the new counter is provided/returned.
+  Nonblocking ``read()`` uses ``EAGAIN`` to signal that there is no
+  *new* counter value available. The generation counter is considered
+  *new* for each open file descriptor that hasn't confirmed the new
+  value, following a generation change. Therefore, once a generation
+  change takes place, all ``read()`` calls will immediately return the
+  new generation counter and will continue to do so until the
+  new value is confirmed back to the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  ``sizeof(unsigned)`` in size.
+
+``write()``:
+  Write is used to confirm the up-to-date Vm Gen counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` confirms the up-to-date counter back to
+  the driver.
+  Partial writes are not allowed - write buffer should be exactly
+  ``sizeof(unsigned)`` in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for tracking count of open file
+  descriptors that haven't acknowledged a generation counter update.
+  This is exposed through two IOCTLs:
+
+  - VMGENID_GET_OUTDATED_WATCHERS: immediately returns the number of
+    *outdated* watchers - number of file descriptors that were open
+    during a VM generation change, and which have not yet confirmed the
+    new generation counter.
+  - VMGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    watchers, or if a ``timeout`` argument is provided, until the
+    timeout expires.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date copy of the VM generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections - see examples.
+
+``close()``:
+  Removes the file descriptor as a Vm generation counter watcher.
+
+Example application workflows
+-----------------------------
+
+1) Watchdog thread simplified example::
+
+	void watchdog_thread_handler(int *thread_active)
+	{
+		unsigned genid;
+		int fd = open("/dev/vmgenid", O_RDWR | O_CLOEXEC, S_IRUSR | S_IWUSR);
+
+		do {
+			// read new gen ID - blocks until VM generation changes
+			read(fd, &genid, sizeof(genid));
+
+			// because of VM generation change, we need to rebuild world
+			reseed_app_env();
+
+			// confirm we're done handling gen ID update
+			write(fd, &genid, sizeof(genid));
+		} while (atomic_read(thread_active));
+
+		close(fd);
+	}
+
+2) ASYNC simplified example::
+
+	void handle_io_on_vmgenfd(int vmgenfd)
+	{
+		unsigned genid;
+
+		// because of VM generation change, we need to rebuild world
+		reseed_app_env();
+
+		// read new gen ID - we need it to confirm we've handled update
+		read(fd, &genid, sizeof(genid));
+
+		// confirm we're done handling the gen ID update
+		write(fd, &genid, sizeof(genid));
+	}
+
+	int main() {
+		int epfd, vmgenfd;
+		struct epoll_event ev;
+
+		epfd = epoll_create(EPOLL_QUEUE_LEN);
+
+		vmgenfd = open("/dev/vmgenid",
+		               O_RDWR | O_CLOEXEC | O_NONBLOCK,
+		               S_IRUSR | S_IWUSR);
+
+		// register vmgenid for polling
+		ev.events = EPOLLIN;
+		ev.data.fd = vmgenfd;
+		epoll_ctl(epfd, EPOLL_CTL_ADD, vmgenfd, &ev);
+
+		// register other parts of your app for polling
+		// ...
+
+		while (1) {
+			// wait for something to do...
+			int nfds = epoll_wait(epfd, events,
+				MAX_EPOLL_EVENTS_PER_RUN,
+				EPOLL_RUN_TIMEOUT);
+			if (nfds < 0) die("Error in epoll_wait!");
+
+			// for each ready fd
+			for(int i = 0; i < nfds; i++) {
+				int fd = events[i].data.fd;
+
+				if (fd == vmgenfd)
+					handle_io_on_vmgenfd(vmgenfd);
+				else
+					handle_some_other_part_of_the_app(fd);
+			}
+		}
+
+		return 0;
+	}
+
+3) Mapped memory polling simplified example::
+
+	/*
+	 * app/library function that provides cached secrets
+	 */
+	char * safe_cached_secret(app_data_t *app)
+	{
+		char *secret;
+		volatile unsigned *const genid_ptr = get_vmgenid_mapping(app);
+	again:
+		secret = __cached_secret(app);
+
+		if (unlikely(*genid_ptr != app->cached_genid)) {
+			// rebuild world then confirm the genid update (thru write)
+			rebuild_caches(app);
+
+			app->cached_genid = *genid_ptr;
+			ack_vmgenid_update(app);
+
+			goto again;
+		}
+
+		return secret;
+	}
+
+4) Orchestrator simplified example::
+
+	/*
+	 * orchestrator - manages multiple apps and libraries used by a service
+	 * and tries to make sure all sensitive components gracefully handle
+	 * VM generation changes.
+	 * Following function is called on detection of a VM generation change.
+	 */
+	int handle_vmgen_update(int vmgen_fd, unsigned new_gen_id)
+	{
+		// pause until all components have handled event
+		pause_service();
+
+		// confirm *this* watcher as up-to-date
+		write(vmgen_fd, &new_gen_id, sizeof(unsigned));
+
+		// wait for all *others* for at most 5 seconds.
+		ioctl(vmgen_fd, VMGENID_WAIT_WATCHERS, 5000);
+
+		// all apps on the system have rebuilt worlds
+		resume_service();
+	}
```
#### [PATCH] vringh: fix vringh_iov_push_*() documentation
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11909725
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2ED6DC6369E
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 16:17:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E293B20776
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 16:17:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WZFubFPe"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731796AbgKPQRF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 11:17:05 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:50536 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730837AbgKPQRF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 11:17:05 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605543424;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qiy7dPJkCedncPHfKBWxJXduYz70r7PiHicBol/8nJM=;
        b=WZFubFPekZzUGU9ohbLAC0OBXfYL1CAv8IIY2KAj8cksLL6ra4l5FSD2UXUWfim4ViFDIV
        NylBtwMosh3Uojle/AF8SXXZehciGs44510quboY3QaEUQwGivEJwXQ9VBVUxJjfSrCNPC
        enqLO49AQ48mBkOUaovkgNXUHS5vHxw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-466-8l_JSKdHMz-YnAKe83Dk9A-1; Mon, 16 Nov 2020 11:17:00 -0500
X-MC-Unique: 8l_JSKdHMz-YnAKe83Dk9A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 76C151868425;
        Mon, 16 Nov 2020 16:16:59 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-123.ams2.redhat.com
 [10.36.113.123])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E97255C5B0;
        Mon, 16 Nov 2020 16:16:54 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: mst@redhat.com
Cc: virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>
Subject: [PATCH] vringh: fix vringh_iov_push_*() documentation
Date: Mon, 16 Nov 2020 17:16:53 +0100
Message-Id: <20201116161653.102904-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vringh_iov_push_*() functions don't have 'dst' parameter, but have
the 'src' parameter.

Replace 'dst' description with 'src' description.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vringh.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
