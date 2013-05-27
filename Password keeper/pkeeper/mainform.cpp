
#include "mainform.h"

#include <qvariant.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qfile.h>
#include <qdir.h>
#include <qdatastream.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qpixmap.h>
#include <qbitmap.h>
#include <qapplication.h>


#include "newfield.h"
#include "createprofile.h"
#include "checkpass.h"
#include "changeprofile.h"
#include "rc4.h"
#include "md5.h"


CurList saveList;
vector<CurList> undoList;
int undoCount = -1;

QString gKey;


MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
    (void)statusBar();
    if ( !name )
	setName( "MainForm" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );
    MainFormLayout = new QVBoxLayout( centralWidget(), 11, 6, "MainFormLayout"); 

    listView = new QListView( centralWidget(), "listView" );
    listView->addColumn( tr( "Type" ) );
    listView->addColumn( tr( "Name" ) );
    listView->addColumn( tr( "Login" ) );
    listView->addColumn( tr( "Password" ) );
    listView->addColumn( tr( "Description" ) );
    listView->setResizeMode( QListView::AllColumns );
    listView->setSorting(-1);
    MainFormLayout->addWidget( listView );

    // actions
    createProfileAction = new QAction( this, "createProfileAction" );
    createProfileAction->setIconSet( QPixmap::fromMimeSource("new.png") );
    openProfileAction = new QAction(this, "openProfileAction" );
    openProfileAction->setIconSet( QPixmap::fromMimeSource("open.png") );
    tb_openProfileAction = new QAction(this, "tb_openProfileAction");
    tb_openProfileAction->setIconSet( QPixmap::fromMimeSource("tb_open.png") );
    closeProfileAction = new QAction( this, "closeProfileAction" );
    closeProfileAction->setIconSet( QPixmap::fromMimeSource("close.png") );
    tb_closeProfileAction = new QAction( this, "tb_closeProfileAction" );
    tb_closeProfileAction->setIconSet( QPixmap::fromMimeSource("tb_close.png") );
    deleteProfileAction = new QAction( this, "deleteProfileAction" );
    deleteProfileAction->setIconSet( QPixmap::fromMimeSource("delete_all.png") );
    changeProfileAction = new QAction( this, "changeProfileAction" );
    fileQuitAction = new QAction( this, "fileQuitAction" );
    fileSaveAction = new QAction( this, "fileSaveAction" );
    fileSaveAction->setIconSet( QPixmap::fromMimeSource("save.png") );
    tb_fileSaveAction = new QAction( this, "tb_fileSaveAction" );
    tb_fileSaveAction->setIconSet( QPixmap::fromMimeSource("tb_save.png") );
    editUndoAction = new QAction( this, "editUndoAction" );
    editUndoAction->setIconSet( QPixmap::fromMimeSource("undo.png") );
    tb_editUndoAction = new QAction( this, "editUndoAction" );
    tb_editUndoAction->setIconSet( QPixmap::fromMimeSource("tb_undo.png") );
    editRedoAction = new QAction( this, "editRedoAction" );
    editRedoAction->setIconSet( QPixmap::fromMimeSource("redo.png") );
    tb_editRedoAction = new QAction( this, "tb_editRedoAction" );
    tb_editRedoAction->setIconSet( QPixmap::fromMimeSource("tb_redo.png") );
    editNewField = new QAction( this, "editNewField" );
    editNewField->setIconSet( QPixmap::fromMimeSource("new.png") );
    editEditField = new QAction( this, "editEditField" );
    editEditField->setIconSet( QPixmap::fromMimeSource("edit.png") );
    tb_editEditField = new QAction( this, "tb_editEditField" );
    tb_editEditField->setIconSet( QPixmap::fromMimeSource("tb_edit.png") );
    tb_editNewField = new QAction( this, "tb_editNewField" );
    tb_editNewField->setIconSet( QPixmap::fromMimeSource("tb_new.png") );
    editDeleteField = new QAction( this, "editDeleteField" );
    editDeleteField->setIconSet( QPixmap::fromMimeSource("delete.png") );
    tb_editDeleteField = new QAction( this, "tb_editDeleteField" );
    tb_editDeleteField->setIconSet( QPixmap::fromMimeSource("tb_delete.png") );
    editDeleteAll = new QAction( this, "editDeleteAll" );
    editDeleteAll->setIconSet( QPixmap::fromMimeSource("delete_all.png") );
    helpAboutAction = new QAction( this, "helpAboutAction" );


    // toolbars
    fileToolbar = new QToolBar( tr("File"), this, DockTop );
    tb_openProfileAction->addTo( fileToolbar);
    tb_fileSaveAction->addTo( fileToolbar);
    tb_closeProfileAction->addTo( fileToolbar );
    
    editToolbar = new QToolBar( tr("Edit"), this, DockTop );
    tb_editUndoAction->addTo( editToolbar );
    tb_editRedoAction->addTo( editToolbar );
    editToolbar->addSeparator();
    tb_editNewField->addTo( editToolbar );
    tb_editEditField->addTo( editToolbar );
    tb_editDeleteField->addTo( editToolbar );

    // menubar
    MenuBarEditor = new QMenuBar( this, "MenuBarEditor" );


    File = new QPopupMenu( this );
    createProfileAction->addTo( File );
    openProfileAction->addTo( File );
    fileSaveAction->addTo( File );
    closeProfileAction->addTo( File );
    deleteProfileAction->addTo( File );
    changeProfileAction->addTo( File );
    File->insertSeparator();
    fileQuitAction->addTo( File );
    MenuBarEditor->insertItem( QString(""), File, 1 );
    
    Edit = new QPopupMenu( this );
    editUndoAction->addTo( Edit );
    editRedoAction->addTo( Edit );
    Edit->insertSeparator();
    editNewField->addTo( Edit );
    editEditField->addTo( Edit );
    editDeleteField->addTo( Edit );
    editDeleteAll->addTo(Edit);
    MenuBarEditor->insertItem( QString(""), Edit, 2 );
    
    Help = new QPopupMenu( this );
    helpAboutAction->addTo( Help );
    MenuBarEditor->insertItem( QString(""), Help, 3 );
    
    rmbMenu = new QPopupMenu( this );
    editUndoAction->addTo( rmbMenu );
    editRedoAction->addTo( rmbMenu );
    rmbMenu->insertSeparator();
    editNewField->addTo( rmbMenu );
    editEditField->addTo( rmbMenu );
    editDeleteField->addTo( rmbMenu );

    languageChange();
    resize( QSize(700, 400).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    
    connect(createProfileAction, SIGNAL( activated() ), this, SLOT( createProfile() )  );
    connect(openProfileAction, SIGNAL( activated() ), this, SLOT( openProfile() )  );
    connect(tb_openProfileAction, SIGNAL( activated() ), this, SLOT( openProfile() ) );
    connect(closeProfileAction, SIGNAL( activated() ), this, SLOT( closeProfile() )  );
    connect(tb_closeProfileAction, SIGNAL( activated() ), this, SLOT( closeProfile() )  );
    connect(deleteProfileAction, SIGNAL( activated() ), this, SLOT( deleteProfile() ) );
    connect(changeProfileAction, SIGNAL( activated() ), this, SLOT( changeProfile() ) );
    connect(fileSaveAction, SIGNAL( activated() ), this, SLOT( save() ) );
    connect(tb_fileSaveAction, SIGNAL( activated() ), this, SLOT( save() ) );
    connect(fileQuitAction, SIGNAL( activated() ), this, SLOT( close() ) );
    connect(editUndoAction, SIGNAL( activated() ), this, SLOT( undo() ) );
    connect(tb_editUndoAction, SIGNAL( activated() ), this, SLOT( undo() ) );
    connect(editRedoAction, SIGNAL( activated() ), this, SLOT( redo() ) );
    connect(tb_editRedoAction, SIGNAL( activated() ), this, SLOT( redo() ) );
    connect(editNewField, SIGNAL( activated() ), this, SLOT( newField() ) );
    connect(tb_editNewField, SIGNAL( activated() ), this, SLOT( newField() ) );
    connect(editEditField, SIGNAL(activated() ), this, SLOT( editField() ) );
    connect(tb_editEditField, SIGNAL(activated() ), this, SLOT( editField() ) );
    connect(editDeleteField, SIGNAL( activated() ), this, SLOT( deleteField() ) );
    connect(tb_editDeleteField, SIGNAL( activated() ), this, SLOT( deleteField() ) );
    connect(editDeleteAll, SIGNAL( activated() ), this, SLOT( deleteAll() ) );
    connect(helpAboutAction, SIGNAL( activated() ), this, SLOT( about() ) );
    
    connect(listView, SIGNAL( doubleClicked(QListViewItem *) ), this, SLOT( edit(QListViewItem *) ) );
    connect(listView, SIGNAL( contextMenuRequested( QListViewItem *, const QPoint&, int) ), this, SLOT( slotRMB( QListViewItem*, const QPoint &, int ) ) );
    
    modified = false;
    Caption();
    
    if(!ifProfileExists())
	    createProfile();
    else
	    setEnabledActions(1);
}

