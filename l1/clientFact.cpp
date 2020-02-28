#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h> // this file was missing


#define MAXSIZE 100
#include <iostream>
using namespace std;

// RECORD 
// LAB1 -> Any 4 programs 
// LAB2 -> Any 4 programs, leave file thing

int main()
{
    int sockfd, retval;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE];


    // socket function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << ("\nSocket Creation Error");
    }
    // printf("%i", sockfd); // printing the return value of the socket
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect function
    retval = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        cout << ("Connection error") << endl;
        return 1;
    }
    cout << "Enter number: ";

    cin.getline(buff, MAXSIZE);// scanf("%s", buff);
    
    // send function to send the buffer
    sentbytes = send(sockfd, buff, sizeof(buff), 0);

    if (sentbytes == -1)
    {
        cout << ("!!");
        close(sockfd);
    }

    // recv function to receive the buff
    recedbytes = recv(sockfd, buff, sizeof(buff), 0);

    cout << buff << endl; //puts(buff);//printf("\n");
    close(sockfd);
}
