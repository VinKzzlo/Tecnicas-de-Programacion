/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 6 de mayo de 2024, 16:59
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAX_DATOS 20
/*
 * 
 */
int main(int argc, char** argv) {
    int numDat;
    double coordX[MAX_DATOS], coordY[MAX_DATOS], area, perimetro;
    
    leerDatos("Poligono.txt",coordX, coordY, numDat);
    imprimeDatosArreglos("ReporteVertices.txt",coordX,coordY,numDat);
    calcularAreaPerimetro(coordX,coordY,numDat,perimetro,area);
    imprimeReporteFinal("ReporteCompletoPoligono.txt",
                        coordX,coordY,numDat,perimetro,area);
    return 0;
}

