
/* 
 * Archivo:   main.cpp
 * Autor:     VinKzzlo
 *
 * Creado el on 3 de junio de 2024, 16:14
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAX_ALU 100
#define MAX_CUR 50
#define MAX_ESC 30

int main(int argc, char** argv) {
    int semestre;
    solicitarDatos(semestre);
    
    int alumnosCods[MAX_ALU], alumnosNroCur[MAX_ALU]{},numAlu;
    double alumnosCreds[MAX_ALU]{}, alumnosPago[MAX_ALU]{};
    char alumnosEsc[MAX_ALU], *alumnosNomb[MAX_ALU];
    
    int cursosCods[MAX_CUR], numCur;
    double cursosCreds[MAX_CUR];
    
    int escalasSemestre[MAX_ESC], numEsc;
    double escalasPrecio[MAX_ESC];
    char escalasLetra[MAX_ESC];
    
    leerDatosAlumnos("Alumnos.txt",alumnosCods,alumnosNomb,alumnosEsc,numAlu);
    leerDatosCursos("Cursos.txt",cursosCods,cursosCreds,numCur);
    leerDatosEscalas("Escalas.txt",escalasSemestre,escalasPrecio,
                     escalasLetra,numEsc);
    procesarMatricula("Matricula.txt",semestre,
                      alumnosCods,alumnosNomb,alumnosEsc,numAlu,
                      cursosCods,cursosCreds,numCur,
                      escalasSemestre,escalasPrecio, escalasLetra,numEsc,
                      alumnosNroCur,alumnosCreds,alumnosPago);
    
    
    return 0;
}

