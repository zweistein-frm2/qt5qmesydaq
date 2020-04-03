/****************************************************************************
** Meta object code from reading C++ file 'mesydaq2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mesydaq2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mesydaq2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mesydaq2_t {
    QByteArrayData data[94];
    char stringdata0[915];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mesydaq2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mesydaq2_t qt_meta_stringdata_Mesydaq2 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Mesydaq2"
QT_MOC_LITERAL(1, 9, 13), // "statusChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "str"
QT_MOC_LITERAL(4, 28, 17), // "analyzeDataBuffer"
QT_MOC_LITERAL(5, 46, 29), // "QSharedDataPointer<SD_PACKET>"
QT_MOC_LITERAL(6, 76, 7), // "pPacket"
QT_MOC_LITERAL(7, 84, 21), // "newCmdPackageReceived"
QT_MOC_LITERAL(8, 106, 17), // "headerTimeChanged"
QT_MOC_LITERAL(9, 124, 8), // "syncLost"
QT_MOC_LITERAL(10, 133, 2), // "id"
QT_MOC_LITERAL(11, 136, 5), // "bLost"
QT_MOC_LITERAL(12, 142, 10), // "threadExit"
QT_MOC_LITERAL(13, 153, 7), // "addMCPD"
QT_MOC_LITERAL(14, 161, 13), // "writeRegister"
QT_MOC_LITERAL(15, 175, 3), // "reg"
QT_MOC_LITERAL(16, 179, 3), // "val"
QT_MOC_LITERAL(17, 183, 11), // "setProtocol"
QT_MOC_LITERAL(18, 195, 6), // "mcpdIP"
QT_MOC_LITERAL(19, 202, 6), // "dataIP"
QT_MOC_LITERAL(20, 209, 8), // "dataPort"
QT_MOC_LITERAL(21, 218, 5), // "cmdIP"
QT_MOC_LITERAL(22, 224, 7), // "cmdPort"
QT_MOC_LITERAL(23, 232, 11), // "getProtocol"
QT_MOC_LITERAL(24, 244, 8), // "QString&"
QT_MOC_LITERAL(25, 253, 8), // "quint16&"
QT_MOC_LITERAL(26, 262, 7), // "setMode"
QT_MOC_LITERAL(27, 270, 4), // "addr"
QT_MOC_LITERAL(28, 275, 4), // "mode"
QT_MOC_LITERAL(29, 280, 9), // "setPulser"
QT_MOC_LITERAL(30, 290, 3), // "mod"
QT_MOC_LITERAL(31, 294, 7), // "channel"
QT_MOC_LITERAL(32, 302, 8), // "position"
QT_MOC_LITERAL(33, 311, 3), // "amp"
QT_MOC_LITERAL(34, 315, 5), // "onoff"
QT_MOC_LITERAL(35, 321, 14), // "setCounterCell"
QT_MOC_LITERAL(36, 336, 6), // "source"
QT_MOC_LITERAL(37, 343, 7), // "trigger"
QT_MOC_LITERAL(38, 351, 7), // "compare"
QT_MOC_LITERAL(39, 359, 14), // "setParamSource"
QT_MOC_LITERAL(40, 374, 5), // "param"
QT_MOC_LITERAL(41, 380, 11), // "setAuxTimer"
QT_MOC_LITERAL(42, 392, 3), // "tim"
QT_MOC_LITERAL(43, 396, 14), // "setMasterClock"
QT_MOC_LITERAL(44, 411, 14), // "setTimingSetup"
QT_MOC_LITERAL(45, 426, 6), // "master"
QT_MOC_LITERAL(46, 433, 4), // "term"
QT_MOC_LITERAL(47, 438, 7), // "extsync"
QT_MOC_LITERAL(48, 446, 5), // "setId"
QT_MOC_LITERAL(49, 452, 6), // "mcpdid"
QT_MOC_LITERAL(50, 459, 7), // "setGain"
QT_MOC_LITERAL(51, 467, 4), // "gain"
QT_MOC_LITERAL(52, 472, 12), // "setThreshold"
QT_MOC_LITERAL(53, 485, 6), // "thresh"
QT_MOC_LITERAL(54, 492, 17), // "setMdllThresholds"
QT_MOC_LITERAL(55, 510, 7), // "threshX"
QT_MOC_LITERAL(56, 518, 7), // "threshY"
QT_MOC_LITERAL(57, 526, 7), // "threshA"
QT_MOC_LITERAL(58, 534, 15), // "setMdllSpectrum"
QT_MOC_LITERAL(59, 550, 6), // "shiftX"
QT_MOC_LITERAL(60, 557, 6), // "shiftY"
QT_MOC_LITERAL(61, 564, 6), // "scaleX"
QT_MOC_LITERAL(62, 571, 6), // "scaleY"
QT_MOC_LITERAL(63, 578, 14), // "setMdllDataset"
QT_MOC_LITERAL(64, 593, 3), // "set"
QT_MOC_LITERAL(65, 597, 19), // "setMdllTimingWindow"
QT_MOC_LITERAL(66, 617, 3), // "xlo"
QT_MOC_LITERAL(67, 621, 3), // "xhi"
QT_MOC_LITERAL(68, 625, 3), // "ylo"
QT_MOC_LITERAL(69, 629, 3), // "yhi"
QT_MOC_LITERAL(70, 633, 19), // "setMdllEnergyWindow"
QT_MOC_LITERAL(71, 653, 3), // "elo"
QT_MOC_LITERAL(72, 657, 3), // "ehi"
QT_MOC_LITERAL(73, 661, 11), // "acqListfile"
QT_MOC_LITERAL(74, 673, 5), // "yesno"
QT_MOC_LITERAL(75, 679, 17), // "autoSaveHistogram"
QT_MOC_LITERAL(76, 697, 5), // "start"
QT_MOC_LITERAL(77, 703, 10), // "startedDaq"
QT_MOC_LITERAL(78, 714, 4), // "stop"
QT_MOC_LITERAL(79, 719, 10), // "stoppedDaq"
QT_MOC_LITERAL(80, 730, 5), // "reset"
QT_MOC_LITERAL(81, 736, 4), // "cont"
QT_MOC_LITERAL(82, 741, 12), // "allPulserOff"
QT_MOC_LITERAL(83, 754, 19), // "writeListfileHeader"
QT_MOC_LITERAL(84, 774, 21), // "writeClosingSignature"
QT_MOC_LITERAL(85, 796, 16), // "writeProtectFile"
QT_MOC_LITERAL(86, 813, 10), // "QIODevice*"
QT_MOC_LITERAL(87, 824, 9), // "pIODevice"
QT_MOC_LITERAL(88, 834, 19), // "writeBlockSeparator"
QT_MOC_LITERAL(89, 854, 20), // "writeHeaderSeparator"
QT_MOC_LITERAL(90, 875, 13), // "analyzeBuffer"
QT_MOC_LITERAL(91, 889, 8), // "lostSync"
QT_MOC_LITERAL(92, 898, 13), // "setHeadertime"
QT_MOC_LITERAL(93, 912, 2) // "ht"

    },
    "Mesydaq2\0statusChanged\0\0str\0"
    "analyzeDataBuffer\0QSharedDataPointer<SD_PACKET>\0"
    "pPacket\0newCmdPackageReceived\0"
    "headerTimeChanged\0syncLost\0id\0bLost\0"
    "threadExit\0addMCPD\0writeRegister\0reg\0"
    "val\0setProtocol\0mcpdIP\0dataIP\0dataPort\0"
    "cmdIP\0cmdPort\0getProtocol\0QString&\0"
    "quint16&\0setMode\0addr\0mode\0setPulser\0"
    "mod\0channel\0position\0amp\0onoff\0"
    "setCounterCell\0source\0trigger\0compare\0"
    "setParamSource\0param\0setAuxTimer\0tim\0"
    "setMasterClock\0setTimingSetup\0master\0"
    "term\0extsync\0setId\0mcpdid\0setGain\0"
    "gain\0setThreshold\0thresh\0setMdllThresholds\0"
    "threshX\0threshY\0threshA\0setMdllSpectrum\0"
    "shiftX\0shiftY\0scaleX\0scaleY\0setMdllDataset\0"
    "set\0setMdllTimingWindow\0xlo\0xhi\0ylo\0"
    "yhi\0setMdllEnergyWindow\0elo\0ehi\0"
    "acqListfile\0yesno\0autoSaveHistogram\0"
    "start\0startedDaq\0stop\0stoppedDaq\0reset\0"
    "cont\0allPulserOff\0writeListfileHeader\0"
    "writeClosingSignature\0writeProtectFile\0"
    "QIODevice*\0pIODevice\0writeBlockSeparator\0"
    "writeHeaderSeparator\0analyzeBuffer\0"
    "lostSync\0setHeadertime\0ht"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mesydaq2[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  289,    2, 0x06 /* Public */,
       4,    1,  292,    2, 0x06 /* Public */,
       7,    0,  295,    2, 0x06 /* Public */,
       8,    1,  296,    2, 0x06 /* Public */,
       9,    2,  299,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  304,    2, 0x0a /* Public */,
      13,    6,  305,    2, 0x0a /* Public */,
      13,    5,  318,    2, 0x2a /* Public | MethodCloned */,
      13,    4,  329,    2, 0x2a /* Public | MethodCloned */,
      13,    3,  338,    2, 0x2a /* Public | MethodCloned */,
      13,    2,  345,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  350,    2, 0x2a /* Public | MethodCloned */,
      14,    3,  353,    2, 0x0a /* Public */,
      17,    6,  360,    2, 0x0a /* Public */,
      17,    5,  373,    2, 0x2a /* Public | MethodCloned */,
      17,    4,  384,    2, 0x2a /* Public | MethodCloned */,
      17,    3,  393,    2, 0x2a /* Public | MethodCloned */,
      17,    2,  400,    2, 0x2a /* Public | MethodCloned */,
      23,    6,  405,    2, 0x0a /* Public */,
      26,    3,  418,    2, 0x0a /* Public */,
      29,    6,  425,    2, 0x0a /* Public */,
      35,    4,  438,    2, 0x0a /* Public */,
      39,    3,  447,    2, 0x0a /* Public */,
      41,    3,  454,    2, 0x0a /* Public */,
      43,    2,  461,    2, 0x0a /* Public */,
      44,    4,  466,    2, 0x0a /* Public */,
      48,    2,  475,    2, 0x0a /* Public */,
      50,    4,  480,    2, 0x0a /* Public */,
      50,    4,  489,    2, 0x0a /* Public */,
      52,    3,  498,    2, 0x0a /* Public */,
      52,    3,  505,    2, 0x0a /* Public */,
      54,    4,  512,    2, 0x0a /* Public */,
      58,    5,  521,    2, 0x0a /* Public */,
      63,    2,  532,    2, 0x0a /* Public */,
      65,    5,  537,    2, 0x0a /* Public */,
      70,    3,  548,    2, 0x0a /* Public */,
      73,    1,  555,    2, 0x0a /* Public */,
      73,    0,  558,    2, 0x0a /* Public */,
      75,    1,  559,    2, 0x0a /* Public */,
      75,    0,  562,    2, 0x0a /* Public */,
      76,    0,  563,    2, 0x0a /* Public */,
      77,    0,  564,    2, 0x0a /* Public */,
      78,    0,  565,    2, 0x0a /* Public */,
      79,    0,  566,    2, 0x0a /* Public */,
      80,    0,  567,    2, 0x0a /* Public */,
      81,    0,  568,    2, 0x0a /* Public */,
      82,    0,  569,    2, 0x0a /* Public */,
      83,    0,  570,    2, 0x0a /* Public */,
      84,    0,  571,    2, 0x0a /* Public */,
      85,    1,  572,    2, 0x0a /* Public */,
      88,    0,  575,    2, 0x0a /* Public */,
      89,    0,  576,    2, 0x0a /* Public */,
      90,    1,  577,    2, 0x0a /* Public */,
      91,    2,  580,    2, 0x0a /* Public */,
      92,    1,  585,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong,    2,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool,   10,   11,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString, QMetaType::UShort, QMetaType::QString, QMetaType::UShort, QMetaType::QString,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString, QMetaType::UShort, QMetaType::QString, QMetaType::UShort,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString, QMetaType::UShort, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString, QMetaType::UShort,    2,    2,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,   10,   15,   16,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString, QMetaType::QString, QMetaType::UShort, QMetaType::QString, QMetaType::UShort,   10,   18,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString, QMetaType::QString, QMetaType::UShort, QMetaType::QString,   10,   18,   19,   20,   21,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString, QMetaType::QString, QMetaType::UShort,   10,   18,   19,   20,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString, QMetaType::QString,   10,   18,   19,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString,   10,   18,
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 24, 0x80000000 | 24, 0x80000000 | 25, 0x80000000 | 24, 0x80000000 | 25,   10,   18,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::Bool,   10,   27,   28,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::Bool,   30,   27,   31,   32,   33,   34,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,   30,   36,   37,   38,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,   30,   40,   36,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,   30,   42,   16,
    QMetaType::Void, QMetaType::UShort, QMetaType::ULongLong,   30,    2,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   30,   45,   46,   47,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar,   30,   49,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   30,   27,   31,   51,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar, QMetaType::Float,   30,   27,   31,   51,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar,   30,   27,   53,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UShort,   30,   27,   53,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   30,   55,   56,   57,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar, QMetaType::UChar,   30,   59,   60,   61,   62,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar,   30,   64,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort, QMetaType::UShort,   30,   66,   67,   68,   69,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, QMetaType::UChar,   30,   71,   72,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 86,   87,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::ULongLong,   93,

       0        // eod
};

