#ifndef CELL_H
#define CELL_H

#include <qtable.h>
#include <qvariant.h>

class Cell : public QTableItem
{
public:
    Cell(QTable *table, const QString &text);
    
    void setText(const QString &text);
    QString text() const;
    void setPixmap(const QPixmap &pix);
    void paint( QPainter * p, const QColorGroup & cg, const QRect & cr, bool selected );
    QWidget *createEditor() const;
    void setContentFromEditor( QWidget *w );
    
    QPixmap pixmap;
    
private:
	QString value;
	
};

#endif
