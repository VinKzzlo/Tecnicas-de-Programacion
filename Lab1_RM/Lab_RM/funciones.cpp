/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
using namespace std;

void leerDatos(){
    int dni,hora_llegada,min_llegada,segundo_llegada;
    char car;
    imprimirCabezera();
    while(cin.get()!='\n');
    cin>>dni;
    if(cin.eof())break;
    leerNombre();
    
}

void  imprimirCabezera(){
    cout<<setw(70)<<"EMPRESA DE REPARTOS A DOMICILIO"<<endl;
    cout<<setw(65)<<"FECHA DE REPARTOS: 26/08/2024"<<endl;
    imprimirLinea('=');
}

void imprimirLinea(char car){
    for(int i=0;i<80;i++)
        cout.put(car);
    cout<<endl;
}

void leerNombre(){
    char car;
    cin>>ws; 
    while(true){
        car=cin.get();
        if(car==' ')break;
    }
    
}