/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 *
 * Created on 5 de mayo de 2024, 20:22
 */

#include <iostream>
#include <iomanip>

using namespace std;

#define MAX_VER 20

#include "LeerArchivosArreglos.h"

int main(int argc, char** argv) {
    
    double ArrCoordX[MAX_VER];
    double ArrCoordY[MAX_VER];
    int cantVertices;
    LeerCoordenadas(ArrCoordX, ArrCoordY, cantVertices);
    ValidarArreglos(ArrCoordX, ArrCoordY, cantVertices);
    
    double area, perimetro;
    int cantLados;
    CalcularDatosPoligono(ArrCoordX, ArrCoordY, cantVertices, area, perimetro, cantLados);
    ReportePoligono(ArrCoordX, ArrCoordY, cantVertices, area, perimetro, cantLados);
    
    return 0;
}

