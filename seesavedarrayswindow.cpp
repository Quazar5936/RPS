#include <QSqlDatabase>
#include <QTimer>
#include <QLineEdit>
#include "SeeSavedArraysWindow.h"
#include "ui_SeeSavedArraysWindow.h"


void SeeSavedArraysWindow::CheckCurrentArrayTableView(){
    QAbstractItemDelegate *CurrentTableDelegate = ui->CurrentArrayListview->itemDelegate();

    if (!CurrentTableDelegate){
        return;
    }

    QIcon MainIcon(":/Photos/main_icon.png");
    setWindowIcon(MainIcon);

    connect(CurrentTableDelegate, &QAbstractItemDelegate::commitData,
            [&](QWidget *editor) {

                if (auto lineEdit = qobject_cast<QLineEdit*>(editor)) {
                    QString TextFromLineEdit = lineEdit->text().trimmed();

                    if (TextFromLineEdit.isEmpty()) {

                        QModelIndex Index = ui->CurrentArrayListview->currentIndex();
                        if (Index.isValid()) {
                            CurrentArray->setData(Index, "0", Qt::EditRole);
                        }

                        return;
                    }

                    bool ThisIsNumber = false;
                    int NumberCheck = TextFromLineEdit.toInt(&ThisIsNumber);

                    if (!ThisIsNumber){

                        QModelIndex IndexOfNotCorrectNumber = ui->CurrentArrayListview->currentIndex();
                        if (!IndexOfNotCorrectNumber.isValid()) {

                            return;

                        }

                        QPersistentModelIndex pIndexOfNotCorrectNumber = IndexOfNotCorrectNumber;
                        QTimer::singleShot(0, this, [this, pIndexOfNotCorrectNumber]() {

                            if (!pIndexOfNotCorrectNumber.isValid()) {
                                return;
                            }

                            ShowMessageBoxWithOK(this, "Ошибка",
                                                 "Некорректное число. Установлено значение 0.",
                                                 "Verdana", 9);
                            CurrentArray->setData(pIndexOfNotCorrectNumber, "0");

                        });

                    }
                }

            });
}

void SeeSavedArraysWindow::MoveDataFromCurrentArrayToMainWindowArray(QStandardItemModel* MainWindowArray,int *NumberOfArrayElementsMainWindow){
    connect(ui->LoadArrayButton,&QPushButton::clicked, [this, MainWindowArray, NumberOfArrayElementsMainWindow](){
        if (MainWindowArray && CurrentArray->rowCount() != 0){
            *NumberOfArrayElementsMainWindow = NumberOfArrayElements;
            MainWindowArray->clear();
            for(qsizetype i = 0;i < CurrentArray->rowCount();i++){
                QModelIndex CurrentArrayIndex = CurrentArray->index(i,0);
                QStandardItem *NewItem = new QStandardItem(QString("%0").arg(CurrentArray->data(CurrentArrayIndex).toString()));
                NewItem->setEditable(true);
                MainWindowArray->setItem(i, NewItem);


            }
            emit NumberOfArrayElementsChanged();
            this->close();
        }

        else{
            ShowMessageBoxWithOK(this, "Ошибка",
                                 "Недостаточно элементов в массиве, добавьте еще для переноса",
                                 "Verdana", 9);
        }
    } );
}

SeeSavedArraysWindow::SeeSavedArraysWindow(QWidget *parent, QStandardItemModel* MainWindowArray, QString UserLogin, int *NumberOfArrayElementsMainWindow)
    : QDialog(parent)
    , ui(new Ui::SeeSavedArraysWindow)
{

    ui->setupUi(this);
    Login = UserLogin;
    ArrayId = 0;
    NumberOfArrayElements = 0;
    CurrentArray = new QStandardItemModel;
    ArrayToSeeDataFromDb = new QStandardItemModel;

    bool ArraysWereViewed = Database::GetInstance().GetUserArrays(ArrayToSeeDataFromDb, Login);

    if (!ArraysWereViewed){
        return;
    }

    CheckCurrentArrayTableView();
    MoveDataFromCurrentArrayToMainWindowArray(MainWindowArray,NumberOfArrayElementsMainWindow);

    QFont MainFont("Verdana", 9);
    MainFont.setBold(true);
    ui->ArraysTableview->horizontalHeader()->setFont(MainFont);
    ui->ArraysTableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ArraysTableview->setModel(ArrayToSeeDataFromDb);

    ui->CurrentArrayListview->setModel(CurrentArray);
    ui->ArraysTableview->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

}

SeeSavedArraysWindow::~SeeSavedArraysWindow()
{
    delete CurrentArray;
    CurrentArray = nullptr;
    delete ArrayToSeeDataFromDb;
    ArrayToSeeDataFromDb = nullptr;
    delete ui;
}

