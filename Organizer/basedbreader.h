#ifndef BaseDBReader_H
#define BaseDBReader_H

#include <QObject>
#include <QFile>
#include <QSqlDatabase>

class BaseDBReader : public QObject
{
   Q_OBJECT
public:
   explicit BaseDBReader();
   virtual ~BaseDBReader();
   Q_INVOKABLE
   void loadBase();
   Q_INVOKABLE
   void getRecords();
   Q_INVOKABLE
   void writeNewInformation(QString, QString, QString);
   Q_INVOKABLE
   bool removeRecord(const int id);
private:
   QSqlDatabase db;
signals:
   void initEnd(bool succeed);
   void loadTask(int id, QString name, QString date, QString progress);
   void deleteTask();
private slots:
};


#endif // BaseDBReader_H
