#### [PATCH 6/7] KVM: x86: Update cpufreq transition notifier to handle multiple CPUs
##### From: Viresh Kumar <viresh.kumar@linaro.org>

```c
The cpufreq core currently calls the cpufreq transition notifier
callback once for each affected CPU. This is going to change soon and
the cpufreq core will call the callback only once for each cpufreq
policy. The callback must look at the newly added field in struct
cpufreq_freqs, "cpus", which contains policy->related_cpus (both
online/offline CPUs) and perform per-cpu actions for them if any.

This patch updates kvmclock_cpufreq_notifier() to use the new "cpus"
field and perform the per-cpu activity for all online CPUs in this
cpumask.

Signed-off-by: Viresh Kumar <viresh.kumar@linaro.org>
---
 arch/x86/kvm/x86.c | 31 ++++++++++++++++++++-----------
 1 file changed, 20 insertions(+), 11 deletions(-)

```
#### [PATCH] KVM: svm: merge incomplete IPI emulation handling
##### From: Li RongQing <lirongqing@baidu.com>

```c
Invalid int type emulation and target not running emulation have
same codes, which update APIC ICR high/low registers, and emulate
sending the IPI.

so fall through this switch cases to reduce duplicate codes

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
---
 arch/x86/kvm/svm.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [PATCH] kvm/x86/vmx: switch MSR_MISC_FEATURES_ENABLES between host and guest
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
CPUID Faulting is a feature about CPUID instruction. When CPUID Faulting is
enabled, all execution of the CPUID instruction outside system-management
mode (SMM) cause a general-protection (#GP) if the CPL > 0.

About this feature, detailed information can be found at
https://www.intel.com/content/dam/www/public/us/en/documents/application-notes/virtualization-technology-flexmigration-application-note.pdf

There is an issue that current kvm doesn't switch the value of
MSR_MISC_FEATURES_ENABLES between host and guest. If MSR_MISC_FEATURES_ENABLES
exists on the hardware cpu, and host enables CPUID faulting (setting the bit 0
of MSR_MISC_FEATURES_ENABLES), it will impact the guest's behavior because
cpuid faulting is enabled by host and passed to guest.

From my tests, when host enables cpuid faulting, it causes guest boot failure
when guest uses *modprobe* to load modules. Below is the error log:

[    1.233556] traps: modprobe[71] general protection fault ip:7f0077f6495c sp:7ffda148d808 error:0 in ld-2.17.so[7f0077f4d000+22000]
[    1.237780] traps: modprobe[73] general protection fault ip:7fad5aba095c sp:7ffd36067378 error:0 in ld-2.17.so[7fad5ab89000+22000]
[    1.241930] traps: modprobe[75] general protection fault ip:7f3edb89495c sp:7fffa1a81308 error:0 in ld-2.17.so[7f3edb87d000+22000]
[    1.245998] traps: modprobe[77] general protection fault ip:7f91d670895c sp:7ffc25fa7f38 error:0 in ld-2.17.so[7f91d66f1000+22000]
[    1.250016] traps: modprobe[79] general protection fault ip:7f0ddbbdc95c sp:7ffe9c34f8d8 error:0 in ld-2.17.so[7f0ddbbc5000+22000]

*modprobe* calls CPUID instruction thus causing cpuid faulting in guest.
At the end, because guest cannot *modprobe* modules, it boots failure.

This patch switches MSR_MISC_FEATURES_ENABLES between host and guest when
hardware has this MSR.

This patch doesn't confict with the commit db2336a80489 ("KVM: x86: virtualize
cpuid faulting"), which provides a software emulation of cpuid faulting for
x86 arch. Below analysing how cpuid faulting will work after applying this patch:

1. If host cpu is AMD. It doesn't have MSR_MISC_FEATURES_ENABLES, so we can just
use the software emulation of cpuid faulting.

2. If host cpu is Intel and it doesn't have MSR_MISC_FEATURES_ENABLES. The same
as case 1, we can just use the software emulation of cpuid faulting.

3. If host cpu is Intel and it has MSR_MISC_FEATURES_ENABLES. With this patch,
it will write guest's value into MSR_MISC_FEATURES_ENABLES when vm entry.
If guest enables cpuid faulting and when guest calls CPUID instruction with
CPL > 0, it will cause #GP exception in guest instead of VM exit because of
CPUID, thus it doesn't go to the kvm emualtion path but ues the hardware
feature. Also it's a benefit that we needn't use VM exit to inject #GP to
emulate cpuid faulting feature.

Intel SDM vol3.25.1.1 specifies the priority between cpuid faulting
and CPUID instruction.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 19 +++++++++++++++++++
 1 file changed, 19 insertions(+)

```
#### [PATCH][v2] KVM: fix error handling in svm_hardware_setup
##### From: Li RongQing <lirongqing@baidu.com>

```c
From: Li Rongqing <lirongqing@baidu.com>

move svm_hardware_unsetup before svm_hardware_setup, and call
it to free all memory if fail to setup in svm_hardware_setup,
otherwise memory will be leaked

remove __exit attribute for svm_hardware_unsetup since it is
called in __init function

Signed-off-by: Li Rongqing <lirongqing@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 31 +++++++++++++++----------------
 1 file changed, 15 insertions(+), 16 deletions(-)

```
#### =?utf-8?b?562U5aSNOiBbUEFUQ0hdIEtWTTogZml4IGVycm9yIGhhbmRsaW5nIGlu?=	=?utf-8?b?IHN2bV9oYXJkd2FyZV9zZXR1cA==?=
##### From: "Li,Rongqing" <lirongqing@baidu.com>

```c
> -----邮件原件-----
> 发件人: kvm-owner@vger.kernel.org [mailto:kvm-owner@vger.kernel.org] 代
> 表 Singh, Brijesh
> 发送时间: 2019年3月13日 23:50
> 收件人: Li,Rongqing <lirongqing@baidu.com>; x86@kernel.org;
> kvm@vger.kernel.org
> 抄送: Singh, Brijesh <brijesh.singh@amd.com>
> 主题: Re: [PATCH] KVM: fix error handling in svm_hardware_setup
> 
...
> > +	if (svm_sev_enabled())
> > +		bitmap_free(sev_asid_bitmap);
> > +
> > +	for_each_possible_cpu(cpu)
> > +		svm_cpu_uninit(cpu);
> > +
> >   	__free_pages(iopm_pages, IOPM_ALLOC_ORDER);
> >   	iopm_base = 0;
> >   	return r;
> >
> 
> 
> Does it make sense to call the svm_hardware_unsetup() instead of duplicating
> the logic in error code path ?
> 

Thanks for your review;

Two thing needs to do if call svm_hardware_unsetup

1. move svm_hardware_unsetup before svm_hardware_setup, to avoid declaration
2. remove __exit attribute for svm_hardware_unsetup , otherwise these is the below warning:

              WARNING: arch/x86/kvm/kvm-amd.o(.init.text+0x4aa): Section mismatch in reference from the function svm_hardware_setup() to         the function .exit.text:svm_hardware_unsetup()
              The function __init svm_hardware_setup() references
              a function __exit svm_hardware_unsetup().
              This is often seen when error handling in the init function
              uses functionality in the exit path.
              The fix is often to remove the __exit annotation of
              svm_hardware_unsetup() so it may be used outside an exit section.


The RFC is below:



-RongQing




> thanks
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>

```
