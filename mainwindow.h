#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QCloseEvent>
#include "loginwindow.h"
#include "registerwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT
    QString Login;
    QString Password;
    QStandardItemModel* Array;
    QStandardItemModel* SortedArray;
    LoginWindow *ParentLoginWindow;
    int NumberOfArrayElements;
    void CopyArray();
    void CheckArrayListView();
    void CheckSortedArrayListView();
    void GetRememberMeAccountData();


public slots:
    void ChangeNumberOfArrayElements();

public:
    explicit MainWindow(LoginWindow *parent = nullptr, QString NewLogin = "Guest", QString NewPassword = "12345", bool NotGuest = false);
    ~MainWindow();
    bool Registered;

private slots:
    void on_LoadArraysButton_clicked();

    void on_NumberOfArrayElementsLineEdit_editingFinished();

    void on_PlusButton_clicked();

    void on_MinusButton_clicked();

    void on_RandomValuesButton_clicked();

    void on_SortButton_clicked();

    void on_InfoButton_clicked();

    void on_QuitButton_clicked();

    void on_DarkThemeButton_clicked();

    void on_SaveArrayButton_clicked();

    void on_SaveSortedArrayButton_clicked();

    void on_LeaveButton_clicked();

private:
    Ui::MainWindow *ui;
};
void SwitchTheme();
void ShowMessageBoxWithOK(QWidget *Parent, QString WindowTitle, QString Message, QString FontName, int FontSize );
bool CombSort(QStandardItemModel* SortedArray,int NumberOfArrayElements );

#endif // MAINWINDOW_H
