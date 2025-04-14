/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 *
 * Created on 6 de noviembre de 2023, 07:08 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#define tam_alumnos 100
#define tam_cursos 100
#define tam_escalas 30

using namespace std;

#include "funciones.h"
#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int semestre;
    struct Alumno arrAlumnos[tam_alumnos];
    int cantAlumnos = 0;
    struct Curso arrCursos[tam_cursos];
    int cantCursos = 0;
    struct Escala arrEscalas[tam_escalas];
    int cantEscalas = 0;
    solicitarDatos(semestre);
    cargarAlumnos(arrAlumnos, cantAlumnos);
    cargarCursos(arrCursos, cantCursos);
    cargarEscalas(arrEscalas, cantEscalas);
    actualizarMatricula(arrAlumnos, cantAlumnos, arrCursos, cantCursos, arrEscalas,
            cantEscalas, semestre);
    ordenarDatos(arrCursos, cantCursos);
    emitirReporte(arrCursos, cantCursos, semestre);
    return 0;
}

