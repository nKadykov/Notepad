#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow> // включает QMainWindow, который предоставляет окно главного приложения

QT_BEGIN_NAMESPACE
namespace Ui { // объявление класса Notepad в пространстве имён Ui, который является стандартным пространством имён для UI классов, генерируемых из .ui файлов
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT // макрос, который должен стоять первым в определении класса и объявляет наш класс как QObject

public:
    Notepad(QWidget *parent = nullptr); // объявление конструктора с аргументом по умолчанию parent, nullptr обозначает, что виджет не имеет родителей
    ~Notepad(); // виртуальный деструктор для освобождения ресурсов

private slots:
    void newDocument();
    void open();

private:
    Ui::Notepad *ui; // указатель на класс UI
    QString currentFile;
};
#endif // NOTEPAD_H
