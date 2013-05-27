/****************************************************************************
** Form interface generated from reading ui file 'cleardialog.ui'
**
** Created: Втр Май 17 16:30:48 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CLEARDIALOG_H
#define CLEARDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QGroupBox;
class QCheckBox;

class ClearDialog : public QDialog
{
    Q_OBJECT

public:
    ClearDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ClearDialog();

    QPushButton* clearPushButton;
    QPushButton* cancelPushButton;
    QGroupBox* clearGroupBox;
    QCheckBox* serversCheckBox;
    QCheckBox* mapsCheckBox;

protected:
    QGridLayout* ClearDialogLayout;
    QSpacerItem* spacer1;
    QVBoxLayout* layout2;
    QGridLayout* clearGroupBoxLayout;
private slots:
	void clear();
	void enableClearButton();
protected slots:
    virtual void languageChange();

};

#endif // CLEARDIALOG_H
