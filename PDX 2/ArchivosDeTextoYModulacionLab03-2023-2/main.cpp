
/*/ 
 * Projecto:  ArchivosDeTextoYModulacionLab03-2023-2
 * Nombre del Archivo:  main.cpp
 * Autor: El EnTrEvErAdO
/*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"

// Modulo Principal
int main(int argc, char** argv) {
    
    // Emision de Reporte
    emitirReporte("Reporte.txt","Televi.txt","RegistroDePreferencias.txt",
                  "Canales.txt");

    return 0;
}
