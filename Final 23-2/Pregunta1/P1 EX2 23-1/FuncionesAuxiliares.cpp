/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 20:50
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "FuncionesAuxiliares.h"
#include "Articulo.h"
#include "Vendedor.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 133

void leerArticulos(const char *nombArch,struct Articulo *articulos,int &numArt){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    char *codigo, *descripcion, c;
    double precio, stock;
    numArt = 0;
    while(true){
        codigo = leerCadenaExacta(arch,',');
        if(arch.eof())break;
        descripcion = leerCadenaExacta(arch,',');
        arch>>stock>>c>>precio;
        arch.get();
        articulos[numArt].codigo = codigo; 
        articulos[numArt].descripcion = descripcion; 
        articulos[numArt].stock = stock; 
        articulos[numArt].precio = precio; 
        numArt++;
   }
}
void mostrarArticulos(struct Articulo *articulos,int numArt,const char *nombArch){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    arch<<"LISTA DE ARTICULOS"<<endl;
    arch<<left<<setw(10)<<"CODIGO"<<setw(60)<<"DESCRIPCION PRODUCTO"<<setw(10)<<"STOCK"
        <<setw(10)<<"PRECIO"<<setw(14)<<"NUM VENDIDOS"<<setw(15)<<"MONTO VENDIDO"
        <<setw(17)<<"NUM NO VENDIDOS"<<setw(15)<<"MONTO PERDIDO"<<endl;
    for(int i=0;i<numArt;i++){
        arch<<left<<setw(10)<<articulos[i].codigo<<setw(60)<<articulos[i].descripcion
        <<right<<setw(5)<<articulos[i].stock<<setw(12)<<articulos[i].precio
        <<setw(12)<<articulos[i].cantVendidos<<setw(14)<<articulos[i].montoVendido
        <<setw(15)<<articulos[i].cantPerdidos<<setw(18)<<articulos[i].montoPerdido<<endl;
    }
}
void leerVendedores(const char *nombArch,struct Vendedor *vendedores,int &numVend){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double cuotaMin, porcVentas;
    char *nombre, c;
    numVend=0;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        nombre = leerCadenaExacta(arch,',');
        arch>>porcVentas>>c>>cuotaMin;
        vendedores[numVend].codigo = codigo;
        vendedores[numVend].nombre = nombre;
        vendedores[numVend].porcVentas = porcVentas;
        vendedores[numVend].cuotaMin = cuotaMin;
        vendedores[numVend].articulosVendidos = new struct ArticuloPedido[50]{};
        vendedores[numVend].articulosPerdidos = new struct ArticuloPedido[50]{};
        numVend++;
    }
}
void mostrarVendedores(struct Vendedor *vendedores,int numVend,const char *nombArch){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    arch<<setw((21+TAMLINEA)/2)<<"LISTADO DE VENDEDORES"<<endl;
    double pagoVendedor, pagoTodo, pagoPerdido;
    for(int i=0;i<numVend;i++){
        imprimeLinea(arch,'=');
        
        arch<<left<<setw(5)<<"No."<<setw(70)<<"VENDEDOR"<<setw(11)<<"% VENTAS"
            <<setw(15)<<"CUOTA MINIMA"<<setw(16)<<"TOTAL VENDIDO"<<setw(19)<<"TOTAL NO VENDIDO"<<endl;
        
        arch<<right<<setw(3)<<i+1<<") "<<vendedores[i].codigo<<"  "
            <<left<<setw(60)<<vendedores[i].nombre<<right<<setw(6)<<vendedores[i].porcVentas<<'%'
            <<setw(15)<<vendedores[i].cuotaMin<<setw(13)<<vendedores[i].montoTotalVendido
            <<setw(17)<<vendedores[i].montoTotalPerdido<<endl;
        
        reporteArticulos("ARTICULOS VENDIDOS", vendedores[i].articulosVendidos,
                         vendedores[i].cantArtVendidos,arch);
        reporteArticulos("ARTICULOS NO VENDIDOS", vendedores[i].articulosPerdidos,
                         vendedores[i].cantArtPerdidos,arch);
        
        pagoVendedor = (vendedores[i].montoTotalVendido-vendedores[i].cuotaMin)*
                        vendedores[i].porcVentas/100;
        if(pagoVendedor<0) pagoVendedor=0.0;
        
        pagoTodo = (vendedores[i].montoTotalVendido+vendedores[i].montoTotalPerdido-
                    vendedores[i].cuotaMin)*vendedores[i].porcVentas/100;
        if(pagoTodo<0) pagoTodo=0.0;
    
        pagoPerdido = vendedores[i].montoTotalPerdido*vendedores[i].porcVentas/100;
        
        arch<<endl<<left<<"TOTAL PAGADO AL VENDEDOR:"<<right<<setw(108)<<pagoVendedor<<endl;
        arch<<left<<"TOTAL PAGADO AL VENDEDOR SI SE HUBIERAN VENDIDO TODOS LOS PRODUCTOS:"
            <<right<<setw(65)<<pagoTodo<<endl;
        arch<<left<<"TOTAL PERDIDO POR FALTA DE STOCK:"<<right<<setw(100)<<pagoPerdido<<endl;
    }
}
void reporteArticulos(const char *titulo, struct ArticuloPedido *tipoArticulo,
                      int cantArt,ofstream &arch){
    
    arch<<setw(6)<<' '<<left<<titulo<<endl;
    arch<<setw(6)<<' '<<setw(5)<<"No."<<setw(11)<<"ARTICULO"<<setw(10)<<"CANTIDAD"
        <<setw(10)<<"MONTO"<<setw(20)<<"FECHA MAS RECIENTES"<<endl;
    
    for(int i=0;i<cantArt;i++){
        arch<<setw(6)<<' '<<right<<setw(2)<<i+1<<")  "<<left<<setw(8)<<tipoArticulo[i].codigo
            <<right<<setw(10)<<tipoArticulo[i].cantidad<<setw(10)<<tipoArticulo[i].montoTotal
            <<setw(10)<<tipoArticulo[i].fechaUltPed<<endl;
    }
}

