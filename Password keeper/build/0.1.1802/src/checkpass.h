
#ifndef CHECKPASS_H
#define CHECKPASS_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QPushButton;

class CheckPass : public QDialog
{
    Q_OBJECT

public:
    CheckPass( QString &inKey, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~CheckPass();

//     QLabel* loginLabel;
    QLabel* passLabel;
//     QLineEdit* loginLineEdit;
    QLineEdit* passLineEdit;
    QPushButton* clearButton;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QGridLayout* CheckPassLayout;
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

#endif // CHECKPASS_H
