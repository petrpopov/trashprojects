#!/bin/sh

echo Creating Makefile...
qmake -o Makefile gameclient.pro
echo Compiling...
make
echo Copying necessary files...
cp -R ./client_data ~
mv ~/client_data ~/.client_data
cp gameclient ~
echo Installation complete!
