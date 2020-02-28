#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

int main()
{
    int sockfd,newsockfd,retval;
    socklen_t actuallen;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr,clientaddr;

    char buff[MAXSIZE];
    int a=0;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    if(sockfd==-1)
    {
        printf("\nSocket creation error");
    }
    clientaddr.sin_family=AF_INET;
    clientaddr.sin_port=htons(3389);
    clientaddr.sin_addr.s_addr=htons(INADDR_ANY);


    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);

    retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==1)
    {
        printf("Binding error");
        close(sockfd);
    }

    actuallen=sizeof(clientaddr);
    recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,&actuallen);

    if(recedbytes==-1)
    {
        printf("Reciving error\n");
        close(sockfd);
    }
    puts(buff);
    printf("\n");
    scanf("%s",buff);
    sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));

    if(sentbytes==-1)
    {
        printf("sending error");
        close(sockfd);
    }

    close(sockfd);
    close(newsockfd);
}

