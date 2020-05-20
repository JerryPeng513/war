#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#include "globle.h"

class City
{
private:
    int iCityId;
    int iWarriorAmount;
    //{iWarriorId[geHQRed], iWarriorId[geHQBlue]}, !0--exist warrior
    int isWarriorId[geHQAmount];
    int isWarriorRole[geHQAmount];
public:
    City(int id);
    int getId();
    int getWarriorAmount();
    int getWarriorIdRed();
    int getWarriorRoleRed();
    int getWarriorIdBlue();
    int getWarriorRoleBlue();
    int addWarrior(int headquarters, int warriorId, int role);
    int removeWarrior(int headquarters);
};

#endif // CITY_H_INCLUDED
