#include "itdialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

int *pit;

ItDialog::ItDialog( int &it, QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ItDialog" );
    ItDialogLayout = new QVBoxLayout( this, 11, 6, "ItDialogLayout"); 

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    textLabel = new QLabel( this, "textLabel" );
    layout2->addWidget( textLabel );

    spinBox = new QSpinBox( this, "spinBox" );
    spinBox->setMinValue( 1 );
    spinBox->setValue( 3 );
    layout2->addWidget( spinBox );
    ItDialogLayout->addLayout( layout2 );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    okPushButton = new QPushButton( this, "okPushButton" );
    layout1->addWidget( okPushButton );

    cancelPushButton = new QPushButton( this, "cancelPushButton" );
    layout1->addWidget( cancelPushButton );
    ItDialogLayout->addLayout( layout1 );
    languageChange();
    resize( QSize(301, 78).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    connect(okPushButton, SIGNAL( clicked() ), this, SLOT( ok() ));    
    connect(cancelPushButton, SIGNAL( clicked() ), this, SLOT( reject() ) );
    
    pit = &it;
}

void ItDialog::ok()
{
	*pit = spinBox->value();
	accept();
}

ItDialog::~ItDialog()
{
}


void ItDialog::languageChange()
{
    setCaption( tr( "Input number of iterations" ) );
    textLabel->setText( tr( "Iterations:" ) );
    okPushButton->setText( tr( "OK" ) );
    cancelPushButton->setText( tr( "Cancel" ) );
}

