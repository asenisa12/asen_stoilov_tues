#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 20

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}


void *part2(void* data)
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
	
	pthread_t thread;
	int err = pthread_create(&thread,NULL,part2,(void*)arr);
	if (err < 0)
		perror("");
	qsort(arr+(SIZE/2),SIZE/2,sizeof(int),(void*)cmpfunc);
	pthread_join(thread, NULL);
	
	int count1 = 0;
	int count2 = SIZE/2;
	for(i=0;i<SIZE/2;i++){
		int a = arr[count1];
		if ()
		arr[count1]= arr[count2];
		arr[count2] = a;
		count1++;
		count2++;
	}	
	for(i=0;i<SIZE;i++){
			printf("%d\n",arr[i]);
	}

	pthread_exit(NULL);
	
	return 0;
}
