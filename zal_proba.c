/*Napisz program, który spełni następujące funkcje:
program będzie przyjmował dowolną liczbę argumentów
pierwszym argumentem będzie nazwa pliku, w którym będą zapisywane informacje. Kolejne argumenty, to nazwy plików, dla których będzie odczytywana ich wielkość.
Przykład pliku wynikowego:
Plik <nazwa_pliku> ma rozmiar: X bajtów, Y kilobajtów, Z megabajtów
Użyj buforowanych oepracji I/O
Operacje tworzenia piku wynikowego oraz zapisania wyników będzie przeprowadzana w nowo utworzonym procesie (procesie potomnym). Jeśli, któryś z plików nie istnieje, proces potomny zwraca 1, w przeciwnym wypadku 0 (nawet jeśli plik nie istnieje, proces potomny nie przerywa działania)
Proces rodzica, ma czekać na proces potomny
Na koniec wyświetl informację, z jakim kodem proces potomny został zakończony, oraz informację o zakończeniu programu.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



int main(int argc, const char * argv[]) {

pid_t pid;
struct stat f_stat;
int ret = 0;
int status;

if (argc <= 1) {
        
        fprintf(stderr, "za malo argumentow!\n");
        return 1;
    }
    
pid = fork();

if(pid == -1){
	    fprintf(stderr, "blad fork\n");
        return 2;
    }
    
if(pid == 0){
	//dziecko
	
	FILE *file;
	int i = 1; // bo argv0 to nazwa pliku
	
	for(; i<argc; i++){
		
		if(i== 1){
			if((file = fopen(argv[i], "w"))==NULL){
				fprintf(stderr, "blad fopen\n");
				return 3;				
			}
			continue;
		}
		
		if(stat(argv[i], &f_stat) == -1){
			fprintf(stderr, "blad stat dla pliku %s\n", argv[i]);
			ret = 1;
			continue;
		}
		
		if(S_ISREG(f_stat.st_mode)){
			
			fprintf(file, "Plik %s ma rozmiar: %d bajtow, %.2f kilobajtow, %.2f megabajtow\n", argv[i], (int)f_stat.st_size, (float)f_stat.st_size/1024,  (float)f_stat.st_size/2048 );
	
		} else {
			printf("%s nie jest plikiem\n", argv[i]);
			continue;
		}
		
		
	}
	if(fclose(file)== EOF){
		fprintf(stderr, "blad fclose\n");
		abort(); //zabij dziecko		
		
	}
	_exit(ret);
}

else if(pid >0){
	//rodzic
	wait(&status);
	
	if(WIFEXITED(status)){
		printf("Status wyjscia dziecka: %d", WEXITSTATUS(status));			
		
	}
}
return 0;
}
    


