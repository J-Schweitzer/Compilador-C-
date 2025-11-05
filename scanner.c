#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tipos de tokens
typedef enum {
    // Palavras reservadas
    TOKEN_IF, TOKEN_ELSE, TOKEN_INT, TOKEN_RETURN, 
    TOKEN_VOID, TOKEN_WHILE,
    
    // Identificadores e números
    TOKEN_ID, TOKEN_NUM,
    
    // Operadores e símbolos especiais
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_MULT, TOKEN_DIV,
    TOKEN_LT, TOKEN_LE, TOKEN_GT, TOKEN_GE,
    TOKEN_EQ, TOKEN_NE, TOKEN_ASSIGN,
    TOKEN_SEMICOLON, TOKEN_COMMA,
    TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_LBRACKET, TOKEN_RBRACKET,
    TOKEN_LBRACE, TOKEN_RBRACE,
    
    // Especiais
    TOKEN_EOF, TOKEN_ERROR
} TokenType;

// Estrutura do token
typedef struct {
    TokenType type;
    char lexeme[256];
    int line;
} Token;

// Variáveis globais
FILE *source;
int line_num = 1;
char current_char;

// Protótipos
void init_scanner(const char *filename);
char get_next_char();
void unget_char(char c);
Token get_token();
const char* token_type_to_string(TokenType type);
void skip_whitespace();
void skip_comment();

// Palavras reservadas
const char *keywords[] = {"if", "else", "int", "return", "void", "while"};
TokenType keyword_tokens[] = {TOKEN_IF, TOKEN_ELSE, TOKEN_INT, TOKEN_RETURN, TOKEN_VOID, TOKEN_WHILE};
int num_keywords = 6;

// Inicializa o scanner
void init_scanner(const char *filename) {
    source = fopen(filename, "r");
    if (source == NULL) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'\n", filename);
        exit(1);
    }
    current_char = ' ';
}

// Lê o próximo caractere
char get_next_char() {
    char c = fgetc(source);
    if (c == '\n') {
        line_num++;
    }
    return c;
}

// Devolve um caractere
void unget_char(char c) {
    if (c == '\n') {
        line_num--;
    }
    ungetc(c, source);
}

// Pula espaços em branco
void skip_whitespace() {
    while (isspace(current_char)) {
        current_char = get_next_char();
    }
}

// Pula comentários
void skip_comment() {
    if (current_char == '/') {
        char next = get_next_char();
        if (next == '*') {
            // Comentário de bloco
            current_char = get_next_char();
            char prev = ' ';
            while (!(prev == '*' && current_char == '/')) {
                if (current_char == EOF) {
                    return;
                }
                prev = current_char;
                current_char = get_next_char();
            }
            current_char = get_next_char(); // Pula o '/'
        } else {
            unget_char(next);
        }
    }
}

// Verifica se é palavra reservada
TokenType check_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return keyword_tokens[i];
        }
    }
    return TOKEN_ID;
}

