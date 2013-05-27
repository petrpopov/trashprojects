#ifndef RC4_H
#define RC4_H
 
typedef struct rc4_key
{      
	unsigned char state[256];       
	unsigned char x;        
	unsigned char y;
} rc4_key;

class RC4
{
	public:
		RC4();
		
		void prepare_key(unsigned char *key_data_ptr,int key_data_len,rc4_key *key);
		void rc4(unsigned char *buffer_ptr,int buffer_len,rc4_key * key);
		int crypto_file(char *fpurename, char *fciphername, unsigned char *key_data, int l,rc4_key *key);
		~RC4();
};
 
void swap_byte(unsigned char *a, unsigned char *b);
 
#endif
