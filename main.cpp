#include <QtCore>

/// A shorthand to create a named instance of a QObject-deriving class
template <typename T> class Named : public T {
public:
    template<typename... Args> Named(const char * name, Args&&... args) :
        T(std::forward<Args>(args)...) { this->setObjectName(QString::fromUtf8(name)); }
};

class Example : public QObject {
    Q_OBJECT
    Named<QTimer> timer1{"timer1", this};
    Named<QTimer> timer2{"timer2", this};
    Named<QTimer> timer3{"timer3", this};
private slots:
    // These will be automatically connected by connectNamedSlots()
    void on_timer1_timeout() {
        qDebug("timer1 timeout");
    }
    void on_timer2_timeout() {
        qDebug("timer2 timeout");
    }
    void on_timer3_timeout() {
        qDebug("timer3 timeout");
    }
    /// In this example, this slot won't be connected to anything,
    /// to demonstrate runtime warnings.
    void on_notimer_timeout() {}
public:
    /// Starts the timers then uses connectSlotsByName to
    /// set up the connections instead of QObject::connect().
    explicit Example (QObject *parent = nullptr) : QObject(parent)
    {
        // Start the timers
        for (auto child : findChildren<QTimer*>()) child->start(1000);
        // We don't create a timer named "notimer", this is to show the type
        // of warning connectSlotsByName() will generate if no matching object
        // or signal is found.
        QMetaObject::connectSlotsByName(this);
    }
};

int main (int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    Example x;
    return a.exec();
}

#include "main.moc"
