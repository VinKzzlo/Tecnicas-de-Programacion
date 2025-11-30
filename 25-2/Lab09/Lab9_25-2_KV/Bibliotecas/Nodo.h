/*
 *
 * Proyecto:    Lab9_25_2_KV
 * Archivo:     Nodo.h
 * Autor:       VinKzzlo
 * Fecha:       25/11/2025
 *
 */

#ifndef LAB9_25_2_KV_NODO_H
#define LAB9_25_2_KV_NODO_H
#include "Categoria.h"
struct Nodo {
    struct Categoria categoria;
    struct Nodo *siguiente;
};
#endif //LAB9_25_2_KV_NODO_H