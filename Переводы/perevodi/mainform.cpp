
#include "mainform.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qpixmap.h>
#include <qptrlist.h>
#include <qstatusbar.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatastream.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qfiledialog.h>
#include <qclipboard.h>
#include <qdatetime.h>
#include <qvalidator.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qsimplerichtext.h>

#include <math.h>
#include "datedialog.h"
#include "spreadsheet.h"
#include "dateinterval.h"

#include "calc.h"

QString version = "1.0";

struct Data{
	QString table[99][12];
	QString kurs;
	QString kross_kurs;
	QString koef[6];
	QString percent;
	Q_UINT16 mark[99][12];
 	int str;
 	bool mod;
};

int NUM = 0;
Data *tData = new Data[NUM];

MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "MainForm" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );
	setIcon(QPixmap::fromMimeSource("mainicon.png"));
    MainFormLayout = new QVBoxLayout( centralWidget(), 11, 6, "MainFormLayout"); 
    tabWidget = new QTabWidget( centralWidget(), "tabWidget" );

    tab = new QWidget( tabWidget, "tab" );
    tabLayout = new QVBoxLayout( tab, 11, 6, "tabLayout"); 

    listView = new QListView( tab, "listView" );
    listView->addColumn( tr( "Date" ) );
    listView->addColumn( tr( "Delta" ) );
    listView->addColumn( tr( "Sum" ) );
    listView->addColumn( tr( "%" ) );
    listView->setResizeMode( QListView::AllColumns );
    listView->setSorting(-1, FALSE);
    tabLayout->addWidget( listView );
    tabWidget->insertTab( tab, QString::fromLatin1("") );

    tab_2 = new QWidget( tabWidget, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2, 11, 6, "tabLayout_2"); 

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    dateLabel = new QLabel( tab_2, "dateLabel" );
    layout3->addWidget( dateLabel );

    dateLineEdit = new QLineEdit( tab_2, "dateLineEdit" );
    layout3->addWidget( dateLineEdit );

    courseLabel = new QLabel( tab_2, "courseLabel" );
    layout3->addWidget( courseLabel );

    courseLineEdit = new QLineEdit( tab_2, "courseLineEdit" );
    layout3->addWidget( courseLineEdit );

    ccourseLabel = new QLabel( tab_2, "ccourseLabel" );
    layout3->addWidget( ccourseLabel );

    ccourseLineEdit = new QLineEdit( tab_2, "ccourseLineEdit" );
    layout3->addWidget( ccourseLineEdit );
    tabLayout_2->addLayout( layout3 );

    line1 = new QFrame( tab_2, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );
    tabLayout_2->addWidget( line1 );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    konvLabel = new QLabel( tab_2, "konvLabel" );
    layout4->addWidget( konvLabel );

    konvLineEdit = new QLineEdit( tab_2, "konvLineEdit" );
    layout4->addWidget( konvLineEdit );

    pvLabel = new QLabel( tab_2, "pvLabel" );
    layout4->addWidget( pvLabel );

    pvLineEdit = new QLineEdit( tab_2, "pvLineEdit" );
    layout4->addWidget( pvLineEdit );

    spLabel = new QLabel( tab_2, "spLabel" );
    layout4->addWidget( spLabel );

    spLineEdit = new QLineEdit( tab_2, "spLineEdit" );
    layout4->addWidget( spLineEdit );
    tabLayout_2->addLayout( layout4 );

    layout7 = new QHBoxLayout( 0, 0, 6, "layout7"); 

    prLabel = new QLabel( tab_2, "prLabel" );
    layout7->addWidget( prLabel );

    prLineEdit = new QLineEdit( tab_2, "prLineEdit" );
    layout7->addWidget( prLineEdit );

    obLabel = new QLabel( tab_2, "obLabel" );
    layout7->addWidget( obLabel );

    obLineEdit = new QLineEdit( tab_2, "obLineEdit" );
    layout7->addWidget( obLineEdit );

    dkonvLabel = new QLabel( tab_2, "dkonvLabel" );
    layout7->addWidget( dkonvLabel );

    dkonvLineEdit = new QLineEdit( tab_2, "dkonvLineEdit" );
    layout7->addWidget( dkonvLineEdit );
    
    percentLabel = new QLabel( tab_2, "percentLabel" );
    layout7->addWidget(percentLabel);
    
    percentLineEdit = new QLineEdit( tab_2, "percentLineEdit" );
    layout7->addWidget(percentLineEdit);
    tabLayout_2->addLayout( layout7 );

//    table = new QTable( tab_2, "table" );
    table = new Spreadsheet( tab_2, "table" );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Bank(prihod)" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Firm" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Valuta(prihod)" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Firm" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Kassa(prihod)" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Firm" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Bank(uhod)" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Firm" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Valuta(uhod)" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Firm" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Kassa(uhod)" ) );
    table->setNumCols( table->numCols() + 1 );
    table->horizontalHeader()->setLabel( table->numCols() - 1, tr( "Firm" ) );
    
    table->setNumRows( 99 );
    table->setNumCols( 12 );
    table->setSelectionMode(QTable::Single);
    tabLayout_2->addWidget( table );
    
    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    calcButton = new QPushButton( tab_2, "calcButton" );
    calcButton->setDefault( TRUE );
    layout1->addWidget( calcButton );
    tabLayout_2->addLayout( layout1 );
    tabWidget->insertTab( tab_2, QString::fromLatin1("") );
    MainFormLayout->addWidget( tabWidget );

    // actions
    fileQuitAction = new QAction( this, "fileQuitAction" );
    fileNewAction = new QAction( this, "fileNewAction" );
    fileNewAction->setIconSet( QPixmap::fromMimeSource("filenew.png") );
    fileOpenAction = new QAction( this, "Action" );
    fileOpenAction->setIconSet( QPixmap::fromMimeSource("fileopen.png") );
    filesaveAction = new QAction( this, "filesaveAction" );
    filesaveAction->setIconSet( QPixmap::fromMimeSource("filesave.png") );
    fileSave_AsAction = new QAction( this, "fileSave_AsAction" );
    fileSave_AsAction->setIconSet( QPixmap::fromMimeSource("filesaveas.png") );
    fileCloseAction = new QAction( this, "fileCloseAction" );
    fileCloseAction->setIconSet( QPixmap::fromMimeSource("fileclose.png") );
    filePrintAction = new QAction( this, "filePrintAction" );
    filePrintAction->setIconSet( QPixmap::fromMimeSource("fileprint.png") );
    editAdd_cellAction = new QAction( this, "editAdd_cellAction" );
    editCopyAction = new QAction(this, "editCopyAction");
    editCopyAction->setIconSet( QPixmap::fromMimeSource("editcopy.png") );
    editCutAction = new QAction(this, "editCutAction");
    editCutAction->setIconSet( QPixmap::fromMimeSource("editcut.png") );
    editPasteAction = new QAction( this, "editPasteAction");
    editPasteAction->setIconSet( QPixmap::fromMimeSource("editpaste.png") ); 
    editDelAction = new QAction( this, "editDelAction" );
    editDelAction->setIconSet( QPixmap::fromMimeSource("editdelete.png") );
    markDoneAction = new QAction(this, "markDoneAction" );
    markDoneAction->setIconSet( QPixmap::fromMimeSource("done.png") );
    markNotDoneAction = new QAction(this, "markNotDoneAction" );
    markNotDoneAction->setIconSet( QPixmap::fromMimeSource("notdone.png") );
    markNowDoneAction = new QAction(this, "markNowDoneAction" );
    markNowDoneAction->setIconSet( QPixmap::fromMimeSource("nowdone.png") );
    markClearAction = new QAction(this, "markClearAction" );
    markClearAction->setIconSet( QPixmap::fromMimeSource("clear.png") );
    toolsCalculate = new QAction( this, "toolsCalculate" );
    helpAbout = new QAction( this, "helpAbout" );


    // toolbars
    Toolbar = new QToolBar( tr("File"), this, DockTop );
    fileNewAction->addTo( Toolbar );
    fileOpenAction->addTo( Toolbar );
    filesaveAction->addTo( Toolbar );
    Toolbar->addSeparator();
    filePrintAction->addTo( Toolbar ); 
    Toolbar->addSeparator();
    fileCloseAction->addTo( Toolbar );
    
    editToolbar = new QToolBar( tr("Edit"), this, DockTop );
    editCopyAction->addTo( editToolbar );
    editCutAction->addTo( editToolbar );
    editPasteAction->addTo( editToolbar );
    editDelAction->addTo( editToolbar );
    editToolbar->addSeparator();
    markDoneAction->addTo( editToolbar );
    markNotDoneAction->addTo( editToolbar );
    markNowDoneAction->addTo( editToolbar );
    markClearAction->addTo( editToolbar );
    
    // menubar
    MenuBarEditor = new QMenuBar( this, "MenuBarEditor" );


    File = new QPopupMenu( this );
    fileNewAction->addTo( File );
    fileOpenAction->addTo( File );
    filesaveAction->addTo( File );
    fileSave_AsAction->addTo( File );
    filePrintAction->addTo( File );
    File->insertSeparator();
    fileCloseAction->addTo( File );
    fileQuitAction->addTo( File );
    MenuBarEditor->insertItem( QString(""), File, 1 );

    Edit = new QPopupMenu( this );
   
