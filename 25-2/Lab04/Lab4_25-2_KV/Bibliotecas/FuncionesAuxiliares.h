/*
 *
 * Proyecto:    Lab4_25_2_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       4/10/2025
 *
 */

#ifndef LAB4_25_2_KV_FUNCIONESAUXILIARES_H
#define LAB4_25_2_KV_FUNCIONESAUXILIARES_H

void solicitarTarifa(double &tarifa);

void cargarArreglosCanales(const char *nombArch, int *arrCanalFechaCreacion,int *arrCanalCodNum,
    double *arrCanalRating, char *arrCanalCodLetra,int *arrCanalPorcentaje,int &cantCanales);
void cargarArreglosEtiquetas(const char *nombArch,int *arrEtiqCod,int *arrEtiqDuracion,int &cantEtiquetas);

void imprimeReportePrueba(const char *nombArch,
                        int *arrCanalFechaCreacion,int *arrCanalCodNum,double *arrCanalRating,char *arrCanalCodLetra, int *arrCanalPorcentaje,int cantCanales,
                        int *arrEtiqCod,int *arrEtiqDuracion, int cantEtiquetas);

void procesarReproduccionesEtiquetas(const char *nombArch,
        char *arrCanalCodLetra,int *arrCanalCodNum,double *arrCanalRating, int *arrCanalPorcentaje,
        int *arrCanalNumRepro,int *arrCanalTiempoRepro, double *arrCanalIngresos,int cantCanales,
        int *arrEtiqCod,int *arrEtiqDuracion,int *arrEtiqNumRepro,int *arrEtiqTiempoRepro,int cantEtiquetas,double tarifa);

void actualizarArreglosCanales(double ratingCanal,int porcentajeIntRating,int &numReprodCanal,
                int &tiempoReproCanal,double &ingresosCanal,int numReproducciones,int duracionEtiqueta,double tarifa);
void actualizarArreglosEtiquetas(int &etiqNumRepro, int &etiqTiempoRepro,int duracionEtiqueta, int numReproducciones);

void imprimirReporteFinal(const char *nombArch,
        int *arrCanalCodNum,int *arrCanalFechaCreacion,int *arrCanalPorcentaje,int *arrCanalNumRepro,int *arrCanalTiempoRepro,
        double *arrCanalRating,double *arrCanalIngresos,char *arrCanalCodLetra,int cantCanales,
        int *arrEtiqCod,int *arrEtiqDuracion,int *arrEtiqNumRepro,int *arrEtiqTiempoRepro,int cantEtiquetas,double tarifa);

int buscarCanal(const char *arrCanalCodLetra,const int *arrCanalCodNum,char codCanalLet,int codCanalNum,int cantCanales);
int buscarEtiqueta(const int *arrEtiqCod, int codEtiqueta,int cantEtiquetas);

void imprimeFecha(ofstream &archRep, int fecha);
void imprimeHora(ofstream &archRep, int tiempoSegundos);
void imprimeMMSS(ofstream &archRep, int tiempoSegundos);
void imprimeEncabezado(ofstream &archRep,double tarifa);
void imprimeLinea(ofstream &archRep, char car);
void imprimeEncabezadoCanales(ofstream &archRep);
void imprimeEncabezadoEtiquetas(ofstream &archRep);

#endif //LAB4_25_2_KV_FUNCIONESAUXILIARES_H