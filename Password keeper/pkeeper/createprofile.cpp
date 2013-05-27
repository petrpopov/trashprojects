
#include "createprofile.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qdir.h>
#include <qfile.h>
#include <qdatastream.h>
#include <qvalidator.h>

#include "md5.h"

CreateProfile::CreateProfile( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CreateProfile" );
    CreateProfileLayout = new QVBoxLayout( this, 11, 6, "CreateProfileLayout"); 

    infoLabel = new QLabel( this, "infoLabel" );
    CreateProfileLayout->addWidget( infoLabel );

    layout1 = new QGridLayout( 0, 1, 1, 0, 6, "layout1"); 

    repLineEdit = new QLineEdit( this, "repLineEdit" );
    repLineEdit->setEchoMode( QLineEdit::Password );

    layout1->addWidget( repLineEdit, 1, 1 );

//     loginLineEdit = new QLineEdit( this, "loginLineEdit" );

//     layout1->addWidget( loginLineEdit, 0, 1 );

    repLabel = new QLabel( this, "repLabel" );

    layout1->addWidget( repLabel, 1, 0 );

//     loginLabel = new QLabel( this, "loginLabel" );

//     layout1->addWidget( loginLabel, 0, 0 );

    passLineEdit = new QLineEdit( this, "passLineEdit" );
    passLineEdit->setEchoMode( QLineEdit::Password );

    layout1->addWidget( passLineEdit, 0, 1 );

    passLabel = new QLabel( this, "passLabel" );

    layout1->addWidget( passLabel, 0, 0 );
    CreateProfileLayout->addLayout( layout1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout2->addItem( spacer1 );

    clearButton = new QPushButton(this, "clearButton");
    layout2->addWidget(clearButton);
    
    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( FALSE );
    okButton->setDefault( TRUE );
    layout2->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout2->addWidget( cancelButton );
    CreateProfileLayout->addLayout( layout2 );
    languageChange();
    resize( QSize(290, 237).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
//     setTabOrder( loginLineEdit, passLineEdit );
    setTabOrder( passLineEdit, repLineEdit );
    setTabOrder( repLineEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, clearButton );
    
//     connect(loginLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect(passLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect(repLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    
    connect(okButton, SIGNAL( clicked() ), this, SLOT( ok() ) );
    connect(cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect(clearButton, SIGNAL( clicked() ), this, SLOT( clear() ) );
    
    QRegExp regExp("[a-zA-Z0-9]{0,8}");
//     loginLineEdit->setValidator(new QRegExpValidator(regExp, this));
    passLineEdit->setValidator(new QRegExpValidator(regExp, this));
    repLineEdit->setValidator(new QRegExpValidator(regExp, this));
}

void CreateProfile::enableOk()
{
	if(!passLineEdit->text().isEmpty() && !repLineEdit->text().isEmpty())
	{
		if(passLineEdit->text().length() >= 5 && repLineEdit->text().length() >= 5)
			okButton->setEnabled( true );
		else
			okButton->setEnabled( false );
	}
	else
		okButton->setEnabled( false );
}

void CreateProfile::ok()
{
	if(passLineEdit->text() != repLineEdit->text())
	{
		QMessageBox::warning(this, tr("Password keeper"), tr("Entered passwords are not equals to each other!") );
		return;
	}
// 	int l = loginLineEdit->text().length() + passLineEdit->text().length();
// 	if(l >= 255)
// 	{
// 		QMessageBox::warning(this, tr("Password keeper"), tr("Error! Login and password are to long!") );
// 		return;
// 	}
	
	QString home = QDir::homeDirPath();
	QString path = home;
	path += "/.pkeeper";
	
	QDir dir(path);
	if(!dir.exists(path))
		dir.mkdir(path);
	
	path += "/enter.dat";
	QFile file(path);
	if(file.exists())
		file.remove();
	
	if(file.open(IO_WriteOnly))
	{
		QDataStream stream(&file);
// 		QString str = loginLineEdit->text();
// 		str = getHash(str);
// 		stream << str;
		
		QString str = passLineEdit->text();
		str = getHash(str);
		stream << str;
		
		file.close();
		accept();
	}
	else
	{
		QMessageBox::warning(this, tr("Password keeper"), tr("Can't write to file.\nProbably, you have troubles with file permissions."));
		return;
	}
}

void CreateProfile::clear()
{
	passLineEdit->clear();
	repLineEdit->clear();
}

QString CreateProfile::getHash(QString &inString)
{
	char *hash = new char[32];
// 	char *str = new char[inString.length()+1];
// 	str = (char*)inString.data();
	char *str = strdup(inString);
	
  	MD5_string((unsigned char*)str, hash);
	
	QString ret = QString::fromAscii(hash, 32);
	
// 	printf("%s\n", hash);
// 	printf("%s\n", ret.latin1());
	
	delete [] hash;
	delete [] str;
	
	return ret;
}

CreateProfile::~CreateProfile()
{
    // no need to delete child widgets, Qt does it all for us
}


void CreateProfile::languageChange()
{
    setCaption( tr( "Create profile" ) );
    infoLabel->setText( tr( "<b>Warning!</b><br>\n"
"Please, do not choose very simple login and password, or login equals to password!<br>\n"
			  "Password length must be at least 6 digits.") );
    repLabel->setText( tr( "Repeat pass:" ) );
//     loginLabel->setText( tr( "Login:" ) );
    passLabel->setText( tr( "Password:" ) );
    clearButton->setText( tr("Clear") );
    okButton->setText( tr( "Create!" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

