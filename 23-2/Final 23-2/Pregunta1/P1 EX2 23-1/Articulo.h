/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Articulo.h
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 20:43
 */

#ifndef ARTICULO_H
#define ARTICULO_H

struct Articulo{
    char *codigo;
    char *descripcion;
    int stock;
    double precio;
    int cantVendidos;
    double montoVendido;
    int cantPerdidos;
    double montoPerdido;
};

#endif /* ARTICULO_H */

