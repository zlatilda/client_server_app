#include <iostream>
#include "client_socket.h"
using namespace std;

int main()
{
    client_socket obj;
    obj.connect_to_server();
    //obj.send_file("file.txt");
    obj.send_text("Hello, it's client!");

    return 0;
}
