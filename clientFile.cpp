#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<arpa/inet.h>

using namespace std;
int main()
{
    int sockfd,retval;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr;
    char buff[50];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
        exit(0);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1)
        exit(0);
    
    char s1[]="Enter File Name - ";
    puts(s1);
    string name;
    getline(cin,name);
    strcpy(buff,name.c_str());
    sentbytes=send(sockfd,buff,sizeof(buff),0);
    recedbytes=recv(sockfd,buff,sizeof(buff),0);
    puts(buff);
    while(1)
    {
        cout<<"\n1. Search\n2. Replace\n3. Reorder\n4. Exit\n\0";
        cout<<"\nEnter Choice - \0";
        string choice;
        getline(cin,choice);
        strcpy(buff,choice.c_str());
        sentbytes=send(sockfd,buff,sizeof(buff),0);
        if(choice=="4")
            exit(0);
        recedbytes=recv(sockfd,buff,sizeof(buff),0);
        puts(buff);
    }
    close(sockfd);

}