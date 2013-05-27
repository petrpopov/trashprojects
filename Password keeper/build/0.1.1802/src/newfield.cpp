
#include "newfield.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

QStringList *new_list;

NewField::NewField( QString &nameDlg, QStringList &in_list, QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "NewField" );
    NewFieldLayout = new QGridLayout( this, 1, 1, 11, 6, "NewFieldLayout"); 

    layout1 = new QGridLayout( 0, 1, 1, 0, 6, "layout1"); 

    passLineEdit = new QLineEdit( this, "passLineEdit" );

    layout1->addWidget( passLineEdit, 3, 1 );

    nameLineEdit = new QLineEdit( this, "nameLineEdit" );

    layout1->addWidget( nameLineEdit, 1, 1 );

    nameLabel = new QLabel( this, "nameLabel" );

    layout1->addWidget( nameLabel, 1, 0 );

    typeBox = new QComboBox( FALSE, this, "typeBox" );

    layout1->addWidget( typeBox, 0, 1 );

    passLabel = new QLabel( this, "passLabel" );

    layout1->addWidget( passLabel, 3, 0 );

    loginLineEdit = new QLineEdit( this, "loginLineEdit" );

    layout1->addWidget( loginLineEdit, 2, 1 );

    typeLabel = new QLabel( this, "typeLabel" );

    layout1->addWidget( typeLabel, 0, 0 );

    loginLabel = new QLabel( this, "loginLabel" );

    layout1->addWidget( loginLabel, 2, 0 );

    NewFieldLayout->addLayout( layout1, 0, 0 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout2->addItem( spacer1 );

    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( FALSE );
    okButton->setDefault( TRUE );
    layout2->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout2->addWidget( cancelButton );

    NewFieldLayout->addLayout( layout2, 1, 1 );

    layout3 = new QGridLayout( 0, 1, 1, 0, 6, "layout3"); 

    descrTextBox = new QTextEdit( this, "descrTextBox" );

    layout3->addMultiCellWidget( descrTextBox, 0, 1, 1, 1 );
    spacer2 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layout3->addItem( spacer2, 1, 0 );

    descrLabel = new QLabel( this, "descrLabel" );

    layout3->addWidget( descrLabel, 0, 0 );

    NewFieldLayout->addLayout( layout3, 0, 1 );
    languageChange();
    resize( QSize(500, 171).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( typeBox, nameLineEdit );
    setTabOrder( nameLineEdit, loginLineEdit );
    setTabOrder( loginLineEdit, passLineEdit );
    setTabOrder( passLineEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, descrTextBox );
    
    if(!nameDlg.isEmpty())
	    setCaption( tr("%1").arg( nameDlg ) );
    else
	    setCaption( tr("New field") );
    
    if(in_list.count() > 0)
    {    
	    for(int i = 0; i < (int)in_list.count(); i++)
	    {
		    switch(i)
		    {
			    case 0 :
			    {
				    typeBox->setCurrentText( in_list[0] );  
				    break;
			    }
			    case 1 : 
			    {
				    nameLineEdit->setText( in_list[1] );
				    break;
			    }
			    case 2 :
			    {
				    loginLineEdit->setText( in_list[2] );
				    break;
			    }
			    case 3 :
			    {
				    passLineEdit->setText( in_list[3] );
				    break;
			    }
			    case 4 :
			    {
				    descrTextBox->setText( in_list[4] );
				    break;
			    }
		    }
	    }
    }
      
    new_list = &in_list;
    
    connect( nameLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect( loginLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect( passLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect( descrTextBox, SIGNAL( textChanged() ), this, SLOT( enableOk() ) );
    connect( typeBox, SIGNAL( activated(const QString &) ), this, SLOT( enableOk() ) );
    
    connect( okButton, SIGNAL( clicked() ), this, SLOT( ok() ) );
    connect( cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
}


void NewField::ok()
{
	new_list->clear();
	*new_list << (QString)typeBox->currentText().simplifyWhiteSpace();
	*new_list << (QString)nameLineEdit->text().simplifyWhiteSpace();
	*new_list << (QString)loginLineEdit->text().simplifyWhiteSpace();
	*new_list << (QString)passLineEdit->text().simplifyWhiteSpace();
	
 	if(!descrTextBox->text().isEmpty())
		*new_list << (QString)descrTextBox->text().simplifyWhiteSpace();
 	else
 		*new_list << " ";
	
	accept();
}

void NewField::enableOk()
{
	if( !nameLineEdit->text().isEmpty() && !loginLineEdit->text().isEmpty() && !passLineEdit->text().isEmpty() )
		okButton->setEnabled( true );
	else
		okButton->setEnabled( false );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NewField::~NewField()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NewField::languageChange()
{
//     setCaption( tr( "New field" ) );
    nameLabel->setText( tr( "Name:" ) );
    typeBox->clear();
    typeBox->insertItem( QPixmap::fromMimeSource("account.png"), tr( "Account" ) );
    typeBox->insertItem( QPixmap::fromMimeSource("icq.png"), tr( "ICQ" ) );
    typeBox->insertItem( QPixmap::fromMimeSource("irc.png"), tr( "IRC" ) );
    typeBox->insertItem( QPixmap::fromMimeSource("mail.png"), tr( "Mail" ) );
    typeBox->insertItem( QPixmap::fromMimeSource("system.png"), tr( "System" ) );
    typeBox->insertItem( QPixmap::fromMimeSource("other.png"), tr( "Other" ) );
    passLabel->setText( tr( "Password:" ) );
    typeLabel->setText( tr( "Type:" ) );
    loginLabel->setText( tr( "Login:" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
    descrLabel->setText( tr( "Description:" ) );
}

