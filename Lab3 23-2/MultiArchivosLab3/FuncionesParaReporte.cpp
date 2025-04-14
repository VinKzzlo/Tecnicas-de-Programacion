/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesParaReporte.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 21 de abril de 2024, 22:16
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesParaReporte.h"
#define TAMLIN 113
#define MAXNOMBCAN 31

void emitirReportePreferencias(const char *nombArchPref,const char *nombArchTel,
                               const char *nombArchCan, const char *nombArchRep){
    
    ifstream archPref(nombArchPref, ios::in);
    if (not archPref.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchPref<<endl;
        exit(1);
    }
    
    ifstream archTel(nombArchTel, ios::in);
    if (not archTel.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchTel<<endl;
        exit(1);
    }
    
    ifstream archCan(nombArchCan, ios::in);
    if (not archCan.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCan<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep, ios::out);
    if (not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    int canal,nroMenores=0,nroJovenes=0,nroAdultos=0,nroPersonas=0,tiempoTotal=0;
    imprimirEncabezado(archRep);
    while(true){
        //1.- Leer los canales e imprimir sus encabezados
        leeEImprimeEncabezadoCanal(archCan, archRep,canal);
        if(archCan.eof()) break;
        imprimeEncabezadoClientes(archRep);
        imprimeDatosTelevidentes(canal,archTel,archPref, archRep,
                                 nroMenores,nroJovenes,nroAdultos,nroPersonas,
                                 tiempoTotal);
        
    }
}
void leeEImprimeEncabezadoCanal(ifstream &archCan,ofstream &archRep,int &canal){
//    310   /Television Peruana/
    archCan>>canal;
    if(archCan.eof())return;
    imprimeLinea(archRep,'=');
    archRep<<"CANAL: ";
    leeImprimeNombreCanal(archCan,archRep,'/');
    archRep<<"NUMERO: "<<canal<<endl;
    archRep<<"LISTADO DE TELEVIDENTES QUE VEN EL CANAL:"<<endl;
}

void leeImprimeNombreCanal(ifstream &archCan,ofstream &archRep, char cFin){
    int numCaracteres=0, numBlancos;
    char c;
    archCan>>ws;
    archCan.get();
    while(true){
        c = archCan.get();
        if(c == cFin) break;
        numCaracteres++;
        if(c >= 'a' and c<= 'z')
            c -= ('a'-'A');
        archRep.put(c);
    }
    numBlancos = MAXNOMBCAN - numCaracteres;
    archRep<<setw(numBlancos)<<' ';
}

void imprimeEncabezadoClientes(ofstream &archRep){
    imprimeLinea(archRep,'-');
    archRep<<left<<setw(10)<<"DNI No."<<setw(29)<<"NOMBRE"<<setw(11)<<"SEXO"
           <<setw(12)<<"CATEGORIA"<<setw(17)<<"COMPANIA"<<setw(23)<<"RANGO"
           <<setw(11)<<"DURACION"<<endl;
    imprimeLinea(archRep,'-');
}
void imprimeDatosTelevidentes(int canal, ifstream &archTel,ifstream &archPref,
                              ofstream &archRep, int &nroMenores, int &nroJovenes,
                              int &nroAdultos, int &nroPersonas, int &tiempoTotal){
    int nroDNI, canalPref,horaI,horaF;
    archPref.clear();
    archPref.seekg(0,ios::beg);
    while(true){
        archPref>>nroDNI;
        if(archPref.eof()) break;
        while(true){
            if(archPref.get()=='\n')break;
            archPref>>canalPref;
            horaI=obtenerHora(archPref);
            horaF=obtenerHora(archPref);
            if(canal==canalPref){
                buscarImprimirDatosCliente(nroDNI,horaI,horaF,archTel,archRep,
                                           nroMenores,nroJovenes,nroAdultos,
                                           nroPersonas,tiempoTotal);
            }
        }
    }
}

void buscarImprimirDatosCliente(int nroDNI,int horaI,int horaF,
                                ifstream &archTel,ofstream &archRep,
                                int &nroMenores,int &nroJovenes,int &nroAdultos,
                                int &nroPersonas,int &tiempoTotal){
    int dniTel;
    archTel.clear();
    archTel.seekg(0,ios::beg);
    while(true){
        archTel>>dniTel;
        if(archTel.eof())break;
        if(dniTel==nroDNI){
            archRep<<setw(10)<<dniTel;
            imprimirNombreTelevidente(archTel,archRep);
        }
    }
}
void imprimirNombreTelevidente(ifstream &archTel,ofstream &archRep){
    int nroCaracteres=0, nroBlancos, contador=1;
    char letra;
    archTel>>ws;
    while(true){
        letra=archTel.get();
        if(letra==' ') break;
        if(letra=='_') letra=' ';
        archRep.put(letra);
    }
    while(archTel.get()!='\n');
    archRep<<endl;
}

int obtenerHora(ifstream &archPref){
    int hor,min,seg;
    char c;
    archPref>>hor>>c>>min>>c>>seg;
    return (hor*3600+min*60+seg);
}

void imprimirEncabezado(ofstream &archRep){
    imprimeLinea(archRep, '=');
    archRep<<setw((38+TAMLIN)/2)<<"EMPRESA DE OPINION DE MERCADO TP S. A."<<endl;
    archRep<<setw((37+TAMLIN)/2)<<"AVENIDA UNIVERSITARIA 1234 San Miguel"<<endl;
    archRep<<setw((11+TAMLIN)/2)<<"LIMA - PERU"<<endl;
    imprimeLinea(archRep, '=');
    archRep<<setw((69+TAMLIN)/2)<<"REGISTRO DE PREFERENCIAS DE LOS"
                     " TELEVIDENTES POR CANAL DE PREFERENCIA"<<endl;
}
void imprimeLinea(ofstream &archRep, char caracter){
    for(int i=0; i<TAMLIN; i++){
        archRep.put(caracter);
    }
    archRep<<endl;
}

