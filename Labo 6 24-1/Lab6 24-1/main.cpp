/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 1 de junio de 2024, 1:08
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAXALU 100


int main(int argc, char** argv) {
    int facultad;
    solicitarDatos(facultad);
    
    int arrCodigoAlumnos[MAXALU], arrNumCursos[MAXALU]{}, cantAlu=0;
    double arrSumaPonderada[MAXALU]{}, arrNumCreditos[MAXALU]{};
    
    
    cargarCalif("Calificaciones.txt",arrCodigoAlumnos,arrNumCursos,
                         arrSumaPonderada,arrNumCreditos,cantAlu);
    emitirReporte("Alumnos.txt", "Facultades.txt", "ReporteDePagoPorAlumno.txt",
                  arrCodigoAlumnos, arrNumCursos, arrSumaPonderada,
                  arrNumCreditos,cantAlu,facultad);
    
    return 0;
}

