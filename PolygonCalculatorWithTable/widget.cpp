#include "widget.h"
#include "ui_widget.h"

#define COLOR_OK "color:white;"
#define COLOR_ERROR "color:red;"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    calculateAll();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::addPoint()
{
    ui->pointTable->insertRow(ui->pointTable->rowCount());
    QTableWidgetItem *item = ui->pointTable->item(ui->pointTable->rowCount()-1, 0);
    if(!item)
                {
                    item = new QTableWidgetItem;
                    ui->pointTable->setItem(ui->pointTable->rowCount()-1, 0, item);
                }
    Point *point = new Point;
    points.insert({item, point});
    ui->pointTable->setItem(ui->pointTable->rowCount()-1, 1, new QTableWidgetItem(points.at(item)->x));
    ui->pointTable->setItem(ui->pointTable->rowCount()-1, 2, new QTableWidgetItem(points.at(item)->y));
    item->setText(POINT_NAME + QString::number(ui->pointTable->rowCount()));
    ui->pointTable->item(ui->pointTable->rowCount()-1, 1)->setText(QString::number(points.at(item)->x));
    ui->pointTable->item(ui->pointTable->rowCount()-1, 2)->setText(QString::number(points.at(item)->y));
}

double Widget::dabs(double x)
{
    if(x >= 0)
    {
        return x;
    }
    return -1 * x;
}

std::vector<Point> Widget::getVectorPoints()
{
    std::vector<Point> v_points;
    for(int i = 0; i < ui->pointTable->rowCount(); i++)
    {
        v_points.push_back(*points.at(ui->pointTable->item(i, 0)));
    }
    return v_points;
}

double Widget::vectorMultiple(double x1, double y1, double x2, double y2){
    return x1 * y2 - x2 * y1;
}

bool Widget::checkCross(Point p1, Point p2, Point p3, Point p4){
    double v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    v1 = vectorMultiple(p4.x-p3.x, p4.y-p3.y , p1.x-p3.x, p1.y-p3.y);
    v2 = vectorMultiple(p4.x-p3.x, p4.y-p3.y , p2.x-p3.x, p2.y-p3.y);
    v3 = vectorMultiple(p2.x-p1.x , p2.y-p1.y , p3.x-p1.x , p3.y-p1.y);
    v4 = vectorMultiple(p2.x-p1.x , p2.y-p1.y , p4.x-p1.x , p4.y-p1.y);
    if ((v1 * v2 < 0) && (v3 * v4 < 0))
    {
        return true;
    }
    return false;
}

bool Widget::hasCross(std::vector<Point> v_points){
    /*
     * Если в многоульнике меньше 4-ёх вершин,
     * то он не может самопересекаться,
     * поэтому досрочный выход
     */
    if(points.size() < 4)
    {
        return false;
    }
    bool crossed = false;

    unsigned int counter = 1;
    auto it = v_points.begin();
    auto endIt = --v_points.end();

    // Цикл проверки для стороны начальной и конечной вершин
    while(counter < v_points.size()-1)
    {
        if(checkCross(*(v_points.begin()+counter), *(v_points.begin()+1+counter), *it, *endIt))
        {
            crossed = true;
        }
        counter++;
    }

    //Цикл проверки для всех остальных сторон многоульника
    it = v_points.begin()+3;
    while(it != v_points.end())
    {
        counter = 0;
        while(counter < v_points.size()-3){
            if(checkCross(*(v_points.begin()+counter), *(v_points.begin()+1+counter), *(it-1), *it))
            {
                crossed = true;
            }
            counter++;
        }
        ++it;
    }
    return crossed;
}

void Widget::calculateAll()
{
    if(points.size() < 1)
    {
        return;
    }
    calculatePolygonSides();
    bool crossed = false;
    double s = calculatePolygonSquare(&crossed);
    double p = calculatePerimeter();
    ui->squareEdit->setText(ui->pointTable->rowCount() < 3  ? "не существует" :
                                                          (crossed ? "Самопересекающийся многоугольник" :
                                                                     (s == 0 ? "Вырожденный многоугольник" :
                                                                               QString::number(s, 'f', 2))));
    ui->perimeterEdit->setText(ui->pointTable->rowCount() < 3 ? "Многоугольника": QString::number(p, 'f', 2));
}

