#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include "Character.h"
#include "Equipment.h"
#include <math.h>
#include <random>
#include <algorithm>

using namespace std;

class Battle
{
public:
	Battle();
	~Battle();

	void startBattle(Linchong *player, vector<Character *> *enemies)
	{
		vector<pair<int, Character *>> sortedCharacters;
		sortedCharacters.push_back(make_pair(player->getSpeed() + player->getFirstweapon()->getSpeed(), player));
		for (auto enemy : *enemies)
		{
			sortedCharacters.push_back(make_pair(enemy->getSpeed() + enemy->getFirstweapon()->getSpeed(), enemy));
		}

		sort(sortedCharacters.begin(), sortedCharacters.end(), [](const pair<int, Character *> &a, const pair<int, Character *> &b)
			 { return a.first > b.first; });

		int turn = 1;
		while (true)
		{
			// 清除上一回合的弱点命中状态
			for (auto &it : sortedCharacters)
			{
				it.second->setWeaknessReceivedStatus(false);
			}

			for (auto &it : sortedCharacters)
			{
				it.second->setActionAvailability(true);
				if (!it.second->isPlayerControlled())
				{
					while (it.second->getActionAvailability())
					{
						enemyTurn(it.second, player);
						if (evaluateBattleStatus(sortedCharacters))
							return;
					}
				}
				else
				{
					while (it.second->getActionAvailability())
					{
						playerTurn(player, enemies);
						if (evaluateBattleStatus(sortedCharacters))
							return;
					}
				}
			}
			turn++;
		}
	}

	bool evaluateBattleStatus(vector<pair<int, Character *>> &theCharacters)
	{

		for (auto it = theCharacters.begin(); it != theCharacters.end();)
		{
			if (it->second->getHP() <= 0)
			{
				if (it->second->isPlayerControlled())
				{
					cout << "Player defeated!" << endl;
					return true; // 玩家阵亡，退出战斗
				}
				else
				{
					cout << it->second->getName() << " defeated!" << endl;
					it = theCharacters.erase(it); // 移除阵亡的敌人
				}
			}
			else
				it++;
		}

		if (theCharacters.size() == 1 && theCharacters[0].second->isPlayerControlled())
		{
			// 所有敌人已被击败，玩家获胜
			cout << "Player wins!" << endl;
			return true;
		}

		return false; // 继续战斗
	}

	void enemyTurn(Character *enemy, Character *player)
	{
		normalAttack(player, enemy);
	}

	void playerTurn(Character *player, vector<Character *> *enemies)
	{
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: // 普通攻击
		{
			int targetIndex;
			cin >> targetIndex;
			normalAttack((*enemies)[targetIndex], player);
			break;
		}
		case 2: // 招式
		{
			break;
		}
		case 3: // 切换武器
		{
			weaponSwitch(player);
			player->setActionAvailability(true);
			break;
		}
		case 4: // 观察对手
		{
			break;
		}
		default:
			break;
		}
	}
	void takeDamage(Character *target, int damage)
	{
		target->modifyHP(-damage);
	}
	void normalAttack(Character *target, Character *attacker)
	{
		attacker->setActionAvailability(false);
		int damage = attacker->getAttack() + attacker->getFirstweapon()->getAttack() - target->getDefense() - target->getFirstarmor()->getDefense();
		if (isHittingWeakness(target->getFirstarmor()->getWeakness(), attacker->getFirstweapon()->getAttackType()))
		{
			damage *= 1.5;
			if (!target->getWeaknessReceivedStatus())
			{
				attacker->setActionAvailability(true);
				target->setWeaknessReceivedStatus(true);
			}
		}
		if (checkHit(target->getEvasionRate(), attacker->getHitRate()))
			takeDamage(target, damage);
		else
			cout << "未命中！" << endl;
	}

	bool isHittingWeakness(Type theWeakness, Type attackType)
	{
		return (theWeakness == attackType);
	};

	bool checkHit(float evasionRate, float hitRate) // 命中检定
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> dis(0.0, 1.0);
		float randomValue = dis(gen);
		return randomValue <= hitRate * (1 - evasionRate);
	}

	void weaponSwitch(Character *character)
	{
		int index;
		cin >> index;
		swap(*character->getFirstweapon(), *(character->getFirstweapon() + index));
	};
};

#endif
