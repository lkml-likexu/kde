

#### [PATCH net-next V2 00/11] vhost_net TX batching
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi all:

This series tries to batch submitting packets to underlayer socket
through msg_control during sendmsg(). This is done by:

1) Doing userspace copy inside vhost_net
2) Build XDP buff
3) Batch at most 64 (VHOST_NET_BATCH) XDP buffs and submit them once
   through msg_control during sendmsg().
4) Underlayer sockets can use XDP buffs directly when XDP is enalbed,
   or build skb based on XDP buff.

For the packet that can not be built easily with XDP or for the case
that batch submission is hard (e.g sndbuf is limited). We will go for
the previous slow path, passing iov iterator to underlayer socket
through sendmsg() once per packet.

This can help to improve cache utilization and avoid lots of indirect
calls with sendmsg(). It can also co-operate with the batching support
of the underlayer sockets (e.g the case of XDP redirection through
maps).

Testpmd(txonly) in guest shows obvious improvements:

Test                /+pps%
XDP_DROP on TAP     /+44.8%
XDP_REDIRECT on TAP /+29%
macvtap (skb)       /+26%

Netperf TCP_STREAM TX from guest shows obvious improvements on small
packet:

    size/session/+thu%/+normalize%
       64/     1/   +2%/    0%
       64/     2/   +3%/   +1%
       64/     4/   +7%/   +5%
       64/     8/   +8%/   +6%
      256/     1/   +3%/    0%
      256/     2/  +10%/   +7%
      256/     4/  +26%/  +22%
      256/     8/  +27%/  +23%
      512/     1/   +3%/   +2%
      512/     2/  +19%/  +14%
      512/     4/  +43%/  +40%
      512/     8/  +45%/  +41%
     1024/     1/   +4%/    0%
     1024/     2/  +27%/  +21%
     1024/     4/  +38%/  +73%
     1024/     8/  +15%/  +24%
     2048/     1/  +10%/   +7%
     2048/     2/  +16%/  +12%
     2048/     4/    0%/   +2%
     2048/     8/    0%/   +2%
     4096/     1/  +36%/  +60%
     4096/     2/  -11%/  -26%
     4096/     4/    0%/  +14%
     4096/     8/    0%/   +4%
    16384/     1/   -1%/   +5%
    16384/     2/    0%/   +2%
    16384/     4/    0%/   -3%
    16384/     8/    0%/   +4%
    65535/     1/    0%/  +10%
    65535/     2/    0%/   +8%
    65535/     4/    0%/   +1%
    65535/     8/    0%/   +3%

Please review.

Thanks

Changes from V1:

- don't hold page refcnt for XDP_DROP
- release page if build_skb() fails
- introduce a helper to build skb for the path of no batching mode
- rename tun_do_xdp() as tun_xdp_act() and use negative for reporting
  errors instead of a pointer to integer
- introduce a num field in tun_msg_ctl
- introduce a new structure for storing metadata in the head of XDP
  packet
- do not store batche XDP inside vhoet_net_virtqueue

Jason Wang (11):
  net: sock: introduce SOCK_XDP
  tuntap: switch to use XDP_PACKET_HEADROOM
  tuntap: enable bh early during processing XDP
  tuntap: simplify error handling in tun_build_skb()
  tuntap: tweak on the path of skb XDP case in tun_build_skb()
  tuntap: split out XDP logic
  tuntap: move XDP flushing out of tun_do_xdp()
  tun: switch to new type of msg_control
  tuntap: accept an array of XDP buffs through sendmsg()
  tap: accept an array of XDP buffs through sendmsg()
  vhost_net: batch submitting XDP buffers to underlayer sockets

 drivers/net/tap.c      |  88 +++++++++++++-
 drivers/net/tun.c      | 267 ++++++++++++++++++++++++++++++++---------
 drivers/vhost/net.c    | 181 +++++++++++++++++++++++++---
 include/linux/if_tun.h |  14 +++
 include/net/sock.h     |   1 +
 5 files changed, 471 insertions(+), 80 deletions(-)
```
#### [RFC PATCH 0/2] virtio/s390: fix some races in virtio-ccw 
##### From: Halil Pasic <pasic@linux.ibm.com>

```c

Came up with these while investigating
https://bugzilla.linux.ibm.com/show_bug.cgi?id=170918

It's RFC because I don't really understand the original design, and I'm
not sure this is the best way to fix the problems. Thus took I took
minimal intrusive approach.

Halil Pasic (2):
  virtio/s390: avoid race on vcdev->config
  virtio/s390: fix race in ccw_io_helper()

 drivers/s390/virtio/virtio_ccw.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)
```
#### [PATCH v10 00/26] guest dedicated crypto adapters
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>
From: Tony Krowiak <akrowiak@linux.ibm.com>

```c

From: Tony Krowiak <akrowiak@linux.ibm.com>

Notes:
=====

Patches 1-2 (by David) are posted with this series because they are not
currently available in our master branch, upon which this series is based,
and because this series is dependent upon them.  

This patch series works with the v8 QEMU patches.

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

v9 => v10 Change log:
===================
* Replaced statically allocated with dynamically allocated matrix device
* Made changes to drivers/iommu/Kconfig and arch/s390/Kconfig to fix the
  dependency chain so that make menuconfig can be used to configure VFIO_AP
* Added KVM device attributes to enable/disable hw interpretation of AP
  instructions from userspace.
* Return more meaningful error values from mediated matrix device
  assignment sysfs interfaces
