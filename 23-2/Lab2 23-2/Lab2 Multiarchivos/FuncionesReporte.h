/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesReporte.h
 * Autor: VinKzzlo
 *
 * Creado el on 29 de abril de 2024, 16:57
 */

#ifndef FUNCIONESREPORTE_H
#define FUNCIONESREPORTE_H

void emitirReporteCitas(const char *nombArchMed,const char *nombArchPac,
                        const char *nombArchCit,const char *nombArchRep);

void buscaImprimeCitas(int dniPac,ifstream &archCit,ifstream &archMed,
                       ofstream &archRep,double &totalPagoCitas);
void buscaImprimeNombreTarifa(int codMedico,ifstream &archMed,ofstream &archRep,
                              double &tarifa);
void imprimeNombreMedico(ifstream &archMed,ofstream &archRep);
int obtenerHora(ifstream &archCit);

void leeImprimeDatosPaciente(ifstream &archPac,ofstream &archRep, int &dniPac);
void imprimeNombrePac(ifstream &archPac,ofstream &archRep);

void imprimeEncabezadoDatosCita(ofstream &archRep);

void imprimeEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESREPORTE_H */

