/*
 *
 * Proyecto:    Lab6_25_1_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       1/11/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"

void leerTablaInfraccioness(const char *nombArch, int *arrCodigoInfraccion, double *arrMultasInfraccion, int &cantInfracciones) {
    ifstream archIn(nombArch,ios::in);
    if (not archIn.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    int codigo;
    double multa;
    while (true) {
        archIn >> codigo;
        if (archIn.eof()) break;
        archIn >> multa;

        saltarCadenas(archIn,'\n');

        insertarOrdenado(codigo,multa,cantInfracciones,arrCodigoInfraccion,arrMultasInfraccion);

    }

}

void insertarOrdenado(int codigo, double multa, int &cantInfracciones, int *arrCodigoInfraccion, double *arrMultasInfraccion) {
    int i;
    for (i=cantInfracciones-1 ; i>=0 ; i--) {
        if (codigo > arrCodigoInfraccion[i]) break;
        arrCodigoInfraccion[i+1] = arrCodigoInfraccion[i];
        arrMultasInfraccion[i+1] = arrMultasInfraccion[i];
    }
    arrCodigoInfraccion[i+1] = codigo;
    arrMultasInfraccion[i+1] = multa;
    cantInfracciones++;
}

void comprobarLecturaInfracciones(const char *nombArch, int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantInfracciones) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep<<setprecision(2)<<fixed;

    archRep << "CODIGO INFRACCION" << setw(20) << "MULTA INFRACCION" << endl;
    for (int i=0;i<cantInfracciones; i++) {
        archRep << arrCodigoInfraccion[i] << setw(30) << arrMultasInfraccion[i] << endl;
    }


}

//18/12/2024       G938-342      73818744   2061   P       26/1/2025
//6/8/2021       P863-768     90467829      2025
void leerInfraccionesCometidas(const char *nombArchIn, const char *nombArchRep,
    int *arrCodigoInfraccion, double *arrMultasInfraccion, int cantInfracciones,
    int *arrDni, int *arrMasMultaAntigua, int *arrUltimaPendiente,
    double *arrTotalMultas, double *arrTotalPagadas, double *arrTotalPendientes, int &cantRepresentantes) {
    ifstream archIn(nombArchIn,ios::in);
    if (not archIn.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchIn << endl;
        exit(1);
    }
    ofstream archRep(nombArchRep,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchRep << endl;
        exit(1);
    }

    int ddInf, mmInf, aaInf, fechaInf, dni, codInfraccion, fechaPago;
    char placa[9], c, letraPago;
    while (true) {
        archIn >> ddInf;
        if (archIn.eof()) break;
        archIn>>c>>mmInf>>c>>aaInf>>ws;
        fechaInf = aaInf*10000 + mmInf*100 + ddInf;
        archIn >> placa;
        archIn >> dni >> codInfraccion;
        while (true) {
            if (archIn.get()=='\n') break;
            archIn>>letraPago;
            fechaPago = leerFecha(archIn);
        }
        escribirLineaEnArchivoPlacas(archRep,dni,placa);
        int posDNI = buscarDni(dni,arrDni,cantRepresentantes);
    }

}

int leerFecha(ifstream &archIn) {
    int dd, mm, aa;
    archIn >> dd;
    archIn.get();
    archIn >> mm;
    archIn.get();
    archIn >> aa;
    return aa*10000 + mm*100 + dd;
}
void escribirLineaEnArchivoPlacas(ofstream &archRep, int dni, char *placa) {
    archRep << dni << "  " << placa << endl;
}

void saltarCadenas(ifstream &archIn, char delim) {
    while (archIn.get() != delim);
}