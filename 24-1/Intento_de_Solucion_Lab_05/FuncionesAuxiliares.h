/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Author: Bek
 *
 * Created on 12 de mayo de 2024, 05:57 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void LeerMedicosColocarArr(const char *nombArchMedico,int *ArrCodMedico,
                           double *ArrTarifMedico,int &cantMedico);
void LeerMedicinasColocarArr(const char *nombArchMedicina,int *ArrCodMedicina,
                             double *ArrPrecMedicina,int &cantMedicina);
void LeerCitasMedicas(const char *nombArchCitMedic,int *ArrCodMedico,
                      double *ArrTarifMedico,double *ArrIngresoCitas,
                      double *ArrIngresoMedica,int *ArrCantPacConMedic,
                      int *ArrCantPacSinMedic,int cantMedico,
                      int *ArrCodMedicina,double *ArrPrecMedicina,
                      int *ArrCantUnidVendid,double *ArrIngSinDescMedic,
                      double *ArrDescSeguMedic,int cantMedicina);
void ImprimirReportMedicoArr(const char *nombArchRepoMedico,int *ArrCodMedico,
                             double *ArrTarifMedico,int cantMedico);
void ImprimirReportMedicinaArr(const char *nombArchRepoMedicina,int *ArrCodMedicina,
                               double *ArrPrecMedicina,int cantMedicina);
int LeerHora(ifstream &archCitMedica);
int BuscarIndice(int dato,int *Arreglo,int cantDatos);
void EmitirReporteIngresos(const char *nombArchReporIngres,int *ArrCodMedico,
                           double *ArrTarifMedico,double *ArrIngresoCitas,
                           double *ArrIngresoMedica,int *ArrCantPacConMedic,
                           int *ArrCantPacSinMedic,int cantMedico,
                           int *ArrCodMedicina,double *ArrPrecMedicina,
                           int *ArrCantUnidVendid,double *ArrIngSinDescMedic,
                           double *ArrDescSeguMedic,int cantMedicina);
void ImprimirEncabezadoMedico(ofstream &archReporIngresos);
void ImprimirLinea(int cant,char simb,ofstream &archReporIngresos);
void ImprimirReporteMedicos(int *ArrCodMedico,double *ArrTarifMedico,
                            double *ArrIngresoCitas,double *ArrIngresoMedica,
                            int *ArrCantPacConMedic,int *ArrCantPacSinMedic,
                            int cantMedico,ofstream &archReporIngresos);
void ImprimirReporteMedicinas(int *ArrCodMedicina,double *ArrPrecMedicina,
                              int *ArrCantUnidVendid,double *ArrIngSinDescMedic,
                              double *ArrDescSeguMedic,int cantMedicina,
                              ofstream &archReporIngresos);
void ImprimirEncabezadoMedicina(ofstream &archReporIngresos);

#endif /* FUNCIONESAUXILIARES_H */

