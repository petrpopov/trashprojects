/****************************************************************************
** Form interface generated from reading ui file 'mainform.ui'
**
** Created: Чтв Апр 14 22:06:49 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qmainwindow.h>
#include "mynetworkobject.h"

extern MyNetworkObject *MNO;

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QLabel;
class QTextEdit;
class QTimer;
class GameDialog;
class QListView;
class QListViewItem;
class QPushButton;

class mainform : public QMainWindow
{
    Q_OBJECT

public:
    mainform( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~mainform();

    QLabel* logicTextLabel;
    QTextEdit* logicTextEdit;
    QMenuBar *MenuBarEditor;
    QPopupMenu *File;
    QPopupMenu *Game;
    QPopupMenu *Editor;
    QPopupMenu *Help;
    QToolBar *Toolbar;
    QAction* fileNewAction;
    QAction* fileLoadAction;
    QAction* filesaveAction;
    QAction* fileSave_AsAction;
    QAction* fileExitAction;
    QAction* gameCreate_gameAction;
    QAction* gameFind_gameAction;
    QAction* gameAddServerAction;
    QAction* gameClearDataAction;
    QAction* editorClearAction;
    QAction* editorCheck_for_errorsAction;
    QAction* helpHelpAction;
    QAction* helpAboutAction;
    QTimer *timer;
    GameDialog *gamedialog; 
    QListView *commandsListView;
    QListViewItem *element1;
    QListViewItem *element2;
    QListViewItem *element3;
    QPushButton *addButton;
    QPushButton *helpButton;       
private:
	void loadFile(const QString &fileName);
	void saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	bool modified;
	QString curFile;
protected:
    QGridLayout* mainformLayout;
    QVBoxLayout* layout1;
    QHBoxLayout* layout2;
    QVBoxLayout* layout3;
    QHBoxLayout* layout4;
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );
private slots:
	void logicModified();
	void open();
	void save();
	void saveAs();
	void clearEditor();
	void about();
	void newFile();
	void add();
	void create();
	void find();
	void game();
	void showGame();
	void help(const QString &fileName);
	QString strippedName(const QString &fullFileName);
	void fillFunctions();
	void insertFunction();
	void check();
	void clearData();
	void langHelp();
	void mainHelp();
protected slots:
    virtual void languageChange();
};

#endif // MAINFORM_H
