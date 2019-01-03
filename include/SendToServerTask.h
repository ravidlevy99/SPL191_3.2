//
// Created by yarin on 1/2/19.
//

#ifndef CLIENT_SENDTOSERVERTASK_H
#define CLIENT_SENDTOSERVERTASK_H


#include "connectionHandler.h"

class SendToServerTask {
private:
    ConnectionHandler& connectionHandler;
    bool &isLoggedIn;
    bool &gotError;
    std::vector<std::string> split(const std::string&s , char delim);
    void RegisterOrLoginMessage(std::vector<std::string> RegisterOrLoginVector);
    void shortToByte(short num, char* byteArr);
    void LogoutMessage();
    void FollowMessage(std::vector<std::string> FollowVector);
    void PostMessage(std::vector<std::string> PostVector);
    void PrivateMessage(std::vector<std::string> PrivateVector);
    void UserListMessage();
    void StatMessage(std::string userName);


public:
    SendToServerTask(ConnectionHandler&connectionHandler1 , bool &isLoggedIn1, bool &gotError);
    void operator()();
};


#endif //CLIENT_SENDTOSERVERTASK_H
