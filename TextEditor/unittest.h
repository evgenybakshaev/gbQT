#ifndef UNITTEST_H
#define UNITTEST_H

#include <QObject>
#include <QtTest/QTest>

class UnitTest : public QObject
{
    Q_OBJECT
public:
    explicit UnitTest(QObject *parent = nullptr);

private slots:
    void testChangeTheme();
    void testOn_actioninsertDateTime_triggered();
};

#endif // UNITTEST_H
