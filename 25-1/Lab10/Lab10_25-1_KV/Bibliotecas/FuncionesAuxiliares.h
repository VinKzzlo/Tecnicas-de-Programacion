/*
 *
 * Proyecto:    Lab10_25_1_KV
 * Archivo:     FuncionesAuxiliares.h
 * Autor:       VinKzzlo
 * Fecha:       24/11/2025
 *
 */

#ifndef LAB10_25_1_KV_FUNCIONESAUXILIARES_H
#define LAB10_25_1_KV_FUNCIONESAUXILIARES_H

void crearListaOrdenada(const char *nombArch,struct Nodo *&lista);
void leerAlumno(ifstream &arch,struct Cuenta &cuentaNueva);
void insertarOrdenado(struct Cuenta cuentaNueva,struct Nodo *&lista);
void mostrarLista(const char *nombArch,Nodo *lista);
void registrarMovimientos(const char *nombArch,struct Nodo *lista);
int leerFecha(ifstream &arch);
struct Nodo *buscarCuenta(int codigo, struct Nodo *lista);
void actualizarCuenta(int fecha, double montoMovimiento, struct Cuenta &cuenta);
void emiteReporteSaldos(const char *nombArch, struct Nodo *lista);
char *leeCadenaExacta(ifstream &arch, char delim='\n');
void imprimeCuenta(ofstream &archRep,const struct Cuenta &cuenta);
void imprimeFecha(ofstream &archrRep, int fecha);
#endif //LAB10_25_1_KV_FUNCIONESAUXILIARES_H