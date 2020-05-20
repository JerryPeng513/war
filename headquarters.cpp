#include "warrior.h"
#include "globle.h"
#include "headquarters.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

Headquarters::Headquarters(int id, int e)
{
    iHeadquartersId = id;
    for (int iRoleIndex = 0; iRoleIndex < geRoleAmount; ++ iRoleIndex)
    {
        isWarriorAmount[iRoleIndex] = 0;
    }
    iWarriorTotal = 0;
    iEnergy = e;
}

int Headquarters::getHeadquartersId()
{
    return iHeadquartersId;
}

int Headquarters::getDragonAmount()
{
    return isWarriorAmount[geDragon];
}

int Headquarters::getNinjaAmount()
{
    return isWarriorAmount[geNinja];
}

int Headquarters::getIcemanAmount()
{
    return isWarriorAmount[geIceman];
}

int Headquarters::getLionAmount()
{
    return isWarriorAmount[geLion];
}

int Headquarters::getWolfAmount()
{
    return isWarriorAmount[geWolf];
}

int Headquarters::getWarriorTotal()
{
    return iWarriorTotal;
}

int Headquarters::getEnergy()
{
    return iEnergy;
}

void Headquarters::addWarrior(int id, int role, int vitality, int attack, int loyalty, int decrease, vector<City> &citySet, int cityAmount)
{
    if (iEnergy < vitality || 0 > role || geRoleAmount <= role)
    {
        return ;
    }
    int iCity;
    if (geHQRed == iHeadquartersId)
    {
        iCity = 0;
        citySet[iCity].addWarrior(geHQRed, id, role);
    }
    else
    {
        iCity = cityAmount - 1;
        citySet[iCity].addWarrior(geHQBlue, id, role);
    }
    iEnergy -= vitality;
    switch (role)
    {
    case geDragon:
        {
            Dragon *warrior = new Dragon(id, role, iHeadquartersId, iCity, vitality, attack);
            vsWarrior[role].push_back(warrior);
            break;
        }
    case geNinja:
        {
            Ninja *warrior = new Ninja(id, role, iHeadquartersId, iCity, vitality, attack);
            vsWarrior[role].push_back(warrior);
            break;
        }
    case geIceman:
        {
            Iceman *warrior = new Iceman(id, role, iHeadquartersId, iCity, vitality, attack);
            vsWarrior[role].push_back(warrior);
            break;
        }
    case geLion:
        {
            Lion *warrior = new Lion(id, role, iHeadquartersId, iCity, vitality, attack, loyalty, decrease);
            vsWarrior[role].push_back(warrior);
            break;
        }
    case geWolf:
        {
            Wolf *warrior = new Wolf(id, role, iHeadquartersId, iCity, vitality, attack);
            vsWarrior[role].push_back(warrior);
            break;
        }
    default:
        {
            break;
        }
    }
    ++ isWarriorAmount[role];
    ++ iWarriorTotal;
}

template<typename T>
struct WarriorCmp: binary_function<T *, int, bool>
{
    bool operator()(T * &w, int id) const
    {
        return (w->getId() == id);
    }
};

Warrior *Headquarters::getWarrior(int id)
{
    for (int iRoleIndex = 0; iRoleIndex < geRoleAmount; ++ iRoleIndex)
    {
        vector<Warrior *>::iterator viWarrior = find_if(vsWarrior[iRoleIndex].begin(), vsWarrior[iRoleIndex].end(), bind2nd(WarriorCmp<Warrior>(), id));
        if (viWarrior != vsWarrior[iRoleIndex].end())
        {
            return *viWarrior;
        }
    }
    return NULL;
}

Warrior *Headquarters::getWarrior(int id, int role)
{
    if (0 > role || geRoleAmount <= role)
    {
        return NULL;
    }
    vector<Warrior *>::iterator viWarrior = find_if(vsWarrior[role].begin(), vsWarrior[role].end(), bind2nd(WarriorCmp<Warrior>(), id));
    if (viWarrior != vsWarrior[role].end())
    {
        return *viWarrior;
    }
    return NULL;
}

void Headquarters::removeWarrior(int id, vector<City> &citySet, int cityAmount)
{
    for (int iRoleIndex = 0; iRoleIndex < geRoleAmount; ++ iRoleIndex)
    {
        vector<Warrior *>::iterator viWarrior = find_if(vsWarrior[iRoleIndex].begin(), vsWarrior[iRoleIndex].end(), bind2nd(WarriorCmp<Warrior>(), id));
        if (viWarrior != vsWarrior[iRoleIndex].end())
        {
            int iCity = (*viWarrior)->getCity();
            if (0 > iCity || cityAmount <= iCity)
            {
                return ;
            }
            citySet[iCity].removeWarrior(iHeadquartersId);
            delete (*viWarrior);
            vsWarrior[iRoleIndex].erase(viWarrior);
            -- isWarriorAmount[iRoleIndex];
            -- iWarriorTotal;
            return ;
        }
    }
}

