#include "mainform.h"

#include <qvariant.h>
#include <qcanvas.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qspinbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qpainter.h>
#include <qstatusbar.h>
#include <qmessagebox.h>

//#include <math.h>
#include "itdialog.h"

void koh_shablon(int *x_in, int *y_in, int size)
{
	int x0 = x_in[0];
	int x1 = x_in[1];
	int y0 = y_in[0];
	int y1 = y_in[1];
	
	x_in[0] = x0;
	x_in[1] = (x1 - x0)/3 + x0;
	x_in[2] = (x0 + x1)/2 + (y0 - y1)*1.73/6;
	x_in[3] = (x1 - x0)*2/3 + x0;
	x_in[4] = x1;
	
	y_in[0] = y0;
	y_in[1] = (y1 - y0)/3 + y0;
	y_in[2] = (y0 + y1)/2 + (x1 - x0)*1.73/6;
	y_in[3] = (y1 - y0)*2/3 + y0;
	y_in[4] = y1;
}

MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
	: QMainWindow( parent, name, fl )
{
	(void)statusBar();
	if ( !name )
		setName( "MainForm" );
	setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, sizePolicy().hasHeightForWidth() ) );
	setMinimumSize( QSize( 622, 569 ) );
	setMaximumSize( QSize( 622, 569 ) );
	setCentralWidget( new QWidget( this, "qt_central_widget" ) );
	MainFormLayout = new QGridLayout( centralWidget(), 1, 1, 11, 6, "MainFormLayout"); 

	groupBox = new QGroupBox( centralWidget(), "groupBox1" );
	groupBox->setColumnLayout(0, Qt::Vertical );
	groupBox->layout()->setSpacing( 6 );
	groupBox->layout()->setMargin( 11 );
	groupBox1Layout = new QVBoxLayout( groupBox->layout() );
	groupBox1Layout->setAlignment( Qt::AlignTop );

	canvas = new QCanvas(550,500);
	canvasView = new QCanvasView( canvas, groupBox, "canvasView" );
	canvasView->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, canvasView->sizePolicy().hasHeightForWidth() ) );
	canvasView->setMinimumSize( QSize( 552, 502 ) );
	groupBox1Layout->addWidget( canvasView );

	nameLabel = new QLabel( groupBox, "nameLabel" );
	groupBox1Layout->addWidget( nameLabel );

	MainFormLayout->addWidget( groupBox, 0, 0 );

	layout14 = new QVBoxLayout( 0, 0, 6, "layout14"); 

	layout13 = new QHBoxLayout( 0, 0, 6, "layout13"); 

// 	itLabel = new QLabel( centralWidget(), "itLabel" );
// 	layout13->addWidget( itLabel );

// 	spinBox = new QSpinBox( centralWidget(), "spinBox" );
// 	spinBox->setMinValue( 1 );
// 	layout13->addWidget( spinBox );
	layout14->addLayout( layout13 );
	spacer6 = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
	layout14->addItem( spacer6 );

	MainFormLayout->addLayout( layout14, 0, 1 );

    // actions
	helpAboutAction = new QAction( this, "helpAboutAction" );
	fileQuitAction = new QAction( this, "fileQuitAction" );
	fractalCurveAction = new QAction( this, "fractalCurveAction" );


    // toolbars


    // menubar
	MenuBarEditor = new QMenuBar( this, "MenuBarEditor" );


	File = new QPopupMenu( this );
	fileQuitAction->addTo( File );
	MenuBarEditor->insertItem( QString(""), File, 1 );

	Fractal = new QPopupMenu( this );
	fractalCurveAction->addTo( Fractal );
	MenuBarEditor->insertItem( QString(""), Fractal, 2 );

	Help = new QPopupMenu( this );
	helpAboutAction->addTo( Help );
	MenuBarEditor->insertItem( QString(""), Help, 3 );

	languageChange();
	resize( QSize(622, 569).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
    
	connect(fileQuitAction, SIGNAL( activated() ), this, SLOT( close() ));
	connect(fractalCurveAction, SIGNAL( activated() ), this, SLOT( koh_curve() ) );
	connect(helpAboutAction, SIGNAL( activated() ), this, SLOT( about() ) );
}

