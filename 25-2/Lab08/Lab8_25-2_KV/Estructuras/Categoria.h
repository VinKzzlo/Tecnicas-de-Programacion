/*
 *
 * Proyecto:    Lab8_25_2_KV
 * Archivo:     Categoria.h
 * Autor:       VinKzzlo
 * Fecha:       18/11/2025
 *
 */

#ifndef LAB8_25_2_KV_CATEGORIA_H
#define LAB8_25_2_KV_CATEGORIA_H
#include "../Estructuras/Reproduccion.h"
struct Categoria {
    char *codigo;
    char *nombre;
    char *descripcion;
    struct Reproduccion *reproducciones;
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};
#endif //LAB8_25_2_KV_CATEGORIA_H