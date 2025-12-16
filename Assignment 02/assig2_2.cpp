#include<stdio.h>
 void print_binary(int n){
 	for( int i=7;i>=0;i--){
 		printf("%d",(n>>i)&1);
	 }
 }
 int main(){
 	int a,bv,c;
 	a=0x2A;
 	bv=1<<5;
 	c=a^bv;
 	printf(" in decimal:%d\n",c);
 	printf(" in hexadeciml:0x%X\n",c);
 	printf("in binary:");
 	print_binary(c);
 }
