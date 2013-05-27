/****************************************************************************
** ItDialog meta object code from reading C++ file 'itdialog.h'
**
** Created: ?? 21. ??? 21:12:29 2005
**      by: The Qt MOC ($Id: $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "itdialog.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ItDialog::className() const
{
    return "ItDialog";
}

QMetaObject *ItDialog::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ItDialog( "ItDialog", &ItDialog::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ItDialog::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ItDialog", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ItDialog::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ItDialog", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ItDialog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"languageChange", 0, 0 };
    static const QUMethod slot_1 = {"ok", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "languageChange()", &slot_0, QMetaData::Protected },
	{ "ok()", &slot_1, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"ItDialog", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ItDialog.setMetaObject( metaObj );
    return metaObj;
}

void* ItDialog::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ItDialog" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool ItDialog::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: languageChange(); break;
    case 1: ok(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ItDialog::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool ItDialog::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool ItDialog::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
