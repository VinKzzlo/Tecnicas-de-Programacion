
#include <iostream>
#include <iomanip>
using namespace std;
#include "FuncionesParaReporte.h"
#define TAMLINEA 111

void EmitirReporte(){
    int dd,mm,aa, nroDNI, horaI, horaF;
    double tarifaPorH, pagoMedicinas;
    char especialidad, fueRecetado, caracter;
    int nroPacientes=0, nroPacNoRec=0, nroPacRecet=0, nroPacDerm=0, nroPacPed=0,
        nroPacDermFech=0, ultimaEstadist;
    double totalIngresos=0.0, gastosPacRec, gastosPacDerm;
    
    imprimirEncabezado();
    while(true){
        cin>>dd;
        if(cin.eof()) break;
        nroPacientes++;
        cin>>caracter>>mm>>caracter>>aa;
        cin>>nroDNI;
        horaI = convertirHora();
        horaF = convertirHora();
        cin>>tarifaPorH;
        cin>>especialidad>>fueRecetado;
        if(fueRecetado=='S'){
            cin>>pagoMedicinas;
        }
        else
            pagoMedicinas=0.0;
        imprimeYProcesaDatos(dd,mm,aa,nroDNI,horaI,horaF,tarifaPorH,especialidad,
                fueRecetado,pagoMedicinas,totalIngresos,
                nroPacNoRec,nroPacRecet,nroPacDerm,nroPacPed,nroPacDermFech,
                 gastosPacRec,gastosPacDerm,ultimaEstadist);
           
    }
    imprimirLinea('=');
    cout<<"Total de ingresos : "<<totalIngresos;
}

void imprimeYProcesaDatos(int dd,int mm,int aa,int nroDNI,int horaI,int horaF,
     double tarifaPorH,char especialidad,char fueRecetado,double pagoMedicinas,
     double &totalIngresos,int &nroPacNoRec,int &nroPacRecet,
     int &nroPacDerm,int &nroPacPed,int &nroPacDermFech,double &gastosPacRec,
     double &gastosPacDerm,int &ultimaEstadist){
    int duracionEnS;
    double duracionEnH;
    bool cardiologia=false, pediatria=false, dermatologia=false; 
    cout<<right<<setfill('0')<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<aa<<setfill(' ');
    cout<<setw(2)<<' '<<setw(8)<<nroDNI<<setw(2)<<' ';
    imprimirHora(horaI);
    cout<<setw(2)<<' ';
    imprimirHora(horaF);
    duracionEnS = horaF - horaI;
    duracionEnH = (double)duracionEnS/3600;
    cout<<setw(4)<<' ';
    imprimirHora(duracionEnS);
    cout<<setw(8)<<' ';
    cout.precision(4);
    cout<<fixed;
    cout<<right<<setw(7)<<duracionEnH<<left;
    cout<<setw(6)<<' ';
    imprimirCategoria(14,especialidad,cardiologia,pediatria,dermatologia);
    imprimirMonto(tarifaPorH,duracionEnH,pagoMedicinas, totalIngresos);
    cout<<endl;
}

void imprimirHora(int tiempoEnS){
    int hor, min, seg;
    hor = tiempoEnS/3600;
    min = (tiempoEnS - hor*3600)/60;
    seg = (tiempoEnS - hor*3600 - min*60);
    cout<<setfill('0')<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg;
    cout<<setfill(' ');
}

void imprimirCategoria(int espaciado,char especialidad,
        bool &card, bool &ped,bool &derm){
    if(especialidad=='C'){
        cout<<setw(espaciado)<<"Cardiologia";
        card=true;
    }
    else if(especialidad=='D'){
        cout<<setw(espaciado)<<"Dermatologia";
        derm=true;
    }
    else if(especialidad=='P'){
        cout<<setw(espaciado)<<"Pediatria";
        ped=true;
    }
}

void imprimirMonto(double tarifaPorH,double duracionEnH,
        double pagoMedicinas, double &totalIngresos){
    double pagoTotal;
    pagoTotal = tarifaPorH*duracionEnH + pagoMedicinas;
    cout.precision(2);
    cout<<right<<setw(8)<<' '<<setw(10)<<pagoTotal;
    totalIngresos = totalIngresos + pagoTotal;
}

int convertirHora(){
    int hor, min, seg, valorHoraEnS;
    char car;
    cin>>hor>>car>>min>>car>>seg;
    valorHoraEnS = hor*3600 + min*60 + seg;
    return valorHoraEnS;
}

void imprimirEncabezado(){
    cout<<setw((22+TAMLINEA)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    imprimirLinea('=');
    cout<<setw((42+TAMLINEA)/3)<<"REGISTRO DE CITAS DE LAS CONSULTAS MEDICAS"
            <<endl;
    imprimirLinea('=');
    cout<<left<<setw(12)<<"Fecha"<<setw(11)<<"Paciente"<<setw(11)<<"Inicio"
        <<setw(8)<<"Fin"<<setw(17)<<"Duracion(H:M:S)"<<setw(13)<<"Duracion(H)"
        <<setw(16)<<"Especialidad"<<setw(23)<<"Pago (cita+medicinas)"<<endl;
    imprimirLinea('-');
}

void imprimirLinea(char caracter){
    for(int i=0; i<TAMLINEA; i++){
        cout<<caracter;
    }
    cout<<endl;
}