/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 23 de junio de 2024, 18:16
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "Articulo.h"
#include "Vendedor.h"
#include "FuncionesAuxiliares.h"
#define TAMLINEA
#define NO_ENCONTRADO -1

void leerArticulosAlmacenaBIN(const char *nombArchTxt,const char *nombArchBin){
    ifstream archTxt(nombArchTxt,ios::in);
    if(not archTxt.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchTxt<<endl;
        exit(1);    
    }
    ofstream archBin(nombArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchBin<<endl;
        exit(1);    
    }
    
    struct Articulo articulo{};
    double precio;
    char codigo[8],descripcion[60];
    while(true){
        archTxt.getline(codigo,8,',');
        if(archTxt.eof())break;
        archTxt.getline(descripcion,60,',');
        archTxt>>precio;
        pasarMayus(descripcion);
        strcpy(articulo.codigo,codigo);
        strcpy(articulo.descripcion,descripcion);
        articulo.precio = precio;
        archBin.write(reinterpret_cast<const char*>(&articulo),
                      sizeof(struct Articulo));
        archTxt.get();
    }
}

void leerVendedoresAlmacenaBIN(const char *nombArchTxt,const char *nombArchBin){
    ifstream archTxt(nombArchTxt,ios::in);
    if(not archTxt.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchTxt<<endl;
        exit(1);    
    }
    ofstream archBin(nombArchBin,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchBin<<endl;
        exit(1);    
    }
    struct Vendedor vendedor{};
    int codigo;
    double porcVentas, cuotaMin;
    char nombre[60], c;
    while(true){
        archTxt>>codigo;
        if(archTxt.eof())break;
        archTxt.get();
        archTxt.getline(nombre,60,',');
        archTxt>>porcVentas>>c>>cuotaMin;
        vendedor.codigo = codigo;
        modificarCadena(nombre);
        strcpy(vendedor.nombre,nombre);
        vendedor.porcVentas = porcVentas;
        vendedor.cuotaMin = cuotaMin;
//        vendedor.superoCuota = true;
        archBin.write(reinterpret_cast<const char*>(&vendedor),
                      sizeof(struct Vendedor));
    }
}

void actualizarVentas(const char *nombArchArt,const char *nombArchVend,
                      const char *nombArchVent){
    fstream archArt(nombArchArt, ios::in|ios::out|ios::binary);
    if(not archArt.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchArt<<endl;
        exit(1);    
    }
    fstream archVend(nombArchVend, ios::in|ios::out|ios::binary);
    if(not archVend.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchVend<<endl;
        exit(1);    
    }
    ifstream archVenta(nombArchVent,ios::in);
    if(not archVenta.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchVent<<endl;
        exit(1);    
    }
    int tamArchArt,tamRegArt,numRegArt,tamArchVend,tamRegVend,numRegVend;
    datosDelArchivoArtF(archArt,tamArchArt,tamRegArt,numRegArt);
    datosDelArchivoVendF(archVend,tamArchVend,tamRegVend,numRegVend);
    int codigoVend, cant, posArt, posVend;
    double precio;
    char codigoArt[8];
    while(true){
        archVenta>>codigoArt;
        if(archVenta.eof())break;
        archVenta>>codigoVend>>cant;
        posArt = buscarArticulo(codigoArt,archArt,numRegArt);
        posVend = buscarVendedor(codigoVend,archVend,numRegVend);
        if(posArt != NO_ENCONTRADO and posVend != NO_ENCONTRADO){
            modificarArticulos(archArt,tamRegArt,codigoArt,cant,posArt,precio);
            modificarVendedor(archVend,tamRegVend,codigoArt,codigoVend,cant,posVend,precio);
        }
    }
    
}

void modificarArticulos(fstream &archArt,int tamRegArt,char *codigoArt,
                        int cant,int posArt,double &precio){
    struct Articulo articulo;
    archArt.seekg((posArt)*tamRegArt,ios::beg);
    archArt.read(reinterpret_cast<char*>(&articulo),tamRegArt);
    precio = articulo.precio;
    articulo.cantVendido += cant;
    articulo.montoVendido +=precio*cant;
    archArt.seekg((posArt)*tamRegArt,ios::beg);
    archArt.write(reinterpret_cast<const char*>(&articulo),tamRegArt);
    archArt.flush();
}

