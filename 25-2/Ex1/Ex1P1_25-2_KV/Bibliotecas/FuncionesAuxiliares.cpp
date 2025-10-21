/*
 *
 * Proyecto:    Ex1P1_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       19/10/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define TAM_LINEA 155
#define TAM_NOMBRE 60
#define TAM_IDIOMA 15

void procesarReproduccionesDeStreams(const char *nombArchStreams, const char *nombArchCategorias,
    const char *nombArchIdiomas, const char *nombArchCanales, const char *nombArchReporte) {

    ifstream archStreams (nombArchStreams,ios::in);
    if (not archStreams.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchStreams << endl;
        exit(1);
    }
    ifstream archCategorias (nombArchCategorias,ios::in);
    if (not archCategorias.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchCategorias << endl;
        exit(1);
    }
    ifstream archIdiomas (nombArchIdiomas,ios::in);
    if (not archIdiomas.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchIdiomas << endl;
        exit(1);
    }
    ifstream archCanales (nombArchCanales,ios::in);
    if (not archCanales.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchCanales << endl;
        exit(1);
    }
    ofstream archReporte (nombArchReporte, ios::out);
    if (not archReporte.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArchReporte << endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;

    imprimeEncabezado(archReporte);

    int codStream, duracionStream, codIdioma, numCategoria;
    char letraCategoria, letraDOMenor, letraDOMayor;
    int numDOMenor, numDOMayor;
    //Variables resumen final
    int cantStreams =0, duracionTotalReproduccion=0;
    while (true) {
        int vecesReproducidas=0, tiempoTotalReprod=0;
        double dropOffMenor=99999, dropOffMayor=0;
        archStreams >> codStream;
        if (archStreams.eof()) break;
        duracionStream = leerHoraOFecha(archStreams,true);
        archStreams >>codIdioma >> letraCategoria>>numCategoria;
        imprimeInformacionStream(archReporte,archCategorias,archIdiomas,codStream,letraCategoria,numCategoria,codIdioma,duracionStream);
        imprimeStreamEnCanales(archReporte,archCanales,codStream,duracionStream,vecesReproducidas,tiempoTotalReprod,dropOffMenor,dropOffMayor,
            letraDOMenor,numDOMenor,letraDOMayor,numDOMayor);
        imprimeResumenStream(archReporte,vecesReproducidas,tiempoTotalReprod,dropOffMenor,dropOffMayor,
            letraDOMenor,numDOMenor,letraDOMayor,numDOMayor);
        cantStreams++;
        duracionTotalReproduccion += tiempoTotalReprod;
    }
    imprimeResumenTotal(archReporte,cantStreams,duracionTotalReproduccion);

}

void imprimeInformacionStream(ofstream &archRep, ifstream &archCategorias, ifstream &archIdiomas,
    int codStream, char letraCategoria, int numCategoria, int numIdioma, int duracionStream) {
    imprimeLinea(archRep,'=');
    archRep << "STREAM: " << setw(10) << codStream;
    imprimeCategoria(archRep,archCategorias,letraCategoria,numCategoria);
    imprimeIdioma(archRep,archIdiomas,numIdioma);
    archRep << "DURACION: ";
    imprimeHora(archRep,duracionStream);
    archRep<<endl;
    imprimeLinea(archRep,'=');
}

void imprimeCategoria(ofstream &archRep, ifstream &archCategorias, char letraCategoria, int numCategoria) {
    archRep << setw(12) << "CATEGORIA:" << setw(4) << letraCategoria << numCategoria << " - ";

    archCategorias.clear();
    archCategorias.seekg(0,ios::beg);
    int codBuscado;
    char letraBuscada;
    while (true) {
        archCategorias>>letraBuscada;
        if (archCategorias.eof())break;
        archCategorias>>codBuscado>>ws;
        if (letraBuscada==letraCategoria and codBuscado==numCategoria)
            imprimeCadena(archRep,archCategorias,true);
        else
            saltarCadena(archCategorias,'\n');
    }

}

void imprimeIdioma(ofstream &archRep, ifstream &archIdiomas, int numIdioma) {
    archRep << setw(12) << "IDIOMA:" << setw(6) << numIdioma << " - ";

    archIdiomas.clear();
    archIdiomas.seekg(0,ios::beg);
    int codBuscado;
    while (true) {
        archIdiomas>>codBuscado;
        if (archIdiomas.eof())break;
        archIdiomas>>ws;
        if (codBuscado==numIdioma)
            imprimeCadena(archRep,archIdiomas,false);
        else
            saltarCadena(archIdiomas,'\n');
    }

}
// 6/2/2021    A7791    auronplay    678119    16/7/2025    17:52:9    2.35    0.960
void imprimeStreamEnCanales(ofstream &archReporte, ifstream &archCanales,
    int codStream, int duracionStream, int &vecesReproducidas, int &tiempoTotalReprod,
    double &dropOffMenor, double &dropOffMayor, char &letraDOMenor, int &numDOMenor, char &letraDOMayor, int &numDOMayor) {

    archCanales.clear();
    archCanales.seekg(0,ios::beg);

    int codNumCanal, datoNum, fechaReprod, horaInicio, codStreamLeido, contCanales=0;
    double ratingCalidad, dropOff;
    char codLetCanal;

    while (true) {
        archCanales>>datoNum;
        if (archCanales.eof())break;
        saltarCadena(archCanales,' ');
        archCanales>>codLetCanal>>codNumCanal>>ws; //Sacamos el espacio en blanco previo al nombre del canal
        saltarCadena(archCanales,' ');
        bool encabezadoImpreso=true;
        int cantReproduccionesCanal=0, tiempoTotalXCanal=0;
        double sumaRatingCanal=0.0, sumaDropOffCanal=0.0;
        while (true) {
            if (archCanales.get()=='\n') break;
            archCanales>>codStreamLeido;
            fechaReprod = leerHoraOFecha(archCanales,false);
            horaInicio = leerHoraOFecha(archCanales,true);
            archCanales>>ratingCalidad>>dropOff;
            if (codStreamLeido==codStream) {
                if (encabezadoImpreso)
                    imprimeEncabezadoCanal(archReporte,codLetCanal,codNumCanal,contCanales,encabezadoImpreso);
                imprimeReproduccion(archReporte,fechaReprod,horaInicio,duracionStream,ratingCalidad,dropOff,cantReproduccionesCanal,
                    tiempoTotalXCanal,sumaRatingCanal,sumaDropOffCanal);
                actualizarMenorMayorDropOff(dropOff,codLetCanal,codNumCanal,dropOffMenor,dropOffMayor,letraDOMenor,numDOMenor,letraDOMayor,numDOMayor);
            }
        }
        if (cantReproduccionesCanal>0) {
            imprimeResumenXCanal(archReporte,cantReproduccionesCanal,tiempoTotalXCanal,sumaRatingCanal,sumaDropOffCanal);
            vecesReproducidas += cantReproduccionesCanal;
            tiempoTotalReprod += tiempoTotalXCanal;
        }
    }

}

void imprimeEncabezadoCanal(ofstream &archReporte,char codLetCanal,int codNumCanal,int &contCanales,bool &encabezadoImpreso) {

    archReporte << setw(2) << ' ' << setfill('0') << setw(2) << contCanales+1 << ')' << setfill(' ');
    archReporte << setw(9) << "CANAL: " << codLetCanal << codNumCanal << endl;
    archReporte << setw(21) << "REPRODUCCIONES" << endl;
    archReporte << setw(10) << "No." << setw(12) << "FECHA" << setw(16) << "INICIO" << setw(13) << "FIN"
                << setw(25) << "RATING CALIDAD" << setw(20) << "TASA DROP-OFF" << endl;
    contCanales++;
    encabezadoImpreso=false;
}

void imprimeReproduccion(ofstream &archReporte, int fechaReprod, int horaInicio, int duracionStream,
    double ratingCalidad, double dropOff, int &cantReproducciones,int &tiempoTotalXCanal,double &sumaRating,double &sumaDropOff) {
    archReporte<<setw(7) << ' ' << setfill('0') << setw(2) << cantReproducciones+1 << ')' << setfill(' ');
    archReporte << setw(5) << ' ';
    imprimeFecha(archReporte,fechaReprod);
    archReporte << setw(5) << ' ';
    imprimeHora(archReporte,horaInicio);
    archReporte << setw(7) << ' ';
    imprimeHora(archReporte,horaInicio+duracionStream);
    archReporte << setw(18) << ratingCalidad << setw(20) << dropOff << '%' << endl;
    cantReproducciones++;
    tiempoTotalXCanal+= duracionStream;
    sumaRating += ratingCalidad;
    sumaDropOff += dropOff;
}

void actualizarMenorMayorDropOff(double dropOff,char codLetCanal,int codNumCanal,double &dropOffMenor,double &dropOffMayor,
    char &letraDOMenor,int &numDOMenor,char &letraDOMayor,int &numDOMayor) {
    if (dropOff>dropOffMayor) {
        dropOffMayor = dropOff;
        letraDOMayor = codLetCanal;
        numDOMayor = codNumCanal;
    }
    if (dropOff<dropOffMenor) {
        dropOffMenor = dropOff;
        letraDOMenor = codLetCanal;
        numDOMenor = codNumCanal;
    }
}

void imprimeResumenXCanal(ofstream &archReporte,int cantReproduccionesCanal,
    int tiempoTotalXCanal,double sumaRatingCanal,double sumaDropOffCanal) {
    archReporte << endl;
    archReporte << setw(7) << ' ' << "TOTAL TIEMPO REPRODUCCIONES: ";
    imprimeHora(archReporte,tiempoTotalXCanal);
    archReporte << endl;
    archReporte << setw(7) << ' ' << "PROMEDIO RATING CALIDAD: " << sumaRatingCanal/cantReproduccionesCanal << endl;
    archReporte << setw(7) << ' ' << "PROMEDIO TASA DROP-OFF: " << sumaDropOffCanal/cantReproduccionesCanal << endl;

    imprimeLinea(archReporte,'-');
}

void imprimeResumenStream(ofstream &archReporte, int vecesReproducidas, int tiempoTotalReprod, double dropOffMenor,
    double dropOffMayor, char letraDOMenor, int numDOMenor, char letraDOMayor, int numDOMayor) {
    archReporte << "RESUMEN DEL STREAM:" << endl;
    archReporte << "#VECES REPRODUCIDAS: " << vecesReproducidas << endl;
    archReporte << "#TIEMPO TOTAL REPRODUCCION: ";
    imprimeHora(archReporte,tiempoTotalReprod);
    archReporte << endl;
    archReporte << "TASA DROP-OFF MENOR: " << dropOffMenor << " CANAL: " << letraDOMenor << numDOMenor <<endl;
    archReporte << "TASA DROP-OFF MAYOR: " << dropOffMayor << " CANAL: " << letraDOMayor << numDOMayor <<endl;
}

void imprimeResumenTotal(ofstream &archReporte,int cantStreams,int duracionTotalReproduccion) {
    imprimeLinea(archReporte,'=');
    archReporte << "RESUMEN TOTAL: " << endl;
    imprimeLinea(archReporte,'-');
    archReporte << "# STREAMS: " << cantStreams << endl;
    archReporte << "DURACION TOTAL REPRODUCCION: ";
    imprimeHora(archReporte,duracionTotalReproduccion);
    archReporte<<endl;
    imprimeLinea(archReporte,'=');
}


void imprimeCadena(ofstream &archRep, ifstream &archIn, bool enMayus) {
    char car;
    int cantCaracteres=0,cantBlancos;
    while (true) {
        car = archIn.get();
        if (car=='\n') break;
        if (car=='_') car = ' ';
        if (enMayus) {
            if (car >= 'a' and car <= 'z')
                car -= ('a'-'A');
        }
        archRep.put(car);
        cantCaracteres++;
    }
    if (enMayus)
        cantBlancos = TAM_NOMBRE-cantCaracteres;
    else
        cantBlancos = TAM_IDIOMA-cantCaracteres;
    archRep << setw(cantBlancos) << ' ';

}

void saltarCadena(ifstream &archIn, char delim) {
    while (archIn.get()!=delim);
}



void imprimeEncabezado(ofstream &archReporte) {
    imprimeLinea(archReporte,'=');
    archReporte << setw((TAM_LINEA+26)/2) << "PLATAFORMA DE STREAMING TP" << endl;
    archReporte << setw((TAM_LINEA+23)/2) << "REPRODUCCION DE STREAMS" << endl;
}

void imprimeLinea(ofstream &archReporte, char car) {
    for (int i=0; i<TAM_LINEA; i++)
        archReporte.put(car);
    archReporte << endl;
}

int leerHoraOFecha(ifstream &archIn, bool esHora) {
    int dd_hh, mm, aa_ss;
    archIn>>dd_hh;
    archIn.get();
    archIn>>mm;
    archIn.get();
    archIn>>aa_ss;

    //Si es hora el tiempo se transforma a segundos
    if (esHora)
        return dd_hh*3600 + mm*60 + aa_ss;
    //Si es fecha se empaqueta en AAAAMMDD
    return aa_ss*10000 + mm*100 + dd_hh;
}

void imprimeHora(ofstream &archRep, int tiempoSegundos) {
    int hh, mm, ss;
    hh = tiempoSegundos/3600;
    mm = (tiempoSegundos%3600)/60;
    ss = tiempoSegundos%60;

    archRep << setfill('0') << setw(2) << hh << ':';
    archRep << setw(2) << mm << ':';
    archRep << setw(2) << ss << setfill(' ');

}

void imprimeFecha(ofstream &archRep, int AAAAMMDD) {
    int dd, mm, aa;
    aa = AAAAMMDD/10000;
    mm = (AAAAMMDD%10000)/100;
    dd = AAAAMMDD%100;

    archRep << setfill('0') << setw(2) << dd << '/';
    archRep << setw(2) << mm << '/';
    archRep << setw(4) << aa << setfill(' ');

}