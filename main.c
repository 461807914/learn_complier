#include "common.h"


void fun1()
{
	char *s = "test assert!";
	ASSERT(0, s);
}
void fun2()
{
	NOT_REACHED();
}

int main()
{
	printf("hello complier!\n");
	fun2();
	return 0;
}