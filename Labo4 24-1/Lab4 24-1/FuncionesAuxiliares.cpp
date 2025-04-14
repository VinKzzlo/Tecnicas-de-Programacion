/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 5 de mayo de 2024, 14:01
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAMLINEA 120
#define MAXCARNOMB 40

void emiteReporteCitasMedicas(const char *nombArchCitas,const char *nombArchMedici,
                              const char *nombArchMedico, const char *nombArchRep){
    
    ifstream archCitas(nombArchCitas, ios::in);
    if (not archCitas.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCitas<<endl;
        exit(1);
    }
    
    ifstream archMedici(nombArchMedici, ios::in);
    if (not archMedici.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchMedici<<endl;
        exit(1);
    }
    
    ifstream archMedico(nombArchMedico, ios::in);
    if (not archMedico.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchMedico<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep, ios::out);
    if (not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    int codMedico, codMedMAX;
    double tarifa, pagoMedMAX=0.0;
    imprimeEncabezado(archRep);
    archRep.precision(2);
    archRep<<fixed;
    while(true){
        leeImprimeDatosMedico(archMedico,archRep,codMedico,tarifa);
        if(archMedico.eof()) break;
        leeImprimeDatosPacientes(codMedico,tarifa,archCitas,archMedici,archRep,
                                 codMedMAX,pagoMedMAX);
    }
    archRep<<"MEDICO QUE APORTO MAS INGRESOS AL INSTITUTO"<<endl;
    archRep<<"Codigo: "<<codMedMAX;
    
}

void leeImprimeDatosMedico(ifstream &archMedico,ofstream &archRep,
                           int &codMedico, double &tarifa){
    imprimeLinea(archRep,'=');
    archMedico>>codMedico;
    if (archMedico.eof())return;
    archRep<<"Codigo del medico: "<<setw(6)<<' '<<codMedico<<endl;
    archRep<<"Nombre del medico: "<<setw(6)<<' ';
    imprimeNombres(archMedico,archRep,'M');
    archRep<<"Especialidad del medico: ";
    imprimeNombres(archMedico,archRep,'E');
    archMedico>>tarifa;
    archRep<<"Tarifa: "<<setw(17)<<' '<<tarifa<<endl;
    archRep<<"PACIENTES ATENDIDOS"<<endl;
    
//    while(archMedico.get() != '\n');
}

//21/8/2023   45914393   81.22   14:18:52   16:45:39   89213   31389   7   85865   6
void leeImprimeDatosPacientes(int codMedico,double tarifa,
                              ifstream &archCitas,ifstream &archMedici,
                              ofstream &archRep, int &codMedMAX, double &pagoMedMAX){
    int dd,mm,aa, nroDNI, horaI, horaF, codMedCita, fecha, duracion;
    double porcDcto, pagoCita, pagoMedicinas=0.0;
    char c;
    archCitas.clear();
    archCitas.seekg(0,ios::beg);
    while(true){
        archCitas>>dd;
        if(archCitas.eof())break;
        archCitas>>c>>mm>>c>>aa>>nroDNI;
        fecha = aa*10000 + mm*100 + dd;
        archCitas>>porcDcto;
        horaI = obtenerHora(archCitas);
        horaF = obtenerHora(archCitas);
        duracion = horaF-horaI;
        archCitas>>codMedCita;
        if(codMedico == codMedCita and duracion<9085){
            imprimeDatosPaciente(fecha, nroDNI,horaI,horaF,duracion,
                                     porcDcto,tarifa,archRep,pagoCita);
            leeImprimeMedicinasRecetadas(porcDcto,archCitas,archMedici,archRep,
                                         pagoMedicinas);
            double pagoTotal = pagoCita+pagoMedicinas;
            imprimePagos(pagoMedicinas,pagoTotal,archRep);
            if(pagoTotal>pagoMedMAX){
                pagoMedMAX = pagoTotal;
                codMedMAX = codMedico;
            }
        }
        else while (archCitas.get() != '\n');
    }
}

void leeImprimeMedicinasRecetadas(double porcDcto,ifstream &archCitas,
                                  ifstream &archMedici,ofstream &archRep,
                                  double &pagoMedicinas){
    int numMedicinas=0, codMedici,codMediciEval, cantMedici;
    double precioMedicina, costoMedInd;
    imprimeEncabezadoMedicinas(archRep);
    while(true){
        if(archCitas.get() == '\n') break;
        archCitas>>codMedici>>cantMedici;
        archMedici.clear();
        archMedici.seekg(0,ios::beg);
        while(true){
            archMedici>>codMediciEval;
            if(archMedici.eof()) break;
            if(codMedici==codMediciEval){
                numMedicinas++;
                archRep<<setw(22)<<' '<<setfill('0')<<setw(2)<<numMedicinas<<setfill(' ')
                       <<setw(4)<<' '<<setw(5)<<codMediciEval<<setw(6)<<' ';
                imprimeNombres(archMedici,archRep,'D');
                archMedici>>precioMedicina;
                archRep<<setw(4)<<' '<<setw(3)<<cantMedici<<setw(5)<<' '
                       <<setw(7)<<precioMedicina<<setw(4)<<' ';
                costoMedInd = (precioMedicina*cantMedici)*(1-(porcDcto)/200);
                archRep<<setw(7)<<costoMedInd<<endl;
                pagoMedicinas += costoMedInd;
                break;
            }
            else while(archMedici.get() != '\n');
        }
    }
    if(numMedicinas == 0 ){
        archRep<<"NO SE RECETARON MEDICINAS EN ESTA CITA"<<endl;
    }
}

void imprimePagos(double pagoMedicinas,double pagoTotal, ofstream &archRep){
    archRep<<"Pago total por medicinas: "<<setw(8)<<pagoMedicinas<<endl;
    archRep<<"Pago total: "<<setw(14)<<' '<<setw(8)<<pagoTotal<<endl;
    
}

void imprimeDatosPaciente(int fecha, int nroDNI,int horaI,int horaF,int duracion,
               double porcDcto,double tarifa,ofstream &archRep,double &pagoCita){
    imprimeEncabezadoPaciente(archRep);
    imprimeFecha(fecha,archRep);
    archRep<<setw(8)<<nroDNI<<setw(2)<<' ';
    imprimeHora(horaI,archRep);
    imprimeHora(horaF,archRep);
    imprimeHora(duracion,archRep);
    archRep<<setw(20)<<porcDcto<<'%'<<setw(10)<<' ';
    calculaImprimePagoCita(tarifa,duracion,porcDcto,archRep,pagoCita);
    archRep<<endl;
    
}

void calculaImprimePagoCita(double tarifa, int duracion,double porcDcto,
                            ofstream &archRep,double &pagoCita){
    double duracionEnH, dctoAplicado;
    duracionEnH = duracion/(double)3600;
    pagoCita = tarifa*duracionEnH;
    dctoAplicado = pagoCita*(porcDcto/100);
    pagoCita -= dctoAplicado;
    archRep<<setw(8)<<pagoCita;
}
void imprimeEncabezadoPaciente(ofstream &archRep){
    imprimeLinea(archRep,'-');
    archRep<<left<<setw(12)<<"Fecha"<<setw(11)<<"Paciente"<<setw(11)<<"Inicio"
           <<setw(8)<<"Fin"<<setw(10)<<"Duracion"<<setw(27)<<"% de descuento por Seguro"
           <<setw(25)<<"Pago por cita"<<endl;
    imprimeLinea(archRep,'-');
    
}
void imprimeFecha(int fecha,ofstream &archRep){
    int dd,mm,aa;
    aa = fecha/10000;
    mm = (fecha - aa*10000)/100;
    dd = fecha - aa*10000 - mm*100;
    archRep<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
           <<setw(4)<<aa<<setfill(' ')<<setw(2)<<' ';
}

void imprimeEncabezadoMedicinas(ofstream &archRep){
    archRep<<"Medicinas recetadas:"<<endl;
    archRep<<left<<setw(22)<<' '<<setw(5)<<"No."<<setw(12)<<"Codigo"
           <<setw(MAXCARNOMB)<<"Descripción"<<setw(22)<<setw(14)<<"Cantidad"
           <<setw(12)<<"Precio"<<setw(6)<<"Pago"<<right<<endl;
}

int obtenerHora(ifstream &archCitas){
    int hor,min,seg;
    char c;
    archCitas>>hor>>c>>min>>c>>seg;
    return (hor*3600+min*60+seg);
}
void imprimeHora(int timeInS,ofstream &archRep){
    int hor,min,seg;
    hor = timeInS/3600;
    min = (timeInS - hor*3600)/60;
    seg = timeInS - hor*3600 - min*60;
    archRep<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'
           <<setw(2)<<seg<<setfill(' ')<<setw(2)<<' ';
}
void imprimeNombres(ifstream &archLectura,ofstream &archRep,char seleccion){
    int nroCaracteres=0, nroBlancos;
    char letra;
    archLectura>>ws;
    if (seleccion=='M'){
        archLectura.get();
    }
    while (true){
        letra = archLectura.get();
        if(seleccion=='M'){
            if(letra == '/') break;
        }
        else{
            if(letra == ' ') break;
        }
        nroCaracteres++;
        if(letra == '_') letra = ' ';
        archRep.put(letra);
    }
    nroBlancos = MAXCARNOMB - nroCaracteres;
    archRep<<setw(nroBlancos)<<' ';
    if(seleccion=='M' or seleccion=='E') archRep<<endl;
  
}

void imprimeEncabezado(ofstream &archRep){
    archRep<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea(archRep,'=');
    archRep<<setw((25+TAMLINEA)/2)<<"REGISTRO DE CITAS MEDICAS"<<endl;
}
void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA; i++)
        archRep.put(caracter);
    archRep<<endl;
}