#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

using namespace std;
struct sb
{
    string regno;
    string name;
    string course;
    string dob;
};
int main()
{
    struct sb msg={"24","Kobe Bryant","NBA","23-08-1978"};
    vector<sb> data;
    data.push_back(msg);
    int sockfd,newsockfd,retval;
    socklen_t actuallen;
    int recedbytes,sentbytes;
    struct sockaddr_in serveraddr,clientaddr;
    char buff[100];
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

    
    
    
    
    
    while(1)
    {
       recedbytes=recv(newsockfd,buff,sizeof(buff),0);
       string s1=buff;
       char choice=s1[0];
       switch(choice)
       {
           case '1':
           {
               vector<string> details;
               string s2=s1.substr(2);
               stringstream ss(s2);
               string word;
               while(ss>>word)
                   details.push_back(word);
                struct sb temp;
                temp.regno=details[0];
                temp.name=details[1];
                temp.course=details[2];
                temp.dob=details[3];
                data.push_back(temp);

               strcpy(buff,"Details Inserted\0");
               sentbytes=send(newsockfd,buff,sizeof(buff),0);
               break;
           }
           case '2':
           {
               int pos=-1;
               int check=0;
               string s2=s1.substr(2);
               for(int i=0;i<data.size();i++)
               {
                   if(data[i].regno==s2) { // was BUG
                    check=1;
                    pos=i;
                   }
               }
               if(check==1)
               {
                   string s3="";
                   s3+=data[pos].regno+"\t";
                   s3+=data[pos].name+"\t";
                   s3+=data[pos].course+"\t";
                   s3+=data[pos].dob;
                   s3+="\0";
                   strcpy(buff,s3.c_str());
                   puts(buff);
               }
               else
                strcpy(buff,"Details Not Found\0");
               sentbytes=send(newsockfd,buff,sizeof(buff),0);
               break;
           }
           case '3':
           {
               int check=0;
               string s2=s1.substr(2);
               for(int i=0;i<data.size();i++)
               {
                   if(data[i].regno==s2)
                   {
                       check=1;
                       data.erase(data.begin()+i);
                       break;
                   }
               }
               if(check==1)
                strcpy(buff,"Details Deleted\0");
               else
                strcpy(buff,"Details Not Found\0");
                sentbytes=send(newsockfd,buff,sizeof(buff),0);
                break;
           }
           case '4':
           {
               string s3="";
               for(int i=0;i<data.size();i++)
               {
                   s3+=data[i].regno+"\t";
                   s3+=data[i].name+"\t";
                   s3+=data[i].course+"\t";
                   s3+=data[i].dob+"\n";
               }
               s3+="\0";
               strcpy(buff,s3.c_str());
               sentbytes=send(newsockfd,buff,sizeof(buff),0);
               break;
           }
           case '5':
           {
               exit(0);
           }
       }
    }
    close(newsockfd);
    close(sockfd);
}
