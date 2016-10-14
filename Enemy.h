#pragma once
#include "resource.h"


class Enemy {
private:
	string mName, mType, mDescription;
	int mStrength, mVitality, mAgility, mKnowledge, mHumanity;
public:
	Enemy();
	Enemy(string name, string type, string description, int strength, int vitality, int agility, int knowledge, int humanity);
	~Enemy();

	//setters
	void setStrength(int newStrength);
	void setVitality(int newVitality);
	void setAgility(int newAgility);
	void setKnowledge(int newKnowledge);
	void setHumanity(int newHumanity);

	//getters
	string getName();
	string getType();
	string getDescription();
	int getStrength();
	int getVitality();
	int getAgility();
	int getKnowledge();
	int getHumanity();
};

