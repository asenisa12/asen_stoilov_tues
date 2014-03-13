#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int brashno = 1000;
pthread_mutex_t lock;
int masa[4] = {0,0,0,0};
void* maika(void* arg){
	int max_gram = 100;
	int i = 0;
	while(brashno!=0){
		
		if(brashno<100) max_gram = brashno;
		
		int zagreb = (rand()%max_gram)+1;
		brashno -= max_gram;
		usleep(zagreb*1000);
		
		if(masa[i]==0) masa[i]=1;
		i++;
		if (i>3) i=0;
	}
}

void* ivancho(void* arg){
	int dinamo = (rand()%100)+1;
	usleep(dinamo*1000);
	
}

int main(){
	
	pthread_t maika;
	pthread_t ivancho;
	
	
	
return 0;	
}
