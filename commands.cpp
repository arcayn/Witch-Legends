// COMMANDS.CPP
// Code copyright 2016 Kaeos.net

// This file handles processing of each command
// once passed by the command handler

#include "ops.h" 

void walker(char direction, Player &player) {
	if (direction == 'f' || direction == 'b') {
		string currY = player.stringGetter("YCO");
		if (direction == 'f') {
			currY = changeYCO(currY, -1);
		}
		else {
			currY = changeYCO(currY, 1);
		}
		player.stringSetter("YCO", currY);
	}
	else {
		int currX = player.intGetter("XCO");
		if (direction == 'r') {
			currX++;
		}
		else {
			currX--;
		}
		player.setter("XCO", currX);
	}
}
void gameWalk(string direction, Player &player, int comm, int distance) {
	transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
	char dirChar = direction[0];
	
	for (int i = 0; i < distance; i++) {
		char newPosHere;
		if (dirChar == 'f' || dirChar == 'b') {
			string currY = player.stringGetter("YCO");
			if (dirChar == 'f') {
				currY = changeYCO(currY, -1);
			}
			else {
				currY = changeYCO(currY, 1);
			}
			newPosHere = getLevelData(player.stringGetter("position"), currY, player.intGetter("XCO"))[2];
		}
		else {
			int currX = player.intGetter("XCO");
			if (dirChar == 'r') {
				currX++;
			}
			else {
				currX--;
			}
			newPosHere = getLevelData(player.stringGetter("position"), player.stringGetter("YCO"), currX)[2];
		}
		if (newPosHere == '0') {
			cout << endl << "A wall obstructs your movement" << endl;
			i = distance;
			refundAP(player, atoi(getIniData("command", "0", "AP_cost").c_str()));
			reduceAP(player);
		}
		else if (newPosHere == 'L') {
			cout << endl << "This door is locked" << endl;
			i = distance;
			refundAP(player, atoi(getIniData("command", "0", "AP_cost").c_str()));
			reduceAP(player);
		}
		else if (newPosHere == ' ') { 
			walker(dirChar, player);
	    }
		else {
			string letterID = "RE";
			letterID = letterID + newPosHere;
			string herePa = getThing(player.stringGetter("position"), letterID).substr(getThing(player.stringGetter("position"), letterID).length() - 6, 1);
			if (herePa == "P") {
				walker(dirChar, player);
			}
			else if (herePa == "D") {
				string enID = "EN";
				enID += newPosHere;
				string playerLoc = player.stringGetter("position");
				string accLine = getEntityData(playerLoc, enID);
				vector<string> linetok = tokenise(accLine);
				string openVal = linetok[1];
				if (openVal == "open") {
					walker(dirChar, player);
				}
				else {
					cout << endl << "This door is closed" << endl;
					i = distance;
					refundAP(player, atoi(getIniData("command", "0", "AP_cost").c_str()));
					reduceAP(player);
				}
			}
			else {
				cout << endl << getThing(player.stringGetter("position"), letterID).substr(0, getThing(player.stringGetter("position"), letterID).length() - 6) << " obstructs your movement" << endl;
				i = distance;
				refundAP(player, atoi(getIniData("command", "0", "AP_cost").c_str()));
				reduceAP(player);
			}
		}
	}
	if (dirChar == 'f' || dirChar == 'b' || dirChar == 'l' || dirChar == 'r') {
		processEnemies(player, comm);
	}
	else {
		cout << endl << "Not a valid direction!" << endl << endl;
	}
}

