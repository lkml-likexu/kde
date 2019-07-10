

#### [PATCH v2 0/2]  KVM: nVMX: add tracepoints for nested VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Debugging VM-Enter failures has been the bane of my existence for years.
Seeing KVM's VMCS dump format pop up on a console triggers a Pavlovian
response of swear words and sighs.  As KVM's coverage of VM-Enter checks
improve, so too do the odds of being able to triage/debug a KVM (or any
other hypervisor) bug by running the bad KVM build as an L1 guest.

Improve support for using KVM to debug a buggy VMM by adding tracepoints
to capture the basic gist of a VM-Enter failure so that extracting said
information from KVM doesn't require attaching a debugger or modifying
L0 KVM to manually log failures.

The captured information is by no means complete or perfect, e.g. I'd
love to capture *exactly* why a consistency check failed, but logging
that level of detail would require invasive code changes and might even
act as a deterrent to adding more checks in KVM.

v2: Rebase to kvm/queue.

Sean Christopherson (2):
  KVM: nVMX: add tracepoint for failed nested VM-Enter
  KVM: nVMX: trace nested VM-Enter failures detected by H/W

 arch/x86/include/asm/vmx.h |  14 ++
 arch/x86/kvm/trace.h       |  22 +++
 arch/x86/kvm/vmx/nested.c  | 271 +++++++++++++++++++------------------
 arch/x86/kvm/x86.c         |   1 +
 4 files changed, 180 insertions(+), 128 deletions(-)
```
#### [PATCH v2 0/3] Documentation: virtual: convert .txt to .rst
##### From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
X-Google-Original-From: Luke Nowakowski-Krijger <lnowakow@neg.ucsd.edu>
From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

```c

From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

Converted a few documents in virtual and virtual/kvm to .rst format.
Also added toctree hooks wherever there were .rst files. Adding hooks to
the main doc tree should be in another patch series once there are more
files in the directory.

After confirming with the appropriate lists that all the
Documentation/virtual/* files are not obsolete I will continue
converting the rest of the .txt files to .rst.

Changes in v2: 
	Documentation: kvm: Convert cpuid.txt to .rst
	+ added updated Author email address
	+ changed table to simpler format
	- removed function bolding from v1
	Documentation: virtual: Add toctree hooks
	- Removed vcpu-request from hooks that was added in v1

Chanes in v1:
	Documentation: kvm: Convert cpuid.txt to .rst
	+ Converted doc to .rst format
	Documentation: virtual: Convert paravirt_ops.txt to .rst
	+ Converted doc to .rst format
	Documentation: virtual: Add toctree hooks
	+ Added index.rst file in virtual directory
	+ Added index.rst file in virtual/kvm directory


Luke Nowakowski-Krijger (3):
  Documentation: kvm: Convert cpuid.txt to .rst
  Documentation: virtual: Convert paravirt_ops.txt to .rst
  Documentation: virtual: Add toctree hooks

 Documentation/virtual/index.rst               | 18 ++++
 Documentation/virtual/kvm/cpuid.rst           | 99 +++++++++++++++++++
 Documentation/virtual/kvm/cpuid.txt           | 83 ----------------
 Documentation/virtual/kvm/index.rst           | 11 +++
 .../{paravirt_ops.txt => paravirt_ops.rst}    | 19 ++--
 5 files changed, 139 insertions(+), 91 deletions(-)
 create mode 100644 Documentation/virtual/index.rst
 create mode 100644 Documentation/virtual/kvm/cpuid.rst
 delete mode 100644 Documentation/virtual/kvm/cpuid.txt
 create mode 100644 Documentation/virtual/kvm/index.rst
 rename Documentation/virtual/{paravirt_ops.txt => paravirt_ops.rst} (65%)
```
