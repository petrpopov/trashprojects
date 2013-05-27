/****************************************************************************
** Form interface generated from reading ui file 'findgame.ui'
**
** Created: Вск Апр 17 15:24:40 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FINDGAME_H
#define FINDGAME_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QListView;
class QListViewItem;
class QLabel;
class QGroupBox;
class QLineEdit;
class QComboBox;
class QSpinBox;

class FindGame : public QDialog
{
    Q_OBJECT

public:
    FindGame( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FindGame();

    QPushButton* helpPushButton;
    QPushButton* cancelPushButton;
    QListView* findListView;
    QLabel* findTextLabel;
    QGroupBox* logicGroupBox;
    QLineEdit* logicLineEdit;
    QLabel* logicTextLabel;
    QPushButton* logicPushButton;
    QPushButton* joinPushButton;
    QGroupBox* gameGroupBox;
    QGroupBox* serverGroupBox;
    QLabel* ipTextLabel;
    QComboBox* ipComboBox;
    QSpinBox* portSpinBox;
    QLabel* portTextLabel;
    QLabel* typeTextLabel;
    QComboBox* typeComboBox;
    QPushButton* findPushButton;

protected:
    QGridLayout* FindGameLayout;
    QSpacerItem* spacer5;
    QHBoxLayout* layout8;
    QSpacerItem* spacer3;
    QVBoxLayout* layout9;
    QGridLayout* layout10;
    QSpacerItem* spacer7;
    QGridLayout* logicGroupBoxLayout;
    QGridLayout* layout11;
    QSpacerItem* spacer6;
    QGridLayout* gameGroupBoxLayout;
    QGridLayout* serverGroupBoxLayout;
    QSpacerItem* spacer1;
    QHBoxLayout* layout4;
private slots:
	void loadServerIP();
	void errorMessages(int mes, const QString &caption);
	void chooseLogic();
	void enableJoinButton();
	void find();
	void join();
	void help();
protected slots:
    virtual void languageChange();

};

#endif // FINDGAME_H
