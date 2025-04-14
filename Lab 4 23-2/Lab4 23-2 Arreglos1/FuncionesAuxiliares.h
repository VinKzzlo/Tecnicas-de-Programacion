/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 6 de mayo de 2024, 17:02
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerDatos(const char *nombArch,double *coordX,double *coordY, int &numDat);
void imprimeDatosArreglos(const char *nombArch,double *coordX,double *coordY,
                          int numDat);
void calcularAreaPerimetro(double *coordX,double *coordY,int numDat,
                           double &perimetro, double &area);
void imprimeReporteFinal(const char *nombArch, double *coordX,double *coordY,
                         int numDat,double perimetro,double area);
#endif /* FUNCIONESAUXILIARES_H */

