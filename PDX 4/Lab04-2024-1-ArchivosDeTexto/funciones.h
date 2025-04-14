
/*/ 
 * Projecto:  Lab04-2024-1-ArchivosDeTexto
 * Nombre del Archivo:  funciones.h
 * Autor: Super Spaghetti X
/*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

                /*  - / > [ Declaracion de Funciones ] < / -  */

void emitirReporte(const char *,const char *,const char *,const char *);

void procesarCitasRealizadas(ofstream &,ifstream &,ifstream &,int,double,int &,
                             double &);

void procesarResumenGeneral(ofstream &,ifstream &,int,double);

void imprimirDatosDeCita(ofstream &,int,int,int,int,double,double,double,
                         double &);

void procesarMedicinasRecetadas(ofstream &,ifstream &,ifstream &,double,
                                double &);

void procesarResumenParcial(ofstream &,int,double,double,int &,double &);

ifstream abrirArchivo_IFS(const char *);

ofstream abrirArchivo_OFS(const char *);

void imprimirEncabezado(ofstream &,char);

void imprimirLinea(ofstream &,int,char);

void procesarNombreDeMedico(ofstream &,ifstream &);

void procesarEspecialidadDeMedico(ofstream &,ifstream &);

void procesarDescripcionDeMedicina(ofstream &,ifstream &);

int obtenerHora(ifstream &);

void imprimirFecha(ofstream &,int);

void imprimirHora(ofstream &,int);

#endif /* FUNCIONES_H */
