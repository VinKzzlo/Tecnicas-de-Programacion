/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 12 de mayo de 2024, 21:47
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leeDatosMedicos(const char *nombArch,int *medicosCods,double *medicosTarifa,
                     int &numMedicos);
void leeDatosMedicinas(const char *nombArch,int *medicinCods,
                       double *medicinPrecios, int &numMedicin);
void reporteDePrueba(const char *nombArch,int *medicosCods,double *medicosTarifa,
                     int numMedicos,
                    int *medicinCods,double *medicinPrecios,int numMedicin);
void actualizarTotales(const char *nombArch,int *medicosCods,double *medicosTarifa,
                      int *medicosPacRec,int *medicosPacNoRec,double *medicosIngCitas,
                      double *medicosIngMeds,int numMedicos,
                      int *medicinCods,double *medicinPrecios,int *medicinCantVend,
                      double *medicinIngSinD,double *medicinDctos,int numMedicin);
void actualizarIngresoCita(double &medicosIngCitas,double duracionEnH,
                          double medicosTarifa,double porcDcto);
void actualizarDatosMedici(ifstream &arch,double &medicosIngMeds, double porcDcto,
                          int *medicinCods,double *medicinPrecios,int *medicinCantVend,
                          double *medicinIngSinD,double *medicinDctos,int numMedicin);

int buscarPosicionMedico(int codMedico,int *medicosCods,int numMedicos);
int buscarPosicionMedicina(int codMedicina,int *medicinCods,int numMedicin);

int leerObtenerHora(ifstream &arch);

void emitirReporte(const char *nombArch,int *medicosCods,double *medicosTarifa,
                   int *medicosPacRec,int *medicosPacNoRec,double *medicosIngCitas,
                   double *medicosIngMeds,int numMedicos,
                   int *medicinCods,double *medicinPrecios,int *medicinCantVend,
                   double *medicinIngSinD,double *medicinDctos,int numMedicin,
                   char seleccion, double &promedioIngresosTotales); //si es N, reporte normal, si es M, mejores medicos

void imprimirRegistroPorMedico(ofstream &arch,int *medicosCods,double *medicosTarifa,
                               int *medicosPacRec,int *medicosPacNoRec,
                               double *medicosIngCitas, double *medicosIngMeds,
                               int numMedicos,double &promedioIngresosTotales);
 void imprimirRegistroPorMedicamento(ofstream &arch,int *medicinCods,
                                    double *medicinPrecios,int *medicinCantVend,
                                    double *medicinIngSinD,double *medicinDctos,
                                    int numMedicin);
 
 void eliminarMeds(double promedioIngresosTotales,int *medicosCods,double *medicosTarifa,
                   int *medicosPacRec,int *medicosPacNoRec,double *medicosIngCitas,
                   double *medicosIngMeds,int &numMedicos);
 
 void imprimeEncabezadoMedico(ofstream &arch);
 void imprimeEncabezadoMedicina(ofstream &arch);
 void imprimeLinea(ofstream &arch,char caracter);
#endif /* FUNCIONESAUXILIARES_H */

