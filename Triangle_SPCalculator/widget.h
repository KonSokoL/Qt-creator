#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "Triangle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    Triangle trngl;
    void calculateAll();
    ~Widget();

private slots:
    void on_summbitBtn_clicked();

    void on_x1InputLine_textChanged(const QString);

    void on_y1InputLine_textChanged(const QString);

    void on_x2InputLine_textChanged(const QString);

    void on_y2InputLine_textChanged(const QString);

    void on_x3InputLine_textChanged(const QString);

    void on_y3InputLine_textChanged(const QString);

    void on_checkTriangleExistsBox_stateChanged();

private:
    bool hasError = false;
    bool inputIsEmpty = false;
    void readAllPoints();
    void refreshResultStyle();
    bool checkAndEditInput(QLineEdit*, bool);
    void errorOrEmpty(QLineEdit*);

    Ui::Widget *ui;
};
#endif // WIDGET_H
