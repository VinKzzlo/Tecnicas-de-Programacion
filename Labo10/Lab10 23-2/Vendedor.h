/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Vendedor.h
 * Autor: VinKzzlo
 *
 * Creado el on 23 de junio de 2024, 18:12
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "ArticuloVendido.h"

struct Vendedor{
    int codigo;
    char nombre[60];
    double porcVentas;
    double cuotaMin;
    struct ArticuloVendido artVendidos[60];
    int numArtVend;
    double montoVend;
    bool superoCuota;
};

#endif /* VENDEDOR_H */

