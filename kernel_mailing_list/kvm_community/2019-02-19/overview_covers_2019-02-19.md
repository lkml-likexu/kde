

#### [PATCH v2 0/2] Inject a PMI for KVM Guest when ToPA buffer is filled
##### From: Luwei Kang <luwei.kang@intel.com>

```c

Each intel processor trace table of physical addresses (ToPA) entry
has an INT bit. If this bit is set, the processor will signal a
performance-monitoring interrupt (PMI) when the corresponding trace
output region is filled. This patch set will inject a PMI for Intel
Processor Trace when ToPA buffer is filled.

>From v1:
 - Exported a global function pointers may not a good chioce.
   Add a new member in kvm_guest_cbs to send Intel PT PMI for KVM guest.

Luwei Kang (2):
  KVM: x86: Inject PMI for KVM guest
  KVM: x86: Add support of clear Trace_ToPA_PMI status

 arch/x86/events/intel/core.c     |  6 +++++-
 arch/x86/include/asm/kvm_host.h  |  1 +
 arch/x86/include/asm/msr-index.h |  8 ++++++++
 arch/x86/kvm/vmx/pmu_intel.c     |  8 +++++++-
 arch/x86/kvm/x86.c               | 10 ++++++++++
 include/linux/perf_event.h       |  1 +
 6 files changed, 32 insertions(+), 2 deletions(-)
```
#### [PATCH 0/8] VFIO Device states interface in GVT
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c

This patchset provides GVT vGPU with device states control and
interfaces to get/set device data.


Desgin of device state control and interfaces to get/set device data
====================================================================

CODE STRUCTURES
---------------
/* Device State region type and sub-type */
#define VFIO_REGION_TYPE_DEVICE_STATE           (1 << 1)
#define VFIO_REGION_SUBTYPE_DEVICE_STATE_CTL       (1)
#define VFIO_REGION_SUBTYPE_DEVICE_STATE_DATA_CONFIG      (2)
#define VFIO_REGION_SUBTYPE_DEVICE_STATE_DATA_MEMORY      (3)
#define VFIO_REGION_SUBTYPE_DEVICE_STATE_DATA_DIRTYBITMAP (4)

#define VFIO_DEVICE_STATE_INTERFACE_VERSION 1
#define VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY 1
#define VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY 2

#define VFIO_DEVICE_STATE_RUNNING 0 
#define VFIO_DEVICE_STATE_STOP 1
#define VFIO_DEVICE_STATE_LOGGING 2

#define VFIO_DEVICE_DATA_ACTION_GET_BUFFER 1
#define VFIO_DEVICE_DATA_ACTION_SET_BUFFER 2

struct vfio_device_state_ctl {
	__u32 version;	  /* ro, version of device control interface*/
	__u32 device_state;       /* VFIO device state, wo */
	__u32 caps;		 /* ro */
        struct {
		__u32 action;  /* wo, GET_BUFFER or SET_BUFFER */ 
		__u64 size;    /*rw, total size of device config*/
	} device_config;
	struct {
		__u32 action;    /* wo, GET_BUFFER or SET_BUFFER */ 
		__u64 size;     /* rw, total size of device memory*/  
                __u64 pos;/*chunk offset in total buffer of device memory*/
	} device_memory;
	struct {
		__u64 start_addr; /* wo */
		__u64 page_nr;   /* wo */
	} system_memory;
};

DEVICE DATA
-----------
A VFIO device's data can be divided into 3 categories: device config,
device memory and system memory dirty pages.

Device Config: such kind of data like MMIOs, page tables...
               Every device is supposed to possess device config data.
               Usually the size of device config data is small (no big
               than 10M), and it needs to be loaded in certain strict
               order.
               Therefore no dirty data logging is enabled for device
               config and it must be got/set as a whole.

Device Memory: device's internal memory, standalone and outside system
               memory.  It is usually very big.
               Not all device has device memory. Like IGD only uses system
               memory and has no device memory.

System Memory Dirty Pages: A device can produce dirty pages in system
               memory. 


DEVICE STATE REGIONS
---------------------
A VFIO device driver needs to register two mandatory regions and optionally
another two regions if it plans to support device state management.

