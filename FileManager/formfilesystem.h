#ifndef FORMFILESYSTEM_H
#define FORMFILESYSTEM_H

#include <QWidget>
#include <QGridLayout>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QApplication>
#include <QSharedPointer>
#include "threadfinder.h"

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
    QSharedPointer<ThreadFinder>findThread;
public:
    void clearTree();
    QFileSystemModel *getDirModel()const
    {
       return dirModel;
    }
    void setDirModel(QFileSystemModel *newmodel);
    QFileSystemModel *getFileModel()const
    {
       return fileModel;
    }
    void setFileModel(QFileSystemModel *newmodel);
    void rebuildModel(QString str);
    void rebuildFileModel(QString str);
private:

private slots:
   void on_disckSelBox_activated(int index);
   void on_tree_clicked(const QModelIndex &index);

   void on_lineEdit_2_returnPressed();

private:
   QFileSystemModel *dirModel;
   QFileSystemModel *fileModel;
   QStandardItemModel *searchModel;
   QString curretnPath;
protected:
public slots:
   void deleteThread();             // Удаляем поток при завершение работы
   void setCurrentPath(QString);  // Выводим текущий каталог поиска
   //void genStringPathFile(QString); // Выводим найденный файл
   //void finishThread();
};

#endif // FORMFILESYSTEM_H
