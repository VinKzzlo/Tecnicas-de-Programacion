/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 20:49
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerArticulos(const char *nombArch,struct Articulo *articulos,int &numArt);
void mostrarArticulos(struct Articulo *articulos,int numArt,const char *nombArch);
void leerVendedores(const char *nombArch,struct Vendedor *vendedores,int &numVend);
void mostrarVendedores(struct Vendedor *vendedores,int numVend,const char *nombArch);
void reporteArticulos(const char *titulo, struct ArticuloPedido *tipoArticulo,
                      int cantArt,ofstream &arch);
void leerVentas(const char *nombArch,struct Articulo *articulos,int numArt,
                struct Vendedor *vendedores,int numVend);
int buscarArticulo(char *codArt,struct Articulo *articulos,int numArt);
int buscarVendedor(int codVend,struct Vendedor *vendedores,int numVend);
void completarArticulo(struct Articulo &articulo,int cant,
                       double &precio,bool &vendido);
void completarVendedor(struct Vendedor &vendedor,char *codArt,int cant,
                       double precio,int fecha,bool vendido);
void agregarVentas(char *codArt,double precio,int cant,int fecha,
                   struct ArticuloPedido *articulosPed,int &cantArtP);
int buscarArtEnVend(struct ArticuloPedido *articulosPed,int cantArtP,char *cod);
char* leerCadenaExacta(ifstream &arch,char delimitador);
void imprimeLinea(ofstream &arch,char c);
#endif /* FUNCIONESAUXILIARES_H */

