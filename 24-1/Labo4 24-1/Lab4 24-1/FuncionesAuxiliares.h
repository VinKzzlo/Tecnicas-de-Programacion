/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 5 de mayo de 2024, 14:01
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void emiteReporteCitasMedicas(const char *nombArchCitas,const char *nombArchMedici,
                              const char *nombArchMedico, const char *nombArchRep);
void leeImprimeDatosMedico(ifstream &archMedico,ofstream &archRep,
                           int &codMedico, double &tarifa);
void leeImprimeDatosPacientes(int codMedico,double tarifa,
                              ifstream &archCitas,ifstream &archMedici,
                              ofstream &archRep, int &codMedMAX, double &pagoMedMAX);
void leeImprimeMedicinasRecetadas(double porcDcto,ifstream &archCitas,
                                  ifstream &archMedici,ofstream &archRep,
                                  double &pagoMedicinas);
void imprimePagos(double pagoMedicinas,double pagoTotal, ofstream &archRep);

void imprimeDatosPaciente(int fecha, int nroDNI,int horaI,int horaF,int duracion,
                          double porcDcto,double tarifa,
                          ofstream &archRep,double &pagoCita);
void calculaImprimePagoCita(double tarifa, int duracion,double porcDcto,
                            ofstream &archRep,double &pagoCita);
void imprimeEncabezadoPaciente(ofstream &archRep);

void imprimeFecha(int fecha,ofstream &archRep);

void imprimeEncabezadoMedicinas(ofstream &archRep);

int obtenerHora(ifstream &archCitas);
void imprimeHora(int timeInS,ofstream &archRep);
void imprimeNombres(ifstream &archLectura,ofstream &archRep,char seleccion);

void imprimeEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESAUXILIARES_H */