void leerVentas(const char *nombArch,struct Articulo *articulos,int numArt,
                struct Vendedor *vendedores,int numVend){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codVend, cant, dd,mm,aa, fecha, posArt, posVend;
    double precio;
    bool vendido;
    char codArt[8],c ;
    while(true){
        arch>>codArt;
        if(arch.eof())break;
        arch>>codVend>>cant>>dd>>c>>mm>>c>>aa;
        fecha = aa*10000 + mm*100 + dd;
        posArt = buscarArticulo(codArt,articulos,numArt);
        posVend = buscarVendedor(codVend,vendedores,numVend);
        if(posArt != NO_ENCONTRADO and posVend != NO_ENCONTRADO){
            completarArticulo(articulos[posArt],cant,precio,vendido);
            completarVendedor(vendedores[posVend],codArt,cant,precio,fecha,vendido);
        }
    }
}

void completarArticulo(struct Articulo &articulo,int cant,
                       double &precio,bool &vendido){
    if(cant<=articulo.stock){
        articulo.stock -= cant;
        articulo.cantVendidos += cant;
        articulo.montoVendido += articulo.precio*cant;
        vendido = true;
    }
    else{
        articulo.cantPerdidos += cant;
        articulo.montoPerdido += articulo.precio*cant;
        vendido = false;
    }
    precio = articulo.precio;
}
void completarVendedor(struct Vendedor &vendedor,char *codArt,int cant,
                       double precio,int fecha,bool vendido){
    if(vendido){
        vendedor.montoTotalVendido += cant*precio;
        agregarVentas(codArt,precio,cant,fecha,vendedor.articulosVendidos,
                      vendedor.cantArtVendidos);
    }
    else{
        vendedor.montoTotalPerdido += cant*precio;
        agregarVentas(codArt,precio,cant,fecha,vendedor.articulosPerdidos,
                      vendedor.cantArtPerdidos);
    }
}
void agregarVentas(char *codArt,double precio,int cant,int fecha,
                   struct ArticuloPedido *articulosPed,int &cantArtP){
    int pos;
    pos = buscarArtEnVend(articulosPed,cantArtP,codArt);
    if(pos != NO_ENCONTRADO){
        articulosPed[pos].cantidad += cant;
        articulosPed[pos].fechaUltPed = fecha;
        articulosPed[pos].montoTotal += cant*precio;
        if(articulosPed[pos].fechaUltPed<fecha)
            articulosPed[pos].fechaUltPed = fecha;
    }
    else{
        articulosPed[cantArtP].codigo = new char[strlen(codArt)+1];
        strcpy(articulosPed[cantArtP].codigo,codArt);
        articulosPed[cantArtP].cantidad = cant;
        articulosPed[cantArtP].montoTotal = precio*cant;
        articulosPed[cantArtP].fechaUltPed = fecha;
        cantArtP++;
    }
}

int buscarArticulo(char *codArt,struct Articulo *articulos,int numArt){
    for(int i=0;i<numArt;i++)
        if(strcmp(codArt,articulos[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}
int buscarVendedor(int codVend,struct Vendedor *vendedores,int numVend){
    for(int i=0;i<numVend;i++)
        if(codVend == vendedores[i].codigo) return i;
    return NO_ENCONTRADO;
}

int buscarArtEnVend(struct ArticuloPedido *articulosPed,int cantArtP,char *cod){
    for(int i=0;i<cantArtP;i++)
        if(strcmp(cod,articulosPed[i].codigo)==0) return i;
    return NO_ENCONTRADO;
}

char* leerCadenaExacta(ifstream &arch,char delimitador){
    char buffer[100], *cadena;
    arch.getline(buffer,100,delimitador);
    if(arch.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

void imprimeLinea(ofstream &arch,char c){
    for(int i=0;i<TAMLINEA;i++)
        arch.put(c);
    arch<<endl;
}