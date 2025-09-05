
/*/ 
 * Projecto:  TPX_L1
 * Nombre del Archivo:  funciones.h
 * Autor: Critical Cyndx
/*/

#ifndef FUNCIONES_H
#define FUNCIONES_H
// Funciones en Main
void emitirReporte(void);


// Funciones Principales
void procesarImprimirDatos(int,int,int,int,int,int,int,char,char,int &,int &,
                int &,int &,int &,int &,int &,int &,int &,int &,int &,int &);
void imprimirResumen(int,int,int,int,int,int,int,int,int,int,int,int,int);


// Funciones Secundarias
void imprimirSexo(int,char,bool &,bool &,int &,int &);
void imprimirCategoria(int,int,bool &,bool &,bool &,int &,int &);
void imprimirCanales(int,int,int,int,int &);
void imprimirCompania(int,char);
void validarCondiciones(bool,bool,bool,bool,bool,int,int,int,int,int,int,
                char,int &,int &,int &,int &,int &,int &,int &);


// Funciones Derivadas
void cuartaCondicionValidada(int,int,int,int &);


// Funciones Auxiliares
void imprimirEncabezado(void);
void imprimirLinea(int,char);
int obtenerFecha_Hora(char);
void imprimirHora(int);

#endif /* FUNCIONES_H */
