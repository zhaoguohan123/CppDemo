#include <Windows.h>
#include <stdio.h>

extern int b;
extern const DWORD a;

void fun_a(){
	DWORD cpp_a = a;
	printf("a.cpp a= %d, b = %d \n",cpp_a,b);
}