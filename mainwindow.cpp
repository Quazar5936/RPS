#include <QTimer>
#include <QRandomGenerator>
#include <QCloseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "seesavedarrayswindow.h"
#include "infowindow.h"
#include "database.h"
#include "programtheme.h"
#include "loginwindow.h"
#include "registerwindow.h"

void MainWindow::CheckArrayListView(){
    QAbstractItemDelegate *ElementsOfArrayListViewDelegate = ui->ArrayListview->itemDelegate();

    if (!ElementsOfArrayListViewDelegate){
        return;
    }

    connect(ElementsOfArrayListViewDelegate, &QAbstractItemDelegate::commitData,
            [&](QWidget *editor) {

                if (auto lineEdit = qobject_cast<QLineEdit*>(editor)) {
                    QString TextFromLineEdit = lineEdit->text().trimmed();

                    if (TextFromLineEdit.isEmpty()) {

                        QModelIndex Index = ui->ArrayListview->currentIndex();
                        if (Index.isValid()) {
                            Array->setData(Index, "0", Qt::EditRole);
                        }

                        return;
                    }

                    bool ThisIsNumber = false;
                    int NumberCheck = TextFromLineEdit.toInt(&ThisIsNumber);

                    if (!ThisIsNumber){

                        QModelIndex IndexOfNotCorrectNumber = ui->ArrayListview->currentIndex();
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
                            Array->setData(pIndexOfNotCorrectNumber, "0");

                        });

                    }
                }

            });
}

void MainWindow::CheckSortedArrayListView(){
    QAbstractItemDelegate *SortedArrayListViewDelegate = ui->SortedArrayListview->itemDelegate();

    if (!SortedArrayListViewDelegate){
        return;
    }

    connect(SortedArrayListViewDelegate, &QAbstractItemDelegate::commitData,
            [&](QWidget *editor) {

                if (auto lineEdit = qobject_cast<QLineEdit*>(editor)) {
                    QString TextFromLineEdit = lineEdit->text().trimmed();

                    if (TextFromLineEdit.isEmpty()) {

                        QModelIndex Index = ui->SortedArrayListview->currentIndex();
                        if (Index.isValid()) {
                            SortedArray->setData(Index, "0", Qt::EditRole);
                        }

                        return;
                    }

                    bool ThisIsNumber = false;
                    int NumberCheck = TextFromLineEdit.toInt(&ThisIsNumber);

                    if (!ThisIsNumber){

                        QModelIndex IndexOfNotCorrectNumber = ui->SortedArrayListview->currentIndex();
                        if (!IndexOfNotCorrectNumber.isValid()) {
                            return;

                        }

                        QPersistentModelIndex pIndexOfNotCorrectNumber = IndexOfNotCorrectNumber;
                        QTimer::singleShot(0, this, [this, pIndexOfNotCorrectNumber]() {


                            if (pIndexOfNotCorrectNumber.isValid()) {

                                ShowMessageBoxWithOK(this, "Ошибка",
                                                     "Некорректное число. Установлено значение 0.",
                                                     "Verdana", 9);
                                SortedArray->setData(pIndexOfNotCorrectNumber, "0");
                                qDebug() << "123";
                            }

                        });

                    }
                }

            });
}




