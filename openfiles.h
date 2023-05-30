#ifndef OPENFILES_H
#define OPENFILES_H       //Макрос для определения названия .h

#include <QMainWindow>
#include <QFileDialog>         //Подключение библиотек
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class OpenFiles; }     // Определение класса
QT_END_NAMESPACE

struct sweet
{
    std::string name;
    int weight;
    int price;
    sweet* next;
};                        //Объявление структур для сладостей
struct sweettypes
{
    int code;
    std::string name;
    sweet* giftget;
    sweettypes* next;
};

class OpenFiles : public QMainWindow         //Объявление класса окна открытия файлов
{
    Q_OBJECT
public:
    OpenFiles(QWidget *parent = nullptr);
    ~OpenFiles();

private slots:
    void on_pushButton_clicked();      //Слоты для обработки нажатия на кнопки откртия и создания нового файла
    void on_pushButton_2_clicked();

private:
    Ui::OpenFiles *ui;                //Функция создания интерфейса

signals:
    void signal(sweettypes*,int,QString);  //Сигнал для отправки ГОЛОВЫ структуры типов сладостей, их колличества, и путь до файла который был создан/открыт.
};

#endif // OPENFILES_H
