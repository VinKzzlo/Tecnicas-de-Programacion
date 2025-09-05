/* 
 * Archivo:   FuncionesReporte.h
 * Autor:     VinKzzlo
 *
 * Creado el on 21 de abril de 2024, 18:54
 */

#ifndef FUNCIONESREPORTE_H
#define FUNCIONESREPORTE_H

void emitirReporteDeFacturas(const char *nombArchCli,const char *nombArchFac,
                             const char *nombArchPro,const char *nombArchRep);

void leerImprimirDatosFactura(ifstream &archFac,ofstream &archRep);
void leerImprimirDatosCliente(ifstream &archFac, ifstream &archCli,
                              ofstream &archRep);
void buscarImprimirCliente(int dni,ifstream &archCli,ofstream &archRep);
void leerImprimirNombre(ifstream &archCli,ofstream &archRep,
                       char cIni, char cFin);
#endif /* FUNCIONESREPORTE_H */

