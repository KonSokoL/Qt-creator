#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qmessagebox.h>
#include <QLineEdit>
#include <math.h>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    /// Окно ошибок
    QMessageBox errorBox;

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    /// Обработчик событий для работы с клавиатурой
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_summbitBtn_clicked();

    void on_sqrtRBtn_clicked();

    void on_plusRBtn_clicked();

    void on_minusRBtn_clicked();

    void on_multiplyRBtn_clicked();

    void on_devideRBtn_clicked();

    void on_operand1_textChanged();

    void on_operand2_textChanged();

private:
    // Объявление переменных операндов 1, 2 и результата
    double operand1 = 0, operand2 = 0, result = 0;
    /// Переменная ошибки
    int hasError = NoError;
    /// Переменная операции
    int Operation = None;
    // Логические переменные для проверки пустоты полей ввода
    bool operand1IsEmpty = false, operand2IsEmpty = false;
    /// Перечисление ошибок
    enum Errors {NoError, Op1Empty, Op2Empty,
                 OpBothEmpty, InputError, DevideError,
                 SqrtError, NANError, OpIsNotChosen};
    /// Перечисление операций
    enum Operations {None, Plus, Minus, Multiply, Devide, Sqrt};
    /// Функция чтения и проверки значений
    void readOperands();
    /// Функция рассчёта выражения
    void calculate();
    /// Функция выбора и вывода ошибки
    void errorOutput();
    /// Функция проверки пустоты
    void checkEmpty();
    /// Функция изменения цвета строки ввода в зависимости от валидности ввода
    bool setStyleInput(QLineEdit *, bool);
    /// Показ окна ошибки
    void errorBoxShow(QString);
    /// Функция обновления стиля окна
    void refreshStyle();

    Ui::Widget *ui;
};
#endif // WIDGET_H
