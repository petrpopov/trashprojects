/****************************************************************************
** Form interface generated from reading ui file 'addserver.ui'
**
** Created: Сбт Апр 16 15:37:12 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef ADDSERVER_H
#define ADDSERVER_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;

class AddServer : public QDialog
{
    Q_OBJECT

public:
    AddServer( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~AddServer();

    QPushButton* okPushButton;
    QPushButton* cancelPushButton;
    QLineEdit* ipLineEdit;

protected:
    QGridLayout* AddServerLayout;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
private slots:
	void addServerIP();
	void enableOkButton();
protected slots:
    virtual void languageChange();

};

#endif // ADDSERVER_H
