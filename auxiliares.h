#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <string>

bool leerArchivo(const std::string &ruta, std::string &salida, bool mostrar = false);
int validarEntrada(const std::string& mensaje = "Ingrese un número entero: ");

#endif

