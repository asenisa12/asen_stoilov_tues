#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct Arg{
	int* num;
	int count;										//num+1
};


typedef struct Arg Arg;
void* sum(void* data)
{	
	struct Arg* arg = (struct Arg*)data;

	if((*arg).count == 1)
	{
		printf("%d\n",*((*arg).num));
		return (void*)((*arg).num);
	}

	if ((*arg).count == 2) 
	{	
		int sum=*((*arg).num) + *(((*arg).num+1));
		printf("%d\n",sum);
		return (void*)(sum);	
	}
	
	int count = (*arg).count/2;
	(*arg).count = count;
	
	pthread_t thread1;
	pthread_create(&thread1,NULL,sum,(void*)arg); //optimizirai !!! napravi za 10 ;)

	int sum1 = 0;
	pthread_join(thread1,(void**)&sum1);

	(*arg).num = (*arg).num+(*arg).count;
	(*arg).count = count;

	pthread_t thread2;
	pthread_create(&thread2,NULL,sum,(void*)arg);
	
	int sum2 = 0;
	pthread_join(thread1,(void**)&sum2);

	int sum = sum1+sum2;
	return (void*)(sum);
}

int main()
{
	int arr[8] = {1,2,3,4,5,6,7,8};
	Arg arg;
	arg.num = arr;
	arg.count = 8;	

	pthread_t thread;
	pthread_create(&thread,NULL,sum,&arg);
	int status = 0;
	pthread_join(thread,(void**)&status);
	printf("%d\n",status);	
	pthread_exit(NULL);
	return 0;		
}	
