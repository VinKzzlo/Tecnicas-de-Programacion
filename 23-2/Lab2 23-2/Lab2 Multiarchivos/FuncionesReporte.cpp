/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesReporte.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 29 de abril de 2024, 16:57
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesReporte.h"
#define TAMLINEA 111
#define MAXNOMB 40

void emitirReporteCitas(const char *nombArchMed,const char *nombArchPac,
                        const char *nombArchCit,const char *nombArchRep){
    ifstream archMed(nombArchMed,ios::in);
    if (not archMed.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchMed<<endl;
        exit(1);
    }
    
    ifstream archPac(nombArchPac,ios::in);
    if (not archPac.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchPac<<endl;
        exit(1);
    }
    
    ifstream archCit(nombArchCit,ios::in);
    if (not archCit.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchCit<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep,ios::out);
    if (not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchRep<<endl;
        exit(1);
    }
    int dniPac;
    double totalRecaudado=0.0;
    imprimeEncabezado(archRep);
    while(true){
        double totalPagoCitas=0.0;
        imprimeLinea(archRep,'=');
        leeImprimeDatosPaciente(archPac,archRep,dniPac);
        if(archPac.eof())break;
        imprimeEncabezadoDatosCita(archRep);
        buscaImprimeCitas(dniPac,archCit,archMed,archRep,totalPagoCitas);
        imprimeLinea(archRep,'-');
        totalRecaudado += totalPagoCitas;
    }
}

void buscaImprimeCitas(int dniPac,ifstream &archCit,ifstream &archMed,
                       ofstream &archRep,double &totalPagoCitas){
    int dniCit, codMedico, dd,mm,aa, horaI, horaF;
    double duracionEnH, tarifa;
    char c;
    archCit.clear();
    archCit.seekg(0,ios::beg);
    while(true){
        archCit>>dniCit;
        if(archCit.eof())break;
        if(dniPac==dniCit){
            archCit>>codMedico;
            archCit>>dd>>c>>mm>>c>>aa;
            archRep<<right<<setw(5)<<' '<<setfill('0')<<setw(2)<<dd<<'/'
                   <<setw(2)<<mm<<'/'<<setw(4)<<aa<<setfill(' ')<<setw(5)<<' ';
            buscaImprimeNombreTarifa(codMedico,archMed,archRep,tarifa);
            horaI = obtenerHora(archCit);
            horaF = obtenerHora(archCit);
            duracionEnH = (horaF - horaI)/(double)3600;
            archRep<<endl;
        }
        else{
            while(archCit.get() != '\n');
        }
    }
}

void buscaImprimeNombreTarifa(int codMedico,ifstream &archMed,ofstream &archRep,
                              double &tarifa){
    int codigo;
    archMed.clear();
    archMed.seekg(0,ios::beg);
    while(true){
        archMed>>codigo;
        if(archMed.eof())break;
        if(codigo==codMedico){
            imprimeNombreMedico(archMed,archRep);
            archMed>>tarifa;
            archRep.precision(2);
            archRep<<fixed;
            archRep<<setw(10)<<tarifa;
        }
        else{
            while(archMed.get() != '\n');
        }
    }
}

void imprimeNombreMedico(ifstream &archMed,ofstream &archRep){
    int nroCaracteres=0, nroBlancos;
    char letra;
    archMed>>ws;
    while(true){
        letra = archMed.get();
        if(letra == ' ') break;
        nroCaracteres++;
        if (letra == '_') letra=' ';
        archRep.put(letra);
    }
    nroBlancos = MAXNOMB - nroCaracteres;
    archRep<<setw(nroBlancos)<<' ';
}

int obtenerHora(ifstream &archCit){
    int hor,min,seg;
    char c;
    archCit>>hor>>c>>min>>c>>seg;
    return (hor*3600 + min*60 +seg);
}

void leeImprimeDatosPaciente(ifstream &archPac,ofstream &archRep, int &dniPac){
    int telefono;
    archPac>>dniPac;
    if(archPac.eof())return;
    archRep<<left<<setw(5)<<' '<<setw(14)<<"DNI"<<setw(MAXNOMB)<<"Paciente"
           <<setw(10)<<"Telefono"<<endl;
    archRep<<setw(5)<<' '<<setw(14)<<dniPac;
    imprimeNombrePac(archPac,archRep);
    archPac>>telefono;
    archRep<<setw(10)<<telefono<<endl;
    archRep<<endl;
    archRep<<setw(5)<<' '<<"CITAS REALIZADAS: "<<endl;
}

void imprimeEncabezadoDatosCita(ofstream &archRep){
    imprimeLinea(archRep,'-');
    archRep<<setw(5)<<' '<<setw(14)<<"FECHA"<<setw(MAXNOMB+5)<<"MEDICO"
           <<setw(12)<<"TARIFA"<<setw(14)<<"LLEGADA"<<setw(14)<<"SALIDA"
           <<setw(16)<<"TIEMPO(hrs)."<<setw(10)<<"PAGO"<<endl;
    imprimeLinea(archRep,'-');
}

void imprimeNombrePac(ifstream &archPac,ofstream &archRep){
    int nroCaracteres=0, nroBlancos;
    char letra;
    archPac>>ws;
    archPac.get();
    while(true){
        letra = archPac.get();
        if(letra == ']') break;
        nroCaracteres++;
        archRep.put(letra);
    }
    nroBlancos = MAXNOMB - nroCaracteres;
    archRep<<setw(nroBlancos)<<' ';
}

void imprimeEncabezado(ofstream &archRep){
    archRep<<setw((23+TAMLINEA)/2)<<"CLINICA PSICOLOGICA TP."<<endl;
    archRep<<setw((30+TAMLINEA)/2)<<"RELACION DE CITAS POR PACIENTE"<<endl;
}
void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA;i++)
        archRep.put(caracter);
    archRep<<endl;
}