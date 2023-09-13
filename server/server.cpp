#include <iostream>
#include "server_socket.h"
using namespace std;

int main()
{
    server_socket obj;
    obj.binding();
    obj.listening(10);
    //obj.send_text("hello, it's server");
    //obj.receive_text();
    obj.receive_file();
    return 0;
}
