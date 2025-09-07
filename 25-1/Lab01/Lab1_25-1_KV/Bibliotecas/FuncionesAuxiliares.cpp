/*
 *
 * Proyecto:    Lab1_25_1_KV
 * Archivo:     FuncionesAuxiliares.cpp
 * Autor:       VinKzzlo
 * Fecha:       1/09/2025
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define MAX_LINE 140
#define NAME_SIZE 60

void imprimeReporteProcesandoInfracciones() {
    int fechaIni = leerFecha();
    int fechaFin = leerFecha();
    //Se imprime el encabezado que contiene las fechas a considerar
    cout << setw((MAX_LINE+25)/2)<<"MINISTERIO DE TRANSPORTES" << endl;
    cout << setw((MAX_LINE+32)/2)<< "MULTAS IMPUESTAS A LAS COMPANIAS" << endl;
    cout << setw((MAX_LINE+14)/2)<<"RANGO DE FECHAS A CONSIDERAR: DEL ";
    imprimeFecha(fechaIni);
    cout << " - ";
    imprimeFecha(fechaFin);
    cout <<endl;
    //Ahora Iniciamos el procesamiento de la informacion contenida en el archivo
    procesarInfracciones(fechaIni,fechaFin);
}

void procesarInfracciones(int fechaIni, int fechaFin) {
    int dni, numCompania=1, dniMayorPago, dniMenorPago;
    double montoMayorPago=0, montoMenorPago=10000000, montoTotalXCompania, montoTotalRecaudado=0.0;
    char tipoVehiculo;
    cout.precision(2);
    cout<<fixed;
    while (true) {
        montoTotalXCompania=0.0;
        cin>>dni;
        if (cin.eof()) break;
        imprimeLinea('=');
        imprimeHeaderCompania(dni,numCompania);
        numCompania++;
        imprimeHeaderVehiculos();
        //Lectura de Vehiculos
        leeImprimeVehiculosCompania(fechaIni,fechaFin,montoTotalXCompania);
        //while (cin.get()!='\n');
        imprimeLinea('-');
        cout << "PAGO TOTAL: "<< montoTotalXCompania << endl;
        if (montoTotalXCompania>montoMayorPago) {
            montoMayorPago = montoTotalXCompania;
            dniMayorPago = dni;
        }
        if (montoTotalXCompania <montoMenorPago) {
            montoMenorPago = montoTotalXCompania;
            dniMenorPago = dni;
        }
        montoTotalRecaudado+=montoTotalXCompania;
    }
    imprimeLinea('=');
    cout << "TOTAL RECAUDADO" << montoTotalRecaudado<<endl;
    imprimeLinea('=');
    cout <<"DNI Mayor:"<<dniMayorPago<<endl;
    cout <<"Pago Mayor:"<<montoMayorPago<<endl;
    cout <<"DNI Menor:"<<dniMenorPago<<endl;
    cout <<"Pago Menor:"<<montoMenorPago<<endl;
}

void leeImprimeVehiculosCompania(int fechaIni,int fechaFin,double &montoTotalXCompania) {
    double incrementoTipo, incrementoFecha,incrementoHora;
    char tipoVehiculo, c, gravedad;
    int placa1, placa2, fechaMulta, horaMulta;
    while (true) {
        double montoMulta = 0.0;
        cin>>ws;
        tipoVehiculo = cin.get();
        cin>>placa1>>c>>placa2;
        imprimeTipo_Placa_DevuelveIncremento(tipoVehiculo,placa1,placa2,incrementoTipo);
        fechaMulta = leerFecha();
        imprimeFecha(fechaMulta);
        cout <<setw(5)<<' ';
        horaMulta = leerHora();
        calculaIncrementosXFechaYHora(fechaIni,fechaFin,fechaMulta,horaMulta,incrementoFecha,incrementoHora);
        imprimeHora(horaMulta);
        cout <<setw(2)<<' ';
        cin>>ws>>gravedad;
        imprimeGravedadDevuelveMulta(gravedad,montoMulta);
        imprimeIncrementosAumentaMulta(montoMulta,incrementoTipo,incrementoFecha,incrementoHora);
        montoTotalXCompania += montoMulta;
        if (cin.get()=='\n') break;
    }

}

void imprimeTipo_Placa_DevuelveIncremento(char tipoVehiculo,int placa1,int placa2,double &incrementoTipo) {
    cout <<left<< "-";
    if (tipoVehiculo=='P') {
        cout <<setw(10)<<"PEQUENO ";
        incrementoTipo = 2.7;
    }
    else if (tipoVehiculo=='M') {
        cout <<setw(10)<<"MEDIANO ";
        incrementoTipo = 11.7;
    }
    else if (tipoVehiculo=='C') {
        cout <<setw(10)<< "GRANDE ";
        incrementoTipo = 15.3;
    }

    cout <<tipoVehiculo<<placa1<<placa2<<setw(4)<<' '<<right;
}

void imprimeGravedadDevuelveMulta(char gravedad,double &montoMulta) {
    if (gravedad=='L') {
        cout <<setw(10)<<"LEVE ";
        montoMulta = 158.33;
    }
    else if (gravedad=='G') {
        cout <<setw(10)<<"GRAVE ";
        montoMulta = 516.75;
    }
    else if (gravedad=='M') {
        cout <<setw(10)<<"MUY GRAVE ";
        montoMulta = 3920.25;
    }

    cout << setw(10) << montoMulta ;
}



void calculaIncrementosXFechaYHora(int fechaIni,int fechaFin,int fechaMulta,int horaMulta,
    double &incrementoFecha,double &incrementoHora) {
    if (fechaMulta<fechaIni)
        incrementoFecha = 10.75;
    else if (fechaMulta <=fechaFin)
        incrementoFecha = 7.25;
    else
        incrementoFecha = 0.00;

    if (horaMulta<=(4*3600+30*60))
        incrementoHora = 3.7;
    else if (horaMulta<=(11*3600+25*60))
        incrementoHora = 8.5;
    else if (horaMulta <= (20*3600+40*60))
        incrementoHora = 5.8;
    else
        incrementoHora = 3.7;

}

void imprimeIncrementosAumentaMulta(double &montoMulta,double incrementoTipo,double incrementoFecha,double incrementoHora) {
    double montoIncTipo, montoIncFecha, montoIncHora;

    montoIncTipo = montoMulta*incrementoTipo/100;
    montoIncFecha = montoMulta*incrementoFecha/100;
    montoIncHora = montoMulta*incrementoHora/100;



    montoMulta = montoMulta + montoIncTipo + montoIncHora + montoIncFecha;

    cout << setw(14) << montoIncTipo << setw(13)<<montoIncFecha << setw(17)<<montoIncHora
        << setw(17)<<montoMulta <<endl;

}

void imprimeHeaderCompania(int dni, int numCompania) {
    char c;
    int tamNombre = 0;
    cout << "COMPANIA No. "<< numCompania <<endl;
    cout << "REPRESENTANTE LEGAL: ";
    //Como solo se lee e imprime los nombres caracter x caracter,
    //se hace todo en un solo modulo, en caso haya mas nombres la impresion puede modularse
    cin >> ws; //Quitamos todos los espacios previos al nombre
    while (true) {
        c = cin.get();
        if (c == ' ') break; //Paramos lectura cuando termine el nombre
        if (c == '/' or c == '-') c = ' ';
        if (c >= 'a' and c<='z') c -= 'a' - 'A';
        cout.put(c);
        tamNombre++;
    }
    int cantBlancos = NAME_SIZE - tamNombre;
    cout << setw(cantBlancos)<< ' ' << "DNI: "<<dni<<endl;
}

void imprimeHeaderVehiculos() {
    imprimeLinea('-');
    cout << "VEHICULOS INFRACCIONADOS:"<<endl;
    cout <<right<<setw(100)<<"INCREMENTOS"<<endl;
    cout << setw(6)<<"TIPO"<<setw(10)<<"PLACA"<<setw(12)<<"FECHA"<<setw(14)<<"HORA"
        <<setw(15)<<"GRAVEDAD"<<setw(10)<<"MULTA"<<setw(15)<<"POR TIPO"
        <<setw(15)<<"POR FECHA"<<setw(15)<<"POR HORA"<<setw(18)<<"TOTAL A PAGAR"<<endl;
}

int leerFecha() {
    int dd,mm,aa;
    char c;//Lee el guion

    cin>>dd>>c>>mm>>c>>aa;

    return aa*10000 + mm*100 +dd;
}

int leerHora() {
    int ss,mm,hh;
    char c;//Lee el guion

    cin>>hh>>c>>mm>>c>>ss;

    return hh*3600 + mm*60 + ss;
}

void imprimeFecha(int fecha) {
    int mm, dd,aa;
    aa= fecha/10000;
    mm = (fecha%10000)/100;
    dd = fecha%100;
    cout << setfill('0')<<setw(2)<< dd << '/' <<setw(2)<< mm << '/' << aa<<setfill(' ');
}

void imprimeHora(int hora) {
    int hh, mm,ss;
    hh= hora/3600;
    mm = (hora-hh*3600)/60;
    ss = hora-hh*3600-mm*60;
    cout << setfill('0')<<setw(2)<< hh << ':' <<setw(2)<< mm << ':' << ss<<setfill(' ');
}

void imprimeLinea(char c) {
    for (int i=0;i<MAX_LINE;i++)
        cout.put(c);
    cout <<endl;
}
