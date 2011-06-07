/****************************************************************************
** Meta object code from reading C++ file 'Kiwi.h'
**
** Created: Tue Jun 7 15:37:56 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Kiwi.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Kiwi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Pixy__Kiwi[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x0a,
      37,   11,   11,   11, 0x0a,
      58,   11,   11,   11, 0x0a,
      79,   11,   11,   11, 0x0a,
     100,   11,   11,   11, 0x0a,
     117,   11,   11,   11, 0x0a,
     134,   11,   11,   11, 0x0a,
     151,   11,   11,   11, 0x0a,
     168,   11,   11,   11, 0x0a,
     195,   11,   11,   11, 0x0a,
     222,   11,   11,   11, 0x0a,
     245,   11,   11,   11, 0x0a,
     260,   11,   11,   11, 0x0a,
     284,   11,   11,   11, 0x0a,
     306,   11,   11,   11, 0x0a,
     331,   11,   11,   11, 0x0a,
     356,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Pixy__Kiwi[] = {
    "Pixy::Kiwi\0\0inIdx\0evtTabChanged(int)\0"
    "evtShowAboutDialog()\0evtClickChangeRoot()\0"
    "evtClickUpdateRoot()\0evtClickCreate()\0"
    "evtClickModify()\0evtClickRename()\0"
    "evtClickDelete()\0evtClickFindDiffOriginal()\0"
    "evtClickFindDiffModified()\0"
    "evtClickFindDiffDest()\0evtClickDiff()\0"
    "evtClickFindMD5Source()\0evtClickGenerateMD5()\0"
    "evtChangeStructure(bool)\0"
    "evtClickGenerateScript()\0"
    "evtClickGenerateTarball()\0"
};

const QMetaObject Pixy::Kiwi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Pixy__Kiwi,
      qt_meta_data_Pixy__Kiwi, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Pixy::Kiwi::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Pixy::Kiwi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Pixy::Kiwi::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Pixy__Kiwi))
        return static_cast<void*>(const_cast< Kiwi*>(this));
    return QObject::qt_metacast(_clname);
}

int Pixy::Kiwi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: evtTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: evtShowAboutDialog(); break;
        case 2: evtClickChangeRoot(); break;
        case 3: evtClickUpdateRoot(); break;
        case 4: evtClickCreate(); break;
        case 5: evtClickModify(); break;
        case 6: evtClickRename(); break;
        case 7: evtClickDelete(); break;
        case 8: evtClickFindDiffOriginal(); break;
        case 9: evtClickFindDiffModified(); break;
        case 10: evtClickFindDiffDest(); break;
        case 11: evtClickDiff(); break;
        case 12: evtClickFindMD5Source(); break;
        case 13: evtClickGenerateMD5(); break;
        case 14: evtChangeStructure((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: evtClickGenerateScript(); break;
        case 16: evtClickGenerateTarball(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
