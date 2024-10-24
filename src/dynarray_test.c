#include <stdio.h>
#include <float.h>

#define DYN_ARRAY_VALUE_TYPE float
#define DYN_ARRAY_ERR_VALUE FLT_MIN
#include "dynarray.h"

void printDynArray(const struct DynArray *arr) {
    for (size_t i = 0; i < arr->size; ++i)
        printf("arr[%lu] = %f\n", i, DynArrayGet(arr, i));
}

int main(int argc, char **argv) {
    float values[] = {1, 2, 3};

    struct DynArray darr;
    DynArrayInit(&darr, 3, values);

    printDynArray(&darr);

    DynArrayPushBack(&darr, 0.2354);
    printDynArray(&darr);

    DynArrayTerm(&darr);

    return 0;
}