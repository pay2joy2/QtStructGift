#ifndef GIFT_H
#define GIFT_H

#include <vector>
#include <QWidget>
#include "openfiles.h"
#include <QMessageBox>       //Подключение библиотек
#include "ui_gift.h"

namespace Ui {
class Gift;
}
struct giftcell
{
    std::string SweetType;
    std::string name;
    int amount;              //Подструктура с типом сладости в подарке
    giftcell* next;
};

struct gift
{
    gift* next;
    giftcell* getcell;      //Структура подарка
};

class Gift : public QWidget
{
    Q_OBJECT

public:
    explicit Gift(QWidget *parent = nullptr);
    ~Gift();

public:
    sweettypes *TempHead;
    int countofgifts = 1;
    giftcell* HeadCell, *TailCell;  //Объявление глобальных переменных
    gift* HeadGift, *TailGift;

public slots:
    void slot(sweettypes* Head); //Слот принимающий голову из меню
private:
    gift* GetGift(sweettypes* Head, gift* HeadGift, giftcell *HeadCell, gift **TailGift, giftcell *TailCell,int amountofTypes, int type,sweettypes* tempfor);        //Объявление функций
    giftcell* cellsget(int type, int price, int weight, int amountofTypes, std::vector<bool> Array, sweettypes* tempfor, gift *tempgift, sweettypes *Head, giftcell* HeadCell, giftcell *TailCell);

signals:
    void signal();    //Объявление сигналов

private slots:
    void on_BackToMenu_clicked();
    void on_FormGift_clicked();     //Объявление слотов кнопок
    void on_SaveToFile_clicked();

private:
    Ui::Gift *ui;
};

#endif // GIFT_H