//     Edit->insertSeparator();
    editAdd_cellAction->addTo( Edit );
    MenuBarEditor->insertItem( QString(""), Edit, 2 );
    
    Mark = new QPopupMenu( this ); 
    markDoneAction->addTo( Mark );
    markNotDoneAction->addTo( Mark );
    markNowDoneAction->addTo( Mark );
    markClearAction->addTo( Mark );
    Edit->insertItem( tr("Mark as"), Mark );
    Edit->insertSeparator();
    editCopyAction->addTo( Edit );
    editCutAction->addTo( Edit );
    editPasteAction->addTo( Edit );
    editDelAction->addTo( Edit );

    Tools = new QPopupMenu( this );
    toolsCalculate->addTo( Tools );
    MenuBarEditor->insertItem( QString(""), Tools, 3 );
    
    Help = new QPopupMenu( this );
    helpAbout->addTo(Help);
    MenuBarEditor->insertItem( QString(""), Help, 4 );
    
    languageChange();
    resize( QSize(635, 598).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( tabWidget, listView );
    setTabOrder( listView, dateLineEdit );
    setTabOrder( dateLineEdit, courseLineEdit );
    setTabOrder( courseLineEdit, ccourseLineEdit );
    setTabOrder( ccourseLineEdit, konvLineEdit );
    setTabOrder( konvLineEdit, pvLineEdit );
    setTabOrder( pvLineEdit, spLineEdit );
    setTabOrder( spLineEdit, prLineEdit );
    setTabOrder( prLineEdit, obLineEdit );
    setTabOrder( obLineEdit, dkonvLineEdit );
    setTabOrder( dkonvLineEdit, percentLineEdit );
    setTabOrder( percentLineEdit, table );
    setTabOrder( table, calcButton );
    
    connect(fileNewAction, SIGNAL( activated() ), this, SLOT( newFile() ) );
    connect(fileOpenAction, SIGNAL( activated() ), this, SLOT( open() ) );
    connect(filesaveAction, SIGNAL( activated() ), this, SLOT( save() ) );
    connect(fileCloseAction, SIGNAL( activated() ), this, SLOT( closeFile() ) );
    connect(fileQuitAction, SIGNAL( activated() ), this, SLOT( close() ) );
    connect(filePrintAction, SIGNAL( activated() ), this, SLOT( print() ));
    connect(editAdd_cellAction, SIGNAL( activated() ), this, SLOT( addCell() ) );
    connect(editCopyAction, SIGNAL( activated() ), this, SLOT( copy() ) );
    connect(editCutAction, SIGNAL( activated() ), this, SLOT( cut() ) );
    connect(editDelAction, SIGNAL( activated() ), this, SLOT( del() ) );
    connect(editPasteAction, SIGNAL( activated() ), this, SLOT( paste() ) );
    connect(markDoneAction, SIGNAL( activated() ), this, SLOT( markDone() ) );
    connect(markNotDoneAction, SIGNAL( activated() ), this, SLOT( markNotDone() ) );
    connect(markNowDoneAction, SIGNAL( activated() ), this, SLOT( markNowDone() ) );
    connect(markClearAction, SIGNAL( activated() ), this, SLOT( markClear() ) );
    connect(toolsCalculate, SIGNAL( activated() ), this, SLOT( calculate() ));
    connect(helpAbout, SIGNAL( activated() ), this, SLOT( about() ) );
    
    connect(calcButton, SIGNAL( clicked() ), this, SLOT( calculate() ) );
    
    connect(listView, SIGNAL( selectionChanged(QListViewItem *) ), this, SLOT( loadData(QListViewItem *) ) );
    connect(table, SIGNAL( valueChanged(int, int)), this, SLOT( redefine(int, int) ) );
    
    connect(courseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kurs() ) );
    connect(ccourseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kross_kurs() ) );
    connect(konvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_konv() ) );
    connect(pvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pv() ) );
    connect(spLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_sp() ) );
    connect(prLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pr() ) );
    connect(obLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_ob() ) );
    connect(dkonvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_dkonv() ) );
    connect(percentLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_percent() ) );
    
    connect(dateLineEdit, SIGNAL( returnPressed() ), this, SLOT( loadFromDate() ) );
    
    
    
    QRegExp regExp("[0-9-.]{0,10}");
    courseLineEdit->setValidator(new QRegExpValidator(regExp, this));
    ccourseLineEdit->setValidator(new QRegExpValidator(regExp, this));
    
    QRegExp regExp3("[0-9-.+*/()]{0,10}");
    konvLineEdit->setValidator(new QRegExpValidator(regExp3, this));
    pvLineEdit->setValidator(new QRegExpValidator(regExp3, this));
    prLineEdit->setValidator(new QRegExpValidator(regExp3, this));
    obLineEdit->setValidator(new QRegExpValidator(regExp3, this));
    percentLineEdit->setValidator(new QRegExpValidator(regExp3, this));
    
    QRegExp regExp1("[0-9]{1,2}[.]{1,1}[0-9]{1,2}[.]{1,1}[0-9]{1,4}");
    dateLineEdit->setValidator(new QRegExpValidator(regExp1, this));
    
    QRegExp regExp2("[eE$]{0,1}[0-9-.]{1,10}");
    spLineEdit->setValidator(new QRegExpValidator(regExp2, this));
    
    QRegExp regExp4("[0-9-.+*/()]{1,20}[;]{1,1}[0-9]{0,2}");
    dkonvLineEdit->setValidator(new QRegExpValidator(regExp4, this));
    
    
    modified = false;
    Caption();
    
    tab_2->setEnabled(FALSE);
    editCopyAction->setEnabled(FALSE);
    editCutAction->setEnabled(FALSE);
    editPasteAction->setEnabled(FALSE);
    editDelAction->setEnabled(FALSE);
    toolsCalculate->setEnabled(FALSE);
    Mark->setEnabled(FALSE);
    markDoneAction->setEnabled(FALSE);
    markNotDoneAction->setEnabled(FALSE);
    markNowDoneAction->setEnabled(FALSE);
    markClearAction->setEnabled(FALSE);

    setWindowState(Qt::WindowMaximized);
}


void MainForm::loadFromDate()
{
	QString str = dateLineEdit->text();
	item = listView->findItem(str,0);
	if(item){
		listView->setSelected(item, TRUE);
	}
	else{
		QMessageBox::warning(this, tr("Perevodi"), tr("There are no data in this file for entered date!"));
	}
}

