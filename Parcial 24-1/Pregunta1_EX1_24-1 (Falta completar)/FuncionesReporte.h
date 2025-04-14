/* 
 * Archivo:   FuncionesReporte.h
 * Autor: VinKzzlo
 *
 * Creado el on 25 de mayo de 2024, 23:46
 */

#ifndef FUNCIONESREPORTE_H
#define FUNCIONESREPORTE_H

void emitirReporteCitas(const char *nombArchCitas,const char *nombArchMedicinas,
                        const char *nombArchMedicos,const char *nombArchPacientes,
                        const char *nombArchReporte);



void leeImprimeDatosPaciente(int codPaciente,ifstream &archPac,
                             ofstream &archRep, double &porcDcto);
void procesaCitas(int codPaciente,double porcDcto,ifstream &archCita,
                  ifstream &archMeds,ifstream &archMedici,ofstream &archRep);

int obtenerHora(ifstream &archCita);
void imprimeHora(int duracionEnS,ofstream &archRep);
void imprimeNombres(ifstream &archIn,ofstream &archRep, char seleccion);

void imprimeEncabezados(ofstream &archRep,char seleccion);
void imprimeLinea(ofstream &archRep,char c);

#endif /* FUNCIONESREPORTE_H */

