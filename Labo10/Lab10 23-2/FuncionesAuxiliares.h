/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 23 de junio de 2024, 18:16
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerArticulosAlmacenaBIN(const char *nombArchTxt,const char *nombArchBin);
void leerVendedoresAlmacenaBIN(const char *nombArchTxt,const char *nombArchBin);
void actualizarVentas(const char *nombArchArt,const char *nombArchVend,
                      const char *nombArchVent);
void corregirVendedores(const char *nombArchVend);
void ordenarVendedores(const char *nombArchVend);
void emitirReporte(const char *nombArchArt,const char *nombArchVend,
                   const char *nombArchRep);
void modificarArticulos(fstream &archArt,int tamRegArt,char *codigoArt,
                        int cant,int posArt,double &precio);
void modificarVendedor(fstream &archVend,int tamRegVend,char *codigoArt,
                       int codigoVend,int cant,int posVend,double precio);
int buscarArticulo(char *codigoArt,fstream &archArt,int numRegArt);
int buscarVendedor(int codigoVend,fstream &archVend,int numRegVend);
int buscarArticuloEnVendedor(struct ArticuloVendido *artVendidos,char *codigoArt,
                             int numArtVend);

void pasarMayus(char *descripcion);
void modificarCadena(char *nombre);




void mostrarArchivoBinarioArt(const char *nombArchBin);
void mostrarArchivoBinarioVend(const char *nombArchBin);
void datosDelArchivoArt(ifstream &archBin,int &tamArch,int &tamReg,int &numReg);
void datosDelArchivoVend(ifstream &archBin,int &tamArch,int &tamReg,int &numReg);
void datosDelArchivoArtF(fstream &archBin,int &tamArch,int &tamReg,int &numReg);
void datosDelArchivoVendF(fstream &archBin,int &tamArch,int &tamReg,int &numReg);
#endif /* FUNCIONESAUXILIARES_H */