void Mesydaq2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Mesydaq2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statusChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->analyzeDataBuffer((*reinterpret_cast< QSharedDataPointer<SD_PACKET>(*)>(_a[1]))); break;
        case 2: _t->newCmdPackageReceived(); break;
        case 3: _t->headerTimeChanged((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 4: _t->syncLost((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->threadExit(); break;
        case 6: _t->addMCPD((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< quint16(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 7: _t->addMCPD((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< quint16(*)>(_a[5]))); break;
        case 8: _t->addMCPD((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 9: _t->addMCPD((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 10: _t->addMCPD((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->addMCPD((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 12: _t->writeRegister((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 13: _t->setProtocol((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< quint16(*)>(_a[6]))); break;
        case 14: _t->setProtocol((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 15: _t->setProtocol((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4]))); break;
        case 16: _t->setProtocol((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 17: _t->setProtocol((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 18: _t->getProtocol((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< quint16(*)>(_a[6]))); break;
        case 19: _t->setMode((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 20: _t->setPulser((*reinterpret_cast< const quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< quint8(*)>(_a[4])),(*reinterpret_cast< quint8(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 21: _t->setCounterCell((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4]))); break;
        case 22: _t->setParamSource((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 23: _t->setAuxTimer((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 24: _t->setMasterClock((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 25: _t->setTimingSetup((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 26: _t->setId((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 27: _t->setGain((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< quint8(*)>(_a[4]))); break;
        case 28: _t->setGain((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 29: _t->setThreshold((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 30: _t->setThreshold((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 31: _t->setMdllThresholds((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< quint8(*)>(_a[4]))); break;
        case 32: _t->setMdllSpectrum((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3])),(*reinterpret_cast< quint8(*)>(_a[4])),(*reinterpret_cast< quint8(*)>(_a[5]))); break;
        case 33: _t->setMdllDataset((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 34: _t->setMdllTimingWindow((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3])),(*reinterpret_cast< quint16(*)>(_a[4])),(*reinterpret_cast< quint16(*)>(_a[5]))); break;
        case 35: _t->setMdllEnergyWindow((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< quint8(*)>(_a[3]))); break;
        case 36: _t->acqListfile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: { bool _r = _t->acqListfile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->autoSaveHistogram((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: { bool _r = _t->autoSaveHistogram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->start(); break;
        case 41: _t->startedDaq(); break;
        case 42: _t->stop(); break;
        case 43: _t->stoppedDaq(); break;
        case 44: _t->reset(); break;
        case 45: _t->cont(); break;
        case 46: _t->allPulserOff(); break;
        case 47: _t->writeListfileHeader(); break;
        case 48: _t->writeClosingSignature(); break;
        case 49: _t->writeProtectFile((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        case 50: _t->writeBlockSeparator(); break;
        case 51: _t->writeHeaderSeparator(); break;
        case 52: _t->analyzeBuffer((*reinterpret_cast< QSharedDataPointer<SD_PACKET>(*)>(_a[1]))); break;
        case 53: _t->lostSync((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 54: _t->setHeadertime((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 49:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QIODevice* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Mesydaq2::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mesydaq2::statusChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Mesydaq2::*)(QSharedDataPointer<SD_PACKET> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mesydaq2::analyzeDataBuffer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Mesydaq2::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mesydaq2::newCmdPackageReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Mesydaq2::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mesydaq2::headerTimeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Mesydaq2::*)(quint16 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Mesydaq2::syncLost)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Mesydaq2::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Mesydaq2.data,
    qt_meta_data_Mesydaq2,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Mesydaq2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mesydaq2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mesydaq2.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Mesydaq2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    }
    return _id;
}

// SIGNAL 0
void Mesydaq2::statusChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mesydaq2::analyzeDataBuffer(QSharedDataPointer<SD_PACKET> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mesydaq2::newCmdPackageReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Mesydaq2::headerTimeChanged(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Mesydaq2::syncLost(quint16 _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
