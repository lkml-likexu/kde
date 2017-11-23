#### [PATCH 1/3] kvm: make KVM_CAP_ENABLE_CAP_VM architecture agnostic
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The first such capability to be handled in virt/kvm/ will be manual
dirty page reprotection.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Junaid Shahid <junaids@google.com>
---
 Documentation/virtual/kvm/api.txt | 13 +++++++++----
 arch/powerpc/kvm/powerpc.c        | 14 ++------------
 arch/s390/kvm/kvm-s390.c          | 11 +----------
 arch/x86/kvm/x86.c                | 14 ++------------
 include/linux/kvm_host.h          |  2 ++
 virt/kvm/kvm_main.c               | 25 +++++++++++++++++++++++++
 6 files changed, 41 insertions(+), 38 deletions(-)

```
#### [PATCH kvm-unit-tests] README: document ACCEL environment variable
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Suggested-by: Luiz Capitulino <lcapitulino@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Luiz Capitulino <lcapitulino@redhat.com>
---
 README.md | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH kvm-unit-tests] vmx: fix infinite loop on vmentry failure
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Broken by commit c76ddf062ecfc0b93c92f4006213888c487be92d
due to a copy-and-paste bug.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: nVMX: Test VMPTRLD with operand outside of backed memory
##### From: Jim Mattson <jmattson@google.com>

```c
Reads of unbacked addresses from the PCI bus should return all
ones. Since kvm's VMCS revision identifier isn't 0xffffffff, this
means that a VMPTRLD with an argument outside of backed memory should
set the VM-instruction error number to 11 (VMPTRLD with incorrect VMCS
revision identifier) if there is already a valid VMCS pointer loaded.

make_vmcs_current() has been modified to return all of the arithmetic
flags, so that the caller can distinguish VMfailInvalid from
VMfailValid.

Suggested-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
---
 x86/vmx.c | 17 ++++++++++++++---
 x86/vmx.h | 10 ++++++----
 2 files changed, 20 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM/x86: Use SVM assembly instruction mnemonics instead of .byte streams
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Recently the minimum required version of binutils was changed to 2.20,
which supports all SVM instruction mnemonics. The patch removes
all .byte #defines and uses real instruction mnemonics instead.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/include/asm/svm.h |  7 -------
 arch/x86/kvm/svm.c         | 12 ++++++------
 2 files changed, 6 insertions(+), 13 deletions(-)

```
#### [PULL 1/2] kvm: Use KVM_GET_MSR_INDEX_LIST for MSR_IA32_ARCH_CAPABILITIES support
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
From: Bandan Das <bsd@redhat.com>

When writing to guest's MSR_IA32_ARCH_CAPABILITIES, check whether it's
supported in the guest using the KVM_GET_MSR_INDEX_LIST ioctl.

Fixes: d86f963694df27f11b3681ffd225c9362de1b634
Suggested-by: Eduardo Habkost <ehabkost@redhat.com>
Tested-by: balducci@units.it
Signed-off-by: Bandan Das <bsd@redhat.com>
Message-Id: <jpg4lc4iiav.fsf_-_@linux.bootlegged.copy>
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 target/i386/kvm.c | 15 +++++++--------
 1 file changed, 7 insertions(+), 8 deletions(-)

```
#### [PATCH v2 1/2] kvm: nVMX: NMI-window exiting should wake L2 from HLTFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
According to the SDM, "NMI-window exiting" VM-exits wake a logical
processor from the same inactive states as would an NMI. Specifically,
they wake a logical processor from the shutdown state and from the
states entered using the HLT and MWAIT instructions.

Fixes: 6dfacadd5858 ("KVM: nVMX: Add support for activity state HLT")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

```
#### [PATCH v2] kvm: vmx: Rename vmx_instruction_info to vm_exit_instruction_info
##### From: Jim Mattson <jmattson@google.com>

```c
Many years ago, Intel documented field 440EH of the VMCS as the "VMX
instruction-information field" (e.g. Intel document C97063-002 from
April 2005), and kvm followed suit. However, this field is no longer
applicable only to VMX instruction intercepts. It now provides
instruction-information for string PIO VM-exits, descriptor table
VM-exits, RDRAND VM-exits, and RDSEED VM-exits. At some point, the SDM
began referring to this field as the "VM-exit instruction-information
field." Since this field name is not yet exposed as part of a
userspace API, let's rename it to match the current SDM.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/include/asm/hyperv-tlfs.h |   2 +-
 arch/x86/include/asm/vmx.h         |   2 +-
 arch/x86/kvm/vmx.c                 | 105 +++++++++++++++--------------
 arch/x86/kvm/vmx_evmcs.h           |   2 +-
 4 files changed, 57 insertions(+), 54 deletions(-)

```
#### [PATCH v4 1/6] vfio/mdev: Add new "aggregate" parameter for mdev create
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
For special mdev type which can aggregate instances for mdev device,
this extends mdev create interface by allowing extra "aggregate=xxx"
parameter, which is passed to mdev device model to be able to create
bundled number of instances for target mdev device.

v2: create new create_with_instances operator for vendor driver
v3:
- Change parameter name as "aggregate="
- Fix new interface comments.
- Parameter checking for new option, pass UUID string only to
  parse and properly end parameter for kstrtouint() conversion.

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 drivers/vfio/mdev/mdev_core.c    | 21 +++++++++++++++++----
 drivers/vfio/mdev/mdev_private.h |  4 +++-
 drivers/vfio/mdev/mdev_sysfs.c   | 32 ++++++++++++++++++++++++++++----
 include/linux/mdev.h             | 11 +++++++++++
 4 files changed, 59 insertions(+), 9 deletions(-)

```
#### [PATCH v2 1/4] x86/hyper-v: move synic/stimer control structures definitions to hyperv-tlfs.h
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
We implement Hyper-V SynIC and synthetic timers in KVM too so there's some
room for code sharing.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 69 ++++++++++++++++++++++++++++++
 drivers/hv/hv.c                    |  2 +-
 drivers/hv/hyperv_vmbus.h          | 68 -----------------------------
 3 files changed, 70 insertions(+), 69 deletions(-)

```
