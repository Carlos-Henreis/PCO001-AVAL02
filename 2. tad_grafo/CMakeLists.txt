cmake_minimum_required(VERSION 3.28)
project(tad_grafo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(tads_auxiliares)

add_executable(tad_grafo
        tads_auxiliares/FilaEstatica.cpp
        tads_auxiliares/FilaEstatica.h
        tads_auxiliares/ListaDinEncadeada.cpp
        tads_auxiliares/ListaDinEncadeada.h
        Grafo.cpp
        Grafo.h
        main.cpp)
