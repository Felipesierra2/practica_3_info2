#include "administrador.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "codificar.h"
#include "auxiliares.h"


//==========================FUNCIONES PRINCIPALES ==================
void menuAdmin(int semilla, int metodo){
    int opcion = 0;

    do {
        std::cout << "\n=== MENU DEL ADMINISTRADOR ===" << std::endl;
        std::cout << "1. Registrar nuevo usuario del cajero" << std::endl;
        std::cout << "2. Volver al menu principal" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 1) {
            std::string cedula, clave, saldo;

            std::cout << "Ingrese la cedula del usuario: ";
            std::getline(std::cin, cedula);

            std::cout << "Ingrese la clave del usuario: ";
            std::getline(std::cin, clave);

            std::cout << "Ingrese el saldo inicial del usuario (COP): ";
            std::getline(std::cin, saldo);

            std::string datos = cedula + ";" + clave + ";" + saldo + "\n";

            // Guardar el archivo temporario en texto (opcional, para depuración)
            std::ofstream tempo("temp_usuario.txt", std::ios::binary);
            if (!tempo) {
                std::cerr << "Error: no se pudo crear usuario.txt\n";
                break;
            }
            tempo << datos;
            tempo.close();

            // Crear el archivo codificado (se asume que la función lo escribe en disco)
            const std::string archivoCodificado = "codificado.bin";
            if (metodo == 1)
                codificarMetodo1(datos, semilla, archivoCodificado);
            else if (metodo == 2)
                codificarMetodo2(datos, semilla, archivoCodificado);

            // Leer el archivo codificado en binario
            std::ifstream tempoCodificado(archivoCodificado, std::ios::binary);
            if (!tempoCodificado) {
                std::cerr << "Error: no se pudo abrir " << archivoCodificado << " despues de codificar.\n";
                break;
            }
            std::string codificada((std::istreambuf_iterator<char>(tempoCodificado)),
                                   std::istreambuf_iterator<char>());
            tempoCodificado.close();

            // Abrir clientes.txt en append binario y escribir los bytes tal cual
            std::ofstream clientes("clientes.txt", std::ios::app | std::ios::binary);
            if (!clientes) {
                std::cerr << "Error: no se pudo abrir clientes.txt\n";
                break;
            }

            // Escribir bytes y separar registros con un '\n' si tu decodificador lo espera
            if (!codificada.empty()) {
                clientes.write(codificada.data(), static_cast<std::streamsize>(codificada.size()));
                clientes.put('\n'); // opcional: usa esto si tu decodificador espera líneas separadas
            }
            clientes.close();

            std::cout << "Usuario registrado exitosamente.\n";
        }
    }while(opcion !=2);
}
