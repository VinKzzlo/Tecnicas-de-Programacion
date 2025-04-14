/* 
 * File:   funcionesCadenas.cpp

 *
 * Created on 6 de noviembre de 2023, 07:08 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#include "funcionesCadenas.h"

void modificarNombre(char *nombre){
    int i = 0;
    while(true){
        if(nombre[i]==0) break;
        nombre[i]-=(nombre[i]>='a' and nombre[i]<='z'?'a'-'A':0);
        i++;
    }
}