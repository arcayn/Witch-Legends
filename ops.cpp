#include "ops.h"
#define arrSize(array) (sizeof((array))/sizeof((array[0])))

void initiateGame() {
	cout << getDialog("001") << endl;
	cout << getDialog("002") << endl;
	cout << getDialog("003") << endl;
	cout << getDialog("004") << endl;
	cout << getDialog("005") << endl << endl;
	string adventurerName;
	string adventurerHero;
	cout << "What do you tell her is your name?: ";
	getline(cin, adventurerName);
	system("cls");
	cout << '"' << adventurerName << getDialog("006") << endl;	
	cout << getDialog("007") << endl;
	cout << getDialog("008") << endl;
	cout << getDialog("009") << endl << endl;
	bool heroSelected = false;
	int realStats[5];
	while (heroSelected == false) {
		cout << "What do tell her your class is? Choose from: Paladin, Brawler, Thief, Scribe or Mage." << endl << "Alternatively, type 'help', followed by a class, for a breakdown of that class' stats." << endl;
		string option;
		int displayVitality, displayStrength, displayAgility, displayKnowledge, displayHumanity;
		getline(cin, option);
		int statsArray[5];
		if (option[0] == 'h' || option[0] == 'H') {
			bool statsSet = false;
			transform(option.begin(), option.end(), option.begin(), ::tolower);
			if (option == "help") {
				cout << endl << "Hero class not recognised" << endl << endl;
			}
			else if (option[option.length() - 1] == 'n' || option[option.length()] == 'N') {
				statsArray[0] = 8;
				statsArray[1] = 10;
				statsArray[2] = 4;
				statsArray[3] = 2;
				statsArray[4] = 6;
				statsSet = true;
			}
			else if (option[option.length() - 1] == 'r' || option[option.length()] == 'R') {
				statsArray[0] = 10;
				statsArray[1] = 4;
				statsArray[2] = 6;
				statsArray[3] = 2;
				statsArray[4] = 4;
				statsSet = true;
			}
			else if (option[option.length() - 1] == 'f' || option[option.length()] == 'F') {
				statsArray[0] = 6;
				statsArray[1] = 5;
				statsArray[2] = 10;
				statsArray[3] = 7;
				statsArray[4] = 2;
				statsSet = true;
			}
			else if (option[option.length() - 2] == 'b' || option[option.length() - 1] == 'B') {
				statsArray[0] = 2;
				statsArray[1] = 4;
				statsArray[2] = 6;
				statsArray[3] = 10;
				statsArray[4] = 8;
				statsSet = true;
			}
			else if (option[option.length() - 2] == 'g' || option[option.length() - 1] == 'G') {
				statsArray[0] = 2;
				statsArray[1] = 4;
				statsArray[2] = 6;
				statsArray[3] = 8;
				statsArray[4] = 10;
				statsSet = true;
			}
			else {
				cout << "Hero class not recognised" << endl << endl;
			}

		
			displayStrength = statsArray[0];
			displayVitality = statsArray[1];
			displayAgility = statsArray[2];
			displayKnowledge = statsArray[3];
			displayHumanity = statsArray[4];
			
			if (statsSet) {
				cout << endl << "Humanity:  " << displayHumanity << " - " << getDialog("010") << endl;
				cout << "Knowledge: " << displayKnowledge << " - " << getDialog("011") << endl;
				cout << "Agility:   " << displayAgility << " - " << getDialog("012") << endl;
				cout << "Vitality:  " << displayVitality << " - " << getDialog("013") << endl;
				cout << "Strength:  " << displayStrength << " - " << getDialog("014") << endl << endl;
			}
		}
		else if (option == "") {
			cout << "Euan don't be like this" << endl << endl;
		}
		else {
			if (option[option.length() - 1] == 'n' || option[option.length()] == 'N') {
				adventurerHero = "paladin";
				heroSelected = true;
				system("cls");
				cout << '"' << adventurerName << getDialog("015") << endl;
				cout << getDialog("016") << endl;
				cout << getDialog("017") << endl;
				realStats[0] = 8;
				realStats[1] = 10;
				realStats[2] = 4;
				realStats[3] = 2;
				realStats[4] = 6;
			}
			else if (option[option.length() - 1] == 'r' || option[option.length()] == 'R') {
				adventurerHero = "brawler";
				heroSelected = true;
				system("cls");
				cout << getDialog("018") << endl;
				cout << getDialog("019") << endl;
				cout << getDialog("020") << endl;
				realStats[0] = 10;
				realStats[1] = 4;
				realStats[2] = 6;
				realStats[3] = 2;
				realStats[4] = 4;
			}
			else if (option[option.length() - 1] == 'f' || option[option.length()] == 'F') {
				adventurerHero = "thief";
				heroSelected = true;
				system("cls");
				cout << getDialog("021") << endl;
				cout << getDialog("022") << endl;
				cout << getDialog("023") << endl;
				cout << getDialog("024") << endl;
				realStats[0] = 6;
				realStats[1] = 5;
				realStats[2] = 10;
				realStats[3] = 7;
				realStats[4] = 2;
			}
			else if (option[option.length() - 2] == 'b' || option[option.length() - 1] == 'B') {
				adventurerHero = "scribe";
				heroSelected = true;
				system("cls");
				cout << "'" << adventurerName << getDialog("025") << endl;
				cout << getDialog("026") << endl;
				cout << getDialog("027") << endl;
				cout << getDialog("028") << endl;
				realStats[0] = 2;
				realStats[1] = 4;
				realStats[2] = 6;
				realStats[3] = 10;
				realStats[4] = 8;
			}
			else if (option[option.length() - 2] == 'g' || option[option.length() - 1] == 'G') {
				adventurerHero = "mage";
				heroSelected = true;
				system("cls");
				cout << getDialog("029") << endl;
				cout << getDialog("030") << endl;
				realStats[0] = 2;
				realStats[1] = 4;
				realStats[2] = 6;
				realStats[3] = 8;
				realStats[4] = 10;
			}
			else {
				cout << "Hero class not recognised. Try again." << endl << endl;
			}
		}
	}
	cout << getDialog("031") << endl;
	cout << getDialog("032") << endl;
	cout << getDialog("033") << endl;
	cout << getDialog("034") << adventurerName << ',' << endl << getDialog("035") << endl;
	cout << getDialog("036") << endl;
	cout << getDialog("037") << endl << endl;
	
	int adventurerMaxHealth = realStats[1] * 40;
	ofstream playerData;
	playerData.open("data.wld");
	playerData << endl;
	playerData << "001 " << realStats[1] << endl;
	playerData << "002 " << realStats[3] << endl;
	playerData << "003 " << realStats[4] << endl;
	playerData << "004 " << realStats[0] << endl;
	playerData << "005 " << realStats[2] << endl;
	playerData << "006 " << adventurerHero << endl;
	playerData << "007 " << 0 << endl;
	playerData << "008 " << adventurerMaxHealth << endl;
	playerData << "009 " << adventurerMaxHealth << endl;
	playerData << "010 " << 1 << endl;
	playerData << "011 " << realStats[4]*40 << endl;
	playerData << "012 " << "tutorial" << endl;
	playerData << "013 " << getThing("tutorial", "YST") << endl;
	playerData << "014 " << atoi(getThing("tutorial", "XST").c_str()) << endl;
	playerData << "015 " << adventurerName << endl;
	playerData << "016 " << 3 << endl;
	playerData << "MON" << 0 << endl << endl;

	vector<string> profileAttribs = makeProfile();
	string attribIds[20] = { "GEN", "RAC", "EYE", "LEN", "HAI", "NOS", "SKI", "TON", "FHA", "HEI", "MEA", "BUI", "LIM", "DES", "FEA", "SUG", "CLA", "PAR", "ICO", "CHE" };
	for (int i = 0; i < 20; i++) {
		playerData << attribIds[i] << ' ' << profileAttribs[i] << endl;
	}
	playerData << endl;

	playerData.close();
	ofstream startData;
	startData.open("starter.wld");
	startData << "started!";
	startData.close();
	startTheGame();
}

