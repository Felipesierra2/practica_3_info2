#include "codificar.h"
#include <bitset>
#include <iostream>

static std::string concatenarBytes(const std::string& datos){
    std::string bits;
    bits.reserve(datos.size()*8);

    for (size_t i = 0; i < datos.size(); ++i) {
        unsigned char b = static_cast<unsigned char>(datos[i]);
        bits += std::bitset<8>(b).to_string();
    }
    return bits;
}

static std::string completarBits(const std::string& bits8, int semilla){
    size_t longitud = bits8.length();
    size_t resto = longitud % semilla;

    if (resto == 0) return bits8;

    size_t nuevaLongitud = longitud + (semilla - resto);
    std::string resultado;
    resultado.reserve(nuevaLongitud);
    resultado = bits8;
    resultado.append(semilla - resto, '0');

    return resultado;

}

static std::string invertirLosBits(const std::string& bloques){
    std::string invertirTodos = bloques;
    for (size_t i = 0; i < invertirTodos.size(); i++){
        invertirTodos[i] = (invertirTodos[i] == '0') ? '1':'0';
    }
    return invertirTodos;
}

static std::string invertirCadaN(const std::string& bits, int n){
    std::string salida = bits;
    if (n <= 0) return salida;
    for (int i = n - 1; i < (int)salida.size(); i+=n){
        salida[i] = (salida[i] == '0') ? '1':'0';
    }
    return salida;
}

static std::string codificarBloques(const std::string& bits, int semilla){
    size_t totalBloques = bits.size() / semilla;
    std::string resultado;
    resultado.reserve(bits.size());

    for (size_t i = 0; i < totalBloques ;i++){
        size_t inicio = i * semilla;
        std::string bloque = bits.substr(inicio, semilla);

        if (i == 0){
            resultado+=invertirLosBits(bloque);
        }else{
            std::string sigtes = bits.substr((i-1)*semilla,semilla);
            int unos = 0;
            for (char u:sigtes)
                if (u == '1')
                    ++unos;
            int ceros = static_cast<int>(semilla) - unos;

            if (unos == ceros){
                resultado+=invertirLosBits(bloque);
            }else if (ceros > unos){
                resultado+= invertirCadaN(bloque, 2);
            }else{
                resultado+= invertirCadaN(bloque,3);
            }
        }
    }

    return resultado;
}


void codificarMetodo1(const std::string &datos, int semilla) {
    if (semilla <= 0) {
        std::cerr << "Semilla inválida\n";
        return;
    }
    std::string bits8 = concatenarBytes(datos);

    if (bits8.empty()) {
        std::cerr << "Archivo vacío: nada que codificar\n";
        return;
    }
    std::string completos = completarBits(bits8, semilla);

    if (completos.size() % semilla != 0) {
        std::cerr << "Advertencia: padding incorrecto: "
                  << completos.size() << " % " << semilla << " != 0\n";
    }
    std::string codificado = codificarBloques(completos, semilla);

    if (codificado.size() < 300) std::cout << codificado << '\n';
    else std::cout << codificado.substr(0,300) << "\n...(truncado)\n";
}


void codificarMetodo2(const std::string &datos, int semilla){
    std::cout << "Ejecutando metodo 2" << std::endl;
}

