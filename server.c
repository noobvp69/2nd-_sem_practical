#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){

    int sockdes,newsock,c;
    char msg[2000],reply[2000];
    struct sockaddr_in server, client;
    sockdes = socket(AF_INET,SOCK_STREAM,0);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(sockdes,(struct sockaddr *)&server,sizeof(server));
    printf("Bind accepted.");
    printf("\n Waiting for incoming connections....");
    listen(sockdes,3);

   

    c = sizeof(struct sockaddr);

    newsock = accept(sockdes,(struct sockaddr *)&client,(socklen_t*)&c);
    if(newsock<0){printf("Connection failed.");}
    printf("\nConnection accepted.");
    while(1){
        recv(newsock,reply,2000,0);
        printf("\n From Client: \n");
        puts(reply);
        printf("\n To Client: \n");
        scanf("%s",msg);
        send(newsock,msg,2000,0);
    }
}