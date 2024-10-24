#include <stdio.h>
#include <float.h>

#include "dynarray.h"

DEFINE_DYN_ARRAY(float, FLT_MIN)

void fprintDynArray_float(FILE *out, const char *arrName, const DynArray_float *arr) {
    const size_t size = CALL_PTR(arr, size);
    if (arrName == NULL) arrName = "";
    for (size_t i = 0; i < size; ++i)
        fprintf(out, "%s[%lu] = %f\n", arrName, i, CALL_PTR(arr, get, i));
}

int main(int argc, char **argv) {
    float values[] = {1, 2, 3};

    DynArray_float arr;
    initDynArray_float(&arr, sizeof(values) / sizeof(float), values);

    fprintDynArray_float(stdout, NULL, &arr);
    putchar('\n');

    CALL(arr, pushBack, 0.231);
    CALL(arr, pushBack, 0.3);
    CALL(arr, pushBack, 0.2);
    CALL(arr, pushBack, -234532.0);
    CALL(arr, pushBack, -0.3);
    CALL(arr, pushBack, 2131);

    fprintDynArray_float(stdout, NULL, &arr);

    CALL(arr, term);

    return 0;
}