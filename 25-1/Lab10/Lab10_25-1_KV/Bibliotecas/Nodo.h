/*
 *
 * Proyecto:    Lab10_25_1_KV
 * Archivo:     Nodo.h
 * Autor:       VinKzzlo
 * Fecha:       24/11/2025
 *
 */

#ifndef LAB10_25_1_KV_NODO_H
#define LAB10_25_1_KV_NODO_H
#include "Cuenta.h"
struct Nodo {
    struct Cuenta cuenta;
    struct Nodo *siguiente;
};
#endif //LAB10_25_1_KV_NODO_H