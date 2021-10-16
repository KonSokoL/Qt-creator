#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QMessageBox errorBox;

    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // Объявление функции для последующего его использования
    void logCalculation();

    void on_logOper1_currentIndexChanged(int index);

    void on_operationBox_currentIndexChanged(int index);

    void on_logOper2_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
