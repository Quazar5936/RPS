#include <QVBoxLayout>
#include "InfoWindow.h"
#include "ui_InfoWindow.h"

InfoWindow::InfoWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoWindow)
{

    ui->setupUi(this);

    QIcon MainIcon(":/Photos/main_icon.png");
    setWindowIcon(MainIcon);

    QVBoxLayout *Layout = new QVBoxLayout(ui->scrollAreaWidgetContent);
    QString Text = "Добро пожаловать в справку!"
                   "\nЗдесь находится вся информация о программе.\n"
                   "Программа представляет из себя менеджер массивов,\n"
                   "который имеет функции создания, редактирования, удаления, обновления, сортировки, сохранения\n"
                   "массивов. Главное окно создано для сортировки, сохранения, редактирования массивов\n"
                   "Второе окно(кнопка Сохраненные массивы) необходимо для редактирования и обновления массивов,\n"
                   "а также для переноса выбранного пользователем массива в главное окно.\n"
                   "    Программа предоставляет возможность создания личного кабинета, за которым будут закрепляться\n"
                   "сохраненные массивы, можно пользоваться программой без входа, но все сохраненные массивы под\n"
                   "аккаунтом гостя будут удалены после выхода из программы.\n"
                   "    Имеется гибкий и интуитивно понятный интерфейс, также программа позволяет установить темную тему."
                   "\n\n  <b>Дата выхода последней версии: 06.12.2025</b>\n\n\nИконки взяты с сайта Flaticon, автор Freepik";
    Text.replace("\n","<br>");

    ui->RegisterLabel->setWordWrap(true);
    ui->RegisterLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->RegisterLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->RegisterLabel->setText(Text);

    Layout->addWidget(ui->RegisterLabel);

}

InfoWindow::~InfoWindow()
{

    delete ui;
}
