
using namespace std;


#include <string>
#include <thread>
#include "../include/connectionHandler.h"
#include "../include/ReadFromServerTask.h"
#include "../include/SendToServerTask.h"


int main(int argc, char *argv[]) {
    if (argc < 3)
        return -1;

    string host = argv[1];
    short port = stoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect())
        return -1;

    bool isLoggedIn = true;
    bool gotError = false;

    ReadFromServerTask readFromServerTask(connectionHandler , isLoggedIn, gotError);
    SendToServerTask sendToServerTask(connectionHandler, isLoggedIn, gotError);

    thread th1(ref(readFromServerTask));
    thread th2(ref(sendToServerTask));

    th1.join();
    th2.join();
    return 0;

}
