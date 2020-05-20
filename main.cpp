#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "globle.h"
#include "warrior.h"
#include "headquarters.h"
#include "city.h"
using namespace std;

#define warriorCreate(iHour, iMinute, hqRed, hqBlue, iWarriorTime, bRedStop, bBlueStop, isVitality, isAttack, isSeqRed, isSeqBlue, vCity, iCityAmount, iDecrease) { \
    int iWarriorIndex = iWarriorTime % geRoleAmount; \
    if (false == bRedStop) \
    { \
        if (hqRed.getEnergy() >= isVitality[isSeqRed[iWarriorIndex]]) \
        { \
            cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red "<<gstrRoleNameList[isSeqRed[iWarriorIndex]]<<" "<<iWarriorTime + 1<<" born"<<endl; \
            if (geLion == isSeqRed[iWarriorIndex]) \
            { \
                cout<<"Its loyalty is "<<hqRed.getEnergy() - isVitality[isSeqRed[iWarriorIndex]]<<endl; \
            } \
            hqRed.addWarrior(iWarriorTime + 1, isSeqRed[iWarriorIndex], isVitality[isSeqRed[iWarriorIndex]], isAttack[isSeqRed[iWarriorIndex]], hqRed.getEnergy() - isVitality[isSeqRed[iWarriorIndex]], iDecrease, vCity, iCityAmount); \
        } \
        else \
        { \
            bRedStop = true; \
        } \
    } \
    if (false == bBlueStop) \
    { \
        if (hqBlue.getEnergy() >= isVitality[isSeqBlue[iWarriorIndex]]) \
        { \
            cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue "<<gstrRoleNameList[isSeqBlue[iWarriorIndex]]<<" "<<iWarriorTime + 1<<" born"<<endl; \
            if (geLion == isSeqBlue[iWarriorIndex]) \
            { \
                cout<<"Its loyalty is "<<hqBlue.getEnergy() - isVitality[isSeqBlue[iWarriorIndex]]<<endl; \
            } \
            hqBlue.addWarrior(iWarriorTime + 1, isSeqBlue[iWarriorIndex], isVitality[isSeqBlue[iWarriorIndex]], isAttack[isSeqBlue[iWarriorIndex]], hqBlue.getEnergy() - isVitality[isSeqBlue[iWarriorIndex]], iDecrease, vCity, iCityAmount); \
        } \
        else \
        { \
            bBlueStop = true; \
        } \
    } \
    ++ iWarriorTime; \
}

#define lionEscape(iHour, iMinute, hqRed, hqBlue, vCity, iCityAmount) { \
    vector<int> vLionIdRed, vLionIdBlue; \
    hqRed.processEscapeLion(iCityAmount, vCity, vLionIdRed); \
    for (vector<int>::iterator viLionIdRed = vLionIdRed.begin(); viLionIdRed != vLionIdRed.end(); ++ viLionIdRed) \
    { \
        cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red lion "<<*viLionIdRed<<" ran away"<<endl; \
    } \
    hqBlue.processEscapeLion(iCityAmount, vCity, vLionIdBlue); \
    for (vector<int>::iterator viLionIdBlue = vLionIdBlue.begin(); viLionIdBlue != vLionIdBlue.end(); ++ viLionIdBlue) \
    { \
        cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue lion "<<*viLionIdBlue<<" ran away"<<endl; \
    } \
}

