#include "globle.h"
#include "warrior.h"

Warrior::Warrior(int id, int role, int headquarters, int city, int vitality, int attack)
{
    iWarriorId = id;
    iRole = role;
    iHeadquarters = headquarters;
    iCity = city;
    iVitality = vitality;
    iAttack = attack;
    isWeaponAmount[geSword] = 0;
    isWeaponAmount[geBomb] = 0;
    isWeaponAmount[geArrow] = 0;
    iArrowUsedOnce = 0;
    iWeaponSum = 0;
}

int Warrior::getId()
{
    return iWarriorId;
}

int Warrior::getRole()
{
    return iRole;
}

int Warrior::getHeadquarters()
{
    return iHeadquarters;
}

int Warrior::getCity()
{
    return iCity;
}

int Warrior::getVitality()
{
    return iVitality;
}

int Warrior::getAttack()
{
    return iAttack;
}

int Warrior::getSwordAmount()
{
    return isWeaponAmount[geSword];
}

int Warrior::getBombAmount()
{
    return isWeaponAmount[geBomb];
}

int Warrior::getArrowAmount()
{
    return isWeaponAmount[geArrow];
}

int Warrior::getArrowUsedOnce()
{
    return iArrowUsedOnce;
}

int Warrior::getWeaponSum()
{
    return iWeaponSum;
}

int Warrior::getCurWeapon()
{
    return iCurWeapon;
}

void Warrior::operateWeaponAmount(int weaponIndex, int op, int amount)
{
    if (0 > weaponIndex || geWeaponAmount <= weaponIndex)
    {
        return ;
    }
    switch (op)
    {
    case geWeaponAdd:
        {
            isWeaponAmount[weaponIndex] += amount;
            iWeaponSum += amount;
            break;
        }
    case geWeaponMinus:
        {
            isWeaponAmount[weaponIndex] -= amount;
            iWeaponSum -= amount;
            break;
        }
    case geArrowUsedOnceAdd:
        {
            isWeaponAmount[weaponIndex] += amount;
            iWeaponSum += amount;
            iArrowUsedOnce += amount;
            break;
        }
    case geArrowUsedOnceMinus:
        {
            isWeaponAmount[weaponIndex] -= amount;
            iWeaponSum -= amount;
            iArrowUsedOnce -= amount;
            break;
        }
    default:
        {
            break;
        }
    }
}

void Warrior::setWeaponSeq()
{
    iCurWeapon = geSword;
    for (int iWeaponIndex = 0; iWeaponIndex < geWeaponAmount; ++ iWeaponIndex)
    {
        if (0 != isWeaponAmount[iWeaponIndex])
        {
            iCurWeapon = iWeaponIndex;
            break;
        }
    }
}

void Warrior::setWeaponNext()
{
    for (int i = 1; i < geWeaponAmount; ++ i)
    {
        int iWeaponIndex = (iCurWeapon + i) % geWeaponAmount;
        if (0 != isWeaponAmount[iWeaponIndex])
        {
            iCurWeapon = iWeaponIndex;
            break;
        }
    }
}

bool Warrior::isWarriorDead()
{
    return (0 >= iVitality);
}

void Dragon::moveWarrior(int direction)
{
    if (geMoveRight == direction)
    {
        ++ iCity;
    }
    else
    {
        -- iCity;
    }
}

void Dragon::attack(Warrior *w)
{
    if (0 >= iWeaponSum)
    {
        return ;
    }
    int iHurtPower = 0;
    switch (iCurWeapon)
    {
    case geSword:
        {
            iHurtPower = iAttack * 2 / 10;
            break;
        }
    case geBomb:
        {
            iHurtPower = iAttack * 4 / 10;
            iVitality -= iHurtPower / 2;
            -- isWeaponAmount[geBomb];
            -- iWeaponSum;
            break;
        }
    case geArrow:
        {
            iHurtPower = iAttack * 3 / 10;
            if (0 < iArrowUsedOnce)
            {
                -- iArrowUsedOnce;
                -- isWeaponAmount[geArrow];
                -- iWeaponSum;
            }
            else
            {
                ++ iArrowUsedOnce;
            }
            break;
        }
    }
    w->hurted(iHurtPower);
}

void Dragon::hurted(int hurtPower)
{
    iVitality -= hurtPower;
}

void Ninja::moveWarrior(int direction)
{
    if (geMoveRight == direction)
    {
        ++ iCity;
    }
    else
    {
        -- iCity;
    }
}

