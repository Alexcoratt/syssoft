#ifndef CUSTOM_TYPENAME_REGISTRY_H
#define CUSTOM_TYPENAME_REGISTRY_H

#include "DynamicArray.h"
#include <stdint.h>

extern DynamicArray customTypeNameRegistry;

typedef uint32_t type_t;
#define UNKNOWN_TYPENAME UINT32_MAX

void initCustomTypeRegistry();
void termCustomTypeRegistry();

void addCustomType(const char *typeName);
type_t getCustomType(const char *typeName);

#endif