void MainForm::setEnabledActions(int level)
{
	//0 - profile doesn't exists
	//1 - profile exists, but closed
	//2 - profile exists and opened
	
	switch(level)
	{
		case 0 :
		{
			createProfileAction->setEnabled(true);
			openProfileAction->setEnabled(false);
			tb_openProfileAction->setEnabled(false);
			closeProfileAction->setEnabled(false);
			tb_closeProfileAction->setEnabled(false);
			deleteProfileAction->setEnabled(false);
			changeProfileAction->setEnabled(false);
			fileSaveAction->setEnabled(false);
			tb_fileSaveAction->setEnabled(false);
			editUndoAction->setEnabled(false);
			tb_editUndoAction->setEnabled(false);
			editRedoAction->setEnabled(false);
			tb_editRedoAction->setEnabled(false);
			editNewField->setEnabled(false);
			tb_editNewField->setEnabled(false);
			editEditField->setEnabled(false);
			tb_editEditField->setEnabled(false);
			editDeleteField->setEnabled(false);
			tb_editDeleteField->setEnabled(false);
			editDeleteAll->setEnabled(false);
			
			break;
		}
		case 1 :
		{
			createProfileAction->setEnabled(false);
			openProfileAction->setEnabled(true);
			tb_openProfileAction->setEnabled(true);
			closeProfileAction->setEnabled(false);
			tb_closeProfileAction->setEnabled(false);
			deleteProfileAction->setEnabled(true);
			changeProfileAction->setEnabled(false);
			fileSaveAction->setEnabled(false);
			tb_fileSaveAction->setEnabled(false);
			editUndoAction->setEnabled(false);
			tb_editUndoAction->setEnabled(false);
			editRedoAction->setEnabled(false);
			tb_editRedoAction->setEnabled(false);
			editNewField->setEnabled(false);
			tb_editNewField->setEnabled(false);
			editEditField->setEnabled(false);
			tb_editEditField->setEnabled(false);
			editDeleteField->setEnabled(false);
			tb_editDeleteField->setEnabled(false);
			editDeleteAll->setEnabled(false);
			
			break;
		}
		case 2 :
		{
			createProfileAction->setEnabled(false);
			openProfileAction->setEnabled(false);
			tb_openProfileAction->setEnabled(false);
			closeProfileAction->setEnabled(true);
			tb_closeProfileAction->setEnabled(true);
			deleteProfileAction->setEnabled(true);
			changeProfileAction->setEnabled(false);
			fileSaveAction->setEnabled(true);
			tb_fileSaveAction->setEnabled(true);
			editUndoAction->setEnabled(false);
			tb_editUndoAction->setEnabled(false);
			editRedoAction->setEnabled(false);
			tb_editRedoAction->setEnabled(false);
			editNewField->setEnabled(true);
			tb_editNewField->setEnabled(true);
			editEditField->setEnabled(true);
			tb_editEditField->setEnabled(true);
			editDeleteField->setEnabled(true);
			tb_editDeleteField->setEnabled(true);
			editDeleteAll->setEnabled(true);
			
			break;
		}
	}
}

