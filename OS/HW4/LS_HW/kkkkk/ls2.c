#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/*void output(char* name,bool flags[3]){
	struct dirent *dir;
	DIR* pDir = opendir(name);
	while((dir = readdir(pDir)) != NULL){
		printf("%s\n", dir->d_name);
	}
	int a =1;
	if(flags[2]){
		rewinddir(pDir);
		while((dir = readdir(pDir)) != NULL){
			if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0)
				is_dir(dir->d_name,pDir,flags,1);
		}		
	}

	closedir(pDir);
}*/


bool is_dir(char *argument,DIR* pDir,bool flags[3],int count){
	struct dirent *dir;
	printf("\n");
	rewinddir(pDir);
	while((dir = readdir(pDir)) != NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,argument)==0) {
				char **Dirs=malloc(sizeof(char)+1);
				int Dcount=0;
				if(count>0 || flags[2]) printf("%s:\n",argument);

				struct dirent *dir2;
				DIR* pDir2 = opendir(dir->d_name);

				while((dir2 = readdir(pDir2))!= NULL){
					printf("%s ", dir2->d_name);
					if(dir2->d_type == DT_DIR && flags[2] && strcmp(dir2->d_name,".")!=0 && strcmp(dir2->d_name,"..")){
						//printf(",,,,,,,%s\n", dir2->d_name);
						Dirs[Dcount] = malloc(sizeof(dir2->d_name)+2);
						const char* name = dir2->d_name;
						strncpy(Dirs[Dcount],name,strlen(name));
						Dcount++;
					}

				}
				printf("\n");

				if(flags[2] && Dcount>0){
					int i;
					for(i=0;i<Dcount;i++){
						printf("--%s__\n", Dirs[i]);
						is_dir(Dirs[i],pDir2,flags,1);
					}
					/*rewinddir(pDir2);

					while((dir2 = readdir(pDir2))!=NULL){
						
						if(strcmp(dir2->d_name,".")!=0 && strcmp(dir2->d_name,"..")!=0)
							is_dir(dir2->d_name,pDir2,flags,1);
						printf("--%s\n", dir2->d_name);
					}*/
				}
				free(Dirs);
				closedir(pDir2);
				return true;
		}
	}
	rewinddir(pDir);
	return false;
}

bool is_file(char *argument,DIR* pDir,bool flags[3],int *count){
	struct dirent *dir;
	while((dir = readdir(pDir)) != NULL){
		if(dir->d_type == DT_REG && strcmp(dir->d_name,argument)==0) {
			printf("%s ",argument);
			*count+=1;
			printf("%d\n",*count);
			return true;	
		}
	}
	rewinddir(pDir);
	return false;
}

int main(int argc, char** argv){
	bool flags[3]={false,false,false};
	DIR* pDir;

	int i;
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
	pDir = opendir(".");
	int count=0;
	for(i=1;i<argc;i++){
			is_file(argv[i],pDir,flags,&count);
	}
	printf("\n");
	rewinddir(pDir);
	int given_dirs=0;
	for(i=1;i<argc;i++){
			if(is_dir(argv[i],pDir,flags,count))
				given_dirs++;
	}
	
	printf("%d\n",count);
	if(given_dirs==0 && count==0){
		if(is_dir(".",pDir,flags,count));
	}
	closedir(pDir);

	return 0;

}