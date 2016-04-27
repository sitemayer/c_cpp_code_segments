#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN(a) sizeof(a)/sizeof(a[0])
#define MIN(a, b)  (a)<(b) ? (a) : (b)

typedef int (*sort_func)(int *, int);

/**
 * @Brief  bubble sort (n^2)
 *
 * @Param  parr
 * @Param  len
 *
 * @return 0 for success
 */
static int bubble_sort(int *parr, int len)
{
    char flg = 0;
    int i = 0, j = 0;

    if (parr == NULL) {
        return -1;
    }

    for (i = 0; i < len-1; i++) {
        flg = 0;
        for (j = 0; j < len-i-1; j++) {
            if (parr[j] < parr[j+1]) {
                parr[j] = parr[j] ^ parr[j+1];
                parr[j+1] = parr[j] ^ parr[j+1];
                parr[j] = parr[j] ^ parr[j+1];
                flg = 1;
            }
        }
        if (!flg) {
            break;
        }
    }

    return 0;
}

/**
 * @Brief  select sort (n^2)
 *
 * @Param  parr
 * @Param  len
 *
 * @return 0 for success
 */
static int select_sort(int *parr, int len)
{
    int i = 0, j = 0, max = 0;

    if (parr == NULL) {
        return -1;
    }

    for (i = 0; i < len-1; i++) {
        max = i;
        for (j = i+1; j < len; j++) {
            if (parr[max] < parr[j]) {
                max = j;
            }
        }
        if (i != max) {
            parr[i] = parr[i] ^ parr[max];
            parr[max] = parr[i] ^ parr[max];
            parr[i] = parr[i] ^ parr[max];
        }
    }

    return 0;
}

/**
 * @Brief  insert sort (n^2)
 *
 * @Param  parr
 * @Param  len
 *
 * @return 0 for success
 */
static int insert_sort(int *parr, int len)
{
    int i = 0, j = 0, temp = 0;

    if (parr == NULL) {
        return -1;
    }

    for (i = 1; i < len; i++) {
        temp = parr[i];
        for (j = i-1; j >= 0; j--) {
            if (parr[j] > temp) {
                parr[j+1] = parr[j];
                parr[j] = temp;
            }
        }
    }

    return 0;
}

/**
 * @Brief  quick sort (nlogn)
 *
 * @Param  parr
 * @Param  len
 *
 * @return 0 for success
 */
static int quick_sort(int *parr, int len)
{
    int i = 0, pivot = 0, lidx= 0, midx = 0, ridx = 0;
    int *left = NULL, *mid = NULL, *right = NULL;

    if (parr == NULL) {
        return -1;
    }

    if (len) {
        pivot = parr[len-1];
        left = (int *)malloc(len * sizeof(int));
        right = (int *)malloc(len * sizeof(int));
        mid = (int *)malloc(len * sizeof(int));
        for (i = 0; i < len; i++) {
            if (pivot > parr[i]) {
                left[lidx++] = parr[i];
            } else if (pivot < parr[i]) {
                right[ridx++] = parr[i];
            } else {
                mid[midx++] = parr[i];
            }
        }
        quick_sort(left, lidx);
        quick_sort(right, ridx);
        for (i = 0; i < lidx; i++) {
            parr[i] = left[i];
        }
        for (i = 0; i < midx; i++) {
            parr[lidx+i] = mid[i];
        }
        for (i = 0; i < ridx; i++) {
            parr[lidx+midx+i] = right[i];
        }
        free(left);
        free(mid);
        free(right);
    }

    return 0;
}

/**
 * @Brief  merge sort (nlogn)
 *
 * @Param  parr
 * @Param  len
 *
 * @return 0 for success
 */
static int merge_sort(int *parr, int len)
{
    int i = 0, idx = 0;
    int start = 0, start1 = 0, end1 = 0, start2 = 0, end2 = 0;
    int *arr = parr, *tmp = NULL, *ptmp = NULL;

    if (ptmp == NULL || parr == NULL) {
        return -1;
    }

    ptmp = (int *)malloc(len * sizeof(int));

    for (i = 1; i < len; i *= 2) {
        for (start = 0; start < len; start += 2*i) {
            idx = start;
            start1 = start;
            end1 = MIN(start+i, len);
            start2 = end1;
            end2 = MIN(start+2*i, len);

            while (start1<end1 && start2<end2) {
                ptmp[idx++] = arr[start1]<arr[start2] ? arr[start1++] : arr[start2++];
            }
            while (start1 < end1) {
                ptmp[idx++] = arr[start1++];
            }
            while (start2 < end2) {
                ptmp[idx++] = arr[start2++];
            }
        }
        tmp = arr;
        arr = ptmp;
        ptmp = tmp;
    }

    if (arr != parr) {
        for (i = 0; i < len; i++) {
            ptmp[i] = arr[i];
        }
        ptmp = arr;
    }
    free(ptmp);

    return 0;
}

#ifdef SORT_TEST
static int sort_test(sort_func sort, int *parr, int len)
{
    int ret = -1;

    if (parr && sort) {
        ret = sort(parr, len);
    }

    return ret;
}

static void array_print(int *parr, int len)
{
    int i = 0;

    printf("{ ");\
    for (i = 0; i < len-1; i++) {
        printf("%d, ", parr[i]);
    }
    printf("%d }\n", parr[len-1]);\
}

#define TEST_CASE(sort, parr) do {\
    sort_test(sort, parr, ARR_LEN(parr));\
    printf("after " #sort " " #parr " = ");\
    array_print(parr, ARR_LEN(parr));\
} while (0)

int main(int argc, char const* argv[])
{
    int arr1[] = {1, 5, 4, 9, 8, -1, 10};
    int arr2[] = {7, 6, -10, 25, 55, 2};
    int arr3[] = {1, 3, 5, 0, 2, 4, 8, 7, 9, 6};
    int arr4[] = {34, 12, 1, -25, 65, 2, 4, 9, 1};
    int arr5[] = {-9, 33, 2, 9, 6, 1, 3, 5, 4, 8, 10, 7};

    TEST_CASE(bubble_sort, arr1);
    TEST_CASE(select_sort, arr2);
    TEST_CASE(insert_sort, arr3);
    TEST_CASE(merge_sort, arr4);
    TEST_CASE(quick_sort, arr5);

    return 0;
}
#endif
