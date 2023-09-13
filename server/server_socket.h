#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <Windows.h>
    typedef int socklen_t;
    #define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

#elif __linux__
    #include <arpa/inet.h>
#endif

#define SIZE 1024

class server_socket
{
private:
    const char *ip;
    int port;
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_size;  // client

public:
    server_socket();
    server_socket(int);
    int binding();
    int listening(int);
    int send_text(const char* message);
    void send_file();
    int receive_text();
    void receive_file();
    ~server_socket();
};

#endif
