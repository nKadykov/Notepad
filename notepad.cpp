#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include "notepad.h"
#include "./ui_notepad.h" // заголовочный файл UI

Notepad::Notepad(QWidget *parent) // определение конструктора Notepad
    : QMainWindow(parent) // вызов QMainWindow конструктора
    , ui(new Ui::Notepad) // создание экземпляра класса UI и назначение его члену ui
{
    ui->setupUi(this); // установка ui
}

Notepad::~Notepad() // определение деструктора
{
    delete ui;
}

void Notepad::newDocument()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the File");
    if(fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

