#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int MurmurHash3 (const void *key, int len) {
    int h1 = 42;
    const unsigned char *data = (const unsigned char *)key;
    const int nblocks = len / 4;
    for (int i = 0; i < nblocks; i++) {
        int k1 = *((int *)(data + i * 4));
        k1 *= 0xcc9e2d51;
        k1 = (k1 << 15) | (k1 >> 17); 
        k1 *= 0x1b873593;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> 19);
        h1 = h1 * 5 + 0xe6546b64;
    }
    const unsigned char *tail = data + nblocks * 4;
    int k1 = 0;
    switch (len & 3) {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
                k1 *= 0xcc9e2d51;
                k1 = (k1 << 15) | (k1 >> 17);
                k1 *= 0x1b873593;
                h1 ^= k1;
    }
    h1 ^= len;
    h1 = (h1 ^ (h1 >> 16)) * 0x85ebca6b;
    h1 = (h1 ^ (h1 >> 13)) * 0xc2b2ae35;
    h1 = h1 ^ (h1 >> 16);

    return h1;
}

typedef struct token{
	char token_name[50];
	unsigned int row, col;
	char token_type[50];
}tk;

typedef struct symbol{
    char name[50];
    char type[30];
    int size;
    struct symbol* next;
}sy;

int d_size=0;
char dbuf[30]="";
typedef struct {
    char type_name[30];  
    int size;         
} DataType;
DataType data_types[] = {
    {"int", 4},
    {"float", 4},
    {"double", 8},
    {"char", 1},
    {"void", 0},  
    {"long", 8},  
    {"short", 2},
    {"unsigned", 4}
};
void updateDataTypeSize(const char* type_name) {
    int num_types = sizeof(data_types) / sizeof(data_types[0]);
    
    for (int i = 0; i < num_types; i++) {
        if (strcmp(data_types[i].type_name, type_name) == 0) {
            strcpy(dbuf,data_types[i].type_name);
            d_size=data_types[i].size;
        }
    }
}


sy* symbol_table[10]={NULL};
int k=1;

int getNextchar(FILE* fp, int* row, int* col){
	int c = getc(fp);

	*col = *col + 1;
	if(c=='\n'){
		*row = *row + 1;
		*col = 0;
	}
	return c;
}

int isSymbol(char c) {
    char symbols[] = "+-*/%=<>&|^!~(){}[],;";
    for (int i = 0; i < strlen(symbols); i++) {
        if (c == symbols[i]) {
            return 1;
        }
    }
    return 0;
}

