#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	
	int fd;
	char buf[1024];
	char nazwa[100];
	int i;
	ssize_t retlen;
	
	fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
	
	if (fd == -1){
		perror("problem ze stworzeniem");
		return 1;
	}
		

		srand(time(NULL));
	for(i = 0; i<10 ;i++){
		nazwa[i] = (rand() % 10);
 		snprintf(buf, 40, "%d", nazwa[i]);
 		
        retlen = write(fd,buf,4);
        	if (retlen == -1){
				perror("problem z wpisaniem tekstu");
				return 2;
			}
        write(fd, "\n", 1);

	}
		
	if(close(fd) == -1){
		perror ("problem z zamknieciem fd");
		return 3;
	}
	
	return 0;
	
}



