
#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qmainwindow.h>

#include <vector>

using namespace std;

struct Item
{
	QString type;
	QString name;
	QString login;
	QString pass;
	QString descr;
};

class CurList
{
	public:
		vector<Item> list;
		bool operator== (CurList& X);
};



class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QListView;
class QListViewItem;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~MainForm();

    QListViewItem *item;
    QListView* listView;
    QToolBar* fileToolbar;
    QToolBar* editToolbar;
    QMenuBar *MenuBarEditor;
    QPopupMenu *File;
    QPopupMenu *Edit;
    QPopupMenu *Help;
    QPopupMenu *rmbMenu;
    QAction* helpAboutAction;
    QAction* createProfileAction;
    QAction* openProfileAction;
    QAction* tb_openProfileAction;
    QAction* closeProfileAction;
    QAction* tb_closeProfileAction;
    QAction* deleteProfileAction;
    QAction* changeProfileAction;
    QAction* fileQuitAction;
    QAction* fileSaveAction;
    QAction* tb_fileSaveAction;
    QAction* editUndoAction;
    QAction* tb_editUndoAction;
    QAction* editRedoAction;
    QAction* tb_editRedoAction;
    QAction* editNewField;
    QAction* editEditField;
    QAction* tb_editEditField;
    QAction* tb_editNewField;
    QAction* editDeleteField;
    QAction* tb_editDeleteField;
    QAction* editDeleteAll;
    
private:
	bool modified;

protected:
    QVBoxLayout* MainFormLayout;
    
    void closeEvent(QCloseEvent *event);
    
private slots:
	QString getHash(QString &);
	void sortListView();
	void setEnabledActions(int);
	bool ifProfileExists();
	void createProfile();
	void openProfile();
	void closeProfile();
	void deleteProfile();
	void changeProfile();
	void clear();
	void Caption();
	void open();
	void save();
	void newField();
	void editField();
	void edit(QListViewItem *);
	void deleteField();
	void deleteAll();
	void about();
	void undo();
	void redo();
	void fillListForUndo();
	void fillSaveStruct(CurList &);
	void slotRMB( QListViewItem*, const QPoint &, int );
	
protected slots:
    virtual void languageChange();

};

#endif // MAINFORM_H
