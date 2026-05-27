#include <iostream>
#include <string>

using namespace std;

void imprimirMenu() {
    cout << "\n========================================\n";
    cout << "      CONVERSOR UNIVERSAL DE BASES      \n";
    cout << "========================================\n";
    cout << "[1] Decimal -> Outras Bases (F1)\n";
    cout << "[2] Outras Bases -> Decimal (F2)\n";
    cout << "[3] Binario <-> Octal/Hexa Agrupamento (F3)\n";
    cout << "[4] Octal <-> Hexa usando Binario como ponte (F4)\n";
    cout << "[5] Demonstrar Validacao de Entrada (F5)\n";
    cout << "[6] Demonstrar Numeros Fracionarios (F6)\n";
    cout << "[7] Bases Arbitrarias (2 a 36) / Passo a Passo\n";
    cout << "[8] Deteccao Automatica (0b, 0o, 0x)\n";
    cout << "[9] Modo Quiz: Teste seus conhecimentos (F9)\n";
    cout << "[10] Calculadora de Maximos de k bits (F10)\n";
    cout << "[0] Sair\n";
    cout << "Opcao: ";
}

void mostrarErro(string msg) {
    cout << "\n[ERRO] " << msg << "\n";
}

void mostrarResultado(string resultado, int base, bool truncado) {
    cout << "\n>> Resultado na base " << base << ": " << resultado;
    if (truncado) cout << " (TRUNCADO em 16 casas - Regra F6)";
    cout << "\n";
}
