/* 
    - Nazwy plików zostaną przekazane przez użytkownika jako parametry do wywołania programu.
    - Program stworzy nowy katalog zaliczenie, z uprawnieniami 0755
    - Plik o nazwie lista.txt będzie zawierał nazwy plików, które został przekazane jako parametr oraz ich rozmiar. Jeśli plik nie istnieje albo nie jest plikiem regularnym, zapisz odpowiednią informację.
    - Do zapisu użyj buforowanych operacji I/O.
    - Wszystkie powyższe operacje (tworzenie katalogu, zapis do pliku) odbywa się w procesie potomnym. Proces rodzica czeka na dziecko.
    - Na koniec wyświetl informację o numerze PID rodzica, dziecka, oraz informację o zakończeniu programu.
    
 * Author: Klaudia Wojciechowska
 * Date: 17-July-2020
 * Version: 1.0.0
	
 */
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	
pid_t pid;
pid_t ch_pid;
struct stat f_stat;
int katalog;
int stat;
FILE *file;
int i;
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
	//proces dziecka
	katalog = mkdir("zaliczenie",0755);	 //tworzenie katalogu
	if (katalog == -1){
		fprintf(stderr, "nie mozna stworzyc katalogu 'zaliczenie'\n"); // sprawdzenie bledow przy tworzeniu katalogu zaliczenie
        return 3;
	}

	if((file = fopen("zaliczenie/lista.txt", "w"))==NULL){ //utworzenie pliku lista.txt w folderze zaliczenie
					fprintf(stderr, "blad fopen\n"); //sprawdzenie bledow przy tworzeniu pliku txt
					return 4;	
				}
	
	for(i = 1; i<argc; i++){ //sprawdzanie wszystkich argumentow 
			
		if(lstat(argv[i], &f_stat) == -1){ //sprawdzenie czy element istnieje
			fprintf(file, "Plik %s: nie istnieje \n", argv[i]); 
			continue;
		}
		
		else if(S_ISREG(f_stat.st_mode)){ //sprawdzenie czy plik jest regularny 
			
			fprintf(file, "Plik %s: %d\n", argv[i], (int)f_stat.st_size);
			continue;
			}
			
		else {
			fprintf(file,"Plik %s: nie plik regularny\n", argv[i]); //wyswietlenie reszty ktore nie sa plikami regularnymi
			continue;
		}		
	}
	
	if(fclose(file)== EOF){ //zamykamy strumien file i sprawdzamy czy się zamknął, jeżeli nie, wyswietli nam błąd
		fprintf(stderr, "blad fclose\n");			
	}
	
}

else if (pid > 0){
	//proces rodzica
	printf("PID rodzica: %d\n", (int) getpid()); //wyswietla pid rodzica
	ch_pid = wait(&stat); // proces rodzica czeka na dziecko
	printf("PID dziecka: %d\n", (int) ch_pid); //wyswietla pid dziecka ktory jest zwracany z funkcji wait
	
	
	if(WIFEXITED(stat)) 
        {
            printf("Szczesliwe zakonczenie programu,\n status wyjścia %d \n", WEXITSTATUS(stat) ); // sprawdza czy zakonczylo sie sukcesem i zwraca exit code
        }
        if(WIFSIGNALED(stat))
        {
            printf("W programie byly sygnaly,\n status wyjścia %d \n", WEXITSTATUS(stat)); //sprawdza czy po drodze program napotkał jakieś sygnały
        }
        
}

return 0;

	
}
