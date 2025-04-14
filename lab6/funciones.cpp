
// File:   funciones.cpp
// Author: superflash41

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "funciones.h"
#define NOT_FOUND -1
#define BUFSZ 120

void leerCalificaciones(const char* fn, int* cods, int* cursos, 
        double* sumas, double* credits, int& nd) {
    ifstream arch(fn, ios::in);
    if (!arch) cout<<"ERROR. No se pudo abrir "<<fn<<endl;
    double cred;
    char aux[10];
    while (true) {
        arch>>aux;
        if (arch.eof()) break;
        arch>>cred;
        leerNotas(arch, cred, cods, cursos, sumas, credits, nd);
    }
}

void leerNotas(ifstream& arch, double cred, int* cods, int* cursos, 
        double* sumas, double* credits, int& nd) {
    int cod, nota, pos;
    while (true) {
        arch>>cod>>nota;
        if ((pos=buscarCod(cod, cods, 0, nd-1))!=NOT_FOUND)
            actualizarArreglos(nota, cred, cursos[pos], sumas[pos], credits[pos]);
        else
            insertarOrdenado(cod, nota, cred, cods, cursos, sumas, credits, nd);
        if (arch.get()=='\n') break;
    }
}

int buscarCod(int cod, int* cods, int ini, int fin) {
    while (true) {
        if (ini > fin) return NOT_FOUND;
        int mid = (ini+fin)/2;
        if (cod == cods[mid]) return mid;
        if (cod < cods[mid]) fin = mid-1;
        else ini = mid+1;
    }
}

void actualizarArreglos(int nota, double cred, int& cursos, double& sumas, 
        double& credits) {
    cursos++;
    sumas += nota*cred;
    credits += cred;
}

void insertarOrdenado(int cod, int nota, double cred, int* cods, int* cursos, 
        double* sumas, double* credits, int& nd) {
    int i;
    for (i=nd-1; i>=0; i--)
        if (cod < cods[i]) {
            cods[i+1] = cods[i];
            cursos[i+1] = cursos[i];
            sumas[i+1] = sumas[i];
            credits[i+1] = credits[i];
        } else break;
    cods[i+1] = cod;
    cursos[i+1] = 0;
    sumas[i+1] = 0;
    credits[i+1] = 0;
    nd++;
    actualizarArreglos(nota, cred, cursos[i+1], sumas[i+1], credits[i+1]);
}

void generarReporte(const char* fnR, const char* fnA, const char* fnF, 
        int* cods, int* cursos, double* sumas, double* credits, int nd) {
    ifstream alum(fnA, ios::in);
    if (!alum) cout<<"ERROR. No se pudo abrir "<<fnA<<endl;
    ifstream fac(fnF, ios::in);
    if (!fac) cout<<"ERROR. No se pudo abrir "<<fnF<<endl;
    ofstream arch(fnR, ios::out);
    if (!arch) cout<<"ERROR. No se pudo abrir "<<fnR<<endl;
    // lectura de la facultad
    int facultad = 300103;
    arch.precision(2);
    arch<<fixed;
    imprimirFacultad(fac, arch, facultad);
    imprimirDatosAlumnos(alum, arch, facultad, cods, cursos, sumas, credits, nd);
}

void imprimirFacultad(ifstream& fac, ofstream& arch, int facultad) {
    char og[BUFSZ];
    int cod;
    while (true) {
        fac>>og;
        if (fac.eof()) break;
        fac>>cod;
        if (cod==facultad) {
            imprimirNombreFacultad(arch, og);
            break;
        }
    }
}

void imprimirNombreFacultad(ofstream& arch, char* og) {
    for (int i=0; og[i]; i++)
        if (og[i]=='_') og[i] = ' ';
    arch<<og<<endl;
    arch<<setfill('=')<<setw(100)<<" "<<setfill(' ')<<endl;
}

void imprimirDatosAlumnos(ifstream& alum, ofstream& arch, int facultad, 
        int* cods, int* cursos, double* sumas, double* credits, int nd) {
    int cod, facu, pos;
    char og[BUFSZ], mod[BUFSZ];
    while (true) {
        alum>>cod;
        if (alum.eof()) break;
        alum>>og>>facu;
        if ((pos=buscarCod(cod, cods, 0, nd-1))!=NOT_FOUND and facu==facultad) {
            procesarNombre(og, mod);
            arch<<setw(10)<<cod<<" - "<<left<<setw(46)<<mod<<right<<setw(4)<<cursos[pos]<<
                    setw(10)<<sumas[pos]<<setw(8)<<credits[pos]<<setw(8)<<
                    sumas[pos]/credits[pos]<<endl;
        }
    }
}

void procesarNombre(char* og, char* mod) {
    int i=0, j=0, k;
    bool mayus = true;
    while (og[i]!='/') i++;
    i++;
    while (og[i]!='/') i++;
    k=i; // position until it needs to copy then
    i++;
    for (; og[i]; i++) {
        if (og[i]=='-') {
            og[i] = ' ';
            mayus = true;
        } else {
            if (mayus) mayus = false;
            else uncap(og[i]);
        }
        mod[j] = og[i]; j++;
    }
    mod[j]=' '; j++;
    mayus = true;
    for (i=0; i<k; i++) {
        if (og[i]=='/') {
            og[i] = ' ';
            mayus = true;
        } else {
            if (mayus) mayus = false;
            else uncap(og[i]);
        }
        mod[j] = og[i]; j++;
    }
    mod[j] = 0;
}

void uncap(char& c) {
    c -= 'A'-'a';
}