void gameOpen(string toSearch, Player &player, int comm) {
	transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
	string levelAround[3];
	levelAround[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	levelAround[0].erase(levelAround[0].begin());
	levelAround[0].pop_back();
	levelAround[1].erase(levelAround[1].begin());
	levelAround[1].pop_back();
	levelAround[2].erase(levelAround[2].begin());
	levelAround[2].pop_back();
	string nonAction[4];
	nonAction[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	nonAction[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	nonAction[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	nonAction[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string itemsAround = levelAround[0] + levelAround[1] + levelAround[2];
	string nonItems = nonAction[0] + nonAction[1] + nonAction[2] + nonAction[3];
	string defsAround[10];
	for (int i = 0; i < 8; i++) {
		if (itemsAround[i] == '0') {}
		else if (itemsAround[i] == ' ' || itemsAround[i] == 'L') {}
		else {
			char thing = itemsAround[i];
			string letterID = "RE";
			letterID = letterID + itemsAround[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			currDef = currDef.substr(0, currDef.length() - 6);
			currDef = tokenise(currDef).back();
			transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
			defsAround[i] = currDef;
		}
	}
	defsAround[9] = "NULLPTR";
	string defsNotAround[21];
	for (int i = 0; i < 19; i++) {
		if (nonItems[i] == '0') {}
		else if (nonItems[i] == ' ' || nonItems[i] == 'L') {}
		else {
			char thing = nonItems[i];
			string letterID = "RE";
			letterID = letterID + nonItems[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			currDef = currDef.substr(0, currDef.length() - 6);
			currDef = tokenise(currDef).back();
			transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
			defsNotAround[i] = currDef;
		}
	}
	defsNotAround[20] = "NULLPTR";


	if (find(begin(defsAround), end(defsAround), toSearch) != end(defsAround)) {
		char itemRep = itemsAround[std::distance(defsAround, std::find(begin(defsAround), end(defsAround), toSearch))];
		string itemID = "EN";
		itemID = itemID + itemRep;
		string origLine = getEntityData(player.stringGetter("position"), itemID);
		char searchType = origLine[0];
		vector<string> namesVector;
		vector<string> itemsVector;
		 if (searchType == 'S') {
			 bool empty = false;
			vector<string> itemsInItem = tokenise(origLine);
			itemsInItem.erase(itemsInItem.begin());
			if (itemsInItem.size() == 0) { empty = true; }
			itemsVector = itemsInItem;
			string dummySearch = toSearch;
			dummySearch[0] = toupper(dummySearch[0]);
			cout << endl << dummySearch << " contains:" << endl;
			for (int i = 0; i < itemsVector.size(); i++) {
				string itemName = getIniData("item", itemsVector[i], "friendly_name");
				namesVector.push_back(itemName);
			    cout << itemName << endl;
				
			}

			cout << endl << "> ";
			string nextComm;
			getline(cin, nextComm);
			transform(nextComm.begin(), nextComm.end(), nextComm.begin(), ::tolower);
			vector<string> commVec = tokenise(nextComm);
			if (commVec[0] == "take") {
				commVec.erase(commVec.begin());
				string itemToTake = commVec[0];
				for (int i = 1; i < commVec.size(); i++) {
					itemToTake = itemToTake + " " + commVec[i];
				}
				bool itemTook = false;
				for (int i = 0; i < namesVector.size(); i++) {
					transform(namesVector[i].begin(), namesVector[i].end(), namesVector[i].begin(), ::tolower);
					if (namesVector[i] == itemToTake) {
						player.addInv(itemsVector[i]);
						origLine.replace(origLine.find(itemsVector[i]), itemsVector[i].length() + 1, "");
						changeLine(player.stringGetter("position") + ".wled", itemID, itemID + ' ' + origLine);
						itemTook = true;
					}
				}
				if (!itemTook) {
					cout << endl << "Item not in container!" << endl;
				}
				gameOpen(toSearch, player, comm);
			}
			else if (commVec[0] == "exit") { getComm(player); }
			else {	processCommand(player, nextComm); }
			
		 }
		 else if (searchType == 'D') {
			 string prefix = tokenise(getEntityData(player.stringGetter("position"), itemID))[0];
			 if (tokenise(getEntityData(player.stringGetter("position"), itemID))[1] != "open") {
				 changeLine(player.stringGetter("position") + ".wled", itemID, itemID + ' ' + prefix + ' ' + "open");
				 cout << endl << "Opened door!" << endl << endl;
			 }
			 else {
				 cout << endl << "Already open!" << endl << endl;
				 refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
			 }
		 }
		 else if (searchType = 'G') {
			 string prefix = tokenise(getEntityData(player.stringGetter("position"), itemID))[0];
			 string location = tokenise(getEntityData(player.stringGetter("position"), itemID))[2];
			 changeLine(player.stringGetter("position") + ".wled", itemID, itemID + ' ' + prefix + ' ' + "open " + location);
			 player.stringSetter("position", location);
			 int newX = atoi(getThing(location, "XST").c_str());
			 player.setter("XCO", newX);
			 string newY = getThing(location, "YST");
			 player.stringSetter("YCO", newY);
			 cout << endl << "Traversed the gateway to " << location << endl;
			 processEnemies(player, 3);
		 }
		 else {
			 cout << endl << "Not an openable item!" << endl << endl;
			 refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
		 }
	    
		
	}
	else if (find(begin(defsAround), end(defsAround), toSearch) != end(defsNotAround)) {
		cout << endl << "Out of action area!" << endl << endl;
		refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
	}
	else {
		cout << endl << "Not a visible item!" << endl << endl;
		refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
	}
}

void gameClose(string toSearch, Player &player, int comm) {
	transform(toSearch.begin(), toSearch.end(), toSearch.begin(), ::tolower);
	string levelAround[3];
	levelAround[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	levelAround[0].erase(levelAround[0].begin());
	levelAround[0].pop_back();
	levelAround[1].erase(levelAround[1].begin());
	levelAround[1].pop_back();
	levelAround[2].erase(levelAround[2].begin());
	levelAround[2].pop_back();
	string nonAction[4];
	nonAction[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	nonAction[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	nonAction[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	nonAction[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string itemsAround = levelAround[0] + levelAround[1] + levelAround[2];
	string nonItems = nonAction[0] + nonAction[1] + nonAction[2] + nonAction[3];
	string defsAround[10];
	for (int i = 0; i < 8; i++) {
		if (itemsAround[i] == '0') {}
		else if (itemsAround[i] == ' ' || itemsAround[i] == 'L') {}
		else {
			char thing = itemsAround[i];
			string letterID = "RE";
			letterID = letterID + itemsAround[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			currDef = currDef.substr(0, currDef.length() - 6);
			currDef = tokenise(currDef).back();
			transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
			defsAround[i] = currDef;
		}
	}
	defsAround[9] = "NULLPTR";
	string defsNotAround[21];
	for (int i = 0; i < 19; i++) {
		if (nonItems[i] == '0') {}
		else if (nonItems[i] == ' ' || nonItems[i] == 'L') {}
		else {
			char thing = nonItems[i];
			string letterID = "RE";
			letterID = letterID + nonItems[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			currDef = currDef.substr(0, currDef.length() - 6);
			currDef = tokenise(currDef).back();
			transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
			defsNotAround[i] = currDef;
		}
	}
	defsNotAround[20] = "NULLPTR";


	if (find(begin(defsAround), end(defsAround), toSearch) != end(defsAround)) {
		char itemRep = itemsAround[std::distance(defsAround, std::find(begin(defsAround), end(defsAround), toSearch))];
		string itemID = "EN";
		itemID = itemID + itemRep;
		string origLine = getEntityData(player.stringGetter("position"), itemID);
		char searchType = origLine[0];
		vector<string> namesVector;
		vector<string> itemsVector;
		if (searchType == 'D') {
			string prefix = tokenise(getEntityData(player.stringGetter("position"), itemID))[0];
			if (tokenise(getEntityData(player.stringGetter("position"), itemID))[1] == "open") {
				changeLine(player.stringGetter("position") + ".wled", itemID, itemID + ' ' + prefix + ' ' + "closed");
				cout << endl << "Closed door!" << endl << endl;
			}
			else {
				cout << endl << "Already closed!" << endl << endl;
				refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
			}
		}
		else {
			cout << endl << "Not an openable door!" << endl << endl;
			refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
		}


	}
	else if (find(begin(defsAround), end(defsAround), toSearch) != end(defsNotAround)) {
		cout << endl << "Out of action area!" << endl << endl;
		refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
	}
	else {
		cout << endl << "Not a visible item!" << endl << endl;
		refundAP(player, atoi(getIniData("command", "3", "AP_cost").c_str()));
	}
}

void gameSearch(Player &player, int comm) {
	string levelAround[4];
	levelAround[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	levelAround[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string itemsAround = levelAround[0] + levelAround[1] + levelAround[2] + levelAround[3];
	char visAround[20];
	for (int i = 0; i < 19; i++) {
		if (itemsAround[i] == '0') {}
		else if (itemsAround[i] == ' ' || itemsAround[i] == 'L') {}
		else {
			char thing = itemsAround[i];
			string letterID = "RE";
			letterID = letterID + itemsAround[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			currDef = currDef.substr(currDef.length() - 1, 1);
			visAround[i] = currDef[0];
		}
	}
	cout << endl;
	int itemsFound = 0;
	for (int i = 0; i < 20; i++) {
		if (visAround[i] == 'I') {
			SYSTEMTIME time;
			GetSystemTime(&time);
			WORD millis = (time.wSecond * 1000) + time.wMilliseconds;
			srand(millis);
			int findChance;
			findChance = player.intGetter("knowledge") * 9;
			findChance += rand() % 3;
			int foundTester = rand() % 100;
			if (foundTester <= findChance) {
				string location = player.stringGetter("position") + ".wlad";
				if (itemsAround[i] == '0') {}
				else if (itemsAround[i] == ' ' || itemsAround[i] == 'L') {}
				else {
					string letterID = "RE";
					letterID = letterID + itemsAround[i];
					string thingHere = getThing(player.stringGetter("position"), letterID);
					thingHere = thingHere.substr(0, thingHere.length() - 6);
					cout << thingHere << " found!" << endl;
					string lineDef = getThing(player.stringGetter("position"), letterID);
					lineDef.pop_back();
					lineDef = lineDef + 'V';
					lineDef = letterID + ' ' + getThingIni(player.stringGetter("position"), letterID) + ' ' + lineDef;
					changeLine(location, letterID, lineDef);
					itemsFound++;
				}
			}
		}
	}
	if (itemsFound == 0) {
		cout << "Nothing found" << endl;
	}
	cout << endl;
}

void gameEsp(Player &player) {
	string playerPos = player.stringGetter("position");
	vector<string> minimap = returnGameGrid(playerPos);
	string usedchars;
	vector<string> charDefs;
	cout << endl;

	string acQuest = getQuests()[0];
	string questLoc = getIniData("quest", acQuest, "objLoc");
	string objType = getIniData("quest", acQuest, "objType");
	char questLocChar = '0';
	string questTypes[] = { "talk", "kill", "get", "" };
	if (questLoc == player.stringGetter("position")) {
		if (find(begin(questTypes), end(questTypes), objType) != end(questTypes)) {
			questLocChar = getIniData("quest", acQuest, "objLocChar")[0];
		}
	}
	/*else {
		vector<vector<int>> adjs = adjMatrix();
		//cout << dijk(0, 3, adjs) << endl;
		
		vector<int> path = dijk(0, 3, adjs);
		for (int i = 0; i < path.size(); i++) {
			cout << path[i] << endl;
		}
	}*/

	for (int i = 0; i < minimap.size(); i++) {
		for (int x = 0; x < minimap[i].size(); x++) {
			if (minimap[i][x] == '0' || minimap[i][x] == 'L') {}
			else if (minimap[i][x] == questLocChar) { minimap[i][x] = '@'; }
			else {
				string letterID = "RE";
				letterID += minimap[i][x];
				string iniCode = getThingIni(playerPos, letterID);
				minimap[i][x] = getIniData("env", iniCode, "genericSymbol")[0];
				bool inList = false;
				for (int n = 0; n < usedchars.length(); n++) {
					if (usedchars[n] == minimap[i][x]) {
						inList = true;
					}
				}
				if (inList == false) {
					usedchars += minimap[i][x];
					charDefs.push_back(getIniData("env", iniCode, "genericName"));
				}
			}
		}
	}
	int playerY = atoi(player.stringGetter("YCO").c_str());
	for (int i = 0; i < minimap.size(); i++) {
		for (int x = 0; x < minimap[i].length(); x++) {
			if (i == playerY && x == player.intGetter("XCO")-1) {
				cout << textColor(5, "#");
			}
			else if (minimap[i][x] == '@') {
				cout << textColor(10, "@");
			}
			else if (minimap[i][x] != '0' && minimap[i][x] != ' ') {
				string minimapChar = ""s + minimap[i][x];
				cout << textColor(12, minimapChar);
				textColor();
			}
			else { cout << minimap[i][x]; }
		}
		cout << endl;
	}
	cout << endl;
	cout << textColor(5, "#");
	textColor();
	cout << " - Player" << endl;
	cout << textColor(10, "@");
	textColor();
	cout << " - Objective" << endl;
	cout << "0 - Wall" << endl;
	cout << "L - Locked Door" << endl;
	for (int i = 0; i < usedchars.length(); i++) {
		string usedChar = ""s + usedchars[i];
		cout << textColor(12, usedChar);
		textColor();
		cout << " - " << charDefs[i] << endl;
	}

	cout << endl;
}

void gameSleep(Player &player) {
	string around[5];
	around[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	around[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	around[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	around[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	around[4] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 2), player.intGetter("XCO"));
	string things = "";
	for (int x = 0; x < 4; x++) {
		for (int i = 0; i < around[x].length(); i++) {
			bool inList = false;
			for (int t = 0; t < things.length(); t++) {
				if (things[t] == around[x][i]) {
					inList = true;
				}
			}
			if (inList == false) {
				things += around[x][i];
			}
		}
	}

	bool safe = true;
	for (int i = 0; i < things.length(); i++) {
		string letterID = "RE";
		letterID += things[i];
		if (things[i] == '0' || things[i] == 'L' || things[i] == ' ') {}
		else {
			string thing = getThing(player.stringGetter("position"), letterID);
			if (thing.substr(thing.length() - 4, 1) == "A") {
				safe = false;
			}
		}
	}
	if (safe) {
		cout << endl << getDialog("SLE1") << endl << getDialog("SLE2") << endl;
		Sleep(5000);
		system("cls");
		for (int i = 0; i < 20; i++) {
			cout << "Z";
			double healthadd = player.intGetter("maxHealth") / (double)40;
			int newhealth = player.intGetter("health") + healthadd;
			if (newhealth <= player.intGetter("maxHealth")) {
				player.setter("health", newhealth);
			}
			Sleep(350);
		}
		cout << endl;
		cout << getDialog("WAKE") << endl << getDialog("WAKE2") << endl << endl;
		processEnemies(player, 7);
	}
	else {
		cout << endl << getDialog("NOSLEEP") << endl << endl;
		refundAP(player, atoi(getIniData("command", "7", "AP_cost").c_str()));
		reduceAP(player);
	}
}

void gameTalk(Player &player, string entity) {
	transform(entity.begin(), entity.end(), entity.begin(), ::tolower);
	string levelAround[4];
	levelAround[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	levelAround[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string itemsAround = levelAround[0] + levelAround[1] + levelAround[2] + levelAround[3];
	string defsAround[21];
	for (int i = 0; i < 20; i++) {
		if (itemsAround[i] == '0') {}
		else if (itemsAround[i] == ' ' || itemsAround[i] == 'L') {}
		else {
			char thing = itemsAround[i];
			string letterID = "RE";
			letterID = letterID + itemsAround[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			currDef = currDef.substr(0, currDef.length() - 6);
			currDef = tokenise(currDef).back();
			transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
			defsAround[i] = currDef;
		}
	}
	defsAround[20] = "NULLPTR";
    vector<string> defsVec(defsAround, defsAround + sizeof defsAround / sizeof defsAround[0]);

	bool talkedTo = false;
	if (find(begin(defsAround), end(defsAround), entity) != end(defsAround)) {
		string diFile;
		char itemRep = itemsAround[std::distance(defsAround, std::find(begin(defsAround), end(defsAround), entity))];
		string itemID = "RE";
		itemID = itemID + itemRep;
		string origLine = getThingIni(player.stringGetter("position"), itemID);
		string genName = tokenise(origLine)[0];
		diFile = getIniData("npc", genName, "dialog");
		talkEntity(diFile, genName, player);
		talkedTo = true;
	}
	if (!talkedTo) {
		refundAP(player, 2);
		cout << endl << "Entity not recognised" << endl;
	}
}

void gameTake(Player &player, string item) {
	transform(item.begin(), item.end(), item.begin(), ::tolower);
	string levelAround[3];
	levelAround[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	levelAround[0].erase(levelAround[0].begin());
	levelAround[0].pop_back();
	levelAround[1].erase(levelAround[1].begin());
	levelAround[1].pop_back();
	levelAround[2].erase(levelAround[2].begin());
	levelAround[2].pop_back();
	string nonAction[4];
	nonAction[0] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -2), player.intGetter("XCO"));
	nonAction[1] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	nonAction[2] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	nonAction[3] = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string itemsAround = levelAround[0] + levelAround[1] + levelAround[2];
	string nonItems = nonAction[0] + nonAction[1] + nonAction[2] + nonAction[3];
	string defsAround[10];
	vector<char> aroundItems;
	for (int i = 0; i < 9; i++) {
		if (itemsAround[i] == ' ' || itemsAround[i] == 'L' || itemsAround[i] == '0') {
			aroundItems.push_back('h');  
		}
		else {
			char thing = itemsAround[i];
			string letterID = "RE";
			letterID = letterID + itemsAround[i];
			string currDef = getThing(player.stringGetter("position"), letterID);
			char currItem = currDef[currDef.length() - 3];
			aroundItems.push_back(currItem);
			currDef = currDef.substr(0, currDef.length() - 6);
			currDef = tokenise(currDef).back();
			transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
			defsAround[i] = currDef;
		}
	}
	defsAround[9] = "NULLPTR";
	vector<string> defsVec(defsAround, defsAround + sizeof defsAround / sizeof defsAround[0]);

	bool taken = false;
	string * findItr = find(begin(defsAround), end(defsAround), item);
	if (findItr != end(defsAround)) {
		int defNum = distance(defsAround, findItr);
		char isItem = aroundItems[defNum];
		if (isItem == 'I') {
			char itemRep = itemsAround[defNum];
			string letterID = "RE";
			letterID = letterID + itemRep;
			string numCode = getThingIni(player.stringGetter("position"), letterID);
			player.addInv(numCode);
			//DANGEROUS LINE AHEAD// changeLine(player.stringGetter("position") + ".wlad", letterID, "+-Picked Up Item lolz-+");
			int row = defNum / 3;
			int column = defNum % 3;
			string accRow;
			switch (row) {
			case 0:
				accRow = changeYCO(player.stringGetter("YCO"), -1);
				break;
			case 1:
				accRow = changeYCO(player.stringGetter("YCO"), 0);
				break;
			case 2:
				accRow = changeYCO(player.stringGetter("YCO"), 1);
				break;
			default:
				accRow = changeYCO(player.stringGetter("YCO"), 0);
			}
			int accCol = player.intGetter("XCO");
			switch (column) {
			case 0:
				accCol--;
				break;
			case 1:
				break;
			case 2:
				accCol++;
				break;
			default:
				accCol += 0;
			}
			string origLine = getLevelLine(player.stringGetter("position"), accRow);
			origLine.replace(origLine.begin() + accCol - 1, origLine.begin() + accCol, " ");
			changeLine(player.stringGetter("position") + ".wlad", accRow, accRow + ' ' + origLine);
			cout << endl << "Taken " << item << '!' << endl << endl;
		}
		else {
			cout << endl << "Not an item!" << endl << endl;
			refundAP(player, 1);
		}
	}
	else {
		bool taken = false;
		char Here = getLevelData(player.stringGetter("position"), changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"))[2];
		string oneID = "RE"s + Here;
		string itemID = "EN"s + Here;
		string hereDef = getThing(player.stringGetter("position"), oneID);
		char hereType = hereDef[hereDef.length() - 3];
		if (hereType == 'H') {
			string accLine = getEntityData(player.stringGetter("position"), itemID);
			vector<string> lineVec = tokenise(accLine);
			lineVec.erase(lineVec.begin());
			vector<string> defsVec;
			for (int i = 0; i < lineVec.size(); i++) {
				string currDef = getIniData("item", lineVec[i], "friendly_name");
				transform(currDef.begin(), currDef.end(), currDef.begin(), ::tolower);
				defsVec.push_back(currDef);
			}
			for (int i = 0; i < defsVec.size(); i++) {
				if (defsVec[i] == item) {
					taken = true;
					if (lineVec.size() == 1) {
						string accRow = player.stringGetter("YCO");
						int accCol = player.intGetter("XCO");
						string origLine = getLevelLine(player.stringGetter("position"), accRow);
						origLine.replace(origLine.begin() + accCol - 1, origLine.begin() + accCol, " ");
						changeLine(player.stringGetter("position") + ".wlad", accRow, accRow + ' ' + origLine);
					}
					player.addInv(lineVec[i]);
					string origline = accLine;
					origline.replace(origline.find(lineVec[i]), lineVec[i].length() + 1, "");
					changeLine(player.stringGetter("position") + ".wled", itemID, itemID + ' ' + origline);
					cout << endl << "Taken " << defsVec[i] << "!" << endl << endl;
					double apAdd = player.intGetter("agility") / (double)5;
					apAdd += 1.8;
					apAdd += player.dubGetter("AP");
					if (apAdd > 20) { apAdd = 20.0; }
					player.dubSetter("AP", apAdd);
				}
			}
		}
		if (!taken) {
			cout << endl << "Not an available item!" << endl << endl;
			refundAP(player, 1);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////// QUARTANTINE ZONE/PROCRASTINATION STATION /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gameDrop(Player &player, string item, int quantity) {
	int itemLoc;
	vector<string>& playerInv = player.getInv();
	vector<string> invNames;
	for (int i = 0; i < playerInv.size(); i++) {
		invNames.push_back(getIniData("item", playerInv[i], "friendly_name"));
	}
	int itemsNumber = count(invNames.begin(), invNames.end(), item);
	string lineHere = getLevelData(player.stringGetter("position"), player.stringGetter("YCO"), player.intGetter("XCO"));
    char here = lineHere[2];
	string numCode;
	if (itemsNumber == 0) {
		cout << endl << "Item not in inventory!" << endl << endl;
	}
	else {
		for (int i = 0; i < invNames.size(); i++) {
			if (invNames[i] == item) {
				numCode = playerInv[i];
				itemLoc = i;
			}
		}
		    
		if (itemsNumber >= quantity) {}
		else {
			cout << endl << "Less than specified quantity of items in inventory! You wanted to drop: " << quantity << " but there are only: " << itemsNumber << ". Dropping: " << itemsNumber << endl;
			quantity = itemsNumber;
		}
		char typeHere = 'b';
		if (here != ' ' && here != '0' && here != 'L') {
			string thingHere = getThing(player.stringGetter("position"), "RE"s + here);
			typeHere = thingHere[thingHere.length() - 3];
		}
		vector<string> hereItems = getDroppedItems(player.stringGetter("position"), to_string(player.intGetter("XCO")), player.stringGetter("YCO"));
		if (quantity == 1 && here == ' ' && hereItems[0] == "NULL") {
			string newLine = "DR "s + player.stringGetter("YCO") + to_string(player.intGetter("XCO")) + "I"s + numCode;
			appendLine(newLine, player.stringGetter("position") + ".wlad"s);
		}
		else if (here == ' ') {
			
		}
		else if (typeHere = 'H') {
			vector<string> preVec = tokenise(getEntityData(player.stringGetter("position"), "EN"s + here));
			preVec.erase(preVec.begin());
			string toPush = playerInv[itemLoc];
			player.removeInv(toPush, quantity);
			for (int i = 0; i < quantity; i++) {
				preVec.push_back(toPush);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void metaProfile(Player &player, int comm) {
	cout << endl << replaceDelims("DE1") << endl << replaceDelims("DE2") << endl << replaceDelims("DE3") << endl << replaceDelims("DE4") << endl << replaceDelims("DE5") << endl << replaceDelims("DE6") << endl << endl;
	processAP(player);
}

void metaInv(Player &player) {
	vector<string> namesVector;
	vector<string> itemsVector = getInv();
	cout << endl << "Inventory contains:" << endl;
	for (int i = 0; i < itemsVector.size(); i++) {
		string itemName = getIniData("item", itemsVector[i], "friendly_name");
		namesVector.push_back(itemName);
		cout << itemName << endl;
	}
	cout << endl;
}

void gameCast(Player &player, string spell, string target) {
	if (spell == "spark") { castSpark(target); }
	//else if (spell == "")
}