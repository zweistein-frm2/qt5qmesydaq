/****************************************************************************
** Meta object code from reading C++ file 'measurement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../measurement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'measurement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Measurement_t {
    QByteArrayData data[54];
    char stringdata0[684];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Measurement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Measurement_t qt_meta_stringdata_Measurement = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Measurement"
QT_MOC_LITERAL(1, 12, 10), // "stopSignal"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "acqListfile"
QT_MOC_LITERAL(4, 36, 17), // "autoSaveHistogram"
QT_MOC_LITERAL(5, 54, 14), // "mappingChanged"
QT_MOC_LITERAL(6, 69, 13), // "analyzeBuffer"
QT_MOC_LITERAL(7, 83, 29), // "QSharedDataPointer<SD_PACKET>"
QT_MOC_LITERAL(8, 113, 7), // "pPacket"
QT_MOC_LITERAL(9, 121, 9), // "calcRates"
QT_MOC_LITERAL(10, 131, 13), // "setHeadertime"
QT_MOC_LITERAL(11, 145, 2), // "ht"
QT_MOC_LITERAL(12, 148, 17), // "setMonitorMapping"
QT_MOC_LITERAL(13, 166, 2), // "id"
QT_MOC_LITERAL(14, 169, 5), // "input"
QT_MOC_LITERAL(15, 175, 7), // "channel"
QT_MOC_LITERAL(16, 183, 11), // "requestStop"
QT_MOC_LITERAL(17, 195, 6), // "m_mode"
QT_MOC_LITERAL(18, 202, 4), // "Mode"
QT_MOC_LITERAL(19, 207, 8), // "m_status"
QT_MOC_LITERAL(20, 216, 6), // "Status"
QT_MOC_LITERAL(21, 223, 14), // "m_histfilename"
QT_MOC_LITERAL(22, 238, 10), // "m_histPath"
QT_MOC_LITERAL(23, 249, 21), // "m_calibrationfilename"
QT_MOC_LITERAL(24, 271, 10), // "m_listPath"
QT_MOC_LITERAL(25, 282, 12), // "m_configPath"
QT_MOC_LITERAL(26, 295, 12), // "m_configfile"
QT_MOC_LITERAL(27, 308, 8), // "m_height"
QT_MOC_LITERAL(28, 317, 7), // "m_width"
QT_MOC_LITERAL(29, 325, 15), // "DataAcquisition"
QT_MOC_LITERAL(30, 341, 14), // "ReplayListFile"
QT_MOC_LITERAL(31, 356, 13), // "HistogramLoad"
QT_MOC_LITERAL(32, 370, 13), // "HistogramType"
QT_MOC_LITERAL(33, 384, 17), // "PositionHistogram"
QT_MOC_LITERAL(34, 402, 18), // "AmplitudeHistogram"
QT_MOC_LITERAL(35, 421, 26), // "CorrectedPositionHistogram"
QT_MOC_LITERAL(36, 448, 11), // "NoHistogram"
QT_MOC_LITERAL(37, 460, 19), // "HistogramFileFormat"
QT_MOC_LITERAL(38, 480, 14), // "StandardFormat"
QT_MOC_LITERAL(39, 495, 12), // "SimpleFormat"
QT_MOC_LITERAL(40, 508, 12), // "SpectrumType"
QT_MOC_LITERAL(41, 521, 12), // "TimeSpectrum"
QT_MOC_LITERAL(42, 534, 13), // "Diffractogram"
QT_MOC_LITERAL(43, 548, 12), // "TubeSpectrum"
QT_MOC_LITERAL(44, 561, 9), // "XSpectrum"
QT_MOC_LITERAL(45, 571, 9), // "YSpectrum"
QT_MOC_LITERAL(46, 581, 14), // "EnergySpectrum"
QT_MOC_LITERAL(47, 596, 17), // "AmplitudeSpectrum"
QT_MOC_LITERAL(48, 614, 18), // "SingleTubeSpectrum"
QT_MOC_LITERAL(49, 633, 18), // "SingleLineSpectrum"
QT_MOC_LITERAL(50, 652, 10), // "NoSpectrum"
QT_MOC_LITERAL(51, 663, 4), // "Idle"
QT_MOC_LITERAL(52, 668, 7), // "Started"
QT_MOC_LITERAL(53, 676, 7) // "Stopped"

    },
    "Measurement\0stopSignal\0\0acqListfile\0"
    "autoSaveHistogram\0mappingChanged\0"
    "analyzeBuffer\0QSharedDataPointer<SD_PACKET>\0"
    "pPacket\0calcRates\0setHeadertime\0ht\0"
    "setMonitorMapping\0id\0input\0channel\0"
    "requestStop\0m_mode\0Mode\0m_status\0"
    "Status\0m_histfilename\0m_histPath\0"
    "m_calibrationfilename\0m_listPath\0"
    "m_configPath\0m_configfile\0m_height\0"
    "m_width\0DataAcquisition\0ReplayListFile\0"
    "HistogramLoad\0HistogramType\0"
    "PositionHistogram\0AmplitudeHistogram\0"
    "CorrectedPositionHistogram\0NoHistogram\0"
    "HistogramFileFormat\0StandardFormat\0"
    "SimpleFormat\0SpectrumType\0TimeSpectrum\0"
    "Diffractogram\0TubeSpectrum\0XSpectrum\0"
    "YSpectrum\0EnergySpectrum\0AmplitudeSpectrum\0"
    "SingleTubeSpectrum\0SingleLineSpectrum\0"
    "NoSpectrum\0Idle\0Started\0Stopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Measurement[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
      10,   90, // properties
       5,  120, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       1,    0,   67,    2, 0x26 /* Public | MethodCloned */,
       3,    1,   68,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,
       5,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   75,    2, 0x0a /* Public */,
       9,    0,   78,    2, 0x0a /* Public */,
      10,    1,   79,    2, 0x0a /* Public */,
      12,    3,   82,    2, 0x0a /* Public */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,   11,
    QMetaType::Void, QMetaType::UShort, QMetaType::SChar, QMetaType::SChar,   13,   14,   15,
    QMetaType::Void,

 // properties: name, type, flags
      17, 0x80000000 | 18, 0x00095009,
      19, 0x80000000 | 20, 0x00095009,
      21, QMetaType::QString, 0x00095003,
      22, QMetaType::QString, 0x00095003,
      23, QMetaType::QString, 0x00095003,
      24, QMetaType::QString, 0x00095003,
      25, QMetaType::QString, 0x00095003,
      26, QMetaType::QString, 0x00095003,
      27, QMetaType::UShort, 0x00095001,
      28, QMetaType::UShort, 0x00095001,

 // enums: name, alias, flags, count, data
      18,   18, 0x0,    3,  145,
      32,   32, 0x0,    4,  151,
      37,   37, 0x0,    2,  159,
      40,   40, 0x0,   10,  163,
      20,   20, 0x0,    3,  183,

 // enum data: key, value
      29, uint(Measurement::DataAcquisition),
      30, uint(Measurement::ReplayListFile),
      31, uint(Measurement::HistogramLoad),
      33, uint(Measurement::PositionHistogram),
      34, uint(Measurement::AmplitudeHistogram),
      35, uint(Measurement::CorrectedPositionHistogram),
      36, uint(Measurement::NoHistogram),
      38, uint(Measurement::StandardFormat),
      39, uint(Measurement::SimpleFormat),
      41, uint(Measurement::TimeSpectrum),
      42, uint(Measurement::Diffractogram),
      43, uint(Measurement::TubeSpectrum),
      44, uint(Measurement::XSpectrum),
      45, uint(Measurement::YSpectrum),
      46, uint(Measurement::EnergySpectrum),
      47, uint(Measurement::AmplitudeSpectrum),
      48, uint(Measurement::SingleTubeSpectrum),
      49, uint(Measurement::SingleLineSpectrum),
      50, uint(Measurement::NoSpectrum),
      51, uint(Measurement::Idle),
      52, uint(Measurement::Started),
      53, uint(Measurement::Stopped),

       0        // eod
};

