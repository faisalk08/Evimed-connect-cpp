/****************************************************************************
** Meta object code from reading C++ file 'WebkitUI.h'
**
** Created: Tue Jan 15 12:23:25 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/WebkitUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebkitUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WebkitUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   18,   10,    9, 0x09,
      52,   46,    9,    9, 0x09,
      80,    9,    9,    9, 0x09,
      97,    9,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_WebkitUI[] = {
    "WebkitUI\0\0QString\0fileName\0"
    "loadScript(string)\0reply\0"
    "namFinished(QNetworkReply*)\0"
    "replyReadyRead()\0replyFinished()\0"
};

void WebkitUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WebkitUI *_t = static_cast<WebkitUI *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->loadScript((*reinterpret_cast< string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: _t->namFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->replyReadyRead(); break;
        case 3: _t->replyFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WebkitUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WebkitUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WebkitUI,
      qt_meta_data_WebkitUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WebkitUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WebkitUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WebkitUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WebkitUI))
        return static_cast<void*>(const_cast< WebkitUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int WebkitUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