void Headquarters::removeWarrior(int id, int role, vector<City> &citySet, int cityAmount)
{
    if (0 > role || geRoleAmount <= role)
    {
        return ;
    }
    vector<Warrior *>::iterator viWarrior = find_if(vsWarrior[role].begin(), vsWarrior[role].end(), bind2nd(WarriorCmp<Warrior>(), id));
    if (viWarrior != vsWarrior[role].end())
    {
        int iCity = (*viWarrior)->getCity();
        if (0 > iCity || cityAmount <= iCity)
        {
            return ;
        }
        citySet[iCity].removeWarrior(iHeadquartersId);
        delete (*viWarrior);
        vsWarrior[role].erase(viWarrior);
        -- isWarriorAmount[role];
        -- iWarriorTotal;
    }
}

int Headquarters::moveWarrior(vector<City> &citySet, int cityAmount)
{
    //move warrior by sequence
    if (geHQRed == iHeadquartersId)
    {
        for (int iCityIndex = cityAmount - 2; iCityIndex >= 0; -- iCityIndex)
        {
            int iWarriorIdRed = citySet[iCityIndex].getWarriorIdRed();
            if (0 != iWarriorIdRed)
            {
                int iWarriorRoleRed = citySet[iCityIndex].getWarriorRoleRed();
                Warrior *warriorRed = getWarrior(iWarriorIdRed, iWarriorRoleRed);
                if (NULL == warriorRed)
                {
                    return -1;
                }
                if (0 != citySet[iCityIndex].removeWarrior(geHQRed))
                {
                    return -1;
                }
                warriorRed->moveWarrior(geMoveRight);
                if (0 != citySet[iCityIndex + 1].addWarrior(geHQRed, iWarriorIdRed, iWarriorRoleRed))
                {
                    return -1;
                }
            }
        }
    }
    else
    {
        for (int iCityIndex = 1; iCityIndex < cityAmount; ++ iCityIndex)
        {
            int iWarriorIdBlue = citySet[iCityIndex].getWarriorIdBlue();
            if (0 != iWarriorIdBlue)
            {
                int iWarriorRoleBlue = citySet[iCityIndex].getWarriorRoleBlue();
                Warrior *warriorBlue = getWarrior(iWarriorIdBlue, iWarriorRoleBlue);
                if (NULL == warriorBlue)
                {
                    return -1;
                }
                if (0 != citySet[iCityIndex].removeWarrior(geHQBlue))
                {
                    return -1;
                }
                warriorBlue->moveWarrior(geMoveLeft);
                if (0 != citySet[iCityIndex - 1].addWarrior(geHQBlue, iWarriorIdBlue, iWarriorRoleBlue))
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

//op:0--add, 1--minus; ret:0--success, !0--fail
int Headquarters::operateEnergy(int op, int amount)
{
    if (geEnergyAdd == op)
    {
        iEnergy += amount;
        return 0;
    }
    if (geEnergyMinus == op)
    {
        if (iEnergy < amount)
        {
            return -1;
        }
        iEnergy -= amount;
        return 0;
    }
    return -1;
}

void Headquarters::processEscapeLion(int cityAmount, vector<City> &citySet, vector<int> &lionIds)
{
    int iCityEnd;
    if (geHQRed == iHeadquartersId)
    {
        iCityEnd = cityAmount - 1;
    }
    else
    {
        iCityEnd = 0;
    }
    vector<Warrior *>::iterator viLion = vsWarrior[geLion].begin();
    while (viLion != vsWarrior[geLion].end())
    {
        if (((Lion *)(*viLion))->isLionEscape(iCityEnd))
        {
            //if (0 == citySet[(*viLion)->getCity()].removeWarrior(iHeadquartersId))
            citySet[(*viLion)->getCity()].removeWarrior(iHeadquartersId);
            lionIds.push_back((*viLion)->getId());
            delete (*viLion);
            viLion = vsWarrior[geLion].erase(viLion);
            -- isWarriorAmount[geLion];
            -- iWarriorTotal;
        }
        else
        {
            ++ viLion;
        }
    }
}
