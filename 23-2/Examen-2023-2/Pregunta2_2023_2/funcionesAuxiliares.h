/* 
 * File:   main.cpp
 * Author:  Vicente Jorge
 * Código: 20222159
 * Created on 9 de octubre de 2023, 06:35 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <fstream>
using namespace std;

// Funciones / tareas principales

void leerAlum(const char *nombArch,int *arrCodeAlu,char *arrEscAlu,
        int &cantAlu);
void leerCur(const char *nombArch,int *arrCodeCur,double *arrCredCur,
        int &cantCur);
void leerEsc(const char *nombArch,int *arrAnioEsc,int *arrCicloEsc,
        char *arrTipoEsc,double *arrValorEsc,int &numEsc);
void emitirRepDeEscalas(const char *nombArch,int *arrAnioEsc,char *arrTipoEsc,
        int *arrCicloEsc,double *arrValorEsc,int numEsc);
void actualizacionMatricula(const char *nombArch,int *arrAnioEsc,
        int *arrCicloEsc,char *arrTipoEsc,int *cantAluEsc,double *cantCredEsc,
        double *totalIngresosEsc,int numEsc,int *arrCodeAlu,char *arrEscAlu,
        int *arrCodeCur,double *arrCredCur,int cantAlu,int cantCur,
        double *arrValorEsc);
void emitirReporte(const char *nombArch,int *arrAnioEsc,int *arrCicloEsc,
        char *arrTipoEsc,double *arrValorEsc,int *cantAluEsc,
        double *cantCredEsc,double *totalIngresosEsc,int numEsc);

void ordenarArrays(int *arrAnioEsc,int *arrCicloEsc,char *arrTipoEsc,
        double  *arrValorEsc,int *cantAluEsc,double *cantCredEsc,
        double *totalIngresosEsc,int numEsc);

// Funciones que permiten el cambio de variables

void cambiarInt(int &datoI,int &datoK);
void cambiarDouble(double &datoI,double &datoK);
void cambiarChar(char &datoI,char &datoK);

// Funcion que ayuda a procesar los cursos en la lectura de la matricula

void procesarCursos(ifstream &arch,int posEsc,int *arrCodeCur,
        double *arrCredCur,double *cantCredEsc,double *totalIngresosEsc,
        int cantCur,double *arrValorEsc);

// Funciones que buscan posiciones en arreglos

int buscarPosEsc(char escalaAlu,int *arrAnioEsc,int *arrCicloEsc,
        char *arrTipoEsc,int numEsc,int anio,int ciclo);
int buscaPosAlu(int *arrCodeAlu,int codeAlu,int cantAlu);
int buscarPosCur(int curso,int *arrCodeCur,int cantCur);

// Funcions que ayudan en la impresion de reportes

void imprimirSalto(ofstream &arch,char c);
void imprimirEncabezado(ofstream &arch);

#endif /* FUNCIONESAUXILIARES_H */