So, there are up to four regions in total.
one is control region (region CTL) which is accessed via read/write system
call from user space;
the left three are data regions which are mmaped into user space and can be
accessed in the same way as accessing memory from user space.
(If data regions failed to be mmaped into user space, the way of read/write
system calls from user space is also valid).

1. region CTL:
          Mandatory.
          This is a control region.
          Its layout is defined in struct vfio_device_state_ctl.
          Reading from this region can get version, capabilities and data
          size of device state interfaces.
          Writing to this region can set device state, data size and
          choose which interface to use, i.e, among
          "get device config buffer", "set device config buffer",
          "get device memory buffer", "set device memory buffer",
          "get system memory dirty bitmap". 
2. region DEVICE_CONFIG
          Mandatory.
          This is a data region that holds device config data.
          It is able to be mmaped into user space.
3. region DEVICE_MEMORY
          Optional.
          This is a data region that holds device memory data.
          It is able to be mmaped into user space.
4. region DIRTY_BITMAP
          Optional.
          This is a data region that holds bitmap of dirty pages in system
          memory that a VFIO devices produces.
          It is able to be mmaped into user space.


DEVICE STATES
-------------
Four states are defined for a VFIO device:
        RUNNING, RUNNING & LOGGING, STOP & LOGGING, STOP.
They can be set by writing to device_state field of vfio_device_state_ctl
region.

LOGGING state is a special state that it CANNOT exist independently.
It must be set alongside with state RUNNING or STOP, i.e, 
        RUNNING & LOGGING, STOP & LOGGING

It is used for dirty data logging both for device memory and system memory.

LOGGING only impacts device/system memory.
Device config should be always accessible and return whole config snapshot
regardless of LOGGING state.

Typical state transition flows for VFIO devices are:
    (a) RUNNING --> RUNNING & LOGGING --> STOP & LOGGING --> STOP
    (b) RUNNING --> STOP --> RUNNING

RUNNING: In this state, a VFIO device is in active state ready to receive
         commands from device driver.
         interfaces includes "get device config buffer", "get device config
         size", "get device memory buffer", "get device memory size"
         return whole data snapshot.
         "get system memory dirty bitmap" returns empty bitmap.
         It is the default state that a VFIO device enters initially.

STOP:	 In this state, a VFIO device is deactivated to interact with
         device driver.
         "get device config buffer", "get device config size"
         "get device memory buffer", "get device memory size",
          return whole data snapshot.
         "get system memory dirty bitmap" returns empty bitmap.

RUNNING & LOGGING: In this state, a VFIO device is in active state.
         "get device config buffer", "get device config size" returns whole
         snapshot of device config. 
         "get device memory buffer", "get device memory size", "get system
         memory dirty bitmap" returns dirty data since last call to those
         interfaces.

STOP & LOGGING: In this state, the VFIO device is deactivated.
         "get device config buffer", "get device config size" returns whole
         snapshot of device config. 
         "get device memory buffer", "get device memory size", "get system
         memory dirty bitmap" returns dirty data since last call to those
         interfaces.

Note:
The reason why RUNNING is the default state is that device's active state
must not depend on device state interface.
It is possible that region vfio_device_state_ctl fails to got registered.
In that condition, a device needs be in active state by default. 


DEVICE DATA CAPS
------------------
Device Config capability is by default on, no need to set this cap.

For devices that have devcie memory, it is required to expose DEVICE_MEMORY
capability.
#define VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY 1

For devices producing dirty pages in system memory, it is required to
expose cap SYSTEM_MEMORY in order to get dirty bitmap in certain range of
system memory.
#define VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY 2

see section "DEVICE STATE INTERFACE" for "get caps" interface to get device
data caps from userspace VFIO.


DEVICE STATE INTERFACES
------------------------
1. get version
   (1) user space calls read system call on "version" field of region CTL.
   (2) VFIO driver writes version number of device state interfaces to the
       "version" field of region CTL.

2. get caps
   (1) user space calls read system call on "caps" field of region CTL.
   (2) if a VFIO device has huge device memory, VFIO driver reports
       VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY in "caps" field of region CTL.
       if a VFIO device produces dirty pages in system memory, VFIO driver
       reports VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY in "caps" field of
       region CTL.

