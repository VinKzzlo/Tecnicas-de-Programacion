/* 
 * Archivo:   FuncionesReporte.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 25 de mayo de 2024, 23:47
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesReporte.h"
#define TAMLINEA 111
#define MAXCARNOMB 40
#define MAXCARESP 20



void emitirReporteCitas(const char *nombArchCitas,const char *nombArchMedicinas,
                        const char *nombArchMedicos,const char *nombArchPacientes,
                        const char *nombArchReporte){
//    Apertura de archivos
    ifstream archCita(nombArchCitas,ios::in);
    if(not archCita.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCitas<<endl;
        exit(1);
    }
    ifstream archMedici(nombArchMedicinas,ios::in);
    if(not archMedici.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchMedicinas<<endl;
        exit(1);
    }
    ifstream archMeds(nombArchMedicos,ios::in);
    if(not archMeds.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchMedicos<<endl;
        exit(1);
    }
    ifstream archPac(nombArchPacientes,ios::in);
    if(not archPac.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchPacientes<<endl;
        exit(1);
    }
    ofstream archRep(nombArchReporte,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchReporte<<endl;
        exit(1);
    }
    
    int codPaciente;
    double porcDcto;
    archRep.precision(2);
    archRep<<fixed;
    imprimeEncabezados(archRep,'A');
    while(true){
        archPac>>codPaciente;
        if(archPac.eof())break;
        leeImprimeDatosPaciente(codPaciente,archPac,archRep,porcDcto);
        procesaCitas(codPaciente,porcDcto,archCita,archMeds,archMedici,archRep);
    }
    
    
    
    
}

void leeImprimeDatosPaciente(int codPaciente,ifstream &archPac,
                             ofstream &archRep, double &porcDcto){
    int distrito,anio;
    archRep<<left<<"PACIENTE : "<<codPaciente<<" - ";
    imprimeNombres(archPac,archRep,'A');
    archPac>>distrito>>anio>>porcDcto;
    archRep<<"Anio de nacimiento: "<<setw(8)<<anio<<"%Descuento: "<<right
           <<setw(6)<<porcDcto<<'%'<<endl;
    imprimeLinea(archRep,'-');
    archRep<<"CITAS:"<<endl;
    imprimeLinea(archRep,'-');
}

void procesaCitas(int codPaciente,double porcDcto,ifstream &archCita,
                  ifstream &archMeds,ifstream &archMedici,ofstream &archRep){
    int dd,mm,aa,codPacEval, horaI,horaF,codMedico;
    double pagoCita;
    char c;
    archCita.clear();
    archCita.seekg(0,ios::beg);
    while(true){
        archCita>>dd;
        if(archCita.eof())break;
        archCita>>c>>mm>>c>>aa>>codPacEval;
        if(codPacEval==codPaciente){
            horaI = obtenerHora(archCita);
            horaF = obtenerHora(archCita);
            int duracionEnS = horaF-horaI;
            archCita>>codMedico;
            imprimeEncabezados(archRep,'B');
            archRep<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
                    <<setw(4)<<aa<<setfill(' ')<<setw(3)<<' ';
            imprimeHora(duracionEnS,archRep);
//            buscaImprimeDatosMedico(codMedico,duracionEnS,archMeds,)
            while(archCita.get() != '\n');
        }
        else while(archCita.get() != '\n');
    }
}

int obtenerHora(ifstream &archCita){
    int hor,min,seg;
    char c;
    archCita>>hor>>c>>min>>c>>seg;
    return (hor*3600+min*60+seg);
}

void imprimeHora(int duracionEnS,ofstream &archRep){
    int hor,min,seg;
    hor = duracionEnS/3600;
    min = (duracionEnS - hor*3600)/60;
    seg = duracionEnS - hor*3600 - min*60;
    archRep<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'
           <<setw(2)<<seg<<"  "<<setfill(' ');
}

void imprimeNombres(ifstream &archIn,ofstream &archRep, char seleccion){
    int nroBlancos, nroCaracteres=0;
    char letra;
    archIn>>ws;
    if(seleccion=='A')
        archIn.get();
    while(true){
        letra = archIn.get();
        if(seleccion=='A'){
            if(letra=='/' or letra==']') break;
        }
        else
            if(letra==' ')break;
            nroCaracteres++;
        if (letra=='_') letra=' ';
        archRep.put(letra);
    }
    if(seleccion=='A')
        nroBlancos= MAXCARNOMB - nroCaracteres;
    else
        nroBlancos=MAXCARESP - nroCaracteres;
    archRep<<setw(nroBlancos)<<' ';
}

void imprimeEncabezados(ofstream &archRep,char seleccion){
    if(seleccion=='A'){
        archRep<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
        imprimeLinea(archRep,'=');
        archRep<<setw((37+TAMLINEA)/2)<<"DETALLE DE CITAS MEDICAS POR PACIENTE"<<endl;
        imprimeLinea(archRep,'=');
    }
    else if(seleccion=='B'){
        archRep<<left<<setw(13)<<"Fecha"<<setw(13)<<"Duracion"
               <<setw(MAXCARNOMB)<<"Medico"<<setw(MAXCARESP)<<"Especialidad"
                <<setw(20)<<"Pago por cita"<<endl;
    }
}

void imprimeLinea(ofstream &archRep,char c){
    for(int i=0;i<TAMLINEA;i++)
        archRep.put(c);
    archRep<<endl;
}