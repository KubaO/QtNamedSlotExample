#include <QtCore>

/// A shorthand to create a named instance of a QObject-deriving class
template <typename T> class Named : public T {
public:
    template<typename... Args> Named(const char * name, Args&&... args) :
        T(std::forward<Args>(args)...) { this->setObjectName(QString::fromUtf8(name)); }
};

/// A source of signals.
struct SignalSource : public QObject {
    Q_SIGNAL void signal();
    explicit SignalSource(QObject * parent = nullptr) : QObject{parent} {}
    Q_OBJECT
};

class Example : public QObject {
    Q_OBJECT
    int count = 0;
    Named<SignalSource> object1{"object1", this};
    Named<SignalSource> object2{"object2", this};
    Named<SignalSource> object3{"object3", this};
private slots:
    // These will be automatically connected by connectNamedSlots()
    void on_object1_signal() { ++ count; }
    void on_object2_signal() { ++ count; }
    void on_object3_signal() { ++ count; }
    /// In this example, this slot won't be connected to anything,
    /// to demonstrate runtime warnings.
    void on_noobject_signal() { ++count; }
public:
    /// Uses connectSlotsByName to set up the connections instead of QObject::connect().
    explicit Example (QObject *parent = nullptr) : QObject{parent}
    {
        // We don't create an object named "noobject", this is to show the type
        // of warning connectSlotsByName() will generate if no matching object
        // or signal is found.
        QMetaObject::connectSlotsByName(this);
        Q_ASSERT(count == 0);
        emit object1.signal();
        emit object2.signal();
        emit object3.signal();
        Q_ASSERT(count == 3);
    }
};

int main () {
    Example x;
}
#include "main.moc"
