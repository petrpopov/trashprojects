/****************************************************************************
** DateInterval meta object code from reading C++ file 'dateinterval.h'
**
** Created: Thu Dec 8 18:56:02 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "dateinterval.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *DateInterval::className() const
{
    return "DateInterval";
}

QMetaObject *DateInterval::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DateInterval( "DateInterval", &DateInterval::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString DateInterval::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DateInterval", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DateInterval::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DateInterval", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DateInterval::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"languageChange", 0, 0 };
    static const QUMethod slot_1 = {"enableDate", 0, 0 };
    static const QUMethod slot_2 = {"enableOk", 0, 0 };
    static const QUMethod slot_3 = {"ok", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "languageChange()", &slot_0, QMetaData::Protected },
	{ "enableDate()", &slot_1, QMetaData::Private },
	{ "enableOk()", &slot_2, QMetaData::Private },
	{ "ok()", &slot_3, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"DateInterval", parentObject,
	slot_tbl, 4,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DateInterval.setMetaObject( metaObj );
    return metaObj;
}

void* DateInterval::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DateInterval" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool DateInterval::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: languageChange(); break;
    case 1: enableDate(); break;
    case 2: enableOk(); break;
    case 3: ok(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DateInterval::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool DateInterval::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool DateInterval::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
