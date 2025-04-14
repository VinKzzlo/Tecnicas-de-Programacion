/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Funciones.h
 * Author: USUARIO
 *
 * Created on 11 de mayo de 2024, 20:06
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void emitirReporte(const char*nombArchRep, const char *nombArchMedicinas, 
                   const char*nombArchMedicos, const char*nombArchCitas);

void leerEspecialidad(ifstream &archMedicos, ofstream &archRep);

void imprimirEncabezado(ofstream &archRep);

void imprimeLinea(char c, int n, ofstream &archRep);

void imprimirEncabezado2(ofstream &archRep);

void leerCitasMedicas(ifstream &archCitas, ofstream &archRep);

#endif /* FUNCIONES_H */

