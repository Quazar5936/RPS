#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "mainwindow.h"
#include "database.h"

RegisterWindow::RegisterWindow(LoginWindow *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    ui->setupUi(this);


    Login = "Guest";
    Password = "123";
    ParentLoginWindow = parent;

    QIcon MainIcon(":/Photos/main_icon.png");
    setWindowIcon(MainIcon);

    ui->GuestLabel->setText("<a href=\"#\">Продолжить как гость</a>");
    ui->GuestLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->GuestLabel->setCursor(Qt::PointingHandCursor);
    ui->GuestLabel->setStyleSheet("QLabel { color: #0078D7; }"
                                  "QLabel:hover { color: #005A9E; text-decoration: underline; }");

    connect(ui->GuestLabel, &QLabel::linkActivated, this, [this]() {

        this->hide();
        MainWindow* MainWnd = new MainWindow(ParentLoginWindow, Login, Password, false);


        MainWnd->exec();
    });
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_LoginLineEdit_editingFinished()
{
    Login = ui->LoginLineEdit->text();
}


void RegisterWindow::on_PasswordLineEdit_editingFinished()
{
    Password = ui->PasswordLineEdit->text();
}


void RegisterWindow::on_RegisterButton_clicked()
{
    qDebug() << 1;
    if (Login.trimmed().isEmpty() || Password.trimmed().isEmpty()){
        qDebug() << 1;
        ShowMessageBoxWithOK(this,"Введите больше данных в поля Логин и пароль", "Недостаточно данных для регистрации/авторизации", "Verdana", 9);
        return;
    }

    if (Database::GetInstance().ThisAccountIsExists(Login)){
        qDebug() << 2;
        ShowMessageBoxWithOK(this,"Такой аккаунт существует", "Такой аккаунт существует, выберите другой логин", "Verdana", 9);
        return;
    }

    if (!Database::GetInstance().CreateAccount(Login, Password)){
        qDebug() << 3;
        ShowMessageBoxWithOK(this,"Аккаунт не создан", "Аккаунт не создан, попробуйте снова", "Verdana", 9);
        return;
    }

    this->hide();
    MainWindow* MainWnd = new  MainWindow(ParentLoginWindow,Login,Password, true);
    MainWnd->exec();
}

