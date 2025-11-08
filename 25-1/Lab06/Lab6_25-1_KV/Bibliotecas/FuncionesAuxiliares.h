/*
 *
 * Proyecto:    Lab6_25_1_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       1/11/2025
 *
 */

#ifndef LAB6_25_1_KV_FUNCIONESAUXILIARES_H
#define LAB6_25_1_KV_FUNCIONESAUXILIARES_H

void leerTablaInfraccioness(const char *nombArch, int *arrCodigoInfraccion,double *arrMultasInfraccion,int &cantInfracciones);
void insertarOrdenado(int codigo,double multa,int &cantInfracciones,int *arrCodigoInfraccion,double *arrMultasInfraccion);
void comprobarLecturaInfracciones(const char *nombArch, int *arrCodigoInfraccion,double *arrMultasInfraccion,int cantInfracciones);

void leerInfraccionesCometidas(const char *nombArchIn,const char *nombArchRep,
        int *arrCodigoInfraccion,double *arrMultasInfraccion,int cantInfracciones,
        int *arrDni, int *arrMasMultaAntigua, int*arrUltimaPendiente,
        double *arrTotalMultas,double *arrTotalPagadas,double *arrTotalPendientes,int &cantRepresentantes);
void escribirLineaEnArchivoPlacas(ofstream &archRep, int dni, char *placa);

int leerFecha(ifstream &archIn);
void saltarCadenas(ifstream &archIn, char delim);

#endif //LAB6_25_1_KV_FUNCIONESAUXILIARES_H