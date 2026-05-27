#include <iostream>
#include <string>

using namespace std;
#include "conversor.cpp"

void validarTeste(string nomeTeste, string obtido, string esperado) {
    if (obtido == esperado) cout << "[PASSOU] " << nomeTeste << "\n";
    else cout << "[FALHA]  " << nomeTeste << " | Esp: " << esperado << " | Obt: " << obtido << "\n";
}

int main() {
    cout << "=== INICIANDO SUITE DE TESTES ===\n\n";
    bool trunc;

    // Teste F7: Bases Arbitrárias (Base 36 tem todos os números de 0 a 9 e letras de A a Z)
    cout << "Testando F7 (Bases de 2 a 36)...\n";
    validarTeste("F7: Z(36) -> Decimal", doubleParaStringBase(stringParaDoubleBase("Z", 36), 10, trunc), "35");
    validarTeste("F7: 10(10) -> Base 20", doubleParaStringBase(stringParaDoubleBase("10", 10), 20, trunc), "A");
    
    // Teste F8: Detecção Automática
    cout << "\nTestando F8 (Deteccao de Prefixo)...\n";
    string num1 = "0b1010";
    validarTeste("F8: Deteccao Base '0b'", to_string(inferirBase(num1)), "2");
    validarTeste("F8: Prefixo '0b' limpo da string", num1, "1010"); // Prova que a função limpou a sujeira

    string num2 = "0xFF";
    validarTeste("F8: Deteccao Base '0x'", to_string(inferirBase(num2)), "16");
    validarTeste("F8: Prefixo '0x' limpo da string", num2, "FF");

    cout << "\n=== FIM DOS TESTES ===\n";
    return 0;
}
