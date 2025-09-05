/* 
 * File:   main.cpp
 * Author:  Vicente Jorge
 * Código: 20222159
 * Created on 9 de octubre de 2023, 06:35 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "funcionesAuxiliares.h"

#define MAX_ALU 100
#define MAX_CUR 50
#define MAX_ESC 30

int main(int argc, char** argv) {
    int arrCodeAlu[MAX_ALU],cantAlu=0;
    int arrCodeCur[MAX_CUR],cantCur=0;
    int arrAnioEsc[MAX_ESC],arrCicloEsc[MAX_ESC],numEsc=0;
    int cantAluEsc[MAX_ESC]{};
    double cantCredEsc[MAX_ESC]{},totalIngresosEsc[MAX_ESC]{};
    double arrValorEsc[MAX_ESC];
    char arrTipoEsc[MAX_ESC];
    double arrCredCur[MAX_CUR];
    char arrEscAlu[MAX_ALU];
    leerAlum("Alumnos.txt",arrCodeAlu,arrEscAlu,cantAlu);
    leerCur("Cursos.txt",arrCodeCur,arrCredCur,cantCur);
    leerEsc("Escalas.txt",arrAnioEsc,arrCicloEsc,arrTipoEsc,arrValorEsc,numEsc);
    emitirRepDeEscalas("ReporteDeEscalas.txt",arrAnioEsc,arrTipoEsc,
            arrCicloEsc,arrValorEsc,numEsc);
    actualizacionMatricula("Matricula.txt",arrAnioEsc,arrCicloEsc,
            arrTipoEsc,cantAluEsc,cantCredEsc,totalIngresosEsc,numEsc,
            arrCodeAlu,arrEscAlu,arrCodeCur,arrCredCur,cantAlu,cantCur,
            arrValorEsc);
    ordenarArrays(arrAnioEsc,arrCicloEsc,arrTipoEsc,arrValorEsc,
            cantAluEsc,cantCredEsc,totalIngresosEsc,numEsc);
    emitirReporte("Reporte_Ingresos_Ciclos_Escalas.txt",arrAnioEsc,
            arrCicloEsc,arrTipoEsc,arrValorEsc,cantAluEsc,cantCredEsc,
            totalIngresosEsc,numEsc);
    return 0;
}