void Ninja::attack(Warrior *w)
{
    if (0 >= iWeaponSum)
    {
        return ;
    }
    int iHurtPower = 0;
    switch (iCurWeapon)
    {
    case geSword:
        {
            iHurtPower = iAttack * 2 / 10;
            break;
        }
    case geBomb:
        {
            iHurtPower = iAttack * 4 / 10;
            -- isWeaponAmount[geBomb];
            -- iWeaponSum;
            break;
        }
    case geArrow:
        {
            iHurtPower = iAttack * 3 / 10;
            if (0 < iArrowUsedOnce)
            {
                -- iArrowUsedOnce;
                -- isWeaponAmount[geArrow];
                -- iWeaponSum;
            }
            else
            {
                ++ iArrowUsedOnce;
            }
            break;
        }
    }
    w->hurted(iHurtPower);
}

void Ninja::hurted(int hurtPower)
{
    iVitality -= hurtPower;
}

void Iceman::moveWarrior(int direction)
{
    iVitality -= iVitality / 10;

    if (geMoveRight == direction)
    {
        ++ iCity;
    }
    else
    {
        -- iCity;
    }
}

void Iceman::attack(Warrior *w)
{
    if (0 >= iWeaponSum)
    {
        return ;
    }
    int iHurtPower = 0;
    switch (iCurWeapon)
    {
    case geSword:
        {
            iHurtPower = iAttack * 2 / 10;
            break;
        }
    case geBomb:
        {
            iHurtPower = iAttack * 4 / 10;
            iVitality -= iHurtPower / 2;
            -- isWeaponAmount[geBomb];
            -- iWeaponSum;
            break;
        }
    case geArrow:
        {
            iHurtPower = iAttack * 3 / 10;
            if (0 < iArrowUsedOnce)
            {
                -- iArrowUsedOnce;
                -- isWeaponAmount[geArrow];
                -- iWeaponSum;
            }
            else
            {
                ++ iArrowUsedOnce;
            }
            break;
        }
    }
    w->hurted(iHurtPower);
}

void Iceman::hurted(int hurtPower)
{
    iVitality -= hurtPower;
}

int Lion::getLoyalty()
{
    return iLoyalty;
}

bool Lion::isLionEscape(int cityEnd)
{
    return (0 >= iLoyalty && iCity != cityEnd);
}

void Lion::moveWarrior(int direction)
{
    iLoyalty -= iDecrease;

    if (geMoveRight == direction)
    {
        ++ iCity;
    }
    else
    {
        -- iCity;
    }
}

void Lion::attack(Warrior *w)
{
    if (0 >= iWeaponSum)
    {
        return ;
    }
    int iHurtPower = 0;
    switch (iCurWeapon)
    {
    case geSword:
        {
            iHurtPower = iAttack * 2 / 10;
            break;
        }
    case geBomb:
        {
            iHurtPower = iAttack * 4 / 10;
            iVitality -= iHurtPower / 2;
            -- isWeaponAmount[geBomb];
            -- iWeaponSum;
            break;
        }
    case geArrow:
        {
            iHurtPower = iAttack * 3 / 10;
            if (0 < iArrowUsedOnce)
            {
                -- iArrowUsedOnce;
                -- isWeaponAmount[geArrow];
                -- iWeaponSum;
            }
            else
            {
                ++ iArrowUsedOnce;
            }
            break;
        }
    }
    w->hurted(iHurtPower);
}

void Lion::hurted(int hurtPower)
{
    iVitality -= hurtPower;
}

void Wolf::moveWarrior(int direction)
{
    if (geMoveRight == direction)
    {
        ++ iCity;
    }
    else
    {
        -- iCity;
    }
}

void Wolf::attack(Warrior *w)
{
    if (0 >= iWeaponSum)
    {
        return ;
    }
    int iHurtPower = 0;
    switch (iCurWeapon)
    {
    case geSword:
        {
            iHurtPower = iAttack * 2 / 10;
            break;
        }
    case geBomb:
        {
            iHurtPower = iAttack * 4 / 10;
            iVitality -= iHurtPower / 2;
            -- isWeaponAmount[geBomb];
            -- iWeaponSum;
            break;
        }
    case geArrow:
        {
            iHurtPower = iAttack * 3 / 10;
            if (0 < iArrowUsedOnce)
            {
                -- iArrowUsedOnce;
                -- isWeaponAmount[geArrow];
                -- iWeaponSum;
            }
            else
            {
                ++ iArrowUsedOnce;
            }
            break;
        }
    }
    w->hurted(iHurtPower);
}

void Wolf::hurted(int hurtPower)
{
    iVitality -= hurtPower;
}
