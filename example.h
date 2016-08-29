#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>

class Example : public QObject {
    Q_OBJECT

public:

    explicit Example (QObject *parent = 0);

private slots:

    // These will be automatically connected by connectNamedSlots()
    void on_timer1_timeout ();
    void on_timer2_timeout ();
    void on_timer3_timeout ();
    void on_notimer_timeout (); // <- for demonstrating runtime warnings

private:

    void setupTimer (int interval, QString name);
    
};

#endif // EXAMPLE_H
