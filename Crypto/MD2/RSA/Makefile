# Simple Makefile for compiling MD2
#
CC=	gcc
CFLAGS= -O2 -DMD=2 -I../mddriver -I.

all:	md2

mddriver.o: 
	$(CC) $(CFLAGS) -c mddriver.c 

md2:	md2c.o mddriver.o
	$(CC) $(CFLAGS) -o md2 md2c.c mddriver.o
	make clean

modified.o:
	$(CC) $(CFLAGS) -c modified.c

modified: md2c.o modified.o
	$(CC) $(CFLAGS) -o md2 md2c.c modified.o  
	make clean
clean:
	rm -f *.o
