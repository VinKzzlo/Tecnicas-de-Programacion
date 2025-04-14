/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesParaReporte.h
 * Autor: VinKzzlo
 *
 * Creado el on 26 de abril de 2024, 21:31
 */

#ifndef FUNCIONESPARAREPORTE_H
#define FUNCIONESPARAREPORTE_H

void emitirReporte(const char *nombArchCitas, const char *nombArchMedicos,
                   const char *nombArchRep);

void leeImprimeDatosCita(ifstream &archCitas,ifstream &archMed,
                         ofstream &archRep, double &ingresosTotales,
                        int &codPacienteMax, double &pagoPacienteMax);
void hallaPacienteGastoMax(int codPaciente, double pagoRealizado,
                           int &codPacienteMax, double &pagoPacienteMax);
void buscaImprimeDatosMedicoRetornaTarifa(int codMedico,ifstream &archMed,
                                          ofstream &archRep, double &tarifaH);
void imprimeNombreEspMedico(ifstream &archMed,ofstream &archRep,char seleccion);
void imprimePagoSumaIngresos(double tarifaH,double duracionEnH,double pagoMedicinas,
                             double porcDcto, ofstream &archRep,double &ingresosTotales,
                             double &pagoRealizado);

int leeHoraConvierteASeg(ifstream &archCitas);
void imprimeHora(int horaEnS, ofstream &archRep);

void imprimirEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESPARAREPORTE_H */