bool MainForm::ifProfileExists()
{
	QString path = QDir::homeDirPath();
	path += "/.pkeeper";
	
	QDir dir(path);
	if(!dir.exists(path))
		return false;
	path += "/enter.dat";
	QFile file(path);
	if(!file.exists())
		return false;
	return true;
}

void MainForm::createProfile()
{
	CreateProfile *dlg = new CreateProfile();
	dlg->exec();
	
	if(dlg->result() == QDialog::Rejected)
	{
		setEnabledActions(0);
		statusBar()->message(tr("Cancelled"), 2000);
	}
	else
	{
		setEnabledActions(1);
		statusBar()->message(tr("Profile created"), 2000);
	}
}

void MainForm::openProfile()
{
	QString key;
	CheckPass *dlg = new CheckPass(key);
	dlg->exec();
	
	if(dlg->result() == QDialog::Rejected)
		statusBar()->message(tr("Cancelled"), 2000);
	else
	{
		gKey = key;
		open();
	}
}

void MainForm::closeProfile()
{
	if(modified){
		int res = QMessageBox::warning(this, tr("Password keeper"), tr("Your data have been changed!\nDo you want to save them, before closing profile?"),
				     QMessageBox::Yes | QMessageBox::Default,
				     QMessageBox::No,
				     QMessageBox::Cancel | QMessageBox::Escape);
		if(res == QMessageBox::Yes)
		{
			save();
			clear();
		}
		else if(res == QMessageBox::No)
			clear();
		modified = false;
		Caption();
		
	}
	else
		clear();
	setEnabledActions(1);
}

