#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

// Объявление макросов цвета
#define COLOR_ERROR "color: red;"
#define COLOR_OK "color: green;"

// Объявление макросов текстов ошибок
#define DEVIDE_ERROR "Нельзя делить на ноль"
#define NAN_ERROR "Результат не является числом"
#define OP_IS_NOT_CHOSEN "Не выбран оператор"
#define SQRT_ERROR "Нельзя посчитать корень отрицательного числа"
#define INPUT_ERROR "Неверный ввод чисел"
#define OP1_IS_EMPTY "Введите " + ui->element1Label->text()
#define OP2_IS_EMPTY "Введите " + ui->element2Lable->text()
#define OP_BOTH_ARE_EMPTY "Введите " + ui->element1Label->text() + " и " + ui->element2Lable->text()



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Установка размера окна
    this->setFixedSize(727, 212);

    // Установка названия окна
    this->setWindowTitle("Калькулятор");

    // Установка параметров окна ошибки
    errorBox.setWindowTitle("Ошибка!");
    errorBox.setStandardButtons(QMessageBox::Ok);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){

    // Задействование кнопки Return для работы кнопки "Посчитать"
    if(event->key() == Qt::Key_Return){
        Widget::on_summbitBtn_clicked();
    }

    // Задействование кнопки Escape для закрытия программы
    if(event->key() == Qt::Key_Escape){
        this->close();
    }
    // Задействование кнопок "+", "-", "*", "/", "s" для выбора оператора
    if(event->key() == Qt::Key_Plus){
        ui->plusRBtn->setChecked(true);
    }
    if(event->key() == Qt::Key_Minus){
        ui->minusRBtn->setChecked(true);
    }
    if(event->key() == Qt::Key_Asterisk){
        ui->multiplyRBtn->setChecked(true);
    }
    if(event->key() == Qt::Key_Slash){
        ui->devideRBtn->setChecked(true);
    }
    if(event->key() == Qt::Key_S){
        ui->sqrtRBtn->setChecked(true);
    }
}

void Widget::readOperands()
{
    /// Логическая переменная для проверки валидности ввода
    bool ok = false;
    hasError = NoError;
    operand1IsEmpty = false;
    operand2IsEmpty = false;
    // Присваивание числа из поля ввода 1-го операнда
    operand1 = ui->operand1->text().toDouble(&ok);
    // Проверка валидности ввода операнда 1
    if (!setStyleInput(ui->operand1, ok))
    {
        if (ui->operand1->text().isEmpty())
        {
            operand1IsEmpty = true;
        }
        else
        {
            hasError = InputError;
        }
    }
    // Присваивание числа из поля ввода 1-го операнда
    operand2 = ui->operand2->text().toDouble(&ok);
    // Проверка валидности ввода операнда 1
    if (!setStyleInput(ui->operand2, ok))
    {
        if (ui->operand2->text().isEmpty())
        {
            operand2IsEmpty = true;
        }
        else
        {
            hasError = InputError;
        }
    }
}

void Widget::calculate()
{
    if (Operation == None)
    {
        hasError = OpIsNotChosen;
    }

    checkEmpty();

    /*
     * Рассчёт будет проходить только при
     * условии того, что не будет ошибок ввода
     */
    if (hasError == NoError)
    {
        switch (Operation)
        {
            case Plus:
                result = operand1 + operand2;
                break;
            case Minus:
                result = operand1 - operand2;
                break;
            case Multiply:
                result = operand1 * operand2;
                break;
            case Devide:
                // Проверка деления на ноль
                if (operand2 == 0)
                {
                    hasError = DevideError;
                    break;
                }
                else
                {
                    result = operand1 / operand2;
                    break;
                }
            case Sqrt:
                /*
                 * Проверка отрицательности
                 * подкоренного числа
                 */
                if (operand2 < 0)
                {
                    hasError = SqrtError;
                    break;
                }
                else
                {
                    result = sqrt(operand2);
                    break;
                }
        }
        // Проверка на бесконечность и "не число"
        if (result == INFINITY or result == NAN)
        {
            hasError = NANError;
        }
    }

    if (hasError != NoError)
    {
        return errorOutput();
    }

    // Вывод результата в resultLine
    ui->resultLine->setText(QString::number(result));
}