int isKeyword(const char *str) {
    const char *keywords[] = {"break", "for", "if"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isfunction(const char *str) {
    const char *funcs[] = {"isset", "echo"};
    int funsize = sizeof(funcs) / sizeof(funcs[0]);
    for (int i = 0; i < funsize; i++) {
        if (strcmp(str, funcs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int row=1;
int col=0;

tk getNextToken(FILE* fp) {
    int c;
    int isDirective = 0;
    tk token;
    c = getNextchar(fp, &row, &col);

    while (1) {

        if (c == '/') {
            int cb;
            cb = getNextchar(fp, &row, &col);
            if (cb == '/') {
                while (cb != '\n') cb = getNextchar(fp, &row, &col);
                c = cb;
            } else if (cb == '*') {
                do {
                    while (c != '*') c = getNextchar(fp, &row, &col);
                    c = getNextchar(fp, &row, &col);
                } while (c != '/');
            }
        }


        if(c == EOF){
            break;
        }

        // if (c == '<'){
        //     while(c != '/n')
        //     c = getNextchar(fp, &row, &col);
        // }

        // if (c == '?'){
        //     while(c != '/n' || c != EOF)
        //         c = getNextchar(fp, &row, &col);
        //     break;
        // }

        if (c == '$') {
            int cb;
            int i = 0;
            char buf[100];
            cb = getNextchar(fp, &row, &col);
            while(isalnum(cb)){
                buf[i++] = cb;
            }
            strcpy(token.token_type, "id");
            strcpy(token.token_name, "buf");
            return token;
        }

        // Check for whitespace and discard it
        if (c == ' ' || c == '\t') {
            c = getNextchar(fp, &row, &col);
            while (c == ' ' || c == '\t') c = getNextchar(fp, &row, &col);
        }

        if (c >= '0' && c <= '9') {
            token.row = row;
            token.col = col;
            int i = 0;
            while (c >= '0' && c <= '9') {
                token.token_name[i++] = c;
                c = getNextchar(fp, &row, &col);
            }
            ungetc(c, fp);
            col--;
            token.token_name[i] = '\0';
            strcpy(token.token_type, "num");
            return token;
        }

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            token.row = row;
            token.col = col;
            int i = 0;
            while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                token.token_name[i++] = c;
                c = getNextchar(fp, &row, &col);
            }
            ungetc(c, fp);
            col--;
            token.token_name[i] = '\0';

            if (isKeyword(token.token_name)) {
                strcpy(token.token_type, "Keyword");
            } else if(isfunction(token.token_name)){
                strcpy(token.token_type, "Function");
            } else{
                strcpy(token.token_type, "id");
            }
            }

            return token;

        if (isSymbol(c)) {
            token.row = row;
            token.col = col;
            token.token_name[0] = c;
            if (c == '=' || c == '<' || c == '>' || c == '!') {
                int nextChar = getNextchar(fp, &row, &col);
                if (nextChar == '=') {
                    token.token_name[1] = nextChar;
                    token.token_name[2] = '\0';

                    if (c == '=') strcpy(token.token_type, "EQUALS");
                    if (c == '<') strcpy(token.token_type, "LESSTHAN_EQ");
                    if (c == '>') strcpy(token.token_type, "GREATERTHAN_EQ");
                    if (c == '!') strcpy(token.token_type, "NOT_EQ");

                    return token;
                } else {
                    ungetc(nextChar, fp);
                    col--;
                    token.token_name[1] = '\0';
                    if(c=='=') strcpy(token.token_type,"=");
                    if (c == '<') strcpy(token.token_type, "LESSTHAN");
                    if (c == '>') strcpy(token.token_type, "GREATERTHAN");
                    if (c == '!') strcpy(token.token_type, "NOT");
                    return token;
                }
            }else{
                token.token_name[1] = '\0';
                token.token_type[0] = c;
                token.token_type[1] = '\0';
            }
            return token;
        }
    }
    
    token.token_name[0] = '\0';
    return token;
}


int main(){
    int prev_index;
	FILE *fp;
	fp = fopen("input.php", "r");
	if(fp==NULL){
		printf("Cannot open file\n");
		exit(0);
	}
	tk temp;
    int flag=0;
	while(1){
		temp = getNextToken(fp);
		if(temp.token_name[0]=='\0')
			break;
        if(strcmp(temp.token_type,"[")==0)
            flag=1;
        if((strcmp(temp.token_type,"num")==0)&&(flag==1)){
            sy* temppp=symbol_table[prev_index];
            while(temppp->next!=NULL)
                temppp=temppp->next;
            temppp->size=d_size*atoi(temp.token_name);
            flag=0;
        }
        if(strcmp(temp.token_type,"id")==0){
            snprintf(temp.token_type + strlen(temp.token_type), sizeof(temp.token_type) - strlen(temp.token_type), "%d", k);
            k++;
            int hash=MurmurHash3(temp.token_name,strlen(temp.token_name));
            int index=hash%10;
            printf("%d\t",index);
            sy* helper=symbol_table[index];
            sy* tempp=(sy*)malloc(sizeof(sy));
            int yes=1;
            if(helper!=NULL){
                sy* prev;
                while(helper!=NULL){
                    if(strcmp(helper->name,temp.token_name)==0){
                        yes=0;
                    }
                    prev=helper;
                    helper=helper->next;
                }
                if(yes==1)
                    prev->next=tempp;
            }
            if(yes==1){
                if(helper==NULL){
                    symbol_table[index]=tempp;
                }
                strcpy(tempp->name,temp.token_name);
                strcpy(tempp->type,dbuf);
                tempp->size=d_size;
                tempp->next=NULL;
                prev_index=index;
            }
        }
        updateDataTypeSize(temp.token_name);
		printf("<%s,%d,%d,%s>\n", temp.token_type, temp.row, temp.col,temp.token_name);
	}
	fclose(fp);
    printf("-----------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%d\n", i);
        if(symbol_table[i] != NULL) {  
            sy* temp = symbol_table[i];
            while (temp != NULL) {  
                printf("<%s, %s, %d>\n", temp->name, temp->type, temp->size);
                temp = temp->next; 
            }
        }
    }
	return 0;
}