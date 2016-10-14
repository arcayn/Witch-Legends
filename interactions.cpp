#include "ops.h"

void processInteraction(Player &player, int prevComm) {
	string levelAround[3] = { "","","" };
	levelAround[0] = getLevelData("tutorial", changeYCO(player.stringGetter("YCO"), -1), player.intGetter("XCO"));
	levelAround[1] = getLevelData("tutorial", changeYCO(player.stringGetter("YCO"), 0), player.intGetter("XCO"));
	levelAround[2] = getLevelData("tutorial", changeYCO(player.stringGetter("YCO"), 1), player.intGetter("XCO"));
	string inFOV = levelAround[1] + levelAround[0] + levelAround[2];
	string thingsInFOV = "";
	for (int i = 0; i < inFOV.length(); i++) {
		bool inList = false;
		for (int x = 0; x < thingsInFOV.length(); x++) {
			if (thingsInFOV[x] == inFOV[i]) {
				inList = true;
			}
		}
		if (inList == false) {
			thingsInFOV = thingsInFOV + inFOV[i];
		}
	}
	/*for (int i = 0; i < thingsInFOV.length(); i++) {
		if (thingsInFOV[i] == '0') {}
		else if (thingsInFOV[i] == ' ') {}
		else {
			char thingInFOV;
			thingInFOV = thingsInFOV[i];
			string letterID = "RE";
			letterID = letterID + thingInFOV;
			string thingDef;
			thingDef = getThing("tutorial", letterID);
			thingDef = thingDef.substr(thingDef.length() - 4, 1);
			string accDef;
			accDef = getThing("tutorial", letterID);
			accDef = accDef.substr(0, accDef.length() - 6);
			if (thingDef == "A") {
				cout << accDef << " attacked you! You die!" << endl;
				cout << "Press any key to respawn" << endl;
				system("pause>nul");
				system("cls");
				player.setter("XCO", 10);
				player.stringSetter("YCO", "008");
			}
		}
	}*/

	processEnvironment(player);
	processAP(player);
}

void enemyMovement() {
	srand(time(NULL));
	int randIndex = rand() % 4;
	char directions[] = { 'f', 'b', 'r', 'l' };
}

void enemyDetection(Player &player, int prevComm) {

}

