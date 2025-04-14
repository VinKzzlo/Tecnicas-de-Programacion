/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 30 de junio de 2024, 2:08
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "FuncionesAuxiliares.h"
#include "Cliente.h"
#include "Libro.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 174

void crearClientesBIN(const char *nombArchCSV,const char *nombArchBIN){
    ifstream archCsv(nombArchCSV,ios::in);
    if(not archCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCSV<<endl;
        exit(1);
    }
    ofstream archBin(nombArchBIN,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchBIN<<endl;
        exit(1);
    }
    struct Cliente cliente;
    int dni;
    char nombre[60];
    while(true){
        archCsv>>dni;
        if(archCsv.eof())break;
        archCsv.get();
        archCsv.getline(nombre,60);
        cliente.dni = dni;
        strcpy(cliente.nombre,nombre);
        archBin.write(reinterpret_cast<const char*>(&cliente),
                      sizeof(struct Cliente));
    }
}

void crearLibrosBIN(const char *nombArchCSV,const char *nombArchBIN){
    ifstream archCsv(nombArchCSV,ios::in);
    if(not archCsv.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCSV<<endl;
        exit(1);
    }
    ofstream archBin(nombArchBIN,ios::out|ios::binary);
    if(not archBin.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchBIN<<endl;
        exit(1);
    }
    struct Libro libro{};
    char codigo[8], titulo[100], autor[60];
    double precio;
    while(true){
        archCsv.getline(codigo,8,',');
        if(archCsv.eof())break;
        archCsv.getline(titulo,100,',');
        archCsv.getline(autor,60,',');
        archCsv>>precio;
        archCsv.get();
        strcpy(libro.codigo,codigo);
        strcpy(libro.titulo,titulo);
        strcpy(libro.autor,autor);
        libro.precio = precio;
        archBin.write(reinterpret_cast<const char*>(&libro),
                      sizeof(struct Libro));
    }
}

void actualizarLibrosConVentas(const char *nombArchVenta,const char *nombArchCli,
                               const char *nombArchLibro){
    ifstream archVenta(nombArchVenta,ios::in);
    if(not archVenta.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchVenta<<endl;
        exit(1);
    }
    ifstream archCli(nombArchCli,ios::in|ios::binary);
    if(not archCli.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCli<<endl;
        exit(1);
    }
    fstream archLib(nombArchLibro,ios::in|ios::out|ios::binary);
    if(not archLib.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchLibro<<endl;
        exit(1);
    }
    char codLib[8],c;
    int dniCli, dd,mm,aa, calificacion;
    while(true){
        archVenta.getline(codLib,8,',');
        if(archVenta.eof())break;
        archVenta>>dniCli;
        archVenta>>c>>dd>>c>>mm>>c>>aa>>c>>calificacion;
        archVenta.get();
        completarArchivo(archCli,archLib,dniCli,codLib,dd,mm,aa,calificacion);
    }
    determinarFechaReciente(archLib);
    calcularRanking(archLib);
}

void completarArchivo(ifstream &archCli,fstream &archLib,int dniCli,char *codLib,
                      int dd,int mm,int aa,int calificacion){
    int posL, posC, tamRegC, tamRegL, numRegC,numRegL, nL;
    struct Cliente cliente;
    struct Libro libro;
    tamRegC = sizeof(struct Cliente);
    tamRegL = sizeof(struct Libro);
    numRegC = cantidadRegistrosIfs(archCli,tamRegC);
    numRegL = cantidadRegistrosFs(archLib,tamRegL);
    posC = buscarCliente(dniCli,archCli,numRegC);
    posL = buscarLibro(codLib,archLib,numRegL);
    if(posC != NO_ENCONTRADO and posL != NO_ENCONTRADO){
        archCli.seekg(posC*tamRegC,ios::beg);
        archLib.seekg(posL*tamRegL,ios::beg);
        archCli.read(reinterpret_cast<char*>(&cliente),tamRegC);
        archLib.read(reinterpret_cast<char*>(&libro),tamRegL);
        libro.sumaCalificaciones += calificacion;
        nL = libro.librosVendidos;
        libro.ventas[nL].calificacion = calificacion;
        libro.ventas[nL].dniComp = dniCli;
        strcpy(libro.ventas[nL].nombComp,cliente.nombre);
        libro.ventas[nL].fecha.dd = dd;
        libro.ventas[nL].fecha.mm = mm;
        libro.ventas[nL].fecha.aa = aa;
        libro.ventas[nL].fecha.fecha = aa*10000 + mm*100 + dd;
        libro.librosVendidos++;
        archLib.seekg(posL*tamRegL,ios::beg);
        archLib.write(reinterpret_cast<const char*>(&libro),tamRegL);
        archLib.flush();
    }
}

