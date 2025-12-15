#ifndef SeeSavedArraysWindow_H
#define SeeSavedArraysWindow_H

#include <QDialog>
#include <QStandardItemModel>
#include "database.h"

namespace Ui {
class SeeSavedArraysWindow;
}

class SeeSavedArraysWindow : public QDialog
{
    Q_OBJECT
    QStandardItemModel* CurrentArray;
    QStandardItemModel* ArrayToSeeDataFromDb;
    QString Login;
    int ArrayId;
    int NumberOfArrayElements;
    void GetUserArrays();
    bool ShowCurrentArray(int ArrayId);
    void CheckCurrentArrayTableView();
    void MoveDataFromCurrentArrayToMainWindowArray(QStandardItemModel* MainWindowArray, int *NumberOfArrayElementsMainWindow);

signals:
    void NumberOfArrayElementsChanged();
public:
    explicit SeeSavedArraysWindow(QWidget *parent,QStandardItemModel* MainWindowArray, QString UserLogin = "Guest",int *NumberOfArrayElementsMainWindow = nullptr);
    ~SeeSavedArraysWindow();

private slots:
    void on_SeeArrayButton_clicked();

    void on_UpdateArrayButton_clicked();

    void on_PlusButton_clicked();

    void on_MinusButton_clicked();

    void on_NumberOfArrayElementsLineEdit_editingFinished();

    void on_DeleteArrayButton_clicked();

private:
    Ui::SeeSavedArraysWindow *ui;
};
void ShowMessageBoxWithOK(QWidget *Parent, QString WindowTitle, QString Message, QString FontName, int FontSize );
#endif // SeeSavedArraysWindow_H
