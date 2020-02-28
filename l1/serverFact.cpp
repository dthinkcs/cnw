#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAXSIZE 100
#include <iostream>
using namespace std;

long long factorial(int n) {
    long long ans = 1;
    for (int i = 1; i <= n; i++)
        ans *= i;
    return ans;
}

int main()
{
    int sockfd, newsockfd, retval;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;

    char buff[MAXSIZE];
    int a = 0;
    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
    // bind
    retval = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        printf("Binding error");
        close(sockfd);
    }
    // listen
    retval = listen(sockfd, 1);
    if (retval == -1)
    {
        close(sockfd);
    }

    actuallen = sizeof(clientaddr);
    // accept
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &actuallen);

    if (newsockfd == -1)
    {
        close(sockfd);
    }
    // recv
    recedbytes = recv(newsockfd, buff, sizeof(buff), 0);

    if (recedbytes == -1)
    {
        close(sockfd);
        close(newsockfd);
    }

        // BUSINESS LOGIC
    int n;
    sscanf(buff, "%d", &n);
    long long fact = factorial(n);
    sscanf(fact, "%s", buff);
    //cout << "Answer: " <<  << endl;


    sentbytes = send(newsockfd, buff, sizeof(buff), 0);

    if (sentbytes == -1)
    {
        close(sockfd);
        close(newsockfd);
    }





    close(sockfd);
    close(newsockfd);
}
