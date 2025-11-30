/*
 *
 * Proyecto:    Lab10_25_1_KV
 * Archivo:     Cuenta.h
 * Autor:       VinKzzlo
 * Fecha:       24/11/2025
 *
 */

#ifndef LAB10_25_1_KV_CUENTA_H
#define LAB10_25_1_KV_CUENTA_H
struct Cuenta {
    int codigo;
    char *nombre;
    double saldo;
    int fechaSobregiro;
    bool sobregiro;
};
#endif //LAB10_25_1_KV_CUENTA_H