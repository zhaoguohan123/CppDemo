#include <stdio.h>
#include <Windows.h>

int b = 9;
extern const DWORD a = 10; // const �������ļ�����Ч

extern void fun_a();
int main(){
	
	fun_a();
	printf("main a = %d ,b = %d\n",a,b);
	getchar();
}