void MainForm::calculate()
{
	
	double S[6] = {0,0,0,0,0,0};
	int r[6] = {0,0,0,0,0,0};
	int rm;
	
	for(int i = 0; i < 6; i++){
		r[i] = lastRow(table, 2*i);
	}
	rm = max(r, 6);
	rm += 2;
	
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		bool sp = false;
		double k = 0;
		double kk = 0;
		bool ok;
		k = tData[pos].kurs.toDouble(&ok);
		if(ok){
			if(k != 0){
				kk = tData[pos].kross_kurs.toDouble(&ok);
				if(ok){
					if(kk != 0){
						double koef[7] = {0,0,0,0,0,0,0};
						for(int i = 0; i < 6; i++){
							if(i != 2){
								if(i != 5){
									QString str = tData[pos].koef[i];
									char *string = new char[2*str.length()];
									qstrcpy(string, (char*)str.data());
									string[str.length()] = '=';
									char *p = string;
									int stat;
									double s = 0;
									s = Calc(&p,&stat);
									if(stat == 0){
										koef[i] = s;
										str = QString::number(s);
									
										switch(i){
										case 0 : {
										konvLineEdit->setText(str);
										break;
										}
										case 1 : {
										pvLineEdit->setText(str);
										break;
										}
										case 3: {
										prLineEdit->setText(str);
										break;
										}
										case 4 : {
										obLineEdit->setText(str);
										break;
										}
										}
									}
									else{
										koef[i] = 0;
									}
								}
								else{
									QString str = tData[pos].koef[i];
									int p = str.find(';');
									if(p != -1){
										QStringList sl = QStringList::split(";",str);
										str = sl[0];
										char *string = new char[2*str.length()];
										qstrcpy(string,(char*)str.data());
										string[str.length()] = '=';
										char *p = string;
										int stat;
										double s = 0;
										
										s = Calc(&p,&stat);
										if(stat == 0){
										koef[i] = s;
										double q = 0;
										q = sl[1].toDouble(&ok);
										if(ok){
										koef[i+1] = q;
										}
										str = QString::number(s);
										str += ";";
										str += sl[1];
										dkonvLineEdit->setText(str);
										}
										else{
										koef[i] = 0;
										}
									}
									else{
										char *string = new char[2*str.length()];
										qstrcpy(string,(char*)str.data());
										string[str.length()] = '=';
										char *p = string;
										int stat;
										double s = 0;
										
										s = Calc(&p,&stat);
										if(stat == 0){
										koef[i] = s;
										str = QString::number(s);
										dkonvLineEdit->setText(str);
										}
										else{
										koef[i] = 0;
										}
									}
								}
								
							}
							else{
								QString str = tData[pos].koef[i];
								if( (str.at(0) == 'e') || (str.at(0) == 'E') ){
									str = str.right(str.length()-1);
									double s = str.toDouble(&ok);
									if(ok){
										s *= kk;
										koef[i] = s;
										sp = true;
									}
								}
								else{
									if(str.at(0) == '$'){
										str = str.right(str.length()-1);
										double s = str.toDouble(&ok);
										if(ok){
										koef[i] = s;
										sp = true;
										}
									}
									else{
										double s = str.toDouble(&ok);
										if(ok){
										koef[i] = s;
										sp = false;
										}
									}
								}
							}
						}
						
						
						if(tData[pos].str > 0){
							for(int z = 0; z < 12; z++){
								table->clearCell(tData[pos].str,z);
								tData[pos].table[tData[pos].str][z] = "";
								table->clearCell(tData[pos].str+1,z);
								tData[pos].table[tData[pos].str+1][z] = "";
							}
						}
						
						
						for(int i = 0; i < 6; i++){
							switch(i){
							case 0:{ //Bank prihod, rubli only, konvertaciya
							for(int j = 0; j <= r[i]; j++){
								QString str = tData[pos].table[j][2*i];
								str.replace(" ", "");
								double s = str.toDouble(&ok);
								if(ok){
									if(j <= koef[6]){
										if(!tData[pos].koef[5].isEmpty()){
											s *= koef[5];
										}
										
									}
									S[i] += s;
								}
							}
							
							S[i] *= koef[0];
							S[i] = S[i]/k;	
							
							QString str = QString::number(S[i], 'f');
							str = delZero(str);
							str = addSpaces(str);
							
							table->setText(rm, 2*i, str);
							tData[pos].table[rm][2*i] = str;
							tData[pos].str = rm;
							
							break;
							}
							case 1:{ //Valuta prihod, $,e,E,  progon valuti
							for(int j = 0; j <= r[i]; j++){
								QString str = tData[pos].table[j][2*i];
								str.replace(" ", "");
								if( (str.at(0) == 'e') || (str.at(0) == 'E') ){
									str = str.right(str.length()-1);
									double s = str.toDouble(&ok);
									if(ok){
										s *= kk;
										S[i] += s;
									}
								}
								else{
									if(str.at(0) == '$'){
										str = str.right(str.length()-1);
										double s = str.toDouble(&ok);
										if(ok){
											S[i] += s;
										}
									}
								}
							}
							
							S[i] *= koef[1];
							
							QString str = QString::number(S[i], 'f');
							str = delZero(str);
							str = addSpaces(str);
							
							table->setText(rm, 2*i, str);
							tData[pos].table[rm][2*i] = str;
							tData[pos].str = rm;
							
							break;
							}
							case 2:{ //Kassa prihod rubli,$,e,E
							for(int j = 0; j <= r[i]; j++){
								QString str = tData[pos].table[j][2*i];
								str.replace(" ", "");
								if( (str.at(0) == 'e') || (str.at(0) == 'E') ){
									str = str.right(str.length()-1);
									double s = str.toDouble(&ok);
									if(ok){
										s *= kk;
										S[i] += s;
									}
								}
								else{
									if(str.at(0) == '$'){
										str = str.right(str.length()-1);
										double s = str.toDouble(&ok);
										if(ok){
										S[i] += s;
										}
									}
									else{
										double s = str.toDouble(&ok);
										if(ok){
										s = s/k;
										S[i] += s;
										}
									}
								}
							}
							
							QString str = QString::number(S[i], 'f');
							str = delZero(str);
							str = addSpaces(str);
							
							table->setText(rm, 2*i, str);
							tData[pos].table[rm][2*i] = str;
							tData[pos].str = rm;
							
							break;
							}
							case 3:{ //Bank uhod rubli only   progon rublya
							for(int j = 0; j <= r[i]; j++){
								QString str = tData[pos].table[j][2*i];
								str.replace(" ", "");
								double s = str.toDouble(&ok);
								if(ok){
									S[i] += s;
								}
							}
							
							S[i] *= koef[3];
							S[i] = S[i]/k;
							
							QString str = QString::number(S[i], 'f');
							str = delZero(str);
							str = addSpaces(str);
							
							table->setText(rm, 2*i, str);
							tData[pos].table[rm][2*i] = str;
							tData[pos].str = rm;
							
							break;
							}
							case 4:{ //Valuta uhod $,e,E, stoimost perevoda
							for(int j = 0; j <= r[i]; j++){
								QString str = tData[pos].table[j][2*i];
								str.replace(" ", "");
								if( (str.at(0) == 'e') || (str.at(0) == 'E') ){
									str = str.right(str.length()-1);
									double s = str.toDouble(&ok);
									if(ok){
										s *= kk;
										S[i] += s;
										
										if(sp == true){
										S[i] += koef[2];
										}
// 										else{
// 										S[i] *= koef[2];
// 										}
									}
								}
								else{
									if(str.at(0) == '$'){
										str = str.right(str.length()-1);
										double s = str.toDouble(&ok);
										if(ok){
										S[i] += s;
										
										if(sp == true){
										S[i] += koef[2];
										}
// 										else{
// 										S[i] *= koef[2];
// 										}
										}
									}
								}
							}
							if(sp == false)
								S[i] *= koef[2];
							/*
							if(sp == true){
								S[i] += koef[2];
							}
							else{
								S[i] *= koef[2];
							}*/

							QString str = QString::number(S[i], 'f');
							str = delZero(str);
							str = addSpaces(str);
							
							table->setText(rm, 2*i, str);
							tData[pos].table[rm][2*i] = str;
							tData[pos].str = rm;
							
							break;
							}
							case 5:{ //Kassa uhod $,e,E,r   obnalichka
							for(int j = 0; j <= r[i]; j++){
								QString str = tData[pos].table[j][2*i];
								str.replace(" ", "");
								if( (str.at(0) == 'e') || (str.at(0) == 'E') ){
									str = str.right(str.length()-1);
									double s = str.toDouble(&ok);
									if(ok){
										s *= kk;
										S[i] += s;
									}
								}
								else{
									if(str.at(0) == '$'){
										str = str.right(str.length()-1);
										double s = str.toDouble(&ok);
										if(ok){
										S[i] += s;
										}
									}
									else{
										double s = str.toDouble(&ok);
										if(ok){
										s = s/k;
										S[i] += s;
										}
									}
								}
							}
							
							S[i] *= koef[4];
							
							QString str = QString::number(S[i], 'f');
							str = delZero(str);
							str = addSpaces(str);
							
							table->setText(rm, 2*i, str);
							tData[pos].table[rm][2*i] = str;
							tData[pos].str = rm;
							
							break;
							}
							}
						}
						QString str = "+";
						QString n = QString::number(S[0]+S[1]+S[2], 'f');
						n = addSpaces(n);
						str += n;
						str = delZero(str);
						table->setText(rm+1, 0, str);
						tData[pos].table[rm+1][0] = str;
						str = "-";
						n = QString::number(S[3]+S[4]+S[5], 'f');
						n = addSpaces(n);
						str += n;
						str = delZero(str);
						table->setText(rm+1,6, str);
						tData[pos].table[rm+1][6] = str;
						
						double Sum = S[0]+S[1]+S[2]-S[3]-S[4]-S[5];
						str = "";
						str = QString::number(Sum, 'f');
						str = addSpaces(str);
						str = delZero(str);
// 						item->setText(1, QString::number(Sum,'f') );
// 						item->setText(2, QString::number(Sum,'f') );
						item->setText(1, str);
						item->setText(2, str);
						if(listView->childCount() > 1){
							QString cur = item->text(0);
							QApplication::setOverrideCursor(waitCursor);
							recSum(cur);
							QApplication::restoreOverrideCursor();
						}
						else if(listView->childCount() == 1){
							percentCalc(item);
						}
						
// 						percentCalc();
						
						modified = true;
						Caption();
					}
					else{
						QMessageBox::warning(this, tr("Perevodi"), tr("Cross-course can't be zero!"));
					}
				}
			}
			else{
				QMessageBox::warning(this, tr("Perevodi"), tr("Course can't be zero!"));
			}
		}
	}
	
	
	
}

void MainForm::percentCalc(QListViewItem *item1)
{
// 	item = listView->selectedItem();
	if(item1){
		int pos = 0;
		int h = item1->height();
		pos = listView->itemPos( item1 )/h;
		pos = listView->childCount() - pos - 1;
		
		bool ok;
		double sum = 0;
		double per = 0;
		
		QString str = item1->text(2);
		str.replace(" ", "");
		sum = str.toDouble(&ok);
		if(!ok)
			return;
		
		if(sum >= 0)
			return;
		
		str = tData[pos].percent;
		str.replace(" ", "");
		per = str.toDouble(&ok);
		if(!ok)
			return;
		
		per = (per * sum) / 36000;
		sum += per;
		
		str = QString::number(sum,'f');
		str = addSpaces(str);
		str = delZero(str);
		item1->setText(2, str );
		
		str = QString::number(per,'f');
		str = addSpaces(str);
		str = delZero(str);
		item1->setText(3, str );
	}
}


QString MainForm::delZero(QString &string)
{
	QString str = string;
	QString a;
	int pos = string.find('.');
	if(pos != -1){
		bool ok;
		a = string.at(pos+3);
		int c = a.toInt(&ok, 10);;
		if(ok){
			if(c < 5){
				str = string.left(pos+3);
			}
			else{
				if(c >= 5){
					a = string.at(pos+2);
					c = a.toInt(&ok);
					if(ok){
						c += 1;
						str = string.left(pos+2);
						str += QString::number(c);
					}
				}
			}
		}
	}
	else{
		str += ".00";
	}
	return str;
}


QString MainForm::forDate(QString &date)
{
	int p1 = date.find(".");
	int p2 = date.find(".", p1+1);
	QString d = date.left(p1);
	QString y = date.right(date.length()-p2-1);
	QString m = date.mid(p1+1, p2-p1-1);
	QString dat = y + "." + m + "." + d;
	return dat;
}

