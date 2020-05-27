#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "utilities.h"

#define MAX_LINE 1024


//This is the way to enter password
//you know it would be crazy if I use algorithm to encrypt all these
//with public key of the server and send it, only the server can decode it with it RSA private key
//that would so damn cool, but this isn't python so it won't be easy

//[PRIOR]
// void changeCharToAterisk(){
//     do{

//     }
// }

int main(int argc, char *argv[]){
    
    int sockfd, n;
    // set all the bit to 0
    int counter = 0;
    int authenticated = 0;
    int userChoice = 0;
    char code[MAX_LINE] = {0};
    char userName[MAX_LINE] = {0}; 
    char password[MAX_LINE] = {0};
   
    struct sockaddr_in serverAddr; 
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    if (argc != 2){
        printf("./lamb zeroska\nzeroska is the name of creator aka Nguyen Dang Khuong");
        exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Some thing wrong in socket()\n");
        exit(1);
    }
    //set things for the socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1337);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    //connect to server
    if(connect(sockfd, (struct sockaddr*)&serverAddr, sizeof serverAddr) < 0){
        printf("Something wrong in connect()\n");
        exit(1);
    }
    //after send this infomation, the server will check
    //If user enter the right password and username -> Ok! time to chat
    //If not user will have to register 
    //
    do{
        //this counter looks redundant
        if (counter == 3){
            printf("You have your chance\n GOOD BYE!");
            exit(1);
        }
        printf("Enter you username: ");
        fgetstr(userName, sizeof userName, stdin);
        printf("Enter your password: ");
        fgetstr(password, sizeof password, stdin);
        counter++;

        //send userName and password to the server for authenticate
        send(sockfd, userName, sizeof userName,0);
        send(sockfd, password, sizeof password, 0);
        
        //if server response is 401 then just keep asking for password and username
        //after 3 try exit the program
        printf("[*] Sending information\n");
        read(sockfd,code, MAX_LINE);
        //THIS IS A CRIME BY NOT SPLIT THESE THING TO ITS OWN FUNCTION ...
        if(strcmp(code, "401")==0){
            memset(userName, 0, sizeof userName);
            memset(password, 0, sizeof password);
            printf("You don't have an account yet, would you like to have one\nYes(1) or No(Any key): ");
            scanf("%d",&userChoice);
            fflush(stdin);

            if(userChoice == 1){     
                printf("[*] Sign Up\n");
                printf("Enter you name: ");
                fgetstr(userName,sizeof userName, stdin);
                printf("Enter your password: ");
                fgetstr(password, sizeof password,stdin);
                //send user register information
                //A note here for my fallen friend, use sizeof instead of strlen
                send(sockfd,userName,sizeof userName,0);
                send(sockfd,password, sizeof password,0);
                printf("**** Authenticated ****\n");
            }
            else{
                printf("Should create an account my friend\n");   
                exit(1);
            }
        }
        authenticated = 1;
    }while(authenticated == 0);
    printf("[*] Welcome to Lamb Chat - by Zeroska\n");

    //loop for the client chat, send and recv from the server
    while(1){
        char userInput[MAX_LINE] = {0};
        char serverResponse[MAX_LINE] = {0};

        printf("%s > ", userName);

        
        fgetstr(userInput, sizeof userInput, stdin);
        //damn should I use concat to combine 2 string together
        //Why It just send single shit 
        send(sockfd, userInput, sizeof userInput,0);
        if (strcmp(userInput, "!exit") == 0){
            break;
        }
        printf("[*] Wait for server to reply\n");
        //if you want to send without any prior than I think we should have a chekck
        //or a loop in this something

        //recv(sockfd,serverResponse,strlen(serverResponse),0);
        read(sockfd, serverResponse, MAX_LINE);
        printf("server: %s\n",serverResponse);
    }
    printf("GoodBye, Come again");
    return 0;
}
