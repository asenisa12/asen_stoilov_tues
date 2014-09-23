//--------------------------------------------
// NAME: Asen Stoilov
// CLASS: 11a
// NUMBER: 4
// PROBLEM: #3
// FILE NAME: wc3.c (unix file name)
// FILE PURPOSE:
// simulation of collecting gold
//---------------------------------------------

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t* wait_for_worker;
struct mine{//simulates the mine
	int gold;
	bool closed;
	bool ocupied;
};
struct worker{//simulates the worker
	int mine_ocupied;
	int gold_collected;
};
struct element{//argument of the thread
	int count;
	int mines_num;
	int workers_num;
};

struct mine* mines;
struct worker* workers;

bool mines_empty(int size){//shows if the mine is empty or not
	int i;
	int empty=0;
	for (i = 0; i<size; ++i)
		if(mines[i].gold<10)
			empty++;
	if(empty==size) return true;
	return false;
}

void show_gold_mines(int size){
	int i,gold=0;
	for (i = 0; i<size; ++i)
		gold+=mines[i].gold;
	printf("goldin mines %d\n",gold);
}
void show_gold_workers(int size){
	int i,gold=0;
	for (i = 0; i<size; ++i)
		gold+=workers[i].gold_collected;
	printf("gold in workers %d\n",gold);
}

bool all_ocupied(int size){//show if all the mines are ocupied or not
	int i;
	int ocupied=0;
	for (i = 0; i<size; ++i)
		if(mines[i].ocupied==true)
			ocupied++;
	if(ocupied==size) return true;
	return false;
}

bool mine_available(int mines_num, int workers_num ,int mident){//shows if the mine is available fo diging
	int i;
	int count=0;
	for(i=0;i<workers_num;i++){
		if(workers[i].mine_ocupied==mident){
			count++;
		}
	} 
	int workers_per_mine = workers_num / mines_num +1;
	if(count<workers_per_mine)return true;
	return false;	
}

void* colecting(void* arg){
	
	struct element* worker_args = (struct element*)arg;
	int i=0;
	while(1){
		if(!mines[i].closed){
			if(!mines[i].ocupied || (all_ocupied(worker_args->mines_num) && mine_available(worker_args->mines_num,worker_args->workers_num,i))){
				mines[i].ocupied=true;

				while (mines[i].gold>0){
					if(pthread_mutex_lock(&wait_for_worker[i])!=0)
						perror("");
					workers[i].mine_ocupied = i;
					
					if(mines[i].gold>0){
						printf("Worker %d entered the mine %d\n",worker_args->count,i);
						workers[worker_args->count].gold_collected += 10;
						mines[i].gold -=10;
						usleep(5);
						printf("Worker %d exited the mine  %d\n", worker_args->count,i);
					}else mines[i].closed=true;

					if(pthread_mutex_unlock(&wait_for_worker[i])!=0)
						perror("");	
					usleep(5);

				}
			}
		}
		if(mines_empty(worker_args->mines_num))break;
		i++;
		if(i==worker_args->mines_num) i=0;
	}
	pthread_exit(NULL);
}

int main(int argc, char const *argv[]){

	int M = atoi(argv[1]);
	int gold = atoi(argv[2]);
	int N = atoi(argv[3]);

	pthread_t worker_thread[N];
	int i;

	
	wait_for_worker =malloc(sizeof(pthread_mutex_t)*M); 
	mines = malloc((sizeof(struct mine))*(M+100));
	workers = malloc((sizeof(struct worker))*(N+100));

	for(i=0;i<M;i++){
		mines[i].gold=gold;
		mines[i].closed=false;
		mines[i].ocupied=false;
		if(pthread_mutex_init(&wait_for_worker[i], NULL)!=0)
		perror("");
	}
	show_gold_mines(M);
	struct element elem[N];
	for (i=0;i<N;i++){
		elem[i].count = i;
		elem[i].mines_num = M;
		elem[i].workers_num = N;
		workers[i].gold_collected=0;
		if(pthread_create(&worker_thread[i],NULL,colecting,&elem[i])!=0) 
			perror("");
	}
	for (i=0;i<N;i++){
		pthread_join(worker_thread[i],NULL);
	}
	show_gold_mines(M);
	show_gold_workers(N);
	for(i=0;i<M;i++)
	if(pthread_mutex_destroy(&wait_for_worker[i])!=0)
		perror("");
	free(mines);
	free(workers);
	free(wait_for_worker);
	return 0;
}