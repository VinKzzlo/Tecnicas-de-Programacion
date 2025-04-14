

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "Funciones.h"


void leerArchivosYImprimir(const char *nombArchMed, const char *nombArchMedic, 
                           const char *nombArchCitas, const char *nombArchRep){
//    Abrir archivos
    ifstream archMed(nombArchMed, ios::in);
    if(not archMed.is_open()){
        cout<<"ERROR, no se puede abrir el archivo"<<nombArchMed<<endl;
        exit(1);
    }
    ifstream archMedic(nombArchMedic, ios::in);
    if(not archMedic.is_open()){
        cout<<"ERROR, no se puede abrir el archivo"<<nombArchMedic<<endl;
        exit(1);
    }
    ifstream archCitas(nombArchCitas, ios::in);
    if(not archCitas.is_open()){
        cout<<"ERROR, no se puede abrir el archivo"<<nombArchCitas<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep, ios:: out);
    if(not archRep.is_open()){
        cout<<"ERROR, no se puede abrir el archivo"<<nombArchRep<<endl;
        exit(1);
    }
    int codigoMed;
    char c;
    
    //Leer archivo de Medicos
    //50611     /EDGAR MUNOZ VERGEL/   Urologia   337.03
    while(true){
        archMed>>codigoMed;
        if(archMed.eof()) break;
        leerNombre(archMed);
        while (archMed.get() != '\n');
    }
    
}
void leerNombre(ifstream &archMed){
     
}
    