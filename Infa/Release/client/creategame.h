/****************************************************************************
** Form interface generated from reading ui file 'creategame.ui'
**
** Created: Птн Апр 15 21:38:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QLabel;
class QComboBox;
class QSpinBox;
class QLineEdit;
class QPushButton;

class CreateGame : public QDialog
{
    Q_OBJECT

public:
    CreateGame( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~CreateGame();

    QGroupBox* serverGroupBox;
    QLabel* ipTextLabel;
    QComboBox* ipComboBox;
    QLabel* portTextLabel;
    QSpinBox* portSpinBox;
    QGroupBox* gameGroupBox;
    QLabel* typeTextLabel;
    QLabel* nameTextLabel;
    QLabel* numberTextLabel;
    QLineEdit* nameLineEdit;
    QSpinBox* numberSpinBox;
    QComboBox* typeComboBox;
    QGroupBox* logicGroupBox;
    QPushButton* logicPushButton;
    QLabel* logicTextLabel;
    QLineEdit* logicLineEdit;
    QPushButton* createPushButton;
    QPushButton* helpPushButton;
    QPushButton* cancelPushButton;

protected:
    QGridLayout* CreateGameLayout;
    QGridLayout* serverGroupBoxLayout;
    QSpacerItem* spacer2;
    QGridLayout* gameGroupBoxLayout;
    QSpacerItem* spacer1;
    QGridLayout* logicGroupBoxLayout;
    QVBoxLayout* layout3;
    QSpacerItem* spacer3;
private slots:
	void loadServerIP();
	void createGame();
	void chooseLogic();
	void enableCreateButton();
	void errorMessages(int mes);
	void help();
protected slots:
    virtual void languageChange();

};

#endif // CREATEGAME_H
