

#### [PATCH v12 00/12] Intel Processor Trace virtualization enabling
##### From: Luwei Kang <luwei.kang@intel.com>

```c

Hi All,

Here is a patch-series which adding Processor Trace enabling in KVM guest. You can get It's software developer manuals from:
https://software.intel.com/sites/default/files/managed/c5/15/architecture-instruction-set-extensions-programming-reference.pdf
In Chapter 4 INTEL PROCESSOR TRACE: VMX IMPROVEMENTS.

Introduction:
Intel Processor Trace (Intel PT) is an extension of Intel Architecture that captures information about software execution using dedicated hardware facilities that cause only minimal performance perturbation to the software being traced. Details on the Intel PT infrastructure and trace capabilities can be found in the Intel 64 and IA-32 Architectures Software Developer’s Manual, Volume 3C.

The suite of architecture changes serve to simplify the process of virtualizing Intel PT for use by a guest software. There are two primary elements to this new architecture support for VMX support improvements made for Intel PT.
1. Addition of a new guest IA32_RTIT_CTL value field to the VMCS.
  — This serves to speed and simplify the process of disabling trace on VM exit, and restoring it on VM entry.
2. Enabling use of EPT to redirect PT output.
  — This enables the VMM to elect to virtualize the PT output buffer using EPT. In this mode, the CPU will treat PT output addresses as Guest Physical Addresses (GPAs) and translate them using EPT. This means that Intel PT output reads (of the ToPA table) and writes (of trace output) can cause EPT violations, and other output events.

Processor Trace virtualization can be work in one of 2 possible modes by set new option "pt_mode". Default value is system mode.
 a. system-wide: trace both host/guest and output to host buffer;
 b. host-guest: trace host/guest simultaneous and output to their respective buffer.

>From V11:
 - In patch 3, arguments caps vs. cap is not good. Spell second one out. -- Thomas Gleixner

>From V10: (This version don't have code change)
 - move the patch 5 in version 9 to patch 3 (reorder patch 5) -- Alexander Shishkin
 - refind the patch description of patch 5 (add new capability for Intel PT) -- Alexander Shishkin
 - CC all the maintainers, reviewers and submitters in each patch of this patch set -- Alexander Shishkin

>From V9:
 - remove redundant initialize for "ctl_bitmask" in patch 9;
 - do some changes for patch's description.

>From V8:
 - move macro definition MSR_IA32_RTIT_ADDR_RANGE from msr-index.h to intel_pt.h;
 - initialize the RTIT_CTL bitmask to ~0ULL.

>From V7:
 - remove host only mode since it can be emulated by perf code;
 - merge patch 8 and 9 to make code and data in the same patch;
 - rename __pt_cap_get() to pt_cap_decode();
 - other minor change.

>From V6:
 - split pathes 1~2 to four separate patches (these patches do 2 things) and add more descriptions.

>From V5:
 - rename the function from pt_cap_get_ex() to __pt_cap_get();
 - replace the most of function from vmx_pt_supported() to "pt_mode == PT_MODE_HOST_GUEST"(or !=).

>From V4:
 - add data check when setting the value of MSR_IA32_RTIT_CTL;
 - Invoke new interface to set the intercept of MSRs read/write after "MSR bitmap per-vcpu" patches.

>From V3:
 - change default mode to SYSTEM mode;
 - add a new patch to move PT out of scattered features;
 - add a new fucntion kvm_get_pt_addr_cnt() to get the number of address ranges;
 - add a new function vmx_set_rtit_ctl() to set the value of guest RTIT_CTL, GUEST_IA32_RTIT_CTL and MSRs intercept.

>From v2:
 - replace *_PT_SUPPRESS_PIP to *_PT_CONCEAL_PIP;
 - clean SECONDARY_EXEC_PT_USE_GPA, VM_EXIT_CLEAR_IA32_RTIT_CTL and VM_ENTRY_LOAD_IA32_RTIT_CTL in SYSTEM mode. These bits must be all set or all clean;
 - move processor tracing out of scattered features;
 - add a new function to enable/disable intercept MSRs read/write;
 - add all Intel PT MSRs read/write and disable intercept when PT is enabled in guest;
 - disable Intel PT and enable intercept MSRs when L1 guest VMXON;
 - performance optimization.
   In Host only mode. we just need to save host RTIT_CTL before vm-entry and restore host RTIT_CTL after vm-exit;
   In HOST_GUEST mode. we need to save and restore all MSRs only when PT has enabled in guest.
 - use XSAVES/XRESTORES implement context switch.
   Haven't implementation in this version and still in debuging. will make a separate patch work on this.

>From v1:
 - remove guest-only mode because guest-only mode can be covered by host-guest mode;
 - always set "use GPA for processor tracing" in secondary execution control if it can be;
 - trap RTIT_CTL read/write. Forbid write this msr when VMXON in L1 hypervisor.

Chao Peng (7):
  perf/x86/intel/pt: Move Intel-PT MSRs bit definitions to a public
    header
  perf/x86/intel/pt: Change pt_cap_get() to a public function
  KVM: x86: Add Intel Processor Trace virtualization mode
  KVM: x86: Add Intel Processor Trace cpuid emulation
  KVM: x86: Add Intel Processor Trace context switch for each vcpu
  KVM: x86: Implement Intel Processor Trace MSRs read/write emulation
  KVM: x86: Set intercept for Intel PT MSRs read/write

Luwei Kang (5):
  perf/x86/intel/pt: Introduce a new function to get capability of Intel
    PT
  perf/x86/intel/pt: Add new bit definitions for Intel PT MSRs
  perf/x86/intel/pt: add new capability for Intel PT
  KVM: x86: Introduce a function to initialize the PT configuration
  KVM: x86: Disable Intel Processor Trace when VMXON in L1 guest

 arch/x86/events/intel/pt.c       |  14 +-
 arch/x86/events/intel/pt.h       |  58 -----
 arch/x86/include/asm/intel_pt.h  |  39 ++++
 arch/x86/include/asm/kvm_host.h  |   1 +
 arch/x86/include/asm/msr-index.h |  37 ++++
 arch/x86/include/asm/vmx.h       |   8 +
 arch/x86/kvm/cpuid.c             |  22 +-
 arch/x86/kvm/svm.c               |   6 +
 arch/x86/kvm/vmx.c               | 441 ++++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c               |  33 ++-
 10 files changed, 591 insertions(+), 68 deletions(-)
```
#### [PATCH 0/3] kvm: selftests: initial version of state save/restore
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

