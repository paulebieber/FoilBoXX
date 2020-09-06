/****************************************************************************
** Meta object code from reading C++ file 'AirfoilInterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/AirfoilInterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AirfoilInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AirfoilInterface_t {
    QByteArrayData data[8];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AirfoilInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AirfoilInterface_t qt_meta_stringdata_AirfoilInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AirfoilInterface"
QT_MOC_LITERAL(1, 17, 7), // "changed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "activated"
QT_MOC_LITERAL(4, 36, 11), // "recursively"
QT_MOC_LITERAL(5, 48, 13), // "calcAllPolars"
QT_MOC_LITERAL(6, 62, 12), // "setThickness"
QT_MOC_LITERAL(7, 75, 9) // "thickness"

    },
    "AirfoilInterface\0changed\0\0activated\0"
    "recursively\0calcAllPolars\0setThickness\0"
    "thickness"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AirfoilInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    7,

       0        // eod
};

void AirfoilInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AirfoilInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->activated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->calcAllPolars(); break;
        case 3: _t->setThickness((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AirfoilInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirfoilInterface::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AirfoilInterface::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirfoilInterface::activated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AirfoilInterface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AirfoilInterface::calcAllPolars)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AirfoilInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<HierarchyElement::staticMetaObject>(),
    qt_meta_stringdata_AirfoilInterface.data,
    qt_meta_data_AirfoilInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AirfoilInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AirfoilInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AirfoilInterface.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Airfoil"))
        return static_cast< Airfoil*>(this);
    return HierarchyElement::qt_metacast(_clname);
}

int AirfoilInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = HierarchyElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AirfoilInterface::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AirfoilInterface::activated(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AirfoilInterface::calcAllPolars()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
