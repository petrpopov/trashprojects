
SHELL=/bin/sh
CC=g++

md5:		driver.o md5.o
	$(CC) -o md5 driver.o md5.o

driver.o:	driver.cpp
	$(CC) -c driver.cpp

md5.o:		md5.h md5.cpp
	$(CC) -c md5.cpp

clean:
	-rm *.o
