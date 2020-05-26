#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "unistd.h"
#include "string.h"
#include "arpa/inet.h" 
#include "utilities.h"
#include "time.h"

#define MAX 1024
//I want to write the data of the user to a file
//which is our database 
//cool ehhehehe
struct User{
    char name[MAX];
    char password[MAX];
};

void saveTofile(struct User user){
    FILE *p = fopen("database.txt","w");
    fprintf(p, "user:%s\npassword:%s", user.name, user.password);
    fclose(p);
}

void readDatabase(){
    FILE *p = fopen("database.txt","r");
}

// void authenticate(){

// }


int main(void){
    int listenfd, connfd, val;
    struct sockaddr_in serverAddr;
    
    if ((listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0){
        printf("Something wrong in socket()");
        exit(1);
    }
    printf("[*] socket created\n");
    //seting up the socket properties
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1337);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    //if what's wrong with bind
    if ((bind(listenfd, (struct sockaddr *) &serverAddr,sizeof serverAddr)) < 0){
        printf("Something wrong in bind()");
        exit(1);
    }
    //To be honest I want to make it has a little bit of delay for the effect that
    //something is happening but =)) the delay function I code is getting bypass everytime
    
    printf("[*] Bind succesful\n");
    //after bind we will listen for connection, max = 100 connection
    listen(listenfd,100);
    printf("[*] Listen for connection\n");
    printf("[*] Server up and running\n");
    //this is where magic happen
    connfd = accept(listenfd,(struct sockaddr*) NULL, NULL);
    while(1){
        char serverReponse[MAX] = {0};
        char clientSend[MAX] = {0};
        
        read(connfd, clientSend, MAX);
        //recv(connfd,clientSend,strlen(clientSend),0);
        fprintf(stdout,"Client: %s\n", clientSend);
        
        if (strcmp(clientSend, "!exit") == 0){
            close(connfd);
            printf("Client disconnected\n");
        }
        printf("> ");
        fgetstr(serverReponse,sizeof serverReponse, stdin);
        send(connfd,serverReponse,sizeof serverReponse,0);
        printf("Wait for client to reply\n");
        //if someone connect to the server
    }
    return 0;
}