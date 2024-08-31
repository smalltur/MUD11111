#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <iostream>

using namespace std;

enum Type
{
	slash,
	strike,
	piece
}; // 攻击属性及弱点属性

class Equipment
{
protected:
	string name;
	int price;

public:
	Equipment(string name, int price) : name(name), price(price) {}
	string getName() const { return name; }
	int getPrice() const { return price; }
	virtual string getDescription() const =0;
	virtual void describe() const
	{
		cout << "Name: " << name << ", Price: " << price << endl;
	}

	virtual ~Equipment() {}
};

class Weapon : public Equipment
{
private:
	int attack;
	int speed;
	float hitRate;
	Type attackType;

public:
	Weapon(string name, int price, int attack, int speed, float hitRate, Type attackType)
		: Equipment(name, price), attack(attack), speed(speed), hitRate(hitRate), attackType(attackType) {}

	int getAttack() const { return attack; }
	int getSpeed() const { return speed; }
	float getHitRate() const { return hitRate; }
	Type getAttackType() const { return attackType; }

	string getDescription() const override
	{
		return "该武器攻击加成:. " + to_string(attack) + " 命中加成:. " + to_string(hitRate) + " 速度加成: ." + to_string(speed) + " 攻击方式：." + to_string(int(attackType));
	}

	void describe() const override
	{
		cout << "Weapon: " << name << ", Attack: " << attack << ", Speed: " << speed << ", Hit Rate: " << hitRate << ", Attack Type: " << int(attackType) << endl;
	}
};

class Armor : public Equipment
{
private:
	int defense;
	int HP;
	Type weakness;

public:
	Armor(string name, int price, int defense, int HP, Type weakness)
		: Equipment(name, price), defense(defense), HP(HP), weakness(weakness) {}

	int getDefense() const { return defense; }
	int getHP() const { return HP; }
	Type getWeakness() const { return weakness; }

	string getDescription() const override
	{
		return "该防具防御加成: ." + to_string(defense) + " 最大生命加成: ." + to_string(HP) + " 弱点：." + to_string(int(weakness));
	}

	void describe() const override
	{
		cout << "Armor: " << name << ", Defense: " << defense << ", HP Bonus: " << HP << ", Weakness: " << int(weakness) << endl;
	}
};


#endif