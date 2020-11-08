#include "formfilesystem.h"
#include "ui_formfilesystem.h"
#include <QDir>
#include <QDebug>
#include <QStandardItemModel>

FormFileSystem::FormFileSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormFileSystem),
    dirModel(nullptr),
    fileModel(nullptr),
    searchModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    QFileInfoList list = QDir::drives();
    QFileInfoList::const_iterator listdisk = list.begin();
    int amount = list.count();
    for (int i = 0; i < amount; i++)
    {
        ui->disckSelBox->addItem(listdisk->path());
        listdisk++;
    }
    if (amount > 0)
    {
        rebuildModel(list.at(0).path());
    }
}

FormFileSystem::~FormFileSystem()
{
    if (findThread != nullptr)       // При завершении нужно остановить поток, если он существует
       {
           if (findThread->isRunning()) // Проверяем, работает ли поток
           {
               findThread->findStop();  // Меняем флаг для завершения всех циклов потока
               findThread->terminate(); // Ожидаем завершения потока
           }
           findThread.reset();          // Сбрасываем поток, вызывая деструктор
       }
    delete ui;
}

void FormFileSystem::setDirModel(QFileSystemModel *newmodel)
{
    ui->tree->setModel(newmodel);
    dirModel = newmodel;
    ui->tree->setColumnHidden(1,true);
    ui->tree->setColumnHidden(2,true);
    ui->tree->setColumnHidden(3,true);
}
void FormFileSystem::setFileModel(QFileSystemModel *newmodel)
{
    ui->listView->setModel(newmodel);
    fileModel = newmodel;
}

void FormFileSystem::rebuildModel(QString str)
{
    curretnPath = str;
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    setDirModel(model);
    ui->tree->setRootIndex(dirModel->setRootPath(str));
    ui->tree->setColumnWidth(0,200);

    rebuildFileModel(str);
    ui->lineEdit->setText(str);
}

void FormFileSystem::rebuildFileModel(QString str)
{
    QFileSystemModel *fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::AllDirs | QDir::AllEntries | QDir::NoDotAndDotDot);
    setFileModel(fileModel);
    ui->listView->setRootIndex(fileModel->setRootPath(str));
}

void FormFileSystem::on_disckSelBox_activated(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void FormFileSystem::on_tree_clicked(const QModelIndex &index)
{
    ui->lineEdit->setText(dirModel->filePath(index));
    rebuildFileModel(dirModel->filePath(index));
    //ui->listView->setRootIndex(fileModel->setRootPath(dirModel->filePath(index)));
}

void FormFileSystem::on_lineEdit_2_returnPressed()
{
    if (findThread.get())
    {
        findThread->findStop();
        findThread->terminate();
        findThread.reset();
        return;
    }
    findThread = QSharedPointer<ThreadFinder>::create(ui->lineEdit->text() + "/", ui->lineEdit_2->text());
    findThread->start(QThread::NormalPriority);
    connect(findThread.get(), SIGNAL(stopedThread()), this, SLOT(deleteThread()));
    //connect(findThread.get(), SIGNAL(writeFoundPath(QString)), this, SLOT(setCurrentPath(QString)));
    connect(findThread.get(), SIGNAL(findFile(QString)), this, SLOT(setCurrentPath(QString)));
    searchModel->clear();
    ui->listView->setModel(searchModel);
}

void FormFileSystem::deleteThread()
{
    findThread.reset();
}

void FormFileSystem::setCurrentPath(QString file)
{
    //qDebug() << file;
    searchModel->appendRow(new QStandardItem(file));
}
