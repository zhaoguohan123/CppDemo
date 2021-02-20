// Demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define NUM_THREADS     5

using namespace std;

struct thread_data
{
	int thread_id;
	char * message;
};

void * PrintHello(void * threadarg)  // 线程函数用来输出被传入的参数
{
	struct thread_data * my_data;
	my_data = (struct thread_data *)threadarg;

	cout<< "Thread ID: \t"<<my_data->thread_id;
	cout<< "Message: "<<my_data->message<<endl;

	pthread_exit(NULL);
	return 0;
}

void CallBackFun()               // 生成要传入线程的参数
{
	pthread_t threads[NUM_THREADS] = {0};
	//struct thread_data td[NUM_THREADS] = {0};
	struct thread_data *td[NUM_THREADS];                                   // 使用结构体指针数组，方便分配堆内存
	
	int rc;
	int i;

	for( i=0; i < NUM_THREADS; i++ ){
		td[i] = (struct thread_data *)malloc(sizeof(struct thread_data));   // 使用堆内存
		cout <<"main() : creating thread, " << i << endl;
		td[i]->thread_id = i;
		td[i]->message = (char * )"This is message";
		rc = pthread_create(&threads[i], NULL,
			PrintHello, (void *)td[i]);
		if (rc){
			cout << "Error:unable to create thread," << rc << endl;
			exit(-1);
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	CallBackFun();
	//Sleep(10000);
	//pthread_exit(NULL);
	getchar();
	return 0;
}