3. set device state
   (1) user space calls write system call on "device_state" field of region
       CTL.
   (2) device state transitions as:

       RUNNING -- start dirty data logging --> RUNNING & LOGGING 
       RUNNING -- deactivate --> STOP
       RUNNING -- deactivate & start dirty data longging --> STOP & LOGGING
       RUNNING & LOGGING -- stop dirty data logging --> RUNNING
       RUNNING & LOGGING -- deactivate --> STOP & LOGGING
       RUNNING & LOGGING -- deactivate & stop dirty data logging --> STOP
       STOP -- activate --> RUNNING
       STOP -- start dirty data logging --> STOP & LOGGING
       STOP -- activate & start dirty data logging --> RUNNING & LOGGING
       STOP & LOGGING -- stop dirty data logging --> STOP
       STOP & LOGGING -- activate --> RUNNING & LOGGING
       STOP & LOGGING -- activate & stop dirty data logging --> RUNNING

4. get device config size
   (1) user space calls read system call on "device_config.size" field of
       region CTL for the total size of device config snapshot.
   (2) VFIO driver writes device config data's total size in
       "device_config.size" field of region CTL.

5. set device config size
   (1) user space calls write system call.
       total size of device config snapshot --> "device_config.size" field
       of region CTL.
   (2) VFIO driver reads device config data's total size from
       "device_config.size" field of region CTL.

6 get device config buffer
   (1) user space calls write system call.
       "GET_BUFFER" --> "device_config.action" field of region CTL.
   (2) VFIO driver
       a. gets whole snapshot for device config 
       b. writes whole device config snapshot to region
       DEVICE_CONFIG.
   (3) user space reads the whole of device config snapshot from region
       DEVICE_CONFIG.
 
7. set device config buffer
   (1) user space writes whole of device config data to region
       DEVICE_CONFIG.
   (2) user space calls write system call.
       "SET_BUFFER" --> "device_config.action" field of region CTL.
   (3) VFIO driver loads whole of device config from region DEVICE_CONFIG.

8. get device memory size
   (1) user space calls read system call on "device_memory.size" field of
       region CTL for device memory size.
   (2) VFIO driver
       a. gets device memory snapshot (in state RUNNING or STOP), or
          gets device memory dirty data (in state RUNNING & LOGGING or
          state STOP & LOGGING)
       b. writes size in "device_memory.size" field of region CTL
 
9. set device memory size
   (1) user space calls write system call on "device_memory.size" field of
       region CTL to set total size of device memory snapshot.
   (2) VFIO driver reads device memory's size from "device_memory.size"
       field of region CTL.


10. get device memory buffer
   (1) user space calls write system.
       pos --> "device_memory.pos" field of region CTL,
       "GET_BUFFER" --> "device_memory.action" field of region CTL.
       (pos must be 0 or multiples of length of region DEVICE_MEMORY).
   (2) VFIO driver writes N'th chunk of device memory snapshot/dirty data
       to region DEVICE_MEMORY.
       (N equals to pos/(region length of DEVICE_MEMORY))
   (3) user space reads the N'th chunk of device memory snapshot/dirty data
       from region DEVICE_MEMORY.
 
11. set device memory buffer
   (1) user space writes N'th chunk of device memory snapshot/dirty data to
       region DEVICE_MEMORY.
       (N equals to pos/(region length of DEVICE_MEMORY))
   (2) user space writes pos to "device_memory.pos" field and writes
       "SET_BUFFER" to "device_memory.action" field of region CTL.
   (3) VFIO driver loads N'th chunk of device memory snapshot/dirty data
       from region DEVICE_MEMORY.

12. get system memory dirty bitmap
   (1) user space calls write system call to specify a range of system
       memory that querying dirty pages.
       system memory's start address --> "system_memory.start_addr" field
       of region CTL,
       system memory's page count --> "system_memory.page_nr" field of
       region CTL.
   (2) if device state is not in RUNNING or STOP & LOGGING,
       VFIO driver returns empty bitmap; otherwise,
       VFIO driver checks the page_nr,
       if it's larger than the size that region DIRTY_BITMAP can support,
       error returns; if not,
       VFIO driver returns as bitmap to specify dirty pages that
       device produces since last query in this range of system memory .
   (3) usespace reads back the dirty bitmap from region DIRTY_BITMAP.


