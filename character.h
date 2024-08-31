#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <iostream>
#include "equipment.h"

using namespace std;

class Equipment;
class Character
{
protected:
    string name;
    int attack;
    int HP;
    int maxHP;
    int defense;
    int speed;
    float hitRate;
    float evasionRate;
    int gold;
    bool actionAvailability = true;
    bool hasReceivedWeaknessHit = false;
    bool isPlayer;
    vector<Weapon *> weapons;
    vector<Armor *> armors;

public:
    Character(const string &name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer)
        : name(name), attack(attack), HP(HP), maxHP(maxHP), defense(defense), speed(speed), hitRate(hitRate), evasionRate(evasionRate), gold(gold), isPlayer(isPlayer) {}
        
    string getName() const
    {
        return name;
    }

    int getAttack() const
    {
        return attack;
    }

    int getHP() const
    {
        return HP;
    }

    void modifyHP(int modifyAmount)
    {
        HP += modifyAmount;
    }

    int getMaxHP() const
    {
        return maxHP;
    }

    int getDefense() const
    {
        return defense;
    }

    int getSpeed() const
    {
        return speed;
    }

    float getHitRate() const
    {
        return hitRate;
    }

    float getEvasionRate() const
    {
        return evasionRate;
    }

    int getGold() const
    {
        return gold;
    }

    bool isPlayerControlled() const
    {
        return isPlayer;
    }

    void setActionAvailability(bool isAvailable)
    {
        actionAvailability = isAvailable;
    }

    bool getActionAvailability()
    {
        return actionAvailability;
    }

    void setWeaknessReceivedStatus(bool isHit)
    {
        hasReceivedWeaknessHit = isHit;
    }

    bool getWeaknessReceivedStatus()
    {
        return hasReceivedWeaknessHit;
    }

    Weapon *getFirstweapon()
    {
        return weapons.front();
    }
    Armor *getFirstarmor()
    {
        return armors.front();
    }
};

class Linchong : public Character
{
protected:
    int place;

public:
    Linchong(const string &name, int attack, int HP, int maxHP, int defense, int speed, float hitRate, float evasionRate, int gold, bool isPlayer, int place)
        : Character(name, attack, HP, maxHP, defense, speed, hitRate, evasionRate, gold, isPlayer), place(place){}

    int getPlace()
    {
        return place;
    }
    void changePlace() {} // 待补全

   	//输出武器防具信息(有点问题
	void printWeapons() const {
		for (size_t i = 0; i < weapons.size(); ++i) {
			cout << weapons[i]->getName() << ": " << weapons[i]->getDescription()<<endl;
		}
	}

	void printArmors() const {
		for (size_t i = 0; i < armors.size(); ++i) {
			cout << armors[i]->getName() << ": " << armors[i]->getDescription() << endl;
		}
	}

	//买武器
	bool buyItem1(Weapon* equipment) {
		if (equipment->getPrice() <= gold) {
			gold -= equipment->getPrice();
			cout << "购买成功！你现在还有 " << gold << " 块钱" << endl;
			weapons.push_back(equipment);
			return true;
		}
		else {
            cout << "钱不够!你需要" << equipment->getPrice() << "块钱，但是你只有" << gold << "块钱。" << endl;
			return false;
		}
	}
	//买防具
	bool buyItem2(Armor* equipment) {
		if (equipment->getPrice() <= gold) {
			gold -= equipment->getPrice();
			cout << "购买成功！你现在还有 " << gold << " 块钱" << endl;
			armors.push_back(equipment);
			return true;
		}
		else {
			cout << "钱不够！你需要" << equipment->getPrice() << "块钱，但是你只有" << gold << "块钱." << endl;
			return false;
		}
	}
};

#endif