void modificarVendedor(fstream &archVend,int tamRegVend,char *codigoArt,
                       int codigoVend,int cant,int posVend,double precio){
    struct Vendedor vendedor;
    int posArt, na;
    archVend.seekg((posVend)*tamRegVend,ios::beg);
    archVend.read(reinterpret_cast<char*>(&vendedor),tamRegVend);
    posArt = buscarArticuloEnVendedor(vendedor.artVendidos,codigoArt,vendedor.numArtVend);
    if(posArt != NO_ENCONTRADO){
        vendedor.artVendidos[posArt].cantVendido += cant;
        vendedor.artVendidos[posArt].montoVendido += precio*cant;
        vendedor.artVendidos[posArt].pagoRecibido += cant*precio*(vendedor.porcVentas/100);
    }
    else{
        na = vendedor.numArtVend;
        strcpy(vendedor.artVendidos[na].codigo,codigoArt);
        vendedor.artVendidos[na].cantVendido += cant;
        vendedor.artVendidos[na].montoVendido += precio*cant;
        vendedor.artVendidos[na].pagoRecibido += cant*precio*(vendedor.porcVentas/100);
        vendedor.numArtVend++;
    }
    archVend.seekg((posVend)*tamRegVend,ios::beg);
    archVend.write(reinterpret_cast<const char*>(&vendedor),tamRegVend);
    archVend.flush();
}

void corregirVendedores(const char *nombArchVend){
    fstream archVend(nombArchVend, ios::in|ios::out|ios::binary);
    if(not archVend.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchVend<<endl;
        exit(1);    
    }
    struct Vendedor vendedor;
    int tamArchVend,tamRegVend,numRegVend;
    datosDelArchivoVendF(archVend,tamArchVend,tamRegVend,numRegVend);
    for(int i=0;i<numRegVend;i++){
        archVend.read(reinterpret_cast<char*>(&vendedor),tamRegVend);
        for(int j=0;j<vendedor.numArtVend;j++){
            vendedor.montoVend += vendedor.artVendidos[j].montoVendido;
        }
        if(vendedor.montoVend<=vendedor.cuotaMin){
            vendedor.montoVend = 0;
            vendedor.superoCuota = false;
        }
        else{
            vendedor.montoVend *= vendedor.porcVentas/100;
            vendedor.superoCuota = true;
        }
        archVend.seekg(i*tamRegVend,ios::beg);
        archVend.write(reinterpret_cast<const char*>(&vendedor),tamRegVend);
        archVend.flush();
    }
    
}

void ordenarVendedores(const char *nombArchVend){
    fstream archVend(nombArchVend,ios::in|ios::out|ios::binary);
    if(not archVend.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchVend<<endl;
        exit(1);    
    }
    struct Vendedor vendedorI, vendedorJ;
    int tamArchVend,tamRegVend,numRegVend;
    datosDelArchivoVendF(archVend,tamArchVend,tamRegVend,numRegVend);
    for(int i=0;i<numRegVend-1;i++)
        for(int j=i+1;j<numRegVend;j++){
            archVend.seekg(i*tamRegVend,ios::beg);
            archVend.read(reinterpret_cast<char*>(&vendedorI),tamRegVend);
            archVend.seekg(j*tamRegVend,ios::beg);
            archVend.read(reinterpret_cast<char*>(&vendedorJ),tamRegVend);
            if(vendedorJ.montoVend>vendedorI.montoVend){
                archVend.seekg(i*tamRegVend,ios::beg);
                archVend.write(reinterpret_cast<const char*>(&vendedorJ),tamRegVend);
                archVend.seekg(j*tamRegVend,ios::beg);
                archVend.write(reinterpret_cast<const char*>(&vendedorI),tamRegVend);
                archVend.flush();
            }
        }
}

void emitirReporte(const char *nombArchArt,const char *nombArchVend,
                   const char *nombArchRep){
    ifstream archArt(nombArchArt,ios::in|ios::binary);
    if(not archArt.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchArt<<endl;
        exit(1);    
    }
    ifstream archVend(nombArchVend,ios::in|ios::binary);
    if(not archVend.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchVend<<endl;
        exit(1);    
    }
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);    
    }
    double ingresoTotal=0, pagos=0;
    archRep.precision(2);
    archRep<<fixed;
    
    
}

