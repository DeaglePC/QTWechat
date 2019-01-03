/****************************************************************************
** Meta object code from reading C++ file 'cwechatrequest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../libwebwx/network/cwechatrequest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cwechatrequest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CWechatRequest_t {
    QByteArrayData data[8];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CWechatRequest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CWechatRequest_t qt_meta_stringdata_CWechatRequest = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CWechatRequest"
QT_MOC_LITERAL(1, 15, 18), // "sglGetHeadFinished"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "userName"
QT_MOC_LITERAL(4, 44, 11), // "headImgData"
QT_MOC_LITERAL(5, 56, 22), // "sglGetUserselfFinished"
QT_MOC_LITERAL(6, 79, 12), // "userselfData"
QT_MOC_LITERAL(7, 92, 18) // "sltGetHeadFinished"

    },
    "CWechatRequest\0sglGetHeadFinished\0\0"
    "userName\0headImgData\0sglGetUserselfFinished\0"
    "userselfData\0sltGetHeadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CWechatRequest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    4,
    QMetaType::Void, QMetaType::QVariantHash,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CWechatRequest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CWechatRequest *_t = static_cast<CWechatRequest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglGetHeadFinished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->sglGetUserselfFinished((*reinterpret_cast< const QVariantHash(*)>(_a[1]))); break;
        case 2: _t->sltGetHeadFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CWechatRequest::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWechatRequest::sglGetHeadFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CWechatRequest::*)(const QVariantHash & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWechatRequest::sglGetUserselfFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CWechatRequest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CWechatRequest.data,
      qt_meta_data_CWechatRequest,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CWechatRequest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CWechatRequest::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CWechatRequest.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CWechatRequest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CWechatRequest::sglGetHeadFinished(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CWechatRequest::sglGetUserselfFinished(const QVariantHash & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
