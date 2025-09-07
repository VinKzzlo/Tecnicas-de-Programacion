/*
 *
 * Proyecto:    Lab1_25_1_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       1/09/2025
 *
 */

#ifndef LAB1_25_1_KV_FUNCIONESAUXILIARES_H
#define LAB1_25_1_KV_FUNCIONESAUXILIARES_H

void imprimeReporteProcesandoInfracciones();
int leerFecha();
int leerHora();
void imprimeFecha(int fecha);
void imprimeHora(int hora);
void procesarInfracciones(int fechaIni,int fechaFin);
void leeImprimeVehiculosCompania(int fechaIni,int fechaFin,double &montoTotalXCompania);
void imprimeLinea(char c);
void imprimeHeaderVehiculos();
void imprimeTipo_Placa_DevuelveIncremento(char tipoVehiculo,int placa1,int placa2,double &incrementoTipo);
void calculaIncrementosXFechaYHora(int fechaIni,int fechaFin,int fechaMulta, int horaMulta,
    double &incrementoFecha,double &incrementoHora);
void imprimeIncrementosAumentaMulta(double &montoMulta,double incrementoTipo,double incrementoFecha,double incrementoHora);
void imprimeGravedadDevuelveMulta(char gravedad,double &montoMulta);
void imprimeHeaderCompania(int dni, int numCompania);
#endif //LAB1_25_1_KV_FUNCIONESAUXILIARES_H