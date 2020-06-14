#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include<string.h>

int main(int argc, char *argv[]){
pid_t proces; 
int status;
char nazwa[60]="";
FILE *plik;
int i;
 
 proces = fork();
 
 if(proces == -1)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
if(proces == 0)
    {
			 if (argc<2) 
			        {
			            printf("Nie podano pliku na poczatku programu!\n");
			            exit(1);
			            return 5;
    				}
    		else
    		{
    			strcat(nazwa, argv[1]);
    			if((plik = fopen(nazwa, "w")) == NULL) {
	            	perror("blad tworzenia pliku");
	        		return 2;
	            }
	            
				for (i = 9; i<=99; i++)
            	{
	                if(i%3==0)
	                {
	                	fprintf(plik,"%d\n", i);
					}
            	}
            fclose(plik);
            exit(0);	
			}		
    }


    wait(&status);

    
    if (WIFEXITED(status))
    {
        printf("Status wyjscia procesu potomnego to %d\n ",WEXITSTATUS(status));
        
    }
    return 0;

}
