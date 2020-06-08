#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {

int fd_input, fd_output;
ssize_t test;
char kopiaplik[255] = "";
char buff[1];
int i;

if (argc != 2) {
	perror("brak argumentow");
	return 1;
}

fd_input = open(argv[1], O_RDONLY); //odczyt
    
    if (fd_input == -1) {
        
        perror("blad otwarcia wejscia");
        return 2;
    }
    
strcpy(kopiaplik, argv[1]);
strcat(kopiaplik, ".red"); 
 
fd_output = open(kopiaplik, O_CREAT | O_TRUNC | O_WRONLY, 0644); //utworzenie kopiaplik
    if (fd_output == -1) {  
        perror("blad otwarcia wyjscia");
        return 2;
    }
    
i= 0;

while (read(fd_input, &buff, 1) == 1) {
	
	if( (i % 3) == 0) {

		test = write(fd_output, &buff, 1);
		
		if (test == -1){
			perror("blad zapisywania");
			continue;
		}
	}
	
	i++;
}
    close (fd_output);
    close (fd_input);
    
    return 0;
	
}
