#include "resource.h"
#define arrSize(array) (sizeof((array))/sizeof((array[0])))

// gender
// race
// eyes
// hair
// skin
// clan
// These attributes can chosen

vector<string> makeProfile() {
	string genders[] = { " male", " female", "n androgyne", " fluid" };
	string races[] = { "dwarf", "elf", "human", "halfling", "primal", "sapien", "woodfolk", "waterfolk", "spiritform" };
	string eyes[] = { "blue", "black", "violet", "green", "abyssal", "red", "grey", "brown" };
	string lengths[] = { "short", "long", "styled" };
	string hairs[] = { "black", "brown", "blonde", "white", "fiery red", "violet" };
	string cheeks[] = { "pronounced", "sharp", "soft", "almost invisible", "high", "noble", "low" };
	string noses[] = { "roman", "long", "pointed", "small", "upturned", "crooked" };
	string skin[] = { "rich", "soft", "stark", "translucent", "rough" };
	string tones[] = { "brown", "black", "white", "bleached", "dark", "olive", "rosy", "sarcoline" };
	string facialhair[] = { ", sporting a short goatee", ", with a light dusting of stubble", ", a long beard drooping from the chin", ", and a carefully groomed beard around the jaw" };
	string heights[] = { "short", "tall", "of average height" };
	string specheightsTall[] = { "5'10", "6'", "6'2", "6'4", "7'"};
	string specheights[] = { "5'4", "5'6", "5'8", "5'10", "6'" };
	string specheightsShort[] = { "5'4", "5'2", "5'", "4'8", "4'6" };
	string builds[] = { "strong", "stocky", "lean", "slim", "large", "small" };
	string limbs[] = { "long", "short" };
	string limbdescs[] = { "gangly", "slim", "strong", "toned", "broad" };
	string features[] = { "tattoo", "scar", "birthmark" };
	string suggestions[] = { "military", "intellectual", "aristocratic", "criminal", "adventurous", "noble", "highborn" };
	string clans[] = { "boros", "riza", "sata", "lux", "fidel", "crestis", "terrus" };
	string bodyparts[] = { "arm", "leg", "neck", "ankle", "hand" };
	string icons[] = { " bear", " lion", " sextant", "n hourglass", " skeleton", " skull", " star", " lantern", " sphinx", " crown", " ouroboros", " pentangle", " sphere", " mountain" };
	string values[20];

	srand(time(NULL));
	int randIndex;
	int indexLen;
	string nonSpecs[] = { "human", "dwarf", "primal", "halfling", "" };
	string subs[] = { "dwarf", "primal", "halfling", "" };
	int binRand = rand() % 2;
	int triRand = rand() % 3;

	//gender

	randIndex = rand() % 4;
	values[0] = genders[randIndex];

	//race

	randIndex = rand() % 9;
	values[1] = races[randIndex];

	//eyes

	if (find(begin(nonSpecs), end(nonSpecs), values[1]) != end(nonSpecs)) {
		string activeArr[] = { "blue", "black", "green", "red", "grey", "brown" };
		indexLen = 6;
		randIndex = rand() % indexLen;
		values[2] = activeArr[randIndex];
	}
	else {
		vector<string> activeArr(begin(eyes), end(eyes));
		indexLen = activeArr.size();
		randIndex = rand() % indexLen;
		values[2] = activeArr[randIndex];
	}

	//hair length

	randIndex = rand() % 3;
	values[3] = lengths[randIndex];

	//hair colour

	if (find(begin(nonSpecs), end(nonSpecs), values[1]) != end(nonSpecs)) {
		if (values[1] == "human") {
			string activeArr[] = { "black", "brown", "blonde", "fiery red" };
			indexLen = 4;
			randIndex = rand() % indexLen;
			values[4] = activeArr[randIndex];
		}
		else {
			string activeArr[] = { "brown", "blonde", "fiery red" };
			indexLen = 3;
			randIndex = rand() % indexLen;
			values[4] = activeArr[randIndex];
		}
	}
	else {
		vector<string> activeArr(begin(hairs), end(hairs));
		indexLen = activeArr.size();
		randIndex = rand() % indexLen;
		values[4] = activeArr[randIndex];
	}

	//cheekbones

	if (find(begin(subs), end(subs), values[1]) != end(subs)) {
		string activeArr[] = { "pronounced", "sharp", "soft", "almost invisible", "low" };
		indexLen = 5;
		randIndex = rand() % indexLen;
		values[19] = activeArr[randIndex];
	}
	else {
		vector<string> activeArr(begin(cheeks), end(cheeks));
		indexLen = activeArr.size();
		randIndex = rand() % indexLen;
		values[19] = activeArr[randIndex];
	}

	//nose

	if (find(begin(subs), end(subs), values[1]) != end(subs)) {
		string activeArr[] = { "long", "pointed", "small", "crooked" };
		indexLen = 4;
		randIndex = rand() % indexLen;
		values[5] = activeArr[randIndex];
	}
	else {
		vector<string> activeArr(begin(noses), end(noses)-1);
		indexLen = activeArr.size();
		randIndex = rand() % indexLen;
		values[5] = activeArr[randIndex];
	}

	//skin

	if (values[4] == "fiery red" || values[4] == "blonde") {
		string firstArr[] = { "rich", "soft", "rough" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "rosy", "sarcoline", "white" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else if (values[4] == "violet" && binRand == 0) {
		string firstArr[] = { "stark", "translucent" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "bleached", "white" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else if (values[4] == "violet") {
		string firstArr[] = { "rich", "soft", "rough" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "black", "dark" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else if (values[4] == "black" && binRand == 0) {
		string firstArr[] = { "stark", "translucent" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "bleached", "white" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else if (values[4] == "black") {
		string firstArr[] = { "rich", "soft", "rough" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "brown", "black", "dark", "white", "olive", "rosy", "sarcoline" };
		indexLen = 7;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else if (values[4] == "white") {
		string firstArr[] = { "stark", "translucent" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "bleached", "white" };
		indexLen = 2;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else if (values[4] == "brown") {
		string firstArr[] = { "rich", "soft", "rough" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[6] = firstArr[randIndex];
		string arrTwo[] = { "brown", "black", "dark", "white", "olive", "rosy", "sarcoline" };
		indexLen = 7;
		randIndex = rand() % indexLen;
		values[7] = arrTwo[randIndex];
	}
	else { 
		values[6] = "NULL";
		values[7] = "NULL";
	}

	//facial hair

	if (values[0] == "male" && find(begin(nonSpecs), end(nonSpecs), values[1]) != end(nonSpecs)) {
		indexLen = 4;
		randIndex = rand() % indexLen;
		values[8] = facialhair[randIndex];
	}
	else {
		values[8] = "";
	}

	//height - general

	if (values[1] == "dwarf" || values[1] == "halfling") {
		values[9] = "short";
	}
	else if (values[1] == "treefolk" || values[1] == "spiritform") {
		values[9] = "tall";
	}
	else if (binRand == 1) {
		values[9] = "of average height";
	}
	else if (find(begin(nonSpecs), end(nonSpecs), values[1]) != end(nonSpecs)) {
		values[9] = "short";
	}
	else {
		values[9] = "tall";
	}

	//height

	if (values[9] == "short") {
		indexLen = 5;
		randIndex = rand() % indexLen;
		values[10] = specheightsShort[randIndex];
	}
	if (values[9] == "of average height") {
		indexLen = 5;
		randIndex = rand() % indexLen;
		values[10] = specheights[randIndex];
	}
	if (values[9] == "tall") {
		indexLen = 5;
		randIndex = rand() % indexLen;
		values[10] = specheightsTall[randIndex];
	}

	//build

	if (values[1] == "human") {
		indexLen = 6;
		randIndex = rand() % indexLen;
		values[11] = builds[randIndex];
	}
	else if (find(begin(subs), end(subs), values[1]) != end(subs)) {
		string firstArr[] = { "strong", "stocky", "large" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[11] = firstArr[randIndex];
	}
	else {
		string firstArr[] = { "strong", "slim", "lean" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[11] = firstArr[randIndex];
	}

	//limbs

	if (values[1] == "human") {
		string shortAdjs[] = { "strong", "stocky", "large", "" };
		if (find(begin(shortAdjs), end(shortAdjs), values[1]) != end(shortAdjs)) {
			values[12] = "short";
		}
		else {
			values[12] = "long";
		}
	}
	else if (find(begin(subs), end(subs), values[1]) != end(subs)) {
		values[12] = "short";
	}
	else {
		values[12] = "long";
	}

	//limb descriptions

	if (values[12] == "long") {
		string limbDescArr[] = { "gangly", "slim", "toned" };
		values[13] = limbDescArr[triRand];
	}
	else if (values[12] == "short") {
		string limbDescArr[] = { "strong", "broad", "toned" };
		values[13] = limbDescArr[triRand];
	}

	//feature

	if (find(begin(subs), end(subs), values[1]) != end(subs)) {
		values[14] = features[rand() % 2];
	}
	else {
		int randTotal = rand() % 2;
		randTotal++;
		values[14] = features[randTotal];
	}
	

	//suggestions

	if (values[14] == "tattoo") {
		if (find(begin(nonSpecs), end(nonSpecs), values[1]) != end(nonSpecs)) {
			string firstArr[] = { "military", "criminal", "aristocratic", "intellectual" };
			indexLen = 4;
			randIndex = rand() % indexLen;
			values[15] = firstArr[randIndex];
		}
		else {
			string firstArr[] = { "military", "aristocratic", "intellectual" };
			indexLen = 3;
			randIndex = rand() % indexLen;
			values[15] = firstArr[randIndex];
		}
		
	}
	if (values[14] == "birthmark") {
		string firstArr[] = { "highborn", "noble", "aristocratic" };
		indexLen = 3;
		randIndex = rand() % indexLen;
		values[15] = firstArr[randIndex];
	}
	if (values[14] == "scar") {
		if (find(begin(nonSpecs), end(nonSpecs), values[1]) != end(nonSpecs)) {
			string firstArr[] = { "military", "criminal", "adventurous" };
			indexLen = 3;
			randIndex = rand() % indexLen;
			values[15] = firstArr[randIndex];
		}
		else {
			string firstArr[] = { "military", "adventurous" };
			indexLen = 2;
			randIndex = rand() % indexLen;
			values[15] = firstArr[randIndex];
		}
	}

	//clan

	indexLen = 7;
	randIndex = rand() % indexLen;
	values[16] = clans[randIndex];
	int clanID = randIndex;

	//body part

	indexLen = 5;
	randIndex = rand() % indexLen;
	values[17] = bodyparts[randIndex];

	//icon

	int indexStart = clanID * 2;
	indexStart += binRand;
	values[18] = icons[indexStart];

	//for (int i = 0; i < 20; i++) {
	//	cout << values[i] << endl;
	//}

	vector<string> valueVector(begin(values), end(values));

	return valueVector;
}