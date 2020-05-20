#ifndef GLOBLE_H_INCLUDED
#define GLOBLE_H_INCLUDED

#include <string>
using namespace std;

enum EnergyOpIndex {geEnergyAdd = 0, geEnergyMinus};
enum WeaponAmountOpIndex {geWeaponAdd = 0, geWeaponMinus, geArrowUsedOnceAdd, geArrowUsedOnceMinus};
enum WeaponIndex {geSword = 0, geBomb, geArrow, geWeaponAmount};
enum ColorIndex {geRed = 0, geBlue, geColorAmount};
enum RoleIndex {geDragon = 0, geNinja, geIceman, geLion, geWolf, geRoleAmount};
enum MoveDirectionIndex {geMoveRight = 0, geMoveLeft};
enum HeadquartersIndex {geHQRed = 0, geHQBlue, geHQAmount};
enum EventTriggerTime {geEventWarriorCreate = 0, geEventLionEscape = 5, geEventWarriorMove = 10, geEventWolfRob = 35, geEventWarriorBattle = 40, geEventHeadquartersReport = 50, geEventWarriorReport = 55};

extern const int giCityWarriorFloor;
extern const int giCityWarriorCeiling;
extern const int giWeaponSumCeiling;

//strWeaponNameList: 0--"sword", 1--"bomb", 2--"arrow"
extern const string gstrWeaponNameList[geWeaponAmount];
//strColorNameList: 0--"red", 1--"blue"
extern const string gstrColorNameList[geColorAmount];
//strRoleNameList: 0--"dragon", 1--"ninja", 2--"iceman", 3--"lion", 4--"wolf"
extern const string gstrRoleNameList[geRoleAmount];

#endif // GLOBLE_H_INCLUDED
