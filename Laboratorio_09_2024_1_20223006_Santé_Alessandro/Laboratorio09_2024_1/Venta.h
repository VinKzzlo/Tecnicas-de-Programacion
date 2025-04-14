/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Venta.h
 * Author: aml
 *
 * Created on 17 de junio de 2024, 07:15 PM
 */

#ifndef VENTA_H
#define VENTA_H
#include "Fecha.h"

struct Venta{
    int dni;
    struct Fecha fecha;
    int calificacion;
};

#endif /* VENTA_H */

