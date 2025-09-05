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

// Funcion que ayuda a la inicialización de archivos
void inicializarArchYEmitirReporte(const char *nombArchRep,
        const char *nombArchAlu,const char *nombArchEsc,const char *nombArchCur,
        const char *nombArchMat,int anio,int ciclo);

// Funciones auxiliadoras para diversos procesos
void procesarYEmitirReporte(ifstream &archAlu,ifstream &archCur,
        ifstream &archEsc,ifstream &archMat,ofstream &archRep,
        int anio,int ciclo);
void procesarMatricula(ifstream &archAlu,ifstream &archCur,ifstream &archEsc,
        ofstream &archRep,int codeAlum,double &totalPagado,int anio,int ciclo,
        ifstream &archMat);
void procesaCurso(ifstream &archCur,ofstream &archRep,int curso,double &monto,
        double &creditos,int cantCur,double escala);
void procesarResumen(ofstream &archRep,int cantAlu,double totalPagado);

// Funcion que determina el valor de la escala de un alumno
double determinarEscala(char tipoEscala,ifstream &archEsc,int anio,int ciclo);

// Funciones que ayudan a la impresion o cambio de datos
void imprimirCadena(ofstream &archRep,ifstream &archDatos,bool curso);
void imprimirAlumnoYDefinirEscala(int codeAlum,ifstream &archAlu,
        ofstream &archRep,char &escala);
void imprimirEncabezado(ofstream &archRep,int anio,int ciclo);
void imprimirSalto(ofstream &archRep,char c);
void cambiarCar(char &c,bool mayus);

// Funciones que ayudan a la lectura de datos
void ingresarFechas(int &anio,int &ciclo);

#endif /* FUNCIONESAUXILIARES_H */

