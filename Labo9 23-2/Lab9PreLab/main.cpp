/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 17 de junio de 2024, 16:54
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Escala.h"
#include "Curso.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int semestre;
    solicitarDatos(semestre);
    
    struct Escala escalas[30];
    int numEsc;
    leerEscalas("Escalas.csv",escalas,numEsc);
    
    struct Curso *cursos;
    cursos = new struct Curso[100]{};
    int numCur;
    leerCursos("Cursos.csv",cursos,numCur);
    actualizarMatricula("Matricula.csv",semestre,escalas,numEsc,cursos,numCur,
                        "Alumnos.csv");
    ordenarDatos(cursos,numCur);
    emitirReporte("ReporteDePagoPorCurso.txt",semestre,cursos,numCur);
    return 0;
}

