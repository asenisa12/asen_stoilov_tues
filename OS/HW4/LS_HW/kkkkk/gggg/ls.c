#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

void output(DIR* pDir,bool flag_a,bool flag_l,bool flag_R){
	struct dirent *dir;

	if(flag_a) printf("1\n");
	if(flag_l) printf("2\n");
	if(flag_R) printf("3\n");

	while((dir = readdir(pDir)) != NULL){

     		printf("%s\n", dir->d_name);
	}
	
	closedir(pDir);
}

bool is_file(char *argument,DIR* pDir,bool flags[3],int *count){
	struct dirent *dir;
	rewinddir(pDir);
	while((dir = readdir(pDir)) != NULL){
		if(dir->d_type == DT_REG && strcmp(dir->d_name,argument)==0) {
			printf("%s ",argument);
			return true;	
		}
	}
	printf("ls cannot")
	return false;
}

int main(int argc, char** argv){
	bool flags[3]={false,false,false};
	DIR* pDir;

		if(argc<2|| argv[1][0]=='-'){
			printf("as");
			pDir = opendir(".");
		}else  pDir = opendir(argv[1]);

		int i;
		if(argc <2)
			for(i=1;i<argc;i++){
				if(argv[i][0]=='-'){
					int j;
					for(j=1;argv[i][j]!='\0';j++){
						if(argv[i][j]=='l') flags[0]=true;
						if(argv[i][j]=='a') flags[1]=true;
						if(argv[i][j]=='R') flags[2]=true;

					}
				}
			}

		if(pDir == NULL){
			pDir = opendir(".");
			if(is_file(argv[1],pDir)){
				int i;
				for(i=2;i<argc;i++)
					is_file(argv[i],pDir);
				printf("\n");
			}else{
				closedir(pDir);
				printf("Cannot open dir");
				exit(2);	
			}
			
		}else {
			output(pDir,flags[0],flags[1],flags[2]);
		}

	return 0;
}