void MainForm::recSum(QString &cur)
{
	QStringList strl, sstrl;
	QString str;
	
	item = listView->lastItem();
	while(item != NULL){
		str = item->text(0);
		str = forDate(str);
		strl += str;
		item = item->itemAbove();
	}
	sstrl = strl;
	for(int i = 1; i <= NUM; i++){
		QDate m = QDate::fromString(strl[i-1], Qt::ISODate);
		int k = i;
		for(int j = i; j <= NUM; j++){
			QDate d = QDate::fromString(strl[j-1], Qt::ISODate);
			if( m > d){
				m = d;
				k = j;
			}
		}
		strl[k-1] = strl[i-1];
		QString s;
		s.sprintf("%d.%2d.%2d", m.year(), m.month(), m.day());
		strl[i-1] = s;
	}

	for(int i = 0; i < NUM; i++){
		QDate d = QDate::fromString(strl[i], Qt::ISODate);
		QString s;
		s.sprintf("%2d.%2d.%d", d.day(), d.month(), d.year());
		strl[i] = s;
	}
	for(int i = 0; i < NUM; i++){
		QDate d = QDate::fromString(sstrl[i], Qt::ISODate);
		QString s;
		s.sprintf("%2d.%2d.%d", d.day(), d.month(), d.year());
		sstrl[i] = s;
	}

	/*
	for ( QStringList::Iterator it = sstrl.begin(); it != sstrl.end(); ++it ) {
		str =  *it;
		printf("%s\n", str.latin1());
	}*/
	
	
	Data *t = new Data[NUM];
	for(int i = 0; i < NUM; i++){
		for(int j = 0; j < 99; j++){
			for(int k = 0; k < 12; k++){
				t[i].table[j][k] = tData[i].table[j][k];
				t[i].mark[j][k] = tData[i].mark[j][k];
			}
		}
		for(int j = 0; j < 6; j++){
			t[i].koef[j] = tData[i].koef[j];
		}
		t[i].kurs = tData[i].kurs;
		t[i].kross_kurs = tData[i].kross_kurs;
		t[i].percent = tData[i].percent;
		t[i].str = tData[i].str;
		t[i].mod = tData[i].mod;
	}
	delete [] tData;
	tData = new Data[NUM];
	
		
	listView->clear();
	for(int i = 0; i < NUM; i++){
		item = new QListViewItem(listView, "0", "0", "0", "0");
		item->setText(0, strl[i]);
		listView->insertItem(item);
		
		QString str = sstrl[i];
		int pos = 0;
		bool ex = false;
		for(int j = 0; j < NUM; j++){
			if(strl[j] == str){
				if(ex == false){
					pos = j;
					ex = true;
				}
			}
		}
		
		
		for(int j = 0; j < 99; j++){
			for(int k = 0; k < 12; k++){
				tData[pos].table[j][k] = t[i].table[j][k];
				tData[pos].mark[j][k] = t[i].mark[j][k];
			}
		}
		for(int j = 0; j < 6; j++){
			tData[pos].koef[j] = t[i].koef[j];
		}
		tData[pos].kurs = t[i].kurs;
		tData[pos].kross_kurs = t[i].kross_kurs;
		tData[pos].percent = t[i].percent;
		tData[pos].str = t[i].str;
		tData[pos].mod = t[i].mod;
	}
	
	
	item = listView->lastItem();
	double s1 = 0;
	double s2 = 0;
	bool ok;
	while(item != NULL){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		QString str = tData[pos].table[ tData[pos].str+1 ][0];
		str.replace(" ", "");
		s1 = str.toDouble(&ok);
		if(ok){
			str = tData[pos].table[ tData[pos].str+1 ][6];
			str.replace(" ", "");
			s2 = str.toDouble(&ok);
			if(ok){
				s1 += s2;
				QString a = QString::number(s1, 'f');
				a = addSpaces(a);
				a = delZero(a);
				item->setText(1, a);
				item->setText(2, a);
				
			}
		}
		item = item->itemAbove();
	}
	
	item = listView->lastItem();
	int i = 0;
	while(item != NULL){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		
		if(i > 0){
			QString st = item->itemBelow()->text(2);
			st.replace(" ", "");
			double s = st.toDouble(&ok);
			QString st1 = item->text(2);
			st1.replace(" ", "");
			double s1 = st1.toDouble(&ok);
			if(ok){
				s1 += s;
				QString a = QString::number(s1, 'f');
				a = addSpaces(a);
				a = delZero(a);
				item->setText(2, a );
			}
		}
		
		item = item->itemAbove();
		i++;
	}
	
	i = 0;
	item = listView->lastItem();
	while(item != NULL){
		if(i > 0){
			QString st = item->itemBelow()->text(3);
			st.replace(" ", "");
			double per = st.toDouble(&ok);
			if(ok){
				st = item->text(2);
				st.replace(" ", "");
				double s = st.toDouble(&ok);
				if(ok){
					s += per;
					st = QString::number(s, 'f');
					st = addSpaces(st);
					st = delZero(st);
					item->setText(2, st);
				}
			}
		}
		percentCalc(item);
		item = item->itemAbove();
		i++;
	}
	
	item = listView->findItem(cur,0);
	if(item){
		listView->setSelected(item, TRUE);
	}
	else{
		listView->setSelected(listView->firstChild(),TRUE);
	}
}

int MainForm::lastRow(QTable *stable, int col)
{
	int i = 0;
	int r = stable->numRows();

	bool ex = false;
	while( r >= 0 ){
		QString str = stable->text(r,col);
		if( !str.isEmpty() ){
			if(!ex){
				i = r;
				ex = true;
			}
		}
		r--;
	}
	
	return i;
}

int MainForm::max(int *arr, int len)
{
	int m = 0;
	for(int i = 0; i < len; i++){
		if(arr[i] >= m){
			m = arr[i];
		}
	}
	return m;
}

void MainForm::clear()
{
	disconnect(table, SIGNAL( valueChanged(int, int)), this, SLOT( redefine(int, int) ) );
	disconnect(courseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kurs() ) );
	disconnect(ccourseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kross_kurs() ) );
	disconnect(konvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_konv() ) );
	disconnect(pvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pv() ) );
	disconnect(spLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_sp() ) );
	disconnect(prLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pr() ) );
	disconnect(obLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_ob() ) );
	disconnect(dkonvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_dkonv() ) );
	disconnect(percentLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_percent() ) );
	
	listView->clear();
	for(int i = 0; i < 99; i++){
		for(int j = 0; j < 12; j++){
			table->clearCell(i,j);
		}
	}
	dateLineEdit->clear();
	courseLineEdit->clear();
	ccourseLineEdit->clear();
	konvLineEdit->clear();
	pvLineEdit->clear();
	spLineEdit->clear();
	prLineEdit->clear();
	obLineEdit->clear();
	dkonvLineEdit->clear();
	percentLineEdit->clear();
	
	connect(table, SIGNAL( valueChanged(int, int)), this, SLOT( redefine(int, int) ) );
	connect(courseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kurs() ) );
	connect(ccourseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kross_kurs() ) );
	connect(konvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_konv() ) );
	connect(pvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pv() ) );
	connect(spLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_sp() ) );
	connect(prLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pr() ) );
	connect(obLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_ob() ) );
	connect(dkonvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_dkonv() ) );
	connect(percentLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_percent() ) );
}

void MainForm::newFile()
{
	if(modified == true){
		int res = QMessageBox::warning(this, tr("Perevodi"), tr("This file has been changed.\nDo you want to save it?"),
				QMessageBox::Yes | QMessageBox::Default,
				QMessageBox::No,
				QMessageBox::Cancel | QMessageBox::Escape);
		if(res == QMessageBox::Yes){
			save();
			closeFile();
		}
		if(res == QMessageBox::No){
			modified = false;
			closeFile();
		}
	}
	else{
		closeFile();
	}
}

void MainForm::closeFile()
{
	if(modified == false){
		clear();
		curFile = "";
		modified = false;
		Caption();
		delete [] tData;
		NUM = 0;
		tData = new Data[NUM];
		tab_2->setEnabled(FALSE);
		editDelAction->setEnabled(FALSE);
		toolsCalculate->setEnabled(FALSE);
		editCopyAction->setEnabled(FALSE);
		editCutAction->setEnabled(FALSE);
		editPasteAction->setEnabled(FALSE);
		Mark->setEnabled(FALSE);
		markDoneAction->setEnabled(FALSE);
		markNotDoneAction->setEnabled(FALSE);
		markNowDoneAction->setEnabled(FALSE);
		markClearAction->setEnabled(FALSE);
		statusBar()->message(tr("Closed"), 2000);
	}
	else{
		int res = QMessageBox::warning(this, tr("Perevodi"), tr("This file has been changed.\nDo you want to save it?"),
					       QMessageBox::Yes | QMessageBox::Default,
					       QMessageBox::No,
					       QMessageBox::Cancel | QMessageBox::Escape);
		if(res == QMessageBox::Yes){
			save();
			clear();
			curFile = "";
			modified = false;
			Caption();
			delete [] tData;
			NUM = 0;
			tData = new Data[NUM];
			tab_2->setEnabled(FALSE);
			editDelAction->setEnabled(FALSE);
			toolsCalculate->setEnabled(FALSE);
			editCopyAction->setEnabled(FALSE);
			editCutAction->setEnabled(FALSE);
			editPasteAction->setEnabled(FALSE);
			Mark->setEnabled(FALSE);
			markDoneAction->setEnabled(FALSE);
			markNotDoneAction->setEnabled(FALSE);
			markNowDoneAction->setEnabled(FALSE);
			markClearAction->setEnabled(FALSE);
			statusBar()->message(tr("Closed"), 2000);
		}
		if(res == QMessageBox::No){
			clear();
			curFile = "";
			modified = false;
			Caption();
			delete [] tData;
			NUM = 0;
			tData = new Data[NUM];
			tab_2->setEnabled(FALSE);
			editDelAction->setEnabled(FALSE);
			toolsCalculate->setEnabled(FALSE);
			editCopyAction->setEnabled(FALSE);
			editCutAction->setEnabled(FALSE);
			editPasteAction->setEnabled(FALSE);
			Mark->setEnabled(FALSE);
			markDoneAction->setEnabled(FALSE);
			markNotDoneAction->setEnabled(FALSE);
			markNowDoneAction->setEnabled(FALSE);
			markClearAction->setEnabled(FALSE);
			statusBar()->message(tr("Closed"), 2000);
		}
		if(res == QMessageBox::Cancel){
			statusBar()->message(tr("Cancelled"), 2000);
		}
	}
	
}

