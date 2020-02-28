#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<bits/stdc++.h>
#include<arpa/inet.h>
#define MAXSIZE 90

using namespace std;
int main()
{
int sockfd,retval;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr, clientaddr;
bool filepresent = false;
int option;
char buff[MAXSIZE];
//socket
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd==-1)
{
cout<<"Socket Creation Error"<<endl;
exit(0);
}

//server configuration
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

//client configuration
clientaddr.sin_family=AF_INET;
clientaddr.sin_port=htons(3389);
clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

//bind
retval=bind(sockfd,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
if(retval==1)
{
cout<<"Binding Error"<<endl;
close(sockfd);
}

cout<<"Enter File"<<endl;
cin>>buff;

//send
sentbytes=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

if(sentbytes==-1)
{
cout<<"Sending Error"<<endl;
close(sockfd);
}

socklen_t size=sizeof(serveraddr);

//receive
recedbytes=recvfrom(sockfd,&filepresent,sizeof(filepresent),0,(struct sockaddr*)&serveraddr,&size);
 
if(filepresent){
    cout<<"Choose the following"<<endl<<"1. Search a particular word\n2. Replace a particular word\n3. Reordering the file contents\n4. Exit"<<endl;
    cin>>option;
    sentbytes=sendto(sockfd,&option,sizeof(option),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr)); 
}
else{
    cout<<"File is not Presesnt"<<endl;
}


close(sockfd);

}