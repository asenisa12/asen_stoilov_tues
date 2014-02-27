#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct Arg{
	int* num;
	int count;											//num+1
};


typedef struct Arg Arg;
void sum(void* arg)
{	
	struct Arg* struc = (struct Arg*)arg;
	if ( struc->count == 1 ) return struc->*num;
	
		
	

}

int main()
{
	int arr[10];
	int i;
	for (i=0; i<10; i++) arr[i] = i+1;
	Arg arg;
	arg.num = &arr[0];
	arg.count = 0;	
		
		
	