EXAMPLE USAGE
-------------
Take live migration of a VFIO device as an example to use those device
state interfaces.

Live migration save path:

(QEMU LIVE MIGRATION STATE --> DEVICE STATE INTERFACE --> DEVICE STATE)

MIGRATION_STATUS_NONE --> VFIO_DEVICE_STATE_RUNNING
 |
MIGRATION_STATUS_SAVE_SETUP
 |
 .save_setup callback -->
 get device memory size (whole snapshot size)
 get device memory buffer (whole snapshot data)
 set device state --> VFIO_DEVICE_STATE_RUNNING & VFIO_DEVICE_STATE_LOGGING
 |
MIGRATION_STATUS_ACTIVE
 |
 .save_live_pending callback --> get device memory size (dirty data)
 .save_live_iteration callback --> get device memory buffer (dirty data)
 .log_sync callback --> get system memory dirty bitmap
 |
(vcpu stops) --> set device state -->
 VFIO_DEVICE_STATE_STOP & VFIO_DEVICE_STATE_LOGGING
 |
.save_live_complete_precopy callback -->
 get device memory size (dirty data)
 get device memory buffer (dirty data)
 get device config size (whole snapshot size)
 get device config buffer (whole snapshot data)
 |
.save_cleanup callback -->  set device state --> VFIO_DEVICE_STATE_STOP
MIGRATION_STATUS_COMPLETED

MIGRATION_STATUS_CANCELLED or
MIGRATION_STATUS_FAILED
 |
(vcpu starts) --> set device state --> VFIO_DEVICE_STATE_RUNNING


Live migration load path:

(QEMU LIVE MIGRATION STATE --> DEVICE STATE INTERFACE --> DEVICE STATE)

MIGRATION_STATUS_NONE --> VFIO_DEVICE_STATE_RUNNING
 |
(vcpu stops) --> set device state --> VFIO_DEVICE_STATE_STOP
 |
MIGRATION_STATUS_ACTIVE
 |
.load state callback -->
 set device memory size, set device memory buffer, set device config size,
 set device config buffer
 |
(vcpu starts) --> set device state --> VFIO_DEVICE_STATE_RUNNING
 |
MIGRATION_STATUS_COMPLETED


Patch Orgnization
=================

The first 6 patches let vGPU view its base ggtt address as starting from
0. Before vGPU submitting workloads to HW, trap vGPU's workloads, scan
commands to patch them to start from base address of the ggtt partition
assiggned to the vGPU.

The latter two patches implements the VFIO device states interfaces.
Patch 7 implements loading device config data from vGPU and restoring
device config data into vGPU through GVT's internal interface
intel_gvt_save_restore.

Patch 8 exposes device states interfaces to userspace VFIO through VFIO
regions of type VFIO_REGION_TYPE_DEVICE_STATE. Through those regions, user
space VFIO can get/set device's state and data.


Yan Zhao (2):
  drm/i915/gvt: vGPU device config data save/restore interface
  drm/i915/gvt: VFIO device states interfaces

Yulei Zhang (6):
  drm/i915/gvt: Apply g2h adjust for GTT mmio access
  drm/i915/gvt: Apply g2h adjustment during fence mmio access
  drm/i915/gvt: Patch the gma in gpu commands during command parser
  drm/i915/gvt: Retrieve the guest gm base address from PVINFO
  drm/i915/gvt: Align the guest gm aperture start offset for live
    migration
  drm/i915/gvt: Apply g2h adjustment to buffer start gma for dmabuf

 drivers/gpu/drm/i915/gvt/Makefile      |   2 +-
 drivers/gpu/drm/i915/gvt/aperture_gm.c |   6 +-
 drivers/gpu/drm/i915/gvt/cfg_space.c   |   3 +-
 drivers/gpu/drm/i915/gvt/cmd_parser.c  |  31 +-
 drivers/gpu/drm/i915/gvt/dmabuf.c      |   3 +
 drivers/gpu/drm/i915/gvt/execlist.c    |   2 +-
 drivers/gpu/drm/i915/gvt/gtt.c         |  25 +-
 drivers/gpu/drm/i915/gvt/gtt.h         |   3 +
 drivers/gpu/drm/i915/gvt/gvt.c         |   1 +
 drivers/gpu/drm/i915/gvt/gvt.h         |  48 +-
 drivers/gpu/drm/i915/gvt/kvmgt.c       | 414 +++++++++++-
 drivers/gpu/drm/i915/gvt/migrate.c     | 863 +++++++++++++++++++++++++
 drivers/gpu/drm/i915/gvt/migrate.h     |  97 +++
 drivers/gpu/drm/i915/gvt/mmio.c        |  13 +
 drivers/gpu/drm/i915/gvt/mmio.h        |   1 +
 drivers/gpu/drm/i915/gvt/vgpu.c        |  11 +-
 include/uapi/linux/vfio.h              |  38 ++
 17 files changed, 1511 insertions(+), 50 deletions(-)
 create mode 100644 drivers/gpu/drm/i915/gvt/migrate.c
 create mode 100644 drivers/gpu/drm/i915/gvt/migrate.h