#define moveWarrior(iHour, iMinute, hqRed, hqBlue, vCity, iCityAmount, iCase) { \
    if (0 != hqRed.moveWarrior(vCity, iCityAmount)) \
    { \
        cout<<"red move fail"<<endl; \
    } \
    if (0 != hqBlue.moveWarrior(vCity, iCityAmount)) \
    { \
        cout<<"blue move fail"<<endl; \
    } \
    if (vCity[0].getWarriorAmount() > 0 && 0 != vCity[0].getWarriorIdBlue()) /* judge blue warrior break into red headquarters */\
    { \
        int iWarriorIdBlue = vCity[0].getWarriorIdBlue(); \
        int iWarriorRoleBlue = vCity[0].getWarriorRoleBlue(); \
        Warrior *warriorBlue = hqBlue.getWarrior(iWarriorIdBlue, iWarriorRoleBlue); \
        if (NULL != warriorBlue) \
        { \
            cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue "<<gstrRoleNameList[iWarriorRoleBlue]<<" "<<iWarriorIdBlue<<" reached red headquarter with "<<warriorBlue->getVitality()<<" elements and force "<<warriorBlue->getAttack()<<endl; \
            cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red headquarter was taken"<<endl; \
        } \
    } \
    for (int iCityIndex = 1; iCityIndex < iCityAmount - 1; ++ iCityIndex) /* print info */\
    { \
        if (vCity[iCityIndex].getWarriorAmount() > 0 && 0 != vCity[iCityIndex].getWarriorIdRed()) \
        { \
            int iWarriorIdRed = vCity[iCityIndex].getWarriorIdRed(); \
            int iWarriorRoleRed = vCity[iCityIndex].getWarriorRoleRed(); \
            Warrior *warriorRed = hqRed.getWarrior(iWarriorIdRed, iWarriorRoleRed); \
            if (NULL != warriorRed) \
            { \
                cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red "<<gstrRoleNameList[iWarriorRoleRed]<<" "<<iWarriorIdRed<<" marched to city "<<iCityIndex<<" with "<<warriorRed->getVitality()<<" elements and force "<<warriorRed->getAttack()<<endl; \
            } \
        } \
        if (vCity[iCityIndex].getWarriorAmount() > 0 && 0 != vCity[iCityIndex].getWarriorIdBlue()) \
        { \
            int iWarriorIdBlue = vCity[iCityIndex].getWarriorIdBlue(); \
            int iWarriorRoleBlue = vCity[iCityIndex].getWarriorRoleBlue(); \
            Warrior *warriorBlue = hqBlue.getWarrior(iWarriorIdBlue, iWarriorRoleBlue); \
            if (NULL != warriorBlue) \
            { \
                cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue "<<gstrRoleNameList[iWarriorRoleBlue]<<" "<<iWarriorIdBlue<<" marched to city "<<iCityIndex<<" with "<<warriorBlue->getVitality()<<" elements and force "<<warriorBlue->getAttack()<<endl; \
            } \
        } \
    } \
    if (vCity[iCityAmount - 1].getWarriorAmount() > 0 && 0 != vCity[iCityAmount - 1].getWarriorIdRed()) /* judge red warrior break into blue headquarters */ \
    { \
        int iWarriorIdRed = vCity[iCityAmount - 1].getWarriorIdRed(); \
        int iWarriorRoleRed = vCity[iCityAmount - 1].getWarriorRoleRed(); \
        Warrior *warriorRed = hqRed.getWarrior(iWarriorIdRed, iWarriorRoleRed); \
        if (NULL != warriorRed) \
        { \
            cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red "<<gstrRoleNameList[iWarriorRoleRed]<<" "<<iWarriorIdRed<<" reached blue headquarter with "<<warriorRed->getVitality()<<" elements and force "<<warriorRed->getAttack()<<endl; \
            cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue headquarter was taken"<<endl; \
        } \
    } \
    if ((vCity[0].getWarriorAmount() > 0 && 0 != vCity[0].getWarriorIdBlue()) || (vCity[iCityAmount - 1].getWarriorAmount() > 0 && 0 != vCity[iCityAmount - 1].getWarriorIdRed())) \
    { \
        ++ iCase; \
        goto NewTurn; \
    } \
}