void talkEntity(string diFile, string genName, Player &player) {

	string walkSyns[] = { "walk", "move", "hike", "step", "tour", "skip", "waltz", "dance", "glide", "jaunt", "tramp", "tread", "stroll", "march", "shimmy", "parade", "shuffle", "stretch", "traipse", "perambulate", "trundle", "jaipse", "sashshay", "cha-cha", "bound", "leap", "NULLPTR" };
	string sneakSyns[] = { "sneak", "crawl" };
	string runSyns[] = { "sprint", "run", "jog" };

	string openingChat = getNPCChat(diFile, "T01");
	cout << endl << getIniData("npc", genName, "friendly_name") << ": " << openingChat << endl;

	string chat = "null";
	string chatNum = "01";
	string yesSyns[] = { "yes", "sure" };
	string noSyns[] = { "no", "nope" };
	string sarcSyns[] = { "ugh", "sarcastic" };
	string agrSyns[] = { "aggressive", "AHHH" };
	string noneSyns[] = { "...", "*silence*" };
	string buySyns[] = { "buy", "get" };
	string sellSyns[] = { "sell" };
	while (chat != "exit") {
		cout << player.stringGetter("name") << ": ";
		getline(cin, chat);
		bool failed = false;
		transform(chat.begin(), chat.end(), chat.begin(), ::tolower);
		if (find(begin(sellSyns), end(sellSyns), tokenise(chat)[0]) != end(sellSyns)) {
			vector<string> namesVector;
			vector<string> chatTok = tokenise(chat);
			chatTok.erase(chatTok.begin());
			string itemToSell = join(chatTok, ' ');
			bool itemsold = false;
			vector<string> playerInv = player.getInv();
			for (int i = 0; i < playerInv.size(); i++) {
				string itemName = getIniData("item", playerInv[i], "friendly_name");
				namesVector.push_back(itemName);
			}
			for (int i = 0; i < namesVector.size(); i++) {
				transform(namesVector[i].begin(), namesVector[i].end(), namesVector[i].begin(), ::tolower);
				if (namesVector[i] == itemToSell) {
					string numCode = playerInv[i];


				}
			}
		}
		if (find(begin(buySyns), end(buySyns), tokenise(chat)[0]) != end(buySyns)) {
			vector<string> namesVector;
			vector<string> chatTok = tokenise(chat);
			chatTok.erase(chatTok.begin());
			string itemToTake = join(chatTok, ' ');
			bool itemTook = false;
			vector<string> itemsForSale = tokenise(getNPCChat(diFile, "SELL"));
			vector<string> itemQuants = tokenise(getNPCChat(diFile, "QUAN"));
			vector<int> quants;
			for (int i = 0; i < itemQuants.size(); i++) {
				if (itemQuants[i] != "inf") {
					quants.push_back(atoi(itemQuants[i].c_str()));
				}
				else {
					quants.push_back(-69);
				}
			}
			for (int i = 0; i < itemsForSale.size(); i++) {
				string itemName = getIniData("item", itemsForSale[i], "friendly_name");
				namesVector.push_back(itemName);
			}
			for (int i = 0; i < namesVector.size(); i++) {
				transform(namesVector[i].begin(), namesVector[i].end(), namesVector[i].begin(), ::tolower);
				if (namesVector[i] == itemToTake) {
					if (atoi(getIniData("item", itemsForSale[i], "buy_value").c_str()) <= player.intGetter("money")) {
						if (quants[i] > 0 || quants[i] == -69) {
							player.addInv(itemsForSale[i]);
							int currMon = player.intGetter("money");
							currMon -= atoi(getIniData("item", itemsForSale[i], "buy_value").c_str());
							player.setter("money", currMon);
							if (quants[i] != -69) {
								quants[i]--;
								itemQuants[i] = to_string(quants[i]);
								string quantsToWrite = join(itemQuants, ' ');
								changeLine(diFile + ".wldf", "QUAN", "QUAN " + quantsToWrite);
							}
							break;
						}
					}
					else {
						cout << getIniData("npc", genName, "friendly_name") << ": " << getNPCChat(diFile, "NMN") << endl;
						failed = true;
						itemTook = true;
					}
				}
			}
			if (!itemTook) {
				cout << getIniData("npc", genName, "friendly_name") << ": " << getNPCChat(diFile, "NIN") << endl;
			}
			else {
				if (!failed) {
					cout << getIniData("npc", genName, "friendly_name") << ": " << getNPCChat(diFile, "ABU") << endl;
				}
			}
		}
		else {

			int chatIndex = 69;
			if (find(begin(yesSyns), end(yesSyns), chat) != end(yesSyns)) { chatIndex = 0; }
			else if (find(begin(noSyns), end(noSyns), chat) != end(noSyns)) { chatIndex = 1; }
			else if (find(begin(sarcSyns), end(sarcSyns), chat) != end(sarcSyns)) { chatIndex = 2; }
			else if (find(begin(agrSyns), end(agrSyns), chat) != end(agrSyns)) { chatIndex = 3; }
			else if (find(begin(noneSyns), end(noneSyns), chat) != end(noneSyns)) { chatIndex = 4; }

			if (chatIndex != 69) {
				string letterID = "R" + chatNum;
				chatNum = tokenise(getNPCChat(diFile, letterID))[chatIndex];
				letterID = "T" + chatNum;
				string reply = getNPCChat(diFile, letterID);
				if (tokenise(reply).back() == "%exit%") {
					vector<string> printV = tokenise(reply);
					printV.pop_back();
					cout << getIniData("npc", genName, "friendly_name") << ": " << join(printV, ' ') << endl << endl;
					chat = "exit";
				}
				else if (tokenise(reply).back() == "%shop%") {
					if (getNPCChat(diFile, "SELL") != "") {
						vector<string> itemsForSale = tokenise(getNPCChat(diFile, "SELL"));
						vector<string> itemQuants = tokenise(getNPCChat(diFile, "QUAN"));
						vector<int> quants;
						for (int i = 0; i < itemQuants.size(); i++) {
							if (itemQuants[i] != "inf") {
								quants.push_back(atoi(itemQuants[i].c_str()));
							}
							else {
								quants.push_back(-69);
							}
						}
						vector<string> printV = tokenise(reply);
						printV.pop_back();
						string shopName = getIniData("npc", genName, "friendly_name");
						cout << shopName << ": " << join(printV, ' ') << endl;
						for (int i = 0; i < itemsForSale.size(); i++) {
							if (quants[i] > 0) {
								cout << shopName << ": " << quants[i] << ' ' << getIniData("item", itemsForSale[i], "friendly_name") << " for " << getIniData("item", itemsForSale[i], "buy_value") << " talons each" << endl;
							}
							else if (quants[i] == -69) {
								cout << shopName << ": " << getIniData("item", itemsForSale[i], "friendly_name") << 's' << " for " << getIniData("item", itemsForSale[i], "buy_value") << " talons each" << endl;
							}
							else {}
						}
					}
					else {
						if (tokenise(getNPCChat(diFile, "NOI")).back() == "%exit%") {
							vector<string> printV = tokenise(getNPCChat(diFile, "NOI"));
							printV.pop_back();
							cout << getIniData("npc", genName, "friendly_name") << ": " << join(printV, ' ') << endl << endl;
							chat = "exit";
						}
						else {
							cout << getIniData("npc", genName, "friendly_name") << ": " << getNPCChat(diFile, "NOI") << endl;
						}
					}
				}
				else {
					cout << getIniData("npc", genName, "friendly_name") << ": " << reply << endl;
				}
			}
			else {
				if (chat == "exit") { cout << endl; }
				else if (find(begin(walkSyns), end(walkSyns), tokenise(chat)[0]) != end(walkSyns)) { processCommand(player, chat); chat = "exit"; }
				else if (find(begin(sneakSyns), end(sneakSyns), tokenise(chat)[0]) != end(sneakSyns)) { processCommand(player, chat); chat = "exit"; }
				else if (find(begin(runSyns), end(runSyns), tokenise(chat)[0]) != end(runSyns)) { processCommand(player, chat); chat = "exit"; }
				else {
					cout << getIniData("npc", genName, "friendly_name") << ": " << getNPCChat(diFile, "NOR") << endl;
				}
			}
		}
	}
}