/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Libro.h
 * Author: aml
 *
 * Created on 17 de junio de 2024, 07:16 PM
 */

#ifndef LIBRO_H
#define LIBRO_H
#include "Venta.h"
struct Libro{
    char *codigo;
    char *titulo;
    char *autor;
    double precio;
    struct Venta *ventas;
    int librosVendidos;
    int sumaDeCalificaciones;
    int ranking;
};

#endif /* LIBRO_H */

