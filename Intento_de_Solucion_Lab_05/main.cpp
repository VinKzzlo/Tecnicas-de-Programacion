/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Bek
 *
 * Created on 12 de mayo de 2024, 05:50 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAXMEDICOS 40
#define MAXMEDICINA 250

int main(int argc, char** argv) {
    
    int cantMedico=0,cantMedicina=0;
    int ArrCodMedico[MAXMEDICOS],ArrCodMedicina[MAXMEDICINA];
    double ArrTarifMedico[MAXMEDICOS],ArrPrecMedicina[MAXMEDICINA];
    //tarea 1
    LeerMedicosColocarArr("Medicos.txt",ArrCodMedico,ArrTarifMedico,cantMedico);
    //tarea 2
    LeerMedicinasColocarArr("Medicinas.txt",ArrCodMedicina,
                            ArrPrecMedicina,cantMedicina);
    //tarea 3
    ImprimirReportMedicoArr("ReporteSimpleMedicos.txt",ArrCodMedico,
                            ArrTarifMedico,cantMedico);
    ImprimirReportMedicinaArr("ReporteSimpleMedicina.txt",ArrCodMedicina,
                              ArrPrecMedicina,cantMedicina);
    //tarea 4
    //Actualizar precios de acuerdo al archivo citas medicas
    double ArrIngresoCitas[MAXMEDICOS]{},ArrIngresoMedica[MAXMEDICOS]{};
    int ArrCantPacConMedic[MAXMEDICOS]{},ArrCantPacSinMedic[MAXMEDICOS]{};
    
    int ArrCantUnidVendid[MAXMEDICINA]{};
    double ArrIngSinDescMedic[MAXMEDICINA]{},ArrDescSeguMedic[MAXMEDICINA]{};
    
    LeerCitasMedicas("CitasMedicas.txt",ArrCodMedico,ArrTarifMedico,ArrIngresoCitas,
                     ArrIngresoMedica,ArrCantPacConMedic,ArrCantPacSinMedic,cantMedico,
                     ArrCodMedicina,ArrPrecMedicina,ArrCantUnidVendid,
                     ArrIngSinDescMedic,ArrDescSeguMedic,cantMedicina);
    
    EmitirReporteIngresos("ReporteDeIngresos.txt",ArrCodMedico,ArrTarifMedico,
                          ArrIngresoCitas,ArrIngresoMedica,ArrCantPacConMedic,
                          ArrCantPacSinMedic,cantMedico,ArrCodMedicina,
                          ArrPrecMedicina,ArrCantUnidVendid,ArrIngSinDescMedic,
                          ArrDescSeguMedic,cantMedicina);
    return 0;
}

