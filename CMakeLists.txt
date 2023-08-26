cmake_minimum_required(VERSION 3.23)
project(ContoBanca)

set(CMAKE_CXX_STANDARD 23)

add_executable(ContoBanca main.cpp Conto.cpp Conto.h Transazione.cpp Transazione.h Utente.cpp Utente.h Interfaccia.cpp Interfaccia.h)
