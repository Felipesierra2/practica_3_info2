// main.cpp
#include <iostream>
#include <limits>
#include "auxiliares.h"
#include "codificar.h"
#include "decodificar.h"


int main(int argc, char** argv) {
    std::string archivo;

    if (argc >= 2) {
        archivo = argv[1];
    } else {
        std::cout << "Nombre del archivo (enter para 'prueba1.txt'): ";
        std::getline(std::cin, archivo);
        if (archivo.empty()) archivo = "prueba1.txt";
    }

    std::string datos;
    if (!leerArchivo(archivo, datos, true)) {
        std::cerr << "Error leyendo archivo: " << archivo << "\n";
        return 1;
    }

    std::cout << "=== Programa de Codificacion y Decodifiacion===" << std::endl;

    int opcion = validarEntrada("Ingrese 1 para codificar o 2 para decodificar: ");
    int semilla = 0,metodo = 0;
    std::string archivoSalida;

    if (opcion == 1) {
        int semilla = validarEntrada("Ingrese el tamano de la semilla: ");
        int metodo = validarEntrada("Ingrese el metodo a codificar: ");

        std::cout << "Nombre archivo salida (enter para salida.bin): ";
        std::getline(std::cin, archivoSalida);

        if (archivoSalida.empty()) archivoSalida = "salida.bin";

        if (metodo == 1) codificarMetodo1(datos, semilla , archivoSalida);
        else if(metodo == 2) codificarMetodo2(datos, semilla,archivoSalida);
        else std::cout << "Error: Intentelo nuevamente. " << std::endl;
    }

    else if (opcion == 2) {
        int semilla = validarEntrada("Ingrese el tamano de la semilla: ");
        int metodo = validarEntrada("Ingrese el metodo a decodificar: ");

        std::cout << "Nombre del archivo codificado (enter para salida.bin): ";
        std::string archivoCod;
        std::getline(std::cin, archivoCod);

        if (archivoCod.empty()) archivoCod = "salida.bin";

        std::cout << "Archivo de salida (enter para 'descomprimido.txt'): ";
        std::getline(std::cin, archivoSalida);
        if (archivoSalida.empty()) archivoSalida = "descomprimido.txt";

        decodificar(semilla, metodo, archivoCod, archivoSalida);
    }
    else {
        std::cout << "Opción no válida." << std::endl;
    }
    return 0;
}