MainWindow::MainWindow(LoginWindow *parent, QString NewLogin, QString NewPassword, bool NotGuest)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->setupUi(this);


    Array = new QStandardItemModel;
    SortedArray = new QStandardItemModel;

    this->ParentLoginWindow = parent;

    CheckSortedArrayListView();
    CheckArrayListView();

    Login = NewLogin;
    Password = NewPassword;
    Registered = NotGuest;

    ui->GreetingLabel->setText("Добро пожаловать, " + Login + "!");
    if (Login == "Guest"){
        ui->GreetingLabel->setText("Добро пожаловать, Гость!");
    }

    ui->NumberOfArrayElementsLineEdit->setFocus();

    QIcon MainIcon(":/Photos/main_icon.png");
    setWindowIcon(MainIcon);

    QIcon DarkThemeIcon(":/Photos/darkth.png");
    ui->DarkThemeButton->setIcon(DarkThemeIcon);
    ui->DarkThemeButton->setToolTip("Темная тема");

    QIcon QuitIcon(":/Photos/door_exit.png");
    ui->QuitButton->setIcon(QuitIcon);
    ui->QuitButton->setToolTip("Выйти из программы");

    QIcon InfoIcon(":/Photos/angle.png");
    ui->InfoButton->setIcon(InfoIcon);
    ui->InfoButton->setToolTip("Справка");

    QIcon LeaveIcon(":/Photos/leftacc.png");
    ui->LeaveButton->setIcon(LeaveIcon);
    ui->LeaveButton->setToolTip("Выйти из аккаунта");

    NumberOfArrayElements = 25;
    for(int i = 0;i < NumberOfArrayElements;i++){
        QStandardItem *StartRows = new QStandardItem(QString("%0").arg(i));
        StartRows->setEditable(true);
        Array->setItem(i, StartRows);
    }

    ui->ArrayListview->setModel(Array);
    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));

}

MainWindow::~MainWindow()
{
    delete Array;
    Array = nullptr;
    delete SortedArray;
    SortedArray = nullptr;

    delete ui;
}

void MainWindow::on_LoadArraysButton_clicked()
{

    SeeSavedArraysWindow SeeArraysForm(this,Array,Login, &NumberOfArrayElements);


    connect(&SeeArraysForm, &SeeSavedArraysWindow::NumberOfArrayElementsChanged,this,&MainWindow::ChangeNumberOfArrayElements);
    SeeArraysForm.exec();
}


void MainWindow::on_NumberOfArrayElementsLineEdit_editingFinished()
{
    QString NumberFromNumberOfArrayElementLineEditCheck = ui->NumberOfArrayElementsLineEdit->text();
    bool NumberIsCorrect = false;
    int NewNumberOfArrayElements = NumberFromNumberOfArrayElementLineEditCheck.toInt(&NumberIsCorrect);

    if (!NumberIsCorrect){
        ShowMessageBoxWithOK(this,"Некорректное число элементов массива", "Введите новое число элементов массива", "Verdana", 9);
        return;

    }

    if (NewNumberOfArrayElements + 1 > 100000 || NewNumberOfArrayElements < 1){
        ShowMessageBoxWithOK(this,"Некорректное число элементов массива", "Введите новое число элементов массива", "Verdana", 9);
        return;

    }


    if (NumberOfArrayElements < NewNumberOfArrayElements){

        for (;NumberOfArrayElements < NewNumberOfArrayElements; NumberOfArrayElements++){
            QStandardItem *NewItem = new QStandardItem(QString("%0").arg(0));
            Array->setItem(NumberOfArrayElements, NewItem);
        }

        ++NumberOfArrayElements;

    }

    if (NumberOfArrayElements > NewNumberOfArrayElements){

        --NumberOfArrayElements;

        for(;NumberOfArrayElements > NewNumberOfArrayElements; NumberOfArrayElements--){
            Array->removeRow(NumberOfArrayElements);
        }

        if (NewNumberOfArrayElements == 1){
            Array->removeRow(NumberOfArrayElements - 1);
        }

    }

    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));
    ui->ArrayListview->setModel(Array);

}

void MainWindow::ChangeNumberOfArrayElements(){
    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));

}

void MainWindow::on_PlusButton_clicked()
{
    if (NumberOfArrayElements + 1 > 100000){
        return;
    }

    ++NumberOfArrayElements;
    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));
    QStandardItem *NewRow = new QStandardItem(QString("%0").arg(0));
    NewRow->setEditable(true);
    Array->setItem(NumberOfArrayElements - 1, NewRow);

    ui->ArrayListview->setModel(Array);
}


