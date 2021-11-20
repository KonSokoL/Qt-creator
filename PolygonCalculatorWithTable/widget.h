#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QItemSelectionModel>
#include <map>
#include <vector>
#include <math.h> //sqrt, pow

#include "point.h"

#define POINT_NAME "Точка "

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    std::map<QTableWidgetItem*, Point*> points;
    /// Функция добавления новой точки
    void addPoint();
    /// Расчёт модуля для вещественного числа
    double dabs(double x);
    /// Функция произведения векторов
    double vectorMultiple(double x1, double y1, double x2, double y2);
    /// Функция проверки пересечения 2-ух отрезков
    bool checkCross(Point p1, Point p2, Point p3, Point p4);
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addPointBtn_clicked();

    void on_removePointBtn_clicked();

    void on_xEdit_textChanged(const QString &arg1);

    void on_yEdit_textChanged(const QString &arg1);

    void on_pointTable_itemSelectionChanged();

private:
    /// Расчёт периметра многоульника
    double calculatePerimeter();
    /// Рассчитывает стороны соединения всех вершин многоугольника
    void calculatePolygonSides();
    /// Расчёт площади многоульника
    double calculatePolygonSquare(bool*);
    /// Функция проверки на наличие в многоульнике пересекающихся сторон
    bool hasCross(std::vector<Point>);
    std::vector<Point> getVectorPoints();
    void calculateAll();
    void refreshCoordinates();
    bool checkEditInput(QLineEdit*, bool);
    Ui::Widget *ui;
};
#endif // WIDGET_H
