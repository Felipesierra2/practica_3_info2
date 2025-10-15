#include "administrador.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include "codificar.h"
#include "decodificar.h"
#include "auxiliares.h"
#include "login.h"


//==========================FUNCIONES PRINCIPALES ==================
void accesoAdmin(int semilla, int metodo){
    std::string claveIngresada;
    std::string claveGuardada;

    if (!leerArchivo("sudo.txt", claveGuardada, true)) {
        std::cerr << "Error: No se encontro el archivo sudo.txt.\n";
        return;
    }

    std::cout << "\nIngrese la clave de administrador: ";
    std::getline(std::cin, claveIngresada);

    std::ofstream temp("temp_admin.txt");
    temp << claveIngresada;
    temp.close();

    if (metodo == 1)
        codificarMetodo1(claveIngresada, semilla, "temp_codificada.txt");
    else if (metodo == 2)
        codificarMetodo2(claveIngresada, semilla, "temp_codificada.txt");
    else {
        std::cerr << "Metodo de codificacion no valido.\n";
        return;
    }

    std::string codificadaIngresada;
    leerArchivo("temp_codificada.txt", codificadaIngresada, true);

    if (codificadaIngresada == claveGuardada) {
        std::cout << "\nAcceso concedido al administrador.\n";
        menuAdmin(semilla, metodo); // <- entra al menú del admin
    } else {
        std::cout << "\nClave incorrecta. Acceso denegado.\n";
    }

}

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

            std::ofstream tempo("temp_usuario.txt");
            tempo << datos;
            tempo.close();

            if (metodo == 1)
                codificarMetodo1(datos, semilla, "temp_codificado.txt");
            else if(metodo == 2)
                codificarMetodo2(datos, semilla, "temp_codificado.txt");

            std::ifstream tempoCodificado("temp_usuario.txt", std::ios::binary);
            std::string codificada ((std::istreambuf_iterator<char>(tempoCodificado)),
                                   std::istreambuf_iterator<char>());

            tempoCodificado.close();

            std::ofstream clientes("clientes.txt", std::ios::app | std::ios::binary);
            if (!clientes) {
                std::cerr << "Error: no se pudo abrir clientes.txt\n";
                return;
            }

            clientes << codificada <<"\n";
            clientes.close();

            std::cout << "✅ Usuario registrado exitosamente.\n";
        }



    }while(opcion !=2);
}
