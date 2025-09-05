/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesParaReporte.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 15 de abril de 2024, 16:00
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesParaReporte.h"
#define TAMLINEA 111

//  9/09/2023   94683380   11:17:52   12:48:30   124.34   C   S   317.86

void emitirReporte(const char *nombArchDatos, const char *nombArchRep){
    int dd, mm, aa, nroDNI, horaI, horaF, nroPac=0, nroPacRec=0,nroPacNoRec=0,
    nroPacDerm=0, nroPacPed=0, nroPacCardF=0, nroPacUltEstadist=0;
    double tarifaPorH, pagoMedicinas, totalIngresos=0.0, 
            gastosMedPacRec=0.0, gastosMedPacDerm=0.0;
    char especialidad,fueRecetado, c;
    
    ifstream archDat(nombArchDatos, ios::in);
    if(not archDat.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchDatos<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep, ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchDatos<<endl;
        exit(1);
    }
    
    imprimirEncabezado(archRep);
    while(true){
        archDat>>dd;
        if(archDat.eof()) break;
        nroPac++;
        archDat>>c>>mm>>c>>aa>>nroDNI;
        horaI = convertirHora(archDat);
        horaF = convertirHora(archDat);
        archDat>>tarifaPorH>>especialidad>>fueRecetado;
        if(fueRecetado=='S'){
            archDat>>pagoMedicinas;
            gastosMedPacRec += pagoMedicinas;
            nroPacRec++;
        }
        else{
            pagoMedicinas=0.0;
            nroPacNoRec++;
        }
        imprimirYProcesarDatos(archRep, dd,mm,aa, nroDNI, horaI, horaF, tarifaPorH,
                especialidad, fueRecetado, pagoMedicinas, totalIngresos,
                nroPacDerm, nroPacPed, nroPacCardF, nroPacUltEstadist,
                gastosMedPacDerm);
    }
    imprimeLinea(archRep,'-');
    archRep<<"Total de ingresos : "<<totalIngresos;
}

void imprimirYProcesarDatos(ofstream &archRep, int dd,int mm,int aa, int nroDNI,
     int horaI, int horaF, double tarifaPorH,char especialidad,char fueRecetado,
     double pagoMedicinas, double &totalIngresos,
     int &nroPacDerm, int &nroPacPed, int &nroPacCardF,int &nroPacUltEstadist,
               double &gastosMedPacDerm){
    int fechaConvertida, duracionEnS;
    double duracionEnH;
    bool cardio, derma, pedia;
    fechaConvertida = aa*10000 + mm*100 + dd;
    archRep<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<setw(2)
           <<aa<<setfill(' ')<<"  "<<setw(8)<<nroDNI<<"  ";
    imprimirHora(archRep,horaF);
    archRep<<"  ";
    imprimirHora(archRep,horaI);
    archRep<<setw(4)<<' ';
    archRep.precision(4);
    archRep<<fixed;
    duracionEnS = horaF-horaI;
    duracionEnH = (double)duracionEnS/3600;
    imprimirHora(archRep,duracionEnS);
    archRep<<setw(8)<<' '<<setw(7)<<duracionEnH<<left<<setw(6)<<' ';
    imprimirEspecialidad(archRep,especialidad, cardio, pedia, derma);
    imprimeMontoYSumaIngresos(archRep,tarifaPorH,
            duracionEnH,pagoMedicinas,totalIngresos);
    archRep<<endl;
    
}

void imprimirEspecialidad(ofstream &archRep, char especialidad,
        bool &cardio, bool &pedia,bool &derma){
    if(especialidad=='C'){
        archRep<<setw(14)<<"Cardiologia";
        cardio=true;
    }
    else if(especialidad=='D'){
        archRep<<setw(14)<<"Dermatologia";
        derma=true;
    }
    else if(especialidad=='P'){
        archRep<<setw(14)<<"Pediatria";
        pedia=true;
    }
}
void imprimeMontoYSumaIngresos(ofstream &archRep, double tarifaPorH,
        double duracionEnH,double pagoMedicinas, double &totalIngresos){
    double pagoTotal;
    pagoTotal = tarifaPorH*duracionEnH + pagoMedicinas;
    archRep.precision(2);
    archRep<<right<<setw(8)<<' '<<setw(10)<<pagoTotal;
    totalIngresos = totalIngresos + pagoTotal;
}

void imprimirHora(ofstream &archRep,int horaEnS){
    int hor, min, seg;
    hor = horaEnS/3600;
    min = (horaEnS - hor*3600)/60;
    seg = horaEnS - hor*3600 - min*60;
    archRep<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg;
    archRep<<setfill(' ');
}

int convertirHora(ifstream &archDat){
    int hh, mm, ss;
    char c;
    archDat>>hh>>c>>mm>>c>>ss;
    return (hh*3600+mm*60+ss);
}

void imprimirEncabezado(ofstream &archRep){
    archRep<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea(archRep, '=');
    archRep<<setw((42+TAMLINEA)/3)<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"
            <<endl;
    imprimeLinea(archRep, '=');
    archRep<<left<<setw(12)<<"Fecha"<<setw(11)<<"Paciente"<<setw(11)<<"Inicio"
        <<setw(8)<<"Fin"<<setw(17)<<"Duracion(H:M:S)"<<setw(13)<<"Duracion(H)"
        <<setw(16)<<"Especialidad"<<setw(23)<<"Pago (cita+medicinas)"<<endl;
    imprimeLinea(archRep, '-');
}

void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA; i++)
        archRep<<caracter;
    archRep<<endl;
}