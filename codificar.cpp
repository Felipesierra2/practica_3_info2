#include "codificar.h"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <fstream>

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

static std::string invertirCadaN(const std::string& bits, int grupo) {
    std::string result = bits;
    if (grupo <= 0) return result;
    for (int i = 0; i < (int)bits.size(); i += grupo) {
        // invertimos el bloque [i .. i+grupo-1] (si alcanza)
        for (int j = 0; j < grupo && (i + j) < (int)bits.size(); ++j) {
            result[i + j] = (bits[i + j] == '0') ? '1' : '0';
        }
    }
    return result;
}

static std::string desplazarBloques(const std::string& bitsBloque){
    std::string salida = bitsBloque;
    if (bitsBloque.empty()) return salida;

    salida[0] = bitsBloque[bitsBloque.size() - 1];

    for (size_t i = 1; i < bitsBloque.size(); i++){
        salida[i] = bitsBloque[i-1];
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

static std::string codificarBloqMetodo2(const std::string& bits, int semilla){
    size_t totalBloques = bits.size() / semilla;
    std::string resultado;
    resultado.reserve(bits.size());

    for (size_t i = 0; i < totalBloques; i++){
        size_t inicio = i * semilla;
        std::string bloque = bits.substr(inicio,semilla);

        resultado += desplazarBloques(bloque);
    }

    return resultado;
}

static bool escribirBinarios(const std:: string& bits, const std::string& archivoExit, uint64_t tamOriginal){
    if (bits.empty()) {
        std::cerr << "guardarBinario: bits vacios\n";
        return false;
    }

    if (bits.size() % 8 != 0) {
        std::cerr << "guardarBinario: error - la cadena no es multiplo de 8\n";
        return false;
    }

    std::ofstream exit(archivoExit, std::ios::binary);
    if(!exit){
        std::cerr << "No se pudo abrir: " << archivoExit << std::endl;
        return false;
    }

    exit.write(reinterpret_cast<const char*>(&tamOriginal), sizeof(tamOriginal));
    std::string buffer;
    buffer.reserve(bits.size() / 8);

    for (size_t i = 0; i < bits.size(); i+= 8){
        unsigned char byte = 0;
        for (size_t j = 0; j < 8; j++){
            char bit = bits[i + j];
            byte = (byte << 1) | (bit == '1' ? 1u:0u);
        }
        buffer.push_back(static_cast<char>(byte));
    }

    exit.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
    exit.close();
    return true;
}




//=====================Funciones principales================================

void codificarMetodo1(const std::string &datos, int semilla, const std::string &archivoExit) {
    if (semilla <= 0) {
        std::cerr << "Semilla invalida\n";
        return;
    }
    std::string bits8 = concatenarBytes(datos);

    if (bits8.empty()) {
        std::cerr << "Archivo vacio: nada que codificar\n";
        return;
    }
    std::string completos = completarBits(bits8, semilla);

    if (completos.size() % semilla != 0) {
        std::cerr << "Error: "<< completos.size() << " % " << semilla << " != 0\n";
    }
    std::string codificado = codificarBloques(completos, semilla);

    auto padA8 = [](const std::string &s)->std::string {
        size_t resto = s.size() % 8;
        if (resto == 0) return s;
        size_t faltan = 8 - resto;
        std::string r = s;
        r.append(faltan, '0');
        return r;
    };

    std::string codificad8bits = padA8(codificado);

    if(!escribirBinarios(codificad8bits,archivoExit, bits8.size())){
        std::cerr << "Error al escribir el archivo" << std::endl;
    }else {
        std::cout << "Salida escrita en binario: " << archivoExit
                  << " (original_bits=" << bits8.size()
                  << ", payload_bits=" << codificad8bits.size()
                  << ", payload_bytes=" << codificad8bits.size()/8 << ")\n";
    }
}

void codificarMetodo2(const std::string &datos, int semilla,const std::string &archivoExit){
    if (semilla <= 0) {
        std::cerr << "Semilla invalida\n";
        return;
    }
    std::string bits8 = concatenarBytes(datos);

    if (bits8.empty()) {
        std::cerr << "Archivo vacio: nada que codificar\n";
        return;
    }
    std::string completos = completarBits(bits8, semilla);

    if (completos.size() % semilla != 0) {
        // error lógico: completarBits debe garantizar que esto no ocurra
        std::cerr << "Error: padding no aplicado correctamente\n";
        return;
    }
    std::string codificad2 = codificarBloqMetodo2(completos,semilla);

    auto padA8 = [](const std::string &s)->std::string {
        size_t resto = s.size() % 8;
        if (resto == 0) return s;
        size_t faltan = 8 - resto;
        std::string r = s;
        r.append(faltan, '0');
        return r;
    };

    std::string codificad8bits = padA8(codificad2);

    if(!escribirBinarios(codificad8bits,archivoExit,bits8.size())){
        std::cerr << "Error al escribir el archivo" << std::endl;
    }else {
        std::cout << "Salida escrita en binario: " << archivoExit
                  << " (original_bits=" << bits8.size()
                  << ", payload_bits=" << codificad8bits.size()
                  << ", payload_bytes=" << codificad8bits.size()/8 << ")\n";
    }
}

