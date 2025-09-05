/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 1 de junio de 2024, 1:14
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAMLINEA 112
#define NO_ENCONTRADO -1

void solicitarDatos(int &facultad){
    cout<<"Ingrese el codigo de facultad: "<<endl;
    cin>>facultad;
}

void cargarCalif(const char *nombArch, int *arrCodigoAlumnos,int *arrNumCursos,
                 double *arrSumaPonderada,double *arrNumCreditos, int &cantAlu){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    double creditos;
    char codCur[10];
    cantAlu=0;
    while(true){
        arch>>codCur;
        if(arch.eof())break;
        arch>>creditos;
        leerNotas(arch,creditos,arrCodigoAlumnos,arrNumCursos,arrSumaPonderada,
                  arrNumCreditos,cantAlu);
    }
}

void leerNotas(ifstream &arch,double creditos,int *arrCodigoAlumnos,int *arrNumCursos,
               double *arrSumaPonderada, double *arrNumCreditos, int &cantAlu){
    int codigo, nota, posAlu;
    while(true){
        arch>>codigo>>nota;
        posAlu = buscarAlumno(codigo,arrCodigoAlumnos,cantAlu);
        if(posAlu != NO_ENCONTRADO)
            actualizarArreglos(creditos,nota,arrNumCursos[posAlu],
                               arrSumaPonderada[posAlu],arrNumCreditos[posAlu]);
        else
            insertarOrdenado(codigo,creditos,nota,arrCodigoAlumnos,arrNumCursos,
                             arrSumaPonderada,arrNumCreditos,cantAlu);
        if(arch.get()=='\n')break;
    }
}

int buscarAlumno(int codigo,int *arrCodigoAlumnos,int cantAlu){
    int limInf=0, limSup=cantAlu-1, puntoMedio;
    while(true){
        if(limInf>limSup)return NO_ENCONTRADO;
        puntoMedio = (limInf+limSup)/2;
        if(codigo == arrCodigoAlumnos[puntoMedio]) return puntoMedio;
        if(codigo < arrCodigoAlumnos[puntoMedio])
            limSup = puntoMedio-1;
        else
            limInf = puntoMedio+1;
    }
}

void insertarOrdenado(int codigo,double creditos, int nota,
                      int *arrCodigoAlumnos,int *arrNumCursos,
                      double *arrSumaPonderada, double *arrNumCreditos,
                      int &cantAlu){
    int i;
    for (i=cantAlu-1; i>=0; i--)
        if (codigo < arrCodigoAlumnos[i]) {
            arrCodigoAlumnos[i+1] = arrCodigoAlumnos[i];
            arrNumCursos[i+1] = arrNumCursos[i];
            arrSumaPonderada[i+1] = arrSumaPonderada[i];
            arrNumCreditos[i+1] = arrNumCreditos[i];
        } else break;
    arrCodigoAlumnos[i+1] = codigo;
    arrNumCursos[i+1] = 0;
    arrSumaPonderada[i+1] = 0;
    arrNumCreditos[i+1] = 0;
    cantAlu++;
    actualizarArreglos(creditos,nota,arrNumCursos[i+1],arrSumaPonderada[i+1],
                       arrNumCreditos[i+1]);
}

void actualizarArreglos(double creditos,int nota,int &numCursos,
                        double &sumaPonderada,double &numCreditos){
    numCursos++;
    sumaPonderada += (nota*creditos);
    numCreditos += creditos;
}
void emitirReporte(const char *nombArchAlu,const char *nombArchFac,const char *nombArchRep,
                   int *arrCodigoAlumnos,int *arrNumCursos,
                   double *arrSumaPonderada,double *arrNumCreditos,
                   int cantAlu,int facultad){
    ifstream archAlu(nombArchAlu,ios::in);
    if(not archAlu.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchAlu<<endl;
        exit(1);
    }
    ifstream archFac(nombArchFac,ios::in);
    if(not archFac.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchFac<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep,ios::out);
    if(not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    archRep.precision(2);
    archRep<<fixed;
    imprimeEncabezado(archFac,archRep,facultad);
    imprimeAlumnos(facultad,archAlu,archRep,arrCodigoAlumnos,arrNumCursos,
                  arrSumaPonderada,arrNumCreditos,cantAlu);
    imprimeLinea(archRep,'=');
}

void imprimeAlumnos(int facultad,ifstream &archAlu,ofstream &archRep,
                   int *arrCodigoAlumnos,int *arrNumCursos,
                   double *arrSumaPonderada,double *arrNumCreditos,int cantAlu){
    int codAlu, codFacu, posAlu;
    double promedio;
    char nombAlu[50], nombModAlu[50];
    while(true){
        archAlu>>codAlu;
        if(archAlu.eof())break;
        archAlu>>nombAlu>>codFacu;
        posAlu = buscarAlumno(codAlu,arrCodigoAlumnos,cantAlu);
        if(posAlu != NO_ENCONTRADO and codFacu==facultad){
            modificarNombre(nombAlu,nombModAlu);
            promedio = arrSumaPonderada[posAlu]/arrNumCreditos[posAlu];
            archRep<<left<<codAlu<<" - "<<setw(40)<<nombAlu
                   <<right<<setw(7)<<arrNumCursos[posAlu]<<setw(17)<<arrSumaPonderada[posAlu]
                   <<setw(15)<<arrNumCreditos[posAlu]<<setw(18)<<promedio<<endl;
        }
    }
}

void imprimeEncabezado(ifstream &archFac,ofstream &archRep,int facultad){
    char nombFacu[30];
    int facu, longNomb;
    archRep<<setw((24+TAMLINEA)/2)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    archRep<<setw((46+TAMLINEA)/2)<<"PROMEDIO PONDERADO DE "
                                    "LOS ALUMNOS MATRICULADOS"<<endl;
    archRep<<setw((13+TAMLINEA)/2)<<"CICLO: 2024-1"<<endl;
    while(true){
        archFac>>nombFacu;
        if(archFac.eof())break;
        archFac>>facu;
        if(facu==facultad){
            quitaEspacios(nombFacu);
            longNomb = longitud(nombFacu);
            archRep<<setw((longNomb+TAMLINEA)/2)<<nombFacu<<endl;
            break;
        }
    }
    imprimeLinea(archRep,'=');
    archRep<<left<<setw(5)<<' '<<setw(45)<<"ALUMNO"<<setw(15)<<"No. de Cursos"
           <<setw(16)<<"Suma Ponderada"<<setw(17)<<"No. de Creditos"
           <<setw(16)<<"Prom Ponderado"<<endl;
    imprimeLinea(archRep,'-');
    
    
}
void imprimeLinea(ofstream &archRep,char c){
    for(int i=0;i<TAMLINEA;i++)
        archRep.put(c);
    archRep<<endl;
}

void modificarNombre(char *nombAlu,char *nombModAlu){
    
}

void quitaEspacios(char *nombre){
    for(int i=0;nombre[i];i++)
        if(nombre[i]=='_')nombre[i]=' ';
}
int longitud(char *nombre){
    int numCar;
    for(numCar=0;nombre[numCar];numCar++);
    return numCar;
}