```
#### [kvm-unit-tests PATCH 0/3] s390x: Report string cleanup
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

For automated failure reporting we need unique report strings, to be
able to pinpoint the failing test. This series makes the reports
unique and cleans up sthyi reporting, so it is better readable.

This series is based on the skey fix, the pfmf patch will otherwise
result in a conflict.

Janosch Frank (3):
  s390x: Beautify sthyi report strings
  s390x: Beautify pfmf report strings
  s390x: Add prefix for dxc afp emulator test

 s390x/emulator.c |  3 ++-
 s390x/pfmf.c     | 18 +++++++++++++-----
 s390x/sthyi.c    | 45 +++++++++++++++++++++++++++++----------------
 3 files changed, 44 insertions(+), 22 deletions(-)
```
#### [PATCH 0/5] QEMU VFIO live migration
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c

This patchset enables VFIO devices to have live migration capability.
Currently it does not support post-copy phase.

It follows Alex's comments on last version of VFIO live migration patches,
including device states, VFIO device state region layout, dirty bitmap's
query.

Device Data
-----------
Device data is divided into three types: device memory, device config,
and system memory dirty pages produced by device.

Device config: data like MMIOs, page tables...
        Every device is supposed to possess device config data.
    	Usually device config's size is small (no big than 10M), and it
        needs to be loaded in certain strict order.
        Therefore, device config only needs to be saved/loaded in
        stop-and-copy phase.
        The data of device config is held in device config region.
        Size of device config data is smaller than or equal to that of
        device config region.

Device Memory: device's internal memory, standalone and outside system
        memory. It is usually very big.
        This kind of data needs to be saved / loaded in pre-copy and
        stop-and-copy phase.
        The data of device memory is held in device memory region.
        Size of devie memory is usually larger than that of device
        memory region. qemu needs to save/load it in chunks of size of
        device memory region.
        Not all device has device memory. Like IGD only uses system memory.

System memory dirty pages: If a device produces dirty pages in system
        memory, it is able to get dirty bitmap for certain range of system
        memory. This dirty bitmap is queried in pre-copy and stop-and-copy
        phase in .log_sync callback. By setting dirty bitmap in .log_sync
        callback, dirty pages in system memory will be save/loaded by ram's
        live migration code.
        The dirty bitmap of system memory is held in dirty bitmap region.
        If system memory range is larger than that dirty bitmap region can
        hold, qemu will cut it into several chunks and get dirty bitmap in
        succession.


Device State Regions
--------------------
Vendor driver is required to expose two mandatory regions and another two
optional regions if it plans to support device state management.

So, there are up to four regions in total.
One control region: mandatory.
        Get access via read/write system call.
        Its layout is defined in struct vfio_device_state_ctl
Three data regions: mmaped into qemu.
        device config region: mandatory, holding data of device config
        device memory region: optional, holding data of device memory
        dirty bitmap region: optional, holding bitmap of system memory
                            dirty pages

(The reason why four seperate regions are defined is that the unit of mmap
system call is PAGE_SIZE, i.e. 4k bytes. So one read/write region for
control and three mmaped regions for data seems better than one big region
padded and sparse mmaped).


kernel device state interface [1]
--------------------------------------
#define VFIO_DEVICE_STATE_INTERFACE_VERSION 1
#define VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY 1
#define VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY 2

#define VFIO_DEVICE_STATE_RUNNING 0 
#define VFIO_DEVICE_STATE_STOP 1
#define VFIO_DEVICE_STATE_LOGGING 2

