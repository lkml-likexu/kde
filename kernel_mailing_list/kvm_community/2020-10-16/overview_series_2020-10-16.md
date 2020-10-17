#### [PATCH v2] vfio/fsl-mc: fix the return of the uninitialized variable ret
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_fsl_mc_reflck_attach function may return, on success path,
an uninitialized variable. Fix the problem by initializing the return
variable to 0.

Addresses-Coverity: ("Uninitialized scalar variable")
Fixes: f2ba7e8c947b ("vfio/fsl-mc: Added lock support in preparation for interrupt handling")
Reported-by: Colin Ian King <colin.king@canonical.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 drivers/vfio/fsl-mc/vfio_fsl_mc.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
