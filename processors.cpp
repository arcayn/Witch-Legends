// PROCESSORS.CPP
// Code copyright 2016 Kaeos.net

// This file handles processing of the game scenario
// each phase

#include "ops.h"

string walkSynonyms[] = { "walk", "move", "hike", "step", "tour", "skip", "waltz", "dance", "glide", "jaunt", "tramp", "tread", "stroll", "march", "shimmy", "parade", "shuffle", "stretch", "traipse", "perambulate", "trundle", "jaipse", "sashshay", "cha-cha", "bound", "leap", "NULLPTR" };
string sneakSynonyms[] = { "sneak", "crawl" };
string openSynonyms[] = { "open", "check" };
string clearSynonyms[] = { "clear", "cls" };
string profileSynonyms[] = { "profile", "character", "player" };
string runSynonyms[] = { "sprint", "run", "jog" };
string searchSynonyms[] = { "search", "find" };
string espSynonyms[] = { "esp", "map", "level", "area" };
string sleepSynonyms[] = { "sleep", "rest", "settle" };
string closeSynonyms[] = { "shut", "close", "slam" };
string invSynonyms[] = { "inventory", "inv", "stuff", "bag", "soup" };
string talkSynonyms[] = { "talk", "chat" };
string takeSynonyms[] = { "take" };

void processEnemies(Player &player, int prevComm) {
	
	enemyMovement();
	enemyDetection(player, prevComm);

	processInteraction(player, prevComm);
}

