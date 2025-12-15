#include <QFile>
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainwindow.h"
#include "database.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    Login = "Guest";
    Password = "123";

    ui->RegisterLabel->setText("<a href=\"#\">Регистрация</a>");
    ui->RegisterLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->RegisterLabel->setCursor(Qt::PointingHandCursor);
    ui->RegisterLabel->setStyleSheet("QLabel { color: #0078D7; }"
                                     "QLabel:hover { color: #005A9E; text-decoration: underline; }");

    QIcon MainIcon(":/Photos/main_icon.png");
    setWindowIcon(MainIcon);

    SwitchTheme();

    connect(ui->RegisterLabel, &QLabel::linkActivated, this, [this]() {

        this->hide();

        RegisterWindow* RegWnd = new RegisterWindow(this);

        RegWnd->exec();
    });

}

LoginWindow::~LoginWindow()
{


    Database::GetInstance().DeleteGuestData();
    Database::GetInstance().CloseConnection();

    delete ui;
}

void LoginWindow::on_LoginButton_clicked()
{
    if (Login.trimmed().isEmpty() || Password.trimmed().isEmpty()){
        ShowMessageBoxWithOK(this,"Введите больше данных в поля Логин и пароль", "Недостаточно данных для регистрации/авторизации", "Verdana", 9);
        return;
    }

    if (!Database::GetInstance().ThisAccountIsExists(Login)){
        ShowMessageBoxWithOK(this,"Такого аккаунта не существует", "Такого аккаунта не существует, пожалуйста, зарегистрируйтесь", "Verdana", 9);
        return;
    }

    if (!Database::GetInstance().LogInToAccount(Login, Password)){
        ShowMessageBoxWithOK(this,"Неправильный пароль", "Неправильный пароль, попробуйте снова", "Verdana", 9);
        return;
    }



    ui->PasswordLineEdit->clear();
    ui->LoginLineEdit->clear();

    this->hide();
    MainWindow* MainWnd = new MainWindow(this, Login, Password, true);


    MainWnd->exec();
}


void LoginWindow::on_LoginLineEdit_editingFinished()
{
    Login = ui->LoginLineEdit->text();
}


void LoginWindow::on_PasswordLineEdit_editingFinished()
{
    Password = ui->PasswordLineEdit->text();
}

