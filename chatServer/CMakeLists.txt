# chatServer/CMakeLists.txt

# Create an executable for chatServer
add_executable(asyncServer async_server.cpp)

# Link networkLibrary and utils libraries
target_link_libraries(asyncServer PRIVATE networkLibrary utils)
