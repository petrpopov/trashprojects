
#include "dateinterval.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qvalidator.h>

QString *p_string;

DateInterval::DateInterval( QString &dateStr, QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "DateInterval" );
    DateIntervalLayout = new QVBoxLayout( this, 11, 6, "DateIntervalLayout"); 

    buttonGroup = new QButtonGroup( this, "buttonGroup" );
    buttonGroup->setColumnLayout(0, Qt::Vertical );
    buttonGroup->layout()->setSpacing( 6 );
    buttonGroup->layout()->setMargin( 11 );
    buttonGroupLayout = new QVBoxLayout( buttonGroup->layout() );
    buttonGroupLayout->setAlignment( Qt::AlignTop );

    layout4 = new QHBoxLayout( 0, 0, 6, "layout4"); 

    radioButton1 = new QRadioButton( buttonGroup, "radioButton1" );
    layout4->addWidget( radioButton1 );

    groupBox = new QGroupBox( buttonGroup, "groupBox" );
    groupBox->setColumnLayout(0, Qt::Vertical );
    groupBox->layout()->setSpacing( 6 );
    groupBox->layout()->setMargin( 11 );
    groupBoxLayout = new QVBoxLayout( groupBox->layout() );
    groupBoxLayout->setAlignment( Qt::AlignTop );

    inputLabel = new QLabel( groupBox, "inputLabel" );
    groupBoxLayout->addWidget( inputLabel );

    layout3 = new QHBoxLayout( 0, 0, 6, "layout3"); 

    beginLabel = new QLabel( groupBox, "beginLabel" );
    layout3->addWidget( beginLabel );

    beginLineEdit = new QLineEdit( groupBox, "beginLineEdit" );
    layout3->addWidget( beginLineEdit );

    endLabel = new QLabel( groupBox, "endLabel" );
    layout3->addWidget( endLabel );

    endLineEdit = new QLineEdit( groupBox, "endLineEdit" );
    layout3->addWidget( endLineEdit );
    groupBoxLayout->addLayout( layout3 );
    layout4->addWidget( groupBox );
    buttonGroupLayout->addLayout( layout4 );

    radioButton2 = new QRadioButton( buttonGroup, "radioButton2" );
    buttonGroupLayout->addWidget( radioButton2 );
    DateIntervalLayout->addWidget( buttonGroup );

    layout5 = new QHBoxLayout( 0, 0, 6, "layout5"); 
    spacer2 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout5->addItem( spacer2 );

    okButton = new QPushButton( this, "okButton" );
    okButton->setDefault( TRUE );
    layout5->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout5->addWidget( cancelButton );
    DateIntervalLayout->addLayout( layout5 );
    languageChange();
    resize( QSize(580, 187).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // tab order
    setTabOrder( radioButton1, radioButton2 );
    setTabOrder( radioButton2, beginLineEdit );
    setTabOrder( beginLineEdit, endLineEdit );
    setTabOrder( endLineEdit, okButton );
    setTabOrder( okButton, cancelButton );
    
    radioButton1->setChecked(TRUE);
    
    QRegExp regExp("[0-9]{1,2}[.]{1,1}[0-9]{1,2}[.]{1,1}[0-9]{1,4}");
    beginLineEdit->setValidator(new QRegExpValidator(regExp, this));
    endLineEdit->setValidator(new QRegExpValidator(regExp, this));
    
    connect(radioButton1, SIGNAL( stateChanged(int) ), this, SLOT( enableDate() ) );
    connect(radioButton2, SIGNAL( stateChanged(int) ), this, SLOT( enableDate() ) );
    connect(cancelButton, SIGNAL( clicked() ), SLOT( reject() ) );
    connect(okButton, SIGNAL( clicked() ), SLOT( ok() ) );
    connect(beginLineEdit, SIGNAL( textChanged( const QString & ) ), this, SLOT( enableOk() ) );
    
    okButton->setEnabled(FALSE);
    
    p_string = &dateStr;
    
    if(!dateStr.isEmpty()){
	    beginLineEdit->setText(dateStr);
    }
}

void DateInterval::enableOk()
{
	if(beginLineEdit->text().isEmpty())
		okButton->setEnabled(FALSE);
	else
		okButton->setEnabled(TRUE);
}


void DateInterval::enableDate()
{
	if(radioButton1->isChecked()){
		groupBox->setEnabled(TRUE);
		enableOk();
	}
	else{
		groupBox->setEnabled(FALSE);
		okButton->setEnabled(TRUE);
	}
}

void DateInterval::ok()
{
	if(radioButton1->isChecked()){
		QString str = beginLineEdit->text();
		str += ";";
		str += endLineEdit->text();
		
		*p_string = str;
	}
	else{
		if(radioButton2->isChecked()){	
			QString str = "all";
			*p_string = str;
		}
	}	
	
	accept();
}

DateInterval::~DateInterval()
{
    // no need to delete child widgets, Qt does it all for us
}


void DateInterval::languageChange()
{
    setCaption( tr( "Date interval" ) );
    buttonGroup->setTitle( tr( "Print interval" ) );
    radioButton1->setText( tr( "Print selected:" ) );
    groupBox->setTitle( tr( "Date" ) );
    inputLabel->setText( tr( "Input date interval:" ) );
    beginLabel->setText( tr( "Begin:" ) );
    endLabel->setText( tr( "End:" ) );
    radioButton2->setText( tr( "Print all" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

