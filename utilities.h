#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//just some code I copy on the internet
//there are 3 stream in C (you could call it FILE)
//stdin, stdout, stderr in this case stream is stdin 
char *fgetstr(char *string, int n, FILE *stream){
    char* result;
    result = fgets(string, n ,stream);
    if(!result){
        return result;
    }
    if(string[strlen(string) -1] == '\n'){
        string[strlen(string) -1] = 0;
    }
    return string;
}
