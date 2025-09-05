/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Alessandro Salvador Santé Vega - 20223006
 * Created on 10 de junio de 2024, 07:10 PM
 * - Descripción del programa - 
 * Programa que busca imprimir las estadísticas generales de un alumno en el
 * último ciclo de estudios (nro Cursos, Prom. Ponderado, Facultad a la que pertenece.
 * Para ello, se procesan los datos de 3 archivos: Alumnos, con los datos personales;
 * Facultades, con el nombre y codigo de la facultad; y Calificaciones, que contiene
 * los alumnos por cada curso junto a su nota (además del numero de creditos del curso
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "Alumno.h"
#include "FuncionesAuxiliares.h"

int main(int argc, char** argv) {
    
    struct Alumno arrAlumnos[100]{};
    int numAlu;
    leerCalificaciones("Calificaciones.txt",arrAlumnos,numAlu);
    leerAlumnos("Alumnos.csv",arrAlumnos,numAlu);
    leerFacultades("Facultades.txt",arrAlumnos,numAlu);
    emitirReporte("ReporteDePagoPorAlumno.txt",arrAlumnos,numAlu);
    return 0;
}

