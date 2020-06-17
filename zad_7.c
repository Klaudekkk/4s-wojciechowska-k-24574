#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include<time.h>

static void sig_usr(int);
FILE *file;

int main(int argc, char *argv[])
{

	pid_t pid = getpid();
	if((file = fopen("zad7.txt", "w"))==NULL){
		fprintf(stderr, "blad fopen\n");
		return 3;				
	}
	fprintf(file, "PID aktualnego procesu: %d\n", (int) getpid());	
	
	
	
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("cannot catch SIGUSR1\n");
        return 1;
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("cannot catch SIGUSR2\n");
        return 1; 
    }

    while(1){
    	pause();
	}
	

	
		
		
	}


static void sig_usr(int signo)
{
    if(signo == SIGUSR1){
        printf("received SIGUSR1\n");
        fprintf(file, "PID aktualnego procesu: %d\n", (int)getppid());	
        fclose(file);
        exit(0);
    }
        
    else if(signo == SIGUSR2){
    	printf("received SIGUSR2\n");
    	file = freopen("pid.txt", "w",file);
        fclose(file);
        exit(0);
	}
        
    else
    {
        printf("received signal %d\n", signo);
    }
}
