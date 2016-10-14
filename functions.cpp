#include "resource.h"

bool colors = true;

vector<string> tokenise(string str) {
	istringstream buf(str);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end);
	return tokens;
}

string changeYCO(string currY, int change) {
	int newY = atoi(currY.c_str()) + change;
	string accY = to_string(newY);
	string zeroPad = string(3 - accY.length(), '0');
	return zeroPad + accY;
}

/////////////////////////////////////DIALOOOOOG
string getDialog(string lineNumber) {
	ifstream fin("dialog.wld");

	string line;
	while (getline(fin, line))
	{
		if (isDialogWanted(line, lineNumber)) {
			vector<string> linetok = tokenise(line);
			string returnVal = linetok[1];
			for (int i = 2; i < linetok.size(); i++) {
				returnVal += " "+linetok[i];
			}
			return returnVal;
		}
	}
}
bool isDialogWanted(const string & line, string lineNumber)
{
	return (line.find(lineNumber) == 0);
}
////////////////////////////////////STATSSS
string getStat(string lineNumber) {
	ifstream fin("data.wld");

	string line;
	while (getline(fin, line))
	{
		if (isStatWanted(line, lineNumber)) {
			int statLength = line.length() - 4;
			return line.substr(4, statLength);
		}
	}
}
bool isStatWanted(const string & line, string lineNumber)
{
	return (line.find(lineNumber) == 0);
}
/////////////////////////////////////LEVELLLLLL
string getLevelData(string location, string lineNumber, int XCO) {
	string ext = ".wlad";
	ifstream fin(location + ext);

	string line;
	while (getline(fin, line))
	{
		if (isDataWanted(line, lineNumber)) {
			int dataLength = line.length() - 4;
			return line.substr(4, dataLength).substr(XCO-3, 5);
		}
	}
}
bool isDataWanted(const string & line, string lineNumber)
{
	return (line.find(lineNumber) == 0);
}

void appendLine(string line, string file) {
	ifstream fin(file);
	string line;
	vector<string> fileVec;
	while (getline(fin, line)) {
		fileVec.push_back(line);
	}
	ofstream fout(file);
	for (int i = 0; i < fileVec.size(); i++) {
		fout << fileVec[i] << endl;
	}
	fout << line;
}

vector<string> getDroppedItems(string location, string XCO, string YCO) {
	string ext = ".wlad";
	ifstream fin(location + ext);
	string line;
	vector<string> retVec;
	bool itemHere = false;
	while (getline(fin, line)) {
		if (line.find("DR") == 0) {
			vector<string> lineTok = tokenise(line);
			if (lineTok[1] == YCO && lineTok[2] == XCO) {
				lineTok.erase(lineTok.begin()); lineTok.erase(lineTok.begin()+1); lineTok.erase(lineTok.begin()+2);
				string toReturn = join(lineTok, ' ');
				retVec.push_back(toReturn);
				itemHere = true;
			}
		}
	}
	if (!itemHere) {
		retVec.push_back("NULL");
	}
	return retVec;
}
////////////////////////////////////THINGSSSS
string getThing(string location, string lineNumber) {
	string ext = ".wlad";
	ifstream fin(location + ext);

	string line;
	while (getline(fin, line))
	{
		if (line.find(lineNumber) == 0) {
			vector<string> linetok = tokenise(line);
			string returnVal = linetok[2];
			for (int i = 3; i < linetok.size(); i++) {
				returnVal += " " + linetok[i];
			}
			return returnVal;
		}
	}
}

string getLevelLine(string location, string lineNumber) {
	string ext = ".wlad";
	ifstream fin(location + ext);

	string line;
	while (getline(fin, line))
	{
		if (line.find(lineNumber) == 0) {
			vector<string> linetok = tokenise(line);
			string returnVal = linetok[1];
			for (int i = 2; i < linetok.size(); i++) {
				returnVal += " " + linetok[i];
			}
			return returnVal;
		}
	}
}

