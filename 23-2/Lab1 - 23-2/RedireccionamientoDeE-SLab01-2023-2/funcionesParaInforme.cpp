

/* 
 * File:   funcionesParaInforme.cpp
 * Author: asant
 *
 * Created on 7 de abril de 2024, 22:27
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "funcionesParaInforme.h"
#define LONGLINEA 162

void generarEImprimirReporte(){
    int nroDNI, sexo, fechaNac, horaP, horaA, duracion, canal1, canal2, canal3,
            compania;
    //variables de las estadisticas
    int nroTelevidentes=0, cantEst1=0, cantEst2=0, cantEst3=0, cantEst4=0,
            cantEst5=0, cantEst6=0, cantEst7=0, cantMujeres=0, cantHombres=0,
            cantAdultos=0, cantMenores=0, totalCanalesVistos=0;
    imprimirEncabezado();
    //empezar a leer y procesar datos
    while(true){
        cin>>nroDNI;
        if(cin.eof()) break;
        nroTelevidentes++;
        cin>>sexo;
        fechaNac = convertirFechaUHora('F');
        horaP = convertirFechaUHora('H');
        horaA = convertirFechaUHora('F');
        cin>>canal1>>canal2>>canal3>>compania;
        imprimeDatosYProcesaEstad(nroDNI,sexo,fechaNac,horaP,horaA,canal1,
                                  canal2, canal3, compania, &cantEst1, &cantEst2, 
                                  &cantEst3, &cantEst4, &cantEst5, &cantEst6,
                &cantEst7, &cantMujeres, &cantHombres, &cantAdultos, &cantMenores, &totalCanalesVistos);
    }
}

void imprimeDatosYProcesaEstad(int nroDNI,int sexo,int fechaNac,int horaP,int horaA,int canal1,
                                  int canal2,int canal3,char compania, int &cantEst1, int &cantEst2, 
                                 int  &cantEst3, int &cantEst4, int &cantEst5, int &cantEst6,
                int &cantEst7, int &cantMujeres, int &cantHombres, int &cantAdultos, int&cantMenores, int &totalCanalesVistos){
    
}


int convertirFechaUHora(char seleccion){
    int dd_hora, mm_min, aa_seg;
    char caracter;
    cin>>dd_hora>>caracter>>mm_min>>caracter>>aa_seg;
    if(seleccion='F')
        return (aa_seg*10000 + mm_min*100 + dd_hora);
    else
        return (dd_hora*3600 + mm_min*60 + aa_seg);
}

void imprimirEncabezado(){
    cout<<setw((35+LONGLINEA)/2)<<"EMPRESA DE OPINION DE MERCADO S. A."<<endl;
    imprimirLinea('=');
    cout<<setw((44+LONGLINEA)/3)<<"REGISTRO DE PREFERENCIAS DE LOS TELEVIDENTES"
        <<endl;
    imprimirLinea('=');
    cout<<setw(11)<<"DNI No."<<setw(15)<<"Sexo"<<setw(22)<<"Categoria";
    cout<<setw(19)<<"Hora(P)"<<setw(16)<<"Hora(A)"<<setw(21)<<"Duracion(H:M:S)";
    cout<<setw(18)<<"Duracion(H)"<<setw(15)<<"Canales"<<setw(20)<<"Compania";
    cout<<endl;
    imprimirLinea('-');
    
}

void imprimirLinea(char c){
    for(int i=0;i<LONGLINEA;i++){
        cout<<c;
    }
    cout<<endl;
}