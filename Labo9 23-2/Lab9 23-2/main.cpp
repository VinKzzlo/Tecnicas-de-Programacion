/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 15 de junio de 2024, 1:55
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Curso.h"
#include "Escala.h"


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
    leerMatricula("Matricula.csv",cursos,numCur,semestre,"Alumnos.csv",
                  escalas, numEsc);
    ordenarDatos(cursos,numCur);
    emitirReporte("ReporteDePagoPorCurso.txt",semestre,cursos,numCur);
    return 0;
}

