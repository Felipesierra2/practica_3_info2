#ifndef LOGIN_H
#define LOGIN_H

#include <string>

void identificarUsuario(int semilla, int metodo);
bool esAdmin(const std::string& claveIngresada, int semilla, int metodo);
bool esCliente(const std::string& cedula, const std::string& clave, int semilla, int metodo);

#endif // LOGIN_H
