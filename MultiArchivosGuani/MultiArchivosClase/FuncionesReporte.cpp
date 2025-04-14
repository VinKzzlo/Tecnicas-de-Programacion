/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesReporte.cpp
 * Autor:     VinKzzlo
 *
 * Creado el on 21 de abril de 2024, 18:54
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesReporte.h"

void emitirReporteDeFacturas(const char *nombArchCli,const char *nombArchFac,
                             const char *nombArchPro,const char *nombArchRep){
    //1.- Preparar los archivos
    ifstream archCli(nombArchCli, ios::in);
    if(not archCli.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchCli<<endl;
        exit(1);
    }
    
    ifstream archFac(nombArchFac, ios::in);
    if(not archFac.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchFac<<endl;
        exit(1);
    }
    
    ifstream archPro(nombArchPro, ios::in);
    if(not archPro.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchPro<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep, ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchRep<<endl;
        exit(1);
    }
    
    //1.1. Imprimir encabezados
    while(true){
    //2.- leer e imprimir los datos de la factura
        leerImprimirDatosFactura(archFac,archRep);
        if(archFac.eof()) break;
    //3.- leer e imprimir los datos del cliente, buscando los datos faltantes
        leerImprimirDatosCliente(archFac,archCli,archRep);
    //3.5- imprimir subtítulos
    //4.- leer e imprimir los datos de los productos comprados, determinando
    //    el PU y el subtotal, calculando el total facturado
    //5.- imprimir el total facturado     
    }
    
    
}

void leerImprimirDatosFactura(ifstream &archFac,ofstream &archRep){
//10001   10/03/2020   85054426     956872   4   488600   6   606509   11   782023   15   931079   11
    int numFac, dd,mm,aa;
    char c;
    archFac>>numFac;
    if(archFac.eof()) return;
    archFac>>dd>>c>>mm>>c>>aa;
    archRep<<"Factura No.: "<<setw(10)<<numFac<<setw(12)<<"Fecha:  "
           <<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa
           <<setfill(' ')<<endl;
}

void leerImprimirDatosCliente(ifstream &archFac, ifstream &archCli,
                              ofstream &archRep){
    int dni;
    archFac>>dni;
    buscarImprimirCliente(dni,archCli,archRep);
    while(archFac.get()!='\n');
    archRep<<endl;
}

void buscarImprimirCliente(int dni,ifstream &archCli,ofstream &archRep){
//    17000095  [Hijar Pairazaman Jenny Delicia]     5     39827505
    int dniCli;
    bool loEncontro = false;
    archCli.clear();
    archCli.seekg(0,ios::beg);
    while (not loEncontro){
        archCli>>dniCli;
        if(archCli.eof()) break;
        if(dni==dniCli){
            archRep<<"Cliente  DNI:"<<setw(10)<<dni<<setw(12)<<"Nombre: ";
            leerImprimirNombre(archCli,archRep, '[',']');
            loEncontro = true;
        }
        while(archCli.get() != '\n');
    }
    if(not loEncontro)
        archRep<<"Cliente DNI:"<<setw(10)<<dni<<setw(12)
               <<"NO SE ENCONTRO"<<endl;
}

void leerImprimirNombre(ifstream &archCli,ofstream &archRep,
                       char cIni, char cFin){
    char c;
    archCli>>ws;
    archCli.get();
    while(true){
        c = archCli.get();
        if(c == cFin) break;
        archRep.put(c);
    }
    archRep<<endl;
}