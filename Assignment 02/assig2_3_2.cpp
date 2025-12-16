#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t reg = 0xABCD;
    uint8_t lower4;
    lower4 = reg & 0xF0;  
 printf("Lower 4 bits = 0x%X\n", lower4);
    return 0;
}
