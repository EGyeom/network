#include <network.h>

int main(int argc, char* argv[])
{
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartup() error!");
#endif
    SOCKET serv;
    SOCKET clnt;
    int serv_addr_len = 0;
    int clnt_addr_len = 0;
    SOCKADDR serv_addr;
    SOCKADDR clnt_addr;
    char buf[256] = {0,};
    serv = socket(PF_INET,SOCK_STREAM,0);

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr_len = sizeof(serv_addr);
        
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
