#include <stdio.h>

void printBinary(unsigned int n) {
    int i;
    
    for (i = 31; i >= 0; i--) {
        unsigned int bit = (n >> i) & 1;
        printf("%u", bit);
    }
    printf("\n");
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);

    printBinary(num);
    return 0;
}
