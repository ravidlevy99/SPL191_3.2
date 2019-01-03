cmake_minimum_required(VERSION 3.12)
project(Client)

set(CMAKE_CXX_STANDARD 14)
find_package(Boost COMPONENTS system filesystem thread REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

SET(CMAKE_CXX_FLAGS -pthread)
SET(CMAKE_CXX_FLAGS -lboost_thread)
SET(PLATFORM_SPECIFIC_LIBS "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(Client src/connectionHandler.cpp src/Main.cpp src/ReadFromServerTask.cpp include/ReadFromServerTask.h src/SendToServerTask.cpp include/SendToServerTask.h include/connectionHandler.h)
target_link_libraries( Client LINK_PUBLIC ${Boost_LIBRARIES} )
