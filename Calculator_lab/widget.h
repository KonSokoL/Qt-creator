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
    /// Error window
    QMessageBox errorBox;

    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    /// Event handler for working with the keyboard
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
    // Declaring variable operands 1, 2 and result
    double operand1 = 0, operand2 = 0, result = 0;
    /// Error variable
    int hasError = NoError;
    /// Operation variable
    int Operation = None;
    // Boolean variables for checking if input fields are empty
    bool operand1IsEmpty = false, operand2IsEmpty = false;
    /// Enumeration of errors
    enum Errors {NoError, Op1Empty, Op2Empty,
                 OpBothEmpty, InputError, DevideError,
                 SqrtError, NANError, OpIsNotChosen};
    /// Enumeration of operations
    enum Operations {None, Plus, Minus, Multiply, Devide, Sqrt};
    /// Function for reading and checking values
    void readOperands();
    /// Calculate function
    void calculate();
    /// Error selection and output function
    void errorOutput();
    /// Empty check function
    void checkEmpty();
    /// Function for changing the color of the input line depending on the validity of the input
    bool setStyleInput(QLineEdit *, bool);
    /// Error window display function
    void errorBoxShow(QString);
    /// Window style update function
    void refreshStyle();

    Ui::Widget *ui;
};
#endif // WIDGET_H
