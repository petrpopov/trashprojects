/****************************************************************************
** Form interface generated from reading ui file 'datedialog.ui'
**
** Created: Чт 3. ноя 16:06:00 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.3   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QSpinBox;
class QPushButton;

class DateDialog : public QDialog
{
    Q_OBJECT

public:
    DateDialog( QString &date, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~DateDialog();

    QLabel* dateTextLabel;
    QLabel* dayTextLabel;
    QSpinBox* daySpinBox;
    QLabel* monthTextLabel;
    QSpinBox* monthSpinBox;
    QLabel* yearTextLabel;
    QSpinBox* yearSpinBox;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QVBoxLayout* DateDialogLayout;
    QHBoxLayout* layout2;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();
private slots:
	void ok();
	void cancel();

};

#endif // DATEDIALOG_H
