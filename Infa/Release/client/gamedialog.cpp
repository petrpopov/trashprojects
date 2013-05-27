#include <qapplication.h>
#include <qcanvas.h>
#include <qvaluelist.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qlayout.h>

#include "gamedialog.h"

#define ROWS 20
#define COLS 20

GameDialog::GameDialog(QWidget *parent, const char *name) : QDialog(parent, name)
{
	setCaption( tr("Game dialog") );
	
	mapCanvas = new QCanvas(this, "mapCanvas");
	mapCanvas->resize(COLS*25, ROWS*25);
	mapCanvas->setAdvancePeriod( 100 );
	
	textCanvas = new QCanvas(this, "textCanvas");
	textCanvas->resize(COLS*25, ROWS*25);
	textCanvas->setAdvancePeriod( 100 );
	
	mapCanvasView = new QCanvasView(mapCanvas, this, "mapCanvasView");
	mapCanvasView->resize(COLS*25+2, ROWS*25+2);
	mapCanvasView->setCanvas(mapCanvas);
	
	QVBoxLayout *vLayout = new QVBoxLayout( this );
	vLayout->setResizeMode( QLayout::Fixed );
	vLayout->addWidget( mapCanvasView );

	showingText = new QCanvasText( textCanvas );
	
	QString fileName = QDir::homeDirPath();
	fileName.append("/.client_data/pixmaps");
	QDir dir( fileName );
	if( !dir.exists() ){
		QMessageBox::critical(this, tr("Game dialog"), tr("Directory %1 with necessary files does not exists!").arg( fileName ) );
	}
	else {
		
		QValueList <QPixmap> pixmapsList;
		pixmapsList.append( QPixmap( fileName + "/exit1.jpg" ) );//0
		pixmapsList.append( QPixmap( fileName + "/sand1.jpg" ) );//1
		pixmapsList.append( QPixmap( fileName + "/wall1.jpg" ) );//2
		pixmapsList.append( QPixmap( fileName + "/zero1.jpg" ) );//3
		pixmapsList.append( QPixmap( fileName + "/fire1.jpg" ) );//4
		pixmapsList.append( QPixmap( fileName + "/fire2.jpg" ) );//5
		pixmapsList.append( QPixmap( fileName + "/fire3.jpg" ) );//6
		pixmapsList.append( QPixmap( fileName + "/fire4.jpg" ) );//7
		pixmapsList.append( QPixmap( fileName + "/hero1.jpg" ) );//8
		pixmapsList.append( QPixmap( fileName + "/hero2.jpg" ) );//9
		pixmapsList.append( QPixmap( fileName + "/hero3.jpg" ) );//10
		pixmapsList.append( QPixmap( fileName + "/hero4.jpg" ) );//11
		pixmapsList.append( QPixmap( fileName + "/robot1.jpg" ) );//12
		pixmapsList.append( QPixmap( fileName + "/robot2.jpg" ) );//13
		pixmapsList.append( QPixmap( fileName + "/robot3.jpg" ) );//14
		pixmapsList.append( QPixmap( fileName + "/robot4.jpg" ) );//15
		
		mapArray = new QCanvasPixmapArray( pixmapsList );
		
		for( int i = 0; i < ROWS; i++ ){
			for( int j = 0; j < 2*COLS; j++ ){
				mapCanvasSprite[i][j] = new QCanvasSprite( mapArray, mapCanvas );
			}
		}
	}
}
void GameDialog::showMap( char *inputMap )
{
	char showmap[ROWS][2*COLS];

	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < 2*COLS; j++){
			showmap[i][j] = inputMap[j + 2*COLS*i];
		}
	}
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < 2*COLS; j += 2){
			switch( showmap[i][j] ){
				case '#' : {
					mapCanvasSprite[i][j]->move(j*25/2, i*25, 2);
					mapCanvasSprite[i][j]->show();
					break;
				}
				case ' ' : {
					mapCanvasSprite[i][j]->move(j*25/2, i*25, 1);
					mapCanvasSprite[i][j]->show();
					break;
				}
				case '$' : {
					mapCanvasSprite[i][j]->move(j*25/2, i*25, 0);
					mapCanvasSprite[i][j]->show();
					break;
				}
				case '?' : {
					mapCanvasSprite[i][j]->move(j*25/2, i*25, 3);
					mapCanvasSprite[i][j]->show();
					break;
				}
				case 'H' : {
					if( showmap[i][j+1] == '1' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 8);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '2' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 9);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '3' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 10);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '4' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 11);
						mapCanvasSprite[i][j]->show();
					}
					break;
				}
				case 'R' : {
					if( showmap[i][j+1] == '1' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 12);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '2' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 13);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '3' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 14);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '4' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 15);
						mapCanvasSprite[i][j]->show();
					}
					break;
				}
				case 'F' : {
					if( showmap[i][j+1] == '1' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 4);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '2' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 5);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '3' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 6);
						mapCanvasSprite[i][j]->show();
					}else if( showmap[i][j+1] == '4' ){
						mapCanvasSprite[i][j]->move(j*25/2, i*25, 7);
						mapCanvasSprite[i][j]->show();
					}
					break;
				}
			}
		}
	}
}
void GameDialog::showText( const QString &text, int result )
{
	showingText->hide();
	showingText->setText( text );
	showingText->setFont( QFont( "Helvetica", 24 ) );
	if( result == -1 ){
		showingText->move( textCanvas->width()/3 + 20, textCanvas->height()/3);
		showingText->setColor( QColor( "blue" ) );
	}
	if( result > 0 ){
		showingText->move( textCanvas->width()/4 - 30, textCanvas->height()/3);
		showingText->setColor( QColor( "red" ) );
	}
	if( result == 50 ){
		showingText->move( textCanvas->width()/3 + 20, textCanvas->height()/3);
		showingText->setColor( QColor( "magenta" ) );
	}
	if( result == 100 ){
		showingText->move( textCanvas->width()/3 + 30, textCanvas->height()/3 );
		showingText->setColor( QColor("darkRed") );
	}
	showingText->show();
}
void GameDialog::changeCanvas( const QString &canvas )
{
	if( canvas == "map" ){
		mapCanvasView->setCanvas( mapCanvas );
	}
	if( canvas == "text" ){
		mapCanvasView->setCanvas( textCanvas );
	}
}










