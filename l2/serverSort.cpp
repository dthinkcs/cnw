#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#define MAXSIZE 100

void sel_sort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        int tmp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = tmp;
    }
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout << "Socket Creation Error" << endl;
        return 1;
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET; // IPv4
    serveraddr.sin_port = htons(3388); // port number
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // host to network loop back address
    // 2. bind the socket to our IP and port
    int bind_status = bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
    if (bind_status == -1) {
        cout << "Binding Error" << endl;
        close(sockfd);
        return 1;
    }

    // 3. listen
    int listen_status = listen(sockfd, 1);
    if (listen_status == -1) {
        close(sockfd);
        return 1;
    } 

    // /fill the data up with where the connection is coming from
    struct sockaddr_in clientaddr;
    socklen_t actuallen = sizeof(clientaddr);
    int client_sockfd = accept(sockfd, (struct sockaddr *) &clientaddr, &actuallen);
    if (client_sockfd == -1) {
        cout << "Could not Accept connection" << endl;
        close(sockfd);
        return 1;
    }

    char buff_fc[MAXSIZE]; // from client
    int receive_status = recv(client_sockfd, buff_fc, sizeof(buff_fc), 0);
    if (receive_status == -1) {
        cout << "Could Not Receive" << endl;
        close(sockfd);
        close(client_sockfd);
        return 1;
    }

    string str(buff_fc);
    vector<int> arr;
    stringstream ss(str);
    int temp; // replace(str.begin(), str.end(), ':', ' ');  // replace ':' by ' '
    while (ss >> temp)
        arr.push_back(temp);
    sel_sort(arr); // WRITE OWN SORT FN sort(arr.begin(), arr.end())

    string ans = "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        ans = ans + to_string(arr[i]) + " ";
    } 
    cout << ans << endl;
    strcpy(buff_fc, ans.c_str()); //mutating the buff_fc

    int send_status = send(client_sockfd, buff_fc, sizeof(buff_fc), 0);
    if (send_status == -1) {
        cout << "Could Not Send" << endl;
        close(sockfd);
        close(client_sockfd);
    }
    close(sockfd);
    close(client_sockfd);

}