/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesReporte.h
 * Author: Alessandro Salvador Santé Vega - 20223006
 *
 * Created on 29 de abril de 2024, 07:19 PM
 */

#ifndef FUNCIONESREPORTE_H
#define FUNCIONESREPORTE_H

void emitirReporte(const char *nombArchCitas,const char *nombArchMedicinas,
                   const char *nombArchMedicos,const char *nombArchRep);

void leeImprimeDatosMedico(ifstream &archMedico,ofstream &archRep,
                           int &codMedico,double &tarifa);
void leeImprimeNombres(ifstream &archMedico,ofstream &archRep,char seleccion);
void imprimeEncabezadoCita(ofstream &archRep);
void leeValidaParaImprimirDatosCitas(int codMedico,double tarifa,
                    ifstream &archCit,ifstream &archMedicina,ofstream &archRep);
void validaImprimeMedicinas(ifstream &archCit,ifstream &archMedicina,ofstream &archRep);
void imprimeEncabezadoMedicinas(ofstream &archRep);
void calculaImprimePagoCita(double tarifa,int duracionEnS,double porcDcto,
                            double &pagoCita, ofstream &archRep);

int obtenerHora(ifstream &archCit);
void imprimeHora(int tiempoEnS, ofstream &archRep);

void imprimirEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESREPORTE_H */

