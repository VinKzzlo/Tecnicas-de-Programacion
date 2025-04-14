/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Author: aml
 *
 * Created on 17 de junio de 2024, 07:18 PM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerClientes(const char *nombArch,struct Cliente *arrClientes,int &numClientes);
void leerLibros(const char *nombArch,struct Libro *arrLibros,int &numLibros);
void actualizarVentas(const char *nombArch,struct Libro *arrLibros,int numLibros);
void ordenarLibros(struct Libro *arrLibros,int numLibros);
void emitirReporte(const char *nombArch,struct Libro *arrLibros,int numLibros,
                   struct Cliente *arrClientes,int numClientes);
void imprimeClientes(struct Venta *ventas,int numVentas,struct Cliente *arrClientes,
                     int numClientes,ofstream &arch);
void cambiarLibros(struct Libro &libroI,struct Libro &libroJ);
int buscarLibro(char *codigo,struct Libro *arrLibros,int numLibros);
void actualizarFecha(struct Fecha fecha,int dd,int mm, int aa);
void determinarRanking(struct Libro *arrLibros,int numLibros);
char* leerCadenaExacta(ifstream &arch,char delimitador);
void leerFecha(ifstream &arch,int &dd,int &mm,int &aa);
void imprimeEncabezado(ofstream &arch);
void imprimeLinea(ofstream &arch,char c);
#endif /* FUNCIONESAUXILIARES_H */

