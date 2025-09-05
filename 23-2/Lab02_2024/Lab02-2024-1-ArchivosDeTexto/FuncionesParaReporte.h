/* 
 * File:   FuncionesParaReporte.h
 * Autor:  Alessandro Salvador Santé Vega - 20223006
 * Created on 15 de abril de 2024, 07:16 PM
 */

#ifndef FUNCIONESPARAREPORTE_H
#define FUNCIONESPARAREPORTE_H

void generarReporte(const char *nombArchDatos,const char *nombArchRep);

void imprimeYProcesaDatos(ofstream &archRep,int dd,int mm,int aa,int nroDNI,
                          int horaI, int horaF, int duracionEnS, 
                          double porcentDcto, double tarifPorH,
                          double pagoMedicinas, double &totalIngresos);
void imprimePagoYSumaIngresos(ofstream &archRep,double tarifPorH,double duracionEnH,
                              double pagoMedicinas, double &totalIngresos);
void imprimirEstadisticas(ofstream &archRep,int nroRegistros,int nroRegProc);

int convertirHora(ifstream &archDat);
void imprimeHora(ofstream &archRep,int tiempoEnS);

void imprimirEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char caracter);


#endif /* FUNCIONESPARAREPORTE_H */

