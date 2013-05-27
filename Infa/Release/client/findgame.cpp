/****************************************************************************
** Form implementation generated from reading ui file 'findgame.ui'
**
** Created: Вск Апр 17 15:24:42 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "findgame.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qapplication.h> 
//#include "mynetworkobject.h"

//MyNetworkObject *MNO;
#include "mainform.h"
#include "helpbrowser.h"

QListViewItem *a;
QString servIP;
struct game *root = NULL, *p, *q;
char gtype;
int count;
QString logik;
char* join_logic;
int port;

FindGame::FindGame( QWidget* parent, const char* name, bool modal, WFlags fl )
	: QDialog( parent, name, modal, fl )
{
	if ( !name )
		setName( "FindGame" );
	FindGameLayout = new QGridLayout( this, 1, 1, 11, 6, "FindGameLayout"); 

	layout8 = new QHBoxLayout( 0, 0, 6, "layout8"); 

	helpPushButton = new QPushButton( this, "helpPushButton" );
	layout8->addWidget( helpPushButton );
	spacer3 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	layout8->addItem( spacer3 );

	cancelPushButton = new QPushButton( this, "cancelPushButton" );
	layout8->addWidget( cancelPushButton );

	FindGameLayout->addMultiCellLayout( layout8, 3, 3, 0, 1 );

	layout9 = new QVBoxLayout( 0, 0, 6, "layout9"); 

	findListView = new QListView( this, "findListView" );
	findListView->addColumn( tr( "Name" ) );
	findListView->addColumn( tr( "Maximum" ) );
	findListView->addColumn( tr( "Current" ) );
	findListView->setResizeMode( QListView::AllColumns );
	layout9->addWidget( findListView );

	findTextLabel = new QLabel( this, "findTextLabel" );
	layout9->addWidget( findTextLabel );

	FindGameLayout->addMultiCellLayout( layout9, 0, 2, 0, 0 );
	spacer5 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
	FindGameLayout->addItem( spacer5, 1, 1 );

	layout10 = new QGridLayout( 0, 1, 1, 0, 6, "layout10"); 
	spacer7 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
	layout10->addItem( spacer7, 1, 0 );

	logicGroupBox = new QGroupBox( this, "logicGroupBox" );
	logicGroupBox->setColumnLayout(0, Qt::Vertical );
	logicGroupBox->layout()->setSpacing( 6 );
	logicGroupBox->layout()->setMargin( 11 );
	logicGroupBoxLayout = new QGridLayout( logicGroupBox->layout() );
	logicGroupBoxLayout->setAlignment( Qt::AlignTop );

	logicLineEdit = new QLineEdit( logicGroupBox, "logicLineEdit" );

	logicGroupBoxLayout->addMultiCellWidget( logicLineEdit, 1, 1, 0, 1 );

	logicTextLabel = new QLabel( logicGroupBox, "logicTextLabel" );

	logicGroupBoxLayout->addWidget( logicTextLabel, 0, 0 );

	logicPushButton = new QPushButton( logicGroupBox, "logicPushButton" );

	logicGroupBoxLayout->addWidget( logicPushButton, 0, 1 );

	layout10->addMultiCellWidget( logicGroupBox, 0, 1, 1, 1 );

	joinPushButton = new QPushButton( this, "joinPushButton" );
	joinPushButton->setEnabled( FALSE );

	layout10->addWidget( joinPushButton, 0, 0 );

	FindGameLayout->addLayout( layout10, 2, 1 );

	layout11 = new QGridLayout( 0, 1, 1, 0, 6, "layout11"); 

	gameGroupBox = new QGroupBox( this, "gameGroupBox" );
	gameGroupBox->setColumnLayout(0, Qt::Vertical );
	gameGroupBox->layout()->setSpacing( 6 );
	gameGroupBox->layout()->setMargin( 11 );
	gameGroupBoxLayout = new QGridLayout( gameGroupBox->layout() );
	gameGroupBoxLayout->setAlignment( Qt::AlignTop );

	serverGroupBox = new QGroupBox( gameGroupBox, "serverGroupBox" );
	serverGroupBox->setColumnLayout(0, Qt::Vertical );
	serverGroupBox->layout()->setSpacing( 6 );
	serverGroupBox->layout()->setMargin( 11 );
	serverGroupBoxLayout = new QGridLayout( serverGroupBox->layout() );
	serverGroupBoxLayout->setAlignment( Qt::AlignTop );

	ipTextLabel = new QLabel( serverGroupBox, "ipTextLabel" );

	serverGroupBoxLayout->addWidget( ipTextLabel, 0, 0 );

	ipComboBox = new QComboBox( FALSE, serverGroupBox, "ipComboBox" );

	serverGroupBoxLayout->addMultiCellWidget( ipComboBox, 0, 0, 1, 2 );

	portSpinBox = new QSpinBox( serverGroupBox, "portSpinBox" );
	portSpinBox->setMaxValue( 65535 );
	portSpinBox->setMinValue( 51000 );

	serverGroupBoxLayout->addWidget( portSpinBox, 1, 2 );

	portTextLabel = new QLabel( serverGroupBox, "portTextLabel" );

	serverGroupBoxLayout->addWidget( portTextLabel, 1, 0 );
	spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
	serverGroupBoxLayout->addItem( spacer1, 1, 1 );

	gameGroupBoxLayout->addWidget( serverGroupBox, 1, 0 );

	layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

	typeTextLabel = new QLabel( gameGroupBox, "typeTextLabel" );
	layout4->addWidget( typeTextLabel );

	typeComboBox = new QComboBox( FALSE, gameGroupBox, "typeComboBox" );
	layout4->addWidget( typeComboBox );

	gameGroupBoxLayout->addLayout( layout4, 0, 0 );

	layout11->addMultiCellWidget( gameGroupBox, 0, 1, 1, 1 );

	findPushButton = new QPushButton( this, "findPushButton" );
	findPushButton->setDefault( TRUE );

	layout11->addWidget( findPushButton, 0, 0 );
	spacer6 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
	layout11->addItem( spacer6, 1, 0 );

	FindGameLayout->addLayout( layout11, 0, 1 );
	languageChange();
	resize( QSize(594, 343).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );

    // tab order
	setTabOrder( typeComboBox, ipComboBox );
	setTabOrder( ipComboBox, findPushButton );
	setTabOrder( findPushButton, findListView );
	setTabOrder( findListView, logicPushButton );
	setTabOrder( logicPushButton, joinPushButton );
	setTabOrder( joinPushButton, cancelPushButton );
	setTabOrder( cancelPushButton, helpPushButton );
	setTabOrder( helpPushButton, logicLineEdit );
	setTabOrder( logicLineEdit, portSpinBox );
	
	connect(cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
	connect(findPushButton, SIGNAL( clicked() ), this, SLOT( find() ) );
	connect(logicPushButton, SIGNAL( clicked() ), this, SLOT( chooseLogic() ) );
	connect(logicLineEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( enableJoinButton() ) );
   // connect(findListView, SIGNAL( selectionChanged() ), this, SLOT( enableJoinButton() ) );
	connect(joinPushButton, SIGNAL( clicked() ), this, SLOT( join() ) );
	connect(helpPushButton, SIGNAL( clicked() ), this, SLOT( help() ) );
	loadServerIP();
}
void FindGame::loadServerIP()
{
	QString server;
	QString fileName = QDir::homeDirPath();
	fileName.append("/.client_data/servers.txt");
	QFile file(fileName);
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		while( !in.atEnd() ){
			in >> server;
			if( !server.isEmpty() ){
				ipComboBox->insertItem(server);
			}
		}
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Create game"), tr("Can't open file servers.txt!\nUsing default values.."));
	}
}
void FindGame::find()
{
	int res;
	QString str; 
	int zu1,zu2;
	
	gtype = '1';
	if ( typeComboBox->currentText()=="Labirinth" )
	{
		gtype = '1';
	}
	if ( typeComboBox->currentText()=="Kill 'em all!")
	{
		gtype = '2';
	}
	servIP = ipComboBox->currentText();    
	port = portSpinBox->value();
	
	QApplication::setOverrideCursor( waitCursor );
	res = MNO->find_game(gtype, (char*)servIP.data(), port, &root);
	QApplication::restoreOverrideCursor();
	
	switch( res ){
		case 0:{
			p = root;
			findListView->clear();
			if (p != NULL){
				enableJoinButton();
				count = 0;
				while(p != NULL)
				{
					printf("###\n%s %c %c %s\n###\n",p->name,p->maxnum,p->curnum,p->pid);
					zu1 = (p->maxnum) - '0';
					zu2 = (p->curnum) - '0';
					a = new QListViewItem(findListView,(char*)(p->name), str.setNum(zu1),
							str.setNum(zu2));
					count++;
					p = p->next;
				}
		//a = findListView->firstChild();
		//a->setSelected(true);
			}
			break;
		}
		default:{
			errorMessages(res, "Find game");
		}
	}
	QString caption;
	caption.setNum( count );
	switch( count ){
		case 0:{
			caption.append( tr(" servers were found") );
			break;
		}
		case 1:{
			caption.append( tr(" server was found") );
			break;
		}
		default:{
			caption.append( tr(" servers were found") );
		}
	}
	findTextLabel->setText( caption );
}
void FindGame::join()
{
	int res;
	p = root;
	int i;
	i = 0;
	if(p != NULL){
		a = findListView->firstChild();
		while( a != NULL ){
			if(a->isSelected() == true){
				i++;
			}
			a= a->itemBelow();
		}
		if( i ==0 ){
			QMessageBox::warning(this, tr("Join game"), tr("Nothing is selected") );
		}
		else if( i > 0){
			QString fileName;
			fileName = logicLineEdit->text();
			QFile file(fileName);
			if( file.open(IO_ReadOnly) ){
				QTextStream in(&file);
				QChar c;
				logik = "";
				while( !in.atEnd() ){
					in >> c;
					logik += c;
				}
				file.close();
				join_logic = (char*)logik.data();
				
				QString str;
				//!!! Вернуться к началу списка!!!
				a = findListView->firstChild();
				//Идём по списку, пока элементы есть и не выбраны
				while((a != NULL)&&(a->isSelected() == false)){
					a = a->itemBelow();
					p = p->next;
				}
				//Когда мы вылетели из цикла, указатели автоматически
				// показывают на нужные объекты
				
				QApplication::setOverrideCursor( waitCursor );
				res = MNO->join_game(gtype, p->pid, join_logic, (char*)servIP.data(), port);
				QApplication::restoreOverrideCursor();
				
				switch( res ){
					case 0:{
						accept();
						break;
					}
					default:{
						errorMessages(res, "Join game");
						break;
					}
				}
			}
			else {
				QMessageBox::critical(this, tr("Join game"), tr("Can't open file '%1' for reading").arg( fileName ) );
			}
		}
	}
}
void FindGame::errorMessages(int mes, const QString &caption)
{
	switch( mes ){
		case -1: {
			QMessageBox::critical(this, caption, tr("Can't create socket!"));
			break;
		}
		case -2:{
			QMessageBox::critical(this, caption, tr("IP adress in an inadmissible format!"));
			break;
		}
		case -3:{
			QMessageBox::critical(this, caption, tr("Can't connect to server!"));
			break;
		}
		case -4:{
			QMessageBox::critical(this, caption, tr("Can't write to socket!"));
			break;
		}    
		case -5:{
			QMessageBox::critical(this, caption, tr("Can't read from socket!"));
			break;
		}
		case -7:{
			QMessageBox::critical(this, tr("Error!"), tr("Can't create map file!") );
			break;
		}
		case -8:{
			QMessageBox::critical(this, caption, tr("Error in data for game!") );
			break;
		}
		case -10:{
			QMessageBox::critical(this, tr("Error!"), tr("Can't open directory with maps!") );
			break;
		}
	}
}
void FindGame::chooseLogic()
{
	QString path = QDir::homeDirPath();
	QString fileName = QFileDialog::getOpenFileName(path, tr("Text files (*.txt)"), this );
	if( !fileName.isEmpty() ){
		logicLineEdit->setText(fileName);
	}
}
void FindGame::enableJoinButton()
{
	//int children;
	//children = findListView->childCount();
	q = root;
	QString text = logicLineEdit->text();
	if( ( !text.isEmpty() ) && ( q != NULL) ){
		joinPushButton->setEnabled( true );
	}
	else {
		joinPushButton->setEnabled( false );
	}
}
void FindGame::help()
{
	HelpBrowser *helpbrowser = new HelpBrowser;
	helpbrowser->show();
	helpbrowser->showPage("join_game.htm");
}
/*
 *  Destroys the object and frees any allocated resources
 */
