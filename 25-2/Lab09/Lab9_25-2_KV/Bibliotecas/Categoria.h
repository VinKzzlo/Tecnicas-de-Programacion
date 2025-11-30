/*
 *
 * Proyecto:    Lab9_25_2_KV
 * Archivo:     Categoria.h
 * Autor:       VinKzzlo
 * Fecha:       25/11/2025
 *
 */

#ifndef LAB9_25_2_KV_CATEGORIA_H
#define LAB9_25_2_KV_CATEGORIA_H
struct Categoria {
    char *codigo;
    char *nombre;
    char *descripcion;
    char *canalConDuracionMaxima;
    int duracionMaxima;
    int duracionTotal;
    double arrDropOff[20];
    int cantidadDeReproducciones;
    double promedioDropOff;
};
#endif //LAB9_25_2_KV_CATEGORIA_H