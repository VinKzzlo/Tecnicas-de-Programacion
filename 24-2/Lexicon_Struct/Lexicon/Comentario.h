/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Comentario.h
 * Autor:  VinKzzlo
 *
 * Creado el 3 de julio de 2025, 22:11
 */
#include "Palabra.h"
#ifndef COMENTARIO_H
#define COMENTARIO_H

struct Comentario{
    char *texto;
    char *pre_procesado;
    struct Palabra palabras[20];
    int cantidad_palabras;
    int polaridad_total;
};

#endif /* COMENTARIO_H */

