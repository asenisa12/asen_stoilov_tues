#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int gcd_count(int a, int b){
	int gcd;
	for(int i=1;i<=a&&i<=b;i++)
    	if(a%i==0 && b%i == 0 )
    		gcd = i;
    		
    return gcd;		
}

int gen_d(int e,int fn){
	int d;
	int i=0;
	for(i;;i++){
		d=(fn*i+1)/e;
		if((fn*i+1)%e==0) return d;
	}
	
}

int rand_num(){
	int prime;
	int num=(rand()%512) +128;
	int i =0;
	int count =0; 
	for(i=1;i<num; i++)
		if(num%i==0) count++;
		
		if(count<2) return num; 
	return rand_num();
}

int main(){
	srand(time(NULL));
	int p =rand_num();
	int q;
	while(q=rand_num())
		if(q!=p)break;
		
		
	int n = p*q;
	
	int fn = (p-1)*(q-1);
	int e;
	while(e=(rand()%fn) +1)
		if(gcd_count(e,fn)==1)break;
	printf("e  %d\n",e);	
	int d = gen_d((double)e,(double)fn);
	printf("d  %d\n",d);	
		
		
	return 0;
}
