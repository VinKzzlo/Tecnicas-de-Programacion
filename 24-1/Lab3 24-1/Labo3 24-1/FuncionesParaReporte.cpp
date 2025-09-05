/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesParaReporte.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 26 de abril de 2024, 21:31
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesParaReporte.h"
#define TAMLINEA 150
#define MAXCARNOMB 40
#define MAXCARESPC 20

void emitirReporte(const char *nombArchCitas, const char *nombArchMedicos,
                   const char *nombArchRep){
    
    ifstream archCitas(nombArchCitas,ios::in);
    if(not archCitas.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchCitas<<endl;
        exit(1);
    }
    
    ifstream archMed(nombArchMedicos,ios::in);
    if(not archMed.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchMedicos<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo"<<nombArchRep<<endl;
        exit(1);
    }
    
    int codPacienteMax;
    double ingresosTotales=0.0, pagoPacienteMax=0.0;
    imprimirEncabezado(archRep);
    while(true){
        archRep.precision(2);
        archRep<<fixed;
        leeImprimeDatosCita(archCitas,archMed,archRep,ingresosTotales,
                           codPacienteMax, pagoPacienteMax);
        if(archCitas.eof()) break;
    }
    imprimeLinea(archRep,'=');
    archRep<<"Total de ingresos: "<<setw(35)<<ingresosTotales<<endl;
    imprimeLinea(archRep,'=');
    archRep<<"Paciente que más gastó en una cita médica: "<<codPacienteMax<<endl;
    archRep<<"Monto gastado:"<<setw(40)<<pagoPacienteMax<<endl;
    imprimeLinea(archRep,'=');
    
}

void leeImprimeDatosCita(ifstream &archCitas,ifstream &archMed,
                         ofstream &archRep, double &ingresosTotales,
                        int &codPacienteMax, double &pagoPacienteMax){
    int dd,mm,aa, codPaciente, horaI, horaF, duracionEnS, codMedico;
    double porcDcto, pagoMedicinas,tarifaH, duracionEnH, pagoRealizado;
    char fueRecetado, c;
    
    archCitas>>dd;
    if(archCitas.eof()) return;
    archCitas>>c>>mm>>c>>aa>>codPaciente>>porcDcto;
    archRep<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa<<"  "
           <<setw(8)<<codPaciente<<"  ";
    horaI = leeHoraConvierteASeg(archCitas);
    imprimeHora(horaI, archRep);
    horaF = leeHoraConvierteASeg(archCitas);
    imprimeHora(horaF, archRep);
    duracionEnS = horaF-horaI;
    duracionEnH = (double)duracionEnS/3600;
    imprimeHora(duracionEnS, archRep);
    archRep<<setfill(' ')<<setw(7)<<porcDcto<<'%'<<setw(6)<<' ';
    archCitas>>codMedico>>fueRecetado;
    buscaImprimeDatosMedicoRetornaTarifa(codMedico,archMed,archRep,tarifaH);
    if(fueRecetado=='S')
        archCitas>>pagoMedicinas;
    else
        pagoMedicinas= 0.0;
    imprimePagoSumaIngresos(tarifaH,duracionEnH,pagoMedicinas, porcDcto,
                            archRep,ingresosTotales, pagoRealizado);
    hallaPacienteGastoMax(codPaciente,pagoRealizado,codPacienteMax,pagoPacienteMax);
//    while(archCitas.get()!='\n');
    archRep<<endl;
}

void hallaPacienteGastoMax(int codPaciente, double pagoRealizado,
                           int &codPacienteMax, double &pagoPacienteMax){
    
    if(pagoRealizado>pagoPacienteMax){
        pagoPacienteMax = pagoRealizado;
        codPacienteMax = codPaciente;
    }
}

void buscaImprimeDatosMedicoRetornaTarifa(int codMedico,ifstream &archMed,
                                          ofstream &archRep, double &tarifaH){
    int codMedRegistro;
    bool loEncontro=false;
    archMed.clear();
    archMed.seekg(0,ios::beg);
    while(not loEncontro){
        archMed>>codMedRegistro;
        if(archMed.eof())break;
        if(codMedico==codMedRegistro){
            imprimeNombreEspMedico(archMed,archRep,'N');
            imprimeNombreEspMedico(archMed,archRep,'E');
            archMed>>tarifaH;
            loEncontro=true;
        }
        else
            while(archMed.get()!='\n');
    }
}

void imprimeNombreEspMedico(ifstream &archMed,ofstream &archRep,char seleccion){
    int nroBlancos, nroCaracteres=0;
    char letra, letraAnt='_';
    if(seleccion=='N'){
        archMed>>ws;
        while(true){
            letra = archMed.get();
            if(letra == ' ') break;
            nroCaracteres++;
            if(letra == '_') archRep.put(' ');
            else {
                if (letraAnt!='_') letra += ('a'- 'A');
                archRep.put(letra);
            }
            letraAnt = letra;
        }
        nroBlancos = MAXCARNOMB - nroCaracteres;
        archRep<<setw(nroBlancos)<<' ';
    }
    else if(seleccion=='E'){
        archMed>>ws;
        while(true){
            letra = archMed.get();
            if(letra == ' ') break;
            nroCaracteres++;
            if(letra == '_') archRep.put(' ');
            else {
                if (letraAnt!='_') letra -= ('a'- 'A');
                archRep.put(letra);
            }
            letraAnt = letra;
        }
        nroBlancos = MAXCARESPC - nroCaracteres;
        archRep<<setw(nroBlancos)<<' ';
    }
}
void imprimePagoSumaIngresos(double tarifaH,double duracionEnH,double pagoMedicinas,
                             double porcDcto, ofstream &archRep,double &ingresosTotales,
                             double &pagoRealizado){
    double pagoTarifa, descuento;
    pagoTarifa = (tarifaH*duracionEnH);
    descuento = pagoTarifa*(porcDcto/100) + pagoMedicinas*((porcDcto/100)/2);
    pagoRealizado = pagoTarifa + pagoMedicinas - descuento;
    archRep<<setw(15)<<pagoRealizado;
    ingresosTotales += pagoRealizado;
}

int leeHoraConvierteASeg(ifstream &archCitas){
    int hor,min,seg;
    char c;
    archCitas>>hor>>c>>min>>c>>seg;
    return (hor*3600 + min*60 + seg);
}

void imprimeHora(int horaEnS, ofstream &archRep){
    int hh, mm, ss;
    hh = horaEnS/3600;
    mm = (horaEnS - hh*3600)/60;
    ss = horaEnS - hh*3600 - mm*60;
    archRep<<setw(2)<<hh<<':'<<setw(2)<<mm<<':'<<setw(2)<<ss;
    archRep<<"  ";
}

void imprimirEncabezado(ofstream &archRep){
    archRep<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea(archRep,'=');
    archRep<<setw((25+TAMLINEA)/2)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    imprimeLinea(archRep,'=');
    archRep<<left<<setw(12)<<"Fecha"<<setw(11)<<"Paciente"<<setw(11)<<"Inicio"
           <<setw(8)<<"Fin"<<setw(10)<<"Duracion"<<setw(14)<<"& por Seguro"
           <<setw(MAXCARNOMB)<<"Medico"<<setw(MAXCARESPC)<<"Especialidad"
           <<setw(22)<<"Pago (cita+medicinas)"<<endl;
    imprimeLinea(archRep,'-');
    archRep<<right;
}

void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0;i<TAMLINEA;i++)
        archRep.put(caracter);
    archRep<<endl;
}