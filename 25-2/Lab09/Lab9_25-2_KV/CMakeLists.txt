cmake_minimum_required(VERSION 4.0)
project(Lab9_25_2_KV)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab9_25_2_KV main.cpp
        Bibliotecas/Categoria.h
        Bibliotecas/Nodo.h
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h)
