#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//just some code I copy on the internet
//there are 3 stream in C (you could call it FILE)
//stdin, stdout, stderr in this case stream is stdin 


//this will be pain, a lot of pain my friend
//Paper about RSA: https://en.wikipedia.org/wiki/RSA_(cryptosystem)


//Simple CEASAR, to be honest Im wanna do the RSA thing so bad, it would take up so much time
//If I just do copy, paste and modify that won't be any issues but I don't like thae (I mean I do like that)



char *ceasarEncrypt(int shift, char *string){
    
}

char *ceasarDecrypt(int unshift, char *string){

}


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
