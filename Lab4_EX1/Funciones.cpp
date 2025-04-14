

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Funciones.h"
#define MAXLINEA 115
void emitirReporte(const char*nombArchRep, const char *nombArchMedicinas, 
                   const char*nombArchMedicos, const char*nombArchCitas){
    ofstream archRep(nombArchRep, ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchRep<<endl;
        exit(1);
    }
    ifstream archMedicinas(nombArchMedicinas, ios::in);
    if(not archMedicinas.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchMedicinas<<endl;
        exit(1);
    }
    ifstream archMedicos(nombArchMedicos, ios::in);
    if(not archMedicos.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchMedicos<<endl;
        exit(1);
    }
    ifstream archCitas(nombArchCitas, ios::in);
    if(not archCitas.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchCitas<<endl;
        exit(1);
    }
    // 50611     /EDGAR MUNOZ VERGEL/   Urologia   337.03
    int codigo;
    double tarifa;
    char c;
    imprimirEncabezado(archRep);
    cout.precision(2);
    cout<<fixed;
    while(true){
        archMedicos>>codigo;
        if(archMedicos.eof()) break;
        archRep<<"Codigo del medico: "<<codigo<<endl;
        
        archMedicos>>ws;
        archRep<<"Nombre del medico: ";
        archMedicos.get();
        while(true){
            c=archMedicos.get();
            if(c=='/') break;
            c-=((c>='a' and c<='z')? 'a'-'A':0);
            archRep<<c;
        }
        archRep<<endl;
        leerEspecialidad(archMedicos, archRep);
        archMedicos>>tarifa;
        archRep<<"Tarifa: "<<tarifa<<endl; 
        imprimirEncabezado2(archRep);
        
        leerCitasMedicas(archCitas, archRep);
        
//        while(archMedicos.get() != '\n');
        
    }
    
}
void leerCitasMedicas(ifstream &archCitas, ofstream &archRep){
    // 9/9/2023   94683380   2.60   11:17:52   12:48:30   40414   28409   5
    int dd, mm, aa, dni;
    int hh1, mm1, ss1, hh2, mm2, ss2;
    double dscto, duracionH, pago;
    char c;
    while(true){
        archCitas>>dd>>c>>mm>>c>>aa;
        if(archCitas.eof()) break;
        archCitas>>dni;
        archCitas>>dscto;
        archCitas>>hh1>>c>>mm1>>c>>ss1;
        archCitas>>hh2>>c>>mm2>>c>>ss2;
        archRep<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa
               <<setfill(' ');
        archRep<<setw(14)<<dni;
        archRep<<setfill('0')<<setw(2)<<hh1<<':'<<setw(2)<<mm1<<':'<<setw(2)
               <<ss1<<setfill(' ');
        archRep<<setfill('0')<<setw(2)<<hh2<<':'<<setw(2)<<mm2<<':'<<setw(2)
               <<ss2<<setfill(' ')<<endl;
//        imprimirDuracion(hh1, mm1, ss1, hh2, mm2, ss2, archRep, &duracionH);
//        archRep<<setw(12)<<dscto;
//        
//        pago = pago + dscto*duracionH;
//        archRep<<setw(10)<<pago;
//        lecturaVariable(archCitas, archRep);
        break;
    }
    
    
    
}
void leerEspecialidad(ifstream &archMedicos, ofstream &archRep){
    char c;
    archRep<<"Especialidad: ";
    archMedicos>>ws;
    while(true){
        c=archMedicos.get();
        if(c==' ') break;
        c-=((c>='a' and c<='z')? 'a'-'A':0);
        archRep<<c;
    }
    archRep<<endl;
}
void imprimirEncabezado(ofstream &archRep){
    archRep<<setw(60)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea('=', MAXLINEA, archRep);
    archRep<<setw(60)<<"REGISTRO DE CITAS MEDICAS"<<endl;
    imprimeLinea('=', MAXLINEA, archRep);
}
void imprimeLinea(char c, int n, ofstream &archRep){
    for(int i=0; i<n; i++){
        archRep<<c;
    }
    archRep<<endl;
    
}
void imprimirEncabezado2(ofstream &archRep){
    archRep<<"PACIENTES ATENDIDOS"<<endl;
    imprimeLinea('=', MAXLINEA, archRep);
    archRep<<setw(10)<<"Fecha"<<setw(12)<<"Paciente"<<setw(12)<<"Inicio"
           <<setw(12)<<"Fin"<<setw(12)<<"Duracion"<<setw(30)<<"% por descuento"
            " por Seguro"<<setw(15)<<"Pago por cita"<<endl;
    imprimeLinea('=', MAXLINEA, archRep);
}