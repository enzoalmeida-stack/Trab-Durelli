#include <string>

using namespace std;

int charParaValor(char c);

bool validarEntrada(string entrada, int base) {
    if (entrada.empty()) return false;
    int qtdVirgulas = 0;
    
    for (char c : entrada) {
        if (c == '.' || c == ',') {
            qtdVirgulas++;
            if (qtdVirgulas > 1) return false; 
            continue;
        }
        int v = charParaValor(c);
        if (v == -1 || v >= base) {
            return false; 
        }
    }
    return true;
}
