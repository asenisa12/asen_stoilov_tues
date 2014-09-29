#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define LINK_SIZE sizeof(struct Link)
#define NODE_SIZE sizeof(struct Node)
int M,N;

struct Node{
	int id;
	int link_count;
	struct Link* link;
};

struct Link{
	int weight;
	struct Node *first, *second;
};

int find_shortest(struct Node *node,int first ,int last,int prev){
	int paths_num=0,i,weight=INT_MAX,curweight;

	for(i=0;i<node[first-1].link_count;i++){
		int id1 =node[first-1].link[i].first->id;
		int id2 =node[first-1].link[i].second->id;
		int id;

		if(id1 == last || id2 == last){
			curweight = node[first-1].link[i].weight;
			if(curweight < weight) weight = curweight;
			continue;
		}
		if(id1 != first &&  id1 != prev){
			id = id1;
		}else if(id2 != first &&  id2 != prev){
			id = id2;
		}else continue;

		curweight = node[first-1].link[i].weight + find_shortest(node,id,last,first);
		if(curweight<weight) weight = curweight; 
	}
	return weight;
}

void add_to_graph(struct Link *link, struct Node *node, int i){
	if(node[i].link_count == 0){
		node[i].link=link;
	}else{
		struct Node *nd2 = (struct Node*)realloc(node,N*NODE_SIZE+LINK_SIZE); 
		node = nd2;
		struct Link *links = (struct Link*)malloc((node[i].link_count+1) * LINK_SIZE);
		memcpy(&links, &(node[i].link), (size_t)(node[i].link_count * LINK_SIZE));

		links[node[i].link_count] = *link;
		node[i].link = (struct Link*)malloc((node[i].link_count+1) * LINK_SIZE);
		node[i].link = links;
	}
	node[i].link_count++;
}

int main(){
	printf("input N: ");
	scanf("%d",&N);
	printf("input M: ");
	scanf("%d",&M);

	if(N<=0 || M<=0){
		printf("\nWrong input !!!\n");
		return -1;
	}

	struct Node *nd = (struct Node*)malloc(N*(NODE_SIZE+LINK_SIZE));
	int i;
	
	for(i=0; i<N; i++){
		nd[i].id = i+1;
		nd[i].link_count = 0;
		nd[i].link = malloc(LINK_SIZE);
	}

	struct Link *link = (struct Link*)malloc(M*LINK_SIZE);

	for(i=0;i<M;i++)
		while(true){
			int num1,num2,weight;
			printf("input num1: ");
			scanf("%d",&num1);
			printf("input num2: ");
			scanf("%d",&num2);
			printf("input weight: ");
			scanf("%d",&weight);

			if(num1>N-1 || num2>N-1 || num1<0 || num2<0){
				printf("\nwrong input\n");
				continue;
			}

			link[i].first = &nd[num1];
			link[i].second = &nd[num2];
			link[i].weight =weight;

			add_to_graph(&link[i],nd,num1);
			add_to_graph(&link[i],nd,num2);

			break;
		}

	for(i = 0;i<N;i++){
		int j;
		for(j=0;j<nd[i].link_count;i++){
			printf("%d %d\n",i,nd[i].link[j].first->id);
			printf("%d\n",nd[i].link[j].second->id);
		}
	}

	printf("shortest path %d\n",find_shortest(nd,1,2,-1));


	free(link);	
	free(nd);
	return 0;
}