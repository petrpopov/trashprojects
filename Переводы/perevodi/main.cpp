#include <qapplication.h>
#include <qtranslator.h>

#include "mainform.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainForm *mainform = new MainForm;
	app.setMainWidget(mainform); 
	QTranslator appT;
	appT.load("perevodi_ru.qm");
	app.installTranslator(&appT);
	mainform->show();
	return app.exec();
}

