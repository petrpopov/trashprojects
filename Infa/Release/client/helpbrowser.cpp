#include "helpbrowser.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qdir.h>

/*
 *  Constructs a HelpBrowser as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
HelpBrowser::HelpBrowser( QWidget* parent, const char* name )
    : QWidget( parent, name, WGroupLeader )
{
    if ( !name )
	setName( "HelpBrowser" );
    HelpBrowserLayout = new QGridLayout( this, 1, 1, 11, 6, "HelpBrowserLayout"); 
    setIcon(QPixmap::fromMimeSource("help.png"));

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 

    homePushButton = new QPushButton( this, "homePushButton" );
    homePushButton->setPixmap( QPixmap::fromMimeSource( "home.png" ) );
    layout1->addWidget( homePushButton );

    backPushButton = new QPushButton( this, "backPushButton" );
    backPushButton->setPixmap( QPixmap::fromMimeSource( "back.png" ) );
    layout1->addWidget( backPushButton );
    forwardPushButton = new QPushButton(this, "forwardPushButton");
    forwardPushButton->setPixmap( QPixmap::fromMimeSource( "fwd.png" ) );
    layout1->addWidget( forwardPushButton );
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    closePushButton = new QPushButton( this, "closePushButton" );
    closePushButton->setPixmap( QPixmap::fromMimeSource( "exit.png" ) );
    layout1->addWidget( closePushButton );

    HelpBrowserLayout->addLayout( layout1, 0, 0 );

    textBrowser = new QTextBrowser( this, "textBrowser" );

    HelpBrowserLayout->addWidget( textBrowser, 1, 0 );
    languageChange();
    resize( QSize(600, 400).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    
    connect(closePushButton, SIGNAL( clicked() ), this, SLOT( close() ) );
    connect(homePushButton, SIGNAL( clicked() ), this, SLOT( home() ) );
    connect(backPushButton, SIGNAL( clicked() ), this, SLOT( back() ) );
    connect(forwardPushButton, SIGNAL( clicked() ), this, SLOT( forward() ) );
    connect(textBrowser, SIGNAL( sourceChanged( const QString & ) ), this, SLOT( updateCaption() ) );
}
void HelpBrowser::showPage( const QString &fileName )
{
	QString name = QDir::homeDirPath();
	name.append("/.client_data/doc/");
	name.append(fileName);
	textBrowser->setSource(name);
	QString caption;
	caption = tr("Help: %1").arg( textBrowser->documentTitle() );
	setCaption( caption );
}
void HelpBrowser::updateCaption()
{
	QString caption;
	caption = tr("Help: %1").arg( textBrowser->documentTitle() );
	setCaption( caption );
}
void HelpBrowser::home()
{
	showPage("index.htm");
}
void HelpBrowser::back()
{
	textBrowser->backward();
}
void HelpBrowser::forward()
{
	textBrowser->forward();
}
/*
 *  Destroys the object and frees any allocated resources
 */
HelpBrowser::~HelpBrowser()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void HelpBrowser::languageChange()
{
    setCaption( tr( "Help:" ) );
   // homePushButton->setToolTip( tr( "Home" ) );
    //backPushButton->setToolTip( tr( "Back" ) );
    //forwardPushButton->setToolTip( tr("Forward") );
    //closePushButton->setToolTip( tr( "Close" ) );
}

