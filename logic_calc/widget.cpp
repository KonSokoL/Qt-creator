#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Установка названия окна
    this->setWindowTitle("Logical calculator");

    //Установка размера окна
    this->setFixedSize(664, 94);

    //Установка стиля для logOper1, logOper2 и operationBox
    ui->logOper1->setStyleSheet
            ("QComboBox { background-color: white; color: black} ");
    ui->logOper2->setStyleSheet
            ("QComboBox { background-color: white; color: black}");
    ui->operationBox->setStyleSheet
            ("QComboBox { background-color: white; color: black}");

    // Расчёт логического выражения при запуске программы
    logCalculation();
}

Widget::~Widget()
{
    delete ui;
}

/**
 * Перечисление операций в порядке, совпадающим
 * с индексами элементов в списке operationBox
 */
enum Operations
{
    /// И
    AND,
    /// ИЛИ
    OR,
    /// НЕ
    NOT,
    /// ИСКЛЮЧАЮЩИЕ ИЛИ
    XOR,
    /// РАВНО
    EQUAL,
    /// НЕРАВНО
    NOTEQUAL
};

/// Функция вычисления логического выражения
void Widget::logCalculation()
{
    QPalette p; // Переменная палитры для изменения цвета окна
    bool result; // Объявление логической переменной для результата вычисления

    /*
     * Условие для появления выпадающего списка logOper1,
     * если он до этого был спрятан
     */
    if (ui->logOper1->isHidden())
    {
        ui->logOper1->show();
    }

    /*
     * Считывание индекса элементов из списков logOper1 и logOper2 и
     * присваивание их logOper1_index и logOper2_index соответсвенно
     */
    bool logOper1_index = ui->logOper1->currentIndex();
    bool logOper2_index = ui->logOper2->currentIndex();
    ui->errorLabel->setText("");

    // Конструкция switch case для выбора операции
    switch (ui->operationBox->currentIndex())
    {
        case AND:
            result = logOper1_index & logOper2_index;
            break;
        case OR:
            result = logOper1_index | logOper2_index;
            break;
        case NOT:
            ui->logOper1->hide();
            result = !logOper2_index;
            break;
        case XOR:
            result = logOper1_index ^ logOper2_index;
            break;
        case EQUAL:
            result = logOper1_index == logOper2_index;
            break;
        case NOTEQUAL:
            result = logOper1_index != logOper2_index;
            break;
        default:
            p.setColor(QPalette::Window, Qt::red);
            ui->errorLabel->setText("Нераспознанная функция");
            break;
    }

    /*
     * Изменение цветовой палитры окна в красный или зеленый цвет
     * в зависимости от результата вычисления логического выражения
     */
    p.setColor(QPalette::Window, (result ? Qt::green : Qt::red));
    this->setPalette(p);
}

/// Слот, если что-то поменялось в logOper1
void Widget::on_logOper1_currentIndexChanged(int index)
{
    logCalculation();
}

/// Слот, если что-то поменялось в operationBox
void Widget::on_operationBox_currentIndexChanged(int index)
{
    logCalculation();
}

/// Слот, если что-то поменялось в logOper2
void Widget::on_logOper2_currentIndexChanged(int index)
{
    logCalculation();
}
