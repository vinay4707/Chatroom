cmake_minimum_required(VERSION 3.10)

# Project name and version
project(ChatApplication VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(utils)
add_subdirectory(networkLibrary)
add_subdirectory(chatClient)
add_subdirectory(chatServer)
