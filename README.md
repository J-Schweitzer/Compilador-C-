# Scanner para Linguagem C-

Um analisador léxico (scanner) completo para a linguagem C-, desenvolvido em C. O programa identifica e classifica todos os tokens da linguagem, exibindo tipo e lexema de cada marca reconhecida.

## 📋 Descrição

Este projeto implementa a primeira fase de um compilador: a análise léxica. O scanner lê um arquivo fonte em C- e quebra o código em tokens (marcas), identificando palavras reservadas, identificadores, números, operadores e símbolos especiais.

## ✨ Funcionalidades

- **Palavras Reservadas**: `if`, `else`, `int`, `return`, `void`, `while`
- **Identificadores**: sequências alfanuméricas iniciadas por letra
- **Números**: sequências de dígitos
- **Operadores Aritméticos**: `+`, `-`, `*`, `/`
- **Operadores Relacionais**: `<`, `<=`, `>`, `>=`, `==`, `!=`
- **Operador de Atribuição**: `=`
- **Delimitadores**: `;`, `,`, `(`, `)`, `[`, `]`, `{`, `}`
- **Comentários**: `/* ... */` (ignorados durante análise)
- **Contagem de Linhas**: rastreamento da posição de cada token

## 🚀 Como Usar

### Compilação

**Linux/macOS:**
```bash
gcc -o scanner scanner.c
```

**Windows (MinGW/GCC):**
```bash
gcc -o scanner.exe scanner.c
```

**Windows (Visual Studio):**
```bash
cl scanner.c
```

### Execução

**Linux/macOS:**
```bash
./scanner arquivo.cm
```

**Windows:**
```bash
scanner.exe arquivo.cm
```

## 📝 Exemplo de Uso

### Arquivo de entrada (`teste.cm`):
```c
int fatorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * fatorial(n - 1);
    }
}

int main(void) {
    int x;
    x = 5;
    return fatorial(x);
}
```

### Comando:
```bash
./scanner teste.cm
```

## 🛠️ Estrutura do Código

```
scanner.c
├── Tipos de Tokens (TokenType enum)
├── Estrutura Token
├── Funções principais:
│   ├── init_scanner()      - Inicializa o scanner
│   ├── get_token()         - Obtém próximo token
│   ├── skip_whitespace()   - Ignora espaços
│   ├── skip_comment()      - Ignora comentários
│   └── check_keyword()     - Verifica palavras reservadas
└── main()                  - Função principal
```

## 📊 Tipos de Tokens

| Categoria | Tokens |
|-----------|--------|
| Palavras Reservadas | `if`, `else`, `int`, `return`, `void`, `while` |
| Identificadores | `ID` |
| Literais | `NUM` |
| Operadores Aritméticos | `+`, `-`, `*`, `/` |
| Operadores Relacionais | `<`, `<=`, `>`, `>=`, `==`, `!=` |
| Atribuição | `=` |
| Pontuação | `;`, `,` |
| Delimitadores | `(`, `)`, `[`, `]`, `{`, `}` |

## 🔍 Gramática da Linguagem C-

A linguagem C- é um subconjunto simplificado de C, contendo:
- Dois tipos de dados: `int` e `void`
- Estruturas de controle: `if-else` e `while`
- Funções com parâmetros
- Arrays unidimensionais
- Operações aritméticas e relacionais
- Comentários de bloco

## ⚙️ Requisitos

- Compilador C (GCC, Clang, MSVC)
- Sistema operacional: Linux, macOS, Windows

## 📚 Referências

- Louden, Kenneth C. "Compiler Construction: Principles and Practice"
- Aho, Alfred V. et al. "Compilers: Principles, Techniques, and Tools" (Dragon Book)
