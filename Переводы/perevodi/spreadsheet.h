#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <qstringlist.h>
#include <qtable.h>

class Cell;
class SpreadsheetCompare;

class Spreadsheet : public QTable
{
    Q_OBJECT
public:
    Spreadsheet(QWidget *parent = 0, const char *name = 0);
    
    Cell *cell(int row, int col) const;
    void setText(int row, int col, const QString &text);
    QString text(int row, int col) const;
    void setPixmap(int row, int col, const QPixmap &pix);

};

#endif
