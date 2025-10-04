/*
 *
 * Proyecto:    Lab2_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       18/09/2025
 *
 */

#ifndef LAB2_25_2_KV_FUNCIONESAUXILIARES_H
#define LAB2_25_2_KV_FUNCIONESAUXILIARES_H

void solicitaFechasYTarifas(int &fechaIni,int &fechaFin,double &tarifaPubli,double &tarifaDuracion);
void procesaImprimeRegistroCanalesAfiliados(const char *nombArchTwitch,const char *nombArchReporte,
                                            int fechaIni,int fechaFin,double tarifaPubli,double tarifaDuracion);
void imprimeEncabezado(ofstream &archRep, int fechaIni, int fechaFin, double tarifaPubli, double tarifaDuracion);
void imprimeFecha (ofstream &archRep, int fecha);

#endif //LAB2_25_2_KV_FUNCIONESAUXILIARES_H