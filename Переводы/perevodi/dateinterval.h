
#ifndef DATEINTERVAL_H
#define DATEINTERVAL_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QButtonGroup;
class QRadioButton;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;

class DateInterval : public QDialog
{
    Q_OBJECT

public:
    DateInterval( QString &dateStr, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~DateInterval();

    QButtonGroup* buttonGroup;
    QRadioButton* radioButton1;
    QGroupBox* groupBox;
    QLabel* inputLabel;
    QLabel* beginLabel;
    QLineEdit* beginLineEdit;
    QLabel* endLabel;
    QLineEdit* endLineEdit;
    QRadioButton* radioButton2;
    QPushButton* okButton;
    QPushButton* cancelButton;

protected:
    QVBoxLayout* DateIntervalLayout;
    QVBoxLayout* buttonGroupLayout;
    QHBoxLayout* layout4;
    QVBoxLayout* groupBoxLayout;
    QHBoxLayout* layout3;
    QHBoxLayout* layout5;
    QSpacerItem* spacer2;

protected slots:
    virtual void languageChange();
    
private slots:
	void enableDate();
	void enableOk();
	void ok();

};

#endif // DATEINTERVAL_H
