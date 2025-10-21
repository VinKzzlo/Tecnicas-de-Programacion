/*
 *
 * Proyecto:    Lab5_25_2_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       6/10/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define NOT_FOUND (-1)
#define TAM_LINEA 120

void solicitaTarifa(double &tarifa) {
    cout << "INGRESE EL MONTO DE LA TARIFA PARA LOS INGRESOS POR DURACIÓN DE LAS ETIQUETAS" << endl;
    cin >> tarifa;
}


void cargarCanales(const char *nombArch,int *arrCanalCodNum,char *arrCanalCodLet,double *arrCanalRating,int &cantCanales) {
    ifstream archCanal(nombArch,ios::in);
    if (not archCanal.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
    }
    // 26/12/2021     M8596     Maximilian_DOOD     1.46

    int num, codNum;
    char codLetra;
    double rating;
    while (true) {
        archCanal>>num;
        if (archCanal.eof())break;
        while (archCanal.get()!=' ');
        archCanal>>codLetra>>codNum>>ws;
        while (archCanal.get()!=' ');
        archCanal>>rating;

        arrCanalCodLet[cantCanales] = codLetra;
        arrCanalCodNum[cantCanales] = codNum;
        arrCanalRating[cantCanales] = rating;

        cantCanales++;
    }

}

void cargarEtiquetas(const char *nombArch, int *arrEtiquetaCod, int *arrEtiquetaDuracion, int &cantEtiquetas) {
    ifstream archEtiqueta(nombArch,ios::in);
    if (not archEtiqueta.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
    }

    int codEtiqueta, mm, ss;

    while (true) {
        archEtiqueta>>codEtiqueta;
        if (archEtiqueta.eof())break;
        archEtiqueta>>ws;
        while (archEtiqueta.get()!=' ');
        archEtiqueta>>mm;
        archEtiqueta.get();
        archEtiqueta>>ss;

        arrEtiquetaCod[cantEtiquetas] = codEtiqueta;
        arrEtiquetaDuracion[cantEtiquetas] = mm*60 + ss;
        cantEtiquetas++;
    }

}

void cargarEtiquetasEnCanales(const char *nombArch, int *arrEtiqCanNumCanal, char *arrEtiqCanLetCanal,
    int *arrEtiqCanCodEtiqueta, int &cantEtiquetasEnCanales) {

    ifstream archEtiqEnCanal(nombArch,ios::in);
    if (not archEtiqEnCanal.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
    }

    int canalNum, codEtiqueta;
    char canalLet;

    while (true) {
        archEtiqEnCanal>>canalLet;
        if (archEtiqEnCanal.eof())break;
        archEtiqEnCanal>>canalNum>>codEtiqueta;

        //Para evitar repetidos (no se solicitó el el lab pero para tenerlo en cuenta)
        int posCanalEtiq = buscarEtiquetaEnCanal(canalLet,canalNum,codEtiqueta,
            arrEtiqCanLetCanal,arrEtiqCanNumCanal,arrEtiqCanCodEtiqueta,cantEtiquetasEnCanales);

        if (posCanalEtiq == NOT_FOUND) {
            arrEtiqCanLetCanal[cantEtiquetasEnCanales] = canalLet;
            arrEtiqCanNumCanal[cantEtiquetasEnCanales] = canalNum;
            arrEtiqCanCodEtiqueta[cantEtiquetasEnCanales] = codEtiqueta;
            cantEtiquetasEnCanales++;
        }

    }



}

int buscarEtiquetaEnCanal(char canalLet, int canalNum, int codEtiqueta,
    const char *arrEtiqCanLetCanal,const int *arrEtiqCanNumCanal,const int *arrEtiqCanCodEtiqueta, int cantEtiquetasEnCanales) {
    for (int i = 0; i < cantEtiquetasEnCanales; ++i) {
        if (canalLet==arrEtiqCanLetCanal[i] and canalNum==arrEtiqCanNumCanal[i] and codEtiqueta==arrEtiqCanCodEtiqueta[i])
            return i;
    }
    return NOT_FOUND;
}

void imprimeReporteSimple(const char *nombArch, int *arrCanalCodNum, char *arrCanalCodLet, double *arrCanalRating, int cantCanales,
    int *arrEtiquetaCod, int *arrEtiquetaDuracion, int cantEtiquetas,
    int *arrEtiqCanNumCanal, char *arrEtiqCanLetCanal, int *arrEtiqCanCodEtiqueta, int cantEtiquetasEnCanales) {
    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep << setprecision(2) << fixed;

    archRep << "DATOS Leídos y almacenados en arreglos" << endl;

    archRep << "CANALES REGISTRADOS" << endl;
    for (int i = 0; i < cantCanales; ++i) {
        archRep << setw(5) << arrCanalCodLet[i] << arrCanalCodNum[i] << setw(10) << arrCanalRating[i] << endl;
    }

    archRep << "ETIQUETAS REGISTRADAS" << endl;
    for (int i = 0; i < cantEtiquetas; ++i) {
        archRep << arrEtiquetaCod[i] << setw(10) << " ";
        imprimeMMSS(archRep,arrEtiquetaDuracion[i]);
        archRep << endl;
    }

    archRep << "ETIQUETAS EN CANALES" << endl;
    for (int i = 0; i < cantEtiquetasEnCanales; ++i) {
        archRep << arrEtiqCanLetCanal[i] << arrEtiqCanNumCanal[i] << setw(20) << arrEtiqCanCodEtiqueta[i] << endl;
    }


}

void ordenarEtiquetas(int *arrEtiquetaCod, int *arrEtiquetaDuracion, int cantEtiquetas) {
    for (int i = 0; i < cantEtiquetas-1; ++i)
        for (int j = i+1; j < cantEtiquetas; ++j) {
            if (arrEtiquetaDuracion[i] < arrEtiquetaDuracion[j]) {
                cambiarInt(arrEtiquetaCod[i],arrEtiquetaCod[j]);
                cambiarInt(arrEtiquetaDuracion[i],arrEtiquetaDuracion[j]);
            }
        }
}


void cambiarInt(int &datoI, int &datoJ) {
    int aux;
    aux = datoI;
    datoI = datoJ;
    datoJ = aux;
}

void acumulaReproducciones(const char *nombArch, int *arrEtiqCanTotalRep, int *arrEtiqCanTiempoTotal,
    int *arrEtiqCanNumCanal, char *arrEtiqCanLetCanal, int *arrEtiqCanCodEtiqueta, int cantEtiquetasEnCanales,
    int *arrCanalCodNum, char *arrCanalCodLet, int cantCanales,
    int *arrEtiquetaCod, int *arrEtiquetaDuracion, int cantEtiquetas) {

    ifstream archRepro(nombArch,ios::in);
    if (not archRepro.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
    }

    int dato, codCanal, codEtiqueta, numReprod;
    char letraCanal;

    while (true) {
        archRepro>>dato;
        if (archRepro.eof())break;
        while (archRepro.get()!= ' ');
        archRepro>>letraCanal>>codCanal>>codEtiqueta>>numReprod;
        int posCanEnEtiq = buscarEtiquetaEnCanal(letraCanal,codCanal,codEtiqueta,arrEtiqCanLetCanal,
            arrEtiqCanNumCanal,arrEtiqCanCodEtiqueta,cantEtiquetasEnCanales);
        if (posCanEnEtiq != NOT_FOUND) {
            int posCanal = buscarCanales(arrEtiqCanLetCanal[posCanEnEtiq],arrEtiqCanNumCanal[posCanEnEtiq],
                arrCanalCodNum,arrCanalCodLet,cantCanales);
            int posEtiqueta = buscarEtiquetas(arrEtiqCanCodEtiqueta[posCanEnEtiq],arrEtiquetaCod,cantEtiquetas);
            if (posCanal!=NOT_FOUND and posEtiqueta != NOT_FOUND) {
                arrEtiqCanTotalRep[posCanEnEtiq] += numReprod;
                arrEtiqCanTiempoTotal[posCanEnEtiq] += numReprod*arrEtiquetaDuracion[posEtiqueta];
            }
        }
    }

}

int buscarCanales(char letraCanal, int numeroCanal, int *arrCanalCodNum, char *arrCanalCodLet, int cantCanales) {
    for (int i = 0; i < cantCanales; ++i) {
        if (letraCanal==arrCanalCodLet[i] and numeroCanal==arrCanalCodNum[i])
            return i;
    }
    return NOT_FOUND;
}

int buscarEtiquetas(int codEtiqueta, int *arrEtiquetaCod, int cantEtiquetas) {
    for (int i = 0; i < cantEtiquetas; ++i) {
        if (codEtiqueta==arrEtiquetaCod[i])
            return i;
    }
    return NOT_FOUND;
}


void imprimeReporteFinal(const char *nombArch,
    int *arrCanalCodNum, char *arrCanalCodLet, double *arrCanalRating, int cantCanales,
    int *arrEtiquetaCod, int *arrEtiquetaDuracion, int cantEtiquetas,
    int *arrEtiqCanTotalRep, int *arrEtiqCanTiempoTotal, int *arrEtiqCanNumCanal, char *arrEtiqCanLetCanal,
    int *arrEtiqCanCodEtiqueta, int cantEtiquetasEnCanales,double tarifa) {

    ofstream archRep(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archRep << setprecision(2) << fixed;


    imprimeEncabezado(archRep,tarifa);
    for (int i = 0; i < cantEtiquetas; ++i) {

        imprimeDatosEtiqueta(archRep,i+1,arrEtiquetaCod[i],arrEtiquetaDuracion[i]);
        imprimeEncabezadoCanales(archRep);
        int totalReproducciones=0, tiempoTotalReproducido=0, contadorCanales=0;
        double sumaRating=0.0; //Para el promedio del resumen
        for (int j = 0; j < cantEtiquetasEnCanales ; ++j) {
            if (arrEtiquetaCod[i] == arrEtiqCanCodEtiqueta[j]) {
                archRep << setw(2) << contadorCanales+1 << ')' << setw(11) << arrEtiqCanLetCanal[j] << arrEtiqCanNumCanal[j];
                int posCanal = buscarCanales(arrEtiqCanLetCanal[j],arrEtiqCanNumCanal[j],arrCanalCodNum,arrCanalCodLet,cantCanales);
                archRep << setw(14) << arrCanalRating[posCanal];
                archRep << setw(20) << arrEtiqCanTotalRep[j] << setw(20) << ' ';
                imprimeHHMMSS(archRep,arrEtiqCanTiempoTotal[j]);
                archRep << endl;
                contadorCanales++;
                totalReproducciones += arrEtiqCanTotalRep[j];
                tiempoTotalReproducido += arrEtiqCanTiempoTotal[j];
                sumaRating += arrCanalRating[posCanal];
            }
        }
        imprimeResumenEtiqueta(archRep,totalReproducciones,tiempoTotalReproducido,sumaRating,contadorCanales,tarifa);
    }

}


void imprimeHHMMSS(ofstream &archRep, int tiempoSegundos) {
    int hh = tiempoSegundos/3600;
    int mm = (tiempoSegundos%3600)/60;
    int ss = tiempoSegundos%60;

    archRep << setw(3) << hh << ':';
    archRep << setfill('0') << setw(2) << mm << ':';
    archRep << setw(2) << ss << setfill(' ');

}

void imprimeMMSS(ofstream &archRep, int tiempoSegundos) {
    int hh = tiempoSegundos/3600;
    int mm = (tiempoSegundos%3600)/60;
    int ss = tiempoSegundos%60;

    archRep << setfill('0') << setw(2) << mm << ':';
    archRep << setw(2) << ss << setfill(' ');

}

void imprimeEncabezado(ofstream &archRep, double tarifa) {
    archRep << setw((TAM_LINEA+20)/2) << "PLATAFORMA TP_TWITCH" << endl;
    archRep << setw(60) << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifa << " POR CADA MINUTO Y FRACCIÓN" << endl;
}

void imprimeLinea(ofstream &archRep,char c) {
    for (int i=0; i < TAM_LINEA ; i++)
        archRep.put(c);
    archRep << endl;
}

void imprimeDatosEtiqueta(ofstream &archRep, int num, int codEtiqueta, int duracionEtiqueta) {
    imprimeLinea(archRep,'=');
    archRep << "ETIQUETA No. " << num << endl;
    archRep << setw(11) << "CODIGO: " << codEtiqueta << endl;
    archRep << setw(13) << "DURACION: ";
    imprimeMMSS(archRep,duracionEtiqueta);
    archRep << endl;
}

void imprimeEncabezadoCanales(ofstream &archRep) {
    imprimeLinea(archRep,'-');
    archRep << setw(29) << "CANALES DONDE SE REPRODUCE" << endl;
    archRep << setw(34) << "RATING DE" << setw(22) << "NUMERO TOTAL" << setw(28) << "TIEMPO TOTAL DE" << endl;
    archRep << "No." << setw(15) << "CODIGO" << setw(15) << "CALIDAD" << setw(25) << "DE REPRODUCCIONES"
    << setw(25) << "REPRODUCCIONES" << endl;
}

void imprimeResumenEtiqueta(ofstream &archRep, int totalReproducciones, int tiempoTotalReproducido,
    double sumaRating, int contadorCanales,double tarifa) {

    int porcentajePromedio;
    imprimeLinea(archRep,'-');
    archRep << setw(25) << "RESUMEN DE LA ETIQUETA" << endl;
    archRep << setw(29) << "TOTAL DE REPRODUCCIONES:" << setw(29) << totalReproducciones << endl;;
    archRep << setw(30) << "TIEMPO TOTAL REPRODUCIDO:" << setw(19) << ' ';
    imprimeHHMMSS(archRep,tiempoTotalReproducido);
    archRep << endl;
    double promedioRating = sumaRating/contadorCanales;
    //Calculo porcentaje promedio
    if (promedioRating>=1 and promedioRating <=2) porcentajePromedio=-25;
    else if (promedioRating<=3) porcentajePromedio = 0;
    else if (promedioRating<=4) porcentajePromedio = 20;
    else if (promedioRating<=5) porcentajePromedio = 30;

    double tiempoMinutos = (double)tiempoTotalReproducido/60;
    double ingresosReproducciones = tiempoMinutos*tarifa*(1+((double)porcentajePromedio/100));

    archRep << setw(36) << "PORCENTAJE PROMEDIO POR RATING:" << setw(21) << porcentajePromedio << '%' << endl;
    archRep <<  setw(33) << "INGRESOS POR REPRODUCCIONES:" << setw(25) <<ingresosReproducciones << endl;

}