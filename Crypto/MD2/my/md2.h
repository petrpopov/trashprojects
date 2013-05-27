/* Copyright (C) 1990, RSA Data Security, Inc. All rights reserved.

   License to copy and use this software is granted for
   non-commercial Internet Privacy-Enhanced Mail provided that it is
   identified as the "RSA Data Security, Inc. MD2 Message Digest
   Algorithm" in all material mentioning or referencing this software
   or this function.

   RSA Data Security, Inc. makes no representations concerning either
   the merchantability of this software or the suitability of this
   software for any particular purpose. It is provided "as is"
   without express or implied warranty of any kind.

   These notices must be retained in any copies of any part of this
   documentation and/or software.  
 */


#include <stdio.h>
#include <stdlib.h>

static unsigned char PI_SUBST[256] = {
  41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
  19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
  76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
  138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
  245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
  148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
  39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
  181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
  150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
  112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
  96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
  85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
  234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
  129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
  8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
  203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
  166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
  31, 26, 219, 153, 141, 51, 159, 17, 131, 20
};

static unsigned char MD2_Buffer[48];


int MD2Append(unsigned char *message, int length);
void MD2Compute(unsigned char *message, int length);
void MD2Hash(unsigned char* message, int length, unsigned char hash[32]);

int MD2Append(unsigned char *message, int length)
{
	/*computing number of bytes to append*/
	int n = ((length/16) + 1)*16 - length;
	message = (unsigned char*)realloc(message, (length + n + 16)*sizeof(unsigned char));
	
	/*adding n bytes of value 'n'*/
	int i;
	int N = length + n;
	for(i = length; i < N; i++)
		message[i] = n;
	
	/* computing cheksum */
	unsigned char CS[16];
	int j,c;
	for(i = 0; i < 16; i++)
		CS[i] = 0;
	
	int L = 0;
	for(i = 0; i < N/16; i++){
		for(j = 0; j < 16; j++){
			c = message[i*16 + j];
			CS[j] = PI_SUBST[c^L];
			L = CS[j];
		}
	}
	
	for(i = 0; i < 16; i++)
		message[i + N] = CS[i];
	
	return N + 16;
}

void MD2Compute(unsigned char *message, int length)
{
	int i,j,k,t;
	for(i = 0; i < length/16; i++){
		for(j = 0; j < 16; j++){
			MD2_Buffer[16 + j] = message[i*16 + j];
			MD2_Buffer[32 + j] = MD2_Buffer[16 + j] ^ MD2_Buffer[j];
		}
		
		t = 0;
		for(j = 0; j < 18; j++){
			for(k = 0; k < 48; k++)
				t = MD2_Buffer[k] ^= PI_SUBST[t];
			t = (t + j) % 256;
		}
	}
	
	
}

void MD2Hash(unsigned char* message, int length, unsigned char hash[32])
{
	int Length = length;
	int i;
	unsigned char *string = (unsigned char*)malloc(Length*sizeof(unsigned char));
	for(i = 0; i < length; i++)
		string[i] = message[i];

	
	/*Step 1, 2*/
	Length = MD2Append(string, Length);
	
	/*Step 3*/
	for(i = 0; i < 48; i++)
		MD2_Buffer[i] = 0;
	
	/*Step 4*/
	MD2Compute(string, Length);
	
	/*Step 5*/	
	unsigned char s[3];
	for(i = 0; i < 16; i++){
		sprintf(s, "%02x", MD2_Buffer[i]);
		hash[2*i] = s[0];
		hash[2*i+1] = s[1];
	}
	
	free(string);
}
 
