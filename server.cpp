#include <cstdio>

#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h> // read,write
#include <sys/socket.h> // socket

#include <arpa/inet.h>

#include <stdlib.h> // atoi
#include <string.h> // strlen

#include <sys/wait.h>
#include <signal.h>

int main(int argc, char* argv[])
{
    int serv;
    int clnt;
    uint32_t serv_addr_len = 0;
    uint32_t clnt_addr_len = 0;
    sockaddr_in serv_addr;
    sockaddr_in clnt_addr;
    char buf[256] = {0,};
    serv = socket(PF_INET,SOCK_STREAM,0);

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr_len = sizeof(serv_addr);
    
    printf("%x\n", serv_addr.sin_addr.s_addr);
    int option = 1;
    setsockopt(serv,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
    
    if(bind(serv,(sockaddr*)&serv_addr,serv_addr_len) == -1)
    {
        printf("bind error\n");
        return 0;
    }

    if(listen(serv,5) == -1)
    {
        printf("listen error\n");
        return 0;
    }

    clnt_addr_len = sizeof(clnt_addr);
    if((clnt = accept(serv,(sockaddr*)&clnt_addr, &clnt_addr_len)) == -1)
    {
        printf("accept error\n");
    }
    else printf("accepted client\n");

    write(clnt,"helloworld\n",strlen("helloworld\n"));
    int slength = -1;
    // slength = read(clnt,buf,256);
    while((slength = read(clnt,buf,256)) != 0)
    {
        write(clnt,buf,slength);
        buf[slength] = 0;
        printf("%s\n", buf); 
    }
    return 0;   
}