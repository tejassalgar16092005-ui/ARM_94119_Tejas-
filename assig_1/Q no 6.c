#include <stdio.h>

void swapXOR(int *a, int *b) {
    if (a != b) { 
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

int main() {
    int x, y;
    printf("Enter two numbers: ");
    scanf("%d %d", &x, &y);

    printf("Before swapping: x = %d, y = %d\n", x, y);

    swapXOR(&x, &y);

    printf("After swapping: x = %d, y = %d\n", x, y);

    return 0;
}
