/****************************************************************************
** Meta object code from reading C++ file 'mpsd8.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mpsd8.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mpsd8.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MPSD8_t {
    QByteArrayData data[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MPSD8_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MPSD8_t qt_meta_stringdata_MPSD8 = {
    {
QT_MOC_LITERAL(0, 0, 5), // "MPSD8"
QT_MOC_LITERAL(1, 6, 8) // "m_busNum"

    },
    "MPSD8\0m_busNum"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPSD8[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::UChar, 0x00095001,

       0        // eod
};

void MPSD8::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MPSD8 *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< quint8*>(_v) = _t->busNumber(); break;
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

QT_INIT_METAOBJECT const QMetaObject MPSD8::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MPSD8.data,
    qt_meta_data_MPSD8,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MPSD8::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPSD8::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPSD8.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MPSD8::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_NoModule_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoModule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoModule_t qt_meta_stringdata_NoModule = {
    {
QT_MOC_LITERAL(0, 0, 8) // "NoModule"

    },
    "NoModule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoModule[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void NoModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject NoModule::staticMetaObject = { {
    &MPSD8::staticMetaObject,
    qt_meta_stringdata_NoModule.data,
    qt_meta_data_NoModule,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NoModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NoModule.stringdata0))
        return static_cast<void*>(this);
    return MPSD8::qt_metacast(_clname);
}

int NoModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MPSD8::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_MPSD8old_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MPSD8old_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MPSD8old_t qt_meta_stringdata_MPSD8old = {
    {
QT_MOC_LITERAL(0, 0, 8) // "MPSD8old"

    },
    "MPSD8old"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPSD8old[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void MPSD8old::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MPSD8old::staticMetaObject = { {
    &MPSD8::staticMetaObject,
    qt_meta_stringdata_MPSD8old.data,
    qt_meta_data_MPSD8old,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MPSD8old::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPSD8old::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPSD8old.stringdata0))
        return static_cast<void*>(this);
    return MPSD8::qt_metacast(_clname);
}

int MPSD8old::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MPSD8::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_MPSD8plus_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MPSD8plus_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MPSD8plus_t qt_meta_stringdata_MPSD8plus = {
    {
QT_MOC_LITERAL(0, 0, 9) // "MPSD8plus"

    },
    "MPSD8plus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPSD8plus[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void MPSD8plus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MPSD8plus::staticMetaObject = { {
    &MPSD8::staticMetaObject,
    qt_meta_stringdata_MPSD8plus.data,
    qt_meta_data_MPSD8plus,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MPSD8plus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPSD8plus::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPSD8plus.stringdata0))
        return static_cast<void*>(this);
    return MPSD8::qt_metacast(_clname);
}

int MPSD8plus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MPSD8::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_MPSD8SingleADC_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MPSD8SingleADC_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MPSD8SingleADC_t qt_meta_stringdata_MPSD8SingleADC = {
    {
QT_MOC_LITERAL(0, 0, 14) // "MPSD8SingleADC"

    },
    "MPSD8SingleADC"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPSD8SingleADC[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void MPSD8SingleADC::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MPSD8SingleADC::staticMetaObject = { {
    &MPSD8::staticMetaObject,
    qt_meta_stringdata_MPSD8SingleADC.data,
    qt_meta_data_MPSD8SingleADC,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MPSD8SingleADC::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPSD8SingleADC::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPSD8SingleADC.stringdata0))
        return static_cast<void*>(this);
    return MPSD8::qt_metacast(_clname);
}

int MPSD8SingleADC::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MPSD8::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
