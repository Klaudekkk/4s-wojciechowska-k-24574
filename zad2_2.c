#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
	
	int fd;
	int liczba; 
	int i;
    char buf[60];
    
    if(argc != 2){
        perror("nie wipisano nazwy pliku z ktorego pobierac sie bedzie liczby\n");
        return 1;
    }
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1){
    	perror("blad otwarcia pliku");
    	return 2;
	}
	
	
    for(i = 0; i < 10; i++){
    	
        read(fd, &buf, 1);
        lseek(fd, 4, SEEK_CUR);
        liczba = atoi(buf) * 3;
        printf("%d\n", liczba);
        sprintf(buf,"");
    }
    return 0;

}
