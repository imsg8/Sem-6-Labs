#include "lexer.h"

int main() {
    struct token *tokenList = NULL;
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    processFile(filename, &tokenList);
    printTokens(tokenList);
    freeTokens(tokenList);

    return 0;
}
