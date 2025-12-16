#include<stdio.h>


void print_binary(int n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}
int main(){
	int a,bv,c,num;
	a=0x2A;

	bv=1<<4;
	c=a|bv;
	printf("decimal:%d\n",c);
		printf("hexadecimal:0x%X\n",c);
			printf("binary:",c);
		print_binary(c);
		return 0;


}
