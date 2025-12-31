#include <stdio.h>

int countOneBits(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);   
        count++;
    }
    return count;
}

int main() {
    unsigned int num;

    printf("Enter a number: ");
    scanf("%u", &num);

    printf("Number of 1 bits = %d\n", countOneBits(num));

    return 0;
}
