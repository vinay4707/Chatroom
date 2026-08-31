# chatClient/CMakeLists.txt

# Create an executable for chatClient
add_executable(asyncClient async_client.cpp)

# Link networkLibrary and utils libraries
target_link_libraries(asyncClient PRIVATE networkLibrary utils)
