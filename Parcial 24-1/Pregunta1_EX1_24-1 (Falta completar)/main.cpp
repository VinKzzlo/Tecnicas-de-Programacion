/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 25 de mayo de 2024, 23:26
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesReporte.h"
/*
 * 
 */
int main(int argc, char** argv) {
    emitirReporteCitas("CitasMedicas.txt","Medicinas.txt","Medicos.txt",
                       "Pacientes.txt","DetallesCitas.txt");
    return 0;
}

