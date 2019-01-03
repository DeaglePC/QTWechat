/****************************************************************************
** Meta object code from reading C++ file 'cwebwxwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../libwebwx/cwebwxwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cwebwxwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CWebwxWork_t {
    QByteArrayData data[23];
    char stringdata0[289];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CWebwxWork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CWebwxWork_t qt_meta_stringdata_CWebwxWork = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CWebwxWork"
QT_MOC_LITERAL(1, 11, 11), // "sglQrcodeOk"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "qrcode"
QT_MOC_LITERAL(4, 31, 10), // "sglHintMsg"
QT_MOC_LITERAL(5, 42, 3), // "msg"
QT_MOC_LITERAL(6, 46, 15), // "sglAllContactOk"
QT_MOC_LITERAL(7, 62, 10), // "allContact"
QT_MOC_LITERAL(8, 73, 12), // "sglOneHeadOk"
QT_MOC_LITERAL(9, 86, 12), // "headFileName"
QT_MOC_LITERAL(10, 99, 13), // "sglNewMessage"
QT_MOC_LITERAL(11, 113, 6), // "newMsg"
QT_MOC_LITERAL(12, 120, 22), // "sglGetUserselfFinished"
QT_MOC_LITERAL(13, 143, 12), // "userselfData"
QT_MOC_LITERAL(14, 156, 19), // "sglMainLoopFinished"
QT_MOC_LITERAL(15, 176, 11), // "sltMainLoop"
QT_MOC_LITERAL(16, 188, 13), // "sltGetHeadImg"
QT_MOC_LITERAL(17, 202, 3), // "url"
QT_MOC_LITERAL(18, 206, 23), // "sltGetHeadImgByUsername"
QT_MOC_LITERAL(19, 230, 8), // "userName"
QT_MOC_LITERAL(20, 239, 18), // "sltGetHeadFinished"
QT_MOC_LITERAL(21, 258, 7), // "content"
QT_MOC_LITERAL(22, 266, 22) // "sltGetUserselfFinished"

    },
    "CWebwxWork\0sglQrcodeOk\0\0qrcode\0"
    "sglHintMsg\0msg\0sglAllContactOk\0"
    "allContact\0sglOneHeadOk\0headFileName\0"
    "sglNewMessage\0newMsg\0sglGetUserselfFinished\0"
    "userselfData\0sglMainLoopFinished\0"
    "sltMainLoop\0sltGetHeadImg\0url\0"
    "sltGetHeadImgByUsername\0userName\0"
    "sltGetHeadFinished\0content\0"
    "sltGetUserselfFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CWebwxWork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    1,   80,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x06 /* Public */,
      10,    1,   86,    2, 0x06 /* Public */,
      12,    1,   89,    2, 0x06 /* Public */,
      14,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   93,    2, 0x0a /* Public */,
      16,    1,   94,    2, 0x0a /* Public */,
      18,    1,   97,    2, 0x0a /* Public */,
      20,    2,  100,    2, 0x0a /* Public */,
      22,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QVariantHash,   13,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   19,   21,
    QMetaType::Void, QMetaType::QVariantHash,   13,

       0        // eod
};

void CWebwxWork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CWebwxWork *_t = static_cast<CWebwxWork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglQrcodeOk((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sglHintMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sglAllContactOk((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->sglOneHeadOk((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->sglNewMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sglGetUserselfFinished((*reinterpret_cast< const QVariantHash(*)>(_a[1]))); break;
        case 6: _t->sglMainLoopFinished(); break;
        case 7: _t->sltMainLoop(); break;
        case 8: _t->sltGetHeadImg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->sltGetHeadImgByUsername((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->sltGetHeadFinished((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 11: _t->sltGetUserselfFinished((*reinterpret_cast< const QVariantHash(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CWebwxWork::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglQrcodeOk)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CWebwxWork::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglHintMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CWebwxWork::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglAllContactOk)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CWebwxWork::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglOneHeadOk)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CWebwxWork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglNewMessage)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CWebwxWork::*)(const QVariantHash & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglGetUserselfFinished)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CWebwxWork::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWebwxWork::sglMainLoopFinished)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CWebwxWork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CWebwxWork.data,
      qt_meta_data_CWebwxWork,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CWebwxWork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CWebwxWork::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CWebwxWork.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CWebwxWork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CWebwxWork::sglQrcodeOk(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CWebwxWork::sglHintMsg(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CWebwxWork::sglAllContactOk(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CWebwxWork::sglOneHeadOk(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CWebwxWork::sglNewMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CWebwxWork::sglGetUserselfFinished(const QVariantHash & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CWebwxWork::sglMainLoopFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