// Obtém o próximo token
Token get_token() {
    Token token;
    token.line = line_num;
    token.lexeme[0] = '\0';
    
    // Pula espaços e comentários
    while (1) {
        skip_whitespace();
        if (current_char == '/') {
            char peek = get_next_char();
            if (peek == '*') {
                skip_comment();
            } else {
                unget_char(peek);
                break;
            }
        } else {
            break;
        }
    }
    
    // EOF
    if (current_char == EOF) {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }
    
    // Identificadores e palavras reservadas
    if (isalpha(current_char)) {
        int i = 0;
        while (isalnum(current_char)) {
            token.lexeme[i++] = current_char;
            current_char = get_next_char();
        }
        token.lexeme[i] = '\0';
        token.type = check_keyword(token.lexeme);
        return token;
    }
    
    // Números
    if (isdigit(current_char)) {
        int i = 0;
        while (isdigit(current_char)) {
            token.lexeme[i++] = current_char;
            current_char = get_next_char();
        }
        token.lexeme[i] = '\0';
        token.type = TOKEN_NUM;
        return token;
    }
    
    // Operadores e símbolos
    switch (current_char) {
        case '+':
            token.type = TOKEN_PLUS;
            sprintf(token.lexeme, "+");
            current_char = get_next_char();
            break;
        case '-':
            token.type = TOKEN_MINUS;
            sprintf(token.lexeme, "-");
            current_char = get_next_char();
            break;
        case '*':
            token.type = TOKEN_MULT;
            sprintf(token.lexeme, "*");
            current_char = get_next_char();
            break;
        case '/':
            token.type = TOKEN_DIV;
            sprintf(token.lexeme, "/");
            current_char = get_next_char();
            break;
        case '<':
            current_char = get_next_char();
            if (current_char == '=') {
                token.type = TOKEN_LE;
                sprintf(token.lexeme, "<=");
                current_char = get_next_char();
            } else {
                token.type = TOKEN_LT;
                sprintf(token.lexeme, "<");
            }
            break;
        case '>':
            current_char = get_next_char();
            if (current_char == '=') {
                token.type = TOKEN_GE;
                sprintf(token.lexeme, ">=");
                current_char = get_next_char();
            } else {
                token.type = TOKEN_GT;
                sprintf(token.lexeme, ">");
            }
            break;
        case '=':
            current_char = get_next_char();
            if (current_char == '=') {
                token.type = TOKEN_EQ;
                sprintf(token.lexeme, "==");
                current_char = get_next_char();
            } else {
                token.type = TOKEN_ASSIGN;
                sprintf(token.lexeme, "=");
            }
            break;
        case '!':
            current_char = get_next_char();
            if (current_char == '=') {
                token.type = TOKEN_NE;
                sprintf(token.lexeme, "!=");
                current_char = get_next_char();
            } else {
                token.type = TOKEN_ERROR;
                sprintf(token.lexeme, "!");
            }
            break;
        case ';':
            token.type = TOKEN_SEMICOLON;
            sprintf(token.lexeme, ";");
            current_char = get_next_char();
            break;
        case ',':
            token.type = TOKEN_COMMA;
            sprintf(token.lexeme, ",");
            current_char = get_next_char();
            break;
        case '(':
            token.type = TOKEN_LPAREN;
            sprintf(token.lexeme, "(");
            current_char = get_next_char();
            break;
        case ')':
            token.type = TOKEN_RPAREN;
            sprintf(token.lexeme, ")");
            current_char = get_next_char();
            break;
        case '[':
            token.type = TOKEN_LBRACKET;
            sprintf(token.lexeme, "[");
            current_char = get_next_char();
            break;
        case ']':
            token.type = TOKEN_RBRACKET;
            sprintf(token.lexeme, "]");
            current_char = get_next_char();
            break;
        case '{':
            token.type = TOKEN_LBRACE;
            sprintf(token.lexeme, "{");
            current_char = get_next_char();
            break;
        case '}':
            token.type = TOKEN_RBRACE;
            sprintf(token.lexeme, "}");
            current_char = get_next_char();
            break;
        default:
            token.type = TOKEN_ERROR;
            sprintf(token.lexeme, "%c", current_char);
            current_char = get_next_char();
            break;
    }
    
    return token;
}

// Converte tipo de token para string
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_IF: return "IF";
        case TOKEN_ELSE: return "ELSE";
        case TOKEN_INT: return "INT";
        case TOKEN_RETURN: return "RETURN";
        case TOKEN_VOID: return "VOID";
        case TOKEN_WHILE: return "WHILE";
        case TOKEN_ID: return "ID";
        case TOKEN_NUM: return "NUM";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_MULT: return "MULT";
        case TOKEN_DIV: return "DIV";
        case TOKEN_LT: return "LT";
        case TOKEN_LE: return "LE";
        case TOKEN_GT: return "GT";
        case TOKEN_GE: return "GE";
        case TOKEN_EQ: return "EQ";
        case TOKEN_NE: return "NE";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <arquivo_fonte>\n", argv[0]);
        return 1;
    }
    
    init_scanner(argv[1]);
    
    printf("========================================\n");
    printf("ANALISADOR LÉXICO - LINGUAGEM C-\n");
    printf("========================================\n");
    printf("Arquivo: %s\n\n", argv[1]);
    printf("%-6s %-15s %s\n", "Linha", "Tipo", "Lexema");
    printf("========================================\n");
    
    Token token;
    do {
        token = get_token();
        printf("%-6d %-15s %s\n", token.line, token_type_to_string(token.type), token.lexeme);
    } while (token.type != TOKEN_EOF);
    
    printf("========================================\n");
    
    fclose(source);
    return 0;
}