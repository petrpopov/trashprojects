/****************************************************************************
** Spreadsheet meta object code from reading C++ file 'spreadsheet.h'
**
** Created: Thu Dec 8 18:56:00 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "spreadsheet.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Spreadsheet::className() const
{
    return "Spreadsheet";
}

QMetaObject *Spreadsheet::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Spreadsheet( "Spreadsheet", &Spreadsheet::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Spreadsheet::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Spreadsheet", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Spreadsheet::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Spreadsheet", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Spreadsheet::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QTable::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Spreadsheet", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Spreadsheet.setMetaObject( metaObj );
    return metaObj;
}

void* Spreadsheet::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Spreadsheet" ) )
	return this;
    return QTable::qt_cast( clname );
}

bool Spreadsheet::qt_invoke( int _id, QUObject* _o )
{
    return QTable::qt_invoke(_id,_o);
}

bool Spreadsheet::qt_emit( int _id, QUObject* _o )
{
    return QTable::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Spreadsheet::qt_property( int id, int f, QVariant* v)
{
    return QTable::qt_property( id, f, v);
}

bool Spreadsheet::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
