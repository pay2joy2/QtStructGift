#include "gift.h"

Gift::Gift(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gift)
{
    ui->setupUi(this);  //Настройка интерфейса, подключение интерфейса к данному файлу.
    this->setWindowIcon(QIcon("logo.ico"));   //Настройка иконки окна
    ui->lineTypes->setValidator(new QIntValidator(0, 100000000, this));
    ui->linePrice->setValidator(new QIntValidator(0, 100000000, this));
    ui->lineWeight->setValidator(new QIntValidator(0, 100000000, this));
    ui->treeWidget->setColumnCount(3);
    ui->treeWidget->headerItem()->setText(0,"Сладость");
    ui->treeWidget->headerItem()->setText(1, "Цена");                            //Настройка таблицы
    ui->treeWidget->headerItem()->setText(2, "Колличество");
    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    HeadCell = NULL;
    HeadGift = NULL;
    TailGift = NULL;
    TailCell = NULL;
}

Gift::~Gift()
{
    delete ui;
}

void Gift::slot(sweettypes *Head)
{
    TempHead = Head;
}

void Gift::on_BackToMenu_clicked() //Функция выхода назад, в главное меню
{
    emit signal();
    this->hide();
}

giftcell* Gift::cellsget(int type, int price, int weight, int amountofTypes, std::vector<bool> Array, sweettypes* tempfor, gift *tempgift, sweettypes *Head, giftcell* HeadCell, giftcell *TailCell) //Функция подбора типов в подарок
{
    giftcell* tempcell;
    for (int i = 0; i < type; i++)
    {
        int num = rand() % amountofTypes;
        while (Array[num] == true)
        {
            num = rand() % amountofTypes;        //Проверка на уникальность типа
        }
        Array[num] = true;
        tempfor = Head;
        for (int g = 0; g < num; g++)
        {
            tempfor = tempfor->next;
        }
        int amountofsweets = 0;
        sweet* tempSweets;
        tempSweets = tempfor->giftget;
        while (tempSweets)
        {
            amountofsweets++;
            tempSweets = tempSweets->next;       //Подсчёт колличества сладостей
        }
        int randomnum = rand() % amountofsweets;
        tempSweets = tempfor->giftget;
        for (int a = 0; a < randomnum; a++)
        {
            tempSweets = tempSweets->next;        //выбор случайной сладости
        }
        int counter = 0;
        int sum = 0;
        int weighsum = 0;
        while (true)
        {
            counter++;
            sum += tempSweets->price;
            weighsum += tempSweets->weight;
            if (sum > price / type || weighsum > weight / type)     //Функция подсчёта необходимого колличества сладостей подходящего под условия
            {
                counter--;
                sum = sum - tempSweets->price;
                weighsum = weighsum - tempSweets->weight;
                break;
            }
        }
        if (counter != 0)
        {
            tempcell = new giftcell;
            tempcell->next = NULL;
            tempcell->amount = counter;
            tempcell->name = tempSweets->name;
            tempcell->SweetType = tempfor->name;    //Если подошли условия, сладость создаётся
            if (HeadCell == NULL)
            {
                HeadCell = tempcell;
                TailCell = tempcell;
                tempgift->getcell = HeadCell;
            }
            else
            {
                TailCell->next = tempcell;
                TailCell = tempcell;
                if (tempcell == NULL)
                {

                }
            }
        }
    }
    return HeadCell;
}

