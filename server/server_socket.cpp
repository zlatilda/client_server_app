#include "server_socket.h"

server_socket::server_socket()
{
    #ifdef _WIN32
        WSADATA Data;
        WSAStartup(MAKEWORD(2, 2), &Data);
    #endif

    this->ip = "127.0.0.1";
    this->port = 7500;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    printf("[+]Server socket created successfully.\n");
}

server_socket::server_socket(int port)
{
    #ifdef _WIN32
        WSADATA Data;
        WSAStartup(MAKEWORD(2, 2), &Data);
    #endif

    this->ip = "127.0.0.1";
    this->port = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

server_socket::~server_socket()
{
    close(sockfd);

    #ifdef _WIN32
        WSACleanup();
    #endif
}

int server_socket::binding()
{
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = port;
    this->server_addr.sin_addr.s_addr = inet_addr(ip);

    int is_binded = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(is_binded < 0)
    {
        perror("[-]Error in binding");
        exit(1);
    }
    printf("[+]Binding successfully.\n");

    return is_binded;
}

int server_socket::listening(int backlog_queue_size)
{
    int is_listening = listen(sockfd, backlog_queue_size);
    if( is_listening == 0)
    {
         printf("[+]Listening....\n");
    }
    else
    {
        perror("[-]Error in listening");
        exit(1);
    }

    return is_listening;
}

void server_socket::send_text(const char* message)
{
    struct sockaddr_in new_addr;
    addr_size = sizeof(new_addr);

    int new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    if (new_sock< 0)
    {
        perror("[-]Error accepting connection");
        exit(1);
    }

    int is_sent = send(new_sock, message, SIZE , NULL);
    if (is_sent < 0)
    {
        perror("[-]Error writing to socket");
        exit(1);
    }

    printf("SERVER: ", message);
}

void server_socket::receive_text()
{
    struct sockaddr_in new_addr;
    addr_size = sizeof(new_addr);

    int new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

    if (new_sock< 0)
    {
        perror("[-]Error accepting connection");
        exit(1);
    }

    char buffer[SIZE];
    memset(buffer, 0, SIZE);
    int is_received = recv(new_sock, buffer, SIZE, NULL);
    if(is_received == 0)
    {
        perror("[-]Error in receiving a message");
        exit(1);
    }
    printf("RECIEVED MESSAGE: %s\n", buffer);
}

void server_socket::receive_file(const char* filename)
{
    struct sockaddr_in new_addr;
    addr_size = sizeof(new_addr);
    int new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

    write_file(new_sock, filename);

    printf("[+]Data written in the file successfully.\n");

    close(new_sock);
}

void server_socket::send_file(const char* filename)
{
    FILE* fp;
    fp = fopen(filename, "r");
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

void server_socket::write_file(int sockfd, const char* filename){
    int n;
    FILE* fp;
    //const char* filename = "file.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
          break;
        }

        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
}
