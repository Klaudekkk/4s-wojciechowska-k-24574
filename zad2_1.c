#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	
	int fd;
	ssize_t retlen;
	const char *buf;
	
	int i, x;
	int tab[10]={0};
	srand(time(NULL));
	for(i = 0; i<10 ;i++){
		tab[i]= (rand() % 10);
	}

	for (i=0; i<10; i++){
		printf("%d\n", tab[i]);
	}
	
	fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
	
	if (fd == -1){
		perror("problem ze stworzeniem");
		return 1;
	}
	
	retlen = write(fd, buf, strlen(buf)); //jak przekazać warosci tab[i] do pliku ???
	
	if (retlen == -1){
		perror("problem z wpisaniem tekstu");
		return 2;
	}
	
	if(close(fd) == -1){
		perror ("problem z zamknieciem fd");
		return 3;
	}
	
	return 0;
	
