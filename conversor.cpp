#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

// =========================================================
// O "BOTÃO" LIGA/DESLIGA DO PASSO A PASSO
// =========================================================
bool modoPassoAPasso = false;

int inferirBase(string& num) {
    if (num.length() >= 2 && num[0] == '0') {
        char p = num[1];
        if (p == 'b' || p == 'B') { num.erase(0, 2); return 2; }
        if (p == 'o' || p == 'O') { num.erase(0, 2); return 8; }
        if (p == 'x' || p == 'X') { num.erase(0, 2); return 16; }
    }
    return 10; 
}

long long potenciaManual(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

int charParaValor(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

char valorParaChar(int v) {
    if (v >= 0 && v <= 9) return (char)(v + '0');
    return (char)(v - 10 + 'A');
}

void separarPartes(string num, string& intPart, string& fracPart) {
    size_t pos = num.find('.');
    if (pos == string::npos) pos = num.find(',');
    
    if (pos != string::npos) {
        intPart = num.substr(0, pos);
        fracPart = num.substr(pos + 1);
    } else {
        intPart = num;
        fracPart = "";
    }
}

// =========================================================
// CÁLCULOS COM PASSO A PASSO CONTROLADO
// =========================================================
long long baseParaDecimal(string numero, int baseOrigem) {
    long long total = 0;
    int tam = (int)numero.length(); 
    
    if (modoPassoAPasso && baseOrigem != 10) cout << "\n   [Passo a Passo] Convertendo parte inteira para Decimal (Soma de Pesos):\n   ";
    
    for (int i = 0; i < tam; i++) {
        long long parcela = charParaValor(numero[i]) * potenciaManual(baseOrigem, tam - 1 - i);
        total += parcela;
        
        if (modoPassoAPasso && baseOrigem != 10) {
            cout << numero[i] << "*" << baseOrigem << "^" << (tam - 1 - i);
            if (i < tam - 1) cout << " + ";
        }
    }
    if (modoPassoAPasso && baseOrigem != 10) cout << " = " << total << "\n";
    return total;
}

string decimalParaBase(long long decimal, int baseDestino) {
    if (decimal == 0) return "0";
    string res = "";
    long long temp = decimal;
    
    if (modoPassoAPasso && baseDestino != 10) cout << "\n   [Passo a Passo] Convertendo " << decimal << " para base " << baseDestino << " (Divisoes Sucessivas):\n";
    
    while (temp > 0) {
        int resto = temp % baseDestino;
        if (modoPassoAPasso && baseDestino != 10) cout << "   " << temp << " / " << baseDestino << " = " << (temp / baseDestino) << " (Resto: " << valorParaChar(resto) << ")\n";
        
        res += valorParaChar(resto);
        temp /= baseDestino;
    }
    reverse(res.begin(), res.end());
    
    if (modoPassoAPasso && baseDestino != 10) cout << "   Lendo os restos de baixo para cima: " << res << "\n";
    return res;
}

double stringParaDoubleBase(string num, int baseOrigem) {
    string intPart, fracPart;
    separarPartes(num, intPart, fracPart);
    
    double total = baseParaDecimal(intPart, baseOrigem);
    double divisor = baseOrigem;
    
    if (modoPassoAPasso && fracPart.length() > 0 && baseOrigem != 10) cout << "\n   [Passo a Passo] Convertendo fracao para Decimal:\n   ";
    
    for (char c : fracPart) {
        double parcela = charParaValor(c) / divisor;
        total += parcela;
        if (modoPassoAPasso && baseOrigem != 10) cout << c << "/" << divisor << " + ";
        divisor *= baseOrigem;
    }
    if (modoPassoAPasso && fracPart.length() > 0 && baseOrigem != 10) cout << "0 = " << total << "\n";
    
    return total;
}

string doubleParaStringBase(double num, int baseDestino, bool& truncado) {
    long long intPart = (long long)num;
    double fracPart = num - intPart;
    string res = decimalParaBase(intPart, baseDestino);
    
    if (fracPart > 0) {
        res += ".";
        string fracStr = "";
        int maxCasas = 16;
        truncado = false;
        
        if (modoPassoAPasso && baseDestino != 10) cout << "\n   [Passo a Passo] Multiplicacoes sucessivas da fracao por " << baseDestino << ":\n";
        
        while (fracPart > 0 && (int)fracStr.length() < maxCasas) {
            double original = fracPart;
            fracPart *= baseDestino;
            int digito = (int)fracPart;
            fracStr += valorParaChar(digito);
            
            if (modoPassoAPasso && baseDestino != 10) cout << "   " << original << " * " << baseDestino << " = " << fracPart << " (Inteiro extraido: " << valorParaChar(digito) << ")\n";
            
            fracPart -= digito;
        }
        if (fracPart > 0) truncado = true;
        res += fracStr;
    } else {
        truncado = false;
    }
    return res;
}

string binarioParaAgrupamento(string bin, int baseDestino) {
    string intPart, fracPart;
    separarPartes(bin, intPart, fracPart);
    int tamGrupo = (baseDestino == 8) ? 3 : 4;
    
    if (modoPassoAPasso) cout << "\n   [Passo a Passo] Agrupando binario em blocos de " << tamGrupo << " bits...\n";
    
    int restoInt = (int)intPart.length() % tamGrupo;
    if (restoInt != 0) {
        string zeros = "";
        for(int i = 0; i < (tamGrupo - restoInt); i++) zeros += "0";
        intPart = zeros + intPart;
    }
    
    int restoFrac = (int)fracPart.length() % tamGrupo;
    if (restoFrac != 0 && fracPart.length() > 0) {
        for(int i = 0; i < (tamGrupo - restoFrac); i++) fracPart += "0";
    }
    
    string resInt = "";
    for (size_t i = 0; i < intPart.length(); i += tamGrupo) {
        string bloco = intPart.substr(i, tamGrupo);
        char convertido = valorParaChar(baseParaDecimal(bloco, 2));
        if (modoPassoAPasso) cout << "   Bloco inteiro " << bloco << " -> " << convertido << "\n";
        resInt += convertido;
    }
    if (resInt == "") resInt = "0";

    string resFrac = "";
    for (size_t i = 0; i < fracPart.length(); i += tamGrupo) {
        string bloco = fracPart.substr(i, tamGrupo);
        char convertido = valorParaChar(baseParaDecimal(bloco, 2));
        if (modoPassoAPasso) cout << "   Bloco fracionario " << bloco << " -> " << convertido << "\n";
        resFrac += convertido;
    }
    
    if (resFrac.length() > 0) return resInt + "." + resFrac;
    return resInt;
}

string agrupamentoParaBinario(string num, int baseOrigem) {
    string intPart, fracPart;
    separarPartes(num, intPart, fracPart);
    int tamGrupo = (baseOrigem == 8) ? 3 : 4;
    
    if (modoPassoAPasso) cout << "\n   [Passo a Passo] Expandindo cada digito para " << tamGrupo << " bits...\n";
    
    string resInt = "";
    for (char c : intPart) {
        string bin = decimalParaBase(charParaValor(c), 2);
        while ((int)bin.length() < tamGrupo) bin = "0" + bin;
        if (modoPassoAPasso) cout << "   Digito " << c << " -> " << bin << "\n";
        resInt += bin;
    }
    while (resInt.length() > 1 && resInt[0] == '0') resInt.erase(0, 1);
    if (resInt == "") resInt = "0";

    string resFrac = "";
    for (char c : fracPart) {
        string bin = decimalParaBase(charParaValor(c), 2);
        while ((int)bin.length() < tamGrupo) bin = "0" + bin;
        if (modoPassoAPasso) cout << "   Digito " << c << " -> " << bin << "\n";
        resFrac += bin;
    }
    
    if (resFrac.length() > 0) return resInt + "." + resFrac;
    return resInt;
}

string octalHexaCruzado(string num, int baseOrigem, int baseDestino) {
    if (modoPassoAPasso) cout << "\n   [Passo a Passo] FASE 1: Converter para ponte (Binario)...";
    string binarioIntermediario = agrupamentoParaBinario(num, baseOrigem);
    
    if (modoPassoAPasso) cout << "\n   [Passo a Passo] FASE 2: Converter da ponte para o destino...\n";
    return binarioParaAgrupamento(binarioIntermediario, baseDestino);
}