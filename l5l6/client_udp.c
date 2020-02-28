#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

int main()
{
    int sockfd, retval;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE];
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1)
    {
        printf("\nSocket Creation Error");
        exit(0);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port=htons(3389);
    clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    retval=bind(sockfd,(struct sockaddr*)&clientadd,sizeof(clientaddr));
    if(retval==1)
    {
        printf("Binding error");
        close(sockfd);
    }

    printf("enter the text\n");

    scanf("%s",&buff);


    sentbytes=sendto(sockfd,buff,sizeof(buff),0,
    struct sockaddr*)&serveraddr,sizeof(serveraddr));

    if(sentbytes==-1)
    {
        printf("sending error");
        close(sockfd);
    }
    int size = sizeof(serveraddr);

    recedbytes = recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&serveraddr,&size);

    puts(buff);
    printf("\n");
    close(sockfd);
}
