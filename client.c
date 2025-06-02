#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){

    int sockdes;
    char msg[2000],reply[2000];
    struct sockaddr_in client;
    sockdes = socket(AF_INET, SOCK_STREAM,0);
    
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(8888);

    connect(sockdes,(struct sockaddr *)&client,sizeof(client));
    printf("\n Connection established.\n");
    while(1){
        printf("\nTo Server: \n");
        scanf("%s",msg);
        send(sockdes,msg,2000,0);
        recv(sockdes,reply,2000,0);
        printf("\n From Server: \n");
        puts(reply);

    }
    
}