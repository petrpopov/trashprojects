#include <stdio.h>
#include <string.h>

#include "md2.h"
 
int main(int argc, char *argv[])
{
	int l = 3;
	unsigned char *mes1;
	mes1 = (unsigned char*)malloc(l*sizeof(unsigned char));
	strcpy(mes1, "piton");
	unsigned char hash[32];
	MD2Hash(mes1, l, hash);
	int i;
	for(i = 0; i < 32; i++)
		printf("%c", hash[i]);
	printf("\n");
	
	return 0;
}