void MainForm::closeEvent(QCloseEvent *event)
{
	if(modified == true){
		int res = QMessageBox::warning(this, tr("Perevodi"), tr("This file has been changed.\nDo you want to save it?"), 
					       QMessageBox::Yes | QMessageBox::Default,
					       QMessageBox::No,
					       QMessageBox::Cancel | QMessageBox::Escape);
		if(res == QMessageBox::Yes){
			save();
			event->accept();
		}
		if(res == QMessageBox::No){
			event->accept();
		}
		if(res == QMessageBox::Cancel){
			event->ignore();
		}
	}
	else{
		event->accept();
	}
}

void MainForm::Caption()
{
	if(modified == true){
		if(curFile.isEmpty()){
			setCaption( tr("Perevodi %1 - Unsaved").arg(version) );
		}
		else{
			setCaption( tr("Perevodi %1 - %2 *").arg(version).arg(curFile) );
		}
	}
	else{
		if(curFile.isEmpty()){
			setCaption( tr("Perevodi %1").arg(version) );
		}
		else{
			setCaption( tr("Perevodi %1 - %2").arg(version).arg(curFile) );
		}
	}
}

void MainForm::open()
{
	if(modified == false){
		QString home = QDir::homeDirPath();
		QString fileName = QFileDialog::getOpenFileName(home, tr("Data files (*.dat)"), this );
		if(!fileName.isEmpty()){
			clear();
			curFile = fileName;
			readFile(curFile);
			modified = false;
			Caption();
			statusBar()->message(tr("Opened"), 2000);
		}
		else{
			statusBar()->message(tr("Cancelled"), 2000);
		}
	}
	else{
		int res = QMessageBox::warning(this, tr("Perevodi"), tr("This document has been changed.\nDo you want to save it?"), 
					       QMessageBox::Yes | QMessageBox::Default,
					       QMessageBox::No,
					       QMessageBox::Cancel | QMessageBox::Escape);
		if(res == QMessageBox::Yes){
			save();
		}
		if(res == QMessageBox::No){
			QString home = QDir::homeDirPath();
			QString fileName = QFileDialog::getOpenFileName(home, tr("Data files (*.dat)"), this );
			if(!fileName.isEmpty()){
				closeFile();
				curFile = fileName;
				readFile(curFile);
				modified = false;
				Caption();
				statusBar()->message(tr("Opened"), 2000);
			}
			else{
				statusBar()->message(tr("Cancelled"), 2000);
			}
		}
	}
}

void MainForm::save()
{
	if(!curFile.isEmpty()){
		writeFile(curFile);
		statusBar()->message(tr("Saved"), 2000);
	}
	else{
		saveAs();
	}
}

void MainForm::saveAs()
{
	QString home = QDir::homeDirPath();
	QString fileName = QFileDialog::getSaveFileName(home, tr("Data files (*.dat)"), this );
	if(!fileName.isEmpty()){
		if(fileName.right(4) != ".dat"){
			fileName += ".dat";
		}
		QFile file(fileName);
		if(file.exists()){
			int res = QMessageBox::warning(this, tr("Perevodi"), tr("This file already exists!\nDo you want to overwrite it?"),
					QMessageBox::Yes,
					QMessageBox::No | QMessageBox::Default | QMessageBox::Escape);
			if(res == QMessageBox::Yes){
				curFile = fileName;
				writeFile(fileName);
				statusBar()->message(tr("Saved"), 2000);
			}
		}
		else{
			curFile = fileName;
			writeFile(fileName);
			statusBar()->message(tr("Saved"), 2000);
		}
	}
	else{
		statusBar()->message(tr("Cancelled"), 2000);
	}
}

void MainForm::writeFile(QString &fileName)
{
	if(!fileName.isEmpty()){
		QFile file(fileName);
		if(file.exists()){
			file.remove();
		}
		
		if(file.open(IO_WriteOnly)){
			QDataStream out(&file);
			out.setVersion(5);
			
			QApplication::setOverrideCursor(waitCursor);
			
			out << (Q_UINT32)MagicNumber;
			out << (Q_UINT32)NUM;
			
// 			item = listView->firstChild();
			item = listView->lastItem();
			QString str;
			for(int i = 0; i < NUM; i++){
				for(int j = 0; j < 4; j++){
					str = item->text(j);
					out << str;
				}
				
				out << tData[i].kurs;
				out << tData[i].kross_kurs;
				out << tData[i].percent;
				for(int j = 0; j < 6; j++){
					str = tData[i].koef[j];
					out << str;
				}
				out << (Q_UINT16)tData[i].str;
				
				int len = 0;
				for(int j = 0; j < 99; j++){
					for(int k = 0; k < 12; k++){
						str = tData[i].table[j][k];
						if(!str.isEmpty()){
							len++;
						}
					}
				}
				
				out << (Q_UINT16)len;
				for(int j = 0; j < 99; j++){
					for(int k = 0; k < 12; k++){
						str = tData[i].table[j][k];
						if(!str.isEmpty()){
							out << (Q_UINT16)j << (Q_UINT16)k << (Q_UINT16)tData[i].mark[j][k] << tData[i].table[j][k];
						}
					}
				}
				item = item->itemAbove();
			}
			QApplication::restoreOverrideCursor();
			modified = false;	
			Caption();	
		}
		else{
			QMessageBox::warning(this, tr("Perevodi"), tr("Can't open file %1 for writing!").arg(fileName));
		}
	}
}

void MainForm::readFile(QString &fileName)
{
	QFile file(fileName);
	if(file.open(IO_ReadOnly)){
		QDataStream in(&file);
		in.setVersion(5);
		
		bool old = false;
		Q_UINT32 mn;
		in >> mn;
		
		
 		if(mn != MagicNumber && mn != OldMagicNumber){
 			QMessageBox::warning(this, tr("Perevodi"), tr("This is not a suitable file!"));
 		}
		else{
			if(mn == OldMagicNumber)
				old = true;
			
			Q_UINT32 num;
			in >> num;
			NUM = num;
			delete [] tData;
			tData = new Data[NUM];
			
			listView->clear();
			QString str;
			for(int i = 0; i < NUM; i++){
				item = new QListViewItem(listView);
				for(int j = 0; j < 4; j++){
					in >> str;
					item->setText(j, str);
				}
				listView->insertItem(item);
				
				in >> tData[i].kurs >> tData[i].kross_kurs;
				if(old == true)
					tData[i].percent = "0";
				else
					in >> tData[i].percent;
				
				for(int j = 0; j < 6; j++){
					in >> tData[i].koef[j];
				}
				Q_UINT16 n;
				in >> n;
				tData[i].str = n;
				
				Q_UINT16 len;
				in >> len;
				
				Q_UINT16 a,b,c;
				for(int j = 0; j < len; j++){
					in >> a >> b >> c >> str;
					tData[i].table[a][b] = str;
					tData[i].mark[a][b] = c;
				}
			}
			
			
			tab_2->setEnabled(TRUE);
			editDelAction->setEnabled(TRUE);
			toolsCalculate->setEnabled(TRUE);
			editCopyAction->setEnabled(TRUE);
			editCutAction->setEnabled(TRUE);
			editPasteAction->setEnabled(TRUE);
			Mark->setEnabled(TRUE);
			markDoneAction->setEnabled(TRUE);
			markNotDoneAction->setEnabled(TRUE);
			markNowDoneAction->setEnabled(TRUE);
			markClearAction->setEnabled(TRUE);
			listView->setSelected(listView->firstChild(), TRUE);
		}
	}
	else{
		QMessageBox::warning(this, tr("Perevodi"), tr("Can't open file %1 for reading").arg(fileName));
	}
}

