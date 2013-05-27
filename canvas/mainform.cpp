#include "mainform.h"

#include <qvariant.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qcanvas.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qapplication.h>
#include <qvaluelist.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qfile.h>
#include <qtextstream.h>

int X = 713;
int Y = 574;

int i = 0;

QString mainPath;
QStringList newsList;
int newsIndex = 0;

MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
	: QWidget( parent, name, fl )
{
    if ( !name )
	setName( "MainForm" );

    setMouseTracking(true);
    mLeftPressed = false;
    
    mainCanvas = new QCanvas(this);
    mainCanvas->resize(X, Y);
    
    mainCanvasView = new QCanvasView(mainCanvas, this);
    mainCanvasView->resize(X+2, Y+2);
    
    QPixmap mainPixmap = QPixmap::fromMimeSource("journal.bmp"); 
    mainPixmap.setMask( mainPixmap.createHeuristicMask() );
    
    mainCanvas->setBackgroundPixmap(mainPixmap);
    mainCanvasView->setMask( mainPixmap.createHeuristicMask() );
    setMask( mainPixmap.createHeuristicMask() );
    
    mainPath = qApp->applicationDirPath();
    mainPath += "/images/";
    
    textColor= new QColor(0, 165, 200);
    
    QString path = qApp->applicationDirPath();
    QFile file(path + "/data/News.txt");
    if(file.open(IO_ReadOnly))
    {
	    QTextStream stream(&file);
	    QString str = stream.read();
	    file.close();	   
	    
	    newsList = QStringList::split("\n", str);
    }
    
    createButtons();
    createCanvas( "main" );
    currentCanvas = "main";
    
    
    languageChange();
    resize( QSize(X, Y).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

void MainForm::createCanvas(QString name)
{
	if(name == "main")
	{
		powerSprite->setCanvas(mainCanvas);
		powerSprite->move(10, 465, 0);
	 	powerSprite->show();
		
		databaseSprite->setCanvas(mainCanvas);
		databaseSprite->move(548, 502);
	 	databaseSprite->show();
		
		journalSprite->setCanvas(mainCanvas);
		journalSprite->move(608, 477);
	 	journalSprite->show();
		
		navigationSprite->setCanvas(mainCanvas);
		navigationSprite->move(639, 468);
	 	navigationSprite->show();
		
		newsSprite->setCanvas(mainCanvas);
		newsSprite->move(290, 130);
		newsSprite->show();
		
//   		newsText->setText("Hello, world!\nGoodbye America!");
		QStringList a = QStringList::split("\t", newsList[newsIndex]);
		QString str = a[0];
		newsText->setTextFlags(Qt::AlignHCenter);
		newsText->setText(str);
		newsText->move(260, 280);
		newsText->show();
		
		rtSprite->setCanvas(mainCanvas);
		rtSprite->move(650, 82);
		rtSprite->show();
		
		rSprite->setCanvas(mainCanvas);
		rSprite->move(650, 105);
		rSprite->show();
		
		ltSprite->setCanvas(mainCanvas);
		ltSprite->move(433, 82);
		ltSprite->show();
		
		lSprite->setCanvas(mainCanvas);
		lSprite->move(433,105);
		lSprite->show();
		
		mainCanvas->update();
	}
}

void MainForm::createButtons()
{
	QValueList<QPixmap> pixList;
    
	powerPix = new QPixmap();
	powerPix->load(mainPath + "power0000.bmp");
	powerPix->setMask(powerPix->createHeuristicMask());
	pixList.append(*powerPix);
	powerPix->load(mainPath + "power0001.bmp");
	powerPix->setMask(powerPix->createHeuristicMask());
	pixList.append(*powerPix);
	powerPix->load(mainPath + "power0002.bmp");
	powerPix->setMask(powerPix->createHeuristicMask());
	pixList.append(*powerPix);
   
	powerArray = new QCanvasPixmapArray(pixList);
	powerSprite = new QCanvasSprite(powerArray, mainCanvas);
    
	pixList.clear();
	databasePix = new QPixmap();
	databasePix->load(mainPath + "database0000.bmp");
	databasePix->setMask(databasePix->createHeuristicMask());
	pixList.append(*databasePix);
	databasePix->load(mainPath + "database0001.bmp");
	databasePix->setMask(databasePix->createHeuristicMask());
	pixList.append(*databasePix);
	databasePix->load(mainPath + "database0002.bmp");
	databasePix->setMask(databasePix->createHeuristicMask());
	pixList.append(*databasePix);
    
	databaseArray = new QCanvasPixmapArray(pixList);
	databaseSprite = new QCanvasSprite(databaseArray, mainCanvas);
	
	pixList.clear();
	journalPix = new QPixmap();
	journalPix->load(mainPath + "journal0000.bmp");
	journalPix->setMask(journalPix->createHeuristicMask());
	pixList.append(*journalPix);
	journalPix->load(mainPath + "journal0001.bmp");
	journalPix->setMask(journalPix->createHeuristicMask());
	pixList.append(*journalPix);
	journalPix->load(mainPath + "journal0002.bmp");
	journalPix->setMask(journalPix->createHeuristicMask());
	pixList.append(*journalPix);
	
	journalArray = new QCanvasPixmapArray(pixList);
	journalSprite = new QCanvasSprite(journalArray, mainCanvas);
	
	pixList.clear();
	navigationPix = new QPixmap();
	navigationPix->load(mainPath + "navigation0000.bmp");
	navigationPix->setMask(navigationPix->createHeuristicMask());
	pixList.append(*navigationPix);
	navigationPix->load(mainPath + "navigation0001.bmp");
	navigationPix->setMask(navigationPix->createHeuristicMask());
	pixList.append(*navigationPix);
	navigationPix->load(mainPath + "navigation0002.bmp");
	navigationPix->setMask(navigationPix->createHeuristicMask());
	pixList.append(*navigationPix);
	
	navigationArray = new QCanvasPixmapArray(pixList);
	navigationSprite = new QCanvasSprite(navigationArray, mainCanvas);
	
	//news pix and text
	pixList.clear();
	newsPix = new QPixmap();
	newsPix->load(mainPath + "news/delichi.bmp");
	pixList.append(*newsPix);
	newsPix->load(mainPath + "news/gentis.bmp");
	pixList.append(*newsPix);
	newsPix->load(mainPath + "news/htpd.bmp");
	pixList.append(*newsPix);
	newsPix->load(mainPath + "news/hyperspace.bmp");
	pixList.append(*newsPix);
	newsPix->load(mainPath + "news/mayor.bmp");
	pixList.append(*newsPix);
	newsPix->load(mainPath + "news/son.bmp");
	pixList.append(*newsPix);
	newsPix->load(mainPath + "news/tpn.bmp");
	pixList.append(*newsPix);
    
	newsArray = new QCanvasPixmapArray(pixList);
	newsSprite = new QCanvasSprite(newsArray, mainCanvas);
	
	newsText = new QCanvasText(mainCanvas);
	newsText->setColor(*textColor);
	newsText->setFont( QFont("Helvetica", 12) );
	
	//arrow buttons
	pixList.clear();
	rlPix = new QPixmap();
	rlPix->load(mainPath + "rt0000.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "rt0001.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "rt0002.png");
	pixList.append(*rlPix);
	
	rtArray = new QCanvasPixmapArray(pixList);
	rtSprite = new QCanvasSprite(rtArray, mainCanvas);
	
	pixList.clear();
	rlPix->load(mainPath + "r0000.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "r0001.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "r0002.png");
	pixList.append(*rlPix);
	
	rArray = new QCanvasPixmapArray(pixList);
	rSprite = new QCanvasSprite(rArray, mainCanvas);
	
	pixList.clear();
	rlPix->load(mainPath + "lt0000.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "lt0001.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "lt0002.png");
	pixList.append(*rlPix);
	
	ltArray = new QCanvasPixmapArray(pixList);
	ltSprite = new QCanvasSprite(ltArray, mainCanvas);
	
	pixList.clear();
	rlPix->load(mainPath + "l0000.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "l0001.png");
	pixList.append(*rlPix);
	rlPix->load(mainPath + "l0002.png");
	pixList.append(*rlPix);
	
	lArray = new QCanvasPixmapArray(pixList);
	lSprite = new QCanvasSprite(lArray, mainCanvas);
}

void MainForm::mousePressEvent(QMouseEvent *pe)
{
	if(pe->button() == Qt::LeftButton)
	{
		mLeftPressed = true;
		
		int x = pe->pos().x();
		int y = pe->pos().y();
		
		QString who = whichButton(x, y);
		if(who == "power")
			powerSprite->setFrame(1);
		else if(who == "database")
			databaseSprite->setFrame(1);
		else if(who == "journal")
			journalSprite->setFrame(1);
		else if(who == "navigation")
			navigationSprite->setFrame(1);
		else if(who == "rt")
			rtSprite->setFrame(1);
		else if(who == "r")
			rSprite->setFrame(1);
		else if(who == "lt")
			ltSprite->setFrame(1);
		else if(who == "l")
			lSprite->setFrame(1);
		else if(who == "none")
			setFrameZeroButtons();
		
		if(currentCanvas == "main")
			mainCanvas->update();
	}
	mPosition = pe->pos();
}

void MainForm::mouseMoveEvent(QMouseEvent *pe)
{
	if(mLeftPressed)
	{
		move( pe->globalPos() - mPosition );
	}
	
	int x = pe->pos().x();
	int y = pe->pos().y();
	
	QString who = whichButton(x,y);
	setFrameZeroButtons();
	
	if(who == "power")
		powerSprite->setFrame(2);
	else if(who == "database")
		databaseSprite->setFrame(2);
	else if(who == "journal")
		journalSprite->setFrame(2);
	else if(who == "navigation")
		navigationSprite->setFrame(2);
	else if(who == "rt")
		rtSprite->setFrame(2);
	else if(who == "r")
		rSprite->setFrame(2);
	else if(who == "lt")
		ltSprite->setFrame(2);
	else if(who == "l")
		lSprite->setFrame(2);
	else if(who == "none")
		setFrameZeroButtons();
	
	if(currentCanvas == "main")
		mainCanvas->update();
		
}

void MainForm::mouseReleaseEvent(QMouseEvent *pe)
{
	if(pe->button() == Qt::LeftButton)
	{
		mLeftPressed = false;
		
		int x = pe->pos().x();
		int y = pe->pos().y();
		
		QString who = whichButton(x, y);
 		if(who == "power")
		{
			powerSprite->setFrame(2);
  			close();
		}
		else if(who == "database")
			databaseSprite->setFrame(2);
		else if(who == "journal")
			journalSprite->setFrame(2);
		else if(who == "navigation")
			navigationSprite->setFrame(2);
		else if(who == "rt")
			rtSprite->setFrame(2);
		else if(who == "r")
			rSprite->setFrame(2);
		else if(who == "lt")
			ltSprite->setFrame(2);
		else if(who == "l")
			lSprite->setFrame(2);
		else if(who == "none")
			setFrameZeroButtons();
		
		if(currentCanvas == "main")
			mainCanvas->update();
	}
}

QString MainForm::whichButton(int x, int y)
{
	if(x >= 10 && x <= powerPix->width()+10 && y >= 465 && y <= powerPix->height()+465)
		return "power";
	if(x >= 548 && x <= databasePix->width()+548 && y>= 502 && y <= databasePix->height()+502)
		return "database";
	if(x >= 608 && x <= journalPix->width()+608 && y >= 477 && y <= journalPix->height()+477)
		return "journal";
	if(x>=639 && x <= navigationPix->width()+639 && y >=468 && y <= navigationPix->height()+468)
		return "navigation";
	if(x >= 650 && x <= rlPix->width()+650 && y >= 82 && y <= rlPix->height()+82)
		return "rt";
	if(x >= 650 && x <= rlPix->width()+650 && y >= 105 && y <= rlPix->height()+105)
		return "r";
	if(x >= 433 && x <= rlPix->width()+433 && y >= 82 && y <= rlPix->height()+82)
		return "lt";
	if(x >= 433 && x <= rlPix->width()+433 && y >= 105 && y <= rlPix->height()+105)
		return "l";
	
	return "none";
}

void MainForm::setFrameZeroButtons()
{
	powerSprite->setFrame(0);
	databaseSprite->setFrame(0);
	journalSprite->setFrame(0);
	navigationSprite->setFrame(0);
	rtSprite->setFrame(0);
	rSprite->setFrame(0);
	ltSprite->setFrame(0);
	lSprite->setFrame(0);
}



MainForm::~MainForm()
{
    
}


void MainForm::languageChange()
{
    setCaption( tr( "PoL" ) );
}

