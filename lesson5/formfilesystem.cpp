#include "formfilesystem.h"
#include "ui_formfilesystem.h"
#include <QDir>

FormFileSystem::FormFileSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormFileSystem),
    model(nullptr)
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
    delete ui;
}

void FormFileSystem::setNewModel(QFileSystemModel *newmodel)
{
    ui->tree->setModel(newmodel);
    model = newmodel;
}

void FormFileSystem::rebuildModel(QString str)
{
    curretnPath = str;
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    setNewModel(model);
    ui->tree->setRootIndex(model->setRootPath(str));
    ui->tree->setColumnWidth(0,200);
    ui->lineEdit->setText(str);
}

void FormFileSystem::on_disckSelBox_activated(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void FormFileSystem::on_tree_clicked(const QModelIndex &index)
{
    ui->lineEdit->setText(model->filePath(index));
}
