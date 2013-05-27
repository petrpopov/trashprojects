/****************************************************************************
** MainForm meta object code from reading C++ file 'mainform.h'
**
** Created: Mon Dec 12 21:15:30 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mainform.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainForm::className() const
{
    return "MainForm";
}

QMetaObject *MainForm::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainForm( "MainForm", &MainForm::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainForm::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainForm", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainForm::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainForm", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainForm::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"languageChange", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "item1", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_1 = {"percentCalc", 1, param_slot_1 };
    static const QUMethod slot_2 = {"calculate", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "stable", &static_QUType_ptr, "QTable", QUParameter::In },
	{ "col", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"lastRow", 3, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "arr", &static_QUType_varptr, "\x10", QUParameter::In },
	{ "len", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"max", 3, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::Out },
	{ 0, &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_5 = {"forDate", 2, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::Out },
	{ 0, &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_6 = {"delZero", 2, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::Out },
	{ 0, &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_7 = {"addSpaces", 2, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_8 = {"recSum", 1, param_slot_8 };
    static const QUMethod slot_9 = {"loadFromDate", 0, 0 };
    static const QUMethod slot_10 = {"addCell", 0, 0 };
    static const QUParameter param_slot_11[] = {
	{ 0, &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_11 = {"loadData", 1, param_slot_11 };
    static const QUMethod slot_12 = {"Caption", 0, 0 };
    static const QUMethod slot_13 = {"clear", 0, 0 };
    static const QUMethod slot_14 = {"newFile", 0, 0 };
    static const QUMethod slot_15 = {"closeFile", 0, 0 };
    static const QUParameter param_slot_16[] = {
	{ "fileName", &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_16 = {"writeFile", 1, param_slot_16 };
    static const QUParameter param_slot_17[] = {
	{ "fileName", &static_QUType_QString, 0, QUParameter::InOut }
    };
    static const QUMethod slot_17 = {"readFile", 1, param_slot_17 };
    static const QUMethod slot_18 = {"open", 0, 0 };
    static const QUMethod slot_19 = {"save", 0, 0 };
    static const QUMethod slot_20 = {"saveAs", 0, 0 };
    static const QUMethod slot_21 = {"copy", 0, 0 };
    static const QUMethod slot_22 = {"cut", 0, 0 };
    static const QUMethod slot_23 = {"del", 0, 0 };
    static const QUMethod slot_24 = {"paste", 0, 0 };
    static const QUMethod slot_25 = {"markDone", 0, 0 };
    static const QUMethod slot_26 = {"markNotDone", 0, 0 };
    static const QUMethod slot_27 = {"markNowDone", 0, 0 };
    static const QUMethod slot_28 = {"markClear", 0, 0 };
    static const QUMethod slot_29 = {"print", 0, 0 };
    static const QUParameter param_slot_30[] = {
	{ 0, &static_QUType_ptr, "QPainter", QUParameter::In },
	{ 0, &static_QUType_ptr, "QSimpleRichText", QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_30 = {"printPage", 4, param_slot_30 };
    static const QUParameter param_slot_31[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In },
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_31 = {"redefine", 2, param_slot_31 };
    static const QUMethod slot_32 = {"red_kurs", 0, 0 };
    static const QUMethod slot_33 = {"red_kross_kurs", 0, 0 };
    static const QUMethod slot_34 = {"red_konv", 0, 0 };
    static const QUMethod slot_35 = {"red_pv", 0, 0 };
    static const QUMethod slot_36 = {"red_sp", 0, 0 };
    static const QUMethod slot_37 = {"red_pr", 0, 0 };
    static const QUMethod slot_38 = {"red_ob", 0, 0 };
    static const QUMethod slot_39 = {"red_dkonv", 0, 0 };
    static const QUMethod slot_40 = {"red_percent", 0, 0 };
    static const QUMethod slot_41 = {"about", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "languageChange()", &slot_0, QMetaData::Protected },
	{ "percentCalc(QListViewItem*)", &slot_1, QMetaData::Private },
	{ "calculate()", &slot_2, QMetaData::Private },
	{ "lastRow(QTable*,int)", &slot_3, QMetaData::Private },
	{ "max(int*,int)", &slot_4, QMetaData::Private },
	{ "forDate(QString&)", &slot_5, QMetaData::Private },
	{ "delZero(QString&)", &slot_6, QMetaData::Private },
	{ "addSpaces(QString&)", &slot_7, QMetaData::Private },
	{ "recSum(QString&)", &slot_8, QMetaData::Private },
	{ "loadFromDate()", &slot_9, QMetaData::Private },
	{ "addCell()", &slot_10, QMetaData::Private },
	{ "loadData(QListViewItem*)", &slot_11, QMetaData::Private },
	{ "Caption()", &slot_12, QMetaData::Private },
	{ "clear()", &slot_13, QMetaData::Private },
	{ "newFile()", &slot_14, QMetaData::Private },
	{ "closeFile()", &slot_15, QMetaData::Private },
	{ "writeFile(QString&)", &slot_16, QMetaData::Private },
	{ "readFile(QString&)", &slot_17, QMetaData::Private },
	{ "open()", &slot_18, QMetaData::Private },
	{ "save()", &slot_19, QMetaData::Private },
	{ "saveAs()", &slot_20, QMetaData::Private },
	{ "copy()", &slot_21, QMetaData::Private },
	{ "cut()", &slot_22, QMetaData::Private },
	{ "del()", &slot_23, QMetaData::Private },
	{ "paste()", &slot_24, QMetaData::Private },
	{ "markDone()", &slot_25, QMetaData::Private },
	{ "markNotDone()", &slot_26, QMetaData::Private },
	{ "markNowDone()", &slot_27, QMetaData::Private },
	{ "markClear()", &slot_28, QMetaData::Private },
	{ "print()", &slot_29, QMetaData::Private },
	{ "printPage(QPainter*,const QSimpleRichText&,int,int)", &slot_30, QMetaData::Private },
	{ "redefine(int,int)", &slot_31, QMetaData::Private },
	{ "red_kurs()", &slot_32, QMetaData::Private },
	{ "red_kross_kurs()", &slot_33, QMetaData::Private },
	{ "red_konv()", &slot_34, QMetaData::Private },
	{ "red_pv()", &slot_35, QMetaData::Private },
	{ "red_sp()", &slot_36, QMetaData::Private },
	{ "red_pr()", &slot_37, QMetaData::Private },
	{ "red_ob()", &slot_38, QMetaData::Private },
	{ "red_dkonv()", &slot_39, QMetaData::Private },
	{ "red_percent()", &slot_40, QMetaData::Private },
	{ "about()", &slot_41, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainForm", parentObject,
	slot_tbl, 42,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainForm.setMetaObject( metaObj );
    return metaObj;
}

void* MainForm::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainForm" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool MainForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: languageChange(); break;
    case 1: percentCalc((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 2: calculate(); break;
    case 3: static_QUType_int.set(_o,lastRow((QTable*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2))); break;
    case 4: static_QUType_int.set(_o,max((int*)static_QUType_varptr.get(_o+1),(int)static_QUType_int.get(_o+2))); break;
    case 5: static_QUType_QString.set(_o,forDate((QString&)static_QUType_QString.get(_o+1))); break;
    case 6: static_QUType_QString.set(_o,delZero((QString&)static_QUType_QString.get(_o+1))); break;
    case 7: static_QUType_QString.set(_o,addSpaces((QString&)static_QUType_QString.get(_o+1))); break;
    case 8: recSum((QString&)static_QUType_QString.get(_o+1)); break;
    case 9: loadFromDate(); break;
    case 10: addCell(); break;
    case 11: loadData((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 12: Caption(); break;
    case 13: clear(); break;
    case 14: newFile(); break;
    case 15: closeFile(); break;
    case 16: writeFile((QString&)static_QUType_QString.get(_o+1)); break;
    case 17: readFile((QString&)static_QUType_QString.get(_o+1)); break;
    case 18: open(); break;
    case 19: save(); break;
    case 20: saveAs(); break;
    case 21: copy(); break;
    case 22: cut(); break;
    case 23: del(); break;
    case 24: paste(); break;
    case 25: markDone(); break;
    case 26: markNotDone(); break;
    case 27: markNowDone(); break;
    case 28: markClear(); break;
    case 29: print(); break;
    case 30: printPage((QPainter*)static_QUType_ptr.get(_o+1),(const QSimpleRichText&)*((const QSimpleRichText*)static_QUType_ptr.get(_o+2)),(int)static_QUType_int.get(_o+3),(int)static_QUType_int.get(_o+4)); break;
    case 31: redefine((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 32: red_kurs(); break;
    case 33: red_kross_kurs(); break;
    case 34: red_konv(); break;
    case 35: red_pv(); break;
    case 36: red_sp(); break;
    case 37: red_pr(); break;
    case 38: red_ob(); break;
    case 39: red_dkonv(); break;
    case 40: red_percent(); break;
    case 41: about(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainForm::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainForm::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool MainForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
