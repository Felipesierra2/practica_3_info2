#include <iostream>
#include <string>
#include "auxiliares.h"
#include "codificar.h"
#include "decodificar.h"
#include "login.h"
#include "limpiarartemporales.h"

int main() {
    std::cout << "=== SISTEMA DE CAJERO ELECTRONICO ===" << std::endl;

    std::cout << "\n1. Codificar archivo" << std::endl;
    std::cout << "2. Decodificar archivo" << std::endl;
    std::cout << "3. Acceder al sistema (Admin / Cliente)" << std::endl;

    int opcion = validarEntrada("\nSeleccione una opcion: ");

    int semilla = validarEntrada("Ingrese el tamano de la semilla: ");
    int metodo  = validarEntrada("Ingrese el metodo (1 o 2): ");

    std::string archivoEntrada, archivoSalida;

    if (opcion == 1) {
        std::cout << "Archivo de entrada: ";
        std::getline(std::cin, archivoEntrada);
        if (archivoEntrada.empty()) archivoEntrada = "sudo.txt";

        std::cout << "Archivo de salida (enter para 'sudo.bin'): ";
        std::getline(std::cin, archivoSalida);
        if (archivoSalida.empty()) archivoSalida = "sudo.bin";

        std::string datos;
        if (!leerArchivo(archivoEntrada, datos, true)) {
            std::cerr << "Error al leer el archivo: " << archivoEntrada << "\n";
            return 1;
        }

        if (metodo == 1)
            codificarMetodo1(datos, semilla, archivoSalida);
        else
            codificarMetodo2(datos, semilla, archivoSalida);
    }

    else if (opcion == 2) {
        std::cout << "Archivo encriptado (enter para 'sudo.bin'): ";
        std::getline(std::cin, archivoEntrada);
        if (archivoEntrada.empty()) archivoEntrada = "sudo.bin";

        std::cout << "Archivo de salida (enter para 'resultado.txt'): ";
        std::getline(std::cin, archivoSalida);
        if (archivoSalida.empty()) archivoSalida = "resultado.txt";

        decodificar(semilla, metodo,archivoEntrada, archivoSalida);
    }

    else if (opcion == 3) {
        identificarUsuario(semilla, metodo, archivoSalida);
    }

    limpiarTemporales();
    std::cout << "\nEjecucion finalizada correctamente.\n";
    return 0;
}





