#include <QStandardItemModel>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include "programtheme.h"
#include "database.h"

bool ProgramTheme::ThemeIsDark = true;
bool CombSort(QStandardItemModel* SortedArray,int NumberOfArrayElements )
{
    const double SHRINK_FACTOR = 1.3;
    int gap = NumberOfArrayElements;
    bool swapped = true;

    while (gap > 1 || swapped) {

        gap = static_cast<int>(std::floor(gap / SHRINK_FACTOR));
        if (gap < 1) gap = 1;

        swapped = false;

        for (int i = 0; i + gap < NumberOfArrayElements; ++i) {
            int j = i + gap;

            QModelIndex idxI = SortedArray->index(i, 0);
            QModelIndex idxJ = SortedArray->index(j, 0);

            if (!idxI.isValid() || !idxJ.isValid()) {
                continue;
            }

            bool ok1 = false, ok2 = false;
            int valI = SortedArray->data(idxI, Qt::EditRole).toInt(&ok1);
            int valJ = SortedArray->data(idxJ, Qt::EditRole).toInt(&ok2);

            if (!ok1 || !ok2) {
                qWarning() << "CombSort: некорректное число в ячейке" << i << "или" << j;
                return false;
            }

            if (valI > valJ) {

                SortedArray->setData(idxI, valJ, Qt::EditRole);
                SortedArray->setData(idxJ, valI, Qt::EditRole);
                swapped = true;
            }
        }
    }

    return true;
}

void SwitchTheme(){
    if (ProgramTheme::ThemeIsDark){
        qApp->setStyle("Fusion");

        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(45, 45, 45));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        qApp->setPalette(darkPalette);


        qApp->setStyleSheet(

            "QToolTip {"
            "color: #ffffff;"
            "background-color: #2a2a2a;"
            "border: 1px solid #555555;"
            "padding: 4px;"
            "}"
            "QLineEdit, QTextEdit {"
            "border: 1px solid #555;"
            "border-radius: 3px;"
            "padding: 3px;"
            "}"
            "QPushButton {"
            "border: 1px solid #555;"
            "border-radius: 4px;"
            "padding: 5px 10px;"
            "background: #444;"
            "}"
            "QPushButton:hover {"
            "background: #555;"
            "}"
            "QPushButton:pressed {"
            "background: #666;"
            "}"
            "QPushButton:disabled {"
            "color: #888;"
            "}"
            "QComboBox {"
            "border: 1px solid #555;"
            "padding: 2px;"
            "background: #373737;"
            "}"
            "QComboBox::drop-down {"
            "border: 0px;"
            "width: 20px;"
            "}"
            "QComboBox QAbstractItemView {"
            "background: #2d2d2d;"
            "selection-background-color: #4080ff;"
            "}"
            "QScrollBar:vertical {"
            "border: none;"
            "background: #333;"
            "width: 12px;"
            "margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle:vertical {"
            "background: #555;"
            "min-height: 20px;"
            "border-radius: 5px;"
            "}"
            "QScrollBar::handle:vertical:hover {"
            "background: #666;"
            "}"
            );
    }
    else{
        QPalette lightPalette;
        QColor lightBg     = QColor(245, 245, 245);
        QColor lighterBg   = QColor(255, 255, 255);
        QColor lightAccent = QColor(64, 128, 255);
        QColor darkText    = QColor(40, 40, 40);
        QColor midText     = QColor(120, 120, 120);
        QColor border      = QColor(200, 200, 200);

        lightPalette.setColor(QPalette::Window, lightBg);
        lightPalette.setColor(QPalette::WindowText, darkText);
        lightPalette.setColor(QPalette::Base, lighterBg);
        lightPalette.setColor(QPalette::AlternateBase, QColor(240, 240, 240));
        lightPalette.setColor(QPalette::ToolTipBase, lightBg);
        lightPalette.setColor(QPalette::ToolTipText, darkText);
        lightPalette.setColor(QPalette::Text, darkText);
        lightPalette.setColor(QPalette::Button, lightBg);
        lightPalette.setColor(QPalette::ButtonText, darkText);
        lightPalette.setColor(QPalette::BrightText, Qt::red);
        lightPalette.setColor(QPalette::Link, lightAccent);

        lightPalette.setColor(QPalette::Highlight, lightAccent);
        lightPalette.setColor(QPalette::HighlightedText, Qt::white);
        lightPalette.setColor(QPalette::Disabled, QPalette::WindowText, midText);
        lightPalette.setColor(QPalette::Disabled, QPalette::Text, midText);
        lightPalette.setColor(QPalette::Disabled, QPalette::ButtonText, midText);

        qApp->setPalette(lightPalette);
        qApp->setStyleSheet(
            "QToolTip {"
            "color: #333333;"
            "background-color: #ffffff;"
            "border: 1px solid #cccccc;"
            "padding: 4px;"
            "}"
            "QLineEdit, QTextEdit {"
            "border: 1px solid #ccc;"
            "border-radius: 3px;"
            "padding: 3px;"
            "background: white;"
            "}"
            "QPushButton {"
            "border: 1px solid #ccc;"
            "border-radius: 4px;"
            "padding: 5px 10px;"
            "background: #f0f0f0;"
            "}"
            "QPushButton:hover {"
            "background: #e0e0e0;"
            "}"
            "QPushButton:pressed {"
            "background: #d0d0d0;"
            "}"
            "QPushButton:disabled {"
            "color: #999;"
            "}"
            "QComboBox {"
            "border: 1px solid #ccc;"
            "padding: 2px;"
            "background: white;"
            "}"
            "QComboBox::drop-down {"
            "border: 0px;"
            "width: 20px;"
            "}"
            "QComboBox QAbstractItemView {"
            "background: white;"
            "selection-background-color: #4080ff;"
            "}"
            "QScrollBar:vertical {"
            "border: none;"
            "background: #f0f0f0;"
            "width: 12px;"
            "margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle:vertical {"
            "background: #ccc;"
            "min-height: 20px;"
            "border-radius: 5px;"
            "}"
            "QScrollBar::handle:vertical:hover {"
            "background: #bbb;"
            "}"
            );
    }
}


void ShowMessageBoxWithOK(QWidget *Parent, QString WindowTitle, QString Message, QString FontName, int FontSize ){
    QMessageBox ErrorMessageBox(Parent);
    ErrorMessageBox.setWindowTitle(WindowTitle);
    ErrorMessageBox.setText(Message);
    QFont FontForErrorMessageBox(FontName, FontSize, QFont::Bold);
    ErrorMessageBox.setFont(FontForErrorMessageBox);

    auto OKButton = ErrorMessageBox.addButton("Ок", QMessageBox::AcceptRole);


    ErrorMessageBox.exec();
}

void DbCheck(){
    const QString DbName = "UsersData.sqlite";

    Database& Db = Database::GetInstance();

    bool DatabaseCreatingSuccessful = Db.ConnectToDatabase(DbName);
    if (!DatabaseCreatingSuccessful){
        QCoreApplication::quit();
    }

    Database::GetInstance().FirstDatabaseConnection();

}
