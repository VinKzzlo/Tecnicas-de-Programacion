/* 
 * File:   main.cpp
 * Author:  Vicente Jorge
 * Código: 20222159
 * Created on 9 de octubre de 2023, 06:35 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "funcionesAuxiliares.h"

int main(int argc, char** argv) {
    int anio,ciclo;
    ingresarFechas(anio,ciclo);
//    Para pruebas
//    anio=2023;
//    ciclo=1;
    inicializarArchYEmitirReporte("ReportePorCiclo.txt","Alumnos.txt",
            "Escalas.txt","Cursos.txt","Matricula.txt",anio,ciclo);
    return 0;
}

