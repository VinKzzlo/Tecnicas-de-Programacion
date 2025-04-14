/* 
 * Archivo:   FuncionesAuxiliares.h
 * Autor: VinKzzlo
 *
 * Creado el on 26 de mayo de 2024, 14:51
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

void leerDatosPacientes(const char *nombArch,int *pacientesDNI,int *pacientesDist,
                        double *pacientesDcto,char *pacientesClasif,int &cantPac);
void leerDatosMedicinas(const char *nombArch,int *medicinaCodigo,
                        double *medicinaPrecio,int &cantMedi);
void verificarReportePrueba(const char *nombArch,int *pacientesDNI,
                            int *pacientesDist, double *pacientesDcto,
                            char *pacientesClasif, int cantPac,
                            int *medicinaCodigo, double *medicinaPrecio,
                            int cantMedi);
void updateTotalPacientes(const char *nombArch, int *pacientesDNI,
                          int *pacientesDist, double *pacientesDcto,
                          char *pacientesClasif, int cantPac,
                          int *medicinaCodigo, double *medicinaPrecio,
                          int cantMedi,
                          int *pacientesCantCit,int *pacientesCantMeds,
                          double *pacientesPago);
int buscarPaciente(int nroDNIPac,int *pacientesDNI,int cantPac);
int buscarMedicina(int codMedic,int *medicinaCodigo,int cantMedi);
void registrarEnPacis(ifstream &arch,int &pacientesCantMeds,double &pacientesPago,
                      double pacientesDcto,int *medicinaCodigo,
                      double *medicinaPrecio, int cantMedi);
void ordenarArreglosPacs(int *pacientesDNI,int *pacientesDist,double *pacientesDcto,
                         char *pacientesClasif,int *pacientesCantCit,
                         int *pacientesCantMeds,double *pacientesPago,int cantPac);
void cambiarInt(int &datoI,int &datoK);
void cambiarDbl(double &datoI,double &datoK);
void cambiarChr(char &datoI,char &datoK);
void emitirReportePacientes(const char *nombArch,int *pacientesDNI,int *pacientesDist,
                            double *pacientesDcto, char *pacientesClasif,
                            int *pacientesCantCit, int *pacientesCantMeds,
                            double *pacientesPago,int cantPac);
void imprimeEncabezado(ofstream &arch);
void imprimeLinea(ofstream &arch,char c);
#endif /* FUNCIONESAUXILIARES_H */

