#include "player.h"

Player::Player() {
	mStrength, mVitality, mAgility, mKnowledge, mHumanity, mHealth, mLevel, mMaxHealth, mXP, mMana, mXCO = 0;
	mAP = 0.1;
	mName, mHero, mYCO, mPosition = "";
}

Player::Player(string name, string hero, int strength, int vitality, int agility, int knowledge, int humanity, int health, int level, int XP, int mana, int maxHealth, string YCO, int XCO, string position, double AP, vector<string> inv, int money) {
	mStrength = strength;
	mVitality = vitality;
	mAgility = agility;
	mKnowledge = knowledge;
	mHumanity = humanity;
	mHealth = health;
	mMana = mana;
	mXP = XP;
	mMaxHealth = maxHealth;
	mLevel = level;
	mName = name;
	mHero = hero;
	mYCO = YCO;
	mXCO = XCO;
	mPosition = position;
	mAP = AP;
	mInv = inv;
	mMoney = money;
}

Player::~Player()
{

}

//setter

void Player::setter(string attribute, int newVar) {
	if (attribute == "strength") { mStrength = newVar; }
	else if (attribute == "vitality") { mVitality = newVar; }
	else if (attribute == "agility") { mAgility = newVar; }
	else if (attribute == "knowledge") { mKnowledge = newVar; }
	else if (attribute == "humanity") { mHumanity = newVar; }
	else if (attribute == "health") { mHealth = newVar; }
	else if (attribute == "level") { mLevel = newVar; }
	else if (attribute == "XP") { mXP = newVar; }
	else if (attribute == "mana") { mMana = newVar; }
	else if (attribute == "maxHealth") { mMaxHealth = newVar; }
	else if (attribute == "XCO") { mXCO = newVar; }
	else if (attribute == "money") { mMoney = newVar; }
	else { throw 990; }
}
void Player::stringSetter(string attribute, string newVar) {
	if (attribute == "YCO") { mYCO = newVar; }
	if (attribute == "position") { mPosition = newVar; }
}

void Player::dubSetter(string attribute, double newVar) {
	if (attribute == "AP") { mAP = newVar; }
}

//getters

string Player::stringGetter(string attribute) {
	if (attribute == "name") { return mName; }
	else if (attribute == "hero") { return mHero; }
	else if (attribute == "YCO") { return mYCO; }
	else if (attribute == "position") { return mPosition; }
	else { throw 991; }
}

int Player::intGetter(string attribute) {
	if (attribute == "strength") { return mStrength; }
	else if (attribute == "vitality") { return mVitality; }
	else if (attribute == "agility") { return mAgility; }
	else if (attribute == "knowledge") { return mKnowledge; }
	else if (attribute == "humanity") { return mHumanity; }
	else if (attribute == "health") { return mHealth; }
	else if (attribute == "level") { return mLevel; }
	else if (attribute == "XP") { return mXP; }
	else if (attribute == "mana") { return mMana; }
	else if (attribute == "maxHealth") { return mMaxHealth; }
	else if (attribute == "XCO") { return mXCO; }
	else if (attribute == "money") { return mMoney; }
	else { throw 991; }
}

double Player::dubGetter(string attribute) {
	if (attribute == "AP") { return mAP; }
}

//Inventory

int Player::removeInv(string item, int quantity) {
	int itemsRemoved = 0;
	for (int i = 0; i < mInv.size(); i++) {
		if (itemsRemoved >= quantity) { break; }
		else if (mInv[i] == item) {
			mInv.erase(mInv.begin() + i);
			itemsRemoved++;
		}
		else {}
	}
	if (itemsRemoved == 0) { return 2; }
	else if (itemsRemoved < quantity) { return 1; }
	else { return 0; }
}

int Player::addInv(string item) {
	if (mInv.size() < 20) {
		mInv.push_back(item);
		return 0;
	}
	else {
		return 1;
	}
}

vector<string> Player::getInv() {
	return mInv;
}