int buscarArticuloEnVendedor(struct ArticuloVendido *artVendidos,char *codigoArt,
                             int numArtVend){
    for(int i=0;i<numArtVend;i++){
        if(strcmp(codigoArt,artVendidos[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}

int buscarArticulo(char *codigoArt,fstream &archArt,int numRegArt){
    struct Articulo articulo;
    archArt.seekg(0,ios::beg);
    for(int i=0;i<numRegArt;i++){
        archArt.read(reinterpret_cast<char*>(&articulo),sizeof(struct Articulo));
        if(strcmp(codigoArt,articulo.codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}

int buscarVendedor(int codigoVend,fstream &archVend,int numRegVend){
    struct Vendedor vendedor;
    archVend.seekg(0,ios::beg);
    for(int i=0;i<numRegVend;i++){
        archVend.read(reinterpret_cast<char*>(&vendedor),sizeof(struct Vendedor));
        if(codigoVend == vendedor.codigo) return i;
    }
    return NO_ENCONTRADO;
}

void pasarMayus(char *descripcion){
    for(int i=0;descripcion[i];i++)
        if(descripcion[i]>= 'a' and descripcion[i]<='z') descripcion[i] -= 'a'-'A';
}

void modificarCadena(char *nombre){
    bool minus=false;
    //ESCALANTE/YINO/EDWARD-GONZALO
    for(int i=0;nombre[i];i++){
        if(nombre[i]=='/' or nombre[i]=='-'){
            nombre[i] = ' ';
            minus = false;
        }
        else{
            if(minus){
                nombre[i] += 'a'-'A';
            }
            else{
                minus = true;
            }
        }
    }
}

void mostrarArchivoBinarioArt(const char *nombArchBin){
    ifstream archBin(nombArchBin,ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchBin<<endl;
        exit(1);    
    }
    struct Articulo articulo;
    int tamArch,tamReg,numReg;
    cout.precision(2);
    cout<<fixed;
    datosDelArchivoArt(archBin,tamArch,tamReg,numReg);
    for(int i=0;i<numReg;i++){
        archBin.read(reinterpret_cast<char*>(&articulo),
                     sizeof(struct Articulo));
        cout<<right<<setw(3)<<i+1<<" )  "<<left<<setw(10)<<articulo.codigo
            <<setw(60)<<articulo.descripcion<<right<<setw(10)<<articulo.precio
            <<"   "<<articulo.cantVendido<<"   "<<articulo.montoVendido<<endl;
    }
}


void mostrarArchivoBinarioVend(const char *nombArchBin){
    ifstream archBin(nombArchBin,ios::in|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchBin<<endl;
        exit(1);    
    }
    struct Vendedor vendedor;
    int tamArch,tamReg,numReg;
    cout.precision(2);
    cout<<fixed;
    cout<<endl;
    datosDelArchivoVend(archBin,tamArch,tamReg,numReg);
    for(int i=0;i<numReg;i++){
        archBin.read(reinterpret_cast<char*>(&vendedor),
                     sizeof(struct Vendedor));
        cout<<right<<setw(3)<<i+1<<" )  "<<setw(10)<<vendedor.codigo<<"   "
            <<left<<setw(60)<<vendedor.nombre<<"  "<<right<<setw(10)<<vendedor.porcVentas
            <<"   "<<vendedor.cuotaMin<<"   "<<vendedor.numArtVend<<"   "
            <<vendedor.montoVend<<"   "<<vendedor.superoCuota<<endl;
    }
}
void datosDelArchivoArt(ifstream &archBin,int &tamArch,int &tamReg,int &numReg){
    tamReg = sizeof(struct Articulo);
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    numReg = tamArch/tamReg;
    archBin.seekg(0,ios::beg);
}

void datosDelArchivoVend(ifstream &archBin,int &tamArch,int &tamReg,int &numReg){
    tamReg = sizeof(struct Vendedor);
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    numReg = tamArch/tamReg;
    archBin.seekg(0,ios::beg);
}

void datosDelArchivoArtF(fstream &archBin,int &tamArch,int &tamReg,int &numReg){
    tamReg = sizeof(struct Articulo);
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    numReg = tamArch/tamReg;
    archBin.seekg(0,ios::beg);
}

void datosDelArchivoVendF(fstream &archBin,int &tamArch,int &tamReg,int &numReg){
    tamReg = sizeof(struct Vendedor);
    archBin.seekg(0,ios::end);
    tamArch = archBin.tellg();
    numReg = tamArch/tamReg;
    archBin.seekg(0,ios::beg);
}