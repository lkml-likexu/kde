#### [PATCH] selftests: kvm: Add files generated when compiled to .gitignore
##### From: Kelsey Skunberg <skunberg.kelsey@gmail.com>

```c
The following files are generated in /selftests/kvm/ after compiling and
should be added to /selftests/kvm/.gitignore:

	- /x86_64/hyperv_cpuid
	- /x86_64/smm_test

Signed-off-by: Kelsey Skunberg <skunberg.kelsey@gmail.com>
---
 tools/testing/selftests/kvm/.gitignore | 2 ++
 1 file changed, 2 insertions(+)

--
2.20.1

```
