#include "example.h"
#include <QTimer>
#include <QDebug>
#include <QMetaObject>


/**
 * Constructor creates some QTimers then uses connectSlotsByName to
 * set up the connections instead of QObject::connect(). Note that we
 * don't need to store QTimer*'s to do this, which could be handy in
 * some applications.
 */

Example::Example (QObject *parent) :
    QObject(parent)
{

    setupTimer(1100, "timer1");
    setupTimer(1700, "timer2");
    setupTimer(2300, "timer3");

    // We don't create a timer named "notimer", this is to show the type
    // of warning connectSlotsByName() will generate if no matching object
    // or signal is found.

    QMetaObject::connectSlotsByName(this);

}


/**
 * Convenience function to create a periodic QTimer, set its name, and
 * start it with the specified interval (milliseconds).
 */

void Example::setupTimer (int interval, QString name) {

    QTimer *timer = new QTimer(this); // <- Part of this object tree.
    timer->setObjectName(name);       // <- Name will match slot names.
    timer->start(interval);

}


void Example::on_timer1_timeout () {

    qDebug("timer1 timeout");

}


void Example::on_timer2_timeout () {

    qDebug("timer2 timeout");

}


void Example::on_timer3_timeout () {

    qDebug("timer3 timeout");

}


void Example::on_notimer_timeout () {

    // In this example, this slot won't be connected to anything.

}
