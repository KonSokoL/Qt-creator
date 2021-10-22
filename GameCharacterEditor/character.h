#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#define MAX_POINTS 20 //Максимальное количество очков прокачки

#define HEALTH_RATE 9 // Здоровья за единицу силы
#define DAMAGE_RATE 6 // Урона за единицу ловкости
#define MANA_RATE 11 // Маны за единицу интеллекта
#define WEIGHT_RATE 5.5 // Веса за единицу выносливости

#define DEF_STRENGTH 1 // Начальное значение силы
#define DEF_DEXTERITY 1 // Начальное значение ловкости
#define DEF_INTELLIG 0 // Начальное значение интеллекта
#define DEF_ENDURANCE 1 // Начальное значение выносливости

/*
 * Коэффициент, при котором характеристики
 * персонажа будут объединятся в новый класс
 */
#define CLASS_UNION_RATIO 1.5

/// Пол персонажа
enum Gender{
    None, Male, Female
};


/// Типа операции с характеристикой персонажа
enum Operation{
    Increment, Decrement
};

/// Первинчные характеристики персонажа
enum CharacterStat{
    Strength, Agility, Intelligence, Endurance
};

/// Возможные классы персонажей
enum CharacterClass{
    NoneG, Tank, TankF,
    Warrior, WarriorF, Mage, MageF,
    Knight, KnightF, Paladin, PaladinF,
    Bard, BardF, Master, MasterF
};


/// Сущность персонажа
class Character{
private:
    /// Переменная класса персонажа
    CharacterClass ch_class = NoneG;
    /// Установка класса персонажа
    void setCharacterClass(CharacterClass);
    /// Проверка на пол персонажа
    void setGenderClass(CharacterClass);
public:
    // Конструктор
    Character(){
        // Установка начальных характеристик персонажу
        strength = DEF_STRENGTH, agility = DEF_DEXTERITY, intelligence = DEF_INTELLIG, endurance = DEF_ENDURANCE;
        // Расчёт вторичных характеристик
        calculateSecondaryCharacterValues();
    }
    /// Имя персонажа
    std::string name;
    /// Пол персонажа
    Gender gender = Gender::None;
    // Первичные характеристики
    int strength = 0, agility = 0, intelligence = 0, endurance = 0;
    // Вторичные характеристики
    float health = 0, damage = 0, mana = 0, weight = 0;
    /// Количество свободных очков прокачки
    int maxAvailablePoints = MAX_POINTS;

    /// Функция расчёта вторичных характеристик
    void calculateSecondaryCharacterValues();
    /// Функция изменения первичных характеристик
    int changeStat(CharacterStat cs, Operation op);
    /**
     * Фукнция для определения класса персонажа на основе характеристи
     * c использованием стандартных и тернарных условных конструкций
     */
    void calculateClass();
    /// Геттер класса персонажа
    inline CharacterClass getClass(){return ch_class;}
    inline Gender getGender(){return gender;}
};

#endif // CHARACTER_H
