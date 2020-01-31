#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

using namespace std;
int main()
{
    int sockfd,newsockfd,retval;
    socklen_t actuallen;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr,clientaddr;
    char buff[50];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
        exit(0);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(3388);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1)
        exit(0);
    retval=listen(sockfd,1);
    if(retval==-1)
        exit(0);
    actuallen=sizeof(clientaddr);
    newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);
    if(newsockfd==-1)
        exit(0);

    recedbytes=recv(newsockfd,buff,sizeof(buff),0);
    ifstream file;
    vector<string>content;
    string name=buff;
    file.open(name);
    if(file.is_open())
        strcpy(buff,"File Found\0");
    else
        strcpy(buff,"File Not Found\0");
    sentbytes=send(newsockfd,buff,sizeof(buff),0);
    while(1)
    {
        int check=0;
        recedbytes=recv(newsockfd,buff,sizeof(buff),0);
        puts(buff);
        string s1=buff;
        string word;
        char choice=s1[0];
        switch(choice)
        {
            case '1':
            {
                int flag=0;
                string s2=s1.substr(2);
                while(file>>word)
                {
                    if(word==s2)
                    {
                        strcpy(buff,"Word Found\0");
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    strcpy(buff,"Word Not Found\0");
                    file.clear();
                }
                file.seekg(0,ios::beg);
                break;
            }
            case '2':
            {
                string s2=s1.substr(2);
                stringstream ss(s2);
                string msg;
                vector<string> vect;
                while(ss>>msg)
                    vect.push_back(msg);
                while(file>>word)
                {
                    if(word==vect[0])
                    {
                        strcpy(buff,"Content Changed\0");
                        content.push_back(vect[1]);
                        check=1;
                    }
                    else
                        content.push_back(word);
                }
                break;
            }
            case '3':
            {
                while(file>>word)
                    content.push_back(word);
                sort(content.begin(),content.end());
                check=1;
                break;
            }
            case '4':
            {
                file.close();
                exit(0);
                break;
            }

        }
        if(check==1)
        {
            file.close();
            fstream fs;
            fs.open(name,ofstream::out|ofstream::trunc);
            for(int i=0;i<content.size();i++)
                fs<<(content[i]+"\n");
            fs.close();
            file.open(name);
            content.clear();
        }
        sentbytes=send(newsockfd,buff,sizeof(buff),0);
    }
    close(newsockfd);
    close(sockfd);
}
