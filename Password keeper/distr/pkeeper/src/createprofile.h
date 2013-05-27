
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
    QLineEdit* repLineEdit;
//     QLineEdit* loginLineEdit;
    QLabel* repLabel;
//     QLabel* loginLabel;
    QLineEdit* passLineEdit;
    QLabel* passLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* clearButton;

protected:
    QVBoxLayout* CreateProfileLayout;
    QGridLayout* layout1;
    QHBoxLayout* layout2;
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
