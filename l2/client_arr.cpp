#include <stdio.h> // printf scanf 
#include <stdlib.h> // memory management
#include <string.h> // string functions
#include <unistd.h> // system calls fork exec close 

// sockets
#include <sys/socket.h> // socket defin recv, send
#include <sys/stat.h> // s.xxx file mode
#include <sys/types.h> // system types

// addresses
#include <netinet/in.h> // socket addressesing
#include <fcntl.h> // non blocking
#include <arpa/inet.h> // inet_addr, etc

#include <iostream>
#include <string>
using namespace std;

#define MAXSIZE 100

int main(void) {

    // create a socket descriptor 1.socket
    // int socket(int family, int type, int protocol)
    // socket(IPv4, tcp, no raw sockets since using tcp therefore no more informaiton needed 0 means default)
    // socket -> endpoint
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout << "Socket creation error" << endl;
        return 1;
    }

    // specify address for the socket
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET; // ipv4
    serveraddr.sin_port = htons(3388); // 3388 port NNBBBBB->number not string
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //  sin_addr is a struct with s_addr attribute/field 

    // socket handler, typecast the address of sockaddr_in -> sockaddr
    int connection_status = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (connection_status == -1) {
        cout << "Connection error" << endl;
        close(sockfd);
        return 1;
    }

    // BUSINESS LOGIC
    char buff[MAXSIZE];
    cout << "Enter arr of numbers:" << endl;
    cin.getline(buff, MAXSIZE); 


    // 3. send
    int send_status = send(sockfd, buff, sizeof(buff), 0);
    if (send_status == -1) {
        cout << "Could not send buffer" << endl;
        close(sockfd);
        return 1;
    }
    // SAME buff space <- receive stuff
    recv(sockfd, buff, sizeof(buff), 0);
    cout << buff << endl; 
    close(sockfd);

}