void MainForm::del()
{
	QCanvasItemList list = canvas->allItems();
	QCanvasItemList::Iterator it = list.begin();
	for (; it != list.end(); ++it) {
		if ( *it )
			delete *it;
	}
	
	canvas->update();
}

void MainForm::draw_koh_curve(int it)
{
	int num = 2;
	int *x,*y;
	int *xp,*yp;
	int xn[5], yn[5];
	bool ex;
	
	int p = it;
	
	x = new int[num];
	xp = new int[(num - 1)*5];
	y = new int[num];
	yp = new int[(num - 1)*5];
	
	x[0] = 0;
	x[1] = canvas->width()-1;
	y[0] = canvas->height()/2;
	y[1] = canvas->height()/2;
	
	xn[0] = x[0];
	xn[1] = x[1];
	yn[0] = y[0];
	yn[1] = y[1];
	
	
	for(int k = 0; k < p; k++){
		ex = false;
		int i = 0;
		
		while(!ex){
			xn[0] = x[i];
			xn[1] = x[i+1];
			yn[0] = y[i];
			yn[1] = y[i+1];
			
			koh_shablon(xn, yn, 5);
			
			for(int j = 0; j < 5; j++){
				xp[i*5 + j] = xn[j];
				yp[i*5 + j] = yn[j];
			}
			i++;
			if(i == num - 1){
				ex = true;
			}
		}
		delete(x);
		delete(y);
		num = (num - 1)*5;
		x = new int[num];
		y = new int[num];
		
		for(int j = 0; j < num; j++){
			x[j] = xp[j];
			y[j] = yp[j];
		}
		delete(xp);
		delete(yp);
		xp = new int[(num - 1)*5];
		yp = new int[(num - 1)*5];
	}

	for(int j = 0; j < num; j++){
		y[j] = canvas->height() - y[j];
	}
	
	QPointArray arr(num);
	for(int j = 0; j < num; j++){
		arr.setPoint(j, x[j], y[j]);
	}
	MyCurve *mc = new MyCurve(canvas);
	mc->setPen(Qt::blue);
	mc->setPoints(arr);
	mc->show();
	canvas->update();
}

void MainForm::koh_curve()
{
	int iter;
	ItDialog *itdialog = new ItDialog(iter);
	itdialog->exec();
	
	if(itdialog->result() == QDialog::Accepted){
		cur_curve = 0;
		cur_name = "Simple curve";
		nameLabel->setText(cur_name);
	
		del();
		draw_koh_curve(iter);
		canvas->update();
		statusBar()->message(tr("Done!"), 2000);
	}
	else{
		statusBar()->message(tr("Cancelled"), 2000);
	}
	
}

void MainForm::about()
{
	QMessageBox::about(this, "SimpleF", tr("Copyright &copy; 2005, MIPT, piton<br><a href=mailto:piton@mail.mipt.ru>piton@mail.mipt.ru</a>"));
}

MainForm::~MainForm()
{
   
}


void MainForm::languageChange()
{
	setCaption( tr( "SimpleF" ) );
	groupBox->setTitle( tr( "Graph" ) );
	nameLabel->setText( tr( "" ) );
// 	itLabel->setText( tr( "Iterations" ) );
	helpAboutAction->setText( tr( "About" ) );
	helpAboutAction->setMenuText( tr( "A&bout" ) );
	fileQuitAction->setText( tr( "Quit" ) );
	fileQuitAction->setMenuText( tr( "&Quit" ) );
	fileQuitAction->setAccel( tr( "Ctrl+Q" ) );
	fractalCurveAction->setText("Simple curve");
    
	if (MenuBarEditor->findItem(1))
		MenuBarEditor->findItem(1)->setText( tr( "&File" ) );
	if (MenuBarEditor->findItem(2))
		MenuBarEditor->findItem(2)->setText( tr( "Fractal" ) );
	if (MenuBarEditor->findItem(3))
		MenuBarEditor->findItem(3)->setText( tr( "&Help" ) );
}

MyCurve::MyCurve(QCanvas *canvas)
	: QCanvasRectangle(canvas)
{
}

MyCurve::~MyCurve()
{
	hide();
}

void MyCurve::setPoints ( QPointArray pa )
{
	ar = pa;
}

void MyCurve::drawShape(QPainter &painter)
{
	painter.drawPolyline(ar);
}

QRect MyCurve::boundingRect() const
{
	return QRect(0,0,550,500);
}
