#### [PATCH 1/1] KVM: x86: remove unused declaration of kvm_write_tsc()
##### From: Dongli Zhang <dongli.zhang@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongli Zhang <dongli.zhang@oracle.com>
X-Patchwork-Id: 12165931
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70BB1C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 07:06:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E0DD61A1E
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 07:06:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230134AbhCZHF4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 03:05:56 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:58830 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230156AbhCZHFk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Mar 2021 03:05:40 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12Q6ihpK076398;
        Fri, 26 Mar 2021 07:04:09 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-type : mime-version;
 s=corp-2020-01-29; bh=Uknmy1GGIhz70q64h5Hpk/xYkf3jsHD5regb2qmRFWk=;
 b=RoVWyQsSWtWWbxHOAATcZuITYrHf7b5gIRs7nUq+gMEUMrJWWwHsFFIiz7aRD+35vdlR
 J5IE3DvphYORDUiF4ZyWjDtOm9NFzk0I0+MDovFmtCosB0vuUqVu1cu7jCbJd79knoKM
 a6bSOsJATfaLqb+iWJLiYezxIERXRCiEncbyMc5mcv0ye/2mbfKF3kkmbD5mx2cAqEHQ
 oIO8J51vqHsBCE1dq2a4tNdesEDDIJW+WWDOi79jMPAbjl1JGFXwySjvevAZIK+n9saj
 eAFroTqoarlaK6HLBmlG6gifcKQhMpt/FQzLalhmIgKo2YiuWXrmQd4n+dTpYSnPp5ug oA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 37h13hs0qn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 26 Mar 2021 07:04:08 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12Q71ADP067877;
        Fri, 26 Mar 2021 07:04:08 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2105.outbound.protection.outlook.com [104.47.70.105])
        by userp3030.oracle.com with ESMTP id 37h13xb6th-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 26 Mar 2021 07:04:07 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=DLpEmC6rEtd0hiFwF3ivCWokb1BymVqtBcYmFqXSOlCWoVPiR+lCRxYhhsZWexy1pq45NYp4QEb1dRm5qpV55XZS35lmFzIwXoawz8wz/fkBvDYnRNfLRCNIVGdbmNxTnU1ussL11qq4/enzKoLdLcFEDyy3wqyYRzddoV+ZP040Lh3YK3scgGOLGH2CQzKU9raQLN2DlHhpvqCZimNKH9d7UBaCtOLhxbmtyYb2sSPpERJpZZyERnalTDOLutaBf6GLnuzwVrCCawYjIyhIWvccBL5LspoOsP6IpSb9LuFS6KBZ342hM7mrGIzfwMELisjtjDGSA6FF22drAuTW0A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Uknmy1GGIhz70q64h5Hpk/xYkf3jsHD5regb2qmRFWk=;
 b=MnkVpjV0ieBqAgWYg4CZmeDseGAFnb0JKpnNiltgg04ma2SM4jvv/u8R6cbHtYninTP6I35mq10oKoI9EPrE3CP0LSsgjgHK/8JHxxNCec+JXp3v6b9HEFJd918F4JT534T+mVvjP9ldieR037lBXRZkJk8i8d/i47gWae6xsx5jQS6UDRsm9X0yzzffKvgcuuwHbAE8MxbypE2K5X9VgEjyBy1u5DfJxjf9LlHIOSYQ21JrnMG952nN87E/10Y2H9llFP/tHKSMrLA3KGyqlvF1hYlOyUCWu721W8J/CjT32SzwFes5jr77demsUzAUIj6q7r03tOE3I5rgtZMXag==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Uknmy1GGIhz70q64h5Hpk/xYkf3jsHD5regb2qmRFWk=;
 b=Z/6XNgurugESFUzKrI3DGHVFF2Qj3qcAqUH6F+Zl/ucoXsB3UNVPLDf2y23rpe6tgaO+FuwP6dSqbU7fOM9ToUHaJOkxzHc/fE1jcG9gAXs//SCvg+wAtU8WX7JgJQO1G8c2yaj+22oQ90FcrffZBycEi5xeMCjgzXgR8KsFQGg=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from BYAPR10MB2663.namprd10.prod.outlook.com (2603:10b6:a02:a9::20)
 by SJ0PR10MB4541.namprd10.prod.outlook.com (2603:10b6:a03:2db::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.24; Fri, 26 Mar
 2021 07:04:05 +0000
Received: from BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::44f7:1d8f:cc50:48ad]) by BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::44f7:1d8f:cc50:48ad%6]) with mapi id 15.20.3977.030; Fri, 26 Mar 2021
 07:04:05 +0000
