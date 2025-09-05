/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Author: aml
 *
 * Created on 8 de abril de 2024, 07:10 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void EmitirReporte();
int CalcularDuracion(int hh_Ini, int min_Ini, int seg_Ini,
                     int hh_Fin, int min_Fin, int seg_Fin);
void TransformarDuracion(int duracion, int &hh, int &min, int &seg);
double CalcularDuracionHoras(int duracion);
double CalcularMontoTotal(char carReceta, double duracionHoras,
                          double tarifaHora, double precioMedi);

#endif /* FUNCIONESAUXILIARES_H */

