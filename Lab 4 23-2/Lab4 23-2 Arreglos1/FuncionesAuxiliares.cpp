/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 6 de mayo de 2024, 17:02
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cmath>
#include "FuncionesAuxiliares.h"

void leerDatos(const char *nombArch,double *coordX,double *coordY, int &numDat){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    double cooX, cooY;
    numDat=0;
    while(true){
        arch>>cooX;
        if(arch.eof())break;
        arch>>cooY;
        coordX[numDat] = cooX;
        coordY[numDat] = cooY;
        numDat++;
    }
}

void imprimeDatosArreglos(const char *nombArch,double *coordX,double *coordY,
                          int numDat){
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    char vertice='A';
    arch<<setw(10)<<"Vertice"<<setw(15)<<"Coordenada X"
            <<setw(15)<<"Coordenada Y"<<endl;
    arch.precision(2);
    arch<<fixed;
    for(int i=0; i<numDat; i++){
        arch<<setw(10)<<vertice<<setw(15)<<coordX[i]
            <<setw(15)<<coordY[i]<<endl;
        vertice++;
    }
    
}

void calcularAreaPerimetro(double *coordX,double *coordY,int numDat,
                           double &perimetro, double &area){
    double suma1=0.0, suma2=0.0;
    perimetro=0.0;
    for(int i=0; i<numDat; i++){
        if(i+1 == numDat) break;
        suma1 += coordY[i]*coordX[i+1];
        suma2 += coordX[i]*coordY[i+1];
        perimetro += sqrt(pow((coordX[i+1] - coordX[i]),2) +
                          pow((coordY[i+1] - coordY[i]),2));
    }
    suma1 += coordY[numDat-1]*coordX[0];
    suma2 += coordX[numDat-1]*coordY[0];
    perimetro += sqrt(pow((coordX[0] - coordX[numDat-1]),2) +
                          pow((coordY[0] - coordY[numDat-1]),2));
    area = fabs(suma2-suma1)/(double)2;
}

void imprimeReporteFinal(const char *nombArch, double *coordX,double *coordY,
                         int numDat,double perimetro,double area){
    
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    char vertice='A';
    arch<<setw((29+40)/2)<<"REPORTE DE DATOS DEL POLIGONO"<<endl;
    arch<<setw(10)<<"Vertice"<<setw(15)<<"Coordenada X"
            <<setw(15)<<"Coordenada Y"<<endl;
    arch.precision(2);
    arch<<fixed;
    for(int i=0; i<numDat; i++){
        arch<<setw(10)<<vertice<<setw(15)<<coordX[i]
            <<setw(15)<<coordY[i]<<endl;
        vertice++;
    }
    arch.precision(2);
    arch<<fixed;
    arch<<"El número de lados del poligono es: "<<setw(10)<<numDat<<endl;
    arch<<"El area del poligono es: "<<setw(10)<<area<<endl;
    arch<<"El perimetro del poligono es: "<<setw(10)<<perimetro<<endl;
    
}