/****************************************************************************
** MainForm meta object code from reading C++ file 'mainform.h'
**
** Created: Wed Feb 7 17:45:44 2007
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mainform.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
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
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"createButtons", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "name", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"createCanvas", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "pe", &static_QUType_ptr, "QMouseEvent", QUParameter::In }
    };
    static const QUMethod slot_2 = {"mousePressEvent", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "pe", &static_QUType_ptr, "QMouseEvent", QUParameter::In }
    };
    static const QUMethod slot_3 = {"mouseMoveEvent", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "pe", &static_QUType_ptr, "QMouseEvent", QUParameter::In }
    };
    static const QUMethod slot_4 = {"mouseReleaseEvent", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_QString, 0, QUParameter::Out },
	{ "x", &static_QUType_int, 0, QUParameter::In },
	{ "y", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"whichButton", 3, param_slot_5 };
    static const QUMethod slot_6 = {"setFrameZeroButtons", 0, 0 };
    static const QUMethod slot_7 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "createButtons()", &slot_0, QMetaData::Public },
	{ "createCanvas(QString)", &slot_1, QMetaData::Public },
	{ "mousePressEvent(QMouseEvent*)", &slot_2, QMetaData::Private },
	{ "mouseMoveEvent(QMouseEvent*)", &slot_3, QMetaData::Private },
	{ "mouseReleaseEvent(QMouseEvent*)", &slot_4, QMetaData::Private },
	{ "whichButton(int,int)", &slot_5, QMetaData::Private },
	{ "setFrameZeroButtons()", &slot_6, QMetaData::Private },
	{ "languageChange()", &slot_7, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainForm", parentObject,
	slot_tbl, 8,
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
    return QWidget::qt_cast( clname );
}

bool MainForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: createButtons(); break;
    case 1: createCanvas((QString)static_QUType_QString.get(_o+1)); break;
    case 2: mousePressEvent((QMouseEvent*)static_QUType_ptr.get(_o+1)); break;
    case 3: mouseMoveEvent((QMouseEvent*)static_QUType_ptr.get(_o+1)); break;
    case 4: mouseReleaseEvent((QMouseEvent*)static_QUType_ptr.get(_o+1)); break;
    case 5: static_QUType_QString.set(_o,whichButton((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2))); break;
    case 6: setFrameZeroButtons(); break;
    case 7: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainForm::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainForm::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool MainForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
