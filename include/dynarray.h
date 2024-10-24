#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <stddef.h>

#ifdef DYN_ARRAY_VALUE_TYPE
    typedef DYN_ARRAY_VALUE_TYPE darr_value_t;
    #ifndef DYN_ARRAY_ERR_VALUE
        #error "Dynamic array error value is not set"
    #endif
#else
    #warning "Dynamic array value type is not set. Default type is int"

    #include <limits.h>
    typedef int darr_value_t;
    #define DYN_ARRAY_ERR_VALUE INT_MIN
#endif

struct DynArray {
    size_t size;
    size_t maxSize;
    darr_value_t *values;
};

// basic methods
void DynArrayInit(struct DynArray *, size_t, const darr_value_t *);
void DynArrayTerm(struct DynArray *);

// value access
darr_value_t *DynArrayAt(struct DynArray *, size_t);
darr_value_t *DynArrayAtNoRangeCheck(struct DynArray *, size_t); // get access to value from DynArray without out of range checking

darr_value_t *DynArrayFront(struct DynArray *);
darr_value_t *DynArrayBack(struct DynArray *);

// getting
darr_value_t DynArrayGet(const struct DynArray *, size_t);
darr_value_t DynArrayGetNoRangeCheck(const struct DynArray *, size_t); // get value from DynArray without out of range checking

size_t DynArraySize(const struct DynArray *);

// setting
void DynArrayResize(struct DynArray *, size_t newSize);

void DynArrayPushBack(struct DynArray *, darr_value_t);
darr_value_t DynArrayPopBack(struct DynArray *);

#endif