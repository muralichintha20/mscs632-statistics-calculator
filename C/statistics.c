/*
 * statistics.c
 * Basic Statistics Calculator (Procedural Paradigm)
 *
 * Calculates mean, median, and mode for a list of integers.
 * Demonstrates manual memory management, direct array manipulation,
 * and an explicit sorting/counting approach typical of procedural C.
 *
 * Author: Murali Krishna Chintha
 * Course: MSCS-632 Advanced Programming Languages
 */

#include <stdio.h>
#include <stdlib.h>

/* Comparison callback used by qsort to order integers ascending. */
int compare_ints(const void *a, const void *b) {
    int left = *(const int *)a;
    int right = *(const int *)b;
    if (left < right) return -1;
    if (left > right) return 1;
    return 0;
}

/* Mean: sum of all values divided by the count. */
double calculate_mean(const int *data, int n) {
    long sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        sum += data[i];
    }
    return (double)sum / (double)n;
}

/*
 * Median: middle value of the sorted array.
 * Expects a sorted array. For an even count it averages the two
 * central elements; for an odd count it returns the center element.
 */
double calculate_median(const int *sorted, int n) {
    if (n % 2 == 1) {
        return (double)sorted[n / 2];
    }
    return ((double)sorted[n / 2 - 1] + (double)sorted[n / 2]) / 2.0;
}

/*
 * Mode: the most frequently occurring value(s).
 * Operates on a sorted array so equal values are adjacent, which lets
 * us count runs in a single pass. The caller passes an output array and
 * receives the number of modes through out_count. Memory for the run
 * scan is handled on the stack; no dynamic allocation is needed here.
 */
void calculate_mode(const int *sorted, int n, int *modes, int *out_count) {
    int best_freq = 0;
    int i = 0;

    /* First pass: find the highest frequency. */
    while (i < n) {
        int j = i;
        while (j < n && sorted[j] == sorted[i]) {
            j++;
        }
        int freq = j - i;
        if (freq > best_freq) {
            best_freq = freq;
        }
        i = j;
    }

    /* Second pass: collect every value whose frequency equals best_freq. */
    *out_count = 0;
    i = 0;
    while (i < n) {
        int j = i;
        while (j < n && sorted[j] == sorted[i]) {
            j++;
        }
        if (j - i == best_freq) {
            modes[*out_count] = sorted[i];
            (*out_count)++;
        }
        i = j;
    }
}

int main(void) {
    /* Sample dataset. */
    int sample[] = {7, 3, 9, 3, 5, 7, 3, 8, 5, 10, 7, 3};
    int n = (int)(sizeof(sample) / sizeof(sample[0]));
    int i;

    /*
     * Manual memory management: allocate a working copy on the heap so the
     * original input order is preserved while we sort the copy. In C the
     * programmer is responsible for both malloc and the matching free.
     */
    int *data = (int *)malloc((size_t)n * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        data[i] = sample[i];
    }

    printf("Statistics Calculator (C, Procedural)\n");
    printf("=====================================\n");
    printf("Input data (%d values): ", n);
    for (i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    /* Sort the copy in place for median and mode. */
    qsort(data, (size_t)n, sizeof(int), compare_ints);

    printf("Sorted data:           ");
    for (i = 0; i < n; i++) {
        printf("%d ", data[i]);
    }
    printf("\n\n");

    /* Mean. */
    printf("Mean:   %.2f\n", calculate_mean(data, n));

    /* Median. */
    printf("Median: %.2f\n", calculate_median(data, n));

    /* Mode. A dataset can have more than one mode, so reserve n slots. */
    int *modes = (int *)malloc((size_t)n * sizeof(int));
    if (modes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(data);
        return 1;
    }
    int mode_count = 0;
    calculate_mode(data, n, modes, &mode_count);

    printf("Mode:   ");
    for (i = 0; i < mode_count; i++) {
        printf("%d", modes[i]);
        if (i < mode_count - 1) {
            printf(", ");
        }
    }
    printf("\n");

    /* Release every block we allocated. */
    free(modes);
    free(data);

    return 0;
}
