/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 12 de mayo de 2024, 12:07
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAMLINEA 100
#define MAXCARNOMB 60

void leerCicloEvaluar(int &year,int &ciclo){
    char c;
    cout<<"Ingrese el año y ciclo a evaluar, use el formato aaaa-ciclo:"<<endl;
    cin>>year>>c>>ciclo;
}

void generarReporte(int year,int ciclo,const char *nombArchAlu,
                    const char *nombArchCur, const char *nombArchEsc,
                    const char *nombArchMatr,const char *nombArchRep){
    //Apertura de archivos
    ifstream archAlu(nombArchAlu,ios::in);
    if(not archAlu.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchAlu<<endl;
        exit(1);
    }
    ifstream archCur(nombArchCur,ios::in);
    if(not archCur.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCur<<endl;
        exit(1);
    }
    ifstream archEsc(nombArchEsc,ios::in);
    if(not archEsc.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchEsc<<endl;
        exit(1);
    }
    ifstream archMatr(nombArchMatr,ios::in);
    if(not archMatr.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchMatr<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    
    int cantAlu=0, aaMat,cicloMat, codigoAlu;
    double totalPagado=0.0;
    char c;
    archRep.precision(2);
    archRep<<fixed;
    imprimeEncabezado(archRep,year,ciclo);
    while(true){
        
        archMatr>>aaMat;
        if(archMatr.eof())break;
        archMatr>>c>>cicloMat;
        if(year==aaMat and ciclo==cicloMat){
            archMatr>>codigoAlu;
            imprimeMatriculaAlumno(codigoAlu,aaMat,cicloMat,archMatr,archAlu,
                                   archCur,archEsc,archRep,totalPagado);
            cantAlu++;
        }
        else while(archMatr.get() != '\n');
    }
    archRep<<"RESUMEN: "<<endl;
    archRep<<"CANTIDAD TOTAL DE ALUMNOS: "<<setw(10)<<cantAlu<<"       ";
    archRep<<"MONTO TOTAL PAGADO: "<<setw(20)<<totalPagado;
}

void imprimeMatriculaAlumno(int codigoAlu,int aaMat,int cicloMat,
                            ifstream &archMatr,ifstream &archAlu,
                            ifstream &archCur,ifstream &archEsc,ofstream &archRep,
                            double &totalPagado){
    int codCurso, cantCur=0;
    double escala, totalPorAlu=0, totalCreditos=0;
    double creditos, monto;
    char escalaLetra;
    imprimeAlumnoRetornaEscala(codigoAlu,archAlu,archRep,escalaLetra);
    imprimeLinea(archRep,'-');
    escala = determinaCostoPorCreditoEscala(aaMat,cicloMat,escalaLetra,archEsc);
    imprimeEncabezadoCursos(archRep);
    while(true){
        if(archMatr.get() == '\n') break;
        archMatr>>codCurso;
        cantCur++;
        imprimeCursoYMonto(codCurso,cantCur,escala,archCur,archRep,
                           creditos,monto);
        totalPorAlu += monto;
        totalCreditos += creditos;
        totalPagado += monto;
    }
    imprimeLinea(archRep,'-');
    archRep<<"TOTAL CREDITOS: "<<setw(7)<<totalCreditos<<setw(5)<<' ';
    archRep<<"TOTAL MONTO PAGADO: "<<setw(10)<<totalPorAlu<<endl;
    imprimeLinea(archRep,'=');
//    while(archMatr.get() !='\n');
}

void imprimeAlumnoRetornaEscala(int codigoAlu,ifstream &archAlu,
                                ofstream &archRep,char &escalaLetra){
    int codAluN;
    archAlu.clear();
    archAlu.seekg(0,ios::beg);
    while(true){
        archAlu>>codAluN;
        if(archAlu.eof())break;
        if(codAluN==codigoAlu){
            archAlu>>ws;
            archRep<<"ALUMNO: "<<codAluN<<" - ";
            imprimeNombres(archAlu,archRep,'A');
            archAlu>>escalaLetra;
            archRep<<"ESCALA: "<<escalaLetra<<endl;
            break;
        }
        else{
            while(archAlu.get() != '\n');
        }
    }
}

double determinaCostoPorCreditoEscala(int aaMat,int cicloMat,char escalaLetra,
                                      ifstream &archEsc){
    int aaEval,cicloEval;
    double costoEscala;
    char c, escalaEval;
    archEsc.clear();
    archEsc.seekg(0,ios::beg);
    while(true){
        archEsc>>aaEval;
        if(archEsc.eof())break;
        archEsc>>c>>cicloEval>>escalaEval>>costoEscala;
        if(aaEval==aaMat and cicloEval==cicloMat and escalaEval==escalaLetra){
            return costoEscala;
        }
    }
}

void imprimeEncabezadoCursos(ofstream &archRep){
    archRep<<left<<setw(5)<<' '<<setw(MAXCARNOMB)<<"CURSO MATRICULADO"
           <<setw(10)<<' '<<setw(13)<<"CREDITOS"<<"MONTO PAGADO"<<right<<endl;
    imprimeLinea(archRep,'-');
}
void imprimeCursoYMonto(int codCurso,int cantCur,double escala,
                        ifstream &archCur,ofstream &archRep,
                        double &creditos, double &monto){
    int codCurEval;
    archCur.clear();
    archCur.seekg(0,ios::beg);
    while(true){
        archCur>>codCurEval;
        if(archCur.eof())break;
        if(codCurEval==codCurso){
            archCur>>ws;
            archRep<<" "<<setfill('0')<<setw(2)<<cantCur<<')'<<setfill(' ')
                   <<" "<<codCurEval<<" - ";
            imprimeNombres(archCur,archRep,'C');
            archCur>>creditos;
            break;
        }
        else while(archCur.get() != '\n');
    }
    archRep<<setw(2)<<' '<<setw(5)<<creditos<<setw(6)<<' ';
    monto = escala*creditos;
    archRep<<setw(13)<<monto<<endl;
}

void imprimeNombres(ifstream &archLectura,ofstream &archRep,char seleccion){
    int cantCar=0, cantBlancos;
    char letra;
    while(true){
        letra=archLectura.get();
        if(letra==' ')break;
        cantCar++;
        if(letra=='_') letra=' ';
        if(seleccion=='A'){
            if(letra >= 'a' and letra <='z')
                letra -= ('a'-'A');
        }
        archRep.put(letra);
    }
    cantBlancos = MAXCARNOMB-cantCar;
    archRep<<setw(cantBlancos)<<' ';
}

void imprimeEncabezado(ofstream &archRep, int year, int ciclo){
    archRep<<setw((TAMLINEA+24)/2)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    archRep<<setw((TAMLINEA+36)/2)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    archRep<<setw((TAMLINEA)/2)<<"CICLO: "<<year<<'-'<<ciclo<<endl;
    imprimeLinea(archRep,'=');
}
void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA;i++)
        archRep.put(caracter);
    archRep<<endl;
}