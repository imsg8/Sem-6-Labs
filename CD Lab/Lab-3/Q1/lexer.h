#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct token {
    int lineno;
    int colno;
    char lexemeName[64];
    struct token *next;
};

typedef enum {
    ID, NUM, STRING, KEYWORD, SYMBOL, OPERATOR
} TokenType;

const char *keywords[] = {"int", "float", "char", "return", "main", "if", "else", "while", "for", "void", NULL};

const char *symbols = "[]{}(),;";

struct token *createToken(int lineno, int colno, const char *lexemeName);
void addToken(struct token **head, int lineno, int colno, const char *lexemeName);
int isKeyword(const char *str);
int isSymbol(char c);
int isOperator(const char *str);
void processFile(const char *filename, struct token **head);
void printTokens(struct token *head);
void freeTokens(struct token *head);

struct token *createToken(int lineno, int colno, const char *lexemeName) {
    struct token *newToken = (struct token *)malloc(sizeof(struct token));
    newToken->lineno = lineno;
    newToken->colno = colno;
    strcpy(newToken->lexemeName, lexemeName);
    newToken->next = NULL;
    return newToken;
}

void addToken(struct token **head, int lineno, int colno, const char *lexemeName) {
    struct token *newToken = createToken(lineno, colno, lexemeName);
    if (*head == NULL) {
        *head = newToken;
    } else {
        struct token *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newToken;
    }
}

int isKeyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isSymbol(char c) {
    return strchr(symbols, c) != NULL;
}

int isOperator(const char *str) {
    const char *operators[] = {"+", "-", "*", "/", "%", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "=", NULL};
    for (int i = 0; operators[i] != NULL; i++) {
        if (strcmp(str, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void printTokens(struct token *head) {
    while (head != NULL) {
        printf("<%s,%d,%d> ", head->lexemeName, head->lineno, head->colno);
        head = head->next;
    }
    printf("\n");
}

void freeTokens(struct token *head) {
    struct token *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void processFile(const char *filename, struct token **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int lineno = 0;

    while (fgets(line, sizeof(line), file)) {
        lineno++;
        int colno = 1;
        char *token = strtok(line, " \t\n");
        struct token *lineTokens = NULL;
        while (token != NULL) {
            if (isKeyword(token)) {
                addToken(&lineTokens, lineno, colno, "");
            } else if (isOperator(token)) {
                addToken(&lineTokens, lineno, colno, "");
            } else if (isdigit(token[0])) {
                addToken(&lineTokens, lineno, colno, "num");
            } else if (token[0] == '"') {
                addToken(&lineTokens, lineno, colno, "");
            } else if (isSymbol(token[0])) {
                char symbol[2] = {token[0], '\0'};
                addToken(&lineTokens, lineno, colno, symbol);
            } else {
                addToken(&lineTokens, lineno, colno, "id");
            }
            token = strtok(NULL, " \t\n");
            colno++;
        }
        printTokens(lineTokens);
        freeTokens(lineTokens);
    }

    fclose(file);
}
