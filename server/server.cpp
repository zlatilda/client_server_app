#include <iostream>
#include "server_socket.h"
using namespace std;

int main()
{
    server_socket obj;
    obj.binding();
    obj.listening(10);
    //obj.receive_file("file.txt");
    obj.receive_text();
    return 0;
}
