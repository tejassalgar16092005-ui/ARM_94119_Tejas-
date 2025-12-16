#include<stdio.h>
 void print_binary(	int n){
 
 	for(int i=0;i>=0;i--){
 		printf("%d",(n>>i)&1);
	 }
 	
 }
 int main(){
 	int a,bv,c;
 	a=0x2A;
 	bv=1<<1;
 	c=a&~(bv);
 	printf(" in decimal:%d\n",c);
 	printf(" in hexadecimal:0x%X \n",c);
 	printf("in decimal:",c);
 	print_binary(c);
 }