void MainForm::deleteProfile()
{
	int res = QMessageBox::warning(this, tr("Password keeper"), tr("Are you sure to delete ALL saved data?"),
				       QMessageBox::Yes,
				       QMessageBox::Cancel | QMessageBox::Escape);
	if(res == QMessageBox::Yes)
	{
		QString key;
		CheckPass *dlg = new CheckPass(key);
		dlg->exec();
		
		if(dlg->result() == QDialog::Rejected)
		{
			statusBar()->message(tr("Cancelled"), 2000);
			return;
		}
		
		listView->clear();
		QString path = QDir::homeDirPath();
		path += "/.pkeeper";
		QDir dir(path);
		if(!dir.exists())
		{
			QMessageBox::warning(this, tr("Password keeper"), tr("Probably, you profile has been deleted outside the program!") );
			return;
		}
		QString fpath = path + "/enter.dat";
		QFile file(fpath);
		if(file.exists()){
			bool ok = file.remove();
			if(!ok){
				QMessageBox::warning(this, tr("Password keeper"), tr("Can't delete file!\nProbably, you have troubles with file permissions."));
				return;
			}
		}
		fpath = path + "/data.dat";
		file.setName(fpath);
		if(file.exists()){
			bool ok = file.remove();
			if(!ok){
				QMessageBox::warning(this, tr("Password keeper"), tr("Can't delete file!\nProbably, you have troubles with file permissions."));
				return;
			}
		}
		bool ok = dir.rmdir(path);
		if(!ok){
			QMessageBox::warning(this, tr("Password keeper"), tr("Can't delete directory!\nProbably, you have troubles with file permissions."));
			return;
		}
		
		listView->clear();
		modified = false;
		Caption();
		setEnabledActions(0);
		statusBar()->message(tr("Profile has been deleted!"), 2000);
		QMessageBox::warning(this, tr("Password keeper"), tr("All your profile data have been deleted!") );
	}
}

void MainForm::changeProfile()
{
	QString key;
	CheckPass *cp_dlg = new CheckPass(key);
	cp_dlg->exec();
	if(cp_dlg->result() == QDialog::Rejected)
		return;
	
	QString pass;
	ChangeProfile *dlg = new ChangeProfile(pass);
	dlg->exec();
	
	if(dlg->result() == QDialog::Rejected)
	{
		statusBar()->message(tr("Cencelled"), 2000);
		return;
	}
	else
	{
		if(pass.isEmpty())
			return;
		
		bool ok;
		QString path = QDir::homeDirPath();
		path += "/.pkeeper";
		QDir dir(path);
		if(!dir.exists(path)){
			ok = dir.mkdir(path);
			if(ok == false){
				QMessageBox::warning(this, tr("Password keeper"), tr("Error! Can't create directory!\nProbably you have troubles with file permissions.") );
				return;
			}
		}
		
		QString fpath = path + "/enter.dat";
		QFile file(fpath);
		if(file.exists()){
			ok = file.remove();
			if(ok == false){
				QMessageBox::warning(this, tr("Password keeper"), tr("Error! Can't remove file!\nProbably you have troubles with file permissions.") );
				return;
			}
		}
		
		if(file.open(IO_WriteOnly)){
			QDataStream stream(&file);
			QString str = getHash(pass);
			stream << str;
			
			file.close();
			
			gKey = pass;
			save();
		}
		else
		{
			QMessageBox::warning(this, tr("Password keeper"), tr("Can't write to file.\nProbably, you have troubles with file permissions."));
			return;
		}
	}
}

QString MainForm::getHash(QString &inStr)
{
	char *hash = new char[32];
// 	char *str = new char[inStr.length()+1];
// 	str = (char*)inStr.data();
	char *str = strdup(inStr);
	
	MD5_string((unsigned char*)str, hash);
	
	QString ret = QString::fromAscii(hash, 32);
	
// 	printf("%s\n", hash);
// 	printf("%s\n", ret.latin1());
	
	delete [] hash;
	delete [] str;
	
	return ret;
}

void MainForm::clear()
{
	listView->clear();
}

void MainForm::Caption()
{
	if(modified)
		setCaption( tr("Password keeper - *") );
	else
		setCaption( tr("Password keeper") );
}

