#include "mainform.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <qtimer.h>
#include <qregexp.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qcanvas.h>
#include <qdragobject.h>

#include "addserver.h"
#include "creategame.h"
#include "findgame.h"
#include "gamedialog.h"
#include "helpbrowser.h"
#include "cleardialog.h"

#include "checker.h"

#define ROWS 20
#define COLS 20
#define PAUSE 1000

MyNetworkObject *MNO = new MyNetworkObject();
LogikChecker *checker = new LogikChecker;
char mapdata[ROWS*2*COLS];
int countCanvas;
/*
 *  Constructs a mainform as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
mainform::mainform( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "mainform" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );
    mainformLayout = new QGridLayout( centralWidget(), 1, 1, 11, 6, "mainformLayout"); 
    setIcon(QPixmap::fromMimeSource("icon.png"));

    layout1 = new QVBoxLayout( 0, 0, 6, "layout1"); 
    layout2 = new QHBoxLayout( 0, 0, 6, "layou2" );
    layout3 = new QVBoxLayout( 0, 0, 6, "layout3");
    layout4 = new QHBoxLayout( 0, 0, 6, "layout4");
    
    logicTextLabel = new QLabel( centralWidget(), "logicTextLabel" );
    layout1->addWidget( logicTextLabel );

    logicTextEdit = new QTextEdit( centralWidget(), "logicTextEdit" );
    layout2->addWidget( logicTextEdit );

    commandsListView = new QListView(centralWidget(), "commandsListView");
    commandsListView->setMaximumSize(200,3000);
    commandsListView->setResizeMode( QListView::AllColumns );
    commandsListView->addColumn("Language");
    
    addButton = new QPushButton("Paste", centralWidget(), "addButton");
    helpButton = new QPushButton("Help", centralWidget(), "helpButton");
    
    layout4->addWidget( addButton );
    layout4->addWidget( helpButton );
    
    layout3->addWidget( commandsListView );
    layout3->addLayout( layout4 );
    
    layout2->addLayout( layout3 );    
    
    layout1->addLayout( layout2 );
    mainformLayout->addLayout( layout1, 0, 0 );

    // actions
    fileNewAction = new QAction( this, "fileNewAction" );
    fileNewAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "new.png" ) ) );
    fileLoadAction = new QAction( this, "fileLoadAction" );
    fileLoadAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "open.png" ) ) );
    filesaveAction = new QAction( this, "filesaveAction" );
    filesaveAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "save.png" ) ) );
    fileSave_AsAction = new QAction( this, "fileSave_AsAction" );
    fileExitAction = new QAction( this, "fileExitAction" );
    gameCreate_gameAction = new QAction( this, "gameCreate_gameAction" );
    gameCreate_gameAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "create.png" ) ) );
    gameFind_gameAction = new QAction( this, "gameFind_gameAction" );
    gameFind_gameAction->setIconSet( QIconSet( QPixmap::fromMimeSource( "find.png" ) ) );
    gameAddServerAction = new QAction(this, "gameAddServerAction");
    gameClearDataAction = new QAction(this, "gameClearDataAction");
    editorClearAction = new QAction( this, "editorClearAction" );
    editorCheck_for_errorsAction = new QAction( this, "editorCheck_for_errorsAction" );
    editorCheck_for_errorsAction->setIconSet( QIconSet( QPixmap::fromMimeSource("check.png") ) );   
    helpHelpAction = new QAction( this, "helpHelpAction" );
    helpHelpAction->setIconSet( QIconSet( QPixmap::fromMimeSource("help.png") ) );
    helpAboutAction = new QAction( this, "helpAboutAction" );


    // toolbars
    Toolbar = new QToolBar( QString(""), this, DockTop ); 

    fileNewAction->addTo( Toolbar );
    fileLoadAction->addTo( Toolbar );
    filesaveAction->addTo( Toolbar );
    Toolbar->addSeparator();
    gameCreate_gameAction->addTo( Toolbar );
    gameFind_gameAction->addTo( Toolbar );
    Toolbar->addSeparator();
    editorCheck_for_errorsAction->addTo( Toolbar );
    helpHelpAction->addTo( Toolbar );


    // menubar
    MenuBarEditor = new QMenuBar( this, "MenuBarEditor" );


    File = new QPopupMenu( this );
    fileNewAction->addTo( File );
    fileLoadAction->addTo( File );
    filesaveAction->addTo( File );
    fileSave_AsAction->addTo( File );
    File->insertSeparator();
    fileExitAction->addTo( File );
    MenuBarEditor->insertItem( QString(""), File, 1 );

    Game = new QPopupMenu( this );
    gameCreate_gameAction->addTo( Game );
    gameFind_gameAction->addTo( Game );
    Game->insertSeparator();
    gameAddServerAction->addTo( Game );
    gameClearDataAction->addTo( Game );
    MenuBarEditor->insertItem( QString(""), Game, 2 );

    Editor = new QPopupMenu( this );
    editorClearAction->addTo( Editor );
    editorCheck_for_errorsAction->addTo( Editor );    
    MenuBarEditor->insertItem( QString(""), Editor, 3 );

    Help = new QPopupMenu( this );
    helpHelpAction->addTo( Help );
    helpAboutAction->addTo( Help );
    MenuBarEditor->insertItem( QString(""), Help, 4 );

    languageChange();
    resize( QSize(670, 460).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    
    modified = false;
    setCurrentFile("");
    
    timer = new QTimer( this ); 
    
    logicTextEdit->viewport()->setAcceptDrops( false );
    setAcceptDrops( true );
    
    connect(fileNewAction, SIGNAL( activated() ), this, SLOT( newFile() ) );
    connect(fileLoadAction, SIGNAL( activated() ), this, SLOT( open() ));
    connect(filesaveAction, SIGNAL( activated() ), this, SLOT( save() ) );
    connect(fileSave_AsAction, SIGNAL( activated() ), this, SLOT( saveAs() ));
    connect(fileExitAction, SIGNAL( activated() ), this, SLOT( close() ) );
    connect(gameCreate_gameAction, SIGNAL( activated() ), this, SLOT( create() ));
    connect(gameFind_gameAction, SIGNAL( activated() ), this, SLOT( find() ) );
    connect(gameAddServerAction, SIGNAL( activated() ), this, SLOT( add() ) );
    connect(editorClearAction, SIGNAL( activated() ), this, SLOT( clearEditor() ) );    
    connect(helpHelpAction, SIGNAL( activated() ), this, SLOT( mainHelp() ) );
    connect(helpAboutAction, SIGNAL( activated() ), this, SLOT( about() ) );
    connect(logicTextEdit, SIGNAL( textChanged() ), this, SLOT(logicModified()) );
    connect(timer, SIGNAL( timeout() ), this, SLOT( showGame() ) );
    connect(commandsListView, SIGNAL( doubleClicked( QListViewItem *, const QPoint &, int ) ), this, SLOT( insertFunction() ) );
    connect(addButton, SIGNAL( clicked() ), this, SLOT( insertFunction() ) );
    connect(editorCheck_for_errorsAction, SIGNAL( activated() ), this, SLOT( check() ) );
    connect(gameClearDataAction, SIGNAL( activated() ), this, SLOT( clearData() ) );
    connect(helpButton, SIGNAL( clicked() ), this, SLOT( langHelp() ) );
    
    for(int i = 0; i < ROWS*2*COLS; i++) {
    	mapdata[i] = ' ';
    }
    fillFunctions();
}
void mainform::dragEnterEvent( QDragEnterEvent *event )
{
	event->accept( QUriDrag::canDecode( event ) );
}
void mainform::dropEvent( QDropEvent *event )
{
	QStringList fileNames;
	if( QUriDrag::decodeLocalFiles( event, fileNames ) ){
		loadFile( fileNames[0] );
	}
}
void mainform::newFile()
{
	if( modified == true ) {
		int res = QMessageBox::warning(this, tr("Game client"), tr("Your game logic has been changed.\n"
		"Do you want to save it?"),
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape);
		if ( res == QMessageBox::Yes ){
			save();
			clearEditor();
			setCurrentFile("");
		}
		if ( res == QMessageBox::No ){
			clearEditor();
			setCurrentFile("");
		}
	}
	else {
		clearEditor();
		setCurrentFile("");
	}
}
void mainform::open()
{
	QString dir = QDir::homeDirPath();
	if( modified == false){
		QString fileName = QFileDialog::getOpenFileName(dir, tr("Text files (*.txt)"), this);
		if(!fileName.isEmpty()){
			loadFile(fileName);
		}
	}
	else {
		int res = QMessageBox::warning(this, tr("Game client"), tr("Your game logic has been changed.\n"
		"Do you want to save it?"),
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape);
		if ( res == QMessageBox::Yes ){
			save();
		}
		else if ( res == QMessageBox::No){
			QString fileName = QFileDialog::getOpenFileName(dir, tr("Text files (*.txt)"), this);
			if(!fileName.isEmpty()){
				loadFile(fileName);
			}
		}
	}
}
void mainform::save()
{
	if( curFile.isEmpty() ){
		saveAs();
	}
	else {
		saveFile(curFile);
	}
}
void mainform::saveAs()
{
	QString dir = QDir::homeDirPath();
	QString fileName = QFileDialog::getSaveFileName(dir, tr("Text files (*.txt)"), this);
	if( QFile::exists( fileName ) ){
		QString message;
		message = tr("File %1 is already exists.\nDo you want to overwrite it?").arg( QDir::convertSeparators( fileName) );		
		int res = QMessageBox::warning(this, tr("Game client"), message,
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No | QMessageBox::Escape);
		if ( res == QMessageBox::Yes ){
			if(!fileName.isEmpty()){
			saveFile(fileName);
			}
		}
	}
	else {
		if(!fileName.isEmpty()){
			saveFile(fileName);
		}
	}
}
void mainform::loadFile(const QString &fileName)
{
	QFile file(fileName);
	if(file.open(IO_ReadOnly)){
		QTextStream in(&file);
		QString text;
		QChar c;
		while(!in.atEnd()){
			in >> c;
			text += c;
		}
		logicTextEdit->clear();
		logicTextEdit->setText(text);
		file.close();
		statusBar()->message("Logic loaded", 2000);
		modified = false;
		setCurrentFile(fileName);
	}
}
void mainform::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if(file.open(IO_WriteOnly)){
		QTextStream out(&file);
		out << logicTextEdit->text();
		file.close();
		statusBar()->message("Logic saved", 2000);
		modified = false;
		setCurrentFile(fileName);
	}
}
void mainform::setCurrentFile(const QString &fileName)
{
	QString caption;
	curFile = fileName;
	if( !curFile.isEmpty() ){
		caption = tr("%1 - %2").arg( strippedName( curFile ) ).arg( tr("NPRG client 1.0b") );
	}
	else {
		caption = tr("Newfile - %1").arg( tr("NPRG client 1.0b") );
	}
	setCaption( caption );
}
QString mainform::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}
void mainform::logicModified()
{
	modified = true;
}
void mainform::clearEditor()
{
	QString text;
	text = logicTextEdit->text();
	if( !text.isEmpty() ){
		logicTextEdit->clear();
	}
}
void mainform::add()
{
	AddServer addserver(this);
	addserver.exec();
	if( addserver.result() == QDialog::Accepted ){
		statusBar()->message( tr("A new server IP added to a configuration file"), 2000 );
	}
	else if( addserver.result() == QDialog::Rejected ){
		statusBar()->message( tr("Cancelled"), 2000 );
	}
}
void mainform::create()
{
	if( modified == false ){
		CreateGame creategame(this);
		creategame.exec();
		if( creategame.result() == QDialog::Accepted ){
			statusBar()->message( tr("Game created"), 2000 );
			game();
		}
		else if( creategame.result() == QDialog::Rejected ){
			statusBar()->message( tr("Cancelled"), 2000);
		}
	}
	else {
		int res = QMessageBox::warning(this, tr("Game client"), tr("Your game logic has been changed.\n"
				"Do you want to save it?"),
				QMessageBox::Yes | QMessageBox::Default,
				QMessageBox::No,
				QMessageBox::Cancel | QMessageBox::Escape);
		if ( res == QMessageBox::Yes ){
			save();
		}
		else if ( res ==QMessageBox::No ){
			CreateGame creategame(this);
			creategame.exec();
			if( creategame.result() == QDialog::Accepted ){
				statusBar()->message( tr("Game created"), 2000 );
				game();
			}
			else if( creategame.result() == QDialog::Rejected ){
				statusBar()->message( tr("Cancelled"), 2000);
			}
		}
	}
}
void mainform::find()
{
	if( modified == false ){
		FindGame findgame(this);
		findgame.exec();
		if( findgame.result() == QDialog::Accepted ){
			statusBar()->message( tr("Joined to game"), 2000 );
			game();
		}
		else if( findgame.result() == QDialog::Rejected ) {
			statusBar()->message( tr("Cancelled"), 2000 );
		}
	}
	else {
		int res = QMessageBox::warning(this, tr("Game client"), tr("Your game logic has been changed.\n"
				"Do you want to save it?"),
				QMessageBox::Yes | QMessageBox::Default,
				QMessageBox::No,
				QMessageBox::Cancel | QMessageBox::Escape);
		if ( res == QMessageBox::Yes ){
			save();
		}
		else if ( res == QMessageBox::No ){
			FindGame findgame(this);
			findgame.exec();
			if( findgame.result() == QDialog::Accepted ){
				statusBar()->message( tr("Joined to game"), 2000 );
				game();
			}
			else if( findgame.result() == QDialog::Rejected ) {
				statusBar()->message( tr("Cancelled"), 2000 );
			}
		}
	}
}
void mainform::game()
{
	countCanvas = 0;
	QString home = QDir::homeDirPath();
	QDir dir = QDir( home.append("/.client_data/pixmaps") );
	
	if ( !dir.exists() ){
		QMessageBox::critical(this, tr("Game dialog"), tr("Directory with necessary pictures does not exist!\nIt is impossible to continue the game.") );
	}
	else {
		gamedialog = new GameDialog;
		gamedialog->show();
		gamedialog->changeCanvas( "text" );
		gamedialog->showText("Waiting...=)", -1 );
		timer->start( PAUSE, FALSE );
	}
}
void mainform::showGame()
{
	//GameDialog *gamedialog = new GameDialog;
	int res = MNO->getData(mapdata, ROWS*2*COLS);
	if( res == 0 ){
		countCanvas++;
		if( countCanvas <= 1){
		gamedialog->changeCanvas( "map" );
		}
		gamedialog->showMap(mapdata);
	}
	if( res == -1 ){
		gamedialog->changeCanvas( "text" );
		gamedialog->showText("Waiting...=)", res );
	}
	if( ( res > 0 ) && ( res != 50 ) && ( res != 100 ) ){
		QString winner, number;
		winner = "The winner is bot number ";
		number.setNum( res );
		winner.append( number );
		winner.append(" !");
		gamedialog->changeCanvas( "text" );
		gamedialog->showText( winner, res );
		timer->stop();
	}
	if( res == 50 ){
		gamedialog->changeCanvas( "text" );
		gamedialog->showText( "Drawn game !", res );
		timer->stop();
	}
	if( res == 100 ){
		gamedialog->changeCanvas( "text" );
		gamedialog->showText( "You win!!!\n", res );
		timer->stop();
	}
}
void mainform::help(const QString &fileName)
{
	HelpBrowser *helpbrowser = new HelpBrowser;
	helpbrowser->show();
	//helpbrowser->showPage("index.htm");
	helpbrowser->showPage( fileName );
}
void mainform::mainHelp()
{
	help( "index.htm" );
}
void mainform::check()
{
	int numStr;
	char response[30];
	char *logik;
	QString currentText;
	QString message;
	
	currentText = logicTextEdit->text();
	logik = (char*)currentText.data();
	int res = checker->check(logik,&numStr,response);
	
	switch( res ){
		case 0 : {
			statusBar()->message(tr("Logic OK! No syntax errors were found!"), 4000);
			printf("Logik OK!\n");
			break;
		}
		case -2 : {
			statusBar()->message(tr("Warning! Logic might be incorrect!"), 4000);
			QMessageBox::warning(this, tr("NPRG client"), tr("Warning! Logic might be incorrect!"));
			printf("Warning! Logik might be incorrect!\n");
			break;
		}
		case -1 : {
			statusBar()->message(tr("Error! Logic is incorrect!"), 4000);
			printf("Error at line %d. %s\n",numStr,response);
			
			message = tr("Logic is incorrect!\n\n");
			message.append( tr("Error at line %1.\n%2").arg(numStr).arg(response) );
			QMessageBox::critical(this, tr("NPRG client"), message);
			break;
		}
	}
}
void mainform::clearData()
{
	ClearDialog cleardialog(this);
	cleardialog.exec();
	if( cleardialog.result() == QDialog::Accepted ){
		statusBar()->message( tr("Cleared"), 2000 );
	}
	else if( cleardialog.result() == QDialog::Rejected ){
		statusBar()->message( tr("Cancelled"), 2000 );
	}
}
void mainform::fillFunctions()
{
	commandsListView->setSorting(-1);
	
	QStringList list;
	QString name,line;
	QString fileName = QDir::homeDirPath();
	fileName.append("/.client_data/language");
	
	element1 = new QListViewItem(commandsListView, "Language");
	element1->setPixmap( 0, QPixmap::fromMimeSource( "gear.png" ) );
	commandsListView->insertItem(element1);
	element2 = new QListViewItem(element1, "Waypoints");
	element1->insertItem(element2);

	QFile file( fileName + "/properties/waypoints/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem(element1, "Waypoint");
	element1->insertItem(element2);
	file.setName( fileName + "/properties/waypoint/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem(element1, "Enemy properties");
	element1->insertItem(element2);
	file.setName( fileName + "/properties/enemy/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem(element1, "Enemies properties");
	element1->insertItem(element2);
	file.setName( fileName + "/properties/enemies/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem(element1, "Target properties");
	element1->insertItem(element2);
	file.setName( fileName + "/properties/target/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem(element1, "My properties");
	element1->insertItem(element2);
	file.setName( fileName + "/properties/my/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	element2 = new QListViewItem(element1, "");
	element1->insertItem(element2);
	//element1->setOpen( true );
	
//	element1 = new QListViewItem(commandsListView, "Functions");
//	element1->setPixmap( 0, QPixmap::fromMimeSource( "gear.png" ) );
//	commandsListView->insertItem(element1);
	element2 = new QListViewItem(element1, "Key words");
	element1->insertItem(element2);
	file.setName( fileName + "/functions/keywords/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem( element1, "Statements" );
	element1->insertItem( element2 );
	file.setName( fileName + "/functions/statements/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem( element1, "Low level functions" );
	element1->insertItem( element2 );
	file.setName( fileName + "/functions/lowlevel/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	
	element2 = new QListViewItem( element1, "High level functions" );
	element1->insertItem( element2 );
	file.setName( fileName + "/functions/highlevel/entry.txt");
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			line = in.readLine();
			list += line;
		}
		file.close();
		for( QStringList::Iterator it = list.begin(); it != list.end(); it++ ){
			name = *it;
			if( name != "" ){
				element3 = new QListViewItem(element2, name);
				element2->insertItem(element3);
			}
		}
		list.clear();
	}
	element1->setOpen( true );
	
}
void mainform::langHelp()
{
	bool ok = false;
	element1 = commandsListView->firstChild();
	element2 = element1->firstChild();
	element3 = element2->firstChild();
	
	while( element1 != NULL ){
		element2 = element1->firstChild();
		while( element2 != NULL ){
			element3 = element2->firstChild();
			while( element3 != NULL ){
				if( element3->isSelected() == true){
					if( element3->parent() == element2 ){
						QString text = element3->text(0);
						if( ( text == "Shoot" ) || ( text == "GetTarget" )||(text == "SetEnemiesPriority(equation)" ) ){
							help("shooting.htm");
						}
						if( ( text == "GoToWaypoint" ) || ( text == "GetWaypoint" ) || ( text == "SetWaypointsPriority(equation)" ) ){
							help("waypoint.htm");
						}
						if( element3->parent()->text(0) == "Low level functions"){
							help("lowlevel.htm");
						}
						if( ( text == "CanGoBack" ) || ( text == "CanGoForward" ) || ( text == "CanGoRight" ) || ( text == "CanGoLeft" ) || ( text == "IsAvailablePoint(x, y)" ) ){
							help("cango.htm");
						}
						if( text == "FinishIsKnown" ){
							help("finish.htm");
						}
						if( text == "WaypointExists(line1, line2)" ){
							help("waypointex.htm");
						}
						if( text == "IsDefinedWaypoint" ){
							help("waypoint.htm");
						}
						if( element3->parent()->text(0) == "My properties" ){
							help("my.htm");
						}
						if( element3->parent()->text(0) == "Target properties" ){
							help("target.htm");
						}
						if( element3->parent()->text(0) == "Enemies properties" ){
							help("enemies.htm");
						}
						if( element3->parent()->text(0) == "Enemy properties" ){
							help("enemy.htm");
						}
						if( element3->parent()->text(0) == "Waypoint" ){
							help("waypointprop.htm");
						}
						if( element3->parent()->text(0) == "Waypoints" ){
							help("waypointsprop.htm");
						}
						ok = true;
					}
					element3 = NULL;
				}
				else {
					element3 = element3->itemBelow();
				}
			}
			if( ok ){
				element2 = NULL;
			}
			else {
				element2 = element2->itemBelow();
			}
		}
		if( ok ){
			element1 = NULL;
		}
		else {
			element1 = element1->itemBelow();
		}
	}
}
void mainform::insertFunction()
{
	bool ok = false;
	bool zu = false;
	QString text;
	element1 = commandsListView->firstChild();
	element2 = element1->firstChild();
	element3 = element2->firstChild();
	
	while( element1 != NULL ){
		element2 = element1->firstChild();
		while( element2 != NULL ){
			element3 = element2->firstChild();
			while( element3 != NULL ){
				if( element3->isSelected() == true){
					if( element3->parent() == element2 ){
						if(element2->text(0) == "My properties" ){
							logicTextEdit->insert(" My" + element3->text(0) + ' ');
							zu = true;
						}
						if(element2->text(0) == "Target properties" ){
							logicTextEdit->insert( " Target" + element3->text(0) + ' ' );
							zu = true;
						}
						if(element2->text(0) == "Enemies properties" ){
							logicTextEdit->insert( " Enemies" + element3->text(0) + ' ' );
							zu = true;
						}
						if(element2->text(0) == "Enemy properties" ){
							logicTextEdit->insert( " Enemy" + element3->text(0) + ' ' );
							zu = true;
						}
						if(element2->text(0) == "Waypoint" ){
							logicTextEdit->insert( " Waypoint" + element3->text(0) + ' ' );
							zu = true;
						}
						if(element2->text(0) == "Waypoints" ){
							logicTextEdit->insert( " Waypoints" + element3->text(0) + ' ' );
							zu = true;
						}
						if( !zu ) {
							logicTextEdit->insert(' ' + element3->text(0) + ' ');
						}
						ok = true;
					}
					element3 = NULL;
				}
				else {
					element3 = element3->itemBelow();
				}
			}
			if( ok ){
				element2 = NULL;
			}
			else {
				element2 = element2->itemBelow();
			}
		}
		if( ok ){
			element1 = NULL;
		}
		else {
			element1 = element1->itemBelow();
		}
	}
}
void mainform::about()
{
	QMessageBox::about(this, tr("About NPRG client"), tr("<h2>Network Programmable Game Robots</h2><br>Version 1.0b"
	"<p>Copyright &copy; 2005 MIPT, 344 group<p>This application is a simple client for our second term"
	" project - network programmable robots."));
}
/*void mainform::highLight()
{
	QRegExp expr("\\b(include)\\b");
	int pos = 0;
	if (( pos = expr.search( logicTextEdit->text(), pos )) != -1 ) {
		printf("%d", pos);
		pos += expr.matchedLength();
	}
}*/
/*
 *  Destroys the object and frees any allocated resources
 */
