/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 26 de mayo de 2024, 14:46
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAXPAC 100
#define MAXMED 250


int main(int argc, char** argv) {
    int pacientesDNI[MAXPAC], pacientesDist[MAXPAC], cantPac,
        pacientesCantCit[MAXPAC]{},pacientesCantMeds[MAXPAC]{};
    double pacientesDcto[MAXPAC], pacientesPago[MAXPAC]{};
    char pacientesClasif[MAXPAC];
    
    int medicinaCodigo[MAXMED], cantMedi;
    double medicinaPrecio[MAXMED];
    
    leerDatosPacientes("Pacientes.txt",pacientesDNI,pacientesDist,pacientesDcto,
                       pacientesClasif,cantPac);
    leerDatosMedicinas("Medicinas.txt",medicinaCodigo,medicinaPrecio,cantMedi);
    verificarReportePrueba("ReporteDePrueba.txt",pacientesDNI,pacientesDist,
                           pacientesDcto,pacientesClasif,cantPac,
                           medicinaCodigo,medicinaPrecio,cantMedi);
    updateTotalPacientes("CitasMedicas.txt",pacientesDNI,pacientesDist,
                           pacientesDcto,pacientesClasif,cantPac,
                           medicinaCodigo,medicinaPrecio,cantMedi,
                           pacientesCantCit,pacientesCantMeds,pacientesPago);
    ordenarArreglosPacs(pacientesDNI,pacientesDist,pacientesDcto,pacientesClasif,
                        pacientesCantCit,pacientesCantMeds,pacientesPago,cantPac);
    emitirReportePacientes("ConsolidadoPacientes.txt",pacientesDNI,pacientesDist,
                           pacientesDcto,pacientesClasif, pacientesCantCit,
                           pacientesCantMeds,pacientesPago,cantPac);
    
    return 0;
}

