#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

const int inf = 1 << 30;

vector<string> getDroppedItems(string location, string XCO, string YCO);
void appendLine(string line, string file);
string getLevelLine(string location, string lineNumber);
void startTheGame();
void initiateGame();
string join(vector<string> vec, char delim);
string getDialog(string lineNumber);
string getNPCChat(string location, string lineNumber);
vector<string> getInv();
vector<string> getQuests();
vector<vector<int>> adjMatrix();
vector<int> dijk(int A, int B, vector< vector<int> > adj);
bool isDialogWanted(const std::string & line, string lineNumber);
string getStat(string lineNumber);
bool isStatWanted(const std::string & line, string lineNumber);
string getLevelData(string location, string lineNumber, int XCO);
bool isDataWanted(const std::string & line, string lineNumber);
string getThing(string location, string lineNumber);
string getThingIni(string location, string lineNumber);
string getIniData(string type, string numCode, string value);
void changeLine(string file, string lineNumber, string newLine);
bool isWanted(const std::string & line, string lineNumber);
vector<string> makeProfile();
string getEntityData(string location, string lineNumber);
vector<string> tokenise(string str);
string changeYCO(string currY, int change);
string replaceDelims(string lineNumber);
vector<string> retrieveInv();
vector<string> returnGameGrid(string location);
string textColor(int color = 7, string Message = "");


