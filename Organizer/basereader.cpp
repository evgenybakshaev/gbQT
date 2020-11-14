#include "basereader.h"
#include <QDataStream>

BaseReader::BaseReader() : file(nullptr)
{
}
BaseReader::~BaseReader()
{
   if (file) file->close();
}

void BaseReader::loadBase()
{
   file = new QFile("./testbase.bin", this);                 // Файл с данными
                                                             // о городах
   if (!file) return;
   if (!file->open(QIODevice::ReadWrite))
   {
           emit initEnd(false);
           return;
   }
   emit initEnd(true);
}

void BaseReader::getNextRecord()                              // Читаем запись
                                                              // о следующем
                                                              // городе
{
   if (file->atEnd()) return;
   QDataStream stream(file);
   int len = 0;
   stream.readRawData((char*)&len, sizeof len);
   QByteArray b;
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString name = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString date = QString::fromUtf8(b);

   stream.readRawData((char*)&len, sizeof len);
   b.resize(len);
   stream.readRawData(b.data(), len);
   QString progress = QString::fromUtf8(b);
   emit loadTown(name, date, progress);
}

void BaseReader::writeNewInformation(QString name, QString date, QString progress) // Записываем
{
   QDataStream stream(file);
   auto bytes = name.toUtf8();
   int len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
   bytes = date.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
   bytes = progress.toUtf8();
   len = bytes.length();
   stream.writeRawData((char*)&len, sizeof len);
   stream.writeRawData(bytes.data(), len);
}
