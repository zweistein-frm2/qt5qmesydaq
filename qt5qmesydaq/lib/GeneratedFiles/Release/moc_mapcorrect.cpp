/****************************************************************************
** Meta object code from reading C++ file 'mapcorrect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mapcorrect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapcorrect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapCorrection_t {
    QByteArrayData data[11];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapCorrection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapCorrection_t qt_meta_stringdata_MapCorrection = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MapCorrection"
QT_MOC_LITERAL(1, 14, 12), // "m_bNoMapping"
QT_MOC_LITERAL(2, 27, 11), // "Orientation"
QT_MOC_LITERAL(3, 39, 13), // "OrientationUp"
QT_MOC_LITERAL(4, 53, 15), // "OrientationDown"
QT_MOC_LITERAL(5, 69, 15), // "OrientationLeft"
QT_MOC_LITERAL(6, 85, 16), // "OrientationRight"
QT_MOC_LITERAL(7, 102, 16), // "OrientationUpRev"
QT_MOC_LITERAL(8, 119, 18), // "OrientationDownRev"
QT_MOC_LITERAL(9, 138, 18), // "OrientationLeftRev"
QT_MOC_LITERAL(10, 157, 19) // "OrientationRightRev"

    },
    "MapCorrection\0m_bNoMapping\0Orientation\0"
    "OrientationUp\0OrientationDown\0"
    "OrientationLeft\0OrientationRight\0"
    "OrientationUpRev\0OrientationDownRev\0"
    "OrientationLeftRev\0OrientationRightRev"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapCorrection[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       1,   17, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Bool, 0x00095001,

 // enums: name, alias, flags, count, data
       2,    2, 0x0,    8,   22,

 // enum data: key, value
       3, uint(MapCorrection::OrientationUp),
       4, uint(MapCorrection::OrientationDown),
       5, uint(MapCorrection::OrientationLeft),
       6, uint(MapCorrection::OrientationRight),
       7, uint(MapCorrection::OrientationUpRev),
       8, uint(MapCorrection::OrientationDownRev),
       9, uint(MapCorrection::OrientationLeftRev),
      10, uint(MapCorrection::OrientationRightRev),

       0        // eod
};

void MapCorrection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MapCorrection *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isNoMap(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MapCorrection::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MapCorrection.data,
    qt_meta_data_MapCorrection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MapCorrection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapCorrection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapCorrection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MapCorrection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