* No longer enforcing convention that the ADM is a superset of the AQM at
  for guest level 2
* Broke 2 vSIE patches into several to make it easier to review them
* Reworked vSIE patches to handle various CRYCB formats
v8 => v9 Change log:
===================
* Removed /sys/devices/virtual/misc/vfio_ap device and restored 
  /sys/devices/vfio_ap/matrix device as parent of mediated matrix devices
* Return boolean from ap_configuration_available() in ap.h instead of 0 or
  an error.
* Miscellaneous changes due to review comments 

v7 => v8 Change log:
===================
* Removed the AP bus gained the ability to designate queues as 'used by
  host' or as 'used by alternate driver(s)'. 
* Removed 'activate' attribute from mediated device.
* Do consistency checking during device assignment:
  1. Verify that APQNs assigned to the mediated device are bound to the 
     VFIO AP device driver
  2. Verify that no APQN assigned to the mediated matrix device is assigned
     to any other mediated matrix device.
* The attributes of a mediated matrix device that is in use by a guest can
  not be changed - i.e., no device assignment/unassignment allowed
* A mediated matrix device that is in use by a guest can not be removed.
* Removed all printk logging from VFIO AP driver; allowing return codes
  from interfaces to describe the error.
* Reworked the handling of the CRYCB in vSIE based upon patches introduced
  by David in the mainline. 

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

v4 => v5 Change log:
===================
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
    * No longer storing the AP queue device in a list, it is retrievable via
      the device core
    * Removed unnecessary check whether matrix device exists
    * Store the vfio_ap_queue structure in the private field of the ap_queue
      structure rather than using list interface
  * remove function
    * Retrieve vfio_ap_queue structure from the struct ap_queue private 
      data rather than from a list
  * Removed unnecesary check 
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
      bound to the vfio_ap device driver then it is assumed that the APQN is 
      bound to another driver and assignment will fail
  * assign_domain mdev attribute:
    * Added check to verify the domain ID does not exceed the max 
      value
    * If any APQNs configured for the mediated matrix device that
      have an APQI matching the domain ID being assigned are not
      bound to the vfio_ap device driver then it is assumed that the APQN is 
      bound to another driver and assignment will fail
* tools/arch/s390/include/uapi/asm/kvm.h
  * removed  KVM_S390_VM_CPU_FEAT_AP feature definition

David Hildenbrand (2):
  KVM: s390: vsie: simulate VCPU SIE entry/exit
  KVM: s390: introduce and use KVM_REQ_VSIE_RESTART

Pierre Morel (9):
  KVM: s390: Clear Crypto Control Block when using vSIE
  KVM: s390: vsie: Do the CRYCB validation first
  KVM: s390: vsie: Make use of CRYCB FORMAT2 clear
  KVM: s390: vsie: Allow CRYCB FORMAT-2
  KVM: s390: vsie: allow CRYCB FORMAT-1
  KVM: s390: vsie: allow CRYCB FORMAT-0
  KVM: s390: vsie: allow guest FORMAT-0 CRYCB on host FORMAT-1
  KVM: s390: vsie: allow guest FORMAT-1 CRYCB on host FORMAT-2
  KVM: s390: vsie: allow guest FORMAT-0 CRYCB on host FORMAT-2

Tony Krowiak (15):
  KVM: s390: refactor crypto initialization
  s390: vfio-ap: base implementation of VFIO AP device driver
  s390: vfio-ap: register matrix device with VFIO mdev framework
  s390: vfio-ap: sysfs interfaces to configure adapters
  s390: vfio-ap: sysfs interfaces to configure domains
  s390: vfio-ap: sysfs interfaces to configure control domains
  s390: vfio-ap: sysfs interface to view matrix mdev matrix
  KVM: s390: interfaces to clear CRYCB masks
  s390: vfio-ap: implement mediated device open callback
  s390: vfio-ap: implement VFIO_DEVICE_GET_INFO ioctl
  s390: vfio-ap: zeroize the AP queues
  s390: vfio-ap: implement VFIO_DEVICE_RESET ioctl
  KVM: s390: device attrs to enable/disable AP interpretation
  KVM: s390: CPU model support for AP virtualization
  s390: doc: detailed specifications for AP virtualization

 Documentation/s390/vfio-ap.txt        |  778 ++++++++++++++++++++++++++
 MAINTAINERS                           |   12 +
 arch/s390/Kconfig                     |   11 +
 arch/s390/include/asm/kvm_host.h      |    7 +
 arch/s390/include/uapi/asm/kvm.h      |    3 +
 arch/s390/kvm/kvm-s390.c              |  134 +++--
 arch/s390/kvm/kvm-s390.h              |    1 +
 arch/s390/kvm/vsie.c                  |  208 +++++++-
 arch/s390/tools/gen_facilities.c      |    2 +
 drivers/iommu/Kconfig                 |    8 +
 drivers/s390/crypto/Makefile          |    4 +
 drivers/s390/crypto/vfio_ap_drv.c     |  153 ++++++
 drivers/s390/crypto/vfio_ap_ops.c     |  973 +++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |   88 +++
 include/uapi/linux/vfio.h             |    2 +
 15 files changed, 2324 insertions(+), 60 deletions(-)
 create mode 100644 Documentation/s390/vfio-ap.txt
 create mode 100644 drivers/s390/crypto/vfio_ap_drv.c
 create mode 100644 drivers/s390/crypto/vfio_ap_ops.c
 create mode 100644 drivers/s390/crypto/vfio_ap_private.h
```
