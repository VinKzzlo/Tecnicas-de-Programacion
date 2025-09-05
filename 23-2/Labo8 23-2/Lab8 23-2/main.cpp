/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 10 de junio de 2024, 16:51
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"
#define MAX_ALU 100
#define MAX_CUR 100
#define MAX_ESC 30

int main(int argc, char** argv) {
    int anio,ciclo, semestre;
    solicitarDatos(anio,ciclo);
    semestre = anio*10 + ciclo;
    
    int numAlu, numCur, numEsc;
    struct Alumno alumnos[MAX_ALU];
    struct Curso cursos[MAX_CUR];
    struct Escala escalas[MAX_ESC];
    
    leerAlumnos("Alumnos.csv",alumnos,numAlu);
    leerCursos("Cursos.csv",cursos,numCur);
    leerEscalas("Escalas.csv",escalas,numEsc);
    updateCursos("Matricula.csv",alumnos,numAlu,cursos,numCur,escalas,numEsc,semestre);
    return 0;
}

