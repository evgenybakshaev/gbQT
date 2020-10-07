#include "shortcuts.h"
#include "ui_shortcuts.h"
#include "mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
Shortcuts::Shortcuts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Shortcuts),
    model(new QStandardItemModel)
{
    ui->setupUi(this);

    ui->tableView->setModel(model);

}

Shortcuts::~Shortcuts()
{
    delete ui;
    delete model;
}

void Shortcuts::keyPressEvent(QKeyEvent *event)
{
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedIndexes();
    //int row;
    foreach (QModelIndex index, indexList) {
        //row = index.row();
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        int keyInt = keyEvent->key();
        Qt::Key key = static_cast<Qt::Key>(keyInt);
        if(key == Qt::Key_unknown){
            //qDebug() << "Unknown key from a macro probably";
            return;
        }
        // the user have clicked just and only the special keys Ctrl, Shift, Alt, Meta.
        if(key == Qt::Key_Control ||
            key == Qt::Key_Shift ||
            key == Qt::Key_Alt ||
            key == Qt::Key_Meta)
        {
            //qDebug() << "Single click of special key: Ctrl, Shift, Alt or Meta";
            //qDebug() << "New KeySequence:" << QKeySequence(keyInt).toString(QKeySequence::NativeText);
            return;
        }

        // check for a combination of user clicks
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        QString keyText = keyEvent->text();
        // if the keyText is empty than it's a special key like F1, F5, ...
        //qDebug() << "Pressed Key:" << keyText;

        QList<Qt::Key> modifiersList;
        if(modifiers & Qt::ShiftModifier)
            keyInt += Qt::SHIFT;
        if(modifiers & Qt::ControlModifier)
            keyInt += Qt::CTRL;
        if(modifiers & Qt::AltModifier)
            keyInt += Qt::ALT;
        if(modifiers & Qt::MetaModifier)
            keyInt += Qt::META;

        //qDebug() << "New KeySequence:" << QKeySequence(keyInt).toString(QKeySequence::NativeText);
                    ;

        model->setData(index, QKeySequence(keyInt).toString(QKeySequence::NativeText));
    }



}

void Shortcuts::on_pushButton_2_released()
{
    this->close();
}

void Shortcuts::on_pushButton_released()
{
    QList<QString> list;
    for(int i=0; i < model->rowCount(); ++i)
        list << model->item(i,1)->text();
    emit shortcuts_changed(list);
    this->close();
}