#define reportWarrior(iHour, iMinute, hqRed, hqBlue, vCity, iCityAmount) { \
    for (int iCityIndex = 1; iCityIndex < iCityAmount - 1; ++ iCityIndex) \
    { \
        if (0 < vCity[iCityIndex].getWarriorAmount()) \
        { \
            if (0 != vCity[iCityIndex].getWarriorIdRed()) \
            { \
                int iWarriorIdRed = vCity[iCityIndex].getWarriorIdRed(); \
                int iWarriorRoleRed = vCity[iCityIndex].getWarriorRoleRed(); \
                Warrior *warriorRed = hqRed.getWarrior(iWarriorIdRed, iWarriorRoleRed); \
                if (NULL != warriorRed) \
                { \
                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red "<<gstrRoleNameList[iWarriorRoleRed]<<" "<<iWarriorIdRed<<" has "<<warriorRed->getSwordAmount()<<" sword "<<warriorRed->getBombAmount()<<" bomb "<<warriorRed->getArrowAmount()<<" arrow and "<<warriorRed->getVitality()<<" elements"<<endl; \
                } \
            } \
            if (0 != vCity[iCityIndex].getWarriorIdBlue()) \
            { \
                int iWarriorIdBlue = vCity[iCityIndex].getWarriorIdBlue(); \
                int iWarriorRoleBlue = vCity[iCityIndex].getWarriorRoleBlue(); \
                Warrior *warriorBlue = hqBlue.getWarrior(iWarriorIdBlue, iWarriorRoleBlue); \
                if (NULL != warriorBlue) \
                { \
                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue "<<gstrRoleNameList[iWarriorRoleBlue]<<" "<<iWarriorIdBlue<<" has "<<warriorBlue->getSwordAmount()<<" sword "<<warriorBlue->getBombAmount()<<" bomb "<<warriorBlue->getArrowAmount()<<" arrow and "<<warriorBlue->getVitality()<<" elements"<<endl; \
                } \
            } \
        } \
    } \
}