From: Dongli Zhang <dongli.zhang@oracle.com>
To: kvm@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/1] KVM: x86: remove unused declaration of kvm_write_tsc()
Date: Fri, 26 Mar 2021 00:03:34 -0700
Message-Id: <20210326070334.12310-1-dongli.zhang@oracle.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [138.3.200.16]
X-ClientProxiedBy: CH2PR12CA0027.namprd12.prod.outlook.com
 (2603:10b6:610:57::37) To BYAPR10MB2663.namprd10.prod.outlook.com
 (2603:10b6:a02:a9::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (138.3.200.16) by
 CH2PR12CA0027.namprd12.prod.outlook.com (2603:10b6:610:57::37) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.26 via Frontend
 Transport; Fri, 26 Mar 2021 07:04:03 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 25c34928-6628-4550-5af4-08d8f02557ae
X-MS-TrafficTypeDiagnostic: SJ0PR10MB4541:
X-Microsoft-Antispam-PRVS: 
 <SJ0PR10MB45418BA8334F4526CB1E074FF0619@SJ0PR10MB4541.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:132;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 j4qolgCGVy8Ywn19Nv1I6KHCnA0XF7EXhXsVKcEBfUB26+2AeJi3cXN2rLk0iXp8LSv3b/VYnZRExQ2TGBf4Nn/uqDydwPe+aDOWBSdMFxYjU83lk/eytaV/gFRkc+ywSsDWn9wOpmGU7ZXE8TQD0aZsBLYeYBrcicd7G3Aj9tZIiQh46V2bQjQBIxspHgJsfsbehuvXFlPXRdx0vYQhoCHQGLuyBz1TiDqwmAOVJ5gub+5BTD/WpaukuEP/ofzzCpLCdxLkNj65sH2AmUEsxNbhHgRkdCRcx976akcvyl5otT1fq/2zt4LtPngVQcj8T62ZuBFGu7Thaa7hpeT7B6hbrI3agbEIjb3q3O4JbQuSNsDebbFUI7pOmV6srrb/9b3xSPEAOUQs2uStTPBuOotmRotLPkZI4KGfRnCrk4S84/iBuYqSwRrRbtTB0bxsDaICDv/8Od5+EQ9vOsv9XSAH3haXeFcMgJJIRmjay+WQ4z1FsBvalJS+WhXG4cVCv9sqGLF4ESC8GP9LS7m2LrSYfAwW8XPyb/URjMBMp5eG0lPHFG2alw3oa2lFYUv2sx2p0aJUPrLIrmrjUZxYaSKis693Iv1CkRe2xXoQPIilnYBz5TrJlc7bBpoFuw4SVNVtZJE1dPbkBNMjfhS+AyiPtA1Bgpzrd7goubn0v47x4S+YzO6sewrAZ/SJcdMv
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BYAPR10MB2663.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(396003)(39860400002)(366004)(376002)(136003)(6512007)(66556008)(66476007)(8676002)(2906002)(86362001)(7416002)(83380400001)(4744005)(26005)(8936002)(66946007)(52116002)(69590400012)(5660300002)(6506007)(956004)(16526019)(478600001)(38100700001)(6486002)(1076003)(6666004)(4326008)(44832011)(36756003)(316002)(2616005)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 JV6RYTtPmkNLF5XoSp9dmCzjgt7unbq1g6i0a8LYteRcD3viahqmMiDtU5GRTMXW+8SyOx8WNGOVomUtBT8uyElC5g6ZnuosCJHTSVlkcAbEWphqkgBBIp0vbSgUFWLywZs4qFCNHHgIE0y3V4ECg7L4PmWt+A0JjdAtOe2o8aVU+uZWVKdwyk9sQHPO80gwQgKTGEKd7X0B9iQIno2X9mH7Puepwp4fe0nsBAjrmaBKKCOyjLtvVcoHoOlwuT1ZS+nwXb/VRC+yDJ9oGSNYKnjV0GeNr40eGq0SNMi2EQV/D9MRSM+ztN6Tb42zfzMln4P9k3V4eph3KM0zismTVwi2bHqXDzdy1AxUizJbGYHjRzRXrq+Q2AYQROZr/VF8rHyHEH5MqfQ/Votle/2ou2ESubtyp0/Jj7zPEm46v23Tt8BdrDzJ3B9G6SySLJmMLUgASCfUOvG2gPXXYP9nM44DQ7X89OZPbf6KThcGWFTiwlqedB2PM/iEGH3VETdMRlbk42pFipgLMRuXwEPy8GYhRm8y7wBJAyDgMKHlLxj9oTlLD1InkO7strqG9Mn9UZcIFtfN7/p7rKqW1WQTmSgr/qk7wiSQwIVGNUnCQRXjArNUZPXu+ha5qr+TpnR+QDrOFXwWNDrv+F/MOaD102+FRFUgIGzCQ2cIK7Q6B/n5FJaP5IrVjQbdylYfHcwDghEq4iDncvtYZKESeYyH2BQIkpsqRNnburDBhh6EgLrJgfEHRHfq03hSavF9exXcFeubhF0n4ERa1M9rCmM/sK6FTao0PwXzd+xR2ADQDPO0D57Vdd/hq0x6WDW1Fdg+BBtprPI5j4poynjokl/7xq3Vt4Fk7/ZxnPMOxP/hUR8Suud2zokalvApW+xDo3WrJyJ2xnD83OHPbaKVXOkYhxguV0UvJG4KhUhm101elISA/Q3O4LV8fqbimbeyiR2FCMf09wBPdL46ATDUpBtiw0HSvP1UoTnmwLzVmAICElxt6RqWNsInObDbDtDX5aiuM0RufyGW0jARpfiN4ZdVvVTkCrWhBSXRKkFM5/AVHjY4THZJe0VlDAgi/2x4Sa9gr9fazldJGTGn0ne5FIQaUnbENHgvPYx1sePFsiVl1YKFgYjuSMZm6xts4Fb2rwkQkEVv8+8qYq8GaidVgc760KzqMtrMFqYLyOSftbJHudmGmq0JOIrc0mn4UwH+ziOpgzqLaBP16XiqhHciv1I8lId/2zgEXKs3k+q8fRhiuJd8/frwd0hkiHjuTFQ1WmdrPkv7tx+Gcj/aIzffSRVB/bsc8hoHpc6XeIjpPH63Mv3358uZXh9UEyDYVGM65ZJM
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 25c34928-6628-4550-5af4-08d8f02557ae
X-MS-Exchange-CrossTenant-AuthSource: BYAPR10MB2663.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Mar 2021 07:04:05.0344
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 WRjYgr+PCTdoVvrSXw0GLlmXgzhptd0wtQIKhQww+DZW2+mGZq2zIB6JOzsw5uAipNNVqif20k52Otx7LTBpgQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SJ0PR10MB4541
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9934
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 mlxscore=0 bulkscore=0
 spamscore=0 mlxlogscore=999 suspectscore=0 adultscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103250000
 definitions=main-2103260048
X-Proofpoint-GUID: UYyGnH-fHR_0IQOTgEN6HWyewcHC9Kfo
X-Proofpoint-ORIG-GUID: UYyGnH-fHR_0IQOTgEN6HWyewcHC9Kfo
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9934
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 mlxscore=0
 spamscore=0 impostorscore=0 malwarescore=0 lowpriorityscore=0
 suspectscore=0 clxscore=1011 adultscore=0 phishscore=0 mlxlogscore=999
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2103250000 definitions=main-2103260047
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The kvm_write_tsc() was not used since commit 0c899c25d754 ("KVM: x86: do
not attempt TSC synchronization on guest writes"). Remove its unused
declaration.

Signed-off-by: Dongli Zhang <dongli.zhang@oracle.com>
---
 arch/x86/kvm/x86.h | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH 1/2] vfio/pci: remove vfio_pci_nvlink2
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 12165837
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,URIBL_RED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0671EC433E6
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 06:14:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D935761A4E
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 06:14:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230080AbhCZGNx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 02:13:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57376 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230007AbhCZGNl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Mar 2021 02:13:41 -0400
Received: from bombadil.infradead.org (bombadil.infradead.org
 [IPv6:2607:7c80:54:e::133])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E68CCC0613B0;
        Thu, 25 Mar 2021 23:13:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20210309; h=Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender
        :Reply-To:Content-Type:Content-ID:Content-Description;
        bh=7R3FYx/VSeEiEJOz2uYFNibCm/30TE6qd/CRtuXZYMI=;
 b=MIbZ1MFuIL0jkpD1JTCwAajp1c
        BQerDGkcHgA7e+GK5bSEGtu5Jfyd/U/zFNsSherYPytHjoQtSvkF6Zr/H+FKrO2/xtBRtiK8XKUPu
        6JSaWHGHOMQ3CFrkHGTRYfI7++CwdK+ZsQrBnsuijXA2MPqPnHEt9ghC7rEQ7+DuWFW5ErcSikr7C
        8oW+L7yEG/zTVoj42LoFYbNqU3jrbxfdrRM+nhKUrieUt9I7Qr799BoE/G054sf8jbmwmSJ4yIiIT
        NJfUA6x0t4SMC3icW+37ktU9fCei2FkmJ8+zcIc/1S+77L5E//cUaQOkMGUphDr+dN1RUW72BRN++
        EhVUNsPg==;
Received: from [2001:4bb8:191:f692:97ff:1e47:aee2:c7e5] (helo=localhost)
        by bombadil.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1lPfid-005AmW-NQ; Fri, 26 Mar 2021 06:13:16 +0000
From: Christoph Hellwig <hch@lst.de>
To: Michael Ellerman <mpe@ellerman.id.au>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Jason Gunthorpe <jgg@nvidia.com>,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org, Paul Mackerras <paulus@samba.org>,
        linuxppc-dev@lists.ozlabs.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, linux-api@vger.kernel.org
Subject: [PATCH 1/2] vfio/pci: remove vfio_pci_nvlink2
Date: Fri, 26 Mar 2021 07:13:10 +0100
Message-Id: <20210326061311.1497642-2-hch@lst.de>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210326061311.1497642-1-hch@lst.de>
References: <20210326061311.1497642-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 bombadil.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This driver never had any open userspace (which for VFIO would include
VM kernel drivers) that use it, and thus should never have been added
by our normal userspace ABI rules.

Signed-off-by: Christoph Hellwig <hch@lst.de>
Acked-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 drivers/vfio/pci/Kconfig            |   6 -
 drivers/vfio/pci/Makefile           |   1 -
 drivers/vfio/pci/vfio_pci.c         |  18 -
 drivers/vfio/pci/vfio_pci_nvlink2.c | 490 ----------------------------
 drivers/vfio/pci/vfio_pci_private.h |  14 -
 include/uapi/linux/vfio.h           |  38 +--
 6 files changed, 4 insertions(+), 563 deletions(-)
 delete mode 100644 drivers/vfio/pci/vfio_pci_nvlink2.c

```
#### [RFC PATCH v3 1/2] KVM: arm64: Move CMOs from user_mem_abort to the fault handlers
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12165721
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09E2DC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 03:18:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDB5D61A3F
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 03:18:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230370AbhCZDSL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 23:18:11 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:14551 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230317AbhCZDRg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 23:17:36 -0400
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4F66Xg4vQhzPmrt;
        Fri, 26 Mar 2021 11:14:59 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.498.0; Fri, 26 Mar 2021 11:17:26 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Alexandru Elisei" <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v3 1/2] KVM: arm64: Move CMOs from user_mem_abort to the
 fault handlers
Date: Fri, 26 Mar 2021 11:16:53 +0800
Message-ID: <20210326031654.3716-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210326031654.3716-1-wangyanan55@huawei.com>
References: <20210326031654.3716-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently uniformly permorm CMOs of D-cache and I-cache in function
user_mem_abort before calling the fault handlers. If we get concurrent
guest faults(e.g. translation faults, permission faults) or some really
unnecessary guest faults caused by BBM, CMOs for the first vcpu are
necessary while the others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions
where they are really needed and avoid the unnecessary ones. As it's a
time consuming process to perform CMOs especially when flushing a block
range, so this solution reduces much load of kvm and improve efficiency
of the page table code.

So let's move both clean of D-cache and invalidation of I-cache to the
map path and move only invalidation of I-cache to the permission path.
Since the original APIs for CMOs in mmu.c are only called in function
user_mem_abort, we now also move them to pgtable.c.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 31 ---------------
 arch/arm64/kvm/hyp/pgtable.c     | 68 +++++++++++++++++++++++++-------
 arch/arm64/kvm/mmu.c             | 23 ++---------
 3 files changed, 57 insertions(+), 65 deletions(-)

```
#### [PATCH 01/18] KVM: x86/mmu: Coalesce TDP MMU TLB flushes when zapping collapsible SPTEs
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12165537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6959DC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 02:21:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 36C71619DC
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 02:21:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231327AbhCZCUr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 22:20:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35212 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230327AbhCZCUN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 22:20:13 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 86B88C061761
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 19:20:13 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id x8so8408426ybo.6
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 19:20:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=xb8DgI2xFcrM/12UvqDPQlPXHEZwzPOiZzDwlsIie/g=;
        b=LTA+FlztlbawA45c1WTNtB0+0k4zDG2JNcBSVgOBw6hAgXeXfNjZbqxa0273lIWLNe
         ttjcg3fq+z634BQAWTxUlSsrRwNAaP+NP0BoTVohovvNTClDA7Atl31Oegy0JstB9ddH
         QquMjA9vYXTD8sE0ETK+TS3DQ0/9PyHdPbhasPovVlJc6LBQ4ZzAIKNbkbAQxLe+0uY9
         5ul5DAL52znGITYaaSnYG1czEu70soT/ovFzF22WuRsZzZM2LTU5TaSfaNlMMeAYoxEh
         nxkXSMEvdAqjZ2IhpJWyzFxM0kGdcqc6rH1PgDdXHrzIHZH3KWpk77UxwCuoas+sWLNA
         Nygg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=xb8DgI2xFcrM/12UvqDPQlPXHEZwzPOiZzDwlsIie/g=;
        b=UPh9LKPSLS8qczQj9SZPnCFthZLlbf9HWqDUOSravNZ5mWolZYupBNt6sPLyv08Hn1
         EgU7w3JJ1flZ2WDKp+ht9GL18iw2WXoUIsmBwUNyJ+XI4VFANrLTZN6CuUOIGP1tjFn1
         fyoUw6PUhiUV0Qgq9wAcicNRPV2RnKT0wnlJWXx3fmT4RRMOPfw/Cwst2qfeIUqaemVp
         XbiLuFjXWlL9oL/AOjfkgxIRb+48qOY/IKEJAA+P3WkfW9/Tld7Uj2ffWn9ZoNEatVjg
         bNov9Gu57pUbTsPtEaQhlvabMjw170FA6MD4TxR2Dvqg/ppISK70xNDk/+3NSz2nJeSv
         MTZg==
X-Gm-Message-State: AOAM531NosBHzA8ANh3vzSY4chl/3DB329HlbDmHI2WVdVXWNqz3bEzV
        3gS+0Uuf51EfRqC3LPfdFTrHOrMSpSk=
X-Google-Smtp-Source: 
 ABdhPJzT/d6MruEkvrArmoOcIHLexgvlTJlZNDyv9Tx14134QiRzKCyIxhCXc8QGkX5T07WTvqrR6kS/xTk=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b1bb:fab2:7ef5:fc7d])
 (user=seanjc job=sendgmr) by 2002:a25:37c1:: with SMTP id
 e184mr16469856yba.260.1616725212722;
 Thu, 25 Mar 2021 19:20:12 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Mar 2021 19:19:40 -0700
