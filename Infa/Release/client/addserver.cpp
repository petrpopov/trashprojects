/****************************************************************************
** Form implementation generated from reading ui file 'addserver.ui'
**
** Created: Сбт Апр 16 15:37:15 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "addserver.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qvalidator.h>
#include <qfile.h>
#include <qdir.h>
#include <qtextstream.h>
#include <qmessagebox.h>

/*
 *  Constructs a AddServer as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
AddServer::AddServer( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "AddServer" );
    AddServerLayout = new QGridLayout( this, 1, 1, 11, 6, "AddServerLayout"); 

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    okPushButton = new QPushButton( this, "okPushButton" );
    okPushButton->setEnabled( FALSE );
    okPushButton->setDefault( TRUE );
    layout1->addWidget( okPushButton );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    cancelPushButton = new QPushButton( this, "cancelPushButton" );
    layout1->addWidget( cancelPushButton );

    AddServerLayout->addLayout( layout1, 1, 0 );

    ipLineEdit = new QLineEdit( this, "ipLineEdit" );

    AddServerLayout->addWidget( ipLineEdit, 0, 0 );
    languageChange();
    resize( QSize(282, 114).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( ipLineEdit, okPushButton );
    setTabOrder( okPushButton, cancelPushButton );  
    
    connect( cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( ipLineEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( enableOkButton() ) );
    connect( okPushButton, SIGNAL( clicked() ), this, SLOT( addServerIP() ) );
    
    QRegExp regExp("[0-9]{1,3}[.]{1,1}[0-9]{1,3}[.]{1,1}[0-9]{1,3}[.]{1,1}[0-9]{1,3}");
    ipLineEdit->setValidator(new QRegExpValidator(regExp, this) );
}
void AddServer::addServerIP()
{
	QString text;
	QChar c;
	QString home;
	QString fileName;
	
	home = QDir::homeDirPath();
	fileName.append( home );
	fileName.append("/.client_data");
	
	QDir dir = QDir( fileName );
	if( !dir.exists() ){
		QMessageBox::critical(this, tr("Add server"), tr("Gameclient directory '~/.client_data' does not exists") );
		reject();
	}
	else {
	fileName.append("/servers.txt");
	QFile file( fileName );
	if( file.open(IO_ReadWrite) ){
		QTextStream stream(&file);
		while( !stream.atEnd() ){
			stream >> c;
		}
		text = "\n";
		text.append( ipLineEdit->text() );
		stream << text;
		file.close();
	}
	else {
		QMessageBox::critical( this, tr("Add server"), tr("Can't open file %1 for writing!").arg(fileName) );
	}
	}
	accept();
}
void AddServer::enableOkButton()
{
	okPushButton->setEnabled( ipLineEdit->hasAcceptableInput() );
}
/*
 *  Destroys the object and frees any allocated resources
 */
AddServer::~AddServer()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void AddServer::languageChange()
{
    setCaption( tr( "Add a server IP" ) );
    okPushButton->setText( tr( "Add" ) );
    QWhatsThis::add( okPushButton, tr( "Add an ip to a configuration file" ) );
    cancelPushButton->setText( tr( "Cancel" ) );
    QWhatsThis::add( ipLineEdit, tr( "Input here a new server ip" ) );
}

