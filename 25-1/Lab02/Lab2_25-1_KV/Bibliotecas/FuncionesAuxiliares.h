/*
 *
 * Proyecto:    Lab2_25_1_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       15/09/2025
 *
 */

#ifndef LAB2_25_1_KV_FUNCIONESAUXILIARES_H
#define LAB2_25_1_KV_FUNCIONESAUXILIARES_H

void imprimeReporteMultasCompanias(const char *nombArchInfracciones, const char *nombArchMultas,
    const char *nombArchReporte);
void leeImprimeVehiculosMultas(ifstream &archInfra,ifstream &archMultas,ofstream &archRep,
    int &cantLeves,int &cantGraves,int &cantMuyGraves,double &montoLeves,double &montoGraves,double &montoMuyGraves);
void imprimeDatosInfraccionVehiculo(ofstream &archRep,char tipoVehiculo,int numPlaca1,int numPlaca2,int fechaInfraccion);
void imprimeResumenParcial(ofstream &archRep,int cantLeves,int cantGraves,int cantMuyGraves,
    double montoLeves,double montoGraves,double montoMuyGraves);
void imprimeDetalleMulta(ifstream &archMultas,ofstream &archRep,int codigoMulta,
            int &cantLeves, int &cantGraves, int &cantMuyGraves,
            double &montoLeves, double &montoGraves, double &montoMuyGraves);
void imprimeGravedad(ofstream &archRep, char tipoMulta);
void imprimeEncabezado(ofstream &archRep);
void imprimeHeaderInfracciones(ofstream &archRep);
void imprimeLinea(ofstream &archRep,char c,int size);
void imprimeHeaderCompania(ifstream &archInfra, ofstream &archRep, int dni, int cant);
void leeImprimeCadenas(ifstream &archIn, ofstream &archRep, bool finDeLinea);
void leeImprimeDescripcion(ifstream &archIn, ofstream &archRep);
int leeFecha(ifstream &archIn);
void imprimeFecha(ofstream &archRep, int fecha);
void actualizaAcumuladores(char tipoMulta,double montoMulta,
    int &cantLeves,int &cantGraves,int &cantMuyGraves,double &montoLeves,double &montoGraves,double &montoMuyGraves);

#endif //LAB2_25_1_KV_FUNCIONESAUXILIARES_H