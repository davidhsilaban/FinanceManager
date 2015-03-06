/****************************************************************************
** Meta object code from reading C++ file 'MainPages.h'
**
** Created: Tue 6. May 17:26:38 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainPages.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainPages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NoFileOpenedPage[] = {

 // content:
       6,       // revision
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

static const char qt_meta_stringdata_NoFileOpenedPage[] = {
    "NoFileOpenedPage\0"
};

void NoFileOpenedPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData NoFileOpenedPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NoFileOpenedPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NoFileOpenedPage,
      qt_meta_data_NoFileOpenedPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NoFileOpenedPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NoFileOpenedPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NoFileOpenedPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NoFileOpenedPage))
        return static_cast<void*>(const_cast< NoFileOpenedPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int NoFileOpenedPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_InitialPage[] = {

 // content:
       6,       // revision
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

static const char qt_meta_stringdata_InitialPage[] = {
    "InitialPage\0"
};

void InitialPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData InitialPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InitialPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InitialPage,
      qt_meta_data_InitialPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InitialPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InitialPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InitialPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InitialPage))
        return static_cast<void*>(const_cast< InitialPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int InitialPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_InsertDataPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      33,   15,   15,   15, 0x08,
      45,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_InsertDataPage[] = {
    "InsertDataPage\0\0addTransaction()\0"
    "resetForm()\0refreshCategories()\0"
};

void InsertDataPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InsertDataPage *_t = static_cast<InsertDataPage *>(_o);
        switch (_id) {
        case 0: _t->addTransaction(); break;
        case 1: _t->resetForm(); break;
        case 2: _t->refreshCategories(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData InsertDataPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InsertDataPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InsertDataPage,
      qt_meta_data_InsertDataPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InsertDataPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InsertDataPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InsertDataPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InsertDataPage))
        return static_cast<void*>(const_cast< InsertDataPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int InsertDataPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_ViewDataPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ViewDataPage[] = {
    "ViewDataPage\0\0refreshTable()\0"
};

void ViewDataPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ViewDataPage *_t = static_cast<ViewDataPage *>(_o);
        switch (_id) {
        case 0: _t->refreshTable(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ViewDataPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ViewDataPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewDataPage,
      qt_meta_data_ViewDataPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewDataPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewDataPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewDataPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewDataPage))
        return static_cast<void*>(const_cast< ViewDataPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewDataPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
