/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Venta.h
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 2:04
 */

#ifndef VENTA_H
#define VENTA_H
#include "Fecha.h"

struct Venta{
    int dniComp;
    char nombComp[60];
    struct Fecha fecha;
    int calificacion;
};

#endif /* VENTA_H */

