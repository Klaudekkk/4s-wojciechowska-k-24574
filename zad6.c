#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
	
	pid_t proces; 
	int status;
	int ret;
	
	proces= fork();
	
	if (proces == -1){
		fprintf(stderr, "Fork failed\n");
        return 1;		
	}
	
	
	if (proces == 0){
		//printf("Jestem dzieckiem/n");
		ret = execlp("ls", "ls", "-l", NULL);
		if(ret == -1){
			fprintf(stderr, "exec error\n");
        	return 2;
		}
		
		exit(0);
	}
	
	else if( proces > 0){
		//printf("jestem rodzicem/n");
		
		wait(&status);
		
	}
	
	printf("koniec\n");
	return 0;

}
