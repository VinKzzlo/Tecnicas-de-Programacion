/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesReporte.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 28 de abril de 2024, 18:53
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesReporte.h"
#define TAMLINEA 122
#define MAXCARCANAL 38

void emitirReportePreferencias(const char *nombArchCan,const char *nombArchPref,
                              const char *nombArchTelv,const char *nombArchRep){
    
    ifstream archCan(nombArchCan,ios::in);
    if(not archCan.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchCan<<endl;
        exit(1);
    }
    
    ifstream archPref(nombArchPref,ios::in);
    if(not archPref.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchPref<<endl;
        exit(1);
    }
    
    ifstream archTel(nombArchTelv,ios::in);
    if(not archTel.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchTelv<<endl;
        exit(1);
    }
    
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    
    imprimeEncabezado(archRep);
    archRep.precision(2);
    archRep<<fixed;
    int canalEvaluar;
    while(true){
        int nroMen=0, nroJov=0, nroAdu=0, nroTel=0, timeT=0;
        int tiempoPromedioEnS;
        double porcMen, porcJov, porcAdu;
        imprimeEncabezadoCanal(archCan,archRep,canalEvaluar);
        if (archCan.eof())break;
        buscaImprimeTelevidentes(canalEvaluar,archPref,archTel,archRep,
                                 nroMen, nroJov, nroAdu, nroTel, timeT);
        imprimeLinea(archRep,'-');
        tiempoPromedioEnS = timeT/nroTel;
        
        archRep<<"PROMEDIO DE TIEMPO QUE VEN LOS TELEVIDENTES EL CANAL: ";
        imprimeHora(tiempoPromedioEnS,archRep);
        archRep<<endl;
        porcMen = (double)nroMen/nroTel;
        porcJov = (double)nroJov/nroTel;
        porcAdu = (double)nroAdu/nroTel;
        archRep<<"MENORES: "<<right<<setw(10)<<porcMen*100<<'%'<<endl;
        archRep<<"JOVENES: "<<right<<setw(10)<<porcJov*100<<'%'<<endl;
        archRep<<"ADULTOS: "<<right<<setw(10)<<porcAdu*100<<'%'<<endl;
        archRep<<"TOTAL DE PERSONAS QUE VEN EL CANAL: "<<nroTel<<endl;
    }
}

void buscaImprimeTelevidentes(int canalEvaluar,ifstream &archPref,ifstream &archTel,
                              ofstream &archRep,
                int &nroMen, int &nroJov, int &nroAdu, int &nroTel, int &timeT){
    int nroDNI, canal, horaI, horaF, duracionEnS;
    bool encontroCanal=false;
    
    archPref.clear();
    archPref.seekg(0,ios::beg);
    while(true){
        archPref>>nroDNI;
        if(archPref.eof()) break;
        while(true){
            archPref>>canal;
            horaI = obtenerHora(archPref);
            horaF = obtenerHora(archPref);
            duracionEnS = horaF - horaI;
            if (canal == canalEvaluar){
                imprimeDatosCliente(nroDNI,horaI,horaF,duracionEnS,archTel,archRep,nroTel,
                                    nroMen, nroJov, nroAdu);
                timeT += duracionEnS;               
            }
            if(archPref.get() == '\n') break;  
        }
        
    }
}

void imprimeDatosCliente(int nroDNI,int horaI,int horaF,int duracionEnS,
                         ifstream &archTel,ofstream &archRep, int &nroTel,
                         int &nroMen, int &nroJov, int &nroAdu ){
    int DNITel, fechaNacConvert;
    char sexo, compania;
    bool menor=false, joven=false, adulto=false;
    archTel.clear();
    archTel.seekg(0,ios::beg);
    while(true){
        archTel>>DNITel;
        if(archTel.eof())break;
        if(DNITel==nroDNI){
            archRep<<setw(10)<<nroDNI;
            imprimeNombreCliente(archTel,archRep);
            obtenerFechaNac(archTel,fechaNacConvert,nroMen,nroJov,nroAdu,
                            menor, joven, adulto);
            leeImprimeSexo(archTel,archRep);
            imprimeCategoria(archRep,menor,joven,adulto);
            leeImprimeCompania(archTel,archRep);
            imprimeHora(horaI,archRep);
            archRep<<'-';
            imprimeHora(horaF,archRep);
            archRep<<setw(11)<<' ';
            imprimeHora(duracionEnS,archRep);
            archRep<<left<<endl;
            nroTel++;
        }
        else
            while(archTel.get() != '\n');
    }
    
}

