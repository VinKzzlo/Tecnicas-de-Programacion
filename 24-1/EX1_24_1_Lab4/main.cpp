/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: USUARIO
 *
 * Created on 11 de mayo de 2024, 12:21
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "Funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    leerArchivosYImprimir("Medicos.txt", "Medicinas.txt", "CitasMedicas.txt",
                           "Reporte.txt");
    
    return 0;
}

