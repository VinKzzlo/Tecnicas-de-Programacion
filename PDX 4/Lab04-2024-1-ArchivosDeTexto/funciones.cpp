
/*/ 
 * Projecto:  Lab04-2024-1-ArchivosDeTexto
 * Nombre del Archivo:  funciones.cpp
 * Autor: Super Spaghetti X
/*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"
#define TAMLINEA 136
#define MAXTEXTO 40
#define MAXDURACION 2*3600+31*60+25

                  /*  - / > [ Funciones en main() ] < / -  */

// Modulo de Emision de Reporte
void emitirReporte(const char *nombArchReporte,const char *nombArchMedicos,
                   const char *nombArchMedicinas,const char *nombArchCitas){
    // Apertura de Archivos && Declaracion de Variables
    ifstream archMedicos = abrirArchivo_IFS(nombArchMedicos);
    ifstream archMedicinas = abrirArchivo_IFS(nombArchMedicinas);
    ifstream archCitas = abrirArchivo_IFS(nombArchCitas);
    ofstream archReporte = abrirArchivo_OFS(nombArchReporte);
    int medID,max_MedID;
    double medTarifa,max_MedMonto = 0;
    // Inicializacion de Elementos
    archReporte<<fixed;
    archReporte.precision(2);
    // Proceso de Emision de Reporte
    imprimirEncabezado(archReporte,'A');
    while(1){
        archMedicos>>medID;
        if(archMedicos.eof()) break;                                            // Validacion de Fin de Archivo
        archReporte<<setw(22)<<"Codigo del medico:"<<setw(7)<<medID<<endl;
        archReporte<<setw(22)<<"Nombre del medico:"<<setw(2)<<' ';
        procesarNombreDeMedico(archReporte,archMedicos);
        archReporte<<endl<<setw(17)<<"Especialidad:"<<setw(7)<<' ';
        procesarEspecialidadDeMedico(archReporte,archMedicos);
        archMedicos>>medTarifa;
        archReporte<<endl<<setw(11)<<"Tarifa:"<<setw(19)<<medTarifa<<endl;
        // Procesamiento de Citas Realizadas por Medico
        procesarCitasRealizadas(archReporte,archMedicinas,archCitas,medID,
                                medTarifa,max_MedID,max_MedMonto);
        imprimirLinea(archReporte,TAMLINEA,'=');
    }
    // Procesamiento de Resumen General
    procesarResumenGeneral(archReporte,archMedicos,max_MedID,max_MedMonto);
}

              /*  - / > [ Funciones de Orden Principal ] < / -  */

