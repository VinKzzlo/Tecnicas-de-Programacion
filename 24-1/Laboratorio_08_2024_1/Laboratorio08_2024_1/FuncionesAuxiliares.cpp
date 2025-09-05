/* 
 * File:   FuncionesAuxiliares.cpp
 * Author: Alessandro Salvador Santé Vega - 20223006
 * Created on 10 de junio de 2024, 07:10 PM

 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include <cstring>
#include "Alumno.h"
#include "FuncionesAuxiliares.h"
#define NO_ENCONTRADO -1
#define TAMLINEA 160

void leerCalificaciones(const char *nombArch,
                        struct Alumno *arrAlumnos,int &numAlu){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codAlu,nota, posAlu;
    double creditos;
    char codCurso[7];
    numAlu=0;
    while(true){
        arch>>codCurso;
        if(arch.eof())break;
        arch>>creditos;
        while(true){
            arch>>codAlu>>nota;
            posAlu = buscarAlumno(codAlu,arrAlumnos,numAlu);
            if(posAlu == NO_ENCONTRADO){
                //Se insertan los datos al final y se actualiza num de alumnos
                insertarDatos(codAlu,creditos,nota,arrAlumnos,numAlu);
             }
            else{
                //Se actualizan solo los datos acumulativos
                actualizarDatos(creditos,nota,arrAlumnos,posAlu);
            }
            if(arch.get()== '\n') break;
        }
    }
    //Una vez actualizadas todas las sumas ponderadas y num de creditos, calculamos los promedios por alumno
    actualizarPromedios(arrAlumnos,numAlu);
}

void leerAlumnos(const char *nombArch,
                        struct Alumno *arrAlumnos,int numAlu){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int codigo, posAlu;
    char nombre[60],codFacu[12];
    while(true){
        arch>>codigo;
        if(arch.eof())break;
        arch.get();//sacamos la coma
        arch.getline(nombre,60,',');
        arch.getline(codFacu,12);
        posAlu = buscarAlumno(codigo,arrAlumnos,numAlu);
        if(posAlu != NO_ENCONTRADO){
            //Asignamos el nombre y codigo de la facultad para el alumno
            strcpy(arrAlumnos[posAlu].facultad.codigo,codFacu);
            strcpy(arrAlumnos[posAlu].nombre,nombre);
        }
    }
}

void leerFacultades(const char *nombArch,
                    struct Alumno *arrAlumnos,int numAlu){
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    char nombFacu[50], codFacu[12];
    while(true){
        arch>>nombFacu;
        if(arch.eof())break;
        arch>>ws;
        arch.getline(codFacu,12);
        modificarCadena(nombFacu);
        for(int i=0;i<numAlu;i++){
            //Recorremos cada facultad por alumno y comparamos con el codigo leido
            //Es decir, asignaremos el nombre de la facultad leida para todos los alumnos
            //de aquella facultad
            if(strcmp(codFacu,arrAlumnos[i].facultad.codigo)==0){
                strcpy(arrAlumnos[i].facultad.nombre,nombFacu);
            }
        }
    }
}

void emitirReporte(const char *nombArch,
                    struct Alumno *arrAlumnos,int numAlu){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    imprimeEncabezado(arch);
    //Inicializamos algunas variables para poder imprimir al alumno con mayor
    //cantidad de creditos matriculados
    double maxCreds=0.0;
    int i=0, posMax;
    for(i;i<numAlu;i++){
        if(arrAlumnos[i].numCreditos>maxCreds){
            posMax = i;
            maxCreds = arrAlumnos[i].numCreditos;
        }
        arch<<arrAlumnos[i].codigo<<" - "<<setw(44)<<arrAlumnos[i].nombre
            <<right<<setw(7)<<arrAlumnos[i].numCursos<<setw(20)<<arrAlumnos[i].sumaPonderada
            <<setw(15)<<arrAlumnos[i].numCreditos<<setw(15)<<arrAlumnos[i].promedioPonderado
            <<setw(7)<<' '<<left<<setw(15)<<arrAlumnos[i].facultad.nombre<<endl;
    }
    imprimeLinea(arch,'=');
    arch<<"Alumno con mayor numero de creditos matriculados: "<<endl;
    arch<<setw(10)<<' '<<arrAlumnos[posMax].nombre<<" ["<<arrAlumnos[posMax].codigo
        <<"] con "<<arrAlumnos[posMax].numCreditos<<" creditos de la "
        <<arrAlumnos[posMax].facultad.nombre;
}

int buscarAlumno(int codAlu,struct Alumno *arrAlumnos,int numAlu){
    for(int i=0;i<numAlu;i++)
        if(codAlu == arrAlumnos[i].codigo) return i;
    return NO_ENCONTRADO;
}

void insertarDatos(int codAlu,double creditos,int nota,
                  struct Alumno *arrAlumnos,int &numAlu){
    //Se insertan los datos y se actualiza el numero de alumnos para asi insertar al final
    arrAlumnos[numAlu].codigo = codAlu;
    actualizarDatos(creditos, nota,arrAlumnos,numAlu);
    numAlu++;
}

void actualizarDatos(double creditos,int nota,struct Alumno *arrAlumnos,int pos){
    arrAlumnos[pos].numCursos++;
    arrAlumnos[pos].sumaPonderada += creditos*nota;
    arrAlumnos[pos].numCreditos += creditos;
}

void actualizarPromedios(struct Alumno *arrAlumnos,int numAlu){
    double promedio;
    for(int i=0;i<numAlu;i++){
        promedio = 0.0; //Por si hay alumnos que no se matricularon
        if(arrAlumnos[i].numCreditos>0){
            promedio = (arrAlumnos[i].sumaPonderada)/(arrAlumnos[i].numCreditos);
        }
        arrAlumnos[i].promedioPonderado = promedio;
    }
}

void modificarCadena(char *nombFacu){
    //Eliminamos los caracteres de separacion, para este caso en particular es el '_'
    for(int i=0;nombFacu[i];i++)
        if(nombFacu[i]=='_') nombFacu[i]=' ';
}

void imprimeEncabezado(ofstream &arch){
    arch<<setw((24+TAMLINEA)/2)<<"INSTITUCION EDUCATIVA_TP"<<endl;
    arch<<setw((46+TAMLINEA)/2)<<"PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS"<<endl;
    arch<<setw((13+TAMLINEA)/2)<<"CICLO: 2024-1"<<endl;
    arch<<setw((20+TAMLINEA)/2)<<"TODAS LAS FACULTADES"<<endl;
    imprimeLinea(arch,'=');
    arch<<left<<setw(5)<<' '<<setw(50)<<"ALUMNO"<<setw(15)<<"No. de Cursos"
        <<setw(16)<<"Suma Ponderada"<<setw(17)<<"No. de Creditos"
        <<setw(16)<<"Prom Ponderado"<<setw(15)<<"Facultad"<<endl;
    imprimeLinea(arch,'-');
}

void imprimeLinea(ofstream &arch,char car){
    for(int i=0;i<TAMLINEA;i++)
        arch.put(car);
    arch<<endl;
}