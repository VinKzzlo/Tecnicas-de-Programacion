/* 
 * File:   main.cpp
 * Autor:  Alessandro Salvador Santé Vega - 20223006
 * Created on 15 de abril de 2024, 07:15 PM
 * 
 * Descripción del programa: Programa que lee datos de citas médicas
 * realizadas en un centro de salud, y se pide procesarlos según las
 * condiciones necesarias (para citas con cierta duración),
 * luego se genera un reporte y se muestran estadísticas al respecto.
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesParaReporte.h"
int main(int argc, char** argv) {

    generarReporte("CitasMedicas.txt","ReporteDeCitas.txt");
    
    return 0;
}