void MainForm::open()
{
	QString home = QDir::homeDirPath();
	QString path = home;
	path += "/.pkeeper";
	QString path_cph = path;
	
	QDir dir(path);
	if(!dir.exists(path))
	{
		QMessageBox::warning(this,tr("Password keeper"),tr("Error! You profile doesn't exists!") );
		return;
	}
	
	path_cph += "/data.dat";
	path += "/data2.dat";
	
	RC4 *rc4 = new RC4();
	rc4_key rc4key;
	char *key = strdup(gKey);
	char *fo = strdup(path_cph);
	char *fw = strdup(path);
	rc4->crypto_file(fo, fw, (unsigned char*)key, strlen(key), &rc4key);
	
	QFile file(path);
	if(!file.exists())
	{
		setEnabledActions(2);
		return;
	}
	
	
	if(file.open(IO_ReadOnly))
	{
		QTextStream stream(&file);
		listView->clear();
		
		
//  		rc4->prepare_key( (unsigned char*)key, strlen(key), &rc4key );
// 		rc4->prepare_key( (unsigned char*)gKey.data(), gKey.length(), &rc4key );
		
		QString str;
		str = stream.read();
		if(!str.isEmpty())
		{
			QStringList entList = QStringList::split("\t\t", str);
			for(int i = 0; i < (int)entList.count(); i++)
			{
				item = new QListViewItem(listView);
				QStringList list = QStringList::split("\t", entList[i]);
				for(int j = 0; j < (int)list.count(); j++)
					item->setText(j, list[j]);
				listView->insertItem(item);
			}
		}
		file.close();
		
		file.remove();

		if(listView->childCount() > 0)
			listView->setSelected(listView->firstChild(), true);
		
		fillListForUndo();
		fillSaveStruct(saveList);
		modified = false;
		Caption();
		setEnabledActions(2);
		statusBar()->message(tr("Opened"), 2000);
 		sortListView();
	}
	else{
		QMessageBox::warning(this, tr("Password keeper"), tr("Can't write to file.\nProbably, you have troubles with file permissions."));
	}
}

void MainForm::save()
{
	QApplication::setOverrideCursor(waitCursor);
	
	QString home = QDir::homeDirPath();
	QString path = home;
	QString path_cph;
	
	path += "/.pkeeper";
	path_cph = path;
	
	QDir dir(path);
	if(!dir.exists(path))
	{
		QMessageBox::warning(this,tr("Password keeper"),tr("Error! You profile doesn't exists!") );
		return;
	}
	
	path += "/data1.dat";
	path_cph += "/data.dat";
	QFile file(path);
	if(file.exists())
		file.remove();
		
	if(file.open(IO_WriteOnly)){
		QTextStream stream(&file);
		
		RC4 *rc4 = new RC4();
		rc4_key rc4key;
		char *key = strdup(gKey);
// 		rc4->prepare_key( (unsigned char*)key, strlen(key), &rc4key );
// 		rc4->prepare_key( (unsigned char*)gKey.data(), gKey.length(), &rc4key );
		
		QString str;
		item = listView->firstChild();
		while(item != NULL)
		{
			for(int i = 0; i < 5; i++)
			{
				str += item->text(i);
				str += "\t";
			}
			str += "\t";
			item = item->itemBelow();
		}
		stream << str;
		file.close();
				
		char *fo = strdup(path);
		char *fw = strdup(path_cph);
		rc4->crypto_file(fo, fw, (unsigned char*)key, strlen(key), &rc4key);
		file.remove();
		
		fillSaveStruct(saveList);
		modified = false;
		Caption();
		statusBar()->message(tr("Saved"), 2000);
		/*
		QString str;
		item = listView->lastItem();
		while(item != NULL){
			for(int i = 0; i < 5; i++){
				str = item->text(i);
 				str = str.local8Bit();
				char *s = new char[str.length()+1];
				qstrcpy(s, str);
				rc4->rc4( (unsigned char*)s, str.length(), &rc4key);
				str = s;
//  				str = qtCrypto(str);
				stream << (Q_UINT32)str.length() << str;
			}
			item = item->itemAbove();
		}*/	
	}
	else{
		QMessageBox::warning(this, tr("Password keeper"), tr("Can't write to file.\nProbably, you have troubles with file permissions."));
	}
	
	QApplication::restoreOverrideCursor();
}

void MainForm::sortListView()
{
	item = listView->firstChild();
	QStringList list, sort_list;
	QString str;
	while(item != NULL){
		str = item->text(0) += "\t";
		str += item->text(1) += "\t";
		str += item->text(2) += "\t";
		str += item->text(3) += "\t";
		str += item->text(4);
		list << str;
		item = item->itemBelow();
	}
		
	sort_list = list;
	sort_list.sort();
	
	listView->clear();
	for(int j = sort_list.count()-1; j >= 0; --j){
		str = sort_list[j];
		list = QStringList::split("\t", str);
		
		int i = 0;
		item = new QListViewItem(listView);
		for(QStringList::Iterator it = list.begin(); it != list.end(); ++it){
			item->setText(i, *it);
			i++;
		}
		listView->insertItem(item);
		
		QString pix = item->text(0).lower() + ".png";
		item->setPixmap(0, QPixmap::fromMimeSource(pix) );
	}
	if(listView->childCount() > 0)
		listView->setSelected( listView->firstChild(), TRUE );
}