// Modulo de Procesamiento de Citas Realizadas por Medico
void procesarCitasRealizadas(ofstream &archReporte,ifstream &archMedicinas,
                             ifstream &archCitas,int medID,double medTarifa,
                             int &max_MedID,double &max_MedMonto){
    // Declaracion de Variables
    int dd,mm,aa,cit_fecha,cit_pacID,cit_horIni,cit_horFin,cit_medID;
    int numCitas = 0;
    double cit_Desc,monto_Cita,monto_Medicinas = 0,cit_Duracion;
    char simbolo;
    // Reinicio de Lectura de Archivo
    archCitas.clear();
    archCitas.seekg(0,ios::beg);
    // Proceso de Busqueda de Citas Realizadas por Medico
    imprimirEncabezado(archReporte,'B');
    while(1){
        archCitas>>dd;
        if(archCitas.eof()) break;                                              // Validacion de Fin de Archivo
        archCitas>>simbolo>>mm>>simbolo>>aa>>cit_pacID>>cit_Desc;
        cit_horIni = obtenerHora(archCitas);
        cit_horFin = obtenerHora(archCitas);
        archCitas>>cit_medID;
        cit_Duracion = cit_horFin - cit_horIni;
        // Validacion de Hallazgo de Cita Valida Realizada por Medico
        if(cit_medID == medID and cit_Duracion < MAXDURACION){
            numCitas++;
            cit_fecha = 10000*aa+100*mm+dd;
            imprimirDatosDeCita(archReporte,cit_fecha,cit_pacID,cit_horIni,
                                cit_horFin,cit_Duracion,cit_Desc,medTarifa,
                                monto_Cita);
            procesarMedicinasRecetadas(archReporte,archCitas,archMedicinas,
                                       cit_Desc,monto_Medicinas);
            procesarResumenParcial(archReporte,medID,monto_Cita,monto_Medicinas,
                                   max_MedID,max_MedMonto);
        } else while(archCitas.get() != '\n');                                  // Descarte de Datos
    }
    // Validacion por Inexistencia de Citas
    if(numCitas == 0){
        imprimirLinea(archReporte,TAMLINEA,'-');
        archReporte<<endl<<setw((TAMLINEA - 15)/2)<<"> [ NO SE REALIZARON ";
        archReporte<<"CITAS VALIDAS DURANTE EL PERIODO ] <"<<endl<<endl;
    }
}
// Modulo de Procesamiento de Resumen General de Reporte
void procesarResumenGeneral(ofstream &archReporte,ifstream &archMedicos,
                            int max_MedID,double max_MedMonto){
    // Declaracion de Variables
    int medID_Eval;
    double medTarifa;
    // Reinicio de Lectura de Archivo
    archMedicos.clear();
    archMedicos.seekg(0,ios::beg);
    // Iterativa del Proceso de Busqueda de Datos de Mejor Medico
    while(1){
        archMedicos>>medID_Eval;
        if(archMedicos.eof()) break;                                            // Validacion de Fin de Archivo
        // Validacion por Filtro de Mejor Medico
        if(medID_Eval == max_MedID){
            archReporte<<setw(37)<<"MEDICO QUE APORTO MAS INGRESOS AL";
            archReporte<<" INSTITUTO:"<<endl;
            archReporte<<setw(22)<<"Codigo del medico:"<<setw(7)<<max_MedID;
            archReporte<<endl<<setw(22)<<"Nombre del medico:"<<setw(2)<<' ';
            procesarNombreDeMedico(archReporte,archMedicos);
            archReporte<<endl<<setw(17)<<"Especialidad:"<<setw(7)<<' ';
            procesarEspecialidadDeMedico(archReporte,archMedicos);
            archMedicos>>medTarifa;
            archReporte<<endl<<setw(11)<<"Tarifa:"<<setw(19)<<medTarifa<<endl;
            archReporte<<setw(34)<<"Total ingresado por el medico:";
            archReporte<<setw(10)<<max_MedMonto<<endl;
            imprimirLinea(archReporte,TAMLINEA,'=');
            break;
        } else while(archMedicos.get() != '\n');                                // Descarte de Datos
    }
}

             /*  - / > [ Funciones de Orden Secundario ] < / -  */

