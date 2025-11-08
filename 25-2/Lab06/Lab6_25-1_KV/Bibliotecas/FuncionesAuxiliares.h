/*
 *
 * Proyecto:    Lab6_25_1_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       3/11/2025
 *
 */

#ifndef LAB6_25_1_KV_FUNCIONESAUXILIARES_H
#define LAB6_25_1_KV_FUNCIONESAUXILIARES_H

void cargarCategorias(const char *nombArch,char **arrCategoriaCodigo,char **arrCategoriaNombre,int &cantCategorias);
void verificarCategorias(const char *nombArch,char **arrCategoriaCodigo,char **arrCategoriaNombre,int cantCategorias);
void cargarStreams(const char *nombArch, int *arrStreamFecha,int *arrStreamDuracion,char **arrStreamNombCanal,char **arrStreamCodCategoria,
        double *arrStreamRating, double *arrStreamTasaDrop, int &cantStreams);
void verificarStreams(const char *nombArch, int *arrStreamFecha,int *arrStreamDuracion,char **arrStreamNombCanal,char **arrStreamCodCategoria,
        double *arrStreamRating, double *arrStreamTasaDrop, int cantStreams);
void emitirReportesCategoriasStreams(char **arrCategoriaCodigo,char **arrCategoriaNombre,int cantCategorias,
        int *arrStreamFecha,int *arrStreamDuracion,char **arrStreamNombCanal,char **arrStreamCodCategoria,
        double *arrStreamRating, double *arrStreamTasaDrop, int cantStreams);
void imprimeReporte(char *codCategoria,char *nombreCategoria, const char *nombArch,const char *enlace,
        int *arrStreamFecha,int *arrStreamDuracion,char **arrStreamNombCanal,char **arrStreamCodCategoria,
        double *arrStreamRating, double *arrStreamTasaDrop, int cantStreams);
void generaArchivoEnlace(const char *categoria, char *&nombArch, char *&enlace);
char *leeCadenaExacta(ifstream &archIn, char delim = '\n');
int leerHora(ifstream &archIn);
void imprimeHora(ofstream &archRep, int tiempoSegundos);
void imprimeFecha(ofstream &archRep, int fecha);
void imprimeLinea(ofstream &archRep, char car, int size);
#endif //LAB6_25_1_KV_FUNCIONESAUXILIARES_H