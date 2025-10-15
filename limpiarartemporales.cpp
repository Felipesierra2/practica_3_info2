#include "limpiarartemporales.h"

#include <iostream>
#include <cstdio>

void limpiarTemporales() {
    const char* archivos[] = {
        "temp_admin.txt",
        "temp_codificada.txt",
        "temp_actualizado.txt"
    };

    int total = sizeof(archivos) / sizeof(archivos[0]);
    for (int i = 0; i < total; i++) {
        if (std::remove(archivos[i]) == 0) {
            std::cout << "Archivo temporal eliminado: " << archivos[i] << std::endl;
        }
    }
}

