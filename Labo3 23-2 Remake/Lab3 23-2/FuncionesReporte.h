/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesReporte.h
 * Autor: VinKzzlo
 *
 * Creado el on 28 de abril de 2024, 18:53
 */

#ifndef FUNCIONESREPORTE_H
#define FUNCIONESREPORTE_H

void emitirReportePreferencias(const char *nombArchCan,const char *nombArchPref,
                              const char *nombArchTelv,const char *nombArchRep);

void buscaImprimeTelevidentes(int canalEvaluar,ifstream &archPref,ifstream &archTel,
                              ofstream &archRep,
                int &nroMen, int &nroJov, int &nroAdu, int &nroTel, int &timeT);
int obtenerHora(ifstream &archPref);

void imprimeDatosCliente(int nroDNI,int horaI,int horaF,int duracionEnS,
                         ifstream &archTel,ofstream &archRep, int &nroTel,
                         int &nroMen, int &nroJov, int &nroAdu);
void imprimeNombreCliente(ifstream &archTel,ofstream &archRep);
void obtenerFechaNac(ifstream &archTel,int &fechaNacConvert,
                     int &nroMen,int &nroJov,int &nroAdu,
                     bool &menor,bool &joven, bool &adulto);
void leeImprimeSexo(ifstream &archTel, ofstream &archRep);
void imprimeCategoria(ofstream &archRep,bool menor,bool joven,bool adulto);
void leeImprimeCompania(ifstream &archTel,ofstream &archRep);
void imprimeHora(int tiempoEnS, ofstream &archRep);
void imprimeEncabezadoCanal(ifstream &archCan,ofstream &archRep,
                            int &canalEvaluar);
void imprimeNombreCanal(ifstream &archCan,ofstream &archRep);

void imprimeEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);

#endif /* FUNCIONESREPORTE_H */

