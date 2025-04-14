
/* 
 * File:   funcionesParaReporte.h
 * Author: aml
 *
 * Created on 8 de abril de 2024, 07:24 PM
 */

#ifndef FUNCIONESPARAREPORTE_H
#define FUNCIONESPARAREPORTE_H

void generarEImprimirReporte();
void imprimeYProcesaDatos(int fechaCita,int nroDNI,int horaInicio,int horaFin,
    double montoCita,char especialidad,char fueRecetado,double montoMedicinas,
    int nroPacientes,double &montoCitaYMed,double &duracion,double &totalIngresos,
    int &cantEstadist1,int &cantEstadist2,int &cantEstadist3,int &cantEstadist4,
    int &cantEstadist5,int &cantEstadist6);
int leerFechaUHora(char);

void imprimirEncabezado();
void imprimeLinea(char);
void imprimirFecha(int );
void imprimirHora(int);
void imprimirEspecialidad(char especialidad);
#endif /* FUNCIONESPARAREPORTE_H */

