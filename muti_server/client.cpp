#include<iostream>
#include<cstring>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
using namespace std;
int main(){
    int cfd=socket(AF_INET,SOCK_STREAM,0);
    if(cfd<0){
        cout<<"error"<<endl;
        };
    struct sockaddr_in serv;
    serv.sin_port=htons(8888);
    serv.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
    connect(cfd,(struct sockaddr*)&serv,sizeof(serv));
    char buff[1024];
    while(1){
/*        recv(cfd,buff,sizeof(buff),0);
        memset(buff,0x00,sizeof(buff));
        cout<<"server:\t"<<buff<<endl;
        memset(buff,0x00,sizeof(buff));
        cin>>buff;
        send(cfd,buff,sizeof(buff),0);
*/
   memset(buff,0x00,sizeof(buff));
//   recv(STDIN_FILENO,buff,sizeof(buff),0);
   //发送数据
    cin>>buff;
   send(cfd,buff,sizeof(buff),0);
   //读服务端发来的数据
   memset(buff,0x00,sizeof(buff)); 
   recv(cfd,buff,sizeof(buff),0);
   cout<<"server:\t"<<buff<<endl;
   };
    close(cfd);

}