mainform::~mainform()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void mainform::languageChange()
{
    setCaption( tr( "NPRG client" ) );
    logicTextLabel->setText( tr( "Your game logic:" ) );
    QWhatsThis::add( logicTextEdit, tr( "Type your logic here.." ) );
    fileNewAction->setText( tr( "&New" ) );
    fileNewAction->setMenuText( tr( "&New" ) );
    fileNewAction->setToolTip( tr( "New (Ctrl+N)" ) );
    fileNewAction->setStatusTip( tr( "Create a new file with game logic" ) );
    fileNewAction->setAccel( tr( "Ctrl+N" ) );
    fileLoadAction->setText( tr( "&Load" ) );
    fileLoadAction->setMenuText( tr( "&Load" ) );
    fileLoadAction->setToolTip( tr( "Load (Ctrl+O)" ) );
    fileLoadAction->setStatusTip( tr( "Load a file with game logic" ) );
    fileLoadAction->setAccel( tr( "Ctrl+O" ) );
    filesaveAction->setText( tr( "&Save" ) );
    filesaveAction->setMenuText( tr( "&Save" ) );
    filesaveAction->setToolTip( tr( "Save (Ctrl+S)" ) );
    filesaveAction->setStatusTip( tr( "Save your game logic to a current file" ) );
    filesaveAction->setAccel( tr( "Ctrl+S" ) );
    fileSave_AsAction->setText( tr( "Save &As" ) );
    fileSave_AsAction->setMenuText( tr( "Save &As" ) );
    fileSave_AsAction->setToolTip( tr( "Save As..." ) );
    fileSave_AsAction->setStatusTip( tr( "Save your game logic to a selected file" ) );
    fileExitAction->setText( tr( "E&xit" ) );
    fileExitAction->setMenuText( tr( "E&xit" ) );
    fileExitAction->setToolTip( tr( "Close (Ctrl+Q)" ) );
    fileExitAction->setStatusTip( tr( "Close the application" ) );
    fileExitAction->setAccel( tr( "Ctrl+Q" ) );
    gameCreate_gameAction->setText( tr( "&Create game" ) );
    gameCreate_gameAction->setMenuText( tr( "&Create game" ) );
    gameCreate_gameAction->setToolTip( tr( "Create" ) );
    gameCreate_gameAction->setStatusTip( tr( "Create a new game" ) );
    gameFind_gameAction->setText( tr( "&Find game" ) );
    gameFind_gameAction->setMenuText( tr( "&Find game" ) );
    gameFind_gameAction->setToolTip( tr( "Find (Ctrl+F)" ) );
    gameFind_gameAction->setStatusTip( tr( "Find games / Join selected game" ) );
    gameFind_gameAction->setAccel( tr( "Ctrl+F" ) );
    gameAddServerAction->setText( tr("A&dd server") );
    gameAddServerAction->setMenuText( tr("A&dd server") );
    gameAddServerAction->setToolTip( tr("Add server") );
    gameAddServerAction->setStatusTip( tr("Add a new server ip to configuration file") );
    gameClearDataAction->setText( tr("Clear &data") );
    gameClearDataAction->setMenuText( tr("Clear &data") );
    gameClearDataAction->setToolTip( tr("Clear data") );
    gameClearDataAction->setStatusTip( tr("Clear your game data: servers and maps") );
    editorClearAction->setText( tr( "Clear" ) );
    editorClearAction->setMenuText( tr( "Clear" ) );
    editorClearAction->setToolTip("Clear");
    editorClearAction->setStatusTip( tr("Clear the text edit area") );
    editorCheck_for_errorsAction->setText( tr( "Check &logic" ) );
    editorCheck_for_errorsAction->setMenuText( tr( "Check &logic" ) );
    editorCheck_for_errorsAction->setToolTip( tr( "Check logic" ) );
    editorCheck_for_errorsAction->setStatusTip( tr( "Check current logic for errors" ) );    
    helpHelpAction->setText( tr( "&Help" ) );
    helpHelpAction->setMenuText( tr( "&Help" ) );
    helpHelpAction->setToolTip( tr( "Help" ) );
    helpHelpAction->setStatusTip( tr( "Show the help window" ) );
    helpAboutAction->setText( tr( "A&bout" ) );
    helpAboutAction->setMenuText( tr( "A&bout" ) );
    helpAboutAction->setToolTip( tr( "About" ) );
    Toolbar->setLabel( tr( "Toolbar" ) );
    if (MenuBarEditor->findItem(1))
        MenuBarEditor->findItem(1)->setText( tr( "&File" ) );
    if (MenuBarEditor->findItem(2))
        MenuBarEditor->findItem(2)->setText( tr( "&Game" ) );
    if (MenuBarEditor->findItem(3))
        MenuBarEditor->findItem(3)->setText( tr( "&Editor" ) );
    if (MenuBarEditor->findItem(4))
        MenuBarEditor->findItem(4)->setText( tr( "&Help" ) );
}

