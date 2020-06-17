#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{

	FILE *file1;
	FILE *file2;
	DIR *d;
	DIR *d2;
	struct dirent *dir;
	char sciezka[256];
	struct stat f_stat;
	
	mkdir("results", (S_IRUSR | S_IWUSR | S_IXUSR | S_IXGRP | S_IXOTH));
	
	
	file1 = fopen("results/etc_dir.out", "w");
	
	if(file1 == NULL){
		fprintf(stderr, "blad tworzenia pliku etc_dir.out \n");
        return 2;
	}
	
	if((file2 = fopen("results/sysconfig.out", "w") ) == NULL){
		fprintf(stderr, "blad tworzenia pliku sysconfig.out\n");
        return 3;
	}
	// generowanie do pliku etc_dir.out folderow z /etc
	d = opendir("/etc");
	if(d != NULL){
		while( (dir = readdir(d)) != NULL){
		
		if(dir->d_type == DT_DIR){
			fprintf(file1, "\t%s/n", dir->d_name);
		}
				closedir(d);
	}
}

	
	// generowanie do pliku  sysconfig.out
	d2 = opendir("/etc/sysconfig");
	
	while ( (dir = readdir(d2)) != NULL ){
		
		if(dir->d_type == DT_REG){
			fprintf(file2, "\t%s/n", dir->d_name);
		
                memset(sciezka,'\0',256);
                strcat(sciezka,"/etc/sysconfig/");
                strcat(sciezka, dir->d_name);
                
                if(lstat(sciezka, &f_stat) == -1){
                    fprintf(stderr, "Blad przy otwieraniu pliku %s\n", dir->d_name);
                    return 2;
                }
                if(f_stat.st_mode & S_IROTH)
                    continue;
                if(f_stat.st_mode & S_IWOTH)
                    continue;
                    
                    
                if(f_stat.st_mode & S_IXOTH)
                    continue;
                fprintf(file2, "%s\n", dir->d_name);
                }
		}


	closedir(d2);

	fclose(file1);
fclose(file2);

	return 0;
}
