// main.cpp
#include <iostream>
#include "auxiliares.h"
#include "codificar.h"
#include "decodificar.h"

// main muy limpio: solo orquesta
int main(int nombreP, char** arc) {
    const std::string archivo = (nombreP >= 2) ? arc[1] : "prueba1.txt";
    std::string datos;

    // aquí solo llamamos y validamos si falla
    if (!leerArchivo(archivo, datos, true)) {
        std::cerr << "Error leyendo archivo: " << archivo << "\n";
        return 1;
    }

    // ejemplo mínimo: llamar a codificar(datos); (implementa en otro módulo)

    std::cout << "=== Programa de Codificacion y Decodifiacion===" << std::endl;
    int opcion = validarEntrada("Ingrese 1 para codificar o 2 para decodificar: ");

    if (opcion == 1) {
        int semilla = validarEntrada("Ingrese el tamano de la semilla: ");
        int metodo = validarEntrada("Ingrese el metodo a codificar: ");
        std::string archivoSalida;
        if (archivoSalida.empty()) archivoSalida = "salida.bin";

        if (metodo == 1){
            codificarMetodo1(datos, semilla,archivoSalida);
        }
        else if(metodo == 2)
            codificarMetodo2(datos, semilla,archivoSalida);
        else
            std::cout << "Error: Intentelo nuevamente. " << std::endl;
    }
    else if (opcion == 2) {
        decodificar();
    }
    else {
        std::cout << "Opción no válida." << std::endl;
    }
    return 0;
}



