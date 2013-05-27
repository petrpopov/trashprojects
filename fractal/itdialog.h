#ifndef ITDIALOG_H
#define ITDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QSpinBox;
class QPushButton;

class ItDialog : public QDialog
{
    Q_OBJECT

public:
    ItDialog(int &it, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ItDialog();

    QLabel* textLabel;
    QSpinBox* spinBox;
    QPushButton* okPushButton;
    QPushButton* cancelPushButton;

protected:
    QVBoxLayout* ItDialogLayout;
    QHBoxLayout* layout2;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();
private slots:
	void ok();
};

#endif // ITDIALOG_H
