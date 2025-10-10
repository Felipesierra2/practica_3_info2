#include "auxiliares.h"
#include <iostream>
#include <limits>

using namespace std;

int validarEntrada(const string& mensaje) {
    int num;

    while (true) {
        cout << mensaje;
        cin >> num;

        if (cin.fail()) {
            cout << "Error: el valor ingresado no es un número entero. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return num;
        }
    }
}


