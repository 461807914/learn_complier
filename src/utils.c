#include "utils.h"
#include "vm.h"
#include "parser.h"
#include <stdlib.h>
#include <stdarg.h>

// vm为虚拟机指针 
void* memManager(VM* vm, void* ptr, uint32_t oldSize, uint32_t newSize) {
	vm->allocatedBytes += newSize - oldSize; // vm统计申请内存的空间
	if (newSize == 0) {
		free(ptr); // 如果realloc(NULL, 0)会返回一个空的指针，这样会浪费
		return NULL;
	}
	return realloc(ptr, newSize);
}

// 找出大于等于v最近的2次幂
uint32_t ceilToPowerOf2(uint32_t v) {
	// 1 << (log(v-1) + 1)
	v += (v == 0);
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v | = v >> 16;
	v++;
	return v;
}

DEFINE_BUFFER_METHOD(String)
DEFINE_BUFFER_METHOD(Int)
DEFINE_BUFFER_METHOD(Char)
DEFINE_BUFFER_METHOD(Byte)

void symbolTableClear(VM* vm, symbolTable* buffer) {
	uint32_t idx = 0;
	while (idx < buffer->count) {
		memManager(vm, buffer->datas[idx++].str, 0 ,0);
	}
	StringBufferClear(vm, buffer);
}

void errorReport(void* parser, ErrorType errorType, const char* fmt, ...) {
	char buffer[DEFAULT_BUFFER_SIZE] = {'\0'};
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buffer, DEFAULT_BUFFER_SIZE, fmt, ap); // 输出可变参数
	va_end(ap);

	switch (errorType) {
		case ERROR_IO:// 文件io出错
		case ERROR_MEM:// 内存出错
			fprintf(stderr, "%s:%d In function %s():%s\n",
					__FILE__, __LINE__, __func__, buffer);
			break;
		case ERROR_LEX: // 词法分析的错误
		case ERROR_COMPILE:// 编译的错误
			ASSERT(parser != NULL, "parser is null!");
			fprintf(stderr, "%s:%d \"%s\"\n", ((Parser*)parser)->file,
					((Parser*)parser)->preToken.lineNo, buffer);
			break;
		case ERROR_RUNTIME:// 运行时的错误
			fprintf(stderr, "%s\n", buffer);
			break;
		default:
			NOT_REACHED();
	}
}