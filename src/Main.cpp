//
// Created by yarin on 1/2/19.
//
using namespace std;


#include <string>
#include <thread>
#include "../include/connectionHandler.h"
#include "../include/ReadFromServerTask.h"
#include "../include/SendToServerTask.h"


int main(int argc, char *argv[]) {
    if (argc < 2)
        return -1;

    string host = argv[0];
    short port = stoi(argv[1]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect())
        return -1;

    bool isLoggedIn = true;

    ReadFromServerTask readFromServerTask(connectionHandler , isLoggedIn);
    SendToServerTask sendToServerTask(connectionHandler, isLoggedIn);

    thread th1(ref(readFromServerTask));
    thread th2(ref(sendToServerTask));

    th1.join();
    th2.join();
    return 0;

}
