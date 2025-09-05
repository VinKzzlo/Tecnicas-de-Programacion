/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 27 de mayo de 2024, 13:57
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAMLINEA 111
#define NO_ENCONTRADO -1


void solicitarDatos(int &anio,int &ciclo){
    cout<<"Ingrese el anio:"<<endl;
    cin>>anio;
    cout<<"Ingrese el ciclo:"<<endl;
    cin>>ciclo;
}

void leerAlumnos(const char *nombArch, int *alumnoCods,
                 char *alumnoEsc, int &cantAlu){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    char escala;
    cantAlu=0;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch>>ws>>escala;
        insertarOrdenado(alumnoCods,alumnoEsc,codigo,escala,cantAlu);
    }
}

void insertarOrdenado(int *alumnoCods,char *alumnoEsc,
                      int codigo,char escala,int &cantAlu){
    int i=cantAlu-1;
    while(i>=0 and alumnoCods[i]>codigo){
        alumnoCods[i+1] = alumnoCods[i];
        alumnoEsc[i+1] = alumnoEsc[i];
        i--;
    }
    alumnoCods[i+1] = codigo;
    alumnoEsc[i+1] = escala;
    cantAlu++;
}

void leerCursos(const char *nombArch,int *cursosCods,
                double *cursosCreds, int &cantCur){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double creditos;
    cantCur=0;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch>>ws;
        while(arch.get() != ' ');
        arch>>creditos;
        insertarCurOrd(cursosCods,cursosCreds,cantCur,codigo,creditos);
    }
}
void insertarCurOrd(int *cursosCods,double *cursosCreds,int &cantCur,
                    int codigo,double creditos){
    int i=cantCur-1;
    while(i>=0 and cursosCods[i]>codigo){
        cursosCods[i+1] = cursosCods[i];
        cursosCreds[i+1] = cursosCreds[i];
        i--;
    }
    cursosCods[i+1] = codigo;
    cursosCreds[i+1] = creditos;
    cantCur++;
}

void leerEscalas(const char *nombArch,int *escSemestre,double *escCostoXCred,
                 char *escLetra,int &cantEsc){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int anio,ciclo, semestre;
    double costo;
    char escala, c;
    cantEsc=0;
    while(true){
        arch>>anio;
        if(arch.eof())break;
        arch>>c>>ciclo;
        semestre = anio-10+ciclo;   
        arch>>ws>>escala>>costo;
        insertarEscOrd(escSemestre,escCostoXCred,escLetra,cantEsc,
                       semestre,escala,costo);
    }
}
void insertarEscOrd(int *escSemestre,double *escCostoXCred,char *escLetra,
                    int &cantEsc,int semestre,char escala,double costo){
    int i=cantEsc-1;
    while(i>=0 and escSemestre[i]>semestre){
        escSemestre[i+1] = escSemestre[i];
        escCostoXCred[i+1] = escCostoXCred[i];
        escLetra[i+1] = escLetra[i];
        i--;
    }
    escSemestre[i+1] = semestre;
    escCostoXCred[i+1] = costo;
    escLetra[i+1] = escala;
    cantEsc++;
}

void updateTotalAlu(const char *nombArch,int semestre,
                    int *alumnoCods, char *alumnoEsc, int cantAlu,
                    int *cursosCods, double *cursosCreds, int cantCur,
            int *escSemestre,double *escCostoXCred, char *escLetra,int cantEsc,
            int *alumnoNroCurs,double *alumnoCredsMat,double *alumnoMontoPaga){
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int anio,ciclo,semestEval, codAlumno, posAlu, codCurso, posCurso, posEscala;
    char c;
    while(true){
        arch>>anio;
        if(arch.eof())break;
        arch>>c>>ciclo>>codAlumno;
        semestEval = anio*10+ciclo;
        posAlu = busquedaBinaria(alumnoCods,codAlumno,cantAlu);
        if(semestre == semestEval and posAlu!=NO_ENCONTRADO){
            while(true){
                arch>>codCurso;
                posCurso = busquedaBinaria(cursosCods,codCurso,cantCur);
                posEscala = buscarEscala(semestre,alumnoEsc[posAlu],escSemestre,
                                         escLetra,cantEsc);
                if(posCurso!= NO_ENCONTRADO and posEscala != NO_ENCONTRADO){
                    alumnoNroCurs[posAlu]++;
                    alumnoCredsMat[posAlu]+=cursosCreds[posCurso];
                    alumnoMontoPaga[posAlu]+=escCostoXCred[posEscala]*cursosCreds[posCurso];
                }
                if(arch.get() == '\n') break;
            }
        }
        else while(arch.get() != '\n');
    }
}

