/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Atencion.h
 * Autor:  VinKzzlo
 *
 * Creado el 3 de julio de 2025, 22:12
 */
#include "Plato.h"
#include "Comentario.h"
#ifndef ATENCION_H
#define ATENCION_H

struct Atencion{
    int codigo;
    struct Plato *platosAtendidos;
    int cantidadPlatos;
    double totalVenta;
    int hora;
    struct Comentario *comentarios;
    int cantidadComentarios;
};

#endif /* ATENCION_H */

