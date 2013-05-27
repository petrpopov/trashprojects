/****************************************************************************
** DateDialog meta object code from reading C++ file 'datedialog.h'
**
** Created: Thu Dec 8 18:55:58 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "datedialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *DateDialog::className() const
{
    return "DateDialog";
}

QMetaObject *DateDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_DateDialog( "DateDialog", &DateDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString DateDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DateDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString DateDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "DateDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* DateDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"languageChange", 0, 0 };
    static const QUMethod slot_1 = {"ok", 0, 0 };
    static const QUMethod slot_2 = {"cancel", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "languageChange()", &slot_0, QMetaData::Protected },
	{ "ok()", &slot_1, QMetaData::Private },
	{ "cancel()", &slot_2, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"DateDialog", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_DateDialog.setMetaObject( metaObj );
    return metaObj;
}

void* DateDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "DateDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool DateDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: languageChange(); break;
    case 1: ok(); break;
    case 2: cancel(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool DateDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool DateDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool DateDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
