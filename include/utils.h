#ifndef _INCLUDE_UTILS_H
#define _INCLUDE_UTILS_H
#include "common.h"

void* memManager(VM* vm, void* ptr, uint32_t oldSize, uint32_t newSize);

#define ALLOCATE(vmPtr, type) \
	(type*)memManager(vmPtr, NULL, 0, sizoef(type))

#define ALLOCATE_EXTRA(vmPtr, mainType, extraSize) \
		(mainType*) memManager(vmPtr, NULL, 0, sizeof(mainType) + extraSize)

