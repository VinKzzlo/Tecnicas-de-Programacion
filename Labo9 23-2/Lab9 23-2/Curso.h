/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   Curso.h
 * Autor: VinKzzlo
 *
 * Creado el on 15 de junio de 2024, 2:06
 */

#ifndef CURSO_H
#define CURSO_H
#include "Alumno.h"

struct Curso{
    int codigo;
    char *nombre;
    double numCreds;
    struct Alumno *alumnos;
    int numAlu;
    double ingresos;
};

#endif /* CURSO_H */

