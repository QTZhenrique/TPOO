cmake_minimum_required(VERSION 3.28)
project(TP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP main.cpp
        Simulador/Simulador.cpp
        UI/UI.cpp
        Buffer/Buffer.cpp
        Buffer/Buffer.h
        Caravanas/Caravana.cpp
        Caravanas/Caravana.h
        Caravanas/Caravana.h)
