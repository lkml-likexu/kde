#### [RFC PATCH 01/21] x86/sgx: Add defines for SGX device minor numbers
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Add defines to track the minor numbers for each SGX device in
preparation for moving the helper code and provisioning device to the
common subsystem, and in preparation for adding a third device, i.e. a
virtual EPC device.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kernel/cpu/sgx/driver/driver.h | 1 -
 arch/x86/kernel/cpu/sgx/driver/main.c   | 9 +++++----
 arch/x86/kernel/cpu/sgx/sgx.h           | 4 ++++
 3 files changed, 9 insertions(+), 5 deletions(-)

```
