# Conversor Universal de Sistemas de Numeração
### Trabalho Prático 1 — Disciplina: GCC241 (Introdução à Computação)
**Departamento de Ciência da Computação — DCC/UFLA** **Turma:** 14A (2026/1) | 1º Período — Sistemas de Informação  
**Professor:** Dr. Rafael Serapilha Durelli  

---

## 👥 Integrantes da Dupla
* **Gilbran Guimarães Salem** — Matrícula: `202610132`
* **Enzo Ribeiro Almeida** — Matrícula: `202611181`

---

## 📝 Descrição do Projeto
Este projeto consiste no desenvolvimento de um **Conversor Universal de Sistemas de Numeração** robusto via CLI (Interface de Linha de Comando) utilizando a linguagem **C++**. O sistema realiza conversões matemáticas precisas entre diversas bases numéricas, tratando tanto números inteiros quanto fracionários, com ênfase nas bases Decimal (10), Binária (2), Octal (8) e Hexadecimal (16).

### 🚫 Restrição Central (Garantia de Autoria e Ética)
Em total conformidade com as diretrizes rígidas estabelecidas pelo professor no PDF do projeto, **é terminantemente proibido e foi completamente evitado** o uso de quaisquer funções, métodos integrados ou máscaras prontas da linguagem que efetuem conversões automáticas entre bases (como `std::stoi` com argumento de base, `std::bitset`, `strtol` ou especificadores de formatação do `printf` como `%x` e `%o`). 

Todos os algoritmos matemáticos foram concebidos e codificados puramente do zero pela dupla através de aritmética elementar (`+`, `-`, `*`, `/`, `%`), laços de repetição, mapeamentos manuais em tabelas ASCII e manipulação direta de strings de texto caractere a caractere.

---

## 🚀 Funcionalidades Implementadas

A aplicação cobre com sucesso os requisitos funcionais estabelecidos no escopo do projeto, além de incorporar os desafios opcionais propostos pelo docente:

* **F1 (Decimal → Outras Bases):** Conversão de números inteiros decimais para as bases 2, 8 e 16 utilizando o método matemático estrito de divisões sucessivas, acumulando e invertendo os restos obtidos.
* **F2 (Outras Bases → Decimal):** Conversão de bases (2, 8 e 16) de volta para a base decimal por meio do somatório posicional acumulado com pesos multiplicativos baseados em potências.
* **F3 (Pontes Diretas por Agrupamento):** Conversão de Binário → Octal (agrupamento em blocos simétricos de 3 bits) e Binário → Hexadecimal (blocos de 4 bits), além de seus fluxos inversos de expansão, operando **sem realizar conversão intermediária para a base decimal**.
* **F4 (Conversão Octal ↔ Hexadecimal):** Conversão cruzada bidirecional entre as bases 8 e 16, empregando exclusivamente a base binária como ponte e intermediária de dados através de rotinas de expansão e agrupamento conjugadas.
* **F5 (Validação Robusta de Entradas):** Sistema de parsing que varre a string em tempo de execução para garantir que o número pertença ao alfabeto estrito da base de origem (ex: rejeita o dígito `8` se a origem for Octal ou caracteres além de `F` em Hexadecimal), gerando avisos estruturados em caso de falha.
* **F6 (Suporte Integral a Fracionários):** Processamento de números reais contendo separadores flutuantes (ponto ou vírgula) em todas as bases. A conversão fracionária aplica multiplicações sucessivas com limite técnico de precisão fixado em **16 casas decimais**, exibindo um alerta explícito (`TRUNCADO`) em tela caso a dízima exceda essa extensão.
* **F7 (Modo Passo a Passo / Trace):** Recurso didático interativo (acionado na opção `[7]`) que exibe de forma detalhada o *trace* do algoritmo na tela, detalhando tabelas de divisões, restos, multiplicação de pesos posicionais e preenchimentos de bits em tempo real.
* **Desafio Opcional 1 — Bases Arbitrárias (2 a 36):** Acoplado nativamente ao fluxo do Modo Passo a Passo, o núcleo de cálculo estende os algoritmos puramente matemáticos para realizar conversões customizadas entre qualquer intervalo de base de 2 a 36, mapeando os símbolos alfa-numéricos de `0-9` e letras de `A-Z`.
* **Desafio Opcional 2 — Detecção Automática de Base:** Função inteligente integrada na opção `[8]` do menu que inspeciona a string de entrada informada e infere a base de origem através de prefixos padronizados de mercado (`0b` para Binário, `0o` para Octal e `0x` para Hexadecimal), tratando e limpando os metacaracteres para a execução matemática direta.
* **F9 (Modo Quiz Interativo):** Jogo de perguntas e respostas integrado via console com 5 níveis crescentes de magnitude. Sorteia dinamicamente valores, solicita a conversão entre bases aleatórias e computa a pontuação acumulada do usuário ao longo de 3 rodadas consecutivas.
* **F10 (Calculadora de Máximos):** Computa e exibe de maneira simultânea nas 4 bases o maior valor inteiro representável ($2^k - 1$) utilizando uma quantidade $k$ de bits informada pelo usuário, implementando validações contra estouro de memória física (`long long` estabilizado para até 60 bits).

---

## 🛠️ Tecnologias e Arquitetura Modular

O projeto adota uma arquitetura de separação de conceitos através de módulos de arquivos integrados, utilizando apenas recursos nativos da biblioteca padrão do C++ (`<iostream>`, `<string>`, `<algorithm>`, `<cstdlib>`, `<ctime>`), livre de quaisquer dependências externas adicionais.

### 📂 Organização dos Módulos
* `main6.cpp`: O ponto de entrada principal (`main`) da aplicação. Gerencia o loop de eventos da CLI, renderiza as opções do menu de controle e limpa o estado lógico do passo a passo a cada iteração para evitar vazamento de contexto.
* `conversor.cpp`: O núcleo matemático do sistema. Centraliza a flag global `modoPassoAPasso` e implementa de forma pura os algoritmos de divisões, multiplicações fracionárias, agrupamentos de bits e controle de potências manuais.
* `parser.cpp`: Camada de segurança e validação responsável por inspecionar a integridade das strings, computar separadores de ponto flutuante e validar os caracteres permitidos na base de entrada.
* `formatador.cpp`: Camada de visualização encarregada de exibir as tabelas textuais de menu, estruturar mensagens de erro amigáveis e formatar saídas com sinalização de truncamentos de precisão.
* `testes.cpp`: Módulo de verificação autônomo contendo a suíte de testes unitários automatizados para checagem rápida de regressão dos componentes cruciais do sistema.

---

## 🔧 Como Compilar e Executar

### Pré-requisitos
* Compilador C++ atualizado compatível com o padrão C++11 ou superior (ex: `g++` do pacote GCC ou `clang`).
* Ambiente de Terminal (Console Linux, Terminal macOS ou Prompt de Comando/PowerShell no Windows configurado com MinGW).

### 🛠️ Compilação do Programa Principal
Para compilar o ecossistema completo do conversor a partir de seu ponto de entrada, execute o seguinte comando no seu terminal:
```bash
g++ -O2 main6.cpp -o conversor_universal