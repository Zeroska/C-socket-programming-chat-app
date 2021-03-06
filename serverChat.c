#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "utilities.h"

#define MAX_LINE 1024
#define BACKLOG 10 //how many pending connection will be hold
#define CODE_FOUND "1" 
#define CODE_NOT_FOUND "401"
//user data struct
struct User
{
    char name[MAX_LINE];
    char password[MAX_LINE];
};

void saveTofile(struct User user)
{
    //Before saving using algorithm to encrypt
    FILE *p = fopen("database.txt", "a");
    if (p == NULL)
    {
        printf("saveTofile() has problem, please check again\n");
    }
    else
    {
        //the format of the save file
        fprintf(p, "user:%s\npassword:%s\n", user.name, user.password);
        printf("New User Added to the database with %s %s\n",user.name,user.password);
        fclose(p);
    }
}

//This would return 401 for "Can't find user" and 1 for
void initializeDatabase(){
    FILE *p = fopen("database.txt","w");
    if (p == NULL){
        printf("Something wrong in ADMIN\n");
        exit(1);
    }else{
        fprintf(p,"user:%s\npassword:%s\n","ZEROSKA","KHUONG");
        fclose(p);
    }
}

int searchDatabase(struct User user)
{
    FILE *p = fopen("database.txt", "r");
    struct User temp;
     
    if (p == NULL)
    {
        printf("File has something wrong, please check!\n");
        return -1;
    }
    else
    {
        //Search for the right infomation
        printf("[*] Searching ...\n");
        while ((fscanf(p, "user:%s\npassword:%s\n", temp.name, temp.password)) != EOF)
        {
            if ((strcmp(user.name, temp.name) == 0) && (strcmp(user.password, temp.password) == 0))
            {
                printf("[*] Found user in database.txt\n");
                fclose(p);
                return 1;
            }
        }
    }
    fclose(p);
    return 401;
}

int isdatabaseExist(){
    FILE* p = fopen("database.txt","r");
    if (p == NULL){
        return 0;
    }
    fclose(p);
    return -1;
}

void isUserExit(char *clientSend, int socket){
    if (strcmp(clientSend, "!exit") == 0)
    {
        close(socket);
        printf("Client disconnected\n");
    }
}

int main(void)
{
    int listenfd, connfd;
    struct sockaddr_in serverAddr;
    struct User user;
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    //this function only call one time at all the system, except you delete the database.txt
    //I will automatic run again
    if(isdatabaseExist() == 0){
        initializeDatabase();
    }
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Something wrong in socket()");
        exit(1);
    }
    printf("[*] socket created\n");
    //seting up the socket properties
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1337);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //bind() error handler
    if ((bind(listenfd, (struct sockaddr *)&serverAddr, sizeof serverAddr)) < 0)
    {
        printf("Something wrong in bind()");
        exit(1);
    }
 
    printf("[*] Bind succesful\n");
    printf("[*] Server up and running\n");

    if ((listen(listenfd, BACKLOG)) == 0)
    {
        printf("[*] Server is listening ...\n");
    }

    //connect
    connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

    
    //accept user input pass and username
    read(connfd, user.name, MAX_LINE);
    read(connfd, user.password, MAX_LINE);
    //Find it in the database

    if (searchDatabase(user) == 401)
    {
        memset(&user, 0, sizeof user);
        printf("New Register\n");
        //send 401 to inform user not found in the database waiting for register
        send(connfd, CODE_NOT_FOUND, sizeof CODE_NOT_FOUND, 0);
        read(connfd, user.name, MAX_LINE);
        read(connfd, user.password, MAX_LINE);
        //save it to database
        saveTofile(user);
        printf("A wild %s appeared\n",user.name);
    }
    else
    {
        send(connfd, CODE_FOUND, sizeof CODE_FOUND,0);
        printf("Welcome back %s", user.name);
    } 
    while (1)
    {    
        char serverReponse[MAX_LINE] = {0};
        char clientSend[MAX_LINE] = {0};

        read(connfd, clientSend, MAX_LINE);
        fprintf(stdout, "%s: %s\n", user.name, clientSend);
        //check user want to exit or not
        isUserExit(clientSend, connfd);

        printf("> ");
        fgetstr(serverReponse, sizeof serverReponse, stdin);
        send(connfd, serverReponse, sizeof serverReponse, 0);
        printf("[*] Wait for client to reply\n");
        //if someone connect to the server
    }
    return 0;
}
