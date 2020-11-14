#ifndef BASEREADER_H
#define BASEREADER_H

#include <QObject>
#include <QFile>

class BaseReader : public QObject
{
   Q_OBJECT
public:
   explicit BaseReader();
   virtual ~BaseReader();
   Q_INVOKABLE
   void loadBase();
   Q_INVOKABLE
   void getNextRecord();
   Q_INVOKABLE
   void writeNewInformation(QString, QString, QString);
private:
   QFile *file;
signals:
   void initEnd(bool succeed);
   void loadTown(QString name, QString date, QString progress);
private slots:
};


#endif // BASEREADER_H
