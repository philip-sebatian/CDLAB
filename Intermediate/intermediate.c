#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
char keywords[10][10] = {"int", "float", "if", "else", "while", "return", "for"};

int isKeyword(char *word) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(keywords[i], word) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, token[50];
    int i;

    fp = fopen("input.txt", "r"); // open file for reading
    if (fp == NULL) {
        printf("Error: cannot open file.\n");
        return 1;
    }

    printf("Tokens:\n");

    while ((ch = fgetc(fp)) != EOF) {
        // Skip whitespace
        if (isspace(ch))
            continue;

        // Identify identifiers or keywords
        if (isalpha(ch)) {
            i = 0;
            token[i++] = ch;
            ch = fgetc(fp);
            while (isalnum(ch) || ch == '_') {
                token[i++] = ch;
                ch = fgetc(fp);
            }
            token[i] = '\0';
            fseek(fp, -1, SEEK_CUR); // go one character back

            if (isKeyword(token))
                printf("<KEYWORD, %s>\n", token);
            else
                printf("<IDENTIFIER, %s>\n", token);
        }

        // Identify numbers
        else if (isdigit(ch)) {
            i = 0;
            token[i++] = ch;
            ch = fgetc(fp);
            while (isdigit(ch)) {
                token[i++] = ch;
                ch = fgetc(fp);
            }
            token[i] = '\0';
            fseek(fp, -1, SEEK_CUR);
            printf("<NUMBER, %s>\n", token);
        }

        // Identify operators
        else if (strchr("+-*/=<>", ch)) {
            printf("<OPERATOR, %c>\n", ch);
        }

        // Identify separators and symbols
        else if (strchr(";,(){}", ch)) {
            printf("<SYMBOL, %c>\n", ch);
        }

        // Unknown or unsupported characters
        else {
            printf("<UNKNOWN, %c>\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
