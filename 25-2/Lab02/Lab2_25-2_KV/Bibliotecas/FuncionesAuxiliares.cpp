/*
 *
 * Proyecto:    Lab2_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       18/09/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAMLINEA 120
#define TAMNOMBRE 40

void solicitaFechasYTarifas(int &fechaIni, int &fechaFin, double &tarifaPubli, double &tarifaDuracion) {
    int ddIni, ddFin, mmIni, mmFin, aaIni, aaFin;
    char c;
    // //cout << "Ingrese el rango de fechas a considerar para el reporte (formato DD/MM/AAAA)"<<endl;
    // //cout << "Fecha Inicial: ";
    // //cin >> ddIni >> c >> mmIni >> c >> aaIni;
    // fechaIni = aaIni*10000 + mmIni*100 + ddIni;
    // //cout << "Fecha Final: ";
    // //cin >> ddFin >> c >> mmFin >> c >> aaFin;
    // fechaFin = aaFin*10000 + mmFin*100 + ddFin;
    //
    // cout <<"Ingrese la tarifa por publicidad (numero de visualizaciones) a considerar: ";
    // cin >> tarifaPubli;
    // cout <<"Ingrese la tarifa por duracion de stream a considerar: ";
    // cin >> tarifaDuracion;
    fechaIni = 20220910;
    fechaFin = 20230101;
    tarifaPubli = 2.527;
    tarifaDuracion = 0.78;
}

void procesaImprimeRegistroCanalesAfiliados(const char *nombArchTwitch, const char *nombArchReporte,
    int fechaIni, int fechaFin, double tarifaPubli, double tarifaDuracion) {
    int cantStreamsTotal=0, duracionStreamsTotal=0;
    double ingresosTotalesPubli=0.0, ingresosTotalesDuracion=0.0;

    ifstream archTwitch (nombArchTwitch,ios::in);
    if (not archTwitch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo" << nombArchTwitch << endl;
        exit(1);
    }

    ofstream archRep (nombArchReporte,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo" << nombArchReporte << endl;
        exit(1);
    }

    archRep.precision(2);
    archRep<<fixed;

    imprimeEncabezado(archRep,fechaIni,fechaFin,tarifaPubli,tarifaDuracion);

}

void imprimeEncabezado(ofstream &archRep, int fechaIni, int fechaFin, double tarifaPubli, double tarifaDuracion) {
    archRep << setw((TAMLINEA+20)/2) << "PLATAFORMA TP_Twitch" << endl;
    archRep << setw((TAMLINEA+33)/2) << "REGISTRO DE LOS CANALES AFILIADOS" << endl;
    archRep << setw(60) << "FECHAS DE CREACION ENTRE EL ";
    imprimeFecha(archRep,fechaIni);
    archRep << " Y EL ";
    imprimeFecha(archRep,fechaFin);
    archRep << endl;
    archRep << setw(60) << "TARIFA POR NUMERO DE REPRODUCCIONES: " << tarifaPubli
            << " POR CADA 1,000 REPRODUCCIONES Y FRACCION" << endl;
    archRep << setw(64) << "TARIFA POR DURACION DEL STREAM: " << tarifaDuracion
            << " POR CADA MINUTO Y FRACCION" << endl;

}

void imprimeFecha (ofstream &archRep, int fecha) {
    int aa = fecha/10000, mm=(fecha%10000)/100, dd=fecha%100;

    archRep << setfill('0') << setw(2) << dd << '/';
    archRep << setw(2) << mm << '/';
    archRep << setw(4) << aa  << setfill(' ');
}