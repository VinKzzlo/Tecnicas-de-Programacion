    /*
 *
 * Proyecto:    Lab1_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       14/09/2025
 *
 */

#ifndef LAB1_25_2_KV_FUNCIONESAUXILIARES_H
#define LAB1_25_2_KV_FUNCIONESAUXILIARES_H

void procesaImprimeReporteTPTwitch();
void procesaInformacionPorCanal(int fechaCreacion,int numCanales,int &cantStreamsTotal,int &duracionTotalStreams,
                double &ingresosTotalesPorPubli,double &mejorIngresoCanal,int &numericoCodigoMejor,char &letraCodigoMejor);
void leeImprimeStreamsDelCanal(int &duracionTotal,int &ultimaPubli,int &totalReproducciones,double &ingresoPublicidad,
    int &cantStreamsTotal);
void imprimeResumenCanal(int duracionTotal,int ultimaPubli,int totalReproducciones,double ingresoPublicidad);
void imprimeResumenFinal(int cantStreamsTotal,int duracionTotalStreams,double ingresosTotalesPorPubli,
    double mejorIngresoCanal,int numericoCodigoMejor,char letraCodigoMejor);

void leeImprimeNombreEnMayus();
void imprimeEncabezadoTwitch();
void imprimeEncabezadoCanal(int numCanales);
void imprimeEncabezadoReproducciones();
int leeFecha();
int leeHora();
void imprimeFecha(int fecha);
void imprimeHora(int tiempoEnSeg);
void imprimeLinea(char car);

#endif //LAB1_25_2_KV_FUNCIONESAUXILIARES_H