FindGame::~FindGame()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FindGame::languageChange()
{
	setCaption( tr( "Find game" ) );
	helpPushButton->setText( tr( "Help" ) );
	cancelPushButton->setText( tr( "Cancel" ) );
	findListView->header()->setLabel( 0, tr( "Name" ) );
	findListView->header()->setLabel( 1, tr( "Maximum" ) );
	findListView->header()->setLabel( 2, tr( "Current" ) );
	findTextLabel->setText( tr( "0 servers were found" ) );
	logicGroupBox->setTitle( tr( "Logic information" ) );
	logicTextLabel->setText( tr( "Choose file with game logic" ) );
	logicPushButton->setText( tr( "..." ) );
	QWhatsThis::add( logicPushButton, tr( "By pressing this button you can choose a file with your game logic. It is necessary for creating a game." ) );
	joinPushButton->setText( tr( "Join game!" ) );
	QWhatsThis::add( joinPushButton, tr( "Join game!" ) );
	gameGroupBox->setTitle( tr( "Game parametres" ) );
	QWhatsThis::add( gameGroupBox, tr( "Choose your preferred parametres to find" ) );
	serverGroupBox->setTitle( tr( "Server information" ) );
	ipTextLabel->setText( tr( "Server IP" ) );
	ipComboBox->clear();
	ipComboBox->insertItem( tr( "127.0.0.1" ) );
	QWhatsThis::add( portSpinBox, tr( "<b>Server port</b>. 51000 is a default value. Don't change this value, if uncertain!" ) );
	portTextLabel->setText( tr( "Server port" ) );
	typeTextLabel->setText( tr( "Type" ) );
	typeComboBox->clear();
	typeComboBox->insertItem( tr( "Labirinth" ) );
	typeComboBox->insertItem( tr( "Kill 'em all!" ) );
	QWhatsThis::add( typeComboBox, tr( "<b>Labirinth</b> Aim of this game is to find an exit\"\n"
			"\"or/and a prize in a labirint.<br>\n"
					"<b>Kill'em all!</b> This is a battle game in a labirint with\"\n"
					"\"other players." ) );
	findPushButton->setText( tr( "Find game!" ) );
	QWhatsThis::add( findPushButton, tr( "Find game!" ) );
}

