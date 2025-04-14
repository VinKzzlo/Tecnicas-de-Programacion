/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#define NO_ENCONTRADO -1
#define TAMLINE 125

void LeerMedicosColocarArr(const char *nombArchMedico,int *ArrCodMedico,
                           double *ArrTarifMedico,int &cantMedico){
    ifstream archMedico(nombArchMedico,ios::in);
    if (not archMedico.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchMedico<<endl;
        exit(1);
    }
    int codMedico;
    double tarifMedico;
    while(true){
        archMedico>>codMedico;
        if (archMedico.eof()) break;
        archMedico>>ws;
        archMedico.get(); //saca el primer caracter
        while(archMedico.get()!='/'); //elimina el nombre del doctor
        archMedico>>ws;
        while(archMedico.get()!=' '); //elimina especialidad del doctor
        archMedico>>tarifMedico;
        ArrCodMedico[cantMedico] = codMedico;
        ArrTarifMedico[cantMedico] = tarifMedico;
        cantMedico++;
    }
}
void LeerMedicinasColocarArr(const char *nombArchMedicina,int *ArrCodMedicina,
                             double *ArrPrecMedicina,int &cantMedicina){
    
    ifstream archMedicina(nombArchMedicina,ios::in);
    if (not archMedicina.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchMedicina<<endl;
        exit(1);
    }
    int codMedicina;
    double precioMedicina;
    while(true){
        archMedicina>>codMedicina;
        if (archMedicina.eof()) break;
        archMedicina>>ws;
        while(archMedicina.get()!=' '); //elimina el nombre de la medicina
        archMedicina>>precioMedicina;
        ArrCodMedicina[cantMedicina] = codMedicina;
        ArrPrecMedicina[cantMedicina] = precioMedicina;
        cantMedicina++;
    }
}
void LeerCitasMedicas(const char *nombArchCitMedic,int *ArrCodMedico,
                      double *ArrTarifMedico,double *ArrIngresoCitas,
                      double *ArrIngresoMedica,int *ArrCantPacConMedic,
                      int *ArrCantPacSinMedic,int cantMedico,
                      int *ArrCodMedicina,double *ArrPrecMedicina,
                      int *ArrCantUnidVendid,double *ArrIngSinDescMedic,
                      double *ArrDescSeguMedic,int cantMedicina){
    ifstream archCitMedica(nombArchCitMedic,ios::in);
    if (not archCitMedica.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchCitMedic<<endl;
        exit(1);
    }
    int dd,mm,aa,dniPacien,horaIni,horaFin,codMedico;
    double descuento;
    char c;
    while(true){
        archCitMedica>>dd;
        if (archCitMedica.eof()) break;
        archCitMedica>>c>>mm>>c>>aa>>dniPacien>>descuento;
        horaIni = LeerHora(archCitMedica);
        horaFin = LeerHora(archCitMedica);
        archCitMedica>>codMedico;
        
        int indiceMedico = BuscarIndice(codMedico,ArrCodMedico,cantMedico);
        
        if (indiceMedico!=NO_ENCONTRADO){
            double duracion = (horaFin-horaIni)/3600.0;
            double tarifa = ArrTarifMedico[indiceMedico];
            ArrIngresoCitas[indiceMedico] += (tarifa*duracion)*(1-descuento/100);
            
            // Determinar si receta medicina o no
            c = archCitMedica.get();
            if (c==' '){
                ArrCantPacConMedic[indiceMedico]++;
                int codMedicina,cantMedic;
                double montoIngresoMedicina=0;
                while(true){
                    archCitMedica>>codMedicina>>cantMedic;
                    
                    int indiceMedicina = BuscarIndice(codMedicina,ArrCodMedicina,
                                                      cantMedicina);
                    if (indiceMedicina!=NO_ENCONTRADO){
                        double precio = ArrPrecMedicina[indiceMedicina];
                        
                        ArrCantUnidVendid[indiceMedicina] += cantMedic;
                        ArrIngSinDescMedic[indiceMedicina] += precio*cantMedic;
                        ArrDescSeguMedic[indiceMedicina] += (precio*cantMedic)*(descuento/200);
                        montoIngresoMedicina += (precio*cantMedic)*(1-descuento/200);
                        
                    }else{
                        while(archCitMedica.get()!='\n'); //eliminar linea
                    }
                    if (archCitMedica.get()=='\n') break;
                }
                ArrIngresoMedica[indiceMedico]+=montoIngresoMedicina;
            }else{
                ArrCantPacSinMedic[indiceMedico]++;
            }
        }else{
            while(archCitMedica.get()!='\n'); //eliminar linea si medico no existe
        }
    }
}
void ImprimirReportMedicoArr(const char *nombArchRepoMedico,int *ArrCodMedico,
                             double *ArrTarifMedico,int cantMedico){
    ofstream archRepoMedico(nombArchRepoMedico,ios::out);
    if (not archRepoMedico.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchRepoMedico<<endl;
        exit(1);
    }
    archRepoMedico<<setw(16)<<"CODIGO MEDICO"<<setw(20)<<"TARIFA MEDICO"<<endl;
    for(int i=0; i<cantMedico; i++){
        archRepoMedico<<setw(10)<<ArrCodMedico[i];
        archRepoMedico.precision(2);
        archRepoMedico<<fixed;
        archRepoMedico<<setw(20)<<ArrTarifMedico[i]<<endl;
    }
}
void ImprimirReportMedicinaArr(const char *nombArchRepoMedicina,int *ArrCodMedicina,
                               double *ArrPrecMedicina,int cantMedicina){
    ofstream archRepoMedicina(nombArchRepoMedicina,ios::out);
    if (not archRepoMedicina.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchRepoMedicina<<endl;
        exit(1);
    }
    archRepoMedicina<<setw(16)<<"CODIGO MEDICINA"<<setw(20)<<"PRECIO MEDICINA"<<endl;
    for(int i=0; i<cantMedicina; i++){
        archRepoMedicina<<setw(10)<<ArrCodMedicina[i];
        archRepoMedicina.precision(2);
        archRepoMedicina<<fixed;
        archRepoMedicina<<setw(20)<<ArrPrecMedicina[i]<<endl;
    }
}
int LeerHora(ifstream &archCitMedica){
    int hora,min,seg,duracion;
    char c;
    archCitMedica>>hora>>c>>min>>c>>seg;
    duracion = hora*3600 + min*60 + seg;
    return duracion;
}
int BuscarIndice(int dato,int *Arreglo,int cantDatos){
    for (int i=0; i<cantDatos; i++){
        if (Arreglo[i]==dato){
            return i;
        }
    }
    return NO_ENCONTRADO;
}
void EmitirReporteIngresos(const char *nombArchReporIngres,int *ArrCodMedico,
                           double *ArrTarifMedico,double *ArrIngresoCitas,
                           double *ArrIngresoMedica,int *ArrCantPacConMedic,
                           int *ArrCantPacSinMedic,int cantMedico,
                           int *ArrCodMedicina,double *ArrPrecMedicina,
                           int *ArrCantUnidVendid,double *ArrIngSinDescMedic,
                           double *ArrDescSeguMedic,int cantMedicina){
    
    ofstream archReporIngresos(nombArchReporIngres,ios::out);
    if (not archReporIngresos.is_open()){
        cout<<"ERROR: no se pudo abrir el archivo "<<nombArchReporIngres<<endl;
        exit(1);
    }
    ImprimirReporteMedicos(ArrCodMedico,ArrTarifMedico,ArrIngresoCitas,
                           ArrIngresoMedica,ArrCantPacConMedic,ArrCantPacSinMedic,
                           cantMedico,archReporIngresos);
    
    ImprimirReporteMedicinas(ArrCodMedicina,ArrPrecMedicina,ArrCantUnidVendid,
                             ArrIngSinDescMedic,ArrDescSeguMedic,cantMedicina,
                             archReporIngresos);
    
}
void ImprimirEncabezadoMedico(ofstream &archReporIngresos){
    ImprimirLinea(TAMLINE,'=',archReporIngresos);
    archReporIngresos<<setw((TAMLINE+22)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    archReporIngresos<<setw((TAMLINE+31)/2)<<"REGISTRO DE INGRESOS POR MEDICO"<<endl;
    ImprimirLinea(TAMLINE,'=',archReporIngresos);
    archReporIngresos<<"No."<<setw(13)<<"Cod. Medico"<<setw(9)<<"Tarifa"
                     <<setw(16)<<"IngresPorCitas"<<setw(17)<<"IngresPorMedicam"
                     <<setw(14)<<"IngresoTotal"<<setw(18)<<"PacienConMedicina"
                     <<setw(18)<<"PacienSinMedicina"<<setw(17)<<"TotalPacientes"<<endl;
    ImprimirLinea(TAMLINE,'-',archReporIngresos);
}
void ImprimirLinea(int cant,char simb,ofstream &archReporIngresos){
    for(int i=0; i<cant; i++){
        archReporIngresos<<simb;
    }
    archReporIngresos<<endl;
}
void ImprimirReporteMedicos(int *ArrCodMedico,double *ArrTarifMedico,
                            double *ArrIngresoCitas,double *ArrIngresoMedica,
                            int *ArrCantPacConMedic,int *ArrCantPacSinMedic,
                            int cantMedico,ofstream &archReporIngresos){
    
    int pacienConMedic=0,pacienSinMedic=0;
    double ingrePorCitas=0,ingrePorMedic=0,total=0; 
    ImprimirEncabezadoMedico(archReporIngresos);
    archReporIngresos.precision(2);
    archReporIngresos<<fixed;
    for(int i=0; i<cantMedico; i++){
        int totalPacientes = ArrCantPacConMedic[i]+ArrCantPacSinMedic[i];
        double ingresoTotal = ArrIngresoCitas[i] + ArrIngresoMedica[i];
        archReporIngresos<<setfill('0')<<setw(3)<<i<<setfill(' ')<<setw(9)
                         <<ArrCodMedico[i]<<setw(13)<<ArrTarifMedico[i]<<setw(14)
                         <<ArrIngresoCitas[i]<<setw(15)<<ArrIngresoMedica[i]
                         <<setw(15)<<ingresoTotal<<setw(14)<<ArrCantPacConMedic[i]
                         <<setw(16)<<ArrCantPacSinMedic[i]<<setw(20)<<totalPacientes<<endl;
        ingrePorCitas += ArrIngresoCitas[i];
        ingrePorMedic += ArrIngresoMedica[i];
        total += ingresoTotal;
        pacienConMedic += ArrCantPacConMedic[i];
        pacienSinMedic += ArrCantPacSinMedic[i];
    }
    ImprimirLinea(TAMLINE,'-',archReporIngresos);
    archReporIngresos<<"Totales: "<<setw(30)<<ingrePorCitas<<setw(15)<<ingrePorMedic
                     <<setw(15)<<total<<setw(14)<<pacienConMedic<<setw(16)
                     <<pacienSinMedic<<setw(20)<<(pacienConMedic+pacienSinMedic)<<endl;
}
void ImprimirReporteMedicinas(int *ArrCodMedicina,double *ArrPrecMedicina,
                              int *ArrCantUnidVendid,double *ArrIngSinDescMedic,
                              double *ArrDescSeguMedic,int cantMedicina,
                              ofstream &archReporIngresos){
    
    int cantUnidVendid=0,pacienSinMedic=0;
    double ingrSinDscto=0,dsctoPorSegur=0,total=0; 
    ImprimirEncabezadoMedicina(archReporIngresos);
    archReporIngresos.precision(2);
    archReporIngresos<<fixed;
    for(int i=0; i<cantMedicina; i++){
        double totalIngreso = ArrIngSinDescMedic[i]-ArrDescSeguMedic[i];
        archReporIngresos<<setfill('0')<<setw(3)<<i<<setfill(' ')<<setw(9)
                         <<ArrCodMedicina[i]<<setw(13)<<ArrPrecMedicina[i]<<setw(14)
                         <<ArrCantUnidVendid[i]<<setw(19)<<ArrIngSinDescMedic[i]
                         <<setw(16)<<ArrDescSeguMedic[i]<<setw(18)<<totalIngreso<<endl;
        cantUnidVendid += ArrCantUnidVendid[i];
        ingrSinDscto += ArrIngSinDescMedic[i];
        dsctoPorSegur += ArrDescSeguMedic[i];
        total += totalIngreso;
    }
    ImprimirLinea(TAMLINE,'-',archReporIngresos);
    archReporIngresos<<"Totales: "<<setw(30)<<cantUnidVendid<<setw(19)<<ingrSinDscto
                     <<setw(16)<<dsctoPorSegur<<setw(18)<<total<<endl;
}
void ImprimirEncabezadoMedicina(ofstream &archReporIngresos){
    ImprimirLinea(TAMLINE,'=',archReporIngresos);
    archReporIngresos<<setw((TAMLINE+22)/2)<<"EMPRESA DE SALUD S. A."<<endl;
    archReporIngresos<<setw((TAMLINE+33)/2)<<"REGISTRO DE INGRESOS POR MEDICINA"<<endl;
    ImprimirLinea(TAMLINE,'=',archReporIngresos);
    archReporIngresos<<"No."<<setw(13)<<"Cod.Medicin"<<setw(9)<<"Precio"
                     <<setw(16)<<"CantUnidVendid"<<setw(21)<<"IngresoSinDescuento"
                     <<setw(16)<<"DescuentoPorSeg"<<setw(15)<<"TotalIngreso"<<endl;
    ImprimirLinea(TAMLINE,'-',archReporIngresos);
}