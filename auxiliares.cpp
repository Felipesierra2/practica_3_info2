// auxiliares.cpp
#include "auxiliares.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>


static std::string byteToBits(unsigned char c) {
    std::string s;
    s.reserve(8);
    for (int i = 7; i >= 0; --i) s.push_back(((c >> i) & 1) ? '1' : '0');
    return s;
}

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

    std::cout << "Fin de la vista" << std::endl;

    return true;
}







