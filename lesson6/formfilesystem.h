#ifndef FORMFILESYSTEM_H
#define FORMFILESYSTEM_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QFileSystemModel>
#include <QApplication>

namespace Ui {
class FormFileSystem;
}

class FormFileSystem : public QWidget
{
    Q_OBJECT

public:
    explicit FormFileSystem(QWidget *parent = nullptr);
    ~FormFileSystem();

private:
    Ui::FormFileSystem *ui;
public:
    void clearTree();
    QFileSystemModel *getCurrentModel()const
    {
       return model;
    }
    void setNewModel(QFileSystemModel *newmodel);
    void rebuildModel(QString str);
private:

private slots:
   void on_disckSelBox_activated(int index);

   void on_tree_clicked(const QModelIndex &index);

private:
   QFileSystemModel *model;
   QString curretnPath;
protected:
};

#endif // FORMFILESYSTEM_H
