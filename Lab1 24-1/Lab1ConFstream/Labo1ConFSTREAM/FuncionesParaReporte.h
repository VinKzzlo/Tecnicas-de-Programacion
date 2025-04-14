/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesParaReporte.h
 * Autor: VinKzzlo
 *
 * Creado el on 15 de abril de 2024, 16:00
 */

#ifndef FUNCIONESPARAREPORTE_H
#define FUNCIONESPARAREPORTE_H

#include <fstream>


void emitirReporte(const char *nombArchDatos, const char *nombArchRep);
void imprimirYProcesarDatos(ofstream &archRep, int dd,int mm,int aa, int nroDNI,
     int horaI, int horaF, double tarifaPorH,char especialidad,char fueRecetado,
     double pagoMedicinas, double &totalIngresos,
     int &nroPacDerm, int &nroPacPed, int &nroPacCardF,int &nroPacUltEstadist,
               double &gastosMedPacDerm);

void imprimirHora(ofstream &archRep,int horaEnS);
void imprimirEspecialidad(ofstream &archRep, char especialidad,
        bool &cardio, bool &pedia,bool &derma);
void imprimeMontoYSumaIngresos(ofstream &archRep, double tarifaPorH,
        double duracionEnH,double pagoMedicinas, double &totalIngresos);


int convertirHora(ifstream &archDat);

void imprimirEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESPARAREPORTE_H */