void imprimeNombreCliente(ifstream &archTel,ofstream &archRep){
    int nroCar=0, nroBlancos;
    char letra;
    bool mantenerMayus=true;
    archTel>>ws;
    while(true){
        letra = archTel.get();
        if(letra == ' ') break;
        if(letra == '_')
            letra = ' ';
        else if(mantenerMayus){
            mantenerMayus = false;
        }
        else{
            if(letra >= 'A' and letra <= 'Z')
                letra += ('a' - 'A');
            mantenerMayus = true;
        }
        archRep.put(letra);
        nroCar++;
    }
    nroBlancos = MAXCARCANAL - nroCar;
    archRep<<setw(nroBlancos)<<' ';
}

void obtenerFechaNac(ifstream &archTel,int &fechaNacConvert,
                     int &nroMen,int &nroJov,int &nroAdu,
                     bool &menor,bool &joven, bool &adulto){
    int dd,mm,aa;
    char c;
    archTel>>dd>>c>>mm>>c>>aa;
    fechaNacConvert = aa*10000 + mm*100 + dd;
    if(fechaNacConvert>20090000){
        nroMen++;
        menor=true;
    }
    else if(fechaNacConvert>19880000){
        nroJov++;
        joven=true;
    }
    else{
        nroAdu++;
        adulto=true;
    }
}

void leeImprimeSexo(ifstream &archTel, ofstream &archRep){
    char sexo;
    archTel>>sexo;
    if(sexo=='M')
        archRep<<setw(14)<<"Masculino";
    else if(sexo=='F')
        archRep<<setw(14)<<"Femenino";
}

void imprimeCategoria(ofstream &archRep,bool menor,bool joven,bool adulto){
    if(menor)
        archRep<<setw(11)<<"Menor";
    else if(joven)
        archRep<<setw(11)<<"Joven";
    else if(adulto)
        archRep<<setw(11)<<"Adulto";

}

void leeImprimeCompania(ifstream &archTel,ofstream &archRep){
    char comp;
    archTel>>comp;
    if(comp=='A')
        archRep<<setw(12)<<"TVPUCP";
    else if(comp=='B')
        archRep<<setw(12)<<"CableMas";
    else if(comp=='C')
        archRep<<setw(12)<<"TPVision";
}

void imprimeHora(int tiempoEnS, ofstream &archRep){
    int hor, min, seg;
    hor = tiempoEnS/3600;
    min = (tiempoEnS - hor*3600)/60;
    seg = tiempoEnS - hor*3600 - min*60;
    archRep<<right<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'
           <<setw(2)<<seg<<setfill(' ');
}

int obtenerHora(ifstream &archPref){
    int hor, min, seg;
    char c;
    archPref>>hor>>c>>min>>c>>seg;
    return (hor*3600 + min*60 + seg);
}

void imprimeEncabezadoCanal(ifstream &archCan,ofstream &archRep,
                            int &canalEvaluar){
    archCan>>canalEvaluar;
    if(archCan.eof())return;
    imprimeLinea(archRep,'=');
    archRep<<"CANAL: ";
    imprimeNombreCanal(archCan,archRep);
    archRep<<"NUMERO: "<<setw(3)<<canalEvaluar<<endl;
    archRep<<"LISTADO DE TELEVIDENTES QUE VEN EL CANAL:"<<endl;
    imprimeLinea(archRep,'-');
    archRep<<left<<setw(10)<<"DNI No."<<setw(MAXCARCANAL)<<"NOMBRE"<<setw(13)<<"SEXO"
           <<setw(12)<<"CATEGORIA"<<setw(17)<<"COMPANIA"<<setw(23)<<"RANGO"
           <<setw(11)<<"DURACION"<<endl;
    imprimeLinea(archRep,'-');
}

void imprimeNombreCanal(ifstream &archCan,ofstream &archRep){
    int nroCaracteres=0, nroBlancos;
    char letra;
    archCan>>ws;
    archCan.get();
    while(true){
        letra = archCan.get();
        if(letra == '/') break;
        nroCaracteres++;
        if(letra >= 'a' and letra <='z') letra -= ('a' - 'A');
        archRep.put(letra);
    }
    nroBlancos = MAXCARCANAL - nroCaracteres;
    archRep<<setw(nroBlancos)<<' ';
}

void imprimeEncabezado(ofstream &archRep){
    imprimeLinea(archRep,'=');
    archRep<<setw((38+TAMLINEA)/2)<<"EMPRESA DE OPINION DE MERCADO TP S. A."<<endl;
    archRep<<setw((37+TAMLINEA)/2)<<"AVENIDA UNIVERSITARIA 1234 San Miguel"<<endl;
    archRep<<setw((11+TAMLINEA)/2)<<"LIMA - PERU"<<endl;
    imprimeLinea(archRep,'=');
    archRep<<setw((69+TAMLINEA)/2)<<"REGISTRO DE PREFERENCIAS DE LOS "
                                  "TELEVIDENTES POR CANAL DE PREFERENCIA"<<endl;
}

void imprimeLinea(ofstream &archRep,char caracter){
    for(int i=0; i<TAMLINEA; i++)
        archRep.put(caracter);
    archRep<<endl;
}