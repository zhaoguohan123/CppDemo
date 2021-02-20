// Demo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define NUM_THREADS     5

using namespace std;

struct thread_data
{
	int thread_id;
	char * message;
};

void * PrintHello(void * threadarg)  // �̺߳����������������Ĳ���
{
	struct thread_data * my_data;
	my_data = (struct thread_data *)threadarg;

	cout<< "Thread ID: \t"<<my_data->thread_id;
	cout<< "Message: "<<my_data->message<<endl;

	pthread_exit(NULL);
	return 0;
}

void CallBackFun()               // ����Ҫ�����̵߳Ĳ���
{
	pthread_t threads[NUM_THREADS] = {0};
	//struct thread_data td[NUM_THREADS] = {0};
	struct thread_data *td[NUM_THREADS];                                   // ʹ�ýṹ��ָ�����飬���������ڴ�
	
	int rc;
	int i;

	for( i=0; i < NUM_THREADS; i++ ){
		td[i] = (struct thread_data *)malloc(sizeof(struct thread_data));   // ʹ�ö��ڴ�
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