#define VFIO_DEVICE_DATA_ACTION_GET_BUFFER 1
#define VFIO_DEVICE_DATA_ACTION_SET_BUFFER 2
#define VFIO_DEVICE_DATA_ACTION_GET_BITMAP 3

struct vfio_device_state_ctl {
	__u32 version;		  /* ro */
	__u32 device_state;       /* VFIO device state, wo */
	__u32 caps;		 /* ro */
        struct {
		__u32 action;  /* wo, GET_BUFFER or SET_BUFFER */ 
		__u64 size;    /*rw*/
	} device_config;
	struct {
		__u32 action;    /* wo, GET_BUFFER or SET_BUFFER */ 
		__u64 size;     /* rw */  
                __u64 pos; /*the offset in total buffer of device memory*/
	} device_memory;
	struct {
		__u64 start_addr; /* wo */
		__u64 page_nr;   /* wo */
	} system_memory;
};

Devcie States
------------- 
After migration is initialzed, it will set device state via writing to
device_state field of control region.

Four states are defined for a VFIO device:
        RUNNING, RUNNING & LOGGING, STOP & LOGGING, STOP 

RUNNING: In this state, a VFIO device is in active state ready to receive
        commands from device driver.
        It is the default state that a VFIO device enters initially.

STOP:  In this state, a VFIO device is deactivated to interact with
       device driver.

LOGGING: a special state that it CANNOT exist independently. It must be
       set alongside with state RUNNING or STOP (i.e. RUNNING & LOGGING,
       STOP & LOGGING).
       Qemu will set LOGGING state on in .save_setup callbacks, then vendor
       driver can start dirty data logging for device memory and system
       memory.
       LOGGING only impacts device/system memory. They return whole
       snapshot outside LOGGING and dirty data since last get operation
       inside LOGGING.
       Device config should be always accessible and return whole config
       snapshot regardless of LOGGING state.
       
Note:
The reason why RUNNING is the default state is that device's active state
must not depend on device state interface.
It is possible that region vfio_device_state_ctl fails to get registered.
In that condition, a device needs be in active state by default. 

Get Version & Get Caps
----------------------
On migration init phase, qemu will probe the existence of device state
regions of vendor driver, then get version of the device state interface
from the r/w control region.

Then it will probe VFIO device's data capability by reading caps field of
control region.
        #define VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY 1
        #define VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY 2
If VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY is on, it will save/load data of
        device memory in pre-copy and stop-and-copy phase. The data of
        device memory is held in device memory region.
If VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY is on, it will query of dirty pages
        produced by VFIO device during pre-copy and stop-and-copy phase.
        The dirty bitmap of system memory is held in dirty bitmap region.

If failing to find two mandatory regions and optional data regions
corresponding to data caps or version mismatching, it will setup a
migration blocker and disable live migration for VFIO device.


Flows to call device state interface for VFIO live migration
------------------------------------------------------------

Live migration save path:

(QEMU LIVE MIGRATION STATE --> DEVICE STATE INTERFACE --> DEVICE STATE)

MIGRATION_STATUS_NONE --> VFIO_DEVICE_STATE_RUNNING
 |
MIGRATION_STATUS_SAVE_SETUP
 |
 .save_setup callback -->
 get device memory size (whole snapshot size)
 get device memory buffer (whole snapshot data)
 set device state --> VFIO_DEVICE_STATE_RUNNING & VFIO_DEVICE_STATE_LOGGING
 |
MIGRATION_STATUS_ACTIVE
 |
 .save_live_pending callback --> get device memory size (dirty data)
 .save_live_iteration callback --> get device memory buffer (dirty data)
 .log_sync callback --> get system memory dirty bitmap
 |
(vcpu stops) --> set device state -->
 VFIO_DEVICE_STATE_STOP & VFIO_DEVICE_STATE_LOGGING
 |
.save_live_complete_precopy callback -->
 get device memory size (dirty data)
 get device memory buffer (dirty data)
 get device config size (whole snapshot size)
 get device config buffer (whole snapshot data)
 |
.save_cleanup callback -->  set device state --> VFIO_DEVICE_STATE_STOP
MIGRATION_STATUS_COMPLETED

