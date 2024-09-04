// V0: https://gist.githubusercontent.com/joaomlneto/a595baca013335bdc8a9ef6800cda041/raw/9d5ed7a2eaa88c2f1f3686771d2b53c3315e2e86/mprotect_bench.c

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>

#define NTIMES 1000

void initialize(uint64_t *a, size_t size)
{
    a[0] = 123;
    for (size_t i = 1; i < size; i++)
    {
        a[i] = a[i - 1] * a[i - 1] % 100000;
    }
}

void time_mprotect(void *addr, size_t size, size_t ntimes)
{
    clock_t start = clock();
    for (size_t i = 0; i < ntimes; i++)
    {
        if (mprotect(addr, size, PROT_READ) == -1)
        {
            perror("mprotect failed");
            exit(-1);
        }
        if (mprotect(addr, size, PROT_READ | PROT_WRITE) == -1)
        {
            perror("mprotect failed");
            exit(-1);
        }
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("mprotect %zu MB -> %.2lf us\n", size / 1024 / 1024, seconds / ntimes * 1000000);
}

int main(int argc, char *argv[])
{
    long long SIZE = 1 * 1024 * 1024;
    size_t N;
    uint64_t i;

    if (argc > 1)
    {
        long long USER_SIZE_MB = atoll(argv[1]);
        if (USER_SIZE_MB > 1)
            SIZE = USER_SIZE_MB * 1024 * 1024;
    }

    N = SIZE / sizeof(uint64_t);
    uint64_t *a = mmap(NULL, N * sizeof(uint64_t), PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    long pagesize = sysconf(_SC_PAGESIZE);
    initialize(a, N);
    i = ceil(SIZE / pagesize);
    time_mprotect(a, i * pagesize, NTIMES);

    return 0;
}
