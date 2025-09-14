/*
 *
 * Proyecto:    Lab1_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       14/09/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define SIZE_LINE 120
#define SIZE_NAME 20
#define INGRESO_PUBLICIDAD 3.25

void procesaImprimeReporteTPTwitch() {
    int fechaIniValidar = 20220909, fechaFinValidar = 20230101;
    int fechaCreacion, aaCreacion, mmCreacion, ddCreacion, numCanales=0;
    //Acumuladores para Final
    int cantStreamsTotal=0, duracionTotalStreams=0, numericoCodigoMejor;
    double ingresosTotalesPorPubli=0.0, mejorIngresoCanal=0.0;
    char c, letraCodigoMejor;
    imprimeEncabezadoTwitch();
    cin.precision(2);
    cin>>fixed;
    while (true) {
        cin>>ddCreacion;
        if (cin.eof())break;
        cin>>c>>mmCreacion;
        cin>>c>>aaCreacion;
        fechaCreacion = aaCreacion*10000 + mmCreacion*100 + ddCreacion;
        if (fechaCreacion>=fechaIniValidar and fechaCreacion <= fechaFinValidar) {
            numCanales++;
            procesaInformacionPorCanal(fechaCreacion,numCanales,cantStreamsTotal,duracionTotalStreams,
                ingresosTotalesPorPubli,mejorIngresoCanal,numericoCodigoMejor,letraCodigoMejor);
        }
        else {
            while (cin.get()!='\n'); //Saltamos la linea del canal que no queremos analizar pues esta fuera del rango de fechas
        }
    }
    //Resumen Final
    imprimeResumenFinal(cantStreamsTotal, duracionTotalStreams, ingresosTotalesPorPubli, mejorIngresoCanal,
                        numericoCodigoMejor, letraCodigoMejor);
}
//11/09/2022      B8913        Baiano      425797    24/07/2025   02:00:52   5538   01/08/2025   02:10:24   7623   15/07/2025   01:08:43   15998

void procesaInformacionPorCanal(int fechaCreacion,int numCanales,int &cantStreamsTotal,int &duracionTotalStreams,
                double &ingresosTotalesPorPubli,double &mejorIngresoCanal,int &numericoCodigoMejor,char &letraCodigoMejor) {
    char letraCodigo;
    int numeroCodigo, numSeguidores, duracionTotal=0, ultimaPubli=0, totalReproducciones=0;
    double ingresoPublicidad=0.0;

    imprimeEncabezadoCanal(numCanales);
    cin>>ws; //Extraemos todos los espacios en blanco
    letraCodigo = cin.get();
    cin>>numeroCodigo>>ws; //Se lee parte numérica del código y se extraen espacios en blanco para leer el nombre luego.
    leeImprimeNombreEnMayus();
    cin>>numSeguidores;
    //Imprimimos codigo, fecha de Creacion y numero de Seguidores

    cout << letraCodigo << numeroCodigo << setw(7)<< ' ';
    imprimeFecha(fechaCreacion);
    cout << setw(10) << ' ' << numSeguidores << endl;
    //while (cin.get()!='\n') break;
    leeImprimeStreamsDelCanal(duracionTotal,ultimaPubli,totalReproducciones,ingresoPublicidad,cantStreamsTotal);
    duracionTotalStreams+=duracionTotal;
    ingresosTotalesPorPubli +=ingresoPublicidad;
    if (ingresoPublicidad>mejorIngresoCanal) {
        mejorIngresoCanal = ingresoPublicidad;
        numericoCodigoMejor = numeroCodigo;
        letraCodigoMejor = letraCodigo;
    }
    imprimeResumenCanal(duracionTotal,ultimaPubli,totalReproducciones,ingresoPublicidad);
}

void leeImprimeStreamsDelCanal(int &duracionTotal,int &ultimaPubli,int &totalReproducciones,double &ingresoPublicidad,
    int &cantStreamsTotal) {
    int fechaStream, duracionStream, numeroReproducciones;
    imprimeLinea('-');
    imprimeEncabezadoReproducciones();
    while (true) {
        cin>>ws;
        fechaStream = leeFecha();
        duracionStream = leeHora();
        cin>>numeroReproducciones;
        cout << setw(12) << ' ';
        imprimeFecha(fechaStream);
        cout << setw(22) << ' ';
        imprimeHora(duracionStream);
        cout << setw(25)<<numeroReproducciones<<endl;
        //Actualizamos acumuladores
        if (fechaStream>ultimaPubli) ultimaPubli = fechaStream;
        duracionTotal += duracionStream;
        totalReproducciones += numeroReproducciones;
        ingresoPublicidad += ((double)numeroReproducciones/1000)*INGRESO_PUBLICIDAD;
        cantStreamsTotal++;
        if (cin.get()=='\n') break;
    }
}

void imprimeResumenCanal(int duracionTotal,int ultimaPubli,int totalReproducciones,double ingresoPublicidad) {
    imprimeLinea('-');
    cout << setw(6) << ' ' << "RESUMEN DEL CANAL: "<<endl;
    cout << setw(6) << ' ' << "DURACION TOTAL DE LAS REPRODUCCIONES: ";
    imprimeHora(duracionTotal);
    cout <<endl;
    cout << setw(6) << ' ' << "ULTIMA PUBLICACION: ";
    imprimeFecha(ultimaPubli);
    cout <<endl;
    cout << setw(6) << ' ' << "TOTAL DE REPRODUCCIONES: "<< totalReproducciones << endl;
    cout << setw(6) << ' ' << "INGRESOS POR PUBLICIDAD: "<< ingresoPublicidad << endl;

}

void imprimeResumenFinal(int cantStreamsTotal, int duracionTotalStreams, double ingresosTotalesPorPubli,
    double mejorIngresoCanal, int numericoCodigoMejor, char letraCodigoMejor) {
    imprimeLinea('=');
    cout <<"RESUMEN FINAL: ";
    cout <<"CANTIDAD TOTAL DE STREAMS COLOCADO POR LOS CANALES: " << cantStreamsTotal<<endl;
    cout <<"DURACION TOTAL DE LOS STREAMS PUBLICADOS: ";
    imprimeHora(duracionTotalStreams);
    cout <<endl;
    cout <<"INGRESOS TOTALES POR PUBLICIDAD: " << ingresosTotalesPorPubli<<endl;
    cout <<"CANAL CON MAYORES INGRESOS POR PUBLICIDAD: " << letraCodigoMejor<<numericoCodigoMejor << " CON:";
    cout << mejorIngresoCanal << endl;

}


int leeFecha() {
    int dd, mm, aa;
    char c;
    cin>>dd>>c>>mm>>c>>aa;
    return aa*10000 + mm*100 + dd;
}

int leeHora() {
    int seg, min, hor;
    char c;
    cin>>hor>>c>>min>>c>>seg;
    return hor*3600 + min*60 + seg;
}

void leeImprimeNombreEnMayus() {
    int i=0;
    char c;
    cout << setw(6) << ' '; //Imprimimos sangria a la izquierda del nombre
    while (true) {
        c = cin.get();
        if (c==' ') break;
        if (c>='a' and c<='z')
            c -= 'a' -'A'; //Pasamos a mayus;
        cout.put(c);
        i++;
    }
    int espacios = SIZE_NAME -i;
    cout << setw(espacios) << ' ';
}


void imprimeEncabezadoTwitch() {
    cout << setw((SIZE_LINE+20)/2) << "PLATAFORMA TP_Twitch" << endl;
    cout << setw((SIZE_LINE+33)/2) << "REGISTRO DE LOS CANALES AFILIADOS" << endl;
    cout << setw((SIZE_LINE+54)/2) << "FECHAS DE CREACION ENTRE EL 09/09/2022 Y EL 01/01/2023" << endl;
}

void imprimeEncabezadoCanal(int numCanales) {
    imprimeLinea('=');
    cout << "CANAL No. " << numCanales << endl;
    cout << setw(12)<< "NOMBRE" << setw(20)<<"CODIGO" << setw(15)
         <<"CREADO EL" << setw(26)<<"NUMERO DE SEGUIDORES" << endl;
}

void imprimeEncabezadoReproducciones() {
    cout << setw(6) <<' '<< "ULTIMAS REPRODUCCIONES"<<endl;
    cout << setw(12) << ' ' << "FECHA DE PUBLICACION";
    cout << setw(25) << "TIEMPO DE DURACION";
    cout << setw(30) << "NUMERO DE REPRODUCCIONES"<<endl;
}


void imprimeFecha(int fecha) {
    int aa,dd,mm;
    aa = fecha/10000;
    mm = (fecha%10000)/100;
    dd = fecha%100;
    cout << setfill('0') << setw(2) << dd << '/';
    cout << setfill('0') << setw(2) << mm << '/';
    cout << aa;
    cout << setfill(' ');
}

void imprimeHora(int tiempoEnSeg) {
    int hh,mm,ss;
    hh = tiempoEnSeg/3600;
    mm = (tiempoEnSeg%3600)/60;
    ss = tiempoEnSeg%60;
    cout << setfill('0') << setw(2) << hh << ':';
    cout << setfill('0') << setw(2) << mm << ':';
    cout << setfill('0') << setw(2) << ss;
    cout << setfill(' ');
}

void imprimeLinea(char car) {
    for (int i=0;i<SIZE_LINE;i++)
        cout.put(car);
    cout<<endl;
}


