
/* 
 * File:   FuncionesParaReporte.cpp
 * Author: Alessandro Santé Vega - 20223006
 *
 * Created on 8 de abril de 2024, 07:23 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;
#include "funcionesParaReporte.h"
#define LONLINEA 10

void generarEImprimirReporte(){
    int fechaCita, nroDNI, horaInicio, horaFin, nroPacientes=0,
        cantEstadist1=0, cantEstadist2=0, cantEstadist3=0, cantEstadist4=0,
        cantEstadist5=0, cantEstadist6=0;
    double montoCita, montoMedicinas, montoCitaYMed, totalIngresos, duracion;
    char especialidad, fueRecetado;
    
    imprimirEncabezado();
    //Se leen los datos del archivo
    while(true){
        fechaCita = leerFechaUHora('F');
        montoMedicinas=0;
        if(cin.eof()) break;
        nroPacientes++;
        cin>>nroDNI;
        horaInicio = leerFechaUHora('H');
        horaFin = leerFechaUHora('H');
        cin>>montoCita>>especialidad>>fueRecetado;
        if(fueRecetado=='S')
            cin>>montoMedicinas;
//      Se llama a una función que imprimirá y procesará estos datos, para
//      posteriormente usar estos al momento de imprimir el resumen
        imprimeYProcesaDatos(fechaCita, nroDNI, horaInicio, horaFin,montoCita,
                especialidad, fueRecetado, montoMedicinas, nroPacientes,
                montoCitaYMed,duracion, totalIngresos, cantEstadist1, cantEstadist2,
                cantEstadist3, cantEstadist4, cantEstadist5, cantEstadist6);
        
    }
}

void imprimeYProcesaDatos(int fechaCita,int nroDNI,int horaInicio,int horaFin,
    double montoCita,char especialidad,char fueRecetado,double montoMedicinas,
    int nroPacientes,double &montoCitaYMed,double &duracion,double &totalIngresos,
    int &cantEstadist1,int &cantEstadist2,int &cantEstadist3,int &cantEstadist4,
    int &cantEstadist5,int &cantEstadist6){
    imprimirFecha(fechaCita);
    cout<<"   "<<setw(8)<<nroDNI;
    imprimirHora(horaInicio);
    imprimirHora(horaFin);
    duracion = (horaInicio - horaFin)/3600;
    imprimirHora(duracion);
    cout.precision(4);
    cout<<fixed;
    cout<<"  "<<duracion;
    imprimirEspecialidad(especialidad);
    montoCitaYMed = montoCita + montoMedicinas;
    cout.precision(2);
    cout<<montoCitaYMed;
    
}

int leerFechaUHora(char seleccion){
    int dd_hor, mm_min, aa_seg;
    char simbolo;
    cin>>dd_hor>>simbolo>>mm_min>>simbolo>>aa_seg;
    if (seleccion == 'F')
        return (aa_seg*10000 + mm_min*100 + dd_hor);
    else
        return (dd_hor*3600 + mm_min*60 + aa_seg);
}

void imprimirEncabezado(){
    cout<<setw((22+LONLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimeLinea('=');
    cout<<setw(1)<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"<<endl;
    imprimeLinea('=');
    cout<<setw(12)<<"Fecha"<<"Paciente"<<"Inicio"<<"Fin"<<"Duracion(H:M:S)"
            <<"Especialidad"<<"Pago(cita+medicinas)"<<endl;
    imprimeLinea('-');
}

void imprimeLinea(char caracter){
    for(int i=0; i<LONLINEA; i++){
        cout<<caracter;
    }
    cout<<endl;
}

void imprimirFecha(int fecha){
    int aa = fecha/10000, mm = (fecha-aa*10000)/100,
        dd = (fecha-aa*10000-mm*100);
    cout<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'
        <<setw(4)<<aa<<setfill(' ');
}
void imprimirHora(int horaS){
    int hor = horaS/3600, min = (horaS-hor*3600)/60, seg=horaS-hor*3600-min*60;
    cout<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg<<(' ');
}

void imprimirEspecialidad(char especialidad){
    if (especialidad=='C')
        cout<<"Cardiologia"<<' ';
    else if(especialidad=='D')
        cout<<"Dermatologia"<<' ';
    else if(especialidad=='P')
        cout<<"Pediatria"<<' ';
}