#include "widget.h"
#include "ui_widget.h"
#include <QKeyEvent>

// Declaring color macros
#define COLOR_ERROR "color: red;"
#define COLOR_OK "color: green;"

// Declaring error text macros
#define DEVIDE_ERROR "Cannot be divided by zero"
#define NAN_ERROR "Result is not a number"
#define OP_IS_NOT_CHOSEN "No operator selected"
#define SQRT_ERROR "The square root of a negative number cannot be calculated."
#define INPUT_ERROR "Invalid number entry"
#define OP1_IS_EMPTY "Entry " + ui->element1Label->text()
#define OP2_IS_EMPTY "Entry " + ui->element2Lable->text()
#define OP_BOTH_ARE_EMPTY "Entry " + ui->element1Label->text() + " and " + ui->element2Lable->text()



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Setting fixed size for a window
    this->setFixedSize(727, 212);

    // Setting title of a window
    this->setWindowTitle("Calculator");

    // Setting parameters of error window
    errorBox.setWindowTitle("Error!");
    errorBox.setStandardButtons(QMessageBox::Ok);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){

    // Using the Return Button to Work the Calculate Button
    if(event->key() == Qt::Key_Return){
        Widget::on_summbitBtn_clicked();
    }

    // Using the Escape button to close the program
    if(event->key() == Qt::Key_Escape){
        this->close();
    }
    // Using the "+", "-", "*", "/", "s" buttons to select an operator
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
    /// Boolean variable for checking input validity
    bool ok = false;
    hasError = NoError;
    operand1IsEmpty = false;
    operand2IsEmpty = false;
    // Assigning a number from the input field of the 1st operand
    operand1 = ui->operand1->text().toDouble(&ok);
    // Checking the validity of the input of the 1st operand
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
    // Assigning a number from the input field of the 2nd operand
    operand2 = ui->operand2->text().toDouble(&ok);
    // Checking the validity of the input of the 2nd operand
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
     * The calculation will take place only 
     * on the condition that there are 
     * no input errors
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
                // Division by zero check
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
                 * Checking the negativeness 
                 * of a radical number
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
        // Checking for infinity and "not a number"
        if (result == INFINITY or result == NAN)
        {
            hasError = NANError;
        }
    }

    if (hasError != NoError)
    {
        return errorOutput();
    }

    // Outputting the result to resultLine
    ui->resultLine->setText(QString::number(result));
}

void Widget::refreshStyle()
{
    ui->operand1->show();
    ui->element1Label->show();

    switch (Operation)
    {
        case Plus:
            ui->element1Label->setText("Addend 1");
            ui->element2Lable->setText("Addend 2");
            ui->resultLable->setText("Sum");
            break;
        case Minus:
            ui->element1Label->setText("Minuend");
            ui->element2Lable->setText("Subtrahend");
            ui->resultLable->setText("Difference");
            break;
        case Multiply:
            ui->element1Label->setText("Multiplicanda");
            ui->element2Lable->setText("Multiplier");
            ui->resultLable->setText("Product");
            break;
        case Devide:
            ui->element1Label->setText("Dividend");
            ui->element2Lable->setText("Divisor");
            ui->resultLable->setText("Quotient");
            break;
        case Sqrt:
            ui->element2Lable->setText("Radical number");
            ui->resultLable->setText("Result");
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

