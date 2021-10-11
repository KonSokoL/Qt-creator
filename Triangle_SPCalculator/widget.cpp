#include "widget.h"
#include "ui_widget.h"

#define COLOR_OK "color:green"
#define COLOR_ERROR "color:red"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(410, 472);
    this->setWindowTitle("Калькулятор периметра и площади треугольника");
    readAllPoints();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::calculateAll() {
    double p = trngl.getPerimeter();
    double s = trngl.getSquare();
    ui->squareOutputLine->setText(QString::number(s, 'f', 2));
    ui->perimeterOutputLine->setText(QString::number(p, 'f', 2));
}

void Widget::readAllPoints()
{
    hasError = false;
    inputIsEmpty = false;
    bool ok = false;

    trngl.point1.x = ui->x1InputLine->text().toInt(&ok);
    if (!checkAndEditInput(ui->x1InputLine, ok))
    {
        errorOrEmpty(ui->x1InputLine);
    }
    trngl.point1.y = ui->y1InputLine->text().toInt(&ok);
    if (!checkAndEditInput(ui->y1InputLine, ok))
    {
        errorOrEmpty(ui->y1InputLine);
    }
    trngl.point2.x = ui->x2InputLine->text().toInt(&ok);
    if (!checkAndEditInput(ui->x2InputLine, ok))
    {
        errorOrEmpty(ui->x2InputLine);
    }
    trngl.point2.y = ui->y2InputLine->text().toInt(&ok);
    if (!checkAndEditInput(ui->y2InputLine, ok))
    {
        errorOrEmpty(ui->y2InputLine);
    }
    trngl.point3.x = ui->x3InputLine->text().toInt(&ok);
    if (!checkAndEditInput(ui->x3InputLine, ok))
    {
        errorOrEmpty(ui->x3InputLine);
    }
    trngl.point3.y = ui->y3InputLine->text().toInt(&ok);
    if (!checkAndEditInput(ui->y3InputLine, ok))
    {
        errorOrEmpty(ui->y3InputLine);
    }

    if (hasError or inputIsEmpty or (!trngl.checkTriangleExists() and ui->checkTriangleExistsBox->isChecked())) {
        return refreshResultStyle();
    }

    calculateAll();
}

bool Widget::checkAndEditInput(QLineEdit* inputLine, bool ok)
{
    inputLine->setStyleSheet(ok ? COLOR_OK : COLOR_ERROR);
    refreshResultStyle();
    return ok;
}

void Widget::refreshResultStyle(){
    if (hasError)
    {
        ui->perimeterOutputLine->setText("Ошибка расчёта");
        ui->perimeterOutputLine->setStyleSheet(COLOR_ERROR);
        ui->squareOutputLine->setText("Ошибка расчёта");
        ui->squareOutputLine->setStyleSheet(COLOR_ERROR);
    }
    else if (inputIsEmpty)
    {
        ui->perimeterOutputLine->setText("Введите");
        ui->perimeterOutputLine->setStyleSheet(COLOR_ERROR);
        ui->squareOutputLine->setText("координаты");
        ui->squareOutputLine->setStyleSheet(COLOR_ERROR);
    }

    else if (!trngl.checkTriangleExists() and ui->checkTriangleExistsBox->isChecked())
    {
        ui->perimeterOutputLine->setText("Треугольника");
        ui->perimeterOutputLine->setStyleSheet(COLOR_ERROR);
        ui->squareOutputLine->setText("не существует");
        ui->squareOutputLine->setStyleSheet(COLOR_ERROR);
    }
    else
    {
        ui->perimeterOutputLine->setStyleSheet(COLOR_OK);
        ui->squareOutputLine->setStyleSheet(COLOR_OK);
    }
}

void Widget::errorOrEmpty(QLineEdit* input)
{
    if (input->text() == "")
    {
        inputIsEmpty = true;
    }
    else
    {
        hasError = true;
    }
}

void Widget::on_x1InputLine_textChanged(const QString)
{
    readAllPoints();
}


void Widget::on_y1InputLine_textChanged(const QString)
{
    readAllPoints();
}


void Widget::on_x2InputLine_textChanged(const QString)
{
    readAllPoints();
}


void Widget::on_y2InputLine_textChanged(const QString)
{
    readAllPoints();
}


void Widget::on_x3InputLine_textChanged(const QString)
{
    readAllPoints();
}


void Widget::on_y3InputLine_textChanged(const QString)
{
    readAllPoints();
}

void Widget::on_summbitBtn_clicked()
{
    readAllPoints();
}

void Widget::on_checkTriangleExistsBox_stateChanged()
{
    readAllPoints();
}

