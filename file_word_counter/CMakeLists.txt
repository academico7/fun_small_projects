cmake_minimum_required(VERSION 3.12)
project(file_word_counter)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3")

# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# #set(INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
# set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
# set(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# set(MAP_STRUCT_DIR ${PROJECT_SOURCE_DIR}/src/map_structure)

# #include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
# include_directories(${MAP_STRUCT_DIR})

# add_subdirectory(src)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/word_counter_hash.cpp)