void ordenarLibros(const char *nombArchLibro){
    fstream archLib(nombArchLibro,ios::in|ios::out|ios::binary);
    if(not archLib.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchLibro<<endl;
        exit(1);
    }
    int tamRegL, numRegL;
    struct Libro libroI, libroJ;
    tamRegL = sizeof(struct Libro);
    numRegL = cantidadRegistrosFs(archLib,tamRegL);
    for(int i=0;i<numRegL-1;i++){
        for(int j=i+1;j<numRegL;j++){
            
            archLib.seekg(i*tamRegL,ios::beg);
            archLib.read(reinterpret_cast<char*>(&libroI),tamRegL);
            
            archLib.seekg(j*tamRegL,ios::beg);
            archLib.read(reinterpret_cast<char*>(&libroJ),tamRegL);
            
            if(libroI.ranking<libroJ.ranking or
               libroI.ranking==libroJ.ranking and
               libroI.fechaMasReciente.fecha>libroJ.fechaMasReciente.fecha){
                
                archLib.seekg(i*tamRegL,ios::beg);
                archLib.write(reinterpret_cast<const char*>(&libroJ),tamRegL);
            
                archLib.seekg(j*tamRegL,ios::beg);
                archLib.write(reinterpret_cast<const char*>(&libroI),tamRegL);
                archLib.flush();
            }
        }
    }
}

void determinarFechaReciente(fstream &archLib){
    int tamRegL, numRegL, fechaMax;
    struct Libro libro;
    tamRegL = sizeof(struct Libro);
    numRegL = cantidadRegistrosFs(archLib,tamRegL);
    archLib.seekg(0,ios::beg);
    for(int i=0;i<numRegL;i++){
        archLib.read(reinterpret_cast<char*>(&libro),tamRegL);
        fechaMax=0;
        for(int j=0;j<libro.librosVendidos;j++){
            if(libro.ventas[j].fecha.fecha>fechaMax){
                fechaMax = libro.ventas[j].fecha.fecha;
                libro.fechaMasReciente.dd = libro.ventas[j].fecha.dd;
                libro.fechaMasReciente.mm = libro.ventas[j].fecha.mm;
                libro.fechaMasReciente.aa = libro.ventas[j].fecha.aa;
                libro.fechaMasReciente.fecha  = libro.ventas[j].fecha.fecha;
                archLib.seekg(i*tamRegL,ios::beg);
                archLib.write(reinterpret_cast<const char*>(&libro),tamRegL);
                archLib.flush();
            }
        }
    }
}

void calcularRanking(fstream &archLib){
    int tamRegL, numRegL, fechaMax;
    double promedio;
    struct Libro libro;
    tamRegL = sizeof(struct Libro);
    numRegL = cantidadRegistrosFs(archLib,tamRegL);
    archLib.seekg(0,ios::beg);
    for(int i=0;i<numRegL;i++){
        archLib.read(reinterpret_cast<char*>(&libro),tamRegL);
        if(libro.sumaCalificaciones>0){
            promedio = (double)libro.sumaCalificaciones/libro.librosVendidos;
            if(promedio>=75)
                libro.ranking = 4;
            else if(promedio>=50)
                libro.ranking = 3;
            else if(promedio>=25)
                libro.ranking = 2;
            else
                libro.ranking = 1;
        }
        else{
            libro.ranking = 0;
        }
        archLib.seekg(i*tamRegL,ios::beg);
        archLib.write(reinterpret_cast<const char*>(&libro),tamRegL);
        archLib.flush();
    }
}
int cantidadRegistrosIfs(ifstream &arch,int tamReg){
    int tamArch, numReg;
    
    arch.seekg(0,ios::end);
    tamArch = arch.tellg();
    numReg = tamArch/tamReg;
    arch.seekg(0,ios::beg);
    return numReg;
}
int cantidadRegistrosFs(fstream &arch,int tamReg){
    int tamArch, numReg;
    
    arch.seekg(0,ios::end);
    tamArch = arch.tellg();
    numReg = tamArch/tamReg;
    arch.seekg(0,ios::beg);
    return numReg;
}

int buscarCliente(int dniCli,ifstream &archCli,int numRegC){
    struct Cliente cliente;
    archCli.seekg(0,ios::beg);
    for(int i=0;i<numRegC;i++){
        archCli.read(reinterpret_cast<char*>(&cliente),sizeof(struct Cliente));
        if(dniCli == cliente.dni) return i;
    }
    return NO_ENCONTRADO;
}

