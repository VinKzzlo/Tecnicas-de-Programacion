/*
 *
 * Proyecto:    Lab5_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       6/10/2025
 *
 */

#ifndef LAB5_25_2_KV_FUNCIONESAUXILIARES_H
#define LAB5_25_2_KV_FUNCIONESAUXILIARES_H

void solicitaTarifa(double &tarifa);

void cargarCanales(const char *nombArch,int *arrCanalCodNum,char *arrCanalCodLet,double *arrCanalRating,int &cantCanales);
void cargarEtiquetas(const char *nombArch,int *arrEtiquetaCod,int *arrEtiquetaDuracion,int &cantEtiquetas);
void cargarEtiquetasEnCanales(const char *nombArch,int *arrEtiqCanNumCanal,char *arrEtiqCanLetCanal,int *arrEtiqCanCodEtiqueta,
    int &cantEtiquetasEnCanales);
int buscarEtiquetaEnCanal(char canalLet,int canalNum,int codEtiqueta,
    const char *arrEtiqCanLetCanal,const int *arrEtiqCanNumCanal,const int *arrEtiqCanCodEtiqueta,int cantEtiquetasEnCanales);
void imprimeReporteSimple(const char *nombArch, int *arrCanalCodNum,char *arrCanalCodLet,double *arrCanalRating,int cantCanales,
    int *arrEtiquetaCod,int *arrEtiquetaDuracion,int cantEtiquetas,
    int *arrEtiqCanNumCanal,char *arrEtiqCanLetCanal,int *arrEtiqCanCodEtiqueta, int cantEtiquetasEnCanales );

void imprimeHHMMSS(ofstream &archRep,int tiempoSegundos);
void imprimeMMSS(ofstream &archRep,int tiempoSegundos);
void ordenarEtiquetas(int *arrEtiquetaCod,int *arrEtiquetaDuracion,int cantEtiquetas);

void acumulaReproducciones(const char *nombArch,int *arrEtiqCanTotalRep,int *arrEtiqCanTiempoTotal,
        int *arrEtiqCanNumCanal,char *arrEtiqCanLetCanal,int *arrEtiqCanCodEtiqueta,int cantEtiquetasEnCanales,
        int *arrCanalCodNum,char *arrCanalCodLet,int cantCanales,
        int *arrEtiquetaCod,int *arrEtiquetaDuracion,int cantEtiquetas);

int buscarCanales(char letraCanal, int numeroCanal, int *arrCanalCodNum, char *arrCanalCodLet, int cantCanales);
int buscarEtiquetas(int codEtiqueta, int *arrEtiquetaCod, int cantEtiquetas);

void imprimeReporteFinal(const char *nombArch,
        int *arrCanalCodNum,char *arrCanalCodLet,double *arrCanalRating,int cantCanales,
        int *arrEtiquetaCod,int *arrEtiquetaDuracion,int cantEtiquetas,
        int *arrEtiqCanTotalRep,int *arrEtiqCanTiempoTotal,
        int *arrEtiqCanNumCanal,char *arrEtiqCanLetCanal,int *arrEtiqCanCodEtiqueta,int cantEtiquetasEnCanales, double tarifa);

void cambiarInt(int &datoI, int &datoJ);

void imprimeEncabezado(ofstream &archRep,double tarifa);
void imprimeLinea(ofstream &archRep,char c);
void imprimeDatosEtiqueta(ofstream &archRep, int num,int codEtiqueta,int duracionEtiqueta);
void imprimeEncabezadoCanales(ofstream &archRep);
void imprimeResumenEtiqueta(ofstream &archRep,int totalReproducciones,int tiempoTotalReproducido,
    double sumaRating,int contadorCanales,double tarifa);
#endif //LAB5_25_2_KV_FUNCIONESAUXILIARES_H