// Modulo de Impresion de Datos de Cita
void imprimirDatosDeCita(ofstream &archReporte,int fecha,int pacID,int horIni,
                         int horFin,double duracion,double descuento,
                         double tarifa,double &monto){
    // Declaracion de Variables && Inicializacion de Elementos
    monto = (1 - descuento/100)*(((double)duracion)/3600)*tarifa;               // Se aplica el descuento para el pago de la cita
    // Proceso de Impresion de Datos de Cita
    imprimirEncabezado(archReporte,'C');
    archReporte<<setw(8)<<' ';
    imprimirFecha(archReporte,fecha);
    archReporte<<setw(12)<<pacID<<setw(8)<<' ';
    imprimirHora(archReporte,horIni);
    archReporte<<setw(8)<<' ';
    imprimirHora(archReporte,horFin);
    archReporte<<setw(8)<<' ';
    imprimirHora(archReporte,duracion);
    archReporte<<setw(20)<<descuento<<'%'<<setw(25)<<monto<<endl;
}
// Modulo de Procesamiento de Medicinas Recetadas Durante Cita
void procesarMedicinasRecetadas(ofstream &archReporte,ifstream &archCitas,
                                ifstream &archMedicinas,double cit_Desc,
                                double &monto_Medicinas){
    // Declaracion de Variables
    int numMedicinas = 0,medicinaID,medicinaID_Eval,cantRecetada;
    double medicinaPrecio,pago_Medicina;
    // Proceso de Lectura & Procesamiento de Datos de Medicinas de Recetadas en Cita
    imprimirEncabezado(archReporte,'D');
    while(1){
        if(archCitas.get() == '\n') break;                                      // Validacion de Fin de Proceso
        archCitas>>medicinaID>>cantRecetada;
        // Reinicio de Lectura de Archivo
        archMedicinas.clear();
        archMedicinas.seekg(0,ios::beg);
        // Iterativa del Proceso de Busqueda de Datos de Medicina Recetada
        while(1){
            archMedicinas>>medicinaID_Eval;
            if(archMedicinas.eof()) break;                                      // Validacion de Fin de Archivo de Busqueda
            // Validacion de Hallazgo de Medicina Buscada
            if(medicinaID_Eval == medicinaID){
                numMedicinas++;
                archReporte<<setw(12)<<' '<<setfill('0')<<setw(2)<<numMedicinas;
                archReporte<<setfill(' ')<<setw(9)<<medicinaID<<setw(4)<<' ';
                procesarDescripcionDeMedicina(archReporte,archMedicinas);
                archMedicinas>>medicinaPrecio;
                archReporte<<setw(6)<<cantRecetada<<setw(12)<<medicinaPrecio;
                pago_Medicina = (1-cit_Desc/200)*cantRecetada*medicinaPrecio;   // Se aplica la mitad del descuento para el pago de las medicinas
                archReporte<<setw(12)<<pago_Medicina<<endl;
                monto_Medicinas += pago_Medicina;
                break;
            } else while(archMedicinas.get() != '\n');                          // Descarte de Datos
        }
    }
    // Validacion por Inexistencia de Medicinas
    if(numMedicinas == 0){
        archReporte<<endl<<setw((TAMLINEA - 7)/2)<<"> [ NO SE RECETARON ";
        archReporte<<"MEDICINAS DURANTE LA CITA ] <"<<endl<<endl;
    }
}
// Modulo de Procesamiento de Datos por Emision de Resumen Parcial
void procesarResumenParcial(ofstream &archReporte,int medID,double monto_Cit,
                            double montoMedicinas,int &max_MedID,
                            double &max_MedMonto){
    // Declaracion de Variables
    double pagoTotal = monto_Cit + montoMedicinas;
    // Proceso de Impresion de Resumen Parcial
    archReporte<<setw(29)<<"Pago total por medicinas:";
    archReporte<<setw(10)<<montoMedicinas<<endl;
    archReporte<<setw(15)<<"Pago total:"<<setw(24)<<pagoTotal<<endl;
    // Validacion de Nuevo Mejor Aportador
    if(pagoTotal > max_MedMonto){
        max_MedID = medID;
        max_MedMonto = pagoTotal;
    }
}

                  /*  - / > [ Funciones Auxiliares ] < / -  */

