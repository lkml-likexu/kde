#### [Bug 103141] Host-triggerable NULL pointer oops
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

https://bugzilla.kernel.org/show_bug.cgi?id=103141

Alex Lyakas (alex@zadara.com) changed:

           What    |Removed                     |Added
----------------------------------------------------------------------------
                 CC|                            |alex@zadara.com

--- Comment #4 from Alex Lyakas (alex@zadara.com) ---
We hit the same issue with kernel 3.18.19.

After some debugging, I see that the first test program that felix attached,
causes kvm_x86_ops->vcpu_create to return -EEXIST instead of a valid vcpu
pointer. As a result, the call to kvm_x86_ops->fpu_activate tries to access an
invalid pointer, and causes a NULL pointer dereference.

The suggested fix was delivered in kernel 4.2. Although it was tagged as
"stable", I don't see that it was backported to earlier kernels. I believe that
the fix addresses a different issue, in which the vcpu pointer is valid, but
further VMCS write has a problem (this is my understanding). But, of course,
this fix will address also the issue that felix reported. Although for the
```
