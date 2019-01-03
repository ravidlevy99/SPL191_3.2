//
// Created by yarin on 1/2/19.
//

#ifndef CLIENT_READFROMSERVERTASK_H
#define CLIENT_READFROMSERVERTASK_H


#include "connectionHandler.h"

class ReadFromServerTask {
private:
    ConnectionHandler& connectionHandler;
    bool &isLoggedIn;
    bool &gotError;
    short bytesToShort(char* bytesArr);
    void ErrorMessage();
    void NotificationMessage();
    void ACKMessage();
public:
    ReadFromServerTask(ConnectionHandler &connectionHandler1 , bool &isLoggedIn1, bool &gotError);

    void operator()();

};


#endif //CLIENT_READFROMSERVERTASK_H
