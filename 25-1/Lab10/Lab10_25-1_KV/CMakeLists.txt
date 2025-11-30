cmake_minimum_required(VERSION 4.0)
project(Lab10_25_1_KV)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab10_25_1_KV main.cpp
        Bibliotecas/Cuenta.h
        Bibliotecas/Nodo.h
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h)
