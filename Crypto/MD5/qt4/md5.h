#ifndef MD5_H 
#define MD5_H 

#include <QtGlobal> 

#ifndef PROTOTYPES 
#define PROTOTYPES 0 
#endif 

/* POINTER defines a generic pointer type */ 
typedef unsigned char *POINTER; 

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above. 
If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it 
  returns an empty list. 
*/ 
#if PROTOTYPES 
#define PROTO_LIST(list) list 
#else 
#define PROTO_LIST(list) () 
#endif 

class QString; 

class MD5 
{ 
	public: 
   MD5(); 
   ~MD5(); 
   MD5 & update(const QString &); 
   MD5 & update(uchar *input, uint len); 
   const QString final(void); 
	private: 
   bool isFinalized; 
   uchar digest[16]; 
   struct MD5_CTX{ 
      quint32 state[4];                                   /* state (ABCD) */ 
      quint32 count[2];        /* number of bits, modulo 2^64 (lsb first) */ 
      unsigned char buffer[64];                         /* input buffer */ 
} context; 
   void transform(quint32 state[4], uchar block[64]); 
   void encode(uchar *output, quint32 *input, uint len); 
   void decode(quint32 *output, uchar *input, uint len); 
   void memcpy(POINTER output, POINTER input, uint len); 
   void memset(POINTER output, int value, uint len); 

}; 

#endif // MD5_H