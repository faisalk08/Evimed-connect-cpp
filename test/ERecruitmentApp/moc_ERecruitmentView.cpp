/****************************************************************************
** Meta object code from reading C++ file 'ERecruitmentView.h'
**
** Created: Mon Feb 18 09:20:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/ERecruitmentView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ERecruitmentView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ERecruitmentView[] = {

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
      18,   17,   17,   17, 0x08,
      33,   17,   17,   17, 0x08,
      47,   41,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ERecruitmentView[] = {
    "ERecruitmentView\0\0loadFinished()\0"
    "login()\0index\0displayDetail(int)\0"
};

void ERecruitmentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ERecruitmentView *_t = static_cast<ERecruitmentView *>(_o);
        switch (_id) {
        case 0: _t->loadFinished(); break;
        case 1: _t->login(); break;
        case 2: _t->displayDetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ERecruitmentView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ERecruitmentView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ERecruitmentView,
      qt_meta_data_ERecruitmentView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ERecruitmentView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ERecruitmentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ERecruitmentView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ERecruitmentView))
        return static_cast<void*>(const_cast< ERecruitmentView*>(this));
    return QWidget::qt_metacast(_clname);
}

int ERecruitmentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
