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



char *ceasarEncrypt(int key, char *string){
    char ch;
    //But I copy =))) 
    for(int i = 0; string[i] != '\0'; ++i){
		ch = string[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}	
			string[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			string[i] = ch;
		}
	}
    return string;
}

char *ceasarDecrypt(int key, char *string){
    char ch;
	for(int i = 0; string[i] != '\0'; ++i){
		ch = string[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch - key;
			
			if(ch < 'a'){
				ch = ch + 'z' - 'a' + 1;
			}
			
			string[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch - key;
			
			if(ch < 'A'){
				ch = ch + 'Z' - 'A' + 1;
			}	
			string[i] = ch;
		}
	}
    return string;
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
