#include <stdio.h>

char xorWith32IfAlphabet(char ch) {
    
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        char result = ch ^ 32; 
        printf("'%c' is an alphabet. After XOR with 32: '%c'\n", ch, result);
        return result;
    } else {
        printf("'%c' is not an alphabet.\n", ch);
        return ch;
    }
}

int main() {
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);

    xorWith32IfAlphabet(ch);

    return 0;
}
