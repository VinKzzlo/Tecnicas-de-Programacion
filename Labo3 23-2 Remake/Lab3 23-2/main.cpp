/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 28 de abril de 2024, 17:53
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesReporte.h"

/*
 * 
 */
int main(int argc, char** argv) {

    emitirReportePreferencias("Canales.txt","RegistroDePreferencias.txt",
                              "Televidentes.txt","ReportePreferencias.txt");
    
    return 0;
}

