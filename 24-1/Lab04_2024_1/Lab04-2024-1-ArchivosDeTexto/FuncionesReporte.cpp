/* 
 * File:   FuncionesReporte.cpp
 * Author: Alessandro Salvador Santé Vega - 20223006
 *
 * Created on 29 de abril de 2024, 07:13 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesReporte.h"
#define TAMLINEA 111
#define MAXCARNOMB 40

void emitirReporte(const char *nombArchCitas,const char *nombArchMedicinas,
                   const char *nombArchMedicos,const char *nombArchRep){
    
    ifstream archCit(nombArchCitas,ios::in);
    if(not archCit.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchCitas<<endl;
        exit(1);
    }
    
    ifstream archMedicina(nombArchMedicinas,ios::in);
    if(not archMedicina.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchMedicinas<<endl;
        exit(1);
    }
    
    ifstream archMedico(nombArchMedicos,ios::in);
    if(not archMedico.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchMedicos<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo: "<<nombArchRep<<endl;
        exit(1);
    }
    int codMedico;
    double tarifa;
    imprimirEncabezado(archRep);
    while(true){
        leeImprimeDatosMedico(archMedico,archRep,codMedico,tarifa);
        if(archMedico.eof())break;
        leeValidaParaImprimirDatosCitas(codMedico,tarifa,archCit,archMedicina,archRep);
    }
    
    
}

void leeImprimeDatosMedico(ifstream &archMedico,ofstream &archRep,
                           int &codMedico,double &tarifa){
    archMedico>>codMedico;
    if(archMedico.eof())return;
    imprimeLinea(archRep,'=');
    archRep<<"Codigo del medico: "<<codMedico<<endl;
    archRep<<"Nombre del medico: ";
    leeImprimeNombres(archMedico,archRep,'M');
    archRep<<endl;
    archRep<<"Especialidad:"<<setw(6)<<' ';
    leeImprimeNombres(archMedico,archRep,'E');
    archRep<<endl;
    archMedico>>tarifa;
    archRep.precision(2);
    archRep<<fixed;
    archRep<<"Tarifa:"<<setw(12)<<' '<<tarifa<<endl;
    archRep<<"PACIENTES ATENDIDOS"<<endl;
}
void leeImprimeNombres(ifstream &archMedico,ofstream &archRep,char seleccion){
    int nroCaracteres=0, nroBlancos;
    char letra;
    archMedico>>ws;
    if(seleccion=='M')
        archMedico.get();
    while(true){
        letra = archMedico.get();
        if(letra == ' ' or letra=='/') break;
        if(letra == '_') letra=' ';
        archRep.put(letra);
        nroCaracteres++;
    }
    nroBlancos = MAXCARNOMB - nroCaracteres;
    archRep<<setw(nroBlancos)<<' ';
}

void imprimeEncabezadoCita(ofstream &archRep){
    imprimeLinea(archRep,'-');
    archRep<<left<<setw(12)<<"Fecha"<<setw(10)<<"Paciente"<<setw(13)<<"Inicio"
           <<setw(7)<<"Fin"<<setw(10)<<"Duracion"
           <<setw(27)<<"% de descuento por Seguro"<<setw(10)<<"Pago por cita"<<endl;
    imprimeLinea(archRep,'-');
}

void leeValidaParaImprimirDatosCitas(int codMedico,double tarifa,
                    ifstream &archCit,ifstream &archMedicina,ofstream &archRep){
    int dd,mm,aa, nroDNI, horaI, horaF, duracionEnS, codMedCita;
    double porcDcto, pagoCita;
    char c;
    bool hayMedicinas;
    archCit.clear();
    archCit.seekg(0,ios::beg);
    while(true){
        archCit>>dd;
        if(archCit.eof())break;
        archCit>>c>>mm>>c>>aa;
        archCit>>nroDNI>>porcDcto;
        horaI = obtenerHora(archCit);
        horaF = obtenerHora(archCit);
        duracionEnS = horaF - horaI;
        archCit>>codMedCita;
        if((codMedCita == codMedico) and duracionEnS<9085){
            imprimeEncabezadoCita(archRep);
            archRep<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
                   <<setw(4)<<aa<<setfill(' ')<<setw(10)<<nroDNI<<setw(2)<<' ';
            imprimeHora(horaI,archRep);
            imprimeHora(horaF,archRep);
            imprimeHora(duracionEnS,archRep);
            archRep<<setw(17)<<porcDcto<<'%';
            calculaImprimePagoCita(tarifa,duracionEnS,porcDcto,pagoCita,archRep);
            archRep<<endl;
            archRep<<"Medicinas recetadas:"<<endl;
            //Paramos la lectura para probar la impresion
            while(archCit.get() != '\n');
        }
        else{
            while(archCit.get() != '\n');
        }
    }
}

void leeImprimeMedicinas(ifstream &archCit,ifstream &archMedicina,ofstream &archRep,
                            bool hayMedicinas){
    archRep<<"Medicinas Recetadas: "<<endl;
}

void imprimeEncabezadoMedicinas(ofstream &archRep){
    archRep<<setw(2)<<' '<<left<<setw(5)<<"No."<<setw(15)<<"Codigo"
           <<setw(MAXCARNOMB)<<"Descripcion"<<setw(10)<<"Cantidad"
           <<setw(7)<<"Precio"<<setw(7)<<"Pago"<<endl;
}

void calculaImprimePagoCita(double tarifa,int duracionEnS,double porcDcto,
                            double &pagoCita, ofstream &archRep){
    double duracionEnH,descuento;
    duracionEnH = (double)duracionEnS/3600;
    descuento = (tarifa*duracionEnH)*(porcDcto/100);
    pagoCita = tarifa*duracionEnH - descuento;
    archRep<<setw(20)<<pagoCita;
}

int obtenerHora(ifstream &archCit){
    int hor, min, seg;
    char c;
    archCit>>hor>>c>>min>>c>>seg;
    return (hor*3600 + min*60 + seg);
}

void imprimeHora(int tiempoEnS, ofstream &archRep){
    int hor, min, seg;
    hor = tiempoEnS/3600;
    min = (tiempoEnS - hor*3600)/60;
    seg = tiempoEnS - hor*3600 - min*60;
    archRep<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg
           <<setfill(' ')<<setw(2)<<' ';
}
void imprimirEncabezado(ofstream &archRep){
    archRep<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea(archRep,'=');
    archRep<<setw((25+TAMLINEA)/2)<<"REGISTRO DE CITAS MEDICAS"<<endl;
}
void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA; i++)
        archRep.put(caracter);
    archRep<<endl;
}