int main()
{
    freopen("datapub.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int t;
    cin>>t;

    int iCase = 0;
NewTurn:
    for (; iCase < t; ++ iCase)
    {
        int M, N, K, T;
        cin>>M>>N>>K>>T;
        if (M < 1 || M > 100000 || N < 1 || N > 20 || K < 0 || K > 100 || T < 0 || T > 6000)
        {
            cout<<"Case:"<<iCase + 1<<" input error"<<endl;
            continue;
        }
        int iCityAmount = N + 2;
        int iDecrease = K;
        Headquarters hqRed(geHQRed, M);
        Headquarters hqBlue(geHQBlue, M);
        vector<City> vCity;
        for (int iCityIndex = 0; iCityIndex < iCityAmount; ++ iCityIndex)
        {
            vCity.push_back(City(iCityIndex));
        }
        //isVitality[5] = {dVitality, nVitality, iVitality, lVitality, wVitality}
        int isVitality[geRoleAmount], isAttack[geRoleAmount];
        cin>>isVitality[geDragon]>>isVitality[geNinja]>>isVitality[geIceman]>>isVitality[geLion]>>isVitality[geWolf];
        //isAttack[5] = {dAttack, nAttack, iAttack, lAttack, wAttack}
        cin>>isAttack[geDragon]>>isAttack[geNinja]>>isAttack[geIceman]>>isAttack[geLion]>>isAttack[geWolf];
        int isSeqRed[geRoleAmount] = {geIceman, geLion, geWolf, geNinja, geDragon};
        int isSeqBlue[geRoleAmount] = {geLion, geDragon, geNinja, geIceman, geWolf};

        cout<<"Case "<<iCase + 1<<":"<<endl;
        int iHour, iMinute, iWarriorTime = 0;
        bool bRedStop = false, bBlueStop = false;
        for (int iTime = 0; iTime <= T; ++ iTime)
        {
            iHour = iTime / 60;
            iMinute = iTime % 60;
            switch (iMinute)
            {
            case geEventWarriorCreate: //create new warrior
                {
                    warriorCreate(iHour, iMinute, hqRed, hqBlue, iWarriorTime, bRedStop, bBlueStop, isVitality, isAttack, isSeqRed, isSeqBlue, vCity, iCityAmount, iDecrease);
                    break;
                }
            case geEventLionEscape: //lion escape
                {
                    //cout<<"process lion escape"<<endl;
                    lionEscape(iHour, iMinute, hqRed, hqBlue, vCity, iCityAmount);
                    break;
                }
            case geEventWarriorMove:
                {
                    //cout<<"process warrior move"<<endl;
                    moveWarrior(iHour, iMinute, hqRed, hqBlue, vCity, iCityAmount, iCase);
                    break;
                }
            case geEventWolfRob:
                {
                    //cout<<"process wolf rob"<<endl;
                    for (int iCityIndex = 1; iCityIndex < iCityAmount - 1; ++ iCityIndex)
                    {
                        int iWarriorRoleRed = vCity[iCityIndex].getWarriorRoleRed();
                        int iWarriorRoleBlue = vCity[iCityIndex].getWarriorRoleBlue();
                        if (vCity[iCityIndex].getWarriorAmount() == giCityWarriorCeiling && (iWarriorRoleRed == geWolf || iWarriorRoleBlue == geWolf) && !(iWarriorRoleRed == geWolf && iWarriorRoleBlue == geWolf))
                        {
                            int iWarriorIdRed = vCity[iCityIndex].getWarriorIdRed();
                            int iWarriorIdBlue = vCity[iCityIndex].getWarriorIdBlue();
                            Warrior *warriorRed = hqRed.getWarrior(iWarriorIdRed, iWarriorRoleRed);
                            Warrior *warriorBlue = hqBlue.getWarrior(iWarriorIdBlue, iWarriorRoleBlue);
                            if (NULL == warriorRed || NULL == warriorBlue)
                            {
                                continue ;
                            }
                            if (geWolf == iWarriorRoleRed && giWeaponSumCeiling > warriorRed->getWeaponSum())
                            {
                                int iSwordAmountBlue = warriorBlue->getSwordAmount();
                                int iBombAmountBlue = warriorBlue->getBombAmount();
                                int iArrowAmountBlue = warriorBlue->getArrowAmount();
                                if (0 != iSwordAmountBlue)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iAdd = (iSwordAmountBlue > iDemand ? iDemand : iSwordAmountBlue);
                                    warriorRed->operateWeaponAmount(geSword, geWeaponAdd, iAdd);
                                    warriorBlue->operateWeaponAmount(geSword, geWeaponMinus, iAdd);
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<iMinute<<" red wolf "<<iWarriorIdRed<<" took "<<iAdd<<" sword from blue "<<gstrRoleNameList[iWarriorRoleBlue]<<" "<<iWarriorIdBlue<<" in city "<<iCityIndex<<endl;
                                }
                                else if (0 != iBombAmountBlue)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iAdd = (iBombAmountBlue > iDemand ? iDemand : iBombAmountBlue);
                                    warriorRed->operateWeaponAmount(geBomb, geWeaponAdd, iAdd);
                                    warriorBlue->operateWeaponAmount(geBomb, geWeaponMinus, iAdd);
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<iMinute<<" red wolf "<<iWarriorIdRed<<" took "<<iAdd<<" bomb from blue "<<gstrRoleNameList[iWarriorRoleBlue]<<" "<<iWarriorIdBlue<<" in city "<<iCityIndex<<endl;
                                }
                                else if (0 != iArrowAmountBlue)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iArrowOnceAmountBlue = warriorBlue->getArrowUsedOnce();
                                    int iArrowUnusedAmountBlue = iArrowAmountBlue - iArrowOnceAmountBlue;
                                    int iAdd1 = (iArrowUnusedAmountBlue > iDemand ? iDemand : iArrowUnusedAmountBlue);
                                    warriorRed->operateWeaponAmount(geArrow, geWeaponAdd, iAdd1);
                                    warriorBlue->operateWeaponAmount(geArrow, geWeaponMinus, iAdd1);
                                    iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iAdd2 = (iArrowOnceAmountBlue > iDemand ? iDemand : iArrowOnceAmountBlue);
                                    warriorRed->operateWeaponAmount(geArrow, geArrowUsedOnceAdd, iAdd2);
                                    warriorBlue->operateWeaponAmount(geArrow, geArrowUsedOnceMinus, iAdd2);
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<iMinute<<" red wolf "<<iWarriorIdRed<<" took "<<iAdd1 + iAdd2<<" arrow from blue "<<gstrRoleNameList[iWarriorRoleBlue]<<" "<<iWarriorIdBlue<<" in city "<<iCityIndex<<endl;
                                }
                            }
                            if (geWolf == iWarriorRoleBlue && giWeaponSumCeiling > warriorBlue->getWeaponSum())
                            {
                                int iSwordAmountRed = warriorRed->getSwordAmount();
                                int iBombAmountRed = warriorRed->getBombAmount();
                                int iArrowAmountRed = warriorRed->getArrowAmount();
                                if (0 != iSwordAmountRed)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iAdd = (iSwordAmountRed > iDemand ? iDemand : iSwordAmountRed);
                                    warriorRed->operateWeaponAmount(geSword, geWeaponMinus, iAdd);
                                    warriorBlue->operateWeaponAmount(geSword, geWeaponAdd, iAdd);
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<iMinute<<" blue wolf "<<iWarriorIdBlue<<" took "<<iAdd<<" sword from red "<<gstrRoleNameList[iWarriorRoleRed]<<" "<<iWarriorIdRed<<" in city "<<iCityIndex<<endl;
                                }
                                else if (0 != iBombAmountRed)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iAdd = (iBombAmountRed > iDemand ? iDemand : iBombAmountRed);
                                    warriorRed->operateWeaponAmount(geBomb, geWeaponMinus, iAdd);
                                    warriorBlue->operateWeaponAmount(geBomb, geWeaponAdd, iAdd);
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<iMinute<<" blue wolf "<<iWarriorIdBlue<<" took "<<iAdd<<" bomb from red "<<gstrRoleNameList[iWarriorRoleRed]<<" "<<iWarriorIdRed<<" in city "<<iCityIndex<<endl;
                                }
                                else if (0 != iArrowAmountRed)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iArrowOnceAmountRed = warriorRed->getArrowUsedOnce();
                                    int iArrowUnusedAmountRed = iArrowAmountRed - iArrowOnceAmountRed;
                                    int iAdd1 = (iArrowUnusedAmountRed > iDemand ? iDemand : iArrowUnusedAmountRed);
                                    warriorRed->operateWeaponAmount(geArrow, geWeaponMinus, iAdd1);
                                    warriorBlue->operateWeaponAmount(geArrow, geWeaponAdd, iAdd1);
                                    iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iAdd2 = (iArrowOnceAmountRed > iDemand ? iDemand : iArrowOnceAmountRed);
                                    warriorRed->operateWeaponAmount(geArrow, geArrowUsedOnceMinus, iAdd2);
                                    warriorBlue->operateWeaponAmount(geArrow, geArrowUsedOnceAdd, iAdd2);
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<iMinute<<" blue wolf "<<iWarriorIdBlue<<" took "<<iAdd1 + iAdd2<<" arrow from red "<<gstrRoleNameList[iWarriorRoleRed]<<" "<<iWarriorIdRed<<" in city "<<iCityIndex<<endl;
                                }
                            }
                        }
                    }
                    break;
                }
            case geEventWarriorBattle:
                {
                    //cout<<"process warrior battle"<<endl;
                    for (int iCityIndex = 1; iCityIndex <= iCityAmount - 1; ++ iCityIndex)
                    {
                        if (giCityWarriorCeiling == vCity[iCityIndex].getWarriorAmount())
                        {
                            Warrior *warriorRed = hqRed.getWarrior(vCity[iCityIndex].getWarriorIdRed(), vCity[iCityIndex].getWarriorRoleRed());
                            Warrior *warriorBlue = hqBlue.getWarrior(vCity[iCityIndex].getWarriorIdBlue(), vCity[iCityIndex].getWarriorRoleBlue());
                            warriorRed->setWeaponSeq();
                            warriorBlue->setWeaponSeq();
                            while (!(0 == warriorRed->getWeaponSum() && 0 == warriorBlue->getWeaponSum()))
                            {
                                //the weapon of both warriors is only sword and their attack power is 0
                                if (warriorRed->getSwordAmount() == warriorRed->getWeaponSum() && warriorBlue->getSwordAmount() == warriorBlue->getWeaponSum())
                                {
                                    if ((0 == warriorRed->getAttack() * 2 / 10) && (0 == warriorBlue->getAttack() * 2 / 10))
                                    {
                                        break;
                                    }
                                }
                                if (1 == iCityIndex % 2) //odd city number
                                {
                                    warriorRed->attack(warriorBlue);
                                    if (warriorBlue->isWarriorDead())
                                    {
                                        break;
                                    }
                                    warriorBlue->attack(warriorRed);
                                    if (warriorRed->isWarriorDead())
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    warriorBlue->attack(warriorRed);
                                    if (warriorRed->isWarriorDead())
                                    {
                                        break;
                                    }
                                    warriorRed->attack(warriorBlue);
                                    if (warriorBlue->isWarriorDead())
                                    {
                                        break;
                                    }
                                }
                                warriorRed->setWeaponNext();
                                warriorBlue->setWeaponNext();
                            }
                            if (warriorRed->isWarriorDead() && warriorBlue->isWarriorDead())
                            {
                                cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" both red "<<gstrRoleNameList[warriorRed->getRole()]<<" "<<warriorRed->getId()<<" and blue "<<gstrRoleNameList[warriorBlue->getRole()]<<" "<<warriorBlue->getId()<<" died in city "<<iCityIndex<<endl;
                                hqRed.removeWarrior(warriorRed->getId(), warriorRed->getRole(), vCity, iCityAmount);
                                hqBlue.removeWarrior(warriorBlue->getId(), warriorBlue->getRole(), vCity, iCityAmount);
                            }
                            else if (!warriorRed->isWarriorDead() && !warriorBlue->isWarriorDead())
                            {
                                cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" both red "<<gstrRoleNameList[warriorRed->getRole()]<<" "<<warriorRed->getId()<<" and blue "<<gstrRoleNameList[warriorBlue->getRole()]<<" "<<warriorBlue->getId()<<" were alive in city "<<iCityIndex<<endl;
                                if (warriorRed->getRole() == geDragon)
                                {
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red dragon "<<warriorRed->getId()<<" yelled in city "<<iCityIndex<<endl;
                                }
                                if (warriorBlue->getRole() == geDragon)
                                {
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue dragon "<<warriorBlue->getId()<<" yelled in city "<<iCityIndex<<endl;
                                }
                            }
                            else if (!warriorRed->isWarriorDead() && warriorBlue->isWarriorDead())
                            {
                                cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red "<<gstrRoleNameList[warriorRed->getRole()]<<" "<<warriorRed->getId()<<" killed blue "<<gstrRoleNameList[warriorBlue->getRole()]<<" "<<warriorBlue->getId()<<" in city "<<iCityIndex<<" remaining "<<warriorRed->getVitality()<<" elements"<<endl;
                                if (warriorRed->getRole() == geDragon)
                                {
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" red dragon "<<warriorRed->getId()<<" yelled in city "<<iCityIndex<<endl;
                                }
                                int iSwordAmountBlue = warriorBlue->getSwordAmount();
                                if (iSwordAmountBlue != 0)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iAdd = (iSwordAmountBlue > iDemand ? iDemand : iSwordAmountBlue);
                                    warriorRed->operateWeaponAmount(geSword, geWeaponAdd, iAdd);
                                }
                                int iBombAmountBlue = warriorBlue->getBombAmount();
                                if (iBombAmountBlue != 0)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iAdd = (iBombAmountBlue > iDemand ? iDemand : iBombAmountBlue);
                                    warriorRed->operateWeaponAmount(geBomb, geWeaponAdd, iAdd);
                                }
                                int iArrowAmountBlue = warriorBlue->getArrowAmount();
                                if (iArrowAmountBlue != 0)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iArrowOnceAmountBlue = warriorBlue->getArrowUsedOnce();
                                    int iArrowUnusedAmountBlue = iArrowAmountBlue - iArrowOnceAmountBlue;
                                    int iAdd1 = (iArrowUnusedAmountBlue > iDemand ? iDemand : iArrowUnusedAmountBlue);
                                    warriorRed->operateWeaponAmount(geArrow, geWeaponAdd, iAdd1);
                                    iDemand = giWeaponSumCeiling - warriorRed->getWeaponSum();
                                    int iAdd2 = (iArrowOnceAmountBlue > iDemand ? iDemand : iArrowOnceAmountBlue);
                                    warriorRed->operateWeaponAmount(geArrow, geArrowUsedOnceAdd, iAdd2);
                                }
                                hqBlue.removeWarrior(warriorBlue->getId(), warriorBlue->getRole(), vCity, iCityAmount);
                            }
                            else
                            {
                                cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue "<<gstrRoleNameList[warriorBlue->getRole()]<<" "<<warriorBlue->getId()<<" killed red "<<gstrRoleNameList[warriorRed->getRole()]<<" "<<warriorRed->getId()<<" in city "<<iCityIndex<<" remaining "<<warriorBlue->getVitality()<<" elements"<<endl;
                                if (warriorBlue->getRole() == geDragon)
                                {
                                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" blue dragon "<<warriorBlue->getId()<<" yelled in city "<<iCityIndex<<endl;
                                }
                                int iSwordAmountRed = warriorRed->getSwordAmount();
                                if (iSwordAmountRed != 0)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iAdd = (iSwordAmountRed > iDemand ? iDemand : iSwordAmountRed);
                                    warriorBlue->operateWeaponAmount(geSword, geWeaponAdd, iAdd);
                                }
                                int iBombAmountRed = warriorRed->getBombAmount();
                                if (iBombAmountRed != 0)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iAdd = (iBombAmountRed > iDemand ? iDemand : iBombAmountRed);
                                    warriorBlue->operateWeaponAmount(geBomb, geWeaponAdd, iAdd);
                                }
                                int iArrowAmountRed = warriorRed->getArrowAmount();
                                if (iArrowAmountRed != 0)
                                {
                                    int iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iArrowOnceAmountRed = warriorRed->getArrowUsedOnce();
                                    int iArrowUnusedAmountRed = iArrowAmountRed - iArrowOnceAmountRed;
                                    int iAdd1 = (iArrowUnusedAmountRed > iDemand ? iDemand : iArrowUnusedAmountRed);
                                    warriorBlue->operateWeaponAmount(geArrow, geWeaponAdd, iAdd1);
                                    iDemand = giWeaponSumCeiling - warriorBlue->getWeaponSum();
                                    int iAdd2 = (iArrowOnceAmountRed > iDemand ? iDemand : iArrowOnceAmountRed);
                                    warriorBlue->operateWeaponAmount(geArrow, geArrowUsedOnceAdd, iAdd2);
                                }
                                hqRed.removeWarrior(warriorRed->getId(), warriorRed->getRole(), vCity, iCityAmount);
                            }
                        }
                    }
                    break;
                }
            case geEventHeadquartersReport:
                {
                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" "<<hqRed.getEnergy()<<" elements in red headquarter"<<endl;
                    cout<<setfill('0')<<setw(3)<<iHour<<":"<<setw(2)<<iMinute<<" "<<hqBlue.getEnergy()<<" elements in blue headquarter"<<endl;
                    break;
                }
            case geEventWarriorReport:
                {
                    reportWarrior(iHour, iMinute, hqRed, hqBlue, vCity, iCityAmount);
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }
    return 0;
}
