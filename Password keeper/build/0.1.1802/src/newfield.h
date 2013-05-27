
#ifndef NEWFIELD_H
#define NEWFIELD_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLineEdit;
class QLabel;
class QComboBox;
class QPushButton;
class QTextEdit;

class NewField : public QDialog
{
    Q_OBJECT

public:
	NewField( QString &nameDlg, QStringList &in_list, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~NewField();

    QLineEdit* passLineEdit;
    QLineEdit* nameLineEdit;
    QLabel* nameLabel;
    QComboBox* typeBox;
    QLabel* passLabel;
    QLineEdit* loginLineEdit;
    QLabel* typeLabel;
    QLabel* loginLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QTextEdit* descrTextBox;
    QLabel* descrLabel;

protected:
    QGridLayout* NewFieldLayout;
    QGridLayout* layout1;
    QHBoxLayout* layout2;
    QSpacerItem* spacer1;
    QGridLayout* layout3;
    QSpacerItem* spacer2;

private slots:
	void ok();
	void enableOk();
	
protected slots:
    virtual void languageChange();

};

#endif // NEWFIELD_H
