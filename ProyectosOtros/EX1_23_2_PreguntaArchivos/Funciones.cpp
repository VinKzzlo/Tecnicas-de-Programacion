/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "Funciones.h"
#define MAXLINEA 115
void emitirReporte(const char*nombArchAlumnos, const char*nombArchCursos, 
                   const char*nombArchEscalas, const char*nombArchMatriculas,
                   const char*nombArchRep){
    ifstream archAlumnos(nombArchAlumnos, ios:: in);
    if(not archAlumnos.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchAlumnos<<endl;
        exit(1);
    }
    ifstream archCursos(nombArchCursos, ios:: in);
    if(not archCursos.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchCursos<<endl;
        exit(1);
    }
    ifstream archEscalas(nombArchEscalas, ios:: in);
    if(not archEscalas.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchEscalas<<endl;
        exit(1);
    }
    ifstream archMatri(nombArchMatriculas, ios:: in);
    if(not archMatri.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchMatriculas<<endl;
        exit(1);
    }
    ofstream archRep(nombArchRep, ios:: out);
    if(not archRep.is_open()){
        cout<<"ERROR, no se pudo abrir el archivo"<<nombArchRep<<endl;
        exit(1);
    }
    
    int codigo;
    char escala;
    imprimirEncabezado(archRep);
    while(true){
        archAlumnos>>codigo;
        if(archAlumnos.eof()) break;
        archRep<<setw(10)<<"ALUMNO: "<<codigo<<"  -  ";
        leerNombre(archAlumnos, archRep);
        archAlumnos>>escala;
        archRep<<setw(4)<<"ESCALA: "<<escala<<endl;
        while(archAlumnos.get() != '\n');
        imprimeLinea('-', MAXLINEA, archRep);
        imprimirEncabezado2(archRep);
        leerMatricula(codigo, archMatri,archCursos, archRep);
        
    }
}
void leerMatricula(int codigo, ifstream &archMatri,ifstream &archCursos, ofstream &archRep){
    int codigoMatr, ciclo, num;
    char c;
    
    while(true){
        archMatri>>ciclo;
        if(archMatri.eof()) break;
        archMatri>>c>>num;
        archMatri>>codigoMatr;
        archMatri.clear();
        archMatri.seekg(0, ios:: beg);
        if(codigo==codigoMatr){
            lecturaVariable(archMatri, archRep, archCursos);
        }
        while(archMatri.get()!='\n');
        break; //indispensable
    }
    
}
void lecturaVariable(ifstream &archMatri, ofstream &archRep, ifstream &archCursos){
    int codigoCursos;
    while(true){
        archMatri>>codigoCursos;
        if(archMatri.eof()) break;
        buscarCursoMatri(archCursos, archRep, codigoCursos);
        while(archMatri.get()!='\n');
//        break; // no se sabe
    }
}
void buscarCursoMatri(ifstream &archCursos, ofstream &archRep, int codigoCursos){
    int codigoCur;
    double creditos;
    while(true){
        archCursos>>codigoCur;
        if(archCursos.eof()) break;
        
        archCursos.clear();
        archCursos.seekg(0, ios::beg);
        if(codigoCur==codigoCursos){
            archRep<<setw(8)<<codigoCur<<" - ";
            leerNombreCurso(archCursos, archRep);
            archCursos>>creditos;
            archRep<<setw(7)<<creditos<<endl;
        }
//        break; no se sabe
    }
}
void leerNombreCurso(ifstream &archCursos, ofstream &archRep){
    char c;
    archCursos>>ws;
    while(true){
        c=archCursos.get();
        if(c==' ') break;
        c-=((c>='a' and c<='z')? 'a'-'A':0);
        archRep<<c;
    }
    archRep<<endl;
}
void leerNombre(ifstream &archAlumnos, ofstream &archRep){
    char c;
    archAlumnos>>ws;
    while(true){
        c=archAlumnos.get();
        if(c==' ') break;
        c-=((c>='a' and c<='z')? 'a'-'A':0);
        archRep<<c;
    }
    archRep<<"              ";
}
void imprimirEncabezado(ofstream &archRep){
    archRep<<setw(70)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    archRep<<setw(75)<<"DETALLE DE PAGOS REALIZADOS POR CICLO"<<endl;
    archRep<<setw(65)<<"CICLO: 2023-1"<<endl;
    imprimeLinea('=', MAXLINEA, archRep);
}
void imprimeLinea(char c, int n, ofstream &archRep){
    for(int i=0; i<n; i++){
        archRep.put(c);
    }
    archRep<<endl;
}
void imprimirEncabezado2(ofstream &archRep){
    archRep<<right<<setw(10)<<"     CURSO MATRICULADO"<<setw(18)<<"CREDITOS"
           <<setw(18)<<"MONTO PAGADO"<<endl;
}