/*
 *
 * Proyecto:    Lab8_25_2_KV
 * Archivo:     Reproduccion.h
 * Autor:       VinKzzlo
 * Fecha:       18/11/2025
 *
 */

#ifndef LAB8_25_2_KV_REPRODUCCION_H
#define LAB8_25_2_KV_REPRODUCCION_H

struct Reproduccion {
    char *canal;
    double rating;
    int duracion;
    char *comentarios[20];
    int numComentarios;
};

#endif //LAB8_25_2_KV_REPRODUCCION_H