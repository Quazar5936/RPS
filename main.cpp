#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "main.h"
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RPS33_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    DbCheck();
    LoginWindow LgnWnd;
    LgnWnd.show();
    return a.exec();
}
