#include <iostream>
#include "auxiliares.h"
#include "codificar.h"
#include "codificar.h"
#include "decodificar.h"

using namespace std;

int main() {
    cout << "=== Programa de Codificacion y Decodifiacion===" << endl;
    int opcion = validarEntrada("Ingrese 1 para codificar o 2 para decodificar: ");

    if (opcion == 1) {
        codificarMetodo1();
    }
    else if (opcion == 2) {
        decodificar();
    }
    else {
        cout << "Opción no válida." << endl;
    }

    return 0;
}

