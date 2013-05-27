#include <stdio.h>

int S[256];
int rci;
int rcj;

void RC4Init(char *keystring, int size)
{
	int K[256];
	rci = 0;
	rcj = 0;
	
	int i = 0;
	for(i = 0; i < 256; i++)
		S[i] = i;
	
	int k = 0;
	for(i = 0; i < 256; i++){
		if(k == size)
			k = 0;
		K[i] = keystring[k];
		k++;
	}
	
	int t = 0;
	for(rci = 0; rci < 256; rci++){
		rcj = (rcj + S[rci] + K[rci]) % 256;
		t = S[rci];
		S[rci] = S[rcj];
		S[rcj] = t;
	}
	
}

char RC4Crypto(char c)
{
	rci = (rci + 1) % 256;
	rcj = (rcj + S[rci]) % 256;
	
	int t = S[rci];
	S[rci] = S[rcj];
	S[rcj] = t;
	
	t = (S[rci] + S[rcj]) % 256;
	char k = S[t];
	
	return k ^ c;
}

int main(int argc, char *argv[])
{
	RC4Init("qwerty",6);
	char q = '1';
	char s = RC4Crypto(q);
	printf("%c\n", s);
	
	RC4Init("qwerty",6);
	q = 'L';
	s = RC4Crypto(q);
	printf("%c\n", s);
	
	return 0;
}
