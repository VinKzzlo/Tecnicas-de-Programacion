cmake_minimum_required(VERSION 4.0)
project(Lab8_25_2_KV)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab8_25_2_KV main.cpp
        Estructuras/Reproduccion.h
        Estructuras/Categoria.h
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h)
