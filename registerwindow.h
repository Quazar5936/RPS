#ifndef REGISTERWINDOWS_H
#define REGISTERWINDOWS_H

#include <QDialog>
#include "loginwindow.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT
    QString Login;
    QString Password;
    LoginWindow* ParentLoginWindow;

public:
    explicit RegisterWindow(LoginWindow *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_LoginLineEdit_editingFinished();

    void on_PasswordLineEdit_editingFinished();

    void on_RegisterButton_clicked();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOWS_H
