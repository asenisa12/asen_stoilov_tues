#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define ARRAY_SIZE 100000

int main()
{
	int i,average1,average2;
	int arr[ARRAY_SIZE];
	for(i=0;i<ARRAY_SIZE; i++)
	{
		arr[i] = i;
	}

	pid_t child_a = fork();
	if (child_a == 0)
	{
		int sum =0;
		for(i=0;i<ARRAY_SIZE/2; i++)
			sum += arr[i];
		average1 = sum/(ARRAY_SIZE/2);
		printf("average1: %d\n", average1);
		return average1;
	}
	else if (child_a > 0)
	{
		pid_t child_b = fork();
		if (child_b == 0)
		{	
			int sum;
			for(i=ARRAY_SIZE/2;i<ARRAY_SIZE; i++)
				sum += arr[i];
			average2 = sum/(ARRAY_SIZE/2);
			printf("average2: %d\n", average2);
			return average2;
		}
		else if (child_b > 0)
		{
			int status1,status2;
			waitpid(child_a,&status1,0);

			printf("Parent process successfully waited for child process1!\n");

			printf("The *raw* status information of the child process1 is: %d\n", status1);

			printf("The *exit* status (the return value) of child process1 is: %d\n", WEXITSTATUS(status1));

			waitpid(child_b,&status2,0);

			printf("Parent process successfully waited for child process2!\n");

			printf("The *raw* status information of the child process2 is: %d\n", status2);

			printf("The *exit* status (the return value) of child process2 is: %d\n", WEXITSTATUS(status2));
			
		}
	}



	return 0;
}