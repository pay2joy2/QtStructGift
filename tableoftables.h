#ifndef TABLEOFTABLES_H
#define TABLEOFTABLES_H

#include "openfiles.h"
#include <QWidget>
#include <QTreeWidget> //Подключение библиотек
#include <QMessageBox>

namespace Ui {
class TableOfTables;
}

class TableOfTables : public QWidget
{
    Q_OBJECT

public:
    explicit TableOfTables(QWidget *parent = nullptr);
    ~TableOfTables();
private:
    Ui::TableOfTables *ui;

signals:
    void signal(sweettypes*);  //Инициализация сигналов

public:
    sweettypes *tempHead;    //Объявление переменных
    int rowcounter = 0;

public slots:
    void slot(sweettypes* Head); //Сигнал для отправки головы обратно в меню

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked(); //Слоты с кнопок
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
};

#endif // TABLEOFTABLES_H
