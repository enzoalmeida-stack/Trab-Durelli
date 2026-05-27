#include <iostream>
#include <string>
#include <algorithm> 
#include <cstdlib> 
#include <ctime>   

using namespace std;

// Declaramos que a variável do botão liga/desliga existe
extern bool modoPassoAPasso;

// Forward Declarations
void imprimirMenu();
void mostrarErro(string msg);
void mostrarResultado(string resultado, int base, bool truncado);
bool validarEntrada(string entrada, int base);

int inferirBase(string& num);
long long baseParaDecimal(string numero, int baseOrigem);
string decimalParaBase(long long decimal, int baseDestino);
double stringParaDoubleBase(string num, int baseOrigem);
string doubleParaStringBase(double num, int baseDestino, bool& truncado);
string binarioParaAgrupamento(string bin, int baseDestino);
string agrupamentoParaBinario(string num, int baseOrigem);
string octalHexaCruzado(string num, int baseOrigem, int baseDestino);

#include "conversor.cpp"
#include "parser.cpp"
#include "formatador.cpp"

int main() {
    srand(time(NULL)); 
    
    int opcao = -1;
    bool trunc;
    
    while (opcao != 0) {
        // MUITO IMPORTANTE: Desliga o passo a passo toda vez que o menu volta!
        // Assim ele não vaza no Quiz e nem nas outras opções.
        modoPassoAPasso = false; 
        
        imprimirMenu();
        cin >> opcao;

        if (opcao == 1) { 
            string dec; int bDest;
            cout << "\nNumero Decimal (Base 10): "; cin >> dec;
            cout << "Base de destino (2, 8 ou 16): "; cin >> bDest;
            if (validarEntrada(dec, 10) && (bDest == 2 || bDest == 8 || bDest == 16)) {
                mostrarResultado(doubleParaStringBase(stringParaDoubleBase(dec, 10), bDest, trunc), bDest, trunc);
            } else mostrarErro("Entrada ou base invalida!");

        } else if (opcao == 2) { 
            string num; int bOrig;
            cout << "\nBase de origem (2, 8 ou 16): "; cin >> bOrig;
            cout << "Numero na base " << bOrig << ": "; cin >> num;
            if (validarEntrada(num, bOrig)) {
                mostrarResultado(doubleParaStringBase(stringParaDoubleBase(num, bOrig), 10, trunc), 10, trunc);
            } else mostrarErro("Digitos invalidos para esta base!");

        } else if (opcao == 3) { 
            int tipo; string num;
            cout << "\n[1] Binario para Octal/Hexa\n[2] Octal/Hexa para Binario\nEscolha: "; cin >> tipo;
            if (tipo == 1) {
                int bDest;
                cout << "Numero Binario: "; cin >> num;
                cout << "Base de destino (8 ou 16): "; cin >> bDest;
                if (validarEntrada(num, 2) && (bDest == 8 || bDest == 16)) {
                    mostrarResultado(binarioParaAgrupamento(num, bDest), bDest, false);
                } else mostrarErro("Entrada invalida!");
            } else if (tipo == 2) {
                int bOrig;
                cout << "Base de origem (8 ou 16): "; cin >> bOrig;
                cout << "Numero: "; cin >> num;
                if (validarEntrada(num, bOrig) && (bOrig == 8 || bOrig == 16)) {
                    mostrarResultado(agrupamentoParaBinario(num, bOrig), 2, false);
                } else mostrarErro("Entrada invalida!");
            }

        } else if (opcao == 4) { 
            string num; int bOrig, bDest;
            cout << "\nConverter OCTAL e HEXA usando Binario como ponte\n";
            cout << "Base de origem (8 ou 16): "; cin >> bOrig;
            cout << "Numero: "; cin >> num;
            bDest = (bOrig == 8) ? 16 : 8; 
            if (validarEntrada(num, bOrig) && (bOrig == 8 || bOrig == 16)) {
                mostrarResultado(octalHexaCruzado(num, bOrig, bDest), bDest, false);
            } else mostrarErro("Entrada invalida!");

        } else if (opcao == 5) { 
            string num; int bOrig;
            cout << "\n--- DEMONSTRAR REQUISITO F5 ---\n";
            cout << "Base: "; cin >> bOrig;
            cout << "Numero: "; cin >> num;
            if (validarEntrada(num, bOrig)) cout << "\n[SUCESSO] VALIDO!\n";
            else mostrarErro("INVALIDO!");

        } else if (opcao == 6) { 
            string num; int bOrig, bDest;
            cout << "\n--- DEMONSTRAR REQUISITO F6 ---\n";
            cout << "Origem: "; cin >> bOrig;
            cout << "Destino: "; cin >> bDest;
            cout << "Numero com Virgula/Ponto: "; cin >> num;
            if (validarEntrada(num, bOrig)) {
                mostrarResultado(doubleParaStringBase(stringParaDoubleBase(num, bOrig), bDest, trunc), bDest, trunc);
            } else mostrarErro("Invalido!");

        } else if (opcao == 7) { // F7 AQUI!!!
            // Único local onde ligamos o "botão" do Passo a Passo!
            modoPassoAPasso = true; 
            
            string num; int bOrig, bDest;
            cout << "\n--- MODO PASSO A PASSO (F7) & BASES ARBITRARIAS ---\n";
            cout << "Origem (2 a 36): "; cin >> bOrig;
            cout << "Destino (2 a 36): "; cin >> bDest;
            cout << "Numero: "; cin >> num;
            if (bOrig >= 2 && bOrig <= 36 && bDest >= 2 && bDest <= 36 && validarEntrada(num, bOrig)) {
                mostrarResultado(doubleParaStringBase(stringParaDoubleBase(num, bOrig), bDest, trunc), bDest, trunc);
            } else mostrarErro("Invalido!");

        } else if (opcao == 8) { 
            string num; int bDest;
            cout << "\n--- DETECCAO AUTOMATICA ---\n";
            cout << "Prefixo (0b, 0o, 0x): "; cin >> num;
            cout << "Destino: "; cin >> bDest;
            int bOrig = inferirBase(num); 
            if (bDest >= 2 && bDest <= 36 && validarEntrada(num, bOrig)) {
                mostrarResultado(doubleParaStringBase(stringParaDoubleBase(num, bOrig), bDest, trunc), bDest, trunc);
            } else mostrarErro("Invalido!");

        } else if (opcao == 9) { // F9
            cout << "\n--- MODO QUIZ (F9) ---\n";
            int nivel;
            cout << "Escolha a dificuldade (1 a 5): "; cin >> nivel;
            if (nivel < 1 || nivel > 5) { mostrarErro("Nivel invalido!"); continue; }
            
            int pontuacao = 0;
            int basesSorteadas[] = {2, 8, 10, 16};
            
            for(int rodada = 1; rodada <= 3; rodada++) {
                long long max_val = 1;
                for(int i=0; i<nivel; i++) max_val *= 10; 
                if(nivel == 1) max_val = 15;
                
                long long valorSecretoDecimal = (rand() % max_val) + 1;
                int bOrig = basesSorteadas[rand() % 4];
                int bDest = basesSorteadas[rand() % 4];
                while(bOrig == bDest) bDest = basesSorteadas[rand() % 4];
                
                string pergunta = decimalParaBase(valorSecretoDecimal, bOrig);
                string respostaCorreta = decimalParaBase(valorSecretoDecimal, bDest);
                
                cout << "\nRodada " << rodada << "/3 | Converta o numero " << pergunta << " (Base " << bOrig << ") para a Base " << bDest << ":\n>> ";
                string respostaUsuario;
                cin >> respostaUsuario;
                
                for (auto &c : respostaUsuario) c = toupper(c);
                
                if(respostaUsuario == respostaCorreta) {
                    cout << "[CORRETO!] Voce ganhou 10 pontos!\n";
                    pontuacao += 10;
                } else {
                    cout << "[ERRADO] A resposta correta era: " << respostaCorreta << "\n";
                }
            }
            cout << "\nFIM DO QUIZ! Sua pontuacao final: " << pontuacao << " de 30 pontos.\n";

        } else if (opcao == 10) { // F10
            cout << "\n--- CALCULADORA DE MAXIMOS (F10) ---\n";
            int k;
            cout << "Digite a quantidade de bits (k): "; cin >> k;
            
            if (k < 1 || k > 60) {
                mostrarErro("Por favor, insira um k entre 1 e 60 bits para evitar estouro de memoria.");
            } else {
                string maiorBinario = "";
                for(int i = 0; i < k; i++) maiorBinario += "1";
                
                cout << "\nMaior valor representavel com " << k << " bits (2^k - 1):\n";
                cout << ">> Base 2 (Binario): " << maiorBinario << "\n";
                cout << ">> Base 8 (Octal):   " << binarioParaAgrupamento(maiorBinario, 8) << "\n";
                cout << ">> Base 16 (Hexa):   " << binarioParaAgrupamento(maiorBinario, 16) << "\n";
                cout << ">> Base 10 (Dec):    " << baseParaDecimal(maiorBinario, 2) << "\n";
            }

        } else if (opcao != 0) {
            mostrarErro("Opcao invalida.");
        }
    }
    cout << "Programa encerrado!\n";
    return 0;
}
