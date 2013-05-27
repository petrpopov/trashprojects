/****************************************************************************
** Form interface generated from reading ui file 'helpbrowser.ui'
**
** Created: Птн Апр 22 20:18:22 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef HELPBROWSER_H
#define HELPBROWSER_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QTextBrowser;

class HelpBrowser : public QWidget
{
    Q_OBJECT

public:
    HelpBrowser( QWidget* parent = 0, const char* name = 0 );
    ~HelpBrowser();

    QPushButton* homePushButton;
    QPushButton* backPushButton;
    QPushButton* forwardPushButton;
    QPushButton* closePushButton;
    QTextBrowser* textBrowser;

protected:
    QGridLayout* HelpBrowserLayout;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
public slots:
	void showPage( const QString &fileName);
	void home();
	void back();
	void forward();
	void updateCaption();
protected slots:
    virtual void languageChange();

};

#endif // HELPBROWSER_H
