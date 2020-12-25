#include <stdio.h>
#include <Windows.h>

int b = 9;
extern const DWORD a = 10; // const 对象尽在文件内有效

extern void fun_a();
int main(){
	
	fun_a();
	printf("main a = %d ,b = %d\n",a,b);
	getchar();
}