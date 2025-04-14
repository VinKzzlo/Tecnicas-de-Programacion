
// File:   main.cpp
// Author: superflash41

#include <iostream>
#include <iomanip>
using namespace std;

#include "funciones.h"
#define CANT_AL 300

int main(int argc, char** argv) {
    int cods[CANT_AL], cursos[CANT_AL]{}, nd = 0;
    double sumas[CANT_AL]{}, credits[CANT_AL]{};
    leerCalificaciones("cal.txt", cods, cursos, sumas, credits, nd);
    generarReporte("ReporteDePagoPorAlumno.txt", "Alumnos.txt",
            "Facultades.txt", cods, cursos, sumas, credits, nd);
    return 0;
}
