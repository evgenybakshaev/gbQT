#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include <QDialog>
#include <QList>
#include "QStandardItemModel"

namespace Ui {
class Shortcuts;
}

class Shortcuts : public QDialog
{
    Q_OBJECT

public:
    explicit Shortcuts(QWidget *parent = nullptr);
    ~Shortcuts();
protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Shortcuts *ui;
public:
    QStandardItemModel *model;
private slots:
    void on_pushButton_2_released();

    void on_pushButton_released();

public:
signals:
    void shortcuts_changed(QList<QString>);
};

#endif // SHORTCUTS_H
