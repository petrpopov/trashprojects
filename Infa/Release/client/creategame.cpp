/****************************************************************************
** Form implementation generated from reading ui file 'creategame.ui'
**
** Created: Птн Апр 15 21:38:38 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "creategame.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qfiledialog.h>
#include <qapplication.h>
#include "helpbrowser.h"

#include "mainform.h"
//#include "mynetworkobject.h"

//MyNetworkObject *MNO;
char *create_logic;
QString logic;
/*
 *  Constructs a CreateGame as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
CreateGame::CreateGame( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CreateGame" );
    CreateGameLayout = new QGridLayout( this, 1, 1, 11, 6, "CreateGameLayout"); 

    serverGroupBox = new QGroupBox( this, "serverGroupBox" );
    serverGroupBox->setColumnLayout(0, Qt::Vertical );
    serverGroupBox->layout()->setSpacing( 6 );
    serverGroupBox->layout()->setMargin( 11 );
    serverGroupBoxLayout = new QGridLayout( serverGroupBox->layout() );
    serverGroupBoxLayout->setAlignment( Qt::AlignTop );

    ipTextLabel = new QLabel( serverGroupBox, "ipTextLabel" );

    serverGroupBoxLayout->addWidget( ipTextLabel, 0, 0 );

    ipComboBox = new QComboBox( FALSE, serverGroupBox, "ipComboBox" );

    serverGroupBoxLayout->addMultiCellWidget( ipComboBox, 0, 0, 1, 2 );
    spacer2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    serverGroupBoxLayout->addItem( spacer2, 1, 1 );

    portTextLabel = new QLabel( serverGroupBox, "portTextLabel" );

    serverGroupBoxLayout->addWidget( portTextLabel, 1, 0 );

    portSpinBox = new QSpinBox( serverGroupBox, "portSpinBox" );
    portSpinBox->setMaxValue( 65535 );
    portSpinBox->setMinValue( 51000 );

    serverGroupBoxLayout->addWidget( portSpinBox, 1, 2 );

    CreateGameLayout->addWidget( serverGroupBox, 1, 0 );

    gameGroupBox = new QGroupBox( this, "gameGroupBox" );
    gameGroupBox->setColumnLayout(0, Qt::Vertical );
    gameGroupBox->layout()->setSpacing( 6 );
    gameGroupBox->layout()->setMargin( 11 );
    gameGroupBoxLayout = new QGridLayout( gameGroupBox->layout() );
    gameGroupBoxLayout->setAlignment( Qt::AlignTop );

    typeTextLabel = new QLabel( gameGroupBox, "typeTextLabel" );

    gameGroupBoxLayout->addWidget( typeTextLabel, 0, 0 );

    nameTextLabel = new QLabel( gameGroupBox, "nameTextLabel" );

    gameGroupBoxLayout->addWidget( nameTextLabel, 1, 0 );

    numberTextLabel = new QLabel( gameGroupBox, "numberTextLabel" );

    gameGroupBoxLayout->addWidget( numberTextLabel, 2, 0 );

    nameLineEdit = new QLineEdit( gameGroupBox, "nameLineEdit" );

    gameGroupBoxLayout->addMultiCellWidget( nameLineEdit, 1, 1, 1, 2 );

    numberSpinBox = new QSpinBox( gameGroupBox, "numberSpinBox" );
    numberSpinBox->setMaxValue( 4 );
    numberSpinBox->setMinValue( 1 );

    gameGroupBoxLayout->addWidget( numberSpinBox, 2, 2 );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    gameGroupBoxLayout->addItem( spacer1, 2, 1 );

    typeComboBox = new QComboBox( FALSE, gameGroupBox, "typeComboBox" );

    gameGroupBoxLayout->addMultiCellWidget( typeComboBox, 0, 0, 1, 2 );

    CreateGameLayout->addWidget( gameGroupBox, 0, 0 );

    logicGroupBox = new QGroupBox( this, "logicGroupBox" );
    logicGroupBox->setColumnLayout(0, Qt::Vertical );
    logicGroupBox->layout()->setSpacing( 6 );
    logicGroupBox->layout()->setMargin( 11 );
    logicGroupBoxLayout = new QGridLayout( logicGroupBox->layout() );
    logicGroupBoxLayout->setAlignment( Qt::AlignTop );

    logicPushButton = new QPushButton( logicGroupBox, "logicPushButton" );

    logicGroupBoxLayout->addWidget( logicPushButton, 0, 1 );

    logicTextLabel = new QLabel( logicGroupBox, "logicTextLabel" );

    logicGroupBoxLayout->addWidget( logicTextLabel, 0, 0 );

    logicLineEdit = new QLineEdit( logicGroupBox, "logicLineEdit" );

    logicGroupBoxLayout->addMultiCellWidget( logicLineEdit, 1, 1, 0, 1 );

    CreateGameLayout->addWidget( logicGroupBox, 2, 0 );

    layout3 = new QVBoxLayout( 0, 0, 6, "layout3"); 

    createPushButton = new QPushButton( this, "createPushButton" );
    createPushButton->setDefault( TRUE );
    layout3->addWidget( createPushButton );
    spacer3 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout3->addItem( spacer3 );

    helpPushButton = new QPushButton( this, "helpPushButton" );
    layout3->addWidget( helpPushButton );

    cancelPushButton = new QPushButton( this, "cancelPushButton" );
    layout3->addWidget( cancelPushButton );

    CreateGameLayout->addMultiCellLayout( layout3, 0, 2, 1, 1 );
    languageChange();
    resize( QSize(420, 340).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( typeComboBox, nameLineEdit );
    setTabOrder( nameLineEdit, numberSpinBox );
    setTabOrder( numberSpinBox, ipComboBox );
    setTabOrder( ipComboBox, portSpinBox );
    setTabOrder( portSpinBox, createPushButton );
    setTabOrder( createPushButton, cancelPushButton );
    setTabOrder( cancelPushButton, helpPushButton );
    
    createPushButton->setEnabled( false );
    connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( createPushButton, SIGNAL( clicked() ), this, SLOT( createGame() ));
    connect(logicPushButton, SIGNAL( clicked() ), this, SLOT( chooseLogic() ) );
    connect(logicLineEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( enableCreateButton() ) );
    connect(helpPushButton, SIGNAL( clicked() ), this, SLOT( help() ) );
    loadServerIP();
}
void CreateGame::loadServerIP()
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
void CreateGame::createGame()
{
	char type;
	char num;
	char *name;
	char *ip;
	int port;
	
	type = '1';
	if( typeComboBox->currentText() == "Labirinth"){
		type = '1';
	}
	else if ( typeComboBox->currentText() == "Kill'em all!"){
		type = '2';
	}	
	num = numberSpinBox->value() + '0';	
	QString text = nameLineEdit->text();
	if( !text.isEmpty() ){
		name = (char*)text.data();
	}
	else {
		name = "Zuuu...";
	}
	
	QString fileName = logicLineEdit->text();
	QFile file( fileName );
	if( file.open(IO_ReadOnly) ){
		QTextStream in(&file);
		QChar c;
		logic = "";
		while( !in.atEnd() ){
			in >> c;
			logic += c;
		}
		file.close();
		create_logic = (char*)logic.data();
		
		text = ipComboBox->currentText();
		ip = (char*)text.data();
		port = portSpinBox->value();
	
		QApplication::setOverrideCursor( waitCursor );
		int res = MNO->create_game( type, num, name, create_logic, ip, port );
		QApplication::restoreOverrideCursor();
		
		errorMessages( res );
	}
	else {
		QMessageBox::warning(this, tr("Game client"), tr("Can't open file '%1' for reading!").arg(fileName));
	}
}
void CreateGame::chooseLogic()
{
	QString path = QDir::homeDirPath();
	QString fileName = QFileDialog::getOpenFileName(path, tr("Text files (*.txt)"), this );
	if( !fileName.isEmpty() ){
		logicLineEdit->setText(fileName);
	}
}
void CreateGame::enableCreateButton()
{
	QString text;
	text = logicLineEdit->text();
	if( !text.isEmpty() ){
		createPushButton->setEnabled( true );
	}
	else {
		createPushButton->setEnabled( false );
	}
}
void CreateGame::errorMessages(int mes)
{
	switch(mes){
		case 0:
		{
			accept();
			break;
		}
		case -1: 
		{
			QMessageBox::critical(this,tr("Create game"),tr("Can't create socket!"));
			break;
		}
		case -2:
		{
			QMessageBox::critical(this,tr("Create game"),tr("IP adress in an inadmissible format!"));
			break;
		}
		case -3:
		{
			QMessageBox::critical(this,tr("Create game"),tr("Can't connect to server!"));
			break;
		}
		case -4:
		{
			QMessageBox::critical(this,tr("Create game"),tr("Can't write to socket!"));
			break;
		}    
		case -5:
		{
			QMessageBox::critical(this,tr("Create game"),tr("Can't read from socket!"));
			break;
		}
		case -6:
		{
			QMessageBox::critical(this,tr("Create game"),tr("Error receieving logic!"));
			break;
		}
		case -7:
		{
			QMessageBox::critical(this,tr("Create game"),tr("Can't create map file!"));
			break;
		}
		case -8:{
			QMessageBox::critical(this, tr("Create game"), tr("Error in data for game!") );
			break;
		}
		case -9:{
			QMessageBox::critical(this, tr("Create game"), tr("Server is full!") );
			break;
		}
		case -10:{
			QMessageBox::critical(this, tr("Create game"), tr("Can't open directory with maps!") );
			break;
		}
	}
}
void CreateGame::help()
{
	HelpBrowser *helpbrowser = new HelpBrowser;
	helpbrowser->show();
	helpbrowser->showPage("new_game.htm");
}
/*
 *  Destroys the object and frees any allocated resources
 */