MIGRATION_STATUS_CANCELLED or
MIGRATION_STATUS_FAILED
 |
(vcpu starts) --> set device state --> VFIO_DEVICE_STATE_RUNNING


Live migration load path:

(QEMU LIVE MIGRATION STATE --> DEVICE STATE INTERFACE --> DEVICE STATE)

MIGRATION_STATUS_NONE --> VFIO_DEVICE_STATE_RUNNING
 |
(vcpu stops) --> set device state --> VFIO_DEVICE_STATE_STOP
 |
MIGRATION_STATUS_ACTIVE
 |
.load state callback -->
 set device memory size, set device memory buffer, set device config size,
 set device config buffer
 |
(vcpu starts) --> set device state --> VFIO_DEVICE_STATE_RUNNING
 |
MIGRATION_STATUS_COMPLETED



In source VM side,
In precopy phase,
if a device has VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY on,
qemu will first get whole snapshot of device memory in .save_setup
callback, and then it will get total size of dirty data in device memory in
.save_live_pending callback by reading device_memory.size field of control
region.
Then in .save_live_iteration callback, it will get buffer of device memory's
dirty data chunk by chunk from device memory region by writing pos &
action (GET_BUFFER) to device_memory.pos & device_memory.action fields of
control region. (size of each chunk is the size of device memory data
region).
.save_live_pending and .save_live_iteration may be called several times in
precopy phase to get dirty data in device memory.

If VFIO_DEVICE_DATA_CAP_DEVICE_MEMORY is off, callbacks in precopy phase
like .save_setup, .save_live_pending, .save_live_iteration will not call
vendor driver's device state interface to get data from devcie memory.

In precopy phase, if a device has VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY on,
.log_sync callback will get system memory dirty bitmap from dirty bitmap
region by writing system memory's start address, page count and action 
(GET_BITMAP) to "system_memory.start_addr", "system_memory.page_nr", and
"system_memory.action" fields of control region.
If page count passed in .log_sync callback is larger than the bitmap size
the dirty bitmap region supports, Qemu will cut it into chunks and call
vendor driver's get system memory dirty bitmap interface.
If VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY is off, .log_sync callback just
returns without call to vendor driver.

In stop-and-copy phase, device state will be set to STOP & LOGGING first.
in save_live_complete_precopy callback,
If VFIO_DEVICE_DATA_CAP_SYSTEM_MEMORY is on,
get device memory size and get device memory buffer will be called again.
After that,
device config data is get from device config region by reading
devcie_config.size of control region and writing action (GET_BITMAP) to
device_config.action of control region.
Then after migration completes, in cleanup handler, LOGGING state will be
cleared (i.e. deivce state is set to STOP).
Clearing LOGGING state in cleanup handler is in consideration of the case
of "migration failed" and "migration cancelled". They can also leverage
the cleanup handler to unset LOGGING state.


References
----------
1. kernel side implementation of Device state interfaces:
https://patchwork.freedesktop.org/series/56876/


Yan Zhao (5):
  vfio/migration: define kernel interfaces
  vfio/migration: support device of device config capability
  vfio/migration: tracking of dirty page in system memory
  vfio/migration: turn on migration
  vfio/migration: support device memory capability

 hw/vfio/Makefile.objs         |   2 +-
 hw/vfio/common.c              |  26 ++
 hw/vfio/migration.c           | 858 ++++++++++++++++++++++++++++++++++++++++++
 hw/vfio/pci.c                 |  10 +-
 hw/vfio/pci.h                 |  26 +-
 include/hw/vfio/vfio-common.h |   1 +
 linux-headers/linux/vfio.h    | 260 +++++++++++++
 7 files changed, 1174 insertions(+), 9 deletions(-)
 create mode 100644 hw/vfio/migration.c
