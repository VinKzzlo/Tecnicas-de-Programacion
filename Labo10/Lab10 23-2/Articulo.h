/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Articulo.h
 * Autor: VinKzzlo
 *
 * Creado el on 23 de junio de 2024, 18:04
 */

#ifndef ARTICULO_H
#define ARTICULO_H

struct Articulo{
    char codigo[8];
    char descripcion[60];
    double precio;
    int cantVendido;
    double montoVendido;
};

#endif /* ARTICULO_H */

