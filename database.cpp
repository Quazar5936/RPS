#include "database.h"


Database& Database::GetInstance(){

    static Database Db;
    return Db;
}

bool Database::ConnectToDatabase(QString DbName){

    if (Instance!= nullptr){
        return true;
    }
    Instance = new QSqlDatabase;
    *Instance = QSqlDatabase::addDatabase("QSQLITE", "Conn1");
    Instance->setDatabaseName(DbName);
    return Instance->open();

}


void Database::FirstDatabaseConnection(){

    QSqlQuery QueryToCreateTableAccount(*Instance);
    QString QueryStringForCreateTableAccount = "CREATE TABLE IF NOT EXISTS Account ("
                                               "    Login TEXT PRIMARY KEY,"
                                               "    Password TEXT);";
    bool QueryWasExecuted = QueryToCreateTableAccount.exec(QueryStringForCreateTableAccount);

    if (!QueryWasExecuted){

        return;
    }

    QSqlQuery QueryToCreateTableArray(*Instance);
    QString QueryStringForCreateTableArray = "CREATE TABLE IF NOT EXISTS Array ("
                                             "    IdOfArray INTEGER PRIMARY KEY AUTOINCREMENT,"
                                             "    Login TEXT,"
                                             "      Array TEXT,"
                                             "      Date  TEXT,"
                                             "      FOREIGN KEY(Login) REFERENCES Account(Login)"
                                             "      ON DELETE CASCADE"
                                             "      ON UPDATE CASCADE);";
    QueryWasExecuted = QueryToCreateTableArray.exec(QueryStringForCreateTableArray);

    if (!QueryWasExecuted){

        return;
    }

    QSqlQuery QueryToCheckGuest(*Instance);
    QueryWasExecuted = QueryToCheckGuest.exec("SELECT COUNT(*) FROM Account WHERE Login = 'Guest';");

    if (!QueryWasExecuted){
        return;
    }

    QueryToCheckGuest.next();
    int CountOfGuestCheck = QueryToCheckGuest.value(0).toInt();

    if (CountOfGuestCheck == 1){
        return;
    }


    QSqlQuery QueryToCreateGuest(*Instance);

    QueryToCreateGuest.exec("INSERT INTO Account (Login, Password) VALUES ('Guest', '123');");



}

void Database::CloseConnection(){
    if (Instance->isOpen()){

        Instance->close();
    }

    delete Instance;
    Instance = nullptr;

    if (QSqlDatabase::contains("Conn1")){
        QSqlDatabase::removeDatabase("Conn1");
    }

}


bool Database::CreateAccount(QString Login, QString Password){
    if (Login.trimmed().isEmpty() || Password.trimmed().isEmpty()){
        return false;
    }

    QSqlQuery QueryToCreateNewAccount(*Instance);
    QueryToCreateNewAccount.prepare("INSERT INTO Account (Login, Password) VALUES (?, ?);");
    QueryToCreateNewAccount.addBindValue(Login);
    QueryToCreateNewAccount.addBindValue(Password);

    return QueryToCreateNewAccount.exec();
}

bool Database::LogInToAccount(QString Login, QString Password){

    if (Login.trimmed().isEmpty() || Password.trimmed().isEmpty()){
        return false;
    }

    QSqlQuery QueryToLogIn(*Instance);
    QueryToLogIn.prepare("SELECT COUNT(*) FROM Account WHERE Login = ? AND Password = ?;");
    QueryToLogIn.addBindValue(Login);
    QueryToLogIn.addBindValue(Password);

    bool QueryWasExecuted = QueryToLogIn.exec();

    if (!QueryWasExecuted){

        return false;
    }

    QueryToLogIn.next();
    int AccountCheck = QueryToLogIn.value(0).toInt();

    if (AccountCheck == 0){
        return false;
    }

    return true;

}



bool Database::SaveArrayToDb(QStandardItemModel* Array, QString Login)
{
    if (!Array->rowCount()){
        return false;
    }

    QString ArrayStr = "";

    for(int i = 0;i < Array->rowCount();i++){
        QModelIndex iIdx = Array->index(i,0);

        if (iIdx.isValid()){
            ArrayStr += Array->data(iIdx).toString();
            ArrayStr += " ";
        }
    }


    QSqlQuery SaveArrayQuery(*Instance);
    SaveArrayQuery.prepare("INSERT INTO Array (Login, Array, Date) VALUES (?, ?, ?);");

    if (!Login.isEmpty()){
        SaveArrayQuery.addBindValue(Login);
    }
    else{
        SaveArrayQuery.addBindValue("Guest");
    }

    SaveArrayQuery.addBindValue(ArrayStr);
    QString DateTime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    SaveArrayQuery.addBindValue(DateTime);

    return SaveArrayQuery.exec();


}

