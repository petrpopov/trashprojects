
#ifndef CHANGEPROFILE_H
#define CHANGEPROFILE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;

class ChangeProfile : public QDialog
{
    Q_OBJECT

public:
    ChangeProfile( QString &inPass, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ChangeProfile();

    QLabel* infoLabel;
    QLabel* repLabel;
    QLineEdit* passLineEdit;
    QLineEdit* repLineEdit;
    QLabel* passLabel;
    QPushButton* clearButton;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QVBoxLayout* ChangeProfileLayout;
    QGridLayout* layout2;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;

private slots:
	void enableOk();
	void ok();
	
protected slots:
    virtual void languageChange();

};

#endif // CHANGEPROFILE_H