To be improved into a test for nested state save/restore

Paolo Bonzini (3):
  KVM: x86: ensures all MSRs can always be KVM_GET/SET_MSR'd
  kvm: selftests: ensure vcpu file is released
  kvm: selftests: add basic test for state save and restore

 arch/x86/kvm/hyperv.c                         |  27 +++-
 arch/x86/kvm/hyperv.h                         |   2 +-
 arch/x86/kvm/x86.c                            |  15 ++-
 tools/testing/selftests/kvm/Makefile          |   1 +
 tools/testing/selftests/kvm/include/x86.h     |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  18 ++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   1 +
 tools/testing/selftests/kvm/lib/x86.c         | 118 +++++++++++++++++
 tools/testing/selftests/kvm/state_test.c      | 123 ++++++++++++++++++
 9 files changed, 289 insertions(+), 20 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/state_test.c
```
#### [PATCH v9 00/13] KVM/s390: Hugetlbfs enablement
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With the page flag we now have a cleaner way to clear skeys for new
guest pmds. skey operations now also handle faults, as skeys for pmds
can not be saved in the PGSTEs when the pmd is invalid.

If there are no huge upcries, this will be the last version.

Branch:
git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git hlp_vsie
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=hlp_vsie

v9:
	* Added migration skey fault handling
	* s/vaddr/vmaddr/ on fault handling patch
	* Added some missed review
	* Fixed authorship for Dominik's patches

v8:
	* Fixed skey emulation pmd fault handling
	* Improved skey clearing for new pmds

v7:
	* Fixed locking between notification and gmap_idte
	* Dirty log rework

v6:
	* Added clearing of storage keys for newly mapped pmds
	* Split enablement in gmap and kvm part
	* Removed some rebase errors
	* Integrated changes proposed onlist

v5:
	* Removed pmd splitting and userspace protection
	* Split up bigger patches
	* Cleanups

V4:
	* Split up vSIE patches
	* Added hpage module parameter disabling vSIE when set.
	* Added HPAGE capability that has to be enabled for huge guests

V3:
	* Moved splitting to the front.
	* Cleanups

V2:
	* Incorporated changes from David's cleanup
	* Now flushing with IDTE_NODAT for protection transfers.
	* Added RRBE huge page handling for g2 -> g3 skey emulation
	* Added documentation for capability
	* Renamed GMAP_ENTRY_* constants
	* Added SEGMENT hardware bits constants
	* Improved some patch descriptions
	* General small improvements
	* Introduced pte_from_pmd function

Dominik Dingel (2):
  s390/mm: Clear huge page storage keys on enable_skey
  s390/mm: hugetlb pages within a gmap can not be freed

Janosch Frank (11):
  s390/mm: Make gmap_protect_range more modular
  s390/mm: Abstract gmap notify bit setting
  s390/mm: Add gmap pmd linking
  s390/mm: Add gmap pmd notification bit setting
  s390/mm: Add gmap pmd invalidation and clearing
  s390/mm: Add huge page dirty sync support
  s390/mm: Clear skeys for newly mapped huge guest pmds
  s390/mm: Add huge pmd storage key handling
  KVM: s390: Add skey emulation fault handling
  s390/mm: Add huge page gmap linking support
  KVM: s390: Add huge page enablement control

 Documentation/virtual/kvm/api.txt   |  16 ++
 arch/s390/include/asm/gmap.h        |  10 +
 arch/s390/include/asm/hugetlb.h     |   5 +-
 arch/s390/include/asm/mmu.h         |   2 +
 arch/s390/include/asm/mmu_context.h |   1 +
 arch/s390/include/asm/pgtable.h     |  13 +-
 arch/s390/kvm/kvm-s390.c            |  82 ++++++-
 arch/s390/kvm/priv.c                | 105 ++++++---
 arch/s390/mm/gmap.c                 | 455 ++++++++++++++++++++++++++++++++++--
 arch/s390/mm/hugetlbpage.c          |  24 ++
 arch/s390/mm/pageattr.c             |   6 +-
 arch/s390/mm/pgtable.c              | 142 +++++++----
 include/uapi/linux/kvm.h            |   1 +
 13 files changed, 741 insertions(+), 121 deletions(-)
```
#### [PATCH v7 00/22]  vfio-ap: guest dedicated crypto adapters
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

