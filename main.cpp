// main.cpp
#include <iostream>
#include "auxiliares.h"

// main muy limpio: solo orquesta
int main(int nombreP, char** arc) {
    const std::string archivo = (nombreP >= 2) ? arc[1] : "prueba1.txt";
    std::string datos;

    // aquí solo llamamos y validamos si falla
    if (!leerArchivo(archivo, datos, true)) {
        std::cerr << "Error leyendo archivo: " << archivo << "\n";
        return 1;
    }

    // Ahora 'datos' contiene todos los bytes leídos y puedes pasarlo a codificar/decodificar
    std::cout << "Tamaño leído: " << datos.size() << " bytes\n";

    // ejemplo mínimo: llamar a codificar(datos); (implementa en otro módulo)
    return 0;
}

