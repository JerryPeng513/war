#ifndef HEADQUARTERS_H_INCLUDED
#define HEADQUARTERS_H_INCLUDED

#include "warrior.h"
#include "city.h"
#include <vector>
using namespace std;

class Headquarters
{
private:
    int iHeadquartersId;
    int isWarriorAmount[geRoleAmount];
    int iWarriorTotal;
    int iEnergy;
    vector<Warrior *> vsWarrior[geRoleAmount];
public:
    Headquarters(int id, int e);
    int getHeadquartersId();
    int getDragonAmount();
    int getNinjaAmount();
    int getIcemanAmount();
    int getLionAmount();
    int getWolfAmount();
    int getWarriorTotal();
    int getEnergy();
    Warrior *getWarrior(int id);
    Warrior *getWarrior(int id, int role);
    void addWarrior(int id, int role, int vitality, int attack, int loyalty, int decrease, vector<City> &citySet, int cityAmount);
    void removeWarrior(int id, vector<City> &citySet, int cityAmount);
    void removeWarrior(int id, int role, vector<City> &citySet, int cityAmount);
    int moveWarrior(vector<City> &citySet, int cityAmount);
    //op:0--add, 1--minus; ret:0--success, !0--fail
    int operateEnergy(int op, int amount);
    void processEscapeLion(int cityAmount, vector<City> &citySet, vector<int> &lionIds);
};

#endif // HEADQUARTERS_H_INCLUDED
