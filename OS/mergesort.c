#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 20

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


void *sort(void* data)
{
	 qsort((int*)data,SIZE/2,sizeof(int),(void*)cmpfunc);	
	return 0;
}

int main()
{	
	int arr[SIZE];
	int i = SIZE;
	int j=0;
	for(i;i>0;i--)
	{	
		arr[j]= i;
		j++;
	}

	pthread_t thread1;
	pthread_t thread2;
	int error = pthread_create(&thread1,NULL,sort,(void*)(arr+(SIZE/2)));
	if (error < 0)
		perror("");
	error = pthread_create(&thread2,NULL,sort,(void*)arr);
	if (error < 0)
		perror("");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	int count1 = 0;
	int count2 = SIZE/2;
	for(i=0;i<SIZE/2;i++){
		if (arr[count2]<arr[count1]){
			int a = arr[count1];
			arr[count1]= arr[count2];
			arr[count2] = a;
		}
		count1++;
		count2++;
	
	}	
	for(i=0;i<SIZE;i++){
			printf("%d\n",arr[i]);
	}

	pthread_exit(NULL);

	return 0;
}
