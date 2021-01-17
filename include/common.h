#ifndef _INCLUDE_COMMON_H
#define _INCLUDE_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct vm VM;
typedef struct parser Parser;
typedef struct class Class;

#define bool char
#define true 1
#define false 0
// 设置属性,使 gcc对某个语句不产生警告
#define UNSED __attribute__ ((unused))

#ifdef DEBUG
	#define ASSERT(condition, errMsg) \
		do {\
			if  (!(condition)) {\
				fprintf(stderr, "ASSERT failed! %s:%d In function %s(): %s\n", \
					__FILE__, __LINE__, __func__, errMsg); \
				abort(); \
			}\
		} while (0);
#else
	#define ASSERT(condition, errMsg) ((void)0)
#endif

/*
上面的((void)0)表示“什么也不做”,即如果没有DEBUG宏,那么ASSERT语句用一个空的表达式占据
*/

#define NOT_REACHED()\
	do {\
		fprintf(stderr, "NOT_REACHED: %s:%d In function %s()\n", \
			__FILE__, __LINE__, __func__);\
		while (1);\
	} while(0);

/*
程序中有些分支不可能到达，所以要用这个宏来判断
*/
#endif