/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Alumno.h
 * Author: Alessandro Salvador Santé Vega - 20223006
 *
 * Created on 10 de junio de 2024, 07:17 PM
 */

#ifndef ALUMNO_H
#define ALUMNO_H
#include "Facultad.h"

struct Alumno{
    int codigo;
    char nombre[60];
    int numCursos;
    double sumaPonderada;
    double numCreditos;
    double promedioPonderado;
    struct Facultad facultad;
};

#endif /* ALUMNO_H */