gift* Gift::GetGift(sweettypes* Head, gift* HeadGift, giftcell *HeadCell, gift **TailGift, giftcell *TailCell, int amountofTypes, int type,sweettypes* tempfor) //Функция формирования подарка
{
        int price, weight;
        price = ui->linePrice->text().toInt();
        weight = ui->lineWeight->text().toInt();
        std::vector<bool> Array(amountofTypes+1, false);
        srand(time(NULL));
        gift* tempgift;
        tempgift = new gift;
        tempgift->next = NULL;
        tempgift->getcell = NULL;
            if (HeadGift == NULL) {
                HeadGift = tempgift;
                *TailGift = tempgift;
                tempgift->getcell = cellsget(type, price, weight, amountofTypes, Array, tempfor, tempgift, Head, HeadCell, TailCell); //Вызов функции формирования типа сладости
            }
            else
            {
                (*TailGift)->next = tempgift;
                *TailGift = tempgift;
                tempgift->getcell = cellsget(type, price, weight, amountofTypes, Array, tempfor, tempgift, Head, HeadCell, TailCell); // Вызов функции формирования типа сладости
            }
        if (tempgift->getcell != NULL) //Проверка, подошёл ли хотя бы 1 тип под условия
        {
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
            treeItem->setText(0, ("Подарок " + QString::number(countofgifts)));
            giftcell* temptempcells;
            temptempcells = tempgift->getcell;
            while (temptempcells)
            {
                QTreeWidgetItem *treeLeaf = new QTreeWidgetItem();
                treeLeaf->setText(0, QString::fromStdString(temptempcells->SweetType));   //Формирование подарка, добавление в список
                treeLeaf->setText(1, QString::fromStdString(temptempcells->name));
                treeLeaf->setText(2,QString::number(temptempcells->amount));
                treeItem->addChild(treeLeaf);
                temptempcells = temptempcells->next;
            }
        }
        else
        {
            if (HeadGift == *TailGift)
            {
                HeadGift = NULL;
                TailGift = NULL;       //Если типы не подошли, и подарок первый - обнулить структуру.
            }
            else
            {
                gift* temptemp;
                temptemp = HeadGift;
                while(temptemp)
                {
                    if(temptemp->next == tempgift)
                    {
                        temptemp->next = tempgift->next;    //Если типы не подошли, удалить последний пустой подарок
                        if (tempgift->next == NULL)
                        {
                            *TailGift = temptemp;
                        }
                    }
                    temptemp = temptemp->next;
                }
                delete tempgift;
            }
            QMessageBox msgBox;
            msgBox.setText("Введённые данные не достаточны что бы сформировать подарок");  //Вызвать меню, о недостаточности данных.
            msgBox.exec();
        }
        countofgifts++;
        ui->lineTypes->clear();
        ui->lineWeight->clear();     //Отчистить поля ввода данных
        ui->linePrice->clear();
        return HeadGift;
}

void Gift::on_FormGift_clicked() //Функция кнопки для формирования подарка
{
    if (ui->linePrice->text().isEmpty() || ui->lineTypes->text().isEmpty() || ui->lineWeight->text().isEmpty()) //Проверка на заполненность полей данных
    {
        QMessageBox msgBox;
        msgBox.setText("Заполните все необходимые поля"); //Если не заполнены - вызов предупреждения
        msgBox.exec();
    }
    else
    {
        sweettypes* Head;
        Head = TempHead;
        int amountofTypes = 0;
        sweettypes* tempfor;
        tempfor = Head;
        while (tempfor)
        {
            amountofTypes++;             //Подсчёт колличества существующих типов в списках
            tempfor = tempfor->next;
        }
        int type = ui->lineTypes->text().toInt();
        if (type <= amountofTypes) //Проверка, больше ли типов задано, чем существует
        {
            HeadGift = GetGift(Head, HeadGift, HeadCell, &TailGift, TailCell, amountofTypes, type, tempfor); //Вызов функции формирования подарка
        }
        else
        {
            QMessageBox msgBox;        //Если типов больше, вызов предупреждения
            msgBox.setText("Колличество типов больше существующего");
            msgBox.exec();
        }
    }
}

void Gift::on_SaveToFile_clicked() //Функция кнопки сохранения в файл
{
    if (HeadGift != NULL) //Проверка если существуют сформированные подарки
    {
        QString filename;
        QFileDialog dialog(this);
        filename = dialog.getSaveFileName(this, "Create New File","", tr("Text files (*.txt)")); //Вызов диалога создания файла для сохранения
        if (filename.size() != 0)
        {
            std::ofstream g(filename.toLocal8Bit().data());
            gift *tempHead;
            tempHead = HeadGift;
            while(tempHead)
            {
                if(tempHead->getcell != NULL)
                {
                    g << "Подарок " << std::endl;
                    giftcell * tempHeadCell;
                    tempHeadCell = tempHead->getcell;                                 //Сохранение в файл
                    while (tempHeadCell)
                    {
                        g << " " << tempHeadCell->SweetType << " " << tempHeadCell->name << " " << tempHeadCell->amount << " " << std::endl;
                        tempHeadCell = tempHeadCell->next;
                    }
                }
                g << std::endl;
                tempHead = tempHead->next;
            }
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Список подарков пуст"); //Если сформированных подарков нет, вызывается предупреждение
        msgBox.exec();
    }
}

