# networkLibrary/CMakeLists.txt

# Create a static library for networkLibrary
add_library(networkLibrary STATIC networkLibrary.cpp)

# Include directory for networkLibrary (for headers)
target_include_directories(networkLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link utils library
target_link_libraries(networkLibrary PUBLIC utils)
