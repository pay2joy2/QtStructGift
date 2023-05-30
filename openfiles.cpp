#include "mainmenu.h"           //Подключение .h главного меню
#include "openfiles.h"          //Подключение .h для данного меню
#include "./ui_openfiles.h"     //Подключение графического интерфейса данного меню

OpenFiles::OpenFiles(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OpenFiles)       //Объявление и создание графического интерфейса.
{
    ui->setupUi(this);            //Настройка интерфейса, подключение интерфейса к данному файлу.
    this->setWindowIcon(QIcon("logo.ico"));   //Установка иконки для окна
}

OpenFiles::~OpenFiles()
{
    delete ui;          //Удаление интерфейса из памяти, после закрытия окна.
}

void OpenFiles::on_pushButton_clicked()   //Функция вызываемая при нажатии на кнопку "Выбрать файл"
{
    QStringList filelist;
    QString filename;                                   //Переменная для пути к файлу
    const QStringList filters({"Text files (*.txt)"});  //Фильтры для поиска файла только .txt разрешения
    QFileDialog dialog(this);                           //Объявление перменной dialog для работы с классом QFileDialog
    dialog.setNameFilters(filters);                     //Применение фильтров
    if(dialog.exec())
    {
        filelist = dialog.selectedFiles();              //Вызов окна, проверка на то, выбрал ли пользователь файл.
        filename = filelist[0];
        char *filenameChar;
        filenameChar = filename.toLocal8Bit().data();      //Преобразование из QString в char* пути к файлу, для работы с функцией ifstream.
        sweettypes* remember;
        remember = NULL;
        sweettypes* Head, * Tail;
        sweet* HeadSweet, * TailSweet;
        Tail = NULL;                                     //Объявление основные структур, присвоение головы и хвосту значений NULL
        Head = NULL;
        HeadSweet = NULL;
        TailSweet = NULL;
        std::string line;
        std::ifstream f(filenameChar);                  //Открытие файла для чтения
        int counteroftypes = 0;
        while (std::getline(f, line))                   //Считывание всех строк
        {
            if (line.size() != 0) {
                if (isdigit(line[0]))
                {
                    counteroftypes++;
                    sweettypes* temp;
                    temp = new sweettypes;
                    remember = temp;
                    temp->giftget = NULL;
                    HeadSweet = NULL;
                    temp->next = NULL;
                    char* lineChar = _strdup(line.c_str());
                    temp->code = atoi(strtok(lineChar, " "));
                    temp->name = strtok(NULL, " ");
                    if (Head == NULL)
                    {
                        Head = temp;
                        Tail = temp;

                    }
                    else
                    {

                        Tail->next = temp;                                   //Функция для работы с содержимым файла, и переносом в структуры.
                        Tail = temp;
                    }
                }
                else
                {
                    sweet* tempsweet;
                    tempsweet = new sweet;
                    tempsweet->next = NULL;
                    char* lineChar = _strdup(line.c_str());
                    tempsweet->name = strtok(lineChar, " ");
                    tempsweet->price = atoi(strtok(NULL, " "));
                    tempsweet->weight = atoi(strtok(NULL, " "));
                    if (HeadSweet == NULL)
                    {
                        TailSweet = tempsweet;
                        HeadSweet = tempsweet;
                        remember->giftget = HeadSweet;
                    }
                    else
                    {
                        TailSweet->next = tempsweet;
                        TailSweet = tempsweet;
                    }
                }
            }
        }
        f.close();                                            //Закрытие файла
        MainMENU *mainmenu = new MainMENU;                    //Объявление перменной mainmenu для работы с окном и классом главного меню
        connect(this, &OpenFiles::signal, mainmenu, &MainMENU::slot); //Соединение слота меню, и сигнала данного окна.
        emit signal(Head, counteroftypes, filename);                //Отправка сигнала с перменными головы, колличества типов, путём файла)
        mainmenu->show();                                     //Открытие главного меню
        this->close();                                        //Закрытие текущего меню
    }
}

void OpenFiles::on_pushButton_2_clicked() //Функция вызываемая при нажатии на кнопку "Новый файл"
{
    QString filename;           //Объявление переменной для хранения пути файла
    QFileDialog dialog(this);     //Объявление перменной dialog для работы с классом QFileDialog
    filename = dialog.getSaveFileName(this, "Create New File","", tr("Text files (*.txt)")); //Открытие окна для создания нового файла
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) //Проверка на то, создался ли файл
    {
        sweettypes* Head;
        Head = NULL;
        MainMENU *mainmenu = new MainMENU;
        connect(this, &OpenFiles::signal, mainmenu, &MainMENU::slot);     //Код для вызова окна главного меню, отправки сигнала, и закрытие текущего.
        emit signal(Head, 0, filename);
        mainmenu->show();
        this->close();
    }
}

