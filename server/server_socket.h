#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment (lib, "ws2_32.lib")
#ifdef _WIN32
    #include <winsock2.h>
    #include <Windows.h>
    typedef int socklen_t;
    #define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

#elif __linux__
    #include <arpa/inet.h>
#endif

#define SIZE 1024

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

class server_socket
{
private:
    const char *ip;
    int port;
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_size;  // client

    void write_file(int);
public:
    server_socket();
    server_socket(int);
    int binding();
    int listening(int);
    void send_text(const char* message);
    void send_file();
    void receive_text();
    void receive_file();
    ~server_socket();
};

#endif