In-Reply-To: <20210326021957.1424875-1-seanjc@google.com>
Message-Id: <20210326021957.1424875-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210326021957.1424875-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH 01/18] KVM: x86/mmu: Coalesce TDP MMU TLB flushes when zapping
 collapsible SPTEs
From: Sean Christopherson <seanjc@google.com>
To: Marc Zyngier <maz@kernel.org>, Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-kernel@vger.kernel.org,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When zapping collapsible SPTEs across multiple roots, gather pending
flushes and perform a single remote TLB flush at the end, as opposed to
flushing after processing every root.

Note, flush may be cleared by the result of zap_collapsible_spte_range().
This is intended and correct, e.g. yielding may have serviced a prior
pending flush.

Cc: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 22 +++++++++++++---------
 1 file changed, 13 insertions(+), 9 deletions(-)

```
#### [PATCH 1/2] KVM: x86: hyper-v: Forbid unsigned hv_clock->system_time to go negative after KVM_REQ_CLOCK_UPDATE
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12167051
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6AB2C433C1
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 15:56:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD117619F2
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 15:56:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230223AbhCZP40 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 11:56:26 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:60081 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230343AbhCZP4S (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 26 Mar 2021 11:56:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616774177;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=0uRFDlwL1+lzKzSu8HKEgD5Pq5CxP3Jk8mXy5xseyFU=;
        b=YJfCBuFwWbR9R9svCLSAZAjYy9fkim+UdJ9mTSlYCbfzYihVWL37+iLGeGcATiuuhH0oUy
        Z9cfmoOTc9q5CBKGhTv5yG3tl4oMJd2iJQeIARHC7+YpHViDcQqplWlsA5Kt5a/EISlR4y
        NH+AF8ckoMC/sW5zzsiPStP+IuR01i4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-180-IIHrNclkM1WDku7XUy1nPQ-1; Fri, 26 Mar 2021 11:56:15 -0400
X-MC-Unique: IIHrNclkM1WDku7XUy1nPQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D744C8008C;
        Fri, 26 Mar 2021 15:56:03 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.148])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 003FC12C82;
        Fri, 26 Mar 2021 15:56:01 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH 1/2] KVM: x86: hyper-v: Forbid unsigned hv_clock->system_time
 to go negative after KVM_REQ_CLOCK_UPDATE
Date: Fri, 26 Mar 2021 16:55:50 +0100
Message-Id: <20210326155551.17446-2-vkuznets@redhat.com>
In-Reply-To: <20210326155551.17446-1-vkuznets@redhat.com>
References: <20210326155551.17446-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When guest time is reset with KVM_SET_CLOCK(0), it is possible for
hv_clock->system_time to become a small negative number. This happens
because in KVM_SET_CLOCK handling we set kvm->arch.kvmclock_offset based
on get_kvmclock_ns(kvm) but when KVM_REQ_CLOCK_UPDATE is handled,
kvm_guest_time_update() does

hv_clock.system_time = ka->master_kernel_ns + v->kvm->arch.kvmclock_offset;

And 'master_kernel_ns' represents the last time when masterclock
got updated, it can precede KVM_SET_CLOCK() call. Normally, this is not a
problem, the difference is very small, e.g. I'm observing
hv_clock.system_time = -70 ns. The issue comes from the fact that
'hv_clock.system_time' is stored as unsigned and 'system_time / 100' in
compute_tsc_page_parameters() becomes a very big number.

Forbid 'hv_clock.system_time' to go negative in kvm_guest_time_update().
A similar computation in get_kvmclock_ns() seems fine and doesn't require
the quirk.

Alternatively, we could've used 'master_kernel_ns' when computing
'arch.kvmclock_offset' but that would reduce the precision for normal
cases a bit. Another solution is to cast 'hv_clock.system_time' to
's64' in compute_tsc_page_parameters() but it seems we also use
'hv_clock.system_time' in trace_kvm_pvclock_update() as unsigned.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/x86.c | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)

```
#### [PATCH 7/7] Remove unnecessary variable
##### From: qiumibaozi_1@163.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: qiumibaozi_1@163.com
X-Patchwork-Id: 12165993
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E40DC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 08:38:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3952E61A48
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 08:38:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230097AbhCZIh6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 04:37:58 -0400
Received: from m12-18.163.com ([220.181.12.18]:37635 "EHLO m12-18.163.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230012AbhCZIhw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Mar 2021 04:37:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=163.com;
        s=s110527; h=From:Subject:Date:Message-Id:MIME-Version; bh=khWhN
        Liz8Y0gCiaThaxGXk9TRfGzQp0749K+yDhDHHc=; b=nh14fARKixuP4m/P2RqBf
        GI4o9SA1elGFBM7E268Yr/YB0UJLa7QGvwdeYHK4SQRJho0fcbnMbaT0S4f3hhtG
        KW0lGlmqHs9BiVO7Zvstr485aGVYoAZP81eawpeF03WW3ATSr/BRlu7JC8QhGvAE
        +m48qf4KN8PHhhh1B8F1G0=
Received: from COOL-20200916KH.ccdomain.com (unknown [218.94.48.178])
        by smtp14 (Coremail) with SMTP id EsCowABXVvQtnV1gz7cAaw--.4509S2;
        Fri, 26 Mar 2021 16:37:05 +0800 (CST)
From: qiumibaozi_1@163.com
To: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        ganjisheng <ganjisheng@yulong.com>
Subject: [PATCH 7/7] Remove unnecessary variable
Date: Fri, 26 Mar 2021 16:36:59 +0800
Message-Id: <20210326083659.496-1-qiumibaozi_1@163.com>
X-Mailer: git-send-email 2.28.0.windows.1
MIME-Version: 1.0
X-CM-TRANSID: EsCowABXVvQtnV1gz7cAaw--.4509S2
X-Coremail-Antispam: 1Uf129KBjvdXoW7Wr48AF13GFWDurWrJw18Zrb_yoW3uFb_Zr
        1fGa1UGw4kXa1Fvwn2ka15XF13Cwn3WF45Ar1rt39xAF90yr15Cr1vyr95CFZ7WFWfZrWk
        XrZrX3yfKF4I9jkaLaAFLSUrUUUUUb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUvcSsGvfC2KfnxnUUI43ZEXa7IUYUGYPUUUUU==
X-Originating-IP: [218.94.48.178]
X-CM-SenderInfo: 5tlxzxxedr6xjbr6il2tof0z/1tbiLRFh2FSIlawR4AAAsR
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: ganjisheng <ganjisheng@yulong.com>

Signed-off-by: ganjisheng <ganjisheng@yulong.com>
---
 arch/x86/kvm/emulate.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH V2] x86/kvmclock: Stop kvmclocks for hibernate restore
