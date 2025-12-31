#include <stdio.h>
#include <stdlib.h>

void printBinary(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%u", (n >> i) & 1);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    unsigned int num = (unsigned int)atoi(argv[1]);
    printBinary(num);
    return 0;
}
