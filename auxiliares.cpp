// auxiliares.cpp
#include "auxiliares.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <limits>

bool leerArchivo(const std::string &ruta, std::string &salida, bool mostrar) {
    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cerr << "leerArchivo: no se pudo abrir '" << ruta << "'\n";
        return false;
    }

    // calcular tamaño
    archivo.seekg(0, std::ios::end);
    std::streampos tam = archivo.tellg();
    if (tam < 0) tam = 0;
    salida.clear();
    salida.resize(static_cast<size_t>(tam));

    if (tam > 0) {
        archivo.seekg(0, std::ios::beg);
        archivo.read(&salida[0], static_cast<std::streamsize>(tam));
        if (!archivo && !archivo.eof()) {
            std::cerr << "leerArchivo: error al leer '" << ruta << "'\n";
            return false;
        }
    }
    return true;
}


int validarEntrada(const std::string& mensaje) {
    int num;

    while (true) {
        std::cout << mensaje;
        std::cin >> num;

        if (std::cin.fail() || num <= 0) {
            std::cout << "Error:Ingrese un valor entero mayor a 0. Intente nuevamente.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return num;
        }
    }
}




