#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool isDelimiter(char ch) {
    char delimiters[] = {' ', '+', '-', '*', '/', ',', ';', '>', '<', '=', '(', ')', '[', ']', '{', '}'};
    for (int i = 0; i < sizeof(delimiters) / sizeof(delimiters[0]); i++) {
        if (ch == delimiters[i])
            return true;
    }
    return false;
}

bool isOperator(char ch) {
    char operators[] = {'+', '-', '*', '/', '>', '<', '='};
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (ch == operators[i])
            return true;
    }
    return false;
}

bool validIdentifier(char* str) {
    char invalidStartingChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    if (str[0] >= '0' && str[0] <= '9')
        return false;

    for (int i = 0; i < sizeof(invalidStartingChars) / sizeof(invalidStartingChars[0]); i++) {
        if (str[0] == invalidStartingChars[i])
            return false;
    }
    return true;
}

bool isKeyword(char* str) {
    char* keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return",
                        "char", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void",
                        "static", "struct", "goto"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (!strcmp(str, keywords[i]))
            return true;
    }
    return false;
}

bool isInteger(char* str) {
    int len = strlen(str);
    if (len == 0)
        return false;

    for (int i = 0; i < len; i++) {
        if (!(str[i] >= '0' && str[i] <= '9') || (str[i] == '-' && i > 0))
            return false;
    }
    return true;
}

bool isRealNumber(char* str) {
    int len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return false;

    for (int i = 0; i < len; i++) {
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.' || (str[i] == '-' && i > 0))
            return false;
        if (str[i] == '.')
            hasDecimal = true;
    }
    return hasDecimal;
}

char* subString(char* str, int left, int right) {
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (int i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return subStr;
}

void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right]))
            right++;

        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right]))
                printf("'%c' IS AN OPERATOR\n", str[right]);

            right++;
            left = right;
        } else if ((isDelimiter(str[right]) && left != right) || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr))
                printf("'%s' IS A KEYWORD\n", subStr);
            else if (isInteger(subStr))
                printf("'%s' IS AN INTEGER\n", subStr);
            else if (isRealNumber(subStr))
                printf("'%s' IS A REAL NUMBER\n", subStr);
            else if (validIdentifier(subStr) && !isDelimiter(str[right - 1]))
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
            else if (!validIdentifier(subStr) && !isDelimiter(str[right - 1]))
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);

            left = right;
        }
    }
    return;
}

int main() {
    printf("Enter multiple lines of code (Enter 'exit' to end):\n");
    char input[5000] = "";
    char line[1000];

    while (strcmp(line, "exit\n") != 0 && strlen(input) < sizeof(input) - sizeof(line)) {
        fgets(line, sizeof(line), stdin);
        strcat(input, line);
    }

    parse(input);

    return 0;
}
