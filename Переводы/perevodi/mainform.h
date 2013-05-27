#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QTabWidget;
class QWidget;
class QListView;
class QListViewItem;
class QLabel;
class QLineEdit;
class QFrame;
class QTable;
class QPushButton;
class QToolbar;
class QPainter;
class QSimpleRichText;
class Spreadsheet;


class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~MainForm();

    QToolBar *Toolbar;
    QToolBar *editToolbar;
    QTabWidget* tabWidget;
    QWidget* tab;
    QListView* listView;
    QWidget* tab_2;
    QLabel* dateLabel;
    QLineEdit* dateLineEdit;
    QLabel* courseLabel;
    QLineEdit* courseLineEdit;
    QLabel* ccourseLabel;
    QLineEdit* ccourseLineEdit;
    QFrame* line1;
    QLabel* konvLabel;
    QLineEdit* konvLineEdit;
    QLabel* pvLabel;
    QLineEdit* pvLineEdit;
    QLabel* spLabel;
    QLineEdit* spLineEdit;
    QLabel* prLabel;
    QLineEdit* prLineEdit;
    QLabel* obLabel;
    QLineEdit* obLineEdit;
    QLabel* dkonvLabel;
    QLineEdit* dkonvLineEdit;
    QLabel* percentLabel;
    QLineEdit* percentLineEdit;
//    QTable* table;
	Spreadsheet* table;
    QPushButton* calcButton;
    QMenuBar *MenuBarEditor;
    QPopupMenu *File;
    QPopupMenu *Edit;
    QPopupMenu *Mark;
    QPopupMenu *Tools;
    QPopupMenu *Help;
    QListViewItem *item;
    QAction* fileQuitAction;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* filesaveAction;
    QAction* fileSave_AsAction;
    QAction* fileCloseAction;
    QAction* filePrintAction;
    QAction* editAdd_cellAction;
    QAction* editDelAction;
    QAction* editCopyAction;
    QAction* editCutAction;
    QAction* editPasteAction;
    QAction *markDoneAction;
    QAction *markNotDoneAction;
    QAction *markNowDoneAction;
    QAction *markClearAction;
    QAction *toolsCalculate;
    QAction *helpAbout;

protected:
    QVBoxLayout* MainFormLayout;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;
    QHBoxLayout* layout3;
    QHBoxLayout* layout4;
    QHBoxLayout* layout7;
    QHBoxLayout* layout1;
    QSpacerItem* spacer1;
    
    void closeEvent(QCloseEvent *);
private:
	bool modified;	
	QString curFile;
	enum { OldMagicNumber = 0x7F51C222 }; //Version: <= 0.9.4
	enum { MagicNumber = 0x7F51C223 }; //Version > 0.94
	
protected slots:
    virtual void languageChange();
private slots:
	void percentCalc(QListViewItem *item1);
	void calculate();
	int lastRow(QTable *stable, int col);
	int max(int *arr, int len);
	QString forDate(QString &);
	QString delZero(QString &);
	QString addSpaces(QString &);
	void recSum(QString &);
	void loadFromDate();
	void addCell();
	void loadData(QListViewItem *);
	void Caption();
	void clear();
	void newFile();
	void closeFile();
	void writeFile(QString &fileName);
	void readFile(QString &fileName);
	void open();
	void save();
	void saveAs();
	void copy();
	void cut();
	void del();
	void paste();
	void markDone();
	void markNotDone();
	void markNowDone();
	void markClear();
	void print();
	void printPage(QPainter *, const QSimpleRichText &, int, int);
	void redefine(int, int);
	void red_kurs();
	void red_kross_kurs();
	void red_konv();
	void red_pv();
	void red_sp();
	void red_pr();
	void red_ob();
	void red_dkonv();
	void red_percent();
	void about();

};

#endif // MAINFORM_H