##### From: Lenny Szubowicz <lszubowi@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lenny Szubowicz <lszubowi@redhat.com>
X-Patchwork-Id: 12165653
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 48B26C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 02:42:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1634F61A38
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 02:42:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231201AbhCZCmY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 22:42:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40053 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230336AbhCZClw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 22:41:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616726512;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1ehJFMh/kOfU+I9OXEtjP+uM7fVA5wEAWFQ39c7YsNY=;
        b=Fdm8ubvqun7UM/9Jwa+6YRFFsDDd2bzK9RdGuT7xAXWZlGSSUw4jJDg8acpXvAixLNmpIp
        +081e+L7oyTQRh+LBhmK91tUgvXkKfTZrZs2jMF/V3WnOJZ/a8qKCu19wl20otr2+FFF4m
        YHuS6dSFfwHwUdzmkXjkY5+ddMrLo0E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-525-VcP3UqUaPwy-MRVEZIqA8Q-1; Thu, 25 Mar 2021 22:41:48 -0400
X-MC-Unique: VcP3UqUaPwy-MRVEZIqA8Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5258A107ACCD;
        Fri, 26 Mar 2021 02:41:46 +0000 (UTC)
Received: from lszubowi.redhat.com (unknown [10.10.110.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A7FF66EF55;
        Fri, 26 Mar 2021 02:41:43 +0000 (UTC)
From: Lenny Szubowicz <lszubowi@redhat.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH V2] x86/kvmclock: Stop kvmclocks for hibernate restore
Date: Thu, 25 Mar 2021 22:41:43 -0400
Message-Id: <20210326024143.279941-1-lszubowi@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Turn off host updates to the registered kvmclock memory
locations when transitioning to a hibernated kernel in
resume_target_kernel().

This is accomplished for secondary vcpus by disabling host
clock updates for that vcpu when it is put offline. For the
primary vcpu, it's accomplished by using the existing call back
from save_processor_state() to kvm_save_sched_clock_state().

The registered kvmclock memory locations may differ between
the currently running kernel and the hibernated kernel, which
is being restored and resumed. Kernel memory corruption is thus
possible if the host clock updates are allowed to run while the
hibernated kernel is relocated to its original physical memory
locations.

This is similar to the problem solved for kexec by
commit 1e977aa12dd4 ("x86: KVM guest: disable clock before rebooting.")

Commit 95a3d4454bb1 ("x86/kvmclock: Switch kvmclock data to a
PER_CPU variable") innocently increased the exposure for this
problem by dynamically allocating the physical pages that are
used for host clock updates when the vcpu count exceeds 64.
This increases the likelihood that the registered kvmclock
locations will differ for vcpus above 64.

Reported-by: Xiaoyi Chen <cxiaoyi@amazon.com>
Tested-by: Mohamed Aboubakr <mabouba@amazon.com>
Signed-off-by: Lenny Szubowicz <lszubowi@redhat.com>
---
 arch/x86/kernel/kvmclock.c | 40 ++++++++++++++++++++++++++++++++++----
 1 file changed, 36 insertions(+), 4 deletions(-)

```
#### [PATCH 1/4] vfio/type1: fix a couple of spelling mistakes
##### From: Zhen Lei <thunder.leizhen@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhen Lei <thunder.leizhen@huawei.com>
X-Patchwork-Id: 12165983
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5B1DFC433C1
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 08:37:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1325F61477
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 08:37:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230003AbhCZIhd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 04:37:33 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:14617 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230022AbhCZIhG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Mar 2021 04:37:06 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4F6Fdy0cS4z19JkX;
        Fri, 26 Mar 2021 16:35:02 +0800 (CST)
Received: from thunder-town.china.huawei.com (10.174.179.202) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Fri, 26 Mar 2021 16:36:53 +0800
From: Zhen Lei <thunder.leizhen@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Eric Auger <eric.auger@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>
CC: Zhen Lei <thunder.leizhen@huawei.com>
Subject: [PATCH 1/4] vfio/type1: fix a couple of spelling mistakes
Date: Fri, 26 Mar 2021 16:35:25 +0800
Message-ID: <20210326083528.1329-2-thunder.leizhen@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
In-Reply-To: <20210326083528.1329-1-thunder.leizhen@huawei.com>
References: <20210326083528.1329-1-thunder.leizhen@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.179.202]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are several spelling mistakes, as follows:
userpsace ==> userspace
Accouting ==> Accounting
exlude ==> exclude

Signed-off-by: Zhen Lei <thunder.leizhen@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] x86: Simplify the return expression
##### From: zuoqilin1@163.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: zuoqilin1@163.com
X-Patchwork-Id: 12166415
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3BCB3C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 11:29:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F01E061A36
	for <kvm@archiver.kernel.org>; Fri, 26 Mar 2021 11:29:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229982AbhCZL2y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Mar 2021 07:28:54 -0400
Received: from m12-14.163.com ([220.181.12.14]:37540 "EHLO m12-14.163.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229738AbhCZL2f (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Mar 2021 07:28:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=163.com;
        s=s110527; h=From:Subject:Date:Message-Id:MIME-Version; bh=VqcQ3
        QwxKEEaQnL4ibnWt3XJl6W8pH63gUjHJUgNVrA=; b=Kq6ECmXkpn9wM1Iy7VpGJ
        zzSFR4RDnUBZrQvPXR4jAOEQ1Cx78rJoz9dptuOwy2J/e5zsA+lrR9tEqPnGItMd
        rW2p2C77FpgM/6WJw0DU1ayhR4v+vVF2k29cKrmXTDQH+sq/pMhcHNspBR6MLa2m
        38C5cnwRalQ5JQgy3zPcMo=
Received: from COOL-20201210PM.ccdomain.com (unknown [218.94.48.178])
        by smtp10 (Coremail) with SMTP id DsCowADHaXwexV1gLKxVAQ--.32339S2;
        Fri, 26 Mar 2021 19:27:31 +0800 (CST)
From: zuoqilin1@163.com
To: mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        zuoqilin <zuoqilin@yulong.com>
Subject: [PATCH] x86: Simplify the return expression
Date: Fri, 26 Mar 2021 19:27:24 +0800
Message-Id: <20210326112724.1563-1-zuoqilin1@163.com>
X-Mailer: git-send-email 2.28.0.windows.1
MIME-Version: 1.0
X-CM-TRANSID: DsCowADHaXwexV1gLKxVAQ--.32339S2
X-Coremail-Antispam: 1Uf129KBjvdXoW7JF1fXw4xCryUXw15XFyrJFb_yoW3Xrg_Ja
        13Ww45KFZa93y7Aw17Aws5KF1S9w4kXry5Xa18Kay5trn0ya98Za1kKF4fXrW2grW3KFWf
        X3yDGry7Cr4UWjkaLaAFLSUrUUUUUb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUvcSsGvfC2KfnxnUUI43ZEXa7IUnhSdPUUUUU==
X-Originating-IP: [218.94.48.178]
X-CM-SenderInfo: 52xr1xpolqiqqrwthudrp/1tbiZQNhiV8ZNb3ALAAAss
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: zuoqilin <zuoqilin@yulong.com>

Simplify the return expression of kvm_compute_tsc_offset().

Signed-off-by: zuoqilin <zuoqilin@yulong.com>
---
 arch/x86/kvm/x86.c | 6 +-----
 1 file changed, 1 insertion(+), 5 deletions(-)

```
