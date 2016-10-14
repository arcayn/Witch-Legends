#pragma once
#include "resource.h"

class Player {
private:
	string mName, mHero, mYCO, mPosition;
	int mStrength, mVitality, mAgility, mKnowledge, mHumanity, mHealth, mLevel, mXP, mMana, mMaxHealth, mXCO, mMoney;
	vector<string> mInv;
	double mAP;
public:
	Player();
	Player(string name, string hero, int strength, int vitality, int agility, int knowledge, int humanity, int health, int level, int XP, int mana, int MaxHealth, string YCO, int XCO, string position, double AP, vector<string> inv, int mMoney);
	~Player();

	//setters
	void setter(string attribute, int newVar);
	void stringSetter(string attribute, string newVar);
	void dubSetter(string attribute, double newVar);

	//getters
	string stringGetter(string attribute);
	int intGetter(string attribute);
	double dubGetter(string attribute);
	
	//inventory
	int Player::removeInv(string item, int quantity);
	int Player::addInv(string item);
	vector<string> Player::getInv();

};