// Modulo AUXILIAR de Apertura de Archivos IFSTREAM
ifstream abrirArchivo_IFS(const char *nombArch){
    ifstream arch(nombArch,ios::in);
    if(arch.is_open()) return arch;
    cout<<"ERROR DE APERTURA: Archivo "<<nombArch<<endl;
    exit(1);
}
// Modulo AUXILIAR de Apertura de Archivos OFSTREAM
ofstream abrirArchivo_OFS(const char *nombArch){
    ofstream arch(nombArch,ios::out);
    if(arch.is_open()) return arch;
    cout<<"ERROR DE APERTURA: Archivo "<<nombArch<<endl;
    exit(1);
}
// Modulo AUXILIAR de Impresion de Encabezados PREDETERMINADOS de Reporte
void imprimirEncabezado(ofstream &archSalida,char seleccion){
    if(seleccion == 'A'){
        archSalida<<setw((TAMLINEA + 23)/2)<<"EMPRESA DE SALUDA S. A."<<endl;
        imprimirLinea(archSalida,TAMLINEA,'=');
        archSalida<<setw((TAMLINEA + 25)/2)<<"REGISTRO DE CITAS MEDICAS"<<endl;
        imprimirLinea(archSalida,TAMLINEA,'=');
    } else if(seleccion == 'B'){
        archSalida<<setw(24)<<"PACIENTES ATENDIDOS:"<<endl;
    } else if(seleccion == 'C'){
        imprimirLinea(archSalida,TAMLINEA,'-');
        archSalida<<setw(13)<<"Fecha"<<setw(17)<<"Paciente";
        archSalida<<setw(15)<<"Inicio"<<setw(14)<<"Fin"<<setw(19)<<"Duracion";
        archSalida<<setw(29)<<"% de descuento por Seguro";
        archSalida<<setw(21)<<"Pago por cita"<<endl;
        imprimirLinea(archSalida,TAMLINEA,'-');
    } else{
        archSalida<<setw(28)<<"Medicinas recetadas:"<<endl;
        archSalida<<setw(14)<<"No"<<setw(9)<<"Codigo"<<setw(4)<<' '<<left;
        archSalida<<setw(MAXTEXTO)<<"Descripcion"<<right;
        archSalida<<setw(9)<<"Cantidad"<<setw(9)<<"Precio"<<setw(11)<<"Pago";
        archSalida<<endl;
    }
}
// Modulo AUXILIAR de Impresion de Simbolos en Linea
void imprimirLinea(ofstream &archSalida,int medida,char simbolo){
    for(int i = 0;i < medida;i++) archSalida.put(simbolo);
    archSalida<<endl;
}
// Modulo AUXILIAR de Lectura & Impresion de Nombre de Medico en Formato Predeterminado por Reporte
void procesarNombreDeMedico(ofstream &archSalida,ifstream &archEntrada){
    char letra;
    archEntrada>>ws;
    archEntrada.get();
    while(1){
        letra = archEntrada.get();
        if(letra == '/') break;
        if(letra == '_') letra = ' ';
        archSalida.put(letra);
    }
}
// Modulo AUXILIAR de Lectura & Impresion de Especialidad de Medico en Formato Predeterminado por Reporte
void procesarEspecialidadDeMedico(ofstream &archSalida,ifstream &archEntrada){
    char letra;
    archEntrada>>ws;
    while(1){
        letra = archEntrada.get();
        if(letra == ' ') break;
        archSalida.put(letra);
    }
}
// Modulo AUXILIAR de Lectura & Impresion de Descripcion de Medicina en Formato Predeterminado por Reporte
void procesarDescripcionDeMedicina(ofstream &archSalida,ifstream &archEntrada){
    int numCar = 0;
    char letra;
    archEntrada>>ws;
    while(1){
        letra = archEntrada.get();
        if(letra == ' ') break;
        if(letra == '_') letra = ' ';
        archSalida.put(letra);
        numCar++;
    }
    archSalida<<setw(MAXTEXTO - numCar)<<' ';
}
// Modulo AUXILIAR de Lectura y Retorno de Valor Temporal [Hora]
int obtenerHora(ifstream &archEntrada){
    int hor,min,seg;
    char simbolo;
    archEntrada>>hor>>simbolo>>min>>simbolo>>seg;
    return hor*3600+min*60+seg;
}
// Modulo AUXILIAR de Impresion de Valor Temporal como 'Fecha'
void imprimirFecha(ofstream &archSalida,int fecha){
    int aa = fecha/10000;
    int mm = (fecha - aa*10000)/100;
    int dd = fecha - aa*10000 - mm*100;
    archSalida.fill('0');
    archSalida<<setw(2)<<dd<<'/'<<setw(2)<<mm<<'/'<<setw(4)<<aa;
    archSalida.fill(' ');
}
// Modulo AUXILIAR de Impresion de Valor Temporal como 'Hora'
void imprimirHora(ofstream &archSalida,int hora){
    int hor = hora/3600;
    int min = (hora - hor*3600)/60;
    int seg = hora - hor*3600 - min*60;
    archSalida.fill('0');
    archSalida<<setw(2)<<hor<<':'<<setw(2)<<min<<':'<<setw(2)<<seg;
    archSalida.fill(' ');
}
