#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT
    QString Login;
    QString Password;

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void GetRememberMeAccountData();

private slots:
    void on_LoginButton_clicked();

    void on_LoginLineEdit_editingFinished();

    void on_PasswordLineEdit_editingFinished();

private:
    Ui::LoginWindow *ui;
};
void SwitchTheme();
#endif // LOGINWINDOW_H
