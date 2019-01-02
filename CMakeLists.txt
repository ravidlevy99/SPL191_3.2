cmake_minimum_required(VERSION 3.12)
project(Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client src/connectionHandler.cpp src/echoClient.cpp src/Main.cpp src/ReadFromServerTask.cpp include/ReadFromServerTask.h src/SendToServerTask.cpp include/SendToServerTask.h)