void Measurement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Measurement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->stopSignal(); break;
        case 2: _t->acqListfile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->autoSaveHistogram((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->mappingChanged(); break;
        case 5: _t->analyzeBuffer((*reinterpret_cast< QSharedDataPointer<SD_PACKET>(*)>(_a[1]))); break;
        case 6: _t->calcRates(); break;
        case 7: _t->setHeadertime((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 8: _t->setMonitorMapping((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< qint8(*)>(_a[2])),(*reinterpret_cast< qint8(*)>(_a[3]))); break;
        case 9: _t->requestStop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Measurement::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Measurement::stopSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Measurement::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Measurement::acqListfile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Measurement::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Measurement::autoSaveHistogram)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Measurement::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Measurement::mappingChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Measurement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Mode*>(_v) = _t->mode(); break;
        case 1: *reinterpret_cast< Status*>(_v) = _t->status(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getHistfilename(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getHistfilepath(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->getCalibrationfilename(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->getListfilepath(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->getConfigfilepath(); break;
        case 7: *reinterpret_cast< QString*>(_v) = _t->getConfigfilename(); break;
        case 8: *reinterpret_cast< quint16*>(_v) = _t->height(); break;
        case 9: *reinterpret_cast< quint16*>(_v) = _t->width(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Measurement *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setHistfilename(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setHistfilepath(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setCalibrationfilename(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setListfilepath(*reinterpret_cast< QString*>(_v)); break;
        case 6: _t->setConfigfilepath(*reinterpret_cast< QString*>(_v)); break;
        case 7: _t->setConfigfilename(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Measurement::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Measurement.data,
    qt_meta_data_Measurement,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Measurement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Measurement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Measurement.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Measurement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Measurement::stopSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void Measurement::acqListfile(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Measurement::autoSaveHistogram(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Measurement::mappingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
