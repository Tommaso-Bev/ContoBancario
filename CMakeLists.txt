cmake_minimum_required(VERSION 3.23)
project(ContoBanca)


set(CMAKE_CXX_STANDARD 23)

add_subdirectory(test/googletest1.14.0)

include_directories(test/googletest1.14.0/include)
include_directories(test/googletest1.14.0/include)

add_executable(ContoBanca main.cpp Conto.cpp Conto.h Transazione.cpp Transazione.h Utente.cpp Utente.h Interfaccia.cpp Interfaccia.h tests/testUtente.cpp tests/testConto.cpp)

target_link_libraries(ContoBanca gtest gtest_main gmock gmock_main)