void MainWindow::on_MinusButton_clicked()
{
    if (NumberOfArrayElements == 1){
        return;
    }

    --NumberOfArrayElements;
    ui->NumberOfArrayElementsLineEdit->setText(QString::number(NumberOfArrayElements));
    Array->removeRow(NumberOfArrayElements);
    ui->ArrayListview->setModel(Array);
}

void MainWindow::CopyArray(){
    SortedArray->clear();
    for(int i = 0;i < NumberOfArrayElements;i++){

        auto IndexFromArrayOne = Array->index(i,0);

        if (!IndexFromArrayOne.isValid()){
            ShowMessageBoxWithOK(this,"Ошибка при копировании массива", "Пожалуйста, попробуйте отсортировать массив снова", "Verdana", 9);
            return;
        }

        int NumberFromArrayOne = Array->data(IndexFromArrayOne).toInt();
        QStandardItem *NewRowForArrayTwo = new QStandardItem(QString("%0").arg(NumberFromArrayOne));
        NewRowForArrayTwo->setEditable(true);
        SortedArray->setItem(i,NewRowForArrayTwo);
    }
}


void MainWindow::on_RandomValuesButton_clicked()
{
    Array->clear();
    for(int i = 0;i < NumberOfArrayElements;i++){

        int RandomInt = QRandomGenerator::global()->bounded(-100000, 100000);
        QStandardItem *NewRow = new QStandardItem(QString("%0").arg(RandomInt));
        NewRow->setEditable(true);
        Array->setItem(i, NewRow);
    }
}


void MainWindow::on_SortButton_clicked()
{
    this->CopyArray();
    bool SortIsSuccessful = CombSort(SortedArray,NumberOfArrayElements);
    if (!SortIsSuccessful){
        ShowMessageBoxWithOK(this,"Сортировка не удалась", "Попробуйте снова отсортировать массив, сортировка не удалась", "Verdana", 9);
        return;
    }
    ui->SortedArrayListview->setModel(SortedArray);
}


void MainWindow::on_InfoButton_clicked()
{
    InfoWindow InformationWindow;
    InformationWindow.setAttribute(Qt::WA_QuitOnClose, false);
    InformationWindow.exec();


}


void MainWindow::on_QuitButton_clicked()
{
     QCoreApplication::quit();
}


void MainWindow::on_DarkThemeButton_clicked()
{
    if (ProgramTheme::ThemeIsDark){
        ProgramTheme::ThemeIsDark = false;
    }
    else{
        ProgramTheme::ThemeIsDark = true;
    }
    SwitchTheme();
}


void MainWindow::on_SaveArrayButton_clicked()
{
    bool ArrayWasSaved = Database::GetInstance().SaveArrayToDb(Array, Login);
    if (!ArrayWasSaved){
        ShowMessageBoxWithOK(this,"Массив не сохранен", "Сохранение массива неудачно, попробуйте снова", "Verdana", 9);
    }

    else{
        ShowMessageBoxWithOK(this,"Массив сохранен", "Сохранение массива удачно", "Verdana", 9);
    }
}


void MainWindow::on_SaveSortedArrayButton_clicked()
{

    bool ArrayWasSaved = Database::GetInstance().SaveArrayToDb(SortedArray, Login);
    if (!ArrayWasSaved){
        ShowMessageBoxWithOK(this,"Массив не сохранен", "Сохранение массива неудачно, попробуйте снова", "Verdana", 9);
    }

    else{
        ShowMessageBoxWithOK(this,"Массив сохранен", "Сохранение массива удачно", "Verdana", 9);
    }
}



void MainWindow::on_LeaveButton_clicked()
{
    if (!Registered){
        ShowMessageBoxWithOK(this,"Гость не может выйти из аккаунта!", "Перед тем как выйти из аккаунта вам нужно зарегистрироваться!", "Verdana", 9);
        return;
    }

    ParentLoginWindow->show();
    this->close();
}


