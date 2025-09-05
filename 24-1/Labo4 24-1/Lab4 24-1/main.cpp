/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 4 de mayo de 2024, 19:50
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
/*
 * 
 */
int main(int argc, char** argv) {
    emiteReporteCitasMedicas("CitasMedicas.txt","Medicinas.txt","Medicos.txt",
                             "ReporteDeCitasMedicas.txt");
    return 0;
}

