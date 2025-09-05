/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   LeerArchivosArreglos.h
 *
 * Created on 5 de mayo de 2024, 20:32
 */

#ifndef LEERARCHIVOSARREGLOS_H
#define LEERARCHIVOSARREGLOS_H

void LeerCoordenadas(double *ArrCoordX, double *ArrCoordY, int &cantVertices);
void ValidarArreglos(double *ArrCoordX, double *ArrCoordY, int cantVertices);

void CalcularDatosPoligono(double *ArrCoordX, double *ArrCoordY, int cantVertices, 
                                            double &area, double &perimetro, int &cantLados);
double CalcularSumaFormula(double *ArrIni, double *ArrFin, int cantDatos);
void CalcularPerimetro(double *ArrCoordX, double *ArrCoordY, int cantVertices, double &perimetro, int &cantLados);
void ReportePoligono(double *ArrCoordX, double *ArrCoordY, int cantVertices, double area, double perimetro, int cantLados);

#endif /* LEERARCHIVOSARREGLOS_H */

