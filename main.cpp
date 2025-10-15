// main.cpp
#include <iostream>
#include "auxiliares.h"
#include "codificar.h"
#include "decodificar.h"
#include "login.h"
#include "limpiarartemporales.h"

int main() {
    std::cout << "=== SISTEMA DE CAJERO ELECTRONICO ===\n";

    int semilla = validarEntrada("Ingrese el tamaño de la semilla: ");
    int metodo = validarEntrada("Ingrese el método de codificación (1 o 2): ");

    int opcion = validarEntrada(
        "\n1. Codificar archivo\n"
        "2. Decodificar archivo\n"
        "3. Acceder al sistema\n"
        "Seleccione una opción: "
        );

    if (opcion == 1) {
        // CODIFICAR ARCHIVO
        std::string archivo, salida;
        std::cout << "Archivo de entrada: ";
        std::getline(std::cin, archivo);
        if (archivo.empty()) archivo = "sudo.txt";

        std::cout << "Archivo de salida (enter para 'sudo.bin'): ";
        std::getline(std::cin, salida);
        if (salida.empty()) salida = "sudo.bin";

        std::string datos;
        leerArchivo(archivo, datos, true);

        if (metodo == 1) codificarMetodo1(datos, semilla, salida);
        else codificarMetodo2(datos, semilla, salida);
    }

    else if (opcion == 2) {
        std::string archivoCod, salida;
        std::cout << "Archivo encriptado (enter para 'sudo.bin'): ";
        std::getline(std::cin, archivoCod);
        if (archivoCod.empty()) archivoCod = "sudo.bin";

        std::cout << "Archivo de salida (enter para 'sudo.txt'): ";
        std::getline(std::cin, salida);
        if (salida.empty()) salida = "sudo.txt";

        decodificar(semilla, metodo, archivoCod, salida);
    }

    else if (opcion == 3) {
        identificarUsuario(semilla, metodo);
    }

    limpiarArTemporales();
    return 0;
}