void MainForm::newField()
{
	QStringList dataList;
	QString name = "New field";
	NewField *dlg = new NewField(name, dataList);
	dlg->exec();
	
	if(dlg->result() == QDialog::Rejected)
	{
		statusBar()->message(tr("Cancelled"), 2000);
		return;
	}
	
	item = new QListViewItem(listView);
	for(int i = 0; i < 5; i++)
		item->setText(i, dataList[i]);
	listView->insertItem( item );
	
 	sortListView();
	
	item = listView->lastItem();
	while(item != NULL){
		if(dataList[0] == item->text(0) && dataList[1] == item->text(1) && dataList[2] == item->text(2) && dataList[3] == item->text(3) && dataList[4] == item->text(4))
			listView->setSelected(item, TRUE);
		item = item->itemAbove();
	}
	
	editUndoAction->setEnabled(true);
	tb_editUndoAction->setEnabled(true);
	fillListForUndo();
	modified = true;
	Caption();
	statusBar()->message(tr("Added"), 2000);
}

void MainForm::editField()
{
	item = listView->selectedItem();
	edit(item);
}

void MainForm::edit(QListViewItem *item1)
{
	if(!item1)
		return;
	
	QStringList dataList;
	for(int i = 0; i < 5; i++)
		dataList << item1->text(i);
	
	QString name = "Edit field";
	NewField *dlg = new NewField(name, dataList);
	dlg->exec();
	
	if(dlg->result() == QDialog::Rejected)
	{
		statusBar()->message(tr("Cancelled"), 2000);
		return;
	}
	
	for(int i = 0; i < 5; i++)
		item1->setText(i, dataList[i]);
	
	sortListView();
	
	item = listView->lastItem();
	while(item != NULL){
		if(dataList[0] == item->text(0) && dataList[1] == item->text(1) && dataList[2] == item->text(2) && dataList[3] == item->text(3) && dataList[4] == item->text(4))
			listView->setSelected(item, TRUE);
		item = item->itemAbove();
	}
	
	editUndoAction->setEnabled(true);
	tb_editUndoAction->setEnabled(true);
	fillListForUndo();
	
	CurList unList;
	fillSaveStruct(unList);
	if(unList == saveList)
		modified = false;
	else
		modified = true;
	
	Caption();
	statusBar()->message(tr("Edited"), 2000);
}

void MainForm::deleteField()
{
	item = listView->selectedItem();
	if(item){
		if(item->itemAbove()){
 			listView->setSelected( item->itemAbove(), TRUE );
			listView->takeItem(item);
		}	
		else{
			listView->takeItem(item);
			listView->setSelected( listView->firstChild(), TRUE );
		}
		
		editUndoAction->setEnabled(true);
		tb_editUndoAction->setEnabled(true);
		fillListForUndo();
		modified = true;
		Caption();
		statusBar()->message(tr("Deleted"), 2000);
	}
}

void MainForm::deleteAll()
{
	int res = QMessageBox::warning(this, tr("Password keeper"), tr("Are you sure want to delete all fields from profile?"),
				       QMessageBox::Yes,
				       QMessageBox::Cancel | QMessageBox::Escape | QMessageBox::Default);
	if(res == QMessageBox::Yes){
		listView->clear();
		
		editUndoAction->setEnabled(true);
		tb_editUndoAction->setEnabled(true);
		fillListForUndo();
		modified = true;
		Caption();
		statusBar()->message(tr("Deleted"), 2000);
	}
}

void MainForm::closeEvent(QCloseEvent *event)
{
	if(modified){
		int res = QMessageBox::warning(this, tr("Password keeper"), tr("Your data have been changed!\nDo you want to save them, before exiting?"),
					       QMessageBox::Yes | QMessageBox::Default,
					       QMessageBox::No,
					       QMessageBox::Cancel | QMessageBox::Escape);
		if(res == QMessageBox::Yes){
			save();
			event->accept();
		}
		if(res == QMessageBox::No){
			event->accept();
		}
		if(res == QMessageBox::Cancel)
			event->ignore();
	}
	else
		event->accept();
}

