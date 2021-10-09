#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "character.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    /// Словарь с текстовым представлением классов персонажа
    std::map<CharacterClass, std::string> classMap {{None, "Неизвестный"}, {NoneG, "Не выбран пол"} {Tank, "Танк"}, {Warrior, "Воин"},
                                                    {Mage, "Волшебник"}, {Knight, "Рыцарь"}, {Paladin, "Паладин"},
                                                    {Bard, "Бард" }, {Master, "Мастер"}, {NoneF, "Неизвестная"},
                                                    {WarriorF, "Воительница"}, {MageF, "Волшебница"}};
    /// Переменная персонажа
    Character character;
    /// Функция для обновления информации в UI
    void refreshCharacterInfo();
    /// Функция для изменения показателей
    void setStatText(QLabel*, int);
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_strengthPlusButton_clicked();
    void on_agilityPlusButton_clicked();
    void on_intelligencePlusButton_clicked();
    void on_endurancePlusButton_clicked();
    void on_strengthMinusButton_clicked();
    void on_agilityMinusButton_clicked();
    void on_intelligenceMinusButton_clicked();
    void on_enduranceMinusButton_clicked();
    void on_maleButton_clicked();
    void on_femaleButton_clicked();
    void on_nameEdit_textEdited(const QString &arg1);
    void on_createButton_clicked();

private:
    QMessageBox msgBox;
    /// Функция для вызова сообщения
    void callMessageBox(QString);
    /// Функция для вызова окна с Ошибкой
    void callErrorBox(QString);
    /// Функция для изменения характеристик персонажа
    void changeCharacterStats(CharacterStat cs, Operation op);
    void changeStatLabelColor(QLabel*, int);
    Ui::Widget *ui;
};
#endif // WIDGET_H
