

#### [PATCH v4 00/15] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1611150960;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=+aDp550Lm+rofMztKr13LGN261/aN33kUiCXnXHZSts=;
        b=u4mfyPjhhiICRVasCe0gx5uHwLGuJfO0Nwh5LmCImg6SvGFgunQvHFOMzVuArWuXyLPN7Q
        4VZ3QphBnnd7lfNQ+5cqvlSCQ1z2HTK1jtA49OjLiu40GNx+iyhykAfICdGYMvGmMsI5V7
        u7RmQtSlG0WNBRDlF79PQzqxwc1CKgo=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id D8566ADD3;
        Wed, 20 Jan 2021 13:55:59 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, linux-kernel@vger.kernel.org,
        x86@kernel.org, virtualization@lists.linux-foundation.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org,
        clang-built-linux@googlegroups.com
Cc: Juergen Gross <jgross@suse.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Jason Baron <jbaron@akamai.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ard Biesheuvel <ardb@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Mel Gorman <mgorman@suse.de>, Ingo Molnar <mingo@redhat.com>,
        Michal Hocko <mhocko@kernel.org>,
        "Paul E . McKenney" <paulmck@kernel.org>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Andy Lutomirski <luto@kernel.org>,
        Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Nathan Chancellor <natechancellor@gmail.com>,
        Nick Desaulniers <ndesaulniers@google.com>
