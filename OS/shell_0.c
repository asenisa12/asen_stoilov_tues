#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int error(char* argv){
	int f,r;
	char buffer[5000],all[50];
	//f - резултата от open()
	//r - резултата от read() 
	//buffer -  buffer :D
	f = open(argv,O_RDONLY,S_IRUSR);
	if (f<0){
		perror(argv);
		return 0;
	} else {
		r=read(f,buffer,5000);
		if (r<0) {
		strcat(all,argv);	
		strncat(all,": Permission denied ",strlen(": Permission denied "));	
		perror(all);
		close(f); return 0;
		} else {
		close(f);
		return 1;
		}
	}
}

char** parse_cmdline(const char* line){
	char** array = malloc(128 * (sizeof(char)));
	int i,j=0,begin=0,elemSize=0;
	for (i=0; line[i] != '\0'; i++){
		if((line[i] != ' ') || (line[i] != '\0'))
		elemSize++;
		if ((line[i] == ' ' && line[i+1] != ' ') || (line[i+1] == '\0' && line[i-1] != ' ')){
			array[j] = malloc(elemSize * (sizeof(char)+1));
			strncpy(array[j],(line)+begin,elemSize-1);
			elemSize = 0;
			j++;	
			begin = i+1;
		}
	}
return array;
}

int main() {
char* cmdline = NULL;
size_t size = 100;
	while(feof(stdin)==0){
		if(feof(stdin)) break;
		getline(&cmdline,&size,stdin);
		
		pid_t pid = fork();
		
		if (pid == -1){ // проверява дали fork() дава грешка
			perror("fork()");
			return 1;
		}
		else if (pid == 0){ // проверява дали pid е = 0 следователно имаме child процес
			char** arglist = parse_cmdline(cmdline); //foo приема стоиноста на масива върнат от parse_cmdline()
	
			if(error(arglist[0]) != 0){//ако foo[0] е фаил го изпълнява заедно с останалите
				int i;
				for (i=1; arglist[i] != NULL; i++){
				char* const* arg = &arglist[i];
				execv(arglist[0],arg);
				perror("");
				}
		
			}
			free(arglist);
		}
		else{
			int status;
			waitpid(pid,&status, 0);// изчаква child процеса да смени състоянието си
			printf("child status %d\n",WEXITSTATUS(status));// и го принтира на стандарния 
		}
	}
	
return 0;
}