string getThingIni(string location, string lineNumber) {
	string ext = ".wlad";
	ifstream fin(location + ext);

	string line;
	while (getline(fin, line))
	{
		if (line.find(lineNumber) == 0) {
			return tokenise(line)[1];
		}
	}
}

string getNPCChat(string location, string lineNumber) {
	string ext = ".wldf";
	ifstream fin(location + ext);

	string line;
	while (getline(fin, line))
	{
		if (line.find(lineNumber) == 0) {
			vector<string> linetok = tokenise(line);
			if (linetok.size() < 2) { return ""; }
			else {
				string joinLine = linetok[1];
				for (int i = 2; i < linetok.size(); i++) {
					joinLine += ' ' + linetok[i];
				}
				return joinLine;
			}
		}
	}
}

string getEntityData(string location, string lineNumber) {
	string ext = ".wled";
	ifstream fin(location + ext);

	string line;
	bool returned = false;
	while (getline(fin, line))
	{
		if (line.find(lineNumber) == 0) {
			vector<string> linetok = tokenise(line);
			string returnVal = linetok[1];
			for (int i = 2; i < linetok.size(); i++) {
				returnVal += " " + linetok[i];
			}
			returned = true;
			return returnVal;
		}
	}
	if (!returned) { return "NULLIUM"; }
}
/////////////////////////////////////

string getIniData(string type, string numCode, string value) {
	string ext = ".ini";
	ifstream fin(type + 's' + ext);

	string line;
	string subline;
	bool incomplete = true;
	while (getline(fin, line))
	{
		if (line.find('['+numCode+']') == 0) {
			while (getline(fin, subline)) {
				if (subline.find('[') != 0) {
					if (subline.find(value) == 0) {
						int valLength = value.length() + 3;
						string data = subline.substr(valLength, subline.length() - valLength);
						incomplete = false;
						return data;
					}
				}
				else { break; }
			}
		}
	}
	if (incomplete) {
		return "<value not found>";
	}
}

vector<string> returnGameGrid(string location) {
	vector<string> gameGrid;
	string ext = ".wlad";
	ifstream fin(location + ext);
	string line;
	bool isGameGrid = false;
	
	while (getline(fin, line)) {
		if (line == "BEGINGAMEGRID") {
			isGameGrid = true;
		}
		else if (line == "ENDGAMEGRID") {
			isGameGrid = false;
		}
		else if (isGameGrid) {
			int mapLength = line.length() - 4;
			gameGrid.push_back(line.substr(4, mapLength));
		}
		else {}
	}
	return gameGrid;

}

vector<string> retrieveInv() {
	ifstream fin("inventory.wld");
	vector<string> pulledInv;
	string line;
	while (getline(fin, line)) {
		pulledInv.push_back(line);
	}
	return pulledInv;
}

void changeLine(string file, string lineNumber, string newLine) {
	ifstream finy(file);

	int linesOfFile;
	string line;
	while (getline(finy, line))
	{
		if (isWanted(line, "LIN")) {
			int dataLength = line.length() - 4;
			string numbers = line.substr(4, dataLength);
			linesOfFile = atoi(numbers.c_str());
		}
	}
	finy.close();
	ifstream fin(file);
	line = "";
	vector<string> lines;
	while (getline(fin, line))
	{
		if (isWanted(line, lineNumber)) {
			lines.push_back(newLine);
		}
		else {
			lines.push_back(line);
		}
	}
	fin.close();
	ofstream writeFile;
	writeFile.open(file);
	for (int i = 0; i < lines.size(); i++) {
		writeFile << lines[i] << endl;
	}
}
bool isWanted(const string & line, string lineNumber)
{
	return (line.find(lineNumber) == 0);
}

string textColor(int color, string Message) {
	if (colors) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	return Message;
}

