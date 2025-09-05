/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Vendedor.h
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 21:44
 */

#ifndef VENDEDOR_H
#define VENDEDOR_H
#include "ArticuloPedido.h"

struct Vendedor{
    int codigo;
    char *nombre;
    double porcVentas;
    double cuotaMin;
    struct ArticuloPedido *articulosVendidos;
    int cantArtVendidos;
    struct ArticuloPedido *articulosPerdidos;
    int cantArtPerdidos;
    double montoTotalVendido;
    double montoTotalPerdido;
};

#endif /* VENDEDOR_H */