void MainForm::fillListForUndo()
{	
	Item curItem;
	vector<Item> curList;
	CurList currentList;
	
	item = listView->lastItem();
	while(item != NULL)
	{
		curItem.type = item->text(0);
		curItem.name = item->text(1);
		curItem.login = item->text(2);
		curItem.pass = item->text(3);
		curItem.descr = item->text(4);
		
		curList.push_back(curItem);
		
		item = item->itemAbove();
	}
	currentList.list = curList;
	undoList.push_back(currentList);
	undoCount = undoList.size()-1;
}

void MainForm::fillSaveStruct(CurList &someList)
{
	Item curItem;
	vector<Item> curList;
	
	item = listView->lastItem();
	while(item != NULL)
	{
		curItem.type = item->text(0);
		curItem.name = item->text(1);
		curItem.login = item->text(2);
		curItem.pass = item->text(3);
		curItem.descr = item->text(4);
		
		curList.push_back(curItem);
		
		item = item->itemAbove();
	}
	someList.list = curList;
}

void MainForm::undo()
{
	if(undoList.size() == 0)
		return;
	
	if(undoCount == -1)
		undoCount = undoList.size() - 2;
	else
		undoCount--;
	
	if(undoCount <= 0)
	{
		undoCount = 0;
		editUndoAction->setEnabled(false);
		tb_editUndoAction->setEnabled(false);
	}
	editRedoAction->setEnabled(true);
	tb_editRedoAction->setEnabled(true);
	
	listView->clear();
	CurList currentList = undoList[undoCount];
	vector<Item> curList = currentList.list;
	for(int i = 0; i < (int)curList.size(); i++)
	{
		item = new QListViewItem(listView);
		
		item->setText(0, curList[i].type);
		item->setText(1, curList[i].name);
		item->setText(2, curList[i].login);
		item->setText(3, curList[i].pass);
		item->setText(4, curList[i].descr);
		
		QString pix = item->text(0).lower() + ".png";
		item->setPixmap(0, QPixmap::fromMimeSource(pix) );
		
		listView->insertItem(item);
	}
	sortListView();
	if(listView->childCount() > 0)
		listView->setSelected( listView->firstChild(), TRUE );
	
	CurList unList;
	fillSaveStruct(unList);
 	if(unList == saveList)
 		modified = false;
 	else
		modified = true;
	Caption();
}

void MainForm::redo()
{
	if(undoList.size() == 0)
		return;
	
	if(undoCount == -1)
		undoCount = undoList.size() - 1;
	else
		undoCount++;
	
	if(undoCount >= undoList.size()-1)
	{
		undoCount = undoList.size()-1;
		editRedoAction->setEnabled(false);
		tb_editRedoAction->setEnabled(false);
	}
	editUndoAction->setEnabled(true);
	tb_editUndoAction->setEnabled(true);
	
	
	listView->clear();
	CurList currentList = undoList[undoCount];
	vector<Item> curList = currentList.list;
	for(int i = 0; i < (int)curList.size(); i++)
	{
		item = new QListViewItem(listView);
		
		item->setText(0, curList[i].type);
		item->setText(1, curList[i].name);
		item->setText(2, curList[i].login);
		item->setText(3, curList[i].pass);
		item->setText(4, curList[i].descr);
		
		QString pix = item->text(0).lower() + ".png";
		item->setPixmap(0, QPixmap::fromMimeSource(pix) );
		
		listView->insertItem(item);
	}
	sortListView();
	if(listView->childCount() > 0)
		listView->setSelected( listView->firstChild(), TRUE );
	
	CurList unList;
	fillSaveStruct(unList);
	if(unList == saveList)
		modified = false;
	else
		modified = true;
	Caption();
}

void MainForm::slotRMB( QListViewItem *Item, const QPoint &point, int )
{
	if(Item)
		rmbMenu->popup(point);
}

void MainForm::about()
{
	QMessageBox::about(this, tr("Password keeper"), tr("<h2>Password keeper</h2><br>This is a free, small program to save your passwords for mail, forums, etc.<br><a href=mailto:piton3000@rambler.ru>piton3000@rambler.ru</a><br>Copyright &copy; piton, MIPT, 2005") );
}

MainForm::~MainForm()
{

}