void MainForm::addCell()
{
	QString date;
	DateDialog *dlg = new DateDialog(date);
	dlg->exec();
	
	if(dlg->result() == QDialog::Accepted){
		if(!date.isEmpty()){
			int count = 0;
			item = listView->firstChild();
			while(item != NULL){
				QString str = item->text(0);
				if(str == date){
					count++;
				}
				item = item->itemBelow();
			}
			
			if(count > 0){
				QMessageBox::warning(this, tr("Perevodi"), tr("Choose another date!") );
			}
			else{
				item = new QListViewItem( listView, date, "0", "0", "0" );
				listView->insertItem( item );
				
				Data *t = new Data[NUM];
				
				for(int i = 0; i < NUM; i++){
					for(int j = 0; j < 99; j++){
						for(int k = 0; k < 12; k++){
							t[i].table[j][k] = tData[i].table[j][k];
							t[i].mark[j][k] = tData[i].mark[j][k];
						}
					}
					for(int j = 0; j < 6; j++){
						t[i].koef[j] = tData[i].koef[j];
					}
					t[i].kurs = tData[i].kurs;
					t[i].kross_kurs = tData[i].kross_kurs;
					t[i].percent = tData[i].percent;
					t[i].str = tData[i].str;
					t[i].mod = tData[i].mod;
				}
				delete [] tData;
				NUM += 1;
				tData = new Data[NUM];
				for(int i = 0; i < NUM; i++){
					for(int j = 0; j < 99; j++){
						for(int k = 0; k < 12; k++){
							tData[i].mark[j][k] = 0;
						}
					}
					tData[i].str = 0;
				}
				for(int i = 0; i < NUM-1; i++){
					for(int j = 0; j < 99; j++){
						for(int k = 0; k < 12; k++){
							tData[i].table[j][k] = t[i].table[j][k];
							tData[i].mark[j][k] = t[i].mark[j][k];
						}
					}
					for(int j = 0; j < 6; j++){
						tData[i].koef[j] = t[i].koef[j];
					}
					tData[i].kurs = t[i].kurs;
					tData[i].kross_kurs = t[i].kross_kurs;
					tData[i].percent = t[i].percent;
					tData[i].str = t[i].str;
					tData[i].mod = t[i].mod;
				}
				delete [] t;
				
				if(NUM > 1){
					int pos = NUM - 1;
					tData[pos].kurs = tData[pos - 1].kurs;
 					tData[pos].kross_kurs = tData[pos - 1].kross_kurs;
					tData[pos].percent = tData[pos - 1].percent;
 					for(int i = 0; i < 6; i++){
 						tData[pos].koef[i] = tData[pos - 1].koef[i];
 					}
				}
				
				modified = true;
				Caption();
				tab_2->setEnabled(TRUE);
				editDelAction->setEnabled(TRUE);
				toolsCalculate->setEnabled(TRUE);
				editCopyAction->setEnabled(TRUE);
				editCutAction->setEnabled(TRUE);
				editPasteAction->setEnabled(TRUE);
				Mark->setEnabled(TRUE);
				markDoneAction->setEnabled(TRUE);
				markNotDoneAction->setEnabled(TRUE);
				markNowDoneAction->setEnabled(TRUE);
				markClearAction->setEnabled(TRUE);
			
 				listView->setSelected(item, TRUE);
// 				listView->setSelected(listView->lastItem(), TRUE);
				statusBar()->message(tr("Added"), 2000);
			}
		}
	}
	else{
		statusBar()->message( tr("Cancelled"), 2000 );
	}
	
}


void MainForm::loadData(QListViewItem *item1)
{
	if(item1){
		disconnect(table, SIGNAL( valueChanged(int, int)), this, SLOT( redefine(int, int) ) );
		disconnect(courseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kurs() ) );
		disconnect(ccourseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kross_kurs() ) );
		disconnect(konvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_konv() ) );
		disconnect(pvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pv() ) );
		disconnect(spLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_sp() ) );
		disconnect(prLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pr() ) );
		disconnect(obLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_ob() ) );
		disconnect(dkonvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_dkonv() ) );
		disconnect(percentLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_percent() ) );
		
		
		int pos = 0;
		int h = item1->height();
		pos = listView->itemPos( item1 )/h;
		pos = listView->childCount() - pos - 1;
		
		
		for(int i = 0; i < 99; i++){
			for(int j = 0; j < 12; j++){
				table->setText(i,j, tData[pos].table[i][j]);
				int color = tData[pos].mark[i][j];
				switch(color){
					case 1 : {table->setPixmap(i,j, QPixmap::fromMimeSource("1.jpg")); break;}
					case 2 : {table->setPixmap(i,j, QPixmap::fromMimeSource("2.jpg")); break;}
					case 3 : {table->setPixmap(i,j, QPixmap::fromMimeSource("3.jpg")); break;}
					default : { 
						QString str = table->text(i, j);
						table->clearCell(i, j);
						table->setText(i, j, str);
						break;
					}
				}
			}
		}
		dateLineEdit->setText( item1->text(0) );
		courseLineEdit->setText( tData[pos].kurs );
		ccourseLineEdit->setText( tData[pos].kross_kurs );
		konvLineEdit->setText( tData[pos].koef[0] );
		pvLineEdit->setText( tData[pos].koef[1] );
		spLineEdit->setText( tData[pos].koef[2] );
		prLineEdit->setText( tData[pos].koef[3] );
		obLineEdit->setText( tData[pos].koef[4] );
		dkonvLineEdit->setText( tData[pos].koef[5] );
		percentLineEdit->setText( tData[pos].percent );
		
		connect(table, SIGNAL( valueChanged(int, int)), this, SLOT( redefine(int, int) ) );
		connect(courseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kurs() ) );
		connect(ccourseLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_kross_kurs() ) );
		connect(konvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_konv() ) );
		connect(pvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pv() ) );
		connect(spLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_sp() ) );
		connect(prLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_pr() ) );
		connect(obLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_ob() ) );
		connect(dkonvLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_dkonv() ) );
		connect(percentLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( red_percent() ) );
	}
}

void MainForm::cut()
{
	copy();
	del();
}

void MainForm::copy()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			QTableSelection sel;
			if (table->selection(0).isEmpty()){
				sel = QTableSelection(table->currentRow(), table->currentColumn(), table->currentRow(), table->currentColumn());
			}
			else{
				sel = table->selection(0);
			}
	
			QString str;

			for (int i = 0; i < sel.numRows(); ++i) {
				if (i > 0)
					str += "\n";
				for (int j = 0; j < sel.numCols(); ++j) {
					if (j > 0)
						str += "\t";
					str += table->text(sel.topRow() + i, sel.leftCol() + j);
				}
			}
			QApplication::clipboard()->setText(str);
		}
	}
}

void MainForm::paste()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			QTableSelection sel;
			if (table->selection(0).isEmpty()){
				sel = QTableSelection(table->currentRow(), table->currentColumn(), table->currentRow(), table->currentColumn());
			}
			else{
				sel = table->selection(0);
			}
			
			QString str = QApplication::clipboard()->text();
			QStringList rows = QStringList::split("\n", str, true);
			int numRows = rows.size();
			int numCols = rows.first().contains("\t") + 1;

			if (sel.numRows() * sel.numCols() != 1 && (sel.numRows() != numRows || sel.numCols() != numCols)){
				QMessageBox::information(this, tr("Perevodi"), tr("The information cannot be pasted because the "								"copy and paste areas aren't the same size."));
				return;
			}
			
			item = listView->selectedItem();
			int pos = 0;
			int h = item->height();
			pos = listView->itemPos( item )/h;
			pos = listView->childCount() - pos - 1;
			
			for (int i = 0; i < numRows; ++i) {
				QStringList cols = QStringList::split("\t", rows[i], true);
				for (int j = 0; j < numCols; ++j) {
					int row = sel.topRow() + i;
					int col = sel.leftCol() + j;
					if (row < 99 && col < 12){
						 table->setText(row, col, cols[j]);
						 tData[pos].table[row][col] = cols[j];
					}
				}
			}
			modified = true;
			Caption();
		}
	}
	
}

void MainForm::del()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			item = listView->selectedItem();
			if(item){
				int pos = 0;
				int h = item->height();
				pos = listView->itemPos( item )/h;
				pos = listView->childCount() - pos - 1;
			
				for(int i = 0; i < 99; i++){
					for(int j = 0; j < 12; j++){
						if( table->isSelected(i, j) ){
							table->clearCell(i, j);
							tData[pos].table[i][j] = "";
							tData[pos].mark[i][j] = 0;
						}
					}
				}
				modified = true;
				Caption();
				statusBar()->message(tr("Deleted"), 2000);
			}
		}
	}
}

void MainForm::markDone()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			item = listView->selectedItem();
			if(item){
				int pos = 0;
				int h = item->height();
				pos = listView->itemPos( item )/h;
				pos = listView->childCount() - pos - 1;
				
				for(int i = 0; i < 99; i++){
					for(int j = 0; j < 12; j++){
						if( table->isSelected(i,j) ){
							table->setPixmap(i, j, QPixmap::fromMimeSource("1.jpg") );
							tData[pos].mark[i][j] = 1;
						}
					}
				}
				modified = true;
				Caption();
				statusBar()->message(tr("Marked as done"), 2000);
			}
		}
	}	
}

void MainForm::markNotDone()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			item = listView->selectedItem();
			if(item){
				int pos = 0;
				int h = item->height();
				pos = listView->itemPos( item )/h;
				pos = listView->childCount() - pos - 1;
				
				for(int i = 0; i < 99; i++){
					for(int j = 0; j < 12; j++){
						if( table->isSelected(i,j) ){
							table->setPixmap(i, j, QPixmap::fromMimeSource("2.jpg") );
							tData[pos].mark[i][j] = 2;
						}
					}
				}
				modified = true;
				Caption();
				statusBar()->message(tr("Marked as not-done"), 2000);
			}
		}
	}
}

