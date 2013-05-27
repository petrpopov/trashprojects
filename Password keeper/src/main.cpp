#include <qapplication.h>

#include "mainform.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainForm *mainform = new MainForm;
	app.setMainWidget(mainform); 
	mainform->show();
	return app.exec();
}

