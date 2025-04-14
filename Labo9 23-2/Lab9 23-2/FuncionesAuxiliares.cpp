/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 15 de junio de 2024, 2:04
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "FuncionesAuxiliares.h"
#include "Curso.h"
#include "Alumno.h"
#include "Escala.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 111

void solicitarDatos(int &semestre){
    int anio,ciclo;
    char c;
    cout<<"Ingrese el anho y ciclo en formato AAAA-C"<<endl;
    cin>>anio>>c>>ciclo;
    semestre = anio*10+ciclo;
}

void leerEscalas(const char *nombArch,struct Escala *escalas,int &numEsc){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int anio,ciclo;
    double costo;
    char c, escala;
    numEsc=0;
    while(true){
        arch>>anio;
        if(arch.eof())break;
        arch>>c>>ciclo;
        arch.get();
        arch>>escala>>c>>costo;
        escalas[numEsc].semestre = anio*10+ciclo;
        escalas[numEsc].escala = escala;
        escalas[numEsc].pagoXCred = costo;
        numEsc++;
    }
    
}

void leerCursos(const char *nombArch,struct Curso *cursos,int &numCur){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo;
    double creditos;
    char *nombre;
    numCur=0;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        nombre = leerCadenaExacta(arch,',');
        arch>>creditos;
        cadenaAMayus(nombre);
        cursos[numCur].codigo = codigo;
        cursos[numCur].nombre = nombre;
        cursos[numCur].numCreds = creditos;
        cursos[numCur].alumnos = new struct Alumno[50]{};
        numCur++;
    }
}

void leerMatricula(const char *nombArchMat,struct Curso *cursos,
                   int numCur, int semestre,const char *nombArchAlu,
                   struct Escala *escalas,int numEsc){
    ifstream archMat(nombArchMat,ios::in);
    if(not archMat.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchMat<<endl;
        exit(1);
    }
    ifstream archAlu(nombArchAlu,ios::in);
    if(not archAlu.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArchAlu<<endl;
        exit(1);
    }
    int anio,ciclo,semestEval, codAlu, codCur, posCur, na;
    char c;
    while(true){
        archMat>>anio;
        if(archMat.eof())break;
        archMat>>c>>ciclo;
        semestEval = anio*10+ciclo;
        if(anio*10+ciclo==semestre){
            archMat.get(); //Sacamos la coma
            archMat>>codAlu;
            archMat.get();
            while(true){
                archMat>>codCur;
                posCur = buscarCurso(codCur,cursos,numCur);
                if(posCur != NO_ENCONTRADO){
                    na = cursos[posCur].numAlu;
                    cursos[posCur].alumnos[na].codigo = codAlu;
                    cursos[posCur].numAlu++;
                }
                if(archMat.get() == '\n')break;
            }
        }
        else{
            while(archMat.get() != '\n');
        }
    }
    actualizarAlumnos(archAlu,cursos,numCur,escalas,numEsc,semestre);
}

void actualizarAlumnos(ifstream &archAlu,struct Curso *cursos,int numCur,
                       struct Escala *escalas,int numEsc, int semestre){
    int codigo, posEscala;
    double creditos,pagoEsc;
    char escala, *nombre;
    while(true){
        archAlu>>codigo;
        if(archAlu.eof())break;
        archAlu.get();
        nombre = leerCadenaExacta(archAlu,',');
        escala = archAlu.get();
        for(int i=0;i<numCur;i++){
            for(int j=0;j<cursos[i].numAlu;j++){
                if(codigo==cursos[i].alumnos[j].codigo){
                    cursos[i].alumnos[j].nombre = nombre;
                    cursos[i].alumnos[j].escala = escala;
                    posEscala = buscarEscala(escalas,numEsc,escala,semestre);
                    if(posEscala!=NO_ENCONTRADO){
                        cursos[i].alumnos[j].pagoXCred = escalas[posEscala].pagoXCred;
                    }
                    creditos = cursos[i].numCreds;
                    pagoEsc = cursos[i].alumnos[j].pagoXCred;
                    cursos[i].ingresos += creditos*pagoEsc;
                }
            }
        }
    }
}

void ordenarDatos(struct Curso *cursos,int numCur){
    ordenarCursos(cursos,numCur);
    for(int i=0;i<numCur;i++){
        ordenarAlumnos(cursos[i].alumnos,cursos[i].numAlu);
    }
}