void MainForm::markNowDone()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			item = listView->selectedItem();
			if(item){
				int pos = 0;
				int h = item->height();
				pos = listView->itemPos( item )/h;
				pos = listView->childCount() - pos - 1;
				
				for(int i = 0; i < 99; i++){
					for(int j = 0; j < 12; j++){
						if( table->isSelected(i,j) ){
							table->setPixmap(i, j, QPixmap::fromMimeSource("3.jpg") );
							tData[pos].mark[i][j] = 3;
						}
					}
				}
				modified = true;
				Caption();
				statusBar()->message(tr("Marked as In process"), 2000);
			}
		}
	}
}

void MainForm::markClear()
{
	if(tabWidget->currentPageIndex() == 1){
		if(table->isEnabled()){
			item = listView->selectedItem();
			if(item){
				int pos = 0;
				int h = item->height();
				pos = listView->itemPos( item )/h;
				pos = listView->childCount() - pos - 1;
				
				for(int i = 0; i < 99; i++){
					for(int j = 0; j < 12; j++){
						if( table->isSelected(i,j) ){
							QString str = table->text(i, j);
							table->clearCell(i, j);
							table->setText(i, j, str);
							tData[pos].mark[i][j] = 0;
						}
					}
				}
				modified = true;
				Caption();
				statusBar()->message(tr("Cleared"), 2000);
			}
		}
	}
}

QString MainForm::addSpaces(QString &string)
{
	QString s, result;
	
	int pos = string.find(".");
	if( pos != -1 ){
		QString r = string.right(string.length() - pos - 1);
		QString l = string.left(pos);
			
		int j = 0;
		for(int i = l.length()-1; i >= 0; --i){
			if(j == 3){
				j = 0;
				s += " ";
			}
			QChar c = l.at(i);
			s += c;
			j++;
		}
		result = s;
		for(int i = 0; i < (int)s.length(); i++){
			int k = s.length() - i - 1;
			result.at(k) = s.at(i);
		}	
			
		result += '.';
		result += r;
	}
	else{
		if( pos == -1 ){
			int j = 0;
			for(int i = string.length()-1; i >= 0; --i){
				if(j == 3){
					j = 0;
					s += " ";
				}
				QChar c = string.at(i);
				s += c;
				j++;
			}
			result = s;
			for(int i = 0; i < (int)s.length(); i++){
				int k = s.length() - i - 1;
				result.at(k) = s.at(i);
			}
		}
	}
	
	return result;
}

void MainForm::redefine(int i, int j)
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		QString text = table->text(i, j).simplifyWhiteSpace();
		if(!text.isEmpty()){
			if(j % 2 == 0)
				text = delZero(text);
		}
		
		if( text.length() > 3){
			if(j % 2 == 0){
				text.replace(" ", "");
				text = addSpaces(text);
			}
		}
		
		table->setText(i, j, text);
		tData[pos].table[i][j] = text;
		modified = true;
		Caption();
	}
}

void MainForm::red_kurs()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
 		tData[pos].kurs = courseLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_kross_kurs()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
 		tData[pos].kross_kurs = ccourseLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_konv()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].koef[0] = konvLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_pv()
{	
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].koef[1] = pvLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_sp()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].koef[2] = spLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_pr()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].koef[3] = prLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_ob()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].koef[4] = obLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_dkonv()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].koef[5] = dkonvLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::red_percent()
{
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		tData[pos].percent = percentLineEdit->text();
		modified = true;
		Caption();
	}
}

void MainForm::print()
{
	QString date;
	
	item = listView->selectedItem();
	if(item){
		int pos = 0;
		int h = item->height();
		pos = listView->itemPos( item )/h;
		pos = listView->childCount() - pos - 1;
		
		date = item->text(0);
	}
	else{
		date = "";
	}
	
// 	QString date = "";
	DateInterval *dateInt = new DateInterval(date);
	dateInt->exec();
	
	if(dateInt->result() == QDialog::Rejected)
		return;
	else if(dateInt->result() == QDialog::Accepted){
		
		QString str,a;
		
		if(tabWidget->currentPageIndex() == 1){ //Today
			//Headers
			if(table->isEnabled()){ 
			
				if(date == "all"){
					item = listView->firstChild();
					
					str = "";
					
					while(item != NULL){
						int pos = 0;
						int h = item->height();
						pos = listView->itemPos( item )/h;
						pos = listView->childCount() - pos - 1;
						
						str += "<p>";
						str += item->text(0);
						str += "</p>\n<p>";
						str += tr("Dollar course: ");
						str += tData[pos].kurs;
						str += "</p>\n";
				
						str += "<table width=\"100%\" border=1 cellspacing=0><tr width=\"100%\" align=\"center\"><td>";
				
						for(int i = 0; i < 12; i++){
							str += "<b>";
							str += table->horizontalHeader()->label(i);
							str += "</b>";
							if(i == 11){
								str += "</td></tr>";
							}
							else{
								str += "</td><td>";
							}
						}
// 						int r = lastRow(table, 0);
						int r = tData[pos].str;
						for(int i = 0; i <= r; i++){
							str += "<tr>";
							for(int j = 0; j < 12; j++){
								str += "<td align=\"right\">";
// 								a = table->text(i, j);
								a = tData[pos].table[i][j];
								if(a.isEmpty()){
									str += "-----";
								}
								else{
									str += a;
								}
								str += "</td>";
							}
							str += "</tr>";
						}
						
						str += "</table>";
						
						item = item->itemBelow();
					}
//   					printf("%s\n", str.latin1());
				}
				else{
					QStringList sl = QStringList::split(";", date);
					QString beg_d = forDate(sl[0]);
					QDate beg_date = QDate::fromString(beg_d, Qt::ISODate);
					QDate end_date;
					if(sl[1].isEmpty())
						end_date = beg_date;
					else
						end_date = QDate::fromString(forDate(sl[1]), Qt::ISODate);
					
					if(end_date < beg_date){
						QMessageBox::warning(this, tr("Perevodi"), tr("End date must be less or equal than begin date!") );
						return;
					}
					
					QString str1;
					
					item = listView->lastItem();
					QString beg_s = item->text(0);
					QString end_s = item->text(0);
					bool ex = false;
					
					while(item != NULL){
						str1 = item->text(0);
						str1= forDate(str1);
						QDate d = QDate::fromString(str1, Qt::ISODate);
						
						if(d >= beg_date){
							if(ex == false){
								beg_s = item->text(0);
								ex = true;
							}
						}
						if(d <= end_date){
							end_s = item->text(0);
						}
						
						item = item->itemAbove();
					}
					
					item = listView->findItem(end_s, 0);
					if(item){
						QListViewItem *item1;
						item1 = listView->findItem(beg_s, 0);
						
						if(item1){
							bool ok = true;
							
							str = "";
							
							while(ok){
								int pos = 0;
								int h = item->height();
								pos = listView->itemPos( item )/h;
								pos = listView->childCount() - pos - 1;
						
								str += "<p>";
								str += item->text(0);
								str += "</p>\n<p>";
								str += tr("Dollar course: ");
								str += tData[pos].kurs;
								str += "</p>\n";
				
								str += "<table width=\"100%\" border=1 cellspacing=0><tr width=\"100%\" align=\"center\"><td>";
				
								for(int i = 0; i < 12; i++){
									str += "<b>";
									str += table->horizontalHeader()->label(i);
									str += "</b>";
									if(i == 11){
										str += "</td></tr>";
									}
									else{
										str += "</td><td>";
									}
								}
								int r = tData[pos].str;
								for(int i = 0; i <= r; i++){
									str += "<tr>";
									for(int j = 0; j < 12; j++){
										str += "<td align=\"right\">";
										a = tData[pos].table[i][j];
										if(a.isEmpty()){
										str += "-----";
										}
										else{
										str += a;
										}
										str += "</td>";
									}
									str += "</tr>";
								}
						
								str += "</table>";	
								
								item = item->itemBelow();
								if(item == item1->itemBelow())
									ok = false;
							}
// 							printf("%s\n", str.latin1());
						}
					}
				}
				
			}
			
		}
		else{
			if(tabWidget->currentPageIndex() == 0){ //All
				if(listView->childCount() == 0)
					return;
				str += "<table width=\"100%\" border=1 cellspacing=0><tr width=\"100%\" align=\"center\"><td>";
				
				for(int i = 0; i < 4; i++){
					str += "<b>";
					str += listView->header()->label(i);
					str += "</b>";
					if(i == 3){
						str += "</td></tr>";
					}
					else{
						str += "</td><td>";
					}
				}
				
				if(date == "all"){
					item = listView->firstChild();
					while(item != NULL){
						str += "<tr>";
						for(int i = 0; i < 4; i++){
							str += "<td align=\"center\">";
							str += item->text(i);
							str += "</td>";
						}
						str += "</tr>";
						item = item->itemBelow();
					}
				}
				else{
					QStringList sl = QStringList::split(";", date);
					QString beg_d = forDate(sl[0]);
					QDate beg_date = QDate::fromString(beg_d, Qt::ISODate);
					QDate end_date;
					if(sl[1].isEmpty())
						end_date = beg_date;
					else
						end_date = QDate::fromString(forDate(sl[1]), Qt::ISODate);
					
					if(end_date < beg_date){
						QMessageBox::warning(this, tr("Perevodi"), tr("End date must be less or equal than begin date!") );
						return;
					}
					
					QString str1;
					
					item = listView->lastItem();
					QString beg_s = item->text(0);
					QString end_s = item->text(0);
					bool ex = false;
					
					while(item != NULL){
						str1 = item->text(0);
						str1= forDate(str1);
						QDate d = QDate::fromString(str1, Qt::ISODate);
						
						if(d >= beg_date){
							if(ex == false){
								beg_s = item->text(0);
								ex = true;
							}
						}
						if(d <= end_date){
							end_s = item->text(0);
						}
						
						item = item->itemAbove();
					}
					
					item = listView->findItem(end_s, 0);
					if(item){
						QListViewItem *item1;
						item1 = listView->findItem(beg_s, 0);
						
						if(item1){
							bool ok = true;

							while(ok){
								str += "<tr>";
								for(int i = 0; i < 4; i++){
									str += "<td align=\"center\">";
									str += item->text(i);
									str += "</td>";
								}
								str += "</tr>";
								
								item = item->itemBelow();
								if(item == item1->itemBelow())
									ok = false;
							}
						}
					}
				}
			}
//   			printf("%s\n", str.latin1());
		}
		
		QPrinter printer;
		printer.setOrientation(QPrinter::Landscape);
		
		if(printer.setup(this)){
			QPainter painter(&printer);
			int pageHeight = painter.window().height() - 2*48;
			QFont f("Helvetica", 8);
			QSimpleRichText richText(str, f, "", 0, 0, pageHeight);
			richText.setWidth(&painter, painter.window().width());
			int numPages = (int)ceil( (double)richText.height()/pageHeight);
			int index;
			for(int i = 0; i < (int)printer.numCopies(); ++i){
				for(int j = 0; j < numPages; ++j){
					if( i > 0 || j > 0)
						printer.newPage();
					if(printer.pageOrder() == QPrinter::LastPageFirst){
						index = numPages -j - 1;
					}
					else{
						index = j;
					}
					printPage(&painter, richText, pageHeight, index);
				}
			}
		}
	}
}

