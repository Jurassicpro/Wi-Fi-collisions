/****************************************************************************
** Meta object code from reading C++ file 'addmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../view/addmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddMenu_t {
    QByteArrayData data[10];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddMenu_t qt_meta_stringdata_AddMenu = {
    {
QT_MOC_LITERAL(0, 0, 7), // "AddMenu"
QT_MOC_LITERAL(1, 8, 15), // "addRouterSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "addPCSignal"
QT_MOC_LITERAL(4, 37, 13), // "changeChannel"
QT_MOC_LITERAL(5, 51, 15), // "OffOnRouterWave"
QT_MOC_LITERAL(6, 67, 24), // "BtnMenuChangeChannelText"
QT_MOC_LITERAL(7, 92, 23), // "BtnMenuChangeRouterText"
QT_MOC_LITERAL(8, 116, 30), // "BtnMenuChangeRouterChannelText"
QT_MOC_LITERAL(9, 147, 22) // "BtnMenuChangeSpeedText"

    },
    "AddMenu\0addRouterSignal\0\0addPCSignal\0"
    "changeChannel\0OffOnRouterWave\0"
    "BtnMenuChangeChannelText\0"
    "BtnMenuChangeRouterText\0"
    "BtnMenuChangeRouterChannelText\0"
    "BtnMenuChangeSpeedText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddMenu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addRouterSignal(); break;
        case 1: _t->addPCSignal(); break;
        case 2: _t->changeChannel(); break;
        case 3: _t->OffOnRouterWave(); break;
        case 4: _t->BtnMenuChangeChannelText(); break;
        case 5: _t->BtnMenuChangeRouterText(); break;
        case 6: _t->BtnMenuChangeRouterChannelText(); break;
        case 7: _t->BtnMenuChangeSpeedText(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddMenu::addRouterSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AddMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddMenu::addPCSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AddMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddMenu::changeChannel)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AddMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddMenu::OffOnRouterWave)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AddMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_AddMenu.data,
    qt_meta_data_AddMenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AddMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddMenu.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AddMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void AddMenu::addRouterSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AddMenu::addPCSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AddMenu::changeChannel()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AddMenu::OffOnRouterWave()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
