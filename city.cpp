#include "globle.h"
#include "city.h"

City::City(int id)
{
    iCityId = id;
    iWarriorAmount = 0;
    isWarriorId[geHQRed] = 0;
    isWarriorId[geHQBlue] = 0;
    isWarriorRole[geHQRed] = geRoleAmount;
    isWarriorRole[geHQBlue] = geRoleAmount;
}

int City::getId()
{
    return iCityId;
}

int City::getWarriorAmount()
{
    return iWarriorAmount;
}

int City::getWarriorIdRed()
{
    return isWarriorId[geHQRed];
}

int City::getWarriorRoleRed()
{
    return isWarriorRole[geHQRed];
}

int City::getWarriorIdBlue()
{
    return isWarriorId[geHQBlue];
}

int City::getWarriorRoleBlue()
{
    return isWarriorRole[geHQBlue];
}

int City::addWarrior(int headquarters, int warriorId, int role)
{
    if (giCityWarriorCeiling <= iWarriorAmount)
    {
       return -1;
    }
    if (geHQRed == headquarters)
    {
        if (0 == isWarriorId[geHQRed])
        {
            isWarriorId[geHQRed] = warriorId;
            isWarriorRole[geHQRed] = role;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (0 == isWarriorId[geHQBlue])
        {
            isWarriorId[geHQBlue] = warriorId;
            isWarriorRole[geHQBlue] = role;
        }
        else
        {
            return -1;
        }
    }
    ++ iWarriorAmount;
    return 0;
}

int City::removeWarrior(int headquarters)
{
    if (giCityWarriorFloor >= iWarriorAmount)
    {
        return -1;
    }
    if (geHQRed == headquarters)
    {
        if (0 != isWarriorId[geHQRed])
        {
            isWarriorId[geHQRed] = 0;
            isWarriorRole[geHQRed] = geRoleAmount;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        if (0 != isWarriorId[geHQBlue])
        {
            isWarriorId[geHQBlue] = 0;
            isWarriorRole[geHQBlue] = geRoleAmount;
        }
        else
        {
            return -1;
        }
    }
    -- iWarriorAmount;
    return 0;
}