void SeeSavedArraysWindow::on_SeeArrayButton_clicked()
{
    if (ArrayToSeeDataFromDb->rowCount() > 0){
        CurrentArray->clear();
        QModelIndexList FirstSelectedRow = ui->ArraysTableview->selectionModel()->selectedRows();
        if (!FirstSelectedRow.isEmpty()){
            int SelectedRow = FirstSelectedRow.first().row();
            QModelIndex SelectedRowIndex = ArrayToSeeDataFromDb->index(SelectedRow, 0);
            bool ToIntIsCorrect = false;
            ArrayId = ArrayToSeeDataFromDb->data(SelectedRowIndex).toInt(&ToIntIsCorrect);

            if (!ToIntIsCorrect){
                ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось перенести массив в таблицу, попробуйте снова", "Verdana", 9);
                return;
            }

            bool CurrentArrayGetSuccessful = Database::GetInstance().ShowCurrentArray(CurrentArray, ArrayId, NumberOfArrayElements);
            if (!CurrentArrayGetSuccessful){
                ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось перенести массив в таблицу, попробуйте снова", "Verdana", 9);
                return;
            }


            ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));

        }
    }

    else{
        ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось перенести массив в таблицу, попробуйте снова", "Verdana", 9);
    }
}




void SeeSavedArraysWindow::on_UpdateArrayButton_clicked()
{
    if (NumberOfArrayElements == 0){
        ShowMessageBoxWithOK(this, "Ошибка, добавьте больше элементов", "Не удалось обновить массив, добавьте больше элементов", "Verdana", 9);
        return;
    }


    if (Database::GetInstance().UpdateArray(CurrentArray, ArrayId)){
        ShowMessageBoxWithOK(this, "Успех!!!", "Массив успешно обновлен", "Verdana", 9);
        return;
    }

    ShowMessageBoxWithOK(this, "Ошибка!!", "Массив не обновлен, попробуйте снова", "Verdana", 9);

}


void SeeSavedArraysWindow::on_PlusButton_clicked()
{
    if (NumberOfArrayElements + 1 > 100000){
        return;
    }

    ++NumberOfArrayElements;
    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));
    QStandardItem *NewRow = new QStandardItem(QString("%0").arg(0));
    NewRow->setEditable(true);
    CurrentArray->setItem(NumberOfArrayElements - 1, NewRow);

}


void SeeSavedArraysWindow::on_MinusButton_clicked()
{
    if (NumberOfArrayElements == 1){
        return;
    }

    --NumberOfArrayElements;
    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));
    CurrentArray->removeRow(NumberOfArrayElements);

}


void SeeSavedArraysWindow::on_NumberOfArrayElementsLineEdit_editingFinished()
{
    QString NumberFromNumberOfArrayElementLineEditCheck = ui->NumberOfArrayElementsLineEdit->text();
    bool NumberIsCorrect = false;
    int NewNumberOfArrayElements = NumberFromNumberOfArrayElementLineEditCheck.toInt(&NumberIsCorrect);

    if (!NumberIsCorrect){
        ShowMessageBoxWithOK(this,"Некорректное число элементов массива", "Введите новое число элементов массива", "Verdana", 9);
        return;

    }

    if (NewNumberOfArrayElements  + 1> 100000 || NewNumberOfArrayElements < 1){
        ShowMessageBoxWithOK(this,"Некорректное число элементов массива", "Введите новое число элементов массива", "Verdana", 9);
        return;

    }


    if (NumberOfArrayElements < NewNumberOfArrayElements){

        for (;NumberOfArrayElements < NewNumberOfArrayElements; NumberOfArrayElements++){
            QStandardItem *NewItem = new QStandardItem(QString("%0").arg(0));
            CurrentArray->setItem(NumberOfArrayElements, NewItem);
        }

        ++NumberOfArrayElements;

    }

    if (NumberOfArrayElements > NewNumberOfArrayElements){

        --NumberOfArrayElements;

        for(;NumberOfArrayElements > NewNumberOfArrayElements; NumberOfArrayElements--){
            CurrentArray->removeRow(NumberOfArrayElements);
        }

        if (NewNumberOfArrayElements == 1){
            CurrentArray->removeRow(NumberOfArrayElements - 1);
        }

    }

    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));
}


void SeeSavedArraysWindow::on_DeleteArrayButton_clicked()
{
    QModelIndexList FirstSelectedRow = ui->ArraysTableview->selectionModel()->selectedRows();
    if (!FirstSelectedRow.isEmpty() && ArrayToSeeDataFromDb->rowCount() > 0 ){
        int SelectedRow = FirstSelectedRow.first().row();
        QModelIndex SelectedRowIndex = ArrayToSeeDataFromDb->index(SelectedRow, 0);
        if (!SelectedRowIndex.isValid()){
            ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось перенести массив в таблицу, попробуйте снова", "Verdana", 9);
            return;
        }

        bool ToIntIsCorrect = false;
        int ArrayForDeletingId = ArrayToSeeDataFromDb->data(SelectedRowIndex).toInt(&ToIntIsCorrect);

        if (!ToIntIsCorrect){
            ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось перенести массив в таблицу, попробуйте снова", "Verdana", 9);
            return;
        }

        bool CurrentArrayWasDeletedSuccessful = Database::GetInstance().DeleteArray(ArrayForDeletingId);
        if (!CurrentArrayWasDeletedSuccessful){
            ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось удалить массив, попробуйте снова", "Verdana", 9);
            return;
        }

        ArrayToSeeDataFromDb->removeRow(SelectedRow);


        ShowMessageBoxWithOK(this, "Успех!!!", "Массив успешно удален!!", "Verdana", 9);
    }
    else{
        ShowMessageBoxWithOK(this, "Ошибка, попробуйте снова", "Не удалось удалить массив, попробуйте снова", "Verdana", 9);
    }
}
