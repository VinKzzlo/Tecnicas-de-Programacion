/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */
#include<fstream>
#include<iostream>
using namespace std;
#include "LeerArchivosArreglos.h"

#include<cmath>
#include<iomanip>

void LeerCoordenadas(double *ArrCoordX, double *ArrCoordY, int &cantVertices){
    ifstream archCoord("Poligono.txt" , ios::in);
    if(not archCoord.is_open()){
        cout<<"ERROR";
        exit(1);
    }
    
    int i=0;
    double x,y;
    while(true){
        archCoord>>x>>y;
        if(archCoord.eof()) break;
        ArrCoordX[i] = x;
        ArrCoordY[i] = y;
        i++;
    }
    cantVertices=i;
}


void ValidarArreglos(double *ArrCoordX, double *ArrCoordY, int cantVertices){
    ofstream archRep("ReporteArreglos.txt",ios::out);
    
    archRep<<"coord X     coordY"<<endl;
    archRep<<fixed;
    archRep.precision(2);
    for(int i=0 ; i<cantVertices ; i++){
        archRep<<setw(8)<<right<<ArrCoordX[i]<<setw(15)<<right<<ArrCoordY[i]<<endl;
    }
    
}

void CalcularDatosPoligono(double *ArrCoordX, double *ArrCoordY, int cantVertices, 
                                            double &area, double &perimetro, int &cantLados){
    
    double S1 = CalcularSumaFormula(ArrCoordX, ArrCoordY, cantVertices);
    double S2 = CalcularSumaFormula(ArrCoordY, ArrCoordX, cantVertices);
    area = (S1+S2)/2;
    
    CalcularPerimetro(ArrCoordX, ArrCoordY, cantVertices, perimetro, cantLados); 
    
}

double CalcularSumaFormula(double *ArrIni, double *ArrFin, int cantDatos){
    double suma=ArrIni[0]*ArrFin[cantDatos-1];
    for(int i=1 ; i<cantDatos ; i++){
        suma = suma + (ArrIni[i]*ArrFin[i-1]);
    }
    return suma;
}

void CalcularPerimetro(double *ArrCoordX, double *ArrCoordY, int cantVertices, double &perimetro, int &cantLados){
    perimetro = 0;
    cantLados=0;
    for(int i=0 ; i<cantVertices ; i++){
        double x_i = ArrCoordX[i];
        double y_i = ArrCoordY[i];
        
        double x_i_sig, y_i_sig;
        if(i==cantVertices-1){
            //como es el ultimo vertice
            //quiero el primer vertice
            x_i_sig = ArrCoordX[0];
            y_i_sig = ArrCoordY[0];            
        }else{
            //saco el siguiente vertice
            x_i_sig = ArrCoordX[i+1];
            y_i_sig = ArrCoordY[i+1];
        }      
        
        double lado_i_al_i_sig = sqrt( pow(x_i-x_i_sig,2) + pow(y_i-y_i_sig,2) );
        perimetro += lado_i_al_i_sig;
        cantLados++;
    }    
}

void ReportePoligono(double *ArrCoordX, double *ArrCoordY, int cantVertices, double area, double perimetro, int cantLados){
    ofstream archRep("ReportePoligonos.txt", ios::out);
    
    archRep<<"Coordenadas del Poligono"<<endl;
    archRep<<"coord X     coordY"<<endl;
    
    for(int i=0 ; i<cantVertices ; i++){
        archRep<<fixed;
        archRep.precision(2);
        archRep<<setw(8)<<right<<ArrCoordX[i]<<setw(15)<<right<<ArrCoordY[i]<<endl;
    }
    
    archRep<<setw(20)<<left<<"Area: "<<setw(6)<<right<<area<<endl;
    archRep<<setw(20)<<left<<"Perimetro: "<<setw(6)<<right<<perimetro<<endl;
    archRep<<setw(20)<<left<<"Cantidad de Lados: "<<setw(6)<<right<<cantLados<<endl;    
}