void emitirReporte(const char *nombArch,int semestre,
                   struct Curso *cursos,int numCur){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    double totalIngresos=0;
    arch.precision(2);
    arch<<fixed;
    imprimeEncabezado(arch,semestre);
    for(int i=0;i<numCur;i++){
        imprimeLinea(arch,'=');
        arch<<left<<setw(10)<<"No."<<setw(70)<<"CURSO"<<"CREDITOS"<<endl;
        imprimeLinea(arch,'-');
        arch<<setfill('0')<<right<<setw(2)<<i+1<<')'<<setfill(' ')<<"   "
            <<left<<cursos[i].codigo<<" - "<<setw(64)<<cursos[i].nombre
            <<right<<setw(7)<<cursos[i].numCreds<<endl;
        imprimirAlumnosMatriculados(arch,cursos[i].alumnos,cursos[i].numAlu,
                                    cursos[i].numCreds);
        arch<<endl;
        arch<<"TOTAL DE INGRESOS POR MATRICULA: "<<cursos[i].ingresos<<endl;
        totalIngresos += cursos[i].ingresos;
    }
    imprimeLinea(arch,'=');
    arch<<"MONTO TOTAL POR INGRESOS DE MATRICULA:  "<<totalIngresos<<endl;
    imprimeLinea(arch,'=');
}

void imprimirAlumnosMatriculados(ofstream &arch,struct Alumno *alumnos,
                                 int numAlu, double creditos){
    arch<<left<<setw(6)<<' '<<"ALUMNOS MATRICULADOS"<<endl;
    arch<<setw(6)<<' '<<setw(5)<<"No."<<setw(51)<<"ALUMNO"<<setw(9)<<"ESCALA"
        <<setw(20)<<"PAGO POR CREDITO"<<setw(13)<<"TOTAL A PAGAR"<<endl;
    for(int j=0;j<numAlu;j++){
        double totalPagar = alumnos[j].pagoXCred*creditos;
        arch<<setw(6)<<' '<<setfill('0')<<right<<setw(2)<<j+1<<')'<<setfill(' ')<<"  "
            <<left<<alumnos[j].codigo<<"  "<<setw(40)<<alumnos[j].nombre
            <<right<<setw(5)<<alumnos[j].escala<<setw(15)<<alumnos[j].pagoXCred
            <<setw(5)<<' '<<setw(16)<<totalPagar<<endl;
    }
}

void ordenarCursos(struct Curso *cursos,int numCur){
    for(int i=0;i<numCur-1;i++)
        for(int j=i+1;j<numCur;j++)
            if(cursos[i].codigo > cursos[j].codigo)
                cambiarCursos(cursos[i],cursos[j]);
}

void ordenarAlumnos(struct Alumno *alumnos,int numAlu){
    for(int i=0;i<numAlu-1;i++)
        for(int j=i+1;j<numAlu;j++)
            if(alumnos[i].codigo<alumnos[j].codigo)
                cambiarAlumnos(alumnos[i],alumnos[j]);
}

void cambiarCursos(struct Curso &cursoI, struct Curso &cursoJ){
    struct Curso aux;
    aux = cursoI;
    cursoI = cursoJ;
    cursoJ = aux;
}

void cambiarAlumnos(struct Alumno &alumnoI,struct Alumno &alumnoJ){
    struct Alumno aux;
    aux = alumnoI;
    alumnoI = alumnoJ;
    alumnoJ = aux;
}

char* leerCadenaExacta(ifstream &arch,char delimitador){
    char buffer[100], *cadena;
    arch.getline(buffer,100,delimitador);
    if(arch.eof())return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

int buscarCurso(int codCur,struct Curso *cursos,int numCur){
    for(int i=0;i<numCur;i++){
        if(codCur == cursos[i].codigo)return i;
    }
    return NO_ENCONTRADO;
}   

int buscarEscala(const struct Escala *escalas,int numEsc,char escala,int semestre){
    for(int i=0;i<numEsc;i++)
        if(escala == escalas[i].escala and semestre == escalas[i].semestre) return i;
    return NO_ENCONTRADO;
}

void imprimeEncabezado(ofstream &arch, int semestre){
    arch<<setw((TAMLINEA+24)/2)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    arch<<setw((TAMLINEA+36)/2)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    arch<<setw((TAMLINEA+10)/2)<<"CICLO: "<<semestre/10<<'-'<<semestre%10<<endl;
    
}

void imprimeLinea(ofstream &arch,char c){
    for(int i=0;i<TAMLINEA;i++)
        arch.put(c);
    arch<<endl;
}

void cadenaAMayus(char *nombre){
    for(int i=0;nombre[i];i++)
        if(nombre[i]>='a' and nombre[i]<='z') nombre[i]-=('a'-'A');
}