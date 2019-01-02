//
// Created by yarin on 1/2/19.
//

#include "../include/ReadFromServerTask.h"
using namespace std;

ReadFromServerTask::ReadFromServerTask(ConnectionHandler &connectionHandler1 ,bool &isLoggedIn1):connectionHandler(connectionHandler1), isLoggedIn(isLoggedIn1) {}

void ReadFromServerTask::run() {

    string answer="";
    while(isLoggedIn)
    {
        char opCodefromServer[2];
        connectionHandler.getBytes(opCodefromServer , 2);
        short CodefromServer = bytesToShort(opCodefromServer);
        if(CodefromServer == 9 )
        {
            NotificationMessage();
        }
        if(CodefromServer == 10)
        {
            ACKMessage();
        }
        if(CodefromServer == 11)
        {
            ErrorMessage();
        }
    }

}

short ReadFromServerTask::bytesToShort(char *bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}

void ReadFromServerTask::ErrorMessage() {

    char opCode[2];
    connectionHandler.getBytes(opCode, 2);
    short Code = bytesToShort(opCode);
    cout << "ERROR " << Code << endl;
}


void ReadFromServerTask::NotificationMessage() {
    char NotificationType[1];
    connectionHandler.getBytes(NotificationType , 1);

    string userName;
    connectionHandler.getLine(userName);
    string content;
    connectionHandler.getLine(content);

    cout<< "NOTIFICATION " << NotificationType[0]<< " " << userName + " " << content <<endl;
}

void ReadFromServerTask::ACKMessage() {
    char opCode[2];
    connectionHandler.getBytes(opCode , 2);
    short MessageCode = bytesToShort(opCode);

    if(MessageCode == 1 | MessageCode == 2 | MessageCode == 3 | MessageCode == 5 | MessageCode == 6)
    {
        cout << "ACK " << MessageCode <<endl;
        if(MessageCode == 3)
            isLoggedIn = false;
    } else{
        if(MessageCode == 4 | MessageCode == 7)
        {
            char num[2];
            connectionHandler.getBytes(num , 2);
            short numOfUsers = bytesToShort(num);
            vector<string> userNames;
            for(int i = 0 ; i < numOfUsers ; i ++)
            {
                string userName;
                connectionHandler.getLine(userName);
                userNames.push_back(userName);
            }
            cout<<"ACK " << MessageCode << " " << numOfUsers << " ";
            for(int i = 0 ; i < userNames.size()-1 ; i++)
                cout <<userNames[i] << " ";
            cout<<userNames[userNames.size()-1] << endl;
        }
        if(MessageCode == 8)
        {
            char num1[2];
            connectionHandler.getBytes(num1 , 2);
            short numOfPosts = bytesToShort(num1);

            char num2[2];
            connectionHandler.getBytes(num2, 2);
            short numOfFollowers = bytesToShort(num2);

            char num3[2];
            connectionHandler.getBytes(num3 , 2);
            short numOfFollowing = bytesToShort(num3);
            cout<< "ACK " << "8 " << numOfPosts << " " << numOfFollowers << " " << numOfFollowing << endl;
        }
    }

}
