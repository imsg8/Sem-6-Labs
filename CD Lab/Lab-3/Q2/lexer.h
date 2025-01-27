#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct token {
    int row;
    int col;
    char type[32];
    struct token *next;
};

typedef enum {
    ID, NUM, STRING, KEYWORD, SYMBOL, OPERATOR
} TokenType;

const char *keywords[] = {"int", "float", "char", "return", "main", "if", "else", "while", "for", "void", NULL};

const char *symbols = "[]{}(),;";

struct token *createToken(int row, int col, const char *type);
void addToken(struct token **head, int row, int col, const char *type);
int isKeyword(const char *str);
int isSymbol(char c);
int isOperator(const char *str);
void processFile(const char *filename, struct token **head);
struct token *getNextToken(struct token **head);
void printTokens(struct token *head);
void freeTokens(struct token *head);

struct token *createToken(int row, int col, const char *type) {
    struct token *newToken = (struct token *)malloc(sizeof(struct token));
    newToken->row = row;
    newToken->col = col;
    strcpy(newToken->type, type);
    newToken->next = NULL;
    return newToken;
}

void addToken(struct token **head, int row, int col, const char *type) {
    struct token *newToken = createToken(row, col, type);
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
        printf("<%s,%d,%d> ", head->type, head->row, head->col);
        head = head->next;
    }
    printf("\n");
}

void processFile(const char *filename, struct token **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int row = 0;
    int inComment = 0;
    int inString = 0;

    while (fgets(line, sizeof(line), file)) {
        row++;
        int col = 0;
        struct token *lineTokens = NULL;

        for (int i = 0; line[i] != '\0'; i++) {
            char c = line[i];
            col++;

            if (inComment) {
                if (c == '*' && line[i + 1] == '/') {
                    inComment = 0;
                    i++;
                    col++;
                }
                continue;
            }

            if (inString) {
                if (c == '"') {
                    inString = 0;
                }
                continue;
            }

            if (c == '/' && line[i + 1] == '*') {
                inComment = 1;
                i++;
                col++;
                continue;
            }

            if (c == '/' && line[i + 1] == '/') {
                break;
            }

            if (c == '"') {
                inString = 1;
                continue;
            }

            if (isSymbol(c)) {
                char symbol[2] = {c, '\0'};
                addToken(&lineTokens, row, col, symbol);
            } else if (isdigit(c)) {
                char num[64] = {c};
                int j = 1;
                while (isdigit(line[i + 1])) {
                    num[j++] = line[++i];
                    col++;
                }
                num[j] = '\0';
                addToken(&lineTokens, row, col - j + 1, "num");
            } else if (isalpha(c) || c == '_') {
                char id[64] = {c};
                int j = 1;
                while (isalnum(line[i + 1]) || line[i + 1] == '_') {
                    id[j++] = line[++i];
                    col++;
                }
                id[j] = '\0';
                if (isKeyword(id)) {
                    addToken(&lineTokens, row, col - j + 1, "");
                } else {
                    addToken(&lineTokens, row, col - j + 1, "id");
                }
            } else if (isOperator(&line[i])) {
                char op[3] = {c, '\0', '\0'};
                if (isOperator(op) && isOperator(&line[i + 1])) {
                    op[1] = line[i + 1];
                    if (isOperator(op)) {
                        i++;
                        col++;
                    }
                }
                addToken(&lineTokens, row, col, "");
            }
        }

        printTokens(lineTokens);
        freeTokens(lineTokens);
    }

    fclose(file);
}


struct token *getNextToken(struct token **head) {
    if (*head == NULL) return NULL;
    struct token *nextToken = *head;
    *head = (*head)->next;
    return nextToken;
}

void freeTokens(struct token *head) {
    struct token *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
