/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Alessandro Salvador Santé Vega - 20223006
 *
 * Created on 29 de abril de 2024, 07:13 PM
 * 
 * - DESCRIPCION DEL PROGRAMA -
 * Programa que a partir de la correcta lectura de 3 archivos, uno de Citas,
 * uno de datos de medicos y otro de medicinas; Imprime un reporte de Citas Medicas,
 * se toma en cuenta ciertas condiciones para imprimir, y por último imprime
 * los datos del medico que aportó mas ingresos al instituto
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesReporte.h"
/*
 * 
 */
int main(int argc, char** argv) {
    emitirReporte("CitasMedicas.txt","Medicinas.txt","Medicos.txt",
                  "ReporteDeCitasMedicas.txt");
    return 0;
}

