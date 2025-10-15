#include "decodificar.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>


bool leerArchivoComoBits(const std::string& codificado, std::string& bits, uint64_t& tamOriginalBits) {
    std::ifstream archivoBinarios(codificado, std::ios::binary);
    std::cout << "Acá: " << codificado << std::endl;
    if (!archivoBinarios) return false;

    archivoBinarios.read(reinterpret_cast<char*>(&tamOriginalBits), sizeof(tamOriginalBits));
    if (!archivoBinarios) return false;

    bits.clear();
    unsigned char byte;

    while (archivoBinarios.read(reinterpret_cast<char*>(&byte), 1)) {

        for (int i = 7; i >= 0; --i) {
            bits.push_back( ((byte >> i) & 0x01) ? '1' : '0' );
        }
    }
    archivoBinarios.close();
    return true;
}

std::string* dividirBloques(const std::string& bits, int semilla, int& cantidadBloques) {
    int totalBits = static_cast<int>(bits.size());
    cantidadBloques = (totalBits + semilla - 1) / semilla;
    std::string* bloques = new std::string[cantidadBloques];

    int indice = 0;
    for (int i = 0; i < cantidadBloques; ++i) {
        std::string bloque = "";
        for (int j = 0; j < semilla && indice < totalBits; ++j, ++indice) {
            bloque.push_back(bits[indice]);
        }
        bloques[i] = bloque;
    }

    return bloques;
}

std::string invertirBits(const std::string& bloque){
    std::string resul = bloque;
    for(int i = 0; i < bloque.size(); i++){
        resul[i] = (bloque[i] == '0') ? '1':'0';
    }

    return resul;
}

std::string invertirCadaN(const std::string& bits, int grupo) {
    std::string result = bits;
    if (grupo <= 0) return result;
    for (int i = 0; i < (int)bits.size(); i += grupo) {
        for (int j = 0; j < grupo && (i + j) < (int)bits.size(); ++j) {
            result[i + j] = (bits[i + j] == '0') ? '1' : '0';
        }
    }
    return result;
}

std::string decodificarbitsMet1(std::string* bloques, int cantidadBloques, int semilla) {
    if (cantidadBloques <= 0) return "";

    std::string resultado = "";

    std::string anteriorDecod = invertirBits(bloques[0]);
    resultado += anteriorDecod;

    for (int i = 1; i < cantidadBloques; ++i) {
        int unos = 0;
        for (int k = 0; k < anteriorDecod.size(); ++k) {
            if (anteriorDecod[k] == '1') ++unos;
        }
        int ceros = static_cast<int>(anteriorDecod.size()) - unos;

        std::string actualCod = bloques[i];
        std::string actualDecod;

        if (unos == ceros) {
            actualDecod = invertirBits(actualCod);
        } else if (ceros > unos) {
            actualDecod = invertirCadaN(actualCod, 2);
        } else {
            actualDecod = invertirCadaN(actualCod, 3);
        }

        resultado += actualDecod;
        anteriorDecod = actualDecod;
    }

    return resultado;
}



std::string bitsAtexto(const std::string& bits){
    std::string texto = "";

    for (int i = 0; i + 7 < bits.size(); i+=8){
        unsigned char valor = 0;
        for (int j = 0; j < 8; j++){
            valor = (valor << 1) | (bits[i + j] - '0');
        }
        texto+= valor;
    }
    return texto;
}

static std::string desplazarBloquesInverso(const std::string& bitsBloque){
    std::string salida = bitsBloque;
    if (bitsBloque.empty()) return salida;

    char primero = bitsBloque[0];
    for (size_t i = 0; i < bitsBloque.size() - 1; i++){
        salida[i] = bitsBloque[i + 1];
    }
    salida[bitsBloque.size() - 1] = primero;

    return salida;
}


/*==================== Funcion principal =======================*/

void decodificar(int semilla, int metodo, const std::string& codificado, const std::string& decodificado) {
    std::string archivoEntrada = codificado;
    std::string archivoSalida = decodificado;

    if (archivoSalida.empty()) archivoSalida = "descomprimido.txt";

    std::cout << "Iniciando decodificacion (semilla=" << semilla << ", metodo " << metodo << ") del archivo " << codificado << std::endl;

    std::string bits;
    uint64_t tamanoOriginal = 0;
    if(!leerArchivoComoBits(codificado,bits,tamanoOriginal)){
        std::cerr << "Error: no se pudo abrir o leer el archivo Binario " << codificado << std::endl;
        return;
    }

    int cantidadBloques = 0;
    std::string* bloques = dividirBloques(bits,semilla,cantidadBloques);

    std::string bitsDecodificados;
    if (metodo == 1) {
        std::cout << "Ejecutando decodificacion por el metodo 1..." << std::endl;
        bitsDecodificados = decodificarbitsMet1(bloques, cantidadBloques, semilla);
    } else if (metodo == 2) {
        std::cout << "Decodificando con metodo 2..." << std::endl;

        int cantidadBloques = 0;
        std::string* bloques = dividirBloques(bits, semilla, cantidadBloques);

        std::string resultado;
        resultado.reserve(bits.size());

        for (int i = 0; i < cantidadBloques; i++) {
            bitsDecodificados += desplazarBloquesInverso(bloques[i]);
        }

        delete[] bloques;

        if (tamanoOriginal < bitsDecodificados.size())
            bitsDecodificados = bitsDecodificados.substr(0, tamanoOriginal);
        std::cout << "Archivo decodificado con metodo 2: " << archivoSalida << std::endl;

    }else {
        std::cerr << "Error: Ingres 1 para el metodo 1 o 2 para el metodo 2";
        delete[] bloques;
        return;
    }
    if (tamanoOriginal > 0 && bitsDecodificados.size() > tamanoOriginal) {
        bitsDecodificados.erase(bitsDecodificados.begin() + static_cast<long>(tamanoOriginal), bitsDecodificados.end());
    }

    int resto = static_cast<int>(bitsDecodificados.size()) % 8;
    if (resto != 0) bitsDecodificados.erase(bitsDecodificados.end() - resto, bitsDecodificados.end());

    std::string textoDecodificado = bitsAtexto(bitsDecodificados);

    std::ofstream exit(archivoSalida);
    if (!exit) {
        std::cerr << "Error: no se pudo crear el archivo de salida: " << archivoSalida << std::endl;
        delete[] bloques;
        return;
    }
    exit << textoDecodificado;
    exit.close();

    delete[] bloques;


}
