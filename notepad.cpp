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

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &Notepad::saveAs);
    connect(ui->actionPrint, &QAction::triggered, this, &Notepad::print);
    connect(ui->actionExit, &QAction::triggered, this, &Notepad::close);
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

void Notepad::save() {
    QString fileName;
    if(currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if(fileName.isEmpty()) {
            return;
        }
        currentFile = fileName;
    }
    else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if(fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::print() {
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if(dialog.exec() == QDialog::Rejected) {
        return;
    }
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}
