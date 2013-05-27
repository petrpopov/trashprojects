#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>
#include <qcanvas.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QCanvasView;
class QCanvas;
class QGroupBox;
class QLabel;
class QSpinBox;

class MainForm : public QMainWindow
{
	Q_OBJECT

	public:
		MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
		~MainForm();

		QGroupBox* groupBox;
		QCanvasView* canvasView;
		QCanvas* canvas;
		QLabel* nameLabel;
		QLabel* itLabel;
		QSpinBox* spinBox;
		QMenuBar *MenuBarEditor;
		QPopupMenu *File;
		QPopupMenu *Fractal;
		QPopupMenu *Help;
		QAction* helpAboutAction;
		QAction* fileQuitAction;
		QAction* fractalCurveAction;

	protected:
		QGridLayout* MainFormLayout;
		QVBoxLayout* groupBox1Layout;
		QVBoxLayout* layout14;
		QSpacerItem* spacer6;
		QHBoxLayout* layout13;

	protected slots:
		virtual void languageChange();
	private slots:
		void del();
		void about();
		void koh_curve();
		void draw_koh_curve(int);
	private:
		int cur_curve;
		QString cur_name;
};

class MyCurve : public QCanvasRectangle
{
	public:
		MyCurve(QCanvas *canvas);
		~MyCurve();
		
		void drawShape(QPainter &painter);
		void setPoints ( QPointArray pa );
		QRect boundingRect() const;
	private:
		QPointArray ar;
};

#endif // MAINFORM_H
