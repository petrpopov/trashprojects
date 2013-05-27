#include <qlineedit.h>
#include <qpainter.h>
#include <qrect.h>
#include <qpixmap.h>

#include "cell.h"

Cell::Cell(QTable *table, const QString &text)
    : QTableItem(table, OnTyping)
{
	value = text;
}

void Cell::setText(const QString &text)
{
	value = text;
}

QString Cell::text() const
{
	if(!value.isNull())
		return value;
	else
		return "";
}

void Cell::setPixmap(const QPixmap &pix)
{
	pixmap = pix;
}

void Cell::paint( QPainter * p, const QColorGroup & cg, const QRect & cr, bool selected )
{
	p->fillRect( 0, 0, cr.width(), cr.height(),
		     selected ? cg.brush( QColorGroup::Highlight )
	: cg.brush( QColorGroup::Base ) );
 
	int w = cr.width();
	int h = cr.height();
 
	int x = 0;
	if ( !pixmap.isNull() ) {
 		p->drawPixmap( 0, ( cr.height() - pixmap.height() ) / 2, pixmap );
 		x = pixmap.width() + 2;
	}
 
	if ( selected )
		p->setPen( cg.highlightedText() );
	else
		p->setPen( cg.text() );
	p->drawText( x + 2, 0, w - x - 4, h, Qt::AlignRight, text() );
}

QWidget *Cell::createEditor() const
{
	QLineEdit *cb;
	cb = new QLineEdit( table()->viewport() );
	cb->setAlignment(Qt::AlignRight);
	QString text = table()->text(table()->currentRow(), table()->currentColumn());
	
	if(!text.isEmpty()){
		text.replace(" ", "");
	}
	
	cb->setText( text );


	return cb;
}

void Cell::setContentFromEditor( QWidget *w )
{
	if ( w->inherits( "QLineEdit" ) )
		setText( ( (QLineEdit*)w )->text() );
	else
		QTableItem::setContentFromEditor( w );
}
