#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <pthread.h>
#include <getopt.h>

#define NTIMES 1000

static unsigned int NUM_THREADS = 1;
static long long SIZE = 1 * 1024 * 1024;
static pthread_t *threads = NULL;
static unsigned int *thread_ids = NULL;
static double *cost_num = NULL;

void initialize(uint64_t *a, size_t size)
{
    a[0] = 123;
    for (size_t i = 1; i < size; i++)
    {
        a[i] = a[i - 1] * a[i - 1] % 100000;
    }
}

double time_mprotect(void *addr, size_t size, size_t ntimes)
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
    return ((double)(end - start) / CLOCKS_PER_SEC) / ntimes * 1000000;
}

void *thread_function(void *arg)
{
    unsigned int thread_id = *(unsigned int *)arg;
    size_t N = SIZE / sizeof(uint64_t);
    long pagesize = sysconf(_SC_PAGESIZE);

    uint64_t *a = mmap(NULL, N * sizeof(uint64_t), PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    initialize(a, N);
    cost_num[thread_id] = time_mprotect(a, ceil(SIZE / pagesize) * pagesize, NTIMES);

    pthread_exit(NULL);
}

double calculate_average(double *array, int length)
{
    double sum = 0.0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / length;
}

int main(int argc, char *argv[])
{
    int num_threads = 1;
    int num_size = 1;
    int opt;

    struct option long_options[] = {
        {"threads", required_argument, NULL, 't'},
        {"size", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0}};

    while ((opt = getopt_long(argc, argv, "t:s:", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 't':
            num_threads = atoi(optarg);
            if (num_threads > 1)
                NUM_THREADS = num_threads;
            break;
        case 's':
            num_size = atoi(optarg);
            if (num_size > 1)
                SIZE = num_size * 1024 * 1024;
            break;
        default:
            printf("Hint: ./bin -t thread_num -s size_num_in_MB.\n");
            return 1;
        }
    }

    threads = malloc(NUM_THREADS * sizeof(pthread_t));
    thread_ids = malloc(NUM_THREADS * sizeof(int));
    cost_num = malloc(NUM_THREADS * sizeof(double));

    for (unsigned int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        if (result != 0)
        {
            printf("Failed to create thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("mprotect %zu MB %zu threads %.2lf us\n", SIZE / 1024 / 1024,
           NUM_THREADS, calculate_average(cost_num, NUM_THREADS));

    return 0;
}