int buscarLibro(char *codLib,fstream &archLib,int numRegL){
    struct Libro libro;
    archLib.seekg(0,ios::beg);
    for(int i=0;i<numRegL;i++){
        archLib.read(reinterpret_cast<char*>(&libro),sizeof(struct Libro));
        if(strcmp(codLib,libro.codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}

void emitirReporte(const char *nombArchLibro,const char *nombArchRep){
    ifstream archLib(nombArchLibro,ios::in|ios::binary);
    if(not archLib.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchLibro<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    struct Libro libro;
    int tamRegL, numRegL;
    tamRegL = sizeof(struct Libro);
    numRegL = cantidadRegistrosIfs(archLib,tamRegL);
    imprimeEncabezado(archRep);
    for(int i=0;i<numRegL;i++){
        archLib.read(reinterpret_cast<char*>(&libro),sizeof(struct Libro));
        imprimeLinea(archRep,'=');
        archRep<<"LIBRO NO. "<<setfill('0')<<setw(3)<<i+1<<setfill(' ')<<endl;
        archRep<<left<<setw(4)<<' '<<setw(10)<<"CODIGO"<<setw(80)<<"TITULO"
               <<setw(40)<<"AUTOR"<<setw(10)<<"PRECIO"<<setw(20)<<"LIBROS VENDIDOS"
               <<setw(10)<<"RANKINGS"<<endl;
        archRep<<left<<setw(4)<<' '<<setw(10)<<libro.codigo<<setw(80)<<libro.titulo
           <<setw(40)<<libro.autor<<right<<setw(6)<<libro.precio
           <<setw(13)<<libro.librosVendidos<<setw(16)<<libro.ranking<<endl;
        imprimeLinea(archRep,'-');
        archRep<<setw(4)<<' '<<"VENTAS REALIZADAS:"<<endl;
        if(libro.librosVendidos>0){
            imprimeVentas(libro.ventas,archRep,libro.librosVendidos);
            imprimeLinea(archRep,'-');
            archRep<<setw(4)<<' '<<"FECHA MAS RECIENTE DE COMPRA:  ";
            archRep<<setfill('0')<<setw(2)<<libro.fechaMasReciente.dd<<'/'
                   <<setw(2)<<libro.fechaMasReciente.mm<<'/'<<setw(4)<<libro.fechaMasReciente.aa
                   <<setfill(' ')<<endl;
        }
        else{
            archRep<<setw(4)<<' '<<"NO SE VENDIO ESTE LIBRO"<<endl;
        }
    }
    
}

void imprimeVentas(struct Venta *ventas,ofstream &archRep,int numVent){
    
    archRep<<left<<setw(4)<<' '<<setw(5)<<"No."<<setw(10)<<"DNI"<<setw(60)<<"NOMBRE"
           <<setw(23)<<"CALIFICACION"<<setw(11)<<"FECHA"<<endl;
    for(int i=0;i<numVent;i++){
        archRep<<setw(4)<<' '<<right<<setfill('0')<<setw(2)<<i+1<<setfill(' ')<<"   "<<left
               <<setw(10)<<ventas[i].dniComp<<setw(60)<<ventas[i].nombComp
               <<right<<setw(6)<<ventas[i].calificacion<<setw(14)<<' '
               <<setfill('0')<<setw(2)<<ventas[i].fecha.dd<<'/'
               <<setw(2)<<ventas[i].fecha.mm<<'/'<<setw(4)<<ventas[i].fecha.aa
               <<setfill(' ')<<endl;
    }
}
void imprimeEncabezado(ofstream &archRep){
    archRep<<setw((16+TAMLINEA)/2)<<"LIBRERIA PUCP-TP"<<endl;
    archRep<<setw((34+TAMLINEA)/2)<<"RESULTADO DE LAS VENTAS REALIZADAS"<<endl;
}
void imprimeLinea(ofstream &archRep, char c){
    for(int i=0;i<TAMLINEA;i++)
        archRep.put(c);
    archRep<<endl;
}
void mostrarClientesBIN(const char *nombArch){
    ifstream arch(nombArch,ios::in|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    struct Cliente cliente;
    cout.precision(2);
    cout<<fixed;
    cout<<"CLIENTES"<<endl;
    cout<<setw(10)<<"No. DNI"<<"  "<<"Nombre"<<endl;
    while(true){
        arch.read(reinterpret_cast<char*>(&cliente),sizeof(struct Cliente));
        if(arch.eof())break;
        cout<<right<<setw(10)<<cliente.dni<<"  "<<left<<cliente.nombre<<endl;
    }
}

void mostrarLibrosBIN(const char *nombArch,const char *nombArchOut){
    ifstream arch(nombArch,ios::in|ios::binary);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    ofstream archOut(nombArchOut,ios::out);
    if(not archOut.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchOut<<endl;
        exit(1);
    }
    struct Libro libro;
    archOut.precision(2);
    archOut<<fixed;
    archOut<<"LIBROS"<<endl;
    archOut<<left<<"  "<<setw(10)<<"Codigo"<<setw(80)<<"Titulo"<<setw(40)<<"Autor"
        <<setw(10)<<"Precio"<<setw(20)<<"Suma Calificaciones"
        <<setw(10)<<"Vendidos"<<setw(10)<<"Ranking"<<endl;
    while(true){
        arch.read(reinterpret_cast<char*>(&libro),sizeof(struct Libro));
        if(arch.eof())break;
        archOut<<left<<"  "<<setw(10)<<libro.codigo<<setw(80)<<libro.titulo
           <<setw(40)<<libro.autor<<setw(10)<<libro.precio
           <<setw(20)<<libro.sumaCalificaciones
           <<setw(10)<<libro.librosVendidos<<setw(10)<<libro.ranking<<endl;
    }
}