CreateGame::~CreateGame()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CreateGame::languageChange()
{
    setCaption( tr( "Create game" ) );
    serverGroupBox->setTitle( tr( "Server information" ) );
    ipTextLabel->setText( tr( "Server IP" ) );
    ipComboBox->clear();
    ipComboBox->insertItem( tr( "127.0.0.1" ) );
    QWhatsThis::add( ipComboBox, tr( "<b>Server IP</b>. You can add your existing server's ip, by pressing \"...\" button." ) );
    portTextLabel->setText( tr( "Server port" ) );
    QWhatsThis::add( portSpinBox, tr( "<b>Server port</b>. 51000 is a default value. Don't change this value, if uncertain!" ) );
    gameGroupBox->setTitle( tr( "Game information" ) );
    typeTextLabel->setText( tr( "Type" ) );
    nameTextLabel->setText( tr( "Name" ) );
    numberTextLabel->setText( tr( "Number of\n"
"players" ) );
    QWhatsThis::add( nameLineEdit, tr( "<b>Name</b> of your game.<br>\n"
"Example: <i>Cool game</i>" ) );
    QWhatsThis::add( numberSpinBox, tr( "<b>Number</b> of players. This is a maximum number of players, which your game will support" ) );
    typeComboBox->clear();
    typeComboBox->insertItem( tr( "Labirinth" ) );
    typeComboBox->insertItem( tr( "Kill'em all!" ) );
    QWhatsThis::add( typeComboBox, tr( "<b>Labirinth</b> Aim of this game is to find an exit\n"
"or/and a prize in a labirint.<br>\n"
"<b>Kill'em all!</b> This is a battle game in a labirint with\n"
"other players." ) );
    logicGroupBox->setTitle( tr( "Logic information" ) );
    logicPushButton->setText( tr( "..." ) );
    QWhatsThis::add( logicPushButton, tr( "By pressing this button you can choose a file with your game logic. It is necessary for creating a game." ) );
    logicTextLabel->setText( tr( "Choose file with game logic:" ) );
    QWhatsThis::add( logicLineEdit, tr( "You can input here a full path to a file with game logic. Also you can press a \"...\" button." ) );
    createPushButton->setText( tr( "Create game!" ) );
    QWhatsThis::add( createPushButton, tr( "Create game!" ) );
    helpPushButton->setText( tr( "Help" ) );
    cancelPushButton->setText( tr( "Cancel" ) );
}

