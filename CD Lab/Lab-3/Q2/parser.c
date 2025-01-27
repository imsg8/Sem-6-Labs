#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
    struct token *tokenList = NULL;
    char filename[100];

    printf("Enter the filename to parse: ");
    scanf("%s", filename);

    processFile(filename, &tokenList);

    freeTokens(tokenList);
    return 0;
}
