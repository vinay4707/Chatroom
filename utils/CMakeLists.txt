# utils/CMakeLists.txt

# Create a static library for utils
add_library(utils STATIC Logger.cpp)

# Include directory for utils (for headers)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