void MainForm::printPage(QPainter *painter, const QSimpleRichText &richText, int pageHeight, int index)
{
	QRect rect(0, index * pageHeight + 48, richText.width(), pageHeight);
	painter->saveWorldMatrix();
	painter->translate(0, -rect.y());
	richText.draw(painter, 0, 48, rect, colorGroup());
	painter->restoreWorldMatrix();
	QFont f("Helvetica", 8);
	painter->setFont(f);
	painter->drawText(painter->window(), AlignCenter | AlignBottom, QString::number(index+1));
}

void MainForm::about()
{
	QMessageBox::about(this, tr("Perevodi"), tr("<h2>Perevodi %1</h2><p>Copyright &copy; 2005, piton, MIPT<p>Mailto: <a href=mailto:piton3000@rambler.ru>piton3000@rambler.ru</a>").arg(version) );
}

MainForm::~MainForm()
{
   
}


void MainForm::languageChange()
{
	setCaption( tr( "Perevodi %1" ).arg(version) );
    listView->header()->setLabel( 0, tr( "Date" ) );
    listView->header()->setLabel( 1, tr( "Delta" ) );
    listView->header()->setLabel( 2, tr( "Sum" ) );
    listView->header()->setLabel( 3, tr( "%" ) );
    tabWidget->changeTab( tab, tr( "All" ) );
    dateLabel->setText( tr( "Date" ) );
    dateLineEdit->setText( QString::null );
    courseLabel->setText( tr( "Course" ) );
    courseLineEdit->setText( QString::null );
    ccourseLabel->setText( tr( "Cross course" ) );
    ccourseLineEdit->setText( QString::null );
    konvLabel->setText( tr( "Konvertaciya" ) );
    konvLineEdit->setText( QString::null );
    pvLabel->setText( tr( "Progon valuti" ) );
    pvLineEdit->setText( QString::null );
    spLabel->setText( tr( "Stoimost perevoda" ) );
    spLineEdit->setText( QString::null );
    prLabel->setText( tr( "Progon rublya" ) );
    obLabel->setText( tr( "Obnalichka" ) );
    dkonvLabel->setText( tr( "Dopolnitelnaya konvertaciya" ) );
    percentLabel->setText( tr("Percent") );
    table->horizontalHeader()->setLabel( 0, tr( "Bank(prihod)" ) );
    table->horizontalHeader()->setLabel( 1, tr( "Firm" ) );
    table->horizontalHeader()->setLabel( 2, tr( "Valuta(prihod)" ) );
    table->horizontalHeader()->setLabel( 3, tr( "Firm" ) );
    table->horizontalHeader()->setLabel( 4, tr( "Kassa(prihod)" ) );
    table->horizontalHeader()->setLabel( 5, tr( "Firm" ) );
    table->horizontalHeader()->setLabel( 6, tr( "Bank(uhod)" ) );
    table->horizontalHeader()->setLabel( 7, tr( "Firm" ) );
    table->horizontalHeader()->setLabel( 8, tr( "Valuta(uhod)" ) );
    table->horizontalHeader()->setLabel( 9, tr( "Firm" ) );
    table->horizontalHeader()->setLabel( 10, tr( "Kassa(uhod)" ) );
    table->horizontalHeader()->setLabel( 11, tr( "Firm" ) );
    calcButton->setText( tr( "Calculate!" ) );
    tabWidget->changeTab( tab_2, tr( "Today" ) );
    fileQuitAction->setText( tr( "Quit" ) );
    fileQuitAction->setMenuText( tr( "&Quit" ) );
    fileQuitAction->setAccel( tr( "Ctrl+Q" ) );
    fileQuitAction->setStatusTip( tr("Closes the application") );
    fileNewAction->setText( tr( "New" ) );
    fileNewAction->setMenuText( tr( "&New" ) );
    fileNewAction->setAccel( tr( "Ctrl+N" ) );
    fileNewAction->setStatusTip( tr("Creates a new file") );
    fileOpenAction->setText( tr( "Open" ) );
    fileOpenAction->setAccel( tr( "Ctrl+O" ) );
    fileOpenAction->setStatusTip( tr("Openes an existing file") );
    filesaveAction->setText( tr( "Save" ) );
    filesaveAction->setMenuText( tr( "&Save" ) );
    filesaveAction->setAccel( tr( "Ctrl+S" ) );
    filesaveAction->setStatusTip( tr("Saves the current file") );
    fileSave_AsAction->setText( tr( "Save As" ) );
    fileSave_AsAction->setMenuText( tr( "Save As" ) );
    fileSave_AsAction->setStatusTip( tr("Saves the current file with a new filename") );
    fileCloseAction->setText( tr( "Close" ) );
    fileCloseAction->setMenuText( tr( "&Close" ) );
    fileCloseAction->setAccel( tr( "Ctrl+W" ) );
    fileCloseAction->setStatusTip( tr("Closes the current file") );
    filePrintAction->setText( tr( "Print" ) );
    filePrintAction->setMenuText( tr( "&Print" ) );
//     filePrintAction->setAccel( tr( "Ctrl+P" ) );
    filePrintAction->setAccel(CTRL + Key_P);
    filePrintAction->setStatusTip( tr("Prints the current file") );
    editAdd_cellAction->setText( tr( "Add cell" ) );
    editAdd_cellAction->setMenuText( tr( "&Add cell" ) );
    editAdd_cellAction->setStatusTip( tr("Adds a new point in list") );
    editCopyAction->setText( tr("Copy") );
    editCopyAction->setAccel( tr("Ctrl+C") );
    editCopyAction->setStatusTip( tr("Copies selected text from the table") );
    editCutAction->setText( tr("Cut") );
    editCutAction->setAccel( tr("Ctrl+X") );
    editCutAction->setStatusTip( tr("Cuts selected text from the table") );
    editPasteAction->setText( tr("Paste") );
    editPasteAction->setAccel( tr("Ctrl+V") );
    editPasteAction->setStatusTip( tr("Pastes selected text from the table") );
    editDelAction->setText( tr("Delete") );
    editDelAction->setMenuText( tr("&Delete") );
    editDelAction->setAccel( tr("Del") );
    editDelAction->setStatusTip( tr("Deletes selected text from the table") );
    markDoneAction->setText( tr("Done") );
    markDoneAction->setStatusTip( tr("Marks selected cells as \"Done\" (Green)") );
    markNotDoneAction->setText( tr("Not done") );
    markNotDoneAction->setStatusTip( tr("Marks selected cells as \"Not done\" (Red)") );
    markNowDoneAction->setText( tr("In process") );
    markNowDoneAction->setStatusTip( tr("Marks selected cells as \"In process\" (Yellow)") );
    markClearAction->setText( tr("Clear") );
    markClearAction->setStatusTip( tr("Removes markers from selected cells") );
    toolsCalculate->setText( tr("Calculate") );
    toolsCalculate->setMenuText( tr("Calculate") );
    toolsCalculate->setAccel( tr("F9") );
    helpAbout->setMenuText( tr("A&bout") );
    helpAbout->setText( tr("About") );
    
    if (MenuBarEditor->findItem(1))
        MenuBarEditor->findItem(1)->setText( tr( "&File" ) );
    if (MenuBarEditor->findItem(2))
        MenuBarEditor->findItem(2)->setText( tr( "&Edit" ) );
    if (MenuBarEditor->findItem(3))
	    MenuBarEditor->findItem(3)->setText( tr( "&Tools" ) );
    if (MenuBarEditor->findItem(4))
	    MenuBarEditor->findItem(4)->setText( tr( "&Help" ) );
    
}