void MainForm::languageChange()
{
    setCaption( tr( "Password keeper" ) );
    listView->header()->setLabel( 0, tr( "Type" ) );
    listView->header()->setLabel( 1, tr( "Name" ) );
    listView->header()->setLabel( 2, tr( "Login" ) );
    listView->header()->setLabel( 3, tr( "Password" ) );
    listView->header()->setLabel( 4, tr( "Description" ) );
    openProfileAction->setText( tr("Open profile...") );
    openProfileAction->setMenuText( tr("&Open profile...") );
    openProfileAction->setAccel( tr("Ctrl+O") );
    tb_openProfileAction->setText( tr("Open profile...") );
    tb_openProfileAction->setMenuText( tr("&Open profile...") );
    tb_openProfileAction->setAccel( tr("Ctrl+O") );
    closeProfileAction->setText( tr("Close profile") );
    closeProfileAction->setMenuText( tr("&Close profile") );
    closeProfileAction->setAccel( tr("Ctrl+W") );
    tb_closeProfileAction->setText( tr("Close profile") );
    tb_closeProfileAction->setMenuText( tr("&Close profile") );
    tb_closeProfileAction->setAccel( tr("Ctrl+W") );
    createProfileAction->setText( tr("Create profile...") );
    createProfileAction->setMenuText( tr("Create profile...") );
    deleteProfileAction->setText( tr("Profile") );
    deleteProfileAction->setMenuText( tr("&Delete profile") );
    changeProfileAction->setText( tr("Change profile...") );
    changeProfileAction->setMenuText( tr("C&hange profile...") );
    fileSaveAction->setText( tr("Save") );
    fileSaveAction->setMenuText( tr("&Save") );
    fileSaveAction->setAccel( tr("Ctrl+S") );
    tb_fileSaveAction->setText( tr("Save") );
    tb_fileSaveAction->setMenuText( tr("&Save") );
    tb_fileSaveAction->setAccel( tr("Ctrl+S") );
    fileQuitAction->setText( tr( "Quit" ) );
    fileQuitAction->setMenuText( tr( "&Quit" ) );
    fileQuitAction->setAccel( tr( "Ctrl+Q" ) );
    editUndoAction->setText( tr("Undo") );
    editUndoAction->setMenuText( tr("&Undo") );
    editUndoAction->setAccel( tr("Ctrl+Z") );
    tb_editUndoAction->setText( tr("Undo") );
    tb_editUndoAction->setMenuText( tr("&Undo") );
    tb_editUndoAction->setAccel( tr("Ctrl+Z") );
    editRedoAction->setText( tr("Redo") );
    editRedoAction->setMenuText( tr("&Redo") );
    editRedoAction->setAccel( tr("Ctrl+Shift+Z") );
    tb_editRedoAction->setText( tr("Redo") );
    tb_editRedoAction->setMenuText( tr("&Redo") );
    tb_editRedoAction->setAccel( tr("Ctrl+Shift+Z") );
    editNewField->setText( tr("New field...") );
    editNewField->setMenuText( tr("&New field...") );
    editNewField->setAccel( tr("Ctrl+N") );
    tb_editNewField->setText( tr("New field...") );
    tb_editNewField->setMenuText( tr("&New field...") );
    tb_editNewField->setAccel( tr("Ctrl+N") );
    editEditField->setText( tr("Edit field...") );
    editEditField->setMenuText( tr("&Edit field...") );
    editEditField->setAccel( tr("Ctrl+E") );
    tb_editEditField->setText( tr("Edit field...") );
    tb_editEditField->setMenuText( tr("&Edit field...") );
    tb_editEditField->setAccel( tr("Ctrl+E") );
    editDeleteField->setText( tr("Delete field") );
    editDeleteField->setMenuText( tr("&Delete field") );
    editDeleteField->setAccel( tr("Del") );
    tb_editDeleteField->setText( tr("Delete field") );
    tb_editDeleteField->setMenuText( tr("&Delete field") );
    tb_editDeleteField->setAccel( tr("Del") );
    editDeleteAll->setText( tr("Delete all") );
    editDeleteAll->setMenuText( tr("Delete &all") );
    helpAboutAction->setText( tr("About") );
    helpAboutAction->setMenuText( tr("&About") );
    if (MenuBarEditor->findItem(1))
        MenuBarEditor->findItem(1)->setText( tr( "&File" ) );
    if (MenuBarEditor->findItem(2))
	    MenuBarEditor->findItem(2)->setText( tr( "&Edit" ) );
    if (MenuBarEditor->findItem(3))
	    MenuBarEditor->findItem(3)->setText( tr( "&Help" ) );
}

bool CurList::operator== (CurList& X)
{
	bool ret = true;
	if(this->list.size() != X.list.size())
		  ret = false;
	
	int l = this->list.size();
	for(int i = 0; i < (int)l; i++)
	{
		if(this->list[i].type != X.list[l-i-1].type)
			ret = false;
		if(this->list[i].name != X.list[l-i-1].name)
			ret = false;
		if(this->list[i].login != X.list[l-i-1].login)
			ret = false;
		if(this->list[i].pass != X.list[l-i-1].pass)
			ret = false;
		if(this->list[i].descr != X.list[l-i-1].descr)
			ret = false;
	}
	
	return ret;
}
