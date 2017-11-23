#### [PATCH] KVM: validate userspace input in kvm_clear_dirty_log_protect()
##### From: Tomas Bortoli <tomasbortoli@gmail.com>

```c
The function at issue does not fully validate the content of the structure pointed by the log parameter, though its content has just been copied from userspace and lacks validation. Fix that.

Moreover, change the type of n to unsigned long as that is the type returned by kvm_dirty_bitmap_bytes().

Signed-off-by: Tomas Bortoli <tomasbortoli@gmail.com>
Reported-by: syzbot+028366e52c9ace67deb3@syzkaller.appspotmail.com
---
Syzbot report:

BUG: KASAN: slab-out-of-bounds in kvm_clear_dirty_log_protect+0x8cf/0x970 arch/x86/kvm/../../../virt/kvm/kvm_main.c:1262
Read of size 8 at addr ffff88809e631290 by task syz-executor007/7635

CPU: 0 PID: 7635 Comm: syz-executor007 Not tainted 4.20.0+ #2
Hardware name: Google Google Compute Engine/Google Compute Engine, BIOS Google 01/01/2011
Call Trace:
 __dump_stack lib/dump_stack.c:77 [inline]
 dump_stack+0x1db/0x2d0 lib/dump_stack.c:113
 print_address_description.cold+0x7c/0x20d mm/kasan/report.c:187
 kasan_report.cold+0x1b/0x40 mm/kasan/report.c:317
 __asan_report_load8_noabort+0x14/0x20 mm/kasan/generic_report.c:135
 kvm_clear_dirty_log_protect+0x8cf/0x970 arch/x86/kvm/../../../virt/kvm/kvm_main.c:1262
 kvm_vm_ioctl_clear_dirty_log+0xff/0x260 arch/x86/kvm/x86.c:4468
 kvm_vm_ioctl+0xc19/0x1fe0 arch/x86/kvm/../../../virt/kvm/kvm_main.c:3127
 vfs_ioctl fs/ioctl.c:46 [inline]
 file_ioctl fs/ioctl.c:509 [inline]
 do_vfs_ioctl+0x107b/0x17d0 fs/ioctl.c:696
 ksys_ioctl+0xab/0xd0 fs/ioctl.c:713
 __do_sys_ioctl fs/ioctl.c:720 [inline]
 __se_sys_ioctl fs/ioctl.c:718 [inline]
 __x64_sys_ioctl+0x73/0xb0 fs/ioctl.c:718
 do_syscall_64+0x1a3/0x800 arch/x86/entry/common.c:290
 entry_SYSCALL_64_after_hwframe+0x49/0xbe
RIP: 0033:0x440b09
Code: 23 02 00 85 c0 b8 00 00 00 00 48 0f 44 c3 5b c3 90 48 89 f8 48 89 f7 48 89 d6 48 89 ca 4d 89 c2 4d 89 c8 4c 8b 4c 24 08 0f 05 <48> 3d 01 f0 ff ff 0f 83 0b 13 fc ff c3 66 2e 0f 1f 84 00 00 00 00
RSP: 002b:00000000007dff68 EFLAGS: 00000217 ORIG_RAX: 0000000000000010
RAX: ffffffffffffffda RBX: 00000000004a28d8 RCX: 0000000000440b09
RDX: 0000000020000080 RSI: 00000000c018aec0 RDI: 0000000000000004
RBP: 00000000004a28d8 R08: 0000000120080522 R09: 0000000120080522
R10: 0000000120080522 R11: 0000000000000217 R12: 00000000004022a0
R13: 0000000000402330 R14: 0000000000000000 R15: 0000000000000000



 virt/kvm/kvm_main.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
