/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
#include "FuncionesAuxiliares.h"

void EmitirReporte(){
    
    int dia, mes, anio, dniPaciente;
    int hh_Ini, min_Ini, seg_Ini, hh_Fin, min_Fin, seg_Fin;
    int duracion, hh, min, seg, contNoReceta=0;
    double tarifaHora, precioMedi, duracionHoras, montoFinal;
    char car, especialidad, carReceta;
    bool recibioReceta;
    while(true){
        
        cin>>dia;
        if (cin.eof()) break;
        car = cin.get();
        cin>>mes>>car>>anio;
        cin>>dniPaciente>>hh_Ini>>car>>min_Ini>>car>>seg_Ini;
        cin>>hh_Fin>>car>>min_Fin>>car>>seg_Fin;
        cin>>tarifaHora>>especialidad>>carReceta;
        
        if (carReceta=='S'){
            recibioReceta = true;
            cin>>precioMedi;
        }else{
            recibioReceta = false;
        }
        
        //Imprimir Fecha
        cout.fill('0');
        cout<<setw(2)<<dia<<"/"<<setw(2)<<mes<<"/"<<anio;
        cout.fill(' ');
        //Imprimir DNI paciente
        cout<<setw(10)<<dniPaciente;
        //Imprimir Hora Inicio y Fin
        cout<<setw(2)<<" ";
        cout.fill('0');
        cout<<setw(2)<<hh_Ini<<":"<<setw(2)<<min_Ini<<":"<<setw(2)<<seg_Ini;
        cout.fill(' ');
        cout<<setw(2)<<" ";
        cout.fill('0');
        cout<<setw(2)<<hh_Fin<<":"<<setw(2)<<min_Fin<<":"<<setw(2)<<seg_Fin;
        cout.fill(' ');
        //calculamos la Duracion 
        duracion = CalcularDuracion(hh_Ini, min_Ini, seg_Ini,
                                    hh_Fin, min_Fin, seg_Fin);
        //transformamos a Hora Min y Seg
        TransformarDuracion(duracion, hh, min, seg);
        //ImprimirDuracion en Hora, Min Y Seg
        cout<<setw(4)<<" ";
        cout.fill('0');
        cout<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg;
        cout.fill(' ');
        //calculamos la duracion en horas
        duracionHoras = CalcularDuracionHoras(duracion);
        //imprimir duracion en Horas
        cout.precision(4);
        cout<<fixed;
        cout<<setw(15)<<duracionHoras;
        // verificamos la especialidad según el caracter ingresado
        if (especialidad=='C')
            cout<<setw(19)<<right<<"Cardiología";
        if (especialidad=='D')
            cout<<setw(19)<<right<<"Dermatología";
        if (especialidad=='P')
            cout<<setw(19)<<right<<"Pediatría";
        
        //calculamos el monto final por cada paciente
        montoFinal = CalcularMontoTotal(carReceta, duracionHoras,
                                        tarifaHora, precioMedi);
        cout.precision(2);
        cout<<fixed;
        cout<<setw(15)<<montoFinal<<endl;
    }
}
int CalcularDuracion(int hh_Ini, int min_Ini, int seg_Ini,
                     int hh_Fin, int min_Fin, int seg_Fin){
    
    int canInicio, cantFin;
    canInicio = hh_Ini*3600 + min_Ini*60 + seg_Ini;
    cantFin = hh_Fin*3600 + min_Fin*60 + seg_Fin;
    
    return cantFin-canInicio;
}
void TransformarDuracion(int duracion, int &hh, int &min, int &seg){
    
    hh = duracion/3600;
    min = (duracion%3600)/60;
    seg = (duracion%3600)%60;
}
double CalcularDuracionHoras(int duracion){
    
    double horas;
    horas = (double) duracion/3600;
    return horas;
}
double CalcularMontoTotal(char carReceta, double duracionHoras,
                          double tarifaHora, double precioMedi){
    double MontoTotal;
    if (carReceta=='N'){
        MontoTotal = duracionHoras*tarifaHora;
    }else{
        MontoTotal = tarifaHora*duracionHoras + precioMedi;
    }
    return MontoTotal;
}