2 weeks ago we had a final one week bringup session with all involved
folks for crypto passthrough: ap bus, kernel, libvirt. v7 is the result
of the workshop + one additional week of testing and further fixing by
Halil, Pierre and Michael. As Tony is on vacation, I am going to send
out this patch set. From my point of view this is now stable
interface-wise.  Plan is that Tony acts as a maintainer, together with
Halil and Pierre for the vfio-ap driver.  As this is mostly related to
the AP bus, this will go via Martin Schwidefskys tree (but with review
on the kernel.org kvm and s390 list).  When KVM code is involved, this
will probably involve a topic branch that I will merge as well in
kvm-next.

Alex, Kirti: Can you have a look again and ack the vfio/mdev part?

FWIW, the patches are also available at
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=ap

Notes:
=====

Patches 1-6 (by Harald) posted with this series are forthcoming via
Martins tree and are base changes in the ap driver/bus that we use as a
foundation. They have been included here because some of the functions
in this patch series are dependent upon them.

Testers, the good news is that this patch series works with the v6 QEMU
patches. The bad news is that there is no new QEMU patchset version
yet. 

Limitations:
===========

When an AP queue is bound to the vfio_ap driver and in use by a mediated
device (assigned), it must not be reassigned back to the host zcrypt
driver by the host admin. Otherwise the queue might be used in the host
and guest at the same time. (A misconfiguration that acts as shoot yourself
in the foot similar to giving a disk to two guests. We probably will
fence this off in a later version)


