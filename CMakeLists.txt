cmake_minimum_required(VERSION 3.23)
project(OS3)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        headers/MessageQueueProxy.cpp headers/MessageQueueProxy.h
        headers/names.cpp headers/names.h
        )

add_executable(OS3 main.cpp ${SOURCES})
add_executable(MESSENGER messenger.cpp ${SOURCES})