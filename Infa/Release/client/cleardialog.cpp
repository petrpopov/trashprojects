/****************************************************************************
** Form implementation generated from reading ui file 'cleardialog.ui'
**
** Created: Втр Май 17 16:30:48 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "cleardialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qdir.h>

/*
 *  Constructs a ClearDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ClearDialog::ClearDialog( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ClearDialog" );
    ClearDialogLayout = new QGridLayout( this, 1, 1, 11, 6, "ClearDialogLayout"); 

    layout2 = new QVBoxLayout( 0, 0, 6, "layout2"); 

    clearPushButton = new QPushButton( this, "clearPushButton" );
    clearPushButton->setEnabled( FALSE );
    clearPushButton->setDefault( TRUE );
    layout2->addWidget( clearPushButton );

    cancelPushButton = new QPushButton( this, "cancelPushButton" );
    layout2->addWidget( cancelPushButton );

    ClearDialogLayout->addLayout( layout2, 0, 2 );

    clearGroupBox = new QGroupBox( this, "clearGroupBox" );
    clearGroupBox->setColumnLayout(0, Qt::Vertical );
    clearGroupBox->layout()->setSpacing( 6 );
    clearGroupBox->layout()->setMargin( 11 );
    clearGroupBoxLayout = new QGridLayout( clearGroupBox->layout() );
    clearGroupBoxLayout->setAlignment( Qt::AlignTop );

    serversCheckBox = new QCheckBox( clearGroupBox, "serversCheckBox" );

    clearGroupBoxLayout->addWidget( serversCheckBox, 0, 0 );

    mapsCheckBox = new QCheckBox( clearGroupBox, "mapsCheckBox" );

    clearGroupBoxLayout->addWidget( mapsCheckBox, 1, 0 );

    ClearDialogLayout->addWidget( clearGroupBox, 0, 0 );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ClearDialogLayout->addItem( spacer1, 0, 1 );
    languageChange();
    resize( QSize(288, 103).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    
    connect(cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect(clearPushButton, SIGNAL( clicked() ), this, SLOT( clear() ) );
    connect(serversCheckBox, SIGNAL( clicked() ), this, SLOT( enableClearButton() ) );
    connect(mapsCheckBox, SIGNAL( clicked() ), this, SLOT( enableClearButton() ) );
}
void ClearDialog::clear()
{
	QString fileName = QDir::homeDirPath();
	fileName.append("/.client_data");
	QDir dir( fileName );
	if( dir.exists() ){
		if( serversCheckBox->isChecked() ){
			QFile file( fileName + "/servers.txt" );
			if( file.open( IO_WriteOnly ) ){
				QTextStream out(&file);
				out << ' ';
				file.close();
			}
			else {
				QMessageBox::warning(this, tr("NPGR client"), tr("Can't open file '%1' for writing!").arg( fileName + "/servers.txt" ) );
			}
		}
		if( mapsCheckBox->isChecked() ){
			fileName = QDir::homeDirPath();
			QDir d( fileName + "/.client_data/kmaps");
			if( d.exists() ){
				QString rmName;
				QDir dir( fileName );
				QDir d1( fileName + "/.client_data/kmaps/find" );
				QDir d2( fileName + "/.client_data/kmaps/fight" );
				if( d1.exists() ){
					rmName = fileName;
					
					dir.cd( fileName );
					dir.cd("./.client_data/kmaps/find");
					rmName.append("/.client_data/kmaps/find/");
					QStringList findFiles = dir.entryList("*.map");
					
					for ( QStringList::Iterator it = findFiles.begin(); it != findFiles.end(); ++it ) {
						QString name = *it;
						QFile::remove( rmName + name );
						printf("%s - removed\n", (rmName + name).latin1() );
					}
				}
				else {
					QMessageBox::critical(this, tr("NPGR client"), tr("Directory '%1' with necessary files does not exists!").arg( fileName + "/.client_data/kmaps/find" ));
				}
				if( d2.exists() ){
					rmName = fileName;
					
					dir.cd( fileName );
					dir.cd("./.client_data/kmaps/fight");
					rmName.append("/.client_data/kmaps/fight/");
					QStringList fightFiles = dir.entryList("*.map");
					
					for ( QStringList::Iterator it = fightFiles.begin(); it != fightFiles.end(); ++it ) {
						QString name = *it;
						QFile::remove( rmName + name );
						printf("%s - removed\n", (rmName + name).latin1() );
					}
				}
				else {
					QMessageBox::critical(this, tr("NPGR client"), tr("Directory '%1' with necessary files does not exists!").arg( fileName + "/.client_data/kmaps/fight" ));
				}
			}
			else {
				QMessageBox::critical(this, tr("NPGR client"), tr("Directory '%1' with necessary files does not exists!").arg( fileName + "/.client_data/kmaps" ));
			}
		}
	}
	else {
		QMessageBox::critical(this, tr("NPGR client"), tr("Directory '%1' with necessary files does not exists!").arg( fileName ) );
	}
	accept();
}
void ClearDialog::enableClearButton()
{
	if( ( serversCheckBox->isChecked() ) || ( mapsCheckBox->isChecked() ) ){
		clearPushButton->setEnabled( true );
	}
	else {
		clearPushButton->setEnabled( false );
	}
}
/*
 *  Destroys the object and frees any allocated resources
 */
ClearDialog::~ClearDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ClearDialog::languageChange()
{
    setCaption( tr( "Clear data" ) );
    clearPushButton->setText( tr( "Clear !" ) );
    cancelPushButton->setText( tr( "Cancel" ) );
    clearGroupBox->setTitle( tr( "Clear data" ) );
    serversCheckBox->setText( tr( "Servers data" ) );
    mapsCheckBox->setText( tr( "Map files" ) );
}

