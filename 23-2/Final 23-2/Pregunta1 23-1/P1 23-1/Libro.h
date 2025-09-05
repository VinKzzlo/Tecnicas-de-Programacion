/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Libro.h
 * Autor: VinKzzlo
 *
 * Creado el on 1 de julio de 2024, 17:07
 */

#ifndef LIBRO_H
#define LIBRO_H
#include "UsuarioConElLibro.h"

struct Libro{
    char *codigo;
    char *titulo;
    char *autor;
    int cantidad;
    double precio;
    struct UsuarioConElLibro *usuarios;
    int cantUsuarios;
};

#endif /* LIBRO_H */

