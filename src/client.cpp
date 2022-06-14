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
    int sock = 0;
    sockaddr_in sock_addr;
    uint32_t sock_addr_len =0;
    char buf[256] = {0,};

    sock = socket(PF_INET,SOCK_STREAM,0);
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(argv[2]));

    sock_addr_len = sizeof(sock_addr);
    if(connect(sock,(sockaddr*)&sock_addr,sock_addr_len) == -1)
    {
        printf("connect error\n");
    }
    int slength = read(sock,buf,sizeof(buf));
    buf[slength] = 0;
    printf("received : %s\n", buf);
    while(1)
    {
        memset(buf,0,sizeof(buf));
        scanf("%s", buf);
        slength = strlen(buf);
        write(sock,buf,slength);

        slength = read(sock,buf,sizeof(buf));
        buf[slength] = 0;
        printf("received : %s\n", buf);
    }
    close(sock);
    return 0;
}