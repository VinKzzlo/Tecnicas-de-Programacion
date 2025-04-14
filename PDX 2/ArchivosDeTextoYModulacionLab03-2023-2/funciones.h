
/*/ 
 * Projecto:  ArchivosDeTextoYModulacionLab03-2023-2
 * Nombre del Archivo:  funciones.h
 * Autor: El EnTrEvErAdO
/*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

                /*  - / > [ Declaracion de Funciones ] < / -  */

void emitirReporte(const char *,const char *,const char *,const char *);

void procesarNombreDeCanal(ofstream &,ifstream &);

void procesarRegistrosDeTelevidentes(ofstream &,ifstream &,ifstream &,int);

void procesarDatosDeTelevidente(ofstream &,ifstream &,int,int,int,int &,int &,
                                int &,int &,int &);

void emitirResumenParcial(ofstream &,int,int,int,int,int);

void procesarNombreDeTelevidente(ofstream &,ifstream &);

char obtenerCategoria(ifstream &);

void imprimirRegistro(ofstream &,char,char,char,int,int,int &,int &,int &,int &,
                      int &);

ifstream abrirArchivo_IFS(const char *);

ofstream abrirArchivo_OFS(const char *);

int obtenerHora(ifstream &);

void imprimirHora(ofstream &,int);

void imprimirEncabezados(ofstream &,char);

void imprimirLinea(ofstream &,int,char);

#endif /* FUNCIONES_H */
