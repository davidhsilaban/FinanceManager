/****************************************************************************
** Meta object code from reading C++ file 'MainApp.h'
**
** Created: Tue 6. May 17:08:25 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainApp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainApp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      22,    8,    8,    8, 0x08,
      34,   29,    8,    8, 0x08,
      81,   64,    8,    8, 0x08,
     127,    8,    8,    8, 0x08,
     138,    8,    8,    8, 0x08,
     153,    8,  148,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainApp[] = {
    "MainApp\0\0commitData()\0save()\0item\0"
    "listClicked(QListWidgetItem*)\0"
    "current,previous\0"
    "changePage(QListWidgetItem*,QListWidgetItem*)\0"
    "openFile()\0newFile()\0bool\0closeDatabase()\0"
};

void MainApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainApp *_t = static_cast<MainApp *>(_o);
        switch (_id) {
        case 0: _t->commitData(); break;
        case 1: _t->save(); break;
        case 2: _t->listClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->changePage((*reinterpret_cast< QListWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 4: _t->openFile(); break;
        case 5: _t->newFile(); break;
        case 6: { bool _r = _t->closeDatabase();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainApp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainApp::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainApp,
      qt_meta_data_MainApp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainApp))
        return static_cast<void*>(const_cast< MainApp*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
