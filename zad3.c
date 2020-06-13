#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *input, *output;
	char nazwaPliku[255] = "";
	int i, c;
	
	if(argc != 2) {
    	fprintf(stderr, "podaj nazwe pliku ktorego tekst ma byc zdredukowany!");
        return 1;
    }
    
    
	input = fopen(argv[1], "r");
	
	if(input == NULL){
		fprintf(stderr, "blad odczytu");
		return 2;
	}

	strcpy(nazwaPliku, argv[1]); 
    strcat(nazwaPliku, ".red");
    
    output = fopen(nazwaPliku, "w");
    if(output == NULL){
    	fprintf(stderr, "blad otwarcia pliku redukujacego");
    	return 3;
	}
	
	i=0;

	while((c = fgetc(input)) != EOF){
		
		if((i%3)==0){
			
			if((fputc(c, output)) == EOF){
				fprintf(stderr, "blad przy wprowadzaniu znakow na wyjscie");
				continue;
			}		
		}
		i++;	
	}
	
	fclose(input);
    if( fclose(output) == EOF) {
        
        perror("blad zamykania");
        return 4;
    }
	return 0;
}
