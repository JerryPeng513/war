#ifndef WARRIOR_H_INCLUDED
#define WARRIOR_H_INCLUDED
#include "globle.h"

class Warrior
{
protected:
    int iWarriorId;
    int iRole;
    int iHeadquarters;
    int iCity;
    int iVitality;
    int iAttack;
    //{isWeaponAmount[geSword], isWeaponAmount[geBomb], isWeaponAmount[geArrow]}
    int isWeaponAmount[geWeaponAmount];
    int iArrowUsedOnce;
    int iWeaponSum;
    int iCurWeapon;
public:
    Warrior(int id, int role, int headquarters, int city, int vitality, int attack);
    int getId();
    int getRole();
    int getHeadquarters();
    int getCity();
    int getVitality();
    int getAttack();
    int getSwordAmount();
    int getBombAmount();
    int getArrowAmount();
    int getArrowUsedOnce();
    int getWeaponSum();
    int getCurWeapon();
    void operateWeaponAmount(int weaponIndex, int op, int amount);
    void setWeaponSeq();
    void setWeaponNext();
    bool isWarriorDead();
    virtual ~Warrior(){};
    virtual void moveWarrior(int direction) = 0;
    virtual void attack(Warrior *w) = 0;
    virtual void hurted(int hurtPower) = 0;
};

class Dragon: public Warrior
{
public:
    Dragon(int id, int role, int headquarters, int city, int vitality, int attack): Warrior(id, role, headquarters, city, vitality, attack)
    {
        ++ iWeaponSum;
        ++ isWeaponAmount[id % geWeaponAmount];
    };
public:
    virtual void moveWarrior(int direction);
    virtual void attack(Warrior *w);
    virtual void hurted(int hurtPower);
};

class Ninja: public Warrior
{
public:
    Ninja(int id, int role, int headquarters, int city, int vitality, int attack): Warrior(id, role, headquarters, city, vitality, attack)
    {
        iWeaponSum += 2;
        ++ isWeaponAmount[id % geWeaponAmount];
        ++ isWeaponAmount[(id + 1) % geWeaponAmount];
    };
public:
    virtual void moveWarrior(int direction);
    virtual void attack(Warrior *w);
    virtual void hurted(int hurtPower);
};

class Iceman: public Warrior
{
public:
    Iceman(int id, int role, int headquarters, int city, int vitality, int attack): Warrior(id, role, headquarters, city, vitality, attack)
    {
        ++ iWeaponSum;
        ++ isWeaponAmount[id % geWeaponAmount];
    };
public:
    virtual void moveWarrior(int direction);
    virtual void attack(Warrior *w);
    virtual void hurted(int hurtPower);
};

class Lion: public Warrior
{
private:
    int iLoyalty;
    int iDecrease;
public:
    Lion(int id, int role, int headquarters, int city, int vitality, int attack, int loyalty, int decrease): Warrior(id, role, headquarters, city, vitality, attack)
    {
        iLoyalty = loyalty;
        iDecrease = decrease;
        ++ iWeaponSum;
        ++ isWeaponAmount[id % geWeaponAmount];
    };
public:
    int getLoyalty();
    bool isLionEscape(int cityEnd);
    virtual void moveWarrior(int direction);
    virtual void attack(Warrior *w);
    virtual void hurted(int hurtPower);
};

class Wolf: public Warrior
{
public:
    Wolf(int id, int role, int headquarters, int city, int vitality, int attack): Warrior(id, role, headquarters, city, vitality, attack)
    {
    };
public:
    virtual void moveWarrior(int direction);
    virtual void attack(Warrior *w);
    virtual void hurted(int hurtPower);
};
#endif // WARRIOR_H_INCLUDED
