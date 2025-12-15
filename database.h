#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QPair>
#include <QStandardItemModel>

class Database
{
    static Database Db;
    QSqlDatabase *Instance;
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database() = default;

public:

    static Database& GetInstance();
    bool ConnectToDatabase(QString DbName = "UsersData.sqlite");
    void CloseConnection();
    void FirstDatabaseConnection();
    bool CreateAccount(QString Login, QString Password);
    bool LogInToAccount(QString Login, QString Password);
    QPair<QString, QString> GetRememberMeAccountData();
    bool SaveArrayToDb(QStandardItemModel *Array, QString Login);
    void DeleteGuestData();
    bool GetUserArrays(QStandardItemModel *UserArray, QString Login);
    bool ShowCurrentArray(QStandardItemModel *CurrentArray, int ArrayId, int &NumberOfArrayElements);
    bool UpdateArray(QStandardItemModel *CurrentArray, int ArrayId);
    bool DeleteArray(int ArrayId);
    bool ThisAccountIsExists(QString Login);

};

#endif // DATABASE_H
