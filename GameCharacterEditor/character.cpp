#include "character.h"

void Character::calculateSecondaryCharacterValues(){
    health = strength * HEALTH_RATE;
    damage = agility * DAMAGE_RATE;
    mana = intelligence * MANA_RATE;
    weight = endurance * WEIGHT_RATE;
}

void Character::calculateClass(){
    if (gender == Gender::None)
    {
        setCharacterClass(NoneG);
    }
    if(strength >= agility and strength >= intelligence)
    {
        if(agility == intelligence)
            (float)strength / agility < CLASS_UNION_RATIO ? setCharacterClass(Master) : setCharacterClass(Tank);
        else if(agility > intelligence)
            (float)strength / agility < CLASS_UNION_RATIO ? setCharacterClass(Knight) : setCharacterClass(Tank);
        else
            (float)strength /  intelligence < CLASS_UNION_RATIO ? setCharacterClass(Paladin) : setCharacterClass(Tank);

    }
    else if(agility >= strength and agility >= intelligence)
    {
        if(strength == intelligence)
        {
            (float)agility / strength < CLASS_UNION_RATIO ? setCharacterClass(Master) : setCharacterClass(Warrior);
            if (gender == Gender::Female and ch_class == CharacterClass::Warrior)
            {
                setCharacterClass(WarriorF);
            }
        }
        else if(strength > intelligence)
        {
            (float)agility / strength < CLASS_UNION_RATIO ? setCharacterClass(Knight) : setCharacterClass(Warrior);
            if (gender == Gender::Female and ch_class == CharacterClass::Warrior)
            {
                setCharacterClass(WarriorF);
            }
        }
        else
        {
            (float)agility / intelligence < CLASS_UNION_RATIO ? setCharacterClass(Bard) : setCharacterClass(Warrior);
            if (gender == Gender::Female and ch_class == CharacterClass::Warrior)
            {
                setCharacterClass(WarriorF);
            }
        }

    }
    else if(intelligence >= agility and intelligence >= strength)
    {
        if(strength == agility)
        {
            (float)agility / strength < CLASS_UNION_RATIO ? setCharacterClass(Master) : setCharacterClass(Mage);
            if (gender == Gender::Female and ch_class == CharacterClass::Mage)
            {
                setCharacterClass(MageF);
            }
        }
        else if(strength > agility)
        {
            (float)intelligence / agility < CLASS_UNION_RATIO ? setCharacterClass(Bard) : setCharacterClass(Mage);
            if (gender == Gender::Female and ch_class == CharacterClass::Mage)
            {
                setCharacterClass(MageF);
            }
        }
        else
        {
            (float)intelligence / strength < CLASS_UNION_RATIO ? setCharacterClass(Paladin) : setCharacterClass(Mage);
            if (gender == Gender::Female and ch_class == CharacterClass::Mage)
            {
                setCharacterClass(MageF);
            }
        }
    }
    if (gender == Gender::Female and ch_class == CharacterClass::Warrior)
    {
        setCharacterClass(WarriorF);
    }
}

void Character::setCharacterClass(CharacterClass cc)
{
    ch_class = cc;
}

int Character::changeStat(CharacterStat cs, Operation op)
{
    int* statValue = nullptr;
    int minLimit = 0;
    switch (cs)
    {
        case Strength:
            statValue = &strength;
            minLimit = DEF_STRENGTH;
        break;
        case Agility:
            statValue = &agility;
            minLimit = DEF_DEXTERITY;
        break;
        case Intelligence:
            statValue = &intelligence;
            minLimit = DEF_INTELLIG;
        break;
        case Endurance:
            statValue = &endurance;
            minLimit = DEF_ENDURANCE;
        break;
    }
    switch(op)
    {
        case Increment:
            if(*statValue == 10)
            {
                return -1;
            }
            if(maxAvailablePoints >= 0)
            {
                (*statValue)++;
                maxAvailablePoints--;
            }
            if(maxAvailablePoints == -1)
            {
                (*statValue)--;
                maxAvailablePoints = 0;
                return -2;
            }
        break;
        case Decrement:
            if(*statValue > minLimit)
            {
                (*statValue)--;
                maxAvailablePoints++;
            }
        break;
    }
    calculateSecondaryCharacterValues();
    calculateClass();
    return *statValue;
}
