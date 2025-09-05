/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

/* 
 * Archivo:   FuncionesAuxiliares.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 10 de junio de 2024, 17:17
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"
#include "FuncionesAuxiliares.h"
#define NO_ENCONTRADO -1

void solicitarDatos(int &anio,int &ciclo){
    char c;
    cout<<"Ingrese anio y ciclo para emitir el reporte: "<<endl;
    cin>>anio>>c>>ciclo;
}

void leerAlumnos(const char *nombArch,struct Alumno *alumnos,int &numAlu){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    numAlu=0;
    int codigo;
    char nombre[60],escala;
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        arch.getline(nombre,60,',');
        arch>>escala;
        alumnos[numAlu].codigo = codigo;
        strcpy(alumnos[numAlu].nombre,nombre);
        alumnos[numAlu].escala = escala;
        numAlu++;
    }
}

void leerCursos(const char *nombArch,struct Curso *cursos,int &numCur){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    numCur=0;
    int codigo;
    double creditos;
    char nombre[60];
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();
        arch.getline(nombre,60,',');
        arch>>creditos;
        cursos[numCur].codigo = nombre;
        strcpy(cursos[numCur].nombre,nombre);
        cursos[numCur].creditos = creditos;
        numCur++;        
    }
}

void leerEscalas(const char *nombArch,struct Escala *escalas,int &numEsc){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    numEsc=0;
    int anio,ciclo;
    double costo;
    char escala,c;
    while(true){
        arch>>anio;
        if(arch.eof())break;
        arch>>c>>ciclo;
        arch.get();
        arch>>escala;
        arch.get();
        arch>>costo;
        escalas[numEsc].semestre = anio*10+ciclo;
        escalas[numEsc].escala = escala;
        escalas[numEsc].costo = costo;
        numEsc++;
    }
}

void updateCursos(const char *nombArch,struct Alumno *alumnos,int numAlu,
             struct Curso *cursos,int numCur,struct Escala *escalas,int numEsc,int semestre){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int anio,ciclo,codAlumno,codCurso,posAlu, semestreEvaluar, posEsc;
    char c;
    while(true){
        arch>>anio;
        if(arch.eof())break;
        arch>>c>>ciclo>>c>>codAlumno;
        semestreEvaluar = anio*10+ciclo;
        posAlu = buscarAlumno(codAlumno,alumnos,numAlu);
        if(posAlu != NO_ENCONTRADO and semestre==semestreEvaluar){
            posEsc = buscarEscala(semestre,alumnos[posAlu].escala,escalas,numEsc);
            if(posEsc != NO_ENCONTRADO)
        }
        else{
            while(arch.get() != '\n');
        }
    }
}

int buscarAlumno(int codAlumno,struct Alumno *alumnos,int numAlu){
    for(int i=0; i<numAlu;i++)
        if(alumnos[i].codigo==codAlumno) return i;
    return NO_ENCONTRADO;
}

int buscarEscala(int semestre,char escala, struct Escala *escalas, int numEsc){
    for(int i=0; i<numEsc;i++)
        if(escalas[i].escala == escala and escalas[i].semestre==semestre) return i;
    return NO_ENCONTRADO;
}