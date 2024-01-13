#include<iostream>
#include<cstdlib>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<cstring>
using namespace std;

int main(){
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    if(lfd<0){
        cout<<"ERROR"<<endl;
        return -1;
    };
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8888);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    int is_suc=bind(lfd,(struct sockaddr *)&addr,sizeof(addr));
    if(is_suc<0){
    cout<<"error_bind"<<endl;
    return -1;
    }
    is_suc=listen(lfd,128);
    struct sockaddr_in endpoint;
    socklen_t point_len=sizeof(endpoint);
    char sip[16];
    while(true){
        int sock=accept(lfd,(struct sockaddr*) &endpoint,&point_len);
        inet_ntop(AF_INET,&endpoint.sin_addr.s_addr,sip,sizeof(sip));
        cout<<"cfd:"<<sock<<"   "<<"lfd:"<<lfd<<endl<<"client:"<<sip<<":"<<ntohs(endpoint.sin_port)<<endl;
        char buff[1024];
        int pid=fork();
        if(pid >0){
            close(sock);
        }else if(pid <0){
            cout<<"error is client close"<<endl;
            exit(-1);
        }else if(pid==0){ 
            close(lfd);
            while(true){                                                   
                memset(buff,0x00,sizeof(buff));
                int s=recv(sock,buff,sizeof(buff),0);
                if(s>0){ 
                    cout<<"client["<<ntohs(endpoint.sin_port)<<"]:"<<buff<<endl;
                };
                s=send(sock,buff,sizeof(buff),0);
            }
            close(sock);
            exit(0);
        }
    }
    close(lfd);
}






