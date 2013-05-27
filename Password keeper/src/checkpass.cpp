
#include "checkpass.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatastream.h>
#include <qmessagebox.h>
#include <qvalidator.h>

#include "md2.h"

QString *checkKey;

CheckPass::CheckPass( QString &inKey, QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "CheckPass" );
    CheckPassLayout = new QGridLayout( this, 1, 1, 11, 6, "CheckPassLayout"); 

    passLabel = new QLabel( this, "passLabel" );

    CheckPassLayout->addWidget( passLabel, 0, 0 );

    passLineEdit = new QLineEdit( this, "passLineEdit" );
    passLineEdit->setEchoMode( QLineEdit::Password );

    CheckPassLayout->addWidget( passLineEdit, 0, 1 );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout2->addItem( spacer1 );

    clearButton = new QPushButton( this, "clearButton" );
    layout2->addWidget( clearButton );

    okButton = new QPushButton( this, "okButton" );
    okButton->setEnabled( FALSE );
    okButton->setDefault( TRUE );
    layout2->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout2->addWidget( cancelButton );

    CheckPassLayout->addMultiCellLayout( layout2, 2, 2, 0, 1 );
    languageChange();
    resize( QSize(298, 60).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    setTabOrder( passLineEdit, okButton );
    setTabOrder( okButton, cancelButton );
    setTabOrder( cancelButton, clearButton );
    
    checkKey = &inKey;
    
    connect(passLineEdit, SIGNAL( textChanged(const QString &) ), this, SLOT( enableOk() ) );    
    connect(okButton, SIGNAL( clicked() ), this, SLOT( ok() ) );
    connect(cancelButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect(clearButton, SIGNAL( clicked() ), this, SLOT( clear() ) );
    
    QRegExp regExp( "[A-Za-z0-9]{5,8}" );
    passLineEdit->setValidator(new QRegExpValidator(regExp, this));
}

void CheckPass::enableOk()
{
	okButton->setEnabled( passLineEdit->hasAcceptableInput() );
}

void CheckPass::ok()
{
	bool open = false;
	QString pass;
	QString home = QDir::homeDirPath();
	QString path = home;
	path += "/.pkeeper";
	
	QDir dir(path);
	if(!dir.exists(path))
	{
		QMessageBox::warning(this, tr("Password keeper"), tr("Error! You profile doesn't exists!") );
		reject();
	}
	else
	{
		path += "/enter.dat";
		QFile file(path);
		if(!file.exists())
		{
			QMessageBox::warning(this, tr("Password keeper"), tr("Error! You profile doesn't exists!") );
			reject();
		}
		else{
			if(file.open(IO_ReadOnly))
			{
				QDataStream stream(&file);
				
				stream >> pass;
				file.close();
				open = true;
			}
			if(open){	
				QString ePass = passLineEdit->text();
				ePass = getHash(ePass);
				
				if(pass == ePass)
				{
					*checkKey = pass;
					accept();
				}
				else if(pass != ePass)
				{
					QMessageBox::warning(this, tr("Password keeper"), tr("Incorrect password!") );
					clear();
					return;
				}
 			}
		}
	}
}

void CheckPass::clear()
{

	passLineEdit->clear();
}

QString CheckPass::getHash(QString &inStr)
{
// 	char *hash = new char[33];
// 	char *str = new char[inStr.length()+1];
// 	str = (char*)inStr.data();
	char hash[33];
	char *str = strdup(inStr);
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

CheckPass::~CheckPass()
{
    // no need to delete child widgets, Qt does it all for us
}


void CheckPass::languageChange()
{
    setCaption( tr( "Login and password" ) );
//     loginLabel->setText( tr( "Login:" ) );
    passLabel->setText( tr( "Password:" ) );
    clearButton->setText( tr( "Clear" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

