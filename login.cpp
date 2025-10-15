// login.cpp
#include <iostream>
#include <string>
#include <fstream>

//KKKKKKKK======================METODOS================================KKKKKKKKKKKKKKKKKKKK
#include "codificar.h"
#include "administrador.h"
#include "login.h"
#include "menucliente.h"

bool compararArchivosBinarios(const std::string& archivo1, const std::string& archivo2) {
    std::ifstream a1(archivo1, std::ios::binary);
    std::ifstream a2(archivo2, std::ios::binary);

    if (!a1 || !a2) return false;

    a1.seekg(0, std::ios::beg);
    a2.seekg(0, std::ios::beg);

    std::string contenido((std::istreambuf_iterator<char>(a1)),
                          std::istreambuf_iterator<char>());

    std::string contenido2((std::istreambuf_iterator<char>(a2)),
                          std::istreambuf_iterator<char>());

    int tamano = contenido.size();
    int tamano2 = contenido2.size();

    for (int i = 0; i < tamano; i++){
        if(contenido[i] != contenido2[i]) return false;
    }

    return true;
}

void identificarUsuario(int semilla,
                        int metodo,
                        std::string &archivoSalida )
{

    std::string id, clave;

    std::cout << "\n=== SISTEMA DE ACCESO ===" << std::endl;
    std::cout << "Ingrese su identificacion (cedula): ";
    std::getline(std::cin, id);

    std::cout << "Ingrese su clave: ";
    std::getline(std::cin, clave);

    std::cout << "\nProcesando autenticacion...\n";

    if (esAdmin(clave, semilla,metodo, archivoSalida)) {
        std::cout << "Bienvenido, Administrador.\n";
        menuAdmin(semilla, metodo);
        return;
    }

    if (esCliente(id, clave, semilla, metodo)) {
        std::cout << "Bienvenido, Cliente.\n";
        menuCliente(id, semilla, metodo);
        return;
    }

    std::cout << "Credenciales invalidas.\n";
}


bool esAdmin(const std::string& claveIngresada,
             int semilla,
             int metodo,
             std::string& archivoSalida )
{

    const std::string archivoAdmin = "sudo.bin";
    std::string archivoTemp = archivoSalida.empty() ? "temp_admin.bin" : archivoSalida;

    if (metodo == 1)
        codificarMetodo1(claveIngresada, semilla, archivoTemp);
    else if (metodo == 2)
        codificarMetodo2(claveIngresada, semilla, archivoTemp);
    else {
        std::cerr << "Metodo no valido.\n";
        return false;
    }

    bool coinciden = compararArchivosBinarios(archivoAdmin, archivoTemp);

    remove(archivoTemp.c_str());

    return coinciden;
}

bool esCliente(const std::string& cedula,
               const std::string& clave,
               int semilla,
               int metodo) {

    std::string archivoCod = "sudo.bin";
    std::string archivoTemp = "temp_usuario.txt";

    std::ifstream archivo(archivoTemp);
    if (!archivo) {
        std::cerr << "Error: No se pudo abrir el archivo temporal de clientes.\n";
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {

            size_t pos1 = linea.find(';');
            size_t pos2 = linea.find(';', pos1 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string cedulaArchivo = linea.substr(0, pos1);
            std::string claveArchivo = linea.substr(pos1 + 1, pos2 - pos1 - 1);

            if (cedulaArchivo == cedula && claveArchivo == clave) {
                archivo.close();
                return true;
            }
        }
    }

    archivo.close();
    return false;
}

