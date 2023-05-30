#ifndef MAINMENU_H
#define MAINMENU_H

#include "openfiles.h"
#include "tableoftables.h"
#include "gift.h"               //Подключение библиотек
#include <QWidget>
#include <QMessageBox>

namespace Ui {

class MainMENU;
}

class MainMENU : public QWidget
{
    Q_OBJECT

public:
    explicit MainMENU(QWidget *parent = nullptr);
    ~MainMENU();

private slots:
    void on_pushButton_clicked();

    void on_GiftButton_clicked();

    void on_pushButton_4_clicked();        //Объявление слотов для кнопок

    void on_ButtonSave_clicked();

private:
    Ui::MainMENU *ui;

public:
    sweettypes *tempHead;
    int counter;
    int counttable = 0;
    int countgift = 0;                    //Объявление переменных
    TableOfTables * tableof;
    Gift * gift;
    QString filename;

public slots:
    void slot (sweettypes *Head, int counteroftypes, QString nameoffile);
    void slotTable(sweettypes *Head);                                      //Слоты для принятия сигналов
    void slotGift();

signals:
    void signal(sweettypes*);
    void signalsecond(sweettypes*);              //Сигналы
};

#endif // MAINMENU_H
