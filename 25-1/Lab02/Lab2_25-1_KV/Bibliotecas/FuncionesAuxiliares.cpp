/*
 *
 * Proyecto:    Lab2_25_1_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       15/09/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAM_LINEA 230
#define TAM_NAME 45

void imprimeReporteMultasCompanias(const char *nombArchInfracciones, const char *nombArchMultas,
                                   const char *nombArchReporte) {
    ifstream archInfra(nombArchInfracciones, ios::in);
    if (not archInfra.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo" << nombArchInfracciones << endl;
        exit(1);
    }
    ifstream archMultas(nombArchMultas, ios::in);
    if (not archMultas.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo" << nombArchMultas << endl;
        exit(1);
    }
    ofstream archRep(nombArchReporte, ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo" << nombArchReporte << endl;
        exit(1);
    }

    archRep.precision(2);
    archRep<<fixed;

    int dni, cantCompanias=1, cantLeves=0, cantGraves=0, cantMuyGraves=0;
    double montoLeves =0.0, montoGraves = 0.0, montoMuyGraves=0.0;
    imprimeEncabezado(archRep);
    while (true) {
        archInfra>>dni;
        if (archInfra.eof())break;
        cantCompanias++;
        imprimeHeaderCompania(archInfra,archRep,dni,cantCompanias);
        leeImprimeVehiculosMultas(archInfra,archMultas,archRep,cantLeves,cantGraves,cantMuyGraves,
            montoLeves,montoGraves,montoMuyGraves);

        //while (archInfra.get()!='\n');
    }

}

void leeImprimeVehiculosMultas(ifstream &archInfra, ifstream &archMultas, ofstream &archRep,
    int &cantLeves, int &cantGraves, int &cantMuyGraves,
    double &montoLeves, double &montoGraves, double &montoMuyGraves) {
    int numPlaca1, numPlaca2, fechaInfraccion, codigoMulta;
    char tipoVehiculo;
    imprimeHeaderInfracciones(archRep);
    int leves=0,graves=0,muyGraves=0;
    double pagoLeves=0.0,pagoGraves=0.0,pagoMuyGraves=0.0;
    while (true){
        archInfra>>ws; //Quitamos los espacios previos a la placa
        tipoVehiculo = archInfra.get();
        archInfra>>numPlaca1;
        archInfra.get(); //Retiramos el guion
        archInfra>>numPlaca2;
        fechaInfraccion = leeFecha(archInfra);
        archInfra>>codigoMulta;
        imprimeDatosInfraccionVehiculo(archRep,tipoVehiculo,numPlaca1,numPlaca2,fechaInfraccion);
        imprimeDetalleMulta(archMultas,archRep,codigoMulta,leves,graves,muyGraves,
            pagoLeves,pagoGraves,pagoMuyGraves);
        if (archInfra.get()=='\n') break;
    }
    imprimeResumenParcial(archRep,leves,graves,muyGraves,
            pagoLeves,pagoGraves,pagoMuyGraves);

}


void imprimeHeaderInfracciones(ofstream &archRep) {
    imprimeLinea(archRep,'-',TAM_LINEA);
    archRep<<"VEHICULOS INFRACCIONADOS" << endl;
    archRep << setw(7) << "PLACA" << setw(10) << "TIPO" << setw(18) << "FECHA"
    << setw(17) <<"INFRACCION" << setw(12) <<"GRAVEDAD" << setw(18) <<"MULTA" << setw(16) << "DESCRIPCION" << endl;
}

void imprimeDatosInfraccionVehiculo(ofstream &archRep,char tipoVehiculo, int numPlaca1, int numPlaca2, int fechaInfraccion) {

    archRep << "- " << numPlaca1 << numPlaca2 << tipoVehiculo << setw(4) << ' ' <<left;

    if (tipoVehiculo=='P')
        archRep << setw(15) << "PEQUENO";
    else if (tipoVehiculo == 'M')
        archRep << setw(15) <<"MEDIANO";
    else if ( tipoVehiculo == 'G')
        archRep << setw(15) << "GRANDE";

    archRep << right;

    imprimeFecha(archRep,fechaInfraccion);
    //archRep << endl;
}

void imprimeDetalleMulta(ifstream &archMultas, ofstream &archRep, int codigoMulta,
    int &cantLeves, int &cantGraves, int &cantMuyGraves,
    double &montoLeves, double &montoGraves, double &montoMuyGraves) {

    int codMultaArchivo;
    char tipoMulta;
    double montoMulta;
    bool loEncontro = false;

    archMultas.clear();
    archMultas.seekg(0,ios::beg);

    archRep << setw(10) << codigoMulta << setw(9) << ' ';
    while (not loEncontro) {
        archMultas>>tipoMulta;
        if (archMultas.eof())break;
        archMultas >> codMultaArchivo >> montoMulta>>ws;
        if (codMultaArchivo == codigoMulta) {
            imprimeGravedad(archRep,tipoMulta);
            archRep << setw(10) << montoMulta << setw(5) << ' ';
            leeImprimeDescripcion(archMultas,archRep);
            loEncontro = true;
            actualizaAcumuladores(tipoMulta,montoMulta,cantLeves,cantGraves,cantMuyGraves,montoLeves,montoGraves,montoMuyGraves);
        }
        else {
            while (archMultas.get()!='\n');
        }
    }
    if (not loEncontro)
        archRep << "---" << setw(10) << "-----" << "NO SE ENCONTRO LA INFRACCION." << endl;

}

void imprimeGravedad(ofstream &archRep, char tipoMulta) {
    archRep<<left;
    if (tipoMulta=='L')
        archRep << setw(15) << "LEVE";
    else if (tipoMulta == 'G')
        archRep << setw(15) <<"GRAVE";
    else if ( tipoMulta == 'M')
        archRep << setw(15) << "MUY GRAVE";
    archRep<<right;
}

void actualizaAcumuladores(char tipoMulta, double montoMulta,
    int &cantLeves, int &cantGraves, int &cantMuyGraves,
    double &montoLeves, double &montoGraves, double &montoMuyGraves) {
    if (tipoMulta=='L') {
        cantLeves++;
        montoLeves+=montoMulta;
    }
    else if (tipoMulta == 'G') {
        cantGraves++;
        montoGraves+=montoMulta;
    }
    else if ( tipoMulta == 'M') {
        cantMuyGraves++;
        montoMuyGraves+=montoMulta;
    }
}

void imprimeResumenParcial(ofstream &archRep, int cantLeves, int cantGraves, int cantMuyGraves,
    double montoLeves, double montoGraves, double montoMuyGraves) {
    imprimeLinea(archRep,'-',TAM_LINEA);
    archRep << setw(18)<<' ' << "CANTIDAD" << setw(20) << "MONTO PAGADO" << endl;
    archRep << setw(18) <<"FALTAS LEVES:" << setw(5) << cantLeves << setw(20) << montoLeves << endl;
    archRep << setw(18) <<"FALTAS GRAVES:" << setw(5) << cantGraves << setw(20) << montoGraves << endl;
    archRep << setw(18) << "FALTAS MUY GRAVES:" << setw(5) << cantMuyGraves << setw(20) << montoMuyGraves << endl;
    imprimeLinea(archRep,'-',50);
    archRep << "PAGO TOTAL: " << setw(10) << montoLeves+montoGraves+montoMuyGraves << endl;
}

int leeFecha(ifstream &archIn) {
    int dd,mm,aa;
    archIn>>dd;
    archIn.get();
    archIn>>mm;
    archIn.get();
    archIn>>aa;
    return aa*10000 + mm*100 +dd;
}

// 20221109
void imprimeFecha(ofstream &archRep, int fecha) {
    int aa = fecha/10000;
    int mm = (fecha%10000)/100;
    int dd = fecha%100;

    archRep << setfill('0') << setw(2) << dd << '/';
    archRep << setw(2) << mm << '/';
    archRep << setw(4) << aa << setfill(' ');

}
void imprimeEncabezado(ofstream &archRep) {
    archRep << setw((TAM_LINEA+24)/2) << "MINISTERIO DE TRANSPORTE"<<endl;
    archRep << setw((TAM_LINEA+32)/2) << "MULTAS IMPUESTAS A LAS COMPANIAS"<<endl;
}

void imprimeHeaderCompania(ifstream &archInfra, ofstream &archRep,int dni, int cant){
    imprimeLinea(archRep,'=',TAM_LINEA);
    archRep << "COMPANIA No. " << cant << endl;
    archRep << "REPRESENTANTE LEGAL: ";
    leeImprimeCadenas(archInfra,archRep,false);
    archRep << "DNI: " << dni << endl;
}

void leeImprimeDescripcion(ifstream &archIn, ofstream &archRep) {
    char letra;
    while (true) {
        letra = archIn.get();
        archRep.put(letra);
        if (letra == '\n') break;
    }
}

// CONTRERAS/CHANG/JOHANA-CINTHIA
void leeImprimeCadenas(ifstream &archIn, ofstream &archRep, bool finDeLinea) {
    int cantCaracteres=0, cantBlancos;
    char letra;
    bool mayus=true;
    archIn>>ws;
    while (true) {
        letra = archIn.get();
        if (letra == ' ') break;
        cantCaracteres++;
        if (letra=='/' or letra =='-') {
            archRep.put(' ');
            mayus = true;
        }
        else {
            if (mayus) mayus = false;
            else letra += 'a' - 'A';
            archRep.put(letra);
        }
    }
    if (finDeLinea) {
        archRep<<endl;
    }
    else {
        cantBlancos = TAM_NAME - cantCaracteres;
        archRep<<setw(cantBlancos)<<' ';
    }

}


void imprimeLinea(ofstream &archRep, char c,int size) {
    for (int i=0;i<size;i++)
        archRep.put(c);
    archRep<<endl;
}