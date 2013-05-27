#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <qdialog.h>

#define ROWS 20
#define COLS 20

class QCanvas;
class QCanvasView;
class QCanvasSprite;
class QCanvasPixmapArray;
class QCanvasText;

class GameDialog : public QDialog
{
	Q_OBJECT
	public:
		GameDialog(QWidget *parent = 0, const char *name = 0);
	public slots:
		void showMap( char *inputMap );
		void showText( const QString &text, int result );
		void changeCanvas( const QString &canvas );
	private:
		QCanvas *mapCanvas;
		QCanvas *textCanvas;
		QCanvasView *mapCanvasView;
		QCanvasSprite *mapCanvasSprite[ROWS][2*COLS];
		QCanvasPixmapArray *mapArray;
		QCanvasText *showingText;
	public:
		int ex;
};
#endif
