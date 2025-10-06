/*
 *
 * Proyecto:    Lab4_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       4/10/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define NOT_FOUND (-1)
#define TAM_LINEA 145

void solicitarTarifa(double &tarifa) {
    cout << "Ingrese el valor de la tarifa por duración de la etiqueta " << endl;
    cin >> tarifa;
}

void cargarArreglosCanales(const char *nombArch, int *arrCanalFechaCreacion,int *arrCanalCodNum,
    double *arrCanalRating, char *arrCanalCodLetra,int *arrCanalPorcentaje,int &cantCanales) {
    ifstream archCanal(nombArch,ios::in);
    if (not archCanal.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    int diaCreacion,mesCreacion,anhoCreacion,numeroCodigo;
    char c, letraCodigo;
    double rating;
    while (true) {
        archCanal>>diaCreacion;
        if (archCanal.eof()) break;
        archCanal>>c>>mesCreacion>>c>>anhoCreacion;
        archCanal>>ws>>letraCodigo>>numeroCodigo>>ws;
        while (archCanal.get() != ' ');
        archCanal>>rating;
        while (archCanal.get() != '\n');
        arrCanalFechaCreacion[cantCanales] = anhoCreacion*10000 + mesCreacion*100 + diaCreacion;
        arrCanalCodNum[cantCanales] = numeroCodigo;
        arrCanalCodLetra[cantCanales] = letraCodigo;
        arrCanalRating[cantCanales] = rating;
        if (rating>=1 and rating<=2) arrCanalPorcentaje[cantCanales] = -25 ;
        else if (rating<=3) arrCanalPorcentaje[cantCanales] = 0;
        else if (rating<=4) arrCanalPorcentaje[cantCanales] = 20;
        else if (rating<=5) arrCanalPorcentaje[cantCanales] = 30;
        cantCanales++;
    }
}


void cargarArreglosEtiquetas(const char *nombArch,int *arrEtiqCod,int *arrEtiqDuracion,int &cantEtiquetas) {
    ifstream archEtiquetas(nombArch,ios::in);
    if (not archEtiquetas.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    int codEtiqueta, minDuracion, segDuracion;

    while (true) {
        archEtiquetas>>codEtiqueta;
        if (archEtiquetas.eof())break;
        archEtiquetas>>ws;
        while (archEtiquetas.get() != ' ');
        archEtiquetas>>minDuracion;
        archEtiquetas.get();
        archEtiquetas>>segDuracion;
        arrEtiqCod[cantEtiquetas] = codEtiqueta;
        arrEtiqDuracion[cantEtiquetas] = minDuracion*60 + segDuracion;
        cantEtiquetas++;
    }
}

void imprimeReportePrueba(const char *nombArch,
    int *arrCanalFechaCreacion, int *arrCanalCodNum, double *arrCanalRating, char *arrCanalCodLetra, int *arrCanalPorcentaje,int cantCanales,
    int *arrEtiqCod, int *arrEtiqDuracion, int cantEtiquetas) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep<<setprecision(2)<<fixed;

    archRep << "CANALES ADSCRITOS A LA PLATAFORMA" << endl;
    archRep << "CODIGO" << setw(20) << "FECHA CREACION" <<  setw(10) <<"RATING" << setw(15) <<"PORCENTAJE" << endl;
    for (int i = 0; i < cantCanales; i++) {
        archRep << arrCanalCodLetra[i] << arrCanalCodNum[i];
        archRep << setw(7) << " ";
        imprimeFecha(archRep,arrCanalFechaCreacion[i]);
        archRep << setw(13) << arrCanalRating[i];
        archRep<<setw(14) << arrCanalPorcentaje[i]<<'%'<<endl;
    }
    archRep << "ETIQUETAS DE LA PLATAFORMA" << endl;
    archRep << "CODIGO" << setw(15) << "DURACION" << endl;
    for (int i = 0; i < cantEtiquetas; i++) {
        archRep << arrEtiqCod[i] << setw(5) << " ";
        imprimeHora(archRep,arrEtiqDuracion[i]);
        archRep << endl;
    }
}

void procesarReproduccionesEtiquetas(const char *nombArch,
    char *arrCanalCodLetra, int *arrCanalCodNum, double *arrCanalRating,int *arrCanalPorcentaje,
    int *arrCanalNumRepro, int *arrCanalTiempoRepro, double *arrCanalIngresos, int cantCanales,
    int *arrEtiqCod, int *arrEtiqDuracion, int *arrEtiqNumRepro, int *arrEtiqTiempoRepro, int cantEtiquetas,double tarifa) {
    ifstream archReprod(nombArch,ios::in);
    if (not archReprod.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    int datoFecha, codCanalNum, codEtiqueta, numReproducciones;
    char c, codCanalLet;
    while (true) {
        archReprod>>datoFecha;
        if (archReprod.eof())break;
        //Leo /MM/AAAA, variable generica pues no se usa la fecha de registro de la etiqueta
        archReprod>>c>>datoFecha>>c>>datoFecha;
        archReprod>>ws>>codCanalLet>>codCanalNum;
        archReprod>>codEtiqueta>>numReproducciones;
        int posCanal = buscarCanal(arrCanalCodLetra,arrCanalCodNum,codCanalLet,codCanalNum,cantCanales);
        int posEtiqueta = buscarEtiqueta(arrEtiqCod,codEtiqueta,cantEtiquetas);
        if (posCanal!=NOT_FOUND and posEtiqueta!=NOT_FOUND) {
            actualizarArreglosCanales(arrCanalRating[posCanal],arrCanalPorcentaje[posCanal],
                arrCanalNumRepro[posCanal],
                arrCanalTiempoRepro[posCanal],arrCanalIngresos[posCanal],
                numReproducciones,arrEtiqDuracion[posEtiqueta],tarifa);
            actualizarArreglosEtiquetas(arrEtiqNumRepro[posEtiqueta],arrEtiqTiempoRepro[posEtiqueta],
                arrEtiqDuracion[posEtiqueta],numReproducciones);
        }
    }

}

void actualizarArreglosCanales(double ratingCanal, int porcentajeIntRating,
    int &numReprodCanal, int &tiempoReproCanal, double &ingresosCanal,
    int numReproducciones,int duracionEtiqueta,double tarifa) {
    numReprodCanal+=numReproducciones;
    tiempoReproCanal += duracionEtiqueta*numReproducciones;
    double cantMinutosRepro = (duracionEtiqueta*numReproducciones)/(double)60;
    ingresosCanal += cantMinutosRepro*(1 + (double)porcentajeIntRating/100)*tarifa;
}

void actualizarArreglosEtiquetas(int &etiqNumRepro, int &etiqTiempoRepro, int duracionEtiqueta, int numReproducciones) {
    etiqNumRepro += numReproducciones;
    etiqTiempoRepro += duracionEtiqueta*numReproducciones;
}


int buscarCanal(const char *arrCanalCodLetra,const int *arrCanalCodNum,char codCanalLet,int codCanalNum,int cantCanales) {
    for (int i = 0; i < cantCanales; ++i) {
        if (arrCanalCodLetra[i]==codCanalLet and arrCanalCodNum[i]==codCanalNum)
            return i;
    }
    return NOT_FOUND;
}

int buscarEtiqueta(const int *arrEtiqCod, int codEtiqueta, int cantEtiquetas) {
    for (int i = 0; i < cantEtiquetas; ++i) {
        if (arrEtiqCod[i]==codEtiqueta)
            return i;
    }
    return NOT_FOUND;
}

void imprimirReporteFinal(const char *nombArch,
    int *arrCanalCodNum, int *arrCanalFechaCreacion, int *arrCanalPorcentaje, int *arrCanalNumRepro,
    int *arrCanalTiempoRepro, double *arrCanalRating, double *arrCanalIngresos, char *arrCanalCodLetra, int cantCanales,
    int *arrEtiqCod, int *arrEtiqDuracion, int *arrEtiqNumRepro, int *arrEtiqTiempoRepro, int cantEtiquetas,double tarifa) {

    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }

    archRep<<setprecision(2)<<fixed;

    imprimeEncabezado(archRep,tarifa);
    imprimeEncabezadoCanales(archRep);
    for (int i = 0; i < cantCanales; ++i) {
        archRep << setw(3) << i+1 << ")" << setw(6) << arrCanalCodLetra[i] << arrCanalCodNum[i] << setw(8) << " ";
        imprimeFecha(archRep,arrCanalFechaCreacion[i]);
        archRep << setw(19) << arrCanalRating[i] << setw(20) << arrCanalNumRepro[i] << setw(14) << " ";
        imprimeHora(archRep,arrCanalTiempoRepro[i]);
        archRep << setw(15) << arrCanalPorcentaje[i] << '%' << setw(22) << arrCanalIngresos[i] << endl;
    }
    imprimeEncabezadoEtiquetas(archRep);
    for (int i = 0; i < cantEtiquetas; ++i) {
        archRep << setw(3) << i+1 << ")" << setw(10) << arrEtiqCod[i] << setw(10) << " ";
        imprimeMMSS(archRep,arrEtiqDuracion[i]);
        archRep << setw(20) << arrEtiqNumRepro[i] << setw(15) << " ";
        imprimeHora(archRep,arrEtiqTiempoRepro[i]);
        archRep << endl;
    }
}


void imprimeFecha(ofstream &archRep, int fecha) {
    int aa = fecha/10000;
    int mm = (fecha%10000)/100;
    int dd = fecha%100;

    archRep << setfill('0') << setw(2) << dd << '/';
    archRep << setw(2) << mm << '/';
    archRep << setw(4) << aa << setfill(' ');

}

void imprimeHora(ofstream &archRep, int tiempoSegundos) {
    int hh = tiempoSegundos/3600;
    int mm = (tiempoSegundos%3600)/60;
    int ss = tiempoSegundos%60;

    archRep << setfill('0') << setw(2) << hh << ':';
    archRep << setw(2) << mm << ':';
    archRep << setw(2) << ss << setfill(' ');
}

void imprimeMMSS(ofstream &archRep, int tiempoSegundos) {
    int hh = tiempoSegundos/3600;
    int mm = (tiempoSegundos%3600)/60;
    int ss = tiempoSegundos%60;

    archRep << setfill('0')
            << setw(2) << mm << ':'
            << setw(2) << ss << setfill(' ');
}


void imprimeEncabezado(ofstream &archRep, double tarifa) {
    archRep << setw((TAM_LINEA+20)/2) <<"PLATAFORMA TP_Twitch" << endl;
    archRep << setw(60) << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifa << " POR CADA MINUTO Y FRACCION" << endl;
}

void imprimeEncabezadoCanales(ofstream &archRep) {
    imprimeLinea(archRep,'=');
    archRep << "CANALES ADSCRITOS A LA PLATAFORMA" << endl;
    imprimeLinea(archRep,'-');
    archRep << setw(49) << "RATING DE" << setw(23) << "NUMERO TOTAL DE" << setw(21) << "TIEMPO TOTAL DE"
            << setw(21) << "PORCENTAJE DE"
            << setw(30) << "INGRESOS POR REPRODUCCION" << endl;
    archRep << "No." << setw(12) <<"CODIGO" << setw(20) <<"FECHA DE CREACION" << setw(12) <<"CALIDAD"
            << setw(25) << "DE REPRODUCCIONES" << setw(20) <<"REPRODUCCIONES"
            << setw(23) << "RATING DE CALIDAD" << setw(22) <<"DE ETIQUETAS" << endl;
    imprimeLinea(archRep,'-');
}

void imprimeEncabezadoEtiquetas(ofstream &archRep) {
    imprimeLinea(archRep,'=');
    archRep << "ETIQUETAS DE LA PLATAFORMA" << endl;
    imprimeLinea(archRep,'-');
    archRep << setw(55) << "CANTIDAD TOTAL DE" << setw(21) << "TIEMPO TOTAL DE" << endl;
    archRep << "No." << setw(12) <<"ETIQUETA" << setw(15) <<"DURACION"
            << setw(25) << "DE REPRODUCCIONES" << setw(20) <<"REPRODUCIDO" << endl;
    imprimeLinea(archRep,'-');
}


void imprimeLinea(ofstream &archRep, char car) {
    for (int i=0;i<TAM_LINEA;i++)
        archRep.put(car);
    archRep<<endl;
}