string replaceDelims(string lineNumber) {
	string attribIds[20] = { "GEN", "RAC", "EYE", "LEN", "HAI", "NOS", "SKI", "TON", "FHA", "HEI", "MEA", "BUI", "LIM", "DES", "FEA", "SUG", "CLA", "PAR", "ICO", "CHE" };
	string attribs[20] = { "gender", "race", "eyes", "hlength", "hair", "nose", "skin", "tone", "facialhair", "height", "specheight", "build", "limbs", "limbdesc", "feature", "suggestion", "clan", "bodypart", "icon", "cheekbones" };

	string lin = getDialog(lineNumber);
	string linbk = lin;
	bool isVal = false;
	string currVal = "";

	for (int i = 0; i < lin.length(); i++) {
		if (isVal) {
			currVal = currVal + lin[i];
			if (lin[i] == '%') {
				isVal = false;
				string toSearchVal = '%' + currVal;
				if (toSearchVal == "%class%") {
					int valIndex = linbk.find(toSearchVal);
					string newVal = getStat("006");
					linbk.replace(valIndex, toSearchVal.length(), newVal);
				}
				else {
					int valIndex = linbk.find(toSearchVal);
					string accVal = currVal.substr(0, currVal.length() - 1);
					int idIndex = distance(begin(attribs), find(begin(attribs), end(attribs), accVal));
					string attribId = attribIds[idIndex];
					string newVal = getStat(attribId);
					linbk.replace(valIndex, toSearchVal.length(), newVal);
				}
				currVal = "";
			}
		}
		else {
			if (lin[i] == '%') {
				isVal = true;
			}
			else {}
		}

	}
	return linbk;
}

vector<string> getQuests() {
	vector<string> quests;
	ifstream fin("currQuests.wld");
	string line;
	while (getline(fin, line)) {
		quests.push_back(line);
	}
	return quests;
}

vector<string> getInv() {
	vector<string> quests;
	ifstream fin("inventory.wld");
	string line;
	while (getline(fin, line)) {
		quests.push_back(line);
	}
	return quests;
}

vector<vector<int>> adjMatrix() {
	ifstream fin("connections.wlad");
	string line;
	int lines = atoi(getThing("connections", "CONS").c_str());
	vector<vector<int>> retVec;
	while (getline(fin, line)) {
		if (line.find("CONS") == 0) {}
		else {
			vector<int> currLine;
			vector<string> currCons = tokenise(line);
			currCons.erase(currCons.begin(), currCons.begin() + 2);
			vector<int> currConsInts;
			for (int i = 0; i < currCons.size(); i++) {
				currConsInts.push_back(atoi(currCons[i].c_str()));
			}
			for (int i = 0; i < lines; i++) {
				if (find(currConsInts.begin(), currConsInts.end(), i) != currConsInts.end()) {
					currLine.push_back(1);
				}
				else {
					currLine.push_back(0);
				}
			}
			retVec.push_back(currLine);
		}
	}
	return retVec;
}

vector<int> dijk(int A, int B, vector<vector<int>> adj) {
	int n = adj.size();
	vector<int> dist(n);
	vector<int> totPath;
	vector<bool> vis(n);

	for (int i = 0; i < n; ++i) {
		dist[i] = inf;
	}
	dist[A] = 0;

	for (int i = 0; i < n; ++i) {
		int cur = -1;
		for (int j = 0; j < n; ++j) {
			if (vis[j]) continue;
			if (cur == -1 || dist[j] < dist[cur]) {
				cur = j;
			}
		}

		vis[cur] = true;
		totPath.push_back(cur);
		for (int j = 0; j < n; ++j) {
			int path = dist[cur] + adj[cur][j];
			if (path < dist[j]) {
				dist[j] = path;
			}
		}
	}

	//return dist[B];
	totPath.push_back(dist[B]);
	return totPath;
}

string join(vector<string> vec, char delim) {
	string ret = vec[0];
	for (int i = 1; i < vec.size(); i++) {
		ret += delim + vec[i];
	}
	return ret;
}
 