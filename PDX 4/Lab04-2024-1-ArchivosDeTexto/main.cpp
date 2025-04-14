
/*/ 
 * Projecto:  Lab04-2024-1-ArchivosDeTexto
 * Nombre del Archivo:  main.cpp
 * Autor: Super Spaghetti X
/*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "funciones.h"

// Modulo Principal
int main(int argc, char** argv) {

    // Emision de Reporte
    emitirReporte("Reporte.txt","Medicos.txt","Medicinas.txt",
                  "CitasMedicas.txt");

    return 0;
}
