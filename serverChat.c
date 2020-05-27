#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "utilities.h"

#define MAX 1024
//I want to write the data of the user to a file
//which is our database
//cool ehhehehe
struct User
{
    char name[MAX];
    char password[MAX];
};

void saveTofile(struct User user)
{
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

void showDatbase(FILE *database){

}

//This would return 401 for "Can't find user" and 1 for

int searchDatabase(struct User user)
{
    FILE *p = fopen("database.txt", "wr");
    struct User temp;
    if (p == NULL)
    {
        printf("File has something wrong, please check!\n");
        return -1;
    }
    else
    {
        //Search for the right infomation
        //What the fuck should I use now
        while (1)
        {
            //I doubt would this work
            //why here return ??
            fscanf(p, "user:%s\npassword:%s\n", temp.name, temp.password);
            //found it
            printf("%s and %s\n",user.name,temp.name);
            if ((strcmp(user.name, temp.name) == 0) && (strcmp(user.password, temp.password) == 0))
            {
                break; //kinda stupid, but second thought this is clever because you don't need to loop to end of the file
            }
            else
            {
                return 401;
            }
        }
    }
    fclose(p);
    return 1;
}

// void authenticate(){

// }

int main(void)
{
    int listenfd, connfd, val;
    struct sockaddr_in serverAddr;

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
    //if what's wrong with bind
    if ((bind(listenfd, (struct sockaddr *)&serverAddr, sizeof serverAddr)) < 0)
    {
        printf("Something wrong in bind()");
        exit(1);
    }
    //To be honest I want to make it has a little bit of delay for the effect that
    //something is happening but =)) the delay function I code is getting bypass everytime

    printf("[*] Bind succesful\n");
    //after bind we will listen for connection, the 2 argument is backlog
    //
    printf("[*] Server up and running\n");
    if ((listen(listenfd, 10)) == 0)
    {
        printf("[*] Server is listening ...\n");
    }

    //this is where magic happen
    connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

    struct User user;
    //accept user input pass and username
    read(connfd, user.name, MAX);
    read(connfd, user.password, MAX);
    //Find it in the database
    if (searchDatabase(user) == 401)
    {
        memset(&user, 0, sizeof user);
        printf("New Register\n");
        send(connfd, "401", sizeof "401", 0);
        read(connfd, user.name, MAX);
        read(connfd, user.password, MAX);
        //save it to database
        saveTofile(user);
    }
    else
    {
        printf("WTF\n");
    }
    printf("A wild %s appeared\n",user.name);   
    while (1)
    {    
        char serverReponse[MAX] = {0};
        char clientSend[MAX] = {0};
        //After accept I'll fork it
        read(connfd, clientSend, MAX);
        //recv(connfd,clientSend,strlen(clientSend),0);
        fprintf(stdout, "%s: %s\n", user.name, clientSend);

        if (strcmp(clientSend, "!exit") == 0)
        {
            close(connfd);
            printf("Client disconnected\n");
        }
        printf("> "); //this look ridiculous
        fgetstr(serverReponse, sizeof serverReponse, stdin);
        send(connfd, serverReponse, sizeof serverReponse, 0);
        printf("[*] Wait for client to reply\n");
        //if someone connect to the server
    }
    return 0;
}
