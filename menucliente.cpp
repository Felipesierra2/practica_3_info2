// cliente.cpp
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

//==================== METODOS=========================
#include "codificar.h"
#include "decodificar.h"
#include "auxiliares.h"

void menuCliente(const std::string& cedula, int semilla, int metodo){
    int opcion = 0;

    do {
        std::cout << "\n=== MENU DEL CLIENTE ===" << std::endl;
        std::cout << "1. Consultar saldo" << std::endl;
        std::cout << "2. Retirar dinero" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        decodificar(semilla, metodo, "clientes.txt", "temp_clientes.txt");

        std::ifstream entrada("temp_clientes.txt");
        std::ofstream salida("temp_actualizado.txt");
        if (!entrada || !salida) {
            std::cerr << "Error abriendo archivos temporales.\n";
            return;
        }

        std::string linea;
        while (std::getline(entrada, linea)) {
            size_t pos1 = linea.find(';');
            size_t pos2 = linea.find(';', pos1 + 1);

            if (pos1 == std::string::npos || pos2 == std::string::npos) {
                salida << linea << "\n";
                continue;
            }

            std::string cedulaArchivo = linea.substr(0, pos1);
            std::string claveArchivo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string saldoStr = linea.substr(pos2 + 1);
            long saldo = std::stol(saldoStr);

            if (cedulaArchivo == cedula) {
                if (opcion == 1) {
                    std::cout << "\nSu saldo actual es: " << saldo << " COP\n";
                }
                else if (opcion == 2) {
                    long retiro;
                    std::cout << "Ingrese cantidad a retirar: ";
                    std::cin >> retiro;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    long total = retiro + 1000;
                    if (saldo >= total) {
                        saldo -= total;
                        std::cout << "Retiro exitoso. Nuevo saldo: " << saldo << " COP\n";
                    } else {
                        std::cout << "Saldo insuficiente.\n";
                    }
                }


                salida << cedulaArchivo << ";" << claveArchivo << ";" << saldo << "\n";
            } else {

                salida << linea << "\n";
            }
        }

        entrada.close();
        salida.close();


        std::string datosActualizados;
        leerArchivo("temp_actualizado.txt", datosActualizados, true);

        if (metodo == 1)
            codificarMetodo1(datosActualizados, semilla, "clientes.txt");
        else if (metodo == 2)
            codificarMetodo2(datosActualizados, semilla, "clientes.txt");
    } while (opcion != 3);
}


