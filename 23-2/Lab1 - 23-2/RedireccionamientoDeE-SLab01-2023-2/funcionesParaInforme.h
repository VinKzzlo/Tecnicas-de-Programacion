
/* 
 * File:   funcionesParaInforme.h
 * Author: Alessandro Santé Vega - 20223006
 * Created on 7 de abril de 2024, 22:26
 */

#ifndef FUNCIONESPARAINFORME_H
#define FUNCIONESPARAINFORME_H

void generarEImprimirReporte();
void imprimeDatosYProcesaEstad(int ,int ,int ,int ,int ,int ,
                                  int ,int ,char , int &, int &, 
                                 int  &, int &, int &, int &,
                int &, int &, int &, int &, int&, int &);

void imprimirEncabezado();
void imprimirLinea(char);
int convertirFechaUHora(char seleccion);

#endif /* FUNCIONESPARAINFORME_H */