void reduceAP(Player &player) {
	double apSub = player.intGetter("agility") / (double)5;
	apSub += 1.8;
	double newAp = player.dubGetter("AP") - apSub;
	player.dubSetter("AP", newAp);
}
void refundAP(Player &player, int refund) {
	double newAp = player.dubGetter("AP") + refund;
	player.dubSetter("AP", newAp);
}

void startTheGame() {
	Player player(getStat("015"), getStat("006"), atoi(getStat("004").c_str()), atoi(getStat("001").c_str()), atoi(getStat("005").c_str()), atoi(getStat("002").c_str()), atoi(getStat("003").c_str()), atoi(getStat("009").c_str()), atoi(getStat("010").c_str()), atoi(getStat("007").c_str()), atoi(getStat("011").c_str()), atoi(getStat("008").c_str()), getStat("013"), atoi(getStat("014").c_str()), getStat("012"), atof(getStat("016").c_str()), retrieveInv(), atoi(getStat("MON").c_str()));
	cout << getDialog("VER") << endl;
	processEnvironment(player);
	reduceAP(player);
	processAP(player);
	while (true) {
		getComm(player);
		writeData(player);
	}	
}

void getComm(Player &player) {
	string command;
	cout << "> ";
	//gameEsp(player);
	getline(cin, command);
	processCommand(player, command);
}

void writeData(Player &player) {

	string attribIds[20] = { "GEN", "RAC", "EYE", "LEN", "HAI", "NOS", "SKI", "TON", "FHA", "HEI", "MEA", "BUI", "LIM", "DES", "FEA", "SUG", "CLA", "PAR", "ICO", "CHE" };
	string descArr[20];

	for (int i = 0; i < 20; i++) {
		descArr[i] = getStat(attribIds[i]);
	}

	ofstream playerData;
	playerData.open("data.wld");
	playerData << endl;
	playerData << "001 " << player.intGetter("vitality") << endl;
	playerData << "002 " << player.intGetter("knowledge") << endl;
	playerData << "003 " << player.intGetter("humanity") << endl;
	playerData << "004 " << player.intGetter("strength") << endl;
	playerData << "005 " << player.intGetter("agility") << endl;
	playerData << "006 " << player.stringGetter("hero") << endl;
	playerData << "007 " << player.intGetter("XP") << endl;
	playerData << "008 " << player.intGetter("maxHealth") << endl;
	playerData << "009 " << player.intGetter("health") << endl;
	playerData << "010 " << player.intGetter("level") << endl;
	playerData << "011 " << player.intGetter("mana") << endl;
	playerData << "012 " << player.stringGetter("position") << endl;
	playerData << "013 " << player.stringGetter("YCO") << endl;
	playerData << "014 " << player.intGetter("XCO") << endl;
	playerData << "015 " << player.stringGetter("name") << endl;
	playerData << "016 " << player.dubGetter("AP") << endl;
	playerData << "MON " << player.intGetter("money") << endl;

	
	for (int i = 0; i < 20; i++) {
		playerData << attribIds[i] << ' ' << descArr[i] << endl;
	}

	playerData.close();
	ofstream invData;
	invData.open("inventory.wld");
	for (int i = 0; i < player.getInv().size(); i++) {
		invData << player.getInv()[i] << endl;
	}
}