void Database::DeleteGuestData(){

    QSqlQuery QueryToDeleteGuestData(*Instance);
    QueryToDeleteGuestData.prepare("DELETE FROM Array WHERE Login = 'Guest';");
    QueryToDeleteGuestData.exec();
}

 bool Database::GetUserArrays(QStandardItemModel *UserArray, QString Login){
    QSqlQuery QueryToGetUserArrays(*Instance);

    QueryToGetUserArrays.prepare("SELECT * FROM Array WHERE Login = ?;");

    QueryToGetUserArrays.addBindValue(Login);

    bool QueryWasExecuted = QueryToGetUserArrays.exec();

    if (!QueryWasExecuted){

        return false;
    }

    int j = 0;
    while (QueryToGetUserArrays.next()){
        QString IdOfArray = QueryToGetUserArrays.value(0).toString();
        QString UserArrayStr = QueryToGetUserArrays.value(2).toString();
        QString DateTime = QueryToGetUserArrays.value(3).toString();
        int NumberOfArrayElements = 0;

        QStandardItem * ItemOfIdOfArray = new QStandardItem(IdOfArray);

        for(qsizetype i = 0;i < UserArrayStr.length();i++){
            if (UserArrayStr[i] == " "){
                ++NumberOfArrayElements;
            }
        }

        QStandardItem * ItemOfNumberOfElementsOfUserArray = new QStandardItem(QString("%0").arg(NumberOfArrayElements));
        QStandardItem * ItemOfDateTime = new QStandardItem(DateTime);
        ItemOfIdOfArray->setEditable(false);
        ItemOfNumberOfElementsOfUserArray->setEditable(false);
        ItemOfDateTime->setEditable(false);

        UserArray->setItem(j, 0, ItemOfIdOfArray);
        UserArray->setItem(j, 1, ItemOfNumberOfElementsOfUserArray);
        UserArray->setItem(j, 2,  ItemOfDateTime);

        ++j;

    }

    UserArray->setHeaderData(0, Qt::Horizontal, "Id массива");
    UserArray->setHeaderData(1, Qt::Horizontal, "Кол-во элементов");
    UserArray->setHeaderData(2, Qt::Horizontal, "Дата правки");
    qDebug() << j;
    return true;

}

 bool Database::ShowCurrentArray(QStandardItemModel *CurrentArray, int ArrayId,int &NumberOfArrayElements){

     QSqlQuery QueryForGettingArrayById(*Instance);
     QueryForGettingArrayById.prepare("SELECT Array FROM Array WHERE IdOfArray = ?;");
     QueryForGettingArrayById.addBindValue(QString::number(ArrayId));

     bool QueryWasExecuted = QueryForGettingArrayById.exec();

     if (!QueryWasExecuted){
         return false;
     }

     QueryForGettingArrayById.next();
     QString ArrayStr = QueryForGettingArrayById.value(0).toString();
     NumberOfArrayElements = 0;
     QString ElementOfArrayStr = "";
     for(qsizetype i = 0;i < ArrayStr.length();i++){
         if (ArrayStr[i] != " "){
             ElementOfArrayStr += ArrayStr[i];
         }
         if (ArrayStr[i] == " " && !ElementOfArrayStr.isEmpty()){

             QStandardItem * ElementOfArray = new QStandardItem(ElementOfArrayStr);
             ElementOfArray->setEditable(true);
             CurrentArray->setItem(NumberOfArrayElements ,ElementOfArray);
             ElementOfArrayStr = "";
             ++NumberOfArrayElements;
         }

     }

     return true;

 }

 bool Database::UpdateArray(QStandardItemModel *Array, int ArrayId){

    if (!Instance->isOpen()){
         return false;
    }


     QString ArrayStr = "";
     for(qsizetype i = 0;i < Array->rowCount();i++){
         QModelIndex CurrentArrayIndex = Array->index(i,0);
         ArrayStr += Array->data(CurrentArrayIndex).toString();
         if (i + 1!= Array->rowCount()){
             ArrayStr += " ";
         }
     }

     QSqlQuery QueryToUpdateCurrentArray(*Instance);
     QueryToUpdateCurrentArray.prepare("UPDATE ARRAY SET Array =  ? WHERE IdOfArray = ?;");
     QueryToUpdateCurrentArray.addBindValue(ArrayStr);
     QueryToUpdateCurrentArray.addBindValue(ArrayId);
     qDebug() << ArrayId;
     bool QueryWasExecuted = QueryToUpdateCurrentArray.exec();
     return QueryWasExecuted;


 };


 bool Database::DeleteArray(int ArrayId){
     if (!Instance->isOpen()){
         return false;
     }

     QSqlQuery QueryToDeleteArray(*Instance);
     QueryToDeleteArray.prepare("DELETE FROM ARRAY WHERE IdOfArray = ?");
     QueryToDeleteArray.addBindValue(ArrayId);
     return QueryToDeleteArray.exec();

 }

 bool Database::ThisAccountIsExists(QString Login){
     if (!Instance->isOpen()){
         return false;
     }

     QSqlQuery QueryToCheckAccount(*Instance);
     QueryToCheckAccount.prepare("SELECT COUNT(*) FROM Account WHERE Login = ?;");
     QueryToCheckAccount.addBindValue(Login);
     QueryToCheckAccount.exec();

     QueryToCheckAccount.next();

     int AccountCheck =  QueryToCheckAccount.value(0).toInt();
     qDebug() << AccountCheck;
     if (AccountCheck == 0){
         return false;
     }

     return true;
 }
