
#include "changeprofile.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qvalidator.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatastream.h>

QString *changePass;

ChangeProfile::ChangeProfile( QString &inPass, QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ChangeProfile" );
    ChangeProfileLayout = new QVBoxLayout( this, 11, 6, "ChangeProfileLayout"); 

    infoLabel = new QLabel( this, "infoLabel" );
    ChangeProfileLayout->addWidget( infoLabel );

    layout2 = new QGridLayout( 0, 1, 1, 0, 6, "layout2"); 

    repLabel = new QLabel( this, "repLabel" );

    layout2->addWidget( repLabel, 1, 0 );

    passLineEdit = new QLineEdit( this, "oldLineEdit" );
    passLineEdit->setEchoMode( QLineEdit::Password );

    layout2->addWidget( passLineEdit, 0, 1 );

    repLineEdit = new QLineEdit( this, "newLineEdit" );
    repLineEdit->setEchoMode( QLineEdit::Password );

    layout2->addWidget( repLineEdit, 1, 1 );

    passLabel = new QLabel( this, "passLabel" );

    layout2->addWidget( passLabel, 0, 0 );

    ChangeProfileLayout->addLayout( layout2 );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    clearButton = new QPushButton( this, "clearButton" );
    layout1->addWidget( clearButton );

    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( FALSE );
    okButton->setDefault( TRUE );
    layout1->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout1->addWidget( cancelButton );
    ChangeProfileLayout->addLayout( layout1 );
    languageChange();
    resize( QSize(288, 148).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( passLineEdit, repLineEdit );
    setTabOrder( repLineEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, clearButton );
    
    changePass = &inPass;
    
    connect(passLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect(repLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    
    connect(okButton, SIGNAL( clicked() ), this, SLOT( ok() ) );
    connect(cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    
    QRegExp regExp("[a-zA-Z0-9]{0,8}");
    passLineEdit->setValidator(new QRegExpValidator(regExp, this));
    repLineEdit->setValidator(new QRegExpValidator(regExp, this));
}


void ChangeProfile::enableOk()
{
	if(passLineEdit->text().length() >= 5 && repLineEdit->text().length() >= 5)
		okButton->setEnabled(true);
	else
		okButton->setEnabled(false);
}

void ChangeProfile::ok()
{
	if(passLineEdit->text() != repLineEdit->text())
		QMessageBox::warning(this, tr("Password keeper"), tr("Entered passwords are not equal each other!") );
	else
	{
		*changePass = passLineEdit->text();
		accept();
	}
	
}

/*
 *  Destroys the object and frees any allocated resources
 */
ChangeProfile::~ChangeProfile()
{
    // no need to delete child widgets, Qt does it all for us
}


void ChangeProfile::languageChange()
{
    setCaption( tr( "Change login or password" ) );
    infoLabel->setText( tr( "Input here new password:" ) );
    repLabel->setText( tr( "Repeat password:" ) );
    passLabel->setText( tr( "New password:" ) );
//     loginLabel->setText( tr( "Login:" ) );
    clearButton->setText( tr( "Clear" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

