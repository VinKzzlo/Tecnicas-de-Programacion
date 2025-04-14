/* 
 * File:   FuncionesParaReporte.h
 * Autor:  VinKzzlo
 *
 * Creado el 14 de abril de 2024, 1:40
 */

#ifndef FUNCIONESPARAREPORTE_H
#define FUNCIONESPARAREPORTE_H

void EmitirReporte();

void imprimeYProcesaDatos(int ,int ,int ,int ,int ,int ,
     double ,char ,char ,double ,
     double &,int &,int &,
     int &,int &,int &,double &,
     double &,int &);


void imprimirHora(int);
void imprimirCategoria(int, char ,bool &, bool &,bool &);
void imprimirMonto(double ,double ,double , double &);

int convertirHora();

void imprimirEncabezado();
void imprimirLinea(char);

#endif /* FUNCIONESPARAREPORTE_H */