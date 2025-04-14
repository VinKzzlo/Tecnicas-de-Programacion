/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 12 de mayo de 2024, 1:52
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int year, ciclo;
    leerCicloEvaluar(year,ciclo);
    generarReporte(year, ciclo, "Alumnos.txt", "Cursos.txt", "Escalas.txt",
                   "Matricula.txt","ReportePagosPorCiclo.txt");
    return 0;
}

