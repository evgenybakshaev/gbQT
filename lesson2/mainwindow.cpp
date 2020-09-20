#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
//#include <Qlist>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    symb["RUB"] = "₽";
    symb["EURO"] = "€";
    symb["PROM"] = "‰";
    symb["COPY"] = "©";

    itemModel = new CustomListModel(this);
    ui->listView->setModel(itemModel);
    itemModel->appendRow(new QStandardItem(QIcon(":resource/img/C-logo.png"), "C++"));
    itemModel->appendRow(new QStandardItem(QIcon(":resource/img/csharp-logo.png"), "C#"));
    itemModel->appendRow(new QStandardItem(QIcon(":resource/img/java-logo.png"),"Java"));
    itemModel->appendRow(new QStandardItem(QIcon(":resource/img/php-logo.png"), "PHP"));
    itemModel->appendRow(new QStandardItem(QIcon(":resource/img/python-logo.png"), "Python"));
    itemModel->appendRow(new QStandardItem(QIcon(":resource/img/javascript-logo.png"),"Java Script"));

    listGridSize = ui->listView->gridSize();
    iconGridSize = QSize(50,60);

    tableModel = new QStandardItemModel(this);
    ui->tableView->setModel(tableModel);
    tableModel->setColumnCount(4);
    tableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("№"));
    tableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Имя компьютера"));
    tableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("IP адресс"));
    tableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("MAC адресс"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QList<QStandardItem*>list;
    list.append(new QStandardItem("1"));
    list.append(new QStandardItem("ПК 1"));
    list.append(new QStandardItem("192.168.1.1"));
    list.append(new QStandardItem("00:00:0A:BB:28:FC"));
    tableModel->appendRow(list);
    QList<QStandardItem*>list1;
    list1.append(new QStandardItem("2"));
    list1.append(new QStandardItem("ПК 2"));
    list1.append(new QStandardItem("192.168.1.2"));
    list1.append(new QStandardItem("00:00:0A:AB:28:FC"));
    tableModel->appendRow(list1);
    QList<QStandardItem*>list2;
    list2.append(new QStandardItem("3"));
    list2.append(new QStandardItem("ПК 3"));
    list2.append(new QStandardItem("192.168.1.3"));
    list2.append(new QStandardItem("00:00:0A:AB:28:FD"));
    tableModel->appendRow(list2);
}

MainWindow::~MainWindow()
{
    if(itemModel)
        delete itemModel;
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText(); // получаем текст виджета
    QRegExp rx("#@(\\w+)@");
    int pos = 0;
    while((pos = rx.indexIn(str, pos)) != -1){
        if(symb.contains(rx.cap(1))){
            ui->plainTextEdit->find(rx, QTextDocument::FindBackward);
            ui->plainTextEdit->textCursor().insertText(symb[rx.cap(1)]);
        }
        pos += rx.matchedLength();
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if((Qt::CheckState)arg1 == Qt::Checked){
        ui->listView->setViewMode(QListView::ListMode);
        ui->listView->setGridSize(listGridSize);
    }
    else{
        ui->listView->setViewMode(QListView::IconMode);
        ui->listView->setGridSize(iconGridSize);
    }
}

void MainWindow::on_pushButton_2_released()
{
    itemModel->appendRow(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),""));
}

void MainWindow::on_pushButton_3_released()
{
    itemModel->removeRow(ui->listView->currentIndex().row());
}

void MainWindow::on_pushButton_released()
{
    int col = tableModel->columnCount();
    foreach(auto index, ui->tableView->selectionModel()->selection().indexes()) {
        int row = index.row();
        for (int i = 0; i < col; ++i) {
            tableModel->setData(tableModel->index(row,i), QColor(Qt::green), Qt::BackgroundRole);
        }
    }

}

void MainWindow::on_pushButton_4_released()
{
    int col = tableModel->columnCount();
    foreach(auto index, ui->tableView->selectionModel()->selection().indexes()) {
        int row = index.row();
        for (int i = 0; i < col; ++i) {
            tableModel->setData(tableModel->index(row,i), QColor(Qt::white), Qt::BackgroundRole);
        }
    }
}
