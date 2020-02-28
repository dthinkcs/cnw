#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>

//#include<bits/stdc++.h>
#include<string>

#define MAXSIZE 90

using namespace std;


bool palindrome(string word) {
    int length = word.length();
    string word_reverse;
    word_reverse  = word;

    for(int i = 0 ; i< length/2 ; i++){
        swap(word_reverse[i],word_reverse[length-i-1]);
    }

    if(word==word_reverse){
        return true;
    }
    else{
        return false;
    }
}
int main()
{

int sockfd,newsockfd,retval;
socklen_t actuallen;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr,clientaddr;

char buff[MAXSIZE];
int a=0;

//socket
sockfd=socket(AF_INET,SOCK_DGRAM,0);

if(sockfd==-1)
{cout<<"Socket Creation Error"<<endl;
}

clientaddr.sin_family=AF_INET;
clientaddr.sin_port=htons(3389);
clientaddr.sin_addr.s_addr=htons(INADDR_ANY);


serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=htons(INADDR_ANY);

//bind
retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

if(retval==1)
{
cout<<"Binding Error"<<endl;
close(sockfd);
}

actuallen=sizeof(clientaddr);

//receive
recedbytes=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&clientaddr,&actuallen);

if(recedbytes==-1)
{
cout<<"Receiving Error"<<endl;
close(sockfd);
}

if(palindrome(buff)){
    string ans  = "Palindrome";
    char ss[ans.length()+1];
    strcpy(ss, ans.c_str());
    sentbytes=sendto(sockfd,ss,sizeof(ss),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr)); 
}
else{
    string ans  = "Not a Palindrome";
    char ss[ans.length()+1];
    strcpy(ss, ans.c_str());
    sentbytes=sendto(sockfd,ss,sizeof(ss),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr)); 
}



if(sentbytes==-1)
{
cout<<"Sending Error"<<endl;
close(sockfd);
}

close(sockfd);
close(newsockfd);

}