```
#### [PATCH v5 0/9] mmu notifier provide context informations
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

Since last version [4] i added the extra bits needed for the change_pte
optimization (which is a KSM thing). Here i am not posting users of
this, they will be posted to the appropriate sub-systems (KVM, GPU,
RDMA, ...) once this serie get upstream. If you want to look at users
of this see [5] [6]. If this gets in 5.1 then i will be submitting
those users for 5.2 (including KVM if KVM folks feel comfortable with
it).

Note that this serie does not change any behavior for any existing
code. It just pass down more informations to mmu notifier listener.

The rational for this patchset:


CPU page table update can happens for many reasons, not only as a
result of a syscall (munmap(), mprotect(), mremap(), madvise(), ...)
but also as a result of kernel activities (memory compression, reclaim,
migration, ...).

This patch introduce a set of enums that can be associated with each
of the events triggering a mmu notifier:

    - UNMAP: munmap() or mremap()
    - CLEAR: page table is cleared (migration, compaction, reclaim, ...)
    - PROTECTION_VMA: change in access protections for the range
    - PROTECTION_PAGE: change in access protections for page in the range
    - SOFT_DIRTY: soft dirtyness tracking

Being able to identify munmap() and mremap() from other reasons why the
page table is cleared is important to allow user of mmu notifier to
update their own internal tracking structure accordingly (on munmap or
mremap it is not longer needed to track range of virtual address as it
becomes invalid). Without this serie, driver are force to assume that
every notification is an munmap which triggers useless trashing within
drivers that associate structure with range of virtual address. Each
driver is force to free up its tracking structure and then restore it
on next device page fault. With this serie we can also optimize device
page table update [5].

More over this can also be use to optimize out some page table updates
like for KVM where we can update the secondary MMU directly from the
callback instead of clearing it.

Patches to leverage this serie will be posted separately to each sub-
system.

Cheers,
Jérôme

[1] v1 https://lkml.org/lkml/2018/3/23/1049
[2] v2 https://lkml.org/lkml/2018/12/5/10
[3] v3 https://lkml.org/lkml/2018/12/13/620
[4] v4 https://lkml.org/lkml/2019/1/23/838
[5] patches to use this:
    https://lkml.org/lkml/2019/1/23/833
    https://lkml.org/lkml/2019/1/23/834
    https://lkml.org/lkml/2019/1/23/832
    https://lkml.org/lkml/2019/1/23/831
[6] KVM restore change pte optimization
    https://patchwork.kernel.org/cover/10791179/

Cc: Christian König <christian.koenig@amd.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Cc: Jani Nikula <jani.nikula@linux.intel.com>
Cc: Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Felix Kuehling <Felix.Kuehling@amd.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>

Jérôme Glisse (9):
  mm/mmu_notifier: helper to test if a range invalidation is blockable
  mm/mmu_notifier: convert user range->blockable to helper function
  mm/mmu_notifier: convert mmu_notifier_range->blockable to a flags
  mm/mmu_notifier: contextual information for event enums
  mm/mmu_notifier: contextual information for event triggering
    invalidation v2
  mm/mmu_notifier: use correct mmu_notifier events for each invalidation
  mm/mmu_notifier: pass down vma and reasons why mmu notifier is
    happening v2
  mm/mmu_notifier: mmu_notifier_range_update_to_read_only() helper
  mm/mmu_notifier: set MMU_NOTIFIER_USE_CHANGE_PTE flag where
    appropriate v2

 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  |  8 +--
 drivers/gpu/drm/i915/i915_gem_userptr.c |  2 +-
 drivers/gpu/drm/radeon/radeon_mn.c      |  4 +-
 drivers/infiniband/core/umem_odp.c      |  5 +-
 drivers/xen/gntdev.c                    |  6 +-
 fs/proc/task_mmu.c                      |  3 +-
 include/linux/mmu_notifier.h            | 93 +++++++++++++++++++++++--
 kernel/events/uprobes.c                 |  3 +-
 mm/hmm.c                                |  6 +-
 mm/huge_memory.c                        | 14 ++--
 mm/hugetlb.c                            | 12 ++--
 mm/khugepaged.c                         |  3 +-
 mm/ksm.c                                |  9 ++-
 mm/madvise.c                            |  3 +-
 mm/memory.c                             | 26 ++++---
 mm/migrate.c                            |  5 +-
 mm/mmu_notifier.c                       | 12 +++-
 mm/mprotect.c                           |  4 +-
 mm/mremap.c                             |  3 +-
 mm/oom_kill.c                           |  3 +-
 mm/rmap.c                               |  6 +-
 virt/kvm/kvm_main.c                     |  3 +-
 22 files changed, 180 insertions(+), 53 deletions(-)
```
