/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Libro.h
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 2:05
 */

#ifndef LIBRO_H
#define LIBRO_H
#include "Venta.h"

struct Libro{
    char codigo[8];
    char titulo[100];
    char autor[60];
    double precio;
    struct Venta ventas[10];
    int librosVendidos;
    struct Fecha fechaMasReciente;
    int sumaCalificaciones;
    int ranking;
};

#endif /* LIBRO_H */