int busquedaBinaria(int *arreglo,int dato,int cantidad){
    int limiteInf=0, limiteSup=cantidad-1, puntoMedio;
    while(true){
        if(limiteInf>limiteSup) return NO_ENCONTRADO;
        puntoMedio = (limiteInf+limiteSup)/2;
        if(dato==arreglo[puntoMedio])  return puntoMedio;
        if(dato < arreglo[puntoMedio])
            limiteSup = puntoMedio-1;
        else
            limiteInf = puntoMedio+1;
    }
}

int buscarEscala(int semestre,char alumnoEsc,int *escSemestre,char *escLetra,
                 int cantEsc){
    for(int i=0;i<cantEsc;i++){
        if(semestre==escSemestre[i] and alumnoEsc==escLetra[i]) return i;
    }
    return NO_ENCONTRADO;
}

void emitirReporte(const char *nombArchNomb,const char *nombArchApell,
                  const char *nombArchRep, int semestre,
                  int *alumnoCods,int *alumnoNroCurs,double *alumnoCredsMat,
                  char *alumnoEsc,double *alumnoMontoPaga,int cantAlu){
    ifstream archNomb(nombArchNomb,ios::in);
    if (not archNomb.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchNomb<<endl;
        exit(1);
    }
    ifstream archApell(nombArchApell,ios::in);
    if (not archApell.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchApell<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep,ios::out);
    if (not archRep.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchRep<<endl;
        exit(1);
    }
    archRep.precision(2);
    archRep<<fixed;
    imprimeEncabezado(archRep,semestre);
    imprimePorAlumno(archNomb,archApell,archRep,alumnoCods,alumnoNroCurs,
                     alumnoCredsMat,alumnoEsc, alumnoMontoPaga,cantAlu);
    imprimeLinea(archRep,'-');
    
}

void imprimePorAlumno(ifstream &archNomb,ifstream &archApell,ofstream &archRep,
                      int *alumnoCods,int *alumnoNroCurs,double *alumnoCredsMat,
                      char *alumnoEsc,double *alumnoMontoPaga,int cantAlu){
    char apellidoPat_Nomb[50], apellidoMat[30], nombreCompleto[100];
    int codigo, posAlumno;
    while(true){
        archApell>>apellidoMat;
        if(archApell.eof())break;
        archNomb>>codigo;
        if(archNomb.eof())break;
        archNomb>>apellidoPat_Nomb;
        modificaTexto(apellidoMat,apellidoPat_Nomb,nombreCompleto);
        posAlumno=busquedaBinaria(alumnoCods,codigo,cantAlu);
        archRep<<alumnoCods[posAlumno]<<" - ";
        archRep<<left<<setw(40)<<nombreCompleto<<setw(15)<<alumnoNroCurs[posAlumno]
                <<setprecision(2)<<setw(10)<<alumnoCredsMat[posAlumno]<<setw(10)
                <<alumnoEsc[posAlumno]<<setprecision(2)<<alumnoMontoPaga[posAlumno]<<endl;
    }
}

void modificaTexto(const char *apellidoMat,const char *apellidoPat_Nomb,
                   char *nombreCompleto){
    int i=0;
    while(true){
        nombreCompleto[i]=apellidoPat_Nomb[i];
        if(nombreCompleto[i]=='_')break;
        i++;
    }
    nombreCompleto[i+1]=0;
    copiar(nombreCompleto+longitud(nombreCompleto),apellidoMat);
    copiar(nombreCompleto+longitud(nombreCompleto),apellidoPat_Nomb+i);
    agregaEspaciosYPasaMayus(nombreCompleto);
}

int longitud(const char *arreglo){
    int numCar;
    for(numCar=0;arreglo[numCar];numCar++);
    return numCar;
}

void copiar(char *destino, const char *fuente){
    int i=0;
    while(true){
        destino[i]=fuente[i];
        if(fuente[i]==0)break;
        i++;
    }
}

void agregaEspaciosYPasaMayus(char *arreglo){
    for(int i=0;arreglo[i];i++){
        if(arreglo[i]>='a' and arreglo[i]<='z') arreglo[i] -= 'a'-'A';
        if(arreglo[i]=='_')arreglo[i]=' ';
    }
}

void imprimeEncabezado(ofstream &archRep,int semestre){
    archRep<<setw((24+TAMLINEA)/2)<<"INSTITUCION EDUCATIVA TP"<<endl;
    archRep<<setw((36+TAMLINEA)/2)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    archRep<<setw((5+TAMLINEA)/2)<<"CICLO: "<<semestre/10<<'-'<<semestre%10<<endl;
    imprimeLinea(archRep,'=');
    archRep<<"ALUMNO"<<"  "<<"No. DE Cursos"<<"  "<<"CREDITOS"<<"  "<<"ESCALA"
           <<"  "<<"MONTO PAGADO"<<endl;
    imprimeLinea(archRep,'-');
}

void imprimeLinea(ofstream &archRep,char c){
    for(int i=0;i<TAMLINEA;i++)
        archRep.put(c);
    archRep<<endl;
}