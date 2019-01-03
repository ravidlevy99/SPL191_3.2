//
// Created by yarin on 1/2/19.
//
using namespace std;

#include "../include/SendToServerTask.h"
#include "algorithm"
using namespace std;

SendToServerTask::SendToServerTask(ConnectionHandler &connectionHandler1, bool &isLoggedIn1, bool &gotError1):connectionHandler(connectionHandler1), isLoggedIn(isLoggedIn1), gotError(gotError1) {}

void SendToServerTask::operator()() {

    while(isLoggedIn) {
        string line="";
        getline(cin, line);
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        vector<string> result = split(line, ' ');
        if (result[0] == "REGISTER" || result[0] == "LOGIN") {
            RegisterOrLoginMessage(result);
        } else {
            if (result[0] == "LOGOUT") {
                result.erase(result.begin());
                LogoutMessage();
                while(!gotError)
                {
                    if(!isLoggedIn)
                        break;
                }
                if(!isLoggedIn)
                    break;
                if(gotError)
                    gotError = false;
            } else {
                if (result[0] == "FOLLOW") {
                    result.erase(result.begin());
                    FollowMessage(result);
                } else {
                    if (result[0] == "POST") {
                        result.erase(result.begin());
                        PostMessage(result);
                    } else {
                        if (result[0] == "PM") {
                            result.erase(result.begin());
                            PrivateMessage(result);
                        } else {
                            if (result[0] == "USERLIST") {
                                result.erase(result.begin());
                                UserListMessage();
                            } else{
                                if(result[0] =="STAT"){
                                    result.erase(result.begin());
                                    StatMessage(result[0]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}


vector<string> SendToServerTask::split(const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    if (s == "LOGOUT" || s == "USERLIST") {
        result.push_back(s);
        return result;
    }


    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

void SendToServerTask::RegisterOrLoginMessage(std::vector<std::string> RegisterOrLoginVector){
    string RegisterOrLogin = RegisterOrLoginVector[0];
    RegisterOrLoginVector.erase(RegisterOrLoginVector.begin());

    char opCode[2];
    if(RegisterOrLogin == "REGISTER")
        shortToByte(1 , opCode);
    else
        shortToByte(2, opCode);
    vector<char> toSend;

    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    string username = RegisterOrLoginVector[0];
    vector<char> userNameVector(username.c_str(), username.c_str() + username.size());
    for(auto c : userNameVector)
        toSend.push_back(c);

    toSend.push_back('\0');

    string password = RegisterOrLoginVector[1];
    vector<char> passwordVector(password.c_str() , password.c_str()+password.size());
    for(auto c : passwordVector)
        toSend.push_back(c);

    toSend.push_back('\0');

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());


}



void SendToServerTask::shortToByte(short num, char *bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void SendToServerTask::LogoutMessage() {
    char opCode[2];
    shortToByte(3 , opCode);
    vector<char> toSend;
    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());

}

void SendToServerTask::FollowMessage(std::vector<std::string> FollowVector) {
    char opCode[2];
    shortToByte(4 , opCode);
    vector<char> toSend;
    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    const char *followUnfollow = FollowVector[0].c_str();
    toSend.push_back(followUnfollow[0]);
    FollowVector.erase(FollowVector.begin());

    short num = stoi(FollowVector[0]);
    char numOfUsers[2];
    shortToByte(num , numOfUsers);
    toSend.push_back(numOfUsers[0]);
    toSend.push_back(numOfUsers[1]);
    FollowVector.erase(FollowVector.begin());


    for(string str : FollowVector)
    {
        vector<char> stringToChar(str.c_str() , str.c_str() +str.size());
        for(char c : stringToChar)
            toSend.push_back(c);
        toSend.push_back('\0');
    }

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());

}

void SendToServerTask::PostMessage(std::vector<std::string> PostVector) {
    char opCode[2];
    shortToByte(5 , opCode);
    vector<char> toSend;
    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    string post = "";
    for(auto str : PostVector)
        post += str +" ";
    if(post.size()!=0)
        post = post.substr(0 , post.size() -1);

    vector<char> postToChar(post.c_str() , post.c_str() + post.size());
    for(auto c : postToChar)
        toSend.push_back(c);
    toSend.push_back('\0');

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());
}

void SendToServerTask::PrivateMessage(std::vector<std::string> PrivateVector) {
    char opCode[2];
    shortToByte(6 , opCode);
    vector<char> toSend;
    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    string userName = PrivateVector[0];
    PrivateVector.erase(PrivateVector.begin());
    vector<char> userNameVector(userName.c_str() , userName.c_str() + userName.size());
    for(auto c : userNameVector)
        toSend.push_back(c);

    toSend.push_back('\0');

    string post = "";
    for(auto str : PrivateVector)
        post += str +" ";
    if(post.size()!=0)
        post = post.substr(0 , post.size() -1);

    vector<char> postToChar(post.c_str() , post.c_str() + post.size());
    for(auto c : postToChar)
        toSend.push_back(c);
    toSend.push_back('\0');

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());
}

void SendToServerTask::UserListMessage() {
    char opCode[2];
    shortToByte(7 , opCode);
    vector<char> toSend;
    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());

}

void SendToServerTask::StatMessage(std::string userName) {
    char opCode[2];
    shortToByte(8 , opCode);
    vector<char> toSend;
    toSend.push_back(opCode[0]);
    toSend.push_back(opCode[1]);

    vector<char> userNameVector(userName.c_str() , userName.c_str() + userName.size());

    for(auto c : userNameVector)
        toSend.push_back(c);

    toSend.push_back('\0');

    char charToSend[toSend.size()];
    for(int i = 0 ; i < toSend.size() ; i++)
        charToSend[i] = toSend[i];

    connectionHandler.sendBytes(charToSend , toSend.size());
}




