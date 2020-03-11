#include "numbersort.h"
#include "Random.h"
#include "ui_numbersort.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QProcess>

NumberSort::NumberSort(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NumberSort)
{
    ui->setupUi(this);
}

NumberSort::~NumberSort()
{
    delete ui;
}

void NumberSort::quickSort(QVector <int>& array, int left, int right)
{
    int i = left, j = right;
    int temp;
    int pivot = array[(left + right) / 2];

    while (i <= j)
    {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;
        if (i <= j)
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
    if (left < j) quickSort(array, left, j);
    if (i < right) quickSort(array, i, right);
}


void NumberSort::on_SortArray_clicked()
{
    QString buff;
    QString check;
    QTime timer;
    int time;
    QVector<int> array ;
    if(flag)
    {
        // Creating File:"output.txt"
        QFile Input("input.txt");
        QFile Output("output.txt");
        if(!Input.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            ui->statusBar->showMessage("Файл 'input.txt' не был создан.");
            return;
        }

        if(!Output.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
        {
            ui->statusBar->showMessage("Файл 'output.txt' не был создан.");
            return;
        }
        Output.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate);
        // Reading from "input" file
        QTextStream readstream(&Input);
        while(!readstream.atEnd())
        {
            readstream >> buff;
            array.push_back(buff.toInt());
        }
        Input.close();

        // Sort function
        quickSort(array,0,array.size() - 1);

        // Writting sorted array
        buff = "";
        QTextStream writestream(&Output);
        timer.start();
        for(int i = 1; i < array.size(); i++)
        {
            buff =QString::number(array[i]) +  " ";
            writestream << buff;
            buff = "";
        }
        time = timer.elapsed();
        QMessageBox::information(this,"Info","Массив был отсортирован за " + QString::number(time) + " миллисекунд ");
        Output.close();

    }
    else
    {
         ui->statusBar->showMessage("Не был создан массив чисел");
         return;
    }
}

void NumberSort::on_CreatArray_clicked()
{
   bool ok;
   int buff;
   QString str;
   QString Number = ui->lineEdit->text();
   N = Number.toInt(&ok,10);

   // Cheaking of N - amount of numbers
   if(!ok)
   {
       ui->statusBar->showMessage("Ошибка! Введено не число");
       return;
   }else if(N <= 0)
   {
           ui->statusBar->showMessage("Число N должно быть больше 0");
           return;
   }
   flag = true;
   ui->statusBar->clearMessage();

   //Creating File:"input.txt"

   QFile Input("input.txt");
   if(!Input.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
   {
       ui->statusBar->showMessage("Файл 'input.txt' не был создан.");
   }

   // Changing of stream
   QTextStream writestream(&Input);

   // Creating and writing random number of 1 to 1 million

   for(int i = 0; i < N; i++)
   {
       buff = Random::get(1,N);
       str.setNum(buff);
       str += " ";
       writestream << str;
   }

   // Show that work is done
   str = "";
   str += QString::number(N) + " Чисел было сгенерированно.";

   QMessageBox::information(this,"Info",str);

   Input.close();
}


void NumberSort::on_ShowCreatedArray_clicked()
{
    if(flag)
    {
    QProcess* proc=new QProcess(this);
    proc->start("notepad ../build-TypeOfSort-Desktop_x86_windows_msys_pe_32bit-Debug/input.txt");
    }
    else
    {
        ui->statusBar->showMessage("Не был создан массив чисел для просмотра");
        return;
    }
}

void NumberSort::on_ShowSortArray_clicked()
{
    if(flag)
    {
    QProcess* proc=new QProcess(this);
    proc->start("notepad ../build-TypeOfSort-Desktop_x86_windows_msys_pe_32bit-Debug/output.txt");
    }
    else
    {
        ui->statusBar->showMessage("Не был создан массив чисел для обработки просмотра");
        return;
    }
}
