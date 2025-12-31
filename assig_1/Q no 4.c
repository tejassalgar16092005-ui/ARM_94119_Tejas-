#include <stdio.h>

unsigned char makeEvenParity(unsigned char byte) {
    int count = 0;

    
    
    for (int i = 0; i < 8; i++) {
        if (byte & (1 << i))
            count++;
    }

    
    if (count % 2 != 0)
        byte |= 0x80;   

    return byte;
}

int main() {
    unsigned char value;

    printf("Enter a byte (0-255): ");
    scanf("%hhu", &value);

    unsigned char result = makeEvenParity(value);

    printf("Resulting byte with even parity: %u\n", result);

    return 0;
}
