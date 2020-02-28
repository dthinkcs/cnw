#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<bits/stdc++.h>
#define MAXSIZE 90

using namespace std;


void wordSearch(char* buff){
    int count = 0;
    char word[20], find_word[20];
    cout<<"Enter the word to be searched"<<endl;
    cin>>word;
    
    fstream file;  

    // opening file 
    file.open(buff); 
  
    // extracting words from the file 
    while (file >> find_word) 
    {   if(strcmp(word, find_word)==0)
        // displaying content 
        count++; 
    } 
    cout<<word<<" exists "<<count<<" number of times in the "<<buff<<" file"<<endl;
    file.close();

}


void replaceWord(char* buff){

    char word[MAXSIZE], replace[20];
    cout<<"Enter the word to be replaced "<<endl;
    cin>>word;
    cout<< "Enter the replacing word"<<endl;
    cin>>replace;

    FILE *fp1, *fp2;
    char string[MAXSIZE];
    char temp[] = "temp.txt", *ptr1, *ptr2;

    /* open input file in read mode */
    fp1 = fopen(buff, "r");

    /* error handling */
    if (!fp1) {
        printf("Unable to open the input file!!\n");
     
    }

    /* open temporary file in write mode */
    fp2 = fopen(temp, "w");

        /* error handling */
    if (!fp2) {
        printf("Unable to open temporary file!!\n");
       
    }

    /* delete the given word from the file */
    while (!feof(fp1)) {
        strcpy(string, "\0");
        /* read line by line from the input file */
        fgets(string, MAXSIZE, fp1);

                /*
                * check whether the word to delete is
                 * present in the current scanned line
                 */
        if (strstr(string, word)) {
            ptr2 = string;
            while (ptr1 = strstr(ptr2, word)) {
                    /*
                    * letters present before
                    * before the word to be replaced
                    */
            while (ptr2 != ptr1) {
                fputc(*ptr2, fp2);
                ptr2++;
            }
            /* skip the word to be replaced */
            ptr1 = ptr1 + strlen(word);
            fprintf(fp2, "%s", replace);
            ptr2 = ptr1;
            
            }

            /* characters present after the word to be replaced */
            while (*ptr2 != '\0') {
                fputc(*ptr2, fp2);
                ptr2++;
                }
        }
        else {
            /*
            * current scanned line doesn't 
            * have the word that need to be replaced
            */
           fputs(string, fp2);
            }
        }

        /* close the opened files */
        fclose(fp1);
        fclose(fp2);

        /* remove the input file */
        remove(buff);
        /* rename temporary file name to input file name */
        rename(temp, buff);

}

void rearrange(char* buff){
    fstream file;
    vector<string> content;
   
    file.open(buff);
    if(file.is_open())
        cout<<"Opening File"<<endl;
    else
        cout<<"File cannot be opnened"<<endl;
  
    string word;
    
    while(file>>word)
        content.push_back(word);
    sort(content.begin(),content.end());

    ofstream outputFile("rearranged.txt");
    for(int i = 0 ; i<content.size();i++){
        outputFile << content[i]<<" ";
    }
    file.close();
}


int main()
{

int sockfd,newsockfd,retval;
socklen_t actuallen;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr,clientaddr;
bool filepresent = false;
int option;

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
FILE *file;
    if((file = fopen(buff,"r"))!=NULL)
        {
            filepresent = true;
        }
    else
        {
            
            //File not found, no memory leak since 'file' == NULL
            //fclose(file) would cause an error
        }

sentbytes=sendto(sockfd,&filepresent,sizeof(filepresent),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr)); 

//receiving option
recedbytes=recv(newsockfd,&option,sizeof(option),0);
    
    switch(option){

        case 1: wordSearch(buff);
                break;
        case 2: replaceWord(buff);
                break;
        case 3: rearrange(buff);
                break;
        case 4: cout<<"Exit"<<endl;
                //exit(10);
                break;
        default: break;
    }



if(sentbytes==-1)
{
cout<<"Sending Error"<<endl;
close(sockfd);
}

close(sockfd);
close(newsockfd);

}
