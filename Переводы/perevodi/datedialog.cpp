
#include "datedialog.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qdatetime.h>

QString *gDate;

DateDialog::DateDialog( QString &date, QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "DateDialog" );
    DateDialogLayout = new QVBoxLayout( this, 11, 6, "DateDialogLayout"); 

    dateTextLabel = new QLabel( this, "dateTextLabel" );
    DateDialogLayout->addWidget( dateTextLabel );

    layout2 = new QHBoxLayout( 0, 0, 6, "layout2"); 

    dayTextLabel = new QLabel( this, "dayTextLabel" );
    layout2->addWidget( dayTextLabel );

    daySpinBox = new QSpinBox( this, "daySpinBox" );
    layout2->addWidget( daySpinBox );

    monthTextLabel = new QLabel( this, "monthTextLabel" );
    layout2->addWidget( monthTextLabel );

    monthSpinBox = new QSpinBox( this, "monthSpinBox" );
    layout2->addWidget( monthSpinBox );

    yearTextLabel = new QLabel( this, "yearTextLabel" );
    layout2->addWidget( yearTextLabel );

    yearSpinBox = new QSpinBox( this, "yearSpinBox" );
	yearSpinBox->setMaxValue(3000);

    layout2->addWidget( yearSpinBox );
    DateDialogLayout->addLayout( layout2 );

    layout1 = new QHBoxLayout( 0, 0, 6, "layout1"); 
    spacer1 = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout1->addItem( spacer1 );

    okButton = new QPushButton( this, "okButton" );
    layout1->addWidget( okButton );

    cancelButton = new QPushButton( this, "cancelButton" );
    layout1->addWidget( cancelButton );
    DateDialogLayout->addLayout( layout1 );
    languageChange();
    resize( QSize(315, 129).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

	connect(cancelButton, SIGNAL( clicked() ), this, SLOT( cancel() ));
	connect(okButton, SIGNAL( clicked() ), this, SLOT( ok() ));

	QDate tDate = QDate::currentDate();
	daySpinBox->setValue( tDate.day() );
	monthSpinBox->setValue( tDate.month() );
	yearSpinBox->setValue( tDate.year() );

	gDate = &date;
}

void DateDialog::ok()
{
	QString s;
	s = QString::number( daySpinBox->value() );
	s += ".";
	s += QString::number( monthSpinBox->value() );
	s += ".";
	s += QString::number( yearSpinBox->value() );

	*gDate = s;

	QDialog::accept();
}

void DateDialog::cancel()
{
	*gDate = "";
	reject();
}

DateDialog::~DateDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void DateDialog::languageChange()
{
    setCaption( tr( "Date" ) );
    dateTextLabel->setText( tr( "Input date" ) );
    dayTextLabel->setText( tr( "Day" ) );
    monthTextLabel->setText( tr( "Month" ) );
    yearTextLabel->setText( tr( "Year" ) );
    okButton->setText( tr( "OK" ) );
    cancelButton->setText( tr( "Cancel" ) );
}

