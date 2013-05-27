#include <qapplication.h>
 
#include "rc4.h"
 
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	RC4 *rc4 = new RC4();
	rc4_key rc4key;
	
	QString key = "pitonzx1dvz";
	rc4->prepare_key( (unsigned char*)key.data(), key.length(), &rc4key );
	
	QString text = "board.rt.mipt.ru piton z15Hsv";
	char *s = new char[text.length()+1];
	qstrcpy(s, text);
	
	printf("%s\n", s);
	rc4->rc4( (unsigned char*)s, text.length(), &rc4key);
	printf("%s\n", s);
	
	rc4->prepare_key( (unsigned char*)key.data(), key.length(), &rc4key );
	rc4->rc4( (unsigned char*)s, text.length(), &rc4key);
	printf("%s\n", s);
	
	return app.exec();
}

