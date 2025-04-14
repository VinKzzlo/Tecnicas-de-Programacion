/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 12 de mayo de 2024, 19:39
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int medicosCods[50], medicosPacRec[50]{}, medicosPacNoRec[50]{}, numMedicos;
    double medicosTarifa[50], medicosIngCitas[50]{}, medicosIngMeds[50]{};
    
    int medicinCods[220], medicinCantVend[220]{}, numMedicin;
    double medicinPrecios[220], medicinIngSinD[220]{}, medicinDctos[220]{};
    
    double promedioIngresosTotales;
    
    leeDatosMedicos("Medicos.txt",medicosCods,medicosTarifa,numMedicos);
    leeDatosMedicinas("Medicinas.txt",medicinCods,medicinPrecios,numMedicin);
    reporteDePrueba("ReporteDePrueba.txt",medicosCods,medicosTarifa,numMedicos,
                    medicinCods,medicinPrecios,numMedicin);
    actualizarTotales("CitasMedicas.txt",medicosCods,medicosTarifa,medicosPacRec,
                      medicosPacNoRec,medicosIngCitas,medicosIngMeds,numMedicos,
                      medicinCods,medicinPrecios,medicinCantVend,medicinIngSinD,
                      medicinDctos,numMedicin);
    emitirReporte("ReporteDeIngresos.txt",medicosCods,medicosTarifa,medicosPacRec,
                  medicosPacNoRec,medicosIngCitas,medicosIngMeds,numMedicos,
                  medicinCods,medicinPrecios,medicinCantVend,medicinIngSinD,
                  medicinDctos,numMedicin, 'N', promedioIngresosTotales);
    eliminarMeds(promedioIngresosTotales,medicosCods,medicosTarifa,medicosPacRec,
                 medicosPacNoRec,medicosIngCitas,medicosIngMeds,numMedicos);
    emitirReporte("ReporteDeMejoresMedicos.txt",medicosCods,medicosTarifa,medicosPacRec,
                  medicosPacNoRec,medicosIngCitas,medicosIngMeds,numMedicos,
                  medicinCods,medicinPrecios,medicinCantVend,medicinIngSinD,
                  medicinDctos,numMedicin, 'M', promedioIngresosTotales);
    return 0;
}

