#ifndef LOGIN_H
#define LOGIN_H

#include <string>

void identificarUsuario(int semilla,
                        int metodo,
                        std::string& archivoSalida);

bool esAdmin(const std::string& claveIngresada,
             int semilla,
             int metodo,
             std::string &archivoSalida);

bool esCliente(const std::string& cedula,
               const std::string& clave,
               int semilla,
               int metodo);

#endif // LOGIN_H
