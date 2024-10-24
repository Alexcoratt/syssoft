#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

#define T_CALLOC(TYPE, SIZE) (TYPE *)calloc(SIZE, sizeof(TYPE))
#define MAX(LEFT, RIGHT) ((LEFT) > (RIGHT) ? LEFT : RIGHT)

#define DYN_ARRAY_MAX_SIZE_RATIO 1.5F
#define DYN_ARRAY_MIN_SIZE 4LU

size_t getDynArrayMaxSize(size_t currentSize) {
    size_t res = currentSize * DYN_ARRAY_MAX_SIZE_RATIO;
    return MAX(res, DYN_ARRAY_MIN_SIZE);
}

// basic methods
void DynArrayInit(struct DynArray *arr, size_t size, const darr_value_t *values) {
    arr->size = size;
    arr->maxSize = getDynArrayMaxSize(size);
    arr->values = T_CALLOC(darr_value_t, arr->maxSize);

    if (values != NULL)
        memcpy(arr->values, values, size * sizeof(darr_value_t));
}

void DynArrayTerm(struct DynArray *arr) {
    free(arr->values);
}

// value access
darr_value_t *DynArrayAt(struct DynArray *arr, size_t index) {
    if (index < arr->size)
        return arr->values + index;
    return NULL;
}

darr_value_t *DynArrayAtNoRangeCheck(struct DynArray *arr, size_t index) {
    return arr->values + index;
}

darr_value_t *DynArrayFront(struct DynArray *arr) {
    return arr->values;
}

darr_value_t *DynArrayBack(struct DynArray *arr) {
    if (arr->size == 0)
        return NULL;
    return arr->values + (arr->size - 1);
}

// getting
darr_value_t DynArrayGet(const struct DynArray *arr, size_t index) {
    if (index < arr->size)
        return arr->values[index];
    return DYN_ARRAY_ERR_VALUE;
}

darr_value_t DynArrayGetNoRangeCheck(const struct DynArray *arr, size_t index) {
    return arr->values[index];
}

size_t DynArraySize(const struct DynArray *arr) {
    return arr->size;
}

// setting
void DynArrayResize(struct DynArray *arr, size_t newSize) {
    arr->size = newSize;

    if (newSize > arr->maxSize) {
        arr->maxSize = getDynArrayMaxSize(newSize);
        arr->values = (darr_value_t *)realloc(arr->values, arr->maxSize);
    }
}

void DynArrayPushBack(struct DynArray *arr, darr_value_t value) {
    DynArrayResize(arr, arr->size + 1);
    *DynArrayBack(arr) = value;
}

darr_value_t DynArrayPopBack(struct DynArray *arr) {
    if (arr->size == 0)
        return DYN_ARRAY_ERR_VALUE;
    darr_value_t res = *DynArrayBack(arr);
    DynArrayResize(arr, arr->size - 1);
    return res;
}