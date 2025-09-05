/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesParaReporte.h
 * Autor: VinKzzlo
 *
 * Creado el on 21 de abril de 2024, 22:16
 */

#ifndef FUNCIONESPARAREPORTE_H
#define FUNCIONESPARAREPORTE_H

void emitirReportePreferencias(const char *nombArchPref,const char *nombArchTel,
                               const char *nombArchCan, const char *nombArchRep);

void leeEImprimeEncabezadoCanal(ifstream &archCan,ofstream &archRep,int &canal);
void leeImprimeNombreCanal(ifstream &archCan,ofstream &archRep,  char cFin);

void imprimeEncabezadoClientes(ofstream &archRep);
void imprimeDatosTelevidentes(int canal, ifstream &archTel,ifstream &archPref,
                              ofstream &archRep, int &nroMenores, int &nroJovenes,
                              int &nroAdultos, int &nroPersonas, int &tiempoTotal);
void buscarImprimirDatosCliente(int nroDNI,int horaI,int horaF,
                                ifstream &archTel,ofstream &archRep,
                                int &nroMenores,int &nroJovenes,int &nroAdultos,
                                int &nroPersonas,int &tiempoTotal);
void imprimirNombreTelevidente(ifstream &archTel,ofstream &archRep);

int obtenerHora(ifstream &archPref);


void imprimirEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep, char caracter);

#endif /* FUNCIONESPARAREPORTE_H */

