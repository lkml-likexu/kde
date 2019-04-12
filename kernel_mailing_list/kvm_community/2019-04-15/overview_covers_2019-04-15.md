

#### [PATCH v5 0/3] KVM: arm/arm64: Add VCPU workarounds firmware register
##### From: Andre Przywara <andre.przywara@arm.com>

```c

Hi,

another update, mostly basing upon Jeremy's sysfs vulnerabilites
series[1], which adds the new UNAFFECTED state for WORKAROUND_1.
The new patch 1/3 propagates this state to the guest, so a guest benefits
from the host kernel's knowledge about whether this workaround is needed.
This triggers some changes in patch 2/3, where we properly export this
new state to userland as well, so we can deny migration from NOT_NEEDED to
AVAILABLE, and allow the other way round.
The documentation in patch 3/3 has been reworded to be more precise, so
I dropped Steven's R-b: on this.

Cheers,
Andre

-----------------------------
Workarounds for Spectre variant 2 or 4 vulnerabilities require some help
from the firmware, so KVM implements an interface to provide that for
guests. When such a guest is migrated, we want to make sure we don't
loose the protection the guest relies on.

This introduces two new firmware registers in KVM's GET/SET_ONE_REG
interface, so userland can save the level of protection implemented by
the hypervisor and used by the guest. Upon restoring these registers,
we make sure we don't downgrade and reject any values that would mean
weaker protection.
The protection level is encoded in the lower 4 bits, with smaller
values indicating weaker protection.

ARM(32) is a bit of a pain (again), as the firmware register interface
is shared, but 32-bit does not implement all the workarounds.
For now I stuffed two wrappers into kvm_emulate.h, which doesn't sound
like the best solution. Happy to hear about better solutions.

This has been tested with migration between two Juno systems. Out of the
box they advertise identical workaround levels, and migration succeeds.
However when disabling the A57 cluster on one system, WORKAROUND_1 is
not needed and the host kernel propagates this. Migration now only
succeeds in one direction (from the big/LITTLE configuration to the
A53-only setup).

Please have a look and comment!

This is based upon v7 of the "add system vulnerability sysfs entries",
applied on top of 5.1-rc4. Let me know if you want to have a different
base.

Cheers,
Andre

[1] http://lists.infradead.org/pipermail/linux-arm-kernel/2019-April/645382.html

Changelog:
v4 .. v5:
- add patch to advertise ARM64_BP_HARDEN_MITIGATED state to a guest
- allow migration from KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL to
  (new) KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_UNAFFECTED
- reword API documentation
- return -EINVAL on querying invalid firmware register
- add some comments
- minor fixes according to Eric's review

v3 .. v4:
- clarify API documentation for WORKAROUND_1
- check for unknown bits in userland provided register values
- report proper -ENOENT when register ID is unknown

v2 .. v3:
- rebase against latest kvm-arm/next
- introduce UNAFFECTED value for WORKAROUND_1
- require exact match for WORKAROUND_1 levels

v1 .. v2:
- complete rework of WORKAROUND_2 presentation to use a linear scale,
  dropping the complicated comparison routine

Andre Przywara (3):
  arm64: KVM: Propagate full Spectre v2 workaround state to KVM guests
  KVM: arm/arm64: Add save/restore support for firmware workaround state
  KVM: doc: add API documentation on the KVM_REG_ARM_WORKAROUNDS
    register

 Documentation/virtual/kvm/arm/psci.txt |  31 +++++
 arch/arm/include/asm/kvm_emulate.h     |  10 ++
 arch/arm/include/asm/kvm_host.h        |  12 +-
 arch/arm/include/uapi/asm/kvm.h        |  12 ++
 arch/arm64/include/asm/cpufeature.h    |   6 +
 arch/arm64/include/asm/kvm_emulate.h   |  14 +++
 arch/arm64/include/asm/kvm_host.h      |  16 ++-
 arch/arm64/include/uapi/asm/kvm.h      |  10 ++
 arch/arm64/kernel/cpu_errata.c         |  23 +++-
 virt/kvm/arm/psci.c                    | 149 ++++++++++++++++++++++---
 10 files changed, 257 insertions(+), 26 deletions(-)
```
#### [PATCH 0/6] Add Hygon SEV support
##### From: Hao Feng <fenghao@hygon.cn>

```c

Hygon SEV follows AMD SEV work flow, but uses China national standard
cryptographic algorithms SM2/SM3/SM4 instead of (RSA, ECDSA,
ECDH)/SHA/AES. Reuse most AMD SEV code path to support Hygon SEV,
also adds 3 new commands(GM_PUBKEY_GEN, GM_GET_DIGEST,
GM_VERIFY_DIGEST) to support SM2 key exchange protocol.

SM2 is based on ECC(Elliptic Curve Cryptography), and uses a special
curve. It can be used in digital signature, key exchange and
asymmetric cryptography. For key exchange, SM2 is similar to ECDH, but
involves new random key, meaning the two sides need to exchange extra
random public key besides their public key, that's why additional APIs
are needed to support Hygon SEV.
SM3 is a hash algorithm, similar to SHA-256.
SM4 is a block cipher algorithm, similar to AES-128.

1. GM_PUBKEY_GEN
----------------
The command is used to get SM2 random public key from SEV firmware to
compute share key.

Parameters:
* GM_KEY_ID_PADDR (in) - Address of key ID for the random public key.
* GM_KEY_ID_LEN (in) - Length of key ID.
* GM_PUBKEY_PADDR (in) - Address of the random public key.
* GM_PUBKEY_LEN (in,out) - Length of the random public key.

2. GM_GET_DIGEST
----------------
The command is used to get key digest from SEV firmware during SM2 key
exchange, guest owner can check the digest to see if the key
negotiation is successful or not.

Parameters:
* HANDLE (in) - Guest handle
* DIGEST_PADDR (in) - Address of the key digest
* DIGEST_LEN (in, out) - Length of the key digest

3. GM_VERIFY_DIGEST
-------------------
The command is used to send guest owner's key digest to SEV firmware
during SM2 key exchange, firmware can check the digest to see if the
negotiation is successful or not.

Parameters:
* HANDLE (in) - Guest handle
* DIGEST_PADDR (in) - Address of the key digest
* DIGEST_LEN (in) - Length of the key digest

Already tested successfully on Hygon DhyanaPlus processor, also tested
successfully on AMD EPYC processor, results show no side effect on
current AMD SEV implementation.

Hao Feng (6):
  crypto: ccp: Add Hygon Dhyana support
  crypto: ccp: Define Hygon SEV commands
  crypto: ccp: Implement SEV_GM_PUBKEY_GEN ioctl command
  KVM: Define Hygon SEV commands
  KVM: SVM: Add support for KVM_SEV_GM_GET_DIGEST command
  KVM: SVM: Add KVM_SEV_GM_VERIFY_DIGEST command

 arch/x86/kvm/svm.c           | 119 +++++++++++++++++++++++++++++++++++++++++++
 drivers/crypto/ccp/psp-dev.c |  86 +++++++++++++++++++++++++++++++
 drivers/crypto/ccp/sp-pci.c  |   2 +
 include/linux/psp-sev.h      |  49 ++++++++++++++++++
 include/uapi/linux/kvm.h     |  14 +++++
 include/uapi/linux/psp-sev.h |  17 +++++++
 6 files changed, 287 insertions(+)
```