double Widget::calculatePerimeter()
{
    double p = 0;
    for(auto it = points.begin(); it != points.end(); ++it)
    {
        p += it->second->side;
    }
    return p;
}

void Widget::calculatePolygonSides()
{
    if(points.size() <= 1) return;
    auto it = points.begin();
    auto end = --points.end();
    end->second->side = sqrt(pow(it->second->x-end->second->x, 2) + pow(it->second->y-end->second->y, 2));
    while(it != end)
    {
        auto p1 = it->second;
        auto p2 = (++it)->second;
        p1->side = sqrt(pow(p2->x-p1->x, 2) + pow(p2->y-p1->y, 2));
    }
}

double Widget::calculatePolygonSquare(bool *crossed = nullptr)
{
    if(points.size() <= 1)
    {
        return 0;
    }
    *crossed = hasCross(getVectorPoints());
    double part1 = 0, part2 = 0;
    auto it = points.begin();
    auto end = --points.end();
    part1 += end->second->x * it->second->y;
    part2 += end->second->y * it->second->x;
    while(it != end)
    {
        int x1 = it->second->x, y1 = it->second->y;
        ++it;
        part1+=x1*it->second->y;
        part2+=y1*it->second->x;
    }
    return dabs((part1-part2)/2);
}

bool Widget::checkEditInput(QLineEdit* input, bool ok)
{
    input->setStyleSheet(ok ? COLOR_OK : COLOR_ERROR);
    return ok;
}

void Widget::refreshCoordinates()
{
    QTableWidgetItem *item = ui->pointTable->item(ui->pointTable->currentRow(), 0);
    ui->pointTable->item(ui->pointTable->currentRow(), 1)->setText(QString::number(points.at(item)->x));
    ui->pointTable->item(ui->pointTable->currentRow(), 2)->setText(QString::number(points.at(item)->y));
}

void Widget::on_addPointBtn_clicked()
{
    addPoint();
    calculateAll();
}


void Widget::on_removePointBtn_clicked()
{
    ui->pointTable->setCurrentItem(nullptr);
    if(ui->pointTable->rowCount() < 1)
    {
        return;
    }
    QTableWidgetItem *item = ui->pointTable->takeItem(ui->pointTable->rowCount()-1, 0);
    points.erase(item);
    delete item;
    ui->pointTable->removeRow(ui->pointTable->rowCount()-1);
    calculateAll();
}

void Widget::on_xEdit_textChanged(const QString &arg1)
{
    if (!(ui->pointTable->selectedItems().count() > 0))
    {
        return;
    }
    bool ok = true;
    int x = arg1.toInt(&ok);
    if (checkEditInput(ui->xEdit, ok))
    {
        ui->pointTable->selectedItems()[0]->setForeground(Qt::white);
        points.at(ui->pointTable->selectedItems()[0])->x = ok ? x : 0;
        calculateAll();
    }
    refreshCoordinates();
}


void Widget::on_yEdit_textChanged(const QString &arg1)
{
    if (!(ui->pointTable->selectedItems().count() > 0))
    {
        return;
    }
    bool ok = true;
    int x = arg1.toInt(&ok);
    if (checkEditInput(ui->yEdit, ok))
    {
        points.at(ui->pointTable->selectedItems()[0])->y = ok ? x : 0;
        calculateAll();
    }
    refreshCoordinates();
}


void Widget::on_pointTable_itemSelectionChanged()
{
    ui->xEdit->setText(QString::number(points.at(ui->pointTable->item(ui->pointTable->currentRow(), 0))->x));
    ui->yEdit->setText(QString::number(points.at(ui->pointTable->item(ui->pointTable->currentRow(), 0))->y));
    calculateAll();
}

