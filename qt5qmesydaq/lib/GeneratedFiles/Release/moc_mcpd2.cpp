/****************************************************************************
** Meta object code from reading C++ file 'mcpd2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mcpd2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcpd2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MCPD2_t {
    QByteArrayData data[10];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MCPD2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MCPD2_t qt_meta_stringdata_MCPD2 = {
    {
QT_MOC_LITERAL(0, 0, 5), // "MCPD2"
QT_MOC_LITERAL(1, 6, 10), // "startedDaq"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 10), // "stoppedDaq"
QT_MOC_LITERAL(4, 29, 12), // "continuedDaq"
QT_MOC_LITERAL(5, 42, 17), // "analyzeDataBuffer"
QT_MOC_LITERAL(6, 60, 29), // "QSharedDataPointer<SD_PACKET>"
QT_MOC_LITERAL(7, 90, 2), // "pd"
QT_MOC_LITERAL(8, 93, 13), // "analyzeBuffer"
QT_MOC_LITERAL(9, 107, 7) // "pPacket"

    },
    "MCPD2\0startedDaq\0\0stoppedDaq\0continuedDaq\0"
    "analyzeDataBuffer\0QSharedDataPointer<SD_PACKET>\0"
    "pd\0analyzeBuffer\0pPacket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MCPD2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 6,    9,

       0        // eod
};

void MCPD2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MCPD2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startedDaq(); break;
        case 1: _t->stoppedDaq(); break;
        case 2: _t->continuedDaq(); break;
        case 3: _t->analyzeDataBuffer((*reinterpret_cast< QSharedDataPointer<SD_PACKET>(*)>(_a[1]))); break;
        case 4: { bool _r = _t->analyzeBuffer((*reinterpret_cast< QSharedDataPointer<SD_PACKET>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MCPD2::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCPD2::startedDaq)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MCPD2::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCPD2::stoppedDaq)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MCPD2::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCPD2::continuedDaq)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MCPD2::*)(QSharedDataPointer<SD_PACKET> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MCPD2::analyzeDataBuffer)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MCPD2::staticMetaObject = { {
    &MCPD::staticMetaObject,
    qt_meta_stringdata_MCPD2.data,
    qt_meta_data_MCPD2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MCPD2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MCPD2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MCPD2.stringdata0))
        return static_cast<void*>(this);
    return MCPD::qt_metacast(_clname);
}

int MCPD2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MCPD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MCPD2::startedDaq()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MCPD2::stoppedDaq()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MCPD2::continuedDaq()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MCPD2::analyzeDataBuffer(QSharedDataPointer<SD_PACKET> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
