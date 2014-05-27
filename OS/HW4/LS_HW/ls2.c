#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> 
#include  <tgmath.h>

int size();

bool is_dir(char *argument,DIR* pDir,bool flags[3],int count,char* prevdir){
	struct dirent *dir;
	printf("\n");
	rewinddir(pDir);
	while((dir = readdir(pDir)) != NULL){
		if(dir->d_type == DT_DIR && strcmp(dir->d_name,argument)==0) {
				char **Dirs=malloc(sizeof(char)*2);
				int Dcount=0;
				
				char* dirname;
				if(strcmp(prevdir,"")!=0){
					dirname = "";
					dirname = malloc((strlen(prevdir)+strlen(dir->d_name)+size())*sizeof(char));
					strcat(dirname,prevdir);
					strcat(dirname,"/");
					strcat(dirname,dir->d_name);
				}else{
					dirname=argument;
				} 
				//printf("__%s__\n",dirname);
				if(count>0 || flags[2]) printf("%s:\n",dirname);

				struct dirent *dir2;
				DIR* pDir2 = opendir(dirname);
				if(pDir2 == NULL){
					printf("Cannot open dir");
					exit(2);
				}
				//printf(":\n");
				while((dir2 = readdir(pDir2))!= NULL){
					printf("%s ", dir2->d_name);
					if(dir2->d_type == DT_DIR && flags[2] && strcmp(dir2->d_name,".")!=0 && strcmp(dir2->d_name,"..")!=0){
						//printf(",,,,,,,%s\n", dir2->d_name);
						Dirs[Dcount] = malloc((strlen(dir2->d_name)+2)*sizeof(char));
						char* name = dir2->d_name;
						strncpy(Dirs[Dcount],name,strlen(name));
						Dcount++;
					}

				}
				printf("\n");

				if(flags[2] && Dcount>0){
					int i;
					for(i=0;i<Dcount;i++){
						printf("--%s__\n", Dirs[i]);
						is_dir(Dirs[i],pDir2,flags,1,dirname);
					}
				}
				if(strcmp(prevdir,"")!=0)
					free(dirname);
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

int size(){
	return pow(2,25);
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
	if(count>0)printf("\n");
	rewinddir(pDir);
	int given_dirs=0;
	for(i=1;i<argc;i++){
			if(is_dir(argv[i],pDir,flags,count,"."))
				given_dirs++;
	}
	
	//printf("%d\n",count);
	if(given_dirs==0 && count==0){
		if(is_dir(".",pDir,flags,count,""));
	}
	closedir(pDir);

	return 0;

}