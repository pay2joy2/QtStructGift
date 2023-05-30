#include "openfiles.h"          //Подключение .h файла первого окна OpenFiles
#include <QApplication>         //Подключение библиотек


int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //Подключение класса для управления окнами
    OpenFiles w;                //Объявление указателя для класса первого окна OpenFiles
    setlocale(LC_ALL, "rus");   //Установление поддержки русского языка
    w.show();                   //Создание первого окна
    return a.exec();            //Ожидание закрытия окон, для завершения работы программы.
}
