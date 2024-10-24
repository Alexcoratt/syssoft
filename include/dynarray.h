#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#ifndef DYN_ARRAY_MAX_SIZE_RATIO
    #define DYN_ARRAY_MAX_SIZE_RATIO 1.5F
#endif

#ifndef DYN_ARRAY_MIN_SIZE
    #define DYN_ARRAY_MIN_SIZE 4LU
#endif

#define MAX(LEFT, RIGHT) ((LEFT) > (RIGHT) ? LEFT : RIGHT)
#define CALL(OBJ, METHOD, ...) OBJ.methods->METHOD(&OBJ, ##__VA_ARGS__)
#define CALL_PTR(OBJ, METHOD, ...) OBJ->methods->METHOD(OBJ, ##__VA_ARGS__)

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define DEFINE_DYN_ARRAY(T, ERR_VALUE) \
struct __dyn_array_##T; \
\
struct __dyn_array_methods_##T { \
    /* basic methods */ \
    void (*term)(struct __dyn_array_##T *); \
    \
    /* value access */ \
    T *(*at)(struct __dyn_array_##T *, size_t); \
    T *(*atNoRangeCheck)(struct __dyn_array_##T *, size_t); \
    \
    T *(*front)(struct __dyn_array_##T *); \
    T *(*back)(struct __dyn_array_##T *); \
    \
    /* getting */ \
    T (*get)(const struct __dyn_array_##T *, size_t); \
    T (*getNoRangeCheck)(const struct __dyn_array_##T *, size_t); \
    \
    size_t (*size)(const struct __dyn_array_##T *); \
    \
    /* setting */ \
    void (*resize)(struct __dyn_array_##T *, size_t newSize); \
    \
    void (*pushBack)(struct __dyn_array_##T *, T); \
    T (*popBack)(struct __dyn_array_##T *); \
}; \
\
typedef struct __dyn_array_##T { \
    const struct __dyn_array_methods_##T *methods; \
    size_t size; \
    size_t maxSize; \
    T *values; \
} DynArray_##T; \
\
/* basic methods */ \
void __dyn_array_term_##T(struct __dyn_array_##T *arr) { \
    free(arr->values); \
} \
\
/* value access */ \
T *__dyn_array_at_##T(struct __dyn_array_##T *arr, size_t index) { \
    if (index < arr->size) \
        return arr->values + index; \
    return NULL; \
} \
\
T *__dyn_array_at_no_range_check_##T(struct __dyn_array_##T *arr, size_t index) { \
    return arr->values + index; \
} \
\
T *__dyn_array_front_##T(struct __dyn_array_##T *arr) { \
    return arr->values; \
} \
\
T *__dyn_array_back_##T(struct __dyn_array_##T *arr) { \
    if (arr->size == 0) \
        return NULL; \
    return arr->values + (arr->size - 1); \
} \
\
/* getting */ \
T __dyn_array_get_##T(const struct __dyn_array_##T *arr, size_t index) { \
    if (index < arr->size) \
        return arr->values[index]; \
    return ERR_VALUE; \
} \
\
T __dyn_array_get_no_range_check_##T(const struct __dyn_array_##T *arr, size_t index) { \
    return arr->values[index]; \
} \
\
size_t __dyn_array_size_##T(const struct __dyn_array_##T *arr) { \
    return arr->size; \
} \
\
/* setting */ \
void __dyn_array_resize_##T(struct __dyn_array_##T *arr, size_t newSize) { \
    arr->size = newSize; \
    \
    if (newSize > arr->maxSize) { \
        arr->maxSize = newSize * DYN_ARRAY_MAX_SIZE_RATIO; \
        arr->maxSize = MAX(arr->maxSize, DYN_ARRAY_MIN_SIZE); \
        arr->values = (T *)realloc(arr->values, arr->maxSize * sizeof(T)); \
    } \
} \
\
void __dyn_array_push_back_##T(struct __dyn_array_##T *arr, T value) { \
    __dyn_array_resize_##T(arr, arr->size + 1); \
    *__dyn_array_back_##T(arr) = value; \
} \
\
T __dyn_array_pop_back_##T(struct __dyn_array_##T *arr) { \
    if (arr->size == 0) \
        return ERR_VALUE; \
    T res = *__dyn_array_back_##T(arr); \
    __dyn_array_resize_##T(arr, arr->size - 1); \
    return res; \
} \
\
static const struct __dyn_array_methods_##T dyn_array_##T##_methods = { \
    __dyn_array_term_##T, \
    __dyn_array_at_##T, \
    __dyn_array_at_no_range_check_##T, \
    __dyn_array_front_##T, \
    __dyn_array_back_##T, \
    __dyn_array_get_##T, \
    __dyn_array_get_no_range_check_##T, \
    __dyn_array_size_##T, \
    __dyn_array_resize_##T, \
    __dyn_array_push_back_##T, \
    __dyn_array_pop_back_##T \
}; \
\
void initDynArray_##T(struct __dyn_array_##T *arr, size_t size, const T *values) { \
    arr->size = size; \
    arr->maxSize = size * DYN_ARRAY_MAX_SIZE_RATIO; \
    arr->maxSize = MAX(arr->maxSize, DYN_ARRAY_MIN_SIZE); \
    arr->values = (T *)malloc(arr->maxSize * sizeof(T)); \
    arr->methods = &dyn_array_##T##_methods; \
    \
    if (values != NULL) \
        memcpy(arr->values, values, size * sizeof(T)); \
}

#endif