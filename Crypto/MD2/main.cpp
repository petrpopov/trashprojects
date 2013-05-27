#include <stdio.h>
#include <string.h>

#include "md2.h"

int main(int argc, char *argv[])
{
	MD2 *md2 = new MD2();
	char hash[33];
	
	char *s = strdup("abcdefghijklmnopqrstuvwxyz");
	md2->computeHash((unsigned char*)s, strlen(s), hash);
	printf("%s\n", hash);
	return 0;
}
