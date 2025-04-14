/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 2:08
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void crearClientesBIN(const char *nombArchCSV,const char *nombArchBIN);
void crearLibrosBIN(const char *nombArchCSV,const char *nombArchBIN);
void actualizarLibrosConVentas(const char *nombArchVenta,const char *nombArchCli,
                               const char *nombArchLibro);
void completarArchivo(ifstream &archCli,fstream &archLib,int dniCli,char *codLib,
                      int dd,int mm,int aa,int calificacion);
void determinarFechaReciente(fstream &archLib);
void calcularRanking(fstream &archLib);
void ordenarLibros(const char *nombArchLibro);
void emitirReporte(const char *nombArchLibro,const char *nombArchRep);
void imprimeVentas(struct Venta *ventas,ofstream &archRep,int numVent);
void imprimeEncabezado(ofstream &archRep);
void imprimeLinea(ofstream &archRep, char c);
int cantidadRegistrosIfs(ifstream &arch,int tamReg);
int cantidadRegistrosFs(fstream &arch,int tamReg);

int buscarCliente(int dniCli,ifstream &archCli,int numRegC);
int buscarLibro(char *codLib,fstream &archLib,int numRegL);

void mostrarClientesBIN(const char *nombArch);
void mostrarLibrosBIN(const char *nombArch,const char *nombArchOut);
#endif /* FUNCIONESAUXILIARES_H */

