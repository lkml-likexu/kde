#### [Bug 206215] QEMU guest crash due to random 'general protection fault' since kernel 5.2.5 on i7-3517UE
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11335731
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F6701398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 21:53:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E73C02465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 21:53:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730320AbgAOVxB convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 16:53:01 -0500
Received: from mail.kernel.org ([198.145.29.99]:51236 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728925AbgAOVxA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 16:53:00 -0500
From: bugzilla-daemon@bugzilla.kernel.org
To: kvm@vger.kernel.org
Subject: [Bug 206215] QEMU guest crash due to random 'general protection
 fault' since kernel 5.2.5 on i7-3517UE
Date: Wed, 15 Jan 2020 21:52:58 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: blocking
X-Bugzilla-Who: sean.j.christopherson@intel.com
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-206215-28872-3gxqP1CQJM@https.bugzilla.kernel.org/>
In-Reply-To: <bug-206215-28872@https.bugzilla.kernel.org/>
References: <bug-206215-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=206215

--- Comment #1 from Sean Christopherson (sean.j.christopherson@intel.com) ---
+cc Derek, who is hitting the same thing.

On Wed, Jan 15, 2020 at 09:18:56PM +0000, bugzilla-daemon@bugzilla.kernel.org
wrote:
> https://bugzilla.kernel.org/show_bug.cgi?id=206215
> 
>             Bug ID: 206215
>            Summary: QEMU guest crash due to random 'general protection
>                     fault' since kernel 5.2.5 on i7-3517UE
>            Product: Virtualization
>            Version: unspecified
>     Kernel Version: 5.5.0-0.rc6
>           Hardware: x86-64
>                 OS: Linux
>               Tree: Fedora
>             Status: NEW
>           Severity: blocking
>           Priority: P1
>          Component: kvm
>           Assignee: virtualization_kvm@kernel-bugs.osdl.org
>           Reporter: kernel@najdan.com
>         Regression: Yes
> 
> Created attachment 286831
>   --> https://bugzilla.kernel.org/attachment.cgi?id=286831&action=edit
> relevant logs
> 
> Since kernel 5.2.5 any qemu guest fail to start due to "general protection
> fault"
> 
> [  188.533545] traps: gsd-wacom[1855] general protection fault
> ip:7fed39b5e7b0
> sp:7fff3e349620 error:0 in libglib-2.0.so.0.6200.1[7fed39ae3000+83000]
> [  192.002357] traps: gvfs-fuse-sub[1560] general protection fault
> ip:7f9cd88100b2 sp:7f9cd5db0bf0 error:0 in
> libglib-2.0.so.0.6200.1[7f9cd87de000+83000]
> 
> Please note that kernel 5.2.4 work fine.
> 
> Tested guests with Widows Server 2016/2019 & Fedora 31
> 
> Attached logs show the DMESG output of the guests
> 
> Attached host files contains a WARNING thrown upong first guest start on the
> hypervisor:
> 
> [   49.533713] WARNING: CPU: 3 PID: 966 at arch/x86/kvm/x86.c:7963
> kvm_arch_vcpu_ioctl_run+0x1927/0x1ce0 [kvm]

Between the WARN, which is

  WARN_ON_ONCE(test_thread_flag(TIF_NEED_FPU_LOAD));

and the total diff of arch/x86/kvm for 5.2.4 -> 5.2.5 is



that's a big smoking gun pointing at commit ca7e6b286333 ("KVM: X86: Fix
fpu state crash in kvm guest"), which is commit e751732486eb upstream.

1. Can you verify reverting ca7e6b286333 (or e751732486eb in upstream)
   solves the issue?

2. Assuming the answer is yes, on a buggy kernel, can you run with the
   attached patch to try get debug info?

> [   49.533714] Modules linked in: vhost_net vhost tap tun xfrm4_tunnel
> tunnel4
> ipcomp xfrm_ipcomp esp4 ah4 af_key ebtable_filter ebtables ip6table_filter
> ip6_tables bridge stp llc nf_log_ipv4 nf_log_common xt_LOG ipt_REJECT
> nf_reject_ipv4 iptable_filter iptable_security iptable_raw xt_state
> xt_conntrack xt_DSCP xt_multiport iptable_mangle xt_TCPMSS xt_tcpmss
> xt_policy
> xt_nat iptable_nat nf_nat nf_conntrack nf_defrag_ipv6 nf_defrag_ipv4
> intel_rapl
> x86_pkg_temp_thermal intel_powerclamp coretemp kvm_intel sunrpc kvm vfat fat
> mei_hdcp mei_wdt snd_hda_codec_hdmi iTCO_wdt irqbypass iTCO_vendor_support
> snd_hda_codec_realtek snd_hda_codec_generic crct10dif_pclmul crc32_pclmul
> ledtrig_audio snd_hda_intel ghash_clmulni_intel snd_hda_codec intel_cstate
> intel_uncore snd_hda_core snd_hwdep intel_rapl_perf snd_seq snd_seq_device
> snd_pcm i2c_i801 r8169 lpc_ich mei_me snd_timer snd mei e1000e soundcore
> pcc_cpufreq tcp_bbr sch_fq ip_tables xfs i915 libcrc32c i2c_algo_bit
> drm_kms_helper crc32c_intel drm
> [   49.533760]  serio_raw video
> [   49.533764] CPU: 3 PID: 966 Comm: CPU 0/KVM Not tainted
> 5.2.5-200.fc30.x86_64 #1
> [   49.533765] Hardware name: CompuLab 0000000-00000/Intense-PC, BIOS
> IPC_2.2.400.5 X64 03/15/2018
> [   49.533784] RIP: 0010:kvm_arch_vcpu_ioctl_run+0x1927/0x1ce0 [kvm]
> [   49.533786] Code: 4c 89 e7 e8 1b 0b ff ff 4c 89 e7 e8 d3 8c fe ff 41 83 a4
> 24 e8 36 00 00 fb e9 bd ed ff ff f0 41 80 4c 24 31 10 e9 a5 ee ff ff <0f> 0b
> e9
> 74 ed ff ff 49 8b 84 24 c8 02 00 00 a9 00 00 01 00 0f 84
> [   49.533787] RSP: 0018:ffffbe4e423ffd30 EFLAGS: 00010002
> [   49.533789] RAX: 0000000000004b00 RBX: 0000000000000000 RCX:
> ffffa044ce958000
> [   49.533790] RDX: 0000000000000000 RSI: 0000000000000000 RDI:
> 0000000000000000
> [   49.533791] RBP: ffffbe4e423ffdd8 R08: 0000000000000000 R09:
> 00000000000003e8
> [   49.533792] R10: 0000000000000000 R11: 0000000000000000 R12:
> ffffa044d38f8000
> [   49.533792] R13: 0000000000000000 R14: ffffbe4e41ccf7b8 R15:
> 0000000000000000
> [   49.533794] FS:  00007f117953f700(0000) GS:ffffa044ee2c0000(0000)
> knlGS:0000000000000000
> [   49.533795] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
> [   49.533796] CR2: 0000000000000000 CR3: 000000040e8c2003 CR4:
> 00000000001626e0
> [   49.533797] Call Trace:
> [   49.533817]  kvm_vcpu_ioctl+0x215/0x5c0 [kvm]
> [   49.533821]  ? __seccomp_filter+0x7b/0x640
> [   49.533824]  ? __switch_to_asm+0x34/0x70
> [   49.533826]  ? __switch_to_asm+0x34/0x70
> [   49.533827]  ? apic_timer_interrupt+0xa/0x20
> [   49.533831]  do_vfs_ioctl+0x405/0x660
> [   49.533834]  ksys_ioctl+0x5e/0x90
> [   49.533836]  __x64_sys_ioctl+0x16/0x20
> [   49.533839]  do_syscall_64+0x5f/0x1a0
> [   49.533842]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
> [   49.533844] RIP: 0033:0x7f117d1fb34b
> [   49.533845] Code: 0f 1e fa 48 8b 05 3d 9b 0c 00 64 c7 00 26 00 00 00 48 c7
> c0 ff ff ff ff c3 66 0f 1f 44 00 00 f3 0f 1e fa b8 10 00 00 00 0f 05 <48> 3d
> 01
> f0 ff ff 73 01 c3 48 8b 0d 0d 9b 0c 00 f7 d8 64 89 01 48
> [   49.533846] RSP: 002b:00007f117953e698 EFLAGS: 00000246 ORIG_RAX:
> 0000000000000010
> [   49.533848] RAX: ffffffffffffffda RBX: 0000564f2cb65ba0 RCX:
> 00007f117d1fb34b
> [   49.533849] RDX: 0000000000000000 RSI: 000000000000ae80 RDI:
> 0000000000000019
> [   49.533850] RBP: 00007f1179f20000 R08: 0000564f2b7e5390 R09:
> 000000000000ffff
> [   49.533851] R10: 0000564f2ca7a710 R11: 0000000000000246 R12:
> 0000000000000001
> [   49.533852] R13: 00007f1179f21002 R14: 0000000000000000 R15:
> 0000564f2bc66e80
> [   49.533854] ---[ end trace a562473b18c9b742 ]---
> 
> /proc/cpuinfo
> 
> processor       : 0
> vendor_id       : GenuineIntel
> cpu family      : 6
> model           : 58
> model name      : Intel(R) Core(TM) i7-3517UE CPU @ 1.70GHz
> stepping        : 9
> microcode       : 0x1f
> cpu MHz         : 828.296
> cache size      : 4096 KB
> physical id     : 0
> siblings        : 4
> core id         : 0
> cpu cores       : 2
> apicid          : 0
> initial apicid  : 0
> fpu             : yes
> fpu_exception   : yes
> cpuid level     : 13
> wp              : yes
> flags           : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca
> cmov
> pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx rdtscp
> lm
> constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid
> aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 cx16
> xtpr
> pdcm pcid sse4_1 sse4_2 x2apic popcnt tsc_deadline_timer aes xsave avx f16c
> rdrand lahf_lm cpuid_fault epb pti ibrs ibpb stibp tpr_shadow vnmi
> flexpriority
> ept vpid fsgsbase smep erms xsaveopt dtherm ida arat pln pts
> bugs            : cpu_meltdown spectre_v1 spectre_v2 spec_store_bypass l1tf
> mds
> bogomips        : 4389.89
> clflush size    : 64
> cache_alignment : 64
> address sizes   : 36 bits physical, 48 bits virtual
> power management:
> 
> -- 
> You are receiving this mail because:
> You are watching the assignee of the bug.

--- 5.2.4/arch/x86/kvm/x86.c    2020-01-15 13:37:05.154445843 -0800
+++ 5.2.5/arch/x86/kvm/x86.c    2020-01-15 13:37:08.190438719 -0800
@@ -3264,6 +3264,10 @@

        kvm_x86_ops->vcpu_load(vcpu, cpu);

+       fpregs_assert_state_consistent();
+       if (test_thread_flag(TIF_NEED_FPU_LOAD))
+               switch_fpu_return();
+
        /* Apply any externally detected TSC adjustments (due to suspend) */
        if (unlikely(vcpu->arch.tsc_offset_adjustment)) {
                adjust_tsc_offset_host(vcpu, vcpu->arch.tsc_offset_adjustment);
@@ -7955,9 +7959,8 @@
                wait_lapic_expire(vcpu);
        guest_enter_irqoff();

-       fpregs_assert_state_consistent();
-       if (test_thread_flag(TIF_NEED_FPU_LOAD))
-               switch_fpu_return();
+       /* The preempt notifier should have taken care of the FPU already.  */
+       WARN_ON_ONCE(test_thread_flag(TIF_NEED_FPU_LOAD));

        if (unlikely(vcpu->arch.switch_db_regs)) {
                set_debugreg(0, 7); 
```
#### [PATCH 1/2 v2] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11333119
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64270109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 02:04:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 413E22467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 02:04:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="B1Je07Qs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728912AbgAOCEP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jan 2020 21:04:15 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:45602 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728890AbgAOCEP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jan 2020 21:04:15 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00F24AwO128822;
        Wed, 15 Jan 2020 02:04:10 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=6H9u2kI6yMrdKSYVmi8MqUhkawKVcWvg3aeFPBpRT7Y=;
 b=B1Je07QsSyACO68IbShuP00NAJkFRyHaHm4gfAv84+B3ZQjFSLCQlWhZpC0mnXEU6agc
 2IJpOWqKe/YwI3hGLbujRl0uWmT5uZ3+CietXhSXy4ThojmuBHhIXO6KEioMUfAUZcqv
 TgrJec5jajA0h9hBA/XqWvweb95IIpjyu92yT+CaNLVCK+RMHm1Pao4AtT9PhXYyLYQ/
 ta4Y6iBXwj5U3x9meqkZgy+saJd1qn78CbMsT3U5OhTydpJ0Mqwo7ckBJqLmU5yfr9te
 /ajsRo6gw8h9WhXVVeenSOIkboGjQKScSfoylYHcYjHQ4HY6vaeTX+OCoI6a3KpbO22X EA==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 2xf73yhn9v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Jan 2020 02:04:10 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 00F24Acf055356;
        Wed, 15 Jan 2020 02:04:10 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2xh8et4bep-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 15 Jan 2020 02:04:09 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 00F22tiq031586;
        Wed, 15 Jan 2020 02:02:55 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 14 Jan 2020 18:02:55 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 1/2 v2] KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests
Date: Tue, 14 Jan 2020 20:25:40 -0500
Message-Id: <20200115012541.8904-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200115012541.8904-1-krish.sadhukhan@oracle.com>
References: <20200115012541.8904-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9500
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-2001150017
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9500
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-2001150017
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Control Registers, Debug Registers, and
and MSRs" in Intel SDM vol 3C, the following checks are performed on vmentry
of nested guests:

    If the "load debug controls" VM-entry control is 1, bits 63:32 in the DR7
    field must be 0.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 6 ++++++
 arch/x86/kvm/x86.c        | 2 +-
 arch/x86/kvm/x86.h        | 6 ++++++
 3 files changed, 13 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Add a kvm module parameter check for vmware_backdoors test
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11335661
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B35821398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 20:15:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8F91224679
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 20:15:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ArSL4MDM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728927AbgAOUPk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 15:15:40 -0500
Received: from mail-dm6nam10on2081.outbound.protection.outlook.com
 ([40.107.93.81]:37074
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726362AbgAOUPj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 15:15:39 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=NFJsuwmQpi3Yxtwz6xkbuHPKkWSNRYYGNjV5oPRLzr9KSsip69sRGqLVBY5+2PTY8ZuWyADI3tMZ1zu9f8hx0PdSExo9HgCLdVBQdO8Ysd3jYAS6VICQQFwsTqzKvX7UWN6gqbrCDOuTn+Udrwu4jWrXB13H4b2J3k05too2Rs/xRd9unNqTO25mapN4ftIg0zqIFhEy1vVQsc2O2Ptem3Z0wD5LFXPy3bPBiFBjGB4aGPJrUG8JTjSDTgSvXyrbZIFHqi+Nzmxf9K1V5xxYqrFjxAEDZiy6R8G5SPLFDtnQxB9XIvFGa7NxePfTpE0KuQhGTeUjxgWR71HecPTf7Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=hXLV3KKkyDnoTQGl3RnmhdhFl39LZ6u/2gCnStrvHJI=;
 b=ZaJqWzr+KCA3zozq9UWz8G3uBnh1jb5z6z4JKhYXJ4KiflvmzFo+DbXfKlwEM9eoE0dVYFj3femNwJ0+pZRxglDjZdJ4brC5BXcw4oqOa3bw7jU0M/TColT2+V4tkh/eArOO7Vp0unrQV1EFFq7+iYTDfUDkeWWyz5ltdiHcO8++mCWxwN4yvV+u8wxoIVf1DfwMgQtSpx0dvDIa0pkUHz6Du5WLNL1dLhSJcxOsnTS2lhk0JP4fEYcfK5wBWE7HUuj9hacmyI5V0T32kMiKBlJRvFCEqEGxlQjFd/vkpoWEixiH/+Uip4AO47RNcneiWoJIienhsn3eY4xIUOKeGA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=hXLV3KKkyDnoTQGl3RnmhdhFl39LZ6u/2gCnStrvHJI=;
 b=ArSL4MDMRYanLxCrkyRI94r5RUXgfNMtDBiAf3KdzLyAY/mJ4A+cP+x8ohKjEOFZevzQ6duJe4V/DZ0elhLfrhkQrOuFa+d+YrS00VoJVEO24ga63a9irKxOU0kw6eqhOH15aF9fFi+NVJD2FqnXrYlQjDSzc5QiAC2SEre2BB8=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
Received: from CY4PR12MB1574.namprd12.prod.outlook.com (10.172.71.23) by
 CY4PR12MB1702.namprd12.prod.outlook.com (10.175.61.151) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2644.19; Wed, 15 Jan 2020 20:15:37 +0000
Received: from CY4PR12MB1574.namprd12.prod.outlook.com
 ([fe80::610a:6908:1e18:49fd]) by CY4PR12MB1574.namprd12.prod.outlook.com
 ([fe80::610a:6908:1e18:49fd%7]) with mapi id 15.20.2623.017; Wed, 15 Jan 2020
 20:15:37 +0000
Subject: [kvm-unit-tests PATCH] x86: Add a kvm module parameter check for
 vmware_backdoors test
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org
Date: Wed, 15 Jan 2020 14:15:35 -0600
Message-ID: <157911933557.8219.11014260858807770513.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN6PR04CA0106.namprd04.prod.outlook.com
 (2603:10b6:805:f2::47) To CY4PR12MB1574.namprd12.prod.outlook.com
 (2603:10b6:910:e::23)
MIME-Version: 1.0
Received: from naples-babu.amd.com (165.204.78.2) by
 SN6PR04CA0106.namprd04.prod.outlook.com (2603:10b6:805:f2::47) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2623.11 via Frontend
 Transport; Wed, 15 Jan 2020 20:15:36 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 216ea564-0c11-428a-22aa-08d799f7af20
X-MS-TrafficTypeDiagnostic: CY4PR12MB1702:|CY4PR12MB1702:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB17020E45A6A5D0409802B11995370@CY4PR12MB1702.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2089;
X-Forefront-PRVS: 02830F0362
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(396003)(376002)(346002)(136003)(39860400002)(366004)(199004)(189003)(16526019)(2906002)(186003)(86362001)(52116002)(7696005)(26005)(55016002)(6916009)(66556008)(478600001)(4744005)(5660300002)(4326008)(103116003)(316002)(956004)(81156014)(8676002)(81166006)(8936002)(66476007)(44832011)(66946007);DIR:OUT;SFP:1101;SCL:1;SRVR:CY4PR12MB1702;H:CY4PR12MB1574.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 dpXZiCsVOuvJVMV3SWoWKcmxZP6IDQl3tL+dwgYf6iVtqeDlG2C+vqqPL1/OuzXVJGDwGbaqRHj0OPehqzEEd+KRam6aEQaiP0kJonJPdQ1zqmGokmBpGZzwo5ID64+2TA4eQt3+L2hO78h729RakzcmDPrLfr93RYYNKmGSM7Ag9+MctePVww3bIPc7GZjJXY/ri9MtrRXUalfMvBNWvzL4y6g0cwYVK4KpAsQ7Dz3l8kUS8WAwKUijrw0Zp5t+9nqOizXOyKmcigvQtaKbmhWwAdB4h6N2VuUL0E4qLndLJwVnsoLkcx6xb/jmRe9gM4NcYAuu2oCF6073gnF08XaZTPvHZnY8y/PY7vUfsf+0cPCncZnwpcw4l0iIdYyv7oyZsS9yTiiVa9oIvH8tv0IBLtjRN4BpSinRjiK4Xv6lb4GJJPRGzxjJ0Bp+wHVM
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 216ea564-0c11-428a-22aa-08d799f7af20
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2020 20:15:37.2164
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Ie6/4ssyvfYhNxOXOrw3nE/AGCRJLBx7LC1UKM9ug9mrDHLtDsvH8fuUfZbGRmvd
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1702
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmware_backdoors test fails if the kvm module parameter
enable_vmware_backdoor is not set to Y. Add a check before
running the test.

Suggested-by: Huang2, Wei <Wei.Huang2@amd.com>
Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 x86/unittests.cfg |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: x86: Perform non-canonical checks in 32-bit KVM
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11335549
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F05392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 18:36:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4848724679
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 18:36:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729240AbgAOSgI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 13:36:08 -0500
Received: from mga02.intel.com ([134.134.136.20]:49268 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729157AbgAOSgI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 13:36:08 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 15 Jan 2020 10:36:07 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,323,1574150400";
   d="scan'208";a="220100394"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga008.fm.intel.com with ESMTP; 15 Jan 2020 10:36:07 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Perform non-canonical checks in 32-bit KVM
Date: Wed, 15 Jan 2020 10:36:05 -0800
Message-Id: <20200115183605.15413-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the CONFIG_X86_64 condition from the low level non-canonical
helpers to effectively enable non-canonical checks on 32-bit KVM.
Non-canonical checks are performed by hardware if the CPU *supports*
64-bit mode, whether or not the CPU is actually in 64-bit mode is
irrelevant.

For the most part, skipping non-canonical checks on 32-bit KVM is ok-ish
because 32-bit KVM always (hopefully) drops bits 63:32 of whatever value
it's checking before propagating it to hardware, and architecturally,
the expected behavior for the guest is a bit of a grey area since the
vCPU itself doesn't support 64-bit mode.  I.e. a 32-bit KVM guest can
observe the missed checks in several paths, e.g. INVVPID and VM-Enter,
but it's debatable whether or not the missed checks constitute a bug
because technically the vCPU doesn't support 64-bit mode.

The primary motivation for enabling the non-canonical checks is defense
in depth.  As mentioned above, a guest can trigger a missed check via
INVVPID or VM-Enter.  INVVPID is straightforward as it takes a 64-bit
virtual address as part of its 128-bit INVVPID descriptor and fails if
the address is non-canonical, even if INVVPID is executed in 32-bit PM.
Nested VM-Enter is a bit more convoluted as it requires the guest to
write natural width VMCS fields via memory accesses and then VMPTRLD the
VMCS, but it's still possible.  In both cases, KVM is saved from a true
bug only because its flows that propagate values to hardware (correctly)
take "unsigned long" parameters and so drop bits 63:32 of the bad value.

Explicitly performing the non-canonical checks makes it less likely that
a bad value will be propagated to hardware, e.g. in the INVVPID case,
if __invvpid() didn't implicitly drop bits 63:32 then KVM would BUG() on
the resulting unexpected INVVPID failure due to hardware rejecting the
non-canonical address.

The only downside to enabling the non-canonical checks is that it adds a
relatively small amount of overhead, but the affected flows are not hot
paths, i.e. the overhead is negligible.

Note, KVM technically could gate the non-canonical checks on 32-bit KVM
with static_cpu_has(X86_FEATURE_LM), but on bare metal that's an even
bigger waste of code for everyone except the 0.00000000000001% of the
population running on Yonah, and nested 32-bit on 64-bit already fudges
things with respect to 64-bit CPU behavior.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.h | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PATCH 2/2] kvm: Add ioctl for gathering debug counters
##### From: Milan Pandurov <milanpa@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Milan Pandurov <milanpa@amazon.de>
X-Patchwork-Id: 11334641
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 054AE13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 13:43:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C5F6E207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 13:43:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.de header.i=@amazon.de
 header.b="hdVqDXtu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728946AbgAONnb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 08:43:31 -0500
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:54164 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726088AbgAONnb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 08:43:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1579095811; x=1610631811;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=zLtXP9u67moYJgI0kcRDzsrw+pUFCjECk3TMYA8PO7Q=;
  b=hdVqDXtuC9YqOT8TFrnnXzqIu4r8A7/JXVpmr6zJJCZSeCt/CmVift5k
   JKbKuFgGtc/BLGyzxbt7/SMviAfQmDln4QQeiFFghz1+uUQr5rWoOlEvG
   DQsLtxAVdW1VW0Fs/2soa+XGtvQXEMgZJmmjelw/UCGQ4Ud3P9Onb9o29
   o=;
IronPort-SDR: 
 idFNB6zKcAox6Oguln3DkRDqPh+AyPXgyvXqArUndaAF9gd1pjj2DpyrfaMGXpKmvtdwi6h2uq
 M/Oitf6lnuWA==
X-IronPort-AV: E=Sophos;i="5.70,322,1574121600";
   d="scan'208";a="18876712"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 15 Jan 2020 13:43:19 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id 8C758A2BB4;
        Wed, 15 Jan 2020 13:43:17 +0000 (UTC)
Received: from EX13D27EUB004.ant.amazon.com (10.43.166.152) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.243) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Wed, 15 Jan 2020 13:43:16 +0000
Received: from uc3ce012741425f.ant.amazon.com (10.43.161.253) by
 EX13D27EUB004.ant.amazon.com (10.43.166.152) with Microsoft SMTP Server (TLS)
 id 15.0.1367.3; Wed, 15 Jan 2020 13:43:13 +0000
From: Milan Pandurov <milanpa@amazon.de>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <graf@amazon.de>,
        <borntraeger@de.ibm.com>
Subject: [PATCH 2/2] kvm: Add ioctl for gathering debug counters
Date: Wed, 15 Jan 2020 14:43:03 +0100
Message-ID: <20200115134303.30668-1-milanpa@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.253]
X-ClientProxiedBy: EX13D06UWA001.ant.amazon.com (10.43.160.220) To
 EX13D27EUB004.ant.amazon.com (10.43.166.152)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM exposes debug counters through individual debugfs files.
Monitoring these counters requires debugfs to be enabled/accessible for
the application, which might not be always the case.
Additionally, periodic monitoring multiple debugfs files from
userspace requires multiple file open/read/close + atoi conversion
operations, which is not very efficient.

Let's expose new interface to userspace for garhering these
statistics with one ioctl.

Two new ioctl methods are added:
 - KVM_GET_SUPPORTED_DEBUGFS_STAT : Returns list of available counter
 names. Names correspond to the debugfs file names
 - KVM_GET_DEBUGFS_VALUES : Returns list of u64 values each
 corresponding to a value described in KVM_GET_SUPPORTED_DEBUGFS_STAT.

Userspace application can read counter description once using
KVM_GET_SUPPORTED_DEBUGFS_STAT and periodically invoke the
KVM_GET_DEBUGFS_VALUES to get value update.

Signed-off-by: Milan Pandurov <milanpa@amazon.de>
---
Current approach returns all available counters to userspace which might
be an overkill. This can be further extended with an interface in which
userspace provides indicies of counters it is interested in counters
will be filled accordingly.

NOTE: This patch is placed on top of:
https://www.spinics.net/lists/kvm/msg202599.html
---
 include/uapi/linux/kvm.h | 21 ++++++++++++
 virt/kvm/kvm_main.c      | 70 ++++++++++++++++++++++++++++++++++++++++
 2 files changed, 91 insertions(+)

```
#### [PATCH v2 1/2] vfio: introduce vfio_dma_rw to read/write a range of IOVAs
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11333333
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44B0D138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 04:03:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 225BB24671
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 04:03:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729081AbgAOEDF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 14 Jan 2020 23:03:05 -0500
Received: from mga04.intel.com ([192.55.52.120]:12750 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728884AbgAOEDE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 14 Jan 2020 23:03:04 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 14 Jan 2020 20:03:03 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,321,1574150400";
   d="scan'208";a="217983181"
Received: from unknown (HELO joy-OptiPlex-7040.sh.intel.com) ([10.239.13.9])
  by orsmga008.jf.intel.com with ESMTP; 14 Jan 2020 20:03:01 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: zhenyuw@linux.intel.com, intel-gvt-dev@lists.freedesktop.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, kevin.tian@intel.com, peterx@redhat.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v2 1/2] vfio: introduce vfio_dma_rw to read/write a range of
 IOVAs
Date: Tue, 14 Jan 2020 22:53:03 -0500
Message-Id: <20200115035303.12362-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200115034132.2753-1-yan.y.zhao@intel.com>
References: <20200115034132.2753-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_dma_rw will read/write a range of user space memory pointed to by
IOVA into/from a kernel buffer without pinning the user space memory.

TODO: mark the IOVAs to user space memory dirty if they are written in
vfio_dma_rw().

Cc: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio.c             | 45 +++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 76 +++++++++++++++++++++++++++++++++
 include/linux/vfio.h            |  5 +++
 3 files changed, 126 insertions(+)

```
#### [PATCH v2] travis.yml: Prevent 'script' from premature exit
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11334423
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E65A4139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 13:17:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C51C62084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 13:17:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NPP3l/XQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728921AbgAONRI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 08:17:08 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:37675 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726555AbgAONRI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 08:17:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579094227;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=d3lYgzAufqIBnHm/YrA9eVcXZGLVtR4oW9p6BLViQI4=;
        b=NPP3l/XQ4TI8QPrb+LQHlGqqwUfGgpzQ/Lo5dER3ehlsQ90CIuI2otKO+ncetIkeLjg9dk
        oxJREffpIgx5AanFyAFXKUhsQy5hjfg+lACKuGrzYfL7xBE6/QKcAqlLWlfZqjigK5kC5a
        WYfN9TiC+hs1OJwnVbPVzXrgsqgIbmk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-49-dnImFfl2PQah2Y3x4VCaJA-1; Wed, 15 Jan 2020 08:17:06 -0500
X-MC-Unique: dnImFfl2PQah2Y3x4VCaJA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6DA00800D4C
        for <kvm@vger.kernel.org>; Wed, 15 Jan 2020 13:17:05 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-74.gru2.redhat.com
 [10.97.116.74])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B43A510372F3;
        Wed, 15 Jan 2020 13:17:03 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [PATCH v2] travis.yml: Prevent 'script' from premature exit
Date: Wed, 15 Jan 2020 10:17:01 -0300
Message-Id: <20200115131701.41131-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'script' section finishes its execution prematurely whenever
a shell's exit is called. If the intention is to force
Travis to flag a build/test failure then the correct approach
is erroring any command statement. In this change, it combines
the grep's in a single AND statement that in case of false
Travis will interpret as a build error.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
---
 Changes v1 to v2:
   - Simplify the grep's in a single statement [thuth]
   - Also grep for SKIP (besides PASS) [myself]
 .travis.yml | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v3] travis.yml: Prevent 'script' from premature exit
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11335015
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 982C813A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 14:46:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6D563222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 14:46:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="N/J/DzVO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726574AbgAOOqS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 09:46:18 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:24136 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726248AbgAOOqS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 09:46:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579099577;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=OCzZCRpCPvMJOJFp80Kyy/tm7e/FK8QUZeBwS6jnLQU=;
        b=N/J/DzVOOCkbnNjYK7cEFUkUb2N8G5R4y91wybVf4y3z+M4+zEXpiYaWXO2UvuyA3J2BOF
        ZFimoSqL9Ma/cmItvWvrraT/+cgCEWd4Ir1bF2+LRhnW1/Lec8aCsu62vkV2F7mQ85BSwE
        TMtaggWU+TQSspx/f9YJv38jzFZmcy4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-286-xrmhWreLPce99JAUX81nnA-1; Wed, 15 Jan 2020 09:46:15 -0500
X-MC-Unique: xrmhWreLPce99JAUX81nnA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 089BB1902ED3
        for <kvm@vger.kernel.org>; Wed, 15 Jan 2020 14:46:15 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-74.gru2.redhat.com
 [10.97.116.74])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DDEDF89E61;
        Wed, 15 Jan 2020 14:46:11 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [PATCH v3] travis.yml: Prevent 'script' from premature exit
Date: Wed, 15 Jan 2020 11:46:10 -0300
Message-Id: <20200115144610.41655-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'script' section finishes its execution prematurely whenever
a shell's exit is called. If the intention is to force
Travis to flag a build/test failure then the correct approach
is erroring any command statement. In this change, it combines
the grep's in a single AND statement that in case of false
Travis will interpret as a build error.

Signed-off-by: Wainer dos Santos Moschetta <wainersm@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 Changes v2 to v3:
   - Do not grep for SKIP, it needs at least one PASS [thuth]
 Changes v1 to v2:
   - Simplify the grep's in a single statement [thuth]
   - Also grep for SKIP (besides PASS) [myself]
 .travis.yml | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] x86: Add a kvm module parameter check for vmware_backdoors test
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11335649
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3328914B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 19:55:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 10DE124679
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 19:55:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="t2bx/heE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729557AbgAOTzU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 14:55:20 -0500
Received: from mail-mw2nam12on2041.outbound.protection.outlook.com
 ([40.107.244.41]:63631
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729025AbgAOTzU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 14:55:20 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=FIVfoLylm2LDzX9NLADrclAcX2eCT/9NH2pwQoxmV+j3+rJ62q8CNyViXiJF9j7y2Ze9vEg+YtTp1KFbaX0aVC8HtEcrvvMiDxh1ut7BDVrixDXmxXJI34BhRVRqt0H0rwle9vUUE2/7OsbGoh9BaNqlJmwa48G6xV9jxyuIPep4gnhF+gZIJ2LTuihOmpFZoXZ62QUTiSIM/J0nMucFX1dGxYOx5rh/J3/cdbTjlcDafuwIN0sKgeiBsX9fYgWO0Zo3p9M7cq52mOgrodQPxCauGV8UnmSgP2VD9s4RP5DPvK7CIDACM/6FEoHJZIkU+byYqs6A6hsO5D5rDmEQrw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=hXLV3KKkyDnoTQGl3RnmhdhFl39LZ6u/2gCnStrvHJI=;
 b=g4iWqEoOoljxEv7Eu8JI+QjMMMnNXz55Q4mny1vse8QOVv1mWsaE0ylNjpvD77DqRR31eHNPwV7CvvWq/2L0pjnVCUa8HOrs6e4bXsaM+dwTOVNXDFUDNZPsHfxgG6UDTFuNJnNYsz+ccAHBZwixzpvMTBeSyJ4sqg5qIfZtzB2lMXYixPaaxvmQ7k2G4M63kE9TxotJJ4T6rhVlHesUZwJM8ey6LXOxxRHSkEnO5jgW8IJrOIyriGvaDkbyQ4FqtbhkE4C0MwRD6PRFy378kTEf1Gy4xQWeMhRKNxBaoV9wYDLhPXZUR3YlyxW2rGsfFXzfHmqpQLszxrd8SHETkg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=hXLV3KKkyDnoTQGl3RnmhdhFl39LZ6u/2gCnStrvHJI=;
 b=t2bx/heEc1Z3L6Miq98DipFS+x7TAXpKBuivnR52FWZlof3E8o7od8MTkzoCVTIUeSpLYBsz8gr8Szt4ah+111oe2XiJAEwWkVt9z7rBmdFwhYNwMXDogN40fkVSne1vm9kXnT/DwUiwaL4RBOzQSnF9J0J65VL37eZY2a9q7qU=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
Received: from CY4PR12MB1574.namprd12.prod.outlook.com (10.172.71.23) by
 CY4PR12MB1830.namprd12.prod.outlook.com (10.175.81.148) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2644.19; Wed, 15 Jan 2020 19:55:16 +0000
Received: from CY4PR12MB1574.namprd12.prod.outlook.com
 ([fe80::610a:6908:1e18:49fd]) by CY4PR12MB1574.namprd12.prod.outlook.com
 ([fe80::610a:6908:1e18:49fd%7]) with mapi id 15.20.2623.017; Wed, 15 Jan 2020
 19:55:16 +0000
Subject: [PATCH] x86: Add a kvm module parameter check for vmware_backdoors
 test
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org
Date: Wed, 15 Jan 2020 13:55:15 -0600
Message-ID: <157911811499.8078.14507140648862605986.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN6PR04CA0105.namprd04.prod.outlook.com
 (2603:10b6:805:f2::46) To CY4PR12MB1574.namprd12.prod.outlook.com
 (2603:10b6:910:e::23)
MIME-Version: 1.0
Received: from naples-babu.amd.com (165.204.78.2) by
 SN6PR04CA0105.namprd04.prod.outlook.com (2603:10b6:805:f2::46) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2644.19 via Frontend
 Transport; Wed, 15 Jan 2020 19:55:16 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9a9bdd2d-a05f-4e4c-8586-08d799f4d793
X-MS-TrafficTypeDiagnostic: CY4PR12MB1830:|CY4PR12MB1830:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB183082EDDF3572A6196FE81B95370@CY4PR12MB1830.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2089;
X-Forefront-PRVS: 02830F0362
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(136003)(376002)(346002)(396003)(39860400002)(366004)(189003)(199004)(186003)(4744005)(16526019)(478600001)(55016002)(103116003)(5660300002)(26005)(66556008)(316002)(81166006)(2906002)(4326008)(8936002)(44832011)(8676002)(7696005)(86362001)(81156014)(52116002)(6916009)(66946007)(66476007)(956004);DIR:OUT;SFP:1101;SCL:1;SRVR:CY4PR12MB1830;H:CY4PR12MB1574.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 TwtvjXtpbDFUHuLxKm9AEjNon1LOY67OwRW20JLsLRX0ytcR3hcTONGOA0a/NbkgLPYfphMTLrNsAIULvQnTKDo1jMVRs4XpTm5Y+iknwfuaaV1sl1qy6uNoeFx2Gcso7ze59OeJ5T54wcY99S9Y1piJrn6kPMVlPE64R1rBi9m6Nt+8gU+uG2Hz82Fq1XFyez/m1z9nFoTywJKtJLClqDjUqNLWfHdGyxYdWn2pL69bItF5oOZKOkPCXNyoDPdejK1lDmCYtBTcih60wnL1CwyxS9erUH+CAkfjAop0GmvszxoY7N818hDNF6Gt0SjiXsSjzsQ7lNoVqdZyJESPY80il1s03k9TfVIHcclALcvs8XZeews8D1QOCHaiwO0RGLyLJV7r6rp61DqQG0GNE+S9X8Ph38cZKQ5g4SaevTm+MWniAgirDOFL0DhhlK0+
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9a9bdd2d-a05f-4e4c-8586-08d799f4d793
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Jan 2020 19:55:16.6562
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 9Z+gg6SQsGx3AzrN4MwlNRHgMNZBDl03IOYpM3HnBvP6xYakoGIGdhJYoijRRBaL
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1830
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmware_backdoors test fails if the kvm module parameter
enable_vmware_backdoor is not set to Y. Add a check before
running the test.

Suggested-by: Huang2, Wei <Wei.Huang2@amd.com>
Signed-off-by: Babu Moger <babu.moger@amd.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 x86/unittests.cfg |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH RFC 1/3] x86/kvm/hyper-v: remove stale evmcs_already_enabled check from nested_enable_evmcs()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11335443
Return-Path: <SRS0=aSHY=3E=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AFF1292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 17:10:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8E2D02465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 15 Jan 2020 17:10:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Flr8Z9tE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728792AbgAORKX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jan 2020 12:10:23 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:21571 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728963AbgAORKW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jan 2020 12:10:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579108220;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=lUo1D7ikLQfA8lYaKoHVJNnJCuON6B6xnJFrEX1/0vk=;
        b=Flr8Z9tErEIVno9bnIJ5AQL67Rd7nwXFmZcBtk6k22Snk4H7dz6X5IZG1zhpKzmgCi08Zg
        RZWTjXF06c3SV7g4bhQpNj53y7iJHOTqHNprIvsbgzu6yLa9RIDfQDByyhgy3rf38nWNLm
        2NbmDIAd5U3s2SVK4que49hzJg1C7KQ=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-180-KnRBQDvgOJqE4uat1lnifQ-1; Wed, 15 Jan 2020 12:10:19 -0500
X-MC-Unique: KnRBQDvgOJqE4uat1lnifQ-1
Received: by mail-wr1-f70.google.com with SMTP id z10so8157831wrt.21
        for <kvm@vger.kernel.org>; Wed, 15 Jan 2020 09:10:19 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=lUo1D7ikLQfA8lYaKoHVJNnJCuON6B6xnJFrEX1/0vk=;
        b=DOImFha2o5o7C2oZIzwTPcyhMADRxrYff8OGBcImLFv803Oy2x6LA5lcbvtPLgDWeC
         AitTos3uc73aAcAFZigXi6tkx3pA4WkRBBkF72/Pfgwh1ib6u+R9jRoJ9nkICFHf3YXv
         0urSL7Anw6T3uBnA7DWgTbmDpCjYLFP+SxLFCAUH0ByENaLksEuwMv5rLOX6IoF6wmM3
         MS1JO7H8so1RuJoh2ivQnp4RIoYggl8o0AVYWHM9+LhVrVcTA5oF7UIy/ARFEqBEdpLK
         0A5JPXAc+UZVCy7GmkQ83iqg3+WocEUVerknKsuDqiheZ6smQeMNl9Da+ULQFnqYDTZf
         3/xw==
X-Gm-Message-State: APjAAAXMdhrNKwE5DkEbBGn4nEY1dTjte5aVzLEMsxvz78LdEL6HwzoZ
        /YbiL5nCgliCBPO2q5AYZNEpcpy1c6cf+gXdohnzgWPo5hnpigDrLS9PfIJ7XscnEE1hpiygXna
        RfIIljzj8hOXV
X-Received: by 2002:a7b:cbc9:: with SMTP id n9mr887032wmi.89.1579108217927;
        Wed, 15 Jan 2020 09:10:17 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqx4B9x0NLSvFhdpR/GVGflvW4G/nSX8mzTF5mcgnPay7KLNFLabJe8vYU6dpBFPYErt1ooqnQ==
X-Received: by 2002:a7b:cbc9:: with SMTP id n9mr887008wmi.89.1579108217757;
        Wed, 15 Jan 2020 09:10:17 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 y20sm525071wmi.25.2020.01.15.09.10.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 15 Jan 2020 09:10:16 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH RFC 1/3] x86/kvm/hyper-v: remove stale evmcs_already_enabled
 check from nested_enable_evmcs()
Date: Wed, 15 Jan 2020 18:10:12 +0100
Message-Id: <20200115171014.56405-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200115171014.56405-1-vkuznets@redhat.com>
References: <20200115171014.56405-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In nested_enable_evmcs() evmcs_already_enabled check doesn't really do
anything: controls are already sanitized and we return '0' regardless.
Just drop the check.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/evmcs.c | 5 -----
 1 file changed, 5 deletions(-)

```
