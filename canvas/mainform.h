
#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QCanvas;
class QCanvasView;
class QCanvasSprite;
class QCanvasPixmapArray;
class QCanvasText;
class QPoint;

class MainForm : public QWidget
{
    Q_OBJECT

public:
	MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel | Qt::WStyle_Customize | Qt::WStyle_NoBorder);
    ~MainForm();

    QColor *textColor;
    QCanvasText *newsText;
    QString currentCanvas;
    
    QCanvas *mainCanvas;
    QCanvasView *mainCanvasView;
    
    QCanvasSprite *powerSprite;
    QCanvasPixmapArray *powerArray;
    QPixmap *powerPix;
    
    QCanvasSprite *databaseSprite;
    QCanvasPixmapArray *databaseArray;
    QPixmap *databasePix;
    
    QCanvasSprite *journalSprite;
    QCanvasPixmapArray *journalArray;
    QPixmap *journalPix;
    
    QCanvasSprite *navigationSprite;
    QCanvasPixmapArray *navigationArray;
    QPixmap *navigationPix;
    
    QCanvasSprite *newsSprite;
    QCanvasPixmapArray *newsArray;
    QPixmap *newsPix;
    
    //arrow buttons
    QCanvasSprite *rSprite;
    QCanvasPixmapArray *rArray;
    
    QCanvasSprite *rtSprite;
    QCanvasPixmapArray *rtArray;
    
    QCanvasSprite *lSprite;
    QCanvasPixmapArray *lArray;
    
    QCanvasSprite *ltSprite;
    QCanvasPixmapArray *ltArray;
    QPixmap *rlPix;
    
private:
	QPoint mPosition;
	bool mLeftPressed;
	
public slots:	
	void createButtons();
	void createCanvas(QString name);
	
private slots:
	virtual void mousePressEvent(QMouseEvent *pe);
	virtual void mouseMoveEvent(QMouseEvent *pe);
	virtual void mouseReleaseEvent(QMouseEvent *pe);
	QString whichButton(int x, int y);
	void setFrameZeroButtons();
	
protected slots:
    virtual void languageChange();

};

#endif // MAINFORM_H