Abstract:
========

On s390, we have cryptographic coprocessor cards, which are modeled on
Linux as devices on the AP bus. Each card can be partitioned into domains
which can be thought of as a set of hardware registers for processing 
crypto commands. Crypto commands are sent to a specific domain within a
card is via a queue which is identified as a (card,domain) tuple. We model 
this something like the following (assuming we have access to cards 3 and 
4 and domains 1 and 2):

AP -> card3 -> queue (3,1)
            -> queue (3,2)
   -> card4 -> queue (4,1)
            -> queue (4,2)

If we want to virtualize this, we can use a feature provided by the
hardware. We basically attach a satellite control block to our main
hardware virtualization control block and the hardware takes care of
most of the rest.

For this control block, we don't specify explicit tuples, but a list of
cards and a list of domains. The guest will get access to the cross
product.

Because of this, we need to take care that the lists provided to
different guests don't overlap; i.e., we need to enforce sane
configurations. Otherwise, one guest may get access to things like
secret keys for another guest.

The idea of this patch set is to introduce a new device, the matrix
device. This matrix device hangs off a different root and acts as the
parent node for mdev devices.

If you now want to give the tuples (4,1) and (4,2), you need to do the
following:

- Make sure the queues (4,1) and (4,2) belong to vfio_ap (see patches
  #5 and #6)
- Create the mediated device.
- Assign card 4 and domains 1 and 2 to the mediated device
- Optionally activate the mediated device.

QEMU will now simply consume the mediated device and things should work.

For a complete description of the architecture and concepts underlying
the design, see the Documentation/s390/vfio-ap.txt file included with this
patch set.

v6 => v7 Change log:
===================
* The AP bus gained the ability to designate queues as 'used by host'
  or as 'used by alternate driver(s)'. This allows us to authorise access
  (via the CRYCB) to queues that are not currently bound to the vfio_ap
  driver. If a  vfio_ap owned queue diss- and reapears it's guaranteed
  to get bound back to the vfio_ap driver.
* The mediated device gained an 'activate' attribute. Sharing conflicts are
  checked on activation now. If the device was not activated, the mdev
  open still implies activation. An active ap_matrix_mdev device claims
  it's resources -- an inactive does not.
* An active ap_matrix_mdev device can not be removed. An ap_matrix_mdev
  that is hooked up with a guest can not be deactivated.
* An active ap_matrix_mdev device rejects assign_* and deassign_*
  operations. Thus changing the CRYCB masks of a guest in order to
  accomplys certain hotplug scenarios is planned, but not supported yet. In
  previous versions it was possible to do those operations on a ap_matrix_mdev
  that is hooked up to a guest, but the changes would take effect on the next
  mdev_open. 
* Synchronisation was reworked.
* The sysfs path of the parent device changed from /sys/devices/vfio_ap/matrix/
  to /sys/devices/virtual/misc/vfio_ap/. The parent device is a misc
  device now.
* The severity for most of the messages were reduced form error to
  warning.
*  We are not as thick headed about the zapq as we used to be in v6.

v5 => v6 Change log:
===================
* Added VSIE support - thanks to Pierre Morel
* Added VFIO_DEVICE_RESET ioctl
* Zeroizing AP queues when mediated device released and when 
  VFIO_DEVICE_RESET ioctl is invoked
* Removed /arch/s390/kvm/kvm-ap.c and arch/s390/include/asm/kvm-ap.h and
  moved guest matrix configuration into vfio driver
* Removed temporary interfaces to be supplied by AP bus
* Made the variable that keeps track of mdev instance count an atomic_t
  type
* Removed code iterating through vm_list to determine if another guest has
  a queue .... not keep a list of matrix_mdev devices and verify against
  that list. Removes the need for the kvm_lock.
* Added a sysfs attribute for the mediated matrix device to display the
  matrix contained in the guest's CRYCB if a guest is using the mdev.


v4 => v5 Change log:
===================
* Verify AP queues bound to driver in mediated device open callback, prior
  to configuring the matrix in the CRYCB
* Implement VFIO_DEVICE_RESET ioctl
* Zeroize queues on guest entry and exit
* Removed vnet from all email IBM email addresses referenced
* Add synchronization in mdev create/remove and open/release.
* Added code to mdev open callback to ensure not more than one vfio-ap
  device can be opened by a guest.
* Interpret AP instructions by default
* Removed patch implementing interface to enable/disable AP interpretation,
  since that will now be done by default
* Removed patch to reset crypto attributes for ALL vcpus. That will be 
  submitted as a single patch since it will not be needed in this series - 
  i.e., it was called from the interface to enable/disable AP instructions
* All code for initializing crypto for a guest has been moved back to 
  kvm-s390.c, kvm_s390_crypto_init(kvm) function
* Maintaining a module reference count for the vfio_ap module so it is not
  removed while a guest with AP devices is running.
  


v3 => v4 Change log:
===================
* Resolved issue with enabling ZCRYPT when KVM is enabled by using
  #ifdef ZCRYPT in relevant functions
* Added patch with a new function for resetting the crypto attributes
  for all vcpus to resolve the issue raised with running vcpus getting out 
  of sync.
* Removed KVM_S390_VM_CRYPTO_INTERPRET_AP: Setting interpretive exec mode
  from vfio_ap driver when mdev device is opened.


v2 => v3 Change log:
===================
* Set APIE in VCPU setup function
* Renamed patch 13/15:
    KVM: s390: Configure the guest's CRYCB
    KVM: s390: Configure the guest's AP devices
* Fixed problem with building arch/s390/kvm/kvm-ap.c when CONFIG_ZCRYPT
  not selected 
* Removed patch introducing VSIE support for AP pending further 
  investigation
* Initialized AP maximum mask sizes - i.e., APM, AQM and ADM - from info
  returned from PQAP(QCI) function
* Introduced a new device attribute to the KVM_S390_VM_CRYPTO attribute
  group for setting a flag via the KVM_SET_DEVICE_ATTR ioctl to indicate
  whether ECA_APIE should be set or not. The flag is used in the 
  kvm_s390_vcpu_crypto_setup() function to set ECA_APIE in the SIE block. 
  

v1 => v2 Change log:
===================
* Added documentation vfio-ap.txt
* Renamed vfio_ap_matrix module and device driver to vfio_ap
* Use device core device list instead of maintaining list of matrix
  devices in driver
* Added VSIE support for AP
* Create matrix device before registering VFIO AP device driver with the
  AP bus
* Renamed the following files in drivers/s390/crypto:
  * vfio_ap_matrix.drv -> vfio_ap_drv
  * vfio_ap_matrix_private.h -> vfio_ap_private.h
  * vfio_ap_matrix_ops.c -> vfio_ap_ops.c
* arch/s390/include/asm/kvm/ap-matrix-config.h
  * Renamed to kvm-ap.h
  * Changed the data type of the bit mask fields for the matrix structure
    to unsigned long and create them with DECLARE_BITMAP 
  * Changed #define prefixes from AP_MATRIX to KVM_AP
  * Changed function and structure prefixes from ap_matrix to kvm_ap
  * Added function interface to check if AP Extended Addressing (APXA)
    facility is installedCRYCB_FORMAT_MASK
  * Added function interface to get the maximum ID for AP mask type
  * Added function interface to set the AP execution mode
* arch/s390/kvm/ap-matrix-config.c
  * Renamed to kvm-ap.c
  * Changed function prefixes from ap_matrix to kvm_ap
  * Added function to check if AP Extended Addressing (APXA) facility is
    installed
  * Added function to get the maximum ID for AP mask type
  * Added function to set the AP execution mode
  * Added a boolean parameter to the functions that retrieve the APM, AQM
    and ADM bit mask fields from the CRYCB. If true, then the function
    will clear the bits in the mask before returning a reference to it
  * Added validation to verify that APM, AQM and ADM bits that are set do
    not exceed the maximum ID value allowed
  * 
* arch/s390/include/asm/kvm_host.h
  * Changed defined for ECA_AP to ECA_APIE - interpretive execution mode
  * Added a flag to struct kvm_s390_crypto to indicate whether the 
    KVM_S390_VM_CPU_FEAT_AP CPU model feature for AP facilities is set
  * Added two CPU facilities features to set STFLE.12 and STFLE.15
* arch/s390/kvm/kvm-s390.c
  * Added initialization for new KVM_S390_VM_CPU_FEAT_AP CPU model feature
  * Removed kvm_s390_apxa_installed() function
  * Changed call to kvm_s390_apxa_installed() which has been removed to a
    call to new kvm_ap_apxa_installed() function.
  * Added code to kvm_s390_vcpu_crypto_setup() to set the new CPU model 
    feature flag in the kvm_s390_crypto structure 
  * Added CRYCB_FORMAT_MASK to mask CRYCBD
* arch/s390/tools/gen_facilities.c
  * Added STFLE.12 and STFLE.15 to struct facility _def
* drivers/s390/crypto/vfio_ap_matrix_private.h
  * Changed name of file to vfio_ap.private.h
  * Changed #define prefixes from VFIO_AP_MATRIX to VFIO_AP
  * struct ap_matrix: removed list fields and locks
  * struct vfio_ap_queue: removed list field
  * Renamed functions ap_matrix_mdev_register and ap_matrix_mdev_unregister
    to vfio_ap_mdev_register and vfio_ap_mdev_unregister respectively
* drivers/s390/crypto/vfio_ap_matrix_drv.c
  * Renamed file to drivers/s390/crypto/vfio_ap_drv.c
  * Changed all #define, structure and function prefixes to vfio_ap
  * probe function
    * Changed root device name for the matrix device to vfio_ap:
      i.e., /sys/devices/vfio_ap/matrix
    * No longer storing the AP queue device in a list, it is retrievablegit
      via the device core
    * Removed unnecessary check whether matrix device exists
    * Store the vfio_ap_queue structure in the private field of the 
      ap_queue structure rather than using list interface
  * remove function
    * Retrieve vfio_ap_queue structure from the struct ap_queue private 
      data rather than from a list
  * Removed unnecessary check 
* drivers/s390/crypto/vfio_ap_matrix_ops.c
  * Renamed file to vfio_ap_ops.c
  * Changed #define prefixes from AP_MATRIX to VFIO_AP
  * Changed function name prefixes from ap_matrix to vfio_ap
  * Removed ioctl to configure the CRYCB
  * create function
    * Removed ap_matrix_mdev_find_by_uuid() function - function is provided
      by mdev core
    * Removed available_instances verification, provided by mdev core
    * Removed check to see if mediated device exists, handled by mdev core
  * notifier function
    * Configuring matrix here instead of via ioctl
    * Set interpretive execution mode for all VCPUs
   * Removed R/O attributes to display adapters and domains
   * Added an R/O attribute to display the matrix
  * assign_control_domain mdev attribute:
    * Removed check to see if the domain is installed on the linux host
    * Added check to verify the control domain ID does not exceed the max 
      value
  * assign_adapter mdev attribute:
    * Added check to verify the adapter ID does not exceed the max 
      value
    * If any APQNs configured for the mediated matrix device that
      have an APID matching the adapter ID being assigned are not
      bound to the vfio_ap device driver then it is assumed that the APQN
      is bound to another driver and assignment will fail
  * assign_domain mdev attribute:
    * Added check to verify the domain ID does not exceed the max 
      value
    * If any APQNs configured for the mediated matrix device that
      have an APQI matching the domain ID being assigned are not
      bound to the vfio_ap device driver then it is assumed that the APQN
      is bound to another driver and assignment will fail
* tools/arch/s390/include/uapi/asm/kvm.h
  * removed  KVM_S390_VM_CPU_FEAT_AP feature definition

Harald Freudenberger (6):
  s390/zcrypt: Add ZAPQ inline function.
  s390/zcrypt: Review inline assembler constraints.
  s390/zcrypt: Show load of cards and queues in sysfs
  s390/zcrypt: Integrate ap_asm.h into include/asm/ap.h.
  s390/zcrypt: AP bus support for alternate driver(s)
  s390/zcrypt: Support for apmask and aqmask change on live system

Pierre Morel (1):
  KVM: s390: Handling of Cypto control block in VSIE

Tony Krowiak (15):
  KVM: s390: refactor crypto initialization
  s390: vfio-ap: base implementation of VFIO AP device driver
  s390: vfio-ap: register matrix device with VFIO mdev framework
  s390: vfio-ap: sysfs interfaces to configure adapters
  s390: vfio-ap: sysfs interfaces to configure domains
  s390: vfio-ap: sysfs interfaces to configure control domains
  s390: vfio-ap: sysfs interface to view matrix mdev matrix
  s390: vfio-ap: sysfs interface to activate mdev matrix
  KVM: s390: interfaces to clear CRYCB masks
  s390: vfio-ap: implement mediated device open callback
  s390: vfio-ap: implement VFIO_DEVICE_GET_INFO ioctl
  s390: vfio-ap: zeroize the AP queues.
  s390: vfio-ap: implement VFIO_DEVICE_RESET ioctl
  KVM: s390: CPU model support for AP virtualization

 Documentation/s390/vfio-ap.txt        | 591 ++++++++++++++++
 MAINTAINERS                           |  12 +
 arch/s390/Kconfig                     |  11 +
 arch/s390/include/asm/ap.h            | 286 +++++++-
 arch/s390/include/asm/kvm_host.h      |   6 +
 arch/s390/include/uapi/asm/kvm.h      |   1 +
 arch/s390/kvm/kvm-s390.c              | 110 +--
 arch/s390/kvm/vsie.c                  | 224 +++++-
 arch/s390/tools/gen_facilities.c      |   2 +
 drivers/s390/crypto/Makefile          |   4 +
 drivers/s390/crypto/ap_asm.h          | 236 -------
 drivers/s390/crypto/ap_bus.c          | 312 ++++++++-
 drivers/s390/crypto/ap_bus.h          |  29 +
 drivers/s390/crypto/ap_card.c         |   1 -
 drivers/s390/crypto/ap_queue.c        |   1 -
 drivers/s390/crypto/vfio_ap_drv.c     | 141 ++++
 drivers/s390/crypto/vfio_ap_ops.c     | 966 ++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h | 104 +++
 drivers/s390/crypto/zcrypt_card.c     |  12 +
 drivers/s390/crypto/zcrypt_cex2a.c    |   2 +
 drivers/s390/crypto/zcrypt_cex4.c     |   2 +
 drivers/s390/crypto/zcrypt_pcixcc.c   |   2 +
 drivers/s390/crypto/zcrypt_queue.c    |  12 +
 include/uapi/linux/vfio.h             |   2 +
 24 files changed, 2711 insertions(+), 358 deletions(-)
 create mode 100644 Documentation/s390/vfio-ap.txt
 delete mode 100644 drivers/s390/crypto/ap_asm.h
 create mode 100644 drivers/s390/crypto/vfio_ap_drv.c
 create mode 100644 drivers/s390/crypto/vfio_ap_ops.c
 create mode 100644 drivers/s390/crypto/vfio_ap_private.h
```
