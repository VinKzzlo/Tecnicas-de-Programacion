/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 3 de junio de 2024, 16:14
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "FuncionesAuxiliares.h"


void solicitarDatos(int &semestre){
    int anho, ciclo;
    char c;
    cout<<"Ingrese el anho y el ciclo en el formato AAAA-C"<<endl;
    cin>>anho>>c>>ciclo;
    semestre = anho*10+ciclo;
}

void leerDatosAlumnos(const char *nombArch,int *alumnosCods,char **alumnosNomb,
                      char *alumnosEsc,int &numAlu){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    int codigo;
    char escala, *cadena;
    numAlu=0;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        alumnosCods[numAlu] = codigo;
        arch>>ws;
        cadena = leerCadenaExacta(arch,' ');
        modificarCadena(cadena);
        alumnosNomb[numAlu] = cadena;
        arch>>ws>>escala;
        alumnosEsc[numAlu] = escala;
        numAlu++;
    }
    ordenarAlumnos(alumnosCods,alumnosNomb,alumnosEsc,numAlu);
    
//    for(int i=0;i<numAlu;i++)
//         cout<<setw(10)<<alumnosCods[i]<<"  "<<left<<setw(40)<<alumnosNomb[i]
//            <<"  "<<alumnosEsc[i]<<right<<endl;
}
void ordenarAlumnos(int *alumnosCods,char **alumnosNomb,
                    char *alumnosEsc,int numAlu){
    for(int i=0; i<numAlu-1;i++)
        for(int j=i+1;j<numAlu;j++)
            if(alumnosCods[i]>alumnosCods[j]){
                cambiarInt(alumnosCods[i],alumnosCods[j]);
                cambiarStr(alumnosNomb[i],alumnosNomb[j]);
                cambiarChr(alumnosEsc[i],alumnosEsc[j]);
            }
    
}

void leerDatosCursos(const char *nombArch,int *cursosCods,double *cursosCreds,
                     int &numCur){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double creds;
    numCur=0;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        cursosCods[numCur] = codigo;
        arch>>ws;
        while(arch.get() != ' ');
        arch>>creds;
        cursosCreds[numCur] = creds;
        numCur++;
    }
    ordenarCursos(cursosCods,cursosCreds,numCur);
    
    for(int i=0;i<numCur;i++)
         cout<<setw(10)<<cursosCods[i]<<"    "<<cursosCreds[i]<<endl;
}
void ordenarCursos(int *cursosCods,double *cursosCreds, int numCur){
    for(int i=0;i<numCur-1;i++)
        for(int j=i+1;j<numCur;j++)
            if(cursosCods[i]>cursosCods[j]){
                cambiarInt(cursosCods[i],cursosCods[j]);
                cambiarDbl(cursosCreds[i],cursosCreds[j]);
            }
}
void leerDatosEscalas(const char *nombArch,int *escalasSemestre,
                      double *escalasPrecio, char *escalasLetra,int &numEsc){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int anho, ciclo;
    double precio;
    char escala,c;
    numEsc=0;
    while(true){
        arch>>anho;
        if(arch.eof())break;
        arch>>c>>ciclo;
        escalasSemestre[numEsc] = (anho*10+ciclo);
        arch>>escala>>precio;
        escalasLetra[numEsc] = escala;
        escalasPrecio[numEsc] = precio;
        numEsc++;
    }
//    for(int i=0;i<numEsc;i++)
//         cout<<setw(10)<<escalasSemestre[i]<<"  "<<left<<setw(10)<<escalasLetra[i]
//            <<"   "<<escalasPrecio[i]<<right<<endl;
}

void procesarMatricula(const char *nombArch,int semestre,
                      int *alumnosCods,char **alumnosNomb,
                      char *alumnosEsc,int numAlu,
                      int *cursosCods,double *cursosCreds, int numCur,
                      int *escalasSemestre, double *escalasPrecio, 
                      char *escalasLetra,int numEsc,
                   int *alumnosNroCur,double *alumnosCreds,double *alumnosPago){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    
}

void cambiarInt(int &datoI,int &datoJ){
    int aux;
    aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}
void cambiarDbl(double &datoI,double &datoJ){
    double aux;
    aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}
void cambiarStr(char *&cadenaI,char *&cadenaJ){
    char *aux;
    aux = cadenaI;
    cadenaI = cadenaJ;
    cadenaJ = aux;
}

void cambiarChr(char &datoI,char &datoJ){
    char aux;
    aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}


char *leerCadenaExacta(ifstream &arch,char delimitador){
    char buffer[60], *cadena;
    arch.getline(buffer,60,delimitador);
    if(arch.eof())return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

void modificarCadena(char *cadena){
    int longitud = strlen(cadena);
    for(int i=0; i<longitud;i++){
        if(cadena[i]=='_') cadena[i]=' ';
        if(cadena[i]>='a' and cadena[i]<='z') cadena[i] -= ('a'-'A');
    }
}