/****************************************************************************
** Form interface generated from reading ui file 'createprofile.ui'
**
** Created: Срд Фев 15 20:38:07 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CREATEPROFILE_H
#define CREATEPROFILE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;

class CreateProfile : public QDialog
{
    Q_OBJECT

public:
    CreateProfile( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~CreateProfile();

    QLabel* infoLabel;
    QLabel* passLabel;
    QLabel* repLabel;
    QLineEdit* passLineEdit;
    QLineEdit* repLineEdit;
    QPushButton* clearButton;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QGridLayout* CreateProfileLayout;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
    
private slots:
	void enableOk();
	void ok();
	void clear();
	QString getHash(QString &);

protected slots:
    virtual void languageChange();

};

#endif // CREATEPROFILE_H