void processCommand(Player &player, string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	if (find(begin(walkSynonyms), end(walkSynonyms), tokenise(command)[0]) != end(walkSynonyms)) {
		if (atoi(getIniData("command", "0", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "0", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				gameWalk(tokenise(command)[1], player, 0, 1);
			}
			else {
				cout << endl << "Invalid parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(sneakSynonyms), end(sneakSynonyms), tokenise(command)[0]) != end(sneakSynonyms)) {
		if (atoi(getIniData("command", "1", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "1", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				gameWalk(tokenise(command)[1], player, 1, 1);
			}
			else {
				cout << endl << "Invalid parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(takeSynonyms), end(takeSynonyms), tokenise(command)[0]) != end(takeSynonyms)) {
		if (atoi(getIniData("command", "10", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "1", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				vector<string> commTok = tokenise(command);
				commTok.erase(commTok.begin());
				string passComm = join(commTok, ' ');
				gameTake(player, passComm);
			}
			else {
				cout << endl << "Invalid parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(runSynonyms), end(runSynonyms), tokenise(command)[0]) != end(runSynonyms)) {
		if (atoi(getIniData("command", "2", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "2", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				gameWalk(tokenise(command)[1], player, 2, 2);
			}
			else {
				cout << endl << "Invalid parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(openSynonyms), end(openSynonyms), tokenise(command)[0]) != end(openSynonyms)) {
		if (atoi(getIniData("command", "3", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "3", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				gameOpen(tokenise(command)[1], player, 3);
			}
			else {
				cout << endl << "Invalid Parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(talkSynonyms), end(talkSynonyms), tokenise(command)[0]) != end(talkSynonyms)) {
		if (atoi(getIniData("command", "9", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "9", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				gameTalk(player, tokenise(command)[1]);
			}
			else {
				cout << endl << "Invalid Parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(profileSynonyms), end(profileSynonyms), tokenise(command)[0]) != end(profileSynonyms)) {
		if (atoi(getIniData("command", "4", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			double newAP = player.dubGetter("AP") - atoi(getIniData("command", "4", "AP_cost").c_str());
			player.dubSetter("AP", newAP);
			metaProfile(player, 4);
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(searchSynonyms), end(searchSynonyms), tokenise(command)[0]) != end(searchSynonyms)) {
		if (atoi(getIniData("command", "5", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			double newAP = player.dubGetter("AP") - atoi(getIniData("command", "5", "AP_cost").c_str());
			player.dubSetter("AP", newAP);
			gameSearch(player, 5);
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(espSynonyms), end(espSynonyms), tokenise(command)[0]) != end(espSynonyms)) {
		if (atoi(getIniData("command", "6", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			double newAP = player.dubGetter("AP") - atoi(getIniData("command", "6", "AP_cost").c_str());
			player.dubSetter("AP", newAP);
			gameEsp(player);
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(sleepSynonyms), end(sleepSynonyms), tokenise(command)[0]) != end(sleepSynonyms)) {
		if (atoi(getIniData("command", "7", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			double newAP = player.dubGetter("AP") - atoi(getIniData("command", "7", "AP_cost").c_str());
			player.dubSetter("AP", newAP);
			gameSleep(player);
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(closeSynonyms), end(closeSynonyms), tokenise(command)[0]) != end(closeSynonyms)) {
		if (atoi(getIniData("command", "8", "AP_cost").c_str()) <= player.dubGetter("AP")) {
			if (tokenise(command).size() > 1) {
				double newAP = player.dubGetter("AP") - atoi(getIniData("command", "8", "AP_cost").c_str());
				player.dubSetter("AP", newAP);
				gameClose(tokenise(command)[1], player, 3);
			}
			else {
				cout << endl << "Invalid Parameters!" << endl << endl;
			}
		}
		else {
			cout << endl << "Not enough AP!" << endl << endl;
		}
	}
	else if (find(begin(clearSynonyms), end(clearSynonyms), tokenise(command)[0]) != end(clearSynonyms)) {
		system("cls");
		cout << getDialog("VER") << endl;
		processEnvironment(player);
		double apSub = player.intGetter("agility") / (double)5;
		apSub += 1.8;
		double newAp = player.dubGetter("AP") - apSub;
		player.dubSetter("AP", newAp);
		processAP(player);
	}
	else if (find(begin(invSynonyms), end(invSynonyms), tokenise(command)[0]) != end(invSynonyms)) {
		metaInv(player);
	}
	else {
		cout << endl << "Command not recognised!" << endl << endl;
	}
}

void processEnvironment(Player &player) {
	string levelAround[4];
	levelAround[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	levelAround[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string visMap[4];
	visMap[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	visMap[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	visMap[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	visMap[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string paMap[4];
	paMap[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	paMap[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	paMap[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	paMap[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));

	for (int i = 0; i < 4; i++) {
		for (int x = 0; x < 5; x++) {
			if (visMap[i][x] == ' ') {
				visMap[i][x] = '`';
			}
			else if (visMap[i][x] == '0') {
				visMap[i][x] = '¬';
			}
			else if (visMap[i][x] == 'L') {
				visMap[i][x] = '¬';
			}
			else {
				string lineNO = "RE";
				lineNO = lineNO + visMap[i][x];
				string gotThing = getThing(player.stringGetter("position"), lineNO);
				gotThing = gotThing.substr(gotThing.length() - 5, 1);
				if (gotThing == "O") {
					visMap[i][x] = '¬';
				}
				if (gotThing == "T") {
					visMap[i][x] = '`';
				}
			}
		}
	}
	visMap[2][2] = '`';

	if (visMap[1][2] == '`') {
		paMap[1][3] = '¦';
		paMap[1][1] = '¦';
		paMap[0][2] = '¦';
		if (visMap[0][2] == '`') {
			paMap[0][1], paMap[0][3] = '¦';
		}
		if (visMap[1][1] == '`') {
			paMap[0][1] = '¦';
			if (visMap[1][0] == '`' || visMap[0][1] == '`') {
				paMap[0][0] == '¦';
			}
		}
		if (visMap[1][3] == '`') {
			paMap[0][3] = '¦';
			if (visMap[1][4] == '`' || visMap[0][3] == '`') {
				paMap[0][4] == '¦';
			}
		}
	}
	if (visMap[3][2] == '`') {
		paMap[3][3] = '¦';
		paMap[3][1] = '¦';
	}
	if (visMap[2][1] == '`') {
		paMap[3][1] = '¦';
		paMap[2][0] = '¦';
		paMap[1][1] = '¦';
		if (visMap[1][1] == '`') {
			paMap[1][0] = '¦';
			paMap[0][1] = '¦';
			if (visMap[1][0] == '`' || visMap[0][1] == '`') {
				paMap[0][0] == '¦';
			}
		}
		if (visMap[3][1] == '`') {
			paMap[3][0] = '¦';
		}
		if (visMap[2][0] == '`') {
			paMap[3][0] = '¦';
			paMap[1][0] = '¦';
		}
	}
	if (visMap[2][3] == '`') {
		paMap[3][3] = '¦';
		paMap[1][3] = '¦';
		paMap[2][4] = '¦';
		if (visMap[1][3] == '`') {
			paMap[0][3] = '¦';
			if (visMap[1][4] == '`' || visMap[0][3] == '`') {
				paMap[0][4] == '¦';
			}
			paMap[1][4] = '¦';
		}
		if (visMap[3][3] == '`') {
			paMap[3][4] = '¦';
		}
		if (visMap[2][4] == '`') {
			paMap[3][4] = '¦';
			paMap[1][4] = '¦';
		}
	}
	paMap[2][3] = '¦';
	paMap[1][2] = '¦';
	paMap[3][2] = '¦';
	paMap[2][1] = '¦';
	paMap[2][2] = '¦';

	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 5; x++) {
			if (paMap[i][x] != '¦') {
				levelAround[i][x] = ' ';
			}
		}
	}


	string thingsBehind = "";
	int things = 0;
	for (int i = 0; i < levelAround[3].length(); i++) {
		bool inList = false;
		for (int x = 0; x < thingsBehind.length(); x++) {
			if (thingsBehind[x] == levelAround[3][i]) {
				inList = true;
			}
		}
		if (inList == false) {
			thingsBehind = thingsBehind + levelAround[3][i];
		}
	}
	cout << endl << "There is ";
	int itemsPrinted = 0;
	for (int i = 0; i < thingsBehind.length(); i++) {
		if (thingsBehind[i] == '0') {
			if (itemsPrinted != 0) {
				cout << ", ";
			}
			else {}
			cout << textColor(12, "a wall");
			textColor();
			things++;
			itemsPrinted++;
		}
		else if (thingsBehind[i] == ' ') {}
		else {
			string thingBehind;
			thingBehind = thingsBehind[i];
			string letterID = "RE";
			letterID = letterID + thingBehind;
			thingBehind = getThing(player.stringGetter("position"), letterID);
			string totalThing = thingBehind;
			thingBehind = thingBehind.substr(0, thingBehind.length() - 6);
			if (totalThing.back() == 'V') {
				if (itemsPrinted != 0) {
					cout << ", ";
				}
				else {}
				cout << textColor(12, thingBehind);
				textColor();
				things++;
				itemsPrinted++;
			}
		}
	}
	if (things == 0) { cout << "nothing"; }
	cout << " behind you " << endl;

	things = 0;
	string thingsInfront = "";
	for (int i = 0; i < levelAround[0].length(); i++) {
		bool inList = false;
		for (int x = 0; x < thingsInfront.length(); x++) {
			if (thingsInfront[x] == levelAround[0][i]) {
				inList = true;
			}
		}
		if (inList == false) {
			thingsInfront = thingsInfront + levelAround[0][i];
		}
	}
	for (int i = 0; i < levelAround[1].length(); i++) {
		bool inList = false;
		for (int x = 0; x < thingsInfront.length(); x++) {
			if (thingsInfront[x] == levelAround[1][i]) {
				inList = true;
			}
		}
		if (inList == false) {
			thingsInfront = thingsInfront + levelAround[1][i];
		}
	}
	cout << "There is ";
	itemsPrinted = 0;
	for (int i = 0; i < thingsInfront.length(); i++) {
		if (thingsInfront[i] == '0') {
			if (itemsPrinted != 0) {
				cout << ", ";
			}
			else {}
			cout << textColor(12, "a wall");
			textColor();
			things++;
			itemsPrinted++;
		}
		else if (thingsInfront[i] == ' ') {}
		else {
			string thingInfront;
			thingInfront = thingsInfront[i];
			string letterID = "RE";
			letterID = letterID + thingInfront;
			thingInfront = getThing(player.stringGetter("position"), letterID);
			string totalThing = thingInfront;
			thingInfront = thingInfront.substr(0, thingInfront.length() - 6);
			if (totalThing.back() == 'V') {
				if (itemsPrinted != 0) {
					cout << ", ";
				}
				else {}
				cout << textColor(12, thingInfront);
				textColor();
				things++;
				itemsPrinted++;
			}
		}
	}
	if (things == 0) { cout << "nothing"; }
	cout << " in front of you" << endl;

	things = 0;
	string thingsToRight = "";
	string toRight = levelAround[2].substr(levelAround[2].length() - 2, 2);
	for (int i = 0; i < toRight.length(); i++) {
		bool inList = false;
		for (int x = 0; x < thingsToRight.length(); x++) {
			if (thingsToRight[x] == toRight[i]) {
				inList = true;
			}
		}
		if (inList == false) {
			thingsToRight = thingsToRight + toRight[i];
		}
	}
	cout << "There is ";
	itemsPrinted = 0;
	for (int i = 0; i < thingsToRight.length(); i++) {
		if (thingsToRight[i] == '0') {
			if (itemsPrinted != 0) {
				cout << ", ";
			}
			else {}
			cout << textColor(12, "a wall");
			textColor();
			things++;
			itemsPrinted++;
		}
		else if (thingsToRight[i] == ' ') {}
		else {
			string thingToRight;
			thingToRight = thingsToRight[i];
			string letterID = "RE";
			letterID = letterID + thingToRight;
			thingToRight = getThing(player.stringGetter("position"), letterID);
			string totalThing = thingToRight;
			thingToRight = thingToRight.substr(0, thingToRight.length() - 6);
			if (totalThing.back() == 'V') {
				if (itemsPrinted != 0) {
					cout << ", ";
				}
				else {}
				cout << textColor(12, thingToRight);
				textColor();
				things++;
				itemsPrinted++;
			}
		}
	}
	if (things == 0) { cout << "nothing"; }
	cout << " to the right of you" << endl;

	things = 0;
	string thingsToLeft = "";
	string toLeft = levelAround[2].substr(0, 2);
	for (int i = 0; i < toLeft.length(); i++) {
		bool inList = false;
		for (int x = 0; x < thingsToLeft.length(); x++) {
			if (thingsToLeft[x] == toLeft[i]) {
				inList = true;
			}
		}
		if (inList == false) {
			thingsToLeft = thingsToLeft + toLeft[i];
		}
	}
	cout << "There is ";
	itemsPrinted = 0;
	for (int i = 0; i < thingsToLeft.length(); i++) {
		if (thingsToLeft[i] == '0') {
			if (itemsPrinted != 0) {
				cout << ", ";
			}
			else {}
			cout << textColor(12, "a wall");
			textColor();
			things++;
			itemsPrinted++;
		}
		else if (thingsToLeft[i] == ' ') {}
		else {
			string thingToLeft;
			thingToLeft = thingsToLeft[i];
			string letterID = "RE";
			letterID = letterID + thingToLeft;
			thingToLeft = getThing(player.stringGetter("position"), letterID);
			string totalThing = thingToLeft;
			thingToLeft = thingToLeft.substr(0, thingToLeft.length() - 6);
			if (totalThing.back() == 'V') {
				if (itemsPrinted != 0) {
					cout << ", ";
				}
				else {}
				cout << textColor(12, thingToLeft);
				textColor();
				things++;
				itemsPrinted++;
			}
		}
	}
	if (things == 0) { cout << "nothing"; }
	cout << " to the left of you" << endl << endl;

	string thingsHere = "";
	string thingHere;
	char Here = levelAround[2][2];
	cout << "There is ";
	if (Here == '0') { cout << "a wall "; }
	else if (Here == ' ') { cout << "nothing "; }
	else {
		string letterID = "RE";
		string otherID = "EN";
		otherID = otherID + Here;
		letterID = letterID + Here;
		string entityType;
		string baseEntity = getEntityData(player.stringGetter("position"), otherID);
		if (baseEntity != "NULLIUM") {
			entityType = tokenise(baseEntity)[0];
		}
		if (entityType[0] == 'P') {
			vector<string> itemVector = tokenise(getEntityData(player.stringGetter("position"), otherID));
			itemVector.erase(itemVector.begin());
			for (int i = 0; i < itemVector.size(); i++) {
				string itemName = getIniData("item", itemVector[i], "friendly_name");
				cout << textColor(12, "a " + itemName);
				textColor();
				if (i == itemVector.size() - 1) {
					cout << ' ';
				}
				else {
					cout << ", ";
				}
			}
		}
		else {
			thingHere = getThing(player.stringGetter("position"), letterID);
			thingHere = thingHere.substr(0, thingHere.length() - 6);
			cout << textColor(12, thingHere) << ' ';
			textColor();
		}
		string lineDef = getThing(player.stringGetter("position"), letterID);
		lineDef.pop_back();
		lineDef = lineDef + 'V';
		lineDef = letterID + ' ' + getThingIni(player.stringGetter("position"), letterID) + ' ' + lineDef;
		changeLine(player.stringGetter("position")+".wlad", letterID, lineDef);
	}
	cout << "here" << endl << endl;
	double apAdd = player.intGetter("agility") / (double)5;
	apAdd += 1.8;
	apAdd += player.dubGetter("AP");
	if (apAdd > 20) { apAdd = 20.0; }
	player.dubSetter("AP", apAdd);
};

void processAP(Player &player) {
	cout << "Current AP: ";
	string strAP = to_string(player.dubGetter("AP"));
	for (int i = 0; i < strAP.length(); i++) {
		if (strAP[i] != '.') {
			cout << strAP[i];
		}
		else {
			cout << endl;
			break;
		}
	}
}