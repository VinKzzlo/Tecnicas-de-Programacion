/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * Archivo:   main.cpp
 * Autor: VinKzzlo
 *
 * Creado el on 27 de mayo de 2024, 13:07
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAXALU 100
#define MAXCUR 50
#define MAXESC 30

int main(int argc, char** argv) {
    int anio, ciclo, semestre;
    solicitarDatos(anio,ciclo);
    semestre = anio*10+ciclo;
    
    int alumnoCods[MAXALU], alumnoNroCurs[MAXALU]{},cantAlu;
    double alumnoCredsMat[MAXALU]{},alumnoMontoPaga[MAXALU]{};
    char alumnoEsc[MAXALU];
    
    int cursosCods[MAXCUR],cantCur;
    double cursosCreds[MAXCUR];
    
    int escSemestre[MAXESC], cantEsc;
    double escCostoXCred[MAXESC];
    char escLetra[MAXESC];
    
    leerAlumnos("Alumnos.txt",alumnoCods,alumnoEsc,cantAlu);
    leerCursos("Cursos.txt",cursosCods,cursosCreds,cantCur);
    leerEscalas("Escalas.txt",escSemestre,escCostoXCred,escLetra,cantEsc);
    updateTotalAlu("Matricula.txt",semestre,alumnoCods,alumnoEsc,cantAlu,
                   cursosCods,cursosCreds,cantCur,
                   escSemestre,escCostoXCred,escLetra,cantEsc,
                   alumnoNroCurs,alumnoCredsMat,alumnoMontoPaga);
    emitirReporte("AlumnosNombres.txt","AlumnosApellidos.txt",
                  "ReporteDePagoPorAlumno.txt", semestre,
                  alumnoCods,alumnoNroCurs,alumnoCredsMat,alumnoEsc,
                  alumnoMontoPaga,cantAlu);
    
    
    return 0;
}

