/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 29 de abril de 2024, 16:36
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesReporte.h"
/*
 * 
 */
int main(int argc, char** argv) {

    emitirReporteCitas("Medicos.txt","Pacientes.txt","Citas.txt",
                       "ReporteDeCitasPorPaciente.txt");
    
    return 0;
}