void Widget::refreshStyle()
{
    ui->operand1->show();
    ui->element1Label->show();

    switch (Operation)
    {
        case Plus:
            ui->element1Label->setText("Слагаемое 1");
            ui->element2Lable->setText("Слагаемое 2");
            ui->resultLable->setText("Сумма");
            break;
        case Minus:
            ui->element1Label->setText("Уменьшаемое");
            ui->element2Lable->setText("Вычиатемое");
            ui->resultLable->setText("Разность");
            break;
        case Multiply:
            ui->element1Label->setText("Множитель 1");
            ui->element2Lable->setText("Множитель 2");
            ui->resultLable->setText("Произведение");
            break;
        case Devide:
            ui->element1Label->setText("Делимое");
            ui->element2Lable->setText("Делитель");
            ui->resultLable->setText("Частное");
            break;
        case Sqrt:
            ui->element2Lable->setText("Подкоренное число");
            ui->resultLable->setText("Результат");
            ui->operand1->hide();
            ui->element1Label->hide();
            break;
    }
}

void Widget::errorOutput()
{
    switch (hasError)
    {
    case InputError:
        errorBoxShow(INPUT_ERROR);
        break;
    case DevideError:
        errorBoxShow(DEVIDE_ERROR);
        break;
    case SqrtError:
        errorBoxShow(SQRT_ERROR);
        break;
    case NANError:
        errorBoxShow(NAN_ERROR);
        break;
    case OpIsNotChosen:
        errorBoxShow(OP_IS_NOT_CHOSEN);
        break;
    case Op1Empty:
        errorBoxShow(OP1_IS_EMPTY);
        break;
    case Op2Empty:
        errorBoxShow(OP2_IS_EMPTY);
        break;
    case OpBothEmpty:
        errorBoxShow(OP_BOTH_ARE_EMPTY);
        break;
    }
}

void Widget::checkEmpty()
{
    if (Operation != Sqrt)
    {
        if (operand1IsEmpty and operand2IsEmpty)
        {
            hasError = OpBothEmpty;
        }
        else if (operand1IsEmpty)
        {
            hasError = Op1Empty;
        }
        else if (operand2IsEmpty)
        {
            hasError = Op2Empty;
        }
    }
    if (operand2IsEmpty and Operation == Sqrt)
    {
        hasError = Op2Empty;
    }
}

void Widget::errorBoxShow(QString error)
{
    ui->resultLine->setText("");
    errorBox.setText(error);
    errorBox.show();
    return;
}

bool Widget::setStyleInput(QLineEdit* input, bool ok)
{
    input->setStyleSheet(ok ? COLOR_OK : COLOR_ERROR);
    return ok;
}

void Widget::on_summbitBtn_clicked()
{
    calculate();
}

void Widget::on_plusRBtn_clicked()
{
    Operation = Plus;
    ui->resultLine->setText("");
    readOperands();
    refreshStyle();
}

void Widget::on_minusRBtn_clicked()
{
    Operation = Minus;
    ui->resultLine->setText("");
    readOperands();
    refreshStyle();
}

void Widget::on_multiplyRBtn_clicked()
{
    Operation = Multiply;
    ui->resultLine->setText("");
    readOperands();
    refreshStyle();
}

void Widget::on_devideRBtn_clicked()
{
    Operation = Devide;
    ui->resultLine->setText("");
    readOperands();
    refreshStyle();
}

void Widget::on_sqrtRBtn_clicked()
{
    Operation = Sqrt;
    ui->resultLine->setText("");
    ui->operand1->setText("");
    readOperands();
    refreshStyle();
}


void Widget::on_operand1_textChanged()
{
    readOperands();
    refreshStyle();
}


void Widget::on_operand2_textChanged()
{
    readOperands();
    refreshStyle();
}

