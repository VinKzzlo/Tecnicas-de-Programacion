/* 
 * File:   fucniones.cpp
 *
 * Created on 6 de noviembre de 2023, 07:08 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#define veces 120
#define NO_ENCONTRADO -1

using namespace std;

#include "funciones.h"
#include "funcionesCadenas.h"
#include "Alumno.h"
#include "Curso.h"
#include "Escala.h"

void solicitarDatos(int &ciclo){
    int aa, semestre;
    cout<<"Ingrese un anho para el ciclo a evaluar:"<<endl;
    cin>>aa;
    cout<<"Ingrese un semestre para el ciclo a evaluar (1 o 2):"<<endl;
    cin>>semestre;
    ciclo = aa*10+semestre;
}

void cargarAlumnos(struct Alumno *arrAlumnos, int &cantAlumnos){
    int codigo;
    char nombre[100], escala;
    ifstream archAlumnos("alumnos.csv",ios::in);
    if(not archAlumnos.is_open()){
        cout<<"Error en la apertura del archivo alumnos.csv"<<endl;
        exit(1);
    }
    while(true){
        archAlumnos>>codigo;
        if(archAlumnos.eof()) break;
        archAlumnos.get();
        archAlumnos.getline(nombre,100,',');
        escala=archAlumnos.get();
        arrAlumnos[cantAlumnos].codigo=codigo;
        strcpy(arrAlumnos[cantAlumnos].nombre,nombre);
        arrAlumnos[cantAlumnos].escala=escala;
        cantAlumnos++;
    }
}

void cargarCursos(struct Curso *arrCursos, int &cantCursos){
    int codigo;
    double creditos;
    char nombre[100];
    ifstream archCursos("cursos.csv",ios::in);
    if(not archCursos.is_open()){
        cout<<"Error en la apertura del archivo cursos.csv"<<endl;
        exit(1);
    }
    while(true){
        archCursos>>codigo;
        if(archCursos.eof()) break;
        archCursos.get();
        archCursos.getline(nombre,100,',');
        archCursos>>creditos;
        modificarNombre(nombre);
        arrCursos[cantCursos].codigo=codigo;
        strcpy(arrCursos[cantCursos].nombre,nombre);
        arrCursos[cantCursos].creditos=creditos;
        arrCursos[cantCursos].alumnosMatriculados=0;
        arrCursos[cantCursos].montoPagado=0;
        cantCursos++;
    }
}


void cargarEscalas(struct Escala *arrEscalas, int &cantEscalas){
    int aa, ciclo;
    char escala, car;
    double precio;
    ifstream archEscalas("escalas.csv",ios::in);
    if(not archEscalas.is_open()){
        cout<<"Error en la apertura del archivo escalas.csv"<<endl;
        exit(1);
    }
    while(true){
        archEscalas>>aa;
        if(archEscalas.eof()) break;
        archEscalas>>car>>ciclo>>car>>escala>>car>>precio;
        arrEscalas[cantEscalas].ciclo=aa*10+ciclo;
        arrEscalas[cantEscalas].escala=escala;
        arrEscalas[cantEscalas].precio=precio;
        cantEscalas++;
    }
}

void actualizarMatricula(const struct Alumno *arrAlumnos, int cantAlumnos, struct Curso *arrCursos,
        int cantCursos, const struct Escala *arrEscalas, int cantEscalas, int ciclo){
    int aa, semestre, alumno, curso, posAlumno, posCurso, posEscala;
    char car;
    ifstream archMatricula("matricula.csv",ios::in);
    if(not archMatricula.is_open()){
        cout<<"Error en la apertura del archivo matricula.csv"<<endl;
        exit(1);
    }
    while(true){
        archMatricula>>aa;
        if(archMatricula.eof()) break;
        archMatricula>>car>>semestre>>car>>alumno>>car;
        posAlumno=buscarAlumno(arrAlumnos, cantAlumnos, alumno);
        if(posAlumno!=NO_ENCONTRADO and ciclo==aa*10+semestre){
            posEscala=buscarEscala(arrEscalas, cantEscalas, aa*10+semestre, arrAlumnos[posAlumno].escala);
            if(posEscala!=NO_ENCONTRADO){
                while(true){
                    archMatricula>>curso;
                    posCurso=buscarCurso(arrCursos, cantCursos, curso);
                    if(posCurso!=NO_ENCONTRADO){
                        arrCursos[posCurso].alumnosMatriculados++;
                        arrCursos[posCurso].montoPagado+=arrCursos[posCurso].creditos*
                                arrEscalas[posEscala].precio;
                    }
                    if(archMatricula.get()=='\n') break;
                }
            }
            else
                while(archMatricula.get()!='\n');
        }
        else
            while(archMatricula.get()!='\n');
    }
}

int buscarAlumno(const struct Alumno *arrAlumnos, int cantAlumnos, int alumno){
    for(int i=0;i<cantAlumnos;i++)
        if(arrAlumnos[i].codigo==alumno)
            return i;
    return NO_ENCONTRADO;
}

int buscarEscala(const struct Escala *arrEscalas, int cantEscalas, int ciclo, char escala){
    for(int i=0;i<cantEscalas;i++)
        if(arrEscalas[i].escala==escala and arrEscalas[i].ciclo==ciclo)
            return i;
    return NO_ENCONTRADO;
}

int buscarCurso(const struct Curso *arrCursos, int cantCursos, int curso){
    for(int i=0;i<cantCursos;i++)
        if(arrCursos[i].codigo==curso)
            return i;
    return NO_ENCONTRADO;
}

void ordenarDatos(struct Curso *arrCursos, int cantCursos){
    for(int i=0;i<cantCursos-1;i++)
        for(int j=i+1;j<cantCursos;j++)
            if((arrCursos[i].alumnosMatriculados==arrCursos[j].alumnosMatriculados and
                    strcmp(arrCursos[i].nombre,arrCursos[j].nombre)<0)
                    or arrCursos[i].alumnosMatriculados>arrCursos[j].alumnosMatriculados)
                cambiarEstructuras(arrCursos[i],arrCursos[j]);
}

void cambiarEstructuras(struct Curso &cursoI, struct Curso &cursoJ){
    struct Curso aux=cursoI;
    cursoI=cursoJ;
    cursoJ=aux;
}

void emitirReporte(const struct Curso *arrCursos, int cantCursos, int ciclo){
    double totalPagado = 0;
    ofstream archReporte("ReporteDePagoPorCurso.txt",ios::out);
    if(not archReporte.is_open()){
        cout<<"Error en la apertura del archivo ReporteDePagoPorCurso.txt"<<endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;
    archReporte<<setw(72)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    archReporte<<setw(78)<<"DETALLE DE PAGOS REALIZADO POR CICLO"<<endl;
    archReporte<<setw(59)<<"CICLO: "<<ciclo/10<<'-'<<ciclo%10<<endl;
    imprimirLinea('=',veces,archReporte);
    archReporte<<"No."<<setw(10)<<"CURSO"<<setw(63)<<"CREDITOS"<<setw(17)<<"ALUMNOS.MAT"
            <<setw(20)<<"MONTO PAGADO"<<endl;
    imprimirLinea('-',veces,archReporte);
    for(int i=0;i<cantCursos;i++){
        archReporte<<setfill('0')<<setw(2)<<i+1<<')'<<setfill(' ')<<setw(8)<<arrCursos[i].codigo
                <<" - "<<left<<setw(53)<<arrCursos[i].nombre<<right<<setprecision(2)
                <<setw(7)<<arrCursos[i].creditos<<setw(13)<<arrCursos[i].alumnosMatriculados
                <<setw(23)<<setprecision(2)<<arrCursos[i].montoPagado<<endl;
        totalPagado+=arrCursos[i].montoPagado;
    }
    imprimirLinea('-',veces,archReporte);
    archReporte<<"MONTO TOTAL PAGADO:"<<setw(91)<<setprecision(2)<<totalPagado<<endl;
    imprimirLinea('=',veces,archReporte);
}

void imprimirLinea(char simbolo, int cant, ofstream &archReporte){
    for(int i=0;i<cant;i++)
        archReporte.put(simbolo);
    archReporte<<endl;
}