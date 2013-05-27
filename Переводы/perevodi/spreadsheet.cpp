
#include "cell.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent, const char *name)
    : QTable(parent, name)
{
    setSelectionMode(Single);
}

Cell *Spreadsheet::cell(int row, int col) const
{
	return (Cell*)item(row, col);
}

QString Spreadsheet::text(int row, int col) const
{
	Cell *c = cell(row, col);
	if(c)
		return c->text();
	else
		return "";
}

void Spreadsheet::setText(int row, int col, const QString &text)
{
	Cell *c = cell(row, col);
	if(c){
		c->setText(text);
		updateCell(row, col);
	}
	else{
		setItem(row, col, new Cell(this, text) );
	}
}

void Spreadsheet::setPixmap(int row, int col, const QPixmap &pix)
{
	Cell *c = cell(row, col);
	if(c){
		c->setPixmap(pix);
		updateCell(row, col);
	}
// 	else{
// 		setItem(row, col, new Cell(this, "") );
// 		c = cell(row, col);
// 		c->setPixmap(pix);
// 		updateCell(row, col);
// 	}
}



