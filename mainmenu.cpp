#include "mainmenu.h"
#include "./ui_mainmenu.h"

MainMENU::MainMENU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMENU)
{
    ui->setupUi(this);                       //Настройка интерфейса, подключение интерфейса к данному файлу.
    this->setWindowIcon(QIcon("logo.ico"));  //Настройка иконки окна
}

MainMENU::~MainMENU()
{
    delete ui;          //Удаление интерфейса из памяти, после закрытия окна.
}

void MainMENU::on_pushButton_clicked() //Функция для открытия меню таблиц
{
    if (counttable == 0 ) //Работа функции только при первом вызове таблиц
    {
        tableof = new TableOfTables;
        connect(this, &MainMENU::signal, tableof, &TableOfTables::slot); //Соединение слота данного файла и таблиц (Отправка головы списка)
        emit signal(tempHead);      //Отправка сигнала
    }
    counttable = 1; //Делает повторный вызов меню выше невозможным
    connect(tableof, &TableOfTables::signal, this, &MainMENU::slotTable); //Соединение сигнала таблиц , и данного меню. (Принятие головы списка)
    this->hide(); //Скрытие главного меню
    tableof->show(); //Вызов меню таблиц
}

void MainMENU::slot(sweettypes* Head, int counteroftypes, QString nameoffile) // Слот для принятия данных о голове, колличестве типов, пути файла
{
    tempHead = Head;
    counter = counteroftypes;
    filename = nameoffile.toLocal8Bit().data();;
}

void MainMENU::slotTable(sweettypes *Head) //Слот для принятия головы после работы с ней из таблиц
{
    tempHead = Head;
    this->show();
}

void MainMENU::slotGift() //Слот для повторного вызова данного меню, из других окон
{
    this->show();
}

void MainMENU::on_GiftButton_clicked() //Функция открытия меню подарков
{
    if (tempHead != NULL) //Проверка на то, есть ли список.
    {
        if (countgift == 0) //Функция обеспечивает единоразовый вызов
        {
            gift = new Gift;
            connect(this, &MainMENU::signalsecond, gift, &Gift::slot); //Соединение сигнала главного меню, и слота меню подарков
        }
        emit signalsecond(tempHead); //Отправка головы в меню подарков
        countgift = 1;
        connect(gift, &Gift::signal, this, &MainMENU::slotGift);  //Соединение сигнала меню подарков, с слотом главного меню
        gift->show();  //вызов меню подарков
        this->hide();  //скрытие данного меню
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Структуры сладостей не найдены"); //Если список пуст, вызов окна с предупреждением
        msgBox.exec();
    }
}

void MainMENU::on_pushButton_4_clicked() //Функция кнопки "Закрыть без сохранения"
{
    QMessageBox msgBox;
    msgBox.setText("Вы уверены что хотите выйти без сохранения?");     //вызов предупреждающего меню
    QPushButton *YesBtn = msgBox.addButton("Да", QMessageBox::YesRole);
    msgBox.addButton("Нет", QMessageBox::NoRole);       //Кнопки: да,нет
    msgBox.exec();
    if (msgBox.clickedButton() == YesBtn)
    {
        QApplication::closeAllWindows(); //Закрытие при подтверждении
    }
}

void MainMENU::on_ButtonSave_clicked() //Функция для выхода с сохранением в файл
{
    if (tempHead != NULL) //Проверка на то, пустые ли структуры
    {
        std::ofstream f(filename.toLocal8Bit().data()); //Открытие файла для записи
        sweettypes * temp;
        temp = tempHead;
        while(temp) //считывание структур
        {
            f << temp->code << " " << temp->name << " " << std::endl; //Запись типов в файл
            sweet * tempsweet;
            tempsweet = temp->giftget;
            while (tempsweet)
            {
                f << "   " << tempsweet->name << " " << tempsweet->price << " " << tempsweet->weight << " " << std::endl; //Запись сладостей в файл
                tempsweet = tempsweet->next;
            }
            temp = temp->next;
        }
        QApplication::closeAllWindows(); //закрытие всех окон
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Вы уверены что хотите сохранить пустой файл?");
        QPushButton *YesBtn = msgBox.addButton("Да", QMessageBox::YesRole);  //Предупреждающее окно, при сохранении пустых структур
        msgBox.addButton("Нет", QMessageBox::NoRole);
        msgBox.exec();
        if (msgBox.clickedButton() == YesBtn) //Сохранение только после подтверждения
        {
            std::ofstream f(filename.toLocal8Bit().data());
            QApplication::closeAllWindows(); //Закрытие всех окон
        }
    }
}

