cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_PROJECT_NAME PID)

set(SOURCES Src/PID.c)
set(HEADERS Inc/PID.h)
add_library(PID ${SOURCES} ${HEADERS})
target_include_directories(PID PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})