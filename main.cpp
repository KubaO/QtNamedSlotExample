#include <QtCore>

class Example : public QObject {
    Q_OBJECT
    /// Create a periodic QTimer, set its name, and
    /// start it with the specified interval (milliseconds).
    void setupTimer(int interval, const QString & name) {
        QTimer *timer = new QTimer(this); // <- Part of this object tree.
        timer->setObjectName(name);       // <- Name will match slot names.
        timer->start(interval);
    }
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
    /// Creates some QTimers then uses connectSlotsByName to
    /// set up the connections instead of QObject::connect(). Note that we
    /// don't need to store QTimer*'s to do this, which could be handy in
    /// some applications.
    explicit Example (QObject *parent = nullptr) : QObject(parent)
    {
        setupTimer(1100, "timer1");
        setupTimer(1700, "timer2");
        setupTimer(2300, "timer3");
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