Subject: [PATCH v4 00/15] x86: major paravirt cleanup
Date: Wed, 20 Jan 2021 14:55:40 +0100
Message-Id: <20210120135555.32594-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[Resend due to all the Cc:'s missing]

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too, but that would require a major
header file disentangling.

For a clean build without any objtool warnings a modified objtool is
required. Currently this is available in the "tip" tree in the
objtool/core branch.

Changes in V4:
- fixed several build failures
- removed objtool patch, as objtool patches are in tip now
- added patch 1 for making usage of static_call easier
- even more cleanup

Changes in V3:
- added patches 7 and 12
- addressed all comments

Changes in V2:
- added patches 5-12

Juergen Gross (14):
  x86/xen: use specific Xen pv interrupt entry for MCE
  x86/xen: use specific Xen pv interrupt entry for DF
  x86/pv: switch SWAPGS to ALTERNATIVE
  x86/xen: drop USERGS_SYSRET64 paravirt call
  x86: rework arch_local_irq_restore() to not use popf
  x86/paravirt: switch time pvops functions to use static_call()
  x86/alternative: support "not feature" and ALTERNATIVE_TERNARY
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: simplify paravirt macros
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

Peter Zijlstra (1):
  static_call: Pull some static_call declarations to the type headers

 arch/x86/Kconfig                        |   1 +
 arch/x86/entry/entry_32.S               |   4 +-
 arch/x86/entry/entry_64.S               |  28 ++-
 arch/x86/include/asm/alternative-asm.h  |   4 +
 arch/x86/include/asm/alternative.h      |   7 +
 arch/x86/include/asm/cpufeatures.h      |   2 +
 arch/x86/include/asm/idtentry.h         |   6 +
 arch/x86/include/asm/irqflags.h         |  53 ++----
 arch/x86/include/asm/mshyperv.h         |   2 +-
 arch/x86/include/asm/paravirt.h         | 197 ++++++++------------
 arch/x86/include/asm/paravirt_types.h   | 227 +++++++++---------------
 arch/x86/kernel/Makefile                |   3 +-
 arch/x86/kernel/alternative.c           |  49 ++++-
 arch/x86/kernel/asm-offsets.c           |   7 -
 arch/x86/kernel/asm-offsets_64.c        |   3 -
 arch/x86/kernel/cpu/vmware.c            |   5 +-
 arch/x86/kernel/irqflags.S              |  11 --
 arch/x86/kernel/kvm.c                   |   2 +-
 arch/x86/kernel/kvmclock.c              |   2 +-
 arch/x86/kernel/paravirt-spinlocks.c    |   9 +
 arch/x86/kernel/paravirt.c              |  83 +++------
 arch/x86/kernel/paravirt_patch.c        | 109 ------------
 arch/x86/kernel/tsc.c                   |   2 +-
 arch/x86/xen/enlighten_pv.c             |  36 ++--
 arch/x86/xen/irq.c                      |  23 ---
 arch/x86/xen/time.c                     |  11 +-
 arch/x86/xen/xen-asm.S                  |  52 +-----
 arch/x86/xen/xen-ops.h                  |   3 -
 drivers/clocksource/hyperv_timer.c      |   5 +-
 drivers/xen/time.c                      |   2 +-
 include/linux/static_call.h             |  20 ---
 include/linux/static_call_types.h       |  27 +++
 tools/include/linux/static_call_types.h |  27 +++
 33 files changed, 376 insertions(+), 646 deletions(-)
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
```
#### [PATCH v4 00/15] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1611149174;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=CpmyovsicWRsraKS/oNts+zojxJvItjt3KCZ7hy85ig=;
        b=YoQQYyi997NN0sL65a0YYcDujYywf5i4Ag7KpzfJ88RqXywvxFU4fjjUrkFdBLLs+2EdEe
        FmwSt0fjJPJqEsQNSSKHl7g8Q0WLZeDQLdTCe9dgWo8A2HWnLWPkj1p1QYY+Qctq5Ar+lD
        Wn2hf5TRnZUn4VzS1ZuroHV9nujUBC0=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id 0F7E4AAAE;
        Wed, 20 Jan 2021 13:26:14 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: bpetkov@suse.com, linux-kernel@vger.kernel.org, x86@kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org,
        clang-built-linux@googlegroups.com
Subject: [PATCH v4 00/15] x86: major paravirt cleanup
Date: Wed, 20 Jan 2021 14:25:58 +0100
Message-Id: <20210120132613.31487-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too, but that would require a major
header file disentangling.

For a clean build without any objtool warnings a modified objtool is
required. Currently this is available in the "tip" tree in the
objtool/core branch.

Changes in V4:
- fixed several build failures
- removed objtool patch, as objtool patches are in tip now
- added patch 1 for making usage of static_call easier
- even more cleanup

Changes in V3:
- added patches 7 and 12
- addressed all comments

Changes in V2:
- added patches 5-12

Juergen Gross (14):
  x86/xen: use specific Xen pv interrupt entry for MCE
  x86/xen: use specific Xen pv interrupt entry for DF
  x86/pv: switch SWAPGS to ALTERNATIVE
  x86/xen: drop USERGS_SYSRET64 paravirt call
  x86: rework arch_local_irq_restore() to not use popf
  x86/paravirt: switch time pvops functions to use static_call()
  x86/alternative: support "not feature" and ALTERNATIVE_TERNARY
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: simplify paravirt macros
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

Peter Zijlstra (1):
  static_call: Pull some static_call declarations to the type headers

 arch/x86/Kconfig                        |   1 +
 arch/x86/entry/entry_32.S               |   4 +-
 arch/x86/entry/entry_64.S               |  28 ++-
 arch/x86/include/asm/alternative-asm.h  |   4 +
 arch/x86/include/asm/alternative.h      |   7 +
 arch/x86/include/asm/cpufeatures.h      |   2 +
 arch/x86/include/asm/idtentry.h         |   6 +
 arch/x86/include/asm/irqflags.h         |  53 ++----
 arch/x86/include/asm/mshyperv.h         |   2 +-
 arch/x86/include/asm/paravirt.h         | 197 ++++++++------------
 arch/x86/include/asm/paravirt_types.h   | 227 +++++++++---------------
 arch/x86/kernel/Makefile                |   3 +-
 arch/x86/kernel/alternative.c           |  49 ++++-
 arch/x86/kernel/asm-offsets.c           |   7 -
 arch/x86/kernel/asm-offsets_64.c        |   3 -
 arch/x86/kernel/cpu/vmware.c            |   5 +-
 arch/x86/kernel/irqflags.S              |  11 --
 arch/x86/kernel/kvm.c                   |   2 +-
 arch/x86/kernel/kvmclock.c              |   2 +-
 arch/x86/kernel/paravirt-spinlocks.c    |   9 +
 arch/x86/kernel/paravirt.c              |  83 +++------
 arch/x86/kernel/paravirt_patch.c        | 109 ------------
 arch/x86/kernel/tsc.c                   |   2 +-
 arch/x86/xen/enlighten_pv.c             |  36 ++--
 arch/x86/xen/irq.c                      |  23 ---
 arch/x86/xen/time.c                     |  11 +-
 arch/x86/xen/xen-asm.S                  |  52 +-----
 arch/x86/xen/xen-ops.h                  |   3 -
 drivers/clocksource/hyperv_timer.c      |   5 +-
 drivers/xen/time.c                      |   2 +-
 include/linux/static_call.h             |  20 ---
 include/linux/static_call_types.h       |  27 +++
 tools/include/linux/static_call_types.h |  27 +++
 33 files changed, 376 insertions(+), 646 deletions(-)
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
```
