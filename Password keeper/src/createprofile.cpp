
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

#include "md2.h"


CreateProfile::CreateProfile( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CreateProfile" );
    CreateProfileLayout = new QGridLayout( this, 1, 1, 11, 6, "CreateProfileLayout"); 

    infoLabel = new QLabel( this, "infoLabel" );

    CreateProfileLayout->addMultiCellWidget( infoLabel, 0, 0, 0, 1 );

    passLabel = new QLabel( this, "passLabel" );

    CreateProfileLayout->addWidget( passLabel, 1, 0 );

    repLabel = new QLabel( this, "repLabel" );

    CreateProfileLayout->addWidget( repLabel, 2, 0 );

    passLineEdit = new QLineEdit( this, "passLineEdit" );
    passLineEdit->setEchoMode(QLineEdit::Password);

    CreateProfileLayout->addWidget( passLineEdit, 1, 1 );

    repLineEdit = new QLineEdit( this, "repLineEdit" );
    repLineEdit->setEchoMode(QLineEdit::Password);

    CreateProfileLayout->addWidget( repLineEdit, 2, 1 );

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

    CreateProfileLayout->addMultiCellLayout( layout1, 3, 3, 0, 1 );
    languageChange();
    resize( QSize(311, 170).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( passLineEdit, repLineEdit );
    setTabOrder( repLineEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, clearButton );
    
    connect(passLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    connect(repLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );
    
    connect(okButton, SIGNAL( clicked() ), this, SLOT( ok() ) );
    connect(cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect(clearButton, SIGNAL( clicked() ), this, SLOT( clear() ) );
    
    QRegExp regExp("[a-zA-Z0-9]{0,8}");
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
// 	char *hash = new char[33];
// 	char *str = new char[inStr.length()+1];
// 	str = (char*)inStr.data();
	char hash[33];
	char *str = strdup(inString);
	MD2 *md2 = new MD2();
	md2->computeHash((unsigned char*)str, strlen(str), hash);
	
// 	MD5_string((unsigned char*)str, hash);
	
	QString ret = QString::fromAscii(hash, 32);
	
// 	printf("%s\n", hash);
// 	printf("%s\n", ret.latin1());
	
// 	delete [] hash;
	delete [] str;
	
	return ret;
}


/*
 *  Destroys the object and frees any allocated resources
 */
CreateProfile::~CreateProfile()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CreateProfile::languageChange()
{
    setCaption( tr( "Create profile" ) );
    infoLabel->setText( tr( "Enter the password for your profile.<br><b>Warning!</b><br>\n"
"Please, do not choose very simple  password!<br>\n"
"Its length must be at least 6 digits." ) );
    passLabel->setText( tr( "Password:" ) );
    repLabel->setText( tr( "Repeat pass:" ) );
    clearButton->setText( tr( "Clear" ) );
    okButton->setText( tr( "Create!" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

