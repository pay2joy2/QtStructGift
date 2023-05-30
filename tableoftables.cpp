#include "tableoftables.h"
#include "ui_tableoftables.h"

TableOfTables::TableOfTables(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableOfTables)
{
    setlocale(LC_ALL, "rus");
    ui->setupUi(this);                        //Настройка интерфейса, подключение интерфейса к данному файлу.
    this->setWindowIcon(QIcon("logo.ico"));   //Настройка иконки окна
}

void TableOfTables::slot(sweettypes *Head)    //Слот принимающий значение из главного меню, принимает голову списка
{
    tempHead = Head;
    ui->treeWidget->setColumnCount(5);
    ui->treeWidget->headerItem()->setText(0,"Код");
    ui->treeWidget->headerItem()->setText(1, "Тип");
    ui->treeWidget->headerItem()->setText(2, "Наименование");                         //Настройка таблицы
    ui->treeWidget->headerItem()->setText(3, "Цена");
    ui->treeWidget->headerItem()->setText(4, "Вес");
    ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->treeWidget->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    while(tempHead){
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
        treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable);
        treeItem->setText(0, QString::number(tempHead->code));
        treeItem->setText(1, QString::fromStdString((tempHead->name)));
        sweet* tempSweetHead;
        tempSweetHead = tempHead->giftget;
        while(tempSweetHead)                                                   //заполнение таблицы
        {
            QTreeWidgetItem *treeLeaf = new QTreeWidgetItem();
            treeLeaf->setFlags(treeLeaf->flags() | Qt::ItemIsEditable);
            treeLeaf->setText(2,  QString::fromStdString(tempSweetHead->name));
            treeLeaf->setText(3, QString::number(tempSweetHead->price));
            treeLeaf->setText(4, QString::number(tempSweetHead->weight));
            treeLeaf->setTextAlignment(3, Qt::AlignCenter);
            treeLeaf->setTextAlignment(4, Qt::AlignCenter);
            treeItem->addChild(treeLeaf);
            tempSweetHead = tempSweetHead->next;
        }
        tempHead = tempHead->next;
    }
}

TableOfTables::~TableOfTables()
{
    delete ui;
}

void TableOfTables::on_pushButton_clicked()    //Выход в главное меню, с переносом данных из таблицы в структуры.
{
    sweettypes* remember;
    remember = NULL;
    sweettypes* Head, * Tail;
    sweet* HeadSweet, * TailSweet;
    Tail = NULL;
    Head = NULL;
    HeadSweet = NULL;
    TailSweet = NULL;
    for (int i = 0; i < (ui->treeWidget->topLevelItemCount()); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        sweettypes *temp;
        temp = new sweettypes;
        remember = temp;
        temp->giftget = NULL;
        temp->next = NULL;
        HeadSweet = NULL;
        temp->code = item->text(0).toInt();
        temp->name = item->text(1).toStdString();
        if (Head == NULL)
        {
            Tail = temp;
            Head = temp;
            for (int g = 0; g < (item->childCount()); g++)
            {
                QTreeWidgetItem *ChildItem = item->child(g);                  //Перенос из таблицы в структуры
                sweet* tempsweet;
                tempsweet = new sweet;
                tempsweet->next = NULL;
                tempsweet->name = ChildItem->text(2).toStdString();
                tempsweet->price = ChildItem->text(3).toInt();
                tempsweet->weight = ChildItem->text(4).toInt();
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
        else
        {
            Tail->next = temp;
            Tail = temp;
            for (int g = 0; g < (item->childCount()); g++)
            {
                QTreeWidgetItem *ChildItem = item->child(g);
                sweet* tempsweet;
                tempsweet = new sweet;
                tempsweet->next = NULL;
                tempsweet->name = ChildItem->text(2).toStdString();
                tempsweet->price = ChildItem->text(3).toInt();
                tempsweet->weight = ChildItem->text(4).toInt();
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
    emit signal(Head);
    this->hide();
}

void TableOfTables::on_pushButton_2_clicked()  //Функция добавления строки типа сладости
{
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable);
    treeItem->setText(0, "0");
    treeItem->setText(1, "НовыйТипСладости");
}

void TableOfTables::on_pushButton_3_clicked() //Функция добавления подстроки сладости в строку типа сладости
{
    if (ui->treeWidget->currentIndex().isValid()) //Проверка на то, выделен ли тип сладости
    {
        if(!(ui->treeWidget->currentItem()->parent())) //Проверка на то, если текущий тип сладости - самый высокий в иерархии
        {
            QTreeWidgetItem *treeLeaf = new QTreeWidgetItem();
            treeLeaf->setFlags(treeLeaf->flags() | Qt::ItemIsEditable);
            treeLeaf->setText(2, "НоваяСладость");
            treeLeaf->setText(3, "0");
            treeLeaf->setText(4, "0");
            ui->treeWidget->currentItem()->addChild(treeLeaf);
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Выберите тип в который надо добавить сладость");   //Предупреждающее окно, при отсутствии выбора типа сладости
        msgBox.exec();
    }
}

void TableOfTables::on_pushButton_4_clicked()  //Функция для удаления типа сладости
{
    if(ui->treeWidget->currentIndex().isValid())        //Проверка на то, выделен ли тип сладости
    {
        if (!(ui->treeWidget->currentItem()->parent()))
        {
        delete ui->treeWidget->currentItem();

        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Выберите тип который надо удалить"); //Предупреждающее окно, при отсутствии выбора типа сладости
        msgBox.exec();
    }
}

void TableOfTables::on_pushButton_5_clicked()   //Функция удаления сладости
{
    if(ui->treeWidget->currentIndex().isValid())        //Проверка на то, выделена ли сладость
    {
        if(ui->treeWidget->currentItem()->parent())
        {
        ui->treeWidget->currentItem()->parent()->removeChild(ui->treeWidget->currentItem());
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Выберите сладость которую надо удалить"); //Предупреждающее окно, при отсутствии выбора сладости
        msgBox.exec();
    }
}
