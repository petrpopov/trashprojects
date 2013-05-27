#ifndef MD2_H
#define MD2_H

#include <stdio.h>

class MD2
{
	public:
		MD2();
		~MD2();
		
		void computeHash(unsigned char *, int l, char hash[32]);
		
	private:
		unsigned char *mes;
// 		unsigned char *x_buffer;
};

#endif
 
