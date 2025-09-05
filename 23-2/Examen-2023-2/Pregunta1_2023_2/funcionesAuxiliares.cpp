/* 
 * File:   main.cpp
 * Author:  Vicente Jorge
 * Código: 20222159
 * Created on 9 de octubre de 2023, 06:35 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "funcionesAuxiliares.h"

void inicializarArchYEmitirReporte(const char *nombArchRep,
        const char *nombArchAlu,const char *nombArchEsc,const char *nombArchCur,
        const char *nombArchMat,int anio,int ciclo){
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit (1);
    }
    ifstream archAlu(nombArchAlu,ios::in);
    if(not archAlu.is_open()){
        cout<<"No se pudo abrir el archivo "<<nombArchAlu<<endl;
        exit (1);
    }
    ifstream archEsc(nombArchEsc,ios::in);
    if(not archEsc.is_open()){
        cout<<"No se pudo abrir el archivo "<<nombArchEsc<<endl;
        exit (1);
    }
    ifstream archCur(nombArchCur,ios::in);
    if(not archCur.is_open()){
        cout<<"No se pudo abrir el archivo "<<nombArchCur<<endl;
        exit (1);
    }
    ifstream archMat(nombArchMat,ios::in);
    if(not archMat.is_open()){
        cout<<"No se pudo abrir el archivo "<<nombArchMat<<endl;
        exit (1);
    }
    procesarYEmitirReporte(archAlu,archCur,archEsc,archMat,archRep,anio,ciclo);
}

void procesarYEmitirReporte(ifstream &archAlu,ifstream &archCur,
        ifstream &archEsc,ifstream &archMat,ofstream &archRep,
        int anio,int ciclo){
    double totalPagado=0;
    char c;
    int cantAlu=0,anioMat,cicloMat,codeAlum;
    archRep.precision(2);
    archRep<<fixed;
    imprimirEncabezado(archRep,anio,ciclo);
    while(true){
        archMat>>anioMat;
        if(archMat.eof()) break;
        archMat>>c>>cicloMat;
        if(anio==anioMat and ciclo==cicloMat){
            archMat>>codeAlum;
            procesarMatricula(archAlu,archCur,archEsc,archRep,codeAlum,
                    totalPagado,anio,ciclo,archMat);
            cantAlu ++;
        }
        else{
            while(archMat.get()!='\n');
        }
    }
    procesarResumen(archRep,cantAlu,totalPagado);
}

void procesarMatricula(ifstream &archAlu,ifstream &archCur,ifstream &archEsc,
        ofstream &archRep,int codeAlum,double &totalPagado,int anio,int ciclo,
        ifstream &archMat){
    int curso,cantCur=0;
    double escala,montoAlu=0;
    double monto,creditos,creditosTotal=0;
    char tipoEscala;
    imprimirAlumnoYDefinirEscala(codeAlum,archAlu,archRep,tipoEscala);
    imprimirSalto(archRep,'-');
    escala=determinarEscala(tipoEscala,archEsc,anio,ciclo);
    archRep<<setw(20)<<"CURSO MATRICULADO"<<setw(57)<<"CREDITOS"<<setw(20)
            <<"MONTO PAGADO"<<endl;
    imprimirSalto(archRep,'-');
    while(true){
        archMat>>curso;
        cantCur ++;
        procesaCurso(archCur,archRep,curso,monto,creditos,cantCur,escala);
        totalPagado+=monto;
        montoAlu+=monto;
        creditosTotal+=creditos;
        if(archMat.get()=='\n') break;
    }
    imprimirSalto(archRep,'-');
    archRep<<"TOTAL CREDITOS: "<<setw(5)<<creditosTotal<<"  TOTAL MONTO PAGADO:"
            <<setw(10)<<montoAlu<<endl;
    imprimirSalto(archRep,'=');
}

void procesaCurso(ifstream &archCur,ofstream &archRep,int curso,double &monto,
        double &creditos,int cantCur,double escala){
    int curSeek;
    archRep<<" "<<setfill('0')<<setw(2)<<cantCur<<" )  "<<curso<<" - "
            <<setfill(' ');
    archCur.clear();
    archCur.seekg(0,ios::beg);
    while(true){
        archCur>>curSeek;
        if(archCur.eof()) break;
        if(curSeek==curso){
            archCur>>ws;
            imprimirCadena(archRep,archCur,true);
            archCur>>creditos;
            break;
        }
        else{
            while(archCur.get()!='\n');
        }
    }
    monto=escala*creditos;
    archRep<<creditos<<setw(20)<<monto<<endl;
}

void procesarResumen(ofstream &archRep,int cantAlu,double totalPagado){
    archRep<<"RESUMEN:"<<endl;
    archRep<<"CANTIDAD TOTAL DE ALUMNOS: "<<cantAlu
            <<"      MONTO TOTAL PAGADO:  "<<setw(10)<<totalPagado;
}

double determinarEscala(char tipoEscala,ifstream &archEsc,int anio,int ciclo){
    int anioSeek,cicloSeek;
    char c,escalaSeek;
    double costo,valor;
    archEsc.clear();
    archEsc.seekg(0,ios::beg);
    while(true){
        archEsc>>anioSeek;
        if(archEsc.eof()) break;
        archEsc>>c>>cicloSeek>>escalaSeek>>costo;
        if(anio==anioSeek and ciclo==cicloSeek and escalaSeek==tipoEscala)
            return costo;
    }
}

void imprimirAlumnoYDefinirEscala(int codeAlum,ifstream &archAlu,
        ofstream &archRep,char &escala){
    int codeSeek;
    archAlu.clear();
    archAlu.seekg(0,ios::beg);
    while(true){
        archAlu>>codeSeek;
        if(archAlu.eof()) break;
        if(codeAlum==codeSeek){
            archAlu>>ws;
            archRep<<"Alumno: "<<codeAlum<<" - ";
            imprimirCadena(archRep,archAlu,false);
            archAlu>>escala;
            archRep<<setw(10)<<"ESCALA: "<<escala<<endl;
            break;
        }
        else{
            while(archAlu.get()!='\n');
        }
    }
}

void imprimirCadena(ofstream &archRep,ifstream &archDatos,bool curso){
    int cantCar=0,cantBlanc;
    char c;
    bool mayus=true;
    while(true){
        c=archDatos.get();
        if(c==' ') break;
        if(curso){
            if(c=='_'){
                archRep.put(' ');
                c=archDatos.get();
                cantCar ++;
                mayus=true;
            }
            cambiarCar(c,mayus);
            mayus=false;
        }
        else{
            cambiarCar(c,true);
        }
        archRep.put(c);
        cantCar ++;
    }
    cantBlanc=55-cantCar;
    archRep<<setw(cantBlanc)<<' ';
}

void cambiarCar(char &c,bool mayus){
    if(mayus){
        if(c<='z' and c>='a')
            c-='a'-'A';
    }
    else{
        if(c<='Z' and c>='A')
            c-='A'-'a';
    }
    if(c=='_')
        c=' ';
}

void imprimirEncabezado(ofstream &archRep,int anio,int ciclo){
    archRep<<setw(50)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    archRep<<setw(56)<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl;
    archRep<<setw(35)<<"CICLO: "<<anio<<" - "<<ciclo<<endl;
    imprimirSalto(archRep,'=');
}

void imprimirSalto(ofstream &archRep,char c){
    for(int i=0;i<100;i++)
        archRep<<c;
    archRep<<endl;
}

void ingresarFechas(int &anio,int &ciclo){
    char c;
    cout<<"Ingrese el año y ciclo a procesar en formato: aaaa-ciclo: ";
    cin>>anio>>c>>ciclo;
}
