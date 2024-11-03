#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "custom_typename_registry.h"
#include "DynamicArray.h"

size_t findStringInDynamicArray(const DynamicArray *, const char *example);

DynamicArray customTypeNameRegistry;

void initCustomTypeRegistry() {
    initDynamicArray(&customTypeNameRegistry, 0, sizeof(char *), getMaxSizeDefaultImpl);
}

void termCustomTypeRegistry() {
    termDynamicArray(&customTypeNameRegistry);
}

void addCustomType(const char *typeName) {
    pushBackDynamicArray(
        &customTypeNameRegistry,
        strcpy(malloc(strlen(typeName) + 1), typeName) 
    );
}

type_t getCustomType(const char *typeName) {
    size_t found = findStringInDynamicArray(&customTypeNameRegistry, typeName);
    if (found == getDynamicArraySize(&customTypeNameRegistry))
        return UNKNOWN_TYPENAME;

    return (type_t)found;        
}

size_t findStringInDynamicArray(const DynamicArray *darr, const char *example) {
    if (isDynamicArrayEmpty(darr))
        return 0;
    
    size_t res = 0;
    for (; strcmp(example, *(const char **)atConstDynamicArray(darr, res)) != 0; ++res);
    return res;
}